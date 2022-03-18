/***
 *    888              888    888                             d8b                   
 *    888              888    888                             Y8P                   
 *    888              888    888                                                   
 *    888      .d88b.  888888 888888 .d88b.  888d888 .d8888b  888 88888888  .d88b.  
 *    888     d8P  Y8b 888    888   d8P  Y8b 888P"   88K      888    d88P  d8P  Y8b 
 *    888     88888888 888    888   88888888 888     "Y8888b. 888   d88P   88888888 
 *    888     Y8b.     Y88b.  Y88b. Y8b.     888          X88 888  d88P    Y8b.     
 *    88888888 "Y8888   "Y888  "Y888 "Y8888  888      88888P' 888 88888888  "Y8888  
 *                                                                                  
 */

#include    <YSI_Coding\y_hooks>

Lettersize(playerid)
{
    if(timer_lettersize != -1) KillTimer(timer_lettersize), timer_lettersize = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);
    
    Textler_TMP = Textler[gIndex];
    
    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);

    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }

    timer_lettersize = SetTimerEx("Boyut_Lettersize", 30, true, "d", playerid);
    return 1;
}

Lettersize_Manuel(playerid)
{
    Dialog_Show(playerid, MANUEL_LETTERSIZE, DIALOG_STYLE_INPUT, Dil_Mesaji[btl_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\n\
    %s\n\
    %s\n\n\
    %s\n\
    %s",
    Dil_Mesaji[btl_buton_1], Dil_Mesaji[btl_buton_2]
    ,
        Dil_Mesaji[btl_icrk_1],
        Dil_Mesaji[btl_icrk_2],
        Dil_Mesaji[btl_icrk_3],
        Dil_Mesaji[btl_icrk_4],
        fex(fmt(Dil_Mesaji[btl_icrk_5]), Textler[gIndex][text.lettersize][0]),
        fex(fmt(Dil_Mesaji[btl_icrk_6]), Textler[gIndex][text.lettersize][1]),
        Dil_Mesaji[btl_icrk_7],
        Dil_Mesaji[btl_icrk_8],
        Dil_Mesaji[btl_icrk_9],
        Dil_Mesaji[btl_icrk_10]
    );
    return 1;
}

forward Boyut_Lettersize(playerid);
public Boyut_Lettersize(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_lettersize != -1)
    {
        tus = false;
        BilgiText_Gizle();
        if(lr < -1) tus = true, Textler[gIndex][text.lettersize][0] -= (keys == KEY_SPRINT) ? (0.1) : (0.01); // sol
        if(lr > 1)  tus = true, Textler[gIndex][text.lettersize][0] += (keys == KEY_SPRINT) ? (0.1) : (0.01); // sağ
        if(ud < -1) tus = true, Textler[gIndex][text.lettersize][1] -= (keys == KEY_SPRINT) ? (1.0) : (0.1); // yukarı
        if(ud > 1)  tus = true, Textler[gIndex][text.lettersize][1] += (keys == KEY_SPRINT) ? (1.0) : (0.1); // aşağı
        if(tus == true)
        {
            BilgiText_Update();
            Textdraw_Render(gIndex, true);
            TextDrawSetString(Bilgi_Text, fex("~g~~h~X: ~w~~h~%.2f     ~g~~h~Y: ~w~~h~%.2f", Textler[gIndex][text.lettersize][0], Textler[gIndex][text.lettersize][1]));
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_lettersize != -1)
    {
        KillTimer(timer_lettersize), timer_lettersize = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_lettersize != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(timer_lettersize), timer_lettersize = -1;
        DB_Guncelle(gIndex);
        if(Textler_TMP[text.lettersize][0] != Textler[gIndex][text.lettersize][0] || Textler_TMP[text.lettersize][1] != Textler[gIndex][text.lettersize][1])
        {
            new orijinal_data[textdraw_yapilandirmasi];
            
            orijinal_data = Textler[gIndex];

            Textler[gIndex] = Textler_TMP;
            
            gIleri_Ekle(gIndex);
            
            Textler[gIndex] = orijinal_data;
        }
        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
        ChatTemizle();
        Mesaj_Bilgi(playerid, Dil_Mesaji[btl_bilgi_1]);
        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 1);
        }
    }

    if(PRESSED(KEY_NO) && timer_lettersize != -1)
    {
        Lettersize_Manuel(playerid);
    }
    return 1;
}

Dialog:MANUEL_LETTERSIZE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float: x, Float: y;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[btl_hata_1]), Lettersize_Manuel(playerid);
        }

        if(sscanf(inputtext, "ff", x, y)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[btl_hata_1]), Lettersize_Manuel(playerid);
        }

        if(x != 0.0 && y != 0.0)
        {
            Textler[gIndex][text.lettersize][0] = x;
            Textler[gIndex][text.lettersize][1] = y;
        }

        if(x != 0.0 && y == 0.0)
        {
            Textler[gIndex][text.lettersize][0] = x;
        }

        if(x == 0.0 && y != 0.0)
        {
            Textler[gIndex][text.lettersize][1] = y;
        }

        if(x == 0.0 && y == 0.0)
        {
            Textler[gIndex][text.lettersize][0] = x;
            Textler[gIndex][text.lettersize][1] = y;
        }

        Textdraw_Render(gIndex, true);

        TextDrawSetString(Bilgi_Text, fex("~g~~h~X: ~w~~h~%.2f     ~g~~h~Y: ~w~~h~%.2f", Textler[gIndex][text.lettersize][0], Textler[gIndex][text.lettersize][1]));

        DB_Guncelle(gIndex);

        ChatTemizle();

        Mesaj_Bilgi(playerid, Dil_Mesaji[btl_bilgi_1]);
    }
    return 1;
}