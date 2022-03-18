/***
 *    888b     d888          888    d8b          
 *    8888b   d8888          888    Y8P          
 *    88888b.d88888          888                 
 *    888Y88888P888  .d88b.  888888 888 88888b.  
 *    888 Y888P 888 d8P  Y8b 888    888 888 "88b 
 *    888  Y8P  888 88888888 888    888 888  888 
 *    888   "   888 Y8b.     Y88b.  888 888  888 
 *    888       888  "Y8888   "Y888 888 888  888 
 *
 */

Metin(playerid)
{
    Dialog_Show(playerid, METIN, DIALOG_STYLE_INPUT, Dil_Mesaji[metin_baslik], "\
    %s\n{ecf0f1}%s\n\n%s", Dil_Mesaji[metin_buton1], Dil_Mesaji[metin_buton2]
    ,
        Dil_Mesaji[metin_icerik],
        Textler[gIndex][text.string],
        Dil_Mesaji[metin_icerik2]
    );
    return 1;
}

Dialog:METIN(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        ChatTemizle();
        
        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[metin_hata]), Metin(playerid);
        }

        if(strcmp(Textler[gIndex][text.string], inputtext, false)) {
            gIleri_Ekle(gIndex);
            Hud_Render(true), Hud_Goster(true);
        }

        format(Textler[gIndex][text.string], MAX_TEXT_STRING, inputtext);

        Textdraw_Render(gIndex, true);

        DB_Guncelle(gIndex);

        Mesaj_Bilgi(playerid, Dil_Mesaji[metin_bilgi]);

        Mouse(playerid, true, TEXTMOD_NORMAL);
    }
    return 1;
}