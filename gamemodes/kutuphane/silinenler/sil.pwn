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

Sil_Menu(playerid)
{
    new
        DBResult: cache = db_query(proje_db, fex("SELECT *, (SELECT COUNT(*) FROM silinenler) AS total FROM silinenler ORDER BY id DESC LIMIT %d, %d", (silinenler_Sayfa * MAX_SILINENLER), MAX_SILINENLER)),
        rows = db_num_rows(cache),
        buffer[2000],
        index,
        pIcerik[30],
        pFont,
        pGlobalPlayer,
        pTarih
    ;

    format(buffer, sizeof(buffer), "%s%s\t%s\t%s\t%s\n", buffer, Dil_Mesaji[s_header1], Dil_Mesaji[s_header2], Dil_Mesaji[s_header3], Dil_Mesaji[s_header4]);
    format(buffer, sizeof(buffer), "%s>>\t\t\t\n", buffer);
    format(buffer, sizeof(buffer), "%s<<\t\t\t\n", buffer);
    format(buffer, sizeof(buffer), "%s%s\t\t\t\n", buffer, Dil_Mesaji[s_icerik1]);
    format(buffer, sizeof(buffer), "%s%s\t\t\t\n", buffer, Dil_Mesaji[s_icerik2]);
    format(buffer, sizeof(buffer), "%s%s\t\t\t\n", buffer, Dil_Mesaji[s_icerik3]);
    format(buffer, sizeof(buffer), "%s  \t\t\t\n", buffer);

    if(rows)
    {
        do
        {
            silinenler_Id[index]    = db_get_field_assoc_int(cache, "id");
            db_get_field_assoc(cache, "icerik", pIcerik, 30);
            pFont                   = db_get_field_assoc_int(cache, "font");
            pGlobalPlayer           = db_get_field_assoc_int(cache, "globalPlayer");
            pTarih                  = db_get_field_assoc_int(cache, "tarih");
            silinenler_Total        = db_get_field_assoc_int(cache, "total");
            format(buffer, sizeof(buffer), "%s%.20s%s\t%s\t%s\t%s\n"
            ,
                buffer,
                pIcerik,
                (strlen(pIcerik) > 20) ? ("...") : (""),
                Sil_Font_Isim(pFont),
                (pGlobalPlayer == 0) ? ("Global") : ("Player"),
                Tarih_Cek(pTarih)
            );
            index++;
        }
        while(db_next_row(cache));
        Dialog_Show(playerid, SILINENLER, DIALOG_STYLE_TABLIST_HEADERS, fex(fmt(Dil_Mesaji[s_baslik]), (silinenler_Sayfa + 1), Max_Page(silinenler_Total, MAX_SILINENLER)), buffer, Dil_Mesaji[s_buton1], Dil_Mesaji[s_buton2]);
    }
    else
    {
        Mesaj_Hata(playerid, Dil_Mesaji[s_hata]), Depo_Menu(playerid);
    }
    db_free_result(cache);
    return 1;
}

Dialog:SILINENLER(playerid, response, listitem, inputtext[])
{
    if(!response) return Depo_Menu(playerid);
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(silinenler_Sayfa++ >= (Max_Page(silinenler_Total, MAX_SILINENLER) - 1))
                {
                    silinenler_Sayfa = (Max_Page(silinenler_Total, MAX_SILINENLER) - 1);
                }
                Sil_Menu(playerid);
            }

            case 1:
            {
                if(silinenler_Sayfa-- <= 0)
                {
                    silinenler_Sayfa = 0;
                }
                Sil_Menu(playerid);
            }

            // Sayfaya git
            case 2: Sayfa_Menu(playerid, SAYFA_SILINENLER);

            // Tüm verileri temizle
            case 3: Sil_Temizle_Onay(playerid);

            // Tüm verileri geri yükle
            case 4: Sil_GeriYukle_Onay(playerid);

            // Boşluk
            case 5: Sil_Menu(playerid);

            // Tıklanan
            default: Sil_Textdraw_Geri_Yukle(playerid, silinenler_Id[listitem - 6]);
        }
    }
    return 1;
}


/***
 *    88888888888                     d8b          888          
 *        888                         Y8P          888          
 *        888                                      888          
 *        888   .d88b.  88888b.d88b.  888 88888888 888  .d88b.  
 *        888  d8P  Y8b 888 "888 "88b 888    d88P  888 d8P  Y8b 
 *        888  88888888 888  888  888 888   d88P   888 88888888 
 *        888  Y8b.     888  888  888 888  d88P    888 Y8b.     
 *        888   "Y8888  888  888  888 888 88888888 888  "Y8888  
 *
 */

Sil_Temizle_Onay(playerid)
{
    Dialog_Show(playerid, SIL_TEMIZLE_ONAY, DIALOG_STYLE_MSGBOX, Dil_Mesaji[st_baslik], "%s\n%s", Dil_Mesaji[st_buton1], Dil_Mesaji[st_buton2],
    Dil_Mesaji[st_icerik1], Dil_Mesaji[st_icerik2]);
    return 1;
}

Dialog:SIL_TEMIZLE_ONAY(playerid, response, listitem, inputtext[])
{
    if(!response) return Sil_Menu(playerid);
    if(response)
    {
        db_free_result(db_query(proje_db, "DELETE FROM silinenler"));

        silinenler_Sayfa = 0;

        ChatTemizle();

        Mesaj_Bilgi(playerid, Dil_Mesaji[st_bilgi]);

        Depo_Menu(playerid);
    }
    return 1;
}


/***
 *    888    888                            d8b          d8b       .d8888b.                   d8b      Y88b   d88P        888      888          
 *    888    888                            Y8P          Y8P      d88P  Y88b                  Y8P       Y88b d88P         888      888          
 *    888    888                                                  888    888                             Y88o88P          888      888          
 *    8888888888  .d88b.  88888b.  .d8888b  888 88888b.  888      888         .d88b.  888d888 888         Y888P  888  888 888  888 888  .d88b.  
 *    888    888 d8P  Y8b 888 "88b 88K      888 888 "88b 888      888  88888 d8P  Y8b 888P"   888          888   888  888 888 .88P 888 d8P  Y8b 
 *    888    888 88888888 888  888 "Y8888b. 888 888  888 888      888    888 88888888 888     888          888   888  888 888888K  888 88888888 
 *    888    888 Y8b.     888 d88P      X88 888 888  888 888      Y88b  d88P Y8b.     888     888          888   Y88b 888 888 "88b 888 Y8b.     
 *    888    888  "Y8888  88888P"   88888P' 888 888  888 888       "Y8888P88  "Y8888  888     888          888    "Y88888 888  888 888  "Y8888  
 *                        888                                                                                                                   
 *                        888                                                                                                                   
 *                        888                                                                                                                   
 */

Sil_GeriYukle_Onay(playerid)
{
    Dialog_Show(playerid, SIL_TUMUNU_GERI_YUKLE, DIALOG_STYLE_MSGBOX, Dil_Mesaji[stgy_baslik], Dil_Mesaji[stgy_icerik1], Dil_Mesaji[stgy_buton1], Dil_Mesaji[stgy_buton2]);
    return 1;
}

Dialog:SIL_TUMUNU_GERI_YUKLE(playerid, response, listitem, inputtext[])
{
    if(!response) return Sil_Menu(playerid);
    if(response)
    {
        Sil_Textdraw_Hepsini_Geri_Yukle(playerid);
    }
    return 1;
}