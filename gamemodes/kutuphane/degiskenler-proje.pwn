
/***
 *    8888888b.                    d8b          888                        888                                   8888888b.                   d8b          
 *    888  "Y88b                   Y8P          888                        888                                   888   Y88b                  Y8P          
 *    888    888                                888                        888                                   888    888                               
 *    888    888  .d88b.   .d88b.  888 .d8888b  888  888  .d88b.  88888b.  888  .d88b.  888d888                  888   d88P 888d888 .d88b.  8888  .d88b.  
 *    888    888 d8P  Y8b d88P"88b 888 88K      888 .88P d8P  Y8b 888 "88b 888 d8P  Y8b 888P"                    8888888P"  888P"  d88""88b "888 d8P  Y8b 
 *    888    888 88888888 888  888 888 "Y8888b. 888888K  88888888 888  888 888 88888888 888          888888      888        888    888  888  888 88888888 
 *    888  .d88P Y8b.     Y88b 888 888      X88 888 "88b Y8b.     888  888 888 Y8b.     888                      888        888    Y88..88P  888 Y8b.     
 *    8888888P"   "Y8888   "Y88888 888  88888P' 888  888  "Y8888  888  888 888  "Y8888  888                      888        888     "Y88P"   888  "Y8888  
 *                             888                                                                                                           888          
 *                        Y8b d88P                                                                                                          d88P          
 *                         "Y88P"                                                                                                         888P"           
 */

/****************************************************/
#define     PROJE_DB_LIST_QUERY     "\
CREATE TABLE IF NOT EXISTS `projeler` (\
    `isim` TEXT,\
    `tarih` INTEGER\
);"
/****************************************************/
#define     PROJE_DB_QUERY_1        "\
CREATE TABLE IF NOT EXISTS `ayarlar` (\
	`version` TEXT,\
	`saat` INTEGER,\
	`hud` REAL,\
	`global` TEXT,\
	`player` TEXT\
);"
/****************************************************/
#define     PROJE_DB_QUERY_2        "\
CREATE TABLE IF NOT EXISTS `textdrawlar` (\
    `id` INTEGER,\
    `icerik` TEXT,\
    `posX` REAL,\
    `posY` REAL,\
    `lettersizeX` REAL,\
    `lettersizeY` REAL,\
    `textsizeX` REAL,\
    `textsizeY` REAL,\
    `alignment` INTEGER,\
    `color` INTEGER,\
    `usebox` INTEGER,\
    `boxcolor` INTEGER,\
    `shadow` INTEGER,\
    `outline` INTEGER,\
    `bgcolor` INTEGER,\
    `font` INTEGER,\
    `proportional` INTEGER,\
    `selectable` INTEGER,\
    `previewModel` INTEGER,\
    `previewX` REAL,\
    `previewY` REAL,\
    `previewZ` REAL,\
    `previewZoom` REAL,\
    `previewVC1` INTEGER,\
    `previewVC2` INTEGER,\
    `globalPlayer` INTEGER,\
    `degiskenadi` TEXT,\
    `grup` INTEGER,\
    PRIMARY KEY(`id`)\
);"
/****************************************************/
#define     PROJE_DB_QUERY_3        "\
CREATE TABLE IF NOT EXISTS `gerial` (\
    `sid` INTEGER,\
    `id` INTEGER,\
    `icerik` TEXT,\
    `posX` REAL,\
    `posY` REAL,\
    `lettersizeX` REAL,\
    `lettersizeY` REAL,\
    `textsizeX` REAL,\
    `textsizeY` REAL,\
    `alignment` INTEGER,\
    `color` INTEGER,\
    `usebox` INTEGER,\
    `boxcolor` INTEGER,\
    `shadow` INTEGER,\
    `outline` INTEGER,\
    `bgcolor` INTEGER,\
    `font` INTEGER,\
    `proportional` INTEGER,\
    `selectable` INTEGER,\
    `previewModel` INTEGER,\
    `previewX` REAL,\
    `previewY` REAL,\
    `previewZ` REAL,\
    `previewZoom` REAL,\
    `previewVC1` INTEGER,\
    `previewVC2` INTEGER,\
    `globalPlayer` INTEGER,\
    `degiskenadi` TEXT,\
    `grup` INTEGER,\
    PRIMARY KEY(`sid` AUTOINCREMENT)\
);"
/****************************************************/
#define     PROJE_DB_QUERY_4        "\
CREATE TABLE IF NOT EXISTS `silinenler` (\
    `id` INTEGER,\
    `icerik` TEXT,\
    `posX` REAL,\
    `posY` REAL,\
    `lettersizeX` REAL,\
    `lettersizeY` REAL,\
    `textsizeX` REAL,\
    `textsizeY` REAL,\
    `alignment` INTEGER,\
    `color` INTEGER,\
    `usebox` INTEGER,\
    `boxcolor` INTEGER,\
    `shadow` INTEGER,\
    `outline` INTEGER,\
    `bgcolor` INTEGER,\
    `font` INTEGER,\
    `proportional` INTEGER,\
    `selectable` INTEGER,\
    `previewModel` INTEGER,\
    `previewX` REAL,\
    `previewY` REAL,\
    `previewZ` REAL,\
    `previewZoom` REAL,\
    `previewVC1` INTEGER,\
    `previewVC2` INTEGER,\
    `globalPlayer` INTEGER,\
    `degiskenadi` TEXT,\
    `grup` INTEGER,\
    `tarih` INTEGER,\
    PRIMARY KEY(`id` AUTOINCREMENT)\
);"
/****************************************************/

new
    // Proje oluşturuldu veya yüklendi mi ?
    bool: proje_durum = false,

    // Oluşturulan projelerin tutulduğu veritabanı
    DB: proje_listesi,

    // Oluşturulmuş veya yüklenmiş projelerin veritabanı
    DB: proje_db,

    // Oluşturulmuş veya yüklenmiş projenin adı
    proje_adi[PROJE_MAX_ISIM],

    // Proje saati
    proje_saat = 12
;