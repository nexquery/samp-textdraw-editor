
/***
 *    888      d8b          888            
 *    888      Y8P          888            
 *    888                   888            
 *    888      888 .d8888b  888888 .d88b.  
 *    888      888 88K      888   d8P  Y8b 
 *    888      888 "Y8888b. 888   88888888 
 *    888      888      X88 Y88b. Y8b.     
 *    88888888 888  88888P'  "Y888 "Y8888  
 *                                         
 */

Liste_Menu(playerid)
{
    // Değişkenler
    new pos1, pos2, index, buffer[HUD_LISTE_BUFFER];

    // Üst header [ID | Değişken Adı | İçerik | Tür]
    format(buffer, sizeof(buffer), "%s\t%s\t%s\t%s\n"
    ,
        Dil_Mesaji[liste_header1],
        Dil_Mesaji[liste_header2],
        Dil_Mesaji[liste_header3],
        Dil_Mesaji[liste_header4]
    );

    // >>, <<, Sayfaya git
    format(buffer, sizeof(buffer), "%s>>\t\t\t\n", buffer);
    format(buffer, sizeof(buffer), "%s<<\t\t\t\n", buffer);
    format(buffer, sizeof(buffer), "%s%s\t\t\t\n", buffer, Dil_Mesaji[liste_icerik]);
    format(buffer, sizeof(buffer), "%s\t\t\t\n",   buffer);
    
    // Sayfa içeriği
    pos1 = Page_Pos1(liste_Sayfa, HUD_LISTE_ICERIK);
    pos2 = Page_Pos2(liste_Sayfa, Iter_Count(Text_List), HUD_LISTE_ICERIK);
    for(new i = pos1, j = 0; i < pos2; i++, j++)
    {
        index = Iter_Index(Text_List, i);
        if(index == gIndex)
        {
            format(buffer, sizeof(buffer), "%s{f9ca24}%d\t{f9ca24}%s\t{f9ca24}%.20s%s\t{f9ca24}%s\n"
            ,
                buffer,
                index,
                Textdraw_Degisken_Adi(index),
                Textler[index][text.string],
                (strlen(Textler[index][text.string]) > 20) ? ("...") : (""),
                (Textler[index][text.globaplayer] == 0) ? ("Global") : ("Player")
            );
        }
        else
        {
            format(buffer, sizeof(buffer), "%s%d\t%s\t%.20s%s\t%s\n"
            ,
                buffer,
                index,
                Textdraw_Degisken_Adi(index),
                Textler[index][text.string],
                (strlen(Textler[index][text.string]) > 20) ? ("...") : (""),
                (Textler[index][text.globaplayer] == 0) ? ("Global") : ("Player")
            );
        }
        liste_Sayfa_Arr[j] = index;
    }

    Dialog_Show(playerid, LISTE_MENU, DIALOG_STYLE_TABLIST_HEADERS, fex(fmt(Dil_Mesaji[liste_baslik]), liste_Sayfa, Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK)), buffer, Dil_Mesaji[liste_btn1], Dil_Mesaji[liste_btn2]);
    return 1;
}

Dialog:LISTE_MENU(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(liste_Sayfa++ >= Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK))
                {
                    liste_Sayfa = Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK);
                }
                Liste_Menu(playerid);
            }

            case 1:
            {
                if(liste_Sayfa-- <= 1)
                {
                    liste_Sayfa = 1;
                }
                Liste_Menu(playerid);
            }

            case 2:
            {
                Sayfa_Menu(playerid, SAYFA_HUD_LISTE);
            }

            case 3:
            {
                Liste_Menu(playerid);
            }

            default:
            {
                liste_Listitem = listitem - 4;
                Liste_Islem(playerid);
            }
        }
    }
    return 1;
}


/***
 *    888      d8b          888                 8888888         888                        
 *    888      Y8P          888                   888           888                        
 *    888                   888                   888           888                        
 *    888      888 .d8888b  888888 .d88b.         888  .d8888b  888  .d88b.  88888b.d88b.  
 *    888      888 88K      888   d8P  Y8b        888  88K      888 d8P  Y8b 888 "888 "88b 
 *    888      888 "Y8888b. 888   88888888        888  "Y8888b. 888 88888888 888  888  888 
 *    888      888      X88 Y88b. Y8b.            888       X88 888 Y8b.     888  888  888 
 *    88888888 888  88888P'  "Y888 "Y8888       8888888 88888P' 888  "Y8888  888  888  888 
 *                                                                                         
 */

Liste_Islem(playerid)
{
    Dialog_Show(playerid, LISTE_ISLEM, DIALOG_STYLE_LIST, Dil_Mesaji[lislem_baslik], "\
    %s\n%s\n%s\n%s\n%s\n%s\n%s", Dil_Mesaji[lislem_btn1], Dil_Mesaji[lislem_btn2]
    ,
        Dil_Mesaji[lislem_icerik1],
        Dil_Mesaji[lislem_icerik2],
        Dil_Mesaji[lislem_icerik3],
        Dil_Mesaji[lislem_icerik4],
        Dil_Mesaji[lislem_icerik5],
        Dil_Mesaji[lislem_icerik6],
        Dil_Mesaji[lislem_icerik7]
    );
    return 1;
}

Dialog:LISTE_ISLEM(playerid, response, listitem, inputtext[])
{
    if(!response) return Liste_Menu(playerid);
    if(response)
    {
        switch(listitem)
        {
            // Textdrawı seç
            case 0:
            {
                // Textdrawı seç
                gIndex = liste_Sayfa_Arr[liste_Listitem];

                // Chati temizle ve bilgi ver
                ChatTemizle();
                Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[tdraw_sec]), gIndex);

                // Hudu güncelle
                Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);

                if(gIndex != -1)
                {
                    TextDrawBoxColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
                    TextDrawBackgroundColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
                    TextDrawColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
                    TextDrawShowForAll(Textler[gIndex][text.id]);
                    SetTimerEx("Textdraw_Normal_Select", TEXT_SECILEN_TIMER, false, "d", gIndex);
                }
            }

            // Textdrawı seç (Yön Tuşlarıyla)
            case 1:
            {
                // Textdrawı seç
                gIndex = liste_Sayfa_Arr[liste_Listitem];
                Textdraw_Sec_Yon_Tusu(playerid);
            }

            // Textdrawı sil
            case 2:
            {
                Textler[liste_Sayfa_Arr[liste_Listitem]][text.grup]      = 0;
                Textler[liste_Sayfa_Arr[liste_Listitem]][text.grup_temp] = 0;

                // Veriyi ekle
                Sil_Ekle(liste_Sayfa_Arr[liste_Listitem]);

                // Textdrawı sil
                Textdraw_List_Sil(liste_Sayfa_Arr[liste_Listitem]);

                // Veritabanından sil
                DB_Sil(liste_Sayfa_Arr[liste_Listitem]);

                // Geri Aldan sil
                gIleri_Sil(liste_Sayfa_Arr[liste_Listitem]);

                // Chati temizle ve bilgi ver
                ChatTemizle();
                Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[tdraw_sil]), liste_Sayfa_Arr[liste_Listitem]);

                // Textdraw yokas hudu güncelle
                if(!Iter_Count(Text_List)) Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);

                // Textdraw varsa listeyi güncelle
                if(Iter_Count(Text_List))
                {
                    if(liste_Sayfa >= Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK))
                    {
                        liste_Sayfa = Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK);
                    }
                    Liste_Menu(playerid);
                }
            }

            // Textdrawı kopyala
            case 3:
            {
                // Textdrawı kopyala
                new id = Textdraw_List_Kopyala(liste_Sayfa_Arr[liste_Listitem]);

                Textler[id][text.grup]      = 0;
                Textler[id][text.grup_temp] = 0;

                // Veritabanına ekle
                DB_Ekle(id);

                // Chati temizle ve bilgi ver
                ChatTemizle();
                Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[tdraw_kopyala]), id);

                // Listeyi aç
                Liste_Menu(playerid);
            }

            // Textdrawı kopyala ve seç
            case 4:
            {
                // Textdrawı kopyala
                new id = Textdraw_List_Kopyala(liste_Sayfa_Arr[liste_Listitem]);

                Textler[id][text.grup]      = 0;
                Textler[id][text.grup_temp] = 0;

                // Kopyalanan textdrawı seç
                gIndex = id;
                liste_Sayfa = Textdraw_Sayfa_Bul();

                // Veritabanına ekle
                DB_Ekle(id);

                // Chati temizle ve bilgi ver
                ChatTemizle();
                Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[tdraw_kopyala2]), id);

                // Listeyi aç
                Liste_Menu(playerid);
            }

            // Index Değiştir
            case 5:
            {
                // Geçerli sayfaların verilerini al
                index_degistir_Sayfa = liste_Sayfa;

                // Tıklanan Indexi al
                index_degistir_fake_Index = liste_Sayfa_Arr[liste_Listitem];

                // Paneli göster
                Liste_Index_Menu(playerid);
            }

            // Değişken adını düzenle
            case 6:
            {
                Liste_Degisken_Adi(playerid);
            }
        }
    }
    return 1;
}


/***
 *    8888888               888                        8888888b.                    d8b          888    d8b         
 *      888                 888                        888  "Y88b                   Y8P          888    Y8P         
 *      888                 888                        888    888                                888                
 *      888   88888b.   .d88888  .d88b.  888  888      888    888  .d88b.   .d88b.  888 .d8888b  888888 888 888d888 
 *      888   888 "88b d88" 888 d8P  Y8b `Y8bd8P'      888    888 d8P  Y8b d88P"88b 888 88K      888    888 888P"   
 *      888   888  888 888  888 88888888   X88K        888    888 88888888 888  888 888 "Y8888b. 888    888 888     
 *      888   888  888 Y88b 888 Y8b.     .d8""8b.      888  .d88P Y8b.     Y88b 888 888      X88 Y88b.  888 888     
 *    8888888 888  888  "Y88888  "Y8888  888  888      8888888P"   "Y8888   "Y88888 888  88888P'  "Y888 888 888     
 *                                                                              888                                 
 *                                                                         Y8b d88P                                 
 *                                                                          "Y88P"                                  
 */

Liste_Index_Menu(playerid)
{
    // Değişkenler
    new pos1, pos2, index, buffer[HUD_LISTE_BUFFER];

    // Üst header [ID | Değişken Adı | İçerik | Tür]
    format(buffer, sizeof(buffer), "%s\t%s\t%s\t%s\n"
    ,
        Dil_Mesaji[liste_header1],
        Dil_Mesaji[liste_header2],
        Dil_Mesaji[liste_header3],
        Dil_Mesaji[liste_header4]
    );

    // >>, <<, Sayfaya git
    format(buffer, sizeof(buffer), "%s>>\t\t\t\n", buffer);
    format(buffer, sizeof(buffer), "%s<<\t\t\t\n", buffer);
    format(buffer, sizeof(buffer), "%s%s\t\t\t\n", buffer, Dil_Mesaji[liste_icerik]);
    format(buffer, sizeof(buffer), "%s\t\t\t\n",   buffer);
    
    // Sayfa içeriği
    pos1 = Page_Pos1(index_degistir_Sayfa, HUD_LISTE_ICERIK);
    pos2 = Page_Pos2(index_degistir_Sayfa, Iter_Count(Text_List), HUD_LISTE_ICERIK);
    for(new i = pos1, j = 0; i < pos2; i++, j++)
    {
        index = Iter_Index(Text_List, i);
        if(index == index_degistir_fake_Index)
        {
            format(buffer, sizeof(buffer), "%s{f9ca24}%d\t{f9ca24}%s\t{f9ca24}%.20s%s\t{f9ca24}%s\n"
            ,
                buffer,
                index,
                Textdraw_Degisken_Adi(index),
                Textler[index][text.string],
                (strlen(Textler[index][text.string]) > 20) ? ("...") : (""),
                (Textler[index][text.globaplayer] == 0) ? ("Global") : ("Player")
            );
        }
        else
        {
            format(buffer, sizeof(buffer), "%s%d\t%s\t%.20s%s\t%s\n"
            ,
                buffer,
                index,
                Textdraw_Degisken_Adi(index),
                Textler[index][text.string],
                (strlen(Textler[index][text.string]) > 20) ? ("...") : (""),
                (Textler[index][text.globaplayer] == 0) ? ("Global") : ("Player")
            );
        }
        index_degistir_Arr[j] = index;
    }

    Dialog_Show(playerid, LISTE_INDEX_DEGISTIR, DIALOG_STYLE_TABLIST_HEADERS, fex(fmt(Dil_Mesaji[idgstr_bslk]), index_degistir_Sayfa, Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK)), buffer, Dil_Mesaji[idgstr_btn1], Dil_Mesaji[idgstr_btn2]);
    return 1;
}

Dialog:LISTE_INDEX_DEGISTIR(playerid, response, listitem, inputtext[])
{
    if(!response) return Liste_Islem(playerid);
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(index_degistir_Sayfa++ >= Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK))
                {
                    index_degistir_Sayfa = Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK);
                }
                Liste_Index_Menu(playerid);
            }

            case 1:
            {
                if(index_degistir_Sayfa-- <= 1)
                {
                    index_degistir_Sayfa = 1;
                }
                Liste_Index_Menu(playerid);
            }

            case 2:
            {
                Sayfa_Menu(playerid, SAYFA_HUD_LISTE_INDEX);
            }

            case 3:
            {
                Liste_Index_Menu(playerid);
            }

            default:
            {
                new
                    // temp
                    yedek_textdraw[textdraw_yapilandirmasi],

                    // a
                    secili_Textdraw = index_degistir_fake_Index,
                    
                    // b
                    tiklanan_Textdraw = index_degistir_Arr[listitem - 4],

                    bool: durum = false
                ;

                if(index_degistir_fake_Index == gIndex)
                {
                    durum = true;
                }

                /*
                    int temp = *a;
                    *a = *b;
                    *b = temp;
                */

                // int temp = *a;
                yedek_textdraw = Textler[secili_Textdraw];

                // *a = *b;
                Textler[secili_Textdraw] = Textler[tiklanan_Textdraw];

                // *b = temp;
                Textler[tiklanan_Textdraw] = yedek_textdraw;

                // Yeni index
                index_degistir_fake_Index = tiklanan_Textdraw;

                if(durum)
                {
                    gIndex = tiklanan_Textdraw;
                    if(liste_Sayfa >= Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK))
                    {
                        liste_Sayfa = Max_Page(Iter_Count(Text_List), HUD_LISTE_ICERIK);
                    }
                }

                //
                //  Textdrawı güncelle
                //
                TextDrawDestroy(Textler[tiklanan_Textdraw][text.id]);
                Textler[tiklanan_Textdraw][text.id] = Text: -1;

                TextDrawDestroy(Textler[secili_Textdraw][text.id]);
                Textler[secili_Textdraw][text.id] = Text: -1;

                if(secili_Textdraw >= tiklanan_Textdraw)
                {
                    Textdraw_Render(tiklanan_Textdraw, true);
                    Textdraw_Render(secili_Textdraw, true);
                }
                else
                {
                    Textdraw_Render(secili_Textdraw, true);
                    Textdraw_Render(tiklanan_Textdraw, true);
                }

                DB_Guncelle(tiklanan_Textdraw), DB_Guncelle(secili_Textdraw);

                gIleri_Sil(tiklanan_Textdraw), gIleri_Sil(secili_Textdraw);
                //
                //
                //

                // Bilgi
                Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[idgstr_bilgi]), index_degistir_fake_Index);

                // Menü
                Liste_Index_Menu(playerid);
            }
        }
    }
    return 1;
}


/***
 *    8888888b.                    d8b          888                                    d8888      888 d8b 
 *    888  "Y88b                   Y8P          888                                   d88888      888 Y8P 
 *    888    888                                888                                  d88P888      888     
 *    888    888  .d88b.   .d88b.  888 .d8888b  888  888  .d88b.  88888b.           d88P 888  .d88888 888 
 *    888    888 d8P  Y8b d88P"88b 888 88K      888 .88P d8P  Y8b 888 "88b         d88P  888 d88" 888 888 
 *    888    888 88888888 888  888 888 "Y8888b. 888888K  88888888 888  888        d88P   888 888  888 888 
 *    888  .d88P Y8b.     Y88b 888 888      X88 888 "88b Y8b.     888  888       d8888888888 Y88b 888 888 
 *    8888888P"   "Y8888   "Y88888 888  88888P' 888  888  "Y8888  888  888      d88P     888  "Y88888 888 
 *                             888                                                                        
 *                        Y8b d88P                                                                        
 *                         "Y88P"                                                                         
 */

Liste_Degisken_Adi(playerid)
{
    Dialog_Show(playerid, LISTE_DEGISKEN_ADI, DIALOG_STYLE_INPUT, Dil_Mesaji[degadi_bslk], "\
    %s\n%s", Dil_Mesaji[degadi_btn1], Dil_Mesaji[degadi_btn2]
    ,
        Dil_Mesaji[degadi_icrk_1],
        Dil_Mesaji[degadi_icrk_2]
    );
    return 1;
}

Dialog:LISTE_DEGISKEN_ADI(playerid, response, listitem, inputtext[])
{
    if(!response) return Liste_Islem(playerid);
    if(response)
    {
        new id = liste_Sayfa_Arr[liste_Listitem];

        ChatTemizle();

        if(strlen(inputtext) > MAX_GPLAYER_ISIM) {
            return Mesaj_Hata(playerid, Dil_Mesaji[degadi_hata]), Liste_Degisken_Adi(playerid);
        }

        gIleri_Ekle(id);

        if(isnull(inputtext)) {
            Textler[id][text.degiskenAdi][0] = '\0'; 
            Mesaj_Bilgi(playerid, Dil_Mesaji[degadi_bilgi2]);
        }

        if(!isnull(inputtext)) {
            format(Textler[id][text.degiskenAdi], MAX_GPLAYER_ISIM, inputtext);
            Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[degadi_bilgi]), inputtext);
        }

        DB_Guncelle(id);

        Liste_Islem(playerid);
    }
    return 1;
}

/***
 *    88888888888                888        888                                     .d8888b.                    
 *        888                    888        888                                    d88P  Y88b                   
 *        888                    888        888                                    Y88b.                        
 *        888   .d88b.  888  888 888888 .d88888 888d888 8888b.  888  888  888       "Y888b.    .d88b.   .d8888b 
 *        888  d8P  Y8b `Y8bd8P' 888   d88" 888 888P"      "88b 888  888  888          "Y88b. d8P  Y8b d88P"    
 *        888  88888888   X88K   888   888  888 888    .d888888 888  888  888            "888 88888888 888      
 *        888  Y8b.     .d8""8b. Y88b. Y88b 888 888    888  888 Y88b 888 d88P      Y88b  d88P Y8b.     Y88b.    
 *        888   "Y8888  888  888  "Y888 "Y88888 888    "Y888888  "Y8888888P"        "Y8888P"   "Y8888   "Y8888P 
 *
 */

#include    <YSI_Coding\y_hooks>

Textdraw_Sec_Yon_Tusu(playerid)
{
    // Ön veriler
    if(timer_textdraw_sec != -1) KillTimer(timer_textdraw_sec), timer_textdraw_sec = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);

    // İlk işlemleri uygula
    TextDrawBoxColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
    TextDrawBackgroundColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
    TextDrawColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
    TextDrawShowForAll(Textler[gIndex][text.id]);

    // Index bilgisi
    BilgiText_Update();
    TextDrawSetString(Bilgi_Text, fex("~g~~h~Index: ~w~~h~%d / %d", gIndex, Iter_Count(Text_List) - 1));

    // Bilgi
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);

    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }

    // Timeri çalıştır
    timer_textdraw_sec = SetTimerEx("Textdraw_Index_Yon", 85, true, "d", playerid);
    return 1;
}


forward Textdraw_Index_Yon(playerid);
public Textdraw_Index_Yon(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_textdraw_sec != -1)
    {
        tus = false;
        BilgiText_Gizle();

        // Sol
        if(lr < -1)
        {
            tus = true;
            TextDrawBoxColor(Textler[gIndex][text.id], Textler[gIndex][text.boxcolor]);
            TextDrawBackgroundColor(Textler[gIndex][text.id], Textler[gIndex][text.bgcolor]);
            TextDrawColor(Textler[gIndex][text.id], Textler[gIndex][text.color]);
            TextDrawShowForAll(Textler[gIndex][text.id]);
            if(Iter_Count(Text_List) > 1)
            {
                if(Iter_Contains(Text_List, gIndex))
                {
                    gIndex = Iter_Prev(Text_List, gIndex);
                    if (gIndex == Iter_Begin(Text_List))
                    {
                        gIndex = Iter_Last(Text_List);
                    }
                }
            }
            TextDrawBoxColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
            TextDrawBackgroundColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
            TextDrawColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
            TextDrawShowForAll(Textler[gIndex][text.id]);
        }

        // Sağ
        if(lr > 1) 
        {
            tus = true;
            TextDrawBoxColor(Textler[gIndex][text.id], Textler[gIndex][text.boxcolor]);
            TextDrawBackgroundColor(Textler[gIndex][text.id], Textler[gIndex][text.bgcolor]);
            TextDrawColor(Textler[gIndex][text.id], Textler[gIndex][text.color]);
            TextDrawShowForAll(Textler[gIndex][text.id]);
            if(Iter_Count(Text_List) > 1)
            {
                if(Iter_Contains(Text_List, gIndex))
                {
                    gIndex = Iter_Next(Text_List, gIndex);
                    if(gIndex == Iter_End(Text_List))
                    {
                        gIndex = Iter_First(Text_List);
                    }
                }
            }
            TextDrawBoxColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
            TextDrawBackgroundColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
            TextDrawColor(Textler[gIndex][text.id], RENK_SECILEN_TEXT);
            TextDrawShowForAll(Textler[gIndex][text.id]);
        }

        // Güncelle
        if(tus == true)
        {
            BilgiText_Update();
            TextDrawSetString(Bilgi_Text, fex("~g~~h~Index: ~w~~h~%d / %d", gIndex, Iter_Count(Text_List) - 1));
        }
    }
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_textdraw_sec != -1)
    {
        KillTimer(timer_textdraw_sec), timer_textdraw_sec = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_textdraw_sec != -1)
    {
        Bilgi_Text_Kaldir(), KillTimer(timer_textdraw_sec), timer_textdraw_sec = -1;
        TextDrawBoxColor(Textler[gIndex][text.id], Textler[gIndex][text.boxcolor]);
        TextDrawBackgroundColor(Textler[gIndex][text.id], Textler[gIndex][text.bgcolor]);
        TextDrawColor(Textler[gIndex][text.id], Textler[gIndex][text.color]);
        TextDrawShowForAll(Textler[gIndex][text.id]);
        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[tdraw_sec]), gIndex);
        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
        if(spawn_modu == 1) TogglePlayerControllable(playerid, 1);
    }
    return 1;
}

forward Textdraw_Normal_Select(index);
public Textdraw_Normal_Select(index)
{
    TextDrawBoxColor(Textler[gIndex][text.id], Textler[gIndex][text.boxcolor]);
    TextDrawBackgroundColor(Textler[index][text.id], Textler[index][text.bgcolor]);
    TextDrawColor(Textler[index][text.id], Textler[index][text.color]);
    TextDrawShowForAll(Textler[index][text.id]);
}