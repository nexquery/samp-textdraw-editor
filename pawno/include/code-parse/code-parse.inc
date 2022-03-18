/*
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 (the "License"); you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the code-parse.inc code analyser.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (C) 2016
	the Initial Developer. All Rights Reserved.
*/

#if defined _INC_code_parse_inc
	#endinput
#endif
#define _INC_code_parse_inc

// This include provides a handy set of macros for advanced compile-time code
// analysis and generation.  With this, one can do things like analyse the
// parameter types for a function, auto-generate call specifiers, and otherwise
// create code-dependent macros.

// Remove this tag from any final output after all other parsing is done.
#define string:
#define void:

// A very generic entry point.  This can be used by any other system to put
// arbitrary macros at the top level of the file without compiler errors.
#define u@$ 0]);
#define PARSER@FUNC:%0$ u@(u[_:%0 u@$

// This is the "global" entry point.  It takes a list of parser types, followed
// by a custom macro name prefix for the user code, followed by the parameters
// to parse.  We always have "p@:" on the end to detect remaining parameters
// (this will detect any type not covered by others).
#define MAKE_PARSER(%0,%1)(%3(%4)) PARSE@%1(--,,,,,,p@:A@[])(%0)%3(%4,)
#define FUNC_PARSER(%0,%1) MAKE_PARSER(%0,%1:FUNC)

// Modifiers for parameter types.  These detect optional extra bits such as
// "const" and tags.

// Detect "const".
#define c@:%8(%0,%1,%9const%7\32;%2) T@:O@$%7$const$(%9){PARSER_CONST,PARSER_NOT_CONST}(%8)(%0,%1,%2)
#define PARSER_CONST(%7)(%8)(%0,%1,%2) %8(%0%7 ,%1,%2)
#define PARSER_NOT_CONST(%7)(%8)(%0,%1,%2) %8(%0,%1,%7 %2)

// Detect the lack of space after a symbol, for example with `const%1\32;`.
#define PARSER_ISOLATE(%9,%0,%1){%2,%3} _:T@:O@$%1$%0$(%9){%2,%3}
#define T@:O@$$%0$(){%2,%3} %2(%0)
#define O@$%1$%0$(%9){%2,%3} %3(%9%0%1)

// Detect tags.
#define t@:%5:A@[%7]%8(%0,%1,%9:%2) %7%8(%0,%1%9:,%2)

// Duplicate normal tags if this is "GRP:" instead of "TAG:" so that we can keep
// backwards-compatability while supporting the new syntax for both tags and tag
// groups.
#define PARSER_GRP:%8(%0,%1,%2) %8(%0,(%1,%1),%2)

// Don't want group tags (just an ignored tag).
#define PARSER_ID:

// Want group tags, but none found (adjust the parameter shape)
#define PARSER_WANT:%8(%0,%1,%2) %8(%0,(,),%2)

#define F@: PARSER_NO:
#define G@: PARSER_GRP:
#define H@: PARSER_ID:
#define L@: PARSER_WANT:

// Detect groups of tags.  Passed as two parameters WITHIN the `tag` parameter,
// so this:
//   
//   #define GRP_EG:%0(%1) FUNC_PARSER(GRP_EG,VAR_GRP:)(%0(%1))
//   GRP_EG:Func({a, b, c}:v);
//   
// Will call:
//   
//   GRP_EG_VAR(,(a:,{a, b, c}:),v)
//   
// Thus passing the first tag as the first part of the second parameter, and the
// whole tag as given in code as the second parameter.  The first tag is passed
// as special because you can't use `{a, b, c}:` as a tag override in code so
// you have to use just one of the specified tags; and `tagof (v)` will usually
// return the first tag from the group, so it is the most important one.
#define x@:%8(%0,(%1{%7,%9}:,%9),%2) %8(%0,(%7:,%9),%2)

// Detect defaults.
#define d@:%8(%0,%1,%2=%9) %8_DEF(%0,%1,%2,%9)
#define b@:%8(%0,%1,%2=%9,%4) %8_DEF(%0,%1,%2,%4,%9)

// Detect recursive array sizes (multi-dimensional arrays).
#define f@:%8(%0,%1,%2[%9]%6,%3) f@:%8_ARR(%0,%1,%2%6,%3,%9)

// Remove specialisers after we are done with this parameter type.
#define A@[%9]

// Redistribute the new parsers to after the current parameter.
#define LENGTH_REQUIRED{%9}%0(%1)%2(%3)%4(|||%6,%7) %0(%1)j@:q@:%9.%2(%3)%4(%6|||%7)
#define E@{%0} LENGTH_REQUIRED{%0}

// Detect "string:" (words).  Done in two parts so "const string:" doesn't fail
// because the "st" in "const" is detected but is not followed by "i".
#define c@st:%0(%1,%2,%3st%4) %0(%1,%2,%4)
#define w@:A@[%8]%9.%0(%5)%3(%6ring:%1[%2]%9|||%7) %8c@st:%5_STR(,,%6%1%9,%2)%0(%5)%3(|||%7)

// Detect "[]".
#define a@:A@[%8]%9.%0(%5)%3(%1[%2]%9|||%7) %8%5_ARR(,,%1%9,%2)%0(%5)%3(|||%7)

// Detect "<>".
#define o@:A@[%8]%9.%0(%5)%3(%1:%4<%2>%9|||%7) %8%5_SPC(,%1:,%4%9,%2)%0(%5)%3(|||%7)

#define j@:%0(%5)%3(%1[%2]%9|||%7) LENGTH_REQUIRED()
#define q@:%0(%5)%3(%1...%2|||%7)  LENGTH_REQUIRED()

// Detect "&".
#define r@:A@[%8]%9.%0(%5)%3(%1&%2|||%7) %8%5_REF(,,%1%2)%0(%5)%3(|||%7)

// Detect varargs.
#define v@:A@[%8]%9.%0(%5)%3(%1...%2|||%7) %8%5_EXT(,,%1%2)%0(%5)%3(|||%7)

// Detect others.
#define p@:A@[%8]%9.%0(%5)%3(%1|||%7) %8%5_NUM(,,%1)%0(%5)%3(|||%7)

// Detect none.
#define z@:%0[%9]%0(%5)%3(|||,%7)%4$ %9%5_NUL(%3)n@DROP[%5]%7%4$

// Detect out of parameters.
#define n@[%9]%0(%5)%3(%6|||%7)%4$ %9%5_END(%3)n@DROP[%5]%7%4$
#define n@DROP[%5]

// Not none, thus many parameters.  Used to recurse through multiple parameters.
#define m@:n@[%9]%0(%5)%3(%6|||%7,%8)%4$ %0.m@:n@[%9]%0(%5)%3(%7|||%8)%4$

// Detect possible return types.
#define g@:%9~~%5(%9void:%3) %5_VOD(%3)
#define k@:%9~~%5(%9string:%3) %5_STR(%3)
#define l@:%9~~%5(%9:%3) PARSE_WILL_BE(%9)%5_TAG<:,%3>
#define PARSE_WILL_BE(%9)%5<%3> %5(%9%3)

#define PP_LEFT_BRACKET<> (
#define PP_RIGHT_BRACKET<> )
#define PP_LEFT_BRACE<> {
#define PP_RIGHT_BRACE<> }
#define PP_LEFT_SQUARE_BRACKET<> [
#define PP_RIGHT_SQUARE_BRACKET<> ]
#define PP_LEFT_ANGLE_BRACKET<> <
#define PP_RIGHT_ANGLE_BRACKET<> >
#define PP_NULL<>

// Detect possible function modifiers
#define e@[%5]

// Default PAWN keywords.
#define statice@[%5]   %5_static()
#define stocke@[%5]    %5_stock()
#define publice@[%5]   %5_public()
#define conste@[%5]    %5_const()
#define forwarde@[%5]  %5_forward()
#define newe@[%5]      %5_new()
#define operatore@[%5] %5_state()
#define nativee@[%5]   %5_native()

// YSI keywords.
#define globale@[%5]       %5_global()
#define foreigne@[%5]      %5_foreign()
#define timere@[%5]        %5_timer()
#define ptaske@[%5]        %5_ptask()
#define taske@[%5]         %5_task()
#define remoterunce@[%5]   %5_remoterunc()
#define hooke@[%5]         %5_hook()
#define inlinee@[%5]       %5_inline()
#define group_hooke@[%5]   %5_group_hook()
#define master_hooke@[%5]  %5_master_hook()
#define master_taske@[%5]  %5_master_task()
#define master_ptaske@[%5] %5_master_ptask()
#define master_funce@[%5]  %5_master_func()
#define @foreigne@[%5]     %5_@foreign()
#define @globale@[%5]      %5_@global()
#define timerfunce@[%5]    %5_timerfunc()
#define loadtexte@[%5]     %5_loadtext()

#define s@:h@:i@:%4(%0\32;[%5](%8)) %4%8(%0)
#define h@:i@:%4(%0\32;%2[%5](%8)) %0e@[%5]h@:i@:%4(%2[%5](%8))
#define i@:%4(%0[%5](%8)) %8(%0)
#define y@:%8(%1)%2[%5] s@:h@:i@:%8(%1[%5](%8))%2[%5]

// We need the macros in a very specific order, because some will match others
// as well.  For example, arrays will match strings but not vice-versa, so we
// need to check for strings first.  Additionally, requesting scans for arrays
// with tags and arrays without tags (for example) makes no sense - just use the
// former.  For this reason we compress all the options by joining them in a
// list first then expanding that list:
// 
//   %0 - String detection options.     string:a[]
//   %1 - Array detection options.      a[]
//   %2 - Reference detection options.  &a
//   %3 - Vararg detection options.     ...     
//   %4 - Other detection options.      a
// 
// Obviously "other" comes last as it will match literally anything else.  The
// string and array options must be relatively ordered, but their order relative
// to "&" and "..." is arbitrary.  Once all the type options are collected, the
// "PARSE@WHATEVER" macros will stop triggering and the "PARSE@()" macro will
// trigger instead to combine all the tag macros.
#define PARSE@:%8(%9-%2-,%0)(%5)%6(%7) PARSE_EXPAND@(%0)PARSER@%8:z@:m@:n@[%2%9~~](%5)%6(|||%7)$
#define PARSE_EXPAND@(%0,%1,%2,%5,%3,%4)%6[%7] %6[%7]%0%1%2%5%3%4

// Return types.
#define PARSE@RET_VOD:%8(%9-%7-,%0,%1,%2,%5,%3,%4)         PARSE@%8(g@:-%7-,%0,%1,%2,%5,%3,%4)       // void:
#define PARSE@RET_VOD_STR:%8(%9-%7-,%0,%1,%2,%5,%3,%4)     PARSE@%8(g@:k@:-%7-,%0,%1,%2,%5,%3,%4)    // void: string:
#define PARSE@RET_STR_VOD                       PARSE@RET_VOD_STR
#define PARSE@RET_VOD_TAG:%8(%9-%7-,%0,%1,%2,%5,%3,%4)     PARSE@%8(g@:l@:-%7-,%0,%1,%2,%5,%3,%4)    // void: ???:
#define PARSE@RET_TAG_VOD                       PARSE@RET_VOD_TAG
#define PARSE@RET_VOD_STR_TAG:%8(%9-%7-,%0,%1,%2,%5,%3,%4) PARSE@%8(g@:k@:l@:-%7-,%0,%1,%2,%5,%3,%4) // void: string: ???:
#define PARSE@RET_STR_VOD_TAG                   PARSE@RET_VOD_STR_TAG
#define PARSE@RET_VOD_TAG_STR                   PARSE@RET_VOD_STR_TAG
#define PARSE@RET_STR_TAG_VOD                   PARSE@RET_VOD_STR_TAG
#define PARSE@RET_TAG_VOD_STR                   PARSE@RET_VOD_STR_TAG
#define PARSE@RET_TAG_STR_VOD                   PARSE@RET_VOD_STR_TAG
#define PARSE@RET_TAG:%8(%9-%7-,%0,%1,%2,%5,%3,%4)         PARSE@%8(l@:-%7-,%0,%1,%2,%5,%3,%4)       // ???:
#define PARSE@RET_STR:%8(%9-%7-,%0,%1,%2,%5,%3,%4)         PARSE@%8(k@:-%7-,%0,%1,%2,%5,%3,%4)       // string:
#define PARSE@RET_STR_TAG:%8(%9-%7-,%0,%1,%2,%5,%3,%4)     PARSE@%8(k@:l@:-%7-,%0,%1,%2,%5,%3,%4)    // string: ???:
#define PARSE@RET_TAG_STR                       PARSE@RET_STR_TAG

#define PARSE@QAL:%8(%9-%7-,%0,%1,%2,%5,%3,%4) PARSE@%8(%9-y@:-,%0,%1,%2,%5,%3,%4)       // stock, const, etc.
#define PARSE@QUALIFIERS PARSE@QAL

#define PARSE@RET_VOID            PARSE@RET_VOD
#define PARSE@RET_VOID_STRING     PARSE@RET_VOD_STR
#define PARSE@RET_STRING_VOID     PARSE@RET_VOD_STR
#define PARSE@RET_VOID_TAG        PARSE@RET_VOD_TAG
#define PARSE@RET_TAG_VOID        PARSE@RET_VOD_TAG
#define PARSE@RET_VOID_STRING_TAG PARSE@RET_VOD_STR_TAG
#define PARSE@RET_STRING_VOID_TAG PARSE@RET_VOD_STR_TAG
#define PARSE@RET_VOID_TAG_STRING PARSE@RET_VOD_STR_TAG
#define PARSE@RET_STRING_TAG_VOID PARSE@RET_VOD_STR_TAG
#define PARSE@RET_TAG_VOID_STRING PARSE@RET_VOD_STR_TAG
#define PARSE@RET_TAG_STRING_VOID PARSE@RET_VOD_STR_TAG
#define PARSE@RET_STRING          PARSE@RET_STR
#define PARSE@RET_STRING_TAG      PARSE@RET_STR_TAG
#define PARSE@RET_TAG_STRING      PARSE@RET_STR_TAG

// Enforce array lengths.
#define PARSE@LEN:%8(%9,%0,a@:A@[%1],%2,%5,%3,%4) PARSE@%8(%9,%0,a@:A@[%1E@{%2%4}],%2,%5,%3,%4)
#define PARSE@LENGTH PARSE@LEN

// All the parameter types that can be detected (hopefully all).  "tag" macros
// will also match multi-tag types such as "{tag, _}:..."
#define PARSE@NUM_TAG:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[t@:F@:A@[]])       // tag:a
#define PARSE@TAG_NUM                           PARSE@NUM_TAG
#define PARSE@NUM_GRP:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[t@:L@:A@[G@:x@:]])       // {tag1, tag2}:a
#define PARSE@GRP_NUM                           PARSE@NUM_GRP
#define PARSE@STR:%8(%9,%0,%1,%2,%5,%3,%4)             PARSE@%8(%9,w@:A@[],%1,%2,%5,%3,%4)          // string:a[]
#define PARSE@STR_DEF:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,w@:A@[b@:],%1,%2,%5,%3,%4)       // string:a[] = "hi"
#define PARSE@DEF_STR                           PARSE@STR_DEF
#define PARSE@NUM:%8(%9,%0,%1,%2,%5,%3,%4)             PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[])          // a
#define PARSE@NUM_TAG_DEF:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[t@:F@:A@[]d@:])    // tag:a = 5
#define PARSE@NUM_DEF_TAG                       PARSE@NUM_TAG_DEF
#define PARSE@TAG_NUM_DEF                       PARSE@NUM_TAG_DEF
#define PARSE@DEF_NUM_TAG                       PARSE@NUM_TAG_DEF
#define PARSE@TAG_DEF_NUM                       PARSE@NUM_TAG_DEF
#define PARSE@DEF_TAG_NUM                       PARSE@NUM_TAG_DEF
#define PARSE@NUM_GRP_DEF:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[t@:L@:A@[G@:x@:]d@:])    // {tag1, tag2}:a = 5
#define PARSE@NUM_DEF_GRP                       PARSE@NUM_GRP_DEF
#define PARSE@GRP_NUM_DEF                       PARSE@NUM_GRP_DEF
#define PARSE@DEF_NUM_GRP                       PARSE@NUM_GRP_DEF
#define PARSE@GRP_DEF_NUM                       PARSE@NUM_GRP_DEF
#define PARSE@DEF_GRP_NUM                       PARSE@NUM_GRP_DEF
#define PARSE@NUM_DEF:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[d@:])       // a = 5
#define PARSE@DEF_NUM                           PARSE@NUM_DEF
#define PARSE@REF:%8(%9,%0,%1,%2,%5,%3,%4)             PARSE@%8(%9,%0,%1,r@:A@[],%5,%3,%4)          // &a
#define PARSE@REF_TAG:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,r@:A@[t@:F@:A@[]],%5,%3,%4)       // &tag:a
#define PARSE@TAG_REF                           PARSE@REF_TAG
#define PARSE@REF_GRP:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,r@:A@[t@:L@:A@[G@:x@:]],%5,%3,%4)       // &{tag1, tag2}:a
#define PARSE@GRP_REF                           PARSE@REF_GRP
#define PARSE@REF_DEF:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,r@:A@[d@:],%5,%3,%4)       // &a = 5
#define PARSE@DEF_REF                           PARSE@REF_DEF
#define PARSE@REF_TAG_DEF:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,%1,r@:A@[t@:F@:A@[]d@:],%5,%3,%4)    // &tag:a = 5
#define PARSE@REF_DEF_TAG                       PARSE@REF_TAG_DEF
#define PARSE@TAG_REF_DEF                       PARSE@REF_TAG_DEF
#define PARSE@TAG_DEF_REF                       PARSE@REF_TAG_DEF
#define PARSE@DEF_REF_TAG                       PARSE@REF_TAG_DEF
#define PARSE@DEF_TAG_REF                       PARSE@REF_TAG_DEF
#define PARSE@REF_GRP_DEF:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,%1,r@:A@[t@:L@:A@[G@:x@:]d@:],%5,%3,%4)    // &{tag1, tag2}:a = 5
#define PARSE@REF_DEF_GRP                       PARSE@REF_GRP_DEF
#define PARSE@GRP_REF_DEF                       PARSE@REF_GRP_DEF
#define PARSE@GRP_DEF_REF                       PARSE@REF_GRP_DEF
#define PARSE@DEF_REF_GRP                       PARSE@REF_GRP_DEF
#define PARSE@DEF_GRP_REF                       PARSE@REF_GRP_DEF
#define PARSE@EXT:%8(%9,%0,%1,%2,%5,%3,%4)             PARSE@%8(%9,%0,%1,%2,%5,v@:A@[],%4)          // ...
#define PARSE@EXT_TAG:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,%2,%5,v@:A@[t@:F@:A@[]],%4)       // tag:...
#define PARSE@TAG_EXT                           PARSE@EXT_TAG
#define PARSE@NUM_CST_TAG:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[c@:t@:F@:A@[]])    // const tag:a
#define PARSE@NUM_TAG_CST                       PARSE@NUM_CST_TAG
#define PARSE@TAG_NUM_CST                       PARSE@NUM_CST_TAG
#define PARSE@TAG_CST_NUM                       PARSE@NUM_CST_TAG
#define PARSE@CST_NUM_TAG                       PARSE@NUM_CST_TAG
#define PARSE@CST_TAG_NUM                       PARSE@NUM_CST_TAG
#define PARSE@EXT_GRP:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,%2,%5,v@:A@[t@:L@:A@[G@:x@:]],%4)       // {tag1, tag2}:...
#define PARSE@GRP_EXT                           PARSE@EXT_GRP
#define PARSE@NUM_CST_GRP:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[c@:t@:L@:A@[G@:x@:]])    // const {tag1, tag2}:a
#define PARSE@NUM_GRP_CST                       PARSE@NUM_CST_GRP
#define PARSE@GRP_NUM_CST                       PARSE@NUM_CST_GRP
#define PARSE@GRP_CST_NUM                       PARSE@NUM_CST_GRP
#define PARSE@CST_NUM_GRP                       PARSE@NUM_CST_GRP
#define PARSE@CST_GRP_NUM                       PARSE@NUM_CST_GRP
#define PARSE@STR_CST:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,w@:A@[c@:],%1,%2,%5,%3,%4)       // const string:a[]
#define PARSE@CST_STR                           PARSE@STR_CST
#define PARSE@STR_CST_DEF:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,w@:A@[c@:b@:],%1,%2,%5,%3,%4)    // const string:a[] = "hi"
#define PARSE@CST_DEF_STR                       PARSE@STR_CST_DEF
#define PARSE@CST_STR_DEF                       PARSE@STR_CST_DEF
#define PARSE@DEF_CST_STR                       PARSE@STR_CST_DEF
#define PARSE@DEF_STR_CST                       PARSE@STR_CST_DEF
#define PARSE@STR_DEF_CST                       PARSE@STR_CST_DEF
#define PARSE@NUM_CST:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[c@:])       // const a
#define PARSE@CST_NUM                           PARSE@NUM_CST
#define PARSE@ARR:%8(%9,%0,%1,%2,%5,%3,%4)             PARSE@%8(%9,%0,a@:A@[],%2,%5,%3,%4)          // a[]
#define PARSE@ARR_TAG:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,a@:A@[t@:F@:A@[]],%2,%5,%3,%4)       // tag:a[]
#define PARSE@TAG_ARR                           PARSE@ARR_TAG
#define PARSE@ARR_GRP:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,a@:A@[t@:L@:A@[G@:x@:]],%2,%5,%3,%4)       // {tag1, tag2}:a[]
#define PARSE@GRP_ARR                           PARSE@ARR_GRP
#define PARSE@ARR_CST:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,a@:A@[c@:],%2,%5,%3,%4)       // const a[]
#define PARSE@CST_ARR                           PARSE@ARR_CST
#define PARSE@ARR_CST_TAG:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,a@:A@[c@:t@:F@:A@[]],%2,%5,%3,%4)    // const tag:a[]
#define PARSE@CST_TAG_ARR                       PARSE@ARR_CST_TAG
#define PARSE@CST_ARR_TAG                       PARSE@ARR_CST_TAG
#define PARSE@ARR_TAG_CST                       PARSE@ARR_CST_TAG
#define PARSE@TAG_CST_ARR                       PARSE@ARR_CST_TAG
#define PARSE@TAG_ARR_CST                       PARSE@ARR_CST_TAG
#define PARSE@NUM_CST_TAG_DEF:%8(%9,%0,%1,%2,%5,%3,%4) PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[c@:t@:F@:A@[]d@:]) // const tag:a = 5
#define PARSE@NUM_CST_DEF_TAG                   PARSE@NUM_CST_TAG_DEF
#define PARSE@NUM_DEF_CST_TAG                   PARSE@NUM_CST_TAG_DEF
#define PARSE@NUM_DEF_TAG_CST                   PARSE@NUM_CST_TAG_DEF
#define PARSE@NUM_TAG_CST_DEF                   PARSE@NUM_CST_TAG_DEF
#define PARSE@NUM_TAG_DEF_CST                   PARSE@NUM_CST_TAG_DEF
#define PARSE@CST_NUM_TAG_DEF                   PARSE@NUM_CST_TAG_DEF
#define PARSE@CST_NUM_DEF_TAG                   PARSE@NUM_CST_TAG_DEF
#define PARSE@DEF_NUM_CST_TAG                   PARSE@NUM_CST_TAG_DEF
#define PARSE@DEF_NUM_TAG_CST                   PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_NUM_CST_DEF                   PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_NUM_DEF_CST                   PARSE@NUM_CST_TAG_DEF
#define PARSE@CST_TAG_NUM_DEF                   PARSE@NUM_CST_TAG_DEF
#define PARSE@CST_DEF_NUM_TAG                   PARSE@NUM_CST_TAG_DEF
#define PARSE@DEF_CST_NUM_TAG                   PARSE@NUM_CST_TAG_DEF
#define PARSE@DEF_TAG_NUM_CST                   PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_CST_NUM_DEF                   PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_DEF_NUM_CST                   PARSE@NUM_CST_TAG_DEF
#define PARSE@CST_TAG_DEF_NUM                   PARSE@NUM_CST_TAG_DEF
#define PARSE@CST_DEF_TAG_NUM                   PARSE@NUM_CST_TAG_DEF
#define PARSE@DEF_CST_TAG_NUM                   PARSE@NUM_CST_TAG_DEF
#define PARSE@DEF_TAG_CST_NUM                   PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_CST_DEF_NUM                   PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_DEF_CST_NUM                   PARSE@NUM_CST_TAG_DEF
#define PARSE@ARR_CST_GRP:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,a@:A@[c@:t@:L@:A@[G@:x@:]],%2,%5,%3,%4)    // const {tag1, tag2}:a[]
#define PARSE@CST_GRP_ARR                       PARSE@ARR_CST_GRP
#define PARSE@CST_ARR_GRP                       PARSE@ARR_CST_GRP
#define PARSE@ARR_GRP_CST                       PARSE@ARR_CST_GRP
#define PARSE@GRP_CST_ARR                       PARSE@ARR_CST_GRP
#define PARSE@GRP_ARR_CST                       PARSE@ARR_CST_GRP
#define PARSE@NUM_CST_GRP_DEF:%8(%9,%0,%1,%2,%5,%3,%4) PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[c@:t@:L@:A@[G@:x@:]d@:]) // const {tag1, tag2}:a = 5
#define PARSE@NUM_CST_DEF_GRP                   PARSE@NUM_CST_GRP_DEF
#define PARSE@NUM_DEF_CST_GRP                   PARSE@NUM_CST_GRP_DEF
#define PARSE@NUM_DEF_GRP_CST                   PARSE@NUM_CST_GRP_DEF
#define PARSE@NUM_GRP_CST_DEF                   PARSE@NUM_CST_GRP_DEF
#define PARSE@NUM_GRP_DEF_CST                   PARSE@NUM_CST_GRP_DEF
#define PARSE@CST_NUM_GRP_DEF                   PARSE@NUM_CST_GRP_DEF
#define PARSE@CST_NUM_DEF_GRP                   PARSE@NUM_CST_GRP_DEF
#define PARSE@DEF_NUM_CST_GRP                   PARSE@NUM_CST_GRP_DEF
#define PARSE@DEF_NUM_GRP_CST                   PARSE@NUM_CST_GRP_DEF
#define PARSE@GRP_NUM_CST_DEF                   PARSE@NUM_CST_GRP_DEF
#define PARSE@GRP_NUM_DEF_CST                   PARSE@NUM_CST_GRP_DEF
#define PARSE@CST_GRP_NUM_DEF                   PARSE@NUM_CST_GRP_DEF
#define PARSE@CST_DEF_NUM_GRP                   PARSE@NUM_CST_GRP_DEF
#define PARSE@DEF_CST_NUM_GRP                   PARSE@NUM_CST_GRP_DEF
#define PARSE@DEF_GRP_NUM_CST                   PARSE@NUM_CST_GRP_DEF
#define PARSE@GRP_CST_NUM_DEF                   PARSE@NUM_CST_GRP_DEF
#define PARSE@GRP_DEF_NUM_CST                   PARSE@NUM_CST_GRP_DEF
#define PARSE@CST_GRP_DEF_NUM                   PARSE@NUM_CST_GRP_DEF
#define PARSE@CST_DEF_GRP_NUM                   PARSE@NUM_CST_GRP_DEF
#define PARSE@DEF_CST_GRP_NUM                   PARSE@NUM_CST_GRP_DEF
#define PARSE@DEF_GRP_CST_NUM                   PARSE@NUM_CST_GRP_DEF
#define PARSE@GRP_CST_DEF_NUM                   PARSE@NUM_CST_GRP_DEF
#define PARSE@GRP_DEF_CST_NUM                   PARSE@NUM_CST_GRP_DEF
#define PARSE@NUM_CST_DEF:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,%1,%2,%5,%3,p@:A@[c@:d@:])    // const a = 5
#define PARSE@CST_NUM_DEF                       PARSE@NUM_CST_DEF
#define PARSE@CST_DEF_NUM                       PARSE@NUM_CST_DEF
#define PARSE@DEF_CST_NUM                       PARSE@NUM_CST_DEF
#define PARSE@DEF_NUM_CST                       PARSE@NUM_CST_DEF
#define PARSE@NUM_DEF_CST                       PARSE@NUM_CST_DEF
#define PARSE@SPC:%8(%9,%0,%1,%2,%5,%3,%4)             PARSE@%8(%9,%0,%1,%2,o@:A@[],%3,%4)          // special:a<>
#define PARSE@SPC_CST:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,%1,%2,o@:A@[c@:],%3,%4)       // const special:a<>
#define PARSE@CST_SPC                           PARSE@SPC_CST

// Less short names of macros.
#define PARSE@ARRAY                    PARSE@ARR
#define PARSE@NUMBER_TAG               PARSE@NUM_TAG
#define PARSE@TAG_NUMBER               PARSE@NUM_TAG
#define PARSE@NUMBER_TAGGROUP               PARSE@NUM_GRP
#define PARSE@TAGGROUP_NUMBER               PARSE@NUM_GRP
#define PARSE@STRING                   PARSE@STR
#define PARSE@DEFAULT_STRING           PARSE@STR_DEF
#define PARSE@STRING_DEFAULT           PARSE@STR_DEF
#define PARSE@NUMBER                   PARSE@NUM
#define PARSE@TAG_ARRAY                PARSE@ARR_TAG
#define PARSE@ARRAY_TAG                PARSE@ARR_TAG
#define PARSE@NUMBER_TAG_DEFAULT       PARSE@NUM_TAG_DEF
#define PARSE@NUMBER_DEFAULT_TAG       PARSE@NUM_TAG_DEF
#define PARSE@TAG_NUMBER_DEFAULT       PARSE@NUM_TAG_DEF
#define PARSE@DEFAULT_NUMBER_TAG       PARSE@NUM_TAG_DEF
#define PARSE@TAG_DEFAULT_NUMBER       PARSE@NUM_TAG_DEF
#define PARSE@DEFAULT_TAG_NUMBER       PARSE@NUM_TAG_DEF
#define PARSE@TAGGROUP_ARRAY                PARSE@ARR_GRP
#define PARSE@ARRAY_TAGGROUP                PARSE@ARR_GRP
#define PARSE@NUMBER_TAGGROUP_DEFAULT       PARSE@NUM_GRP_DEF
#define PARSE@NUMBER_DEFAULT_TAGGROUP       PARSE@NUM_GRP_DEF
#define PARSE@TAGGROUP_NUMBER_DEFAULT       PARSE@NUM_GRP_DEF
#define PARSE@DEFAULT_NUMBER_TAGGROUP       PARSE@NUM_GRP_DEF
#define PARSE@TAGGROUP_DEFAULT_NUMBER       PARSE@NUM_GRP_DEF
#define PARSE@DEFAULT_TAGGROUP_NUMBER       PARSE@NUM_GRP_DEF
#define PARSE@NUMBER_DEFAULT           PARSE@NUM_DEF
#define PARSE@DEFAULT_NUMBER           PARSE@NUM_DEF
#define PARSE@REFERENCE                PARSE@REF
#define PARSE@TAG_REFERENCE            PARSE@REF_TAG
#define PARSE@REFERENCE_TAG            PARSE@REF_TAG
#define PARSE@TAGGROUP_REFERENCE            PARSE@REF_GRP
#define PARSE@REFERENCE_TAGGROUP            PARSE@REF_GRP
#define PARSE@DEFAULT_REFERENCE        PARSE@REF_DEF
#define PARSE@REFERENCE_DEFAULT        PARSE@REF_DEF
#define PARSE@TAG_REFERENCE_DEFAULT    PARSE@REF_TAG_DEF
#define PARSE@TAG_DEFAULT_REFERENCE    PARSE@REF_TAG_DEF
#define PARSE@REFERENCE_TAG_DEFAULT    PARSE@REF_TAG_DEF
#define PARSE@REFERENCE_DEFAULT_TAG    PARSE@REF_TAG_DEF
#define PARSE@DEFAULT_REFERENCE_TAG    PARSE@REF_TAG_DEF
#define PARSE@DEFAULT_TAG_REFERENCE    PARSE@REF_TAG_DEF
#define PARSE@TAGGROUP_REFERENCE_DEFAULT    PARSE@REF_GRP_DEF
#define PARSE@TAGGROUP_DEFAULT_REFERENCE    PARSE@REF_GRP_DEF
#define PARSE@REFERENCE_TAGGROUP_DEFAULT    PARSE@REF_GRP_DEF
#define PARSE@REFERENCE_DEFAULT_TAGGROUP    PARSE@REF_GRP_DEF
#define PARSE@DEFAULT_REFERENCE_TAGGROUP    PARSE@REF_GRP_DEF
#define PARSE@DEFAULT_TAGGROUP_REFERENCE    PARSE@REF_GRP_DEF
#define PARSE@VARARG                   PARSE@EXT
#define PARSE@VARARG_TAG               PARSE@EXT_TAG
#define PARSE@TAG_VARARG               PARSE@EXT_TAG
#define PARSE@VARARG_TAGGROUP               PARSE@EXT_GRP
#define PARSE@TAGGROUP_VARARG               PARSE@EXT_GRP
#define PARSE@CONST_ARRAY              PARSE@ARR_CST
#define PARSE@ARRAY_CONST              PARSE@ARR_CST
#define PARSE@NUMBER_CONST_TAG         PARSE@NUM_CST_TAG
#define PARSE@NUMBER_TAG_CONST         PARSE@NUM_CST_TAG
#define PARSE@CONST_NUMBER_TAG         PARSE@NUM_CST_TAG
#define PARSE@TAG_NUMBER_CONST         PARSE@NUM_CST_TAG
#define PARSE@CONST_TAG_NUMBER         PARSE@NUM_CST_TAG
#define PARSE@TAG_CONST_NUMBER         PARSE@NUM_CST_TAG
#define PARSE@NUMBER_CONST_TAGGROUP         PARSE@NUM_CST_GRP
#define PARSE@NUMBER_TAGGROUP_CONST         PARSE@NUM_CST_GRP
#define PARSE@CONST_NUMBER_TAGGROUP         PARSE@NUM_CST_GRP
#define PARSE@TAGGROUP_NUMBER_CONST         PARSE@NUM_CST_GRP
#define PARSE@CONST_TAGGROUP_NUMBER         PARSE@NUM_CST_GRP
#define PARSE@TAGGROUP_CONST_NUMBER         PARSE@NUM_CST_GRP
#define PARSE@CONST_STRING             PARSE@STR_CST
#define PARSE@STRING_CONST             PARSE@STR_CST
#define PARSE@CONST_DEFAULT_STRING     PARSE@STR_CST_DEF
#define PARSE@CONST_STRING_DEFAULT     PARSE@STR_CST_DEF
#define PARSE@DEFAULT_CONST_STRING     PARSE@STR_CST_DEF
#define PARSE@DEFAULT_STRING_CONST     PARSE@STR_CST_DEF
#define PARSE@STRING_CONST_DEFAULT     PARSE@STR_CST_DEF
#define PARSE@STRING_DEFAULT_CONST     PARSE@STR_CST_DEF
#define PARSE@CONST_NUMBER             PARSE@NUM_CST
#define PARSE@NUMBER_CONST             PARSE@NUM_CST
#define PARSE@CONST_TAG_ARRAY          PARSE@ARR_CST_TAG
#define PARSE@CONST_ARRAY_TAG          PARSE@ARR_CST_TAG
#define PARSE@ARRAY_CONST_TAG          PARSE@ARR_CST_TAG
#define PARSE@ARRAY_TAG_CONST          PARSE@ARR_CST_TAG
#define PARSE@TAG_CONST_ARRAY          PARSE@ARR_CST_TAG
#define PARSE@TAG_ARRAY_CONST          PARSE@ARR_CST_TAG
#define PARSE@NUMBER_CONST_TAG_DEFAULT PARSE@NUM_CST_TAG_DEF
#define PARSE@NUMBER_CONST_DEFAULT_TAG PARSE@NUM_CST_TAG_DEF
#define PARSE@NUMBER_DEFAULT_CONST_TAG PARSE@NUM_CST_TAG_DEF
#define PARSE@NUMBER_DEFAULT_TAG_CONST PARSE@NUM_CST_TAG_DEF
#define PARSE@NUMBER_TAG_CONST_DEFAULT PARSE@NUM_CST_TAG_DEF
#define PARSE@NUMBER_TAG_DEFAULT_CONST PARSE@NUM_CST_TAG_DEF
#define PARSE@CONST_NUMBER_TAG_DEFAULT PARSE@NUM_CST_TAG_DEF
#define PARSE@CONST_NUMBER_DEFAULT_TAG PARSE@NUM_CST_TAG_DEF
#define PARSE@DEFAULT_NUMBER_CONST_TAG PARSE@NUM_CST_TAG_DEF
#define PARSE@DEFAULT_NUMBER_TAG_CONST PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_NUMBER_CONST_DEFAULT PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_NUMBER_DEFAULT_CONST PARSE@NUM_CST_TAG_DEF
#define PARSE@CONST_TAG_NUMBER_DEFAULT PARSE@NUM_CST_TAG_DEF
#define PARSE@CONST_DEFAULT_NUMBER_TAG PARSE@NUM_CST_TAG_DEF
#define PARSE@DEFAULT_CONST_NUMBER_TAG PARSE@NUM_CST_TAG_DEF
#define PARSE@DEFAULT_TAG_NUMBER_CONST PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_CONST_NUMBER_DEFAULT PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_DEFAULT_NUMBER_CONST PARSE@NUM_CST_TAG_DEF
#define PARSE@CONST_TAG_DEFAULT_NUMBER PARSE@NUM_CST_TAG_DEF
#define PARSE@CONST_DEFAULT_TAG_NUMBER PARSE@NUM_CST_TAG_DEF
#define PARSE@DEFAULT_CONST_TAG_NUMBER PARSE@NUM_CST_TAG_DEF
#define PARSE@DEFAULT_TAG_CONST_NUMBER PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_CONST_DEFAULT_NUMBER PARSE@NUM_CST_TAG_DEF
#define PARSE@TAG_DEFAULT_CONST_NUMBER PARSE@NUM_CST_TAG_DEF
#define PARSE@CONST_TAGGROUP_ARRAY          PARSE@ARR_CST_GRP
#define PARSE@CONST_ARRAY_TAGGROUP          PARSE@ARR_CST_GRP
#define PARSE@ARRAY_CONST_TAGGROUP          PARSE@ARR_CST_GRP
#define PARSE@ARRAY_TAGGROUP_CONST          PARSE@ARR_CST_GRP
#define PARSE@TAGGROUP_CONST_ARRAY          PARSE@ARR_CST_GRP
#define PARSE@TAGGROUP_ARRAY_CONST          PARSE@ARR_CST_GRP
#define PARSE@NUMBER_CONST_TAGGROUP_DEFAULT PARSE@NUM_CST_GRP_DEF
#define PARSE@NUMBER_CONST_DEFAULT_TAGGROUP PARSE@NUM_CST_GRP_DEF
#define PARSE@NUMBER_DEFAULT_CONST_TAGGROUP PARSE@NUM_CST_GRP_DEF
#define PARSE@NUMBER_DEFAULT_TAGGROUP_CONST PARSE@NUM_CST_GRP_DEF
#define PARSE@NUMBER_TAGGROUP_CONST_DEFAULT PARSE@NUM_CST_GRP_DEF
#define PARSE@NUMBER_TAGGROUP_DEFAULT_CONST PARSE@NUM_CST_GRP_DEF
#define PARSE@CONST_NUMBER_TAGGROUP_DEFAULT PARSE@NUM_CST_GRP_DEF
#define PARSE@CONST_NUMBER_DEFAULT_TAGGROUP PARSE@NUM_CST_GRP_DEF
#define PARSE@DEFAULT_NUMBER_CONST_TAGGROUP PARSE@NUM_CST_GRP_DEF
#define PARSE@DEFAULT_NUMBER_TAGGROUP_CONST PARSE@NUM_CST_GRP_DEF
#define PARSE@TAGGROUP_NUMBER_CONST_DEFAULT PARSE@NUM_CST_GRP_DEF
#define PARSE@TAGGROUP_NUMBER_DEFAULT_CONST PARSE@NUM_CST_GRP_DEF
#define PARSE@CONST_TAGGROUP_NUMBER_DEFAULT PARSE@NUM_CST_GRP_DEF
#define PARSE@CONST_DEFAULT_NUMBER_TAGGROUP PARSE@NUM_CST_GRP_DEF
#define PARSE@DEFAULT_CONST_NUMBER_TAGGROUP PARSE@NUM_CST_GRP_DEF
#define PARSE@DEFAULT_TAGGROUP_NUMBER_CONST PARSE@NUM_CST_GRP_DEF
#define PARSE@TAGGROUP_CONST_NUMBER_DEFAULT PARSE@NUM_CST_GRP_DEF
#define PARSE@TAGGROUP_DEFAULT_NUMBER_CONST PARSE@NUM_CST_GRP_DEF
#define PARSE@CONST_TAGGROUP_DEFAULT_NUMBER PARSE@NUM_CST_GRP_DEF
#define PARSE@CONST_DEFAULT_TAGGROUP_NUMBER PARSE@NUM_CST_GRP_DEF
#define PARSE@DEFAULT_CONST_TAGGROUP_NUMBER PARSE@NUM_CST_GRP_DEF
#define PARSE@DEFAULT_TAGGROUP_CONST_NUMBER PARSE@NUM_CST_GRP_DEF
#define PARSE@TAGGROUP_CONST_DEFAULT_NUMBER PARSE@NUM_CST_GRP_DEF
#define PARSE@TAGGROUP_DEFAULT_CONST_NUMBER PARSE@NUM_CST_GRP_DEF
#define PARSE@CONST_NUMBER_DEFAULT     PARSE@NUM_CST_DEF
#define PARSE@CONST_DEFAULT_NUMBER     PARSE@NUM_CST_DEF
#define PARSE@DEFAULT_CONST_NUMBER     PARSE@NUM_CST_DEF
#define PARSE@DEFAULT_NUMBER_CONST     PARSE@NUM_CST_DEF
#define PARSE@NUMBER_CONST_DEFAULT     PARSE@NUM_CST_DEF
#define PARSE@NUMBER_DEFAULT_CONST     PARSE@NUM_CST_DEF
#define PARSE@SPECIAL                  PARSE@SPC
#define PARSE@SPECIAL_CONST            PARSE@SPC_CST
#define PARSE@CONST_SPECIAL            PARSE@SPC_CST

// Multi-dimensional arrays.
#define PARSE@ARR_MUL:%8(%9,%0,%1,%2,%5,%3,%4)         PARSE@%8(%9,%0,a@:A@[f@:],%2,%5,%3,%4)       // a[][]
#define PARSE@MUL_ARR                           PARSE@ARR_MUL
#define PARSE@ARR_TAG_MUL:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,a@:A@[f@:t@:F@:A@[]],%2,%5,%3,%4)    // tag:a[][]
#define PARSE@TAG_MUL_ARR                       PARSE@ARR_TAG_MUL
#define PARSE@TAG_ARR_MUL                       PARSE@ARR_TAG_MUL
#define PARSE@ARR_MUL_TAG                       PARSE@ARR_TAG_MUL
#define PARSE@MUL_ARR_TAG                       PARSE@ARR_TAG_MUL
#define PARSE@MUL_TAG_ARR                       PARSE@ARR_TAG_MUL
#define PARSE@ARR_GRP_MUL:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,a@:A@[f@:t@:L@:A@[G@:x@:]],%2,%5,%3,%4)    // {tag1, tag2}:a[][]
#define PARSE@GRP_MUL_ARR                       PARSE@ARR_GRP_MUL
#define PARSE@GRP_ARR_MUL                       PARSE@ARR_GRP_MUL
#define PARSE@ARR_MUL_GRP                       PARSE@ARR_GRP_MUL
#define PARSE@MUL_ARR_GRP                       PARSE@ARR_GRP_MUL
#define PARSE@MUL_GRP_ARR                       PARSE@ARR_GRP_MUL
#define PARSE@ARR_CST_MUL:%8(%9,%0,%1,%2,%5,%3,%4)     PARSE@%8(%9,%0,a@:A@[f@:c@:],%2,%5,%3,%4)    // const a[][]
#define PARSE@CST_MUL_ARR                       PARSE@ARR_CST_MUL
#define PARSE@CST_ARR_MUL                       PARSE@ARR_CST_MUL
#define PARSE@ARR_MUL_CST                       PARSE@ARR_CST_MUL
#define PARSE@MUL_CST_ARR                       PARSE@ARR_CST_MUL
#define PARSE@MUL_ARR_CST                       PARSE@ARR_CST_MUL
#define PARSE@ARR_CST_TAG_MUL:%8(%9,%0,%1,%2,%5,%3,%4) PARSE@%8(%9,%0,a@:A@[f@:c@:t@:F@:A@[]],%2,%5,%3,%4) // const tag:a[][]
#define PARSE@CST_TAG_ARR_MUL                   PARSE@ARR_CST_TAG_MUL
#define PARSE@CST_TAG_MUL_ARR                   PARSE@ARR_CST_TAG_MUL
#define PARSE@CST_ARR_TAG_MUL                   PARSE@ARR_CST_TAG_MUL
#define PARSE@CST_ARR_MUL_TAG                   PARSE@ARR_CST_TAG_MUL
#define PARSE@CST_MUL_ARR_TAG                   PARSE@ARR_CST_TAG_MUL
#define PARSE@CST_MUL_TAG_ARR                   PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_CST_ARR_MUL                   PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_CST_MUL_ARR                   PARSE@ARR_CST_TAG_MUL
#define PARSE@ARR_CST_MUL_TAG                   PARSE@ARR_CST_TAG_MUL
#define PARSE@MUL_CST_ARR_TAG                   PARSE@ARR_CST_TAG_MUL
#define PARSE@MUL_CST_TAG_ARR                   PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_ARR_CST_MUL                   PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_MUL_CST_ARR                   PARSE@ARR_CST_TAG_MUL
#define PARSE@ARR_TAG_CST_MUL                   PARSE@ARR_CST_TAG_MUL
#define PARSE@ARR_MUL_CST_TAG                   PARSE@ARR_CST_TAG_MUL
#define PARSE@MUL_ARR_CST_TAG                   PARSE@ARR_CST_TAG_MUL
#define PARSE@MUL_TAG_CST_ARR                   PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_ARR_MUL_CST                   PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_MUL_ARR_CST                   PARSE@ARR_CST_TAG_MUL
#define PARSE@ARR_TAG_MUL_CST                   PARSE@ARR_CST_TAG_MUL
#define PARSE@ARR_MUL_TAG_CST                   PARSE@ARR_CST_TAG_MUL
#define PARSE@MUL_ARR_TAG_CST                   PARSE@ARR_CST_TAG_MUL
#define PARSE@MUL_TAG_ARR_CST                   PARSE@ARR_CST_TAG_MUL
#define PARSE@ARR_CST_GRP_MUL:%8(%9,%0,%1,%2,%5,%3,%4) PARSE@%8(%9,%0,a@:A@[f@:c@:t@:L@:A@[G@:x@:]],%2,%5,%3,%4) // const {tag1, tag2}:a[][]
#define PARSE@CST_GRP_ARR_MUL                   PARSE@ARR_CST_GRP_MUL
#define PARSE@CST_GRP_MUL_ARR                   PARSE@ARR_CST_GRP_MUL
#define PARSE@CST_ARR_GRP_MUL                   PARSE@ARR_CST_GRP_MUL
#define PARSE@CST_ARR_MUL_GRP                   PARSE@ARR_CST_GRP_MUL
#define PARSE@CST_MUL_ARR_GRP                   PARSE@ARR_CST_GRP_MUL
#define PARSE@CST_MUL_GRP_ARR                   PARSE@ARR_CST_GRP_MUL
#define PARSE@GRP_CST_ARR_MUL                   PARSE@ARR_CST_GRP_MUL
#define PARSE@GRP_CST_MUL_ARR                   PARSE@ARR_CST_GRP_MUL
#define PARSE@ARR_CST_MUL_GRP                   PARSE@ARR_CST_GRP_MUL
#define PARSE@MUL_CST_ARR_GRP                   PARSE@ARR_CST_GRP_MUL
#define PARSE@MUL_CST_GRP_ARR                   PARSE@ARR_CST_GRP_MUL
#define PARSE@GRP_ARR_CST_MUL                   PARSE@ARR_CST_GRP_MUL
#define PARSE@GRP_MUL_CST_ARR                   PARSE@ARR_CST_GRP_MUL
#define PARSE@ARR_GRP_CST_MUL                   PARSE@ARR_CST_GRP_MUL
#define PARSE@ARR_MUL_CST_GRP                   PARSE@ARR_CST_GRP_MUL
#define PARSE@MUL_ARR_CST_GRP                   PARSE@ARR_CST_GRP_MUL
#define PARSE@MUL_GRP_CST_ARR                   PARSE@ARR_CST_GRP_MUL
#define PARSE@GRP_ARR_MUL_CST                   PARSE@ARR_CST_GRP_MUL
#define PARSE@GRP_MUL_ARR_CST                   PARSE@ARR_CST_GRP_MUL
#define PARSE@ARR_GRP_MUL_CST                   PARSE@ARR_CST_GRP_MUL
#define PARSE@ARR_MUL_GRP_CST                   PARSE@ARR_CST_GRP_MUL
#define PARSE@MUL_ARR_GRP_CST                   PARSE@ARR_CST_GRP_MUL
#define PARSE@MUL_GRP_ARR_CST                   PARSE@ARR_CST_GRP_MUL
#define PARSE@ARRAY_MULTI           PARSE@ARR_MUL
#define PARSE@MULTI_ARRAY           PARSE@ARR_MUL
#define PARSE@TAG_ARRAY_MULTI       PARSE@ARR_TAG_MUL
#define PARSE@TAG_MULTI_ARRAY       PARSE@ARR_TAG_MUL
#define PARSE@ARRAY_TAG_MULTI       PARSE@ARR_TAG_MUL
#define PARSE@ARRAY_MULTI_TAG       PARSE@ARR_TAG_MUL
#define PARSE@MULTI_ARRAY_TAG       PARSE@ARR_TAG_MUL
#define PARSE@MULTI_TAG_ARRAY       PARSE@ARR_TAG_MUL
#define PARSE@TAGGROUP_ARRAY_MULTI       PARSE@ARR_GRP_MUL
#define PARSE@TAGGROUP_MULTI_ARRAY       PARSE@ARR_GRP_MUL
#define PARSE@ARRAY_TAGGROUP_MULTI       PARSE@ARR_GRP_MUL
#define PARSE@ARRAY_MULTI_TAGGROUP       PARSE@ARR_GRP_MUL
#define PARSE@MULTI_ARRAY_TAGGROUP       PARSE@ARR_GRP_MUL
#define PARSE@MULTI_TAGGROUP_ARRAY       PARSE@ARR_GRP_MUL
#define PARSE@CONST_MULTI_ARRAY     PARSE@ARR_CST_MUL
#define PARSE@CONST_ARRAY_MULTI     PARSE@ARR_CST_MUL
#define PARSE@ARRAY_CONST_MULTI     PARSE@ARR_CST_MUL
#define PARSE@ARRAY_MULTI_CONST     PARSE@ARR_CST_MUL
#define PARSE@MULTI_CONST_ARRAY     PARSE@ARR_CST_MUL
#define PARSE@MULTI_ARRAY_CONST     PARSE@ARR_CST_MUL
#define PARSE@CONST_TAG_ARRAY_MULTI PARSE@ARR_CST_TAG_MUL
#define PARSE@CONST_TAG_MULTI_ARRAY PARSE@ARR_CST_TAG_MUL
#define PARSE@CONST_ARRAY_TAG_MULTI PARSE@ARR_CST_TAG_MUL
#define PARSE@CONST_ARRAY_MULTI_TAG PARSE@ARR_CST_TAG_MUL
#define PARSE@CONST_MULTI_ARRAY_TAG PARSE@ARR_CST_TAG_MUL
#define PARSE@CONST_MULTI_TAG_ARRAY PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_CONST_ARRAY_MULTI PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_CONST_MULTI_ARRAY PARSE@ARR_CST_TAG_MUL
#define PARSE@ARRAY_CONST_TAG_MULTI PARSE@ARR_CST_TAG_MUL
#define PARSE@ARRAY_CONST_MULTI_TAG PARSE@ARR_CST_TAG_MUL
#define PARSE@MULTI_CONST_ARRAY_TAG PARSE@ARR_CST_TAG_MUL
#define PARSE@MULTI_CONST_TAG_ARRAY PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_ARRAY_CONST_MULTI PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_MULTI_CONST_ARRAY PARSE@ARR_CST_TAG_MUL
#define PARSE@ARRAY_TAG_CONST_MULTI PARSE@ARR_CST_TAG_MUL
#define PARSE@ARRAY_MULTI_CONST_TAG PARSE@ARR_CST_TAG_MUL
#define PARSE@MULTI_ARRAY_CONST_TAG PARSE@ARR_CST_TAG_MUL
#define PARSE@MULTI_TAG_CONST_ARRAY PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_ARRAY_MULTI_CONST PARSE@ARR_CST_TAG_MUL
#define PARSE@TAG_MULTI_ARRAY_CONST PARSE@ARR_CST_TAG_MUL
#define PARSE@ARRAY_TAG_MULTI_CONST PARSE@ARR_CST_TAG_MUL
#define PARSE@ARRAY_MULTI_TAG_CONST PARSE@ARR_CST_TAG_MUL
#define PARSE@MULTI_ARRAY_TAG_CONST PARSE@ARR_CST_TAG_MUL
#define PARSE@MULTI_TAG_ARRAY_CONST PARSE@ARR_CST_TAG_MUL
#define PARSE@CONST_TAGGROUP_ARRAY_MULTI PARSE@ARR_CST_GRP_MUL
#define PARSE@CONST_TAGGROUP_MULTI_ARRAY PARSE@ARR_CST_GRP_MUL
#define PARSE@CONST_ARRAY_TAGGROUP_MULTI PARSE@ARR_CST_GRP_MUL
#define PARSE@CONST_ARRAY_MULTI_TAGGROUP PARSE@ARR_CST_GRP_MUL
#define PARSE@CONST_MULTI_ARRAY_TAGGROUP PARSE@ARR_CST_GRP_MUL
#define PARSE@CONST_MULTI_TAGGROUP_ARRAY PARSE@ARR_CST_GRP_MUL
#define PARSE@TAGGROUP_CONST_ARRAY_MULTI PARSE@ARR_CST_GRP_MUL
#define PARSE@TAGGROUP_CONST_MULTI_ARRAY PARSE@ARR_CST_GRP_MUL
#define PARSE@ARRAY_CONST_TAGGROUP_MULTI PARSE@ARR_CST_GRP_MUL
#define PARSE@ARRAY_CONST_MULTI_TAGGROUP PARSE@ARR_CST_GRP_MUL
#define PARSE@MULTI_CONST_ARRAY_TAGGROUP PARSE@ARR_CST_GRP_MUL
#define PARSE@MULTI_CONST_TAGGROUP_ARRAY PARSE@ARR_CST_GRP_MUL
#define PARSE@TAGGROUP_ARRAY_CONST_MULTI PARSE@ARR_CST_GRP_MUL
#define PARSE@TAGGROUP_MULTI_CONST_ARRAY PARSE@ARR_CST_GRP_MUL
#define PARSE@ARRAY_TAGGROUP_CONST_MULTI PARSE@ARR_CST_GRP_MUL
#define PARSE@ARRAY_MULTI_CONST_TAGGROUP PARSE@ARR_CST_GRP_MUL
#define PARSE@MULTI_ARRAY_CONST_TAGGROUP PARSE@ARR_CST_GRP_MUL
#define PARSE@MULTI_TAGGROUP_CONST_ARRAY PARSE@ARR_CST_GRP_MUL
#define PARSE@TAGGROUP_ARRAY_MULTI_CONST PARSE@ARR_CST_GRP_MUL
#define PARSE@TAGGROUP_MULTI_ARRAY_CONST PARSE@ARR_CST_GRP_MUL
#define PARSE@ARRAY_TAGGROUP_MULTI_CONST PARSE@ARR_CST_GRP_MUL
#define PARSE@ARRAY_MULTI_TAGGROUP_CONST PARSE@ARR_CST_GRP_MUL
#define PARSE@MULTI_ARRAY_TAGGROUP_CONST PARSE@ARR_CST_GRP_MUL
#define PARSE@MULTI_TAGGROUP_ARRAY_CONST PARSE@ARR_CST_GRP_MUL

