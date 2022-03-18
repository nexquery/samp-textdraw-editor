#if defined _INC_indirection
	#endinput
#endif
#define _INC_indirection

#if !defined ADDRESSOF_INC
	#tryinclude "..\amx\addressof"
#endif
#if !defined ADDRESSOF_INC
	#tryinclude <amx_assembly\addressof>
#endif
#if !defined ADDRESSOF_INC
	#tryinclude "..\amx_assembly\addressof"
#endif
#if !defined ADDRESSOF_INC
	#tryinclude "..\..\amx_assembly\addressof"
#endif
#if !defined ADDRESSOF_INC
	#tryinclude "addressof"
#endif
#if !defined ADDRESSOF_INC
	#tryinclude <addressof>
#endif
#if !defined ADDRESSOF_INC
	#define AMX_INCLUDING_FAILED
#endif
#if !defined _ADDR@
	#define AMX_INCLUDING_FAILED
#endif

#if !defined ADDRESSOF_JIT_INC
	#tryinclude "..\amx\addressof_jit"
#endif
#if !defined ADDRESSOF_JIT_INC
	#tryinclude <amx_assembly\addressof_jit>
#endif
#if !defined ADDRESSOF_JIT_INC
	#tryinclude "..\amx_assembly\addressof_jit"
#endif
#if !defined ADDRESSOF_JIT_INC
	#tryinclude "..\..\amx_assembly\addressof_jit"
#endif
#if !defined ADDRESSOF_JIT_INC
	#tryinclude "addressof_jit"
#endif
#if !defined ADDRESSOF_JIT_INC
	#tryinclude <addressof_jit>
#endif
#if !defined ADDRESSOF_JIT_INC
	#define AMX_INCLUDING_FAILED
#endif

#if !defined AMX_HEADER_INC
	#tryinclude "..\amx\amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude <amx_assembly\amx_header>
#endif
#if !defined AMX_HEADER_INC
	#tryinclude "..\amx_assembly\amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude "..\..\amx_assembly\amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude "amx_header"
#endif
#if !defined AMX_HEADER_INC
	#tryinclude <amx_header>
#endif
#if !defined AMX_HEADER_INC
	#define AMX_INCLUDING_FAILED
#endif

#if defined AMX_INCLUDING_FAILED
	#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\"
#elseif !defined AddressofResolve
	#error Please update "https://github.com/Zeex/amx_assembly" to the latest version.
#endif

#if defined CUSTOM_TAG_TYPES
	#define GLOBAL_TAG_TYPES {_,Bit,Text,Group,File,Float,Text3D,CUSTOM_TAG_TYPES}
#else
	#define GLOBAL_TAG_TYPES {_,Bit,Text,Group,File,Float,Text3D}
#endif

enum E_INDIRECTION
{
	E_INDIRECTION_ALWAYS_NULL, // So we can tell this is not a string.
	E_INDIRECTION_HANDER,      // Called by `@` to handle this pointer.
	E_INDIRECTION_CLAIM,       // Called by `Indirect_Claim`.
	E_INDIRECTION_RELEASE,     // Called by `Indirect_Release`.
	E_INDIRECTION_METADATA,    // Only used by end-users.
}

stock
	INDIRECTION_DATA = 0,
	INDIRECTION_TAG = 0;

static stock
	gsCodSize = 0; // The size of `COD`.

#if !defined YSI_MAX_STRING
	#define YSI_MAX_STRING (144)
#endif

#define string:
#define void:

#define PP_LEFT_BRACKET<> (

#if !defined TAGOF
	#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
		// Defer `tagof` on things with colons slightly to remove anything after
		// it.  This lets us do `tagof (Float:i)` with no problem, since the `i`
		// is removed.
		#define TAGOF(%0);
		#define __TAGOF__[%0] %0:
		#define tagof(%0:%1) __NO_TAGOF:__IS_TAGOF:tagof PP_LEFT_BRACKET<>%0:$%1)
		#define __NO_TAGOF:__IS_TAGOF:tagof%9<>%0)%2:$%1) tagof%9<>%0)%2:%1)
		#define __IS_TAGOF:tagof%9<>%0:$%1) tagof%9<>__TAGOF__[%0])
	#elseif defined __COMPILER_TAG_DATA
		#define TAGOF(%0);
	#else
		#define TAGOF(%0); stock const %0:__TAGOF__%0;
		#define __TAGOF__%0\32; __TAGOF__
		#define tagof(%0:%1) __NO_TAGOF:__IS_TAGOF:tagof PP_LEFT_BRACKET<>%0:$%1)
		#define __NO_TAGOF:__IS_TAGOF:tagof%9<>%0)%2:$%1) tagof%9<>%0)%2:%1)
		#define __IS_TAGOF:tagof%9<>%0:$%1) tagof%9<>__TAGOF__%0)
	#endif

	#if !defined __COMPILER_TAG_DATA
		stock bool:operator==(_:a, __NO_TAGOF:b)
		{
			return a == _:b;
		}

		stock bool:operator!=(_:a, __NO_TAGOF:b)
		{
			return a != _:b;
		}
	#endif

	#define __TAGOF__F@_@%0\32; __TAGOF__F@_@
	#if defined __COMPILER_TAG_DATA
		#define SPECIFIER(%0) __COMPILER_TAG_DATA(F@_@%0,0)
	#else
		#define SPECIFIER(%0) TAGOF(F@_@%0)
	#endif
#endif

TAGOF(Float);
TAGOF(File);

// Technically the function tags are not always `F@_@`.  The third character can
// be anything, and is reserved for representing the return type.  However, it
// is currently not used.  DO NOT consume spaces after `F@_@` since this will
// break functions with no parameters since their tag is just `F@_@:` (or
// `F@_@_`).  Function tags could be weak, which means if you pass a pointer to
// a function that wants a different type, or pass an untyped pointer to a
// function that wants any type, you will get a mismatch warning.  However, you
// can pass a typed pointer to a function that doesn't expect any type for
// backwards-compatability reasons.  I decided against this though - make them
// strong and give warnings on all old code!
#define Func:%0<%1> F@_@%1:%0

// Examples of predeclarations of specifier types.  These fix a bug in the old
// compiler where you can't (always) do `tagof (Float:)`.  This is relevant here
// since the specifiers are passed as `F@_@i:Func`, so we need `tagof (F@_@i:)`
// to get at the specifier.  However, since that doesn't work, we instead need
// `tagof (__TAGOF__F@_@i)` with `stock const F@_@i:__TAGOF__F@_@i`.  I.e. we need a
// variable using the tag to get the tag from, instead of getting it directly.
SPECIFIER(i);
SPECIFIER(s);

// This is for getting excess parameters on non-strings.
#define _:%0,) _:%0)

// I did consider an alternate method of making `@` do this:
//   
//   #define @.%0(%1) Indirect_Data(%0),Indirect_Call(%1)
//   
// But that would fail when an `@` call contained another `@` call:
//   
//   @.Func1(@.Func2(42, 43));
//   
// It would save the stack manipulation though (not convinced it would be less
// code though with the generation of multiple function calls).
#define @ str_new_static
#define str_new_static.%0(%1) (Indirect_Call(_:%0,_:(tagof(%0)),%1))
#define Indirect_Call(_:%9&%0,_:(tagof(%9)),%2) Indirect_Call(_:TAGOF_ADDRESSOF:addressof(%0),_:0,%2)
#define TAGOF_ADDRESSOF:addressof(%0<%2>),_:0, addressof(%0<%2>),_:tagof(F@_@%2:),
// Can now do:
//   
//   @.var(params)
//   @&func<iis>(params)
//   @.&func(params)
//   

#if !defined __PawnBuild
	forward __Indirect_FuncInc__();
	
	public __Indirect_FuncInc__()
	{
		memcpy("", "", 0, 0, 0);
		funcidx("");
	}
#endif

stock Indirect_Call(func, tag, GLOBAL_TAG_TYPES:...)
{
	static
		addr = 0;
	#pragma unused tag
	if (!func)
	{
		return 0;
	}
	{}
	// The COD and DAT segments are different, so `func` pointing in to DAT
	// relative to COD will not be a valid pointer, and THAT you can detect!
	// 
	// Get the previous frame.  This undoes the effects of our `PROC` so the
	// called function must have a proper `PROC`.
	#emit ADDR.pri     20
	#emit STOR.pri     addr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFF8
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			// Get the function at `func - COD + 4`.
			#emit CONST.pri    4
			#emit ADD
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit STOR.alt     INDIRECTION_DATA
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       4
		#emit SYSREQ.C     funcidx
		#emit STACK        8
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		INDIRECTION_DATA = GetPublicAddressFromIndex(INDIRECTION_DATA);
	}
	if (INDIRECTION_TAG)
	{
		static
			i = 0,
			lTag[32];
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		if (lTag[0]) for (i = 4; ; )
		{
			switch (lTag[i++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   addr
				#emit LOAD.I
				#emit SREF.pri   addr
			}
			case '\0', 'x':
				break;
			}
			addr += 4;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope (hope it has a `PROC` too).
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	return 0;
}

// Not `Indirect_CallString` to make use of the `string:` macro.
stock string:Indirect_Callstring(func, tag, GLOBAL_TAG_TYPES:...)
{
	static
		addr = 0;
	#pragma unused tag
	if (!func)
	{
		// Get the offset to the secret return parameter.
		#emit LOAD.S.pri   8
		#emit ADDR.alt     12
		#emit ADD
		#emit LOAD.I
		#emit MOVE.alt
		#emit ZERO.pri
		#emit STOR.I
		#emit RETN
		new ret[YSI_MAX_STRING];
		return ret;
	}
	{}
	#emit ADDR.pri     20
	#emit STOR.pri     addr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFF8
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			// Get the function at `func - COD + 4`.
			#emit CONST.pri    4
			#emit ADD
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit STOR.alt     INDIRECTION_DATA
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       4
		#emit SYSREQ.C     funcidx
		#emit STACK        8
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		INDIRECTION_DATA = GetPublicAddressFromIndex(INDIRECTION_DATA);
	}
	if (INDIRECTION_TAG)
	{
		static
			i = 0,
			lTag[32];
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		if (lTag[0]) for (i = 4; ; )
		{
			switch (lTag[i++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   addr
				#emit LOAD.I
				#emit SREF.pri   addr
			}
			case '\0', 'x':
				break;
			}
			addr += 4;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope.
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	// Never called.  Don't use "static" because it would allocate real memory
	// in advance.  Instead, this will want to allocate on the stack but never
	// get hit to do so.
	new ret[YSI_MAX_STRING];
	return ret;
}

// Not `Indirect_Callvoid` to make use of the `void:` macro.
stock void:Indirect_Callvoid(func, tag, GLOBAL_TAG_TYPES:...)
{
	static
		addr = 0;
	#pragma unused tag
	if (!func)
	{
		return;
	}
	{}
	#emit ADDR.pri     20
	#emit STOR.pri     addr
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.alt
	// Get the parameter count.
	#emit POP.pri
	// Reduce the parameter count.
	#emit ADD.C        0xFFFFFFF8
	// Store the return address.
	#emit SWAP.alt
	#emit STOR.alt     INDIRECTION_DATA
	#emit POP.alt
	// Store the new parameter count.
	#emit SWAP.pri
	#emit STOR.pri     INDIRECTION_TAG
	#emit PUSH.alt
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			// Get the function at `func - COD + 4`.
			#emit CONST.pri    4
			#emit ADD
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit STOR.alt     INDIRECTION_DATA
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       4
		#emit SYSREQ.C     funcidx
		#emit STACK        8
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		INDIRECTION_DATA = GetPublicAddressFromIndex(INDIRECTION_DATA);
	}
	if (INDIRECTION_TAG)
	{
		static
			i = 0,
			lTag[32];
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		if (lTag[0]) for (i = 4; ; )
		{
			switch (lTag[i++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   addr
				#emit LOAD.I
				#emit SREF.pri   addr
			}
			case '\0', 'x':
				break;
			}
			addr += 4;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope.
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	// Don't return anything.
}

stock Indirect_Array(func, tag, const params[], size = sizeof (params))
{
	static
		ret = 0,
		src = 0;
	#pragma unused func, tag, params, size
	// Get the previous frame.  This undoes the effects of our `PROC` so the
	// called function must have a proper `PROC`.
	#emit POP.pri
	#emit SCTRL        5
	// Get the return address.
	#emit POP.pri
	#emit STOR.pri     ret
	// Remove the parameter count.
	#emit POP.pri
	// Get the target tag.
	#emit POP.pri
	#emit STOR.pri     INDIRECTION_DATA
	// Get the target function.
	#emit POP.pri
	#emit STOR.pri     INDIRECTION_TAG
	// Get the source data.
	#emit POP.alt
	#emit STOR.alt     src
	// Get the size.
	#emit POP.alt
	#emit SHL.C.alt    2
//	#emit STOR.alt     cnt
	// We cannot just adjust the stack size while the other parameters are still
	// on it, since the new stack might be smaller than the old one, and dealing
	// with that in a simple way is not possible.  Well, it is possible - it's
	// what we are doing!  Copy the parameters.
	#emit LCTRL        4
	#emit SUB
	#emit SCTRL        4
	#emit PUSH.alt
	#emit PUSH.alt
	#emit PUSH.C       0
	#emit PUSH         src
	#emit STOR.pri     src
	#emit PUSH.pri
	#emit PUSH.C       20
	#emit SYSREQ.C     memcpy
	#emit MOVE.pri
	#emit STACK        24
	#emit PUSH.pri
	#emit PUSH         ret
	// 
	// Check the pointer type.  If it is in the `COD` area, jump straight to it
	// with the tag for parameter types (if it isn't 0).  Otherwise, use the
	// `func` from `DAT` as a pointer to a handler.
	if (INDIRECTION_DATA >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.pri     INDIRECTION_DATA
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.pri     INDIRECTION_DATA
		if (!INDIRECTION_DATA)
		{
			#emit STOR.alt     INDIRECTION_DATA
			// Get the function at `func - COD + 4`.
			#emit LOAD.pri     INDIRECTION_DATA
			#emit ADD.C        4
			#emit LOAD.I
			// Call it, passing `func` as a proper pointer, NOT skipping `PROC`.
			#emit SCTRL        6
			// NEVER RETURNS PAST HERE.
		}
		{}
		// `INDIRECTION_DATA` is now a pointer to a string of a function name.
		// Resolve it via index lookup.
		#emit PUSH.alt
		#emit PUSH.C       4
		#emit SYSREQ.C     funcidx
		#emit STACK        8
		#emit STOR.pri     INDIRECTION_DATA
		if (INDIRECTION_DATA == -1)
		{
			// Failure.
			#emit PROC
			#emit RETN
		}
		{}
		// Get the address from the index.
		INDIRECTION_DATA = GetPublicAddressFromIndex(INDIRECTION_DATA);
	}
	if (INDIRECTION_TAG)
	{
		static
			i = 0,
			lTag[32];
		// Skip the `F@_@` prefix.
		GetTagNameFromID(INDIRECTION_TAG, lTag);
		if (lTag[0]) for (i = 4; ; )
		{
			switch (lTag[i++])
			{
			case 'i', 'd', 't', 'f', 'c':
			{
				// Resolve non-reference parameters.
				#emit LREF.pri   src
				#emit LOAD.I
				#emit SREF.pri   src
			}
			case '\0', 'x':
				break;
			}
			src += 4;
		}
	}
	{}
	// No handler, and no tag data.  Just jump to it and hope (hope it has a `PROC` too).
	#emit LOAD.pri     INDIRECTION_DATA
	#emit SCTRL        6
	return 0;
}

/*-------------------------------------------------------------------------*//**
 * <param name="func">The function pointer with attached metadata.</param>
 * <remarks>
 *  Gets extra data from the pointer.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_GetMeta_(func)
{
	if (func >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return 0;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    16
		#emit ADD
		#emit LOAD.I
		#emit RETN
	}
	return 0;
}
#define Indirect_GetMeta(%0) Indirect_GetMeta_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <param name="func">The function pointer to attach metadata to.</param>
 * <param name="data">The metadata.</param>
 *//*------------------------------------------------------------------------**/

stock Indirect_SetMeta_(func, data)
{
	if (func >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		if (func)
		{
			// Probably a string.
			return;
		}
		{}
		// I'm relying on `alt` not changing here...
		// Get the function at `func - COD + 16`.
		#emit CONST.pri    16
		#emit ADD
		#emit LOAD.S.alt   data
		#emit XCHG
		#emit STOR.I
	}
}
#define Indirect_SetMeta(%0) Indirect_SetMeta_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <param name="func">The function pointer you want to use later.</param>
 * <remarks>
 *  If a function pointer is used within one function, that is not a problem.
 *  However, if you want to store the function pointer for use later, you must
 *  first "claim" it, so that any associated data is not cleared when the
 *  parent function ends (i.e. the function that called your function).  After
 *  use it must be released, and the number of claims must match the number of
 *  releases.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Claim_(func)
{
	if (func >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		//#emit JZER.rel     4
		//#emit RETN
		if (func)
		{
			// Probably a string.
			return;
		}
		{}
		// I'm relying on `alt` not changing here...
		#emit STOR.S.alt   func
		#emit POP.pri
		#emit SCTRL        5
		// Get the function at `func - COD + 8`.
		#emit CONST.pri    8
		#emit ADD
		#emit LOAD.I
		#emit SCTRL        6
	}
}
#define Indirect_Claim(%0) Indirect_Claim_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <param name="func">The function pointer you had previously stored.</param>
 * <remarks>
 *  If a function pointer is used within one function, that is not a problem.
 *  However, if you want to store the function pointer for use later, you must
 *  first "claim" it, so that any associated data is not cleared when the
 *  parent function ends (i.e. the function that called your function).  After
 *  use it must be released, and the number of claims must match the number of
 *  releases.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Release_(func)
{
	if (func >= gsCodSize)
	{
		// Get the data at `func - COD`.
		#emit LOAD.S.pri   func
		#emit LOAD.alt     gsCodSize
		#emit SUB
		#emit MOVE.alt
		#emit LOAD.I
		#emit STOR.S.pri   func
		//#emit JZER.rel     4
		//#emit RETN
		if (func)
		{
			// Probably a string.
			return;
		}
		{}
		// I'm relying on `alt` not changing here.  I wouldn't need to if I
		// could use jumps in assembly.
		#emit STOR.S.alt   func
		#emit POP.pri
		#emit SCTRL        5
		// Get the function at `func - COD + 12`.
		#emit CONST.pri    12
		#emit ADD
		#emit LOAD.I
		#emit SCTRL        6
	}
}
#define Indirect_Release(%0) Indirect_Release_(_:%0)

/*-------------------------------------------------------------------------*//**
 * <param name="id">The ID of the tag to get the specifiers from the name of.
 * </param>
 * <param name="dest">Where to store the name.</param>
 * <remarks>
 *  Functions are tagged with a special tag containing their specifiers.  Get
 *  the string value of that tag from the AMX header.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Tag(id, dest[32])
{
	static
		lTag[32];
	GetTagNameFromID(id, lTag),
	dest[0] = '\0';
	if (lTag[0])
		strcat(dest, lTag[4]);
}

/*-------------------------------------------------------------------------*//**
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *  Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *  distinguished from normal function pointers.  This function does the offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Ref_(...)
{
	assert(numargs() == 1);
	#emit LOAD.S.pri       12
	#emit LOAD.alt         gsCodSize
	#emit ADD
	#emit RETN
	return 0;
}
#define Indirect_Ref(%0) Indirect_Ref_(_:(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *  Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *  distinguished from normal function pointers.  This function does the offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_Ptr_(ptr)
{
	#pragma unused ptr
	assert(numargs() == 1);
	#emit LOAD.S.pri       12
	#emit LOAD.alt         gsCodSize
	#emit ADD
	#emit RETN
	return 0;
}
#define Indirect_Ptr(%0) Indirect_Ptr_(_:(%0))

/*-------------------------------------------------------------------------*//**
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *  Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *  distinguished from normal function pointers.  This function does the offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_DeRef_(...)
{
	assert(numargs() == 1);
	#emit LOAD.S.pri       12
	#emit LOAD.alt         gsCodSize
	#emit SUB
	#emit RETN
	return 0;
}
#define Indirect_DeRef(%0) Indirect_DeRef_(_:(%0), sizeof (%0[]))

/*-------------------------------------------------------------------------*//**
 * <param name="">The array to convert to an offset pointer.</param>
 * <remarks>
 *  Strings and arrays are passed relative to `COD` not `DAT` so they can be
 *  distinguished from normal function pointers.  This function does the offset.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock Indirect_DePtr_(ptr)
{
	#pragma unused ptr
	assert(numargs() == 1);
	#emit LOAD.S.pri       12
	#emit LOAD.alt         gsCodSize
	#emit SUB
	#emit RETN
	return 0;
}
#define Indirect_DePtr(%0) Indirect_DePtr_(_:(%0))

#if !defined _ALS_OnJITCompile
	forward OnJITCompile();
#endif

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  A generic public wrapper for calling inline functions.
 * </remarks>
 *//*------------------------------------------------------------------------**/

forward Indirect_FromCallback(Func:cb<>, bool:release);

public Indirect_FromCallback(Func:cb<>, bool:release)
{
	new ret = @.cb();
	if (release)
		Indirect_Release(cb);
	return ret;
}

/*-------------------------------------------------------------------------*//**
 * <remarks>
 *  Get the size of the COD AMX segment.
 * </remarks>
 *//*------------------------------------------------------------------------**/

Indirect_Init()
{
	if (!gsCodSize)
	{
		AddressofResolve();
		new
			amxhdr[AMX_HDR];
		GetAmxHeader(amxhdr);
		gsCodSize = amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
	}
}
 
public OnJITCompile()
{
	Indirect_Init();
	#if defined Indirection_OnJITCompile
		return Indirection_OnJITCompile();
	#else
		return 1;
	#endif
}

public OnFilterScriptInit()
{
	Indirect_Init();
	#if defined Indirection_OnFilterScriptInit
		Indirection_OnFilterScriptInit();
	#endif
	return 1;
}

public OnGameModeInit()
{
	Indirect_Init();
	#if defined Indirection_OnGameModeInit
		Indirection_OnGameModeInit();
	#endif
	return 1;
}

#if defined Indirection_OnJITCompile
	forward Indirection_OnJITCompile();
#endif
#if defined _ALS_OnJITCompile
	#undef OnJITCompile
#else
	#define _ALS_OnJITCompile
#endif
#define OnJITCompile(%0) Indirection_OnJITCompile(%0)

#if defined Indirection_OnFilterScriptInit
	forward Indirection_OnFilterScriptInit();
#endif
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit(%0) Indirection_OnFilterScriptInit(%0)

#if defined Indirection_OnGameModeInit
	forward Indirection_OnGameModeInit();
#endif
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit(%0) Indirection_OnGameModeInit(%0)

