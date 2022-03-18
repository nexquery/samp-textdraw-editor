# code-parse.inc

## Contents

* [Introduction](#introduction)
* [Example 1 - Count Array Parameters](#example-1---count-array-parameters)
  * [Full Code](#full-code)
  * [Console Output](#console-output)
  * [Explanation](#explanation)
  * [Exclude Strings](#exclude-strings)
* [Example 2 - Count All Parameters](#example-2---count-all-parameters)
* [Example 3 - Count Array Parameters And Sum Their Size](#example-3---count-array-parameters-and-sum-their-size)
* [Example 4 - Auto-Generate `CallRemoteFunction` Specifier Strings](#example-4---auto-generate-callremotefunction-specifier-strings)
  * [Three Facts](#three-facts)
  * [Tags](#tags)
* [Example 5 - Output Input Exactly](#example-5---output-input-exactly)
  * [Lie 1](#lie-1)
  * [Lie 2](#lie-2)
  * [Output One Parameter](#output-one-parameter)
  * [Output Everything](#output-everything)
* [Example 6 - Remotes With Alternate Return Types](#example-6---remotes-with-alternate-return-types)
  * [No Return](#no-return)
  * [Tag Return](#tag-return)
  * [String Return](#string-return)
  * [String Return Code Issues](#string-return-code-issues)
  * [Complete String Return Code](#complete-string-return-code)
  * [Use](#use-1)
* [Example 7 - y_timers Clone](#example-7---y_timers-clone)
  * [Use](#use)
* [LEN (LENGTH)](#len-length)
* [QAL (QUALIFICATION)](#qal-qualification)
* [SPC (SPECIAL)](#spc-special)
* [GRP (TAGGROUP)](#grp-taggroup)
  * [Alternate Rebuild](#alternate-rebuild)
* [API](#api)
* [Example 8 - y_inline](#example-8---y_inline)
* [PARSER_ISOLATE](#parser_isolate)
* [Complete Parameter Reference](#complete-parameter-reference)
  * [NUMBER](#number)
  * [NUMBER_CONST](#number_const)
  * [NUMBER_DEFAULT](#number_default)
  * [NUMBER_CONST_DEFAULT](#number_const_default)
  * [NUMBER_TAG](#number_tag)
  * [NUMBER_CONST_TAG](#number_const_tag)
  * [NUMBER_DEFAULT_TAG](#number_default_tag)
  * [NUMBER_CONST_DEFAULT_TAG](#number_const_default_tag)
  * [NUMBER_TAGGROUP](#number_taggroup)
  * [NUMBER_CONST_TAGGROUP](#number_const_taggroup)
  * [NUMBER_DEFAULT_TAGGROUP](#number_default_taggroup)
  * [NUMBER_CONST_DEFAULT_TAGGROUP](#number_const_default_taggroup)
  * [REFERENCE](#reference)
  * [REFERENCE_DEFAULT](#reference_default)
  * [REFERENCE_TAG](#reference_tag)
  * [REFERENCE_DEFAULT_TAG](#reference_default_tag)
  * [REFERENCE_TAGGROUP](#reference_taggroup)
  * [REFERENCE_DEFAULT_TAGGROUP](#reference_default_taggroup)
  * [STRING](#string)
  * [STRING_CONST](#string_const)
  * [STRING_DEFAULT](#string_default)
  * [STRING_CONST_DEFAULT](#string_const_default)
  * [VARARG](#vararg)
  * [VARARG_TAG](#vararg_tag)
  * [VARARG_TAGGROUP](#vararg_taggroup)
  * [ARRAY](#array)
  * [ARRAY_CONST](#array_const)
  * [ARRAY_TAG](#array_tag)
  * [ARRAY_CONST_TAG](#array_const_tag)
  * [ARRAY_TAGGROUP](#array_taggroup)
  * [ARRAY_CONST_TAGGROUP](#array_const_taggroup)
  * [ARRAY_MULTI](#array_multi)
  * [ARRAY_MULTI_CONST](#array_multi_const)
  * [ARRAY_MULTI_TAG](#array_multi_tag)
  * [ARRAY_MULTI_CONST_TAG](#array_multi_const_tag)
  * [ARRAY_MULTI_TAGGROUP](#array_multi_taggroup)
  * [ARRAY_MULTI_CONST_TAGGROUP](#array_multi_const_taggroup)
  * [LENGTH](#length)
  * [SPECIAL](#special)
  * [SPECIAL_CONST](#special_const)
* [Complete Return Reference](#complete-return-reference)
  * [_END](#_end)
  * [_NUL](#_nul)
  * [_END_TAG](#_end_tag)
  * [_NUL_TAG](#_nul_tag)
  * [_END_VOD](#_end_vod)
  * [_NUL_VOD](#_nul_vod)
  * [_END_STR](#_end_str)
  * [_NUL_STR](#_nul_str)
  * [_END_TAG_VOD](#_end_tag_vod)
  * [_NUL_TAG_VOD](#_nul_tag_vod)
  * [_END_VOD_STR](#_end_vod_str)
  * [_NUL_VOD_STR](#_nul_vod_str)
  * [_END_TAG_STR](#_end_tag_str)
  * [_NUL_TAG_STR](#_nul_tag_str)
  * [_END_TAG_VOD_STR](#_end_tag_vod_str)
  * [_NUL_TAG_VOD_STR](#_nul_tag_vod_str)
  * [QUALIFICATION](#qualification)

## Introduction

This library is designed for generating code at compile-time based on existing
code.  It can be thought of as a macro equivalent to amx-assembly - used for
advanced manipulation of the compiler for creating libraries and keywords, more
than end-user code.  As a simple example we will create a macro to count the
number of array parameters in a function, walking through each step in turn.
After that we will demonstrate a more in-depth example to create a y_timers
clone.

## Example 1 - Count Array Parameters

### Full Code

```pawn
// The entry point.  Defines our parser.
#define ARRAY_COUNT:%1(%2) FUNC_PARSER(ARRAY_COUNT,ARR:NUM:)(%1(%2)) stock const countOf_%1 = 0; %1(%2)

// Default.  Called for parameters that didn't match any other type.
#define ARRAY_COUNT_NUM(%9)%8$ %8$

// Arrays.  Called when an array is matched.
#define ARRAY_COUNT_ARR(%9)%8$%0=%1; %8$%0=%1 + 1;

// Ending.  Called when the parsing is complete.
#define ARRAY_COUNT_END(%9)%8$ %8$

// Ending.  Called when there are no function parameters.
#define ARRAY_COUNT_NUL(%9)%8$ %8$

// Use the macro on a function.
ARRAY_COUNT:my_test_function(a, b[], c, const d[], &e = 6, string:f[] = "hi")
{
}

main()
{
	printf("There are %d array parameters to \"my_test_function\"", countOf_my_test_function);
}
```

### Console Output

```
There are 3 array parameters to "my_test_function"
```

### Explanation

To understand the code, we need a clear idea of the code inputs and outputs (and
a good understanding of the pre-processor helps as well).

This is the code input (input):

```pawn
my_test_function(a, b[], c, const d[], &e = 6, string:f[] = "hi")
```

This is the code output (output):

```pawn
stock const countOf_my_test_function = 0 + 1 + 1 + 1;
my_test_function(a, b[], c, const d[], &e = 6, string:f[] = "hi")
```

The bit of the output we really care about is just the first part:

```pawn
stock const countOf_my_test_function = 0 + 1 + 1 + 1;
```

This starts out as:

```pawn
stock const countOf_my_test_function = 0;
```

And has ` + 1` appended every time an array parameter is encountered, with other
parameters getting ignored (`0 + 1 + 1 + 1` can be done by the compiler, so will
only generate `3` in the AMX, not a string of sums).

The library handles the hard part of understanding all the function parameter
types (the input), but you still need to understand and split up your own code
(the output).

Line By Line

```pawn
#define ARRAY_COUNT:%1(%2) FUNC_PARSER(ARRAY_COUNT,ARR:NUM:)(%1(%2)) stock const countOf_%1 = 0; %1(%2)
```

```pawn
#define ARRAY_COUNT:%1(%2)
```

This is just the macro name and match as normal.  Will match anything that looks
like a function with a tag of `ARRAY_COUNT:`.

```pawn
FUNC_PARSER(ARRAY_COUNT,ARR:NUM:)(%1(%2))
```

Create a new function parser called `ARRAY_COUNT`, define which parameter types
it will analyse, and pass it the input.  The parameter type parsers are all
followed by colons and not separated by commas (or any spaces - that is VERY
important).

**DO NOT PUT ANY SPACES IN THIS PART!**

`ARR:` will detect any array.  `NUM:` is essentially *other* - it will detect
anything not detected by any other parser.  There is also `EXT:` (extended)
which will detect `...`, `REF:` (reference) which will detect `&a`, and `STR:`
(string) which will detect `string:a[]`.  This last point is important - because
strings look exactly like arrays (`a[]` and `a[]` - because they ARE arrays) but
are frequently handled differently (for example using `s` instead of `a` in
`CallRemoteFunction`) this library uses the YSI convention of prefixing all
strings with the `string:` tag.  This does not affect any other code in ANY way
- you won't even get any tag mismatch warnings because the tag is removed again
later on in the compilation process.  All it means is that the two types can be
differentiated.

### Exclude Strings

To modify the example so that strings are not included in the array count would
look like:

```pawn
#define ARRAY_COUNT:%1(%2) FUNC_PARSER(ARRAY_COUNT,ARR:NUM:STR:)(%1(%2)) stock const countOf_%1 = 0; %1(%2)
#define ARRAY_COUNT_STR(%9)%8$ %8$
```

`ARRAY_COUNT` is used as a prefix to all other macros, so is prepended whenever
a macro callback is called (with a `_` separator):

```pawn
#define ARRAY_COUNT_NUM(%9)%8$ %8$
```

`ARRAY_COUNT` is the custom prefix specified in the `FUNC_PARSER` call.  `_NUM`
is the suffix for any normal number variables (or anything not otherwise
matched).  `(%9)` is the parameters for this macro - things like name of the
variable, array size, default values, etc.  These are not used here, so they can
just be ignored.  `%8$` is required in both the input and the output, but is
exclusively part of the parser and is what makes the iteration work.  The
contents of `%8` are just the current parser state, `$` is the delimiter after
which comes your stuff (if desired, here it isn't).

```pawn
#define ARRAY_COUNT_ARR(%9)%8$%0=%1; %8$%0=%1 + 1;
```

This is a more complex callback.  Everything up to the `$` is the same -
parameters and internal state, with the `%8$` also appearing in the output
because it is always required (not putting that there will just break the
compilation).

In the `#define ARRAY_COUNT:` line, the first thing that came after the call to
`FUNC_PARSER` was ` stock const countOf_%1 = 0;`.  This is the start of user-
generated output, and is what now appears after the `$`.  So because we want to
change this to ` stock const countOf_%1 = 0 + 1;`, we match against that code
with: `%0=%1;` (technically even the `%0=` isn't required as `%1;` will just
match everything up to the first semi-colon).  Copying that to the output gives
`%0=%1 + 1;`.  We don't need the function definition at the very end, so there's
no point matching against it.

```pawn
#define ARRAY_COUNT_END(%9)%8$ %8$
```

Called when the parsing is complete.

```pawn
#define ARRAY_COUNT_NUL(%9)%8$ %8$
```

Called when there are no function parameters.

## Example 2 - Count All Parameters

We can extend the example again to count all parameter types.  For this, we will
set up some naming rules first:

Substitution parameter | Use
--- | ---
`%0` | The current reference count (`&a`).
`%1` | The current varargs count (`...`) - should only be 0 or 1 but the parser doesn't check that, it can parse quite incorrect code.
`%2` | The current array count (`a[]`).
`%3` | The current string count (`string:a[]`).
`%4` | The current other count (`a`).
`%8` | The parser state (black box).
`%9` | Unused other parameters.

```pawn
// Entry.  Parse all parameter types.
#define ALL_COUNT:%1(%2) FUNC_PARSER(ALL_COUNT,ARR:NUM:EXT:STR:REF:)(%1(%2)) \
	stock const \
		refCount_%1 = 0, \
		extCount_%1 = 0, \
		arrCount_%1 = 0, \
		strCount_%1 = 0, \
		numCount_%1 = 0; \
	%1(%2)

// Counts.  Add one to the relevant number.
#define ALL_COUNT_REF(%9)%8$%0,%1,%2,%3,%4; %8$%0 + 1,%1,%2,%3,%4;
#define ALL_COUNT_EXT(%9)%8$%0,%1,%2,%3,%4; %8$%0,%1 + 1,%2,%3,%4;
#define ALL_COUNT_ARR(%9)%8$%0,%1,%2,%3,%4; %8$%0,%1,%2 + 1,%3,%4;
#define ALL_COUNT_STR(%9)%8$%0,%1,%2,%3,%4; %8$%0,%1,%2,%3 + 1,%4;
#define ALL_COUNT_NUM(%9)%8$%0,%1,%2,%3,%4; %8$%0,%1,%2,%3,%4 + 1;

// Endings
#define ALL_COUNT_END(%9)%8$ %8$
#define ALL_COUNT_NUL(%9)%8$ %8$
```

The first macro is spread over multiple lines for clarity, but doesn't have to
be.

Use:

```pawn
ALL_COUNT:all_test_function(a, b[], c, const d[], &e = 6, string:f[] = "hi")
{
}

main()
{
	printf("There are %d reference parameters to all_test_function", refCount_all_test_function);
	printf("There are %d extended parameters to all_test_function",  extCount_all_test_function);
	printf("There are %d array parameters to all_test_function",     arrCount_all_test_function);
	printf("There are %d string parameters to all_test_function",    strCount_all_test_function);
	printf("There are %d other parameters to all_test_function",     numCount_all_test_function);
}
```

## Example 3 - Count Array Parameters And Sum Their Size

Lets go back to the first example and modify it to show not just the number of
array parameters, but also their combined size.  First a side-note - function
array parameters are often written as `[]`, which we will count as a size of 0.
However, writing `1 +  + 10` is not valid syntax - we actually need a number
there.  Writing `(size +0)` when there is a size will resolve to `(size)`, when
there isn't a size it will resolve to `(+0)`, the unary plus and legal, giving
`(1+0) + (+0) + (1+0)`.  This is the simplest method of dealing with potentially
empty macros.

How do we get the size though?

Previously the addition macro was:

```pawn
#define ARRAY_COUNT_ARR(%9)%8$%0=%1; %8$%0=%1 + 1;
```

The `(%9)` was a placeholder for parameters we didn't care about - it will
consume them all and drop them.  However, each of the `_ARR`, `_STR`, `_NUM`,
`_EXT`, and `_REF` macros take several parameters:

Substitution parameter | Use
--- | ---
`%0`  | `const ` (if it exists).
`%1`  | The tag (if there is one - and only the first if there are many, includes the `:`).
`%2`  | The variable name (only always present value).
`%3`  | Length (strings only).
`%4`  | Default value (if it exists, not on arrays).
`%3+` | Dimension sizes (arrays only).

These parameters:

```pawn
const Float:pos[3]
string:name[] = "Bob"
&v
Float:v = 0
```

Would call as:

```pawn
ARRAY_COUNT_ARR(const ,Float:,pos,3)
ARRAY_COUNT_STR(,,name,,"Bob")
ARRAY_COUNT_REF(,,v,)
ARRAY_COUNT_NUM(,Float:,v,0)
```

Note that the `string:` tag does NOT get passed - it is special and purely used
for internal differentiation.

We can thus change the macro to use one parameter and just ignore the others:

```pawn
#define ARRAY_COUNT_ARR(%0,%1,%2,%3)%8$%6;%7; %8$%6 + 1;%7 + (%3 +0);
```

If you didn't know, you can also use the same substitution variable multiple
times in one macro, with the value getting overridden each time.  I like to do
this on values that are getting ignored, with `%9` for it:

```pawn
#define ARRAY_COUNT_ARR(%9,%9,%9,%4)%8$%0;%1; %8$%0 + 1;%1 + (%4 +0);
```

This makes the full thing:

```pawn
// The entry point.  Defines our parser.
#define ARRAY_COUNT:%1(%2) FUNC_PARSER(ARRAY_COUNT,ARR:NUM:)(%1(%2)) stock const countOf_%1 = 0; stock const sizeOf_%1 = 0; %1(%2)
#define ARRAY_COUNT_NUM(%9)%8$ %8$
#define ARRAY_COUNT_ARR(%9,%9,%9,%3)%8$%0;%1; %8$%0 + 1;%1 + (%3 +0);
#define ARRAY_COUNT_END(%9)%8$ %8$
#define ARRAY_COUNT_NUL(%9)%8$ %8$

// Use the macro on a function.
ARRAY_COUNT:my_test_function(a, b[], c, const d[], &e = 6, string:f[] = "hi")
{
}

main()
{
	printf("There are %d array parameters with size %d to \"my_test_function\"", countOf_my_test_function, sizeOf_my_test_function);
}
```

Tags are always included with their `:`.  This could be detected and ignored
with:

```pawn
#define PREFIX_ARR(%0,%1:,%2,%3)%8$ %8$
```

But it should be noted that while that will return tags without their colon, it
will now fail to work for any variable without a tag at all.

## Example 4 - Auto-Generate `CallRemoteFunction` Specifier Strings

Time for a more advanced example, using the parameter names more.  The end
result will be a new keyword `remote` which behaves like `public`, but also
generates code to call `CallRemoteFunction` directly with the correct string
specifier for out function.  Doing:

```pawn
remote my_func(a, b[], c)
{
}
```

Will generate:

```pawn
my_func(a, b[], c) CallRemoteFunction("remote_my_func", "iai", a, b, c);
forward remote_my_func(a, b[], c);
public remote_my_func(a, b[], c)
{
}
```

Thus just doing: `my_func(10, arr, sizeof (arr));` in code will call all scripts
at once, not just this one.

A normal macro would not be able to determine the exact string `iai` to use in
this situation, and just using the parameters directly in `CallRemoteFunction`
would result in the invalid call `a, b[], c`.

First, we define the entry point and bulk of the output:

```pawn
#define remote%0(%1) FUNC_PARSER(REMOTE,ARR:STR:NUM:)(%0(%1)) \
	%0(%1) CallRemoteFunction("remote_"#%0, ##); \
	forward remote_%0(%1); \
	public remote_%0(%1)
```

We also define a helper macro to turn `remote_ my_func` in to `remote_my_func`:

```pawn
#define remote_%0\32; remote_%0
```

For each of the parameter types, we add a letter to the end of the specifier
string, and add the parameter name to the end of the `CallRemoteFunction`
parameter list:

```pawn
#define REMOTE_ARR(%9,%9,%2,%9)%8$%0(%1)%3(%4#%5#%6#%7) %8$%0(%1)%3(%4#%5#%6a#%7,%2)
#define REMOTE_STR(%9,%9,%2,%9)%8$%0(%1)%3(%4#%5#%6#%7) %8$%0(%1)%3(%4#%5#%6s#%7,%2)
#define REMOTE_NUM(%9,%9,%2)%8$%0(%1)%3(%4#%5#%6#%7) %8$%0(%1)%3(%4#%5#%6i#%7,%2)
```

You could abstract this further, since the only tiny difference between those
three macros is the letter inserted at the end between the two `#`s.  The reason
why `%0(%1)%3(%4#` was used instead of just `%0#` to skip over everything up to
the first `#` is that the `#` is inside some brackets, and they are handled very
specially by the pre-processor unless you explicitly match against the `(`.

Finally, we need the two end macros because they are required but don't do
anything in this instance:

```pawn
#define REMOTE_END(%9)%8$ %8$
#define REMOTE_NUL(%9)%8$ %8$
```

### Three Facts

1. The `forward` keyword is optional.

2. A public function with only a semi-colon after it is a forward.

3. An `@` prefix declares a function public.

We can thus shrink this code to:

```pawn
#define remote%0(%1) FUNC_PARSER(REMOTE,ARR:STR:NUM:)(%0(%1)) stock%0(%1)CallRemoteFunction("@r_"#%0,##);@r_%0(%1);@r_%0(%1)
#define @r_%0\32; @r_
```

As a side-effect of point interesting fact 2, writing this:

```pawn
remote truly_remote(x, y, z);
```

Will declare the function but not define it, allowing a function in a different
script to be easilly called from here.

### Tags

You may have noticed that all normal variables are passed as `i`, never `f`.
PAWN is typeless - the tags are only a hint to the compiler, and only matter at
all for some operators, which can be overloaded based on tag.  Using `i` instead
of `f` makes no difference at all here.  To be really strict you could use:

```pawn
#define REMOTE_NUM(%9,%9,%2)%8$%0(%1)%3(%4#%5#%6#%7) %8$%0(%1)%3(%4#%5#%6i#%7,_:%2)
```

Detecting only the `Float:` tag and leaving all others is much more involved,
and just not worth it.

## Example 5 - Output Input Exactly

For the next example, we are going to write a set of macros that perfectly
output their input...  This sounds pointless - and in code it would be, but is
important here for demonstrating every parameter of every callback macro,
including some I slightly lied about previously (or rather simplified).  The
first lie was about default parameters.

### Lie 1

Earlier I stated that:

```pawn
const Float:pos[3]
string:name[] = "Bob"
&v
Float:v = 0
```

Gave:

```pawn
ARRAY_COUNT_ARR(const ,Float:,pos,3)
ARRAY_COUNT_STR(,,name,,"Bob")
ARRAY_COUNT_REF(,,v)
ARRAY_COUNT_NUM(,Float:,v,0)
```

In actual fact, when a default value is present an extra bit is appended to the
macro name to aid in processing.  So the real output is:

```pawn
ARRAY_COUNT_ARR(const ,Float:,pos,3)
ARRAY_COUNT_STR_DEF(,,name,,"Bob")
ARRAY_COUNT_REF(,,v)
ARRAY_COUNT_NUM_DEF(,Float:,v,0)
```

Note that `const ` has a space after it (the reason for which will be seen
shortly).

The other potential suffix is for multi-dimensional arrays:

```pawn
const Float:pos[][3][MY_ENUM]
```

Becomes:

```pawn
ARRAY_COUNT_ARR_ARR_ARR(const,Float:,pos,,3,MY_NUM)
```

The number of `_ARR` suffixes determine the number of dimensions.

The parameters might be a little confusing, so:

```pawn
PREFIX_NUM(const, tag, name)
PREFIX_NUM_DEF(const, tag, name, default)
PREFIX_REF(, tag, name)
PREFIX_REF_DEF(, tag, name, default)
PREFIX_EXT(, tag,)
PREFIX_STR(const,, name, size)
PREFIX_STR_DEF(const,, name, size, default)
PREFIX_ARR(const, tag, name, size_1)
PREFIX_ARR_ARR(const, tag, name, size_1, size_2)
PREFIX_ARR_ARR_ARR(const, tag, name, size_1, size_2, size_3)
PREFIX_ARR_ARR_ARR_ARR(const, tag, name, size_1, size_2, size_3, size_4)
```

Reference parameters can never be `const ` (that makes no sense), so they will
never have `const ` passed.  However, they still have the parameter there but it
is safe to ignore.  Same with extended (vararg) parameters, which can also not
have default values so there is no `_DEF` variant of them.  For everything else
the `const ` is optional - it may be there or it may be a blank parameter.  As
we will see, often it doesn't matter either way.  Finally, anything more than
two dimensions in an array and the user should probably rethink everything
anyway, so don't worry about the really long ones.  Strings have the tag
parameter but never use it, and can only ever have one dimension.

### Lie 2

The other simplification was that all of these variations are detected for you -
they are not, they must be requested.  Each type (with/without const, defaults,
etc) requires extra macros.  It is always STRONGLY recommended that you use the
updated compiler where this doesn't matter at all, but for very complex macros
on the default compiler, long functions with many options may blow past the line
length limit.  Also, for some contexts it may not matter - public functions
can't have default values etc, so why bother scanning for them doing extra work
that isn't required?  The options are:

Name | Use
--- | ---
TAG | Look for tags.
MUL | Allow multi-dimensional arrays (more than one dimension).
CST | Look for `const `.
DEF | Look for defaults.

The earlier parsers shown didn't use any of these, as often they weren't needed
because the actual values weren't used.  A parser that would detect every
combination of parameter types would look something like:

```pawn
FUNC_PARSER(REBUILD,ARR_MUL_TAG_CST:NUM_TAG_CST_DEF:REF_TAG_DEF:EXT_TAG:STR_CST_DEF:)(input)
```

There are also longer synonyms if you prefer clarity:

```pawn
FUNC_PARSER(REBUILD,ARRAY_TAG_CONST_MULTI:NUMBER_CONST_TAG_DEFAULT:TAG_REFERENCE_DEFAULT:TAG_VARARG:DEFAULT_STRING_CONST:)(input)
```

Clearly, the order of parts doesn't matter - `ARR_MUL_CST` and `CST_MUL_ARR` are
the same.

### Output One Parameter

The code to output one parameter exactly as it came in would be:

```pawn
#define REBUILD_NUM(%0,%1,%2)%8$                         %8$%0 %1%2
#define REBUILD_NUM_DEF(%0,%1,%2,%4)%8$                  %8$%0 %1%2     = %4
#define REBUILD_REF(,%1,%2)%8$                           %8$ & %1%2
#define REBUILD_REF_DEF(,%1,%2,%4)%8$                    %8$ & %1%2     = %4
#define REBUILD_EXT(,%1,)%8$                             %8$   %1...
#define REBUILD_STR(%0,,%2,%3)%8$                        %8$%0   %2[%3]
#define REBUILD_STR_DEF(%0,,%2,%3,%4)%8$                 %8$%0   %2[%3] = %4
#define REBUILD_ARR(%0,%1,%2,%3)%8$                      %8$%0 %1%2[%3]
#define REBUILD_ARR_ARR(%0,%1,%2,%3,%4)%8$               %8$%0 %1%2[%3][%4]
#define REBUILD_ARR_ARR_ARR(%0,%1,%2,%3,%4,%5)%8$        %8$%0 %1%2[%3][%4][%5]
#define REBUILD_ARR_ARR_ARR_ARR(%0,%1,%2,%3,%4,%5,%6)%8$ %8$%0 %1%2[%3][%4][%5][%6]
```

If there is a `const `, it will appear.  If there isn't it won't.  If there is a
tag it will appear.  If there isn't it won't.  Further, the `const ` parameter
actually includes its own space for efficiency reasons, so this works too:

```pawn
#define REBUILD_NUM(%0,%1,%2)%8$                         %8$%0%1%2
#define REBUILD_NUM_DEF(%0,%1,%2,%4)%8$                  %8$%0%1%2=%4
#define REBUILD_REF(,%1,%2)%8$                           %8$&%1%2
#define REBUILD_REF_DEF(,%1,%2,%4)%8$                    %8$&%1%2=%4
#define REBUILD_EXT(,%1,)%8$                             %8$%1...
#define REBUILD_STR(%0,,%2,%3)%8$                        %8$%0%2[%3]
#define REBUILD_STR_DEF(%0,,%2,%3,%4)%8$                 %8$%0%2[%3]=%4
#define REBUILD_ARR(%0,%1,%2,%3)%8$                      %8$%0%1%2[%3]
#define REBUILD_ARR_ARR(%0,%1,%2,%3,%4)%8$               %8$%0%1%2[%3][%4]
#define REBUILD_ARR_ARR_ARR(%0,%1,%2,%3,%4,%5)%8$        %8$%0%1%2[%3][%4][%5]
#define REBUILD_ARR_ARR_ARR_ARR(%0,%1,%2,%3,%4,%5,%6)%8$ %8$%0%1%2[%3][%4][%5][%6]
```

### Output Everything

That code will correctly render each individual parameter, but will not
correctly reform a full function call.  There are no commas and, because there
is no matching against everything already output, this will reverse the
parameters (which is a cool trick, but not what we want here).  The larger
version would look like the following, using a second `$` to denote the current
end of the parameter list:

```pawn
#define REBUILD:%0(%1) FUNC_PARSER(REBUILD,ARR_MUL_TAG_CST:NUM_TAG_CST_DEF:REF_TAG_DEF:EXT_TAG:STR_CST_DEF:)(%0(%1))%0($)

#define REBUILD_NUM(%0,%1,%2)%8$%7(%9$)                         %8$%7(%9, %0 %1%2                $)
#define REBUILD_NUM_DEF(%0,%1,%2,%4)%8$%7(%9$)                  %8$%7(%9, %0 %1%2     = %4       $)
#define REBUILD_REF(,%1,%2)%8$%7(%9$)                           %8$%7(%9,  & %1%2                $)
#define REBUILD_REF_DEF(,%1,%2,%4)%8$%7(%9$)                    %8$%7(%9,  & %1%2     = %4       $)
#define REBUILD_EXT(,%1,)%8$%7(%9$)                             %8$%7(%9,    %1...               $)
#define REBUILD_STR(%0,,%2,%3)%8$%7(%9$)                        %8$%7(%9, %0   %2[%3]            $)
#define REBUILD_STR_DEF(%0,,%2,%3,%4)%8$%7(%9$)                 %8$%7(%9, %0   %2[%3] = %4       $)
#define REBUILD_ARR(%0,%1,%2,%3)%8$%7(%9$)                      %8$%7(%9, %0 %1%2[%3]            $)
#define REBUILD_ARR_ARR(%0,%1,%2,%3,%4)%8$%7(%9$)               %8$%7(%9, %0 %1%2[%3][%4]        $)
#define REBUILD_ARR_ARR_ARR(%0,%1,%2,%3,%4,%5)%8$%7(%9$)        %8$%7(%9, %0 %1%2[%3][%4][%5]    $)
#define REBUILD_ARR_ARR_ARR_ARR(%0,%1,%2,%3,%4,%5,%6)%8$%7(%9$) %8$%7(%9, %0 %1%2[%3][%4][%5][%6]$)

#define REBUILD_END(%9)%8$%7(,%9$) %8$%7(%9)
#define REBUILD_NUL(%9)%8$%7($)    %8$%7()
```

Here the two ending macros come in useful.  Before they trigger the first
parameter will have a leading comma, and the last parameter will have a trailing
dollar.  They remove those match artifacts.

## Example 6 - Remotes With Alternate Return Types

A reminder of the current `remote` macro:

```pawn
#define remote%0(%1) FUNC_PARSER(REMOTE,ARR:STR:NUM:)(%0(%1)) \
	stock %0(%1) CallRemoteFunction("remote_"#%0, ##); \
	forward remote_%0(%1); \
	public remote_%0(%1)

#define remote_%0\32; remote_%0

#define REMOTE_ARR(%9,%9,%2,%9)%8$%0(%1)%3(%4#%5#%6#%7) %8$%0(%1)%3(%4#%5#%6a#%7,%2)
#define REMOTE_STR(%9,%9,%2,%9)%8$%0(%1)%3(%4#%5#%6#%7) %8$%0(%1)%3(%4#%5#%6s#%7,%2)
#define REMOTE_NUM(%9,%9,%2)%8$%0(%1)%3(%4#%5#%6#%7)    %8$%0(%1)%3(%4#%5#%6i#%7,%2)

#define REMOTE_END(%9)%8$ %8$
#define REMOTE_NUL(%9)%8$ %8$
```

Modifying this to return a value is apparently simple:

```pawn
#define remote%0(%1) FUNC_PARSER(REMOTE,ARR:STR:NUM:)(%0(%1)) \
	stock %0(%1) return CallRemoteFunction("remote_"#%0, ##); \
	forward remote_%0(%1); \
	public remote_%0(%1)
```

But optionally returning a value not so much.

### No Return

In this library and others (YSI) *no return* uses the C naming of `void:` when
the code from returns and no returns is different.

Adding a return value was simple, but it may not always be wanted if the
underlying function doesn't return a value.  This is where `void:` comes in.
`void:` is similar to `string:` in that it is not a real tag, just a macro to
provide hints to parsers on what code to generate.  It is removed from the final
code (not that this would make any difference - you can't get a tag mismatch
warning when you don't return anything at all - that's an error regardless of
the tag).

We can request parsing of return types in the same way as parameters (`RET` = 
`RETURN`, `VOD` = `VOID`):

```pawn
FUNC_PARSER(REMOTE,ARR:STR:NUM:RET_VOD:)
```

If no special return type is found, it is assumed to be a normal return, and
this fact is passed to the end macros, where we can insert the `return`:

```pawn
#define REMOTE_END(%9)%8$%0(%1) %8$%0(%1)return
#define REMOTE_NUL(%9)%8$%0(%1) %8$%0(%1)return
```

To ensure a space is inserted between `return` and `CallRemoteFunction`, more
matching is required (trailing spaces on the replacement value are simply
ignored):

```pawn
#define REMOTE_END(%9)%8$%0(%1)%2(%3) %8$%0(%1)return %2(%3)
#define REMOTE_NUL(%9)%8$%0(%1)%2(%3) %8$%0(%1)return %2(%3)
```

Since we have requested detection of `void:`, handle that case as well:

```pawn
#define REMOTE_END_VOD(%9)%8$ %8$
#define REMOTE_NUL_VOD(%9)%8$ %8$
```

There is no `return` by default, so if one isn't needed there is nothing to do.

### Tag Return

A tag return is passed as an extra macro parameter.

```pawn
FUNC_PARSER(REMOTE,ARR:STR:NUM:RET_TAG:)
#define REMOTE_END_TAG(%7,%9)%8$%0(%1)%2(%3) %8$%0(%1)return %7:%2(%3)
```

There is no much to say about these - for the most part tags aren't actually
that interesting from a code generation point of view since they behave the same
as tagless returns, and in almost all code location `tag:func()` is just as
valid as `func()`, so there's no point detecting them.

Detecting either return variation would look like:

```pawn
FUNC_PARSER(REMOTE,ARR:STR:NUM:RET_TAG_VOD:)

#define REMOTE_END_TAG(%7,%9)%8$%0(%1)%2(%3) %8$%0(%1)return %7:%2(%3)
#define REMOTE_END(%9)%8$%0(%1)%2(%3) %8$%0(%1)return %2(%3)
#define REMOTE_END_VOD(%9)%8$ %8$

#define REMOTE_NUL_TAG(%7,%9)%8$%0(%1)%2(%3) %8$%0(%1)return %7:%2(%3)
#define REMOTE_NUL(%9)%8$%0(%1)%2(%3) %8$%0(%1)return %2(%3)
#define REMOTE_NUL_VOD(%9)%8$ %8$
```

### String Return

At a basic level, string returns are handled the same as other return types:

```pawn
FUNC_PARSER(REMOTE,ARR:STR:NUM:RET_STR:)

#define REMOTE_END_STR(%9)%8$%0(%1)%2(%3) %8$%0(%1)return %2(%3)
#define REMOTE_END(%9)%8$%0(%1)%2(%3) %8$%0(%1)return %2(%3)
```

That's the generic version, but `CallRemoteFunction` can't return a string, so
for this example some serious restructuring is required to enable it.  If the
underlying function has a string return, the public function should wrap that in
something else, like a property, and the called function should return that
property's contents.  There are several other considerations and corner cases
for a full version of this code, but they aren't important here.  The output of
a regular return should look like:

```pawn
stock my_func(a, b[], c)
{
	return CallRemoteFunction("remote_my_func", "iai", a, b, c);
}

forward remote_my_func(a, b[], c);
public remote_my_func(a, b[], c)
{
	return 1;
}
```

While the output of a string return should be quite structurally different:

```pawn
stock my_func(a, b[], c)
{
	new ret[32];
	CallRemoteFunction("remote_my_func", "iai", a, b, c);
	getproperty(0, "", 101, ret);
	return ret;
}

forward remote_my_func(a, b[], c);
public remote_my_func(a, b[], c)
{
	setproperty(0, "", 101, underlying_my_func(a, b, c));
}

static underlying_my_func(a, b[], c)
{
	// Can't return string literals in this design, even with the new compiler.
	new ret[32] = "hi";
	return ret;
}
```

There are three parameter-dependent parts of this code: the input parameters
`a, b[], c`, the call parameters `a, b, c`, and the specifier `iai`, each used
in potentially many places.  Creating the full code structure from the start as
done before is non trivial, instead I like to collate all the data THEN build
the structure:

```pawn
#define remote%0(%1) FUNC_PARSER(REMOTE,ARR:STR:NUM:RET_TAG_VOD_STR:)(%0(%1)) %0(%1)##$
#define remote_%0\32; remote_%0
```

The output here is very simply `%0(%1)##$` - this is just our structure in to
which all the individual components will be placed for later processing.  To
insert the parameters looks like:

```pawn
#define REMOTE_ARR(%9,%9,%2,%9)%8$%0(%1)#%6#%7$ %8$%0(%1)#%6a#%7,%2$
#define REMOTE_STR(%9,%9,%2,%9)%8$%0(%1)#%6#%7$ %8$%0(%1)#%6s#%7,%2$
#define REMOTE_NUM(%9,%9,%2)%8$%0(%1)#%6#%7$    %8$%0(%1)#%6i#%7,%2$
```

After the processing of the `my_func(a, b[], c)` example, this will have
produced:

```pawn
my_func(a, b[], c)#iai#, a, b, c$
```

Not valid code, but has all the components required to generate the full code.
The basic version is simple, and now happens in the end macro instead:

```pawn
#define REMOTE_END(%9)%8$%0(%1)#%6#,%7$ %8$ \
	stock %0(%1) return CallRemoteFunction("remote_"#%0, #%6#,%7); \
	forward remote_%0(%1); \
	public remote_%0(%1)

#define REMOTE_NUL(%9)%8$%0(%1)##$ %8$ \
	stock %0(%1) return CallRemoteFunction("remote_"#%0, ##); \
	forward remote_%0(%1); \
	public remote_%0(%1)
```

Void returns are also simple (and almost identical):

```pawn
#define REMOTE_END_VOD(%9)%8$%0(%1)#%6#,%7$ %8$ \
	stock %0(%1) CallRemoteFunction("remote_"#%0, #%6#,%7); \
	forward remote_%0(%1); \
	public remote_%0(%1)

#define REMOTE_NUL_VOD(%9)%8$%0(%1)##$ %8$ \
	stock %0(%1) CallRemoteFunction("remote_"#%0, ##); \
	forward remote_%0(%1); \
	public remote_%0(%1)
```

`,%7` could be written in all places above as `%7` - there is a leading comma
from the processing, but it is required in the `CallRemoteFunction` parameter
list.  In that case the `_NUL` variants become identical to the `_END` variants:

```pawn
#define REMOTE_END(%9)%8$%0(%1)#%6#%7$ %8$ \
	stock %0(%1) return CallRemoteFunction("remote_"#%0, #%6#%7); \
	forward remote_%0(%1); \
	public remote_%0(%1)

#define REMOTE_END_VOD(%9)%8$%0(%1)#%6#%7$ %8$ \
	stock %0(%1) CallRemoteFunction("remote_"#%0, #%6#%7); \
	forward remote_%0(%1); \
	public remote_%0(%1)

#define REMOTE_NUL REMOTE_END
#define REMOTE_NUL_VOD REMOTE_END_VOD
```

Where this is not the case is in the `underlying_` parameter list in the string
return variant (`_STR`).  Detection of the leading comma is required then:

```pawn
#define REMOTE_END_STR(%9)%8$%0(%1)#%6#,%7$ %8$ \
	stock %0(%1)                                    \
	{                                               \
		new ret[32] = "";                           \
		CallRemoteFunction("remote_"#%0, #%6#,%7);  \
		getproperty(0, "", 101, ret);               \
		return ret;                                 \
	}                                               \
	                                                \
	forward remote_%0(%1);                          \
	public remote_%0(%1)                            \
	{                                               \
		setproperty(0, "", 101, underlying_%0(%7)); \
	}                                               \
	                                                \
	stock underlying_%0(%1)

#define REMOTE_NUL_STR(%9)%8$%0(%1)##$ %8$ \
	stock %0()                                    \
	{                                             \
		new ret[32] = "";                         \
		CallRemoteFunction("remote_"#%0, #%6#);   \
		getproperty(0, "", 101, ret);             \
		return ret;                               \
	}                                             \
	                                              \
	forward remote_%0();                          \
	public remote_%0()                            \
	{                                             \
		setproperty(0, "", 101, underlying_%0()); \
	}                                             \
	                                              \
	static underlying_%0()

#define underlying_%0\32; underlying_%0
```

### String Return Code Issues

The above code was spread out, and actually wrong.  This:

```pawn
#define underlying_%0\32; underlying_%0
```

Will output:

```pawn
underlying_string:my_func()
```

Because we are using the original function name given to the parser, not the
parsed name.

Combinations of `const ` and defaults (parameter tags can be ignored) are not
well handled.  The `public` function should keep `const `, but drop defaults;
the `CallRemoteFunction` call should drop both parts, so we actually need to
track three variations of the parameters:

```pawn
(a, const b[], c = 11)
(a, const b[], c)
(a, b, c)
```

Most `remote` declarations can also act as their own `forward`:

```pawn
remote void:other_func_6(a, c, const b[6]);
```

`string:` ones cannot, as the final function is the `underlying_` one, which is
actually called from the `remote_` public, but will not be implemented.

The full code to fix these issues (except the `string:` forwarding) is below.
It is already a lot more complex, but with any parser you must assess how much
flexibility you want to allow - maybe default values can be banned for example.

### Complete String Return Code

```pawn
#define remote%0(%1) FUNC_PARSER(REMOTE,ARR_CST:STR_CST_DEF:NUM_CST_DEF:RET_TAG_VOD_STR:)(%0(%1)) ()(%1)##$

#define REMOTE_STR_DEF(%0,%1,%2,%3,%4)%8$(%9)(%5)#%6#%7$ %8$(%9,%0%2[%3])(%5)#%6s#%7,%2$
#define REMOTE_NUM_DEF(%0,%1,%2,%4)%8$(%9)(%5)#%6#%7$    %8$(%9,%0%2)(%5)#%6i#%7,%2$

#define REMOTE_ARR(%0,%1,%2,%3)%8$(%9)(%5)#%6#%7$ %8$(%9,%0%2[%3])(%5)#%6a#%7,%2$
#define REMOTE_STR(%0,%1,%2,%3)%8$(%9)(%5)#%6#%7$ %8$(%9,%0%2[%3])(%5)#%6s#%7,%2$
#define REMOTE_NUM(%0,%1,%2)%8$(%9)(%5)#%6#%7$    %8$(%9,%0%2)(%5)#%6i#%7,%2$

#define REMOTE_END(%9)%8$(,%1)(%5)#%6#,%7$ %8$ \
	stock %9(%5) return CallRemoteFunction("remote_"#%9, #%6#,%7); \
	forward remote_%9(%1); \
	public remote_%9(%1)

#define REMOTE_END_VOD(%9)%8$(,%1)(%5)#%6#,%7$ %8$ \
	stock %9(%5) CallRemoteFunction("remote_"#%9, #%6#,%7); \
	forward remote_%9(%1); \
	public remote_%9(%1)

#define REMOTE_END_TAG(%3,%9)%8$(,%1)(%5)#%6#,%7$ %8$ \
	stock %3%9(%5) return %3CallRemoteFunction("remote_"#%9, #%6#,%7); \
	forward %3remote_%9(%1); \
	public %3remote_%9(%1)

#define REMOTE_NUL(%9)%8$()()##$ %8$ \
	stock %9() return CallRemoteFunction("remote_"#%9, ##); \
	forward remote_%9(); \
	public remote_%9()

#define REMOTE_NUL_VOD(%9)%8$()()##$ %8$ \
	stock %9() CallRemoteFunction("remote_"#%9, ##); \
	forward remote_%9(); \
	public remote_%9()

#define REMOTE_NUL_TAG(%3,%9)%8$()()##$ %8$ \
	stock %3%9() return %3CallRemoteFunction("remote_"#%9, ##); \
	forward %3remote_%9(); \
	public %3remote_%9()

#define REMOTE_END_STR(%9)%8$(,%1)(%5)#%6#,%7$ %8$  \
	stock %9(%5)                                    \
	{                                               \
		new ret[32] = "";                           \
		CallRemoteFunction("remote_"#%9, #%6#,%7);  \
		getproperty(0, "", 101, ret);               \
		return ret;                                 \
	}                                               \
	                                                \
	forward remote_%9(%1);                          \
	public remote_%9(%1)                            \
	{                                               \
		setproperty(0, "", 101, underlying_%9(%7)); \
	}                                               \
	                                                \
	stock underlying_%9(%1)

#define REMOTE_NUL_STR(%9)%8$()()##$ %8$            \
	stock %9()                                      \
	{                                               \
		new ret[32] = "";                           \
		CallRemoteFunction("remote_"#%9, #%6#);     \
		getproperty(0, "", 101, ret);               \
		return ret;                                 \
	}                                               \
	                                                \
	forward remote_%9();                            \
	public remote_%9()                              \
	{                                               \
		setproperty(0, "", 101, underlying_%9());   \
	}                                               \
	                                                \
	static underlying_%9()

#define underlying_%9\32; underlying_%9
#define remote_%9\32; remote_%9
```

### Use

```pawn
remote DB:other_func_1(a, c, b[]);

remote other_func_2(a, c, string:b[]);

remote string:other_func_3(Text:a, c, b[])
{
	new ret[32] = "hello";
	return ret;
}

remote File:other_func_4(Text:a, c, const b[]);

remote other_func_5(Text:a, c, b[]);

remote void:other_func_6(a, c, const b[6]);

remote other_func_7(a, c, b[]);

remote other_func_8(const a, b[], Float:c);

remote void:other_func_9(const Float:a, c, b[]);

remote other_func_0(const Float:a, c, b[]);

remote string:other_func_a(const Float:a, c, b[])
{
	new ret[32] = "implemented";
	return ret;
}

remote Float:other_func_b(const a, b[], c = 6);

remote other_func_c(const a, c, b[]);

remote void:other_func_d(const a, c, b[]);

remote other_func(a, c, b[])
{
	return 100;
}

main()
{
	new var, Float:flt, str[32];
    new arr[6] = { 1, 2, 3, 4, 5, 6 };
	      other_func_1(66, 99, arr);
	var = other_func_2(66, 99, "hi");
	str = other_func_3(Text:56, 4, arr);
	      other_func_4(Text:32, 5, arr);
	var = other_func_5(Text:9, 6, arr);
	      other_func_6(5, 7, arr);
	var = other_func_7(5, 7, arr);
	var = other_func_8(700, arr, 99.0);
	      other_func_9(1.1, 11, arr);
	var = other_func_0(1.2, 12, arr);
	str = other_func_a(1.3, 13, arr);
	flt = other_func_b(555, arr);
	var = other_func_c(6, 9, arr);
	      other_func_d(6, 9, arr);
	var = other_func(0, 1, arr);
}
```

Note that all of these examples are actually broken - an array passed to
`CallRemoteFunction` *MUST* be immediately followed by its length, none of these
ones do that and so won't work.  There are ways to enforce this at compile-time,
but the library currently doesn't.

## Example 7 - y_timers Clone

This example is actually probably simpler than the last one, but I said I would
end on it, so I will.

The end result is three macros - `timer`, `defer`, and `repeat`; that in order
declare a timer with parameters, call it after a delay, and call it repeatedly
on a loop.  The full version of the library allows for overriding the times at
the call site as well as the declaration site, but this clone will not.  It is
also simplified by the fact that timers can't have return values.  The full
version also fixes arrays, this one again doesn't, but that's not pre-processor
code.  See Slice's include if you want a simple ready-made independent fix for
that.

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:NUM_CST_DEF:LEN:)(%0(%1)) [%2]()(%1)##$

#define TIMER_STR_DEF(%0,%1,%2,%3,%4)%8$[%1](%9)(%5)#%6#%7$ %8$[%1](%9,%0%2[%3])(%5)#%6s#%7,%2$
#define TIMER_NUM_DEF(%0,%1,%2,%4)%8$[%1](%9)(%5)#%6#%7$    %8$[%1](%9,%0%2)(%5)#%6i#%7,%2$
#define TIMER_ARR(%0,%1,%2,%3)%8$[%1](%9)(%5)#%6#%7$        %8$[%1](%9,%0%2[%3])(%5)#%6a#%7,%2$
#define TIMER_STR(%0,%1,%2,%3)%8$[%1](%9)(%5)#%6#%7$        %8$[%1](%9,%0%2[%3])(%5)#%6s#%7,%2$
#define TIMER_NUM(%0,%1,%2)%8$[%1](%9)(%5)#%6#%7$           %8$[%1](%9,%0%2)(%5)#%6i#%7,%2$

#define TIMER_END(%9)%8$[%2](,%1)(%5)#%6#,%7$ %8$ \
	stock defer_%9(__rep, %5) return SetTimerEx("timer_"#%9, (%2), __rep, #%6#, %7); \
	forward timer_%9(%1); \
	public timer_%9(%1)

#define TIMER_NUL(%9)%8$[%2]()()##$ %8$ \
	stock defer_%9(__rep) return SetTimer("timer_"#%9, (%2), __rep); \
	forward timer_%9(); \
	public timer_%9()

#define timer_%9\32; timer_%9
#define defer_%9\32; defer_%9

#define _:%0,) _:%0)
#define defer%0(%1) defer_%0(_:0,%1)
#define repeat%0(%1) defer_%0(_:1,%1)
```

One tiny new macro to draw your attention to:

```pawn
#define _:%0,) _:%0)
```

This consumes a trailing comma after the last parameter in a list.  It cannot be
used everywhere, since you can't always know the true tag to use, but is useful
in cases like this where you can control the tag, and know that there may not be
any more parameters.  Despite seemingly overriding the default `_:` tag, it only
matches in very specific (otherwise invalid) cases so it doesn't break anything.
YSI has had this macro for years, and no-one has complained yet about it
breaking anything...

### Use

```pawn
timer my_timer_1[500](const a, string:b[], c = 5)
{

}

timer my_timer_2[500](const a, string:b[], c = 5)
{

}

timer my_timer_3[500](const a, string:b[])
{

}

timer my_timer_4[500](const a, b[], d)
{

}

timer my_timer_5[500](const a, b[], d = sizeof (b))
{

}

timer my_timer_6[500](const a, b[], const d, e[], f)
{

}

main()
{
	defer my_timer_1(34, "hi");
	repeat my_timer_1(34, "hi");
}
```

## LEN (LENGTH)

`CallRemoteFunction`, `SetTimerEx`, and other natives that take variable
parameters with a specifier string require that arrays passed to them are
followed by the array length (so that memory can be allocated correctly).  This
isn't required for strings as their length can be determined by the NULL byte.
This one fact is the sole reason for the radically different processing of
strings and arrays (i.e. `a` vs. `s`, and `string:`).

This requirement can be enforced at compile-time by appending `LEN:` to the end
of the parser definition.  Most other definitions in `FUNC_PARSER` can come in
any order - the library will determine the best order for them.

**THE `LEN:` SPECIFICATION MUST COME AT THE END.**

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:NUM_CST_DEF:LEN:)(%0(%1)) [%2]()(%1)##$
```

Beyond that, everything else is the same.  Arrays and integers are called back
as normal individually, but now if an array is not followed by either a number
(`a`) or a reference (`&a`) the compiler will show `error 017: undefined symbol
"LENGTH_REQUIRED"` (this was the closest to a useful error that I could get).

This is fine:

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:NUM_CST_DEF:LEN:)(%0(%1)) [%2]()(%1)##$

timer length_required[100](arr[], len)
{
}
```

This is fine:

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:NUM_CST_DEF:)(%0(%1)) [%2]()(%1)##$

timer no_length_required[200](arr[])
{
}
```

This is not:

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:NUM_CST_DEF:LEN:)(%0(%1)) [%2]()(%1)##$

timer length_required[100](arr[])
{
}
```

This is fine:

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:NUM_CST_DEF:LEN:)(%0(%1)) [%2]()(%1)##$

timer length_required[200](arr[], len = sizeof (arr))
{
}
```

This is not:

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:LEN:NUM_CST_DEF:)(%0(%1)) [%2]()(%1)##$

timer length_required[100](arr[], len = sizeof (arr))
{
}
```

This is not:

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,ARR_CST:STR_CST_DEF:NUM_CST:LEN:)(%0(%1)) [%2]()(%1)##$

timer length_required[200](arr[], len = sizeof (arr))
{
}
```

The last one is not allowed because only `NUM_CST` was given, not `NUM_CST_DEF`,
so default values on numbers are not allowed.  The penultimate one has `LEN:` in
the wrong place - this might work slightly, but not fully.

## QAL (QUALIFICATION)

Function qualifiers are the bits that come before the name, i.e. `stock`,
`static`, `const`, `new`, `operator`, `forward`, `public`, and `native`.  If you
are using YSI, this extends to include `global`, `foreign`, `timer`, `inline`,
`ptask`, `task`, `remoterunc`, `hook`, `group_hook`, `master_hook`,
`master_task`, `master_ptask`, `master_func`, `@foreign`, `@global`,
`timerfunc`, `loadtext`, `pvar`, and `svar`.  Several are only valid on
variables, `const` and `inline` are only used on inline functions, and more of
these are uncommon synonyms or alternate (backup) spellings.

The point is, keywords can be used before functions, and can be detected when
using the `QAL:` modifier.  The keywords are only detected if they come after
the main entry macro:

```pawn
#define timer%0[%2](%1) FUNC_PARSER(TIMER,QAL:ARR_CST:STR_CST_DEF:NUM_CST_DEF:LEN:)(%0(%1)) [%2]()(%1)##$

#define TIMER_stock(%9)%8$ %8$ // Saw "stock"
```

Will be detected:

```pawn
timer stock my_timer[100]()
{
}
```

Will not be detected:

```pawn
stock timer my_timer[200]()
{
}
```

The `PREFIX_keyword` macro is called after all the parameters have been
processed, but before the ending macros are called (`_END`, `_NUL`, etc.)

If you don't want to support a qualifier, just don't define it.  If there is no
`PREFIX_public` and they try use `public` then they will get a very nice error
of `error 017: undefined symbol "PREFIX_public"`.

Currently the keyword callbacks do not have any parameters, but use
`PREFIX_forward(%9)` anyway - that will work even with zero parameters, and will
ensure future proofing in case more are added.

## SPC (SPECIAL)

*Special* arrays are those declared through macros with `<>` instead of `[]`,
e.g. iterators:

```pawn
new Iterator:Vehicles<MAX_VEHICLES>;
```

The `SPC` (`SPECIAL`) and `SPC_CST` (`SPECIAL_CONST`) specifiers add detection
for these special arrays.  There is no `_TAG` variant since they always have a
tag by definition.  Their callback would be:

```pawn
#define PREFIX_SPC(%0,%1,%2,%3)%8$
```

With:

Substitution parameter | Use
--- | ---
`%0`  | `const ` (if it exists).
`%1`  | The special type - `Iterator:` above (with the colon, as ever).
`%2`  | The variable name - `Vehicles` above.
`%3`  | Size (anything between the `<>`s) - `MAX_VEHICLES` above.

I did test `Iterator:` with this, but that one generates so much other complex
code that it ran out of memory - the parser works, but just be careful with what
the special array macro generates later.  Also, `<>`s are not real brackets, so
commas between them will totally break everything, for example this:

```pawn
MY_PARSER:func(Iterator:Vehicles<MAX_PLAYERS, MAX_VEHICLES>)
```

will be interpreted as two invalid parameters - `Iterator:Vehicles<MAX_PLAYERS`
and `MAX_VEHICLES>` instead of what it should be.

## GRP (TAGGROUP)

Tag groups are multiple tags assigned to the same variable, most frequently seen
as:

```pawn
Func1({_, Float}:...)
{
}
```

However, any variable can have any tag groups on them:

```pawn
Func2({_, Float}:a, &{bool, File, DB}:b, {Text, PlayerText}:tds[])
{
}
```

Calling `tagof` on these variables at the function site will return the first
tag from the list (at the call site, it will always return the correct declared
tag).  This makes the first tag the most important tag:

```pawn
Func3({Text, PlayerText}:td, tag = tagof (td))
{
	return (tag == tagof (Text:));
}

main()
{
	new
		Text:a,
		PlayerText:b;
	Func3(a);            // true
	Func3(a, tagof (a)); // true
	Func3(b);            // true
	Func3(b, tagof (b)); // false
}
```

Tag groups cannot be used as tag overrides and will give an error:

```pawn
main()
{
	new
		Float:a;
	Func3({Text, PlayerText}:a); // Error
	Func3(Text:a);               // OK
}
```

For this reason it is important to be able to detect tag groups, and provide a
method for getting the correct values to tag override with.  `_GRP` or
`_TAGGROUP`, when used in place of `_TAG`, provides this:


With `_TAG`:

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUL_TAG:)(%0(%1))
#define EXAMPLE_NUL(%0,%1,%2)%8$ "The tag is " #%1

EXAMPLE:Func(a:v);         // The tag is a:
EXAMPLE:Func({a, b, c}:v); // The tag is {a, b, c}:
```

With `_GRP`, both the whole tag group and the first tag (for overriding) are
provided.  To keep backwards-compatability with the existing macro parameters,
they are BOTH given in `%1` when `_GRP` is used instead - even if there is no
tag group:

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUL_GRP:)(%0(%1))
#define EXAMPLE_NUL(%0,(%1,%3),%2)%8$ "The main is " #%1 ", the group is: " %3

EXAMPLE:Func(a:v);         // The main is a:, the group is a:
EXAMPLE:Func({a, b, c}:v); // The main is a:, the group is {a, b, c}:
```

Note that this new sub-parameter code is on a per-type basis:

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUL_GRP:REF_TAG:ARR_GRP:EXT_TAG:)(%0(%1))
#define EXAMPLE_NUL(%0,(%1,%3),%2) // Correct.
#define EXAMPLE_REF(%0,%1,%2)      // Correct.
#define EXAMPLE_ARR(%0,%1,%2)      // Acceptable (ignores the sub-parameters).
#define EXAMPLE_EXT(%0,(%1,%3),%2) // Wrong (sub-parameters not expected).
```

For easy macro parameter management, if you only need the whole tag (but why are
you not just using `_TAG`) use `(%0,(%1,%1),%2)`.  If you only want the main tag
use `(%0,(%1,%2),%2)`.  Macro parameters can appear more than once in the search
string and the old value will be replaced with the new one, so in both those
cases the value you don't need will be replaced with something else.

### Alternate Rebuild

An alternate version of the `REBUILD:` example using `_GRP` instead of `_TAG`
and with many examples you can inspect using `-l` to compile:

```pawn
#define REBUILD:%0(%1) FUNC_PARSER(REBUILD,ARR_MUL_GRP_CST:NUM_GRP_CST_DEF:REF_GRP_DEF:EXT_GRP:STR_CST_DEF:SPC_CST:)(%0(%1))%0($)

#define REBUILD_NUM(%0,(%1,%1),%2)%8$%7(%9$)                         %8$%7(%9, %0 %1%2                $)
#define REBUILD_NUM_DEF(%0,(%1,%1),%2,%4)%8$%7(%9$)                  %8$%7(%9, %0 %1%2     = %4       $)
#define REBUILD_REF(,(%1,%1),%2)%8$%7(%9$)                           %8$%7(%9,  & %1%2                $)
#define REBUILD_REF_DEF(,(%1,%1),%2,%4)%8$%7(%9$)                    %8$%7(%9,  & %1%2     = %4       $)
#define REBUILD_EXT(,(%1,%1),)%8$%7(%9$)                             %8$%7(%9,    %1...               $)
#define REBUILD_STR(%0,,%2,%3)%8$%7(%9$)                        %8$%7(%9, %0   %2[%3]            $)
#define REBUILD_STR_DEF(%0,,%2,%3,%4)%8$%7(%9$)                 %8$%7(%9, %0   %2[%3] = %4       $)
#define REBUILD_SPC(%0,%1,%2,%3)%8$%7(%9$)                      %8$%7(%9, %0 %1%2<%3>            $)
#define REBUILD_ARR(%0,(%1,%1),%2,%3)%8$%7(%9$)                      %8$%7(%9, %0 %1%2[%3]            $)
#define REBUILD_ARR_ARR(%0,(%1,%1),%2,%3,%4)%8$%7(%9$)               %8$%7(%9, %0 %1%2[%3][%4]        $)
#define REBUILD_ARR_ARR_ARR(%0,(%1,%1),%2,%3,%4,%5)%8$%7(%9$)        %8$%7(%9, %0 %1%2[%3][%4][%5]    $)
#define REBUILD_ARR_ARR_ARR_ARR(%0,(%1,%1),%2,%3,%4,%5,%6)%8$%7(%9$) %8$%7(%9, %0 %1%2[%3][%4][%5][%6]$)

#define REBUILD_END(%9)%8$%7(,%9$) %8$%7(%9)
#define REBUILD_NUL(%9)%8$%7($)    %8$%7()

#define REBUILD_static(%9)%8$ %8$B

#define iter_%0\32; iter_
#define Example:%0<> iter_%0[10]

REBUILD:stock static rebuilt_func_1(a, c, b[]);
REBUILD:stock static rebuilt_func_2(a, &c, string:b[] = "");
REBUILD:stock static rebuilt_func_3(Text:a, c, b[]);
REBUILD:stock static rebuilt_func_4(Text:a, &c, const b[]);
REBUILD:stock rebuilt_func_5(Text:a, c, b[]);
REBUILD:stock rebuilt_func_6(a, &c, const b[6][7]);
REBUILD:stock rebuilt_func_7(a, c, b[]);
REBUILD:stock rebuilt_func_8(const a, b[], &Float:c = 66.4);
REBUILD:stock rebuilt_func_9(const Float:a, c, b[]);
REBUILD:public rebuilt_func_a(const Float:a, c, b[]);
REBUILD:public rebuilt_func_0(const Float:a, &c, b[]);
REBUILD:forward rebuilt_func_b(const a, b[], &c = 6);
REBUILD:rebuilt_func_c(const a, string:f[] = "hi", ...);
REBUILD:rebuilt_func_d(const a, c, {Float, _, Text}:...);
REBUILD:public rebuilt_func(a, c, b[]);
REBUILD:rebuilt_func_e(const a, c, Example:Player<>);
REBUILD:rebuilt_func_e(const a, c, Example:Player<>);
REBUILD:rebuilt_func_f(const Example:A<>, Example:Vehicle<>);
REBUILD:rebuilt_func_g(&{Tag1, Tag2}:a, {Float, Fake}:c);
```

## API

The `FUNC_PARSER` macro is the main API entry-point, and generates the macros to
do the parsing.  The reason it is done this way is that things like
`TAG_NUM_DEFAULT:` are pretty descriptive tags - that (relatively) clearly
indicates that you want the parser to detect numbers (regular variables, but
`VAR` could be confused for both *variable* and *vararg*, hence it is avoided).
However, that tag is very long, this tag-macro based parsing method leaves a lot
of unmatched macros behind, and it is recursive.  Long macros with short line-
length limits do not play well together.

The include is quite long, but it doesn't need to be.  The vast majority of the
code is to convert something like this:

```pawn
FUNC_PARSER(REBUILD,ARRAY_TAG_CONST_MULTI:NUMBER_CONST_TAG_DEFAULT:TAG_REFERENCE_DEFAULT:TAG_VARARG:DEFAULT_STRING_CONST)(func(params))
```

In to this:

```pawn
PARSER@FUNC:z@:l@:w@:x@<c@:b@:>a@:x@<f@:c@:t@:>v@:x@<t@:>r@:x@<t@:d@:>o@:x@<c@:t@:d@:>(REBUILD)func(||||||params,)$
```

I.e. just provides a nice API for using the parser.  The actual complex part is
done by these few macros.  Feel free to take just these if you want and derive
your own input to the magical `PARSER@FUNC:` macro:

```pawn
#define void:
#define string:
#define u@$ 0]);
#define PARSER@FUNC:%0$ u@(u[_:%0 u@$
#define c@:%8(%0,%1,%9const%2) %8(%0const ,%1,%9%2)
#define t@:%8(%0,%1,%9:%2) %8(%0,%1%9:,%2)
#define d@:%8(%0,%1,%2=%9) %8_DEF(%0,%1,%2,%9)
#define b@:%8(%0,%1,%2=%9,%4) %8_DEF(%0,%1,%2,%4,%9)
#define f@:%8(%0,%1,%2[%9]%6,%3) f@:%8_ARR(%0,%1,%2%6,%3,%9)
#define x@<%9>
#define w@:x@<%8>%9.%0(%5)(%4|||%6string:%1[%2]%9|||%7)%3$ %8%5_STR(,,%6%1%9,%2)%0(%5)(||||||%7)%3$
#define a@:x@<%8>%9.%0(%5)(%4|||%1[%2]%9|||%7)%3$ %8%5_ARR(,,%1%9,%2)%0(%5)(||||||%7)%3$
#define r@:x@<%8>%9.%0(%5)(%4|||%1&%2|||%7)%3$ %8%5_REF(,,%1%2)%0(%5)(||||||%7)%3$
#define v@:x@<%8>%9.%0(%5)(%4|||%1...%2|||%7)%3$ %8%5_EXT(,,%1%2)%0(%5)(||||||%7)%3$
#define o@:x@<%8>%9.%0(%5)(%4|||%1|||%7)%3$ %8%5_NUM(,,%1)%0(%5)(||||||%7)%3$
#define z@:%0(%5)(||||||,%7)%3$ %5_NUL()%7%3$
#define n@:%0(%5)(%4|||%6|||%7)%3$ %5_END()%7%3$
#define m@:n@:%0(%5)(%4|||%6|||%7,%8)%3$ %0.m@:n@:%0(%5)(%4%6|||%7|||%8)%3$
```

But don't be upset if the underlying macros change (since they have even since I
copied them here).

## Example 8 - y_inline

This entire library is designed for parsing function declarations.  These appear
at the global scope - with one exception: y_inline (or any other inline library
that someone cares to write).  The `PARSER@FUNC:` macro on which the tag-based
parsing works only works at the top level (I tried very hard to make it work
everywhere, but it just didn't QUITE happen).  Note that this macro was
previously written as `__:` (and that macro still has value), but it was renamed
in this library for flexibility, because it is internal, and to minimise global
namespace pollution.

y_inline converts this:

```pawn
main()
{
	inline InlineFunc(a, b[32], string:c[])
	{
		// Code.
	}
}
```

In to:

```pawn
main()
{
	static  InlineFunc[_:I@E:32]=# InlineFunc":....";if(I@E(_:@Ia:@Ib:@Ic:@Ib:@Ic:@Id: InlineFunc))for(new a, b[_:@Iy:32], c[_:(YSI_MAX_STRING)];I@F();)while(I@L(I@K(1),0,@Ix,sizeof  c))
	{
		// Code.
	}
}
```

Representing:

```pawn
main()
{
	static
		InlineFunc[32] = "InlineFunc:....";
	if (Inline_Entry(InlineFunc))
	{
		for (new a, b[32], c[YSI_MAX_STRING]; Inline_Allocator(); )
		{
			while (Inline_Main(HAS(const), 0, cellmax, sizeof (c)))
			{
				// Code.
			}
		}
	}
}
```

This is rewritten at runtime to something equivalent to:

```pawn
main()
{
	goto after;
	static InlineFunc = Inline_Start("InlineFunc", "ia[10]s", &start);
	new a, b[10], string:c[];
	{
start:
	}
after:
}
```

The run-time implementation of y_inline is not the focus of this example though,
only the macros.

Because inline functions are at a function local level, not a global level, we
need two custom macros to start and end the parsing.  These closely mimick the
ones in the inclue (`PARSER@FUNC:` and `u@$`), but wrap all the tag macros up in
a local array size instead of a function parameter array size:

```pawn
#define PARSER@INLINE:%0(%5)%6(%7)$ static %6[_:%0(%5)%6(%7) I@O$
#define I@O$ 32]=
```

The library normally calls `PARSE@` once it has finished parsing the
`FUNC_PARSER` parameters, to start the processing.  Instead we call
`MAKE_PARSER` directly, with an extra `:INLINE` parameter.

```pawn
#define inline%0(%1) MAKE_PARSER(INLINE,ARR:REF:STR:NUM:QAL::INLINE)(%0(%1))()1()
```

The `I@O$` macro mirrors `u@$` - both of them are there to remove the final `$`
on which most of the processing is based (this is the symbol used to skip over
internal state by `%8$`, but needs removing eventually.  They both also close
the array size in which the tag macros are hidden from the syntax checker.

From there the remaining macros are straight forward.  First collate the
parameters in to two lists - one for names and one for numeric representations
of size and type (`0` = variable, `-1` = reference, `cellmax` = string, other =
array (given as the size)).

```pawn
#define INLINE_STR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[YSI_MAX_INLINE_STRING])%1(%3,cellmax)
#define INLINE_ARR(%9,%9,%2,%9)%8$(%0)%1(%3) %8$(%0,%2[%9])%1(%3,%9)
#define INLINE_NUM(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(%3,0)
#define INLINE_REF(%9,%9,%2)%8$(%0)%1(%3) %8$(%0,%2)%1(%3,-1)

#define INLINE_END(%9)%8$(,%0)%1(%3) %8$#%9":....";if(I@E(%9))for(new %0;I@F();)while(I@L(I@K(%1)%3))

#define INLINE_NUL(%9)%8$()%1() %8$#%9":....";if(I@E(%9))for(;I@F();)while(I@L(I@K(%1)))

#define INLINE_const(%9)%8$(%0)%1(%2) %8$(%0)(%2)
```

Note that in writing this code, I found a bug in the old version, which was very
cleanly fixed in this code.  The example above should read
`while (Inline_Main(HAS(const), 0, sizeof (b), cellmax))`, but the code
presented there is as it is generated by the latest internal y_inline code.

## PARSER_ISOLATE

This macro allows direct access to one internal part of the parser - the ability
to detect a space immediately after a symbol.  For example:

```pawn
#define DETECT_CONST(const%0\32;%1)

DETECT_CONST(const a)
```

That will match, because `const` is followed by a space.  However, this will
ALSO match, because `const` is still (eventually) followed by a space:

```pawn
DETECT_CONST(constB )
```

In this case `%0` will be `B`, whereas in the first example it was `` (nothing).
The obvious solution is to try and specify that the space should be immediately
after the symbol:

```pawn
#define DETECT_CONST(const\32;%1)
```

However, due to a quirk (bug/feature/flaw?) in the pre-processor, that will not
work.  Any character matched via an escape code MUST be preceeded by a match
parameter.  Instead, the trick used in this library is to test the contents of
the parameter separately:

```pawn
#define IS_NOTHING()

#define DETECT_CONST(const%0\32;%1) IS_NOTHING(%0)
```

`IS_NOTHING` will not match if `%0` contains anything.  Armed with that
information, and a few more tag macros to handle the `else` case, we can write
`PARSER_ISOLATE`:

```pawn
#define PARSER_ISOLATE(%0,%1){%2,%3} _:T@:O@$%1$%0${%2,%3}
#define T@:O@$$%0$(){%2,%3} %2(%0)
#define O@$%1$%0$(%9){%2,%3} %3(%9%0%1)
```

`T@` detects the "nothing" case by matching `$$`, `O@` detects the "something"
case by matching `$%1$`.  `%0` would in this example contain `const`, `%2` is
the macro to call when `const` is on its own, `%3` the macro to call when it
isn't.  Both are passed everything passed in (so `const` alone or the fully
reassembled symbol).  We also want to detect that nothing OR spaces comes before
the `const` (otherwise we still match symbols that end with `const`), so this is
given in `%9`; passed between brackets since they ignore spaces.

```pawn
// `%1` is everything after the space.
#define HAS_CONST(%9)(%1) %1 is `const`

// `%9` is everything before the space.
#define NO_CONST(%9)(%1) %9 contains `const`

// Think of the brackets and braces here as somewhat like `if () {} else {}`.
#define DETECT_CONST(%9const%0\32;%1) PARSER_ISOLATE(%9,const,%0){HAS_CONST,NO_CONST}(%1)
```

Note that this code is designed to detect spaces and other awkwardness in
end-user code.  DO NOT use any extra spaces in the macros themselves or you'll
probably break the result.

Example use:

```pawn
DETECT_CONST(const a) // a has `const`
DETECT_CONST(constB ) // constB contains `const`
DETECT_CONST(a_const_var ) // a_const_var contains `const`
DETECT_CONST(constC) // Won't match.
DETECT_CONST(      const d) // d is `const`
```

The last case is left to you to deal with.  The lack of space detection is
actually in the example `DETECT_CONST` macro, not `PARSER_ISOLATE`, which is
written assuming you've already determined what needs testing.

## Complete Parameter Reference

All the specifiers, with all their variations, callbacks, and examples; in one
place.  Note that a lot of extra spacing has been added for clarity and ease of
direct comparison.

### NUMBER

AKA **NUM**

Detects standard variables.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM(,,                   name    )
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM(,,               Tag:name    )
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM(,,                   name = 7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM(,,               Tag:name = 7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM(,,const              name    )
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM(,,const          Tag:name    )
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM(,,const              name = 7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM(,,const          Tag:name = 7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM(,,      {Tag1, Tag2}:name    )
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(,,      {Tag1, Tag2}:name = 7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM(,,const {Tag1, Tag2}:name    )
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(,,const {Tag1, Tag2}:name = 7)
```

### NUMBER_CONST

AKA **NUM_CST**

Detects standard variables with optional `const`s.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_CST:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM(      ,,             name    )
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM(      ,,         Tag:name    )
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM(      ,,             name = 7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM(      ,,         Tag:name = 7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM(const ,,             name    )
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM(const ,,         Tag:name    )
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM(const ,,             name = 7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM(const ,,         Tag:name = 7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM(      ,,{Tag1, Tag2}:name    )
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(      ,,{Tag1, Tag2}:name = 7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM(const ,,{Tag1, Tag2}:name    )
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(const ,,{Tag1, Tag2}:name = 7)
```

### NUMBER_DEFAULT

AKA **NUM_DEF**

Detects standard variables with optional default values.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_DEF:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2,%4)%8$
#define EXAMPLE_NUM_DEF(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM    (,,                   name)
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM    (,,               Tag:name)
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM_DEF(,,                   name,7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM_DEF(,,               Tag:name,7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM    (,,const              name)
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM    (,,const          Tag:name)
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM_DEF(,,const              name,7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM_DEF(,,const          Tag:name,7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (,,      {Tag1, Tag2}:name)
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(,,      {Tag1, Tag2}:name,7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (,,const {Tag1, Tag2}:name)
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(,,const {Tag1, Tag2}:name,7)
```

### NUMBER_CONST_DEFAULT

AKA **NUM_CST_DEF**

Detects standard variables with optional `const`s and default values.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_CST_DEF:)(%0(%1))

#define EXAMPLE_NUM(%0,(%1,%3),%2)%8$
#define EXAMPLE_NUM_DEF(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM    (      ,,             name)
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM    (      ,,         Tag:name)
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM_DEF(      ,,             name,7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM_DEF(      ,,         Tag:name,7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM    (const ,,             name)
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM    (const ,,         Tag:name)
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM_DEF(const ,,             name,7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM_DEF(const ,,         Tag:name,7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (      ,,{Tag1, Tag2}:name)
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(      ,,{Tag1, Tag2}:name,7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (const ,,{Tag1, Tag2}:name)
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(const ,,{Tag1, Tag2}:name,7)
```

### NUMBER_TAG

AKA **NUM_TAG**

Detects standard variables with optional tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_TAG:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM(,                   ,name    )
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM(,               Tag:,name    )
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM(,                   ,name = 7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM(,               Tag:,name = 7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM(,const              ,name    )
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM(,const          Tag:,name    )
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM(,const              ,name = 7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM(,const          Tag:,name = 7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM(,      {Tag1, Tag2}:,name    )
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(,      {Tag1, Tag2}:,name = 7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM(,const {Tag1, Tag2}:,name    )
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(,const {Tag1, Tag2}:,name = 7)
```

### NUMBER_CONST_TAG

AKA **NUM_CST_TAG**

Detects standard variables with optional `const`s and tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_CST_TAG:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM(      ,             ,name    )
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM(      ,         Tag:,name    )
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM(      ,             ,name = 7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM(      ,         Tag:,name = 7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM(const ,             ,name    )
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM(const ,         Tag:,name    )
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM(const ,             ,name = 7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM(const ,         Tag:,name = 7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM(      ,{Tag1, Tag2}:,name    )
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(      ,{Tag1, Tag2}:,name = 7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM(const ,{Tag1, Tag2}:,name    )
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(const ,{Tag1, Tag2}:,name = 7)
```

### NUMBER_DEFAULT_TAG

AKA **NUM_DEF_TAG**

Detects standard variables with optional default values and tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_DEF_TAG:)(%0(%1))

#define EXAMPLE_NUM(%0,(%1,%3),%2)%8$
#define EXAMPLE_NUM_DEF(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM    (,                   ,name)
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM    (,               Tag:,name)
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM_DEF(,                   ,name,7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM_DEF(,               Tag:,name,7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM    (,const              ,name)
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM    (,const          Tag:,name)
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM_DEF(,const              ,name,7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM_DEF(,const          Tag:,name,7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (,      {Tag1, Tag2}:,name)
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(,      {Tag1, Tag2}:,name,7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (,const {Tag1, Tag2}:,name)
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(,const {Tag1, Tag2}:,name,7)
```

### NUMBER_CONST_DEFAULT_TAG

AKA **NUM_CST_DEF_TAG**

Detects standard variables with optional `const`s, default values, and tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_CST_DEF_TAG:)(%0(%1))

#define EXAMPLE_NUM_DEF(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM    (      ,             ,name)
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM    (      ,         Tag:,name)
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM_DEF(      ,             ,name,7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM_DEF(      ,         Tag:,name,7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM    (const ,             ,name)
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM    (const ,         Tag:,name)
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM_DEF(const ,             ,name,7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM_DEF(const ,         Tag:,name,7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (      ,{Tag1, Tag2}:,name)
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(      ,{Tag1, Tag2}:,name,7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (const ,{Tag1, Tag2}:,name)
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(const ,{Tag1, Tag2}:,name,7)
```

### NUMBER_TAGGROUP

AKA **NUM_GRP**

Detects standard variables with optional multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_GRP:)(%0(%1))

#define EXAMPLE_NUM(%0,(%1,%3),%2)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM(,(     ,             ),name    )
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM(,( Tag:,         Tag:),name    )
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM(,(     ,             ),name = 7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM(,( Tag:,         Tag:),name = 7)
EXAMPLE:Func(const              name    ); // ERROR
EXAMPLE:Func(const          Tag:name    ); // ERROR
EXAMPLE:Func(const              name = 7); // ERROR
EXAMPLE:Func(const          Tag:name = 7); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM(,(Tag1:,{Tag1, Tag2}:),name    )
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(,(Tag1:,{Tag1, Tag2}:),name = 7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // ERROR
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // ERROR
```

### NUMBER_CONST_TAGGROUP

AKA **NUM_CST_GRP**

Detects standard variables with optional `const`s and multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_CST_GRP:)(%0(%1))

#define EXAMPLE_NUM(%0,(%1,%3),%2)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM(      ,(     ,              ),name    )
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM(      ,( Tag:,          Tag:),name    )
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM(      ,(     ,              ),name = 7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM(      ,( Tag:,          Tag:),name = 7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM(const ,(     ,              ),name    )
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM(const ,( Tag:,          Tag:),name    )
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM(const ,(     ,              ),name = 7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM(const ,( Tag:,          Tag:),name = 7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM(      ,(Tag1:, {Tag1, Tag2}:),name    )
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(      ,(Tag1:, {Tag1, Tag2}:),name = 7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM(const ,(Tag1:, {Tag1, Tag2}:),name    )
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM(const ,(Tag1:, {Tag1, Tag2}:),name = 7)
```

### NUMBER_DEFAULT_TAGGROUP

AKA **NUM_DEF_GRP**

Detects standard variables with optional default values and multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_DEF_GRP:)(%0(%1))

#define EXAMPLE_NUM(%0,(%1,%3),%2)%8$
#define EXAMPLE_NUM_DEF(%0,(%1,%3),%2,%4)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM    (,(     ,              ),name)
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM    (,( Tag:,          Tag:),name)
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM_DEF(,(     ,              ),name,7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM_DEF(,( Tag:,          Tag:),name,7)
EXAMPLE:Func(const              name    ); // ERROR
EXAMPLE:Func(const          Tag:name    ); // ERROR
EXAMPLE:Func(const              name = 7); // ERROR
EXAMPLE:Func(const          Tag:name = 7); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (,(Tag1:, {Tag1, Tag2}:),name)
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(,(Tag1:, {Tag1, Tag2}:),name,7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // ERROR
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // ERROR
```

### NUMBER_CONST_DEFAULT_TAGGROUP

AKA **NUM_CST_DEF_GRP**

Detects standard variables with optional `const`s, default values, and multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM_CST_DEF_GRP:)(%0(%1))

#define EXAMPLE_NUM(%0,(%1,%3),%2)%8$
#define EXAMPLE_NUM_DEF(%0,(%1,%3),%2,%4)%8$

EXAMPLE:Func(                   name    ); // EXAMPLE_NUM    (      ,(     ,              ),name)
EXAMPLE:Func(               Tag:name    ); // EXAMPLE_NUM    (      ,( Tag:,          Tag:),name)
EXAMPLE:Func(                   name = 7); // EXAMPLE_NUM_DEF(      ,(     ,              ),name,7)
EXAMPLE:Func(               Tag:name = 7); // EXAMPLE_NUM_DEF(      ,( Tag:,          Tag:),name,7)
EXAMPLE:Func(const              name    ); // EXAMPLE_NUM    (const ,(     ,              ),name)
EXAMPLE:Func(const          Tag:name    ); // EXAMPLE_NUM    (const ,( Tag:,          Tag:),name)
EXAMPLE:Func(const              name = 7); // EXAMPLE_NUM_DEF(const ,(     ,              ),name,7)
EXAMPLE:Func(const          Tag:name = 7); // EXAMPLE_NUM_DEF(const ,( Tag:,          Tag:),name,7)
EXAMPLE:Func(      {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (      ,(Tag1:, {Tag1, Tag2}:),name)
EXAMPLE:Func(      {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(      ,(Tag1:, {Tag1, Tag2}:),name,7)
EXAMPLE:Func(const {Tag1, Tag2}:name    ); // EXAMPLE_NUM    (const ,(Tag1:, {Tag1, Tag2}:),name)
EXAMPLE:Func(const {Tag1, Tag2}:name = 7); // EXAMPLE_NUM_DEF(const ,(Tag1:, {Tag1, Tag2}:),name,7)
```

### REFERENCE

AKA **REF**

Detects references.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,REF:)(%0(%1))

#define EXAMPLE_REF(%0,%1,%2)%8$

EXAMPLE:Func(&             name    ); // EXAMPLE_REF(,,             name    )
EXAMPLE:Func(&         Tag:name    ); // EXAMPLE_REF(,,         Tag:name    )
EXAMPLE:Func(&             name = 7); // EXAMPLE_REF(,,             name = 7)
EXAMPLE:Func(&         Tag:name = 7); // EXAMPLE_REF(,,         Tag:name = 7)
EXAMPLE:Func(&{Tag1, Tag2}:name    ); // EXAMPLE_REF(,,{Tag1, Tag2}:name    )
EXAMPLE:Func(&{Tag1, Tag2}:name = 7); // EXAMPLE_REF(,,{Tag1, Tag2}:name = 7)
```

### REFERENCE_DEFAULT

AKA **REF_DEF**

Detects references with optional default values.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,REF_DEF:)(%0(%1))

#define EXAMPLE_REF(%0,%1,%2,%4)%8$
#define EXAMPLE_REF_DEF(%0,%1,%2,%4)%8$

EXAMPLE:Func(&             name    ); // EXAMPLE_REF    (,,             name)
EXAMPLE:Func(&         Tag:name    ); // EXAMPLE_REF    (,,         Tag:name)
EXAMPLE:Func(&             name = 7); // EXAMPLE_REF_DEF(,,             name,7)
EXAMPLE:Func(&         Tag:name = 7); // EXAMPLE_REF_DEF(,,         Tag:name,7)
EXAMPLE:Func(&{Tag1, Tag2}:name    ); // EXAMPLE_REF    (,,{Tag1, Tag2}:name)
EXAMPLE:Func(&{Tag1, Tag2}:name = 7); // EXAMPLE_REF_DEF(,,{Tag1, Tag2}:name,7)
```

### REFERENCE_TAG

AKA **REF_TAG**

Detects references with optional tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,REF_TAG:)(%0(%1))

#define EXAMPLE_REF(%0,%1,%2)%8$

EXAMPLE:Func(&             name    ); // EXAMPLE_REF(,             ,name    )
EXAMPLE:Func(&         Tag:name    ); // EXAMPLE_REF(,         Tag:,name    )
EXAMPLE:Func(&             name = 7); // EXAMPLE_REF(,             ,name = 7)
EXAMPLE:Func(&         Tag:name = 7); // EXAMPLE_REF(,         Tag:,name = 7)
EXAMPLE:Func(&{Tag1, Tag2}:name    ); // EXAMPLE_REF(,{Tag1, Tag2}:,name    )
EXAMPLE:Func(&{Tag1, Tag2}:name = 7); // EXAMPLE_REF(,{Tag1, Tag2}:,name = 7)
```

### REFERENCE_DEFAULT_TAG

AKA **REF_DEF_TAG**

Detects references with optional default values and tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,REF_DEF_TAG:)(%0(%1))

#define EXAMPLE_REF(%0,(%1,%3),%2)%8$
#define EXAMPLE_REF_DEF(%0,%1,%2,%4)%8$

EXAMPLE:Func(&             name    ); // EXAMPLE_REF    (,             ,name)
EXAMPLE:Func(&         Tag:name    ); // EXAMPLE_REF    (,         Tag:,name)
EXAMPLE:Func(&             name = 7); // EXAMPLE_REF_DEF(,             ,name,7)
EXAMPLE:Func(&         Tag:name = 7); // EXAMPLE_REF_DEF(,         Tag:,name,7)
EXAMPLE:Func(&{Tag1, Tag2}:name    ); // EXAMPLE_REF    (,{Tag1, Tag2}:,name)
EXAMPLE:Func(&{Tag1, Tag2}:name = 7); // EXAMPLE_REF_DEF(,{Tag1, Tag2}:,name,7)
```

### REFERENCE_TAGGROUP

AKA **REF_GRP**

Detects references with optional multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,REF_GRP:)(%0(%1))

#define EXAMPLE_REF(%0,(%1,%3),%2)%8$

EXAMPLE:Func(&             name    ); // EXAMPLE_REF(,(     ,             ),name    )
EXAMPLE:Func(&         Tag:name    ); // EXAMPLE_REF(,( Tag:,         Tag:),name    )
EXAMPLE:Func(&             name = 7); // EXAMPLE_REF(,(     ,             ),name = 7)
EXAMPLE:Func(&         Tag:name = 7); // EXAMPLE_REF(,( Tag:,         Tag:),name = 7)
EXAMPLE:Func(&{Tag1, Tag2}:name    ); // EXAMPLE_REF(,(Tag1:,{Tag1, Tag2}:),name    )
EXAMPLE:Func(&{Tag1, Tag2}:name = 7); // EXAMPLE_REF(,(Tag1:,{Tag1, Tag2}:),name = 7)
```

### REFERENCE_DEFAULT_TAGGROUP

AKA **REF_DEF_GRP**

Detects references with optional default values and multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,REF_DEF_GRP:)(%0(%1))

#define EXAMPLE_REF(%0,(%1,%3),%2)%8$
#define EXAMPLE_REF_DEF(%0,(%1,%3),%2,%4)%8$

EXAMPLE:Func(&             name    ); // EXAMPLE_REF    (,(     ,              ),name)
EXAMPLE:Func(&         Tag:name    ); // EXAMPLE_REF    (,( Tag:,          Tag:),name)
EXAMPLE:Func(&             name = 7); // EXAMPLE_REF_DEF(,(     ,              ),name,7)
EXAMPLE:Func(&         Tag:name = 7); // EXAMPLE_REF_DEF(,( Tag:,          Tag:),name,7)
EXAMPLE:Func(&{Tag1, Tag2}:name    ); // EXAMPLE_REF    (,(Tag1:, {Tag1, Tag2}:),name)
EXAMPLE:Func(&{Tag1, Tag2}:name = 7); // EXAMPLE_REF_DEF(,(Tag1:, {Tag1, Tag2}:),name,7)
```

### STRING

AKA **STR**

Detects strings (`string:` only).

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,STR:)(%0(%1))

#define EXAMPLE_STR(%0,%1,%2,%3)%8$

EXAMPLE:Func(      string:name[  ]       ); // EXAMPLE_STR(,,      name       ,  )
EXAMPLE:Func(      string:name[32]       ); // EXAMPLE_STR(,,      name       ,32)
EXAMPLE:Func(      string:name[  ] = "hi"); // EXAMPLE_STR(,,      name = "hi",  )
EXAMPLE:Func(      string:name[32] = "hi"); // EXAMPLE_STR(,,      name = "hi",32)
EXAMPLE:Func(const string:name[  ]       ); // EXAMPLE_STR(,,const name       ,  )
EXAMPLE:Func(const string:name[32]       ); // EXAMPLE_STR(,,const name       ,32)
EXAMPLE:Func(const string:name[  ] = "hi"); // EXAMPLE_STR(,,const name = "hi",  )
EXAMPLE:Func(const string:name[32] = "hi"); // EXAMPLE_STR(,,const name = "hi",32)
```

### STRING_CONST

AKA **STR_CST**

Detects strings (`string:` only) with optional `const`s.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,STR_CST:)(%0(%1))

#define EXAMPLE_STR(%0,%1,%2,%3)%8$

EXAMPLE:Func(      string:name[  ]       ); // EXAMPLE_STR(      ,,name       ,  )
EXAMPLE:Func(      string:name[32]       ); // EXAMPLE_STR(      ,,name       ,32)
EXAMPLE:Func(      string:name[  ] = "hi"); // EXAMPLE_STR(      ,,name = "hi",  )
EXAMPLE:Func(      string:name[32] = "hi"); // EXAMPLE_STR(      ,,name = "hi",32)
EXAMPLE:Func(const string:name[  ]       ); // EXAMPLE_STR(const ,,name       ,  )
EXAMPLE:Func(const string:name[32]       ); // EXAMPLE_STR(const ,,name       ,32)
EXAMPLE:Func(const string:name[  ] = "hi"); // EXAMPLE_STR(const ,,name = "hi",  )
EXAMPLE:Func(const string:name[32] = "hi"); // EXAMPLE_STR(const ,,name = "hi",32)
```

### STRING_DEFAULT

AKA **STR_DEF**

Detects strings (`string:` only) with optional default values.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,STR_DEF:)(%0(%1))

#define EXAMPLE_STR(%0,%1,%2,%3)%8$
#define EXAMPLE_STR_DEF(%0,%1,%2,%3,%4)%8$

EXAMPLE:Func(      string:name[  ]       ); // EXAMPLE_STR    (,,      name,  ,    )
EXAMPLE:Func(      string:name[32]       ); // EXAMPLE_STR    (,,      name,32,    )
EXAMPLE:Func(      string:name[  ] = "hi"); // EXAMPLE_STR_DEF(,,      name,  ,"hi")
EXAMPLE:Func(      string:name[32] = "hi"); // EXAMPLE_STR_DEF(,,      name,32,"hi")
EXAMPLE:Func(const string:name[  ]       ); // EXAMPLE_STR    (,,const name,  ,    )
EXAMPLE:Func(const string:name[32]       ); // EXAMPLE_STR    (,,const name,32,    )
EXAMPLE:Func(const string:name[  ] = "hi"); // EXAMPLE_STR_DEF(,,const name,  ,"hi")
EXAMPLE:Func(const string:name[32] = "hi"); // EXAMPLE_STR_DEF(,,const name,32,"hi")
```

### STRING_CONST_DEFAULT

AKA **STR_CST_DEF**

Detects strings (`string:` only) with optional `const`s and default values.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,STR_CST_DEF:)(%0(%1))

#define EXAMPLE_STR(%0,%1,%2,%3)%8$
#define EXAMPLE_STR_DEF(%0,%1,%2,%3,%4)%8$

EXAMPLE:Func(      string:name[  ]       ); // EXAMPLE_STR    (      ,,name,  ,    )
EXAMPLE:Func(      string:name[32]       ); // EXAMPLE_STR    (      ,,name,32,    )
EXAMPLE:Func(      string:name[  ] = "hi"); // EXAMPLE_STR_DEF(      ,,name,  ,"hi")
EXAMPLE:Func(      string:name[32] = "hi"); // EXAMPLE_STR_DEF(      ,,name,32,"hi")
EXAMPLE:Func(const string:name[  ]       ); // EXAMPLE_STR    (const ,,name,  ,    )
EXAMPLE:Func(const string:name[32]       ); // EXAMPLE_STR    (const ,,name,32,    )
EXAMPLE:Func(const string:name[  ] = "hi"); // EXAMPLE_STR_DEF(const ,,name,  ,"hi")
EXAMPLE:Func(const string:name[32] = "hi"); // EXAMPLE_STR_DEF(const ,,name,32,"hi")
```

### VARARG

AKA **EXT**

Detects varargs.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,EXT:)(%0(%1))

#define EXAMPLE_EXT(%0,%1,%2)%8$

EXAMPLE:Func(             ...); // EXAMPLE_EXT(,,             )
EXAMPLE:Func(         Tag:...); // EXAMPLE_EXT(,,         Tag:)
EXAMPLE:Func({Tag1, Tag2}:...); // EXAMPLE_EXT(,,{Tag1, Tag2}:)
```

### VARARG_TAG

AKA **EXT_TAG**

Detects varargs with optional tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,EXT_TAG:)(%0(%1))

#define EXAMPLE_EXT(%0,%1,%2)%8$

EXAMPLE:Func(             ...); // EXAMPLE_EXT(,             ,)
EXAMPLE:Func(         Tag:...); // EXAMPLE_EXT(,         Tag:,)
EXAMPLE:Func({Tag1, Tag2}:...); // EXAMPLE_EXT(,{Tag1, Tag2}:,)
```

### VARARG_TAGGROUP

AKA **EXT_GRP**

Detects varargs with optional multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,EXT_GRP:)(%0(%1))

#define EXAMPLE_EXT(%0,(%1,%3),%2)%8$

EXAMPLE:Func(             ...); // EXAMPLE_EXT(,(     ,             ),)
EXAMPLE:Func(         Tag:...); // EXAMPLE_EXT(,( Tag:,         Tag:),)
EXAMPLE:Func({Tag1, Tag2}:...); // EXAMPLE_EXT(,(Tag1:,{Tag1, Tag2}:),)
```

### ARRAY

AKA **ARR**

Detects 1d arrays.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR:)(%0(%1))

#define EXAMPLE_ARR(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name[42]); // EXAMPLE_ARR(,,                   name,42)
EXAMPLE:Func(               Tag:name[42]); // EXAMPLE_ARR(,,               Tag:name,42)
EXAMPLE:Func(const              name[42]); // EXAMPLE_ARR(,,const              name,42)
EXAMPLE:Func(const          Tag:name[42]); // EXAMPLE_ARR(,,const          Tag:name,42)
EXAMPLE:Func(      {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(,,      {Tag1, Tag2}:name,42)
EXAMPLE:Func(const {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(,,const {Tag1, Tag2}:name,42)
EXAMPLE:Func(                   name[  ]); // EXAMPLE_ARR(,,                   name,  )
EXAMPLE:Func(               Tag:name[  ]); // EXAMPLE_ARR(,,               Tag:name,  )
EXAMPLE:Func(const              name[  ]); // EXAMPLE_ARR(,,const              name,  )
EXAMPLE:Func(const          Tag:name[  ]); // EXAMPLE_ARR(,,const          Tag:name,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(,,      {Tag1, Tag2}:name,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(,,const {Tag1, Tag2}:name,  )
```

### ARRAY_CONST

AKA **ARR_CST**

Detects 1d arrays with optional `const`s.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_CST:)(%0(%1))

#define EXAMPLE_ARR(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name[42]); // EXAMPLE_ARR(      ,,             name,42)
EXAMPLE:Func(               Tag:name[42]); // EXAMPLE_ARR(      ,,         Tag:name,42)
EXAMPLE:Func(const              name[42]); // EXAMPLE_ARR(const ,,             name,42)
EXAMPLE:Func(const          Tag:name[42]); // EXAMPLE_ARR(const ,,         Tag:name,42)
EXAMPLE:Func(      {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(      ,,{Tag1, Tag2}:name,42)
EXAMPLE:Func(const {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(const ,,{Tag1, Tag2}:name,42)
EXAMPLE:Func(                   name[  ]); // EXAMPLE_ARR(      ,,             name,  )
EXAMPLE:Func(               Tag:name[  ]); // EXAMPLE_ARR(      ,,         Tag:name,  )
EXAMPLE:Func(const              name[  ]); // EXAMPLE_ARR(const ,,             name,  )
EXAMPLE:Func(const          Tag:name[  ]); // EXAMPLE_ARR(const ,,         Tag:name,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(      ,,{Tag1, Tag2}:name,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(const ,,{Tag1, Tag2}:name,  )
```

### ARRAY_TAG

AKA **ARR_TAG**

Detects 1d arrays with optional tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_TAG:)(%0(%1))

#define EXAMPLE_ARR(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name[42]); // EXAMPLE_ARR(,                   ,name,42)
EXAMPLE:Func(               Tag:name[42]); // EXAMPLE_ARR(,               Tag:,name,42)
EXAMPLE:Func(const              name[42]); // EXAMPLE_ARR(,const              ,name,42)
EXAMPLE:Func(const          Tag:name[42]); // EXAMPLE_ARR(,const          Tag:,name,42)
EXAMPLE:Func(      {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(,      {Tag1, Tag2}:,name,42)
EXAMPLE:Func(const {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(,const {Tag1, Tag2}:,name,42)
EXAMPLE:Func(                   name[  ]); // EXAMPLE_ARR(,                   ,name,  )
EXAMPLE:Func(               Tag:name[  ]); // EXAMPLE_ARR(,               Tag:,name,  )
EXAMPLE:Func(const              name[  ]); // EXAMPLE_ARR(,const              ,name,  )
EXAMPLE:Func(const          Tag:name[  ]); // EXAMPLE_ARR(,const          Tag:,name,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(,      {Tag1, Tag2}:,name,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(,const {Tag1, Tag2}:,name,  )
```

### ARRAY_CONST_TAG

AKA **ARR_CST_TAG**

Detects 1d arrays with optional `const`s tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_CST_TAG:)(%0(%1))

#define EXAMPLE_ARR(%0,%1,%2,%4)%8$

EXAMPLE:Func(                   name[42]); // EXAMPLE_ARR(      ,             ,name,42)
EXAMPLE:Func(               Tag:name[42]); // EXAMPLE_ARR(      ,         Tag:,name,42)
EXAMPLE:Func(const              name[42]); // EXAMPLE_ARR(const ,             ,name,42)
EXAMPLE:Func(const          Tag:name[42]); // EXAMPLE_ARR(const ,         Tag:,name,42)
EXAMPLE:Func(      {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(      ,{Tag1, Tag2}:,name,42)
EXAMPLE:Func(const {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(const ,{Tag1, Tag2}:,name,42)
EXAMPLE:Func(                   name[  ]); // EXAMPLE_ARR(      ,             ,name,  )
EXAMPLE:Func(               Tag:name[  ]); // EXAMPLE_ARR(      ,         Tag:,name,  )
EXAMPLE:Func(const              name[  ]); // EXAMPLE_ARR(const ,             ,name,  )
EXAMPLE:Func(const          Tag:name[  ]); // EXAMPLE_ARR(const ,         Tag:,name,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(      ,{Tag1, Tag2}:,name,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(const ,{Tag1, Tag2}:,name,  )
```

### ARRAY_TAGGROUP

AKA **ARR_GRP**

Detects 1d arrays with optional multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_GRP:)(%0(%1))

#define EXAMPLE_ARR(%0,(%1,%3),%2,%4)%8$

EXAMPLE:Func(                   name[42]); // EXAMPLE_ARR(,(     ,             ),name,42)
EXAMPLE:Func(               Tag:name[42]); // EXAMPLE_ARR(,( Tag:,         Tag:),name,42)
EXAMPLE:Func(const              name[42]); // ERROR
EXAMPLE:Func(const          Tag:name[42]); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(,(Tag1:,{Tag1, Tag2}:),name,42)
EXAMPLE:Func(const {Tag1, Tag2}:name[42]); // ERROR
EXAMPLE:Func(                   name[  ]); // EXAMPLE_ARR(,(     ,             ),name,  )
EXAMPLE:Func(               Tag:name[  ]); // EXAMPLE_ARR(,( Tag:,         Tag:),name,  )
EXAMPLE:Func(const              name[  ]); // ERROR
EXAMPLE:Func(const          Tag:name[  ]); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(,(Tag1:,{Tag1, Tag2}:),name,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ]); // ERROR
```

### ARRAY_CONST_TAGGROUP

AKA **ARR_CST_GRP**

Detects 1d arrays with optional `const`s and multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_CST_GRP:)(%0(%1))

#define EXAMPLE_ARR(%0,(%1,%3),%2,%4)%8$

EXAMPLE:Func(                   name[42]); // EXAMPLE_ARR(      ,(     ,              ),name,42)
EXAMPLE:Func(               Tag:name[42]); // EXAMPLE_ARR(      ,( Tag:,          Tag:),name,42)
EXAMPLE:Func(const              name[42]); // EXAMPLE_ARR(const ,(     ,              ),name,42)
EXAMPLE:Func(const          Tag:name[42]); // EXAMPLE_ARR(const ,( Tag:,          Tag:),name,42)
EXAMPLE:Func(      {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(      ,(Tag1:, {Tag1, Tag2}:),name,42)
EXAMPLE:Func(const {Tag1, Tag2}:name[42]); // EXAMPLE_ARR(const ,(Tag1:, {Tag1, Tag2}:),name,42)
EXAMPLE:Func(                   name[  ]); // EXAMPLE_ARR(      ,(     ,              ),name,  )
EXAMPLE:Func(               Tag:name[  ]); // EXAMPLE_ARR(      ,( Tag:,          Tag:),name,  )
EXAMPLE:Func(const              name[  ]); // EXAMPLE_ARR(const ,(     ,              ),name,  )
EXAMPLE:Func(const          Tag:name[  ]); // EXAMPLE_ARR(const ,( Tag:,          Tag:),name,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(      ,(Tag1:, {Tag1, Tag2}:),name,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ]); // EXAMPLE_ARR(const ,(Tag1:, {Tag1, Tag2}:),name,  )
```

### ARRAY_MULTI

AKA **ARR_MUL**

Detects multi-dimensional arrays.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_MUL:)(%0(%1))

#define EXAMPLE_ARR_ARR(%0,%1,%2,%4,%5)%8$

EXAMPLE:Func(                   name[42][11]); // EXAMPLE_ARR_ARR(,,                   name,42,11)
EXAMPLE:Func(               Tag:name[42][11]); // EXAMPLE_ARR_ARR(,,               Tag:name,42,11)
EXAMPLE:Func(const              name[42][11]); // EXAMPLE_ARR_ARR(,,const              name,42,11)
EXAMPLE:Func(const          Tag:name[42][  ]); // EXAMPLE_ARR_ARR(,,const          Tag:name,42,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(,,      {Tag1, Tag2}:name,42,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(,,const {Tag1, Tag2}:name,42,  )
EXAMPLE:Func(                   name[  ][11]); // EXAMPLE_ARR_ARR(,,                   name,  ,11)
EXAMPLE:Func(               Tag:name[  ][11]); // EXAMPLE_ARR_ARR(,,               Tag:name,  ,11)
EXAMPLE:Func(const              name[  ][11]); // EXAMPLE_ARR_ARR(,,const              name,  ,11)
EXAMPLE:Func(const          Tag:name[  ][  ]); // EXAMPLE_ARR_ARR(,,const          Tag:name,  ,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(,,      {Tag1, Tag2}:name,  ,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(,,const {Tag1, Tag2}:name,  ,  )

#define EXAMPLE_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$

EXAMPLE:Func(                   name[42][11][     90]); // EXAMPLE_ARR_ARR_ARR(,,                   name,42,11,90     )
EXAMPLE:Func(               Tag:name[42][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,,               Tag:name,42,11,MY_ENUM)
EXAMPLE:Func(const              name[42][11][       ]); // EXAMPLE_ARR_ARR_ARR(,,const              name,42,11,       )
EXAMPLE:Func(const          Tag:name[42][  ][     90]); // EXAMPLE_ARR_ARR_ARR(,,const          Tag:name,42,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,,      {Tag1, Tag2}:name,42,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ][       ]); // EXAMPLE_ARR_ARR_ARR(,,const {Tag1, Tag2}:name,42,  ,       )
EXAMPLE:Func(                   name[  ][11][     90]); // EXAMPLE_ARR_ARR_ARR(,,                   name,  ,11,90     )
EXAMPLE:Func(               Tag:name[  ][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,,               Tag:name,  ,11,MY_ENUM)
EXAMPLE:Func(const              name[  ][11][       ]); // EXAMPLE_ARR_ARR_ARR(,,const              name,  ,11,       )
EXAMPLE:Func(const          Tag:name[  ][  ][     90]); // EXAMPLE_ARR_ARR_ARR(,,const          Tag:name,  ,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,,      {Tag1, Tag2}:name,  ,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ][       ]); // EXAMPLE_ARR_ARR_ARR(,,const {Tag1, Tag2}:name,  ,  ,       )
```

### ARRAY_MULTI_CONST

AKA **ARR_MUL_CST**

Detects multi-dimensional arrays with optional `const`s.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_MUL_CST:)(%0(%1))

#define EXAMPLE_ARR_ARR(%0,%1,%2,%4,%5)%8$

EXAMPLE:Func(                   name[42][11]); // EXAMPLE_ARR_ARR(      ,,             name,42,11)
EXAMPLE:Func(               Tag:name[42][11]); // EXAMPLE_ARR_ARR(      ,,         Tag:name,42,11)
EXAMPLE:Func(const              name[42][11]); // EXAMPLE_ARR_ARR(const ,,             name,42,11)
EXAMPLE:Func(const          Tag:name[42][  ]); // EXAMPLE_ARR_ARR(const ,,         Tag:name,42,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(      ,,{Tag1, Tag2}:name,42,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(const ,,{Tag1, Tag2}:name,42,  )
EXAMPLE:Func(                   name[  ][11]); // EXAMPLE_ARR_ARR(      ,,             name,  ,11)
EXAMPLE:Func(               Tag:name[  ][11]); // EXAMPLE_ARR_ARR(      ,,         Tag:name,  ,11)
EXAMPLE:Func(const              name[  ][11]); // EXAMPLE_ARR_ARR(const ,,             name,  ,11)
EXAMPLE:Func(const          Tag:name[  ][  ]); // EXAMPLE_ARR_ARR(const ,,         Tag:name,  ,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(      ,,{Tag1, Tag2}:name,  ,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(const ,,{Tag1, Tag2}:name,  ,  )

#define EXAMPLE_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$

EXAMPLE:Func(                   name[42][11][     90]); // EXAMPLE_ARR_ARR_ARR(      ,,             name,42,11,90     )
EXAMPLE:Func(               Tag:name[42][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,,         Tag:name,42,11,MY_ENUM)
EXAMPLE:Func(const              name[42][11][       ]); // EXAMPLE_ARR_ARR_ARR(const ,,             name,42,11,       )
EXAMPLE:Func(const          Tag:name[42][  ][     90]); // EXAMPLE_ARR_ARR_ARR(const ,,         Tag:name,42,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,,{Tag1, Tag2}:name,42,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ][       ]); // EXAMPLE_ARR_ARR_ARR(const ,,{Tag1, Tag2}:name,42,  ,       )
EXAMPLE:Func(                   name[  ][11][     90]); // EXAMPLE_ARR_ARR_ARR(      ,,             name,  ,11,90     )
EXAMPLE:Func(               Tag:name[  ][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,,         Tag:name,  ,11,MY_ENUM)
EXAMPLE:Func(const              name[  ][11][       ]); // EXAMPLE_ARR_ARR_ARR(const ,,             name,  ,11,       )
EXAMPLE:Func(const          Tag:name[  ][  ][     90]); // EXAMPLE_ARR_ARR_ARR(const ,,         Tag:name,  ,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,,{Tag1, Tag2}:name,  ,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ][       ]); // EXAMPLE_ARR_ARR_ARR(const ,,{Tag1, Tag2}:name,  ,  ,       )
```

### ARRAY_MULTI_TAG

AKA **ARR_MUL_TAG**

Detects multi-dimensional arrays with optional tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_MUL_TAG:)(%0(%1))

#define EXAMPLE_ARR_ARR(%0,%1,%2,%4,%5)%8$

EXAMPLE:Func(                   name[42][11]); // EXAMPLE_ARR_ARR(,                   ,name,42,11)
EXAMPLE:Func(               Tag:name[42][11]); // EXAMPLE_ARR_ARR(,               Tag:,name,42,11)
EXAMPLE:Func(const              name[42][11]); // EXAMPLE_ARR_ARR(,const              ,name,42,11)
EXAMPLE:Func(const          Tag:name[42][  ]); // EXAMPLE_ARR_ARR(,const          Tag:,name,42,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(,      {Tag1, Tag2}:,name,42,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(,const {Tag1, Tag2}:,name,42,  )
EXAMPLE:Func(                   name[  ][11]); // EXAMPLE_ARR_ARR(,                   ,name,  ,11)
EXAMPLE:Func(               Tag:name[  ][11]); // EXAMPLE_ARR_ARR(,               Tag:,name,  ,11)
EXAMPLE:Func(const              name[  ][11]); // EXAMPLE_ARR_ARR(,const              ,name,  ,11)
EXAMPLE:Func(const          Tag:name[  ][  ]); // EXAMPLE_ARR_ARR(,const          Tag:,name,  ,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(,      {Tag1, Tag2}:,name,  ,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(,const {Tag1, Tag2}:,name,  ,  )

#define EXAMPLE_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$

EXAMPLE:Func(                   name[42][11][     90]); // EXAMPLE_ARR_ARR_ARR(,                   ,name,42,11,90     )
EXAMPLE:Func(               Tag:name[42][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,               Tag:,name,42,11,MY_ENUM)
EXAMPLE:Func(const              name[42][11][       ]); // EXAMPLE_ARR_ARR_ARR(,const              ,name,42,11,       )
EXAMPLE:Func(const          Tag:name[42][  ][     90]); // EXAMPLE_ARR_ARR_ARR(,const          Tag:,name,42,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,      {Tag1, Tag2}:,name,42,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ][       ]); // EXAMPLE_ARR_ARR_ARR(,const {Tag1, Tag2}:,name,42,  ,       )
EXAMPLE:Func(                   name[  ][11][     90]); // EXAMPLE_ARR_ARR_ARR(,                   ,name,  ,11,90     )
EXAMPLE:Func(               Tag:name[  ][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,               Tag:,name,  ,11,MY_ENUM)
EXAMPLE:Func(const              name[  ][11][       ]); // EXAMPLE_ARR_ARR_ARR(,const              ,name,  ,11,       )
EXAMPLE:Func(const          Tag:name[  ][  ][     90]); // EXAMPLE_ARR_ARR_ARR(,const          Tag:,name,  ,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,      {Tag1, Tag2}:,name,  ,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ][       ]); // EXAMPLE_ARR_ARR_ARR(,const {Tag1, Tag2}:,name,  ,  ,       )
```

### ARRAY_MULTI_CONST_TAG

AKA **ARR_MUL_CST_TAG**

Detects multi-dimensional arrays with optional `const`s and tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_MUL_CST_TAG:)(%0(%1))

#define EXAMPLE_ARR_ARR(%0,%1,%2,%4,%5)%8$

EXAMPLE:Func(                   name[42][11]); // EXAMPLE_ARR_ARR(      ,             ,name,42,11)
EXAMPLE:Func(               Tag:name[42][11]); // EXAMPLE_ARR_ARR(      ,         Tag:,name,42,11)
EXAMPLE:Func(const              name[42][11]); // EXAMPLE_ARR_ARR(const ,             ,name,42,11)
EXAMPLE:Func(const          Tag:name[42][  ]); // EXAMPLE_ARR_ARR(const ,         Tag:,name,42,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(      ,{Tag1, Tag2}:,name,42,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(const ,{Tag1, Tag2}:,name,42,  )
EXAMPLE:Func(                   name[  ][11]); // EXAMPLE_ARR_ARR(      ,             ,name,  ,11)
EXAMPLE:Func(               Tag:name[  ][11]); // EXAMPLE_ARR_ARR(      ,         Tag:,name,  ,11)
EXAMPLE:Func(const              name[  ][11]); // EXAMPLE_ARR_ARR(const ,             ,name,  ,11)
EXAMPLE:Func(const          Tag:name[  ][  ]); // EXAMPLE_ARR_ARR(const ,         Tag:,name,  ,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(      ,{Tag1, Tag2}:,name,  ,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(const ,{Tag1, Tag2}:,name,  ,  )

#define EXAMPLE_ARR_ARR_ARR(%0,%1,%2,%4,%5,%6)%8$

EXAMPLE:Func(                   name[42][11][     90]); // EXAMPLE_ARR_ARR_ARR(      ,             ,name,42,11,90     )
EXAMPLE:Func(               Tag:name[42][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,         Tag:,name,42,11,MY_ENUM)
EXAMPLE:Func(const              name[42][11][       ]); // EXAMPLE_ARR_ARR_ARR(const ,             ,name,42,11,       )
EXAMPLE:Func(const          Tag:name[42][  ][     90]); // EXAMPLE_ARR_ARR_ARR(const ,         Tag:,name,42,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,{Tag1, Tag2}:,name,42,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ][       ]); // EXAMPLE_ARR_ARR_ARR(const ,{Tag1, Tag2}:,name,42,  ,       )
EXAMPLE:Func(                   name[  ][11][     90]); // EXAMPLE_ARR_ARR_ARR(      ,             ,name,  ,11,90     )
EXAMPLE:Func(               Tag:name[  ][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,         Tag:,name,  ,11,MY_ENUM)
EXAMPLE:Func(const              name[  ][11][       ]); // EXAMPLE_ARR_ARR_ARR(const ,             ,name,  ,11,       )
EXAMPLE:Func(const          Tag:name[  ][  ][     90]); // EXAMPLE_ARR_ARR_ARR(const ,         Tag:,name,  ,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,{Tag1, Tag2}:,name,  ,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ][       ]); // EXAMPLE_ARR_ARR_ARR(const ,{Tag1, Tag2}:,name,  ,  ,       )
```

### ARRAY_MULTI_TAGGROUP

AKA **ARR_MUL_GRP**

Detects multi-dimensional arrays with optional multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_MUL_GRP:)(%0(%1))

#define EXAMPLE_ARR_ARR(%0,(%1,%3),%2,%4,%5)%8$

EXAMPLE:Func(                   name[42][11]); // EXAMPLE_ARR_ARR(,(     ,             ),name,42,11)
EXAMPLE:Func(               Tag:name[42][11]); // EXAMPLE_ARR_ARR(,( Tag:,         Tag:),name,42,11)
EXAMPLE:Func(const              name[42][11]); // ERROR
EXAMPLE:Func(const          Tag:name[42][  ]); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(,(Tag1:,{Tag1, Tag2}:),name,42,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ]); // ERROR
EXAMPLE:Func(                   name[  ][11]); // EXAMPLE_ARR_ARR(,(     ,             ),name,  ,11)
EXAMPLE:Func(               Tag:name[  ][11]); // EXAMPLE_ARR_ARR(,( Tag:,         Tag:),name,  ,11)
EXAMPLE:Func(const              name[  ][11]); // ERROR
EXAMPLE:Func(const          Tag:name[  ][  ]); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(,(Tag1:,{Tag1, Tag2}:),name,  ,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ]); // ERROR

#define EXAMPLE_ARR_ARR_ARR(%0,(%1,%3),%2,%4,%5,%6)%8$

EXAMPLE:Func(                   name[42][11][     90]); // EXAMPLE_ARR_ARR_ARR(,(     ,             ),name,42,11,90     )
EXAMPLE:Func(               Tag:name[42][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,( Tag:,         Tag:),name,42,11,MY_ENUM)
EXAMPLE:Func(const              name[42][11][       ]); // ERROR
EXAMPLE:Func(const          Tag:name[42][  ][     90]); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,(Tag1:,{Tag1, Tag2}:),name,42,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ][       ]); // ERROR
EXAMPLE:Func(                   name[  ][11][     90]); // EXAMPLE_ARR_ARR_ARR(,(     ,             ),name,  ,11,90     )
EXAMPLE:Func(               Tag:name[  ][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,( Tag:,         Tag:),name,  ,11,MY_ENUM)
EXAMPLE:Func(const              name[  ][11][       ]); // ERROR
EXAMPLE:Func(const          Tag:name[  ][  ][     90]); // ERROR
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(,(Tag1:,{Tag1, Tag2}:),name,  ,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ][       ]); // ERROR
```

### ARRAY_MULTI_CONST_TAGGROUP

AKA **ARR_MUL_CST_GRP**

Detects multi-dimensional arrays with optional `const`s and multiple tags.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR_CST_GRP:)(%0(%1))

#define EXAMPLE_ARR_ARR(%0,(%1,%3),%2,%4,%5)%8$

EXAMPLE:Func(                   name[42][11]); // EXAMPLE_ARR_ARR(      ,(     ,              ),name,42,11)
EXAMPLE:Func(               Tag:name[42][11]); // EXAMPLE_ARR_ARR(      ,( Tag:,          Tag:),name,42,11)
EXAMPLE:Func(const              name[42][11]); // EXAMPLE_ARR_ARR(const ,(     ,              ),name,42,11)
EXAMPLE:Func(const          Tag:name[42][  ]); // EXAMPLE_ARR_ARR(const ,( Tag:,          Tag:),name,42,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(      ,(Tag1:, {Tag1, Tag2}:),name,42,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ]); // EXAMPLE_ARR_ARR(const ,(Tag1:, {Tag1, Tag2}:),name,42,  )
EXAMPLE:Func(                   name[  ][11]); // EXAMPLE_ARR_ARR(      ,(     ,              ),name,  ,11)
EXAMPLE:Func(               Tag:name[  ][11]); // EXAMPLE_ARR_ARR(      ,( Tag:,          Tag:),name,  ,11)
EXAMPLE:Func(const              name[  ][11]); // EXAMPLE_ARR_ARR(const ,(     ,              ),name,  ,11)
EXAMPLE:Func(const          Tag:name[  ][  ]); // EXAMPLE_ARR_ARR(const ,( Tag:,          Tag:),name,  ,  )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(      ,(Tag1:, {Tag1, Tag2}:),name,  ,  )
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ]); // EXAMPLE_ARR_ARR(const ,(Tag1:, {Tag1, Tag2}:),name,  ,  )

#define EXAMPLE_ARR_ARR_ARR(%0,(%1,%3),%2,%4,%5,%6)%8$

EXAMPLE:Func(                   name[42][11][     90]); // EXAMPLE_ARR_ARR_ARR(      ,(     ,              ),name,42,11,90     )
EXAMPLE:Func(               Tag:name[42][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,( Tag:,          Tag:),name,42,11,MY_ENUM)
EXAMPLE:Func(const              name[42][11][       ]); // EXAMPLE_ARR_ARR_ARR(const ,(     ,              ),name,42,11,       )
EXAMPLE:Func(const          Tag:name[42][  ][     90]); // EXAMPLE_ARR_ARR_ARR(const ,( Tag:,          Tag:),name,42,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[42][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,(Tag1:, {Tag1, Tag2}:),name,42,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[42][  ][       ]); // EXAMPLE_ARR_ARR_ARR(const ,(Tag1:, {Tag1, Tag2}:),name,42,  ,       )
EXAMPLE:Func(                   name[  ][11][     90]); // EXAMPLE_ARR_ARR_ARR(      ,(     ,              ),name,  ,11,90     )
EXAMPLE:Func(               Tag:name[  ][11][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,( Tag:,          Tag:),name,  ,11,MY_ENUM)
EXAMPLE:Func(const              name[  ][11][       ]); // EXAMPLE_ARR_ARR_ARR(const ,(     ,              ),name,  ,11,       )
EXAMPLE:Func(const          Tag:name[  ][  ][     90]); // EXAMPLE_ARR_ARR_ARR(const ,( Tag:,          Tag:),name,  ,  ,90     )
EXAMPLE:Func(      {Tag1, Tag2}:name[  ][  ][MY_ENUM]); // EXAMPLE_ARR_ARR_ARR(      ,(Tag1:, {Tag1, Tag2}:),name,  ,  ,MY_ENUM)
EXAMPLE:Func(const {Tag1, Tag2}:name[  ][  ][       ]); // EXAMPLE_ARR_ARR_ARR(const ,(Tag1:, {Tag1, Tag2}:),name,  ,  ,       )
```

## LENGTH

AKA **LEN**

Enforces length variables appearing after arrays.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,ARR:NUM:LEN:)(%0(%1))

#define EXAMPLE_ARR(%0,%1,%2,%4)%8$
#define EXAMPLE_NUM(%0,%1,%2)%8$

EXAMPLE:Func(         length); // EXAMPLE_NUM(,,length)
EXAMPLE:Func(array[], length); // EXAMPLE_ARR(,,array,) EXAMPLE_NUM(,,length)
EXAMPLE:Func(array[]        ); // ERROR
```

### SPECIAL

AKA **SPC**

Detects special arrays (`Type:name<size>`s).

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,SPC:)(%0(%1))

#define EXAMPLE_SPC(%0,%1,%2,%4)%8$

EXAMPLE:Func(      Type:name<  >); // EXAMPLE_SPC(,Type:,      name,  )
EXAMPLE:Func(      Type:name<10>); // EXAMPLE_SPC(,Type:,      name,10)
EXAMPLE:Func(const Type:name<  >); // EXAMPLE_SPC(,Type:,const name,  )
EXAMPLE:Func(const Type:name<10>); // EXAMPLE_SPC(,Type:,const name,10)
```

### SPECIAL_CONST

AKA **SPC_CST**

Detects special arrays (`Type:name<size>`s) with optional `const`s.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,SPC_CST:)(%0(%1))

#define EXAMPLE_SPC(%0,%1,%2,%4)%8$

EXAMPLE:Func(      Type:name<  >); // EXAMPLE_SPC(      ,Type:,name,  )
EXAMPLE:Func(      Type:name<10>); // EXAMPLE_SPC(      ,Type:,name,10)
EXAMPLE:Func(const Type:name<  >); // EXAMPLE_SPC(const ,Type:,name,  )
EXAMPLE:Func(const Type:name<10>); // EXAMPLE_SPC(const ,Type:,name,10)
```

## Complete Return Reference

### _END

Called for completion after all parameters have been parsed.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END(       Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END(  void:Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END( Float:Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END(string:Func)
```

### _NUL

Called for completion when there are no parameters.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL(       Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL(  void:Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL( Float:Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL(string:Func)
```

### _END_TAG

Called for completion after all parameters have been parsed, with an optional tagged return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$
#define EXAMPLE_END_TAG(%0,%1)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (        Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG(  void:,Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG( Float:,Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG(string:,Func)
```

### _NUL_TAG

Called for completion when there are no parameters, with an optional tagged return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_NUL_TAG(%0,%1)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL    (        Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL_TAG(  void:,Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL_TAG( Float:,Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL_TAG(string:,Func)
```

### _END_VOD

Called for completion after all parameters have been parsed, with an optional void (missing) return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_VOD:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$
#define EXAMPLE_END_VOD(%0)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (       Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_VOD(       Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    ( Float:Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (string:Func)
```

### _NUL_VOD

Called for completion when there are no parameters, with an optional void (missing) return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_VOD:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_NUL_VOD(%0)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL    (       Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL_VOD(       Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL    ( Float:Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL    (string:Func)
```

### _END_STR

Called for completion after all parameters have been parsed, with an optional string return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$
#define EXAMPLE_END_STR(%0)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (      Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    ( void:Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (Float:Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_STR(      Func)
```

### _NUL_STR

Called for completion when there are no parameters, with an optional string return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_NUL_STR(%0)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL    (      Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL    ( void:Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL    (Float:Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL_STR(      Func)
```

### _END_TAG_VOD

Called for completion after all parameters have been parsed, with an optional tagged return or void (missing) return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG_VOD:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$
#define EXAMPLE_END_TAG(%0,%1)%8$
#define EXAMPLE_END_VOD(%0)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (        Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_VOD(        Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG( Float:,Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG(string:,Func)
```

### _NUL_TAG_VOD

Called for completion when there are no parameters, with an optional tagged return or void (missing) return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG_VOD:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_NUL_TAG(%0,%1)%8$
#define EXAMPLE_NUL_VOD(%0)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL    (        Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL_VOD(        Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL_TAG( Float:,Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL_TAG(string:,Func)
```

### _END_VOD_STR

Called for completion after all parameters have been parsed, with an optional void (missing) return or string return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_VOD_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$
#define EXAMPLE_END_VOD(%0)%8$
#define EXAMPLE_END_STR(%0)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (       Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_VOD(       Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    ( Float:Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_STR(       Func)
```

### _NUL_VOD_STR

Called for completion when there are no parameters, with an optional void (missing) return or string return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_VOD_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_NUL_VOD(%0)%8$
#define EXAMPLE_NUL_STR(%0)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL    (       Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL_VOD(       Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL    ( Float:Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL_STR(       Func)
```

### _END_TAG_STR

Called for completion after all parameters have been parsed, with an optional tagged return or string return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$
#define EXAMPLE_END_TAG(%0,%1)%8$
#define EXAMPLE_END_STR(%0)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (       Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG( void:,Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG(Float:,Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_STR(       Func)
```

### _NUL_TAG_STR

Called for completion when there are no parameters, with an optional tagged return or string return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_NUL_TAG(%0,%1)%8$
#define EXAMPLE_NUL_STR(%0)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL    (       Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL_TAG( void:,Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL_TAG(Float:,Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL_STR(       Func)
```

### _END_TAG_VOD_STR

Called for completion after all parameters have been parsed; with an optional string return, tagged return, or void (missing) return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG_VOD_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_END(%0)%8$
#define EXAMPLE_END_TAG(%0,%1)%8$
#define EXAMPLE_END_STR(%0)%8$
#define EXAMPLE_END_VOD(%0)%8$

EXAMPLE:       Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END    (       Func)
EXAMPLE:  void:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_VOD(       Func)
EXAMPLE: Float:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_TAG(Float:,Func)
EXAMPLE:string:Func(var); // EXAMPLE_NUM(,,var) EXAMPLE_END_STR(       Func)
```

### _NUL_TAG_VOD_STR

Called for completion when there are no parameters; with an optional string return, tagged return, or void (missing) return.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:RET_TAG_VOD_STR:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_NUL_TAG(%0,%1)%8$
#define EXAMPLE_NUL_STR(%0)%8$
#define EXAMPLE_NUL_VOD(%0)%8$

EXAMPLE:       Func(); // EXAMPLE_NUL    (       Func)
EXAMPLE:  void:Func(); // EXAMPLE_NUL_VOD(       Func)
EXAMPLE: Float:Func(); // EXAMPLE_NUL_TAG(Float:,Func)
EXAMPLE:string:Func(); // EXAMPLE_NUL_STR(       Func)
```

### QUALIFICATION

AKA **QAL**

Used to detect function qualifiers before endings are performed.

```pawn
#define EXAMPLE:%0(%1) FUNC_PARSER(EXAMPLE,NUM:QAL:)(%0(%1))

#define EXAMPLE_NUM(%0,%1,%2)%8$
#define EXAMPLE_NUL(%0)%8$
#define EXAMPLE_stock()%8$
#define EXAMPLE_static()%8$
#define EXAMPLE_global()%8$
#define EXAMPLE_operator()%8$

EXAMPLE:             Func(); //                                     EXAMPLE_NUL(Func)
EXAMPLE:stock        Func(); // EXAMPLE_stock()                     EXAMPLE_NUL(Func)
EXAMPLE:static stock Func(); // EXAMPLE_static() EXAMPLE_stock()    EXAMPLE_NUL(Func)
EXAMPLE:global       Func(); // EXAMPLE_global()                    EXAMPLE_NUL(Func)
EXAMPLE:operator     !(num); // EXAMPLE_NUM(num) EXAMPLE_operator() EXAMPLE_END(!)
```

