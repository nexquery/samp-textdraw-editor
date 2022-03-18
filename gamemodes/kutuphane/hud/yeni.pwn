
/***
 *    Y88b   d88P                d8b 
 *     Y88b d88P                 Y8P 
 *      Y88o88P                      
 *       Y888P  .d88b.  88888b.  888 
 *        888  d8P  Y8b 888 "88b 888 
 *        888  88888888 888  888 888 
 *        888  Y8b.     888  888 888 
 *        888   "Y8888  888  888 888 
 *                                   
 */

Yeni_Menu(playerid)
{
    Dialog_Show(playerid, YENI_MENU, DIALOG_STYLE_LIST, Dil_Mesaji[yeni_baslik], "\
    Normal Textdraw\n\
    Sprite Textdraw (TXD)\n\
    %s\n\
    ", Dil_Mesaji[yeni_btn1], Dil_Mesaji[yeni_btn2], Dil_Mesaji[yeni_icerik]);
    return 1;
}

Dialog:YENI_MENU(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        switch(listitem)
        {
            // Normal Textdraw
            case 0: Textdraw_Normal(), Mouse(playerid, true, TEXTMOD_NORMAL);

            // Sprite Textdraw (TXD)
            case 1: Mouse(playerid, true, TEXTMOD_SPRITE), Sprite_Menu();

            // Preview Models
            case 2: Textdraw_PreviewModels(), Mouse(playerid, true, TEXTMOD_NORMAL);
        }
    }
    return 1;
}


/***
 *    888b    888                                         888      88888888888                888        888                               
 *    8888b   888                                         888          888                    888        888                               
 *    88888b  888                                         888          888                    888        888                               
 *    888Y88b 888  .d88b.  888d888 88888b.d88b.   8888b.  888          888   .d88b.  888  888 888888 .d88888 888d888 8888b.  888  888  888 
 *    888 Y88b888 d88""88b 888P"   888 "888 "88b     "88b 888          888  d8P  Y8b `Y8bd8P' 888   d88" 888 888P"      "88b 888  888  888 
 *    888  Y88888 888  888 888     888  888  888 .d888888 888          888  88888888   X88K   888   888  888 888    .d888888 888  888  888 
 *    888   Y8888 Y88..88P 888     888  888  888 888  888 888          888  Y8b.     .d8""8b. Y88b. Y88b 888 888    888  888 Y88b 888 d88P 
 *    888    Y888  "Y88P"  888     888  888  888 "Y888888 888          888   "Y8888  888  888  "Y888 "Y88888 888    "Y888888  "Y8888888P"  
 *                                                                                                                                         
 */

Textdraw_Normal()
{
    new id = Iter_Free(Text_List);

    Textler[id][text.id]                = Text: -1;
    format(Textler[id][text.string], DIL_MAX_BUFFER, Dil_Mesaji[yeni_textdraw]);
    Textler[id][text.pos][0]            = 270.0;
    Textler[id][text.pos][1]            = 170.0;
    Textler[id][text.lettersize][0]     = 0.300;
    Textler[id][text.lettersize][1]     = 1.500;
    Textler[id][text.textsize][0]       = 0.0;
    Textler[id][text.textsize][1]       = 0.0;
    Textler[id][text.alignment]         = 1; // 1-left 2-centered 3-right.
    Textler[id][text.color]             = 0xFFFFFFFF;
    Textler[id][text.usebox]            = 0;
    Textler[id][text.boxcolor]          = RGB::HexToRGBA(0, 0, 0, 150);
    Textler[id][text.shadow]            = 1;
    Textler[id][text.outline]           = 1;
    Textler[id][text.bgcolor]           = RGB::HexToRGBA(0, 0, 0, 150);
    Textler[id][text.font]              = 1;
    Textler[id][text.proportional]      = 1;
    Textler[id][text.selectable]        = 0;
    Textler[id][text.preview_model]     = 0;
    Textler[id][text.preview_rot][0]    = 0.0;
    Textler[id][text.preview_rot][1]    = 0.0;
    Textler[id][text.preview_rot][2]    = 0.0;
    Textler[id][text.preview_rot][3]    = 1.0;
    Textler[id][text.preview_vc][0]     = 0;
    Textler[id][text.preview_vc][1]     = 0;
    Textler[id][text.globaplayer]       = 0;
    Textler[id][text.degiskenAdi][0]    = '\0';
    Textler[id][text.grup]              = 0;
    Textler[id][text.grup_temp]         = 0;

    gIndex = id;

    Iter_Add(Text_List, id), Textdraw_Render(id, true);

    Hud_Render(true), Hud_Goster(true);

    Hud_Oncelik_Textdraw();

    DB_Ekle(id);
    return 1;
}


/***
 *     .d8888b.                   d8b 888                 88888888888                888        888                               
 *    d88P  Y88b                  Y8P 888                     888                    888        888                               
 *    Y88b.                           888                     888                    888        888                               
 *     "Y888b.   88888b.  888d888 888 888888 .d88b.           888   .d88b.  888  888 888888 .d88888 888d888 8888b.  888  888  888 
 *        "Y88b. 888 "88b 888P"   888 888   d8P  Y8b          888  d8P  Y8b `Y8bd8P' 888   d88" 888 888P"      "88b 888  888  888 
 *          "888 888  888 888     888 888   88888888          888  88888888   X88K   888   888  888 888    .d888888 888  888  888 
 *    Y88b  d88P 888 d88P 888     888 Y88b. Y8b.              888  Y8b.     .d8""8b. Y88b. Y88b 888 888    888  888 Y88b 888 d88P 
 *     "Y8888P"  88888P"  888     888  "Y888 "Y8888           888   "Y8888  888  888  "Y888 "Y88888 888    "Y888888  "Y8888888P"  
 *               888                                                                                                              
 *               888                                                                                                              
 *               888                                                                                                              
 */

Textdraw_Sprite()
{
    new id = Iter_Free(Text_List);

    Textler[id][text.id]                = Text: -1;
    format(Textler[id][text.string], DIL_MAX_BUFFER, Sprite_Cache_Get());
    Textler[id][text.pos][0]            = 250.0;
    Textler[id][text.pos][1]            = 150.0;
    Textler[id][text.lettersize][0]     = 0.0;
    Textler[id][text.lettersize][1]     = 0.0;
    Textler[id][text.textsize][0]       = 90.0;
    Textler[id][text.textsize][1]       = 90.0;
    Textler[id][text.alignment]         = 1;
    Textler[id][text.color]             = 0xFFFFFFFF;
    Textler[id][text.usebox]            = 0;
    Textler[id][text.boxcolor]          = RGB::HexToRGBA(0, 0, 0, 255);
    Textler[id][text.shadow]            = 0;
    Textler[id][text.outline]           = 0;
    Textler[id][text.bgcolor]           = RGB::HexToRGBA(0, 0, 0, 255);
    Textler[id][text.font]              = 4;
    Textler[id][text.proportional]      = 1;
    Textler[id][text.selectable]        = 0;
    Textler[id][text.preview_model]     = 0;
    Textler[id][text.preview_rot][0]    = 0.0;
    Textler[id][text.preview_rot][1]    = 0.0;
    Textler[id][text.preview_rot][2]    = 0.0;
    Textler[id][text.preview_rot][3]    = 1.0;
    Textler[id][text.preview_vc][0]     = 0;
    Textler[id][text.preview_vc][1]     = 0;
    Textler[id][text.globaplayer]       = 0;
    Textler[id][text.degiskenAdi][0]    = '\0';
    Textler[id][text.grup]              = 0;
    Textler[id][text.grup_temp]         = 0;

    gIndex = id;

    Iter_Add(Text_List, id), Textdraw_Render(id, true);

    Hud_Render(true), Hud_Goster(true);

    Hud_Oncelik_Textdraw();

    DB_Ekle(id);
    return 1;
}


/***
 *    8888888b.                           d8b                             888b     d888               888          888          
 *    888   Y88b                          Y8P                             8888b   d8888               888          888          
 *    888    888                                                          88888b.d88888               888          888          
 *    888   d88P 888d888 .d88b.  888  888 888  .d88b.  888  888  888      888Y88888P888  .d88b.   .d88888  .d88b.  888 .d8888b  
 *    8888888P"  888P"  d8P  Y8b 888  888 888 d8P  Y8b 888  888  888      888 Y888P 888 d88""88b d88" 888 d8P  Y8b 888 88K      
 *    888        888    88888888 Y88  88P 888 88888888 888  888  888      888  Y8P  888 888  888 888  888 88888888 888 "Y8888b. 
 *    888        888    Y8b.      Y8bd8P  888 Y8b.     Y88b 888 d88P      888   "   888 Y88..88P Y88b 888 Y8b.     888      X88 
 *    888        888     "Y8888    Y88P   888  "Y8888   "Y8888888P"       888       888  "Y88P"   "Y88888  "Y8888  888  88888P' 
 *                                                                                                                              
 */

Textdraw_PreviewModels()
{
    new id = Iter_Free(Text_List);

    Textler[id][text.id]                = Text: -1;
    format(Textler[id][text.string], DIL_MAX_BUFFER, "_");
    Textler[id][text.pos][0]            = 250.0;
    Textler[id][text.pos][1]            = 150.0;
    Textler[id][text.lettersize][0]     = 0.0;
    Textler[id][text.lettersize][1]     = 0.0;
    Textler[id][text.textsize][0]       = 90.0;
    Textler[id][text.textsize][1]       = 90.0;
    Textler[id][text.alignment]         = 1;
    Textler[id][text.color]             = 0xFFFFFFFF;
    Textler[id][text.usebox]            = 0;
    Textler[id][text.boxcolor]          = RGB::HexToRGBA(0, 0, 0, 0);
    Textler[id][text.shadow]            = 0;
    Textler[id][text.outline]           = 0;
    Textler[id][text.bgcolor]           = RGB::HexToRGBA(0, 0, 0, 85);
    Textler[id][text.font]              = 5;
    Textler[id][text.proportional]      = 0;
    Textler[id][text.selectable]        = 0;
    Textler[id][text.preview_model]     = 0;
    Textler[id][text.preview_rot][0]    = 0.0;
    Textler[id][text.preview_rot][1]    = 0.0;
    Textler[id][text.preview_rot][2]    = 0.0;
    Textler[id][text.preview_rot][3]    = 1.0;
    Textler[id][text.preview_vc][0]     = 0;
    Textler[id][text.preview_vc][1]     = 0;
    Textler[id][text.globaplayer]       = 0;
    Textler[id][text.degiskenAdi][0]    = '\0';
    Textler[id][text.grup]              = 0;
    Textler[id][text.grup_temp]         = 0;

    gIndex = id;

    Iter_Add(Text_List, id), Textdraw_Render(id, true);

    Hud_Render(true), Hud_Goster(true);

    Hud_Oncelik_Textdraw();

    DB_Ekle(id);
    return 1;
}