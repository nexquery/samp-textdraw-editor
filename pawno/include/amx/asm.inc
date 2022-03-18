// Copyright (C) 2012 Zeex
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#if defined ASM_INC
	#endinput
#endif
#define ASM_INC

#include <core>

#include "amx_base"
#include "amx_header"
#include "amx_memory"
#include "asm_macros"
#include "dynamic_call"
#include "opcode"

#if !defined ASM_MAX_LABELS
	#define ASM_MAX_LABELS (8)
#endif

enum AsmError {
	ASM_ERROR_NONE,
	ASM_ERROR_OPCODE,
	ASM_ERROR_OPERAND,
	ASM_ERROR_SPACE,
	ASM_ERROR_LABEL_OVERFLOW,
	ASM_ERROR_LABEL_DUPLICATE,
};

enum AsmContext {
	AsmContext_buffer,
	AsmContext_buffer_size,
	AsmContext_buffer_offset,
	AsmContext_error,
	AsmContext_error_handler,  // ErrorHandler(ctx[AsmContext])
	AsmContext_label_names[ASM_MAX_LABELS],
	// All labels in PAWN should be 4-byte-aligned (1 cell in 32-bit).  This
	// means the bottom two bits are always `0b00`.  We re-use this data to
	// store two bits of information - is this label resolved (i.e. do we know
	// the true address yet), and is this use of the label relative or absolute?
	// 
	// If the label is NOT resolved, the current value is the start pointer of a
	// linked list of jump-ahead uses of the label (relative to DAT), i.e. jumps
	// waiting to know the label's address when it is eventually defined.  If
	// the label IS resolved, it is just the absolute address of the label
	// (relative to COD) so that any new uses can be resolved instantly.  The
	// lowest bit determines which.
	// 
	// If a jump to an unknown label is emitted, the value is the next item in
	// the linked list (potentially NULL), and the bottom bit is instead used to
	// determine which jump type this is - relative (1) or absolute (0).
	AsmContext_labels[ASM_MAX_LABELS],
};

stock const ASM_ARGUMENTS_OFFSET    =  0x0C;
stock const ASM_LOCALS_OFFSET       = -0x04;
stock const ASM_CALLER_FRAME_OFFSET =  0x00;
stock const ASM_RETURN_ADDR_OFFSET  =  0x04;

stock const ASM_CTRL_COD = 0;
stock const ASM_CTRL_DAT = 1;
stock const ASM_CTRL_HEA = 2;
stock const ASM_CTRL_STP = 3;
stock const ASM_CTRL_STK = 4;
stock const ASM_CTRL_FRM = 5;
stock const ASM_CTRL_CIP = 6;
stock const ASM_CTRL_JIT = 7;
stock const ASM_CTRL_JMP = 8;

static gPreviousWriteOffset = cellmin;

// Internal functions:

static stock AsmError:AsmRaiseError(ctx[AsmContext], AsmError:error) {
	if (error != ASM_ERROR_NONE) {
		AsmSetError(ctx, error);
		if (ctx[AsmContext_error_handler] != 0) {
			CallFunction(ctx[AsmContext_error_handler], ref(ctx));
		}
	}
	return error;
}

static stock AsmError:AsmEmitCell(ctx[AsmContext], value) {
	if (ctx[AsmContext_buffer_offset] >= ctx[AsmContext_buffer_size]) {
		return AsmRaiseError(ctx, ASM_ERROR_SPACE);
	}

	WriteAmxMemory(ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset], value);
	ctx[AsmContext_buffer_offset] += 4;

	return ASM_ERROR_NONE;
}

// Label functions:

#define AsmIsLabelResolved(%2,%0)    (%2[AsmContext_labels][(%0)] & 1)
#define AsmIsJumpRelative(%0)        ((%0) & 1)
#define AsmSetJumpRelative(%2,%0,%1) (%2[AsmContext_labels][(%0)] & (%1))
#define AsmGetLabel(%2,%0)           (%2[AsmContext_labels][(%0)] & ~1)
#define AsmSetLabel(%2,%0,%1)        (%2[AsmContext_labels][(%0)] = (%1) | 1)

static stock AsmHashLabel(const label[]) {
	// Return the Bernstein hash of this label.  This is NOT a cryptographically
	// secure hash, but is sufficient for our uses.
	new hash = -1;
	new i = -1;
	new ch = 0;
	while ((ch = label[++i])) {
		hash = hash * 33 + ch;
	}
	return hash;
}

static stock AsmFindLabelIndex(const ctx[AsmContext], hash) {
	for (new i = 0; i != ASM_MAX_LABELS; ++i) {
		if (ctx[AsmContext_label_names][i] == hash) {
			return i;
		}
	}
	return -1;
}

stock AsmError:AsmEmitLabelStringize(ctx[AsmContext], const label[]) {
	// Everything works on the hashes - it saves storing the strings.
	new hash = AsmHashLabel(label);
	// See if this label already exists.
	new idx = AsmFindLabelIndex(ctx, hash);
	// Get the true address.  Use an offset of -8 because
	// `AsmGetJumpAddressFromOffset` assumes the jump is from the start of the
	// next instruction (8 bytes later), while we want it from right here, so
	// shift back accordingly.
	new datAddr = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset];
	new codAddr = AsmGetJumpAddressFromOffset(ctx, -8);
	if (idx == -1) {
		// Doesn't exist.  Get a free slot.
		idx = AsmFindLabelIndex(ctx, 0);
		if (idx == -1) {
			return AsmRaiseError(ctx, ASM_ERROR_LABEL_OVERFLOW);
		}
		ctx[AsmContext_label_names][idx] = hash;
	}
	if (AsmIsLabelResolved(ctx, idx)) {
		// Check that no other labels have the same name.
		return AsmRaiseError(ctx, ASM_ERROR_LABEL_DUPLICATE);
	} else {
		// Loop over all the pending items in the linked list.
		new cur = AsmGetLabel(ctx, idx);
		while (cur) {
			new next = ReadAmxMemory(cur);
			if (AsmIsJumpRelative(next)) {
				WriteAmxMemory(cur, datAddr - cur - 4);
			} else {
				WriteAmxMemory(cur, codAddr);
			}
			cur = next & ~1;
		}
	}
	// Store the label's absolute address, along with a flag to mark that it is
	// resolved.
	AsmSetLabel(ctx, idx, codAddr);
	return ASM_ERROR_NONE;
}

stock AsmError:AsmEmitJumpStringize(ctx[AsmContext], const label[], bool:relative) {
	new hash = AsmHashLabel(label);
	new idx = AsmFindLabelIndex(ctx, hash);
	new datAddr = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset];
	new AsmError:error = ASM_ERROR_NONE;
	if (idx == -1) {
		// Doesn't exist.  Get a free slot.
		idx = AsmFindLabelIndex(ctx, 0);
		if (idx == -1) {
			return AsmRaiseError(ctx, ASM_ERROR_LABEL_OVERFLOW);
		}
		ctx[AsmContext_label_names][idx] = hash;
	}
	if (AsmIsLabelResolved(ctx, idx)) {
		// The label was in the past, jump to that.
		new cur = AsmGetLabel(ctx, idx);
		if (relative) {
			error = AsmEmitCell(ctx, cur - datAddr - 4);
		} else {
			error = AsmEmitCell(ctx, cur);
		}
	} else {
		// The label is not yet known, store this use in the list.
		new cur = AsmGetLabel(ctx, idx);
		if (relative) {
			error = AsmEmitCell(ctx, cur | 1);
		} else {
			error = AsmEmitCell(ctx, cur);
		}
		if (error == ASM_ERROR_NONE) {
			// Store to the list only if the output was successful.
			ctx[AsmContext_labels][idx] = datAddr;
		}
	}
	return error;
}

// Core functions:

stock AsmError:AsmEmitOpcode(ctx[AsmContext], Opcode:opcode) {
	if (opcode <= OP_NONE || _:opcode >= NUM_OPCODES) {
		return AsmRaiseError(ctx, ASM_ERROR_OPCODE);
	}
	return AsmEmitCell(ctx, _:RelocateOpcode(opcode));
}

stock AsmError:AsmEmitOperand(ctx[AsmContext], value) {
	return AsmEmitCell(ctx, value);
}

stock AsmError:AsmEmitInstruction(ctx[AsmContext], Opcode:opcode, ...) {
	// if there's an error while writing then backtracking is useful
	gPreviousWriteOffset = ctx[AsmContext_buffer_offset];

	new AsmError:error = ASM_ERROR_NONE;

	error = AsmEmitOpcode(ctx, opcode);
	if (error != ASM_ERROR_NONE) {
		return error;
	}

	static const STATIC_ARGS = 2;
	new num_opers = numargs() - STATIC_ARGS;

	for (new i = 0; i < num_opers; i++) {
		error = AsmEmitOperand(ctx, getarg(STATIC_ARGS + i));
		if (error != ASM_ERROR_NONE) {
			return error;
		}
	}

	return ASM_ERROR_NONE;
}

stock AsmGetJumpAddressFromOffset(const ctx[AsmContext], offset) {
	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);

	new next_offset = 2 * 4; // offset to the next instruction
	new base = GetAmxBaseAddress() + amxhdr[AMX_HDR_DAT];
	new dest = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] + next_offset + offset;

	return base + dest;
}

stock AsmError:AsmEmitJumpInstruction(ctx[AsmContext], Opcode:opcode, offset) {
	return AsmEmitInstruction(ctx, opcode, AsmGetJumpAddressFromOffset(ctx, offset));
}

stock AsmError:AsmEmitJumpLabelInstruction(ctx[AsmContext], Opcode:opcode, const label[], bool:relative = false) {
	// if there's an error while writing then backtracking is useful
	gPreviousWriteOffset = ctx[AsmContext_buffer_offset];

	new AsmError:error = ASM_ERROR_NONE;

	error = AsmEmitOpcode(ctx, opcode);
	if (error != ASM_ERROR_NONE) {
		return error;
	}
	return AsmEmitJumpStringize(ctx, label, relative);
}

stock AsmError:AsmInitPtr(ctx[AsmContext], buffer, size) {
	ctx[AsmContext_buffer] = buffer;
	ctx[AsmContext_buffer_size] = size;
	ctx[AsmContext_buffer_offset] = 0;
	ctx[AsmContext_error_handler] = 0;
	for (new i = 0; i != ASM_MAX_LABELS; ++i) {
		ctx[AsmContext_label_names][i] = 0;
		ctx[AsmContext_labels][i] = 0;
	}
	return ASM_ERROR_NONE;
}

stock AsmGetPreviousWriteOffset() {
	return gPreviousWriteOffset;
}

stock AsmGetBufferSize(const ctx[AsmContext]) {
	return ctx[AsmContext_buffer_size] - ctx[AsmContext_buffer_offset];
}

stock AsmError:AsmInit(ctx[AsmContext], buffer[], size = sizeof(buffer)) {
	AsmInitPtr(ctx, ref(buffer), size * 4);
}

stock AsmGetCode(const ctx[AsmContext]) {
	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);
	return ctx[AsmContext_buffer] + amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
}

stock AsmGetCodeSize(const ctx[AsmContext]) {
	return ctx[AsmContext_buffer_offset];
}

stock AsmError:AsmGetError(const ctx[AsmContext]) {
	return AsmError:ctx[AsmContext_error];
}

stock AsmSetError(ctx[AsmContext], AsmError:error) {
	ctx[AsmContext_error] = _:error;
}

stock AsmClearError(ctx[AsmContext]) {
	AsmSetError(ctx, ASM_ERROR_NONE);
}

stock AsmGetErrorHandler(const ctx[AsmContext]) {
	return ctx[AsmContext_error_handler];
}

stock AsmError:AsmSetErrorHandler(ctx[AsmContext], error_handler) {
	ctx[AsmContext_error_handler] = error_handler;
	return ASM_ERROR_NONE;
}

stock AsmError:AsmSetErrorHandlerName(ctx[AsmContext], const error_handler[]) {
	ctx[AsmContext_error_handler] = GetPublicAddressFromName(error_handler);
	return ASM_ERROR_NONE;
}

stock AsmEmitPadding(ctx[AsmContext], Opcode:op = OP_NOP) {
	// Must not have parameters, to make the padding valid.
	if (!IsOpcodeValid(op) || gAMXOpcodeParameterCounts[_:op]) {
		op = OP_NOP;
	}
	// Resolve it for speed.
	op = RelocateOpcode(op);
	new
		cur = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset],
		end = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_size];
	while (cur < end) {
		WriteAmxMemory(cur, _:op);
		cur += 4;
	}
	ctx[AsmContext_buffer_offset] = ctx[AsmContext_buffer_size];
}

// Low level functions:

stock AsmError:AsmEmitAdd(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ADD);
}

stock AsmError:AsmEmitAddC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_ADD_C, value);
}

stock AsmError:AsmEmitAddrAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ADDR_ALT, offset);
}

stock AsmError:AsmEmitAddrPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ADDR_PRI, offset);
}

stock AsmError:AsmEmitAlignAlt(ctx[AsmContext], number) {
	return AsmEmitInstruction(ctx, OP_ALIGN_ALT, number);
}

stock AsmError:AsmEmitAlignPri(ctx[AsmContext], number) {
	return AsmEmitInstruction(ctx, OP_ALIGN_PRI, number);
}

stock AsmError:AsmEmitAnd(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_AND);
}

stock AsmError:AsmEmitBounds(ctx[AsmContext], bound) {
	return AsmEmitInstruction(ctx, OP_BOUNDS, bound);
}

stock AsmError:AsmEmitBreak(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_BREAK);
}

stock AsmError:AsmEmitCall(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_CALL, address);
}

stock AsmError:AsmEmitCallAbs(ctx[AsmContext], address) {
	new hdr[AMX_HDR];
	GetAmxHeader(hdr);
	return AsmEmitInstruction(ctx, OP_CALL, address + GetAmxBaseAddress() + hdr[AMX_HDR_COD]);
}

stock AsmError:AsmEmitCallLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_CALL, label);
}

stock AsmError:AsmEmitCmps(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_CMPS, nbytes);
}

stock AsmError:AsmEmitConstAlt(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_CONST_ALT, value);
}

stock AsmError:AsmEmitConstPri(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_CONST_PRI, value);
}

stock AsmError:AsmEmitDec(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_DEC, address);
}

stock AsmError:AsmEmitDecAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_ALT);
}

stock AsmError:AsmEmitDecI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_I);
}

stock AsmError:AsmEmitDecPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_PRI);
}

stock AsmError:AsmEmitDecS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_DEC_S, offset);
}

stock AsmError:AsmEmitEq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_EQ);
}

stock AsmError:AsmEmitEqCAlt(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_EQ_C_ALT, value);
}

stock AsmError:AsmEmitEqCPri(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_EQ_C_PRI, value);
}

stock AsmError:AsmEmitFill(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_FILL, nbytes);
}

stock AsmError:AsmEmitGeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_GEQ);
}

stock AsmError:AsmEmitGrtr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_GRTR);
}

stock AsmError:AsmEmitHalt(ctx[AsmContext], code) {
	return AsmEmitInstruction(ctx, OP_HALT, code);
}

stock AsmError:AsmEmitHeap(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_HEAP, nbytes);
}

stock AsmError:AsmEmitIdxaddr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_IDXADDR);
}

stock AsmError:AsmEmitIdxaddrB(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_IDXADDR_B, shift);
}

stock AsmError:AsmEmitInc(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_INC, address);
}

stock AsmError:AsmEmitIncAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_ALT);
}

stock AsmError:AsmEmitIncI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_I);
}

stock AsmError:AsmEmitIncPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_PRI);
}

stock AsmError:AsmEmitIncS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_INC_S, offset);
}

stock AsmError:AsmEmitInvert(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INVERT);
}

stock AsmError:AsmEmitJeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JEQ, address);
}

stock AsmError:AsmEmitJeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JEQ, offset);
}

stock AsmError:AsmEmitJgeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JGEQ, address);
}

stock AsmError:AsmEmitJgeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JGEQ, offset);
}

stock AsmError:AsmEmitJgrtr(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JGRTR, address);
}

stock AsmError:AsmEmitJgrtrRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JGRTR, offset);
}

stock AsmError:AsmEmitJleq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JLEQ, address);
}

stock AsmError:AsmEmitJleqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JLEQ, offset);
}

stock AsmError:AsmEmitJless(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JLESS, address);
}

stock AsmError:AsmEmitJlessRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JLESS, offset);
}

stock AsmError:AsmEmitJneq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JNEQ, address);
}

stock AsmError:AsmEmitJneqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JNEQ, offset);
}

stock AsmError:AsmEmitJnz(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JNZ, address);
}

stock AsmError:AsmEmitJnzRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JNZ, offset);
}

stock AsmError:AsmEmitJsgeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSGEQ, address);
}

stock AsmError:AsmEmitJsgeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSGEQ, offset);
}

stock AsmError:AsmEmitJsgrtr(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSGRTR, address);
}

stock AsmError:AsmEmitJsgrtrRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSGRTR, offset);
}

stock AsmError:AsmEmitJsleq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSLEQ, address);
}

stock AsmError:AsmEmitJsleqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSLEQ, offset);
}

stock AsmError:AsmEmitJsless(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSLESS, address);
}

stock AsmError:AsmEmitJslessRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSLESS, offset);
}

stock AsmError:AsmEmitJump(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JUMP, address);
}

stock AsmError:AsmEmitJumpRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JUMP, offset);
}

stock AsmError:AsmEmitJzer(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JZER, address);
}

stock AsmError:AsmEmitJzerRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JZER, offset);
}

stock AsmError:AsmEmitJrel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JREL, offset);
}

stock AsmError:AsmEmitJeqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JEQ, label);
}

stock AsmError:AsmEmitJgeqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JGEQ, label);
}

stock AsmError:AsmEmitJgrtrLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JGRTR, label);
}

stock AsmError:AsmEmitJleqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JLEQ, label);
}

stock AsmError:AsmEmitJlessLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JLESS, label);
}

stock AsmError:AsmEmitJneqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JNEQ, label);
}

stock AsmError:AsmEmitJnzLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JNZ, label);
}

stock AsmError:AsmEmitJsgeqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSGEQ, label);
}

stock AsmError:AsmEmitJsgrtrLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSGRTR, label);
}

stock AsmError:AsmEmitJsleqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSLEQ, label);
}

stock AsmError:AsmEmitJslessLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSLESS, label);
}

stock AsmError:AsmEmitJumpLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JUMP, label);
}

stock AsmError:AsmEmitJzerLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JZER, label);
}

stock AsmError:AsmEmitJrelLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JREL, label, true);
}

stock AsmError:AsmEmitLctrl(ctx[AsmContext], index) {
	assert(index >= 0 && index <= 8);
	return AsmEmitInstruction(ctx, OP_LCTRL, index);
}

stock AsmError:AsmEmitLeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LEQ);
}

stock AsmError:AsmEmitLess(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LESS);
}

stock AsmError:AsmEmitLidx(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LIDX);
}

stock AsmError:AsmEmitLidxB(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_LIDX_B, shift);
}

stock AsmError:AsmEmitLoadAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_ALT, address);
}

stock AsmError:AsmEmitLoadPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_PRI, address);
}

stock AsmError:AsmEmitLoad(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_ALT, address);
}

stock AsmError:AsmEmitLoadI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LOAD_I);
}

stock AsmError:AsmEmitLoadSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LOAD_S_ALT, offset);
}

stock AsmError:AsmEmitLoadSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LOAD_S_PRI, offset);
}

stock AsmError:AsmEmitLodbI(ctx[AsmContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return AsmEmitInstruction(ctx, OP_LODB_I, nbytes);
}

stock AsmError:AsmEmitLrefAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LREF_ALT, address);
}

stock AsmError:AsmEmitLrefPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LREF_PRI, address);
}

stock AsmError:AsmEmitLrefSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LREF_S_ALT, offset);
}

stock AsmError:AsmEmitLrefSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LREF_S_PRI, offset);
}

stock AsmError:AsmEmitMoveAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_MOVE_ALT);
}

stock AsmError:AsmEmitMovePri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_MOVE_PRI);
}

stock AsmError:AsmEmitMovs(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_MOVS, nbytes);
}

stock AsmError:AsmEmitNeg(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NEG);
}

stock AsmError:AsmEmitNeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NEQ);
}

stock AsmError:AsmEmitNop(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NOP);
}

stock AsmError:AsmEmitNot(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NOT);
}

stock AsmError:AsmEmitOr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_OR);
}

stock AsmError:AsmEmitPopAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_POP_ALT);
}

stock AsmError:AsmEmitPopPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_POP_PRI);
}

stock AsmError:AsmEmitProc(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PROC);
}

stock AsmError:AsmEmitPushAdr(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_PUSH_ADR, offset);
}

stock AsmError:AsmEmitPushAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PUSH_ALT);
}

stock AsmError:AsmEmitPushC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_PUSH_C, value);
}

stock AsmError:AsmEmitPushPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PUSH_PRI);
}

stock AsmError:AsmEmitPush(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_PUSH, address);
}

stock AsmError:AsmEmitPushS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_PUSH_S, offset);
}

stock AsmError:AsmEmitRet(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_RET);
}

stock AsmError:AsmEmitRetn(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_RETN);
}

stock AsmError:AsmEmitSctrl(ctx[AsmContext], index) {
	assert(index == 2 || 4 <= index <= 6 || index == 8);
	return AsmEmitInstruction(ctx, OP_SCTRL, index);
}

stock AsmError:AsmEmitSdiv(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SDIV);
}

stock AsmError:AsmEmitSdivAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SDIV_ALT);
}

stock AsmError:AsmEmitSgeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SGEQ);
}

stock AsmError:AsmEmitSgrtr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SGRTR);
}

stock AsmError:AsmEmitShl(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SHL);
}

stock AsmError:AsmEmitShlCAlt(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHL_C_ALT, shift);
}

stock AsmError:AsmEmitShlCPri(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHL_C_PRI, shift);
}

stock AsmError:AsmEmitShrCAlt(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHR_C_ALT, shift);
}

stock AsmError:AsmEmitShrCPri(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHR_C_PRI, shift);
}

stock AsmError:AsmEmitShr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SHR);
}

stock AsmError:AsmEmitSignAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SIGN_ALT);
}

stock AsmError:AsmEmitSignPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SIGN_PRI);
}

stock AsmError:AsmEmitSleq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SLEQ);
}

stock AsmError:AsmEmitSless(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SLESS);
}

stock AsmError:AsmEmitSmul(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SMUL);
}

stock AsmError:AsmEmitSmulC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_SMUL_C, value);
}

stock AsmError:AsmEmitSshr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SSHR);
}

stock AsmError:AsmEmitSrefAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SREF_ALT, address);
}

stock AsmError:AsmEmitSrefPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SREF_PRI, address);
}

stock AsmError:AsmEmitSrefSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_SREF_S_ALT, offset);
}

stock AsmError:AsmEmitSrefSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_SREF_S_PRI, offset);
}

stock AsmError:AsmEmitStack(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_STACK, nbytes);
}

stock AsmError:AsmEmitStorAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_STOR_ALT, address);
}

stock AsmError:AsmEmitStorPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_STOR_PRI, address);
}

stock AsmError:AsmEmitStorI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_STOR_I);
}

stock AsmError:AsmEmitStorSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_STOR_S_ALT, offset);
}

stock AsmError:AsmEmitStorSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_STOR_S_PRI, offset);
}

stock AsmError:AsmEmitStrbI(ctx[AsmContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return AsmEmitInstruction(ctx, OP_STRB_I, nbytes);
}

stock AsmError:AsmEmitSub(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SUB);
}

stock AsmError:AsmEmitSubAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SUB_ALT);
}

stock AsmError:AsmEmitSwapAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SWAP_ALT);
}

stock AsmError:AsmEmitSwapPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SWAP_PRI);
}

stock AsmError:AsmEmitSysreqC(ctx[AsmContext], index) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_C, index);
}

stock AsmError:AsmEmitSysreqD(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_D, address);
}

stock AsmError:AsmEmitSysreqPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_PRI);
}

stock AsmError:AsmEmitUdiv(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UDIV);
}

stock AsmError:AsmEmitUdivAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UDIV_ALT);
}

stock AsmError:AsmEmitUmul(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UMUL);
}

stock AsmError:AsmEmitXchg(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_XCHG);
}

stock AsmError:AsmEmitXor(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_XOR);
}

stock AsmError:AsmEmitZero(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_ZERO, address);
}

stock AsmError:AsmEmitZeroAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ZERO_ALT);
}

stock AsmError:AsmEmitZeroPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ZERO_PRI);
}

stock AsmError:AsmEmitZeroS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ZERO_S, offset);
}

// Higher level functions:

stock AsmError:AsmEmitSysreq(ctx[AsmContext], const name[]) {
	return AsmEmitSysreqC(ctx, GetNativeIndexFromName(name));
}

stock AsmError:AsmEmitPopArgs(ctx[AsmContext], n) {
	return AsmEmitStack(ctx, (n + 1) * 4);
}

stock AsmError:AsmEmitPushArg(ctx[AsmContext], n) {
	return AsmEmitPushS(ctx, AsmGetArgOffset(n));
}

stock AsmError:AsmEmitPushNumArgs(ctx[AsmContext], n) {
	return AsmEmitPushC(ctx, 4 * n);
}

// Helpers:

stock AsmGetArgOffset(n) {
	return ASM_ARGUMENTS_OFFSET + 4 * n;
}
