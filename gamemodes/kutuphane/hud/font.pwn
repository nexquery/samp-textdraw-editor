/***
 *    8888888888                888    
 *    888                       888    
 *    888                       888    
 *    8888888  .d88b.  88888b.  888888 
 *    888     d88""88b 888 "88b 888    
 *    888     888  888 888  888 888    
 *    888     Y88..88P 888  888 Y88b.  
 *    888      "Y88P"  888  888  "Y888 
 *
 */

Font()
{
    gIleri_Ekle(gIndex);
    Textler[gIndex][text.font] = (Textler[gIndex][text.font] >= 3) ? (0) : (Textler[gIndex][text.font] + 1);
    DB_Guncelle(gIndex);
    Textdraw_Render(gIndex, true), Hud_Render(true), Hud_Goster(true);
    return 1;
}