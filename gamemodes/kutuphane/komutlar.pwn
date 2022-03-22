
/***
 *    888    d8P                                  888    888                  
 *    888   d8P                                   888    888                  
 *    888  d8P                                    888    888                  
 *    888d88K      .d88b.  88888b.d88b.  888  888 888888 888  8888b.  888d888 
 *    8888888b    d88""88b 888 "888 "88b 888  888 888    888     "88b 888P"   
 *    888  Y88b   888  888 888  888  888 888  888 888    888 .d888888 888     
 *    888   Y88b  Y88..88P 888  888  888 Y88b 888 Y88b.  888 888  888 888     
 *    888    Y88b  "Y88P"  888  888  888  "Y88888  "Y888 888 "Y888888 888     
 *
 */

new vid = -1;

CMD:mouse(playerid, params[])
{
    if(pMouse == false)
    {
        Mouse(playerid, true, TEXTMOD_NORMAL);
    }
    else
    {
        Mouse(playerid, false, TEXTMOD_YOK);
    }
    return 1;
}


CMD:veh(playerid, params[])
{
    new modelid, Float: Pos[4]; GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]), GetPlayerFacingAngle(playerid, Pos[3]);
    if(sscanf(params, "d", modelid)) return Mesaj_Bilgi(playerid, "/veh <model id>");
    if(modelid < 411 || modelid > 611) return Mesaj_Hata(playerid, "Incorrect model id.");
    if(vid != -1) DestroyVehicle(vid);
    vid = CreateVehicle(modelid, Pos[0], Pos[1], Pos[2], Pos[3], -1, -1, -1);
    PutPlayerInVehicle(playerid, vid, 0);
    return 1;
}