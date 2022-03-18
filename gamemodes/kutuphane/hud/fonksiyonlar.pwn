
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

Hud_Render(bool: kaldir = false)
{
    new 
        Float: fhud, 
        Float: artis = 26.0 + 0.5,
        version = Server_Version()
    ;

    // 03DL
    static const pFont_03DL[][]         = {"mdl-2000:tde-12", "mdl-2000:tde-13", "mdl-2000:tde-14", "mdl-2000:tde-15", "mdl-2000:tde-16", "mdl-2000:tde-17"};
    static const pHiza_03DL[][]         = {"mdl-2000:tde-18", "mdl-2000:tde-19", "mdl-2000:tde-20"};
    static const pOranti_03DL[][]       = {"mdl-2000:tde-21", "mdl-2000:tde-22"};
    static const pBox_03DL[][]          = {"mdl-2000:tde-28", "mdl-2000:tde-29"};
    static const pSelectable_03DL[][]   = {"mdl-2000:tde-30", "mdl-2000:tde-31"};
    static const pGlobaPlayer_03DL[][]  = {"mdl-2000:tde-33", "mdl-2000:tde-34"};

    // 037
    static const pFont_037[][]          = {"NexTDE:tde-12", "NexTDE:tde-13", "NexTDE:tde-14", "NexTDE:tde-15", "NexTDE:tde-16", "NexTDE:tde-17"};
    static const pHiza_037[][]          = {"NexTDE:tde-18", "NexTDE:tde-19", "NexTDE:tde-20"};
    static const pOranti_037[][]        = {"NexTDE:tde-21", "NexTDE:tde-22"};
    static const pBox_037[][]           = {"NexTDE:tde-28", "NexTDE:tde-29"};
    static const pSelectable_037[][]    = {"NexTDE:tde-30", "NexTDE:tde-31"};
    static const pGlobaPlayer_037[][]   = {"NexTDE:tde-33", "NexTDE:tde-34"};

    // Alt bar
    format(Text_Hud[0][hud_string], 32, "LD_SPAC:white");
    Text_Hud[0][hud_pos][0]             = -5.0;
    Text_Hud[0][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[0][hud_textsize][0]        = 650.0;
    Text_Hud[0][hud_textsize][1]        = 36.0;
    Text_Hud[0][hud_color]              = RENK_HUD_ALTBAR;
    Text_Hud[0][hud_selectable]         = 0;

    // Proje
    format(Text_Hud[1][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-1") : ("NexTDE:tde-1"));
    Text_Hud[1][hud_pos][0]             = fhud = 2.5;
    Text_Hud[1][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[1][hud_textsize][0]        = 25.0;
    Text_Hud[1][hud_textsize][1]        = 35.0;
    Text_Hud[1][hud_color]              = -1;
    Text_Hud[1][hud_selectable]         = 1;

    // Ayarlar
    format(Text_Hud[2][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-2") : ("NexTDE:tde-2"));
    Text_Hud[2][hud_pos][0]             = fhud += artis;
    Text_Hud[2][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[2][hud_textsize][0]        = 25.0;
    Text_Hud[2][hud_textsize][1]        = 35.0;
    Text_Hud[2][hud_color]              = (proje_durum) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[2][hud_selectable]         = !!proje_durum;

    // Liste
    format(Text_Hud[3][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-3") : ("NexTDE:tde-3"));
    Text_Hud[3][hud_pos][0]             = fhud += artis;
    Text_Hud[3][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[3][hud_textsize][0]        = 25.0;
    Text_Hud[3][hud_textsize][1]        = 35.0;
    Text_Hud[3][hud_color]              = (proje_durum && Iter_Count(Text_List)) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[3][hud_selectable]         = (proje_durum && Iter_Count(Text_List)) ? (1)  : (0);

    // Depo
    format(Text_Hud[4][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-4") : ("NexTDE:tde-4"));
    Text_Hud[4][hud_pos][0]             = fhud += artis;
    Text_Hud[4][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[4][hud_textsize][0]        = 25.0;
    Text_Hud[4][hud_textsize][1]        = 35.0;
    Text_Hud[4][hud_color]              = (proje_durum) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[4][hud_selectable]         = (proje_durum) ? (1)  : (0);

    // Yeni
    format(Text_Hud[5][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-5") : ("NexTDE:tde-5"));
    Text_Hud[5][hud_pos][0]             = fhud += artis;
    Text_Hud[5][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[5][hud_textsize][0]        = 25.0;
    Text_Hud[5][hud_textsize][1]        = 35.0;
    Text_Hud[5][hud_color]              = (proje_durum) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[5][hud_selectable]         = !!proje_durum;

    // Kopyala
    format(Text_Hud[6][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-6") : ("NexTDE:tde-6"));
    Text_Hud[6][hud_pos][0]             = fhud += artis;
    Text_Hud[6][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[6][hud_textsize][0]        = 25.0;
    Text_Hud[6][hud_textsize][1]        = 35.0;
    Text_Hud[6][hud_color]              = (proje_durum && gIndex != -1) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[6][hud_selectable]         = (proje_durum && gIndex != -1) ? (1)  : (0);

    // Sil
    format(Text_Hud[7][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-7") : ("NexTDE:tde-7"));
    Text_Hud[7][hud_pos][0]             = fhud += artis;
    Text_Hud[7][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[7][hud_textsize][0]        = 25.0;
    Text_Hud[7][hud_textsize][1]        = 35.0;
    Text_Hud[7][hud_color]              = (proje_durum && gIndex != -1) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[7][hud_selectable]         = (proje_durum && gIndex != -1) ? (1)  : (0);

    // Konum
    format(Text_Hud[8][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-8") : ("NexTDE:tde-8"));
    Text_Hud[8][hud_pos][0]             = fhud += artis;
    Text_Hud[8][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[8][hud_textsize][0]        = 25.0;
    Text_Hud[8][hud_textsize][1]        = 35.0;
    Text_Hud[8][hud_color]              = (proje_durum && gIndex != -1) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[8][hud_selectable]         = (proje_durum && gIndex != -1) ? (1)  : (0);

    // Textsize
    format(Text_Hud[9][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-9") : ("NexTDE:tde-9"));
    Text_Hud[9][hud_pos][0]             = fhud += artis;
    Text_Hud[9][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[9][hud_textsize][0]        = 25.0;
    Text_Hud[9][hud_textsize][1]        = 35.0;
    Text_Hud[9][hud_color]              = (proje_durum && gIndex != -1) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[9][hud_selectable]         = (proje_durum && gIndex != -1) ? (1)  : (0);

    // Lettersize
    format(Text_Hud[10][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-10") : ("NexTDE:tde-10"));
    Text_Hud[10][hud_pos][0]             = fhud += artis;
    Text_Hud[10][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[10][hud_textsize][0]        = 25.0;
    Text_Hud[10][hud_textsize][1]        = 35.0;
    Text_Hud[10][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[10][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (1)  : (0);

    // Metin
    format(Text_Hud[11][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-11") : ("NexTDE:tde-11"));
    Text_Hud[11][hud_pos][0]             = fhud += artis;
    Text_Hud[11][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[11][hud_textsize][0]        = 25.0;
    Text_Hud[11][hud_textsize][1]        = 35.0;
    Text_Hud[11][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 4) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[11][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 4) ? (1)  : (0);

    // Font
    if(version == VER_03DL) {
        format(Text_Hud[12][hud_string], 32, (gIndex == -1) ? (pFont_03DL[0]) : (pFont_03DL[Textler[gIndex][text.font]]));
    }else{
        format(Text_Hud[12][hud_string], 32, (gIndex == -1) ? (pFont_037[0]) : (pFont_037[Textler[gIndex][text.font]]));
    }
    Text_Hud[12][hud_pos][0]             = fhud += artis;
    Text_Hud[12][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[12][hud_textsize][0]        = 25.0;
    Text_Hud[12][hud_textsize][1]        = 35.0;
    Text_Hud[12][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[12][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (1)  : (0);

    // Hizalama
    if(version == VER_03DL) {
        format(Text_Hud[13][hud_string], 32, (gIndex == -1) ? (pHiza_03DL[0]) : (pHiza_03DL[Textler[gIndex][text.alignment] - 1]));
    }else{
        format(Text_Hud[13][hud_string], 32, (gIndex == -1) ? (pHiza_037[0]) : (pHiza_037[Textler[gIndex][text.alignment] - 1]));
    }
    Text_Hud[13][hud_pos][0]             = fhud += artis;
    Text_Hud[13][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[13][hud_textsize][0]        = 25.0;
    Text_Hud[13][hud_textsize][1]        = 35.0;
    Text_Hud[13][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[13][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (1)  : (0);

    // Orantı
    if(version == VER_03DL) {
        format(Text_Hud[14][hud_string], 32, (gIndex == -1) ? (pOranti_03DL[0]) : (pOranti_03DL[Textler[gIndex][text.proportional]]));
    }else{
        format(Text_Hud[14][hud_string], 32, (gIndex == -1) ? (pOranti_037[0]) : (pOranti_037[Textler[gIndex][text.proportional]]));
    }
    Text_Hud[14][hud_pos][0]             = fhud += artis;
    Text_Hud[14][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[14][hud_textsize][0]        = 25.0;
    Text_Hud[14][hud_textsize][1]        = 35.0;
    Text_Hud[14][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[14][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (1)  : (0);

    // Outline
    format(Text_Hud[15][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-23") : ("NexTDE:tde-23"));
    Text_Hud[15][hud_pos][0]             = fhud += artis;
    Text_Hud[15][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[15][hud_textsize][0]        = 25.0;
    Text_Hud[15][hud_textsize][1]        = 35.0;
    Text_Hud[15][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[15][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (1)  : (0);

    // Shadow
    format(Text_Hud[16][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-24") : ("NexTDE:tde-24"));
    Text_Hud[16][hud_pos][0]             = fhud += artis;
    Text_Hud[16][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[16][hud_textsize][0]        = 25.0;
    Text_Hud[16][hud_textsize][1]        = 35.0;
    Text_Hud[16][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[16][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (1)  : (0);

    // Renk
    format(Text_Hud[17][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-25") : ("NexTDE:tde-25"));
    Text_Hud[17][hud_pos][0]             = fhud += artis;
    Text_Hud[17][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[17][hud_textsize][0]        = 25.0;
    Text_Hud[17][hud_textsize][1]        = 35.0;
    Text_Hud[17][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 5) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[17][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 5) ? (1)  : (0);

    // BG Rengi
    format(Text_Hud[18][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-26") : ("NexTDE:tde-26"));
    Text_Hud[18][hud_pos][0]             = fhud += artis;
    Text_Hud[18][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[18][hud_textsize][0]        = 25.0;
    Text_Hud[18][hud_textsize][1]        = 35.0;
    Text_Hud[18][hud_color]              = (proje_durum && gIndex != -1 && (Textler[gIndex][text.font] <= 3 || Textler[gIndex][text.font] == 5)) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[18][hud_selectable]         = (proje_durum && gIndex != -1 && (Textler[gIndex][text.font] <= 3 || Textler[gIndex][text.font] == 5)) ? (1)  : (0);

    // Box Rengi
    format(Text_Hud[19][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-27") : ("NexTDE:tde-27"));
    Text_Hud[19][hud_pos][0]             = fhud += artis;
    Text_Hud[19][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[19][hud_textsize][0]        = 25.0;
    Text_Hud[19][hud_textsize][1]        = 35.0;
    Text_Hud[19][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3 && Textler[gIndex][text.usebox] == 1) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[19][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3 && Textler[gIndex][text.usebox] == 1) ? (1)  : (0);

    // Box
    if(version == VER_03DL) {
        format(Text_Hud[20][hud_string], 32, (gIndex == -1) ? (pBox_03DL[0]) : (pBox_03DL[Textler[gIndex][text.usebox]]));
    }else{
        format(Text_Hud[20][hud_string], 32, (gIndex == -1) ? (pBox_037[0]) : (pBox_037[Textler[gIndex][text.usebox]]));
    }
    Text_Hud[20][hud_pos][0]             = fhud += artis;
    Text_Hud[20][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[20][hud_textsize][0]        = 25.0;
    Text_Hud[20][hud_textsize][1]        = 35.0;
    Text_Hud[20][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[20][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] <= 3) ? (1)  : (0);

    // Selectable
    if(version == VER_03DL) {
        format(Text_Hud[21][hud_string], 32, (gIndex == -1) ? (pSelectable_03DL[0]) : (pSelectable_03DL[Textler[gIndex][text.selectable]]));
    }else{
        format(Text_Hud[21][hud_string], 32, (gIndex == -1) ? (pSelectable_037[0]) : (pSelectable_037[Textler[gIndex][text.selectable]]));
    }
    Text_Hud[21][hud_pos][0]             = fhud += artis;
    Text_Hud[21][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[21][hud_textsize][0]        = 25.0;
    Text_Hud[21][hud_textsize][1]        = 35.0;
    Text_Hud[21][hud_color]              = (proje_durum && gIndex != -1) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[21][hud_selectable]         = (proje_durum && gIndex != -1) ? (1)  : (0);

    // Preview Models
    format(Text_Hud[22][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-32") : ("NexTDE:tde-32"));
    Text_Hud[22][hud_pos][0]             = fhud += artis;
    Text_Hud[22][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[22][hud_textsize][0]        = 25.0;
    Text_Hud[22][hud_textsize][1]        = 35.0;
    Text_Hud[22][hud_color]              = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] == 5) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[22][hud_selectable]         = (proje_durum && gIndex != -1 && Textler[gIndex][text.font] == 5) ? (1)  : (0);

    // Global Player
    if(version == VER_03DL) {
        format(Text_Hud[23][hud_string], 32, (gIndex == -1) ? (pGlobaPlayer_03DL[0]) : (pGlobaPlayer_03DL[Textler[gIndex][text.globaplayer]]));
    }else{
        format(Text_Hud[23][hud_string], 32, (gIndex == -1) ? (pGlobaPlayer_037[0]) : (pGlobaPlayer_037[Textler[gIndex][text.globaplayer]]));
    }
    Text_Hud[23][hud_pos][0]             = fhud += artis;
    Text_Hud[23][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[23][hud_textsize][0]        = 25.0;
    Text_Hud[23][hud_textsize][1]        = 35.0;
    Text_Hud[23][hud_color]              = (proje_durum && gIndex != -1) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[23][hud_selectable]         = (proje_durum && gIndex != -1) ? (1)  : (0);

    // Geri - İleri Al
    format(Text_Hud[24][hud_string], 32, (version == VER_03DL) ? ("mdl-2000:tde-35") : ("NexTDE:tde-35"));
    Text_Hud[24][hud_pos][0]             = fhud += artis;
    Text_Hud[24][hud_pos][1]             = Text_Hud_Y;
    Text_Hud[24][hud_textsize][0]        = 25.0;
    Text_Hud[24][hud_textsize][1]        = 35.0;
    Text_Hud[24][hud_color]              = (proje_durum && gIndex != -1 && gIleri_Total(gIndex) != 0) ? (-1) : (RENK_HUD_DISABLE);
    Text_Hud[24][hud_selectable]         = (proje_durum && gIndex != -1 && gIleri_Total(gIndex) != 0) ? (1)  : (0);

    // Oluştur
    for(new i = 0; i < sizeof(Text_Hud); i++)
    {
        if(kaldir)
        {
            if(Text_Hud[i][hindex] != Text: -1)
            {
                TextDrawDestroy(Text_Hud[i][hindex]);
                Text_Hud[i][hindex] = Text: -1;
            }
        }
        Text_Hud[i][hindex] = TextDrawCreate(Text_Hud[i][hud_pos][0], Text_Hud[i][hud_pos][1], Text_Hud[i][hud_string]);
        TextDrawTextSize(Text_Hud[i][hindex], Text_Hud[i][hud_textsize][0], Text_Hud[i][hud_textsize][1]);
        TextDrawBackgroundColor(Text_Hud[i][hindex], 255);
        TextDrawFont(Text_Hud[i][hindex], 4);
        TextDrawColor(Text_Hud[i][hindex], Text_Hud[i][hud_color]);
        TextDrawSetSelectable(Text_Hud[i][hindex], Text_Hud[i][hud_selectable]);
    }
    return 1;
}

Hud_Tumunu_Yukle(playerid)
{
    if(dil_secimi == true && spawn_modu != -1)
    {
        Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
    }
    return 1;
}

Hud_Goster(bool: durum)
{
    for(new i = 0; i < sizeof(Text_Hud); i++)
    {
        if(durum == true && Text_Hud[i][hindex] != Text: -1) TextDrawShowForAll(Text_Hud[i][hindex]);
        if(durum == false && Text_Hud[i][hindex] != Text: -1) TextDrawHideForAll(Text_Hud[i][hindex]);
    }
    return 1;
}

Hud_Kaldir()
{
    for(new i = 0; i < sizeof(Text_Hud); i++)
    {
        if(Text_Hud[i][hindex] != Text: -1)
        {
            TextDrawDestroy(Text_Hud[i][hindex]);
            Text_Hud[i][hindex] = Text: -1;
        }
    }
    return 1;
}

Mouse(playerid, bool: durum, mod)
{
    TextMod = mod;
    pMouse = durum;
    if(durum == false) CancelSelectTextDraw(playerid);
    if(durum == true)  SelectTextDraw(playerid, RENK_MOUSE_DEFAULT);
    return 1;
}

Bilgi_Text_Load()
{
    if(Bilgi_Text != Text: -1)
    {
        TextDrawDestroy(Bilgi_Text);
        Bilgi_Text = Text: -1;
    }

    Bilgi_Text = TextDrawCreate(310.000, 360.000, "_");
    TextDrawLetterSize(Bilgi_Text, 0.219, 1.299);
    TextDrawAlignment(Bilgi_Text, 2);
    TextDrawColor(Bilgi_Text, -1);
    TextDrawSetShadow(Bilgi_Text, 1);
    TextDrawSetOutline(Bilgi_Text, 1);
    TextDrawBackgroundColor(Bilgi_Text, 190);
    TextDrawFont(Bilgi_Text, 1);
    TextDrawSetProportional(Bilgi_Text, 1);

    TextDrawShowForAll(Bilgi_Text);
    
    return 1;
}

Bilgi_Text_Kaldir()
{
    if(Bilgi_Text != Text: -1)
    {
        TextDrawDestroy(Bilgi_Text);
        Bilgi_Text = Text: -1;
    }
    return 1;
}

Hud_Oncelik_Textdraw(bool: render_mod = false)
{
    // Hudu ve textleri veya bilgi textini kaldır
    Hud_Kaldir(), Textdraw_Kaldir(), Bilgi_Text_Kaldir();

    // Textdrawı oluştur
    foreach(new id : Text_List) { Textdraw_Render(id, true); }

    // Hudu oluştur
    Hud_Render(render_mod), Hud_Goster(true);

    // Bilgi Textini oluştur ve göster
    Bilgi_Text_Load();
    return 1;
}

BilgiText_Gizle()
{
    if(GetTickCount() > bilgiText_tickCount)
    {
        TextDrawSetString(Bilgi_Text, "_");
    }
    return 1;
}

BilgiText_Update()
{
    bilgiText_tickCount = GetTickCount() + 750;
    return 1;
}