/* Datagram sending/receiving
 *
 * (c) Copyright 2005, ITB CompuPhase
 * This file is provided as is (no warranties).
 */
#if defined _datagram_included
	#endinput
#endif
#define _datagram_included
#pragma library DGram

/// <summary>Sends a packet containing a string.</summary>
/// <param name="message">The buffer that contains the string to send. If this is an unpacked string, it will be UTF-8 encoded before being transferred.</param>
/// <param name="destination">The IP address and port number to which the packet must be sent. If absent or an empty string, this function will broadcast the packet and use the default port number 9930 (optional=<c><b>""</b></c>)</param>
/// <seealso name="@receivestring"/>
/// <seealso name="sendpacket"/>
/// <remarks>This function does not work in the current SA:MP version!</remarks>
/// <returns><b><c>1</c></b> on success, <b><c>0</c></b> on failure.</returns>
native sendstring(const message[], const destination[]="");

/// <summary>Sends a packet.</summary>
/// <param name="packet">The buffer that contains the packet to send.</param>
/// <param name="destination">The IP address and port number to which the packet must be sent. If absent or an empty string, this function will broadcast the packet and use the default port number 9930 (optional=<c><b>""</b></c>)</param>
/// <seealso name="@receivepacket"/>
/// <seealso name="sendstring"/>
/// <remarks>This function does not work in the current SA:MP version!</remarks>
/// <returns><b><c>1</c></b> on success, <b><c>0</c></b> on failure.</returns>
native sendpacket(const packet[], size, const destination[]="");


/// <summary>Sets up the port number to listen at.</summary>
/// <param name="port">The number of the port to listen at. This must be a value between <c><b>1</b></c> and <c><b>65535</b></c>, but you should probably avoid to use any of the reserved port numbers.</param>
/// <seealso name="@receivestring"/>
/// <seealso name="sendstring"/>
/// <remarks>You must call this function <b>before</b> receiving the first packet. In other words, you should set up a port in main.</remarks>
/// <remarks>If no port number has been explicitily chosen, the module will listen at port <c><b>9930</b></c>.</remarks>
/// <remarks>This function does not work in the current SA:MP version!</remarks>
/// <returns>This function always returns <b><c>0</c></b>.</returns>
native listenport(port);


/// <summary>A packed was received.</summary>
/// <param name="message">Contains the message (a zero-terminated string) that was received.</param>
/// <param name="source">Contains the IP address and the port number of the sender of this packet.</param>
/// <seealso name="@receivepacket"/>
/// <seealso name="sendstring"/>
/// <remarks>The string is in unpacked format if the original packet contained a string in UTF-8 format. Note that messages in the ASCII character set are also UTF-8 compliant.</remarks>
/// <remarks>This function does not work in the current SA:MP version!</remarks>
/// <returns>The return value of this function is currently ignored.</returns>
forward @receivestring(const message[], const source[]);

/// <summary>A packed was received.</summary>
/// <param name="packet">Contains the packet that was received.</param>
/// <param name="size">Contains the number of <b>bytes</b> (not cells) that are in the packet</param>
/// <param name="source">Contains the IP address and the port number of the sender of this packet.</param>
/// <seealso name="@receivestring"/>
/// <seealso name="sendpacket"/>
/// <remarks>You must call this function before receiving the first packet. In other words, you should set up a port in main.</remarks>
/// <remarks>If no port number has been explicitily chosen, the module will listen at port <c><b>9930</b></c>.</remarks>
/// <remarks>This function does not work in the current SA:MP version!</remarks>
/// <returns>The return value of this function is currently ignored.</returns>
forward @receivepacket(const packet[], size, const source[]);
