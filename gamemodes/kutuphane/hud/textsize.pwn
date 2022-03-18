/***
 *    88888888888                888             d8b                   
 *        888                    888             Y8P                   
 *        888                    888                                   
 *        888   .d88b.  888  888 888888 .d8888b  888 88888888  .d88b.  
 *        888  d8P  Y8b `Y8bd8P' 888    88K      888    d88P  d8P  Y8b 
 *        888  88888888   X88K   888    "Y8888b. 888   d88P   88888888 
 *        888  Y8b.     .d8""8b. Y88b.       X88 888  d88P    Y8b.     
 *        888   "Y8888  888  888  "Y888  88888P' 888 88888888  "Y8888  
 *
 */


#include    <YSI_Coding\y_hooks>

Textsize(playerid)
{
    if(timer_textsize != -1) KillTimer(timer_textsize), timer_textsize = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);

    Textler_TMP = Textler[gIndex];

    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);

    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }

    timer_textsize = SetTimerEx("Boyut_Textsize", 30, true, "d", playerid);
    return 1;
}

Textsize_Manuel(playerid)
{
    Dialog_Show(playerid, MANUEL_TEXTSIZE, DIALOG_STYLE_INPUT, Dil_Mesaji[btl_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\n\
    %s\n\
    %s\n\n\
    %s\n\
    %s\n\n\
    %s",
    Dil_Mesaji[btl_buton_1], Dil_Mesaji[btl_buton_2]
    ,
        Dil_Mesaji[btl_icrk_1],
        Dil_Mesaji[btl_icrk_2],
        Dil_Mesaji[btl_icrk_3],
        Dil_Mesaji[btl_icrk_4],
        fex(fmt(Dil_Mesaji[btl_icrk_5]), Textler[gIndex][text.textsize][0]),
        fex(fmt(Dil_Mesaji[btl_icrk_6]), Textler[gIndex][text.textsize][1]),
        Dil_Mesaji[btl_icrk_7],
        Dil_Mesaji[btl_icrk_8],
        Dil_Mesaji[btl_icrk_9],
        Dil_Mesaji[btl_icrk_10],
        Dil_Mesaji[btl_icrk_11]
    );
    return 1;
}

forward Boyut_Textsize(playerid);
public Boyut_Textsize(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_textsize != -1)
    {
        tus = false;
        BilgiText_Gizle();
        if(lr < -1) tus = true, Textler[gIndex][text.textsize][0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0); // sol
        if(lr > 1)  tus = true, Textler[gIndex][text.textsize][0] += (keys == KEY_SPRINT) ? (10.0) : (1.0); // sağ
        if(ud < -1) tus = true, Textler[gIndex][text.textsize][1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0); // yukarı
        if(ud > 1)  tus = true, Textler[gIndex][text.textsize][1] += (keys == KEY_SPRINT) ? (10.0) : (1.0); // aşağı
        if(tus == true)
        {
            BilgiText_Update();
            Textdraw_Render(gIndex, true);
            TextDrawSetString(Bilgi_Text, fex("~g~~h~X: ~w~~h~%.2f     ~g~~h~Y: ~w~~h~%.2f", Textler[gIndex][text.textsize][0], Textler[gIndex][text.textsize][1]));
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_textsize != -1)
    {
        KillTimer(timer_textsize), timer_textsize = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_textsize != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(timer_textsize), timer_textsize = -1;
        DB_Guncelle(gIndex);
        if(Textler_TMP[text.textsize][0] != Textler[gIndex][text.textsize][0] || Textler_TMP[text.textsize][1] != Textler[gIndex][text.textsize][1])
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

    if(PRESSED(KEY_NO) && timer_textsize != -1)
    {
        Textsize_Manuel(playerid);
    }
    return 1;
}

Dialog:MANUEL_TEXTSIZE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new Float: x, Float: y;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[btl_hata_1]), Textsize_Manuel(playerid);
        }

        if(sscanf(inputtext, "ff", x, y)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[btl_hata_1]), Textsize_Manuel(playerid);
        }

        if(x != 0.0 && y != 0.0)
        {
            Textler[gIndex][text.textsize][0] = x;
            Textler[gIndex][text.textsize][1] = y;
        }

        if(x != 0.0 && y == 0.0)
        {
            Textler[gIndex][text.textsize][0] = x;
        }

        if(x == 0.0 && y != 0.0)
        {
            Textler[gIndex][text.textsize][1] = y;
        }

        if(x == 0.0 && y == 0.0)
        {
            Textler[gIndex][text.textsize][0] = x;
            Textler[gIndex][text.textsize][1] = y;
        }

        Textdraw_Render(gIndex, true);

        TextDrawSetString(Bilgi_Text, fex("~g~~h~X: ~w~~h~%.2f     ~g~~h~Y: ~w~~h~%.2f", Textler[gIndex][text.textsize][0], Textler[gIndex][text.textsize][1]));

        DB_Guncelle(gIndex);

        ChatTemizle();

        Mesaj_Bilgi(playerid, Dil_Mesaji[btl_bilgi_1]);
    }
    return 1;
}