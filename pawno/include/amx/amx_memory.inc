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

#if defined AMX_MEMORY_INC
	#endinput
#endif
#define AMX_MEMORY_INC

#include <core>

// Returns the address of a variable/array.
stock ref(...) {
	assert(numargs() == 1);
	#emit load.s.pri 12 // first argument
	#emit retn
	return 0; // make compiler happy
}

// Returns an array from an address.
stock deref(v) {
	static gFake[1];
	#emit load.s.pri  v // first argument
	#emit stor.s.pri 16 // secret argument
	#emit retn
	return gFake; // make compiler happy
}

// Returns the address of a variable parameter.
stock argref(n) {
	#emit load.s.alt 0
	#emit load.s.pri n
	#emit add.c 3
	#emit lidx
	#emit retn
	return 0; // make compiler happy
}

// Returns an array from a variable parameter.
stock argderef(n) {
	static gFake[1];
	
	#emit load.s.alt 0
	#emit load.s.pri n
	#emit add.c 3
	#emit lidx
	#emit stor.s.pri 16 // secret argument
	#emit retn
	return gFake; // make compiler happy
}

#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
	#if !defined __PawnBuild
		#define __PawnBuild 0
	#endif
	#if __PawnBuild >= 10
		stock gAmxAssemblyAddress_;
		#define ReadAmxMemory(%0) __emit(load.u.pri %0, stor.pri gAmxAssemblyAddress_, lref.pri gAmxAssemblyAddress_)
		#define WriteAmxMemory(%0,%1) __emit(push.u %1, load.u.alt %0, stor.alt gAmxAssemblyAddress_, pop.pri, sref.pri gAmxAssemblyAddress_)
	#endif
#endif

stock ReadAmxMemoryArray(address, values[], size = sizeof(values)) {
	for (new i = 0; i < size; i++) {
		values[i] = ReadAmxMemory(address + i * 4);
	}
}

stock WriteAmxMemoryArray(address, const values[], size = sizeof(values)) {
	for (new i = 0; i < size; i++) {
		WriteAmxMemory(address + i * 4, values[i]);
	}
}

stock GetAmxNextInstructionPointer()
{
	// Saying "get the current pointer" doesn't make a huge amount of sense -
	// getting the pointer will in itself take code, so exactly where is "here"?
	// This returns its own return address, which points to the instruction
	// directly after the call.  This is at least well defined.
	#emit load.s.pri 4
	#emit retn
	return 0;
}

stock GetAmxHeapBase()
{
	// Initial heap pointer.  Not stored in an accessible register so read it
	// straight from the original header.
	#emit lctrl 1  // DAT
	#emit neg      // -DAT
	#emit add.c 20 // -DAT + 20
	#emit push.pri
	#emit lref.s.pri 0xfffffffc
	#emit stack 4
	#emit retn
	return 0;
}

stock GetAmxHeapTop()
{
	// Current heap pointer.
	#emit lctrl 2
	#emit retn
	return 0;
}

stock GetAmxStackBase()
{
	#emit lctrl 3
	#emit retn
	return 0;
}

stock GetAmxStackBottom()
{
	#emit lctrl 4
	#emit add.c 12
	#emit retn
	return 0;
}

stock GetAmxFrame()
{
	// Doesn't use "lctrl 5" because we want it to look like this function was
	// never called.  Doing that would only return this function's frame.
	#emit load.s.pri 0
	#emit retn
	return 0;
}

stock SetAmxHeapTop(ptr)
{
	#emit load.s.pri ptr
	#emit sctrl 2
}

stock SetAmxStackBottom(ptr)
{
	static
		cip = 0;
	// We need to be tricky here, because the return value is on the stack.
	#emit load.s.alt ptr
	// Store the return address.
	#emit load.s.pri 4
	#emit stor.pri cip
	// Reset the frame.
	#emit load.s.pri 0
	#emit sctrl 5
	// Modify the stack.
	#emit move.pri
	#emit sctrl 4
	// Return.
	#emit load.pri cip
	#emit sctrl 8
	#emit sctrl 6
}

stock SetAmxFrame(ptr)
{
	// We need to be tricky here, because the return value is in our frame.
	// Store the return address.
	#emit load.s.alt 4
	// Modify the frame.
	#emit load.s.pri ptr
	#emit sctrl 5
	// Return.
	#emit move.pri
	#emit stack 16
	#emit sctrl 8
	#emit sctrl 6
}

stock SetAmxNextInstructionPointer(ptr)
{
	#emit load.s.alt ptr
	// Reset the frame.
	#emit load.s.pri 0
	#emit sctrl 5
	// Return.
	#emit move.pri
	#emit stack 16
	#emit sctrl 8
	#emit sctrl 6
}

#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
	#if __PawnBuild >= 10
		#endinput
	#endif
#endif

// after `#endif` because `#if` doesn't elide `#emit`.
stock WriteAmxMemory(address, value) {
	#emit load.s.pri value
	#emit sref.s.pri address
	#emit retn
	return 0; // make compiler happy
}

stock ReadAmxMemory(address) {
	#emit lref.s.pri address
	#emit retn
	return 0; // make compiler happy
}

