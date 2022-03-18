/***
 *     .d8888b.                            888                                 
 *    d88P  Y88b                           888                                 
 *    888    888                           888                                 
 *    888        888d888 888  888 88888b.  888  8888b.  88888b.d88b.   8888b.  
 *    888  88888 888P"   888  888 888 "88b 888     "88b 888 "888 "88b     "88b 
 *    888    888 888     888  888 888  888 888 .d888888 888  888  888 .d888888 
 *    Y88b  d88P 888     Y88b 888 888 d88P 888 888  888 888  888  888 888  888 
 *     "Y8888P88 888      "Y88888 88888P"  888 "Y888888 888  888  888 "Y888888 
 *                                888                                          
 *                                888                                          
 *                                888                                          
 */


Gruplama_Menu(playerid)
{
    if(!Iter_Count(Text_List))
    {
        ChatTemizle();
        Mesaj_Hata(playerid, Dil_Mesaji[grp_hata]), Depo_Menu(playerid);
        return 1;
    }

    Dialog_Show(playerid, GRUPLAMA, DIALOG_STYLE_LIST, Dil_Mesaji[grp_baslik], "\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\t\t%s\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    {FFFFFF}\n\
    %s\n\
    %s\n\
    %s\n\
    ", Dil_Mesaji[grp_buton1], Dil_Mesaji[grp_buton2]
    ,
        Dil_Mesaji[grp_icerik1],
        Dil_Mesaji[grp_icerik2],
        Dil_Mesaji[grp_icerik3],
        Dil_Mesaji[grp_icerik4],
        Dil_Mesaji[grp_icerik5],
        Dil_Mesaji[grp_icerik6],
        Dil_Mesaji[grp_icerik7],
        Dil_Mesaji[grp_icerik8],
        Dil_Mesaji[grp_icerik9],
        Dil_Mesaji[grp_icerik10],
        Dil_Mesaji[grp_icerik11],
        Dil_Mesaji[grp_icerik12],
        Dil_Mesaji[grp_icerik13],
        Dil_Mesaji[grp_icerik14],
        Dil_Mesaji[grp_icerik15],
        Dil_Mesaji[grp_icerik16],
        Dil_Mesaji[grp_icerik17],
        Dil_Mesaji[grp_icerik18],
        Dil_Mesaji[grp_icerik19],
        Dil_Mesaji[grp_icerik20],
        Dil_Mesaji[grp_icerik21],
        Dil_Mesaji[grp_icerik22],
        Dil_Mesaji[grp_icerik23],
        Dil_Mesaji[grp_icerik24],
        Dil_Mesaji[grp_icerik25],
        Dil_Mesaji[grp_icerik26],
        Dil_Mesaji[grp_icerik27],
        Dil_Mesaji[grp_icerik28],
        Dil_Mesaji[grp_icerik29],
        Dil_Mesaji[grp_icerik30],
        Dil_Mesaji[grp_icerik31],
        Dil_Mesaji[grp_icerik32],
        Dil_Mesaji[grp_icerik33],
        Dil_Mesaji[grp_icerik34],
        Dil_Mesaji[grp_icerik35],
        Dil_Mesaji[grp_icerik36],
        Dil_Mesaji[grp_icerik37],
        Dil_Mesaji[grp_icerik38],
        Dil_Mesaji[grp_icerik39],
        Dil_Mesaji[grp_icerik40], Grup_Renk_Modu(),
        Dil_Mesaji[grp_icerik41],
        Dil_Mesaji[grp_icerik42],
        Dil_Mesaji[grp_icerik43],
        Dil_Mesaji[grp_icerik44],
        Dil_Mesaji[grp_icerik45],
        Dil_Mesaji[grp_icerik46],
        Dil_Mesaji[grp_icerik47],
        Dil_Mesaji[grp_icerik48],
        Dil_Mesaji[grp_icerik49],
        Dil_Mesaji[grp_icerik50],
        Dil_Mesaji[grp_icerik51],
        Dil_Mesaji[grp_icerik52],
        Dil_Mesaji[grp_icerik53]
    );
    return 1;
}

Dialog:GRUPLAMA(playerid, response, listitem, inputtext[])
{
    if(!response) return Depo_Menu(playerid);
    if(response)
    {
        switch(listitem)
        {
            // Boş tık
            case 0: Gruplama_Menu(playerid);

            // Gruplanacak öğeleri seç
            case 1: grup_Sayfa = 1, Gruplama_Oge_Sec(playerid);

            // Tüm öğeleri grupla
            case 2:
            {
                foreach(new id : Text_List) { Textler[id][text.grup] = 1; }
                db_free_result(db_query(proje_db, "UPDATE textdrawlar SET grup = 1"));
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi1]);
                Gruplama_Menu(playerid);
            }

            // Tüm öğeleri sıfırla
            case 3:
            {
                foreach(new id : Text_List) { Textler[id][text.grup] = 0; }
                db_free_result(db_query(proje_db, "UPDATE textdrawlar SET grup = 0"));
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi2]);
                Gruplama_Menu(playerid);
            }

            // Boş tık
            case 4, 5: Gruplama_Menu(playerid);

            // Hızlı Grupla: Normal Textdraw
            case 6:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3)
                    {
                        Textler[id][text.grup] = 1;
                    }
                }
                db_free_result(db_query(proje_db, "UPDATE textdrawlar SET grup = 1 WHERE font <= 3"));
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi3]);
                Gruplama_Menu(playerid);
            }

            // Hızlı Grupla: Sprite
            case 7:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] == 4)
                    {
                        Textler[id][text.grup] = 1;
                    }
                }
                db_free_result(db_query(proje_db, "UPDATE textdrawlar SET grup = 1 WHERE font = 4"));
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi4]);
                Gruplama_Menu(playerid);
            }

            // Hızlı Grupla: Preview Models
            case 8:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] == 5)
                    {
                        Textler[id][text.grup] = 1;
                    }
                }
                db_free_result(db_query(proje_db, "UPDATE textdrawlar SET grup = 1 WHERE font = 5"));
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi5]);
                Gruplama_Menu(playerid);
            }

            // Boş tık
            case 9, 10: Gruplama_Menu(playerid);

            // Kopyala
            case 11:
            {
                new total = 0;
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1)
                    {
                        new index                   = Iter_Free(Text_List);
                        Textler[index]              = Textler[id];
                        Textler[index][text.id]     = Text: -1;
                        Textler[index][text.grup]   = 0;
                        Iter_Add(Text_List,         index);
                        Textdraw_Render(index,      true);
                        DB_Ekle(index);
                        total++;
                    }
                }
                ChatTemizle();
                if(total == 0) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]);
                if(total >= 1) Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[grp_bilgi6]), total);
                Gruplama_Menu(playerid);
            }

            // Kopyala ve seç
            case 12:
            {
                new total = 0;
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup_temp] == 1) continue;
                    if(Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.grup]          = 0;
                        DB_Guncelle(id);

                        new index                       = Iter_Free(Text_List);
                        Textler[index]                  = Textler[id];
                        Textler[index][text.id]         = Text: -1;
                        Textler[index][text.grup]       = 1;
                        Textler[index][text.grup_temp]  = 1;
                        Iter_Add(Text_List,             index);
                        Textdraw_Render(index,          true);
                        DB_Ekle(index);

                        total++;
                    }
                }
                foreach(new id : Text_List) { Textler[id][text.grup_temp] = 0; }
                ChatTemizle();
                if(total == 0) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]);
                if(total >= 1) Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[grp_bilgi7]), total);
                Gruplama_Menu(playerid);
            }

            // Boş Tık
            case 13, 14: Gruplama_Menu(playerid);

            // Sil
            case 15:
            {
                new total = 0;
                static const reset[textdraw_yapilandirmasi];
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1)
                    {
                        // Bu textdraw seçiliyse, seçimden kaldır
                        if(gIndex == id) gIndex = -1;

                        // Textdrawı sil
                        if(Textler[id][text.id] != Text: -1) TextDrawDestroy(Textler[id][text.id]);

                        // Grupları sıfırla
                        Textler[id][text.grup]      = 0;
                        Textler[id][text.grup_temp] = 0;
                        
                        // Ana veriyi textdraw listesinden silecek
                        DB_Sil(id);

                        // Silinen textdrawlara ekleyecek
                        Sil_Ekle(id);

                        // Geri ve ileri al listesinden silecek
                        gIleri_Sil(id);

                        // Arrayi sıfırla
                        Textler[id]             = reset;
                        Textler[id][text.id]    = Text: -1;

                        // Totali arttır
                        total++;

                        // Güvenli bir şekilde listeden sil
                        Iter_SafeRemove(Text_List, id, id);
                    }
                }
                Hud_Render(true), Hud_Goster(true);
                if(total == 0) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]);
                if(total >= 1) Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[grp_bilgi8]), total);
                Gruplama_Menu(playerid);
            }

            // Boş tık
            case 16, 17: Gruplama_Menu(playerid);

            // Konum
            case 18:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Konum(playerid);
            }

            // Boş tık
            case 19, 20: Gruplama_Menu(playerid);

            // Boyutlandırma -> Textsize (Normal Textdraw)
            case 21:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                gTextsize_Mod = 0;
                Gruplama_Boyut_Textsize(playerid);
            }

            // Boyutlandırma -> Textsize (Sprite)
            case 22:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                gTextsize_Mod = 1;
                Gruplama_Boyut_Textsize(playerid);
            }

            // Boyutlandırma -> Textsize (Preview Models)
            case 23:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                gTextsize_Mod = 2;
                Gruplama_Boyut_Textsize(playerid);
            }

            // Boyutlandırma -> Textsize (Sprite, Preview Models)
            case 24:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                gTextsize_Mod = 3;
                Gruplama_Boyut_Textsize(playerid);
            }

            // Boyutlandırma -> Textsize (Normal, Sprite, Preview Models)
            case 25:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                gTextsize_Mod = 4;
                Gruplama_Boyut_Textsize(playerid);
            }

            // Boyutlandırma -> Lettersize (Normal Textdraw)
            case 26:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                gTextsize_Mod = 5;
                Gruplama_Boyut_Textsize(playerid);
            }

            // Boş tık
            case 27, 28: Gruplama_Menu(playerid);

            // Metin Değiştir
            case 29:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Metin(playerid);
            }

            // Boş tık
            case 30, 31: Gruplama_Menu(playerid);

            // Font 0
            case 32:
            {
                new bool: durum = false, f_Font = 0;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.font] = f_Font;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[grp_bilgi12]), f_Font);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Font 1
            case 33:
            {
                new bool: durum = false, f_Font = 1;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.font] = f_Font;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[grp_bilgi12]), f_Font);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Font 2
            case 34:
            {
                new bool: durum = false, f_Font = 2;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.font] = f_Font;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[grp_bilgi12]), f_Font);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Font 3
            case 35:
            {
                new bool: durum = false, f_Font = 3;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.font] = f_Font;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[grp_bilgi12]), f_Font);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Boş tık
            case 36, 37: Gruplama_Menu(playerid);

            // Hizala: Sol
            case 38:
            {
                new bool: durum = false;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.alignment] = 1;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi13]);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Hizala: Orta
            case 39:
            {
                new bool: durum = false;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.alignment] = 2;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi13]);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Hizala: Sağ
            case 40:
            {
                new bool: durum = false;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.alignment] = 3;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi13]);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }
            
            // Boş tık
            case 41, 42: Gruplama_Menu(playerid);

            // Metin Orantısı: Aç
            case 43:
            {
                new bool: durum = false;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.proportional] = 1;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi14]);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Metin Orantısı: Kapat
            case 44:
            {
                new bool: durum = false;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.proportional] = 0;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi14]);
                Gruplama_Menu(playerid), Hud_Render(true), Hud_Goster(true);
            }

            // Boş tık
            case 45, 46: Gruplama_Menu(playerid);

            // Outline
            case 47:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Outline(playerid);
            }

            // Shadow
            case 48:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Shadow(playerid);
            }

            // Boş tık
            case 49: Gruplama_Menu(playerid);

            // Renk Modu
            case 50:
            {
                gRenkModu = (gRenkModu == 2) ? (0) : (gRenkModu + 1);
                Gruplama_Menu(playerid);
            }

            // Hex
            case 51:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Renk_Hex(playerid);
            }

            // RGB
            case 52:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Renk_RGB(playerid);
            }

            // RGBA
            case 53:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Renk_RGBA(playerid);
            }

            // Hazır Renkler
            case 54:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                Gruplama_Renk_Hazir(playerid);
            }

            // Boş tık
            case 55, 56: Gruplama_Menu(playerid);
        
            // Box: Aç
            case 57:
            {
                new bool: durum = false;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.usebox] = 1;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi16]);
                Gruplama_Menu(playerid);
                Hud_Render(true), Hud_Goster(true);
            }

            // Box: Kapat
            case 58:
            {
                new bool: durum = false;
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        durum = true, Textler[id][text.usebox] = 0;
                        Textdraw_Render(id, true), DB_Guncelle(id);
                    }
                }
                ChatTemizle();
                if(durum == false) Mesaj_Hata(playerid, Dil_Mesaji[grp_hata2]);
                if(durum == true) Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi16]);
                Gruplama_Menu(playerid);
                Hud_Render(true), Hud_Goster(true);
            }

            // Boş tık
            case 59, 60: Gruplama_Menu(playerid);
        
            // Selectable: Aç
            case 61:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.selectable] = 1;
                    }
                }
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi17]);
                Gruplama_Menu(playerid);
                Hud_Render(true), Hud_Goster(true);
            }

            // Selectable: Kapat
            case 62:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.selectable] = 0;
                    }
                }
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi17]);
                Gruplama_Menu(playerid);
                Hud_Render(true), Hud_Goster(true);
            }

            // Boş tık
            case 63, 64: Gruplama_Menu(playerid);
        
            // Global
            case 65:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.globaplayer] = 0;
                    }
                }
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi18]);
                Gruplama_Menu(playerid);
                Hud_Render(true), Hud_Goster(true);
            }

            // Player
            case 66:
            {
                if(!Grup_Total()) return Mesaj_Hata(playerid, Dil_Mesaji[grp_hata1]), Gruplama_Menu(playerid);
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.globaplayer] = 1;
                    }
                }
                ChatTemizle();
                Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi18]);
                Gruplama_Menu(playerid);
                Hud_Render(true), Hud_Goster(true);
            }
        }
    }
    return 1;
}


/***
 *     .d88888b.                          .d8888b.                    
 *    d88P" "Y88b                        d88P  Y88b                   
 *    888     888                        Y88b.                        
 *    888     888  .d88b.   .d88b.        "Y888b.    .d88b.   .d8888b 
 *    888     888 d88P"88b d8P  Y8b          "Y88b. d8P  Y8b d88P"    
 *    888     888 888  888 88888888            "888 88888888 888      
 *    Y88b. .d88P Y88b 888 Y8b.          Y88b  d88P Y8b.     Y88b.    
 *     "Y88888P"   "Y88888  "Y8888        "Y8888P"   "Y8888   "Y8888P 
 *                     888                                            
 *                Y8b d88P                                            
 *                 "Y88P"                                             
 */

Gruplama_Oge_Sec(playerid)
{
    new pos1, pos2, index;

    gBuffer[0] = '\0';

    format(gBuffer, sizeof(gBuffer), "%s\t%s\t%s\t%s\n"
    ,
        Dil_Mesaji[go_header1],
        Dil_Mesaji[go_header2],
        Dil_Mesaji[go_header3],
        Dil_Mesaji[go_header4]
    );

    format(gBuffer, sizeof(gBuffer), "%s>>\t\t\t\n", gBuffer);
    format(gBuffer, sizeof(gBuffer), "%s<<\t\t\t\n", gBuffer);
    format(gBuffer, sizeof(gBuffer), "%s%s\t\t\t\n", gBuffer, Dil_Mesaji[go_icerik1]);
    format(gBuffer, sizeof(gBuffer), "%s%s\t\t\t\n", gBuffer, Dil_Mesaji[go_icerik2]);
    format(gBuffer, sizeof(gBuffer), "%s%s\t\t\t\n", gBuffer, Dil_Mesaji[go_icerik3]);
    format(gBuffer, sizeof(gBuffer), "%s\t\t\t\n",   gBuffer);

    pos1 = Page_Pos1(grup_Sayfa, MAX_GRUP_OGE_ICERIK);
    pos2 = Page_Pos2(grup_Sayfa, Iter_Count(Text_List), MAX_GRUP_OGE_ICERIK);

    for(new i = pos1, j = 0; i < pos2; i++, j++)
    {
        index = Iter_Index(Text_List, i);
        if(Textler[index][text.grup] == 0)
        {
            format(gBuffer, sizeof(gBuffer), "%s%d\t%s\t%.20s%s\t%s\n"
            ,
                gBuffer,
                index,
                Textdraw_Degisken_Adi(index),
                Textler[index][text.string],
                (strlen(Textler[index][text.string]) > 20) ? ("...") : (""),
                Grup_Kontrol(index)
            );
        }
        else
        {
            format(gBuffer, sizeof(gBuffer), "%s{f9ca24}%d\t{f9ca24}%s\t{f9ca24}%.20s%s\t{f9ca24}%s\n"
            ,
                gBuffer,
                index,
                Textdraw_Degisken_Adi(index),
                Textler[index][text.string],
                (strlen(Textler[index][text.string]) > 20) ? ("...") : (""),
                Grup_Kontrol(index)
            );
        }
        grup_Id[j] = index;
    }

    Dialog_Show(playerid, GRUPLANACAK_OGELER, DIALOG_STYLE_TABLIST_HEADERS, fex(fmt(Dil_Mesaji[go_baslik]), grup_Sayfa, Max_Page(Iter_Count(Text_List), MAX_GRUP_OGE_ICERIK)), gBuffer, Dil_Mesaji[go_buton1], Dil_Mesaji[go_buton2]);
    return 1;
}

Dialog:GRUPLANACAK_OGELER(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        switch(listitem)
        {
            case 0:
            {
                if(grup_Sayfa++ >= Max_Page(Iter_Count(Text_List), MAX_GRUP_OGE_ICERIK))
                {
                    grup_Sayfa = Max_Page(Iter_Count(Text_List), MAX_GRUP_OGE_ICERIK);
                }
                Gruplama_Oge_Sec(playerid);
            }

            case 1:
            {
                if(grup_Sayfa-- <= 1)
                {
                    grup_Sayfa = 1;
                }
                Gruplama_Oge_Sec(playerid);
            }

            // Sayfaya git
            case 2: Sayfa_Menu(playerid, SAYFA_GRUPLAMA);

            // Bu sayfayı grupla
            case 3:
            {
                new j;
                new pos1 = Page_Pos1(grup_Sayfa, MAX_GRUP_OGE_ICERIK);
                new pos2 = Page_Pos2(grup_Sayfa, Iter_Count(Text_List), MAX_GRUP_OGE_ICERIK);
                for(new i = pos1; i < pos2; i++)
                {
                    j = Iter_Index(Text_List, i);
                    Textler[j][text.grup] = 1;
                    DB_Guncelle(j);
                }
                Gruplama_Oge_Sec(playerid);
            }

            // Bu sayfayı gruptan çıkar
            case 4:
            {
                new j;
                new pos1 = Page_Pos1(grup_Sayfa, MAX_GRUP_OGE_ICERIK);
                new pos2 = Page_Pos2(grup_Sayfa, Iter_Count(Text_List), MAX_GRUP_OGE_ICERIK);
                for(new i = pos1; i < pos2; i++)
                {
                    j = Iter_Index(Text_List, i);
                    Textler[j][text.grup] = 0;
                    DB_Guncelle(j);
                }
                Gruplama_Oge_Sec(playerid);
            }

            // Boşluk
            case 5: Gruplama_Oge_Sec(playerid);

            // Tıklanan
            default:
            {
                new index = grup_Id[listitem - 6];
                Textler[index][text.grup] = (Textler[index][text.grup] == 0) ? (1) : (0);
                DB_Guncelle(index);
                Gruplama_Oge_Sec(playerid);
            }
        }
    }
    return 1;
}


/***
 *    888    d8P                                           
 *    888   d8P                                            
 *    888  d8P                                             
 *    888d88K      .d88b.  88888b.  888  888 88888b.d88b.  
 *    8888888b    d88""88b 888 "88b 888  888 888 "888 "88b 
 *    888  Y88b   888  888 888  888 888  888 888  888  888 
 *    888   Y88b  Y88..88P 888  888 Y88b 888 888  888  888 
 *    888    Y88b  "Y88P"  888  888  "Y88888 888  888  888 
 *
 */

#include    <YSI_Coding\y_hooks>

Gruplama_Konum(playerid)
{
    if(Timer_gKonum != -1) KillTimer(Timer_gKonum), Timer_gKonum = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);
    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);
    pozisyon_Offset[0] = 0.0;
    pozisyon_Offset[1] = 0.0;
    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }
    Timer_gKonum = SetTimerEx("Timer_Gruplama_Konum", 50, true, "d", playerid);
    return 1;
}

forward Timer_Gruplama_Konum(playerid);
public Timer_Gruplama_Konum(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(Timer_gKonum != -1)
    {
        tus = false;
        BilgiText_Gizle();

        // sol
        if(lr < -1)
        {
            tus = true;
            pozisyon_Offset[0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
            foreach(new id : Text_List)
            {
                if(Textler[id][text.grup] == 1)
                {
                    Textler[id][text.pos][0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    Textdraw_Render(id, true);
                }
            }
        }

        // Sağ
        if(lr > 1)
        {
            tus = true;
            pozisyon_Offset[0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
            foreach(new id : Text_List)
            {
                if(Textler[id][text.grup] == 1)
                {
                    Textler[id][text.pos][0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    Textdraw_Render(id, true);
                }
            }
        }

        // Yukarı
        if(ud < -1)
        {
            tus = true;
            pozisyon_Offset[1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
            foreach(new id : Text_List)
            {
                if(Textler[id][text.grup] == 1)
                {
                    Textler[id][text.pos][1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    Textdraw_Render(id, true);
                }
            }
        }

        // Aşağı
        if(ud > 1)
        {
            tus = true;
            pozisyon_Offset[1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
            foreach(new id : Text_List)
            {
                if(Textler[id][text.grup] == 1)
                {
                    Textler[id][text.pos][1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    Textdraw_Render(id, true);
                }
            }
        }
        
        if(tus == true)
        {
            BilgiText_Update();
            TextDrawSetString(Bilgi_Text, fex("~g~~h~Offset X: ~w~~h~%.1f     ~g~~h~Offset Y: ~w~~h~%.1f", pozisyon_Offset[0], pozisyon_Offset[1]));
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(Timer_gKonum != -1)
    {
        KillTimer(Timer_gKonum), Timer_gKonum = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && Timer_gKonum != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(Timer_gKonum), Timer_gKonum = -1;
        foreach(new id : Text_List)
        {
            if(Textler[id][text.grup] == 1)
            {
                DB_Guncelle(id);
            }
        }
        Hud_Render(true), Hud_Goster(true);
        ChatTemizle();
        Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi9]);
        Gruplama_Menu(playerid);
        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 1);
        }
    }
    return 1;
}


/***
 *    88888888888                888             d8b                                     888              888    888                             d8b                   
 *        888                    888             Y8P                                     888              888    888                             Y8P                   
 *        888                    888                                                     888              888    888                                                   
 *        888   .d88b.  888  888 888888 .d8888b  888 88888888  .d88b.         888        888      .d88b.  888888 888888 .d88b.  888d888 .d8888b  888 88888888  .d88b.  
 *        888  d8P  Y8b `Y8bd8P' 888    88K      888    d88P  d8P  Y8b      8888888      888     d8P  Y8b 888    888   d8P  Y8b 888P"   88K      888    d88P  d8P  Y8b 
 *        888  88888888   X88K   888    "Y8888b. 888   d88P   88888888        888        888     88888888 888    888   88888888 888     "Y8888b. 888   d88P   88888888 
 *        888  Y8b.     .d8""8b. Y88b.       X88 888  d88P    Y8b.                       888     Y8b.     Y88b.  Y88b. Y8b.     888          X88 888  d88P    Y8b.     
 *        888   "Y8888  888  888  "Y888  88888P' 888 88888888  "Y8888                    88888888 "Y8888   "Y888  "Y888 "Y8888  888      88888P' 888 88888888  "Y8888  
 *
 */

#include    <YSI_Coding\y_hooks>

Gruplama_Boyut_Textsize(playerid)
{
    if(Timer_gTextsize_Normal != -1) KillTimer(Timer_gTextsize_Normal), Timer_gTextsize_Normal = -1;
    Hud_Oncelik_Textdraw();
    Hud_Goster(false);
    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);
    pozisyon_Offset[0] = 0.0;
    pozisyon_Offset[1] = 0.0;
    if(spawn_modu == 1)
    {
        TogglePlayerControllable(playerid, 0);
    }
    Timer_gTextsize_Normal = SetTimerEx("Timer_gTextLettersize_Full", 50, true, "d", playerid);
    return 1;
}

forward Timer_gTextLettersize_Full(playerid);
public Timer_gTextLettersize_Full(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(Timer_gTextsize_Normal != -1)
    {
        tus = false;
        BilgiText_Gizle();

        // Sol
        if(lr < -1)
        {
            tus = true;
            switch(gTextsize_Mod)
            {
                case 0: // Normal Textdraw
                {
                    pozisyon_Offset[0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 1: // Sprite
                {
                    pozisyon_Offset[0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 2: // Preview Models
                {
                    pozisyon_Offset[0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 5 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 3: // Sprite + Preview Models
                {
                    pozisyon_Offset[0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] >= 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 4: // Normal + Sprite + Preview Models
                {
                    pozisyon_Offset[0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 5: // Lettersize -> Normal
                {
                    pozisyon_Offset[0] -= (keys == KEY_SPRINT) ? (0.1) : (0.01);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.lettersize][0] -= (keys == KEY_SPRINT) ? (0.1) : (0.01);
                            Textdraw_Render(id, true);
                        }
                    }
                }
            }
        }

        // Sağ
        if(lr > 1)
        {
            tus = true;
            switch(gTextsize_Mod)
            {
                case 0: // Normal Textdraw
                {
                    pozisyon_Offset[0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 1: // Sprite
                {
                    pozisyon_Offset[0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 2: // Preview Models
                {
                    pozisyon_Offset[0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 5 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 3: // Sprite + Preview Models
                {
                    pozisyon_Offset[0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] >= 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 4: // Normal + Sprite + Preview Models
                {
                    pozisyon_Offset[0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][0] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 5: // Lettersize -> Normal
                {
                    pozisyon_Offset[0] += (keys == KEY_SPRINT) ? (0.1) : (0.01);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.lettersize][0] += (keys == KEY_SPRINT) ? (0.1) : (0.01);
                            Textdraw_Render(id, true);
                        }
                    }
                }
            }
        }

        // Yukarı
        if(ud < -1)
        {
            tus = true;
            switch(gTextsize_Mod)
            {
                case 0: // Normal Textdraw
                {
                    pozisyon_Offset[1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 1: // Sprite
                {
                    pozisyon_Offset[1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 2: // Preview Models
                {
                    pozisyon_Offset[1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 5 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 3: // Sprite + Preview Models
                {
                    pozisyon_Offset[1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] >= 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 4: // Normal + Sprite + Preview Models
                {
                    pozisyon_Offset[1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] -= (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 5: // Lettersize -> Normal
                {
                    pozisyon_Offset[1] -= (keys == KEY_SPRINT) ? (1.0) : (0.1);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.lettersize][1] -= (keys == KEY_SPRINT) ? (1.0) : (0.1);
                            Textdraw_Render(id, true);
                        }
                    }
                }
            }
        }

        // Aşağı
        if(ud > 1)
        {
            tus = true;
            switch(gTextsize_Mod)
            {
                case 0: // Normal Textdraw
                {
                    pozisyon_Offset[1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 1: // Sprite
                {
                    pozisyon_Offset[1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 2: // Preview Models
                {
                    pozisyon_Offset[1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] == 5 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 3: // Sprite + Preview Models
                {
                    pozisyon_Offset[1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] >= 4 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 4: // Normal + Sprite + Preview Models
                {
                    pozisyon_Offset[1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.textsize][1] += (keys == KEY_SPRINT) ? (10.0) : (1.0);
                            Textdraw_Render(id, true);
                        }
                    }
                }
                case 5: // Lettersize -> Normal
                {
                    pozisyon_Offset[1] += (keys == KEY_SPRINT) ? (1.0) : (0.1);
                    foreach(new id : Text_List)
                    {
                        if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                        {
                            Textler[id][text.lettersize][1] += (keys == KEY_SPRINT) ? (1.0) : (0.1);
                            Textdraw_Render(id, true);
                        }
                    }
                }
            }
        }

        // Tuşa bastıysa
        if(tus == true)
        {
            BilgiText_Update();
            if(gTextsize_Mod <= 4) {
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Offset X: ~w~~h~%.1f     ~g~~h~Offset Y: ~w~~h~%.1f", pozisyon_Offset[0], pozisyon_Offset[1]));
            }else{
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Offset X: ~w~~h~%.3f     ~g~~h~Offset Y: ~w~~h~%.3f", pozisyon_Offset[0], pozisyon_Offset[1]));
            }
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(Timer_gTextsize_Normal != -1)
    {
        KillTimer(Timer_gTextsize_Normal), Timer_gTextsize_Normal = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && Timer_gTextsize_Normal != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(Timer_gTextsize_Normal), Timer_gTextsize_Normal = -1;
        foreach(new id : Text_List)
        {
            if(Textler[id][text.grup] == 1)
            {
                DB_Guncelle(id);
            }
        }
        Hud_Render(true), Hud_Goster(true);
        ChatTemizle();
        Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi10]);
        Gruplama_Menu(playerid);
        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 1);
        }
    }
    return 1;
}


/***
 *    888b     d888          888    d8b               8888888b.                    d8b          888    d8b         
 *    8888b   d8888          888    Y8P               888  "Y88b                   Y8P          888    Y8P         
 *    88888b.d88888          888                      888    888                                888                
 *    888Y88888P888  .d88b.  888888 888 88888b.       888    888  .d88b.   .d88b.  888 .d8888b  888888 888 888d888 
 *    888 Y888P 888 d8P  Y8b 888    888 888 "88b      888    888 d8P  Y8b d88P"88b 888 88K      888    888 888P"   
 *    888  Y8P  888 88888888 888    888 888  888      888    888 88888888 888  888 888 "Y8888b. 888    888 888     
 *    888   "   888 Y8b.     Y88b.  888 888  888      888  .d88P Y8b.     Y88b 888 888      X88 Y88b.  888 888     
 *    888       888  "Y8888   "Y888 888 888  888      8888888P"   "Y8888   "Y88888 888  88888P'  "Y888 888 888     
 *                                                                             888                                 
 *                                                                        Y8b d88P                                 
 *                                                                         "Y88P"                                  
 */

Gruplama_Metin(playerid)
{
    Dialog_Show(playerid, GRUPLAMA_METIN, DIALOG_STYLE_INPUT, Dil_Mesaji[gmd_baslik], Dil_Mesaji[gmd_icerik], Dil_Mesaji[gmd_buton1], Dil_Mesaji[gmd_buton2]);
    return 1;
}

Dialog:GRUPLAMA_METIN(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        ChatTemizle();

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[gmd_hata]), Gruplama_Metin(playerid);
        }

        foreach(new id : Text_List)
        {
            if(Textler[id][text.grup] == 1)
            {
                format(Textler[id][text.string], MAX_TEXT_STRING, inputtext);

                Textdraw_Render(id, true);

                DB_Guncelle(id);
            }
        }

        Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi11]);

        Gruplama_Menu(playerid);
    }
    return 1;
}


/***
 *     .d88888b.           888    888 d8b                   
 *    d88P" "Y88b          888    888 Y8P                   
 *    888     888          888    888                       
 *    888     888 888  888 888888 888 888 88888b.   .d88b.  
 *    888     888 888  888 888    888 888 888 "88b d8P  Y8b 
 *    888     888 888  888 888    888 888 888  888 88888888 
 *    Y88b. .d88P Y88b 888 Y88b.  888 888 888  888 Y8b.     
 *     "Y88888P"   "Y88888  "Y888 888 888 888  888  "Y8888  
 *
 */

Gruplama_Outline(playerid)
{
    Dialog_Show(playerid, GRUPLAMA_OUTLINE, DIALOG_STYLE_INPUT, Dil_Mesaji[goline_baslik], Dil_Mesaji[goline_icerik], Dil_Mesaji[goline_buton1], Dil_Mesaji[goline_buton2]);
    return 1;
}

Dialog:GRUPLAMA_OUTLINE(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        new deger;

        ChatTemizle();

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[goline_hata]), Gruplama_Outline(playerid);
        }

        if(sscanf(inputtext, "d", deger)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[goline_hata]), Gruplama_Outline(playerid);
        }

        foreach(new id : Text_List)
        {
            if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
            {
                Textler[id][text.outline] = deger;

                Textdraw_Render(id, true);

                DB_Guncelle(id);
            }
        }

        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[goline_bilgi]), deger);

        Gruplama_Menu(playerid);
    }
    return 1;
}


/***
 *     .d8888b.  888                    888                        
 *    d88P  Y88b 888                    888                        
 *    Y88b.      888                    888                        
 *     "Y888b.   88888b.   8888b.   .d88888  .d88b.  888  888  888 
 *        "Y88b. 888 "88b     "88b d88" 888 d88""88b 888  888  888 
 *          "888 888  888 .d888888 888  888 888  888 888  888  888 
 *    Y88b  d88P 888  888 888  888 Y88b 888 Y88..88P Y88b 888 d88P 
 *     "Y8888P"  888  888 "Y888888  "Y88888  "Y88P"   "Y8888888P"  
 *
 */

Gruplama_Shadow(playerid)
{
    Dialog_Show(playerid, GRUPLAMA_SHADOW, DIALOG_STYLE_INPUT, Dil_Mesaji[gshdow_baslik], Dil_Mesaji[gshdow_icerik], Dil_Mesaji[gshdow_buton1], Dil_Mesaji[gshdow_buton2]);
    return 1;
}

Dialog:GRUPLAMA_SHADOW(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        new deger;

        ChatTemizle();

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[gshdow_hata]), Gruplama_Shadow(playerid);
        }

        if(sscanf(inputtext, "d", deger)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[gshdow_hata]), Gruplama_Shadow(playerid);
        }

        foreach(new id : Text_List)
        {
            if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
            {
                Textler[id][text.shadow] = deger;

                Textdraw_Render(id, true);

                DB_Guncelle(id);
            }
        }

        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[gshdow_bilgi]), deger);

        Gruplama_Menu(playerid);
    }
    return 1;
}


/***
 *    888    888                   
 *    888    888                   
 *    888    888                   
 *    8888888888  .d88b.  888  888 
 *    888    888 d8P  Y8b `Y8bd8P' 
 *    888    888 88888888   X88K   
 *    888    888 Y8b.     .d8""8b. 
 *    888    888  "Y8888  888  888 
 *
 */

Gruplama_Renk_Hex(playerid)
{
    Dialog_Show(playerid, GRUPLAMA_RENK_HEX, DIALOG_STYLE_INPUT, Dil_Mesaji[rhex_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s", Dil_Mesaji[rhex_buton_1], Dil_Mesaji[rhex_buton_2]
    ,
        Dil_Mesaji[rhex_icerik_1],
        Dil_Mesaji[rhex_icerik_2],
        Dil_Mesaji[rhex_icerik_3],
        Dil_Mesaji[rhex_icerik_4],
        Dil_Mesaji[rhex_icerik_5],
        Dil_Mesaji[rhex_icerik_6]
    );
    return 1;
}

Dialog:GRUPLAMA_RENK_HEX(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        new hex, buffer[12], len;
        
        ChatTemizle();

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rhex_hata]), Gruplama_Renk_Hex(playerid);
        }

        format(buffer, 12, inputtext);

        len = strlen(buffer);

        for(new i = 0; i < strlen(buffer); i++) {
            buffer[i] = toupper(buffer[i]);
        }

        // FFFFFF
        if(len == 6) {
            strins(buffer, "FF", len);
        }

        // #FFFFFF
        if(len == 7) {
            strins(buffer, "FF", len), strdel(buffer, 0, 1);
        }

        // 0xFFFFFF
        if(len == 8) {
            strins(buffer, "FF", len);
        }

        if(len > 10) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rhex_hata]), Gruplama_Renk_Hex(playerid);
        }

        if(sscanf(buffer, "h", hex)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rhex_hata]), Gruplama_Renk_Hex(playerid);
        }

        switch(gRenkModu)
        {
            case 0:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 5 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.color] = hex;
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 1:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1 && (Textler[id][text.font] <= 3 || Textler[id][text.font] == 5))
                    {
                        Textler[id][text.bgcolor] = hex;
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 2:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.boxcolor] = hex;
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
        }

        Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi15]);
        Gruplama_Menu(playerid);
    }
    return 1;
}

/***
 *    8888888b.   .d8888b.  888888b.   
 *    888   Y88b d88P  Y88b 888  "88b  
 *    888    888 888    888 888  .88P  
 *    888   d88P 888        8888888K.  
 *    8888888P"  888  88888 888  "Y88b 
 *    888 T88b   888    888 888    888 
 *    888  T88b  Y88b  d88P 888   d88P 
 *    888   T88b  "Y8888P88 8888888P"  
 *
 */

Gruplama_Renk_RGB(playerid)
{
    Dialog_Show(playerid, GRUPLAMA_RENK_RGB, DIALOG_STYLE_INPUT, Dil_Mesaji[rgb_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s", Dil_Mesaji[rgb_buton_1], Dil_Mesaji[rgb_buton_2]
    ,
        Dil_Mesaji[rgb_icerik_1],
        Dil_Mesaji[rgb_icerik_2],
        Dil_Mesaji[rgb_icerik_3],
        Dil_Mesaji[rgb_icerik_4],
        Dil_Mesaji[rgb_icerik_5],
        Dil_Mesaji[rgb_icerik_6]
    );
    return 1;
}

Dialog:GRUPLAMA_RENK_RGB(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        new r, g, b, pos = -1;

        ChatTemizle();

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Gruplama_Renk_RGB(playerid);
        }

        pos = strfind(inputtext, "rgb(", true);
        if(pos != -1) strdel(inputtext, pos, pos + 4);

        pos = strfind(inputtext, ")", true, 0);
        if(pos != -1) strdel(inputtext, pos, strlen(inputtext));

        for(new i = 0; i < strlen(inputtext); i++)
        {
            if(inputtext[i] == ',')
            {
                if(inputtext[i + 1] >= '0' && inputtext[i + 1] <= '9')
                {
                    inputtext[i] = ' ';
                }
                else
                {
                    strdel(inputtext, i, i + 1);
                }
            }
        }

        if(sscanf(inputtext, "ddd", r, g, b)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Gruplama_Renk_RGB(playerid);
        }

        if(r < 0 || r > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Gruplama_Renk_RGB(playerid);
        }

        if(g < 0 || g > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Gruplama_Renk_RGB(playerid);
        }

        if(b < 0 || b > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgb_hata]), Gruplama_Renk_RGB(playerid);
        }

        switch(gRenkModu)
        {
            case 0:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 5 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.color] = RGB::HexToRGBA(r, g, b, 255);
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 1:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1 && (Textler[id][text.font] <= 3 || Textler[id][text.font] == 5))
                    {
                        Textler[id][text.bgcolor] = RGB::HexToRGBA(r, g, b, 255);
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 2:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.boxcolor] = RGB::HexToRGBA(r, g, b, 255);
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
        }

        Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi15]);
        Gruplama_Menu(playerid);
    }
    return 1;
}

/***
 *    8888888b.   .d8888b.  888888b.         d8888 
 *    888   Y88b d88P  Y88b 888  "88b       d88888 
 *    888    888 888    888 888  .88P      d88P888 
 *    888   d88P 888        8888888K.     d88P 888 
 *    8888888P"  888  88888 888  "Y88b   d88P  888 
 *    888 T88b   888    888 888    888  d88P   888 
 *    888  T88b  Y88b  d88P 888   d88P d8888888888 
 *    888   T88b  "Y8888P88 8888888P" d88P     888 
 *
 */

Gruplama_Renk_RGBA(playerid)
{
    Dialog_Show(playerid, GRUPLAMA_RENK_RGBA, DIALOG_STYLE_INPUT, Dil_Mesaji[rgba_baslik], "\
    %s\n\n\
    %s\n\
    %s\n\
    %s\n\
    %s\n\
    %s", Dil_Mesaji[rgba_buton_1], Dil_Mesaji[rgba_buton_2]
    ,
        Dil_Mesaji[rgba_icerik_1],
        Dil_Mesaji[rgba_icerik_2],
        Dil_Mesaji[rgba_icerik_3],
        Dil_Mesaji[rgba_icerik_4],
        Dil_Mesaji[rgba_icerik_5],
        Dil_Mesaji[rgba_icerik_6]
    );
    return 1;
}

Dialog:GRUPLAMA_RENK_RGBA(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        new r, g, b, a, pos = -1;

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Gruplama_Renk_RGBA(playerid);
        }

        pos = strfind(inputtext, "rgba(", true);
        if(pos != -1) strdel(inputtext, pos, pos + 5);

        pos = strfind(inputtext, ")", true, 0);
        if(pos != -1) strdel(inputtext, pos, strlen(inputtext));

        for(new i = 0; i < strlen(inputtext); i++)
        {
            if(inputtext[i] == ',')
            {
                if(inputtext[i + 1] >= '0' && inputtext[i + 1] <= '9')
                {
                    inputtext[i] = ' ';
                }
                else
                {
                    strdel(inputtext, i, i + 1);
                }
            }
        }

        if(sscanf(inputtext, "dddd", r, g, b, a)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Gruplama_Renk_RGBA(playerid);
        }

        if(r < 0 || r > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Gruplama_Renk_RGBA(playerid);
        }

        if(g < 0 || g > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Gruplama_Renk_RGBA(playerid);
        }

        if(b < 0 || b > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Gruplama_Renk_RGBA(playerid);
        }

        if(a < 0 || a > 255) {
            return Mesaj_Hata(playerid, Dil_Mesaji[rgba_hata]), Gruplama_Renk_RGBA(playerid);
        }

        switch(gRenkModu)
        {
            case 0:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 5 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.color] = RGB::HexToRGBA(r, g, b, a);
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 1:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1 && (Textler[id][text.font] <= 3 || Textler[id][text.font] == 5))
                    {
                        Textler[id][text.bgcolor] = RGB::HexToRGBA(r, g, b, a);
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 2:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.boxcolor] = RGB::HexToRGBA(r, g, b, a);
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
        }

        Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi15]);
        Gruplama_Menu(playerid);
    }
    return 1;
}


/***
 *    888    888                   d8b              8888888b.                   888      888                  
 *    888    888                   Y8P              888   Y88b                  888      888                  
 *    888    888                                    888    888                  888      888                  
 *    8888888888  8888b.  88888888 888 888d888      888   d88P .d88b.  88888b.  888  888 888  .d88b.  888d888 
 *    888    888     "88b    d88P  888 888P"        8888888P" d8P  Y8b 888 "88b 888 .88P 888 d8P  Y8b 888P"   
 *    888    888 .d888888   d88P   888 888          888 T88b  88888888 888  888 888888K  888 88888888 888     
 *    888    888 888  888  d88P    888 888          888  T88b Y8b.     888  888 888 "88b 888 Y8b.     888     
 *    888    888 "Y888888 88888888 888 888          888   T88b "Y8888  888  888 888  888 888  "Y8888  888     
 *
 */

Gruplama_Renk_Hazir(playerid)
{
    buffer_renk_str[0] = '\0';
    for(new i = 0; i < sizeof(Renk_Paleti); i++)
    {
        format(buffer_renk_str, sizeof(buffer_renk_str), "%s{%06x}%d - ##########\n", buffer_renk_str, Renk_Paleti[i] >>> 8, i + 1);
    }
    Dialog_Show(playerid, GRUPLAMA_RENK_HAZIR, DIALOG_STYLE_LIST, Dil_Mesaji[renk_baslik], buffer_renk_str, Dil_Mesaji[renk_buton1], Dil_Mesaji[renk_buton2]);
    return 1;
}

Dialog:GRUPLAMA_RENK_HAZIR(playerid, response, listitem, inputtext[])
{
    if(!response) return Gruplama_Menu(playerid);
    if(response)
    {
        ChatTemizle();
        switch(gRenkModu)
        {
            case 0:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 5 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.color] = Renk_Paleti[listitem];
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 1:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.grup] == 1 && (Textler[id][text.font] <= 3 || Textler[id][text.font] == 5))
                    {
                        Textler[id][text.bgcolor] = Renk_Paleti[listitem];
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
            case 2:
            {
                foreach(new id : Text_List)
                {
                    if(Textler[id][text.font] <= 3 && Textler[id][text.grup] == 1)
                    {
                        Textler[id][text.boxcolor] = Renk_Paleti[listitem];
                        Textdraw_Render(id, true);
                        DB_Guncelle(id);
                    }
                }
            }
        }
        Mesaj_Bilgi(playerid, Dil_Mesaji[grp_bilgi15]);
        Gruplama_Menu(playerid);
    }
    return 1;
}