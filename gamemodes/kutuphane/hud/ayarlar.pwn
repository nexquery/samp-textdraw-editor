
/***
 *           d8888                           888                  
 *          d88888                           888                  
 *         d88P888                           888                  
 *        d88P 888 888  888  8888b.  888d888 888  8888b.  888d888 
 *       d88P  888 888  888     "88b 888P"   888     "88b 888P"   
 *      d88P   888 888  888 .d888888 888     888 .d888888 888     
 *     d8888888888 Y88b 888 888  888 888     888 888  888 888     
 *    d88P     888  "Y88888 "Y888888 888     888 "Y888888 888     
 *                      888                                       
 *                 Y8b d88P                                       
 *                  "Y88P"                                        
 */

#include    <YSI_Coding\y_hooks>

Ayarlar_Menu(playerid)
{
    Dialog_Show(playerid, AYARLAR, DIALOG_STYLE_TABLIST_HEADERS, Dil_Mesaji[ayar_baslik], "\
    %s\t%s\n\
    {A3CB38}%s\t%02d:00\n\
    {A3CB38}%s\t%.1f\n\
    {A3CB38}%s\t%s\n\
    {A3CB38}%s\t%s\n\
    ", Dil_Mesaji[ayar_buton1], Dil_Mesaji[ayar_buton2]
    ,
        Dil_Mesaji[ayar_header_1],
        Dil_Mesaji[ayar_header_2],
        Dil_Mesaji[ayar_icerik_1],
        proje_saat,
        Dil_Mesaji[ayar_icerik_2],
        Text_Hud_Y,
        Dil_Mesaji[ayar_icerik_3],
        Text_Global,
        Dil_Mesaji[ayar_icerik_4],
        Text_Player
    );
    return 1;
}

Dialog:AYARLAR(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        switch(listitem)
        {
            // Saat
            case 0: Saat_Menu(playerid);

            // Hud konumu
            case 1: Ayarlar_Hud_Konumu(playerid);

            // Global
            case 2: Ayarlar_Degisken_Global(playerid);

            // Player
            case 3: Ayarlar_Degisken_Player(playerid);
        }
    }
    return 1;
}


/***
 *     .d8888b.                    888    
 *    d88P  Y88b                   888    
 *    Y88b.                        888    
 *     "Y888b.    8888b.   8888b.  888888 
 *        "Y88b.     "88b     "88b 888    
 *          "888 .d888888 .d888888 888    
 *    Y88b  d88P 888  888 888  888 Y88b.  
 *     "Y8888P"  "Y888888 "Y888888  "Y888 
 *                                        
 */

Saat_Menu(playerid)
{
    new buffer[350];
    for(new i = 0; i <= 23; i++)
    {
        format(buffer, sizeof(buffer), "%s%02d:00\n", buffer, i);
    }
    Dialog_Show(playerid, AYAR_SAAT, DIALOG_STYLE_LIST, Dil_Mesaji[saat_baslik], buffer, Dil_Mesaji[saat_buton1], Dil_Mesaji[saat_buton2]);
    return 1;
}

Dialog:AYAR_SAAT(playerid, response, listitem, inputtext[])
{
    if(!response) return Ayarlar_Menu(playerid);
    if(response)
    {
        proje_saat = listitem;

        SetPlayerTime(playerid, proje_saat, 0);

        db_free_result(db_query(proje_db, fex("UPDATE ayarlar SET saat = %d", proje_saat)));

        ChatTemizle();

        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[saat_bilgi]), proje_saat);

        Ayarlar_Menu(playerid);
    }
    return 1;
}


/***
 *    888    888               888      888    d8P                                                    
 *    888    888               888      888   d8P                                                     
 *    888    888               888      888  d8P                                                      
 *    8888888888 888  888  .d88888      888d88K      .d88b.  88888b.  888  888 88888b.d88b.  888  888 
 *    888    888 888  888 d88" 888      8888888b    d88""88b 888 "88b 888  888 888 "888 "88b 888  888 
 *    888    888 888  888 888  888      888  Y88b   888  888 888  888 888  888 888  888  888 888  888 
 *    888    888 Y88b 888 Y88b 888      888   Y88b  Y88..88P 888  888 Y88b 888 888  888  888 Y88b 888 
 *    888    888  "Y88888  "Y88888      888    Y88b  "Y88P"  888  888  "Y88888 888  888  888  "Y88888 
 *                                                                                                    
 */

Ayarlar_Hud_Konumu(playerid)
{
    Hud_Oncelik_Textdraw();

    hud_tasima_modu = true;

    if(hud_tasima_timer != -1) KillTimer(hud_tasima_timer);

    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }

    hud_tasima_timer = SetTimerEx("Hud_Tasiniyor", 20, true, "d", playerid);

    ChatTemizle();

    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);
    return 1;
}

forward Hud_Tasiniyor(playerid);
public Hud_Tasiniyor(playerid)
{
    new keys, updown, leftright;
    GetPlayerKeys(playerid, keys, updown, leftright);

    if(hud_tasima_modu == true && hud_tasima_timer != -1)
    {
        // Bilgi Text gizle
        BilgiText_Gizle();

        // Yukarı ok
        if(updown < -1)
        {
            BilgiText_Update();

            Text_Hud_Y -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
            
            if(Text_Hud_Y <= 0.0) Text_Hud_Y = 0.0;

            TextDrawSetString(Bilgi_Text, fex("~g~~h~Offset: ~w~~h~%.1f", Text_Hud_Y));

            Hud_Render(true), Hud_Goster(true);
        }
        
        // Aşağı ok
        else if(updown > 1)
        {
            BilgiText_Update();

            Text_Hud_Y += (keys == KEY_SPRINT) ? (10.0) : (1.0);

            if(Text_Hud_Y >= 413.0) Text_Hud_Y = 413.0;

            TextDrawSetString(Bilgi_Text, fex("~g~~h~Offset: ~w~~h~%.1f", Text_Hud_Y));

            Hud_Render(true), Hud_Goster(true);
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(hud_tasima_modu == true && hud_tasima_timer != -1)
    {
        hud_tasima_modu = false;

        KillTimer(hud_tasima_timer);

        hud_tasima_timer = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && hud_tasima_modu == true && hud_tasima_timer != -1)
    {
        Bilgi_Text_Kaldir();

        hud_tasima_modu = false;

        KillTimer(hud_tasima_timer);

        hud_tasima_timer = -1;

        db_free_result(db_query(proje_db, fex("UPDATE ayarlar SET hud = %.1f", Text_Hud_Y)));

        ChatTemizle();

        Mesaj_Bilgi(playerid, Dil_Mesaji[hkonum_bilgi]);

        Mouse(playerid, true, TEXTMOD_NORMAL);

        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 1);
        }
    }
    return 1;
}


/***
 *    8888888b.                    d8b          888                        888                                    .d8888b.  888          888               888 
 *    888  "Y88b                   Y8P          888                        888                                   d88P  Y88b 888          888               888 
 *    888    888                                888                        888                                   888    888 888          888               888 
 *    888    888  .d88b.   .d88b.  888 .d8888b  888  888  .d88b.  88888b.  888  .d88b.  888d888                  888        888  .d88b.  88888b.   8888b.  888 
 *    888    888 d8P  Y8b d88P"88b 888 88K      888 .88P d8P  Y8b 888 "88b 888 d8P  Y8b 888P"                    888  88888 888 d88""88b 888 "88b     "88b 888 
 *    888    888 88888888 888  888 888 "Y8888b. 888888K  88888888 888  888 888 88888888 888          888888      888    888 888 888  888 888  888 .d888888 888 
 *    888  .d88P Y8b.     Y88b 888 888      X88 888 "88b Y8b.     888  888 888 Y8b.     888                      Y88b  d88P 888 Y88..88P 888 d88P 888  888 888 
 *    8888888P"   "Y8888   "Y88888 888  88888P' 888  888  "Y8888  888  888 888  "Y8888  888                       "Y8888P88 888  "Y88P"  88888P"  "Y888888 888 
 *                             888                                                                                                                             
 *                        Y8b d88P                                                                                                                             
 *                         "Y88P"                                                                                                                              
 */

Ayarlar_Degisken_Global(playerid)
{
    Dialog_Show(playerid, AYARLAR_DGLOBAL, DIALOG_STYLE_INPUT, Dil_Mesaji[dg_baslik], "%s\n%s", Dil_Mesaji[dg_buton1], Dil_Mesaji[dg_buton2]
    ,
        Dil_Mesaji[dg_icerik_1],
        Dil_Mesaji[dg_icerik_2]
    );
    return 1;
}

Dialog:AYARLAR_DGLOBAL(playerid, response, listitem, inputtext[])
{
    if(!response) return Ayarlar_Menu(playerid);
    if(response)
    {
        if(strlen(inputtext) > MAX_GPLAYER_ISIM) {
            ChatTemizle();
            return Mesaj_Hata(playerid, Dil_Mesaji[dg_hata]), Ayarlar_Degisken_Global(playerid);
        }

        if(isnull(inputtext))  format(Text_Global, MAX_GPLAYER_ISIM, "Text_Global");
        if(!isnull(inputtext)) format(Text_Global, MAX_GPLAYER_ISIM, inputtext);

        db_free_result(db_query(proje_db, fex("UPDATE ayarlar SET global = '%q'", Text_Global)));

        ChatTemizle();

        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[dg_bilgi]), Text_Global);

        Ayarlar_Menu(playerid);
    }
    return 1;
}


/***
 *    8888888b.                    d8b          888                        888                                   8888888b.  888                                    
 *    888  "Y88b                   Y8P          888                        888                                   888   Y88b 888                                    
 *    888    888                                888                        888                                   888    888 888                                    
 *    888    888  .d88b.   .d88b.  888 .d8888b  888  888  .d88b.  88888b.  888  .d88b.  888d888                  888   d88P 888  8888b.  888  888  .d88b.  888d888 
 *    888    888 d8P  Y8b d88P"88b 888 88K      888 .88P d8P  Y8b 888 "88b 888 d8P  Y8b 888P"                    8888888P"  888     "88b 888  888 d8P  Y8b 888P"   
 *    888    888 88888888 888  888 888 "Y8888b. 888888K  88888888 888  888 888 88888888 888          888888      888        888 .d888888 888  888 88888888 888     
 *    888  .d88P Y8b.     Y88b 888 888      X88 888 "88b Y8b.     888  888 888 Y8b.     888                      888        888 888  888 Y88b 888 Y8b.     888     
 *    8888888P"   "Y8888   "Y88888 888  88888P' 888  888  "Y8888  888  888 888  "Y8888  888                      888        888 "Y888888  "Y88888  "Y8888  888     
 *                             888                                                                                                            888                  
 *                        Y8b d88P                                                                                                       Y8b d88P                  
 *                         "Y88P"                                                                                                         "Y88P"                   
 */

Ayarlar_Degisken_Player(playerid)
{
    Dialog_Show(playerid, AYARLAR_DPLAYER, DIALOG_STYLE_INPUT, Dil_Mesaji[dg_baslik], "%s\n%s", Dil_Mesaji[dg_buton1], Dil_Mesaji[dg_buton2]
    ,
        Dil_Mesaji[dg_icerik_1],
        Dil_Mesaji[dg_icerik_2]
    );
    return 1;
}

Dialog:AYARLAR_DPLAYER(playerid, response, listitem, inputtext[])
{
    if(!response) return Ayarlar_Menu(playerid);
    if(response)
    {
        if(strlen(inputtext) > MAX_GPLAYER_ISIM) {
            ChatTemizle();
            return Mesaj_Hata(playerid, Dil_Mesaji[dg_hata]), Ayarlar_Degisken_Player(playerid);
        }

        if(isnull(inputtext))  format(Text_Player, MAX_GPLAYER_ISIM, "Text_Player");
        if(!isnull(inputtext)) format(Text_Player, MAX_GPLAYER_ISIM, inputtext);

        db_free_result(db_query(proje_db, fex("UPDATE ayarlar SET player = '%q'", Text_Player)));

        ChatTemizle();

        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[dg_bilgi]), Text_Player);

        Ayarlar_Menu(playerid);
    }
    return 1;
}