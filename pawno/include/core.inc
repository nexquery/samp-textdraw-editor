/* Core functions
 *
 * (c) Copyright 1998-2005, ITB CompuPhase
 * This file is provided as is (no warranties).
 */
#if defined _core_included
	#endinput
#endif
#define _core_included
#pragma library Core


/// <summary>Returns the amount of memory available for the heap/stack in bytes.</summary>
/// <remarks>In absence of recursion, the pawn parser can also give an estimate of the required stack/heap space.</remarks>
/// <returns>The free space on the heap in bytes. The stack and the heap occupy a shared memory area, so this value indicates the number of bytes that is left for either the stack or the heap.</returns>
native heapspace();

/// <summary>This function returns the ID of a public function by its name.</summary>
/// <param name="name">The name of the public function to get the ID of</param>
/// <seealso name="CallLocalFunction"/>
/// <seealso name="CallRemoteFunction"/>
/// <returns>The ID of the function (IDs start at <b><c>0</c></b>). <b><c>-1</c></b> if the function doesn't exist.</returns>
native funcidx(const name[]);

/// <summary>Get the number of arguments passed to a function.</summary>
/// <seealso name="getarg"/>
/// <seealso name="setarg"/>
/// <returns>The number of arguments passed.</returns>
native numargs();

/// <summary>Get an argument that was passed to a function.</summary>
/// <param name="arg">The argument sequence number. Use <b><c>0</c></b> for first argument</param>
/// <param name="index">The index (in case the argument is an array) (optional=<b><c>0</c></b>)</param>
/// <seealso name="numargs"/>
/// <seealso name="setarg"/>
/// <returns>The value of the argument.</returns>
native getarg(arg, index=0);

/// <summary>Set an argument that was passed to a function.</summary>
/// <param name="arg">The argument sequence number. Use <b><c>0</c></b> for first argument</param>
/// <param name="index">The index (if the argument is an array) (optional=<b><c>0</c></b>)</param>
/// <param name="value">The value to set the argument to</param>
/// <seealso name="getarg"/>
/// <seealso name="numargs"/>
/// <returns><b><c>1</c></b> on success and <b><c>0</c></b> if the argument or the index are invalid.</returns>
native setarg(arg, index=0, value);

/// <summary>This function changes a single character to lowercase.</summary>
/// <param name="c">The character to change to lowercase</param>
/// <remarks>Support for accented characters is platform-dependent.</remarks>
/// <returns>The lower case variant of the input character, if one exists, or the unchanged character code of c if the letter c has no lower case equivalent.</returns>
native tolower(c);

/// <summary>This function changes a single character to uppercase.</summary>
/// <param name="c">The character to change to uppercase</param>
/// <remarks>Support for accented characters is platform-dependent.</remarks>
/// <returns>The upper case variant of the input character, if one exists, or the unchanged character code of c if the letter c has no upper case equivalent.</returns>
native toupper(c);

/// <summary>Swap bytes in a cell</summary>
/// <param name="c">The value for which to swap the bytes.</param>
/// <returns>A value where the bytes are swapped (the lowest byte becomes the highest byte)</returns>
native swapchars(c);

/// <summary>Get a pseudo-random number.</summary>
/// <param name="max">The range of values (from <b><c>0</c></b> to <b><c>max-1</c></b>) that can be returned</param>
/// <remarks>Using a value smaller than <b><c>1</c></b> gives weird values.</remarks>
/// <remarks>The standard random number generator of pawn is likely a linear congruential pseudo-random number generator with a range and a period of 2^31. Linear congruential pseudo-random number generators suffer from serial correlation (especially in the low bits) and it is unsuitable for applications that require high-quality random numbers.</remarks>
/// <returns>A random number ranging from <b><c>0</c></b> to <b><c>max-1</c></b>.</returns>
native random(max);

/// <summary>Return the lowest of two numbers</summary>
/// <param name="value1">The two values for which to find the lowest number</param>
/// <param name="value2">The two values for which to find the lowest number</param>
/// <seealso name="clamp"/>
/// <seealso name="max"/>
/// <returns>The lower value of value1 and value2</returns>
native min(value1, value2);

/// <summary>Return the highest of two numbers</summary>
/// <param name="value1">The two values for which to find the highest number</param>
/// <param name="value2">The two values for which to find the highest number</param>
/// <seealso name="clamp"/>
/// <seealso name="min"/>
/// <returns>The higher value of value1 and value2</returns>
native max(value1, value2);

/// <summary>Force a value to be inside a range.</summary>
/// <param name="value">The value to force in a range</param>
/// <param name="min">The low bound of the range (optional=<b><c>cellmin</c></b>)</param>
/// <param name="max">The high bound of the range (optional=<b><c>cellmax</c></b>)</param>
/// <returns>value, if it is in the range min–max, min, if value is lower than min or max, if value is higher than max.</returns>
native clamp(value, min=cellmin, max=cellmax);

/// <summary>Get a specific property from the memory, the string is returned as a packed string!.</summary>
/// <param name="id">The <a href="http://en.wikipedia.org/wiki/Virtual_machine">virtual machine</a> to use, you should keep this zero (optional=<b><c>0</c></b>)</param>
/// <param name="name">The property's name, you should keep this "" (optional=<b><c>""</c></b>)</param>
/// <param name="value">The property's unique ID, Use the hash-function to calculate it from a string (optional=<b><c>cellmin</c></b>)</param>
/// <param name="string">The variable to store the result in, passed by reference (optional=<b><c>""</c></b>)</param>
/// <seealso name="Setproperty"/>
/// <seealso name="Deleteproperty"/>
/// <seealso name="Existproperty"/>
/// <returns>The value of a property when the name is passed in; fills in the string argument when the value is passed in. If the property does not exist, this function returns zero.</returns>
native getproperty(id=0, const name[]="", value=cellmin, string[]="");

/// <summary>Add a new property or change an existing property.</summary>
/// <param name="id">The virtual machine to use, you should keep this zero (optional=<b><c>0</c></b>)</param>
/// <param name="name">Used in combination with value when storing integers; don't use this if you want to store a string(optional=<b><c>""</c></b>)</param>
/// <param name="value">The integer value to store or the property's unique ID if storing a string. Use the hash-function to calculate it from a string (optional=<b><c>cellmin</c></b>)</param>
/// <param name="string">The value of the property, as a string. Don't use this if you want to store an integer (optional=<b><c>""</c></b>)</param>
/// <seealso name="Getproperty"/>
/// <seealso name="Deleteproperty"/>
/// <seealso name="Existproperty"/>
native setproperty(id=0, const name[]="", value=cellmin, const string[]="");

/// <summary>Delete an earlier set property (<a href="#setproperty">setproperty</a>).</summary>
/// <param name="id">The <a href="http://en.wikipedia.org/wiki/Virtual_machine">virtual machine</a> to use. You should keep this as zero (optional=<b><c>0</c></b>)</param>
/// <param name="name">The property's name, you should keep this blank (optional=<b><c>""</c></b>)</param>
/// <param name="value">The property's unique ID. Use the hash-function to calculate it from a string (optional=<b><c>cellmin</c></b>)</param>
/// <seealso name="Setproperty"/>
/// <seealso name="Getproperty"/>
/// <seealso name="Existproperty"/>
/// <returns>The value of the property. If the property does not exist, the function returns <b><c>0</c></b>.</returns>
native deleteproperty(id=0, const name[]="", value=cellmin);

/// <summary>Check if a property exist.</summary>
/// <param name="id">The <a href="http://en.wikipedia.org/wiki/Virtual_machine">virtual machine</a> to use, you should keep this zero (optional=<b><c>0</c></b>)</param>
/// <param name="name">The property's name, you should keep this (optional=<b><c>""</c></b>)</param>
/// <param name="value">The property's unique ID. Use the hash-function to calculate it from a string (optional=<b><c>cellmin</c></b>)</param>
/// <seealso name="Setproperty"/>
/// <seealso name="Getproperty"/>
/// <seealso name="Deleteproperty"/>
/// <returns><b><c>1</c></b> if the property exists and <b><c>0</c></b> otherwise.</returns>
native existproperty(id=0, const name[]="", value=cellmin);

