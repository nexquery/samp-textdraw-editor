
/***
 *    888    d8P                                      888          
 *    888   d8P                                       888          
 *    888  d8P                                        888          
 *    888d88K      .d88b.  88888b.  888  888  8888b.  888  8888b.  
 *    8888888b    d88""88b 888 "88b 888  888     "88b 888     "88b 
 *    888  Y88b   888  888 888  888 888  888 .d888888 888 .d888888 
 *    888   Y88b  Y88..88P 888 d88P Y88b 888 888  888 888 888  888 
 *    888    Y88b  "Y88P"  88888P"   "Y88888 "Y888888 888 "Y888888 
 *                         888           888                       
 *                         888      Y8b d88P                       
 *                         888       "Y88P"                        
 */

Kopyala(playerid)
{
    if(gIndex != -1)
    {
        new id = Textdraw_List_Kopyala(gIndex);

        Textler[id][text.grup]      = 0;
        Textler[id][text.grup_temp] = 0;

        gIndex = id;

        DB_Ekle(id);
        
        Mesaj_Bilgi(playerid, fmt(Dil_Mesaji[kopyala_bilgi]), id);
    }
    return 1;
}