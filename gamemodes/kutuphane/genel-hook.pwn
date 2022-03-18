
/***
 *           d8888                           888                                   888    888                   888      
 *          d88888                           888                                   888    888                   888      
 *         d88P888                           888                                   888    888                   888      
 *        d88P 888 888  888  8888b.  888d888 888  8888b.  888d888                  8888888888  .d88b.   .d88b.  888  888 
 *       d88P  888 888  888     "88b 888P"   888     "88b 888P"                    888    888 d88""88b d88""88b 888 .88P 
 *      d88P   888 888  888 .d888888 888     888 .d888888 888          888888      888    888 888  888 888  888 888888K  
 *     d8888888888 Y88b 888 888  888 888     888 888  888 888                      888    888 Y88..88P Y88..88P 888 "88b 
 *    d88P     888  "Y88888 "Y888888 888     888 "Y888888 888                      888    888  "Y88P"   "Y88P"  888  888 
 *                      888                                                                                              
 *                 Y8b d88P                                                                                              
 *                  "Y88P"                                                                                               
 */

#include    <YSI_Coding\y_hooks>

hook OnGameModeInit()
{
    // GameModeText'i ayarla
    SetGameModeText(fex("%s %s", TDE_HOSTNAME, TDE_VERSION));

    // Sunucu adını ayarla
    SendRconCommand(fex("hostname %s %s", TDE_HOSTNAME, TDE_VERSION));
    
    // Proje listesini oluştur
    proje_listesi = db_open(DOSYA_PROJE);
    db_free_result(db_query(proje_listesi, PROJE_DB_LIST_QUERY));
    return 1;
}

hook OnGameModeExit()
{
    // Veritabanlarını kapat
    if(db_close(proje_db)) proje_db = DB: 0;
    if(db_close(proje_listesi)) proje_listesi = DB: 0;
    return 1;
}