/***
 *     .d88888b.           888    888 d8b                   
 *    d88P" "Y88b          888    888 Y8P                   
 *    888     888          888    888                       
 *    888     888 888  888 888888 888 888 88888b.   .d88b.  
 *    888     888 888  888 888    888 888 888 "88b d8P  Y8b 
 *    888     888 888  888 888    888 888 888  888 88888888 
 *    Y88b. .d88P Y88b 888 Y88b.  888 888 888  888 Y8b.     
 *     "Y88888P"   "Y88888  "Y888 888 888 888  888  "Y8888  
 *
 */

#include    <YSI_Coding\y_hooks>

Outline(playerid)
{
    if(timer_outline != -1) KillTimer(timer_outline), timer_outline = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);

    Textler_TMP = Textler[gIndex];

    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);

    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }

    timer_outline = SetTimerEx("Timer_Outline", 30, true, "d", playerid);
    return 1;
}

Outline_Manuel(playerid)
{
    Dialog_Show(playerid, MANUEL_OUTLINE, DIALOG_STYLE_INPUT, Dil_Mesaji[os_baslik], "%s\n%s", Dil_Mesaji[os_buton_1], Dil_Mesaji[os_buton_2]
    ,
        fex(fmt(Dil_Mesaji[os_icerik_1]), Textler[gIndex][text.outline]),
        Dil_Mesaji[os_icerik_2]
    );
    return 1;
}

forward Timer_Outline(playerid);
public Timer_Outline(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_outline != -1)
    {
        tus = false;
        BilgiText_Gizle();
        if(lr < -1) tus = true, Textler[gIndex][text.outline] -= (keys == KEY_SPRINT) ? (5) : (1); // sol
        if(lr > 1)  tus = true, Textler[gIndex][text.outline] += (keys == KEY_SPRINT) ? (5) : (1); // sağ
        if(tus == true)
        {
            BilgiText_Update();
            Textdraw_Render(gIndex, true);
            TextDrawSetString(Bilgi_Text, fex("~g~~h~Outline: ~w~~h~%d", Textler[gIndex][text.outline]));
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_outline != -1)
    {
        KillTimer(timer_outline), timer_outline = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_outline != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(timer_outline), timer_outline = -1;
        DB_Guncelle(gIndex);
        if(Textler_TMP[text.outline] != Textler[gIndex][text.outline])
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

    if(PRESSED(KEY_NO) && timer_outline != -1)
    {
        Outline_Manuel(playerid);
    }
    return 1;
}

Dialog:MANUEL_OUTLINE(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new deger;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[os_hata]), Outline_Manuel(playerid);
        }

        if(sscanf(inputtext, "d", deger)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[os_hata]), Outline_Manuel(playerid);
        }

        Textler[gIndex][text.outline] = deger;

        Textdraw_Render(gIndex, true);

        TextDrawSetString(Bilgi_Text, fex("~g~~h~Outline: ~w~~h~%d", Textler[gIndex][text.outline]));

        DB_Guncelle(gIndex);

        ChatTemizle();

        Mesaj_Bilgi(playerid, Dil_Mesaji[os_bilgi_1]);
    }
    return 1;
}