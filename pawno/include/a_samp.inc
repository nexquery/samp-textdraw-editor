/*  SA-MP Functions
 *
 *  (c) Copyright 2005-2017, SA-MP Team
 *
 */

#if defined _INC_a_samp
	#endinput
#endif
#if defined _INC_a_npc
	#error Include `<a_samp>` or `<a_npc>`, not both.
#endif
#define _INC_a_samp
#define _samp_included

#define SAMP_CONST_CORRECT

#pragma tabsize 4
// Ignores warning 217 for properly indented PAWNO code
// It's tab size is 4 and often uses 4 spaces instead, PAWNCC's is 8

// --------------------------------------------------
// Defines
// --------------------------------------------------

// Limits
#if !defined MAX_PLAYER_NAME
	#define MAX_PLAYER_NAME                    (24)
#endif

#if !defined MAX_PLAYERS
	#define MAX_PLAYERS                        (1000)
#endif

#if !defined MAX_VEHICLES
	#define MAX_VEHICLES                       (2000)
#endif

#if !defined MAX_ACTORS
	#define MAX_ACTORS                         (1000)
#endif

#if !defined MAX_OBJECTS
	#define MAX_OBJECTS                        (2000)
#endif

#if !defined MAX_GANG_ZONES
	#define MAX_GANG_ZONES                     (1024)
#endif

#if !defined MAX_TEXT_DRAWS
	#define MAX_TEXT_DRAWS                     (Text:2048)
#endif

#if !defined MAX_PLAYER_TEXT_DRAWS
	#define MAX_PLAYER_TEXT_DRAWS              (PlayerText:256)
#endif

#if !defined MAX_MENUS
	#define MAX_MENUS                          (Menu:128)
#endif

#if !defined MAX_3DTEXT_GLOBAL
	#define MAX_3DTEXT_GLOBAL                  (Text3D:1024)
#endif

#if !defined MAX_3DTEXT_PLAYER
	#define MAX_3DTEXT_PLAYER                  (PlayerText3D:1024)
#endif

#if !defined MAX_PICKUPS
	#define MAX_PICKUPS                        (4096)
#endif

// Invalids
#define NO_TEAM                                (255)

#define INVALID_PLAYER_ID                      (0xFFFF)
#define INVALID_VEHICLE_ID                     (0xFFFF)
#define INVALID_ACTOR_ID                       (0xFFFF)
#define INVALID_OBJECT_ID                      (0xFFFF)
#define INVALID_MENU                           (Menu:0xFF)
#define INVALID_TEXT_DRAW                      (Text:0xFFFF)
#define INVALID_PLAYER_TEXT_DRAW               (PlayerText:0xFFFF)
#define INVALID_GANG_ZONE                      (-1)
#define INVALID_3DTEXT_ID                      (Text3D:0xFFFF)
#define INVALID_PLAYER_3DTEXT_ID               (PlayerText3D:0xFFFF)

// States
#define PLAYER_STATE_NONE                      (0)
#define PLAYER_STATE_ONFOOT                    (1)
#define PLAYER_STATE_DRIVER                    (2)
#define PLAYER_STATE_PASSENGER                 (3)
#define PLAYER_STATE_EXIT_VEHICLE              (4) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_DRIVER      (5) // (used internally)
#define PLAYER_STATE_ENTER_VEHICLE_PASSENGER   (6) // (used internally)
#define PLAYER_STATE_WASTED                    (7)
#define PLAYER_STATE_SPAWNED                   (8)
#define PLAYER_STATE_SPECTATING                (9)

// Marker modes used by ShowPlayerMarkers()
#define PLAYER_MARKERS_MODE_OFF                (0)
#define PLAYER_MARKERS_MODE_GLOBAL             (1)
#define PLAYER_MARKERS_MODE_STREAMED           (2)

// Weapons
#define WEAPON_BRASSKNUCKLE                    (1)
#define WEAPON_GOLFCLUB                        (2)
#define WEAPON_NITESTICK                       (3)
#define WEAPON_KNIFE                           (4)
#define WEAPON_BAT                             (5)
#define WEAPON_SHOVEL                          (6)
#define WEAPON_POOLSTICK                       (7)
#define WEAPON_KATANA                          (8)
#define WEAPON_CHAINSAW                        (9)
#define WEAPON_DILDO                           (10)
#define WEAPON_DILDO2                          (11)
#define WEAPON_VIBRATOR                        (12)
#define WEAPON_VIBRATOR2                       (13)
#define WEAPON_FLOWER                          (14)
#define WEAPON_CANE                            (15)
#define WEAPON_GRENADE                         (16)
#define WEAPON_TEARGAS                         (17)
#define WEAPON_MOLTOV                          (18)
#define WEAPON_COLT45                          (22)
#define WEAPON_SILENCED                        (23)
#define WEAPON_DEAGLE                          (24)
#define WEAPON_SHOTGUN                         (25)
#define WEAPON_SAWEDOFF                        (26)
#define WEAPON_SHOTGSPA                        (27)
#define WEAPON_UZI                             (28)
#define WEAPON_MP5                             (29)
#define WEAPON_AK47                            (30)
#define WEAPON_M4                              (31)
#define WEAPON_TEC9                            (32)
#define WEAPON_RIFLE                           (33)
#define WEAPON_SNIPER                          (34)
#define WEAPON_ROCKETLAUNCHER                  (35)
#define WEAPON_HEATSEEKER                      (36)
#define WEAPON_FLAMETHROWER                    (37)
#define WEAPON_MINIGUN                         (38)
#define WEAPON_SATCHEL                         (39)
#define WEAPON_BOMB                            (40)
#define WEAPON_SPRAYCAN                        (41)
#define WEAPON_FIREEXTINGUISHER                (42)
#define WEAPON_CAMERA                          (43)
#define WEAPON_PARACHUTE                       (46)
#define WEAPON_VEHICLE                         (49)
#define WEAPON_DROWN                           (53)
#define WEAPON_COLLISION                       (54)

// Keys
#define KEY_ACTION                             (1)
#define KEY_CROUCH                             (2)
#define KEY_FIRE                               (4)
#define KEY_SPRINT                             (8)
#define KEY_SECONDARY_ATTACK                   (16)
#define KEY_JUMP                               (32)
#define KEY_LOOK_RIGHT                         (64)
#define KEY_HANDBRAKE                          (128)
#define KEY_LOOK_LEFT                          (256)
#define KEY_SUBMISSION                         (512)
#define KEY_LOOK_BEHIND                        (512)
#define KEY_WALK                               (1024)
#define KEY_ANALOG_UP                          (2048)
#define KEY_ANALOG_DOWN                        (4096)
#define KEY_ANALOG_LEFT                        (8192)
#define KEY_ANALOG_RIGHT                       (16384)
#define KEY_YES                                (65536)
#define KEY_NO                                 (131072)
#define KEY_CTRL_BACK                          (262144)

#define KEY_UP                                 (-128)
#define KEY_DOWN                               (128)
#define KEY_LEFT                               (-128)
#define KEY_RIGHT                              (128)

// Player GUI Dialog
#define DIALOG_STYLE_MSGBOX                    (0)
#define DIALOG_STYLE_INPUT                     (1)
#define DIALOG_STYLE_LIST                      (2)
#define DIALOG_STYLE_PASSWORD                  (3)
#define DIALOG_STYLE_TABLIST                   (4)
#define DIALOG_STYLE_TABLIST_HEADERS           (5)

// Text Draw
#define TEXT_DRAW_FONT_SPRITE_DRAW             (4)
#define TEXT_DRAW_FONT_MODEL_PREVIEW           (5)

// SVar enumeration
#define	SERVER_VARTYPE_NONE                    (0)
#define SERVER_VARTYPE_INT                     (1)
#define SERVER_VARTYPE_STRING                  (2)
#define SERVER_VARTYPE_FLOAT                   (3)

// Artwork/NetModels
#define DOWNLOAD_REQUEST_EMPTY                 (0)
#define DOWNLOAD_REQUEST_MODEL_FILE            (1)
#define DOWNLOAD_REQUEST_TEXTURE_FILE          (2)

#define CLICK_SOURCE_SCOREBOARD                (0)

#define EDIT_RESPONSE_CANCEL                   (0)
#define EDIT_RESPONSE_FINAL                    (1)
#define EDIT_RESPONSE_UPDATE                   (2)

#define SELECT_OBJECT_GLOBAL_OBJECT            (1)
#define SELECT_OBJECT_PLAYER_OBJECT            (2)

#define BULLET_HIT_TYPE_NONE                   (0)
#define BULLET_HIT_TYPE_PLAYER                 (1)
#define BULLET_HIT_TYPE_VEHICLE                (2)
#define BULLET_HIT_TYPE_OBJECT                 (3)
#define BULLET_HIT_TYPE_PLAYER_OBJECT          (4)

// Limits
#if MAX_PLAYER_NAME < 3 || MAX_PLAYER_NAME > 24
	#error MAX_PLAYER_NAME must be >= 3 and <= 24
#endif

#if MAX_PLAYERS < 1 || MAX_PLAYERS > 1000
	#error MAX_PLAYERS must be >= 1 and <= 1000
#endif

#if MAX_VEHICLES < 1 || MAX_VEHICLES > 2000
	#error MAX_VEHICLES must be >= 1 and <= 2000
#endif

#if MAX_ACTORS < 1 || MAX_ACTORS > 1000
	#error MAX_ACTORS must be >= 1 and <= 1000
#endif

#if MAX_OBJECTS < 1 || MAX_OBJECTS > 2000
	#error MAX_OBJECTS must be >= 1 and <= 2000
#endif

#if MAX_GANG_ZONES < 1 || MAX_GANG_ZONES > 1024
	#error MAX_GANG_ZONES must be >= 1 and <= 1024
#endif

#if MAX_TEXT_DRAWS < Text:1 || MAX_TEXT_DRAWS > Text:2048
	#error MAX_TEXT_DRAWS must be >= 1 and <= 2048
#endif

#if MAX_PLAYER_TEXT_DRAWS < PlayerText:1 || MAX_PLAYER_TEXT_DRAWS > PlayerText:256
	#error MAX_PLAYER_TEXT_DRAWS must be >= 1 and <= 256
#endif

#if MAX_MENUS < Menu:1 || MAX_MENUS > Menu:128
	#error MAX_MENUS must be >= 1 and <= 128
#endif

#if MAX_3DTEXT_GLOBAL < Text3D:1 || MAX_3DTEXT_GLOBAL > Text3D:1024
	#error MAX_3DTEXT_GLOBAL must be >= 1 and <= 1024
#endif

#if MAX_3DTEXT_PLAYER < PlayerText3D:1 || MAX_3DTEXT_PLAYER > PlayerText3D:1024
	#error MAX_3DTEXT_PLAYER must be >= 1 and <= 1024
#endif

#if MAX_PICKUPS < 1 || MAX_PICKUPS > 4096
	#error MAX_PICKUPS must be >= 1 and <= 4096
#endif

public const SAMP_INCLUDES_VERSION = 0x037030;

#include <core>
#include <float>
#include <string>
#include <file>
#include <time>
#include <datagram>
#tryinclude <console>
#include <a_players>
#include <a_vehicles>
#include <a_objects>
#include <a_actor>
#include <a_sampdb>
#include <a_http>

/*

Version examples:

0.3.DL R1       - 03D010

0.3.7 R3        - 037030
0.3.7 R2-2      - 037022
0.3.7 R1-2      - 037012
0.3.7           - 037000

0.3z R4         - 030700
0.3z R3         - 030700
0.3z R2-1       - 030700
0.3z R1-2       - 030700
0.3z            - 030700
0.3x R2 patch 1 - 030621
0.3x R2         - 030620
0.3x R1-2       - 030612
0.3x            - 030600
0.3e            - 030500
0.3d            - 030400
0.3c            - 030300
0.3b            - 030200
0.3a            - 030100

0.2X            - 02A000
0.2.2 R3        - 022300

Rough rules:

Uses (roughtly) BCD.  Special versions are denoted outside 0-9.

0.1.2c R4-5
| | ||  | |
0 1 23  4 5
=
0x012345

(assuming c is the third revision)

0.2X becomes 02A000 because it is basically 0.2.3, but not, while higher than
0.2.2 so can't be 020400 (for example).  Also, its a capital letter, so doesn't
use the revision method.

P.S.  Making a consistent scheme for SA:MP versions is REALLY hard.

open.mp releases can use `A` as the first digit.

*/

// --------------------------------------------------
// Natives
// --------------------------------------------------

// Util

#if !defined _console_included
	#define _console_included

	/// <summary>Prints a string to the server console (not in-game chat) and logs (server_log.txt).</summary>
	/// <param name="string">The string to print</param>
	/// <seealso name="printf"/>
	native print(const string[]);

	/// <summary>Outputs a formatted string on the console (the server window, not the in-game chat).</summary>
	/// <param name="format">The format string</param>
	/// <param name="">Indefinite number of arguments of any tag</param>
	/// <seealso name="print"/>
	/// <seealso name="format"/>
	/// <remarks>The format string or its output should not exceed 1024 characters. Anything beyond that length can lead to a server to crash.</remarks>
	/// <remarks>This function doesn't support <a href="#strpack">packed</a> strings.</remarks>
	/// <remarks>
	///   <b>Format Specifiers:</b><p/>
	///   <ul>
	///     <li><b><c>%i</c></b> - integer (whole number)</li>
	///     <li><b><c>%d</c></b> - integer (whole number).</li>
	///     <li><b><c>%s</c></b> - string</li>
	///     <li><b><c>%f</c></b> - floating-point number (Float: tag)</li>
	///     <li><b><c>%c</c></b> - ASCII character</li>
	///     <li><b><c>%x</c></b> - hexadecimal number</li>
	///     <li><b><c>%b</c></b> - binary number</li>
	///     <li><b><c>%%</c></b> - literal <b><c>%</c></b></li>
	///     <li><b><c>%q</c></b> - escape a text for SQLite. (Added in <b>0.3.7 R2</b>)</li>
	///   </ul>
	/// </remarks>
	/// <remarks>The values for the placeholders follow in the exact same order as parameters in the call. For example, <b><c>"I am %i years old"</c></b> - the <b><c>%i</c></b> will be replaced with an Integer variable, which is the person's age.</remarks>
	/// <remarks>You may optionally put a number between the <b><c>%</c></b> and the letter of the placeholder code. This number indicates the field width; if the size of the parameter to print at the position of the placeholder is smaller than the field width, the field is expanded with spaces. To cut the number of decimal places beeing shown of a float, you can add <b><c>.&lt;max number&gt;</c></b> between the <b><c>%</c></b> and the <b><c>f</c></b>. (example: <b><c>%.2f</c></b>)</remarks>
	native printf(const format[], {Float,_}:...);
#endif

/// <summary>Formats a string to include variables and other strings inside it.</summary>
/// <param name="output">The string to output the result to</param>
/// <param name="len">The maximum length output can contain</param>
/// <param name="format">The format string</param>
/// <param name="">Indefinite number of arguments of any tag</param>
/// <seealso name="print"/>
/// <seealso name="printf"/>
/// <remarks>This function doesn't support <a href="#strpack">packed strings</a>.</remarks>
/// <remarks>
///   <b>Format Specifiers:</b><p/>
///   <ul>
///     <li><b><c>%i</c></b> - integer (whole number)</li>
///     <li><b><c>%d</c></b> - integer (whole number).</li>
///     <li><b><c>%s</c></b> - string</li>
///     <li><b><c>%f</c></b> - floating-point number (Float: tag)</li>
///     <li><b><c>%c</c></b> - ASCII character</li>
///     <li><b><c>%x</c></b> - hexadecimal number</li>
///     <li><b><c>%b</c></b> - binary number</li>
///     <li><b><c>%%</c></b> - literal <b><c>%</c></b></li>
///     <li><b><c>%q</c></b> - escape a text for SQLite. (Added in <b>0.3.7 R2</b>)</li>
///   </ul>
/// </remarks>
/// <remarks>The values for the placeholders follow in the exact same order as parameters in the call. For example, <b><c>"I am %i years old"</c></b> - the <b><c>%i</c></b> will be replaced with an Integer variable, which is the person's age.</remarks>
/// <remarks>You may optionally put a number between the <b><c>%</c></b> and the letter of the placeholder code. This number indicates the field width; if the size of the parameter to print at the position of the placeholder is smaller than the field width, the field is expanded with spaces. To cut the number of decimal places beeing shown of a float, you can add <b><c>.&lt;max number&gt;</c></b> between the <b><c>%</c></b> and the <b><c>f</c></b>. (example: <b><c>%.2f</c></b>)</remarks>
native format(output[], len = sizeof output, const format[], {Float,_}:...);

/// <summary>This function sends a message to a specific player with a chosen color in the chat. The whole line in the chatbox will be in the set color unless color embedding is used (since <b><c>0.3c</c></b>).</summary>
/// <param name="playerid">The ID of the player to display the message to</param>
/// <param name="color">The color of the message (<b>RGBA</b>)</param>
/// <param name="message">The text that will be displayed <b>(max 144 characters)</b></param>
/// <seealso name="SendClientMessageToAll"/>
/// <seealso name="SendPlayerMessageToPlayer"/>
/// <seealso name="SendPlayerMessageToAll"/>
/// <remarks>If a message is longer than 144 characters, it will not be sent. Truncation can be used to prevent this. Displaying a message on multiple lines will also solve this issue. </remarks>
/// <remarks>Avoid using the percent sign (or format specifiers) in the actual message text without properly escaping it (like <b><c>%%</c></b>). It will result in crashes otherwise. </remarks>
/// <remarks>You can use color embedding for multiple colors in the message. </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully. Success is reported when the string is over 144 characters, but the message won't be sent.<p/>
///   <b><c>0</c></b>: The function failed to execute. The player is not connected.
/// </returns>
native SendClientMessage(playerid, color, const message[]);

/// <summary>Displays a message in chat to all players. This is a multi-player equivalent of <a href="#SendClientMessage">SendClientMessage</a>.</summary>
/// <param name="color">The color of the message (<b>RGBA</b>)</param>
/// <param name="message">The message to show (<b>max 144 characters</b>)</param>
/// <seealso name="SendClientMessage"/>
/// <seealso name="SendPlayerMessageToAll"/>
/// <remarks>Avoid using format specifiers in your messages without formatting the string that is sent. It will result in crashes otherwise.</remarks>
/// <returns>This function always returns <b><c>1</c></b>.</returns>
native SendClientMessageToAll(color, const message[]);

/// <summary>Sends a message in the name of a player to another player on the server. The message will appear in the chat box but can only be seen by the user specified with <paramref name="playerid"/>. The line will start with the sender's name in their color, followed by the message in white.</summary>
/// <param name="playerid">The ID of the player who will receive the message</param>
/// <param name="senderid">The sender's ID. If invalid, the message will not be sent</param>
/// <param name="message">The message that will be sent</param>
/// <seealso name="SendPlayerMessageToAll"/>
/// <seealso name="SendClientMessage"/>
/// <seealso name="SendClientMessageToAll"/>
/// <seealso name="OnPlayerText"/>
/// <remarks>Avoid using format specifiers in your messages without formatting the string that is sent. It will result in crashes otherwise.</remarks>
native SendPlayerMessageToPlayer(playerid, senderid, const message[]);

/// <summary>Sends a message in the name of a player to all other players on the server. The line will start with the sender's name in their color, followed by the message in white.</summary>
/// <param name="senderid">The ID of the sender. If invalid, the message will not be sent</param>
/// <param name="message">The message that will be sent</param>
/// <seealso name="SendPlayerMessageToPlayer"/>
/// <seealso name="SendClientMessageToAll"/>
/// <seealso name="OnPlayerText"/>
/// <remarks>Avoid using format specifiers in your messages without formatting the string that is sent. It will result in crashes otherwise.</remarks>
native SendPlayerMessageToAll(senderid, const message[]);

/// <summary>Adds a death to the 'killfeed' on the right-hand side of the screen for all players.</summary>
/// <param name="killer">The ID of the killer (can be <b><c>INVALID_PLAYER_ID</c></b>)</param>
/// <param name="killee">The ID of the player that died</param>
/// <param name="weapon">The <a href="http://wiki.sa-mp.com/wiki/Weapons">reason</a> (not always a weapon) for the victim's death. Special icons can also be used (<b><c>ICON_CONNECT</c></b> and <b><c>ICON_DISCONNECT</c></b>)</param>
/// <seealso name="SendDeathMessageToPlayer"/>
/// <seealso name="OnPlayerDeath"/>
/// <remarks>Death messages can be cleared by using a valid player ID for <paramref name="killee"/> that is not connected.</remarks>
/// <remarks>To show a death message for just a single player, use <a href="#SendDeathMessageToPlayer">SendDeathMessageToPlayer</a>. </remarks>
/// <remarks>You can use NPCs to create your own custom death reasons. </remarks>
/// <returns>This function always returns <b><c>1</c></b>, even if the function fails to execute. The function fails to execute (no death message shown) if <paramref name="killee"/> is invalid. If <paramref name="reason"/> is invalid, a generic skull-and-crossbones icon is shown. <paramref name="killer"/> being invalid (<b><c>INVALID_PLAYER_ID</c></b>) is valid.</returns>
native SendDeathMessage(killer, killee, weapon);

/// <summary>Adds a death to the 'killfeed' on the right-hand side of the screen for a single player.</summary>
/// <param name="playerid">The ID of the player to send the death message to</param>
/// <param name="killer">The ID of the killer (can be <b><c>INVALID_PLAYER_ID</c></b>)</param>
/// <param name="killee">The ID of the player that died</param>
/// <param name="weapon">The <a href="http://wiki.sa-mp.com/wiki/Weapons">reason</a> (not always a weapon) for the victim's death. Special icons can also be used (<b><c>ICON_CONNECT</c></b> and <b><c>ICON_DISCONNECT</c></b>)</param>
/// <seealso name="SendDeathMessage"/>
/// <seealso name="OnPlayerDeath"/>
/// <remarks>This Function was added in <b>SA-MP 0.3z R2-2</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute.
/// </returns>
native SendDeathMessageToPlayer(playerid, killer, killee, weapon);

/// <summary>Shows 'game text' (on-screen text) for a certain length of time for all players.</summary>
/// <param name="string">The text to be displayed</param>
/// <param name="time">The duration of the text being shown in milliseconds</param>
/// <param name="style">The style of text to be displayed</param>
/// <seealso name="GameTextForPlayer"/>
/// <seealso name="TextDrawShowForAll"/>
/// <returns>This function always returns <b><c>1</c></b>.</returns>
native GameTextForAll(const string[], time, style);

/// <summary>Shows 'game text' (on-screen text) for a certain length of time for a specific player.</summary>
/// <param name="playerid">The ID of the player to show the gametext for</param>
/// <param name="string">The text to be displayed</param>
/// <param name="time">The duration of the text being shown in milliseconds</param>
/// <param name="style">The style of text to be displayed</param>
/// <seealso name="GameTextForAll"/>
/// <seealso name="TextDrawShowForPlayer"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully. Success is reported when the style and/or time is invalid. Nothing will happen though (no text displayed). May also cause game crashes.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means either the string is null or the player is not connected.
/// </returns>
native GameTextForPlayer(playerid, const string[], time, style);

/// <summary>Sets a 'timer' to call a function after some time. Can be set to repeat.</summary>
/// <param name="funcname">Name of the function to call as a string. This must be a public function (forwarded). A null string here will crash the server</param>
/// <param name="interval">Interval in milliseconds</param>
/// <param name="repeating">Whether the timer should repeat or not</param>
/// <seealso name="SetTimerEx"/>
/// <seealso name="KillTimer"/>
/// <remarks>Timer intervals are not accurate (roughly 25% off). There's a fix available <a href="http://forum.sa-mp.com/showthread.php?t=289675">here</a>. </remarks>
/// <remarks>Timer IDs are never used twice. You can use <a href="#KillTimer">KillTimer</a> on a timer ID and it won't matter if it's running or not. </remarks>
/// <remarks>The function that should be called must be public. </remarks>
/// <remarks>The use of many timers will result in increased memory/cpu usage. </remarks>
/// <returns>The ID of the timer that was started. Timer IDs start at <b><c>1</c></b>.</returns>
native SetTimer(const funcname[], interval, repeating);

/// <summary>Sets a timer to call a function after the specified interval. This variant ('Ex') can pass parameters (such as a player ID) to the function.</summary>
/// <param name="funcname">The name of a public function to call when the timer expires</param>
/// <param name="interval">Interval in milliseconds</param>
/// <param name="repeating">Whether the timer should be called repeatedly (can only be stopped with <a href="#KillTimer">KillTimer</a>) or only once</param>
/// <param name="format">Special format indicating the types of values the timer will pass</param>
/// <param name="">Indefinite number of arguments to pass (must follow format specified in previous parameter)</param>
/// <seealso name="SetTimer"/>
/// <seealso name="KillTimer"/>
/// <seealso name="CallLocalFunction"/>
/// <seealso name="CallRemoteFunction"/>
/// <remarks>Timer intervals are not accurate (roughly 25% off). There's a fix available <a href="http://forum.sa-mp.com/showthread.php?t=289675">here</a>. </remarks>
/// <remarks>Timer IDs are never used twice. You can use KillTimer() on a timer ID and it won't matter if it's running or not. </remarks>
/// <remarks>The function that should be called must be public. </remarks>
/// <remarks>The use of many timers will result in increased memory/cpu usage. </remarks>
/// <remarks>
///   <b>Format syntax:</b><p/>
///   <ul>
///     <li><b><c>i</c></b> - integer</li>
///     <li><b><c>d</c></b> - integer</li>
///     <li><b><c>a</c></b> - array The next parameter must be an integer (<b><c>"i"</c></b>) with the array's size <b>[CURRENTLY UNUSABLE]</b></li>
///     <li><b><c>s</c></b> - string <b>[CURRENTLY UNUSABLE]</b></li>
///     <li><b><c>f</c></b> - float</li>
///     <li><b><c>b</c></b> - boolean</li>
///   </ul>
/// </remarks>
/// <returns>The ID of the timer that was started. Timer IDs start at <b><c>1</c></b> and are never reused. There are no internal checks to verify that the parameters passed are valid (e.g. duration not a minus value).</returns>
native SetTimerEx(const funcname[], interval, repeating, const format[], {Float,_}:...);

/// <summary>Kills (stops) a running timer.</summary>
/// <param name="timerid">The ID of the timer to kill (returned by <a href="#SetTimer">SetTimer</a> or <a href="#SetTimerEx">SetTimerEx</a>)</param>
/// <seealso name="SetTimer"/>
/// <seealso name="SetTimerEx"/>
/// <returns>This function always returns <b><c>0</c></b>.</returns>
native KillTimer(timerid);

/// <summary>Returns the uptime of the actual server (not the SA-MP server) in milliseconds.</summary>
/// <seealso name="tickcount"/>
/// <remarks>GetTickCount will cause problems on servers with uptime of over 24 days as GetTickCount will eventually warp past the integer size constraints. However using <a href="https://gist.github.com/ziggi/5d7d8dc42f54531feba7ae924c608e73">this</a> function fixes the problem.</remarks>
/// <remarks>One common use for GetTickCount is for benchmarking. It can be used to calculate how much time some code takes to execute.</remarks>
/// <returns>Uptime of the actual server (not the SA-MP server).</returns>
native GetTickCount();

/// <summary>Returns the maximum number of players that can join the server, as set by the server variable 'maxplayers' in server.cfg.</summary>
/// <seealso name="GetPlayerPoolSize"/>
/// <seealso name="IsPlayerConnected"/>
/// <remarks>This function can not be used in place of <b><c>MAX_PLAYERS</c></b>. It can not be used at compile time (e.g. for array sizes). <b><c>MAX_PLAYERS</c></b> should always be re-defined to what the 'maxplayers' var will be, or higher.</remarks>
/// <returns>The maximum number of players that can join the server.</returns>
native GetMaxPlayers();

/// <summary>Calls a public function in any script that is loaded.</summary>
/// <param name="function">Public function's name</param>
/// <param name="format">Tag/format of each variable</param>
/// <param name="">'Indefinite' number of arguments of any tag</param>
/// <seealso name="CallLocalFunction"/>
/// <returns>The value that the last public function returned.</returns>
/// <remarks>CallRemoteFunction crashes the server if it's passing an empty string.</remarks>
/// <remarks>
///   Format string placeholders:<p/>
///   <ul>
///     <li><b><c>c</c></b> - a single character</li>
///     <li><b><c>d</c></b> - an integer (whole) number</li>
///     <li><b><c>i</c></b> - an integer (whole) number</li>
///     <li><b><c>x</c></b> - a number in hexadecimal notation</li>
///     <li><b><c>f</c></b> - a floating point number</li>
///     <li><b><c>s</c></b> - a string</li>
///   </ul>
/// </remarks>
native CallRemoteFunction(const function[], const format[], {Float,_}:...);

/// <summary>Calls a public function from the script in which it is used.</summary>
/// <param name="function">Public function's name</param>
/// <param name="format">Tag/format of each variable</param>
/// <param name="">'Indefinite' number of arguments of any tag</param>
/// <seealso name="CallRemoteFunction"/>
/// <returns>The value that the <b>only</b> public function returned.</returns>
/// <remarks>CallLocalFunction crashes the server if it's passing an empty string.</remarks>
/// <remarks>
///   Format string placeholders:<p/>
///   <ul>
///     <li><b><c>c</c></b> - a single character</li>
///     <li><b><c>d</c></b> - an integer (whole) number</li>
///     <li><b><c>i</c></b> - an integer (whole) number</li>
///     <li><b><c>x</c></b> - a number in hexadecimal notation</li>
///     <li><b><c>f</c></b> - a floating point number</li>
///     <li><b><c>s</c></b> - a string</li>
///   </ul>
/// </remarks>
native CallLocalFunction(const function[], const format[], {Float,_}:...);


/// <summary>Returns the norm (length) of the provided vector.</summary>
/// <param name="x">The vector's magnitude on the X axis</param>
/// <param name="y">The vector's magnitude on the Y axis</param>
/// <param name="z">The vector's magnitude on the Z axis</param>
/// <seealso name="GetPlayerDistanceFromPoint"/>
/// <seealso name="GetVehicleDistanceFromPoint"/>
/// <seealso name="floatsqroot"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <returns>The norm (length) of the provided vector as a float.</returns>
native Float:VectorSize(Float:x, Float:y, Float:z);

/// <summary>Get the inversed value of a sine in degrees.</summary>
/// <param name="value">The sine for which to find the angle for</param>
/// <seealso name="floatsin"/>
/// <returns>The angle in degrees.</returns>
native Float:asin(Float:value);

/// <summary>Get the inversed value of a cosine in degrees.</summary>
/// <param name="value">The cosine for which to find the angle for</param>
/// <seealso name="floatcos"/>
/// <returns>The angle in degrees.</returns>
native Float:acos(Float:value);

/// <summary>Get the inversed value of a tangent in degrees.</summary>
/// <param name="value">The tangent for which to find the angle for</param>
/// <seealso name="atan2"/>
/// <seealso name="floattan"/>
/// <returns>The angle in degrees.</returns>
native Float:atan(Float:value);

/// <summary>Get the multi-valued inversed value of a tangent in degrees.</summary>
/// <param name="y">y size</param>
/// <param name="x">x size</param>
/// <seealso name="atan"/>
/// <seealso name="floattan"/>
/// <returns>The angle in degrees.</returns>
native Float:atan2(Float:y, Float:x);


/// <summary>Gets the highest playerid currently in use on the server.</summary>
/// <seealso name="GetVehiclePoolSize"/>
/// <seealso name="GetMaxPlayers"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <returns>The highest playerid currently in use on the server or <b><c>0</c></b> if there are no connected players.</returns>
native GetPlayerPoolSize();

/// <summary>Gets the highest vehicleid currently in use on the server.</summary>
/// <seealso name="GetPlayerPoolSize"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <returns>The highest vehicleid currently in use on the server or <b><c>0</c></b> if there are no created vehicles.</returns>
native GetVehiclePoolSize();

/// <summary>Gets the highest actorid created on the server.</summary>
/// <seealso name="CreateActor"/>
/// <seealso name="IsValidActor"/>
/// <seealso name="SetActorHealth"/>
/// <remarks>This function was added in <b><b>SA-MP 0.3.7</b></b> and will not work in earlier versions!</remarks>
/// <returns>The highest actorid created on the server or <b><c>0</c></b> if there are no created actors.</returns>
native GetActorPoolSize();

// Hash

/// <summary>Hashes a password using the SHA-256 hashing algorithm. Includes a salt. The output is always 256 bytes in length, or the equivalent of 64 Pawn cells.</summary>
/// <param name="password">The password to hash</param>
/// <param name="salt">The salt to use in the hash</param>
/// <param name="ret_hash">The returned hash</param>
/// <param name="ret_hash_len">The returned hash maximum length</param>
/// <remarks>This function was added in <b>SA-MP 0.3.7-R1</b> and will not work in earlier versions!</remarks>
/// <remarks>The salt is appended to the end of the password, meaning password 'foo' and salt 'bar' would form 'foobar'. </remarks>
/// <remarks>The salt should be random, unique for each player and at least as long as the hashed password. It is to be stored alongside the actual hash in the player's account. </remarks>
native SHA256_PassHash(const password[], const salt[], ret_hash[], ret_hash_len = sizeof ret_hash); // SHA256 for password hashing

// Server wide persistent variable system (SVars)

/// <summary>Set an integer server variable.</summary>
/// <param name="varname">The name of the server variable</param>
/// <param name="int_value">The integer to be set</param>
/// <seealso name="GetSVarInt"/>
/// <seealso name="SetSVarString"/>
/// <seealso name="GetSVarString"/>
/// <seealso name="SetSVarFloat"/>
/// <seealso name="GetSVarFloat"/>
/// <seealso name="DeleteSVar"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R2</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The variable name is null or over 40 characters.
/// </returns>
native SetSVarInt(const varname[], int_value);

/// <summary>Gets an integer server variable's value.</summary>
/// <param name="varname">The name of the server variable (case-insensitive). Assigned in SetSVarInt</param>
/// <seealso name="SetSVarInt"/>
/// <seealso name="SetSVarString"/>
/// <seealso name="GetSVarString"/>
/// <seealso name="SetSVarFloat"/>
/// <seealso name="GetSVarFloat"/>
/// <seealso name="DeleteSVar"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R2</b> and will not work in earlier versions!</remarks>
/// <returns>The integer value of the specified server variable. It will still return <b><c>0</c></b> if the variable is not set.</returns>
native GetSVarInt(const varname[]);

/// <summary>Set a string server variable.</summary>
/// <param name="varname">The name of the server variable</param>
/// <param name="string_value">The string to be set</param>
/// <seealso name="SetSVarInt"/>
/// <seealso name="GetSVarInt"/>
/// <seealso name="GetSVarString"/>
/// <seealso name="SetSVarFloat"/>
/// <seealso name="GetSVarFloat"/>
/// <seealso name="DeleteSVar"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R2</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The variable name is null or over 40 characters.
/// </returns>
native SetSVarString(const varname[], const string_value[]);

/// <summary>Gets a string server variable's value.</summary>
/// <param name="varname">The name of the server variable (case-insensitive). Assigned in <a href="#SetSVarString">SetSVarString</a></param>
/// <param name="string_return">The array in which to store the string value in, passed by reference</param>
/// <param name="len">The maximum length of the returned string</param>
/// <seealso name="SetSVarInt"/>
/// <seealso name="GetSVarInt"/>
/// <seealso name="SetSVarString"/>
/// <seealso name="SetSVarFloat"/>
/// <seealso name="GetSVarFloat"/>
/// <seealso name="DeleteSVar"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R2</b> and will not work in earlier versions!</remarks>
/// <returns>The length of the string.</returns>
native GetSVarString(const varname[], string_return[], len = sizeof string_return);

/// <summary>Set a float server variable.</summary>
/// <param name="varname">The name of the server variable</param>
/// <param name="float_value">The float to be set</param>
/// <seealso name="SetSVarInt"/>
/// <seealso name="GetSVarInt"/>
/// <seealso name="SetSVarString"/>
/// <seealso name="GetSVarString"/>
/// <seealso name="GetSVarFloat"/>
/// <seealso name="DeleteSVar"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R2</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The variable name is null or over 40 characters.
/// </returns>
native SetSVarFloat(const varname[], Float:float_value);

/// <summary>Gets a float server variable's value.</summary>
/// <param name="varname">The name of the server variable (case-insensitive). Assigned in <a href="#SetSVarFloat">SetSVarFloat</a></param>
/// <seealso name="SetSVarInt"/>
/// <seealso name="GetSVarInt"/>
/// <seealso name="SetSVarString"/>
/// <seealso name="GetSVarString"/>
/// <seealso name="SetSVarFloat"/>
/// <seealso name="DeleteSVar"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7 R2</b> and will not work in earlier versions!</remarks>
/// <returns>The float value of the specified server variable. It will still return <b><c>0</c></b> if the variable is not set.</returns>
native Float:GetSVarFloat(const varname[]);

/// <summary>Deletes a previously set server variable.</summary>
/// <param name="varname">The name of the server variable to delete</param>
/// <seealso name="SetSVarInt"/>
/// <seealso name="GetSVarInt"/>
/// <seealso name="SetSVarString"/>
/// <seealso name="GetSVarString"/>
/// <seealso name="SetSVarFloat"/>
/// <seealso name="GetSVarFloat"/>
/// <remarks>Once a variable is deleted, attempts to retrieve the value will return <b><c>0</c></b> (for integers and floats and <b><c>NULL</c></b> for strings.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. There is no variable set with the given name.
/// </returns>
native DeleteSVar(const varname[]);

/// <summary>Each SVar (server-variable) has its own unique identification number for lookup, this function returns the highest ID.</summary>
/// <seealso name="GetSVarNameAtIndex"/>
/// <seealso name="GetSVarType"/>
/// <returns>The highest set SVar ID.</returns>
native GetSVarsUpperIndex();

/// <summary>Retrieve the name of a sVar via the index.</summary>
/// <param name="index">The index of the sVar</param>
/// <param name="ret_varname">A string to store the sVar's name in, passed by reference</param>
/// <param name="ret_len">The max length of the returned string</param>
/// <seealso name="GetSVarType"/>
/// <seealso name="GetSVarInt"/>
/// <seealso name="GetSVarFloat"/>
/// <seealso name="GetSVarString"/>
native GetSVarNameAtIndex(index, ret_varname[], ret_len = sizeof ret_varname);

/// <summary>Gets the type (integer, float or string) of a server variable.</summary>
/// <param name="varname">The name of the server variable to get the type of</param>
/// <seealso name="SetSVarInt"/>
/// <seealso name="GetSVarInt"/>
/// <seealso name="SetSVarString"/>
/// <seealso name="GetSVarString"/>
/// <seealso name="SetSVarFloat"/>
/// <seealso name="GetSVarFloat"/>
/// <seealso name="DeleteSVar"/>
/// <remarks>
///   <b>Variable types:</b><p/>
///   <ul>
///     <li><b><c>SERVER_VARTYPE_NONE</c></b> (sVar with name given does not exist)</li>
///     <li><b><c>SERVER_VARTYPE_INT</c></b></li>
///     <li><b><c>SERVER_VARTYPE_STRING</c></b></li>
///     <li><b><c>SERVER_VARTYPE_FLOAT</c></b></li>
///   </ul>
/// </remarks>
/// <returns>Returns the type of the SVar. See table below.</returns>
native GetSVarType(const varname[]);

// Game

/// <summary>Set the name of the game mode, which appears in the server browser.</summary>
/// <param name="string">The gamemode name to display</param>
native SetGameModeText(const string[]);


/// <summary>This function is used to change the amount of teams used in the gamemode. It has no obvious way of being used, but can help to indicate the number of teams used for better (more effective) internal handling. This function should only be used in the <a href="#OnGameModeInit">OnGameModeInit</a> callback. Important: You can pass 2 billion here if you like, this function has no effect at all.</summary>
/// <param name="count">Number of teams the gamemode knows</param>
/// <seealso name="GetPlayerTeam"/>
/// <seealso name="SetPlayerTeam"/>
native SetTeamCount(count);

/// <summary>Adds a class to class selection. Classes are used so players may spawn with a skin of their choice.</summary>
/// <param name="modelid">The <a href="http://wiki.sa-mp.com/wiki/Skins">skin</a> which the player will spawn with</param>
/// <param name="spawn_x">The X coordinate of the spawnpoint of this class</param>
/// <param name="spawn_y">The Y coordinate of the spawnpoint of this class</param>
/// <param name="spawn_z">The Z coordinate of the spawnpoint of this class</param>
/// <param name="z_angle">The direction in which the player should face after spawning</param>
/// <param name="weapon1">The first spawn-<a href="http://wiki.sa-mp.com/wiki/Weapons">weapon</a> for the player</param>
/// <param name="weapon1_ammo">The amount of ammunition for the primary spawn weapon</param>
/// <param name="weapon2">The second spawn-<a href="http://wiki.sa-mp.com/wiki/Weapons">weapon</a> for the player</param>
/// <param name="weapon2_ammo">The amount of ammunition for the second spawn weapon</param>
/// <param name="weapon3">The third spawn-<a href="http://wiki.sa-mp.com/wiki/Weapons">weapon</a> for the player</param>
/// <param name="weapon3_ammo">The amount of ammunition for the third spawn weapon</param>
/// <returns>
///   <ul>
///     <li>The <b>ID of the class</b> which was just added.</li>
///     <li><b><c>319</c></b> if the class limit (<b><c>320</c></b>) was reached. The highest possible class ID is <b><c>319</c></b>.</li>
///   </ul>
/// </returns>
/// <remarks>
///    The maximum class ID is <b><c>319</c></b> (starting from <b><c>0</c></b>, so a total of <b><c>320</c></b> classes).
///    When this limit is reached, any more classes that are added will replace ID <b><c>319</c></b>.
/// </remarks>
/// <seealso name="AddPlayerClassEx"/>
/// <seealso name="SetSpawnInfo"/>
/// <seealso name="SetPlayerSkin"/>
native AddPlayerClass(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);

/// <summary>This function is exactly the same as the <a href="#AddPlayerClass">AddPlayerClass</a> function, with the addition of a team parameter.</summary>
/// <param name="teamid">The team you want the player to spawn in</param>
/// <param name="modelid">The <a href="http://wiki.sa-mp.com/wiki/Skins">skin</a> which the player will spawn with</param>
/// <param name="spawn_x">The X coordinate of the class' spawn position</param>
/// <param name="spawn_y">The Y coordinate of the class' spawn position</param>
/// <param name="spawn_z">The Z coordinate of the class' spawn position</param>
/// <param name="z_angle">The direction in which the player will face after spawning</param>
/// <param name="weapon1">The first spawn-<a href="http://wiki.sa-mp.com/wiki/Weapons">weapon</a> for the player</param>
/// <param name="weapon1_ammo">The amount of ammunition for the first spawn weapon</param>
/// <param name="weapon2">The second spawn-<a href="http://wiki.sa-mp.com/wiki/Weapons">weapon</a> for the player</param>
/// <param name="weapon2_ammo">The amount of ammunition for the second spawn weapon</param>
/// <param name="weapon3">The third spawn-<a href="http://wiki.sa-mp.com/wiki/Weapons">weapon</a> for the player</param>
/// <param name="weapon3_ammo">The amount of ammunition for the third spawn weapon</param>
/// <returns>
///   <ul>
///     <li>The <b>ID of the class</b> which was just added.</li>
///     <li><b><c>319</c></b> if the class limit (<b><c>320</c></b>) was reached. The highest possible class ID is <b><c>319</c></b>.</li>
///   </ul>
/// </returns>
/// <remarks>The maximum class ID is <b><c>319</c></b> (starting from <b><c>0</c></b>, so a total of <b><c>320</c></b> classes). When this limit is reached, any more classes that are added will replace ID <b><c>319</c></b>.</remarks>
/// <seealso name="AddPlayerClass"/>
/// <seealso name="SetSpawnInfo"/>
/// <seealso name="SetPlayerTeam"/>
/// <seealso name="SetPlayerSkin"/>
native AddPlayerClassEx(teamid, modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, weapon1, weapon1_ammo, weapon2, weapon2_ammo, weapon3, weapon3_ammo);

/// <summary>Adds a 'static' vehicle (models are pre-loaded for players) to the gamemode.</summary>
/// <param name="modelid">The <a href="http://wiki.sa-mp.com/wiki/Vehicle_Models">Model ID</a> for the vehicle</param>
/// <param name="spawn_x">The X-coordinate for the vehicle</param>
/// <param name="spawn_y">The Y-coordinate for the vehicle</param>
/// <param name="spawn_z">The Z-coordinate for the vehicle</param>
/// <param name="z_angle">Direction of vehicle - angle</param>
/// <param name="color1">The primary <a href="http://wiki.sa-mp.com/wiki/Color_ID">color ID</a>. <b><c>-1</c></b> for random (random color chosen by client)</param>
/// <param name="color2">The secondary <a href="http://wiki.sa-mp.com/wiki/Color_ID">color ID</a>. <b><c>-1</c></b> for random (random color chosen by client)</param>
/// <returns>
///   <ul>
///     <li>The vehicle ID of the vehicle created (between <b><c>1</c></b> and <b><c>MAX_VEHICLES</c></b>).</li>
///     <li><b><c>INVALID_VEHICLE_ID</c></b> (<b><c>65535</c></b>) if vehicle was not created (vehicle limit reached or invalid vehicle model ID passed).</li>
///   </ul>
/// </returns>
/// <remarks>Can only be used when the server first starts (under <a href="#OnGameModeInit">OnGameModeInit</a>).</remarks>
/// <seealso name="AddStaticVehicleEx"/>
/// <seealso name="CreateVehicle"/>
/// <seealso name="DestroyVehicle"/>
native AddStaticVehicle(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2);

/// <summary>Adds a 'static' vehicle (models are pre-loaded for players)to the gamemode. Differs from <a href="#AddStaticVehicle">AddStaticVehicle</a> in only one way: allows a respawn time to be set for when the vehicle is left unoccupied by the driver.</summary>
/// <param name="modelid">The <a href="http://wiki.sa-mp.com/wiki/Vehicle_Models">Model ID</a> for the vehicle</param>
/// <param name="spawn_x">The X-coordinate for the vehicle</param>
/// <param name="spawn_y">The Y-coordinate for the vehicle</param>
/// <param name="spawn_z">The Z-coordinate for the vehicle</param>
/// <param name="z_angle">The facing - angle for the vehicle</param>
/// <param name="color1">The primary <a href="http://wiki.sa-mp.com/wiki/Color_ID">color ID</a>. <b><c>-1</c></b> for random (random color chosen by client)</param>
/// <param name="color2">The secondary <a href="http://wiki.sa-mp.com/wiki/Color_ID">color ID</a>. <b><c>-1</c></b> for random (random color chosen by client)</param>
/// <param name="respawn_delay">The delay until the car is respawned without a driver, in seconds</param>
/// <param name="addsiren"><b>Added in 0.3.7; will not work in earlier versions.</b> Enables the vehicle to have a siren, providing the vehicle has a horn (optional=<b><c>0</c></b>)</param>
/// <returns>
///   <ul>
///     <li>The vehicle ID of the vehicle created (between <b><c>1</c></b> and <b><c>MAX_VEHICLES</c></b>).</li>
///     <li><b><c>INVALID_VEHICLE_ID</c></b> (<b><c>65535</c></b>) if vehicle was not created (vehicle limit reached or invalid vehicle model ID passed).</li>
///   </ul>
/// </returns>
/// <remarks>Can only be used when the server first starts (under <a href="#OnGameModeInit">OnGameModeInit</a>).</remarks>
/// <seealso name="AddStaticVehicle"/>
/// <seealso name="CreateVehicle"/>
/// <seealso name="DestroyVehicle"/>
native AddStaticVehicleEx(modelid, Float:spawn_x, Float:spawn_y, Float:spawn_z, Float:z_angle, color1, color2, respawn_delay, addsiren=0);

/// <summary>This function adds a 'static' pickup to the game. These pickups support weapons, health, armor etc., with the ability to function without scripting them (weapons/health/armor will be given automatically).</summary>
/// <param name="model">The model of the pickup</param>
/// <param name="type">The pickup type. Determines how the pickup responds when picked up</param>
/// <param name="X">The X coordinate to create the pickup at</param>
/// <param name="Y">The Y coordinate to create the pickup at</param>
/// <param name="Z">The Z coordinate to create the pickup at</param>
/// <param name="virtualworld">The virtual world ID to put the pickup in. Use -1 to show the pickup in all worlds</param>
/// <returns>
///   <b><c>1</c></b> if the pickup is successfully created.
///   <p/>
///   <b><c>0</c></b> if failed to create.
/// </returns>
/// <remarks>This function doesn't return a pickup ID that you can use in, for example, <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a>. Use <a href="#CreatePickup">CreatePickup</a> if you'd like to assign IDs.</remarks>
/// <seealso name="CreatePickup"/>
/// <seealso name="DestroyPickup"/>
/// <seealso name="OnPlayerPickUpPickup"/>
native AddStaticPickup(model, type, Float:X, Float:Y, Float:Z, virtualworld = 0);

/// <summary>This function does exactly the same as AddStaticPickup, except it returns a pickup ID which can be used to destroy it afterwards and be tracked using <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a>.</summary>
/// <param name="model">The <a href="http://wiki.sa-mp.com/wiki/Pickup_IDs">model</a> of the pickup</param>
/// <param name="type">The pickup spawn type (see table under remarks)</param>
/// <param name="X">The X coordinate to create the pickup at</param>
/// <param name="Y">The Y coordinate to create the pickup at</param>
/// <param name="Z">The Z coordinate to create the pickup at</param>
/// <param name="virtualworld">The virtual world ID of the pickup. Use <b><c>-1</c></b> to make the pickup show in all worlds (optional=<b><c>0</c></b>)</param>
/// <seealso name="AddStaticPickup"/>
/// <seealso name="DestroyPickup"/>
/// <seealso name="OnPlayerPickUpPickup"/>
/// <remarks>
///   <b>Known Bugs:</b><p/>
///   Pickups that have a X or Y lower than <b><c>-4096.0</c></b> or bigger than <b><c>4096.0</c></b> won't show up and won't trigger <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a> either.
/// </remarks>
/// <remarks>
///   The only type of pickup that can be picked up from inside a vehicle is <b><c>14</c></b> (except for special pickups such as bribes).<p/>
///   Pickups are shown to, and can be picked up by all players.<p/>
///   It is possible that if <a href="#DestroyPickup">DestroyPickup</a> is used when a pickup is picked up, more than one player can pick up the pickup, due to lag. This can be circumvented through the use of variables.<p/>
///   Certain pickup types come with 'automatic responses', for example using an M4 model in the pickup will automatically give the player the weapon and some ammo. For fully scripted pickups, type <b><c>1</c></b> should be used. <p/>
/// </remarks>
/// <remarks>
///   <b>Available Pickup Types</b><p/>
///   Most other IDs are either undocumented or are similar to type <b><c>1</c></b> (but do not use them just because they seem similar to ID <b><c>1</c></b>, they might have side-effects like ID <b><c>18</c></b> and <b><c>20</c></b>).
///   <ul>
///     <li><b><c>0</c></b> - The pickup does not always display. If displayed, it can't be picked up and does not trigger <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a> and it will stay after server shutdown.</li>
///     <li><b><c>1</c></b> - Exists always. Disables pickup scripts such as horseshoes and oysters to allow for scripted actions ONLY. Will trigger <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a> every few seconds.</li>
///     <li><b><c>2</c></b> - Disappears after pickup, respawns after 30 seconds if the player is at a distance of at least 15 meters.</li>
///     <li><b><c>3</c></b> - Disappears after pickup, respawns after death.</li>
///     <li><b><c>4</c></b> - Disappears after 15 to 20 seconds. Respawns after death.</li>
///     <li><b><c>8</c></b> - Disappears after pickup, but has no effect.</li>
///     <li><b><c>11</c></b> - Blows up a few seconds after being created (bombs?)</li>
///     <li><b><c>12</c></b> - Blows up a few seconds after being created.</li>
///     <li><b><c>13</c></b> - Invisible. Triggers checkpoint sound when picked up with a vehicle, but doesn't trigger <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a>.</li>
///     <li><b><c>14</c></b> - Disappears after pickup, can only be picked up with a vehicle. Triggers checkpoint sound.</li>
///     <li><b><c>15</c></b> - Same as type <b><c>2</c></b>.</li>
///     <li><b><c>18</c></b> - Similar to type <b><c>1</c></b>. Pressing Tab (<b><c>KEY_ACTION</c></b>) makes it disappear but the key press doesn't trigger <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a>.</li>
///     <li><b><c>19</c></b> - Disappears after pickup, but doesn't respawn. Makes "cash pickup" sound if picked up.</li>
///     <li><b><c>20</c></b> - Similar to type <b><c>1</c></b>. Disappears when you take a picture of it with the Camera weapon, which triggers "Snapshot # out of 0" message. Taking a picture doesn't trigger <a href="#OnPlayerPickUpPickup">OnPlayerPickUpPickup</a>.</li>
///     <li><b><c>22</c></b> - Same as type <b><c>3</c></b>.</li>
///   </ul>
/// </remarks>
/// <returns>The ID of the created pickup, <b><c>-1</c></b> on failure (<a href="http://wiki.sa-mp.com/wiki/Limits">pickup max limit</a>).</returns>
native CreatePickup(model, type, Float:X, Float:Y, Float:Z, virtualworld = 0);

/// <summary>Destroys a pickup created with <a href="#CreatePickup">CreatePickup</a>.</summary>
/// <param name="pickup">The ID of the pickup to destroy (returned by <a href="#CreatePickup">CreatePickup</a>)</param>
/// <seealso name="CreatePickup"/>
/// <seealso name="OnPlayerPickUpPickup"/>
native DestroyPickup(pickup);

/// <summary>Toggle the drawing of nametags, health bars and armor bars above players.</summary>
/// <param name="show"><b><c>0</c></b> to disable, <b><c>1</c></b> to enable (enabled by default)</param>
/// <seealso name="DisableNameTagLOS"/>
/// <seealso name="ShowPlayerNameTagForPlayer"/>
/// <seealso name="ShowPlayerMarkers"/>
/// <remarks>This function can only be used in <a href="#OnGameModeInit">OnGameModeInit</a>. For other times, see <a href="#ShowPlayerNameTagForPlayer">ShowPlayerNameTagForPlayer</a>.</remarks>
native ShowNameTags(show);

/// <summary>Toggles player markers (blips on the radar). Must be used when the server starts (<a href="#OnGameModeInit">OnGameModeInit</a>). For other times, see <a href="#SetPlayerMarkerForPlayer">SetPlayerMarkerForPlayer</a>.</summary>
/// <param name="mode">The mode to use for markers. They can be streamed, meaning they are only visible to nearby players. See table below</param>
/// <seealso name="SetPlayerMarkerForPlayer"/>
/// <seealso name="LimitPlayerMarkerRadius"/>
/// <seealso name="ShowNameTags"/>
/// <seealso name="SetPlayerColor"/>
/// <remarks>
///   <b>Marker modes:</b><p/>
///   <ul>
///     <li><b><c>PLAYER_MARKERS_MODE_OFF</c></b> 0</li>
///     <li><b><c>PLAYER_MARKERS_MODE_GLOBAL</c></b> 1</li>
///     <li><b><c>PLAYER_MARKERS_MODE_STREAMED</c></b> 2</li>
///   </ul>
/// </remarks>
/// <remarks>It is also possible to set a player's color to a color that has full transparency (no alpha value). This makes it possible to show markers on a per-player basis.</remarks>
native ShowPlayerMarkers(mode);

/// <summary>Ends the current gamemode.</summary>
/// <seealso name="OnGameModeExit"/>
native GameModeExit();

/// <summary>Sets the world time (for all players) to a specific hour.</summary>
/// <param name="hour">The hour to set (<b><c>0</c></b>-<b><c>23</c></b>)</param>
/// <seealso name="SetPlayerTime"/>
/// <seealso name="SetWeather"/>
/// <seealso name="SetGravity"/>
/// <remarks>To set the minutes and/or to set the time for individual players, see <a href="#SetPlayerTime">SetPlayerTime</a>.</remarks>
/// <remarks>This function is only relevant for players that do not use a passing clock - see <a href="#TogglePlayerClock">TogglePlayerClock</a>.</remarks>
native SetWorldTime(hour);

/// <summary>Get the name of a weapon.</summary>
/// <param name="weaponid">The ID of the weapon to get the name of</param>
/// <param name="weapon">An array to store the weapon's name in, passed by reference</param>
/// <param name="len">The maximum length of the weapon name to store.</param>
/// <seealso name="GetPlayerWeapon"/>
/// <seealso name="AllowInteriorWeapons"/>
/// <seealso name="GivePlayerWeapon"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The weapon specified does not exist.
/// </returns>
native GetWeaponName(weaponid, weapon[], len = sizeof weapon);

/// <param name="enable"><b><c>1</c></b> to enable, <b><c>0</c></b> to disable tire popping</param>
/// <remarks>This function was removed in <b>SA-MP 0.3</b>. Tire popping is enabled by default. If you want to disable tire popping, you'll have to manually script it using <a href="#OnVehicleDamageStatusUpdate">OnVehicleDamageStatusUpdate</a>.</remarks>
native EnableTirePopping(enable); // deprecated function

/// <summary>Enable friendly fire for team vehicles. Players will be unable to damage teammates' vehicles (<a href="#SetPlayerTeam">SetPlayerTeam</a> must be used!).</summary>
/// <seealso name="SetPlayerTeam"/>
/// <remarks>This function was added in <b>SA-MP 0.3x</b> and will not work in earlier versions!</remarks>
native EnableVehicleFriendlyFire();

/// <summary>Toggle whether the usage of weapons in interiors is allowed or not.</summary>
/// <param name="allow"><b><c>1</c></b> to enable weapons in interiors (enabled by default), <b><c>0</c></b> to disable weapons in interiors</param>
/// <remarks>This function does not work in the current SA:MP version!</remarks>
/// <seealso name="SetPlayerInterior"/>
/// <seealso name="GetPlayerInterior"/>
/// <seealso name="OnPlayerInteriorChange"/>
native AllowInteriorWeapons(allow);


/// <summary>Set the world weather for all players.</summary>
/// <param name="weatherid">The <a href="http://wiki.sa-mp.com/wiki/WeatherID">weather</a> to set</param>
/// <seealso name="SetPlayerWeather"/>
/// <seealso name="SetGravity"/>
/// <remarks>If <a href="#TogglePlayerClock">TogglePlayerClock</a> is enabled, weather will slowly change over time, instead of changing instantly.</remarks>
native SetWeather(weatherid);

/// <summary>Get the currently set gravity.</summary>
/// <seealso name="SetGravity"/>
/// <returns>The current set gravity (as a float).</returns>
native Float:GetGravity();

/// <summary>Set the gravity for all players.</summary>
/// <param name="gravity">The value that the gravity should be set to (between -50 and 50)</param>
/// <seealso name="GetGravity"/>
/// <seealso name="SetWeather"/>
/// <seealso name="SetWorldTime"/>
/// <remarks>Default gravity is <b><c>0.008</c></b>.</remarks>
/// <returns>This function always returns <b><c>1</c></b>, even when it fails to execute if the gravity is out of the limits (lower than <b><c>-50.0</c></b> or higher than <b><c>+50.0</c></b>).</returns>
native SetGravity(Float:gravity);

/// <summary>This function will determine whether RCON admins will be teleported to their waypoint when they set one.</summary>
/// <param name="allow"><b><c>0</c></b> to disable and <b><c>1</c></b> to enable</param>
/// <remarks><b>This function, as of 0.3d, is deprecated. Please see <a href="#OnPlayerClickMap">OnPlayerClickMap</a>.</b></remarks>
/// <seealso name="IsPlayerAdmin"/>
/// <seealso name="AllowPlayerTeleport"/>
native AllowAdminTeleport(allow);

/// <summary>This function does not work in the current SA:MP version! </summary>
/// <seealso name="CreatePickup"/>
/// <seealso name="GivePlayerMoney"/>
/// <seealso name="OnPlayerDeath"/>
native SetDeathDropAmount(amount);

/// <summary>Create an explosion at the specified coordinates.</summary>
/// <param name="X">The X coordinate of the explosion</param>
/// <param name="Y">The Y coordinate of the explosion</param>
/// <param name="Z">The Z coordinate of the explosion</param>
/// <param name="type">The type of explosion</param>
/// <param name="Radius">The explosion radius</param>
/// <seealso name="CreateExplosionForPlayer"/>
/// <remarks>There is a limit as to how many explosions can be seen at once by a player. This is roughly 10.</remarks>
/// <returns>This function always returns <b><c>1</c></b>, even when the explosion type and/or radius values are invalid.</returns>
native CreateExplosion(Float:X, Float:Y, Float:Z, type, Float:Radius);

/// <summary>This function allows to turn on zone / area names such as the "Vinewood" or "Doherty" text at the bottom-right of the screen as they enter the area. This is a gamemode option and should be set in the callback <a href="#OnGameModeInit">OnGameModeInit</a>.</summary>
/// <param name="enable">A toggle option for whether or not you'd like zone names on or off</param>
/// <remarks><b>This function was removed in SA-MP 0.3. This was due to crashes it caused.</b></remarks>
native EnableZoneNames(enable);

/// <summary>Uses standard player walking animation (animation of the CJ skin) instead of custom animations for every skin (e.g. skating for skater skins).</summary>
/// <seealso name="ApplyAnimation"/>
/// <seealso name="ClearAnimations"/>
/// <remarks>Only works when placed under <a href="#OnGameModeInit">OnGameModeInit</a>.</remarks>
/// <remarks>Not using this function causes two-handed weapons (not dual-handed - a single weapon that is held by both hands) to be held in only one hand.</remarks>
native UsePlayerPedAnims(); // Will cause the players to use CJ running/walking animations

/// <summary>Disable all the interior entrances and exits in the game (the yellow arrows at doors).</summary>
/// <seealso name="AllowInteriorWeapons"/>
/// <remarks>If the gamemode is changed after this function has been used, and the new gamemode doesn't disable markers, the markers will NOT reappear for already-connected players (but will for newly connected players).</remarks>
/// <remarks>This function will only work if it has been used BEFORE a player connects (it is recommended to use it in OnGameModeInit). It will not remove a connected player's markers.</remarks>
/// <returns>This function always returns <b><c>1</c></b>.</returns>
native DisableInteriorEnterExits();  // will disable all interior enter/exits in the game.

/// <summary>Set the maximum distance to display the names of players.</summary>
/// <param name="distance">The distance to set</param>
/// <seealso name="LimitGlobalChatRadius"/>
/// <seealso name="ShowNameTags"/>
/// <seealso name="ShowPlayerNameTagForPlayer"/>
/// <remarks>Default distance is <b>70</b> SA units</remarks>
native SetNameTagDrawDistance(Float:distance); // Distance at which nametags will start rendering on the client.

/// <summary>Disables the nametag Line-Of-Sight checking so that players can see nametags through objects.</summary>
/// <seealso name="ShowNameTags"/>
/// <seealso name="ShowPlayerNameTagForPlayer"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This can not be reversed until the server restarts.</remarks>
native DisableNameTagLOS(); // Disables the nametag Line-Of-Sight checking

/// <summary>Set a radius limitation for the chat. Only players at a certain distance from the player will see their message in the chat. Also changes the distance at which a player can see other players on the map at the same distance.</summary>
/// <param name="chat_radius">The range in which players will be able to see chat</param>
/// <seealso name="SetNameTagDrawDistance"/>
/// <seealso name="SendPlayerMessageToPlayer"/>
/// <seealso name="SendPlayerMessageToAll"/>
/// <seealso name="OnPlayerText"/>
native LimitGlobalChatRadius(Float:chat_radius);

/// <summary>Set the player marker radius.</summary>
/// <param name="marker_radius">The radius that markers will show at</param>
/// <seealso name="ShowPlayerMarkers"/>
/// <seealso name="SetPlayerMarkerForPlayer"/>
/// <seealso name="LimitGlobalChatRadius"/>
/// <remarks>This Function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
native LimitPlayerMarkerRadius(Float:marker_radius);

// Npc

/// <summary>Connect an NPC to the server.</summary>
/// <param name="name">The name the NPC should connect as. Must follow the same rules as normal player names</param>
/// <param name="script">The NPC script name that is located in the <b>npcmodes</b> folder (without the .amx extension)</param>
/// <seealso name="IsPlayerNPC"/>
/// <seealso name="OnPlayerConnect"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>NPCs do not have nametags. These can be scripted with <a href="#Attach3DTextLabelToPlayer">Attach3DTextLabelToPlayer</a>.</remarks>
/// <returns>This function always return <b><c>1</c></b>.</returns>
native ConnectNPC(const name[], const script[]);

/// <summary>Check if a player is an actual player or an NPC.</summary>
/// <param name="playerid">The ID of the player to check</param>
/// <seealso name="ConnectNPC"/>
/// <seealso name="IsPlayerAdmin"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <returns><b><c>1</c></b> if the player is an NPC, <b><c>0</c></b> if not.</returns>
native IsPlayerNPC(playerid);

native AddCharModel(baseid, newid, const dffname[], const txdname[]);
native AddSimpleModel(virtualworld, baseid, newid, const dffname[], const txdname[]);
native AddSimpleModelTimed(virtualworld, baseid, newid, const dffname[], const txdname[], timeon, timeoff);
native FindModelFileNameFromCRC(crc, retstr[], retstr_size = sizeof retstr);
native FindTextureFileNameFromCRC(crc, retstr[], retstr_size = sizeof retstr);
native RedirectDownload(playerid, const url[]);

// Admin

/// <summary>Check if a player is logged in as an RCON admin.</summary>
/// <param name="playerid">The ID of the player to check</param>
/// <seealso name="SendRconCommand"/>
/// <seealso name="OnRconLoginAttempt"/>
/// <returns><b><c>1</c></b> if the player is an RCON admin, <b><c>0</c></b> if not.</returns>
native IsPlayerAdmin(playerid);

/// <summary>Kicks a player from the server. They will have to quit the game and re-connect if they wish to continue playing.</summary>
/// <param name="playerid">The ID of the player to kick</param>
/// <seealso name="Ban"/>
/// <seealso name="BanEx"/>
/// <remarks>As of <b>SA-MP 0.3x</b>, any action taken directly before Kick() (such as sending a message with <a href="#SendClientMessage">SendClientMessage</a>) will not reach the player. A timer must be used to delay the kick.</remarks>
/// <returns>This function always returns <b><c>1</c></b>, even if the function failed to execute (player specified doesn't exist).</returns>
native Kick(playerid);

/// <summary>Ban a player who is currently in the server. They will be unable to join the server ever again. The ban will be IP-based, and be saved in the samp.ban file in the server's root directory. <a href="#BanEx">BanEx</a> can be used to give a reason for the ban. IP bans can be added/removed using the RCON banip and unbanip commands (<a href="#SendRconCommand">SendRconCommand</a>).</summary>
/// <param name="playerid">The ID of the player to ban</param>
/// <seealso name="BanEx"/>
/// <seealso name="Kick"/>
/// <remarks>As of <b>SA-MP 0.3x</b>, any action taken directly before Ban() (such as sending a message with SendClientMessage) will not reach the player. A timer must be used to delay the ban.</remarks>
/// <remarks></remarks>
native Ban(playerid);

/// <summary>Ban a player with a reason.</summary>
/// <param name="playerid">The ID of the player to ban</param>
/// <param name="reason">The reason for the ban</param>
/// <seealso name="Ban"/>
/// <seealso name="Kick"/>
/// <remarks>As of <b>SA-MP 0.3x</b>, any action taken directly before Ban() (such as sending a message with SendClientMessage) will not reach the player. A timer must be used to delay the ban.</remarks>
native BanEx(playerid, const reason[]);


/// <summary>Sends an RCON (Remote Console) command.</summary>
/// <param name="command">The RCON command to be executed</param>
/// <seealso name="IsPlayerAdmin"/>
/// <seealso name="OnRconCommand"/>
/// <seealso name="OnRconLoginAttempt"/>
/// <remarks>Does not support login, due to the lack of a 'playerid' parameter.</remarks>
/// <remarks>'password 0' will remove the server's password if one is set.</remarks>
/// <returns>This function always returns <b><c>1</c></b>.</returns>
/// <remarks>This function will result in <a href="#OnRconCommand">OnRconCommand</a> being called.</remarks>
native SendRconCommand(const command[]);

/// <summary>Gets a player's network stats and saves them into a string.</summary>
/// <param name="playerid">The ID of the player you want to get the networkstats of</param>
/// <param name="retstr">The string to store the networkstats in, passed by reference</param>
/// <param name="retstr_size">The length of the string that should be stored</param>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3c R4</b> and will not work in earlier versions!</remarks>
/// <remarks>This function may not return accurate data when used under <a href="#OnPlayerDisconnect">OnPlayerDisconnect</a> if the player has quit normally. It usually returns accurate data if the player has been kicked or has timed out.</remarks>
native GetPlayerNetworkStats(playerid, retstr[], retstr_size = sizeof retstr);

/// <summary>Gets the server's network stats and stores them in a string.</summary>
/// <param name="retstr">The string to store the network stats in, passed by reference</param>
/// <param name="retstr_size">The length of the string to be stored</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3c R4</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <b>Example output:</b><p/>
///   <c>
///     Server Ticks: 200<p/>
///     Messages in Send buffer: 0<p/>
///     Messages sent: 142<p/>
///     Bytes sent: 8203<p/>
///     Acks sent: 11<p/>
///     Acks in send buffer: 0<p/>
///     Messages waiting for ack: 0<p/>
///     Messages resent: 0<p/>
///     Bytes resent: 0<p/>
///     Packetloss: 0.0%<p/>
///     Messages received: 54<p/>
///     Bytes received: 2204<p/>
///     Acks received: 0<p/>
///     Duplicate acks received: 0<p/>
///     Inst. KBits per second: 28.8<p/>
///     KBits per second sent: 10.0<p/>
///     KBits per second received: 2.7<p/>
///   </c>
/// </remarks>
/// <returns>This function always returns <b><c>1</c></b>.</returns>
native GetNetworkStats(retstr[], retstr_size = sizeof retstr);

/// <summary>Returns the SA-MP client version, as reported by the player.</summary>
/// <param name="playerid">The ID of the player to get the client version of</param>
/// <param name="version">The string to store the player's version in, passed by reference</param>
/// <param name="len">The maximum length of the version</param>
/// <seealso name="GetPlayerName"/>
/// <seealso name="GetPlayerPing"/>
/// <seealso name="GetPlayerIp"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>The string the version gets stored in will be empty if playerid is an NPC.</remarks>
/// <returns><b><c>1</c></b> on success and <b><c>0</c></b> on failure (if player specified doesn't exist).</returns>
native GetPlayerVersion(playerid, version[], len = sizeof version); // Returns the SA-MP client revision as reported by the player

/// <summary>Blocks an IP address from further communication with the server for a set amount of time (with wildcards allowed). Players trying to connect to the server with a blocked IP address will receive the generic "You are banned from this server." message. Players that are online on the specified IP before the block will timeout after a few seconds and, upon reconnect, will receive the same message.</summary>
/// <param name="ip_address">The IP to block</param>
/// <param name="timems">The time (in milliseconds) that the connection will be blocked for. <b><c>0</c></b> can be used for an indefinite block</param>
/// <seealso name="UnBlockIpAddress"/>
/// <seealso name="OnIncomingConnection"/>
/// <remarks>This function was added in <b>SA-MP 0.3z R2-2</b> and will not work in earlier versions!</remarks>
/// <remarks>Wildcards can be used with this function, for example blocking the IP <b><c>6.9.*.*</c></b> will block all IPs where the first two octets are <b><c>6</c></b> and <b><c>9</c></b> respectively. Any number can be in place of an asterisk.</remarks>
native BlockIpAddress(const ip_address[], timems);


/// <summary>Unblock an IP address that was previously blocked using <a href="#BlockIpAddress">BlockIpAddress</a>.</summary>
/// <param name="ip_address">The IP address to unblock</param>
/// <seealso name="BlockIpAddress"/>
/// <seealso name="OnIncomingConnection"/>
/// <remarks>This function was added in <b>SA-MP 0.3z R2-2</b> and will not work in earlier versions!</remarks>
native UnBlockIpAddress(const ip_address[]);

// Deprecated:

/// <summary>Get the string value of a server variable.</summary>
/// <param name="varname">The name of the string variable to get the value of</param>
/// <param name="buffer">An array into which to store the value, passed by reference</param>
/// <param name="len">The length of the string that should be stored</param>
/// <seealso name="GetServerVarAsInt"/>
/// <seealso name="GetServerVarAsBool"/>
/// <remarks>This function, as of <b>0.3.7 R2</b>, is deprecated. Please see <a href="#GetConsoleVarAsString">GetConsoleVarAsString</a></remarks>
/// <remarks>Using this function on anything other than a <b>string</b> (int, bool or float) or a <b>nonexistent</b> server variable, will <b>crash</b> your server! This is a bug.</remarks>
/// <remarks>Type 'varlist' in the server console to display a list of available server variables and their types.</remarks>
/// <remarks>When filterscripts or plugins is specified as the varname, this function only returns the name of the first specified filterscript or plugin. This is a bug.</remarks>
/// <returns>The length of the returned string. <b><c>0</c></b> if the specified server variable is not a string or doesn't exist.</returns>
native GetServerVarAsString(const varname[], buffer[], len = sizeof buffer);

/// <summary>Get the integer value of a server variable.</summary>
/// <param name="varname">The name of the integer variable to get the value of</param>
/// <seealso name="GetServerVarAsString"/>
/// <seealso name="GetServerVarAsBool"/>
/// <remarks>This function, as of <b>0.3.7 R2</b>, is deprecated. Please see <a href="#GetConsoleVarAsInt">GetConsoleVarAsInt</a></remarks>
/// <remarks>Type 'varlist' in the server console to display a list of available server variables and their types.</remarks>
/// <returns>The value of the specified server variable. 0 if the specified server variable is not an integer or doesn't exist.</returns>
native GetServerVarAsInt(const varname[]);

/// <summary>Get the boolean value of a server variable.</summary>
/// <param name="varname">The name of the boolean variable to get the value of</param>
/// <seealso name="GetServerVarAsString"/>
/// <seealso name="GetServerVarAsInt"/>
/// <remarks>This function, as of <b>0.3.7 R2</b>, is deprecated. Please see <a href="#GetConsoleVarAsBool">GetConsoleVarAsBool</a></remarks>
/// <remarks>Type 'varlist' in the server console to display a list of available server variables and their types.</remarks>
/// <returns>The value of the specified server variable. <b><c>0</c></b> if the specified server variable is not a boolean or doesn't exist.</returns>
native GetServerVarAsBool(const varname[]);
// These are the same 3 functions as above although they avoid the name ambiguity/conflict with the SVar system.

/// <summary>Get the string value of a console variable.</summary>
/// <param name="varname">The name of the string variable to get the value of</param>
/// <param name="buffer">An array into which to store the value, passed by reference</param>
/// <param name="len">The length of the string that should be stored</param>
/// <seealso name="GetConsoleVarAsInt"/>
/// <seealso name="GetConsoleVarAsBool"/>
/// <remarks>Type <b><c>varlist</c></b> in the server console to display a list of available console variables and their types.</remarks>
/// <remarks>When filterscripts or plugins are specified as the varname, this function only returns the name of the first specified filterscript or plugin.</remarks>
/// <remarks>Using this function with anything other than a <b>string</b> (integer, boolean or float) will cause your server to crash. Using it with a nonexistent console variable will also cause your server to crash.</remarks>
/// <returns>The length of the returned string. <b><c>0</c></b> if the specified console variable is not a string or doesn't exist.</returns>
native GetConsoleVarAsString(const varname[], buffer[], len = sizeof buffer);

/// <summary>Get the integer value of a console variable.</summary>
/// <param name="varname">The name of the integer variable to get the value of</param>
/// <seealso name="GetConsoleVarAsString"/>
/// <seealso name="GetConsoleVarAsBool"/>
/// <remarks>Type <b><c>varlist</c></b> in the server console to display a list of available console variables and their types.</remarks>
/// <returns>The value of the specified console variable. <b><c>0</c></b> if the specified console variable is not an integer or doesn't exist.</returns>
native GetConsoleVarAsInt(const varname[]);

/// <summary>Get the boolean value of a console variable.</summary>
/// <param name="varname">The name of the boolean variable to get the value of</param>
/// <seealso name="GetConsoleVarAsString"/>
/// <seealso name="GetConsoleVarAsInt"/>
/// <remarks>Type <b><c>varlist</c></b> in the server console to display a list of available console variables and their types.</remarks>
/// <returns>The value of the specified console variable. <b><c>0</c></b> if the specified console variable is not a boolean or doesn't exist.</returns>
native GetConsoleVarAsBool(const varname[]);

// Extended admin network stats

/// <summary>Gets the tick rate (like FPS) of the server.</summary>
/// <seealso name="GetNetworkStats"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <returns>The server tick rate (per second). Returns <b><c>0</c></b> when the server is just started.</returns>
native GetServerTickRate();

/// <summary>Gets the amount of time (in milliseconds) that a player has been connected to the server for.</summary>
/// <param name="playerid">The ID of the player to get the connected time of</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <remarks>The return value is not reset to zero after changing the game mode (using the RCON command "gmx").</remarks>
/// <returns>This function returns the amount of time (in milliseconds) that a player has been connected to the server for. <b><c>0</c></b> is returned if the player is not connected.</returns>
native NetStats_GetConnectedTime(playerid);

/// <summary>Gets the number of messages the server has received from the player.</summary>
/// <param name="playerid">The ID of the player to get the data from</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <returns>This function returns the number of messages the server has received from the player. <b><c>0</c></b> is returned if the player is not connected.</returns>
native NetStats_MessagesReceived(playerid);

/// <summary>Gets the amount of data (in bytes) that the server has received from the player.</summary>
/// <param name="playerid">The ID of the player to get the data from</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <returns>This function returns the number of bytes the server has received from the player. <b><c>0</c></b> is returned if the player is not connected.</returns>
native NetStats_BytesReceived(playerid);

/// <summary>Gets the number of messages the server has sent to the player.</summary>
/// <param name="playerid">The ID of the player to get the data from</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <returns>The number of messages the server has sent to the player.</returns>
native NetStats_MessagesSent(playerid);

/// <summary>Gets the amount of data (in bytes) that the server has sent to the player.</summary>
/// <param name="playerid">The ID of the player to get the data from</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <returns>This function returns the number of bytes the server has sent to the player. <b><c>0</c></b> is returned if the player is not connected.</returns>
native NetStats_BytesSent(playerid);

/// <summary>Gets the number of messages the player has received in the last second.</summary>
/// <param name="playerid">The ID of the player to get the data from</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <returns>the number of messages the player has received in the last second.</returns>
native NetStats_MessagesRecvPerSecond(playerid);

/// <summary>Gets the packet loss percentage of a player. Packet loss means data the player is sending to the server is being lost (or vice-versa).</summary>
/// <param name="playerid">The ID of the player to get the data from</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <remarks>Anything greater than 0.0% should already be a cause of concern. Anything greater than 1.0% is outright bad.</remarks>
/// <remarks>This function has been found to be currently unreliable the output is not as expected when compared to the client. Therefore this function should not be used as a packet loss kicker. </remarks>
/// <remarks>A more accurate packetloss function can be found here: <a href="http://forum.sa-mp.com/showpost.php?p=2488911&amp;postcount=984">http://forum.sa-mp.com/showpost.php?p=2488911&amp;postcount=984</a></remarks>
/// <returns>The percentage packet loss as a float. <b><c>0.0</c></b> if player not connected.</returns>
native Float:NetStats_PacketLossPercent(playerid);

/// <summary>Gets the player's current connection status.</summary>
/// <param name="playerid">The ID of the player to get the connection status of</param>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_GetIpPort"/>
/// <seealso name="IsPlayerConnected"/>
/// <seealso name="OnPlayerConnect"/>
/// <seealso name="OnPlayerDisconnect"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <b>Status:</b><p/>
///   <ul>
///     <li><b><c>0 - NO_ACTION</c></b></li>
///     <li><b><c>1 - DISCONNECT_ASAP</c></b></li>
///     <li><b><c>2 - DISCONNECT_ASAP_SILENTLY</c></b></li>
///     <li><b><c>3 - DISCONNECT_ON_NO_ACK</c></b></li>
///     <li><b><c>4 - REQUESTED_CONNECTION</c></b></li>
///     <li><b><c>5 - HANDLING_CONNECTION_REQUEST</c></b></li>
///     <li><b><c>6 - UNVERIFIED_SENDER</c></b></li>
///     <li><b><c>7 - SET_ENCRYPTION_ON_MULTIPLE_16_BYTE_PACKET</c></b></li>
///     <li><b><c>8 - CONNECTED</c></b></li>
///   </ul>
/// </remarks>
/// <returns>The player's connection status, as an integer value.</returns>
native NetStats_ConnectionStatus(playerid);

/// <summary>Get a player's IP and port.</summary>
/// <param name="playerid">The ID of the player to get the IP and port of</param>
/// <param name="ip_port">A string array to store the IP and port in, passed by reference</param>
/// <param name="ip_port_len">The maximum length of the IP/port. 22 is recommended</param>
/// <seealso name="GetPlayerIp"/>
/// <seealso name="GetPlayerNetworkStats"/>
/// <seealso name="GetNetworkStats"/>
/// <seealso name="NetStats_GetConnectedTime"/>
/// <seealso name="NetStats_MessagesReceived"/>
/// <seealso name="NetStats_BytesReceived"/>
/// <seealso name="NetStats_MessagesSent"/>
/// <seealso name="NetStats_BytesSent"/>
/// <seealso name="NetStats_MessagesRecvPerSecond"/>
/// <seealso name="NetStats_PacketLossPercent"/>
/// <seealso name="NetStats_ConnectionStatus"/>
/// <remarks>This function was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
native NetStats_GetIpPort(playerid, ip_port[], ip_port_len = sizeof ip_port);

// Menu

/// <summary>Creates a menu.</summary>
/// <param name="title">The title for the new menu</param>
/// <param name="columns">How many colums shall the new menu have</param>
/// <param name="x">The X position of the menu (640x460 canvas - <b><c>0</c></b> would put the menu at the far left)</param>
/// <param name="y">The Y position of the menu (640x460 canvas - <b><c>0</c></b> would put the menu at the far top)</param>
/// <param name="col1width">The width for the first column</param>
/// <param name="col2width">The width for the second column (optional=<b><c>0.0</c></b>)</param>
/// <seealso name="AddMenuItem"/>
/// <seealso name="SetMenuColumnHeader"/>
/// <seealso name="DestroyMenu"/>
/// <seealso name="ShowMenuForPlayer"/>
/// <seealso name="HideMenuForPlayer"/>
/// <seealso name="OnPlayerSelectedMenuRow"/>
/// <seealso name="OnPlayerExitedMenu"/>
/// <remarks>
///   This function merely CREATES the menu - <a href="#ShowMenuForPlayer">ShowMenuForPlayer</a> must be used to show it.<p/>
///   You can only create and access <b><c>2</c></b> columns (<b><c>0</c></b> and <b><c>1</c></b>).<p/>
///   If the title's length is equal to or greater than <b><c>32</c></b> chars the title is truncated to <b><c>30</c></b> characters.
/// </remarks>
/// <remarks>There is a limit of <b><c>12</c></b> items per menu, and a limit of <b><c>128</c></b> menus in total.</remarks>
/// <returns>The ID of the new menu or <b><c>-1</c></b> on failure.</returns>
native Menu:CreateMenu(const title[], columns, Float:x, Float:y, Float:col1width, Float:col2width = 0.0);

/// <summary>Destroys the specified menu.</summary>
/// <param name="menuid">The menu ID to destroy</param>
/// <seealso name="CreateMenu"/>
/// <seealso name="SetMenuColumnHeader"/>
/// <seealso name="AddMenuItem"/>
/// <seealso name="OnPlayerSelectedMenuRow"/>
/// <seealso name="OnPlayerExitedMenu"/>
/// <returns><b><c>1</c></b> if the destroying was successful, otherwise <b><c>0</c></b>.</returns>
native DestroyMenu(Menu:menuid);

/// <summary>Adds an item to a specified menu.</summary>
/// <param name="menuid">The menu id to add an item to</param>
/// <param name="column">The column to add the item to</param>
/// <param name="menutext">The text for the new menu item</param>
/// <remarks>
///   <ul>
///     <li>Crashes when passed an invalid menu ID.</li>
///     <li>You can only have <b><c>12</c></b> items per menu (13th goes to the right side of the header of column name (colored), 14th and higher not display at all).</li>
///     <li>You can only use <b><c>2</c></b> columns (<b><c>0</c></b> and <b><c>1</c></b>).</li>
///     <li>You can only add <b><c>8</c></b> color codes per one item (<b><c>~r~</c></b>, <b><c>~g~</c></b> etc.).</li>
///     <li>Maximum length of menu item is <b><c>31</c></b> symbols. </li>
///   </ul>
/// </remarks>
/// <returns>The index of the row this item was added to.</returns>
/// <seealso name="CreateMenu"/>
/// <seealso name="SetMenuColumnHeader"/>
/// <seealso name="DestroyMenu"/>
/// <seealso name="OnPlayerSelectedMenuRow"/>
/// <seealso name="OnPlayerExitedMenu"/>
native AddMenuItem(Menu:menuid, column, const menutext[]);

/// <summary>Sets the caption of a column in a menu.</summary>
/// <param name="menuid">ID of the menu to change</param>
/// <param name="column">The column (<b><c>0</c></b> or <b><c>1</c></b>) to set the header of</param>
/// <param name="columnheader">The caption text for the column</param>
/// <seealso name="AddMenuItem"/>
/// <seealso name="CreateMenu"/>
/// <seealso name="OnPlayerSelectedMenuRow"/>
/// <remarks>Crashes when passed an invalid menu ID.</remarks>
/// <remarks>Note that you can add only <b><c>12</c></b> items with <a href="#AddMenuItem">AddMenuItem</a>. The 13th object of a menu would replace the header of the column which is correctly set with this function.</remarks>
native SetMenuColumnHeader(Menu:menuid, column, const columnheader[]);

/// <summary>Shows a previously created menu for a player.</summary>
/// <param name="menuid">The ID of the menu to show. Returned by CreateMenu</param>
/// <param name="playerid">The ID of the player to whom the menu will be shown</param>
/// <seealso name="CreateMenu"/>
/// <seealso name="AddMenuItem"/>
/// <seealso name="SetMenuColumnHeader"/>
/// <seealso name="ShowPlayerDialog"/>
/// <seealso name="OnPlayerSelectedMenuRow"/>
/// <seealso name="OnPlayerExitedMenu"/>
/// <remarks>Crashes the both server and player if an invalid menu ID given.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. Menu and/or player doesn't exist.
/// </returns>
native ShowMenuForPlayer(Menu:menuid, playerid);

/// <summary>Hides a menu for a player.</summary>
/// <param name="menuid">The ID of the menu to hide. Returned by <a href="#CreateMenu">CreateMenu</a> and passed to <a href="#OnPlayerSelectedMenuRow">OnPlayerSelectedMenuRow</a></param>
/// <param name="playerid">The ID of the player that the menu will be hidden for</param>
/// <seealso name="ShowMenuForPlayer"/>
/// <seealso name="AddMenuItem"/>
/// <seealso name="SetMenuColumnHeader"/>
/// <seealso name="CreateMenu"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute.
/// </returns>
native HideMenuForPlayer(Menu:menuid, playerid);

/// <summary>Check if a menu ID is vliad.</summary>
/// <param name="menuid">The menu to check for existance</param>
/// <seealso name="CreateMenu"/>
/// <seealso name="DestroyMenu"/>
/// <returns><b><c>1</c></b> if the menu is valid, otherwise <b><c>0</c></b>.</returns>
native IsValidMenu(Menu:menuid);

/// <summary>Disable a menu.</summary>
/// <param name="menuid">The ID of the menu to disable</param>
/// <seealso name="CreateMenu"/>
/// <seealso name="DestroyMenu"/>
/// <seealso name="AddMenuItem"/>
/// <remarks>Crashes when passed an invalid menu ID.</remarks>
native DisableMenu(Menu:menuid);

/// <summary>Disable a specific row in a menu <b>for all players</b>. It will be greyed-out and can't be selected by players.</summary>
/// <param name="menuid">The ID of the menu to disable a row of. Ensure this is valid, as an invalid menu ID will crash the entire server</param>
/// <param name="row">The ID of the row to disable (rows start at 0)</param>
/// <seealso name="CreateMenu"/>
/// <seealso name="DestroyMenu"/>
/// <seealso name="AddMenuItem"/>
/// <remarks>
///   Crashes when passed an invalid menu ID.<p/>
///   This function disabled the specified menu row for <b>all players</b>. There is no function to disable a menu row for a specific player. You'd have to create two menus - one with a row disabled, and one without. Or one per player.
/// </remarks>
/// <returns>This function always returns <b><c>1</c></b>, even if the function fails. If an invalid row is specified, nothing will happen. If an invalid menu ID is specified, the server will crash.</returns>
native DisableMenuRow(Menu:menuid, row);

/// <summary>Gets the ID of the menu the player is currently viewing (shown by <a href="#ShowMenuForPlayer">ShowMenuForPlayer</a>).</summary>
/// <param name="playerid">The ID of the player to get the current menu of</param>
/// <seealso name="ShowMenuForPlayer"/>
/// <seealso name="HideMenuForPlayer"/>
/// <seealso name="CreateMenu"/>
/// <seealso name="DestroyMenu"/>
/// <seealso name="AddMenuItem"/>
/// <seealso name="OnPlayerSelectedMenuRow"/>
/// <seealso name="OnPlayerExitedMenu"/>
/// <remarks>Returns previous menu when none is displayed.</remarks>
/// <returns>The ID of the player's currently shown menu, or <b><c>INVALID_MENU</c></b> (<b><c>255</c></b>) if no menu shown.</returns>
native Menu:GetPlayerMenu(playerid);

/// <summary>Creates a textdraw. Textdraws are, as the name implies, text (mainly - there can be boxes, sprites and model previews (skins/vehicles/weapons/objects too) that is drawn on a player's screens.</summary>
/// <param name="x">The X (left/right) coordinate to create the textdraw at</param>
/// <param name="y">The Y (up/down) coordinate to create the textdraw at</param>
/// <param name="text">The text that will appear in the textdraw</param>
/// <remarks>
///   If you choose values for y that are less than 1, the first text row will be invisible and only the shadow is visible.<p/>
///   text[] must not be empty or the server will crash! If you need a textdraw that shows nothing, use a space underscore. <b>Now it's fixed</b>.<p/>
///   If the last character in the text is a space, the text will all be blank.<p/>
///   If part of the text is off-screen, the color of the text will not show, only the shadow (if enabled) will.
/// </remarks>
/// <remarks>
///   <em>This applies ONLY to sa-mp versions before 0.3z:</em><p/>
///   Maximum length of textdraw is <b>800</b> characters. Longer text will crash the client in older versions.<p/>
///   If you use color codes (such as <b><c>~R~ ~G~</c></b>) beyond 255th character the client will crash trying to display the textdraw.
/// </remarks>
/// <remarks>
///   The x,y coordinate is the top left coordinate for the text draw area based on a 640x480 "canvas" (irrespective of screen resolution). If you plan on using <a href="#TextDrawAlignment">TextDrawAlignment</a> with alignment <b><c>3</c></b> (right), the x,y coordinate is the top right coordinate for the text draw.<p/>
///   This function merely CREATES the textdraw, you must use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a> or <a href="#TextDrawShowForAll">TextDrawShowForAll</a> to show it.<p/>
///   It is recommended to use WHOLE numbers instead of decimal positions when creating textdraws to ensure resolution friendly design.
/// </remarks>
/// <remarks>Keyboard key mapping codes (such as <b><c>~k~~VEHICLE_ENTER_EXIT~</c></b> don't work beyond 255th character. </remarks>
/// <returns>The ID of the created textdraw. Textdraw IDs start at <b><c>0</c></b>.</returns>
native Text:TextDrawCreate(Float:x, Float:y, const text[]);

/// <summary>Destroys a previously-created textdraw.</summary>
/// <param name="text">The ID of the textdraw to destroy. Returned by <a href="#TextDrawCreate">TextDrawCreate</a></param>
native TextDrawDestroy(Text:text);

/// <summary>Sets the width and height of the letters.</summary>
/// <param name="text">The TextDraw to change</param>
/// <param name="x">Width of a char</param>
/// <param name="y">Height of a char</param>
/// <remarks>When using this function purely for the benefit of affecting the TextDraw box, multiply 'Y' by <b><c>0.135</c></b> to convert to <a href="#TextDrawTextSize">TextDrawTextSize</a>-like measurements. <b>Hint</b>: it is easier and extremely precise to use <b><c>LD_SPAC:white</c></b> sprite for box-only textdraws, <a href="#TextDrawTextSize">TextDrawTextSize</a> will have regular offsets.</remarks>
/// <remarks>If you want to change the letter size of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible. </remarks>
/// <remarks>Fonts appear to look the best with an X to Y ratio of <b><c>1</c></b> to <b><c>4</c></b> (e.g. if x is <b><c>0.5</c></b> then y should be <b><c>2</c></b>). </remarks>
native TextDrawLetterSize(Text:text, Float:x, Float:y);

/// <summary>Change the size of a textdraw (box if <a href="#TextDrawUseBox">TextDrawUseBox</a> is enabled and/or clickable area for use with <a href="#TextDrawSetSelectable">TextDrawSetSelectable</a>).</summary>
/// <param name="text">The TextDraw to set the size of</param>
/// <param name="x">The size on the X axis (left/right) following the same 640x480 grid as <a href="#TextDrawCreate">TextDrawCreate</a></param>
/// <param name="y">The size on the Y axis (up/down) following the same 640x480 grid as <a href="#TextDrawCreate">TextDrawCreate</a></param>
/// <remarks>
///   The x and y have different meanings with different TextDrawAlignment values:<p/>
///   <ul>
///     <li><b><c>1</c></b> (left): they are the right-most corner of the box, absolute coordinates.</li>
///     <li><b><c>2</c></b> (center): they need to inverted (switch the two) and the x value is the overall width of the box.</li>
///     <li><b><c>3</c></b> (right): the x and y are the coordinates of the left-most corner of the box </li>
///   </ul>
/// </remarks>
/// <remarks>
///   Using font type <b><c>4</c></b> (sprite) and <b><c>5</c></b> (model preview) converts X and Y of this function from corner coordinates to WIDTH and HEIGHT (offsets).<p/>
///   The TextDraw box starts <b><c>10.0</c></b> units up and <b><c>5.0</c></b> to the left as the origin (<a href="#TextDrawCreate">TextDrawCreate</a> coordinate).<p/>
///   This function defines the clickable area for use with <a href="#TextDrawSetSelectable">TextDrawSetSelectable</a>, whether a box is shown or not.
/// </remarks>
/// <remarks>If you want to change the text size of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible.</remarks>
native TextDrawTextSize(Text:text, Float:x, Float:y);

/// <summary>Set the alignment of text in a text draw.</summary>
/// <param name="text">The ID of the textdraw to set the alignment of</param>
/// <param name="alignment"><b><c>1</c></b>-left <b><c>2</c></b>-centered <b><c>3</c></b>-right</param>
/// <remarks>For alignment <b><c>2</c></b> (center) the x and y values of <a href="#TextSize">TextSize</a> need to be swapped, see notes at <a href="#TextDrawTextSize">TextDrawTextSize</a>, also position coordinate become position of center of textdraw and not left/top edges. </remarks>
native TextDrawAlignment(Text:text, alignment);

/// <summary>Sets the text color of a textdraw.</summary>
/// <param name="text">The ID of the textdraw to change the color of.</param>
/// <param name="color">The color to set the textdraw to</param>
/// <remarks>You can also use GameText Colors in TextDraws.</remarks>
/// <remarks>If the TextDraw is already shown, it must be re-shown (<a href="#TextDrawShowForAll">TextDrawShowForAll</a>/<a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>) for the changes of this function to take effect.</remarks>
native TextDrawColor(Text:text, color);

/// <summary>Toggle whether a textdraw uses a box or not.</summary>
/// <param name="text">The ID of the text textdraw to toggle the box of</param>
/// <param name="use"><b><c>1</c></b> to show a box or <b><c>0</c></b> to not show a box</param>
/// <remarks>If the textdraw is already shown, it must be re-shown (<a href="#TextDrawShowForAll">TextDrawShowForAll</a>/<a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>) to show the changes of this function.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the textdraw specified does not exist.
/// </returns>
native TextDrawUseBox(Text:text, use);

/// <summary>Adjusts the text box colour (only used if <a href="#TextDrawUseBox">TextDrawUseBox</a> 'use' parameter is <b><c>1</c></b>).</summary>
/// <param name="text">The TextDraw to change</param>
/// <param name="color">The colour (<b>RGBA</b>)</param>
/// <remarks>If you want to change the boxcolour of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible.</remarks>
native TextDrawBoxColor(Text:text, color);

/// <summary>Sets the size of a textdraw's text's shadow.</summary>
/// <param name="text">The ID of the textdraw to set the shadow size of</param>
/// <param name="size">The size of the shadow. <b><c>1</c></b> is generally used for a normal shadow size. <b><c>0</c></b> disables the shadow completely</param>
/// <remarks>The shadow can be cut by the box area if the size is set too big for the area.</remarks>
/// <remarks>If you want to change the shadow of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The textdraw does not exist.
/// </returns>
native TextDrawSetShadow(Text:text, size);

/// <summary>Sets the thickness of a textdraw's text's outline. <a href="#TextDrawBackgroundColor">TextDrawBackgroundColor</a> can be used to change the color.</summary>
/// <param name="text">The ID of the text draw to set the outline thickness of</param>
/// <param name="size">The thickness of the outline, as an integer. <b><c>0</c></b> for no outline</param>
/// <remarks>If you want to change the outline of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible.</remarks>
native TextDrawSetOutline(Text:text, size);

/// <summary>Adjusts the text draw area background color (the outline/shadow - NOT the box. For box color, see <a href="#TextDrawBoxColor">TextDrawBoxColor</a>).</summary>
/// <param name="text">The ID of the textdraw to set the background color of</param>
/// <param name="color">The color that the textdraw should be set to</param>
/// <remarks>If <a href="#TextDrawSetOutline">TextDrawSetOutline</a> is used with size &gt; <b><c>0</c></b>, the outline color will match the color used in <a href="#TextDrawBackgroundColor">TextDrawBackgroundColor</a>. Changing the value of color seems to alter the color used in <a href="#TextDrawColor">TextDrawColor</a></remarks>
/// <remarks>If you want to change the background colour of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible.</remarks>
native TextDrawBackgroundColor(Text:text, color);

/// <summary>Changes the text font.</summary>
/// <param name="text">The TextDraw to change</param>
/// <param name="font">There are four font styles, see <a href="http://wiki.sa-mp.com/wiki/PlayerTextDrawFont">http://wiki.sa-mp.com/wiki/PlayerTextDrawFont</a>. Font value <b><c>4</c></b> specifies that this is a txd sprite; <b><c>5</c></b> specifies that this textdraw can display preview models. A font value greater than 5 does not display, and anything greater than 16 crashes the client</param>
/// <remarks>If you want to change the font of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible.</remarks>
native TextDrawFont(Text:text, font);

/// <summary>Appears to scale text spacing to a proportional ratio. Useful when using <a href="#TextDrawLetterSize">TextDrawLetterSize</a> to ensure the text has even character spacing.</summary>
/// <param name="text">The ID of the textdraw to set the proportionality of</param>
/// <param name="set"><b><c>1</c></b> to enable proportionality, <b><c>0</c></b> to disable</param>
/// <remarks>Proportionality is set to <b><c>1</c></b> by default, you might skip this function if you don't want to disable it. </remarks>
/// <remarks>If you want to change the proportionality of a textdraw that is already shown, you don't have to recreate it. Simply use <a href="#TextDrawShowForPlayer">TextDrawShowForPlayer</a>/<a href="#TextDrawShowForAll">TextDrawShowForAll</a> after modifying the textdraw and the change will be visible. </remarks>
native TextDrawSetProportional(Text:text, set);

/// <summary>Sets whether a textdraw can be selected (clicked on) or not.</summary>
/// <param name="text">The ID of the textdraw to make selectable</param>
/// <param name="set"><b><c>1</c></b> to make it selectable, or <b><c>0</c></b> to make it not selectable</param>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks><a href="#TextDrawSetSelectable">TextDrawSetSelectable</a> must be used BEFORE the textdraw is shown to players for it to be selectable.</remarks>
/// <remarks>Use <a href="#TextDrawTextSize">TextDrawTextSize</a> to define the clickable area.</remarks>
native TextDrawSetSelectable(Text:text, set);

/// <summary>Shows a textdraw for a specific player.</summary>
/// <param name="playerid">The ID of the player to show the textdraw for</param>
/// <param name="text">The ID of the textdraw to show. Returned by <a href="#TextDrawCreate">TextDrawCreate</a></param>
/// <remarks>If only a single player will see a textdraw, it might be wise to use player-textdraws instead. This is also useful for textdraws that need to show information specific for an individual player.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means either the player and/or textdraw specified does not exist.
/// </returns>
native TextDrawShowForPlayer(playerid, Text:text);

/// <summary>Hides a textdraw for a specific player.</summary>
/// <param name="playerid">The ID of the player that the textdraw should be hidden for</param>
/// <param name="text">The ID of the textdraw to hide</param>
/// <seealso name="TextDrawHideForAll"/>
/// <seealso name="TextDrawShowForPlayer"/>
/// <seealso name="TextDrawShowForAll"/>
native TextDrawHideForPlayer(playerid, Text:text);

/// <summary>Shows a textdraw for all players.</summary>
/// <param name="text">The ID of the textdraw to show. Returned by <a href="#TextDrawCreate">TextDrawCreate</a></param>
/// <seealso name="TextDrawShowForPlayer"/>
/// <seealso name="TextDrawHideForPlayer"/>
/// <seealso name="TextDrawHideForAll"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the textdraw specified does not exist.
/// </returns>
native TextDrawShowForAll(Text:text);

/// <summary>Hides a text draw for all players.</summary>
/// <param name="text">The ID of the textdraw to hide (returned by <a href="#TextDrawCreate">TextDrawCreate</a>)</param>
/// <seealso name="TextDrawShowForPlayer"/>
/// <seealso name="TextDrawHideForPlayer"/>
/// <seealso name="TextDrawShowForAll"/>
native TextDrawHideForAll(Text:text);

/// <summary>Changes the text on a textdraw.</summary>
/// <param name="text">The TextDraw to change</param>
/// <param name="string">The new string for the TextDraw</param>
/// <remarks>There are limits to the length of textdraw strings - see <a href="http://wiki.sa-mp.com/wiki/Limits">here</a> for more info.</remarks>
native TextDrawSetString(Text:text, const string[]);

/// <summary>Set the model for a textdraw model preview. Click <a href="http://www.sa-mp.com/stuff/03xShots/pmenu.png">here</a> to see this function's effect.</summary>
/// <param name="text">The textdraw id that will display the 3D preview</param>
/// <param name="modelindex">The GTA SA or SA:MP model ID to display</param>
/// <remarks>This function was added in <b>SA-MP 0.3x</b> and will not work in earlier versions!</remarks>
/// <remarks>The textdraw MUST use the font type <b><c>TEXT_DRAW_FONT_MODEL_PREVIEW</c></b> in order for this function to have effect.</remarks>
/// <remarks>Use <a href="#TextDrawBackgroundColor">TextDrawBackgroundColor</a> to set the background color behind the model.</remarks>
native TextDrawSetPreviewModel(Text:text, modelindex);

/// <summary>Sets the rotation and zoom of a 3D model preview textdraw.</summary>
/// <param name="fRotX">The X rotation value</param>
/// <param name="fRotY">The Y rotation value</param>
/// <param name="fRotZ">The Z rotation value</param>
/// <param name="fZoom">The zoom value, smaller values make the camera closer and larger values make the camera further away (optional=<b><c>1.0</c></b>)</param>
/// <remarks>This function was added in <b>SA-MP 0.3x</b> and will not work in earlier versions!</remarks>
/// <remarks>The textdraw MUST use the font type <b><c>TEXT_DRAW_FONT_MODEL_PREVIEW</c></b> in order for this function to have effect.</remarks>
native TextDrawSetPreviewRot(Text:text, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fZoom = 1.0);

/// <summary>If a vehicle model is used in a 3D preview textdraw, this sets the two colour values for that vehicle.</summary>
/// <param name="text">The textdraw id that is set to display a 3D vehicle model preview</param>
/// <param name="color1">The primary Color ID to set the vehicle to</param>
/// <param name="color2">The secondary Color ID to set the vehicle to</param>
/// <remarks>This function was added in <b>SA-MP 0.3x</b> and will not work in earlier versions!</remarks>
/// <remarks>The textdraw MUST use the font type <b><c>TEXT_DRAW_FONT_MODEL_PREVIEW</c></b> in order for this function to have effect.</remarks>
native TextDrawSetPreviewVehCol(Text:text, color1, color2);

// Gang Zones

/// <summary>Create a gangzone (colored radar area).</summary>
/// <param name="minx">The X coordinate for the west side of the gangzone</param>
/// <param name="miny">The Y coordinate for the south side of the gangzone</param>
/// <param name="maxx">The X coordinate for the east side of the gangzone</param>
/// <param name="maxy">The Y coordinate for the north side of the gangzone</param>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
/// <remarks>
///   There is a limit of <b><c>1024</c></b> gangzones.<p/>
///   Putting the parameters in the wrong order results in glitchy behavior.
/// </remarks>
/// <remarks>This function merely CREATES the gangzone, you must use <a href="#GangZoneShowForPlayer">GangZoneShowForPlayer</a> or <a href="#GangZoneShowForAll">GangZoneShowForAll</a> to show it.</remarks>
/// <returns>The ID of the created zone, returns <b><c>-1</c></b> if not created.</returns>
native GangZoneCreate(Float:minx, Float:miny, Float:maxx, Float:maxy);

/// <summary>Destroy a gangzone.</summary>
/// <param name="zone">The ID of the zone to destroy</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
native GangZoneDestroy(zone);

/// <summary>Show a gangzone for a player. Must be created with <a href="#GangZoneCreate">GangZoneCreate</a> first.</summary>
/// <param name="playerid">The ID of the player you would like to show the gangzone for.</param>
/// <param name="zone">The ID of the gang zone to show for the player. Returned by <a href="#GangZoneCreate">GangZoneCreate</a></param>
/// <param name="color">The color to show the gang zone, as an integer or hex in <b>RGBA</b> color format. Alpha transparency supported</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
/// <returns><b><c>1</c></b> if the gangzone was shown, otherwise <b><c>0</c></b> (non-existant).</returns>
native GangZoneShowForPlayer(playerid, zone, color);

/// <summary>Shows a gangzone with the desired color to all players.</summary>
/// <param name="zone">The ID of the gangzone to show (returned by <a href="# GangZoneCreate">GangZoneCreate</a>)</param>
/// <param name="color">The color to show the gang zone, as an integer or hex in <b>RGBA</b> color format. Alpha transparency supported</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully. The gang zone was shown for all players.<p/>
///   <b><c>0</c></b>: The function failed to execute. The gangzone does not exist.
/// </returns>
native GangZoneShowForAll(zone, color);

/// <summary>Hides a gangzone for a player.</summary>
/// <param name="playerid">The ID of the player to hide the gangzone for</param>
/// <param name="zone">The ID of the zone to hide</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
native GangZoneHideForPlayer(playerid, zone);

/// <summary>GangZoneHideForAll hides a gangzone from all players.</summary>
/// <param name="zone">The zone to hide</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
native GangZoneHideForAll(zone);

/// <summary>Makes a gangzone flash for a player.</summary>
/// <param name="playerid">The ID of the player to flash the gangzone for</param>
/// <param name="zone">The ID of the zone to flash</param>
/// <param name="flashcolor">The color to flash the gang zone, as an integer or hex in <b>RGBA</b> color format. Alpha transparency supported</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
native GangZoneFlashForPlayer(playerid, zone, flashcolor);

/// <summary>GangZoneFlashForAll flashes a gangzone for all players.</summary>
/// <param name="zone">The zone to flash</param>
/// <param name="flashcolor">The color to flash the gang zone, as an integer or hex in <b>RGBA</b> color format. Alpha transparency supported</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <seealso name="GangZoneStopFlashForAll"/>
native GangZoneFlashForAll(zone, flashcolor);

/// <summary>Stops a gangzone flashing for a player.</summary>
/// <param name="playerid">The ID of the player to stop the gangzone flashing for</param>
/// <param name="zone">The ID of the gangzonezone to stop flashing</param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForAll"/>
native GangZoneStopFlashForPlayer(playerid, zone);

/// <summary>Stops a gangzone flashing for all players.</summary>
/// <param name="zone">The ID of the zone to stop flashing. Returned by <a href="#GangZoneCreate">GangZoneCreate</a></param>
/// <seealso name="GangZoneCreate"/>
/// <seealso name="GangZoneDestroy"/>
/// <seealso name="GangZoneShowForPlayer"/>
/// <seealso name="GangZoneShowForAll"/>
/// <seealso name="GangZoneHideForPlayer"/>
/// <seealso name="GangZoneHideForAll"/>
/// <seealso name="GangZoneFlashForPlayer"/>
/// <seealso name="GangZoneFlashForAll"/>
/// <seealso name="GangZoneStopFlashForPlayer"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully. Success is reported even if the gang zone wasn't flashing to begin with.<p/>
///   <b><c>0</c></b>: The function failed to execute. The gangzone specified does not exist.
/// </returns>
native GangZoneStopFlashForAll(zone);

// Global 3D Text Labels

/// <summary>Creates a 3D Text Label at a specific location in the world.</summary>
/// <param name="text">The initial text string</param>
/// <param name="color">The text Color, as an integer or hex in <b>RGBA</b> color format</param>
/// <param name="X">X-Coordinate</param>
/// <param name="Y">Y-Coordinate</param>
/// <param name="Z">Z-Coordinate</param>
/// <param name="DrawDistance">The distance from where you are able to see the 3D Text Label</param>
/// <param name="virtualworld">The virtual world in which you are able to see the 3D Text</param>
/// <param name="testLOS">Test the line-of-sight so this text can't be seen through objects (optional=<b><c>0</c></b>)</param>
/// <seealso name="Delete3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToPlayer"/>
/// <seealso name="Attach3DTextLabelToVehicle"/>
/// <seealso name="Update3DTextLabelText"/>
/// <seealso name="CreatePlayer3DTextLabel"/>
/// <seealso name="DeletePlayer3DTextLabel"/>
/// <seealso name="UpdatePlayer3DTextLabelText"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   If <paramref name="text"/> is empty, the server/clients next to the text might crash!<p/>
///   If the virtualworld is set as <b><c>-1</c></b> the text will not appear.
/// </remarks>
/// <remarks>drawdistance seems to be a lot smaller when spectating.</remarks>
/// <remarks>Use <a href="http://wiki.sa-mp.com/wiki/Colors_List#Inline_color_embedding">color embedding</a> for multiple colors in the text.</remarks>
/// <returns>The ID of the newly created 3D Text Label, or <b><c>INVALID_3DTEXT_ID</c></b> if the 3D Text Label limit (<b><c>MAX_3DTEXT_GLOBAL</c></b>) was reached.</returns>
native Text3D:Create3DTextLabel(const text[], color, Float:X, Float:Y, Float:Z, Float:DrawDistance, virtualworld, testLOS=0);

/// <summary>Delete a 3D text label (created with <a href="#Create3DTextLabel">Create3DTextLabel</a>).</summary>
/// <param name="id">The ID of the 3D text label to delete</param>
/// <seealso name="Create3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToPlayer"/>
/// <seealso name="Attach3DTextLabelToVehicle"/>
/// <seealso name="Update3DTextLabelText"/>
/// <seealso name="CreatePlayer3DTextLabel"/>
/// <seealso name="DeletePlayer3DTextLabel"/>
/// <seealso name="UpdatePlayer3DTextLabelText"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <returns><b><c>1</c></b> if the 3D text label was deleted, otherwise <b><c>0</c></b>.</returns>
native Delete3DTextLabel(Text3D:id);

/// <summary>Attach a 3D text label to a player.</summary>
/// <param name="id">The ID of the 3D text label to attach. Returned by <a href="#Create3DTextLabel">Create3DTextLabel</a></param>
/// <param name="playerid">The ID of the player to attach the label to</param>
/// <param name="OffsetX">The X offset from the player</param>
/// <param name="OffsetY">The Y offset from the player</param>
/// <param name="OffsetZ">The Z offset from the player</param>
/// <seealso name="Create3DTextLabel"/>
/// <seealso name="Delete3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToVehicle"/>
/// <seealso name="Update3DTextLabelText"/>
/// <seealso name="CreatePlayer3DTextLabel"/>
/// <seealso name="DeletePlayer3DTextLabel"/>
/// <seealso name="UpdatePlayer3DTextLabelText"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <returns>
/// <b><c>1</c></b>: The function executed successfully.<p/>
/// <b><c>0</c></b>: The function failed to execute. This means the player and/or label do not exist.
/// </returns>
native Attach3DTextLabelToPlayer(Text3D:id, playerid, Float:OffsetX, Float:OffsetY, Float:OffsetZ);

/// <summary>Attaches a 3D Text Label to a specific vehicle.</summary>
/// <param name="id">The ID of the 3D text label to attach. Returned by <a href="#Create3DTextLabel">Create3DTextLabel</a></param>
/// <param name="vehicleid">The vehicle you want to attach the 3D Text Label to</param>
/// <param name="OffsetX">The Offset-X coordinate of the player vehicle (the vehicle is 0.0,0.0,0.0).</param>
/// <param name="OffsetY">The Offset-Y coordinate of the player vehicle (the vehicle is 0.0,0.0,0.0).</param>
/// <param name="OffsetZ">The Offset-Z coordinate of the player vehicle (the vehicle is 0.0,0.0,0.0).</param>
/// <seealso name="Create3DTextLabel"/>
/// <seealso name="Delete3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToPlayer"/>
/// <seealso name="Update3DTextLabelText"/>
/// <seealso name="CreatePlayer3DTextLabel"/>
/// <seealso name="DeletePlayer3DTextLabel"/>
/// <seealso name="UpdatePlayer3DTextLabelText"/>
/// <remarks>Attach3DTextLabelToPlayer was added in SA-MP 0.3a 	This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
native Attach3DTextLabelToVehicle(Text3D:id, vehicleid, Float:OffsetX, Float:OffsetY, Float:OffsetZ);


/// <summary>Updates a 3D Text Label text and color.</summary>
/// <param name="id">The 3D Text Label you want to update</param>
/// <param name="color">The color the 3D Text Label should have from now on</param>
/// <param name="text">The new text which the 3D Text Label should have from now on</param>
/// <seealso name="Create3DTextLabel"/>
/// <seealso name="Delete3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToPlayer"/>
/// <seealso name="Attach3DTextLabelToVehicle"/>
/// <seealso name="CreatePlayer3DTextLabel"/>
/// <seealso name="DeletePlayer3DTextLabel"/>
/// <seealso name="UpdatePlayer3DTextLabelText"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>If <paramref name="text"/> is empty, the server/clients next to the text might crash!</remarks>
native Update3DTextLabelText(Text3D:id, color, const text[]);

// Per-player 3D Text Labels

/// <summary>Creates a 3D Text Label only for a specific player.</summary>
/// <param name="playerid">The player which should see the newly created 3DText Label</param>
/// <param name="text">The text to display</param>
/// <param name="color">The text color</param>
/// <param name="X">X Coordinate (or offset if attached)</param>
/// <param name="Y">Y Coordinate (or offset if attached)</param>
/// <param name="Z">Z Coordinate (or offset if attached)</param>
/// <param name="DrawDistance">The distance where you are able to see the 3D Text Label</param>
/// <param name="attachedplayer">The player you want to attach the 3D Text Label to. (optional=<b><c>INVALID_PLAYER_ID</c></b>)</param>
/// <param name="attachedvehicle">The vehicle you want to attach the 3D Text Label to. (optional=<b><c>INVALID_VEHICLE_ID</c></b>)</param>
/// <param name="testLOS">Test the line-of-sight so this text can't be seen through walls (optional=<b><c>0</c></b>)</param>
/// <seealso name="Create3DTextLabel"/>
/// <seealso name="Delete3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToPlayer"/>
/// <seealso name="Attach3DTextLabelToVehicle"/>
/// <seealso name="Update3DTextLabelText"/>
/// <seealso name="DeletePlayer3DTextLabel"/>
/// <seealso name="UpdatePlayer3DTextLabelText"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>If <paramref name="text"/> is empty, the server/clients next to the text might crash!</remarks>
/// <remarks>drawdistance seems to be a lot smaller when spectating.</remarks>
/// <returns>The ID of the newly created Player 3D Text Label, or <b><c>INVALID_3DTEXT_ID</c></b> if the Player 3D Text Label limit (<b><c>MAX_3DTEXT_PLAYER</c></b>) was reached.</returns>
native PlayerText3D:CreatePlayer3DTextLabel(playerid, const text[], color, Float:X, Float:Y, Float:Z, Float:DrawDistance, attachedplayer=INVALID_PLAYER_ID, attachedvehicle=INVALID_VEHICLE_ID, testLOS=0);

/// <summary>Destroy a 3D text label that was created using <a href="#CreatePlayer3DTextLabel">CreatePlayer3DTextLabel</a>.</summary>
/// <param name="playerid">The ID of the player whose 3D text label to delete</param>
/// <param name="id">The ID of the player's 3D text label to delete</param>
/// <seealso name="Create3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToPlayer"/>
/// <seealso name="Attach3DTextLabelToVehicle"/>
/// <seealso name="Update3DTextLabelText"/>
/// <seealso name="CreatePlayer3DTextLabel"/>
/// <seealso name="UpdatePlayer3DTextLabelText"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the label specified doesn't exist.
/// </returns>
native DeletePlayer3DTextLabel(playerid, PlayerText3D:id);

/// <summary>Updates a player 3D Text Label's text and color.</summary>
/// <param name="playerid">The ID of the player for which the 3D Text Label was created</param>
/// <param name="id">The 3D Text Label you want to update</param>
/// <param name="color">The color the 3D Text Label should have from now on</param>
/// <param name="text">The new text which the 3D Text Label should have from now on</param>
/// <seealso name="Create3DTextLabel"/>
/// <seealso name="Delete3DTextLabel"/>
/// <seealso name="Attach3DTextLabelToPlayer"/>
/// <seealso name="Attach3DTextLabelToVehicle"/>
/// <seealso name="Update3DTextLabelText"/>
/// <seealso name="CreatePlayer3DTextLabel"/>
/// <seealso name="DeletePlayer3DTextLabel"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>If <paramref name="text"/> is empty, the server/clients next to the text might crash!</remarks>
native UpdatePlayer3DTextLabelText(playerid, PlayerText3D:id, color, const text[]);

/// <summary>Shows the player a synchronous (only one at a time) dialog box.</summary>
/// <param name="playerid">The ID of the player to show the dialog to</param>
/// <param name="dialogid">An ID to assign this dialog to, so responses can be processed. Max dialogid is <b><c>32767</c></b>. Using negative values will close any open dialog</param>
/// <param name="style">The style of the dialog</param>
/// <param name="caption">The title at the top of the dialog. The length of the caption can not exceed more than 64 characters before it starts to cut off</param>
/// <param name="info">The text to display in the main dialog. Use <b><c>\n</c></b> to start a new line and <b><c>\t</c></b> to tabulate</param>
/// <param name="button1">The text on the left button</param>
/// <param name="button2">The text on the right button. Leave it blank ( "" ) to hide it</param>
/// <seealso name="TextDrawShowForPlayer"/>
/// <seealso name="OnDialogResponse"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>Use color embedding for multiple colors in the text. </remarks>
/// <remarks>Using <b><c>-1</c></b> as dialogid closes all dialogs currently shown on the client's screen. </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the player is not connected.<p/>
/// </returns>
native ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[]);

/// <summary>Get a players unique ID.</summary>
/// <param name="playerid">The player to get the unique ID of</param>
/// <param name="serial">Where to save the unique ID</param>
/// <param name="maxlen">The size of "serial"</param>
native gpci(playerid, serial[], maxlen);

// --------------------------------------------------
// Forwards (Callback declarations)
// --------------------------------------------------


/// <summary>This callback is triggered when the gamemode starts.</summary>
/// <seealso name="OnGameModeExit"/>
/// <seealso name="OnFilterScriptInit"/>
/// <seealso name="OnFilterScriptExit"/>
/// <remarks>This function can also be used in a filterscript to detect if the gamemode changes with RCON commands like changemode or gmx, as changing the gamemode does not reload a filterscript.</remarks>
/// <returns>
///   <b><c>0</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>1</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnGameModeInit();

/// <summary>This callback is called when a gamemode ends, either through 'gmx', the server being shut down, or <a href="#GameModeExit">GameModeExit</a>.</summary>
/// <seealso name="OnGameModeInit"/>
/// <seealso name="OnFilterScriptExit"/>
/// <seealso name="OnFilterScriptInit"/>
/// <seealso name="GameModeExit"/>
/// <remarks>This function can also be used in a filterscript to detect if the gamemode changes with RCON commands like changemode or gmx, as changing the gamemode does not reload a filterscript.</remarks>
/// <remarks>When using OnGameModeExit in conjunction with the 'rcon gmx' console command keep in mind there is a potential for client bugs to occur an example of this is excessive <a href="#RemoveBuildingForPlayer">RemoveBuildingForPlayer</a> calls during OnGameModeInit which could result in a client crash. </remarks>
/// <remarks>This callback will NOT be called if the server crashes or the process is killed by other means, such as using the Linux kill command or pressing the close-button on the Windows console. </remarks>
/// <returns>
///   <b><c>0</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>1</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnGameModeExit();

/// <summary>This callback is called when a filterscript is initialized (loaded). It is only called inside the filterscript which is starting.</summary>
/// <seealso name="OnFilterScriptExit"/>
/// <seealso name="OnGameModeInit"/>
/// <seealso name="OnGameModeExit"/>
/// <returns>This callback does not handle returns.</returns>
forward OnFilterScriptInit();

/// <summary>This callback is called when a filterscript is unloaded. It is only called inside the filterscript which is unloaded.</summary>
/// <seealso name="OnFilterScriptInit"/>
/// <seealso name="OnGameModeInit"/>
/// <seealso name="OnGameModeExit"/>
/// <returns>This callback does not handle returns.</returns>
forward OnFilterScriptExit();

/// <summary>This callback is called when a player connects to the server.</summary>
/// <param name="playerid">The ID of the player that connected</param>
/// <seealso name="OnPlayerDisconnect"/>
/// <seealso name="OnIncomingConnection"/>
/// <seealso name="OnPlayerFinishedDownloading"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   <b><c>0</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>1</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerConnect(playerid);

/// <summary>This callback is called when a player disconnects from the server.</summary>
/// <param name="playerid">The ID of the player that disconnected</param>
/// <param name="reason">The reason for the disconnection. See table below</param>
/// <seealso name="OnPlayerConnect"/>
/// <seealso name="OnIncomingConnection"/>
/// <seealso name="OnPlayerFinishedDownloading"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>Some functions might not work correctly when used in this callback because the player is already disconnected when the callback is called. This means that you can't get unambiguous information from functions like <a href="#GetPlayerIp">GetPlayerIp</a> and <a href="#GetPlayerPos">GetPlayerPos</a>.</remarks>
/// <remarks>
///   <b>Reasons:</b><p/>
///   <ul>
///     <li><b><c>0</c></b> - timeout/Crash - the player's connection was lost. Either their game crashed or their network had a fault.</li>
///     <li><b><c>1</c></b> - quit - the player purposefully quit, either using the <b><c>/quit (/q)</c></b> command or via the pause menu.</li>
///     <li><b><c>2</c></b> - kick/ban - the player was kicked or banned by the server.</li>
///   </ul>
/// </remarks>
/// <returns>
///   <b><c>0</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>1</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerDisconnect(playerid, reason);

/// <summary>This callback is called when a player spawns.(i.e. after caling <a href="#SpawnPlayer">SpawnPlayer</a> function).</summary>
/// <param name="playerid">The ID of the player that spawned</param>
/// <seealso name="OnPlayerDeath"/>
/// <seealso name="OnVehicleSpawn"/>
/// <seealso name="SpawnPlayer"/>
/// <seealso name="AddPlayerClass"/>
/// <seealso name="SetSpawnInfo"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>The game sometimes deducts $100 from players after spawn.</remarks>
/// <returns>
///   <b><c>0</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>1</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerSpawn(playerid);

/// <summary>This callback is called when a player dies, either by suicide or by being killed by another player.</summary>
/// <param name="playerid">The ID of the player that died</param>
/// <param name="killerid">The ID of the player that killed the player who died, or <b><c>INVALID_PLAYER_ID</c></b> if there was none</param>
/// <param name="reason">The ID of the <a href="http://wiki.sa-mp.com/wiki/Weapons">reason</a> for the player's death</param>
/// <seealso name="OnPlayerSpawn"/>
/// <seealso name="SendDeathMessage"/>
/// <seealso name="SetPlayerHealth"/>
/// <remarks>
///   The reason will return 37 (flame thrower) from any fire sources (e.g. molotov, 18)<p/>
///   The reason will return 51 from any weapon that creates an explosion (e.g. RPG, grenade)<p/>
///   You do not need to check whether killerid is valid before using it in <a href="#SendDeathMessage">SendDeathMessage</a>. <b><c>INVALID_PLAYER_ID</c></b> is a valid killerid ID parameter in that function.<p/>
///   <b>playerid</b> is the only one who can call the callback. (good to know for anti fake death)
/// </remarks>
/// <returns>
///   <b><c>0</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>1</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerDeath(playerid, killerid, reason);

/// <summary>This callback is called when a vehicle <b>re</b>spawns.</summary>
/// <param name="vehicleid">The ID of the vehicle that spawned</param>
/// <seealso name="OnVehicleDeath"/>
/// <seealso name="OnPlayerSpawn"/>
/// <seealso name="SetVehicleToRespawn"/>
/// <seealso name="CreateVehicle"/>
/// <returns>
///   <b><c>0</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>1</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnVehicleSpawn(vehicleid);

/// <summary>This callback is called when a vehicle is destroyed - either by exploding or becoming submerged in water.</summary>
/// <param name="vehicleid">The ID of the vehicle that was destroyed</param>
/// <param name="killerid">The ID of the player that reported (synced) the vehicle's destruction (name is misleading). Generally the driver or a passenger (if any) or the closest player</param>
/// <seealso name="OnVehicleSpawn"/>
/// <seealso name="SetVehicleHealth"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>This callback will also be called when a vehicle enters water, but the vehicle can be saved from destruction by teleportation or driving out (if only partially submerged). The callback won't be called a second time, and the vehicle may disappear when the driver exits, or after a short time.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnVehicleDeath(vehicleid, killerid);

/// <summary>Called when a player sends a chat message.</summary>
/// <param name="playerid">The ID of the player who typed the text</param>
/// <param name="text">The text the player typed</param>
/// <seealso name="OnPlayerCommandText"/>
/// <seealso name="SendPlayerMessageToPlayer"/>
/// <seealso name="SendPlayerMessageToAll"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   Returning <b><c>0</c></b> in this callback will stop the text from being sent to all players.<p/>
///   It is always called first in filterscripts so returning <b><c>0</c></b> there blocks other scripts from seeing it.
/// </returns>
forward OnPlayerText(playerid, text[]);

/// <summary>This callback is called when a player enters a command into the client chat window. Commands are anything that start with a forward slash, e.g. <c>/help</c>.</summary>
/// <param name="playerid">The ID of the player that entered a command</param>
/// <param name="cmdtext">The command that was entered (including the forward slash)</param>
/// <seealso name="OnPlayerText"/>
/// <seealso name="OnRconCommand"/>
/// <seealso name="SendRconCommand"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   Return <b><c>1</c></b> if the command was processed, otherwise <b><c>0</c></b>; If the command was not found both in filterscripts and in gamemode, the player will be received a message: <em>SERVER: Unknown command</em>.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there blocks other scripts from seeing it.
/// </returns>
forward OnPlayerCommandText(playerid, cmdtext[]);

/// <summary>Called when a player changes class at class selection (and when class selection first appears).</summary>
/// <param name="playerid">The ID of the player that changed class</param>
/// <param name="classid">The ID of the current class being viewed (returned by <a href="#AddPlayerClass">AddPlayerClass</a>)</param>
/// <seealso name="OnPlayerRequestSpawn"/>
/// <seealso name="AddPlayerClass"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>This callback is also called when a player presses <b>F4</b>.</remarks>
/// <returns>
///   Returning <b><c>0</c></b> in this callback will prevent the player from spawning. The player can be forced to spawn when <a href="#SpawnPlayer">SpawnPlayer</a> is used.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerRequestClass(playerid, classid);

/// <summary>This callback is called when a player <b><c>starts</c></b> to enter a vehicle, meaning the player is not in vehicle yet at the time this callback is called.</summary>
/// <param name="playerid">ID of the player who attempts to enter a vehicle</param>
/// <param name="vehicleid">ID of the vehicle the player is attempting to enter</param>
/// <param name="ispassenger"><b><c>0</c></b> if entering as driver. <b><c>1</c></b> if entering as passenger</param>
/// <seealso name="OnPlayerExitVehicle"/>
/// <seealso name="OnPlayerStateChange"/>
/// <seealso name="PutPlayerInVehicle"/>
/// <seealso name="GetPlayerVehicleSeat"/>
/// <remarks>This callback is called when a player <b>BEGINS</b> to enter a vehicle, not when they HAVE entered it. See <a href="#OnPlayerStateChange">OnPlayerStateChange</a>. </remarks>
/// <remarks>This callback is still called if the player is denied entry to the vehicle (e.g. it is locked or full). </remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);

/// <summary>This callback is called when a player <b>starts</b> to exit a vehicle.</summary>
/// <param name="playerid">The ID of the player that is exiting a vehicle</param>
/// <param name="vehicleid">The ID of the vehicle the player is exiting</param>
/// <seealso name="OnPlayerEnterVehicle"/>
/// <seealso name="OnPlayerStateChange"/>
/// <seealso name="RemovePlayerFromVehicle"/>
/// <seealso name="GetPlayerVehicleSeat"/>
/// <remarks>Not called if the player falls off a bike or is removed from a vehicle by other means such as using <a href="#SetPlayerPos">SetPlayerPos</a>.</remarks>
/// <remarks>You must use <a href="#OnPlayerStateChange">OnPlayerStateChange</a> and check if their old state is <b><c>PLAYER_STATE_DRIVER</c></b> or <b><c>PLAYER_STATE_PASSENGER</c></b> and their new state is <b><c>PLAYER_STATE_ONFOOT</c></b>.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerExitVehicle(playerid, vehicleid);

/// <summary>This callback is called when a player changes state. For example, when a player changes from being the driver of a vehicle to being on-foot.</summary>
/// <param name="playerid">The ID of the player that changed state</param>
/// <param name="newstate">The player's new state</param>
/// <param name="oldstate">The player's previous state</param>
/// <seealso name="OnPlayerInteriorChange"/>
/// <seealso name="GetPlayerState"/>
/// <seealso name="GetPlayerSpecialAction"/>
/// <seealso name="SetPlayerSpecialAction"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>
///   <b>States:</b><p/>
///   <ul>
///     <li><b><c>PLAYER_STATE_NONE</c></b> - empty (while initializing)</li>
///     <li><b><c>PLAYER_STATE_ONFOOT</c></b> - player is on foot</li>
///     <li><b><c>PLAYER_STATE_DRIVER</c></b> - player is the driver of a vehicle</li>
///     <li><b><c>PLAYER_STATE_PASSENGER</c></b> - player is passenger of a vehicle</li>
///     <li><b><c>PLAYER_STATE_WASTED</c></b> - player is dead or on class selection</li>
///     <li><b><c>PLAYER_STATE_SPAWNED</c></b> - player is spawned</li>
///     <li><b><c>PLAYER_STATE_SPECTATING</c></b> - player is spectating</li>
///     <li><b><c>PLAYER_STATE_EXIT_VEHICLE</c></b> - player exits a vehicle</li>
///     <li><b><c>PLAYER_STATE_ENTER_VEHICLE_DRIVER</c></b> - player enters a vehicle as driver</li>
///     <li><b><c>PLAYER_STATE_ENTER_VEHICLE_PASSENGER</c></b> - player enters a vehicle as passenger </li>
///   </ul>
/// </remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerStateChange(playerid, newstate, oldstate);

/// <summary>This callback is called when a player enters the checkpoint set for that player.</summary>
/// <param name="playerid">The player who entered the checkpoint</param>
/// <seealso name="OnPlayerLeaveCheckpoint"/>
/// <seealso name="OnPlayerEnterRaceCheckpoint"/>
/// <seealso name="OnPlayerLeaveRaceCheckpoint"/>
/// <seealso name="SetPlayerCheckpoint"/>
/// <seealso name="DisablePlayerCheckpoint"/>
/// <seealso name="IsPlayerInCheckpoint"/>
/// <seealso name="SetPlayerRaceCheckpoint"/>
/// <seealso name="DisablePlayerRaceCheckpoint"/>
/// <seealso name="IsPlayerInRaceCheckpoint"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerEnterCheckpoint(playerid);

/// <summary>This callback is called when a player leaves the checkpoint set for them by <a href="#SetPlayerCheckpoint">SetPlayerCheckpoint</a>. Only one checkpoint can be set at a time.</summary>
/// <param name="playerid">The ID of the player that left their checkpoint</param>
/// <seealso name="OnPlayerEnterCheckpoint"/>
/// <seealso name="OnPlayerEnterRaceCheckpoint"/>
/// <seealso name="OnPlayerLeaveRaceCheckpoint"/>
/// <seealso name="SetPlayerCheckpoint"/>
/// <seealso name="DisablePlayerCheckpoint"/>
/// <seealso name="IsPlayerInCheckpoint"/>
/// <seealso name="SetPlayerRaceCheckpoint"/>
/// <seealso name="DisablePlayerRaceCheckpoint"/>
/// <seealso name="IsPlayerInRaceCheckpoint"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerLeaveCheckpoint(playerid);

/// <summary>This callback is called when a player enters a race checkpoint.</summary>
/// <param name="playerid">The ID of the player who entered the race checkpoint</param>
/// <seealso name="OnPlayerEnterCheckpoint"/>
/// <seealso name="OnPlayerLeaveCheckpoint"/>
/// <seealso name="OnPlayerLeaveRaceCheckpoint"/>
/// <seealso name="SetPlayerCheckpoint"/>
/// <seealso name="DisablePlayerCheckpoint"/>
/// <seealso name="IsPlayerInCheckpoint"/>
/// <seealso name="SetPlayerRaceCheckpoint"/>
/// <seealso name="DisablePlayerRaceCheckpoint"/>
/// <seealso name="IsPlayerInRaceCheckpoint"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerEnterRaceCheckpoint(playerid);

/// <summary>This callback is called when a player leaves the race checkpoint.</summary>
/// <param name="playerid">The ID of the player that left the race checkpoint</param>
/// <seealso name="OnPlayerEnterCheckpoint"/>
/// <seealso name="OnPlayerLeaveCheckpoint"/>
/// <seealso name="OnPlayerEnterRaceCheckpoint"/>
/// <seealso name="SetPlayerCheckpoint"/>
/// <seealso name="DisablePlayerCheckpoint"/>
/// <seealso name="IsPlayerInCheckpoint"/>
/// <seealso name="SetPlayerRaceCheckpoint"/>
/// <seealso name="DisablePlayerRaceCheckpoint"/>
/// <seealso name="IsPlayerInRaceCheckpoint"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerLeaveRaceCheckpoint(playerid);

/// <summary>This callback is called when a command is sent through the server console, remote RCON, or via the in-game "/rcon command".</summary>
/// <param name="cmd">A string containing the command that was typed, as well as any passed parameters</param>
/// <seealso name="IsPlayerAdmin"/>
/// <seealso name="OnRconLoginAttempt"/>
/// <remarks>You will need to include this callback in a loaded filterscript for it to work in the gamemode!</remarks>
/// <remarks>"/rcon" is not included in "cmd" when a player types a command. </remarks>
/// <remarks>If you use the <a href="#print">print</a> function here, it will send a message to the player who typed the command in-game as well as the log.</remarks>
/// <remarks>This callback is not called when the player is not logged in as RCON admin. </remarks>
/// <remarks>When the player is not logged in as RCON admin and uses <b>/rcon login</b>, this callback will not be called and <a href="#OnRconLoginAttempt">OnRconLoginAttempt</a> is called instead. However, when the player is logged in as RCON admin, the use of this command will call this callback. </remarks>
/// <returns>
///   <b><c>0</c></b> if the command was not processed, it will be passed to another script or <b><c>1</c></b> if the command was processed, will not be passed to other scripts.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there blocks gamemode from seeing it.
/// </returns>
forward OnRconCommand(cmd[]);

/// <summary>Called when a player attempts to spawn via class selection either by pressing SHIFT or clicking the 'Spawn' button.</summary>
/// <param name="playerid">The ID of the player that requested to spawn</param>
/// <seealso name="OnPlayerSpawn"/>
/// <seealso name="OnPlayerRequestClass"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>To prevent players from spawning with certain classes, the last viewed class must be saved in a variable in <a href="#OnPlayerRequestClass">OnPlayerRequestClass</a>.</remarks>
/// <returns>
///   Returning <b><c>0</c></b> in this callback will prevent the player from spawning.<p/>
///   It is always called first in filterscripts so returning <b><c>0</c></b> there also blocks other scripts from seeing it.
/// </returns>
forward OnPlayerRequestSpawn(playerid);

/// <summary>This callback is called when an object is moved after <a href="#MoveObject">MoveObject</a> (when it stops moving).</summary>
/// <param name="objectid">The ID of the object that was moved</param>
/// <seealso name="MoveObject"/>
/// <seealso name="IsObjectMoving"/>
/// <seealso name="StopObject"/>
/// <seealso name="OnPlayerObjectMoved"/>
/// <remarks><a href="#SetObjectPos">SetObjectPos</a> does not work when used in this callback. To fix it, recreate the object.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnObjectMoved(objectid);

/// <summary>This callback is called when a player object is moved after <a href="#MovePlayerObject">MovePlayerObject</a> (when it stops moving).</summary>
/// <param name="playerid">The playerid the object is assigned to</param>
/// <param name="objectid">The ID of the player object that was moved</param>
/// <seealso name="OnObjectMoved"/>
/// <seealso name="MovePlayerObject"/>
/// <seealso name="IsPlayerObjectMoving"/>
/// <seealso name="StopPlayerObject"/>
/// <remarks>This callback can also be called for NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerObjectMoved(playerid, objectid);

/// <summary>Called when a player picks up a pickup created with <a href="#CreatePickup">CreatePickup</a>.</summary>
/// <param name="playerid">The ID of the player that picked up the pickup</param>
/// <param name="pickupid">The ID of the pickup, returned by CreatePickup</param>
/// <seealso name="CreatePickup"/>
/// <seealso name="DestroyPickup"/>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnPlayerPickUpPickup(playerid, pickupid);

/// <summary>This callback is called when a vehicle is modded.</summary>
/// <param name="playerid">The ID of the driver of the vehicle</param>
/// <param name="vehicleid">The ID of the vehicle which is modded</param>
/// <param name="componentid">The ID of the component which was added to the vehicle</param>
/// <seealso name="AddVehicleComponent"/>
/// <seealso name="OnEnterExitModShop"/>
/// <seealso name="OnVehiclePaintjob"/>
/// <seealso name="OnVehicleRespray"/>
/// <remarks>This callback is NOT called by <a href="#AddVehicleComponent">AddVehicleComponent</a>.</remarks>
/// <returns>
///   Return <b><c>0</c></b> to desync the mod (or an invalid mod) from propagating and / or crashing players.<p/>
///   It is always called first in gamemode so returning <b><c>0</c></b> there also blocks other filterscripts from seeing it.
/// </returns>
forward OnVehicleMod(playerid, vehicleid, componentid);

/// <summary>This callback is called when a player enters or exits a mod shop.</summary>
/// <param name="playerid">The ID of the player that entered or exited the modshop</param>
/// <param name="enterexit"><b><c>1</c></b> if the player entered or <b><c>0</c></b> if they exited</param>
/// <param name="interiorid">The interior ID of the modshop that the player is entering (or 0 if exiting)</param>
/// <seealso name="OnVehicleMod"/>
/// <seealso name="OnVehicleRespray"/>
/// <seealso name="OnVehiclePaintjob"/>
/// <seealso name="AddVehicleComponent"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>Players collide when they get into the same mod shop.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnEnterExitModShop(playerid, enterexit, interiorid);

/// <summary>Called when a player previews a vehicle paintjob inside a mod shop. Watch out, this callback is not called when the player buys the paintjob.</summary>
/// <param name="playerid">The ID of the player that changed the paintjob of their vehicle</param>
/// <param name="vehicleid">The ID of the vehicle that had its paintjob changed</param>
/// <param name="paintjobid">The ID of the new paintjob</param>
/// <seealso name="ChangeVehiclePaintjob"/>
/// <seealso name="ChangeVehicleColor"/>
/// <seealso name="OnVehicleRespray"/>
/// <seealso name="OnVehicleMod"/>
/// <remarks>This callback is not called by <a href="#ChangeVehiclePaintjob">ChangeVehiclePaintjob</a>.</remarks>
/// <returns>
///   This callback does not handle returns. Returning <b><c>0</c></b> won't deny the paintjob change.<p/>
///   It is always called first in gamemode so returning <b><c>0</c></b> there blocks other filterscripts from seeing it.
/// </returns>
forward OnVehiclePaintjob(playerid, vehicleid, paintjobid);

/// <summary>This callback is called when a player exits a mod shop, even if the colors weren't changed. Watch out, the name is ambiguous, Pay 'n' Spray shops don't call this callback.</summary>
/// <param name="playerid">The ID of the player that is driving the vehicle</param>
/// <param name="vehicleid">The ID of the vehicle that was resprayed</param>
/// <param name="color1">The color that the vehicle's primary color was changed to</param>
/// <param name="color2">The color that the vehicle's secondary color was changed to</param>
/// <seealso name="ChangeVehicleColor"/>
/// <seealso name="ChangeVehiclePaintjob"/>
/// <seealso name="OnVehiclePaintjob"/>
/// <seealso name="OnVehicleMod"/>
/// <seealso name="OnEnterExitModShop"/>
/// <remarks>Previewing a component inside a mod shop might call this callback.</remarks>
/// <remarks>This callback is not called by <a href="#ChangeVehicleColor">ChangeVehicleColor</a>.</remarks>
/// <returns>
///   Returning <b><c>0</c></b> in this callback will deny the colour change. Returning <b><c>1</c></b> will allow it. This can be used to prevent hackers from changing vehicle colours using cheats.<p/>
///   It is always called first in gamemode so returning <b><c>0</c></b> there also blocks other filterscripts from seeing it.
/// </returns>
forward OnVehicleRespray(playerid, vehicleid, color1, color2);

/// <summary>This callback is called when a vehicle element such as doors, tires, panels, or lights change their damage status.</summary>
/// <param name="vehicleid">The ID of the vehicle that was changed its damage status</param>
/// <param name="playerid">The ID of the player who synced the change in the damage status (who had the car damaged or repaired)</param>
/// <seealso name="GetVehicleDamageStatus"/>
/// <seealso name="UpdateVehicleDamageStatus"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This does not include vehicle health changes</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.<p/>
/// </returns>
forward OnVehicleDamageStatusUpdate(vehicleid, playerid);

/// <summary>This callback is called when a player's client updates/syncs the position of a vehicle they're not driving. This can happen outside of the vehicle or when the player is a passenger of a vehicle that has no driver.</summary>
/// <param name="vehicleid">The ID of the vehicle that's position was updated</param>
/// <param name="playerid">The ID of the player that sent a vehicle position sync update</param>
/// <param name="passenger_seat">The ID of the seat if the player is a passenger. 0=not in vehicle, 1=front passenger, 2=backleft 3=backright 4+ is for coach/bus etc. with many passenger seats</param>
/// <param name="new_x">The new X coordinate of the vehicle. This parameter was added in <b>0.3z</b>. Leave it out if using an earlier version</param>
/// <param name="new_y">The new Y coordinate of the vehicle. This parameter was added in <b>0.3z</b>. Leave it out if using an earlier version</param>
/// <param name="new_z">The new Z coordinate of the vehicle. This parameter was added in <b>0.3z</b>. Leave it out if using an earlier version</param>
/// <param name="vel_x">The new X velocity of the vehicle. This parameter was added in <b>0.3z R4</b>. Leave it out if using an earlier version</param>
/// <param name="vel_y">The new Y velocity of the vehicle. This parameter was added in <b>0.3z R4</b>. Leave it out if using an earlier version</param>
/// <param name="vel_z">The new Z velocity of the vehicle. This parameter was added in <b>0.3z R4</b>. Leave it out if using an earlier version</param>
/// <seealso name="OnTrailerUpdate"/>
/// <remarks>This callback was added in <b>SA-MP 0.3c R3</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback is called very frequently per second per unoccupied vehicle. You should refrain from implementing intensive calculations or intensive file writing/reading operations in this callback.</remarks>
/// <remarks><a href="#GetVehiclePos">GetVehiclePos</a> will return the old coordinates of the vehicle before this update.</remarks>
/// <returns>
///   Returning <b><c>0</c></b> in this callback will stop the vehicle's position being synced to other players. Update is still sent to the updating player. Useful for combating vehicle teleport hacks.<p/>
///   It is always called first in filterscripts so returning <b><c>0</c></b> there also blocks other scripts from seeing it.
/// </returns>
forward OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z);

/// <summary>This callback is called when a player selects an item from a menu (<a href="#ShowMenuForPlayer">ShowMenuForPlayer</a>).</summary>
/// <param name="playerid">The ID of the player that selected a menu item</param>
/// <param name="row">The ID of the row that was selected. The first row is ID <b><c>0</c></b></param>
/// <seealso name="OnPlayerExitedMenu"/>
/// <seealso name="OnDialogResponse"/>
/// <seealso name="CreateMenu"/>
/// <seealso name="DestroyMenu"/>
/// <seealso name="AddMenuItem"/>
/// <seealso name="ShowMenuForPlayer"/>
/// <seealso name="HideMenuForPlayer"/>
/// <remarks>The menu ID is not passed to this callback. <a href="#GetPlayerMenu">GetPlayerMenu</a> must be used to determine which menu the player selected an item on.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnPlayerSelectedMenuRow(playerid, row);

/// <summary>Called when a player exits a menu.</summary>
/// <param name="playerid">The ID of the player that exited the menu</param>
/// <seealso name="OnPlayerSelectedMenuRow"/>
/// <seealso name="CreateMenu"/>
/// <seealso name="DestroyMenu"/>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnPlayerExitedMenu(playerid);

/// <summary>Called when a player changes interior. Can be triggered by SetPlayerInterior or when a player enter/exits a building.</summary>
/// <param name="playerid">The playerid who changed interior</param>
/// <param name="newinteriorid">The interior the player is now in</param>
/// <param name="oldinteriorid">The interior the player was in before</param>
/// <seealso name="SetPlayerInterior"/>
/// <seealso name="GetPlayerInterior"/>
/// <seealso name="LinkVehicleToInterior"/>
/// <seealso name="OnPlayerStateChange"/>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid);

/// <summary>This callback is called when the state of any supported key is changed (pressed/released). Directional keys do not trigger OnPlayerKeyStateChange (up/down/left/right).</summary>
/// <param name="playerid">The ID of the player that pressed or released a key</param>
/// <param name="newkeys">A map (bitmask) of the keys currently held - see <a href="http://wiki.sa-mp.com/wiki/Keys">here</a></param>
/// <param name="oldkeys">A map (bitmask) of the keys held prior to the current change - see <a href="http://wiki.sa-mp.com/wiki/Keys">here</a></param>
/// <seealso name="GetPlayerKeys"/>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>
///   Useful macros:<p/>
///   <code>
///     // HOLDING(keys)<p/>
///     #define HOLDING(%0) ((newkeys &amp; (%0)) == (%0))<p/>
///     <p/>
///     // PRESSED(keys)<p/>
///     #define PRESSED(%0) (((newkeys &amp; (%0)) == (%0)) &amp;&amp; ((oldkeys &amp; (%0)) != (%0)))<p/>
///     <p/>
///     // PRESSING(keyVariable, keys)<p/>
///     #define PRESSING(%0,%1) (%0 &amp; (%1))<p/>
///     <p/>
///     // RELEASED(keys)<p/>
///     #define RELEASED(%0) (((newkeys &amp; (%0)) != (%0)) &amp;&amp; ((oldkeys &amp; (%0)) == (%0)))<p/>
///   </code>
/// </remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnPlayerKeyStateChange(playerid, newkeys, oldkeys);

/// <summary>This callback is called when someone attempts to log in to RCON in-game; successful or not.</summary>
/// <param name="ip">The IP of the player that tried to log in to RCON</param>
/// <param name="password">The password used to login with</param>
/// <param name="success"><b><c>0</c></b> if the password was incorrect or <b><c>1</c></b> if it was correct</param>
/// <seealso name="OnRconCommand"/>
/// <seealso name="IsPlayerAdmin"/>
/// <seealso name="SendRconCommand"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback is only called when /rcon login is used in-game. </remarks>
/// <remarks>This callback is only called when the player is not yet logged in. When the player is logged in, <a href="#OnRconCommand">OnRconCommand</a> is called instead.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnRconLoginAttempt( ip[], password[], success );

/// <summary>This callback is called every time a client/player updates the server with their status. It is often used to create custom callbacks for client updates that aren't actively tracked by the server, such as health or armor updates or players switching weapons.</summary>
/// <param name="playerid">ID of the player sending an update packet</param>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>This callback is called, on average, 30 times per second, per player; only use it when you know what it's meant for (or more importantly what it's NOT meant for). </remarks>
/// <remarks>The frequency with which this callback is called for each player varies, depending on what the player is doing. Driving or shooting will trigger a lot more updates than idling. </remarks>
/// <returns>
///   <b><c>0</c></b> - Update from this player will not be replicated to other clients.<p/>
///   <b><c>1</c></b> - Indicates that this update can be processed normally and sent to other players.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerUpdate(playerid);

/// <summary>This callback is called when a player is streamed by some other player's client.</summary>
/// <param name="playerid">The ID of the player who has been streamed</param>
/// <param name="forplayerid">The ID of the player that streamed the other player in</param>
/// <seealso name="OnPlayerStreamOut"/>
/// <seealso name="OnActorStreamIn"/>
/// <seealso name="OnVehicleStreamIn"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerStreamIn(playerid, forplayerid);

/// <summary>This callback is called when a player is streamed out from some other player's client.</summary>
/// <param name="playerid">The player who has been destreamed</param>
/// <param name="forplayerid">The player who has destreamed the other player</param>
/// <seealso name="OnPlayerStreamIn"/>
/// <seealso name="OnActorStreamOut"/>
/// <seealso name="OnVehicleStreamOut"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerStreamOut(playerid, forplayerid);

/// <summary>Called when a vehicle is streamed to a player's client.</summary>
/// <param name="vehicleid">The ID of the vehicle that streamed in for the player</param>
/// <param name="forplayerid">The ID of the player who the vehicle streamed in for</param>
/// <seealso name="OnVehicleStreamOut"/>
/// <seealso name="OnPlayerStreamIn"/>
/// <seealso name="OnPlayerStreamOut"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnVehicleStreamIn(vehicleid, forplayerid);

/// <summary>This callback is called when a vehicle is streamed out for a player's client (it's so far away that they can't see it).</summary>
/// <param name="vehicleid">The ID of the vehicle that streamed out</param>
/// <param name="forplayerid">The ID of the player who is no longer streaming the vehicle</param>
/// <seealso name="OnVehicleStreamIn"/>
/// <seealso name="OnPlayerStreamIn"/>
/// <seealso name="OnPlayerStreamOut"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <returns>
///   This callback does not handle returns.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnVehicleStreamOut(vehicleid, forplayerid);

/// <summary>This callback is called when an actor is streamed in by a player's client.</summary>
/// <param name="actorid">The ID of the actor that has been streamed in for the player</param>
/// <param name="forplayerid">The ID of the player that streamed the actor in</param>
/// <seealso name="OnActorStreamOut"/>
/// <seealso name="OnPlayerStreamIn"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>It is always called first in filterscripts.</remarks>
/// <returns>This callback does not handle returns.</returns>
forward OnActorStreamIn(actorid, forplayerid);

/// <summary>This callback is called when an actor is streamed out by a player's client.</summary>
/// <param name="actorid">The ID of the actor that has been streamed out for the player</param>
/// <param name="forplayerid">The ID of the player that streamed the actor out</param>
/// <seealso name="OnActorStreamIn"/>
/// <seealso name="OnPlayerStreamOut"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>It is always called first in filterscripts.</remarks>
/// <returns>This callback does not handle returns.</returns>
forward OnActorStreamOut(actorid, forplayerid);

/// <summary>This callback is called when a player responds to a dialog shown using <a href="#ShowPlayerDialog">ShowPlayerDialog</a> by either clicking a button, pressing ENTER/ESC or double-clicking a list item (if using a list style dialog).</summary>
/// <param name="playerid">The ID of the player that responded to the dialog</param>
/// <param name="dialogid">The ID of the dialog the player responded to, assigned in ShowPlayerDialog</param>
/// <param name="response"><b><c>1</c></b> for left button and <b><c>0</c></b> for right button (if only one button shown, always <b><c>1</c></b>)</param>
/// <param name="listitem">The ID of the list item selected by the player (starts at <b><c>0</c></b>) (only if using a list style dialog)</param>
/// <param name="inputtext">The text entered into the input box by the player or the selected list item text</param>
/// <seealso name="ShowPlayerDialog"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>A player's dialog doesn't hide when the gamemode restarts, causing the server to print <c>"Warning: PlayerDialogResponse PlayerId: 0 dialog ID doesn't match last sent dialog ID"</c> if a player responded to this dialog after restart.</remarks>
/// <remarks>Parameters can contain different values, based on dialog's <a href="http://wiki.sa-mp.com/wiki/Dialog_Styles">style</a>.</remarks>
/// <returns>
///   Returning <b><c>0</c></b> in this callback will pass the dialog to another script in case no matching code were found in your gamemode's callback.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there blocks other filterscripts from seeing it.
/// </returns>
forward OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);

/// <summary>This callback is called when a player takes damage.</summary>
/// <param name="playerid">The ID of the player that took damage</param>
/// <param name="issuerid">The ID of the player that caused the damage. <b><c>INVALID_PLAYER_ID</c></b> if self-inflicted</param>
/// <param name="amount">The amount of damage the player took (health and armour combined)</param>
/// <param name="weaponid">The ID of the <a href="http://wiki.sa-mp.com/wiki/Weapons">weapon/reason</a> for the damage</param>
/// <param name="bodypart">The body part that was hit. (NOTE: This parameter was added in <b>0.3z</b>. Leave it out if using an older version!)</param>
/// <seealso name="OnPlayerGiveDamage"/>
/// <seealso name="OnPlayerWeaponShot"/>
/// <remarks>This callback was added in <b>SA-MP 0.3d</b> and will not work in earlier versions!</remarks>
/// <remarks><a href="#GetPlayerHealth">GetPlayerHealth</a> and <a href="#GetPlayerArmour">GetPlayerArmour</a> will return the old amounts of the player before this callback. </remarks>
/// <remarks>
///   The weaponid will return <b><c>37</c></b> (flame thrower) from any fire sources (e.g. molotov, <b><c>18</c></b>).<p/>
///   The weaponid will return <b><c>51</c></b> from any weapon that creates an explosion (e.g. RPG, grenade)<p/>
///   <b>playerid</b> is the only one who can call the callback.<p/>
///   The amount is always the maximum damage the weaponid can do, even when the health left is less than that maximum damage. So when a player has <b><c>100.0</c></b> health and gets shot with a Desert Eagle which has a damage value of <b><c>46.2</c></b>, it takes 3 shots to kill that player. All 3 shots will show an amount of <b><c>46.2</c></b>, even though when the last shot hits, the player only has <b><c>7.6</c></b> health left.
/// </remarks>
/// <returns>
///   <b><c>1</c></b> - Callback will not be called in other filterscripts.<p/>
///   <b><c>0</c></b> - Allows this callback to be called in other filterscripts.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there blocks other filterscripts from seeing it.
/// </returns>
forward OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);

/// <summary>This callback is called when a player gives damage to another player.</summary>
/// <param name="playerid">The ID of the player that gave damage</param>
/// <param name="damagedid">The ID of the player that received damage</param>
/// <param name="amount">The amount of health/armour damagedid has lost (combined)</param>
/// <param name="weaponid">The <a href="http://wiki.sa-mp.com/wiki/Weapons">reason</a> that caused the damage</param>
/// <param name="bodypart">The body part that was hit. (NOTE: This parameter was added in <b>0.3z</b>. Leave it out if using an older version!)</param>
/// <seealso name="OnPlayerTakeDamage"/>
/// <remarks>This callback was added in <b>SA-MP 0.3d</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   Keep in mind this function can be inaccurate in some cases.<p/>
///   If you want to prevent certain players from damaging eachother, use <a href="#SetPlayerTeam">SetPlayerTeam</a>.<p/>
///   The weaponid will return <b><c>37</c></b> (flame thrower) from any fire sources (e.g. molotov, 18)<p/>
///   The weaponid will return <b><c>51</c></b> from any weapon that creates an explosion (e.g. RPG, grenade)<p/>
///   <b>playerid</b> is the only one who can call the callback.<p/>
///   The amount is always the maximum damage the weaponid can do, even when the health left is less than that maximum damage. So when a player has <b><c>100.0</c></b> health and gets shot with a Desert Eagle which has a damage value of <b><c>46.2</c></b>, it takes 3 shots to kill that player. All 3 shots will show an amount of <b><c>46.2</c></b>, even though when the last shot hits, the player only has <b><c>7.6</c></b> health left.
/// </remarks>
/// <returns>
///   <b><c>1</c></b> - Callback will not be called in other filterscripts.<p/>
///   <b><c>0</c></b> - Allows this callback to be called in other filterscripts.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there blocks other filterscripts from seeing it.
/// </returns>
forward OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart);

/// <summary>This callback is called when a player gives damage to an actor.</summary>
/// <param name="playerid">The ID of the player that gave damage</param>
/// <param name="damaged_actorid">The ID of the actor that received damage</param>
/// <param name="amount">The amount of health/armour damaged_actorid has lost</param>
/// <param name="weaponid">The reason that caused the damage</param>
/// <param name="bodypart">The body part that was hit</param>
/// <seealso name="CreateActor"/>
/// <seealso name="SetActorInvulnerable"/>
/// <seealso name="SetActorHealth"/>
/// <seealso name="GetActorHealth"/>
/// <seealso name="IsActorInvulnerable"/>
/// <seealso name="IsValidActor"/>
/// <seealso name="OnActorStreamOut"/>
/// <seealso name="OnPlayerStreamIn"/>
/// <remarks>This callback was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>This function does not get called if the actor is set invulnerable (WHICH IS BY DEFAULT). See <a href="#SetActorInvulnerable">SetActorInvulnerable</a>.</remarks>
/// <returns>
///   <b><c>1</c></b> - Callback will not be called in other filterscripts.<p/>
///   <b><c>0</c></b> - Allows this callback to be called in other filterscripts.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there blocks other filterscripts from seeing it.
/// </returns>
forward OnPlayerGiveDamageActor(playerid, damaged_actorid, Float:amount, weaponid, bodypart);

/// <summary>OnPlayerClickMap is called when a player places a target/waypoint on the pause menu map (by right-clicking).</summary>
/// <param name="playerid">The ID of the player that placed a target/waypoint</param>
/// <param name="fX">The X float coordinate where the player clicked</param>
/// <param name="fY">The Y float coordinate where the player clicked</param>
/// <param name="fZ">The Z float coordinate where the player clicked (inaccurate - see note below)</param>
/// <seealso name="SetPlayerPos"/>
/// <seealso name="SetPlayerPosFindZ"/>
/// <seealso name="GetPlayerPos"/>
/// <remarks>This callback was added in <b>SA-MP 0.3d</b> and will not work in earlier versions!</remarks>
/// <remarks>The Z value returned will be <b><c>0</c></b> (invalid) if it is far away from the player; use the <a href="http://forum.sa-mp.com/showthread.php?t=275492">MapAndreas plugin</a> to get a more accurate Z coordinate.</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in gamemode.
/// </returns>
forward OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ);

/// <summary>This callback is called when a player clicks on a textdraw or cancels the select mode with the Escape key.</summary>
/// <param name="playerid">The ID of the player that clicked on the textdraw</param>
/// <param name="clickedid">The ID of the clicked textdraw. <b><c>INVALID_TEXT_DRAW</c></b> if selection was cancelled</param>
/// <seealso name="OnPlayerClickPlayerTextDraw"/>
/// <seealso name="OnPlayerClickPlayer"/>
/// <remarks>This callback was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>The clickable area is defined by <a href="#TextDrawTextSize">TextDrawTextSize</a>. The x and y parameters passed to that function must not be zero or negative. </remarks>
/// <remarks>Do not use <a href="#CancelSelectTextDraw">CancelSelectTextDraw</a> unconditionally within this callback. This results in an infinite loop. </remarks>
/// <returns>
///   Returning <b><c>1</c></b> in this callback will prevent it being called in other scripts. This should be used to signal that the textdraw on which they clicked was 'found' and no further processing is needed. You should return <b><c>0</c></b> if the textdraw on which they clicked wasn't found, just like in <a href="#OnPlayerCommandText">OnPlayerCommandText</a>.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there also blocks other scripts from seeing it.
/// </returns>
forward OnPlayerClickTextDraw(playerid, Text:clickedid);

/// <summary>This callback is called when a player clicks on a player-textdraw. It is not called when player cancels the select mode (ESC) - however, <a href="#OnPlayerClickTextDraw">OnPlayerClickTextDraw</a> is.</summary>
/// <param name="playerid">The ID of the player that selected a textdraw</param>
/// <param name="playertextid">The ID of the player-textdraw that the player selected</param>
/// <seealso name="PlayerTextDrawSetSelectable"/>
/// <seealso name="OnPlayerClickTextDraw"/>
/// <seealso name="OnPlayerClickPlayer"/>
/// <remarks>This callback was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>When a player presses ESC to cancel selecting a textdraw, <a href="#OnPlayerClickTextDraw">OnPlayerClickTextDraw</a> is called with a textdraw ID of <b><c>INVALID_TEXT_DRAW</c></b>. <a href="#OnPlayerClickPlayerTextDraw">OnPlayerClickPlayerTextDraw</a> won't be called also.</remarks>
/// <returns>
///   Returning <b><c>1</c></b> in this callback will prevent it being called in other scripts. This should be used to signal that the textdraw on which they clicked was 'found' and no further processing is needed. You should return <b><c>0</c></b> if the textdraw on which they clicked wasn't found, just like in <a href="#OnPlayerCommandText">OnPlayerCommandText</a>.<p/>
///   It is always called first in filterscripts so returning <b><c>1</c></b> there also blocks other scripts from seeing it.
/// </returns>
forward OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid);

/// <summary>This callback is called when an IP address attempts a connection to the server. To block incoming connections, use <a href="#BlockIpAddress">BlockIpAddress</a>.</summary>
/// <param name="playerid">The ID of the player attempting to connect</param>
/// <param name="ip_address">The IP address of the player attempting to connect</param>
/// <param name="port">The port of the attempted connection</param>
/// <seealso name="OnPlayerConnect"/>
/// <seealso name="OnPlayerDisconnect"/>
/// <seealso name="OnPlayerFinishedDownloading"/>
/// <seealso name="BlockIpAddress"/>
/// <seealso name="UnBlockIpAddress"/>
/// <remarks> 	This callback was added in <b>SA-MP 0.3z R2-2</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnIncomingConnection(playerid, ip_address[], port);

/// <summary>This callback is called when a player sent a trailer update.</summary>
/// <param name="playerid">The ID of the player who sent a trailer update</param>
/// <param name="vehicleid">The Trailer being updated</param>
/// <seealso name="OnUnoccupiedVehicleUpdate"/>
/// <seealso name="GetVehicleTrailer"/>
/// <seealso name="IsTrailerAttachedToVehicle"/>
/// <seealso name="AttachTrailerToVehicle"/>
/// <seealso name="DetachTrailerFromVehicle"/>
/// <remarks>This callback was added in <b>SA-MP 0.3z R4</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback is called very frequently per second per trailer. You should refrain from implementing intensive calculations or intensive file writing/reading operations in this callback. </remarks>
/// <returns>
///   <b><c>0</c></b> - Cancels any trailer updates from being sent to other players. Update is still sent to the updating player.<p/>
///   <b><c>1</c></b> - Processes the trailer update as normal and synchronizes it between all players.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnTrailerUpdate(playerid, vehicleid);

/// <summary>This callback is called when a vehicle's siren is toggled.</summary>
/// <param name="playerid">The ID of the player that toggled the siren (driver)</param>
/// <param name="vehicleid">The ID of the vehicle of which the siren was toggled for</param>
/// <param name="newstate"><b><c>0</c></b> if siren was turned off, <b><c>1</c></b> if siren was turned on</param>
/// <seealso name="GetVehicleParamsSirenState"/>
/// <remarks>This callback was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback can also be called by NPC.</remarks>
/// <remarks>This callback is only called when a vehicle's siren is toggled on or off, NOT when the alternate siren is in use (holding horn).</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent gamemode from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the gamemode.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnVehicleSirenStateChange(playerid, vehicleid, newstate);

/// <summary>This callback is called when a player finishes downloading custom models. For more information on how to add custom models to your server, see <a href="http://forum.sa-mp.com/showthread.php?t=644105">the release thread</a> and <a href="http://forum.sa-mp.com/showthread.php?t=644123">this tutorial</a>.</summary>
/// <param name="playerid">The ID of the player that finished downloading custom models</param>
/// <param name="virtualworld">The ID of the virtual world the player finished downloading custom models for</param>
/// <seealso name="OnPlayerConnect"/>
/// <seealso name="OnPlayerDisconnect"/>
/// <seealso name="OnIncomingConnection"/>
/// <remarks>This callback was added in <b>SA-MP 0.3DL</b> and will not work in earlier versions!</remarks>
/// <remarks>This callback is called every time a player changes virtual worlds, even if there are no custom models present in that world.</remarks>
/// <returns>This callback does not handle returns.</returns>
forward OnPlayerFinishedDownloading(playerid, virtualworld);
forward OnPlayerRequestDownload(playerid, type, crc);

/// <summary>Called when a player double-clicks on a player on the scoreboard.</summary>
/// <param name="playerid">The ID of the player that clicked on a player on the scoreboard</param>
/// <param name="clickedplayerid">The ID of the player that was clicked on</param>
/// <param name="source">The source of the player's click</param>
/// <seealso name="OnPlayerClickTextDraw"/>
/// <remarks>This callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>There is currently only one <paramref name="source"/> (<b><c>0 - CLICK_SOURCE_SCOREBOARD</c></b>). The existence of this argument suggests that more sources may be supported in the future.</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent other filterscripts from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the next filterscript.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerClickPlayer(playerid, clickedplayerid, source);

/// <summary>This callback is called when a player finishes editing an object (<a href="#EditObject">EditObject</a>/<a href="#EditPlayerObject">EditPlayerObject</a>).</summary>
/// <param name="playerid">The ID of the player that edited an object</param>
/// <param name="playerobject"><b><c>0</c></b> if it is a global object or <b><c>1</c></b> if it is a playerobject</param>
/// <param name="objectid">The ID of the edited object</param>
/// <param name="response">The type of response</param>
/// <param name="fX">The X offset for the object that was edited</param>
/// <param name="fY">The Y offset for the object that was edited</param>
/// <param name="fZ">The Z offset for the object that was edited</param>
/// <param name="fRotX">The X rotation for the object that was edited</param>
/// <param name="fRotY">The Y rotation for the object that was edited</param>
/// <param name="fRotZ">The Z rotation for the object that was edited</param>
/// <seealso name="EditObject"/>
/// <seealso name="CreateObject"/>
/// <seealso name="DestroyObject"/>
/// <seealso name="MoveObject"/>
/// <remarks>This callback was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>When using <b><c>EDIT_RESPONSE_UPDATE</c></b> be aware that this callback will not be called when releasing an edit in progress resulting in the last update of <b><c>EDIT_RESPONSE_UPDATE</c></b> being out of sync of the objects current position.</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent other scripts from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the next script.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerEditObject( playerid, playerobject, objectid, response, 
Float:fX, Float:fY, Float:fZ, Float:fRotX, Float:fRotY, Float:fRotZ );


/// <summary>This callback is called when a player ends attached object edition mode.</summary>
/// <param name="playerid">The ID of the player that ended edition mode</param>
/// <param name="response"><b><c>0</c></b> if they cancelled (ESC) or <b><c>1</c></b> if they clicked the save icon</param>
/// <param name="index">The index of the attached object</param>
/// <param name="modelid">The model of the attached object that was edited</param>
/// <param name="boneid">The bone of the attached object that was edited</param>
/// <param name="fOffsetX">The X offset for the attached object that was edited</param>
/// <param name="fOffsetY">The Y offset for the attached object that was edited</param>
/// <param name="fOffsetZ">The Z offset for the attached object that was edited</param>
/// <param name="fRotX">The X rotation for the attached object that was edited</param>
/// <param name="fRotY">The Y rotation for the attached object that was edited</param>
/// <param name="fRotZ">The Z rotation for the attached object that was edited</param>
/// <param name="fScaleX">The X scale for the attached object that was edited</param>
/// <param name="fScaleY">The Y scale for the attached object that was edited</param>
/// <param name="fScaleZ">The Z scale for the attached object that was edited</param>
/// <seealso name="EditAttachedObject"/>
/// <seealso name="SetPlayerAttachedObject"/>
/// <remarks>This callback was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>Editions should be discarded if response was <b><c>0</c></b> (cancelled). This must be done by storing the offsets etc. in an array BEFORE using <a href="#EditAttachedObject">EditAttachedObject</a>.</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent other scripts from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the next script.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerEditAttachedObject( playerid, response, index, modelid, boneid,
Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
Float:fRotX, Float:fRotY, Float:fRotZ,
Float:fScaleX, Float:fScaleY, Float:fScaleZ );

/// <summary>This callback is called when a player selects an object after <a href="#SelectObject">SelectObject</a> has been used.</summary>
/// <param name="playerid">The ID of the player that selected an object</param>
/// <param name="type">The type of selection</param>
/// <param name="objectid">The ID of the selected object</param>
/// <param name="modelid">The model ID of the selected object</param>
/// <param name="fX">The X position of the selected object</param>
/// <param name="fY">The Y position of the selected object</param>
/// <param name="fZ">The Z position of the selected object</param>
/// <seealso name="SelectObject"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b> - Will prevent other scripts from receiving this callback.<p/>
///   <b><c>0</c></b> - Indicates that this callback will be passed to the next script.<p/>
///   It is always called first in filterscripts.
/// </returns>
forward OnPlayerSelectObject(playerid, type, objectid, modelid, Float:fX, Float:fY, Float:fZ);

/// <summary>This callback is called when a player fires a shot from a weapon. Only bullet weapons are supported. Only <b>passenger</b> drive-by is supported (not driver drive-by, and not sea sparrow / hunter shots).</summary>
/// <param name="playerid">The ID of the player that shot a weapon</param>
/// <param name="weaponid">The ID of the <a href="http://wiki.sa-mp.com/wiki/Weapons">weapon</a> shot by the player</param>
/// <param name="hittype">The type of thing the shot hit (none, player, vehicle, or (player)object)</param>
/// <param name="hitid">The ID of the player, vehicle or object that was hit</param>
/// <param name="fX">The X coordinate that the shot hit</param>
/// <param name="fY">The Y coordinate that the shot hit</param>
/// <param name="fZ">The Z coordinate that the shot hit</param>
/// <seealso name="OnPlayerGiveDamage"/>
/// <seealso name="GetPlayerLastShotVectors"/>
/// <remarks>This callback was added in <b>SA-MP 0.3z</b> and will not work in earlier versions!</remarks>
/// <remarks>
///     <li><b><c>BULLET_HIT_TYPE_NONE(0)</c></b></li>
///     <li><b><c>BULLET_HIT_TYPE_PLAYER(1)</c></b></li>
///     <li><b><c>BULLET_HIT_TYPE_VEHICLE(2)</c></b></li>
///     <li><b><c>BULLET_HIT_TYPE_OBJECT(3)</c></b></li>
///     <li><b><c>BULLET_HIT_TYPE_PLAYER_OBJECT(4)</c></b></li>
/// </remarks>
/// <remarks><b><c>BULLET_HIT_TYPE_PLAYER</c></b> is also called for NPCs. Actors are ignored by this callback and detects as <b><c>BULLET_HIT_TYPE_NONE</c></b>.</remarks>
/// <remarks>This callback is only called when lag compensation is <b>enabled</b>. </remarks>
/// <remarks>
///   If hittype is:<p/>
///   <ul>
///     <li>- <b><c>BULLET_HIT_TYPE_NONE</c></b>: the fX, fY and fZ parameters are normal coordinates, will give 0.0 for coordinates if nothing was hit (e.g. far object that the bullet can't reach);</li>
///     <li>- Others: the fX, fY and fZ are offsets relative to the hitid.</li>
///   </ul>
/// </remarks>
/// <remarks>
///   Isn't called if you fired in vehicle as driver or if you are looking behind with the aim enabled (shooting in air).<p/>
///   It is called as <b><c>BULLET_HIT_TYPE_VEHICLE</c></b> with the correct hitid (the hit player's vehicleid) if you are shooting a player which is in a vehicle. It won't be called as <b><c>BULLET_HIT_TYPE_PLAYER</c></b> at all.<p/>
///   <b>Partially fixed in SA-MP 0.3.7:</b> If fake weapon data is sent by a malicious user, other player clients may freeze or crash. To combat this, check if the reported weaponid can actually fire bullets.
/// </remarks>
/// <remarks>
/// </remarks>
/// <remarks><a href="#GetPlayerLastShotVectors">GetPlayerLastShotVectors</a> can be used in this callback for more detailed bullet vector information.</remarks>
/// <returns>
///   <b><c>0</c></b> - Prevent the bullet from causing damage.<p/>
///   <b><c>1</c></b> - Allow the bullet to cause damage.<p/>
///   It is always called first in filterscripts so returning <b><c>0</c></b> there also blocks other scripts from seeing it.
/// </returns>
forward OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);

/// <summary>This callback is called when a SendClientCheck request comletes</summary>
/// <param name="playerid">The ID of the player checked</param>
/// <param name="actionid">The type of check performed</param>
/// <param name="memaddr">The address requested</param>
/// <param name="retndata">The result of the check</param>
/// <seealso name="SendClientCheck"/>
forward OnClientCheckResponse(playerid, actionid, memaddr, retndata);

/// <summary>This callback is called when a SendClientCheck request comletes</summary>
/// <param name="playerid">The ID of the player who got cash from the game</param>
/// <param name="amount">The amount of cash given</param>
/// <param name="source">Where the money came from</param>
/// <remarks>Doesn't work</remarks>
forward OnScriptCash(playerid, amount, source);

// --------------------------------------------------

