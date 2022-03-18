//  SA-MP Native SQLite Database Functions
//
//  (c) Copyright 2015, SA-MP Team
//

#if defined _INC_a_sampdb
	#endinput
#endif
#define _INC_a_sampdb
#define _sampdb_included

#define SAMP_CONST_CORRECT

#pragma tabsize 4

/// <summary>This function is used to open a connection to a SQLite database, which is inside the <b><c>/scriptfiles</c></b> folder.</summary>
/// <param name="name">File name of the database</param>
/// <remarks>Return type for this function has changed since version <b>0.3.7 R2</b>.</remarks>
/// <remarks>
///   It will create a new SQLite database, if there is no SQLite database with the same file name available.<p/>
///   <b>Close</b> your database connection with <a href="#db_close">db_close</a>!
/// </remarks>
/// <returns>Returns index (starting at <b><c>1</c></b>) of the database connection .</returns>
native DB:db_open(const name[]);

/// <summary>Closes an SQLite database that was opened with <a href="#db_open">db_open</a>.</summary>
/// <param name="db">The handle of the database connection to close (returned by <a href="#db_open">db_open</a>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. May mean that the database handle specified is not open.
/// </returns>
native db_close(DB:db);

/// <summary>This function is used to execute an SQL query on an opened SQLite database.</summary>
/// <param name="db">The database handle to query</param>
/// <param name="query">The query to execute</param>
/// <remarks>Return type for this function has changed since version <b>0.3.7 R2</b>.</remarks>
/// <remarks><b>Always</b> free the result by using <a href="#db_free_result">db_free_result</a>!</remarks>
/// <returns>The query result index (<b>starting at 1</b>).</returns>
native DBResult:db_query(DB:db, const query[]);

/// <summary>Frees result memory allocated from <a href="#db_query">db_query</a>.</summary>
/// <param name="dbresult">The result to free</param>
/// <returns>If <b><c>DBResult:dbhandle</c></b> is a valid handle, it returns <b><c>1</c></b>, otherwise <b><c>0</c></b> if <b><c>DBResult:dbhandle</c></b> is a <b><c>NULL</c></b> reference.</returns>
native db_free_result(DBResult:dbresult);

/// <summary>Returns the number of rows from a <a href="#db_query">db_query</a>.</summary>
/// <param name="dbresult">The result of <a href="#db_query">db_query</a></param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>The number of rows in the result.</returns>
native db_num_rows(DBResult:dbresult);

/// <summary>Moves to the next row of the result allocated from <a href="#db_query">db_query</a>.</summary>
/// <param name="dbresult">The result of <a href="#db_query">db_query</a></param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Returns <b><c>1</c></b> on success, otherwise <b><c>0</c></b> if <b><c>DBResult:dbresult</c></b> is a <b><c>NULL</c></b> reference or the last row is reached.</returns>
native db_next_row(DBResult:dbresult);

/// <summary>Get the number of fields in a result.</summary>
/// <param name="dbresult">The result of <a href="#db_query">db_query</a></param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>The number of fields in the result.</returns>
native db_num_fields(DBResult:dbresult);

/// <summary>Returns the name of a field at a particular index.</summary>
/// <param name="dbresult">The result to get the data from; returned by <a href="#db_query">db_query</a></param>
/// <param name="field">The index of the field to get the name of</param>
/// <param name="result">The result</param>
/// <param name="maxlength">The max length of the field</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Returns <b><c>1</c></b>, if the function was successful, otherwise <b><c>0</c></b> if <b><c>DBResult:dbresult</c></b> is a <b><c>NULL</c></b> reference or the column index not available.</returns>
native db_field_name(DBResult:dbresult, field, result[], maxlength = sizeof result);

/// <summary>Get the content of a field from <a href="#db_query">db_query</a>.</summary>
/// <param name="dbresult">The result to get the data from</param>
/// <param name="field">The field to get the data from</param>
/// <param name="result">The result</param>
/// <param name="maxlength">The max length of the field</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Returns <b><c>1</c></b> if successful, otherwise <b><c>0</c></b> if <b><c>DBResult:dbresult</c></b> is a <b><c>NULL</c></b> reference or the column index not available.</returns>
native db_get_field(DBResult:dbresult, field, result[], maxlength = sizeof result);

/// <summary>Get the content of a field as an integer from <a href="#db_query">db_query</a>.</summary>
/// <param name="result">The result to get the data from</param>
/// <param name="field">The field to get the data from (optional=<b><c>0</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Retrieved value as integer (number).</returns>
native db_get_field_int(DBResult:result, field = 0);

/// <summary>Get the content of a field as a float from db_query.</summary>
/// <param name="result">The result to get the data from</param>
/// <param name="field">The field to get the data from (optional=<b><c>0</c></b>)</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Retrieved value as floating point number.</returns>
native Float:db_get_field_float(DBResult:result, field = 0);

/// <summary>Get the contents of field with specified name.</summary>
/// <param name="dbresult">The result to get the data from</param>
/// <param name="field">The fieldname to get the data from</param>
/// <param name="result">The result</param>
/// <param name="maxlength">The max length of the field</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Returns <b><c>1</c></b> if successful, otherwise <b><c>0</c></b> if <b><c>DBResult:dbresult</c></b> is a <b><c>NULL</c></b> reference or the column index not available.</returns>
native db_get_field_assoc(DBResult:dbresult, const field[], result[], maxlength = sizeof result);

/// <summary>Get the contents of field as an integer with specified name.</summary>
/// <param name="result">The result to get the data from</param>
/// <param name="field">The fieldname to get the data from</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Retrieved value as integer (number).</returns>
native db_get_field_assoc_int(DBResult:result, const field[]);

/// <summary>Get the contents of field as a float with specified name.</summary>
/// <param name="result">The result to get the data from</param>
/// <param name="field">The fieldname to get the data from</param>
/// <remarks>Using an <b>invalid handle</b> will crash your server! Get a <b>valid handle</b> by using <a href="#db_open">db_open</a>. But it's protected against <b><c>NULL</c></b> references</remarks>
/// <returns>Retrieved value as floating point number.</returns>
native Float:db_get_field_assoc_float(DBResult:result, const field[]);

/// <summary>Get memory handle for an SQLite database that was opened with <a href="#db_open">db_open</a>.</summary>
/// <param name="db">The index of the database connection (returned by <a href="#db_open">db_open</a>)</param>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R1</b> and will not work in earlier versions!</remarks>
/// <returns>Returns the memory handle for a specified database.</returns>
native db_get_mem_handle(DB:db);

/// <summary>Get <b>memory handle</b> for an SQLite query that was executed with <a href="#db_query">db_query</a>.</summary>
/// <param name="result">The index of the query (returned by <a href="#db_query">db_query</a>)</param>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R1</b> and will not work in earlier versions!</remarks>
/// <returns>Returns the memory handle for a specified query.</returns>
native db_get_result_mem_handle(DBResult:result);

native db_debug_openfiles();
native db_debug_openresults();

