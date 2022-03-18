
/***
 *     .d88888b.                           888    d8b 
 *    d88P" "Y88b                          888    Y8P 
 *    888     888                          888        
 *    888     888 888d888 8888b.  88888b.  888888 888 
 *    888     888 888P"      "88b 888 "88b 888    888 
 *    888     888 888    .d888888 888  888 888    888 
 *    Y88b. .d88P 888    888  888 888  888 Y88b.  888 
 *     "Y88888P"  888    "Y888888 888  888  "Y888 888 
 *
 */

Oranti()
{
    gIleri_Ekle(gIndex);
    Textler[gIndex][text.proportional] = (Textler[gIndex][text.proportional] == 0) ? (1) : (0);
    DB_Guncelle(gIndex);
    Textdraw_Render(gIndex, true), Hud_Render(true), Hud_Goster(true);
    return 1;
}