/*  SA-MP Object Functions
 *
 *  (c) Copyright 2005-2015, SA-MP Team
 *
 */

#if defined _INC_a_objects
	#endinput
#endif
#define _INC_a_objects
#define _objects_included

#define SAMP_CONST_CORRECT

#pragma tabsize 4

// --------------------------------------------------
// Defines
// --------------------------------------------------

#define OBJECT_MATERIAL_SIZE_32x32             (10)
#define OBJECT_MATERIAL_SIZE_64x32             (20)
#define OBJECT_MATERIAL_SIZE_64x64             (30)
#define OBJECT_MATERIAL_SIZE_128x32            (40)
#define OBJECT_MATERIAL_SIZE_128x64            (50)
#define OBJECT_MATERIAL_SIZE_128x128           (60)
#define OBJECT_MATERIAL_SIZE_256x32            (70)
#define OBJECT_MATERIAL_SIZE_256x64            (80)
#define OBJECT_MATERIAL_SIZE_256x128           (90)
#define OBJECT_MATERIAL_SIZE_256x256           (100)
#define OBJECT_MATERIAL_SIZE_512x64            (110)
#define OBJECT_MATERIAL_SIZE_512x128           (120)
#define OBJECT_MATERIAL_SIZE_512x256           (130)
#define OBJECT_MATERIAL_SIZE_512x512           (140)

#define OBJECT_MATERIAL_TEXT_ALIGN_LEFT        (0)
#define OBJECT_MATERIAL_TEXT_ALIGN_CENTER      (1)
#define OBJECT_MATERIAL_TEXT_ALIGN_RIGHT       (2)

// Objects

/// <summary>Creates an object at specified coordinates in the game world.</summary>
/// <param name="modelid">The model to create</param>
/// <param name="X">The X coordinate to create the object at</param>
/// <param name="Y">The Y coordinate to create the object at</param>
/// <param name="Z">The Z coordinate to create the object at</param>
/// <param name="rX">The X rotation of the object</param>
/// <param name="rY">The Y rotation of the object</param>
/// <param name="rZ">The Z rotation of the object</param>
/// <param name="DrawDistance">The distance that San Andreas renders objects at. <b><c>0.0</c></b> will cause objects to render at their default distances. <b>Usable since 0.3b, limited to <c>300</c> prior to 0.3x</b> (optional=<b><c>0.0</c></b>)</param>
/// <seealso name="DestroyObject"/>
/// <seealso name="IsValidObject"/>
/// <seealso name="CreatePlayerObject"/>
/// <seealso name="MoveObject"/>
/// <seealso name="SetObjectPos"/>
/// <seealso name="SetObjectRot"/>
/// <seealso name="GetObjectPos"/>
/// <seealso name="GetObjectRot"/>
/// <seealso name="AttachObjectToPlayer"/>
/// <seealso name="SetObjectMaterialText"/>
/// <seealso name="SetObjectMaterial"/>
/// <remarks>
///   Objects that emit light (lampposts, police lights, bollard lights, neons etc.) that have a greater rotation than <b><c>16.26</c></b> degrees (or <b><c>-16.26</c></b>) on either the X or Y axis will stop shining. This effect also applies to light objects attached to other objects, players and vehicles.
///   If a light object is attached to a car and the car is rotated over <b><c>16.26</c></b> degrees (like in a rollover), the object will also stop emitting light. This is a GTA:SA issue and is not caused by a bug in SA-MP.
/// </remarks>
/// <remarks>In case the light is attached to another object, one fix for this is to set <b>SyncRotation</b> to false in <a href="#AttachObjectToObject">AttachObjectToObject</a>. This will ensure the light stays at <b><c>0</c></b> rotation. This would only really work for objects that consist ONLY of light, so wouldn't work for the police light for example. </remarks>
/// <remarks>There is a limit of <a href="http://wiki.sa-mp.com/wiki/Limits"><b><c>1000</c></b> objects (<b><c>MAX_OBJECTS</c></b>)</a>. To circumvent this limit, you can use a <a href="http://forum.sa-mp.com/showthread.php?t=102865">streamer</a></remarks>
/// <returns>The ID of the object that was created, or <b><c>INVALID_OBJECT_ID</c></b> if the object limit (<b><c>MAX_OBJECTS</c></b>) was reached.</returns>
native CreateObject(modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0);

/// <summary>Attach an object to a vehicle.</summary>
/// <param name="objectid">The ID of the object to attach to the vehicle. Note that this is an object ID, not a model ID. The object must be CreateObject created first</param>
/// <param name="vehicleid">The ID of the vehicle to attach the object to</param>
/// <param name="OffsetX">The X axis offset from the vehicle to attach the object to</param>
/// <param name="OffsetY">The Y axis offset from the vehicle to attach the object to</param>
/// <param name="OffsetZ">The Z axis offset from the vehicle to attach the object to</param>
/// <param name="RotX">The X rotation offset for the object</param>
/// <param name="RotY">The Y rotation offset for the object</param>
/// <param name="RotZ">The Z rotation offset for the object</param>
/// <seealso name="AttachObjectToPlayer"/>
/// <seealso name="AttachObjectToObject"/>
/// <seealso name="AttachPlayerObjectToVehicle"/>
/// <seealso name="CreateObject"/>
/// <remarks>This function was added in <b>SA-MP 0.3c</b> and will not work in earlier versions!</remarks>
/// <remarks>The object must be created first.</remarks>
/// <remarks>When the vehicle is destroyed or respawned, the attached objects won't be destroyed with it; they will remain stationary at the position the vehicle disappeared and be reattached to the next vehicle to claim the vehicle ID that the objects were attached to.</remarks>
native AttachObjectToVehicle(objectid, vehicleid, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:RotX, Float:RotY, Float:RotZ);

/// <summary>You can use this function to attach objects to other objects. The objects will folow the main object.</summary>
/// <param name="objectid">The object to attach to another object</param>
/// <param name="attachtoid">The object to attach the object to</param>
/// <param name="OffsetX">The distance between the main object and the object in the X direction</param>
/// <param name="OffsetY">The distance between the main object and the object in the Y direction</param>
/// <param name="OffsetZ">The distance between the main object and the object in the Z direction</param>
/// <param name="RotX">The X rotation between the object and the main object</param>
/// <param name="RotY">The Y rotation between the object and the main object</param>
/// <param name="RotZ">The Z rotation between the object and the main object</param>
/// <param name="SyncRotation">If set to <b><c>0</c></b>, objectid's rotation will not change with <paramref name="attachtoid"/>'s (optional=<b><c>1</c></b>)</param>
/// <seealso name="AttachObjectToPlayer"/>
/// <seealso name="AttachObjectToVehicle"/>
/// <seealso name="CreateObject"/>
/// <remarks>This function was added in <b>SA-MP 0.3d</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <ul>
///     <li>Both objects need to be created before attempting to attach them.</li>
///     <li>There is no player-object version of this function (AttachPlayerObjectToObject), meaning it will not be supported by streamers.</li>
///   </ul>
/// </remarks>
/// <returns>
/// <b><c>1</c></b>: The function executed successfully.<p/>
/// <b><c>0</c></b>: The function failed to execute. This means the first object (<paramref name="objectid"/>) does not exist. There are no internal checks to verify that the second object (<paramref name="attachtoid"/>) exists.
/// </returns>
native AttachObjectToObject(objectid, attachtoid, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:RotX, Float:RotY, Float:RotZ, SyncRotation = 1);

/// <summary>Attach an object to a player.</summary>
/// <param name="objectid">The ID of the object to attach to the player</param>
/// <param name="playerid">The ID of the player to attach the object to</param>
/// <param name="OffsetX">The distance between the player and the object in the X direction</param>
/// <param name="OffsetY">The distance between the player and the object in the Y direction</param>
/// <param name="OffsetZ">The distance between the player and the object in the Z direction</param>
/// <param name="RotX">The X rotation between the object and the player</param>
/// <param name="RotY">The Y rotation between the object and the player</param>
/// <param name="RotZ">The Z rotation between the object and the player</param>
/// <seealso name="AttachObjectToVehicle"/>
/// <seealso name="AttachObjectToObject"/>
/// <seealso name="AttachPlayerObjectToPlayer"/>
/// <seealso name="SetPlayerAttachedObject"/>
/// <seealso name="CreateObject"/>
/// <returns>This function always returns <b><c>0</c></b>.</returns>
native AttachObjectToPlayer(objectid, playerid, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:RotX, Float:RotY, Float:RotZ);


/// <summary>Change the position of an object.</summary>
/// <param name="objectid">The ID of the object to set the position of. Returned by <a href="#CreateObject">CreateObject</a></param>
/// <param name="X">The X coordinate to position the object at</param>
/// <param name="Y">The Y coordinate to position the object at</param>
/// <param name="Z">The Z coordinate to position the object at</param>
/// <seealso name="GetObjectPos"/>
/// <seealso name="SetObjectRot"/>
/// <seealso name="GetPlayerObjectPos"/>
/// <seealso name="CreateObject"/>
/// <returns>This function always returns <b><c>1</c></b>, even if the object specified does not exist.</returns>
native SetObjectPos(objectid, Float:X, Float:Y, Float:Z);

/// <summary>Get the position of an object.</summary>
/// <param name="objectid">The ID of the object to get the position of.</param>
/// <param name="X">A variable in which to store the X coordinate, passed by reference</param>
/// <param name="Y">A variable in which to store the Y coordinate, passed by reference</param>
/// <param name="Z">A variable in which to store the Z coordinate, passed by reference</param>
/// <seealso name="SetObjectPos"/>
/// <seealso name="GetObjectRot"/>
/// <seealso name="SetPlayerObjectPos"/>
/// <seealso name="CreateObject"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The specified object does not exist.
/// </returns>
native GetObjectPos(objectid, &Float:X, &Float:Y, &Float:Z);

/// <summary>Set the rotation of an object on the three axes (X, Y and Z).</summary>
/// <param name="objectid">The ID of the object to set the rotation of</param>
/// <param name="RotX">The X rotation</param>
/// <param name="RotY">The Y rotation</param>
/// <param name="RotZ">The Z rotation</param>
/// <seealso name="GetObjectRot"/>
/// <seealso name="GetObjectPos"/>
/// <seealso name="CreateObject"/>
/// <seealso name="SetPlayerObjectRot"/>
/// <returns>This function always returns <b><c>1</c></b>, even if the object doesn't exist.</returns>
native SetObjectRot(objectid, Float:RotX, Float:RotY, Float:RotZ);

/// <summary>Use this function to get the objects current rotation. The rotation is saved by reference in three RotX/RotY/RotZ variables.</summary>
/// <param name="objectid">The objectid of the object you want to get the rotation from</param>
/// <param name="RotX">The variable to store the X rotation, passed by reference</param>
/// <param name="RotY">The variable to store the Y rotation, passed by reference</param>
/// <param name="RotZ">The variable to store the Z rotation, passed by reference</param>
/// <seealso name="SetObjectRot"/>
/// <seealso name="SetObjectPos"/>
/// <seealso name="SetPlayerObjectRot"/>
/// <seealso name="CreateObject"/>
/// <returns>The object's rotation is stored in the referenced variables, not in the return value.</returns>
native GetObjectRot(objectid, &Float:RotX, &Float:RotY, &Float:RotZ);

/// <summary>Get the model ID of an object.</summary>
/// <param name="objectid">The ID of the object to get the model of</param>
/// <seealso name="GetPlayerObjectModel"/>
/// <seealso name="CreateObject"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <returns>The model ID of the object. <b><c>-1</c></b> if <paramref name="objectid"/> does not exist.</returns>
native GetObjectModel(objectid);

/// <summary>Disable collisions between players' cameras and the specified object.</summary>
/// <param name="objectid">The ID of the object to disable camera collisions on</param>
/// <seealso name="SetObjectsDefaultCameraCol"/>
/// <seealso name="SetPlayerObjectNoCameraCol"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions! </remarks>
/// <remarks>This only works outside the map boundaries (past <b><c>-3000</c></b>/<b><c>3000</c></b> units on the x and/or y axis).</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The object specified does not exist.
/// </returns>
native SetObjectNoCameraCol(objectid);

/// <summary>Checks if an object with the ID provided exists.</summary>
/// <param name="objectid">The ID of the object to check the existence of</param>
/// <seealso name="IsValidPlayerObject"/>
/// <seealso name="CreateObject"/>
/// <seealso name="DestroyObject"/>
/// <remarks>This is to check if an object exists, not if a model is valid.</remarks>
/// <returns><b><c>1</c></b> if the object exists, <b><c>0</c></b> if not.</returns>
native IsValidObject(objectid);

/// <summary>Destroys (removes) an object that was created using <a href="#CreateObject">CreateObject</a>.</summary>
/// <param name="objectid">The ID of the object to destroy. Returned by <a href="#CreateObject">CreateObject</a></param>
/// <seealso name="CreateObject"/>
/// <seealso name="IsValidObject"/>
/// <seealso name="DestroyPlayerObject"/>
native DestroyObject(objectid);

/// <summary>Move an object to a new position with a set speed. Players/vehicles will 'surf' the object as it moves.</summary>
/// <param name="objectid">The ID of the object to move</param>
/// <param name="X">The X coordinate to move the object to</param>
/// <param name="Y">The Y coordinate to move the object to</param>
/// <param name="Z">The Z coordinate to move the object to</param>
/// <param name="Speed">The speed at which to move the object (units per second)</param>
/// <param name="RotX">The FINAL X rotation (optional=<b><c>-1000.0</c></b>)</param>
/// <param name="RotY">The FINAL Y rotation (optional=<b><c>-1000.0</c></b>)</param>
/// <param name="RotZ">The FINAL Z rotation (optional=<b><c>-1000.0</c></b>)</param>
/// <seealso name="OnObjectMoved"/>
/// <seealso name="IsObjectMoving"/>
/// <seealso name="StopObject"/>
/// <seealso name="MovePlayerObject"/>
/// <seealso name="SetObjectPos"/>
/// <seealso name="SetObjectRot"/>
/// <seealso name="CreateObject"/>
/// <remarks>This function can be used to make objects rotate smoothly. In order to achieve this however, the object must also be <b>moved</b>. The specified rotation is the rotation the object will have after the movement. Hence the object will not rotate when no movement is applied. For a script example take a look at the ferriswheel.pwn filterscript made by Kye included in the server package (SA-MP 0.3d and above). </remarks>
/// <remarks>To fully understand the above note, you can (but not limited to) increase the z position by <b><c>(+0.001</c></b>) and then (<b><c>-0.001</c></b>) after moving it again, as not changing the X, Y or Z will not rotate the object. </remarks>
/// <returns>The time it will take for the object to move in milliseconds.</returns>
native MoveObject(objectid, Float:X, Float:Y, Float:Z, Float:Speed, Float:RotX = -1000.0, Float:RotY = -1000.0, Float:RotZ = -1000.0);

/// <summary>Stop a moving object after <a href="#MoveObject">MoveObject</a> has been used.</summary>
/// <param name="objectid">The ID of the object to stop moving</param>
/// <seealso name="MoveObject"/>
/// <seealso name="IsObjectMoving"/>
/// <seealso name="OnObjectMoved"/>
/// <seealso name="StopPlayerObject"/>
native StopObject(objectid);

/// <summary>Checks if the given objectid is moving.</summary>
/// <param name="objectid">The objectid you want to check if is moving</param>
/// <seealso name="MoveObject"/>
/// <seealso name="StopObject"/>
/// <seealso name="OnObjectMoved"/>
/// <seealso name="IsPlayerObjectMoving"/>
/// <remarks>This function was added in <b>SA-MP 0.3d</b> and will not work in earlier versions!</remarks>
/// <returns><b><c>1</c></b> if the object is moving, <b><c>0</c></b> if not.</returns>
native IsObjectMoving(objectid);

/// <summary>Allows a player to edit an object (position and rotation) using their mouse on a GUI (Graphical User Interface).</summary>
/// <param name="playerid">The ID of the player that should edit the object</param>
/// <param name="objectid">The ID of the object to be edited by the player</param>
/// <seealso name="EditPlayerObject"/>
/// <seealso name="EditAttachedObject"/>
/// <seealso name="SelectObject"/>
/// <seealso name="CancelEdit"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>You can move the camera while editing by pressing and holding the <b>spacebar</b> (or <b>W</b> in vehicle) and moving your mouse.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully. Success is reported when a non-existent object is specified, but nothing will happen.<p/>
///   <b><c>0</c></b>: The function failed to execute. The player is not connected.
/// </returns>
native EditObject(playerid, objectid);

/// <summary>Allows players to edit a player-object (position and rotation) with a GUI and their mouse.</summary>
/// <param name="playerid">The ID of the player that should edit the object</param>
/// <param name="objectid">The object to be edited by the player</param>
/// <seealso name="EditObject"/>
/// <seealso name="EditAttachedObject"/>
/// <seealso name="SelectObject"/>
/// <seealso name="CancelEdit"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>You can move the camera while editing by pressing and holding the <b>spacebar</b> (or <b>W</b> in vehicle) and moving your mouse.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. Player or object not valid.
/// </returns>
native EditPlayerObject(playerid, objectid);

/// <summary>Display the cursor and allow the player to select an object. <a href="#OnPlayerSelectObject">OnPlayerSelectObject</a> is called when the player selects an object.</summary>
/// <param name="playerid">The ID of the player that should be able to select the object</param>
/// <seealso name="EditObject"/>
/// <seealso name="EditPlayerObject"/>
/// <seealso name="EditAttachedObject"/>
/// <seealso name="CancelEdit"/>
/// <seealso name="OnPlayerSelectObject"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
native SelectObject(playerid);

/// <summary>Cancel object edition mode for a player.</summary>
/// <param name="playerid">The ID of the player to cancel edition for</param>
/// <seealso name="SelectObject"/>
/// <seealso name="EditObject"/>
/// <seealso name="EditPlayerObject"/>
/// <seealso name="EditAttachedObject"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
native CancelEdit(playerid);

/// <summary>Creates an object which will be visible to only one player.</summary>
/// <param name="playerid">The ID of the player to create the object for</param>
/// <param name="modelid">The model to create</param>
/// <param name="X">The X coordinate to create the object at</param>
/// <param name="Y">The Y coordinate to create the object at</param>
/// <param name="Z">The Z coordinate to create the object at</param>
/// <param name="rX">The X rotation of the object</param>
/// <param name="rY">The Y rotation of the object</param>
/// <param name="rZ">The Z rotation of the object</param>
/// <param name="DrawDistance">The distance from which objects will appear to players. <b><c>0.0</c></b> will cause an object to render at its default distance. Leaving this parameter out will cause objects to be rendered at their default distance. <b>The maximum usable distance is <c>300</c> in versions prior to 0.3x</b>, in which drawdistance can be unlimited (optional=<b><c>0.0</c></b>)</param>
/// <seealso name="CreateObject"/>
/// <seealso name="IsValidPlayerObject"/>
/// <seealso name="DestroyPlayerObject"/>
/// <seealso name="MovePlayerObject"/>
/// <seealso name="StopPlayerObject"/>
/// <seealso name="SetPlayerObjectPos"/>
/// <seealso name="SetPlayerObjectRot"/>
/// <seealso name="GetPlayerObjectPos"/>
/// <seealso name="GetPlayerObjectRot"/>
/// <seealso name="AttachPlayerObjectToPlayer"/>
/// <seealso name="AttachObjectToPlayer"/>
/// <remarks>The 'DrawDistance' parameter was added in <b>0.3b</b>. It must be left out in scripts for older versions of SA:MP.</remarks>
/// <returns>The ID of the object that was created, or <b><c>INVALID_OBJECT_ID</c></b> if the object limit (<b><c>MAX_OBJECTS</c></b>) was reached.</returns>
native CreatePlayerObject(playerid, modelid, Float:X, Float:Y, Float:Z, Float:rX, Float:rY, Float:rZ, Float:DrawDistance = 0.0);

/// <summary>Attach a player object to a vehicle.</summary>
/// <param name="playerid">The ID of the player the object was created for</param>
/// <param name="objectid">The ID of the object to attach to the vehicle</param>
/// <param name="vehicleid">The ID of the vehicle to attach the object to</param>
/// <param name="fOffsetX">The X position offset for attachment</param>
/// <param name="fOffsetY">The Y position offset for attachment</param>
/// <param name="fOffsetZ">The Z position offset for attachment</param>
/// <param name="fRotX">The X rotation offset for attachment</param>
/// <param name="fRotY">The Y rotation offset for attachment</param>
/// <param name="RotZ">The Z rotation offset for attachment</param>
/// <seealso name="CreatePlayerObject"/>
/// <seealso name="AttachPlayerObjectToPlayer"/>
/// <seealso name="AttachObjectToVehicle"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>You need to create the object before attempting to attach it to a vehicle.</remarks>
native AttachPlayerObjectToVehicle(playerid, objectid, vehicleid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:RotZ);


/// <summary>Sets the position of a player-object to the specified coordinates.</summary>
/// <param name="playerid">The ID of the player whose player-object to set the position of</param>
/// <param name="objectid">The ID of the player-object to set the position of. Returned by <a href="#CreatePlayerObject">CreatePlayerObject</a></param>
/// <param name="X">The X coordinate to put the object at</param>
/// <param name="Y">The Y coordinate to put the object at</param>
/// <param name="Z">The Z coordinate to put the object at</param>
/// <seealso name="GetPlayerObjectPos"/>
/// <seealso name="SetPlayerObjectRot"/>
/// <seealso name="SetObjectPos"/>
/// <seealso name="CreatePlayerObject"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. Player and/or object do not exist.
/// </returns>
native SetPlayerObjectPos(playerid, objectid, Float:X, Float:Y, Float:Z);

/// <summary>Get the position of a player object (<a href="#CreatePlayerObject">CreatePlayerObject</a>).</summary>
/// <param name="playerid">The ID of the player whose player object to get the position of</param>
/// <param name="objectid">The object's id of which you want the current location</param>
/// <param name="X">A float variable in which to store the X coordinate, passed by reference</param>
/// <param name="Y">A float variable in which to store the Y coordinate, passed by reference</param>
/// <param name="Z">A float variable in which to store the Z coordinate, passed by reference</param>
/// <seealso name=""/>
/// <seealso name="SetPlayerObjectPos"/>
/// <seealso name="GetPlayerObjectRot"/>
/// <seealso name="GetObjectPos"/>
/// <seealso name="CreatePlayerObject"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The player and/or the object don't exist.<p/>
///   The object's position is stored in the specified variables.
/// </returns>
native GetPlayerObjectPos(playerid, objectid, &Float:X, &Float:Y, &Float:Z);

/// <summary>Set the rotation of an object on the X, Y and Z axis.</summary>
/// <param name="playerid">The ID of the player whose player-object to rotate</param>
/// <param name="objectid">The ID of the player-object to rotate</param>
/// <param name="RotX">The X rotation to set</param>
/// <param name="RotY">The Y rotation to set</param>
/// <param name="RotZ">The Z rotation to set</param>
/// <seealso name="GetPlayerObjectRot"/>
/// <seealso name="SetPlayerObjectPos"/>
/// <seealso name="SetObjectRot"/>
/// <seealso name="CreatePlayerObject"/>
/// <remarks>To smoothly rotate an object, see <a href="#MovePlayerObject">MovePlayerObject</a>.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute.
/// </returns>
native SetPlayerObjectRot(playerid, objectid, Float:RotX, Float:RotY, Float:RotZ);

/// <summary>Use this function to get the object's current rotation. The rotation is saved by reference in three RotX/RotY/RotZ variables.</summary>
/// <param name="playerid">The player you associated this object to</param>
/// <param name="objectid">The objectid of the object you want to get the rotation from</param>
/// <param name="RotX">The variable to store the X rotation, passed by reference</param>
/// <param name="RotY">The variable to store the Y rotation, passed by reference</param>
/// <param name="RotZ">The variable to store the Z rotation, passed by reference</param>
/// <seealso name="SetPlayerObjectRot"/>
/// <seealso name="GetPlayerObjectPos"/>
/// <seealso name="GetObjectRot"/>
/// <seealso name="CreatePlayerObject"/>
/// <returns>The object's rotation is stored in the specified variables.</returns>
native GetPlayerObjectRot(playerid, objectid, &Float:RotX, &Float:RotY, &Float:RotZ);

/// <summary>Retrieve the model ID of a player-object.</summary>
/// <param name="playerid">The ID of the player whose player-object to get the model of</param>
/// <param name="objectid">The ID of the player-object of which to retrieve the model ID</param>
/// <seealso name="GetObjectModel"/>
/// <seealso name="CreatePlayerObject"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <returns>The model ID of the player object. If the player or object don't exist, it will return <b><c>-1</c></b> or <b><c>0</c></b> if the player or object does not exist.</returns>
native GetPlayerObjectModel(playerid, objectid);

/// <summary>Toggles a player object camera collision.</summary>
/// <param name="playerid">The playerID the object belongs to</param>
/// <param name="objectid">The ID of the object you want to toggle</param>
/// <seealso name="SetObjectNoCameraCol"/>
/// <seealso name="SetObjectsDefaultCameraCol"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>This only works outside the map boundaries (past <b><c>-3000</c></b>/<b><c>3000</c></b> units on the x and/or y axis).</remarks>
/// <returns><b><c>1</c></b> regardless of if the object exists or not.</returns>
native SetPlayerObjectNoCameraCol(playerid, objectid);

/// <summary>Checks if the given object ID is valid for the given player.</summary>
/// <param name="playerid">The ID of the player whose player-object to validate</param>
/// <param name="objectid">The ID of the object to validate</param>
/// <seealso name="IsValidObject"/>
/// <seealso name="CreatePlayerObject"/>
/// <seealso name="DestroyPlayerObject"/>
/// <returns><b><c>1</c></b> if the object exists, <b><c>0</c></b> if not.</returns>
native IsValidPlayerObject(playerid, objectid);

/// <summary>Destroy a player-object created using <a href="#CreatePlayerObject">CreatePlayerObject</a>.</summary>
/// <param name="playerid">The ID of the player whose player-object to destroy</param>
/// <param name="objectid">The ID of the player-object to destroy. Returned by <a href="#CreatePlayerObject">CreatePlayerObject</a></param>
/// <seealso name="CreatePlayerObject"/>
/// <seealso name="IsValidPlayerObject"/>
/// <seealso name="DestroyObject"/>
native DestroyPlayerObject(playerid, objectid);

/// <summary>Move a player object with a set speed. Also supports rotation. Players/vehicles will surf moving objects.</summary>
/// <param name="playerid">The ID of the player whose player-object to move</param>
/// <param name="objectid">The ID of the object to move</param>
/// <param name="X">The X coordinate to move the object to</param>
/// <param name="Y">The Y coordinate to move the object to</param>
/// <param name="Z">The Z coordinate to move the object to</param>
/// <param name="Speed">The speed at which to move the object</param>
/// <param name="RotX">The final X rotation (optional=<b><c>-1000.0</c></b>)</param>
/// <param name="RotY">The final Y rotation (optional=<b><c>-1000.0</c></b>)</param>
/// <param name="RotZ">The final Z rotation (optional=<b><c>-1000.0</c></b>)</param>
/// <seealso name="OnPlayerObjectMoved"/>
/// <seealso name="IsPlayerObjectMoving"/>
/// <seealso name="StopPlayerObject"/>
/// <seealso name="MoveObject"/>
/// <seealso name="SetPlayerObjectPos"/>
/// <seealso name="SetPlayerObjectRot"/>
/// <seealso name="CreatePlayerObject"/>
/// <remarks><b>0.3d R2</b> and older versions do not have the rotational parameters.</remarks>
/// <returns>The time it will take for the object to move in milliseconds.</returns>
native MovePlayerObject(playerid, objectid, Float:X, Float:Y, Float:Z, Float:Speed, Float:RotX = -1000.0, Float:RotY = -1000.0, Float:RotZ = -1000.0);

/// <summary>Stop a moving player-object after <a href="#MovePlayerObject">MovePlayerObject</a> has been used.</summary>
/// <param name="playerid">The ID of the player whose player-object to stop</param>
/// <param name="objectid">The ID of the player-object to stop</param>
/// <seealso name="MovePlayerObject"/>
/// <seealso name="IsPlayerObjectMoving"/>
/// <seealso name="OnPlayerObjectMoved"/>
/// <seealso name="StopObject"/>
native StopPlayerObject(playerid, objectid);

/// <summary>Checks if the given player objectid is moving.</summary>
/// <param name="playerid">The ID of the player whose player-object is checked</param>
/// <param name="objectid">The player objectid you want to check if is moving</param>
/// <seealso name="MovePlayerObject"/>
/// <seealso name="StopPlayerObject"/>
/// <seealso name="OnPlayerObjectMoved"/>
/// <seealso name="IsObjectMoving"/>
/// <remarks>This function was added in <b>SA-MP 0.3d</b> and will not work in earlier versions!</remarks>
/// <returns><b><c>1</c></b> if the player object is moving, <b><c>0</c></b> if not.</returns>
native IsPlayerObjectMoving(playerid, objectid);

/// <summary>The same as AttachObjectToPlayer but for objects which were created for player.</summary>
/// <param name="objectplayer">The id of the player which is linked with the object</param>
/// <param name="objectid">The objectid you want to attach to the player</param>
/// <param name="attachplayer">The id of the player you want to attach to the object</param>
/// <param name="OffsetX">The distance between the player and the object in the X direction</param>
/// <param name="OffsetY">The distance between the player and the object in the Y direction</param>
/// <param name="OffsetZ">The distance between the player and the object in the Z direction</param>
/// <param name="rX">The X rotation</param>
/// <param name="rY">The Y rotation</param>
/// <param name="rZ">The Z rotation</param>
/// <seealso name="SetPlayerAttachedObject"/>
/// <seealso name="AttachPlayerObjectToVehicle"/>
/// <seealso name="AttachObjectToPlayer"/>
/// <seealso name="CreatePlayerObject"/>
/// <remarks><b>This function was removed in SA-MP 0.3.</b></remarks>
native AttachPlayerObjectToPlayer(objectplayer, objectid, attachplayer, Float:OffsetX, Float:OffsetY, Float:OffsetZ, Float:rX, Float:rY, Float:rZ);

/// <summary>Replace the texture of an object with the texture from another model in the game.</summary>
/// <param name="objectid">The ID of the object to change the texture of</param>
/// <param name="materialindex">The material index on the object to change (<b><c>0</c></b> to <b><c>15</c></b>)</param>
/// <param name="modelid">The modelid on which the replacement texture is located. Use <b><c>0</c></b> for alpha. Use <b><c>-1</c></b> to change the material color without altering the texture</param>
/// <param name="txdname">The name of the txd file which contains the replacement texture (use <b><c>"none"</c></b> if not required)</param>
/// <param name="texturename">The name of the texture to use as the replacement (use <b><c>"none"</c></b> if not required)</param>
/// <param name="materialcolor">The object color to set, as an integer or hex in <b>ARGB</b> color format. Using <b><c>0</c></b> keeps the existing material color (optional=<b><c>0</c></b>)</param>
/// <seealso name="SetPlayerObjectMaterial"/>
/// <seealso name="SetObjectMaterialText"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>Vertex lightning of the object will disappear if material color is changed.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute.
/// </returns>
native SetObjectMaterial(objectid, materialindex, modelid, const txdname[], const texturename[], materialcolor=0);

/// <summary>Replace the texture of a player-object with the texture from another model in the game.</summary>
/// <param name="playerid">The ID of the player the object is associated to</param>
/// <param name="objectid">The ID of the object to replace the texture of</param>
/// <param name="materialindex">The material index on the object to change (<b><c>0</c></b> to <b><c>15</c></b>)</param>
/// <param name="modelid">The modelid on which replacement texture is located. Use <b><c>0</c></b> for alpha. Use <b><c>-1</c></b> to change the material color without altering the existing texture</param>
/// <param name="txdname">The name of the txd file which contains the replacement texture (use <b><c>"none"</c></b> if not required)</param>
/// <param name="texturename">The name of the texture to use as the replacement (use <b><c>"none"</c></b> if not required)</param>
/// <param name="materialcolor">The object color to set (<b>ARGB</b>). Using <b><c>0</c></b> keeps the existing material color (optional=<b><c>0</c></b>)</param>
/// <seealso name="SetObjectMaterial"/>
/// <seealso name="SetPlayerObjectMaterialText"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>Vertex lightning of the object will disappear if material color is changed.</remarks>
native SetPlayerObjectMaterial(playerid, objectid, materialindex, modelid, const txdname[], const texturename[], materialcolor=0);


/// <summary>Replace the texture of an object with text.</summary>
/// <param name="objectid">The ID of the object to replace the texture of with text</param>
/// <param name="text">The text to show on the object. (MAX <b>2048</b> characters)</param>
/// <param name="materialindex">The object's material index to replace with text (optional=<b><c>0</c></b>)</param>
/// <param name="materialsize">The size of the material (optional=<b><c>OBJECT_MATERIAL_SIZE_256x128</c></b>)</param>
/// <param name="fontface">The font to use (optional=<b><c>"Arial"</c></b>)</param>
/// <param name="fontsize">The size of the text (MAX <b>255</b>) (optional=<b><c>24</c></b>)</param>
/// <param name="bold">Bold text. Set to <b><c>1</c></b> for bold, <b><c>0</c></b> for not (optional=<b><c>1</c></b>)</param>
/// <param name="fontcolor">The color of the text, in <b>ARGB</b> format (optional=<b><c>-1</c></b>)</param>
/// <param name="backcolor">The background color, in <b>ARGB</b> format (optional=<b><c>0</c></b>)</param>
/// <param name="textalignment">The alignment of the text (optional=<b><c>OBJECT_MATERIAL_TEXT_ALIGN_LEFT</c></b>)</param>
/// <seealso name="SetPlayerObjectMaterialText"/>
/// <seealso name="SetObjectMaterial"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>Color embedding can be used for multiple colors in the text.</remarks>
/// <remarks>
///   <b>Alignment:</b><p/>
///   <ul>
///     <li><b><c>OBJECT_MATERIAL_TEXT_ALIGN_LEFT</c></b> 0</li>
///     <li><b><c>OBJECT_MATERIAL_TEXT_ALIGN_CENTER</c></b> 1</li>
///     <li><b><c>OBJECT_MATERIAL_TEXT_ALIGN_RIGHT</c></b> 2</li>
///   </ul>
/// </remarks>
/// <remarks>
///   <b>Sizes:</b><p/>
///   <ul>
///     <li><b><c>OBJECT_MATERIAL_SIZE_32x32</c></b> 10</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_64x32</c></b> 20</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_64x64</c></b> 30</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_128x32</c></b> 40</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_128x64</c></b> 50</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_128x128</c></b> 60</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x32</c></b> 70</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x64</c></b> 80</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x128</c></b> 90</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x256</c></b> 100</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x64</c></b> 110</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x128</c></b> 120</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x256</c></b> 130</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x512</c></b> 140</li>
///   </ul>
/// </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute.
/// </returns>
native SetObjectMaterialText(objectid, const text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);

/// <summary>Replace the texture of a player object with text.</summary>
/// <param name="playerid">The ID of the player whose player object to set the text of</param>
/// <param name="objectid">The ID of the object on which to place the text</param>
/// <param name="text">The text to set</param>
/// <param name="materialindex">The material index to replace with text (optional=<b><c>0</c></b>)</param>
/// <param name="materialsize">The size of the material (optional=<b><c>OBJECT_MATERIAL_SIZE_256x128</c></b>)</param>
/// <param name="fontface">The font to use (optional=<b><c>"Arial"</c></b>)</param>
/// <param name="fontsize">The size of the text (MAX 255) (optional=<b><c>24</c></b>)</param>
/// <param name="bold">Bold text. Set to <b><c>1</c></b> for bold, <b><c>0</c></b> for not (optional=<b><c>1</c></b>)</param>
/// <param name="fontcolor">The color of the text (optional=<b><c>-1</c></b>)</param>
/// <param name="backcolor">The background color (optional=<b><c>0</c></b>)</param>
/// <param name="textalignment">The alignment of the text (optional=<b><c>OBJECT_MATERIAL_TEXT_ALIGN_LEFT</c></b>)</param>
/// <seealso name="SetObjectMaterialText"/>
/// <seealso name="SetPlayerObjectMaterial"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>Color embedding can be used for multiple colors in the text.</remarks>
/// <remarks>
///   <b>Alignment:</b><p/>
///   <ul>
///     <li><b><c>OBJECT_MATERIAL_TEXT_ALIGN_LEFT</c></b> 0</li>
///     <li><b><c>OBJECT_MATERIAL_TEXT_ALIGN_CENTER</c></b> 1</li>
///     <li><b><c>OBJECT_MATERIAL_TEXT_ALIGN_RIGHT</c></b> 2</li>
///   </ul>
/// </remarks>
/// <remarks>
///   <b>Sizes:</b><p/>
///   <ul>
///     <li><b><c>OBJECT_MATERIAL_SIZE_32x32</c></b> 10</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_64x32</c></b> 20</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_64x64</c></b> 30</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_128x32</c></b> 40</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_128x64</c></b> 50</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_128x128</c></b> 60</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x32</c></b> 70</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x64</c></b> 80</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x128</c></b> 90</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_256x256</c></b> 100</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x64</c></b> 110</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x128</c></b> 120</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x256</c></b> 130</li>
///     <li><b><c>OBJECT_MATERIAL_SIZE_512x512</c></b> 140</li>
///   </ul>
/// </remarks>
native SetPlayerObjectMaterialText(playerid, objectid, const text[], materialindex = 0, materialsize = OBJECT_MATERIAL_SIZE_256x128, const fontface[] = "Arial", fontsize = 24, bold = 1, fontcolor = 0xFFFFFFFF, backcolor = 0, textalignment = 0);


/// <summary>Allows camera collisions with newly created objects to be disabled by default.</summary>
/// <param name="disable"><b><c>1</c></b> to disable camera collisions for newly created objects and <b><c>0</c></b> to enable them (enabled by default)</param>
/// <seealso name="SetObjectNoCameraCol"/>
/// <seealso name="SetPlayerObjectNoCameraCol"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>This function only affects the camera collision of objects created AFTER its use - it does not toggle existing objects' camera collisions.</remarks>
/// <remarks>This only works outside the map boundaries (past <b><c>-3000</c></b>/<b><c>3000</c></b> units on the x and/or y axis).</remarks>
native SetObjectsDefaultCameraCol(disable);

