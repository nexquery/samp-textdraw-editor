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

#if defined DISASM_INC
	#endinput
#endif
#define DISASM_INC

#include <string>
#include <file>

#include "amx_base"
#include "amx_header"
#include "amx_memory"
#include "opcode"

#define DISASM_MAX_PUBLIC_NAME 32
#define DISASM_MAX_NATIVE_NAME 100

enum DisasmContext {
	DisasmContext_start_ip,
	DisasmContext_end_ip,
	DisasmContext_nip,
	DisasmContext_cip,
	Opcode:DisasmContext_opcode
}

enum DisasmResult {
	DISASM_DONE = 0,
	DISASM_NOP  = 1,
	DISASM_OK   = 2
}

static stock gCodBase = 0;

stock DisasmInit(ctx[DisasmContext], start = 0, end = 0) {
	new hdr[AMX_HDR];
	GetAmxHeader(hdr);
	
	gCodBase = GetAmxBaseAddress() + hdr[AMX_HDR_COD];

	new dat = hdr[AMX_HDR_DAT];
	new cod = hdr[AMX_HDR_COD];

	new code_base = cod - dat;

	start += code_base;

	ctx[DisasmContext_nip] = start;
	ctx[DisasmContext_cip] = start;

	ctx[DisasmContext_start_ip] = start;
	if (end != 0) {
		ctx[DisasmContext_end_ip] = code_base + end;
	} else {
		//   code_base + (dat - cod)
		// = (cod - dat) + (dat - cod)
		// = cod - dat + dat - cod
		// = cod - cod + dat - dat
		// = 0
		ctx[DisasmContext_end_ip] = 0;
	}
}

stock bool:DisasmDecodeInsn(ctx[DisasmContext]) {
	new ip = ctx[DisasmContext_nip];
	if (ip >= 0) {
		return false;
	}

	new Opcode:opcode = UnrelocateOpcode(Opcode:ReadAmxMemory(ip));
	if (opcode <= OP_NONE || _:opcode >= NUM_OPCODES) {
		return false;
	}

	ctx[DisasmContext_cip] = ip,
	ctx[DisasmContext_opcode] = opcode;

	if (opcode == OP_CASETBL) {
		ip += 4,
		ip += ReadAmxMemory(ip) * 8;
	}

	return
		ctx[DisasmContext_nip] = ip + gAMXOpcodeBaseSizes[_:opcode],
		true;
}

static stock bool:gRelocateRequired;

stock DisasmInitUnsafe() {
	gRelocateRequired = IsOpcodeRelocationRequired();
}

stock bool:DisasmDecodeInsnUnsafe(ctx[DisasmContext]) {
	static ip, Opcode:opcode;

	ctx[DisasmContext_cip] = ip = ctx[DisasmContext_nip],
	ctx[DisasmContext_opcode] = opcode = gRelocateRequired ? (UnrelocateOpcode(Opcode:ReadAmxMemory(ip))) : (Opcode:ReadAmxMemory(ip));

	if (OP_NONE < opcode < Opcode:NUM_OPCODES) {
		if (opcode == OP_CASETBL) {
			ip += 4,
			ip += ReadAmxMemory(ip) * 8;
		}

		return
			ctx[DisasmContext_nip] = ip + gAMXOpcodeBaseSizes[_:opcode],
			true;
	}

	return false;
}

stock DisasmResult:DisasmNext(ctx[DisasmContext]) {
	// This function is just a slightly more consistent wrapper around
	// "DisasmDecodeInsn".  I wanted to change that function, but that would
	// cause breaking changes.  This returns non-zero while there is still data
	// being read, even if that data is not a valid opcode.  For invalid code,
	// it skips the current cell and returns an invalid opcode.  It also now
	// checks the end point correctly.
	if (ctx[DisasmContext_nip] >= ctx[DisasmContext_end_ip]) {
		return DISASM_DONE;
	} else if (DisasmDecodeInsn(ctx)) {
		return DISASM_OK;
	} else {
		ctx[DisasmContext_cip] = ctx[DisasmContext_nip],
		ctx[DisasmContext_nip] += 4,
		ctx[DisasmContext_opcode] = Opcode:NUM_OPCODES;
		return DISASM_NOP;
	}
}

stock Opcode:DisasmNextInsn(ctx[DisasmContext]) {
	if (DisasmDecodeInsn(ctx)) {
		return ctx[DisasmContext_opcode];
	}
	return OP_NONE;
}

stock Opcode:DisasmGetOpcode(const ctx[DisasmContext]) {
	return ctx[DisasmContext_opcode];
}

stock DisasmGetOperand(const ctx[DisasmContext], index = 0) {
	return ReadAmxMemory(ctx[DisasmContext_cip] + (index + 1) * 4);
}

stock DisasmGetNumOperands(const ctx[DisasmContext]) {
	new Opcode:opcode = ctx[DisasmContext_opcode];

	if (opcode == OP_CASETBL) {
		return ReadAmxMemory(ctx[DisasmContext_cip] + 4);
	} else {
		return gAMXOpcodeParameterCounts[_:opcode];
	}
}

stock bool:DisasmNeedReloc(const ctx[DisasmContext]) {
	return GetOpcodeInstructionRelocatable(ctx[DisasmContext_opcode]);
}

stock DisasmReloc(addr) {
	return addr - gCodBase;
}

stock DisasmGetNextIp(const ctx[DisasmContext]) {
	return ctx[DisasmContext_nip];
}

stock DisasmGetCurIp(const ctx[DisasmContext]) {
	return ctx[DisasmContext_cip];
}

stock DisasmGetRemaining(const ctx[DisasmContext]) {
	return ctx[DisasmContext_end_ip] - ctx[DisasmContext_nip];
}

stock DisasmGetInsnName(const ctx[DisasmContext], name[], size = sizeof(name)) {
	name[0] = '\0';
	strcat(name, GetOpcodeInstructionName(ctx[DisasmContext_opcode]), size);
}

stock DisasmGetOperandReloc(const ctx[DisasmContext], index = 0) {
	new param = ReadAmxMemory(ctx[DisasmContext_cip] + (index + 1) * 4);
	new Opcode:op = ctx[DisasmContext_opcode];
	// Needs special code for dealing with "CASETBL", which has multiple
	// parameters - not all of them to be relocated.  If the opcode is NOT that,
	// then check if it is any other opcode requiring relocation.  This does
	// result in the odd pattern of having a triadic operator in a conditional,
	// but the alternative would be:
	//   
	//   if (ctx[DisasmContext_opcode == OP_CASETBL) {
	//       if (index & 1) {
	//           return param - base;
	//       }
	//   } else if (DisasmNeedReloc(ctx)) {
	//       return param - base;
	//   }
	//   return param;
	//   
	// Or:
	//   
	//   if ((ctx[DisasmContext_opcode == OP_CASETBL && (index & 1)) ||
	//       (ctx[DisasmContext_opcode != OP_CASETBL && DisasmNeedReloc(ctx))) {
	//           return param - base;
	//   } else {
	//       return param;
	//   }
	//   
	// I think the conditional ends up nicer in this rare case.
	if ((op == OP_CASETBL) ? (index & 1) : _:gAMXOpcodeNeedsReloc[_:op]) {
		return param - gCodBase;
	} else {
		return param;
	}
}

static stock ToHexStr(x) {
	new s[11];
	new i = 0;
	new j = 0;

	while (i < sizeof(s) && j < 8) {
		new n = x >> (7 - j) * 4 & 0xF;
		switch (n) {
			case 0x0..0x9:
				s[i] = n + '0';
			case 0xA..0xF:
				s[i] = n + 'a' - 0xA;
		}
		i++;
		j++;
	}

	return s;
}

static stock bool:IsPrintableAscii(c) {
	return 32 <= c <= 126;
}

static stock ToPrintableAscii(c) {
	return IsPrintableAscii(c) ? c : ' ';
}

stock DisasmWriteCode(File:file) {
	new ctx[DisasmContext];
	DisasmInit(ctx);

	new hdr[AMX_HDR];
	GetAmxHeader(hdr);

	new dat = hdr[AMX_HDR_DAT];
	new cod = hdr[AMX_HDR_COD];

	fwrite(file, "; CODE\n\n");

	while (DisasmGetNextIp(ctx) < ctx[DisasmContext_end_ip])
	{
		if (!DisasmDecodeInsn(ctx)) {
			new cip = DisasmGetNextIp(ctx);
			ctx[DisasmContext_nip] += 4;
			fwrite(file, ToHexStr(cip + dat - cod));
			fwrite(file, " ???? ");
			fwrite(file, ToHexStr(ReadAmxMemory(cip)));
			fwrite(file, "\n");
			continue;
		}

		new cip = DisasmGetCurIp(ctx);
		new Opcode:opcode = DisasmGetOpcode(ctx);

		if (opcode == OP_PROC) {
			fwrite(file, "\n");
		}

		new insn_name[OPCODE_MAX_INSN_NAME];
		DisasmGetInsnName(ctx, insn_name);
		fwrite(file, ToHexStr(cip + dat - cod));
		fwrite(file, " ");
		fwrite(file, insn_name);
		fwrite(file, " ");

		switch (opcode) {
			case OP_PROC: {
				new name[32];
				new address = cip + dat - cod;
				if (address == hdr[AMX_HDR_CIP]) {
					strcat(name, "main");
				} else {
					new index = GetPublicIndexFromAddress(address);
					if (index >= 0) {
						GetPublicNameFromIndex(index, name);
					}
				}
				if (strlen(name) != 0) {
					fwrite(file, "; ");
					fwrite(file, name);
				}
			}
			case OP_CASETBL: {
				new num = DisasmGetNumOperands(ctx);
				fwrite(file, ToHexStr(num));
				fwrite(file, " ");
				new rel_addr = DisasmGetOperand(ctx, 1) - gCodBase;
				fwrite(file, ToHexStr(rel_addr));
				for (new i = 1; i <= num; i++) {
					fwrite(file, "\n         case ");
					new val = DisasmGetOperand(ctx, i * 2);
					fwrite(file, ToHexStr(val));
					fwrite(file, " ");
					rel_addr = DisasmGetOperand(ctx, i * 2 + 1) - gCodBase;
					fwrite(file, ToHexStr(rel_addr));
				}
			}
			case OP_CALL: {
				new name[DISASM_MAX_PUBLIC_NAME];
				new address = DisasmGetOperand(ctx) - gCodBase;
				if (address == hdr[AMX_HDR_CIP]) {
					strcat(name, "main");
				} else {
					new index = GetPublicIndexFromAddress(address);
					if (index >= 0) {
						GetPublicNameFromIndex(index, name);
					}
				}
				fwrite(file, ToHexStr(address));
				if (strlen(name) > 0) {
					fwrite(file, "; ");
					fwrite(file, name);
				}
			}
			case OP_SYSREQ_C, OP_SYSREQ_D: {
				new name[DISASM_MAX_NATIVE_NAME];
				new address = DisasmGetOperand(ctx);
				if (opcode == OP_SYSREQ_C) {
					new index = DisasmGetOperand(ctx);
					GetNativeNameFromIndex(index, name);
				} else {
					new index = GetNativeIndexFromAddress(address);
					if (index >= 0) {
						GetNativeNameFromIndex(index, name);
					}
				}
				fwrite(file, ToHexStr(address));
				if (strlen(name) > 0) {
					fwrite(file, "; ");
					fwrite(file, name);
				}
			}
			default: {
				new n = DisasmGetNumOperands(ctx);
				for (new i = 0; i < n; i++) {
					new operand = DisasmGetOperandReloc(ctx, i);
					fwrite(file, ToHexStr(operand));
				}
			}
		}

		fwrite(file, "\n");
	}
}

stock DisasmWriteDataRowChar(File:file, start, num, max) {
	new cur = start;
	new end = start + num*4;

	while (cur < max) {
		new p[4 char + 1];
		p[0] = ReadAmxMemory(cur);

		new u[4 + 1];
		u[0] = ToPrintableAscii(p{0});
		u[1] = ToPrintableAscii(p{1});
		u[2] = ToPrintableAscii(p{2});
		u[3] = ToPrintableAscii(p{3});
		u[4] = '\0';

		if (cur < end) {
			fwrite(file, u);
		} else {
			fwrite(file, " ");
		}
		cur += 4;
	}
}

stock DisasmWriteDataRowHex(File:file, start, num, max) {
	new cur = start;
	new end = start + num*4;

	while (cur < max) {
		if (cur < end) {
			fwrite(file, ToHexStr(ReadAmxMemory(cur)));
		} else {
			fwrite(file, "        ");
		}
		fwrite(file, " ");
		cur += 4;
	}
}

stock DisasmWriteData(File:file) {
	fwrite(file, "\n\n; DATA\n");

	new hdr[AMX_HDR];
	GetAmxHeader(hdr);

	new dat = hdr[AMX_HDR_DAT];
	new hea = hdr[AMX_HDR_HEA];
	new data_end = hea - dat;

	for (new i = 0; i < data_end; i += 0x10) {
		fwrite(file, ToHexStr(i));
		fwrite(file, "  ");
		DisasmWriteDataRowHex(file, i, 4, min(i + 0x10, data_end));
		fwrite(file, " ");
		DisasmWriteDataRowChar(file, i, 4, min(i + 0x10, data_end));
		fwrite(file, "\n");
	}
}

stock DisasmWriteFile(File:file) {
	DisasmWriteCode(file);
	DisasmWriteData(file);
}

stock bool:DisasmWrite(const filename[]) {
	new File:file = fopen(filename, io_write);
	if (file) {
		DisasmWriteFile(file);
		fclose(file);
		return true;
	}
	return false;
}

stock DisasmDump(const filename[]) {
	DisasmWrite(filename);
}
