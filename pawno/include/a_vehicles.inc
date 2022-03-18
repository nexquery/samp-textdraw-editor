/*  SA-MP Vehicle Functions
 *
 *  (c) Copyright 2005-2012, SA-MP Team
 *
 */

#if defined _INC_a_vehicles
	#endinput
#endif
#define _INC_a_vehicles
#define _vehicles_included

#define SAMP_CONST_CORRECT

#pragma tabsize 4

// --------------------------------------------------
// Defines
// --------------------------------------------------

#define CARMODTYPE_SPOILER                     (0)
#define CARMODTYPE_HOOD                        (1)
#define CARMODTYPE_ROOF                        (2)
#define CARMODTYPE_SIDESKIRT                   (3)
#define CARMODTYPE_LAMPS                       (4)
#define CARMODTYPE_NITRO                       (5)
#define CARMODTYPE_EXHAUST                     (6)
#define CARMODTYPE_WHEELS                      (7)
#define CARMODTYPE_STEREO                      (8)
#define CARMODTYPE_HYDRAULICS                  (9)
#define CARMODTYPE_FRONT_BUMPER                (10)
#define CARMODTYPE_REAR_BUMPER                 (11)
#define CARMODTYPE_VENT_RIGHT                  (12)
#define CARMODTYPE_VENT_LEFT                   (13)

#define VEHICLE_PARAMS_UNSET                   (-1)
#define VEHICLE_PARAMS_OFF                     (0)
#define VEHICLE_PARAMS_ON                      (1)

#define VEHICLE_MODEL_INFO_SIZE                (1)
#define VEHICLE_MODEL_INFO_FRONTSEAT           (2)
#define VEHICLE_MODEL_INFO_REARSEAT            (3)
#define VEHICLE_MODEL_INFO_PETROLCAP           (4)
#define VEHICLE_MODEL_INFO_WHEELSFRONT         (5)
#define VEHICLE_MODEL_INFO_WHEELSREAR          (6)
#define VEHICLE_MODEL_INFO_WHEELSMID           (7)
#define VEHICLE_MODEL_INFO_FRONT_BUMPER_Z      (8)
#define VEHICLE_MODEL_INFO_REAR_BUMPER_Z       (9)

// Vehicle

/// <summary>Creates a vehicle in the world. Can be used in place of <a href="#AddStaticVehicleEx">AddStaticVehicleEx</a> at any time in the script.</summary>
/// <param name="vehicletype">The <a href="http://wiki.sa-mp.com/wiki/Vehicle_Models">model</a> for the vehicle</param>
/// <param name="x">The X coordinate for the vehicle</param>
/// <param name="y">The Y coordinate for the vehicle</param>
/// <param name="z">The Z coordinate for the vehicle</param>
/// <param name="rotation">The facing angle for the vehicle</param>
/// <param name="color1">The primary <a href="http://wiki.sa-mp.com/wiki/Color_ID">color ID</a></param>
/// <param name="color2">The secondary <a href="http://wiki.sa-mp.com/wiki/Color_ID">color ID</a></param>
/// <param name="respawn_delay">The delay until the car is respawned without a driver in <b>seconds</b>. Using <b><c>-1</c></b> will prevent the vehicle from respawning</param>
/// <param name="addsiren"><b>Added in 0.3.7; will not work in earlier versions</b>. Enables the vehicle to have a siren, providing the vehicle has a horn (optional=<b><c>0</c></b>)</param>
/// <seealso name="DestroyVehicle"/>
/// <seealso name="AddStaticVehicle"/>
/// <seealso name="AddStaticVehicleEx"/>
/// <seealso name="GetVehicleParamsSirenState"/>
/// <seealso name="OnVehicleSpawn"/>
/// <seealso name="OnVehicleSirenStateChange"/>
/// <remarks>Trains can only be added with AddStaticVehicle and AddStaticVehicleEx.</remarks>
/// <returns>
///   The vehicle ID of the vehicle created (<b><c>1</c></b> to <b><c>MAX_VEHICLES</c></b>).<p/>
///   <b><c>INVALID_VEHICLE_ID (65535)</c></b> if vehicle was not created (vehicle limit reached or invalid vehicle model ID passed).
/// </returns>
native CreateVehicle(vehicletype, Float:x, Float:y, Float:z, Float:rotation, color1, color2, respawn_delay, addsiren=0);

/// <summary>Destroy a vehicle. It will disappear instantly.</summary>
/// <param name="vehicleid">The ID of the vehicle to destroy</param>
/// <seealso name="CreateVehicle"/>
/// <seealso name="RemovePlayerFromVehicle"/>
/// <seealso name="SetVehicleToRespawn"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle does not exist.
/// </returns>
native DestroyVehicle(vehicleid);

/// <summary>Checks if a vehicle is streamed in for a player. Only nearby vehicles are streamed in (visible) for a player.</summary>
/// <param name="vehicleid">The ID of the vehicle to check</param>
/// <param name="forplayerid">The ID of the player to check</param>
/// <seealso name="IsPlayerStreamedIn"/>
/// <seealso name="OnVehicleStreamIn"/>
/// <seealso name="OnVehicleStreamOut"/>
/// <seealso name="OnPlayerStreamIn"/>
/// <seealso name="OnPlayerStreamOut"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>0</c></b>: Vehicle is not streamed in for the player, or the function failed to execute (player and/or vehicle do not exist).<p/>
///   <b><c>1</c></b>: Vehicle is streamed in for the player.
/// </returns>
native IsVehicleStreamedIn(vehicleid, forplayerid);

/// <summary>Gets the position of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the position of</param>
/// <param name="x">A float variable in which to store the X coordinate, passed by reference</param>
/// <param name="y">A float variable in which to store the Y coordinate, passed by reference</param>
/// <param name="z">A float variable in which to store the Z coordinate, passed by reference</param>
/// <seealso name="GetVehicleDistanceFromPoint"/>
/// <seealso name="SetVehiclePos"/>
/// <seealso name="GetVehicleZAngle"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle specified does not exist.
/// </returns>
native GetVehiclePos(vehicleid, &Float:x, &Float:y, &Float:z);

/// <summary>Set a vehicle's position.</summary>
/// <param name="vehicleid">Vehicle ID that you want set new position</param>
/// <param name="x">The X coordinate to position the vehicle at</param>
/// <param name="y">The Y coordinate to position the vehicle at</param>
/// <param name="z">The Z coordinate to position the vehicle at</param>
/// <seealso name="SetPlayerPos"/>
/// <seealso name="GetVehiclePos"/>
/// <seealso name="SetVehicleZAngle"/>
/// <remarks>An empty vehicle will not fall after being teleported into the air.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle specified does not exist.
/// </returns>
native SetVehiclePos(vehicleid, Float:x, Float:y, Float:z);

/// <summary>Get the rotation of a vehicle on the Z axis (yaw).</summary>
/// <param name="vehicleid">The ID of the vehicle to get the Z angle of</param>
/// <param name="z_angle">A float variable in which to store the Z rotation, passed by reference</param>
/// <seealso name="GetVehicleRotationQuat"/>
/// <seealso name="GetVehicleRotation"/>
/// <seealso name="SetVehicleZAngle"/>
/// <seealso name="GetVehiclePos"/>
/// <seealso name="GetPlayerFacingAngle"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle does not exist.
/// </returns>
native GetVehicleZAngle(vehicleid, &Float:z_angle);

/// <summary>Returns a vehicle's rotation on all axes as a quaternion.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the rotation of</param>
/// <param name="w">A float variable in which to store the first quaternion angle, passed by reference</param>
/// <param name="x">A float variable in which to store the second quaternion angle, passed by reference</param>
/// <param name="y">A float variable in which to store the third quaternion angle, passed by reference</param>
/// <param name="z">A float variable in which to store the fourth quaternion angle, passed by reference</param>
/// <seealso name="GetVehicleZAngle"/>
/// <remarks>This function was added in <b>SA-MP 0.3b</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <b>To euler:</b><p/>
///   <code>
///     //GetVehicleRotation Created by IllidanS4<p/>
///     stock GetVehicleRotation(vehicleid,&amp;Float:rx,&amp;Float:ry,&amp;Float:rz){<p/>
///     &#9;new Float:qw,Float:qx,Float:qy,Float:qz;<p/>
///     &#9;GetVehicleRotationQuat(vehicleid,qw,qx,qy,qz);<p/>
///     &#9;rx = asin(2*qy*qz-2*qx*qw);<p/>
///     &#9;ry = -atan2(qx*qz+qy*qw,0.5-qx*qx-qy*qy);<p/>
///     &#9;rz = -atan2(qx*qy+qz*qw,0.5-qx*qx-qz*qz);<p/>
///     }
///   </code>
/// </remarks>
/// <remarks>There is no 'set' variation of this function; you can not SET a vehicle's rotation (apart from the <a href="#SetVehicleZAngle">Z angle</a>) </remarks>
/// <remarks>This function may return incorrect values for unoccupied vehicles. The reason is that the third row of the vehicle's internal rotation matrix gets corrupted if it gets updated while unoccupied. </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle specified does not exist.
/// </returns>
native GetVehicleRotationQuat(vehicleid, &Float:w, &Float:x, &Float:y, &Float:z);

/// <summary>This function can be used to calculate the distance (as a float) between a vehicle and another map coordinate. This can be useful to detect how far a vehicle away is from a location.</summary>
/// <param name="vehicleid">The ID of the vehicle to calculate the distance for</param>
/// <param name="X">The X map coordinate</param>
/// <param name="Y">The Y map coordinate</param>
/// <param name="Z">The Z map coordinate</param>
/// <seealso name="GetPlayerDistanceFromPoint"/>
/// <seealso name="GetVehiclePos"/>
/// <remarks>This function was added in <b>SA-MP 0.3c R3</b> and will not work in earlier versions!</remarks>
/// <returns>A float containing the distance from the point specified in the coordinates.</returns>
native Float:GetVehicleDistanceFromPoint(vehicleid, Float:X, Float:Y, Float:Z);

/// <summary>Set the Z rotation (yaw) of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the rotation of</param>
/// <param name="z_angle">The Z angle to set</param>
/// <seealso name="GetVehicleZAngle"/>
/// <seealso name="SetVehiclePos"/>
/// <remarks>A vehicle's X and Y (pitch and roll) rotation will be reset when this function is used. The X and Y rotations can not be set.</remarks>
/// <remarks>This function does not work on unoccupied vehicles.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle specified does not exist.
/// </returns>
native SetVehicleZAngle(vehicleid, Float:z_angle);

/// <summary>Set the parameters of a vehicle for a player.</summary>
/// <param name="vehicle">The ID of the vehicle to set the parameters of</param>
/// <param name="playerid">The ID of the player to set the vehicle's parameters for</param>
/// <param name="objective"><b><c>0</c></b> to disable the objective or <b><c>1</c></b> to show it. This is a bobbing yellow arrow above the vehicle</param>
/// <param name="doorslocked"><b><c>0</c></b> to unlock the doors or <b><c>1</c></b> to lock them</param>
/// <seealso name="SetVehicleParamsEx"/>
/// <remarks>Vehicles must be respawned for the 'objective' to be removed. This can be circumvented somewhat using Get/SetVehicleParamsEx which do not require the vehicle to be respawned. It is worth noting however that the object will be disabled on a global scale, and this is only useful if only one player has the vehicle as an objective.</remarks>
/// <remarks>Since <b>0.3a</b> you will have to reapply this function when <a href="#OnVehicleStreamIn">OnVehicleStreamIn</a> is called.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The player and/or vehicle specified do not exist.
/// </returns>
native SetVehicleParamsForPlayer(vehicleid, playerid, objective, doorslocked);

/// <summary>Use this function before any player connects (<a href="#OnGameModeInit">OnGameModeInit</a>) to tell all clients that the script will control vehicle engines and lights. This prevents the game automatically turning the engine on/off when players enter/exit vehicles and headlights automatically coming on when it is dark.</summary>
/// <seealso name="SetVehicleParamsEx"/>
/// <seealso name="GetVehicleParamsEx"/>
/// <seealso name="SetVehicleParamsForPlayer"/>
/// <remarks>This Function was added in <b>SA-MP 0.3c</b> and will not work in earlier versions!</remarks>
/// <remarks>Is it not possible to reverse this function after it has been used. You must either use it or not use it.</remarks>
/// <returns>This function always returns <b><c>1</c></b>. It cannot fail to execute.</returns>
native ManualVehicleEngineAndLights();

/// <summary>Sets a vehicle's parameters for all players.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the parameters of</param>
/// <param name="engine">Engine status. <b><c>0</c></b> - Off, <b><c>1</c></b> - On</param>
/// <param name="lights">Light status. <b><c>0</c></b> - Off, <b><c>1</c></b> - On</param>
/// <param name="alarm">Vehicle alarm status. If on, the alarm starts. <b><c>0</c></b> - Off, <b><c>1</c></b> - On</param>
/// <param name="doors">Door lock status. <b><c>0</c></b> - Unlocked, <b><c>1</c></b> - Locked</param>
/// <param name="bonnet">Bonnet (hood) status. <b><c>0</c></b> - Closed, <b><c>1</c></b> - Open</param>
/// <param name="boot">Boot/trunk status. <b><c>0</c></b> - Closed, <b><c>1</c></b> - Open</param>
/// <param name="objective">Toggle the objective arrow above the vehicle. <b><c>0</c></b> - Off, <b><c>1</c></b> - On</param>
/// <seealso name="GetVehicleParamsEx"/>
/// <seealso name="SetVehicleParamsForPlayer"/>
/// <seealso name="UpdateVehicleDamageStatus"/>
/// <remarks>This function was added in <b>SA-MP 0.3c</b> and will not work in earlier versions! </remarks>
/// <remarks>The alarm will not reset when finished, you'll need to reset it by yourself with this function. </remarks>
/// <remarks>Lights also operate during the day (Only when <a href="#ManualVehicleEngineAndLights">ManualVehicleEngineAndLights</a> is enabled). </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle does not exist.
/// </returns>
native SetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

/// <summary>Gets a vehicle's parameters.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the parameters from</param>
/// <param name="engine">Get the engine status. If <b><c>1</c></b>, the engine is running.</param>
/// <param name="lights">Get the vehicle's lights' state. If <b><c>1</c></b> the lights are on</param>
/// <param name="alarm">Get the vehicle's alarm state. If <b><c>1</c></b> the alarm is (or was) sounding</param>
/// <param name="doors">Get the lock status of the doors. If <b><c>1</c></b> the doors are locked</param>
/// <param name="bonnet">Get the bonnet/hood status. If <b><c>1</c></b>, it's open</param>
/// <param name="boot">Get the boot/trunk status. <b><c>1</c></b> means it is open</param>
/// <param name="objective">Get the objective status. <b><c>1</c></b> means the objective is on</param>
/// <seealso name="SetVehicleParamsEx"/>
/// <remarks>This function was added in <b>SA-MP 0.3c</b> and will not work in earlier versions!</remarks>
/// <remarks>If a parameter is unset (SetVehicleParamsEx not used beforehand) the value will be <b><c>-1</c></b> ('unset').</remarks>
native GetVehicleParamsEx(vehicleid, &engine, &lights, &alarm, &doors, &bonnet, &boot, &objective);

/// <summary>Returns a vehicle's siren state (on/off).</summary>
/// <param name="vehicleid">The ID of the vehicle to get the siren state of</param>
/// <seealso name="OnVehicleSirenStateChange"/>
/// <remarks>This function was added in <b>SA-MP 0.3c R3</b> and will not work in earlier versions!</remarks>
/// <returns><b><c>-1</c></b> if unset (off), <b><c>0</c></b> if off, <b><c>1</c></b> if on</returns>
native GetVehicleParamsSirenState(vehicleid);

/// <summary>Allows you to open and close the doors of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the door state of</param>
/// <param name="driver">The state of the driver's door. <b><c>1</c></b> to open, <b><c>0</c></b> to close</param>
/// <param name="passenger">The state of the passenger door. <b><c>1</c></b> to open, <b><c>0</c></b> to close</param>
/// <param name="backleft">The state of the rear left door (if available). <b><c>1</c></b> to open, <b><c>0</c></b> to close</param>
/// <param name="backright">The state of the rear right door (if available). <b><c>1</c></b> to open, <b><c>0</c></b> to close</param>
/// <seealso name="GetVehicleParamsCarDoors"/>
/// <seealso name="SetVehicleParamsCarWindows"/>
/// <seealso name="GetVehicleParamsCarWindows"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks><b><c>1</c></b> is open, <b><c>0</c></b> is closed</remarks>
native SetVehicleParamsCarDoors(vehicleid, driver, passenger, backleft, backright);

/// <summary>Allows you to retrieve the current state of a vehicle's doors.</summary>
/// <param name="vehicleid">The ID of the vehicle</param>
/// <param name="driver">The integer to save the state of the driver's door to</param>
/// <param name="passenger">The integer to save the state of the passenger's door to</param>
/// <param name="backleft">The integer to save the state of the rear left door to (if available)</param>
/// <param name="backright">The integer to save the state of the rear right door to (if available)</param>
/// <seealso name="SetVehicleParamsCarDoors"/>
/// <seealso name="SetVehicleParamsCarWindows"/>
/// <seealso name="GetVehicleParamsCarWindows"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>The values returned in each variable are as follows: <b><c>-1</c></b> if not set, <b><c>0</c></b> if closed, <b><c>1</c></b> if open.</remarks>
native GetVehicleParamsCarDoors(vehicleid, &driver, &passenger, &backleft, &backright);

/// <summary>Allows you to open and close the windows of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the window state of</param>
/// <param name="driver">The state of the driver's window. <b><c>0</c></b> to open, <b><c>1</c></b> to close</param>
/// <param name="passenger">The state of the passenger window. <b><c>0</c></b> to open, <b><c>1</c></b> to close</param>
/// <param name="backleft">The state of the rear left window (if available). <b><c>0</c></b> to open, <b><c>1</c></b> to close</param>
/// <param name="backright">The state of the rear right window (if available). <b><c>0</c></b> to open, <b><c>1</c></b> to close</param>
/// <seealso name="SetVehicleParamsCarDoors"/>
/// <seealso name="GetVehicleParamsCarDoors"/>
/// <seealso name="GetVehicleParamsCarWindows"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
native SetVehicleParamsCarWindows(vehicleid, driver, passenger, backleft, backright);

/// <summary>Allows you to retrieve the current state of a vehicle's windows.</summary>
/// <param name="vehicleid">The ID of the vehicle</param>
/// <param name="driver">The integer to save the state of the drivers window to</param>
/// <param name="passenger">The integer to save the state of the passengers window to</param>
/// <param name="backleft">The integer to save the state of the rear left window to (if available)</param>
/// <param name="backright">The integer to save the state of the rear right window to (if available)</param>
/// <seealso name="SetVehicleParamsCarWindows"/>
/// <seealso name="GetVehicleParamsCarDoors"/>
/// <seealso name="SetVehicleParamsCarDoors"/>
/// <remarks>This function was added in <b>SA-MP 0.3.7</b> and will not work in earlier versions!</remarks>
/// <remarks>The values returned in each variable are as follows: <b><c>-1</c></b> if not set, <b><c>0</c></b> if closed, <b><c>1</c></b> if open.</remarks>
/// <returns>The vehicle's windows state is stored in the specified variables.</returns>
native GetVehicleParamsCarWindows(vehicleid, &driver, &passenger, &backleft, &backright);

/// <summary>Sets a vehicle back to the position at where it was created.</summary>
/// <param name="vehicleid">The ID of the vehicle to respawn</param>
/// <seealso name="CreateVehicle"/>
/// <seealso name="DestroyVehicle"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle does not exist.
/// </returns>
native SetVehicleToRespawn(vehicleid);

/// <summary>Links a vehicle to an interior. Vehicles can only be seen by players in the same interior (<a href="#SetPlayerInterior">SetPlayerInterior</a>).</summary>
/// <param name="vehicleid">The ID of the vehicle to link to an interior</param>
/// <param name="interiorid">The <a href="http://wiki.sa-mp.com/wiki/InteriorIDs">Interior ID</a> to link it to</param>
/// <seealso name="SetVehicleVirtualWorld"/>
/// <seealso name="SetPlayerInterior"/>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle does not exist.<p/>
/// </returns>
native LinkVehicleToInterior(vehicleid, interiorid);

/// <summary>Adds a 'component' (often referred to as a 'mod' (modification)) to a vehicle. Valid components can be found <a href="http://wiki.sa-mp.com/wiki/Car_Component_ID">here</a>.</summary>
/// <param name="vehicleid">The ID of the vehicle to add the component to. Not to be confused with <a href="http://wiki.sa-mp.com/wiki/Confuse_modelid">modelid</a></param>
/// <param name="componentid">The <a href="http://wiki.sa-mp.com/wiki/Car_Component_ID">ID of the component</a> to add to the vehicle</param>
/// <returns>
///   <ul>
///     <li><b><c>0</c></b> - The component was not added because the vehicle does not exist.</li>
///     <li><b><c>1</c></b> - The component was successfully added to the vehicle.</li>
///   </ul>
/// </returns>
/// <remarks>Using an invalid <a href="http://wiki.sa-mp.com/wiki/Car_Component_ID">component ID</a> crashes the player's game. There are no internal checks for this.</remarks>
/// <seealso name="RemoveVehicleComponent"/>
/// <seealso name="GetVehicleComponentInSlot"/>
/// <seealso name="GetVehicleComponentType"/>
/// <seealso name="OnVehicleMod"/>
/// <seealso name="OnEnterExitModShop"/>
native AddVehicleComponent(vehicleid, componentid);

/// <summary>Remove a component from a vehicle.</summary>
/// <param name="vehicleid">ID of the vehicle</param>
/// <param name="componentid">ID of the <a href="http://wiki.sa-mp.com/wiki/Car_Component_ID">component</a> to remove</param>
/// <seealso name="AddVehicleComponent"/>
/// <seealso name="GetVehicleComponentInSlot"/>
/// <seealso name="GetVehicleComponentType"/>
/// <seealso name="OnVehicleMod"/>
/// <seealso name="OnEnterExitModShop"/>
native RemoveVehicleComponent(vehicleid, componentid);

/// <summary>Change a vehicle's primary and secondary colors.</summary>
/// <param name="vehicleid">The ID of the vehicle to change the colors of</param>
/// <param name="color1">The new vehicle's primary <a href="http://wiki.sa-mp.com/wiki/Color_ID">Color ID</a></param>
/// <param name="color2">The new vehicle's secondary <a href="http://wiki.sa-mp.com/wiki/Color_ID">Color ID</a></param>
/// <seealso name="ChangeVehiclePaintjob"/>
/// <seealso name="OnVehicleRespray"/>
/// <remarks>Some vehicles have only a primary color and some can not have the color changed at all. A few (cement, squallo) have 4 colors, of which 2 can not be changed in SA:MP</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully. The vehicle's color was successfully changed.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle does not exist.
/// </returns>
native ChangeVehicleColor(vehicleid, color1, color2);

/// <summary>Change a vehicle's paintjob (for plain colors see <a href="#ChangeVehicleColor">ChangeVehicleColor</a>).</summary>
/// <param name="vehicleid">The ID of the vehicle to change the paintjob of</param>
/// <param name="paintjobid">The ID of the Paintjob to apply. Use <b><c>3</c></b> to remove a paintjob</param>
/// <seealso name="ChangeVehicleColor"/>
/// <seealso name="OnVehiclePaintjob"/>
/// <remarks>
///   <b>Known Bugs:</b><p/>
///   This function calls <a href="#OnVehicleRespray">OnVehicleRespray</a>.<p/>
///   Vehicles change their color to white anymore when a paintjob is removed.
/// </remarks>
/// <returns>This function always returns <b><c>1</c></b> (success), even if the vehicle passed is not created.</returns>
native ChangeVehiclePaintjob(vehicleid, paintjobid);


/// <summary>Set a vehicle's health. When a vehicle's health decreases the engine will produce smoke, and finally fire when it decreases to less than 250 (25%).</summary>
/// <param name="vehicleid">The ID of the vehicle to set the health of</param>
/// <param name="health">The health, given as a float value</param>
/// <seealso name="GetVehicleHealth"/>
/// <seealso name="RepairVehicle"/>
/// <seealso name="SetPlayerHealth"/>
/// <seealso name="OnVehicleDeath"/>
/// <remarks>Full vehicle health is <b><c>1000</c></b>, however higher values are possible and increase the health of the vehicle.</remarks>
/// <remarks>
///   <b>Health:</b><p/>
///   <ul>
///     <li>&gt; 650 - undamaged</li>
///     <li>650-550 - white Smoke</li>
///     <li>550-390 - grey Smoke</li>
///     <li>390-250 - black Smoke</li>
///     <li>&lt; 250 - on fire (will explode seconds later)</li>
///   </ul>
/// </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle does not exist.
/// </returns>
native SetVehicleHealth(vehicleid, Float:health);

/// <summary>Get the health of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the health of</param>
/// <param name="health">A float variable in which to store the vehicle's health, passed by reference</param>
/// <seealso name="SetVehicleHealth"/>
/// <seealso name="GetPlayerHealth"/>
/// <seealso name="GetPlayerArmour"/>
/// <remarks>Full vehicle health is <b><c>1000</c></b>, however higher values are possible and increase the health of the vehicle.</remarks>
/// <remarks>
///   <b>Health:</b><p/>
///   <ul>
///     <li>&gt; 650 - undamaged</li>
///     <li>650-550 - white Smoke</li>
///     <li>550-390 - grey Smoke</li>
///     <li>390-250 - black Smoke</li>
///     <li>&lt; 250 - on fire (will explode seconds later)</li>
///   </ul>
/// </remarks>
/// <returns>
///   <b><c>1</c></b> - success.<p/>
///   <b><c>0</c></b> - failure (invalid vehicle ID).<p/>
/// </returns>
native GetVehicleHealth(vehicleid, &Float:health);

/// <summary>Attach a vehicle to another vehicle as a trailer.</summary>
/// <param name="trailerid">The ID of the vehicle that will be pulled</param>
/// <param name="vehicleid">The ID of the vehicle that will pull the trailer</param>
/// <seealso name="DetachTrailerFromVehicle"/>
/// <seealso name="IsTrailerAttachedToVehicle"/>
/// <seealso name="GetVehicleTrailer"/>
/// <remarks>This will only work if both vehicles are streamed in for a player (check <a href="#IsVehicleStreamedIn">IsVehicleStreamedIn</a>).</remarks>
/// <returns>This function always returns <b><c>1</c></b>, even if neither of the vehicle IDs passed are valid.</returns>
native AttachTrailerToVehicle(trailerid, vehicleid);

/// <summary>Detach the connection between a vehicle and its trailer, if any.</summary>
/// <param name="vehicleid">ID of the pulling vehicle</param>
/// <seealso name="AttachTrailerToVehicle"/>
/// <seealso name="IsTrailerAttachedToVehicle"/>
/// <seealso name="GetVehicleTrailer"/>
native DetachTrailerFromVehicle(vehicleid);

/// <summary>Checks if a vehicle has a trailer attached to it. Use <a href="#GetVehicleTrailer">GetVehicleTrailer</a> to get the vehicle ID of the trailer (if any).</summary>
/// <param name="vehicleid">The ID of the vehicle to check for trailers</param>
/// <seealso name="GetVehicleTrailer"/>
/// <seealso name="AttachTrailerToVehicle"/>
/// <seealso name="DetachTrailerFromVehicle"/>
/// <returns><b><c>1</c></b> if the vehicle has a trailer attached, <b><c>0</c></b> if not.</returns>
native IsTrailerAttachedToVehicle(vehicleid);

/// <summary>Get the ID of the trailer attached to a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the trailer of</param>
/// <seealso name="AttachTrailerToVehicle"/>
/// <seealso name="DetachTrailerFromVehicle"/>
/// <seealso name="IsTrailerAttachedToVehicle"/>
/// <returns>The vehicle ID of the trailer or <b><c>0</c></b> if no trailer is attached.</returns>
native GetVehicleTrailer(vehicleid);

/// <summary>Set a vehicle numberplate.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the number plate of</param>
/// <param name="numberplate">The text that should be displayed on the number plate</param>
/// <seealso name="SetVehicleToRespawn"/>
/// <seealso name="ChangeVehicleColor"/>
/// <seealso name="ChangeVehiclePaintjob"/>
/// <remarks>This function was added in <b>SA-MP 0.3c</b> and will not work in earlier versions!</remarks>
/// <remarks>You can use color embedding on the number plate text.</remarks>
/// <remarks>
///   This function has no internal error checking. Do not assign custom number plates to vehicles without plates (boats, planes, etc) as this will result in some unneeded processing time on the client.<p/>
///   The vehicle must be re-spawned or re-streamed for the changes to take effect.<p/>
///   There's a limit of 32 characters on each number plate (including embedded colors).<p/>
///   The text length that can be seen on the number plate is around 9 to 10 characters, more characters will cause the text to split.<p/>
///   Some vehicle models has a backward number plate, e.g. Boxville (498) (as an alternative to this vehicle you can use vehicle model ID 609, which is a duplicated Boxville (aka Boxburg), but with a regular number plate).<p/>
///   This function only works in versions <b>0.2.1</b>, <b>0.2.2</b>, <b>0.2x</b> and <b>0.3c</b> (and beyond). 
/// </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle does not exist.<p/>
/// </returns>
native SetVehicleNumberPlate(vehicleid, const numberplate[]);

/// <summary>Gets the <a href="http://wiki.sa-mp.com/wiki/Vehicle_Models">model ID</a> of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the model of</param>
/// <seealso name="GetPlayerVehicleID"/>
/// <seealso name="GetVehiclePos"/>
/// <seealso name="GetVehicleZAngle"/>
/// <seealso name="GetPlayerVehicleSeat"/>
/// <returns>The vehicle's <a href="http://wiki.sa-mp.com/wiki/Vehicle_Models">model ID</a>, or <b><c>0</c></b> if the vehicle doesn't exist.</returns>
native GetVehicleModel(vehicleid);

/// <summary>Retrieves the installed component ID (modshop mod(ification)) on a vehicle in a specific slot.</summary>
/// <param name="vehicleid">The ID of the vehicle to check for the component</param>
/// <param name="slot">The component slot to check for components (see below)</param>
/// <seealso name="AddVehicleComponent"/>
/// <seealso name="GetVehicleComponentType"/>
/// <seealso name="OnVehicleMod"/>
/// <seealso name="OnEnterExitModShop"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <b>Slots:</b><p/>
///   <c>
///     CARMODTYPE_SPOILER
///     CARMODTYPE_HOOD
///     CARMODTYPE_ROOF
///     CARMODTYPE_SIDESKIRT
///     CARMODTYPE_LAMPS
///     CARMODTYPE_NITRO
///     CARMODTYPE_EXHAUST
///     CARMODTYPE_WHEELS
///     CARMODTYPE_STEREO
///     CARMODTYPE_HYDRAULICS
///     CARMODTYPE_FRONT_BUMPER
///     CARMODTYPE_REAR_BUMPER
///     CARMODTYPE_VENT_RIGHT
///     CARMODTYPE_VENT_LEFT
///   </c>
/// </remarks>
/// <remarks>
///   <b>Known Bugs:</b><p/>
///   <ul>
///     <li>Doesn't work for <b><c>CARMODTYPE_STEREO</c></b>.</li>
///     <li>Both front bull bars and front bumper components are saved in the <b><c>CARMODTYPE_FRONT_BUMPER</c></b> slot. If a vehicle has both of them installed, this function will only return the one which was installed last.</li>
///     <li>Both rear bull bars and rear bumper components are saved in the <b><c>CARMODTYPE_REAR_BUMPER</c></b> slot. If a vehicle has both of them installed, this function will only return the one which was installed last.</li>
///     <li>Both left side skirt and right side skirt are saved in the <b><c>CARMODTYPE_SIDESKIRT</c></b> slot. If a vehicle has both of them installed, this function will only return the one which was installed last. </li>
///   </ul>
/// </remarks>
/// <returns>The ID of the component installed in the specified slot. Returns <b><c>0</c></b> if no component in specified vehicle's specified slot, or if vehicle doesn't exist.</returns>
native GetVehicleComponentInSlot(vehicleid, slot); // There is 1 slot for each CARMODTYPE_*

/// <summary>Find out what type of component a certain ID is.</summary>
/// <param name="component">The component ID to check</param>
/// <seealso name="AddVehicleComponent"/>
/// <seealso name="RemoveVehicleComponent"/>
/// <seealso name="GetVehicleComponentInSlot"/>
/// <seealso name="OnVehicleMod"/>
/// <seealso name="OnEnterExitModShop"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <returns>The component slot ID of the specified component or <b><c>-1</c></b> if the component is invalid.</returns>
native GetVehicleComponentType(component); // Find CARMODTYPE_* for component id

/// <summary>Fully repairs a vehicle, including visual damage (bumps, dents, scratches, popped tires etc.).</summary>
/// <param name="vehicleid">The ID of the vehicle to repair</param>
/// <seealso name="SetVehicleHealth"/>
/// <seealso name="GetVehicleHealth"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle specified does not exist.
/// </returns>
native RepairVehicle(vehicleid); // Repairs the damage model and resets the health

/// <summary>Get the velocity of a vehicle on the X, Y and Z axes.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the velocity of</param>
/// <param name="X">A float variable in to which to store the vehicle's X velocity, passed by reference</param>
/// <param name="Y">A float variable in to which to store the vehicle's Y velocity, passed by reference</param>
/// <param name="Z">A float variable in to which to store the vehicle's Z velocity, passed by reference</param>
/// <seealso name="GetPlayerVelocity"/>
/// <seealso name="SetVehicleVelocity"/>
/// <seealso name="SetPlayerVelocity"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>Multiply vector with <b><c>250.66667</c></b> for kmph or <b><c>199.416667</c></b> for mph or something...</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle specified does not exist.<p/>
/// </returns>
native GetVehicleVelocity(vehicleid, &Float:X, &Float:Y, &Float:Z);

/// <summary>Sets the X, Y and Z velocity of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the velocity of</param>
/// <param name="X">The velocity in the X direction</param>
/// <param name="Y">The velocity in the Y direction </param>
/// <param name="Z">The velocity in the Z direction</param>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>This function has no affect on un-occupied vehicles and does not affect trains.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle does not exist.
/// </returns>
native SetVehicleVelocity(vehicleid, Float:X, Float:Y, Float:Z);

/// <summary>Sets the angular X, Y and Z velocity of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the velocity of</param>
/// <param name="X">The amount of velocity in the angular X direction</param>
/// <param name="Y">The amount of velocity in the angular Y direction </param>
/// <param name="Z">The amount of velocity in the angular Z direction</param>
/// <seealso name="SetVehicleVelocity"/>
/// <seealso name="GetVehicleVelocity"/>
/// <remarks>This function was added in <b>SA-MP 0.3b</b> and will not work in earlier versions!</remarks>
/// <remarks>This function has no effect on un-occupied vehicles and does not effect trains.</remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. The vehicle does not exist.
/// </returns>
native SetVehicleAngularVelocity(vehicleid, Float:X, Float:Y, Float:Z);

/// <summary>Retrieve the damage statuses of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the damage statuses of</param>
/// <param name="panels">A variable to store the panel damage data in, passed by reference</param>
/// <param name="doors">A variable to store the door damage data in, passed by reference</param>
/// <param name="lights">A variable to store the light damage data in, passed by reference</param>
/// <param name="tires">A variable to store the tire damage data in, passed by reference</param>
/// <seealso name="UpdateVehicleDamageStatus"/>
/// <seealso name="SetVehicleHealth"/>
/// <seealso name="GetVehicleHealth"/>
/// <seealso name="RepairVehicle"/>
/// <seealso name="OnVehicleDamageStatusUpdate"/>
/// <remarks>This Callback was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <b>Door states:</b><p/>
///   <ul>
///     <li><b><c>0x000000FF</c></b> - hood</li>
///     <li><b><c>0x0000FF00</c></b> - trunk</li>
///     <li><b><c>0x00FF0000</c></b> - drivers door</li>
///     <li><b><c>0xFF000000</c></b> - co-drivers door</li>
///     <li>byte meaning:</li>
///     <li><b><c>0x1</c></b> - is opened</li>
///     <li><b><c>0x2</c></b> - is damaged</li>
///     <li><b><c>0x4</c></b> - is removed</li>
///     <li>other bytes are unused</li>
///   </ul>
/// </remarks>
/// <remarks>
///   <b>Light states:</b><p/>
///   <ul>
///     <li><b><c>0x01</c></b> - front left broken</li>
///     <li><b><c>0x04</c></b> - front right broken</li>
///     <li><b><c>0x40</c></b> - back both broken</li>
///   </ul>
/// </remarks>
/// <remarks>
///   <b>Tire states:</b><p/>
///   <ul>
///     <li><b><c>0x1</c></b> - back right popped</li>
///     <li><b><c>0x2</c></b> - front right popped</li>
///     <li><b><c>0x4</c></b> - back left popped</li>
///     <li><b><c>0x8</c></b> - front left popped</li>
///     <li>only check the right states for bikes</li>
///   </ul>
/// </remarks>
/// <returns>
///   <b><c>1</c></b>: The function executed successfully.<p/>
///   <b><c>0</c></b>: The function failed to execute. This means the vehicle specified does not exist.
/// </returns>
native GetVehicleDamageStatus(vehicleid, &panels, &doors, &lights, &tires);

/// <summary>Sets the various visual damage statuses of a vehicle, such as popped tires, broken lights and damaged panels.</summary>
/// <param name="vehicleid">The ID of the vehicle to set the damage of</param>
/// <param name="panels">A set of bits containing the panel damage status</param>
/// <param name="doors">A set of bits containing the door damage status</param>
/// <param name="lights">A set of bits containing the light damage status</param>
/// <param name="tires">A set of bits containing the tire damage status</param>
/// <seealso name="SetVehicleHealth"/>
/// <seealso name="GetVehicleHealth"/>
/// <seealso name="RepairVehicle"/>
/// <seealso name="GetVehicleDamageStatus"/>
/// <seealso name="OnVehicleDamageStatusUpdate"/>
/// <remarks>This function was added in <b>SA-MP 0.3a</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <b>Door states:</b><p/>
///   <ul>
///     <li><b><c>0x000000FF</c></b> - hood</li>
///     <li><b><c>0x0000FF00</c></b> - trunk</li>
///     <li><b><c>0x00FF0000</c></b> - drivers door</li>
///     <li><b><c>0xFF000000</c></b> - co-drivers door</li>
///     <li>byte meaning:</li>
///     <li><b><c>0x1</c></b> - is opened</li>
///     <li><b><c>0x2</c></b> - is damaged</li>
///     <li><b><c>0x4</c></b> - is removed</li>
///     <li>other bytes are unused</li>
///   </ul>
/// </remarks>
/// <remarks>
///   <b>Light states:</b><p/>
///   <ul>
///     <li><b><c>0x01</c></b> - front left broken</li>
///     <li><b><c>0x04</c></b> - front right broken</li>
///     <li><b><c>0x40</c></b> - back both broken</li>
///   </ul>
/// </remarks>
/// <remarks>
///   <b>Tire states:</b><p/>
///   <ul>
///     <li><b><c>0x1</c></b> - back right popped</li>
///     <li><b><c>0x2</c></b> - front right popped</li>
///     <li><b><c>0x4</c></b> - back left popped</li>
///     <li><b><c>0x8</c></b> - front left popped</li>
///     <li>only check the right states for bikes</li>
///   </ul>
/// </remarks>
native UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);

/// <summary>Retrieve information about a specific vehicle model such as the size or position of seats.</summary>
/// <param name="vehiclemodel">The vehicle <a href="http://wiki.sa-mp.com/wiki/Vehicles:All">model</a> to get info of</param>
/// <param name="infotype">The type of information to retrieve</param>
/// <param name="X">A float to store the X value</param>
/// <param name="Y">A float to store the Y value</param>
/// <param name="Z">A float to store the Z value</param>
/// <seealso name="GetVehicleModel"/>
/// <remarks>This function was added in <b>SA-MP 0.3e</b> and will not work in earlier versions!</remarks>
/// <remarks>
///   <b>Information types:</b><p/>
///   <ul>
///     <li><b><c>VEHICLE_MODEL_INFO_SIZE</c></b> - vehicle size</li>
///     <li><b><c>VEHICLE_MODEL_INFO_FRONTSEAT</c></b> - position of the front seat</li>
///     <li><b><c>VEHICLE_MODEL_INFO_REARSEAT</c></b> - position of the rear seat</li>
///     <li><b><c>VEHICLE_MODEL_INFO_PETROLCAP</c></b> - position of the fuel cap</li>
///     <li><b><c>VEHICLE_MODEL_INFO_WHEELSFRONT</c></b> - position of the front wheels</li>
///     <li><b><c>VEHICLE_MODEL_INFO_WHEELSREAR</c></b> - position of the rear wheels</li>
///     <li><b><c>VEHICLE_MODEL_INFO_WHEELSMID</c></b> - position of the middle wheels (applies to vehicles with 3 axes)</li>
///     <li><b><c>VEHICLE_MODEL_INFO_FRONT_BUMPER_Z</c></b> - height of the front bumper</li>
///     <li><b><c>VEHICLE_MODEL_INFO_REAR_BUMPER_Z </c></b> - height of the rear bumper</li>
///   </ul>
/// </remarks>
native GetVehicleModelInfo(vehiclemodel, infotype, &Float:X, &Float:Y, &Float:Z);

// Virtual Worlds

/// <summary>Sets the 'virtual world' of a vehicle. Players will only be able to see vehicles in their own virtual world.</summary>
/// <param name="vehicleid">The ID of vehicle to set the virtual world of</param>
/// <param name="worldid">The ID of the virtual world to put the vehicle in</param>
/// <seealso name="GetVehicleVirtualWorld"/>
/// <seealso name="SetPlayerVirtualWorld"/>
native SetVehicleVirtualWorld(vehicleid, worldid);

/// <summary>Get the virtual world of a vehicle.</summary>
/// <param name="vehicleid">The ID of the vehicle to get the virtual world of</param>
/// <seealso name="SetVehicleVirtualWorld"/>
/// <seealso name="GetPlayerVirtualWorld"/>
/// <returns>The virtual world that the vehicle is in.</returns>
native GetVehicleVirtualWorld(vehicleid);

/// <summary>Check if a vehicle ID is valid.</summary>
/// <param name="vehicleid">The ID of the vehicle to check</param>
/// <seealso name="CreateVehicle"/>
/// <seealso name="DestroyVehicle"/>
/// <returns>true or false.</returns>
native bool:IsValidVehicle(vehicleid);

