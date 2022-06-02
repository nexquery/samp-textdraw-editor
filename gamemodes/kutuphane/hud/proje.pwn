
/***
 *    8888888b.                   d8b          
 *    888   Y88b                  Y8P          
 *    888    888                               
 *    888   d88P 888d888 .d88b.  8888  .d88b.  
 *    8888888P"  888P"  d88""88b "888 d8P  Y8b 
 *    888        888    888  888  888 88888888 
 *    888        888    Y88..88P  888 Y8b.     
 *    888        888     "Y88P"   888  "Y8888  
 *                                888          
 *                               d88P          
 *                             888P"           
 */

Proje_Menu(playerid)
{
    Dialog_Show(playerid, PROJE_MENU, DIALOG_STYLE_LIST, Dil_Mesaji[proje_baslik], "\
    %s\n%s\n%s\n%s\n%s", Dil_Mesaji[proje_buton_1], Dil_Mesaji[proje_buton_2]
    ,
        Dil_Mesaji[proje_icerik_1],
        Dil_Mesaji[proje_icerik_2],
        Dil_Mesaji[proje_icerik_3],
        Dil_Mesaji[proje_icerik_4],
        Dil_Mesaji[proje_icerik_5]
    );
    return 1;
}

Dialog:PROJE_MENU(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        switch(listitem)
        {
            // Proje Oluştur
            case 0: Yeni_Proje_Olustur(playerid);

            // Projeler
            case 1: projeler_sayfa = 0, Projeler_Menu(playerid);

            // İçe Aktar
            case 2: Ice_Aktar_Menu(playerid);

            // Dışa Aktar
            case 3: Disa_Aktar_Menu(playerid);

            // Projeyi Kapat
            case 4: Projeyi_Kapat(playerid);
        }
    }
    return 1;
}


/***
 *    Y88b   d88P                d8b      8888888b.                   d8b                .d88888b.  888                   888                     
 *     Y88b d88P                 Y8P      888   Y88b                  Y8P               d88P" "Y88b 888                   888                     
 *      Y88o88P                           888    888                                    888     888 888                   888                     
 *       Y888P  .d88b.  88888b.  888      888   d88P 888d888 .d88b.  8888  .d88b.       888     888 888 888  888 .d8888b  888888 888  888 888d888 
 *        888  d8P  Y8b 888 "88b 888      8888888P"  888P"  d88""88b "888 d8P  Y8b      888     888 888 888  888 88K      888    888  888 888P"   
 *        888  88888888 888  888 888      888        888    888  888  888 88888888      888     888 888 888  888 "Y8888b. 888    888  888 888     
 *        888  Y8b.     888  888 888      888        888    Y88..88P  888 Y8b.          Y88b. .d88P 888 Y88b 888      X88 Y88b.  Y88b 888 888     
 *        888   "Y8888  888  888 888      888        888     "Y88P"   888  "Y8888        "Y88888P"  888  "Y88888  88888P'  "Y888  "Y88888 888     
 *                                                                    888                                                                         
 *                                                                   d88P                                                                         
 *                                                                 888P"                                                                          
 */

Yeni_Proje_Olustur(playerid)
{
    if(proje_durum == true)
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[po_hata_5]), Proje_Menu(playerid);
    }
    Dialog_Show(playerid, YENI_PROJE_OLUSTUR, DIALOG_STYLE_INPUT, Dil_Mesaji[po_baslik], Dil_Mesaji[po_metin], Dil_Mesaji[po_buton_1], Dil_Mesaji[po_buton_2]);
    return 1;
}

Dialog:YENI_PROJE_OLUSTUR(playerid, response, listitem, inputtext[])
{
    if(!response) return Proje_Menu(playerid);
    if(response)
    {
        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[po_hata_1]), Yeni_Proje_Olustur(playerid);
        }

        if(strlen(inputtext) > PROJE_MAX_ISIM) {
            return Mesaj_Hata(playerid, Dil_Mesaji[po_hata_2]), Yeni_Proje_Olustur(playerid);
        }

        if(Dosya_Adi_Kontrol(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[po_hata_3]), Yeni_Proje_Olustur(playerid);
        }

        if(Proje_Adi_Kontrol(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[po_hata_4]), Yeni_Proje_Olustur(playerid);
        }

        // Veritaban listesine projeyi kaydet
        db_free_result(db_query(proje_listesi, fex("INSERT INTO projeler (isim, tarih) VALUES ('%q', '%d');", inputtext, gettime())));

        // Projenin veritabanını oluştur
        proje_db = db_open(fex(DOSYA_PROJE_DB, inputtext));

        // Sorgu 1
        db_free_result(db_query(proje_db, PROJE_DB_QUERY_1));
        db_free_result(db_query(proje_db, fex("INSERT INTO ayarlar (version, saat, hud, global, player) VALUES ('%s', '%d', '%.1f', '%q', '%q');", TDE_VERSION, proje_saat, Text_Hud_Y, Text_Global, Text_Player)));

        // Sorgu 2
        db_free_result(db_query(proje_db, PROJE_DB_QUERY_2));

        // Sorgu 3
        db_free_result(db_query(proje_db, PROJE_DB_QUERY_3));

        // Sorgu 4
        db_free_result(db_query(proje_db, PROJE_DB_QUERY_4));

        // Proje verilerini ayarla
        proje_durum = true, format(proje_adi, PROJE_MAX_ISIM, inputtext);

        // Hudu yenile
        Hud_Render(true), Hud_Goster(true);

        // Mouse
        Mouse(playerid, true, TEXTMOD_NORMAL);

        // Bilgi
        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[po_bilgi_1]), inputtext);
    }
    return 1;
}


/***
 *    8888888b.                   d8b          888                  
 *    888   Y88b                  Y8P          888                  
 *    888    888                               888                  
 *    888   d88P 888d888 .d88b.  8888  .d88b.  888  .d88b.  888d888 
 *    8888888P"  888P"  d88""88b "888 d8P  Y8b 888 d8P  Y8b 888P"   
 *    888        888    888  888  888 88888888 888 88888888 888     
 *    888        888    Y88..88P  888 Y8b.     888 Y8b.     888     
 *    888        888     "Y88P"   888  "Y8888  888  "Y8888  888     
 *                                888                               
 *                               d88P                               
 *                             888P"                                
 */

Projeler_Menu(playerid)
{
    new
        DBResult: cache = db_query(proje_listesi, fex("SELECT *, (SELECT COUNT(*) FROM projeler) AS total FROM projeler ORDER BY tarih DESC LIMIT %d, %d", (projeler_sayfa * PROJE_MAX_ICERIK), PROJE_MAX_ICERIK)),
        rows = db_num_rows(cache),
        buffer[2000],
        index,
        tarih
    ;

    format(buffer, sizeof(buffer), "%s%s\t%s\n",    buffer, Dil_Mesaji[pler_icerik_1], Dil_Mesaji[pler_icerik_2]);
    format(buffer, sizeof(buffer), "%s>>\t\n",      buffer);
    format(buffer, sizeof(buffer), "%s<<\t\n",      buffer);
    format(buffer, sizeof(buffer), "%s%s\t\n",      buffer, Dil_Mesaji[pler_icerik_3]);
    format(buffer, sizeof(buffer), "%s \t\n",       buffer);

    if(rows)
    {
        do
        {
            db_get_field_assoc(cache, "isim", projeler_listesi[index]), tarih = db_get_field_assoc_int(cache, "tarih"), projeler_total = db_get_field_assoc_int(cache, "total");
            format(buffer, sizeof(buffer), "%s%s\t%s\n"
            ,
                buffer, 
                projeler_listesi[index],
                Tarih_Cek(tarih)
            );
            index++;
        }
        while(db_next_row(cache));

        Dialog_Show(playerid, PROJE_LISTESI, DIALOG_STYLE_TABLIST_HEADERS, fex(fmt(Dil_Mesaji[pler_baslik]), (projeler_sayfa + 1), Max_Page(projeler_total, PROJE_MAX_ICERIK)), buffer, Dil_Mesaji[pler_buton_1], Dil_Mesaji[pler_buton_2]);
    }
    else
    {
        Mesaj_Hata(playerid, Dil_Mesaji[pler_hata]), Proje_Menu(playerid);
    }

    db_free_result(cache);
    return 1;
}

Dialog:PROJE_LISTESI(playerid, response, listitem, inputtext[])
{
    if(!response) return Proje_Menu(playerid);
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(projeler_sayfa++ >= (Max_Page(projeler_total, PROJE_MAX_ICERIK) - 1))
                {
                    projeler_sayfa = (Max_Page(projeler_total, PROJE_MAX_ICERIK) - 1);
                }
                Projeler_Menu(playerid);
            }

            case 1:
            {
                if(projeler_sayfa-- <= 0)
                {
                    projeler_sayfa = 0;
                }
                Projeler_Menu(playerid);
            }

            case 2: Sayfa_Menu(playerid, SAYFA_PROJE_LISTESI);

            case 3: Projeler_Menu(playerid);

            default:
            {
                projeler_listitem = listitem - 4;
                Proje_Islemi(playerid);
            }
        }
    }
    return 1;
}


/***
 *    8888888b.                   d8b               8888888         888                        d8b 
 *    888   Y88b                  Y8P                 888           888                        Y8P 
 *    888    888                                      888           888                            
 *    888   d88P 888d888 .d88b.  8888  .d88b.         888  .d8888b  888  .d88b.  88888b.d88b.  888 
 *    8888888P"  888P"  d88""88b "888 d8P  Y8b        888  88K      888 d8P  Y8b 888 "888 "88b 888 
 *    888        888    888  888  888 88888888        888  "Y8888b. 888 88888888 888  888  888 888 
 *    888        888    Y88..88P  888 Y8b.            888       X88 888 Y8b.     888  888  888 888 
 *    888        888     "Y88P"   888  "Y8888       8888888 88888P' 888  "Y8888  888  888  888 888 
 *                                888                                                              
 *                               d88P                                                              
 *                             888P"                                                               
 */

Proje_Islemi(playerid)
{
    Dialog_Show(playerid, PROJE_ISLEM, DIALOG_STYLE_LIST, Dil_Mesaji[pi_baslik], "%s\n%s", Dil_Mesaji[pi_buton_1], Dil_Mesaji[pi_buton_2]
    ,
        Dil_Mesaji[pi_icerik_1],
        Dil_Mesaji[pi_icerik_2]
    );
    return 1;
}

Projeyi_Sil(playerid)
{
    if(proje_durum == true && isequal(proje_adi, projeler_listesi[projeler_listitem], false))
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[pi_uyari_hata]), Proje_Islemi(playerid);
    }
    Dialog_Show(playerid, PROJE_ISLEM_SIL, DIALOG_STYLE_MSGBOX, Dil_Mesaji[pi_uyari_bslk], Dil_Mesaji[pi_uyari_icrk], Dil_Mesaji[pi_uyari_btn1], Dil_Mesaji[pi_uyari_btn2]);
    return 1;
}

Dialog:PROJE_ISLEM(playerid, response, listitem, inputtext[])
{
    if(!response) return Projeler_Menu(playerid);
    if(response)
    {
        if(listitem == 0) Projeyi_Yukle(playerid, projeler_listesi[projeler_listitem]);
        if(listitem == 1) Projeyi_Sil(playerid);
    }
    return 1;
}

Dialog:PROJE_ISLEM_SIL(playerid, response, listitem, inputtext[])
{
    if(!response) return Proje_Islemi(playerid);
    if(response)
    {
        if(fexist(fex(DOSYA_PROJE_DB, projeler_listesi[projeler_listitem]))) {
            fremove(fex(DOSYA_PROJE_DB, projeler_listesi[projeler_listitem]));
        }

        db_free_result(db_query(proje_listesi, fex("DELETE FROM projeler WHERE LOWER(isim) = LOWER('%q');", projeler_listesi[projeler_listitem])));

        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[pi_uyari_bilgi]), projeler_listesi[projeler_listitem]);

        projeler_listitem = 0;

        projeler_sayfa = 0;
        
        Projeler_Menu(playerid);
    }
    return 1;
}

Projeyi_Yukle(playerid, const proje_dosyasi[])
{
    if(proje_durum == true && isequal(proje_adi, proje_dosyasi, false))
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[pi_hata_1]), Proje_Islemi(playerid);
    }

    if(proje_durum == true && !isequal(proje_adi, proje_dosyasi, false))
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[pi_hata_2]), Proje_Islemi(playerid);
    }

    if(!fexist(fex(DOSYA_PROJE_DB, proje_dosyasi)))
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[pi_hata_3]), Proje_Islemi(playerid);
    }

    if(proje_db != DB: 0) db_close(proje_db), proje_db = DB: 0;

    proje_db = db_open(fex(DOSYA_PROJE_DB, proje_dosyasi));

    new
        DBResult: ayarlar = db_query(proje_db, "SELECT * FROM ayarlar"),
        rows_ayarlar = db_num_rows(ayarlar),
        
        id, g, p,
        DBResult: textdrawlar = db_query(proje_db, "SELECT * FROM textdrawlar"),
        rows_textdrawlar = db_num_rows(textdrawlar)
    ;

    if(rows_ayarlar)
    {
        proje_saat = db_get_field_assoc_int(ayarlar, "saat");
        Text_Hud_Y = db_get_field_assoc_float(ayarlar, "hud");
        db_get_field_assoc(ayarlar, "global", Text_Global);
        db_get_field_assoc(ayarlar, "player", Text_Player);
        SetPlayerTime(playerid, proje_saat, 0);
    }

    if(rows_textdrawlar)
    {
        do
        {
            id = db_get_field_assoc_int(textdrawlar, "id");
            db_get_field_assoc(textdrawlar, "icerik", Textler[id][text.string], MAX_TEXT_STRING);
            Textler[id][text.pos][0]            = db_get_field_assoc_float(textdrawlar, "posX");
            Textler[id][text.pos][1]            = db_get_field_assoc_float(textdrawlar, "posY");
            Textler[id][text.lettersize][0]     = db_get_field_assoc_float(textdrawlar, "lettersizeX");
            Textler[id][text.lettersize][1]     = db_get_field_assoc_float(textdrawlar, "lettersizeY");
            Textler[id][text.textsize][0]       = db_get_field_assoc_float(textdrawlar, "textsizeX");
            Textler[id][text.textsize][1]       = db_get_field_assoc_float(textdrawlar, "textsizeY");
            Textler[id][text.alignment]         = db_get_field_assoc_int(textdrawlar, "alignment");
            Textler[id][text.color]             = db_get_field_assoc_int(textdrawlar, "color");
            Textler[id][text.usebox]            = db_get_field_assoc_int(textdrawlar, "usebox");
            Textler[id][text.boxcolor]          = db_get_field_assoc_int(textdrawlar, "boxcolor");
            Textler[id][text.shadow]            = db_get_field_assoc_int(textdrawlar, "shadow");
            Textler[id][text.outline]           = db_get_field_assoc_int(textdrawlar, "outline");
            Textler[id][text.bgcolor]           = db_get_field_assoc_int(textdrawlar, "bgcolor");
            Textler[id][text.font]              = db_get_field_assoc_int(textdrawlar, "font");
            Textler[id][text.proportional]      = db_get_field_assoc_int(textdrawlar, "proportional");
            Textler[id][text.selectable]        = db_get_field_assoc_int(textdrawlar, "selectable");
            Textler[id][text.preview_model]     = db_get_field_assoc_int(textdrawlar, "previewModel");
            Textler[id][text.preview_rot][0]    = db_get_field_assoc_float(textdrawlar, "previewX");
            Textler[id][text.preview_rot][1]    = db_get_field_assoc_float(textdrawlar, "previewY");
            Textler[id][text.preview_rot][2]    = db_get_field_assoc_float(textdrawlar, "previewZ");
            Textler[id][text.preview_rot][3]    = db_get_field_assoc_float(textdrawlar, "previewZoom");
            Textler[id][text.preview_vc][0]     = db_get_field_assoc_int(textdrawlar, "previewVC1");
            Textler[id][text.preview_vc][1]     = db_get_field_assoc_int(textdrawlar, "previewVC2");
            Textler[id][text.globaplayer]       = db_get_field_assoc_int(textdrawlar, "globalPlayer");
            db_get_field_assoc(textdrawlar, "degiskenadi", Textler[id][text.degiskenAdi], MAX_GPLAYER_ISIM);
            Textler[id][text.grup]              = db_get_field_assoc_int(textdrawlar, "grup");

            if(Textler[id][text.globaplayer] == 0) g++;
            if(Textler[id][text.globaplayer] == 1) p++;

            Iter_Add(Text_List, id);
        }
        while(db_next_row(textdrawlar));
    }

    db_free_result(ayarlar), db_free_result(textdrawlar);

    proje_durum = true, format(proje_adi, PROJE_MAX_ISIM, proje_dosyasi);

    Hud_Oncelik_Textdraw(true), Bilgi_Text_Kaldir();

    Mouse(playerid, true, TEXTMOD_NORMAL);

    Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[pi_bilgi]), proje_adi, g, p, (g + p));
    return 1;
}


/***
 *    8888888                             d8888 888      888                     
 *      888                              d88888 888      888                     
 *      888                             d88P888 888      888                     
 *      888   .d8888b .d88b.           d88P 888 888  888 888888  8888b.  888d888 
 *      888  d88P"   d8P  Y8b         d88P  888 888 .88P 888        "88b 888P"   
 *      888  888     88888888        d88P   888 888888K  888    .d888888 888     
 *      888  Y88b.   Y8b.           d8888888888 888 "88b Y88b.  888  888 888     
 *    8888888 "Y8888P "Y8888       d88P     888 888  888  "Y888 "Y888888 888     
 *                                                                               
 */

#define     MOD_YOK         (0)
#define     MOD_GLOBAL      (1)
#define     MOD_PLAYER      (2)

Ice_Aktar_Menu(playerid)
{
    if(proje_durum == false)
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[ia_hata_1]), Proje_Menu(playerid);
    }

    Dialog_Show(playerid, DOSYA_IAKTAR, DIALOG_STYLE_INPUT, Dil_Mesaji[ia_baslik], "%s\n%s", Dil_Mesaji[ia_btn1], Dil_Mesaji[ia_btn2]
    ,
        Dil_Mesaji[ia_icerik_1],
        Dil_Mesaji[ia_icerik_2]
    );
    return 1;
}

Dialog:DOSYA_IAKTAR(playerid, response, listitem, inputtext[])
{
    if(!response) return Proje_Menu(playerid);
    if(response)
    {
        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[ia_hata_2]), Ice_Aktar_Menu(playerid);
        }

        if(!fexist(fex(DOSYA_ICE_AKTAR, inputtext))) {
            return Mesaj_Hata(playerid, fmt(Dil_Mesaji[ia_hata_3]), inputtext), Ice_Aktar_Menu(playerid);
        }

        Ice_Aktar(playerid, inputtext);
    }
    return 1;
}

Ice_Aktar(playerid, const dosya_adi[])
{
    new
        File: dosya = fopen(fex(DOSYA_ICE_AKTAR, dosya_adi), io_read),
        buffer[750],
        pos = -1,
        mod = MOD_YOK,
        id,
        g,
        p
    ;
    while(fread(dosya, buffer))
    {
        if((id = Iter_Free(Text_List)) == ITER_NONE)
        {
            Mesaj_Hata(playerid, Dil_Mesaji[ia_hata_4]);
            break;
        }

        New_Line(buffer);

        if((pos = strfind(buffer, "TextDrawCreate", true)) != -1)
        {
            new Float: x, Float: y;
            pos = strfind(buffer, "(", false), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1))), sscanf(buffer, "p<,>ff", x, y);
            pos = strfind(buffer, "\"", false), strdel(buffer, 0, pos + 1);
            pos = strfind(buffer, "\");", false), strdel(buffer, pos, strlen(buffer));
            mod = MOD_GLOBAL;
            if(isnull(buffer)) buffer[0] = '_', pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));

            static const reset[textdraw_yapilandirmasi];
            Textler[id]                     = reset;
            Textler[id][text.id]            = Text: -1;
            Textler[id][text.pos][0]        = x;
            Textler[id][text.pos][1]        = y;
            format(Textler[id][text.string], MAX_TEXT_STRING, buffer);
            Textler[id][text.globaplayer]   = 0;

            g++;
        }

        if((pos = strfind(buffer, "CreatePlayerTextDraw", true)) != -1)
        {
            new Float: x, Float: y;
            pos = strfind(buffer, ",", false), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1))), sscanf(buffer, "p<,>ff", x, y);
            pos = strfind(buffer, "\"", false), strdel(buffer, 0, pos + 1);
            pos = strfind(buffer, "\");", false), strdel(buffer, pos, strlen(buffer));
            mod = MOD_PLAYER;
            if(isnull(buffer)) buffer[0] = '_', pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));

            static const reset[textdraw_yapilandirmasi];
            Textler[id]                     = reset;
            Textler[id][text.id]            = Text: -1;
            Textler[id][text.pos][0]        = x;
            Textler[id][text.pos][1]        = y;
            format(Textler[id][text.string], MAX_TEXT_STRING, buffer);
            Textler[id][text.globaplayer]   = 1;

            p++;
        }

        if(mod == MOD_GLOBAL)
        {
            if((pos = strfind(buffer, "TextDrawLetterSize", true)) != -1)
            {
                new Float: x, Float: y;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>ff", x, y);

                Textler[id][text.lettersize][0] = x;
                Textler[id][text.lettersize][1] = y;
            }

            if((pos = strfind(buffer, "TextDrawTextSize", true)) != -1)
            {
                new Float: x, Float: y;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>ff", x, y);

                Textler[id][text.textsize][0] = x;
                Textler[id][text.textsize][1] = y;
            }

            if((pos = strfind(buffer, "TextDrawAlignment", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.alignment] = deger;
            }

            if((pos = strfind(buffer, "TextDrawColor", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                
                if(buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))
                {
                    sscanf(buffer, "p<,>h", deger);
                }
                else
                {
                    sscanf(buffer, "p<,>d", deger);
                }
                
                Textler[id][text.color] = deger;
            }

            if((pos = strfind(buffer, "TextDrawUseBox", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>l", deger);

                Textler[id][text.usebox] = deger;
            }

            if((pos = strfind(buffer, "TextDrawBoxColor", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                
                if(buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))
                {
                    sscanf(buffer, "p<,>h", deger);
                }
                else
                {
                    sscanf(buffer, "p<,>d", deger);
                }

                Textler[id][text.boxcolor] = deger;
            }

            if((pos = strfind(buffer, "TextDrawSetShadow", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.shadow] = deger;
            }

            if((pos = strfind(buffer, "TextDrawSetOutline", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.outline] = deger;
            }

            if((pos = strfind(buffer, "TextDrawBackgroundColor", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));

                if(buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))
                {
                    sscanf(buffer, "p<,>h", deger);
                }
                else
                {
                    sscanf(buffer, "p<,>d", deger);
                }

                Textler[id][text.bgcolor] = deger;
            }

            if((pos = strfind(buffer, "TextDrawFont", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.font] = deger;
            }

            if((pos = strfind(buffer, "TextDrawSetProportional", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.proportional] = deger;
            }

            if((pos = strfind(buffer, "TextDrawSetSelectable", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>l", deger);

                Textler[id][text.selectable] = deger;
            }

            if((pos = strfind(buffer, "TextDrawSetPreviewModel", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.preview_model] = deger;
            }

            if((pos = strfind(buffer, "TextDrawSetPreviewRot", true)) != -1)
            {
                new Float: x, Float: y, Float: z, Float: zoom;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>ffff", x, y, z, zoom);

                Textler[id][text.preview_rot][0] = x;
                Textler[id][text.preview_rot][1] = y;
                Textler[id][text.preview_rot][2] = z;
                Textler[id][text.preview_rot][3] = zoom;
            }

            if((pos = strfind(buffer, "TextDrawSetPreviewVehCol", true)) != -1)
            {
                new r1, r2;
                pos = strfind(buffer, ",", false),  strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>dd", r1, r2);

                Textler[id][text.preview_vc][0] = r1;
                Textler[id][text.preview_vc][1] = r2;
            }

            if(isnull(buffer) && mod != MOD_YOK)
            {
                Iter_Add(Text_List, id), DB_Ekle(id);
                mod = MOD_YOK;
            }
        }
        else if(mod == MOD_PLAYER)
        {
            if((pos = strfind(buffer, "PlayerTextDrawLetterSize", true)) != -1)
            {
                new Float: x, Float: y;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>ff", x, y);

                Textler[id][text.lettersize][0] = x;
                Textler[id][text.lettersize][1] = y;
            }

            if((pos = strfind(buffer, "PlayerTextDrawTextSize", true)) != -1)
            {
                new Float: x, Float: y;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>ff", x, y);

                Textler[id][text.textsize][0] = x;
                Textler[id][text.textsize][1] = y;
            }

            if((pos = strfind(buffer, "PlayerTextDrawAlignment", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.alignment] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawColor", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));

                if(buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))
                {
                    sscanf(buffer, "p<,>h", deger);
                }
                else
                {
                    sscanf(buffer, "p<,>d", deger);
                }

                Textler[id][text.color] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawUseBox", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>l", deger);

                Textler[id][text.usebox] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawBoxColor", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));

                if(buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))
                {
                    sscanf(buffer, "p<,>h", deger);
                }
                else
                {
                    sscanf(buffer, "p<,>d", deger);
                }

                Textler[id][text.boxcolor] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawSetShadow", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.shadow] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawSetOutline", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.outline] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawBackgroundColor", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));

                if(buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X'))
                {
                    sscanf(buffer, "p<,>h", deger);
                }
                else
                {
                    sscanf(buffer, "p<,>d", deger);
                }

                Textler[id][text.bgcolor] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawFont", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.font] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawSetProportional", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.proportional] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawSetSelectable", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>l", deger);

                Textler[id][text.selectable] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawSetPreviewModel", true)) != -1)
            {
                new deger;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>d", deger);

                Textler[id][text.preview_model] = deger;
            }

            if((pos = strfind(buffer, "PlayerTextDrawSetPreviewRot", true)) != -1)
            {
                new Float: x, Float: y, Float: z, Float: zoom;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>ffff", x, y, z, zoom);

                Textler[id][text.preview_rot][0] = x;
                Textler[id][text.preview_rot][1] = y;
                Textler[id][text.preview_rot][2] = z;
                Textler[id][text.preview_rot][3] = zoom;
            }

            if((pos = strfind(buffer, "PlayerTextDrawSetPreviewVehCol", true)) != -1)
            {
                new r1, r2;
                pos = strfind(buffer, ",", false, 0), pos = strfind(buffer, ",", false, pos + 1), strdel(buffer, 0, pos + ((buffer[pos + 1] == ' ') ? (2) : (1)));
                pos = strfind(buffer, ");", false), strdel(buffer, pos, strlen(buffer));
                sscanf(buffer, "p<,>dd", r1, r2);

                Textler[id][text.preview_vc][0] = r1;
                Textler[id][text.preview_vc][1] = r2;
            }

            if(isnull(buffer) && mod != MOD_YOK)
            {
                Iter_Add(Text_List, id), DB_Ekle(id);
                mod = MOD_YOK;
            }
        }
    }

    if(!Iter_Contains(Text_List, id) && mod != MOD_YOK)
    {
        Iter_Add(Text_List, id), DB_Ekle(id);
    }

    fclose(dosya);

    if(g == 0 && p == 0)
        Mesaj_Hata(playerid, Dil_Mesaji[ia_hata_5]), Ice_Aktar_Menu(playerid);
    else
        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[ia_bilgi]), dosya_adi, g, p, (g + p)), Mouse(playerid, true, TEXTMOD_NORMAL), Hud_Oncelik_Textdraw(true), Bilgi_Text_Kaldir();
    return 1;
}



/***
 *    8888888b.  d8b                               d8888 888      888                     
 *    888  "Y88b Y8P                              d88888 888      888                     
 *    888    888                                 d88P888 888      888                     
 *    888    888 888 .d8888b   8888b.           d88P 888 888  888 888888  8888b.  888d888 
 *    888    888 888 88K          "88b         d88P  888 888 .88P 888        "88b 888P"   
 *    888    888 888 "Y8888b. .d888888        d88P   888 888888K  888    .d888888 888     
 *    888  .d88P 888      X88 888  888       d8888888888 888 "88b Y88b.  888  888 888     
 *    8888888P"  888  88888P' "Y888888      d88P     888 888  888  "Y888 "Y888888 888     
 *                                                                                                                         
 */

Disa_Aktar_Menu(playerid)
{
    if(proje_durum == false)
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[da_hata2]), Proje_Menu(playerid);
    }

    if(!Iter_Count(Text_List))
    {
        return Mesaj_Hata(playerid, Dil_Mesaji[da_hata]), Proje_Menu(playerid);
    }

    Dialog_Show(playerid, DOSYA_DAKTAR, DIALOG_STYLE_INPUT, Dil_Mesaji[da_baslik], "%s\n%s", Dil_Mesaji[da_btn1], Dil_Mesaji[da_btn2]
    ,
        Dil_Mesaji[da_icerik_1],
        fex(fmt(Dil_Mesaji[da_icerik_2]), proje_adi)
    );
    return 1;
}

Dialog:DOSYA_DAKTAR(playerid, response, listitem, inputtext[])
{
    if(!response) return Proje_Menu(playerid);
    if(response)
    {
        if(isnull(inputtext))
        {
            Disa_Aktar(playerid, proje_adi);
        }
        else
        {
            new pos = strfind(inputtext, ".txt", true);
            if(pos != -1)
            {
                strdel(inputtext, pos, pos + 4);
            }
            Disa_Aktar(playerid, inputtext);
        }
    }
    return 1;
}

Disa_Aktar(playerid, const dosya_adi[])
{
    new
        File: dosya = fopen(fex(DOSYA_DISA_AKTAR, dosya_adi), io_write),
        index,
        g   = Total_gPlayer(0),
        p   = Total_gPlayer(1),
        dg  = Total_Degisken_gPlayer(0),
        dp  = Total_Degisken_gPlayer(1),
        sz[512]
    ;

    // Global
    if(g)
    {
        index = 0;
        format(sz, sizeof(sz), "new Text: %s[%d];\r\n\r\n", Text_Global, Total_gPlayer2(0));
        fwrite(dosya, sz);
        foreach(new id : Text_List)
        {
            if(Textler[id][text.globaplayer] == 0 && !strlen(Textler[id][text.degiskenAdi]))
            {
                format(sz, sizeof(sz), "%s[%d] = TextDrawCreate(%.3f, %.3f, \"%s\");\r\n", Text_Global, index, Textler[id][text.pos][0], Textler[id][text.pos][1], Textler[id][text.string]);
                fwrite(dosya, sz);
                
                if(Textler[id][text.lettersize][0] != 0.0 || Textler[id][text.lettersize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "TextDrawLetterSize(%s[%d], %.3f, %.3f);\r\n", Text_Global, index, Textler[id][text.lettersize][0], Textler[id][text.lettersize][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.textsize][0] != 0.0 || Textler[id][text.textsize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "TextDrawTextSize(%s[%d], %.3f, %.3f);\r\n", Text_Global, index, Textler[id][text.textsize][0], Textler[id][text.textsize][1]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "TextDrawAlignment(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.alignment]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawColor(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.color]);
                fwrite(dosya, sz);

                if(Textler[id][text.usebox] == 1)
                {
                    format(sz, sizeof(sz), "TextDrawUseBox(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.usebox]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "TextDrawBoxColor(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.boxcolor]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "TextDrawSetShadow(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.shadow]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawSetOutline(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.outline]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawBackgroundColor(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.bgcolor]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawFont(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.font]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawSetProportional(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.proportional]);
                fwrite(dosya, sz);

                if(Textler[id][text.font] == TEXT_DRAW_FONT_MODEL_PREVIEW)
                {
                    format(sz, sizeof(sz), "TextDrawSetPreviewModel(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.preview_model]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "TextDrawSetPreviewRot(%s[%d], %.3f, %.3f, %.3f, %.3f);\r\n", Text_Global, index, Textler[id][text.preview_rot][0], Textler[id][text.preview_rot][1], Textler[id][text.preview_rot][2], Textler[id][text.preview_rot][3]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "TextDrawSetPreviewVehCol(%s[%d], %d, %d);\r\n", Text_Global, index, Textler[id][text.preview_vc][0], Textler[id][text.preview_vc][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.selectable] == 1)
                {
                    format(sz, sizeof(sz), "TextDrawSetSelectable(%s[%d], %d);\r\n", Text_Global, index, Textler[id][text.selectable]);
                    fwrite(dosya, sz);
                }

                fwrite(dosya, "\r\n");

                index++;
            }
        }
    }

    // Player
    if(p)
    {
        index = 0;
        if(p) fwrite(dosya, "####################################################################################################\r\n\r\n");
        format(sz, sizeof(sz), "new PlayerText: %s[MAX_PLAYERS][%d];\r\n\r\n", Text_Player, Total_gPlayer2(1));
        fwrite(dosya, sz);
        foreach(new id : Text_List)
        {
            if(Textler[id][text.globaplayer] == 1 && !strlen(Textler[id][text.degiskenAdi]))
            {
                format(sz, sizeof(sz), "%s[playerid][%d] = CreatePlayerTextDraw(playerid, %.3f, %.3f, \"%s\");\r\n", Text_Player, index, Textler[id][text.pos][0], Textler[id][text.pos][1], Textler[id][text.string]);
                fwrite(dosya, sz);
                
                if(Textler[id][text.lettersize][0] != 0.0 || Textler[id][text.lettersize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawLetterSize(playerid, %s[playerid][%d], %.3f, %.3f);\r\n", Text_Player, index, Textler[id][text.lettersize][0], Textler[id][text.lettersize][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.textsize][0] != 0.0 || Textler[id][text.textsize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawTextSize(playerid, %s[playerid][%d], %.3f, %.3f);\r\n", Text_Player, index, Textler[id][text.textsize][0], Textler[id][text.textsize][1]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "PlayerTextDrawAlignment(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.alignment]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawColor(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.color]);
                fwrite(dosya, sz);

                if(Textler[id][text.usebox] == 1)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawUseBox(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.usebox]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "PlayerTextDrawBoxColor(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.boxcolor]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "PlayerTextDrawSetShadow(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.shadow]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawSetOutline(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.outline]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawBackgroundColor(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.bgcolor]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawFont(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.font]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawSetProportional(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.proportional]);
                fwrite(dosya, sz);

                if(Textler[id][text.font] == TEXT_DRAW_FONT_MODEL_PREVIEW)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawSetPreviewModel(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.preview_model]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "PlayerTextDrawSetPreviewRot(playerid, %s[playerid][%d], %.3f, %.3f, %.3f, %.3f);\r\n", Text_Player, index, Textler[id][text.preview_rot][0], Textler[id][text.preview_rot][1], Textler[id][text.preview_rot][2], Textler[id][text.preview_rot][3]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "PlayerTextDrawSetPreviewVehCol(playerid, %s[playerid][%d], %d, %d);\r\n", Text_Player, index, Textler[id][text.preview_vc][0], Textler[id][text.preview_vc][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.selectable] == 1)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawSetSelectable(playerid, %s[playerid][%d], %d);\r\n", Text_Player, index, Textler[id][text.selectable]);
                    fwrite(dosya, sz);
                }

                fwrite(dosya, "\r\n");

                index++;
            }
        }
    }

    // Değişken Global
    if(dg)
    {
        if(dg) fwrite(dosya, "####################################################################################################\r\n\r\n");
        foreach(new id : Text_List)
        {
            if(Textler[id][text.globaplayer] == 0 && strlen(Textler[id][text.degiskenAdi]))
            {
                format(sz, sizeof(sz), "new Text: %s;\r\n", Textler[id][text.degiskenAdi]);
                fwrite(dosya, sz);
            }
        }
        fwrite(dosya, "\r\n");
        foreach(new id : Text_List)
        {
            if(Textler[id][text.globaplayer] == 0 && strlen(Textler[id][text.degiskenAdi]))
            {
                format(sz, sizeof(sz), "%s = TextDrawCreate(%.3f, %.3f, \"%s\");\r\n", Textler[id][text.degiskenAdi], Textler[id][text.pos][0], Textler[id][text.pos][1], Textler[id][text.string]);
                fwrite(dosya, sz);
                
                if(Textler[id][text.lettersize][0] != 0.0 || Textler[id][text.lettersize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "TextDrawLetterSize(%s, %.3f, %.3f);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.lettersize][0], Textler[id][text.lettersize][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.textsize][0] != 0.0 || Textler[id][text.textsize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "TextDrawTextSize(%s, %.3f, %.3f);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.textsize][0], Textler[id][text.textsize][1]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "TextDrawAlignment(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.alignment]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawColor(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.color]);
                fwrite(dosya, sz);

                if(Textler[id][text.usebox] == 1)
                {
                    format(sz, sizeof(sz), "TextDrawUseBox(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.usebox]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "TextDrawBoxColor(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.boxcolor]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "TextDrawSetShadow(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.shadow]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawSetOutline(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.outline]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawBackgroundColor(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.bgcolor]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawFont(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.font]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "TextDrawSetProportional(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.proportional]);
                fwrite(dosya, sz);

                if(Textler[id][text.font] == TEXT_DRAW_FONT_MODEL_PREVIEW)
                {
                    format(sz, sizeof(sz), "TextDrawSetPreviewModel(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.preview_model]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "TextDrawSetPreviewRot(%s, %.3f, %.3f, %.3f, %.3f);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.preview_rot][0], Textler[id][text.preview_rot][1], Textler[id][text.preview_rot][2], Textler[id][text.preview_rot][3]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "TextDrawSetPreviewVehCol(%s, %d, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.preview_vc][0], Textler[id][text.preview_vc][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.selectable] == 1)
                {
                    format(sz, sizeof(sz), "TextDrawSetSelectable(%s, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.selectable]);
                    fwrite(dosya, sz);
                }

                fwrite(dosya, "\r\n");
            }
        }
    }

    // Değişken Player
    if(dp)
    {
        if(dp) fwrite(dosya, "####################################################################################################\r\n\r\n");
        foreach(new id : Text_List)
        {
            if(Textler[id][text.globaplayer] == 1 && strlen(Textler[id][text.degiskenAdi]))
            {
                format(sz, sizeof(sz), "new PlayerText: %s[MAX_PLAYERS];\r\n", Textler[id][text.degiskenAdi]);
                fwrite(dosya, sz);
            }
        }
        fwrite(dosya, "\r\n");
        foreach(new id : Text_List)
        {
            if(Textler[id][text.globaplayer] == 1 && strlen(Textler[id][text.degiskenAdi]))
            {
                format(sz, sizeof(sz), "%s[playerid] = CreatePlayerTextDraw(playerid, %.3f, %.3f, \"%s\");\r\n", Textler[id][text.degiskenAdi], Textler[id][text.pos][0], Textler[id][text.pos][1], Textler[id][text.string]);
                fwrite(dosya, sz);
                
                if(Textler[id][text.lettersize][0] != 0.0 || Textler[id][text.lettersize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawLetterSize(playerid, %s[playerid], %.3f, %.3f);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.lettersize][0], Textler[id][text.lettersize][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.textsize][0] != 0.0 || Textler[id][text.textsize][1] != 0.0)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawTextSize(playerid, %s[playerid], %.3f, %.3f);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.textsize][0], Textler[id][text.textsize][1]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "PlayerTextDrawAlignment(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.alignment]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawColor(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.color]);
                fwrite(dosya, sz);

                if(Textler[id][text.usebox] == 1)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawUseBox(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.usebox]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "PlayerTextDrawBoxColor(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.boxcolor]);
                    fwrite(dosya, sz);
                }

                format(sz, sizeof(sz), "PlayerTextDrawSetShadow(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.shadow]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawSetOutline(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.outline]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawBackgroundColor(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.bgcolor]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawFont(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.font]);
                fwrite(dosya, sz);

                format(sz, sizeof(sz), "PlayerTextDrawSetProportional(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.proportional]);
                fwrite(dosya, sz);

                if(Textler[id][text.font] == TEXT_DRAW_FONT_MODEL_PREVIEW)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawSetPreviewModel(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.preview_model]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "PlayerTextDrawSetPreviewRot(playerid, %s[playerid], %.3f, %.3f, %.3f, %.3f);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.preview_rot][0], Textler[id][text.preview_rot][1], Textler[id][text.preview_rot][2], Textler[id][text.preview_rot][3]);
                    fwrite(dosya, sz);

                    format(sz, sizeof(sz), "PlayerTextDrawSetPreviewVehCol(playerid, %s[playerid], %d, %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.preview_vc][0], Textler[id][text.preview_vc][1]);
                    fwrite(dosya, sz);
                }

                if(Textler[id][text.selectable] == 1)
                {
                    format(sz, sizeof(sz), "PlayerTextDrawSetSelectable(playerid, %s[playerid], %d);\r\n", Textler[id][text.degiskenAdi], Textler[id][text.selectable]);
                    fwrite(dosya, sz);
                }

                fwrite(dosya, "\r\n");
            }
        }
    }

    fclose(dosya);

    Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[da_bilgi]), dosya_adi, g, p, (g + p));

    Mouse(playerid, true, TEXTMOD_NORMAL);
    return 1;
}


/***
 *    8888888b.                   d8b                   d8b      888    d8P                             888    
 *    888   Y88b                  Y8P                   Y8P      888   d8P                              888    
 *    888    888                                                 888  d8P                               888    
 *    888   d88P 888d888 .d88b.  8888  .d88b.  888  888 888      888d88K      8888b.  88888b.   8888b.  888888 
 *    8888888P"  888P"  d88""88b "888 d8P  Y8b 888  888 888      8888888b        "88b 888 "88b     "88b 888    
 *    888        888    888  888  888 88888888 888  888 888      888  Y88b   .d888888 888  888 .d888888 888    
 *    888        888    Y88..88P  888 Y8b.     Y88b 888 888      888   Y88b  888  888 888 d88P 888  888 Y88b.  
 *    888        888     "Y88P"   888  "Y8888   "Y88888 888      888    Y88b "Y888888 88888P"  "Y888888  "Y888 
 *                                888               888                               888                      
 *                               d88P          Y8b d88P                               888                      
 *                             888P"            "Y88P"                                888                      
 */

Projeyi_Kapat(playerid)
{
    if(proje_durum == false) return Mesaj_Hata(playerid, Dil_Mesaji[pk_hata]), Proje_Menu(playerid);

    Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[pk_bilgi]), proje_adi);

    if(proje_db != DB: 0) db_close(proje_db), proje_db = DB: 0;

    proje_durum = false, proje_adi[0] = '\0';

    // Default:
    gIndex = -1;
    Text_Hud_Y = 413.0;
    Text_Global = "Text_Global";
    Text_Player = "Text_Player";
    SetPlayerTime(playerid, proje_saat = 12, 00);
    //
    
    // Textleri kapat
    static const reset[textdraw_yapilandirmasi];
    foreach(new id : Text_List)
    {
        if(Textler[id][text.id] != Text: -1)
        {
            TextDrawDestroy(Textler[id][text.id]);
            Textler[id] = reset;
            Textler[id][text.id] = Text: -1;
        }
    }
    Iter_Clear(Text_List);

    Hud_Render(true), Hud_Goster(true);

    Proje_Menu(playerid);
    return 1;
}