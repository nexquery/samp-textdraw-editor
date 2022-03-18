
/***
 *    888    888               888 
 *    888    888               888 
 *    888    888               888 
 *    8888888888 888  888  .d88888 
 *    888    888 888  888 d88" 888 
 *    888    888 888  888 888  888 
 *    888    888 Y88b 888 Y88b 888 
 *    888    888  "Y88888  "Y88888 
 *                                       
 */

enum hud_yapilandirmasi
{
    Text:hindex,
    Float:hud_pos[2],
    Float:hud_textsize[2],
    hud_color,
    hud_selectable,
    hud_string[32]
};

new
    // Default hud konum
    Float: Text_Hud_Y = 413.0,

    // Alt hud barı
    Text_Hud[25][hud_yapilandirmasi],

    // Bilgi Text
    Text: Bilgi_Text = Text: -1,
    bilgiText_tickCount
;