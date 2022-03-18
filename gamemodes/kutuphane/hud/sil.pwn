
/***
 *     .d8888b.  d8b 888 
 *    d88P  Y88b Y8P 888 
 *    Y88b.          888 
 *     "Y888b.   888 888 
 *        "Y88b. 888 888 
 *          "888 888 888 
 *    Y88b  d88P 888 888 
 *     "Y8888P"  888 888 
 *
 */

Sil(playerid)
{
    if(gIndex != -1)
    {
        new id = gIndex;

        Textler[id][text.grup]      = 0;
        Textler[id][text.grup_temp] = 0;
        
        Sil_Ekle(gIndex);
        
        Textdraw_List_Sil(id); // otomatik id alıcak

        DB_Sil(id);
        
        gIleri_Sil(id);
        
        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[sil_bilgi]), id);
        
        Hud_Render(true), Hud_Goster(true);
    }
    return 1;
}