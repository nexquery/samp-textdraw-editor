/***
 *     .d8888b.           888                   888             888      888          
 *    d88P  Y88b          888                   888             888      888          
 *    Y88b.               888                   888             888      888          
 *     "Y888b.    .d88b.  888  .d88b.   .d8888b 888888  8888b.  88888b.  888  .d88b.  
 *        "Y88b. d8P  Y8b 888 d8P  Y8b d88P"    888        "88b 888 "88b 888 d8P  Y8b 
 *          "888 88888888 888 88888888 888      888    .d888888 888  888 888 88888888 
 *    Y88b  d88P Y8b.     888 Y8b.     Y88b.    Y88b.  888  888 888 d88P 888 Y8b.     
 *     "Y8888P"   "Y8888  888  "Y8888   "Y8888P  "Y888 "Y888888 88888P"  888  "Y8888  
 *
 */

Selectable()
{
    gIleri_Ekle(gIndex);
    Textler[gIndex][text.selectable] = (Textler[gIndex][text.selectable] == 0) ? (1) : (0);
    DB_Guncelle(gIndex);
    Hud_Render(true), Hud_Goster(true);
    return 1;
}