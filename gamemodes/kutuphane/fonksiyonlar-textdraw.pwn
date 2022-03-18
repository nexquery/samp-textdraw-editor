
/***
 *    88888888888                888        888                               
 *        888                    888        888                               
 *        888                    888        888                               
 *        888   .d88b.  888  888 888888 .d88888 888d888 8888b.  888  888  888 
 *        888  d8P  Y8b `Y8bd8P' 888   d88" 888 888P"      "88b 888  888  888 
 *        888  88888888   X88K   888   888  888 888    .d888888 888  888  888 
 *        888  Y8b.     .d8""8b. Y88b. Y88b 888 888    888  888 Y88b 888 d88P 
 *        888   "Y8888  888  888  "Y888 "Y88888 888    "Y888888  "Y8888888P"  
 *                                                                            
 */

Total_gPlayer(gp_tip)
{
    new total;
    foreach(new id : Text_List)
    {
        // 0: Global
        // 1: Player
        if(Textler[id][text.globaplayer] == gp_tip)
        {
            total++;
        }
    }
    return total;
}

Total_gPlayer2(gp_tip)
{
    new total;
    foreach(new id : Text_List)
    {
        // 0: Global
        // 1: Player
        if(Textler[id][text.globaplayer] == gp_tip && !strlen(Textler[id][text.degiskenAdi]))
        {
            total++;
        }
    }
    return total;
}

Total_Degisken_gPlayer(gp_tip)
{
    new total;
    foreach(new id : Text_List)
    {
        // 0: Global
        // 1: Player
        if(Textler[id][text.globaplayer] == gp_tip && strlen(Textler[id][text.degiskenAdi]))
        {
            total++;
        }
    }
    return total;
}

Textdraw_Render(id, bool: goster)
{
    if(id != -1)
    {
        if(Textler[id][text.id] != Text: -1) {
            TextDrawDestroy(Textler[id][text.id]);
            Textler[id][text.id] = Text: -1;
        }

        Textler[id][text.id] = TextDrawCreate(Textler[id][text.pos][0], Textler[id][text.pos][1], Textler[id][text.string]);
        
        if(Textler[id][text.lettersize][0] != 0.0 || Textler[id][text.lettersize][1] != 0.0) {
            TextDrawLetterSize(Textler[id][text.id], Textler[id][text.lettersize][0], Textler[id][text.lettersize][1]);
        }

        if(Textler[id][text.textsize][0] != 0.0 || Textler[id][text.textsize][1] != 0.0) {
            TextDrawTextSize(Textler[id][text.id], Textler[id][text.textsize][0], Textler[id][text.textsize][1]);
        }

        TextDrawAlignment(Textler[id][text.id], Textler[id][text.alignment]);
        TextDrawColor(Textler[id][text.id], Textler[id][text.color]);
        TextDrawUseBox(Textler[id][text.id], Textler[id][text.usebox]);
        TextDrawBoxColor(Textler[id][text.id], Textler[id][text.boxcolor]);
        TextDrawSetShadow(Textler[id][text.id], Textler[id][text.shadow]);
        TextDrawSetOutline(Textler[id][text.id], Textler[id][text.outline]);
        TextDrawBackgroundColor(Textler[id][text.id], Textler[id][text.bgcolor]);
        TextDrawFont(Textler[id][text.id], Textler[id][text.font]);
        TextDrawSetProportional(Textler[id][text.id], Textler[id][text.proportional]);

        if(Textler[id][text.font] == TEXT_DRAW_FONT_MODEL_PREVIEW)
        {
            TextDrawSetPreviewModel(Textler[id][text.id], Textler[id][text.preview_model]);
            TextDrawSetPreviewRot(Textler[id][text.id], Textler[id][text.preview_rot][0], Textler[id][text.preview_rot][1], Textler[id][text.preview_rot][2], Textler[id][text.preview_rot][3]);
            TextDrawSetPreviewVehCol(Textler[id][text.id], Textler[id][text.preview_vc][0], Textler[id][text.preview_vc][1]);
        }

        if(goster)
        {
            TextDrawShowForAll(Textler[id][text.id]);
        }
    }
    return 1;
}

Textdraw_Kaldir()
{
    foreach(new id : Text_List)
    {
        if(Textler[id][text.id] != Text: -1)
        {
            TextDrawDestroy(Textler[id][text.id]);
            Textler[id][text.id] = Text: -1;
        }
    }
    return 1;
}


/***
 *    888    888               888      8888888888                888               d8b                            
 *    888    888               888      888                       888               Y8P                            
 *    888    888               888      888                       888                                              
 *    8888888888 888  888  .d88888      8888888  .d88b.  88888b.  888  888 .d8888b  888 888  888  .d88b.  88888b.  
 *    888    888 888  888 d88" 888      888     d88""88b 888 "88b 888 .88P 88K      888 888  888 d88""88b 888 "88b 
 *    888    888 888  888 888  888      888     888  888 888  888 888888K  "Y8888b. 888 888  888 888  888 888  888 
 *    888    888 Y88b 888 Y88b 888      888     Y88..88P 888  888 888 "88b      X88 888 Y88b 888 Y88..88P 888  888 
 *    888    888  "Y88888  "Y88888      888      "Y88P"  888  888 888  888  88888P' 888  "Y88888  "Y88P"  888  888 
 *                                                                                           888                   
 *                                                                                      Y8b d88P                   
 *                                                                                       "Y88P"                    
 */

/*
GetNextPlayer(current)
{
	new next = INVALID_PLAYER_ID;
	if(Iter_Count(SpectatePlayers) > 1)
    {
		if(Iter_Contains(SpectatePlayers, current))
        {
			next = Iter_Next(SpectatePlayers, current);
			if(next == Iter_End(SpectatePlayers))
            {
			    next = Iter_First(SpectatePlayers);
			}
		}
	}
	return next;
}

GetPreviousPlayer(current)
{
	new prev = INVALID_PLAYER_ID;
	if(Iter_Count(SpectatePlayers) > 1)
    {
		if(Iter_Contains(SpectatePlayers, current))
        {
			prev = Iter_Prev(SpectatePlayers, current);
			if(prev == Iter_Begin(SpectatePlayers))
            {
			    prev = Iter_Last(SpectatePlayers);
			}
		}
	}
	return prev;
}
*/

Textdraw_Sayfa_Bul()
{
    if(gIndex != -1)
    {
        new
            pos1, 
            pos2, 
            index, 
            max_sayfa = Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK)
        ;
        for(new i = 1; i <= max_sayfa; i++)
        {
            pos1 = Page_Pos1(i, HUD_LISTE_ICERIK);
            pos2 = Page_Pos2(i, Iter_Count(Text_List), HUD_LISTE_ICERIK);
            for(new j = pos1; j < pos2; j++)
            {
                index = Iter_Index(Text_List, j);
                if(index == gIndex)
                {
                    return i;
                }
            }
        }
    }
    return 1;
}

Textdraw_List_Sil(index)
{
    // Textdrawı sil
    if(Textler[index][text.id] != Text: -1) TextDrawDestroy(Textler[index][text.id]);
    
    // Verileri sıfırla
    static const reset[textdraw_yapilandirmasi];
    Textler[index]          = reset;
    Textler[index][text.id] = Text: -1;

    // Bir sonraki indexi bul
    if(gIndex == index)
    {
        gIndex = -1;
        if(Iter_Count(Text_List) > 1)
        {
            if(Iter_Contains(Text_List, index))
            {
                gIndex = Iter_Prev(Text_List, index);
                if (gIndex == Iter_Begin(Text_List))
                {
                    gIndex = Iter_Last(Text_List);
                }
            }
        }
    }

    // Listeden sil
    Iter_Remove(Text_List, index);
    return 1;
}

Textdraw_List_Kopyala(index)
{
    new id                  = Iter_Free(Text_List);
    Textler[id]             = Textler[index];
    Textler[id][text.id]    = Text: -1;
    Textdraw_Render(id,     true);
    Iter_Add(Text_List,     id);
    return id;
}

Textdraw_Degisken_Adi(index)
{
    new buffer[MAX_GPLAYER_ISIM];
    if(isnull(Textler[index][text.degiskenAdi]))
    {
        format(buffer, MAX_GPLAYER_ISIM, (Textler[index][text.globaplayer] == 0) ? (Text_Global) : (Text_Player));
    }
    else
    {
        format(buffer, MAX_GPLAYER_ISIM, Textler[index][text.degiskenAdi]);
    }
    return buffer;
}