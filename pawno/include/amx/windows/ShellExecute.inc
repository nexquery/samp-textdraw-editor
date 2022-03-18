// Copyright (C) 2012 Zeex
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#if defined SHELL_EXECUTE_INC
	#endinput
#endif
#define SHELL_EXECUTE_INC

#include "import_table"
#include "..\amx_header"
#include "..\amx_memory"
#include "..\dynamic_call"
#include "..\phys_memory"
#include "..\shellcode"

// http://msdn.microsoft.com/en-us/library/windows/desktop/bb762153%28v=vs.85%29.aspx

#define SW_HIDE (0)
#define SW_NORMAL (1)
#define SW_MAXIMIZE (3)
#define SW_MINIMIZE (6)
#define SW_RESTORE (9)
#define SW_SHOW (5)
#define SW_SHOWDEFAULT (10)
#define SW_SHOWMAXIMIZED (3)
#define SW_SHOWMINIMIZED (2)
#define SW_SHOWMINNOACTIVE (7)
#define SW_SHOWNA (8)
#define SW_SHOWNOACTIVATE (4)
#define SW_SHOWNORMAL (1)

// (0)                              // The operating system is out of memory or resources.
#define ERROR_FILE_NOT_FOUND (2)    //  The specified file was not found.
#define ERROR_PATH_NOT_FOUND (3)    // The specified path was not found.
#define ERROR_BAD_FORMAT (11)       // The .exe file is invalid (non-Win32 .exe or error in .exe image).
#define SE_ERR_ACCESSDENIED (5)     // The operating system denied access to the specified file.
#define SE_ERR_ASSOCINCOMPLETE (27) // The file name association is incomplete or invalid.
#define SE_ERR_DDEBUSY (30)         // The DDE transaction could not be completed because other DDE transactions were being processed.
#define SE_ERR_DDEFAIL (29)         // The DDE transaction failed.
#define SE_ERR_DDETIMEOUT (28)      // The DDE transaction could not be completed because the request timed out.
#define SE_ERR_DLLNOTFOUND (32)     // The specified DLL was not found.
#define SE_ERR_FNF (2)              // The specified file was not found.
#define SE_ERR_NOASSOC (31)         // There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.
#define SE_ERR_OOM (8)              // There was not enough memory to complete the operation.
#define SE_ERR_PNF (3)              // The specified path was not found.
#define SE_ERR_SHARE (26)           // A sharing violation occurred.

// NOTE: string arguments must be prepared with ToCharString() or similar function.
stock ShellExecute(const Operation[], const File[], const Parameters[], ShowCmd) {
	/*
	.text:10001000 55                                push    ebp
	.text:10001001 8B EC                             mov     ebp, esp
	.text:10001003 8B 45 0C                          mov     eax, [ebp+arg_4]
	.text:10001006 8B 48 18                          mov     ecx, [eax+18h]
	.text:10001009 51                                push    ecx             ; nShowCmd
	.text:1000100A 8B 55 0C                          mov     edx, [ebp+arg_4]
	.text:1000100D 8B 42 14                          mov     eax, [edx+14h]
	.text:10001010 50                                push    eax             ; lpDirectory
	.text:10001011 8B 4D 0C                          mov     ecx, [ebp+arg_4]
	.text:10001014 8B 51 10                          mov     edx, [ecx+10h]
	.text:10001017 52                                push    edx             ; lpParameters
	.text:10001018 8B 45 0C                          mov     eax, [ebp+arg_4]
	.text:1000101B 8B 48 0C                          mov     ecx, [eax+0Ch]
	.text:1000101E 51                                push    ecx             ; lpFile
	.text:1000101F 8B 55 0C                          mov     edx, [ebp+arg_4]
	.text:10001022 8B 42 08                          mov     eax, [edx+8]
	.text:10001025 50                                push    eax             ; lpOperation
	.text:10001026 8B 4D 0C                          mov     ecx, [ebp+arg_4]
	.text:10001029 8B 51 04                          mov     edx, [ecx+4]
	.text:1000102C 52                                push    edx             ; hwnd
	.text:1000102D FF 15 78 56 34 12                 call    ds:ShellExecuteA ; Opens or prints a specified file
	.text:10001033 5D                                pop     ebp
	.text:10001034 C3                                retn
	*/

	#define __asm(%0,%1,%2,%3) (((0x%3) << 24) | ((0x%2) << 16) | (0x%1 << 8) | (0x%0))

	static const asm[] = {
		__asm(90,90,90,90),
		__asm(90,90,90,90),
		__asm(90,90,90,90),
		__asm(90,90,90,90),
		__asm(55,8B,EC,8B),
		__asm(45,0C,8B,48),
		__asm(18,51,8B,55),
		__asm(0C,8B,42,14),
		__asm(50,8B,4D,0C),
		__asm(8B,51,10,52),
		__asm(8B,45,0C,8B),
		__asm(48,0C,51,8B),
		__asm(55,0C,8B,42),
		__asm(08,50,8B,4D),
		__asm(0C,8B,51,04),
		__asm(52,FF,15,00),
		__asm(00,00,00,5D),
		__asm(C3,CC,CC,CC)
	};

//	#undef __

	new address = GetImportAddress("ShellExecuteA");
	WriteAmxMemory(ref(asm) + 63, refabs(address));

	Push(0);                  // HWND hwnd
	Push(refabs(Operation));  // LPCTSTR lpOperation
	Push(refabs(File));       // LPCTSTR lpFile
	Push(refabs(Parameters)); // LPCTSTR lpParameters
	Push(0);                  // LPCTSTR lpDirectory
	Push(ShowCmd);            // INT nShowCmd

	return RunShellcode(refabs(asm));
}
