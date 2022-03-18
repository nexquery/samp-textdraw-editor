
/***
 *    888    888                   888      
 *    888    888                   888      
 *    888    888                   888      
 *    8888888888  .d88b.   .d88b.  888  888 
 *    888    888 d88""88b d88""88b 888 .88P 
 *    888    888 888  888 888  888 888888K  
 *    888    888 Y88..88P Y88..88P 888 "88b 
 *    888    888  "Y88P"   "Y88P"  888  888 
 *                                          
 */

#include    <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    for(new i = 0; i < sizeof(Text_Hud); i++)
    {
        Text_Hud[i][hindex] = Text: -1;
    }

    // Hudu oluşturacak
    Hud_Render();
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text: clickedid)
{  
    // ESC
    if(TextMod == TEXTMOD_NORMAL && clickedid == INVALID_TEXT_DRAW) {
        return Mouse(playerid, true, TEXTMOD_NORMAL);
    }

    // Proje
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[1][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Proje_Menu(playerid);
    }
    
    // Ayarlar
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[2][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Ayarlar_Menu(playerid);
    }

    // Liste
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[3][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), liste_Sayfa = Textdraw_Sayfa_Bul(), Liste_Menu(playerid);
    }

    // Depo
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[4][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Depo_Menu(playerid);
    }

    // Yeni
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[5][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Yeni_Menu(playerid);
    }

    // Kopyala
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[6][hindex]) {
        return Kopyala(playerid);
    }

    // Sil
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[7][hindex]) {
        return Sil(playerid);
    }

    // Konum
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[8][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Konum(playerid);
    }

    // Textsize
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[9][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Textsize(playerid);
    }

    // Lettersize
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[10][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Lettersize(playerid);
    }

    // Metin
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[11][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Metin(playerid);
    }

    // Font
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[12][hindex]) {
        return Font();
    }

    // Hizalama
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[13][hindex]) {
        return Hizalama();
    }

    // Oranti
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[14][hindex]) {
        return Oranti();
    }

    // Outline
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[15][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Outline(playerid);
    }

    // Shadow
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[16][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Shadow(playerid);
    }

    // Renk
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[17][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), SetPVarInt(playerid, "renk_modu", 0), Renk(playerid);
    }

    // BG Rengi
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[18][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), SetPVarInt(playerid, "renk_modu", 1), Renk(playerid);
    }

    // Box Rengi
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[19][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), SetPVarInt(playerid, "renk_modu", 2), Renk(playerid);
    }

    // Box
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[20][hindex]) {
        return Box();
    }

    // Selectable
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[21][hindex]) {
        return Selectable();
    }

    // Preview Models
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[22][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Preview_Models(playerid);
    }

    // Global Player
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[23][hindex]) {
        return Global_Player();
    }

    // Geri - İleri Al
    if(TextMod == TEXTMOD_NORMAL && clickedid == Text_Hud[24][hindex]) {
        return Mouse(playerid, false, TEXTMOD_YOK), Undo_Redo(playerid);
    }
    return 0;
}