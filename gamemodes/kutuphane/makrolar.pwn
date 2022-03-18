
/***
 *    888b     d888          888                      888                  
 *    8888b   d8888          888                      888                  
 *    88888b.d88888          888                      888                  
 *    888Y88888P888  8888b.  888  888 888d888 .d88b.  888  8888b.  888d888 
 *    888 Y888P 888     "88b 888 .88P 888P"  d88""88b 888     "88b 888P"   
 *    888  Y8P  888 .d888888 888888K  888    888  888 888 .d888888 888     
 *    888   "   888 888  888 888 "88b 888    Y88..88P 888 888  888 888     
 *    888       888 "Y888888 888  888 888     "Y88P"  888 "Y888888 888     
 *                                                                         
 */

// Tuşa ilk bastığında algılama
#define PRESSED(%0)             (((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

// sprintf yapısını fex'e dönüştür
#define     fex                 sprintf

// Chat temizle
#define     ChatTemizle();      for(new i = 0; i < 50; i++) { SendClientMessageToAll(-1, " "); }