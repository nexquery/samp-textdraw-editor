
/***
 *    8888888b.                    d8b          888                        888                                    .d88888b.                                               
 *    888  "Y88b                   Y8P          888                        888                                   d88P" "Y88b                                              
 *    888    888                                888                        888                                   888     888                                              
 *    888    888  .d88b.   .d88b.  888 .d8888b  888  888  .d88b.  88888b.  888  .d88b.  888d888                  888     888 888  888 888  888 88888b.   .d8888b 888  888 
 *    888    888 d8P  Y8b d88P"88b 888 88K      888 .88P d8P  Y8b 888 "88b 888 d8P  Y8b 888P"                    888     888 888  888 888  888 888 "88b d88P"    888  888 
 *    888    888 88888888 888  888 888 "Y8888b. 888888K  88888888 888  888 888 88888888 888          888888      888     888 888  888 888  888 888  888 888      888  888 
 *    888  .d88P Y8b.     Y88b 888 888      X88 888 "88b Y8b.     888  888 888 Y8b.     888                      Y88b. .d88P Y88b 888 Y88b 888 888  888 Y88b.    Y88b 888 
 *    8888888P"   "Y8888   "Y88888 888  88888P' 888  888  "Y8888  888  888 888  "Y8888  888                       "Y88888P"   "Y88888  "Y88888 888  888  "Y8888P  "Y88888 
 *                             888                                                                                                888                                     
 *                        Y8b d88P                                                                                           Y8b d88P                                     
 *                         "Y88P"                                                                                             "Y88P"                                      
 */

enum
{
    TEXTMOD_YOK,
    TEXTMOD_NORMAL,
    TEXTMOD_SPRITE,
};

new
    // Geçerli textdraw indexi (array)
    gIndex = -1,

    // Textdrawa tıklayıp işlem gerçekleştirirse
    TextMod = TEXTMOD_NORMAL,

    // Proje listesi
    projeler_sayfa = 0,
    projeler_total,
    projeler_listitem,
    projeler_listesi[PROJE_MAX_ICERIK][PROJE_MAX_ISIM + 1],

    // Hud Liste
    liste_Sayfa = 1,
    liste_Sayfa_Arr[HUD_LISTE_ICERIK],
    liste_Listitem,

    // Hud taşıma
    hud_tasima_timer = -1,
    bool: hud_tasima_modu = false,

    // Konum, Textsize, Lettersize
    timer_konum = -1,
    timer_textsize = -1,
    timer_lettersize = -1,

    // Outline, Shadow
    timer_outline = -1,
    timer_shadow = -1,

    // RGBA
    timer_rgba = -1,
    rgba_index = 0,
    rgba_time,

    // Preview Models
    timer_pModels = -1,
    index_pModels,

    // Geri İleri
    timer_undo = -1,

    // Textdrawı seç
    timer_textdraw_sec = -1,

    // Mouse
    bool: pMouse = false,

    // Index Değiştirme
    timer_IndexDegistir = -1,
    textdraw_swap_index = -1,
    textdraw_swap_index_tmp = -1
;