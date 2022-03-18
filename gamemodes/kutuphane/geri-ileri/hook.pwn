
/***
 *    888    888                   888      
 *    888    888                   888      
 *    888    888                   888      
 *    8888888888  .d88b.   .d88b.  888  888 
 *    888    888 d88""88b d88""88b 888 .88P 
 *    888    888 888  888 888  888 888888K  
 *    888    888 Y88..88P Y88..88P 888 "88b 
 *    888    888  "Y88P"   "Y88P"  888  888 
 *                                          
 *                                          
 *                                          
 */

#include    <YSI_Coding\y_hooks>

Undo_Redo(playerid)
{
    if(timer_undo != -1) KillTimer(timer_undo), timer_undo = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);

    // Orijinal verinin bir kopyasını al
    Textler_TMP = Textler[gIndex];

    // Dolaşım yapılacak indexi sıfırla
    uRedo_Index = 0;

    // Geri ve ileri alınacak verileri yükle + toplam değişiklik sayısını çek
    gIleri_Yukle(gIndex);

    // İlk değişiklikleri göster
    Textler[gIndex] = uRedo[uRedo_Index];
    Textdraw_Render(gIndex, true);
    TextDrawSetString(Bilgi_Text, fex("~g~~h~Index: ~w~~h~%d / %d", uRedo_Index + 1, uRedo_Total));

    // Diğer
    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);
    timer_undo = SetTimerEx("UndoRedo_Timer", 85, true, "d", playerid);
    return 1;
}

forward UndoRedo_Timer(playerid);
public UndoRedo_Timer(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_undo != -1)
    {
        tus = false;

        // sol
        if(lr < -1) {
            tus = true;
            uRedo_Index = (uRedo_Index <= 0) ? (0) : (uRedo_Index - 1);
        }

        // Sağ
        if(lr > 1) 
        {
            tus = true;
            if(uRedo_Index++ >= uRedo_Total - 1)
            {
                uRedo_Index = uRedo_Total - 1;
            }
        }

        if(tus == true)
        {
            Textler[gIndex] = uRedo[uRedo_Index];
            
            Textdraw_Render(gIndex, true);
            
            TextDrawSetString(Bilgi_Text, fex("~g~~h~Index: ~w~~h~%d / %d", uRedo_Index + 1, uRedo_Total));
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_undo != -1)
    {
        KillTimer(timer_undo), timer_undo = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_undo != -1)
    {
        uRedo_onay_Count = GetTickCount() + 350;
        Undo_Redo_Onay(playerid);
    }
    
    if(PRESSED(KEY_NO) && timer_undo != -1)
    {
        Undo_Redo_Manuel(playerid);
    }
    return 1;
}


/***
 *    888b     d888                                     888 
 *    8888b   d8888                                     888 
 *    88888b.d88888                                     888 
 *    888Y88888P888  8888b.  88888b.  888  888  .d88b.  888 
 *    888 Y888P 888     "88b 888 "88b 888  888 d8P  Y8b 888 
 *    888  Y8P  888 .d888888 888  888 888  888 88888888 888 
 *    888   "   888 888  888 888  888 Y88b 888 Y8b.     888 
 *    888       888 "Y888888 888  888  "Y88888  "Y8888  888 
 *                                                          
 */

Undo_Redo_Manuel(playerid)
{
    Dialog_Show(playerid, UNDO_REDO, DIALOG_STYLE_INPUT, Dil_Mesaji[gi_baslik], fex(fmt(Dil_Mesaji[gi_icerik_1]), uRedo_Total), Dil_Mesaji[gi_buton_1], Dil_Mesaji[gi_buton_2]);
    return 1;
}

Dialog:UNDO_REDO(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new deger;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[gi_hata]), Undo_Redo_Manuel(playerid);
        }

        if(sscanf(inputtext, "d", deger)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[gi_hata]), Undo_Redo_Manuel(playerid);
        }

        if(deger < 1 || deger > uRedo_Total) {
            return Mesaj_Hata(playerid, Dil_Mesaji[gi_hata]), Undo_Redo_Manuel(playerid);
        }

        uRedo_Index = deger - 1;

        Textler[gIndex] = uRedo[uRedo_Index];
        
        Textdraw_Render(gIndex, true);
        
        TextDrawSetString(Bilgi_Text, fex("~g~~h~Index: ~w~~h~%d / %d", uRedo_Index + 1, uRedo_Total));
    }
    return 1;
}

/***
 *     .d88888b.       888b    888             d8888      Y88b   d88P 
 *    d88P" "Y88b      8888b   888            d88888       Y88b d88P  
 *    888     888      88888b  888           d88P888        Y88o88P   
 *    888     888      888Y88b 888          d88P 888         Y888P    
 *    888     888      888 Y88b888         d88P  888          888     
 *    888     888      888  Y88888        d88P   888          888     
 *    Y88b. .d88P      888   Y8888       d8888888888          888     
 *     "Y88888P"       888    Y888      d88P     888          888     
 *                                                                    
 */

Undo_Redo_Onay(playerid)
{
    Dialog_Show(playerid, UNDO_REDO_ONAY, DIALOG_STYLE_MSGBOX, Dil_Mesaji[gio_baslik], Dil_Mesaji[gio_icerik_1], Dil_Mesaji[gio_buton_1], Dil_Mesaji[gio_buton_2]);
    return 1;
}

Dialog:UNDO_REDO_ONAY(playerid, response, listitem, inputtext[])
{
    if(uRedo_onay_Count > GetTickCount()) {
        return Undo_Redo_Onay(playerid);
    }

    ChatTemizle();

    if(response)
    {
        // Yeni halini güncelle
        DB_Guncelle(gIndex);

        // Veritabanından geçerli geri alma verisini temizle
        db_free_result(db_query(proje_db, fex("DELETE FROM gerial WHERE sid = %d", uRedo_SID[uRedo_Index])));

        // Bilgi
        Mesaj_Bilgi(playerid, Dil_Mesaji[gio_bilgi_1]);
    }
    else
    {
        // Eski haline çevir
        Textler[gIndex] = Textler_TMP;
        Textdraw_Render(gIndex, true);

        // Bilgi
        Mesaj_Bilgi(playerid, Dil_Mesaji[gio_bilgi_2]);
    }

    // Verileri kaldır
    Bilgi_Text_Kaldir(), KillTimer(timer_undo), timer_undo = -1;
    Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
    return 1;
}