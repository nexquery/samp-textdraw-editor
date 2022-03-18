
/***
 *    8888888b.                             
 *    888  "Y88b                            
 *    888    888                            
 *    888    888  .d88b.  88888b.   .d88b.  
 *    888    888 d8P  Y8b 888 "88b d88""88b 
 *    888    888 88888888 888  888 888  888 
 *    888  .d88P Y8b.     888 d88P Y88..88P 
 *    8888888P"   "Y8888  88888P"   "Y88P"  
 *                        888               
 *                        888               
 *                        888               
 */

Depo_Menu(playerid)
{
    Dialog_Show(playerid, DEPO, DIALOG_STYLE_LIST, Dil_Mesaji[depo_baslik], "\
    %s\n%s", Dil_Mesaji[depo_btn_1], Dil_Mesaji[depo_btn_2]
    ,
        Dil_Mesaji[depo_icerik_1],
        Dil_Mesaji[depo_icerik_2]
    );
    return 1;
}

Dialog:DEPO(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        if(listitem == 0)
        {
            Grup_Renk_Reset();
            Grup_Set(1);
            Gruplama_Menu(playerid);
        }
        else
        {
            Sil_Set(0);
            Sil_Menu(playerid);
        }
    }
    return 1;
}