/***
 *     .d8888b.  888          888               888                  8888888b.  888                                    
 *    d88P  Y88b 888          888               888                  888   Y88b 888                                    
 *    888    888 888          888               888                  888    888 888                                    
 *    888        888  .d88b.  88888b.   8888b.  888                  888   d88P 888  8888b.  888  888  .d88b.  888d888 
 *    888  88888 888 d88""88b 888 "88b     "88b 888                  8888888P"  888     "88b 888  888 d8P  Y8b 888P"   
 *    888    888 888 888  888 888  888 .d888888 888      888888      888        888 .d888888 888  888 88888888 888     
 *    Y88b  d88P 888 Y88..88P 888 d88P 888  888 888                  888        888 888  888 Y88b 888 Y8b.     888     
 *     "Y8888P88 888  "Y88P"  88888P"  "Y888888 888                  888        888 "Y888888  "Y88888  "Y8888  888     
 *                                                                                                888                  
 *                                                                                           Y8b d88P                  
 *                                                                                            "Y88P"                   
 */

Global_Player()
{
    gIleri_Ekle(gIndex);
    Textler[gIndex][text.globaplayer] = (Textler[gIndex][text.globaplayer] == 0) ? (1) : (0);
    DB_Guncelle(gIndex);
    Hud_Render(true), Hud_Goster(true);
    return 1;
}