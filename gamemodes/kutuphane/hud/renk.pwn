
/***
 *    8888888b.                   888      
 *    888   Y88b                  888      
 *    888    888                  888      
 *    888   d88P .d88b.  88888b.  888  888 
 *    8888888P" d8P  Y8b 888 "88b 888 .88P 
 *    888 T88b  88888888 888  888 888888K  
 *    888  T88b Y8b.     888  888 888 "88b 
 *    888   T88b "Y8888  888  888 888  888 
 *
 */

#include    <YSI_Coding\y_hooks>

new buffer_renk_str[4096];

new const Renk_Paleti[] = 
{
    0x000000FF, 0xFFFFFFFF, 0x800000FF, 0x8B0000FF, 0xA52A2AFF,
    0xB22222FF, 0xDC143CFF, 0xFF0000FF, 0xFF6347FF, 0xFF7F50FF,
    0xCD5C5CFF, 0xF08080FF, 0xE9967AFF, 0xFA8072FF, 0xFFA07AFF,
    0xFF4500FF, 0xFF8C00FF, 0xFFA500FF, 0xFFD700FF, 0xB8860BFF,
    0xDAA520FF, 0xBDB76BFF, 0xF0E68CFF, 0x808000FF, 0xFFFF00FF,
    0x9ACD32FF, 0x556B2FFF, 0x6B8E23FF, 0x7CFC00FF, 0x7FFF00FF,
    0xADFF2FFF, 0x006400FF, 0x008000FF, 0x228B22FF, 0x00FF00FF,
    0x32CD32FF, 0x90EE90FF, 0x98FB98FF, 0x8FBC8FFF, 0x00FA9AFF,
    0x00FF7FFF, 0x2E8B57FF, 0x66CDAAFF, 0x3CB371FF, 0x20B2AAFF,
    0x2F4F4FFF, 0x008080FF, 0x008B8BFF, 0x00FFFFFF, 0x00FFFFFF,
    0x00CED1FF, 0x40E0D0FF, 0x48D1CCFF, 0xAFEEEEFF, 0x7FFFD4FF,
    0xB0E0E6FF, 0x5F9EA0FF, 0x4682B4FF, 0x6495EDFF, 0x00BFFFFF,
    0x1E90FFFF, 0xADD8E6FF, 0x87CEEBFF, 0x87CEFAFF, 0x191970FF,
    0x000080FF, 0x00008BFF, 0x0000CDFF, 0x0000FFFF, 0x4169E1FF,
    0x8A2BE2FF, 0x4B0082FF, 0x483D8BFF, 0x6A5ACDFF, 0x7B68EEFF,
    0x9370DBFF, 0x8B008BFF, 0x9400D3FF, 0x9932CCFF, 0xBA55D3FF,
    0x800080FF, 0xD8BFD8FF, 0xDDA0DDFF, 0xEE82EEFF, 0xFF00FFFF,
    0xDA70D6FF, 0xC71585FF, 0xDB7093FF, 0xFF1493FF, 0xFF69B4FF,
    0xFFB6C1FF, 0xFFC0CBFF, 0x8B4513FF, 0xA0522DFF, 0xD2691EFF,
    0xCD853FFF, 0xF4A460FF, 0xDEB887FF, 0xD2B48CFF, 0xBC8F8FFF,
    0xFFE4B5FF, 0xFFDEADFF, 0xFFDAB9FF, 0xF5FFFAFF, 0x708090FF,
    0x778899FF, 0xB0C4DEFF, 0xE6E6FAFF, 0xF0F8FFFF, 0xF8F8FFFF,
    0xF0FFF0FF, 0x696969FF, 0x808080FF, 0xA9A9A9FF, 0xC0C0C0FF
};

Renk(playerid)
{
    buffer_renk_str[0] = '\0';
    format(buffer_renk_str, sizeof(buffer_renk_str), "%sHex\n",  buffer_renk_str);
    format(buffer_renk_str, sizeof(buffer_renk_str), "%sRGB\n",  buffer_renk_str);
    format(buffer_renk_str, sizeof(buffer_renk_str), "%sRGBA\n", buffer_renk_str);
    format(buffer_renk_str, sizeof(buffer_renk_str), "%s%s\n",   buffer_renk_str, Dil_Mesaji[renk_icerik]);
    format(buffer_renk_str, sizeof(buffer_renk_str), "%s-----------------------\n", buffer_renk_str);
    for(new i = 0; i < sizeof(Renk_Paleti); i++)
    {
        format(buffer_renk_str, sizeof(buffer_renk_str), "%s{%06x}%d - ##########\n", buffer_renk_str, Renk_Paleti[i] >>> 8, i + 1);
    }
    Dialog_Show(playerid, RENK, DIALOG_STYLE_LIST, Dil_Mesaji[renk_baslik], buffer_renk_str, Dil_Mesaji[renk_buton1], Dil_Mesaji[renk_buton2]);
    return 1;
}

Dialog:RENK(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        switch(listitem)
        {
            case 0: Renk_Hex(playerid);
            case 1: Renk_RGB(playerid);
            case 2: Renk_RGBA(playerid);
            case 3: RGBA_Tusla(playerid);
            case 4: Renk(playerid);
            default:
            {
                if(GetPVarInt(playerid, "renk_modu") == 0) {
                    if(Textler[gIndex][text.color] != Renk_Paleti[listitem - 5]) {
                        gIleri_Ekle(gIndex);
                    }
                    Textler[gIndex][text.color] = Renk_Paleti[listitem - 5];
                }

                if(GetPVarInt(playerid, "renk_modu") == 1) {
                    if(Textler[gIndex][text.bgcolor] != Renk_Paleti[listitem - 5]) {
                        gIleri_Ekle(gIndex);
                    }
                    Textler[gIndex][text.bgcolor] = Renk_Paleti[listitem - 5];
                }

                if(GetPVarInt(playerid, "renk_modu") == 2) {
                    if(Textler[gIndex][text.boxcolor] != Renk_Paleti[listitem - 5]) {
                        gIleri_Ekle(gIndex);
                    }
                    Textler[gIndex][text.boxcolor] = Renk_Paleti[listitem - 5];
                }

                DB_Guncelle(gIndex);

                Textdraw_Render(gIndex, true);

                Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
            }
        }
    }
    return 1;
}



/***
 *    888    888                   
 *    888    888                   
 *    888    888                   
 *    8888888888  .d88b.  888  888 
 *    888    888 d8P  Y8b `Y8bd8P' 
 *    888    888 88888888   X88K   
 *    888    888 Y8b.     .d8""8b. 
 *    888    888  "Y8888  888  888 
 *
 */


Renk_Hex(playerid)
{
    Dialog_Show(playerid, RENK_HEX, DIALOG_STYLE_INPUT, Dil_Mesaji[rhex_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s", Dil_Mesaji[rhex_buton_1], Dil_Mesaji[rhex_buton_2]
    ,
        Dil_Mesaji[rhex_icerik_1],
        Dil_Mesaji[rhex_icerik_2],
        Dil_Mesaji[rhex_icerik_3],
        Dil_Mesaji[rhex_icerik_4],
        Dil_Mesaji[rhex_icerik_5],
        Dil_Mesaji[rhex_icerik_6]
    );
    return 1;
}

Dialog:RENK_HEX(playerid, response, listitem, inputtext[])
{
    if(!response) return Renk(playerid);
    if(response)
    {
        new hex, buffer[12], len;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rhex_hata]), Renk_Hex(playerid);
        }

        format(buffer, 12, inputtext);

        len = strlen(buffer);

        for(new i = 0; i < strlen(buffer); i++) {
            buffer[i] = toupper(buffer[i]);
        }

        // FFFFFF
        if(len == 6) {
            strins(buffer, "FF", len);
        }

        // #FFFFFF
        if(len == 7) {
            strins(buffer, "FF", len), strdel(buffer, 0, 1);
        }

        // 0xFFFFFF
        if(len == 8) {
            strins(buffer, "FF", len);
        }

        if(len > 10) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rhex_hata]), Renk_Hex(playerid);
        }

        if(sscanf(buffer, "h", hex)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rhex_hata]), Renk_Hex(playerid);
        }

        if(GetPVarInt(playerid, "renk_modu") == 0) {
            if(Textler[gIndex][text.color] != hex) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.color] = hex;
        }

        if(GetPVarInt(playerid, "renk_modu") == 1) {
            if(Textler[gIndex][text.bgcolor] != hex) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.bgcolor] = hex;
        }
        
        if(GetPVarInt(playerid, "renk_modu") == 2) {
            if(Textler[gIndex][text.boxcolor] != hex) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.boxcolor] = hex;
        }

        DB_Guncelle(gIndex);

        Textdraw_Render(gIndex, true);

        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
    }
    return 1;
}


/***
 *    8888888b.   .d8888b.  888888b.   
 *    888   Y88b d88P  Y88b 888  "88b  
 *    888    888 888    888 888  .88P  
 *    888   d88P 888        8888888K.  
 *    8888888P"  888  88888 888  "Y88b 
 *    888 T88b   888    888 888    888 
 *    888  T88b  Y88b  d88P 888   d88P 
 *    888   T88b  "Y8888P88 8888888P"  
 *
 */

Renk_RGB(playerid)
{
    Dialog_Show(playerid, RENK_RGB, DIALOG_STYLE_INPUT, Dil_Mesaji[rgb_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s", Dil_Mesaji[rgb_buton_1], Dil_Mesaji[rgb_buton_2]
    ,
        Dil_Mesaji[rgb_icerik_1],
        Dil_Mesaji[rgb_icerik_2],
        Dil_Mesaji[rgb_icerik_3],
        Dil_Mesaji[rgb_icerik_4],
        Dil_Mesaji[rgb_icerik_5],
        Dil_Mesaji[rgb_icerik_6]
    );
    return 1;
}

Dialog:RENK_RGB(playerid, response, listitem, inputtext[])
{
    if(!response) return Renk(playerid);
    if(response)
    {
        new r, g, b, pos = -1;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Renk_RGB(playerid);
        }

        pos = strfind(inputtext, "rgb(", true);
        if(pos != -1) strdel(inputtext, pos, pos + 4);

        pos = strfind(inputtext, ")", true, 0);
        if(pos != -1) strdel(inputtext, pos, strlen(inputtext));

        for(new i = 0; i < strlen(inputtext); i++)
        {
            if(inputtext[i] == ',')
            {
                if(inputtext[i + 1] >= '0' && inputtext[i + 1] <= '9')
                {
                    inputtext[i] = ' ';
                }
                else
                {
                    strdel(inputtext, i, i + 1);
                }
            }
        }

        if(sscanf(inputtext, "ddd", r, g, b)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Renk_RGB(playerid);
        }

        if(r < 0 || r > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Renk_RGB(playerid);
        }

        if(g < 0 || g > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Renk_RGB(playerid);
        }

        if(b < 0 || b > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Renk_RGB(playerid);
        }

        if(GetPVarInt(playerid, "renk_modu") == 0) {
            if(Textler[gIndex][text.color] != RGB::HexToRGBA(r, g, b, 255)) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.color] = RGB::HexToRGBA(r, g, b, 255);
        }

        if(GetPVarInt(playerid, "renk_modu") == 1) {
            if(Textler[gIndex][text.bgcolor] != RGB::HexToRGBA(r, g, b, 255)) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.bgcolor] = RGB::HexToRGBA(r, g, b, 255);
        }
        
        if(GetPVarInt(playerid, "renk_modu") == 2) {
            if(Textler[gIndex][text.boxcolor] != RGB::HexToRGBA(r, g, b, 255)) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.boxcolor] = RGB::HexToRGBA(r, g, b, 255);
        }

        DB_Guncelle(gIndex);

        Textdraw_Render(gIndex, true);

        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
    }
    return 1;
}


/***
 *    8888888b.   .d8888b.  888888b.         d8888 
 *    888   Y88b d88P  Y88b 888  "88b       d88888 
 *    888    888 888    888 888  .88P      d88P888 
 *    888   d88P 888        8888888K.     d88P 888 
 *    8888888P"  888  88888 888  "Y88b   d88P  888 
 *    888 T88b   888    888 888    888  d88P   888 
 *    888  T88b  Y88b  d88P 888   d88P d8888888888 
 *    888   T88b  "Y8888P88 8888888P" d88P     888 
 *
 */

Renk_RGBA(playerid)
{
    Dialog_Show(playerid, RENK_RGBA, DIALOG_STYLE_INPUT, Dil_Mesaji[rgba_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s", Dil_Mesaji[rgba_buton_1], Dil_Mesaji[rgba_buton_2]
    ,
        Dil_Mesaji[rgba_icerik_1],
        Dil_Mesaji[rgba_icerik_2],
        Dil_Mesaji[rgba_icerik_3],
        Dil_Mesaji[rgba_icerik_4],
        Dil_Mesaji[rgba_icerik_5],
        Dil_Mesaji[rgba_icerik_6]
    );
    return 1;
}

Dialog:RENK_RGBA(playerid, response, listitem, inputtext[])
{
    if(!response) return Renk(playerid);
    if(response)
    {
        new r, g, b, a, pos = -1;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Renk_RGBA(playerid);
        }

        pos = strfind(inputtext, "rgba(", true);
        if(pos != -1) strdel(inputtext, pos, pos + 5);

        pos = strfind(inputtext, ")", true, 0);
        if(pos != -1) strdel(inputtext, pos, strlen(inputtext));

        for(new i = 0; i < strlen(inputtext); i++)
        {
            if(inputtext[i] == ',')
            {
                if(inputtext[i + 1] >= '0' && inputtext[i + 1] <= '9')
                {
                    inputtext[i] = ' ';
                }
                else
                {
                    strdel(inputtext, i, i + 1);
                }
            }
        }

        if(sscanf(inputtext, "dddd", r, g, b, a)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Renk_RGBA(playerid);
        }

        if(r < 0 || r > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Renk_RGBA(playerid);
        }

        if(g < 0 || g > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Renk_RGBA(playerid);
        }

        if(b < 0 || b > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Renk_RGBA(playerid);
        }

        if(a < 0 || a > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Renk_RGBA(playerid);
        }

        if(GetPVarInt(playerid, "renk_modu") == 0) {
            if(Textler[gIndex][text.color] != RGB::HexToRGBA(r, g, b, a)) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.color] = RGB::HexToRGBA(r, g, b, a);
        }

        if(GetPVarInt(playerid, "renk_modu") == 1) {
            if(Textler[gIndex][text.bgcolor] != RGB::HexToRGBA(r, g, b, a)) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.bgcolor] = RGB::HexToRGBA(r, g, b, a);
        }
        
        if(GetPVarInt(playerid, "renk_modu") == 2) {
            if(Textler[gIndex][text.boxcolor] != RGB::HexToRGBA(r, g, b, a)) {
                gIleri_Ekle(gIndex);
            }
            Textler[gIndex][text.boxcolor] = RGB::HexToRGBA(r, g, b, a);
        }

        DB_Guncelle(gIndex);

        Textdraw_Render(gIndex, true);

        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
    }
    return 1;
}


/***
 *    8888888b.   .d8888b.  888888b.         d8888                  88888888888                888                  888          
 *    888   Y88b d88P  Y88b 888  "88b       d88888                      888                    888                  888          
 *    888    888 888    888 888  .88P      d88P888                      888                    888                  888          
 *    888   d88P 888        8888888K.     d88P 888                      888  888  888 .d8888b  888  8888b.  888d888 888  8888b.  
 *    8888888P"  888  88888 888  "Y88b   d88P  888                      888  888  888 88K      888     "88b 888P"   888     "88b 
 *    888 T88b   888    888 888    888  d88P   888      888888          888  888  888 "Y8888b. 888 .d888888 888     888 .d888888 
 *    888  T88b  Y88b  d88P 888   d88P d8888888888                      888  Y88b 888      X88 888 888  888 888     888 888  888 
 *    888   T88b  "Y8888P88 8888888P" d88P     888                      888   "Y88888  88888P' 888 "Y888888 888     888 "Y888888 
 *
 */

#define     RGBA_TICK_COUNT     200

RGBA_Tusla(playerid)
{
    if(timer_rgba != -1) KillTimer(timer_rgba), timer_rgba = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);

    Textler_TMP = Textler[gIndex];

    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);

    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }

    rgba_index = 0;
    rgba_time = GetTickCount();
    timer_rgba = SetTimerEx("Timer_RGBA", 30, true, "d", playerid);
    
    // İlk açılış için
    BilgiText_Update();
    new mod = GetPVarInt(playerid, "renk_modu"), RGBArr[4];
    if(mod == 0) RGB::RGBAToHex(Textler[gIndex][text.color], RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
    if(mod == 1) RGB::RGBAToHex(Textler[gIndex][text.bgcolor], RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
    if(mod == 2) RGB::RGBAToHex(Textler[gIndex][text.boxcolor], RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
    if(rgba_index == 0) TextDrawSetString(Bilgi_Text, fex("~r~~h~R: ~w~~h~%d   ~g~~h~G: ~w~~h~%d   ~g~~h~B: ~w~~h~%d   ~g~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
    if(rgba_index == 1) TextDrawSetString(Bilgi_Text, fex("~g~~h~R: ~w~~h~%d   ~r~~h~G: ~w~~h~%d   ~g~~h~B: ~w~~h~%d   ~g~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
    if(rgba_index == 2) TextDrawSetString(Bilgi_Text, fex("~g~~h~R: ~w~~h~%d   ~g~~h~G: ~w~~h~%d   ~r~~h~B: ~w~~h~%d   ~g~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
    if(rgba_index == 3) TextDrawSetString(Bilgi_Text, fex("~g~~h~R: ~w~~h~%d   ~g~~h~G: ~w~~h~%d   ~g~~h~B: ~w~~h~%d   ~r~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
    return 1;
}

forward Timer_RGBA(playerid);
public Timer_RGBA(playerid)
{
    new keys, ud, lr, RGBArr[4], mod = GetPVarInt(playerid, "renk_modu"), bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_rgba != -1)
    {
        tus = false;
        BilgiText_Gizle();

        if(mod == 0) RGB::RGBAToHex(Textler[gIndex][text.color], RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
        if(mod == 1) RGB::RGBAToHex(Textler[gIndex][text.bgcolor], RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
        if(mod == 2) RGB::RGBAToHex(Textler[gIndex][text.boxcolor], RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
        
        // sol
        if(lr < -1 && GetTickCount() > rgba_time)
        {
            tus = true;
            BilgiText_Update();
            rgba_time = GetTickCount() + RGBA_TICK_COUNT;
            rgba_index = (rgba_index <= 0) ? (0) : (rgba_index - 1);
        }

        // sağ
        if(lr > 1 && GetTickCount() > rgba_time)
        {
            tus = true;
            BilgiText_Update();
            rgba_time = GetTickCount() + RGBA_TICK_COUNT;
            rgba_index = (rgba_index >= 3) ? (3) : (rgba_index + 1);
        }
        
        // Yukarı
        if(ud < -1)
        {
            tus = true;
            BilgiText_Update();

            RGBArr[rgba_index] = (RGBArr[rgba_index] >= 255) ? (255) : (RGBArr[rgba_index] + 1);

            if(mod == 0) Textler[gIndex][text.color] = RGB::HexToRGBA(RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
            if(mod == 1) Textler[gIndex][text.bgcolor] = RGB::HexToRGBA(RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
            if(mod == 2) Textler[gIndex][text.boxcolor] = RGB::HexToRGBA(RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
        }

        // Aşağı
        if(ud > 1)
        {
            tus = true;
            BilgiText_Update();

            RGBArr[rgba_index] = (RGBArr[rgba_index] <= 0) ? (0) : (RGBArr[rgba_index] - 1);

            if(mod == 0) Textler[gIndex][text.color] = RGB::HexToRGBA(RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
            if(mod == 1) Textler[gIndex][text.bgcolor] = RGB::HexToRGBA(RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
            if(mod == 2) Textler[gIndex][text.boxcolor] = RGB::HexToRGBA(RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]);
        }

        if(tus == true)
        {
            Textdraw_Render(gIndex, true);

            if(rgba_index == 0) TextDrawSetString(Bilgi_Text, fex("~r~~h~R: ~w~~h~%d   ~g~~h~G: ~w~~h~%d   ~g~~h~B: ~w~~h~%d   ~g~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
            if(rgba_index == 1) TextDrawSetString(Bilgi_Text, fex("~g~~h~R: ~w~~h~%d   ~r~~h~G: ~w~~h~%d   ~g~~h~B: ~w~~h~%d   ~g~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
            if(rgba_index == 2) TextDrawSetString(Bilgi_Text, fex("~g~~h~R: ~w~~h~%d   ~g~~h~G: ~w~~h~%d   ~r~~h~B: ~w~~h~%d   ~g~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
            if(rgba_index == 3) TextDrawSetString(Bilgi_Text, fex("~g~~h~R: ~w~~h~%d   ~g~~h~G: ~w~~h~%d   ~g~~h~B: ~w~~h~%d   ~r~~h~A: ~w~~h~%d", RGBArr[0], RGBArr[1], RGBArr[2], RGBArr[3]));
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_rgba != -1)
    {
        KillTimer(timer_rgba), timer_rgba = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_rgba != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(timer_rgba), timer_rgba = -1;
        switch(GetPVarInt(playerid, "renk_modu"))
        {
            // text.color
            case 0:
            {
                if(Textler_TMP[text.color] != Textler[gIndex][text.color])
                {
                    new orijinal_data[textdraw_yapilandirmasi];

                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // text.bgcolor
            case 1:
            {
                if(Textler_TMP[text.bgcolor] != Textler[gIndex][text.bgcolor])
                {
                    new orijinal_data[textdraw_yapilandirmasi];

                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // text.boxcolor
            case 2:
            {
                if(Textler_TMP[text.boxcolor] != Textler[gIndex][text.boxcolor])
                {
                    new orijinal_data[textdraw_yapilandirmasi];

                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }
        }
        DB_Guncelle(gIndex);
        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
        ChatTemizle();
        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 1);
        }
    }
    return 1;
}