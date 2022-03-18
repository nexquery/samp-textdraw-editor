/***
 *     .d8888b.                            888                                 
 *    d88P  Y88b                           888                                 
 *    888    888                           888                                 
 *    888        888d888 888  888 88888b.  888  8888b.  88888b.d88b.   8888b.  
 *    888  88888 888P"   888  888 888 "88b 888     "88b 888 "888 "88b     "88b 
 *    888    888 888     888  888 888  888 888 .d888888 888  888  888 .d888888 
 *    Y88b  d88P 888     Y88b 888 888 d88P 888 888  888 888  888  888 888  888 
 *     "Y8888P88 888      "Y88888 88888P"  888 "Y888888 888  888  888 "Y888888 
 *                                888                                          
 *                                888                                          
 *                                888                                          
 */

#define     MAX_GRUP_OGE_ICERIK      15

new
    // Dialog menüsü için
    gBuffer[4096],

    // Grup sayfası
    grup_Sayfa,

    // Gruplanacak öğelerin id değerleri
    grup_Id[MAX_GRUP_OGE_ICERIK],

    // Offset
    Float: pozisyon_Offset[2],

    // Timer
    Timer_gKonum = -1,
    Timer_gTextsize_Normal = -1,

    // Textsize
    gTextsize_Mod,

    // Renk Modu
    gRenkModu
;