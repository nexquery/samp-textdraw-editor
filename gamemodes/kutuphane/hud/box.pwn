/***
 *    888888b.                     
 *    888  "88b                    
 *    888  .88P                    
 *    8888888K.   .d88b.  888  888 
 *    888  "Y88b d88""88b `Y8bd8P' 
 *    888    888 888  888   X88K   
 *    888   d88P Y88..88P .d8""8b. 
 *    8888888P"   "Y88P"  888  888 
 *
 */

Box()
{
    gIleri_Ekle(gIndex);
    Textler[gIndex][text.usebox] = (Textler[gIndex][text.usebox] == 0) ? (1) : (0);
    DB_Guncelle(gIndex);
    Textdraw_Render(gIndex, true);
    Hud_Render(true), Hud_Goster(true);
    return 1;
}