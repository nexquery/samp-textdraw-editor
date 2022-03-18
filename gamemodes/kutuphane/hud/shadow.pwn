/***
 *     .d8888b.  888                    888                        
 *    d88P  Y88b 888                    888                        
 *    Y88b.      888                    888                        
 *     "Y888b.   88888b.   8888b.   .d88888  .d88b.  888  888  888 
 *        "Y88b. 888 "88b     "88b d88" 888 d88""88b 888  888  888 
 *          "888 888  888 .d888888 888  888 888  888 888  888  888 
 *    Y88b  d88P 888  888 888  888 Y88b 888 Y88..88P Y88b 888 d88P 
 *     "Y8888P"  888  888 "Y888888  "Y88888  "Y88P"   "Y8888888P"  
 *
 */

#include    <YSI_Coding\y_hooks>

Shadow(playerid)
{
    if(timer_shadow != -1) KillTimer(timer_shadow), timer_shadow = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);

    Textler_TMP = Textler[gIndex];

    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);

    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }

    timer_shadow = SetTimerEx("Timer_Shadow", 30, true, "d", playerid);
    return 1;
}

Shadow_Manuel(playerid)
{
    Dialog_Show(playerid, MANUEL_SHADOW, DIALOG_STYLE_INPUT, Dil_Mesaji[os_baslik], "%s\n%s", Dil_Mesaji[os_buton_1], Dil_Mesaji[os_buton_2]
    ,
        fex(fmt(Dil_Mesaji[os_icerik_1]), Textler[gIndex][text.shadow]),
        Dil_Mesaji[os_icerik_2]
    );
    return 1;
}

forward Timer_Shadow(playerid);
public Timer_Shadow(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_shadow != -1)
    {
        tus = false;
        BilgiText_Gizle();
        if(lr < -1) tus = true, Textler[gIndex][text.shadow] -= (keys == KEY_SPRINT) ? (5) : (1); // sol
        if(lr > 1)  tus = true, Textler[gIndex][text.shadow] += (keys == KEY_SPRINT) ? (5) : (1); // sağ
        if(tus == true)
        {
            BilgiText_Update();
            Textdraw_Render(gIndex, true);
            TextDrawSetString(Bilgi_Text, fex("~g~~h~Shadow: ~w~~h~%d", Textler[gIndex][text.shadow]));
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_shadow != -1)
    {
        KillTimer(timer_shadow), timer_shadow = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_shadow != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(timer_shadow), timer_shadow = -1;
        DB_Guncelle(gIndex);
        if(Textler_TMP[text.shadow] != Textler[gIndex][text.shadow])
        {
            new orijinal_data[textdraw_yapilandirmasi];
            
            orijinal_data = Textler[gIndex];

            Textler[gIndex] = Textler_TMP;
            
            gIleri_Ekle(gIndex);
            
            Textler[gIndex] = orijinal_data;
        }
        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
        ChatTemizle();
        Mesaj_Bilgi(playerid, Dil_Mesaji[os_bilgi_1]);
        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 1);
        }
    }

    if(PRESSED(KEY_NO) && timer_shadow != -1)
    {
        Shadow_Manuel(playerid);
    }
    return 1;
}

Dialog:MANUEL_SHADOW(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new deger;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[os_hata]), Shadow_Manuel(playerid);
        }

        if(sscanf(inputtext, "d", deger)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[os_hata]), Shadow_Manuel(playerid);
        }

        Textler[gIndex][text.shadow] = deger;

        Textdraw_Render(gIndex, true);

        TextDrawSetString(Bilgi_Text, fex("~g~~h~Shadow: ~w~~h~%d", Textler[gIndex][text.shadow]));

        DB_Guncelle(gIndex);

        ChatTemizle();

        Mesaj_Bilgi(playerid, Dil_Mesaji[os_bilgi_1]);
    }
    return 1;
}