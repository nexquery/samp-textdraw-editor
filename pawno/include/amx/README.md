## Overview

* [`amx.inc`](amx.inc) - Read/write contents of the AMX strcture (`AMX` struct in C code).
* [`amx_base.inc`](amx_base.inc) - Get base address of the AMX in memory (`amx->base`).
* [`amx_header.inc`](amx_header.inc) - Read contents of the AMX header (`AMX_HEADER`) and query header tables such as publics, natives, tags, etc.
* [`amx_memory.inc`](amx_memory.inc) - Read/write contents of variables using their AMX address (kind of like pointers in C).
* [`codescan.inc`](codescan.inc) - Find patterns in bytecode.
* [`disasm.inc`](disasm.inc) - Example of how to disassemble AMX bytecode (i.e. self-disassembly).
* [`dynamic_call.inc`](dynamic_call.inc) - Call any function by address or index. Can be very powerful in combination with [`amx_header.inc`](amx_header.inc).
* [`frame_info.inc`](frame_info.inc) - Get information about call frames from the stack.
* [`heap_alloc.inc`](heap_alloc.inc) - Allocate memory on the AMX heap.
* [`jit.inc`](jit.inc) - Check if running under the [JIT](https://github.com/Zeex/samp-plugin-jit) plugin.
* [`opcode.inc`](opcode.inc) - List of AMX opcodes and utility functions for (un-)relocating opcodes on Linux.
* [`os.inc`](os.inc) - Detect operating system (Windows vs Linux).
* [`phys_memory.inc`](phys_memory.inc) - Read/write memory of the host process (outside of AMX data).
* [`profiler.inc`](profile.inc) - Simple profiler written purely in Pawn. It can measure execution time of public functions.
* [`shellcode.inc`](shellcode.inc) - Execute arbitrary native code (doesn't work on Linux).
* [`stack_dump.inc`](stack_dump.inc) - Print stack contents to the console.
* [`stack_trace.inc`](stack_trace.inc) - Print stack trace.
* [`windows/import_table.inc`](windows/import_table.inc) - Read the PE import table of the host process.
* [`windows/ShellExecute.inc`](windows/ShellExecute.inc) - How to use `shellcode` and `import_table` to call a Win32 API function (in this case `ShellExecuteA`).

## Installation

Simply install to your project:

```bash
sampctl package install amx_assembly
```

Include in your code and begin using the library:

```pawn
#include <amx_assembly\include_name_here>
```

## Usage

There are a few example scripts in the `test` directory that show how to use some of these includes.
