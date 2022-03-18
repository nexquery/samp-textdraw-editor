 /*  SA-MP threaded HTTP/1.0 client for pawn
 *
 *  (c) Copyright 2010, SA-MP Team
 *
 */

#if defined _INC_a_http
	#endinput
#endif
#define _INC_a_http

#define SAMP_CONST_CORRECT

#pragma tabsize 4

// --------------------------------------------------
// Defines
// --------------------------------------------------

// HTTP requests
#define HTTP_GET                               (1)
#define HTTP_POST                              (2)
#define HTTP_HEAD                              (3)

// HTTP error response codes
// These codes compliment ordinary HTTP response codes returned in 'response_code'
// (10x) (20x OK) (30x Moved) (40x Unauthorised) (50x Server Error)  
#define HTTP_ERROR_BAD_HOST                    (1)
#define HTTP_ERROR_NO_SOCKET                   (2)
#define HTTP_ERROR_CANT_CONNECT                (3)
#define HTTP_ERROR_CANT_WRITE                  (4)
#define HTTP_ERROR_CONTENT_TOO_BIG             (5)
#define HTTP_ERROR_MALFORMED_RESPONSE          (6)

/// <summary>Sends a threaded HTTP request.</summary>
/// <param name="index">ID used to differentiate requests that are sent to the same callback (useful for playerids)</param>
/// <param name="type">The type of request you wish to send</param>
/// <param name="url">The URL you want to request. (Without 'http://')</param>
/// <param name="data">Any POST data you want to send with the request</param>
/// <param name="callback">Name of the callback function you want to use to handle responses to this request</param>
/// <remarks>This function was added in <b>SA-MP 0.3b</b> and will not work in earlier versions!</remarks>
/// <returns><b><c>1</c></b> on success, <b><c>0</c></b> on failure.</returns>
/// <remarks>
///   <b>Request types:</b><p/>
///   <ul>
///     <li><b><c>HTTP_GET</c></b></li>
///     <li><b><c>HTTP_POST</c></b></li>
///     <li><b><c>HTTP_HEAD</c></b></li>
///   </ul>
/// </remarks>
/// <remarks>
///   <b>Response codes:</b><p/>
///   <ul>
///     <li><b><c>HTTP_ERROR_BAD_HOST</c></b></li>
///     <li><b><c>HTTP_ERROR_NO_SOCKET</c></b></li>
///     <li><b><c>HTTP_ERROR_CANT_CONNECT</c></b></li>
///     <li><b><c>HTTP_ERROR_CANT_WRITE</c></b></li>
///     <li><b><c>HTTP_ERROR_CONTENT_TOO_BIG</c></b></li>
///     <li><b><c>HTTP_ERROR_MALFORMED_RESPONSE</c></b></li>
///     <li>+ standard HTTP response codes</li>
///   </ul>
/// </remarks>
native HTTP(index, type, const url[], const data[], const callback[]);

// example HTTP callback: public MyHttpResponse(index, response_code, const data[]) { ... }

