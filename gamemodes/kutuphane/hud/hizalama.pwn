/***
 *    888    888 d8b                   888                                 
 *    888    888 Y8P                   888                                 
 *    888    888                       888                                 
 *    8888888888 888 88888888  8888b.  888  8888b.  88888b.d88b.   8888b.  
 *    888    888 888    d88P      "88b 888     "88b 888 "888 "88b     "88b 
 *    888    888 888   d88P   .d888888 888 .d888888 888  888  888 .d888888 
 *    888    888 888  d88P    888  888 888 888  888 888  888  888 888  888 
 *    888    888 888 88888888 "Y888888 888 "Y888888 888  888  888 "Y888888 
 *
 */

Hizalama()
{
    gIleri_Ekle(gIndex);
    Textler[gIndex][text.alignment] = (Textler[gIndex][text.alignment] >= 3) ? (1) : (Textler[gIndex][text.alignment] + 1);
    DB_Guncelle(gIndex);
    Textdraw_Render(gIndex, true), Hud_Render(true), Hud_Goster(true);
    return 1;
}