
/***
 *    8888888b.                    d8b          888                        888                                   88888888888                888        888                               
 *    888  "Y88b                   Y8P          888                        888                                       888                    888        888                               
 *    888    888                                888                        888                                       888                    888        888                               
 *    888    888  .d88b.   .d88b.  888 .d8888b  888  888  .d88b.  88888b.  888  .d88b.  888d888                      888   .d88b.  888  888 888888 .d88888 888d888 8888b.  888  888  888 
 *    888    888 d8P  Y8b d88P"88b 888 88K      888 .88P d8P  Y8b 888 "88b 888 d8P  Y8b 888P"                        888  d8P  Y8b `Y8bd8P' 888   d88" 888 888P"      "88b 888  888  888 
 *    888    888 88888888 888  888 888 "Y8888b. 888888K  88888888 888  888 888 88888888 888          888888          888  88888888   X88K   888   888  888 888    .d888888 888  888  888 
 *    888  .d88P Y8b.     Y88b 888 888      X88 888 "88b Y8b.     888  888 888 Y8b.     888                          888  Y8b.     .d8""8b. Y88b. Y88b 888 888    888  888 Y88b 888 d88P 
 *    8888888P"   "Y8888   "Y88888 888  88888P' 888  888  "Y8888  888  888 888  "Y8888  888                          888   "Y8888  888  888  "Y888 "Y88888 888    "Y888888  "Y8888888P"  
 *                             888                                                                                                                                                       
 *                        Y8b d88P                                                                                                                                                       
 *                         "Y88P"                                                                                                                                                        
 */

#define     MAX_TEXT_LIMIT      2048
#define     MAX_TEXT_STRING     128
#define     MAX_GPLAYER_ISIM    30
#define     text.               Qtext_

enum textdraw_yapilandirmasi
{
    Text:text.id,
    text.string[MAX_TEXT_STRING],
    Float:text.pos[2],
    Float:text.lettersize[2],
    Float:text.textsize[2],
    text.alignment,
    text.color,
    text.usebox,
    text.boxcolor,
    text.shadow,
    text.outline,
    text.bgcolor,
    text.font,
    text.proportional,
    text.selectable,
    text.preview_model,
    Float:text.preview_rot[4],
    text.preview_vc[2],
    text.globaplayer,
    text.degiskenAdi[MAX_GPLAYER_ISIM],
    text.grup,
    text.grup_temp
};

new Textler[MAX_TEXT_LIMIT][textdraw_yapilandirmasi], Iterator: Text_List<MAX_TEXT_LIMIT>;
new Textler_TMP[textdraw_yapilandirmasi];

// Yeniden Sıralama
new TextRowShift[MAX_TEXT_LIMIT][textdraw_yapilandirmasi];

//
new
    // Export alınırken değişken isimleri
    Text_Global[MAX_GPLAYER_ISIM] = "Text_Global",
    Text_Player[MAX_GPLAYER_ISIM] = "Text_Player"
;