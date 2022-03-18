
/***
 *     .d8888b.                             888 
 *    d88P  Y88b                            888 
 *    888    888                            888 
 *    888         .d88b.  88888b.   .d88b.  888 
 *    888  88888 d8P  Y8b 888 "88b d8P  Y8b 888 
 *    888    888 88888888 888  888 88888888 888 
 *    Y88b  d88P Y8b.     888  888 Y8b.     888 
 *     "Y8888P88  "Y8888  888  888  "Y8888  888 
 *                                              
 */

Server_Version()
{
    new sver[10];
    GetConsoleVarAsString("version", sver, sizeof(sver));
    if(!strcmp(sver, "0.3.DL-R1", false)) return VER_03DL;
    return VER_037;
}

New_Line(string[])
{
	new len = strlen(string);
	if(string[0] == 0) return;
    if((string[len - 1] == '\n') || (string[len - 1] == '\r')) 
	{
		string[len - 1] = 0;
		if(string[0] == 0) return;
		if((string[len - 2] == '\n') || (string[len - 2] == '\r'))
		{
			string[len - 2] = 0;
		}
	}
}

Tarih_Cek(epoch)
{
    new buffer[32], yil, ay, gun, saat, dakika, saniye;
    TimestampToDate(epoch, yil, ay, gun, saat, dakika, saniye, .HourGMT = GMT_TIME);
    format(buffer, sizeof(buffer), "%02d.%02d.%04d, %02d:%02d", gun, ay, yil, saat, dakika);
    return buffer;
}

Mesaj_Hata(playerid, const icerik[], va_args<>)
{
    ChatTemizle();
    new buffer[256]; va_format(buffer, sizeof (buffer), icerik, va_start<2>);
    strins(buffer, "[!] {FFFFFF}", 0);
    return SendClientMessage(playerid, RENK_MESAJ_HATA, buffer);
}

Mesaj_Bilgi(playerid, const icerik[], va_args<>)
{
    ChatTemizle();
    new buffer[256]; va_format(buffer, sizeof (buffer), icerik, va_start<2>);
    strins(buffer, "[!] {FFFFFF}", 0);
    return SendClientMessage(playerid, RENK_MESAJ_BILGI, buffer);
}

Dosya_Adi_Kontrol(const sz[])
{
	for(new i = 0; i < strlen(sz); i++)
	{
		switch(sz[i])
		{
			case '\\', '/', ':', '*', '?', '"', '<', '>', '|': return 1;
		}
	}
	return 0;
}

Proje_Adi_Kontrol(const yeni_proje_adi[])
{
    new
        DBResult: cache = db_query(proje_listesi, fex("SELECT isim FROM projeler WHERE LOWER(isim) = LOWER('%q');", yeni_proje_adi)),
        sonuc = db_num_rows(cache)
    ;
    db_free_result(cache);
    return sonuc;
}

fmt(const icerik[])
{
    new string_fix[DIL_MAX_BUFFER];
    format(string_fix, DIL_MAX_BUFFER, icerik);
    for(new i = 0, j = strlen(string_fix); i != j; i++)
    {
        if(string_fix[i] == '#')
        {
            string_fix[i] = '%';
        }
    }
    return string_fix;
}

Page_Pos1(sayfa, limit)
{
    if(sayfa <= 0) sayfa = 1;
	return (sayfa - 1) * limit;
}

Page_Pos2(sayfa, total, limit)
{
    new pos = sayfa * limit;
    pos = (pos >= total) ? (total) : (pos);
    return pos;
}

Max_Page(total, limit)
{
    return ((total - 1) / limit) + 1;
}

Page_Index_Array(sayfa, limit, index)
{
	return (sayfa - 1) * limit + index;
}