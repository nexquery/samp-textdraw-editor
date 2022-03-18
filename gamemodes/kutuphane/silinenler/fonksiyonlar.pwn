/***
 *     .d8888b.  d8b 888 d8b                            888                  
 *    d88P  Y88b Y8P 888 Y8P                            888                  
 *    Y88b.          888                                888                  
 *     "Y888b.   888 888 888 88888b.   .d88b.  88888b.  888  .d88b.  888d888 
 *        "Y88b. 888 888 888 888 "88b d8P  Y8b 888 "88b 888 d8P  Y8b 888P"   
 *          "888 888 888 888 888  888 88888888 888  888 888 88888888 888     
 *    Y88b  d88P 888 888 888 888  888 Y8b.     888  888 888 Y8b.     888     
 *     "Y8888P"  888 888 888 888  888  "Y8888  888  888 888  "Y8888  888     
 *                                                                           
 *                                                                           
 *                                                                           
 */

Sil_Ekle(id)
{
    gSz[0] = '\0';
    format(gSz, sizeof(gSz), "INSERT INTO silinenler (icerik, posX, posY, lettersizeX, lettersizeY, textsizeX, textsizeY, alignment, color, usebox, boxcolor, shadow, outline, bgcolor, font, proportional, selectable, previewModel, previewX, previewY, previewZ, previewZoom, previewVC1, previewVC2, globalPlayer, degiskenadi, grup, tarih) VALUES ('%q', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%.3f', '%.3f', '%.3f', '%.3f', '%d', '%d', '%d', '%q', '%d', '%d')"
    ,
        Textler[id][text.string],
        Textler[id][text.pos][0],
        Textler[id][text.pos][1],
        Textler[id][text.lettersize][0],
        Textler[id][text.lettersize][1],
        Textler[id][text.textsize][0],
        Textler[id][text.textsize][1],
        Textler[id][text.alignment],
        Textler[id][text.color],
        Textler[id][text.usebox],
        Textler[id][text.boxcolor],
        Textler[id][text.shadow],
        Textler[id][text.outline],
        Textler[id][text.bgcolor],
        Textler[id][text.font],
        Textler[id][text.proportional],
        Textler[id][text.selectable],
        Textler[id][text.preview_model],
        Textler[id][text.preview_rot][0],
        Textler[id][text.preview_rot][1],
        Textler[id][text.preview_rot][2],
        Textler[id][text.preview_rot][3],
        Textler[id][text.preview_vc][0],
        Textler[id][text.preview_vc][1],
        Textler[id][text.globaplayer],
        Textler[id][text.degiskenAdi],
        Textler[id][text.grup] = 0, // Varsayılan 0 olarak ayarla
        gettime()
    );
    db_free_result(db_query(proje_db, gSz));
    return 1;
}

Sil_Textdraw_Geri_Yukle(playerid, id)
{
    new index = Iter_Free(Text_List);
    new DBResult: cache = db_query(proje_db, fex("SELECT * FROM silinenler WHERE id = %d", id)), rows = db_num_rows(cache);
    if(rows)
    {
        Textler[index][text.id]                   = Text: -1;
        db_get_field_assoc(cache, "icerik", Textler[index][text.string], MAX_TEXT_STRING);
        Textler[index][text.pos][0]               = db_get_field_assoc_float(cache,  "posX");
        Textler[index][text.pos][1]               = db_get_field_assoc_float(cache,  "posY");
        Textler[index][text.lettersize][0]        = db_get_field_assoc_float(cache,  "lettersizeX");
        Textler[index][text.lettersize][1]        = db_get_field_assoc_float(cache,  "lettersizeY");
        Textler[index][text.textsize][0]          = db_get_field_assoc_float(cache,  "textsizeX");
        Textler[index][text.textsize][1]          = db_get_field_assoc_float(cache,  "textsizeY");
        Textler[index][text.alignment]            = db_get_field_assoc_int(cache,    "alignment");
        Textler[index][text.color]                = db_get_field_assoc_int(cache,    "color");
        Textler[index][text.usebox]               = db_get_field_assoc_int(cache,    "usebox");
        Textler[index][text.boxcolor]             = db_get_field_assoc_int(cache,    "boxcolor");
        Textler[index][text.shadow]               = db_get_field_assoc_int(cache,    "shadow");
        Textler[index][text.outline]              = db_get_field_assoc_int(cache,    "outline");
        Textler[index][text.bgcolor]              = db_get_field_assoc_int(cache,    "bgcolor");
        Textler[index][text.font]                 = db_get_field_assoc_int(cache,    "font");
        Textler[index][text.proportional]         = db_get_field_assoc_int(cache,    "proportional");
        Textler[index][text.selectable]           = db_get_field_assoc_int(cache,    "selectable");
        Textler[index][text.preview_model]        = db_get_field_assoc_int(cache,    "previewModel");
        Textler[index][text.preview_rot][0]       = db_get_field_assoc_float(cache,  "previewX");
        Textler[index][text.preview_rot][1]       = db_get_field_assoc_float(cache,  "previewY");
        Textler[index][text.preview_rot][2]       = db_get_field_assoc_float(cache,  "previewZ");
        Textler[index][text.preview_rot][3]       = db_get_field_assoc_float(cache,  "previewZoom");
        Textler[index][text.preview_vc][0]        = db_get_field_assoc_int(cache,    "previewVC1");
        Textler[index][text.preview_vc][1]        = db_get_field_assoc_int(cache,    "previewVC2");
        Textler[index][text.globaplayer]          = db_get_field_assoc_int(cache,    "globalPlayer");
        db_get_field_assoc(cache, "degiskenadi", Textler[index][text.degiskenAdi], MAX_GPLAYER_ISIM);
        Textler[index][text.grup]                 = 0; // // Varsayılan 0 olarak ayarla <db_get_field_assoc_int(cache,    "grup");>
    }
    db_free_result(cache);

    Iter_Add(Text_List, index);

    Sil_Kaldir(id);
    
    silinenler_Sayfa = 0;
    Sil_Menu(playerid);

    ChatTemizle();
    Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[s_bilgi]), index);

    Textdraw_Render(index, true);

    Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
    return 1;
}

Sil_Textdraw_Hepsini_Geri_Yukle(playerid)
{
    // Mod 0: Yeniden eskiye
    // Mod 1: Eskiden yeniye
    new DBResult: cache, rows, index;
    cache = db_query(proje_db, "SELECT * FROM silinenler ORDER BY id DESC"), rows = db_num_rows(cache);
    if(rows)
    {
        do
        {
            index = Iter_Free(Text_List);

            Textler[index][text.id]                   = Text: -1;
            db_get_field_assoc(cache, "icerik", Textler[index][text.string], MAX_TEXT_STRING);
            Textler[index][text.pos][0]               = db_get_field_assoc_float(cache,  "posX");
            Textler[index][text.pos][1]               = db_get_field_assoc_float(cache,  "posY");
            Textler[index][text.lettersize][0]        = db_get_field_assoc_float(cache,  "lettersizeX");
            Textler[index][text.lettersize][1]        = db_get_field_assoc_float(cache,  "lettersizeY");
            Textler[index][text.textsize][0]          = db_get_field_assoc_float(cache,  "textsizeX");
            Textler[index][text.textsize][1]          = db_get_field_assoc_float(cache,  "textsizeY");
            Textler[index][text.alignment]            = db_get_field_assoc_int(cache,    "alignment");
            Textler[index][text.color]                = db_get_field_assoc_int(cache,    "color");
            Textler[index][text.usebox]               = db_get_field_assoc_int(cache,    "usebox");
            Textler[index][text.boxcolor]             = db_get_field_assoc_int(cache,    "boxcolor");
            Textler[index][text.shadow]               = db_get_field_assoc_int(cache,    "shadow");
            Textler[index][text.outline]              = db_get_field_assoc_int(cache,    "outline");
            Textler[index][text.bgcolor]              = db_get_field_assoc_int(cache,    "bgcolor");
            Textler[index][text.font]                 = db_get_field_assoc_int(cache,    "font");
            Textler[index][text.proportional]         = db_get_field_assoc_int(cache,    "proportional");
            Textler[index][text.selectable]           = db_get_field_assoc_int(cache,    "selectable");
            Textler[index][text.preview_model]        = db_get_field_assoc_int(cache,    "previewModel");
            Textler[index][text.preview_rot][0]       = db_get_field_assoc_float(cache,  "previewX");
            Textler[index][text.preview_rot][1]       = db_get_field_assoc_float(cache,  "previewY");
            Textler[index][text.preview_rot][2]       = db_get_field_assoc_float(cache,  "previewZ");
            Textler[index][text.preview_rot][3]       = db_get_field_assoc_float(cache,  "previewZoom");
            Textler[index][text.preview_vc][0]        = db_get_field_assoc_int(cache,    "previewVC1");
            Textler[index][text.preview_vc][1]        = db_get_field_assoc_int(cache,    "previewVC2");
            Textler[index][text.globaplayer]          = db_get_field_assoc_int(cache,    "globalPlayer");
            db_get_field_assoc(cache, "degiskenadi", Textler[index][text.degiskenAdi], MAX_GPLAYER_ISIM);
            Textler[index][text.grup]                 = 0;

            Iter_Add(Text_List, index);
            Textdraw_Render(index, true);
        }
        while(db_next_row(cache));
    }
    db_free_result(cache);
    db_free_result(db_query(proje_db, "DELETE FROM silinenler"));
    silinenler_Sayfa = 0;
    ChatTemizle();
    Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[stgy_bilgi]), rows);
    Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
    return 1;
}

Sil_Kaldir(id)
{
    db_free_result(db_query(proje_db, fex("DELETE FROM silinenler WHERE id = %d", id)));
    return 1;
}

Sil_Font_Isim(font_id)
{
    new buffer[20];
    switch(font_id)
    {
        case 0..3: format(buffer, sizeof(buffer), "Normal Textdraw");
        case 4: format(buffer, sizeof(buffer), "Sprite");
        case 5: format(buffer, sizeof(buffer), "Preview Model");
    }
    return buffer;
}

Sil_Set(deger)
{
    silinenler_Sayfa = deger;
    return 1;
}

Sil_Get(&total, &rows)
{
    total = silinenler_Total;
    rows = MAX_SILINENLER;
    return 1;
}