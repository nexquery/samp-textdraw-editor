
/***
 *     .d8888b.                     .d888         
 *    d88P  Y88b                   d88P"          
 *    Y88b.                        888            
 *     "Y888b.    8888b.  888  888 888888 8888b.  
 *        "Y88b.     "88b 888  888 888       "88b 
 *          "888 .d888888 888  888 888   .d888888 
 *    Y88b  d88P 888  888 Y88b 888 888   888  888 
 *     "Y8888P"  "Y888888  "Y88888 888   "Y888888 
 *                             888                
 *                        Y8b d88P                
 *                         "Y88P"                 
 */

Sayfa_Menu(playerid, mod)
{
    SetPVarInt(playerid, "sayfa_modu", mod);
    Dialog_Show(playerid, SAYFA_DIALOG, DIALOG_STYLE_INPUT, Dil_Mesaji[sayfa_baslik], fmt(Dil_Mesaji[sayfa_icerik]), Dil_Mesaji[sayfa_btn1], Dil_Mesaji[sayfa_btn2]
    ,
        Sayfa_Total(mod)
    );
    return 1;
}

Sayfa_Total(mod)
{
    if(mod == SAYFA_PROJE_LISTESI) return Max_Page(projeler_total, PROJE_MAX_ICERIK);
    if(mod == SAYFA_HUD_LISTE) return Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK);
    if(mod == SAYFA_HUD_LISTE_INDEX) return Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK);
    if(mod == SAYFA_SILINENLER)
    {
        new total, rMax; Sil_Get(total, rMax);
        return Max_Page(total, rMax);
    }
    if(mod == SAYFA_GRUPLAMA) return Max_Page(Iter_Count(Text_List), Grup_MAX_OGE());
    return 1;
}

Dialog:SAYFA_DIALOG(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new sayfa, mod = GetPVarInt(playerid, "sayfa_modu");

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[sayfa_hata]), Sayfa_Menu(playerid, mod);
        }

        if(sscanf(inputtext, "d", sayfa)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[sayfa_hata]), Sayfa_Menu(playerid, mod);
        }

        if(sayfa < 1 || sayfa > Sayfa_Total(mod)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[sayfa_hata]), Sayfa_Menu(playerid, mod);
        }

        if(mod == SAYFA_PROJE_LISTESI)
        {
            projeler_sayfa = sayfa - 1, Projeler_Menu(playerid);
        }

        if(mod == SAYFA_HUD_LISTE)
        {
            liste_Sayfa = sayfa, Liste_Menu(playerid);
        }

        if(mod == SAYFA_HUD_LISTE_INDEX)
        {
            index_degistir_Sayfa = sayfa, Liste_Index_Menu(playerid);
        }

        if(mod == SAYFA_SILINENLER)
        {
            Sil_Set(sayfa - 1), Sil_Menu(playerid);
        }

        if(mod == SAYFA_GRUPLAMA)
        {
            Grup_Set(sayfa), Gruplama_Oge_Sec(playerid);
        }
    }
    else
    {
        new mod = GetPVarInt(playerid, "sayfa_modu");
        if(mod == SAYFA_PROJE_LISTESI) return Projeler_Menu(playerid);
        if(mod == SAYFA_HUD_LISTE) return Liste_Menu(playerid);
        if(mod == SAYFA_HUD_LISTE_INDEX) return Liste_Index_Menu(playerid);
        if(mod == SAYFA_SILINENLER) return Sil_Menu(playerid);
        if(mod == SAYFA_GRUPLAMA) return Gruplama_Oge_Sec(playerid);
    }
    return 1;
}