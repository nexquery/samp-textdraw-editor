/* Date/time functions
 *
 * (c) Copyright 2001-2005, ITB CompuPhase
 * This file is provided as is (no warranties).
 */
#if defined _time_included
	#endinput
#endif
#define _time_included
#pragma library Time

/// <summary>Get the current server time.</summary>
/// <param name="hour">The variable to store the hour in, passed by reference (optional=<b><c>0</c></b>)</param>
/// <param name="minute">The variable to store the minute in, passed by reference (optional=<b><c>0</c></b>)</param>
/// <param name="second">The variable to store the seconds in, passed by reference (optional=<b><c>0</c></b>)</param>
/// <seealso name="getdate"/>
/// <returns>The function itself returns a Unix Timestamp.</returns>
native gettime(&hour=0, &minute=0, &second=0);

/// <summary>Get the current server date.</summary>
/// <param name="year">The variable to store the year in, passed by reference (optional=<b><c>0</c></b>)</param>
/// <param name="month">The variable to store the month in, passed by reference (optional=<b><c>0</c></b>)</param>
/// <param name="day">The variable to store the day in, passed by reference (optional=<b><c>0</c></b>)</param>
/// <seealso name="gettime"/>
/// <returns>The number of days since the start of the year.</returns>
native getdate(&year=0, &month=0, &day=0);

/// <summary>This function can be used as a replacement for <a href="#GetTickCount">GetTickCount</a>, as it returns the number of milliseconds since the start-up of the server.</summary>
/// <param name="granularity">Upon return, this value contains the number of ticks that the internal system time will tick per second. This value therefore indicates the accuracy of the return value of this function (optional=<b><c>0</c></b>)</param>
/// <returns>The number of milliseconds since start-up of the system. For a 32-bit cell, this count overflows after approximately 24 days of continuous operation.</returns>
native tickcount(&granularity=0);
