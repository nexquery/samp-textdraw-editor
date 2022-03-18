/***
 *    888     888               888               8888888b.               888          
 *    888     888               888               888   Y88b              888          
 *    888     888               888               888    888              888          
 *    888     888 88888b.   .d88888  .d88b.       888   d88P .d88b.   .d88888  .d88b.  
 *    888     888 888 "88b d88" 888 d88""88b      8888888P" d8P  Y8b d88" 888 d88""88b 
 *    888     888 888  888 888  888 888  888      888 T88b  88888888 888  888 888  888 
 *    Y88b. .d88P 888  888 Y88b 888 Y88..88P      888  T88b Y8b.     Y88b 888 Y88..88P 
 *     "Y88888P"  888  888  "Y88888  "Y88P"       888   T88b "Y8888   "Y88888  "Y88P"  
 *                                                                                     
 *                                                                                     
 *                                                                                     
 */

new gSz[2048];

gIleri_Total(id)
{
    new DBResult: cache = db_query(proje_db, fex("SELECT COUNT(*) AS total FROM gerial WHERE id = %d", id)), rows = db_num_rows(cache), total;
    if(rows)
    {
        total = db_get_field_assoc_int(cache, "total");
    }
    db_free_result(cache);
    return total;
}

gIleri_Ekle(id)
{
    // Eğer maksimum veri sınırına ulaşıldıysa en eski değeri sil ve yeni değeri yaz
    if(gIleri_Total(id) == MAX_UNDO_REDO)
    {
        new
            DBResult: cache = db_query(proje_db, fex("SELECT sid FROM gerial WHERE id = %d ORDER BY sid", id)),
            rows = db_num_rows(cache),
            sid
        ;
        if(rows)
        {
            sid = db_get_field_assoc_int(cache,  "sid");
            db_free_result(db_query(proje_db, fex("DELETE FROM gerial WHERE sid = %d", sid)));
        }
        db_free_result(cache);
    }

    // Yeni veriyi ekle
    gSz[0] = '\0';
    format(gSz, sizeof(gSz), "INSERT INTO gerial (id, icerik, posX, posY, lettersizeX, lettersizeY, textsizeX, textsizeY, alignment, color, usebox, boxcolor, shadow, outline, bgcolor, font, proportional, selectable, previewModel, previewX, previewY, previewZ, previewZoom, previewVC1, previewVC2, globalPlayer, degiskenadi, grup) VALUES ('%d', '%q', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%.3f', '%.3f', '%.3f', '%.3f', '%d', '%d', '%d', '%q', '%d')"
    ,
        id,
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
        Textler[id][text.grup]
    );
    db_free_result(db_query(proje_db, gSz));
    return 1;
}

gIleri_Sil(id)
{
    db_free_result(db_query(proje_db, fex("DELETE FROM gerial WHERE id = %d", id)));
    return 1;
}

gIleri_Yukle(id)
{
    uRedo_Total = 0;
    new index = 0;
    new DBResult: cache = db_query(proje_db, fex("SELECT * FROM gerial WHERE id = %d ORDER BY sid DESC", id)), rows = db_num_rows(cache);
    if(rows)
    {
        do
        {
            uRedo_SID[index]                        = db_get_field_assoc_int(cache,  "sid");
            uRedo[index][text.id]                   = Textler[gIndex][text.id];
            db_get_field_assoc(cache, "icerik", uRedo[index][text.string], MAX_TEXT_STRING);
            uRedo[index][text.pos][0]               = db_get_field_assoc_float(cache,  "posX");
            uRedo[index][text.pos][1]               = db_get_field_assoc_float(cache,  "posY");
            uRedo[index][text.lettersize][0]        = db_get_field_assoc_float(cache,  "lettersizeX");
            uRedo[index][text.lettersize][1]        = db_get_field_assoc_float(cache,  "lettersizeY");
            uRedo[index][text.textsize][0]          = db_get_field_assoc_float(cache,  "textsizeX");
            uRedo[index][text.textsize][1]          = db_get_field_assoc_float(cache,  "textsizeY");
            uRedo[index][text.alignment]            = db_get_field_assoc_int(cache,    "alignment");
            uRedo[index][text.color]                = db_get_field_assoc_int(cache,    "color");
            uRedo[index][text.usebox]               = db_get_field_assoc_int(cache,    "usebox");
            uRedo[index][text.boxcolor]             = db_get_field_assoc_int(cache,    "boxcolor");
            uRedo[index][text.shadow]               = db_get_field_assoc_int(cache,    "shadow");
            uRedo[index][text.outline]              = db_get_field_assoc_int(cache,    "outline");
            uRedo[index][text.bgcolor]              = db_get_field_assoc_int(cache,    "bgcolor");
            uRedo[index][text.font]                 = db_get_field_assoc_int(cache,    "font");
            uRedo[index][text.proportional]         = db_get_field_assoc_int(cache,    "proportional");
            uRedo[index][text.selectable]           = db_get_field_assoc_int(cache,    "selectable");
            uRedo[index][text.preview_model]        = db_get_field_assoc_int(cache,    "previewModel");
            uRedo[index][text.preview_rot][0]       = db_get_field_assoc_float(cache,  "previewX");
            uRedo[index][text.preview_rot][1]       = db_get_field_assoc_float(cache,  "previewY");
            uRedo[index][text.preview_rot][2]       = db_get_field_assoc_float(cache,  "previewZ");
            uRedo[index][text.preview_rot][3]       = db_get_field_assoc_float(cache,  "previewZoom");
            uRedo[index][text.preview_vc][0]        = db_get_field_assoc_int(cache,    "previewVC1");
            uRedo[index][text.preview_vc][1]        = db_get_field_assoc_int(cache,    "previewVC2");
            uRedo[index][text.globaplayer]          = db_get_field_assoc_int(cache,    "globalPlayer");
            db_get_field_assoc(cache, "degiskenadi", uRedo[index][text.degiskenAdi], MAX_GPLAYER_ISIM);
            uRedo[index][text.grup]                 = 0; // Varsayılan 0 olarak ayarla <db_get_field_assoc_int(cache,    "grup");>
            index++;
            uRedo_Total++;
        }
        while(db_next_row(cache));
    }
    db_free_result(cache);
    return 1;
}