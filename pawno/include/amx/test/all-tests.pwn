#define main main_amx
#include "amx-test.pwn"
#undef main
#define main main_asm
#include "asm-test.pwn"
#undef main
#define main main_disasm
#include "disasm-test.pwn"
#undef main
#define main main_dynamic_call
#include "dynamic_call-test.pwn"
#undef main
#define main main_jit
#include "jit-test.pwn"
#undef main
#define main main_phys_memory
#include "phys_memory-test.pwn"
#undef main
#define main main_stack_trace
#include "stack_trace-test.pwn"
#undef main

main() {
	main_amx();
	main_asm();
	main_disasm();
	main_dynamic_call();
	main_jit();
	main_phys_memory();
	main_stack_trace();
}


