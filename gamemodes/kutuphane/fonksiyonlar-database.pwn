new pSz[2048];

DB_Ekle(id)
{
    pSz[0] = '\0';
    format(pSz, sizeof(pSz), "INSERT INTO textdrawlar (id, icerik, posX, posY, lettersizeX, lettersizeY, textsizeX, textsizeY, alignment, color, usebox, boxcolor, shadow, outline, bgcolor, font, proportional, selectable, previewModel, previewX, previewY, previewZ, previewZoom, previewVC1, previewVC2, globalPlayer, degiskenadi, grup) VALUES ('%d', '%q', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%.3f', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%.3f', '%.3f', '%.3f', '%.3f', '%d', '%d', '%d', '%q', '%d')"
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
    db_free_result(db_query(proje_db, pSz));
    return 1;
}

DB_Guncelle(id)
{
    pSz[0] = '\0';
    format(pSz, sizeof(pSz), "UPDATE textdrawlar SET icerik = '%q', posX = '%.3f', posY = '%.3f', lettersizeX = '%.3f', lettersizeY = '%.3f', textsizeX = '%.3f', textsizeY = '%.3f', alignment = '%d', color = '%d', usebox = '%d', boxcolor = '%d', shadow = '%d', outline = '%d', bgcolor = '%d', font = '%d', proportional = '%d', selectable = '%d', previewModel = '%d', previewX = '%.3f', previewY = '%.3f', previewZ = '%.3f', previewZoom = '%.3f', previewVC1 = '%d', previewVC2 = '%d', globalPlayer = '%d', degiskenadi = '%q', grup = '%d' WHERE id = '%d'"
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
        Textler[id][text.grup],
        id
    );
    db_free_result(db_query(proje_db, pSz));
    return 1;
}

DB_Sil(id)
{
    pSz[0] = '\0';
    format(pSz, sizeof(pSz), "DELETE FROM textdrawlar WHERE id = '%d'", id);
    db_free_result(db_query(proje_db, pSz));
    return 1;
}