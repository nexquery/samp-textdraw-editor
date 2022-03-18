/* File input/output functions
 *
 * (c) Copyright 2004-2005, ITB CompuPhase
 * This file is provided as is (no warranties).
 */
#if defined _file_included
	#endinput
#endif
#define _file_included
#pragma library File

enum filemode
{
	io_read,            /* file must exist */
	io_write,           /* creates a new file */
	io_readwrite,       /* opens an existing file, or creates a new file */
	io_append,          /* appends to file (write-only) */
}

enum seek_whence
{
	seek_start,
	seek_current,
	seek_end,
}

const EOF = -1;

/// <summary>Open a file (to read from or write to).</summary>
/// <param name="name">The path to the file to open (if just a filename is specified, it will open the file with the name specified in the 'scriptfiles' folder)</param>
/// <param name="mode">The mode to open the file with, see below (optional=<b><c>io_readwrite</c></b>)</param>
/// <remarks>This function can't access files outside the 'scriptfiles' folder!</remarks>
/// <remarks>If you use <a href="#io_read">io_read</a> and the file doesn't exist, it will return a <b><c>NULL</c></b> reference. Using <b>invalid references</b> on file functions will <b>crash</b> your server!</remarks>
/// <remarks>
///   <b>Modes:</b><p/>
///   <ul>
///     <li><b><c>io_read</c></b> - reads from the file.</li>
///     <li><b><c>io_write</c></b> - write in the file, or create the file if it does not exist. Erases all existing contents.</li>
///     <li><b><c>io_readwrite</c></b> - reads the file or creates it if it doesn't already exist.</li>
///     <li><b><c>io_append</c></b> - appends (adds) to file, write-only. If the file does not exist, it is created.</li>
///   </ul>
/// </remarks>
/// <returns>Returns the file handle. This handle is used for reading and writing. <b><c>0</c></b> if failed to open file.</returns>
native File:fopen(const name[], filemode: mode = io_readwrite);

/// <summary>Closes a file. Files should always be closed when the script no longer needs them (after reading/writing).</summary>
/// <param name="handle">The file handle to close. Returned by <a href="#fopen">fopen</a></param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
/// <returns>
///   <b><c>true</c></b>: The function executed successfully.<p/>
///   <b><c>false</c></b>: The function failed to execute. The file could not be closed. It may already be closed.
/// </returns>
native bool:fclose(File: handle);

/// <summary>Creates a file in the "tmp", "temp" or root directory with random name for reading and writing. The file is deleted after <a href="#fclose">fclose</a> is used on the file.</summary>
/// <remarks>This function can crash the server when the right directory isn't created.</remarks>
/// <returns>The temporary file handle. <b><c>0</c></b> if failed.</returns>
native File:ftemp();

/// <summary>Delete a file.</summary>
/// <param name="name">The <b>path</b> of the file to delete. (NOTE: NOT a file handle)</param>
/// <remarks>The file path must be valid.</remarks>
/// <remarks>Files that are currently open (<a href="#fopen">fopen</a>) must be closed first (<a href="#fclose">fclose</a>) to be deleted.</remarks>
/// <returns>
///   <b><c>true</c></b>: The function executed successfully.<p/>
///   <b><c>false</c></b>: The function failed to execute. The file doesn't exist, or you don't have permission to delete it.
/// </returns>
native bool:fremove(const name[]);

/// <summary>Write text into a file.</summary>
/// <param name="handle">The handle of the file to write to (returned by <a href="#fopen">fopen</a>)</param>
/// <param name="string">The string of text to write in to the file</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
/// <remarks>This functions writes to the file in UTF-8, which does not support some localized language symbols.</remarks>
/// <remarks>This function doesn't support <a href="#strpack">packed strings</a>.</remarks>
/// <returns>The length of the written string as an integer.</returns>
native fwrite(File: handle, const string[]);

/// <summary>Read a single line from a file.</summary>
/// <param name="handle">The handle of the file to read from (returned by <a href="#fopen">fopen</a>)</param>
/// <param name="string">A string array to store the read text in, passed by reference</param>
/// <param name="size">The number of bytes to read (optional=<b><c>sizeof string</c></b>)</param>
/// <param name="pack">Should the string be packed? (optional=<b><c>false</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
/// <returns>The length of <b>string</b> (the read text) as an integer.</returns>
native fread(File: handle, string[], size = sizeof string, bool: pack = false);

/// <summary>Write one character to a file.</summary>
/// <param name="handle">The File handle to use, earlier opened by <a href="#fopen">fopen</a></param>
/// <param name="value">The character to write into the file</param>
/// <param name="utf8">If true, write in UTF8 mode, otherwise in extended ASCII (optional=<b><c>true</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
native bool:fputchar(File: handle, value, bool: utf8 = true);

/// <summary>Reads a single character from a file.</summary>
/// <param name="handle">The file handle to use; returned by <a href="#fopen">fopen</a></param>
/// <param name="value">This parameter has no use, just keep it "0"</param>
/// <param name="utf8">If true, read a character as UTF-8, otherwise as extended ASCII (optional=<b><c>true</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
/// <returns>If succeed, it returns the extended ASCII or UTF-8 value of the character at the current position in the file, otherwise EOF (end of file).</returns>
native fgetchar(File: handle, value, bool: utf8 = true);

/// <summary>Write data to a file in binary format, while ignoring line brakes and encoding.</summary>
/// <param name="handle">The File handle to use, opened by fopen()</param>
/// <param name="buffer">The data to write to the file</param>
/// <param name="size">The number of cells to write (optional=<b><c>sizeof buffer</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
native fblockwrite(File: handle, const buffer[], size = sizeof buffer);

/// <summary>This function allows you to read data from a file, without encoding and line terminators.</summary>
/// <param name="handle">File handle to use, opened by <a href="#fopen">fopen</a></param>
/// <param name="buffer">The buffer to save the read data in</param>
/// <param name="size">The number of cells to read (optional=<b><c>sizeof buffer</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
/// <returns>The number of cells read. <b><c>0</c></b> if the file end has been reached.</returns>
native fblockread(File: handle, buffer[], size = sizeof buffer);

/// <summary>Change the current position in the file. You can either seek forward or backward through the file.</summary>
/// <param name="handle">The file handle to use. Returned by <a href="#fopen">fopen</a></param>
/// <param name="position">The new position in the file, relative to the parameter whence (see below) (optional=<b><c>0</c></b>)</param>
/// <param name="whence">The starting position to which parameter position relates (optional=<b><c>seek_start</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
/// <remarks>
///   <b>Whences:</b><p/>
///   <ul>
///     <li><b><c>seek_start</c></b> - set the file position relative to the start of the file (the position parameter must be positive).</li>
///     <li><b><c>seek_current</c></b> - set the file position relative to the current file position: the position parameter is added to the current position.</li>
///     <li><b><c>seek_end</c></b> - set the file position relative to the end of the file (parameter position must be zero or negative).</li>
///   </ul>
/// </remarks>
native fseek(File: handle, position = 0, seek_whence: whence = seek_start);

/// <summary>Returns the length of a file.</summary>
/// <param name="handle">The file handle returned by <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a></param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#fopen">fopen</a> or <a href="#ftemp">ftemp</a>.</remarks>
/// <returns>The length of a file, in bytes.</returns>
native flength(File: handle);

/// <summary>Checks if a specific file exists in the <b><c>/scriptfiles</c></b> directory.</summary>
/// <param name="name">The name of the file</param>
/// <returns>1 if the file exists, 0 otherwise.</returns>
native fexist(const name[]);

/// <summary>Find a filename matching a pattern.</summary>
/// <param name="name">The string to hold the result in, returned as a packed string</param>
/// <param name="pattern">The pattern that should be matched. May contain wildcards</param>
/// <param name="index">The number of the file, in case there are multiple matches (optional=<b><c>0</c></b>)</param>
/// <param name="size">The maximum size of parameter name (optional=<b><c>sizeof name</c></b>)</param>
/// <remarks>This function does not work in the current SA:MP version!</remarks>
/// <returns><b><c>true</c></b> on success, <b><c>false</c></b> on failure.</returns>
native bool:fmatch(name[], const pattern[], index = 0, size = sizeof name);
