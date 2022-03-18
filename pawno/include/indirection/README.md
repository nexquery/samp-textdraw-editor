# `indirection.inc`

[![sampctl](https://shields.southcla.ws/badge/sampctl-indirection-2f2f2f.svg?style=for-the-badge)](https://github.com/Y-Less/indirection)

Indirection is a system for calling function pointers in a generic and type-safe way.  Instead of `CallLocalFunction`, `Call`, `defer`, `Callback_Call`, or any other method, this gives one common interface which can be extended by library authors; utilising tags for compile-time parameters:

```pawn
Caller(Func:func<iisi>, playerid)
{
	@.func(playerid, _:func, "Hello World", random(5));
}

Callee(playerid, func, string[], rand)
{
}

main()
{
	Caller(&Callee, 42);
}
```

## Installation

Simply install to your project:

```bash
sampctl package install Y-Less/indirection
```

Include in your code and begin using the library:

```pawn
#include <indirection>
```

## Usage

### General Users

If the library supports it, you can call a function that takes another function using `&`:

```pawn
FuncThatWantsACallback(&MyCallback);
```

You can also use y_inline:

```pawn
FuncThatWantsACallback(using inline MyInline);
```

Or you can use `addressof` from amx_assembly:

```pawn
FuncThatWantsACallback(addressof(MyCallback));
```

Functions that take other functions are type-safe, so a function that expects a callback that expects two integers will have a type of:

```pawn
FuncThatWantsACallback(Func:callback<ii>)
{
}
```

Here `ii` is the standard notation for two integer parameters.  If you try and pass a function that does not take two integer parameters, the compiler will give a `warning 202: number of arguments does not match definition`:

```pawn
Caller(Func:func<iisi>, playerid)
{
	@.func(playerid, _:func, "Hello World", random(5));
}

Callee(playerid, func, string[])
{
}

main()
{
	Caller(&Callee, 42); // `Callee` is not `iisi`, but just `iis`.
}
```

Function pointers are just normal variables, and so can be passed around between functions as normal:

```pawn
Caller(Func:func<iisi>, playerid)
{
	@.func(playerid, _:func, "Hello World", random(5));
}

Intermediate(Func:func<iisi>)
{
	Caller(func, 42);
}

Callee(playerid, func, string[], rand)
{
}

main()
{
	Intermediate(&Callee);
}
```

The available "types" are: `i` - any integer, `f` - floats, `a` - arrays, `s` - strings, `v` - references (`&var`), `x` - varargs (`...`, must be last), `tTag:` - tagged with `Tag:`.

### Library Writers

A parameter that takes a function pointer has the tag `Func:`, and is followed by the type specifier for the function.  For example `OnPlayerCommandText` would be `Func:func<is>` and `OnUnoccupiedVehicleUpdate` would be `Func:func<iiiffffff>`.  In a function signature this would look like:

```pawn
MyFunction(playerid, Func:func<ifis>)
{
}
```

Pointers are regular variables, so can be stored and copied as normal, with one small exception.  This is fine:

```pawn
MyFunction(playerid, Func:func<i>)
{
	@.func(playerid);
}
```

This is not:

```pawn
public TheFuture(playerid, Func:func<i>)
{
	@.func(playerid);
}

MyFunction(playerid, Func:func<i>)
{
	SetTimerEx("TheFuture", 1000, 0, "ii", playerid, _:func);
}
```

In this case, the function `func` is used after the original function ends.  If you pass the pointer in a timer, save it in a global variable, or in any other way store it to be used at some unknown point in the future you must first "claim" it:

```pawn
MyFunction(playerid, Func:func<i>)
{
	Indirect_Claim(func);
	SetTimerEx("TheFuture", 1000, 0, "ii", playerid, _:func);
}
```

And later "release" it:

```pawn
public TheFuture(playerid, Func:func<i>)
{
	@.func(playerid);
	Indirect_Release(func);
}
```

This is similar to the old y_inline `Callback_Get` and `Callback_Free` functions, but are not always needed, and are not restricted in when they can be called (those y_inline functions are now synonyms for the more generic indirection.inc functions).

As a library writer, the `&` operator must be explicitly supported for your function-taking functions.  This is done with a simple define:

```pawn
MyFunction(playerid, Func:func<i>)
{
	@.func(playerid);
}
#define MyFunction(%1,&%2) MyFunction(%1, addressof(%2<i>))
```

The second parameter of this define is `&%2`, which means it will only match when users call your function with something like `MyFunction(playerid, &Callback)`.  In that case the `&` is replaced with a typed call to `addressof`.  This does mean you have to specify the type twice - once in the function prototype and once in the define.  Note, however, that the define can be more strict as the specifier in the function prototype must NOT use the specifier `t` - all tagged vars are just types of integer:

Good:

```pawn
MyFunction(playerid, Func:func<i>)
{
	@.func(playerid);
}
#define MyFunction(%1,&%2) MyFunction(%1, addressof(%2<tFile:>))
```

Bad:

```pawn
MyFunction(playerid, Func:func<tFile:>)
{
	@.func(playerid);
}
#define MyFunction(%1,&%2) MyFunction(%1, addressof(%2<i>))
```

### MySQL Example:


### Low-Level Providers

The function variable is one of three things.

1) A function pointer, in which case it will point somewhere in the `COD` section.

2) A string pointer, in which case it will point to a string in the `DAT` section, RELATIVE TO `DAT`.  This relativity is how indirection.inc can tell the difference.  Since `DAT` follows `COD`, any data pointers will be larger than any possible function pointer, and the difference can then just be subtracted.

3) A function structure pointer.  This points to `DAT` in the same way as strings, but the target is of the form:

```pawn
enum E_INDIRECTION
{
	E_INDIRECTION_ALWAYS_NULL, // So we can tell this is not a string.
	E_INDIRECTION_HANDER, // Called by `@` to handle this pointer.
	E_INDIRECTION_CLAIM, // Called by `Indirect_Claim` to handle any required allocations.
	E_INDIRECTION_RELEASE, // Called by `Indirect_Release` to handle any required frees.
	... // Any custom data required by your custom handlers.
}
```

`ALWAYS_NULL` is (unsurprisingly) always NULL.  This is so that the data at the pointer is a zero-length string, which is treated as not a string at all.

The `CLAIM` and `RELEASE` functions both have the same signature:

```pawn
MyCustomClaim(func[E_INDIRECTION])
{
}

MyCustomRelease(func[E_INDIRECTION])
{
}
```

You can replace the array size there with any custom one to account for additional data after the standard four items.

The `HANDLER` function has the prototype:

```pawn
MyCustomHandler(...)
{
}
```

All the parameters are the parameters the user gave to `@`, i.e. the parameters for the final function to be called.  For this reason there are two magic globals: `INDIRECTION_DATA` contains a pointer to the `E_INDIRECTION` data.  `INDIRECTION_TAG` contains the index of the function's tag, the string of the tag (which includes all the specifier characters) can be retrieved with `Indirect_Tag(id, dest[32])`.

## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` to test.

### Metadata

You can attach a single piece of metadata to a function.  This is arbitrary data that you can access via the function handle:

```pawn
Indirect_SetMeta(func, 5);
printf("%d", Indirect_GetMeta(func)); // Prints 5
```

This allows you to associate things like handles, for example a timer handle:

```
stock SetTimerCallback(Func:func<>, time, bool:repeat)
{
	Indirect_Claim(func);
	new timer = SetTimerEx("@y_inlineTimerInvoke", time, repeat, "ii", _:func, !repeat);
	Indirect_SetMeta(func, timer);
	return _:func;
}
```

