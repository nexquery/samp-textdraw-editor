
/***
 *           d8888                           888                  
 *          d88888                           888                  
 *         d88P888                           888                  
 *        d88P 888 888  888  8888b.  888d888 888  8888b.  888d888 
 *       d88P  888 888  888     "88b 888P"   888     "88b 888P"   
 *      d88P   888 888  888 .d888888 888     888 .d888888 888     
 *     d8888888888 Y88b 888 888  888 888     888 888  888 888     
 *    d88P     888  "Y88888 "Y888888 888     888 "Y888888 888     
 *                      888                                       
 *                 Y8b d88P                                       
 *                  "Y88P"                                        
 */

// Uzun geri aramaların adını kısalt
DEFINE_HOOK_REPLACEMENT__(Downloading, Dwn);

// Sunucu ayarları
#define     TDE_HOSTNAME        "Textdraw Editor"
#define     TDE_VERSION         "1.5"

// Timestamp verileri hangi saat diliminde hesaplansın?
#define     GMT_TIME            3

// Sunucunun hangi sürüm olduğunu kontrol etme
#define     VER_037             0
#define     VER_03DL            1

// Dil dosyalarının konumları
#define     DIL_MAX_BUFFER      300
#define     DOSYA_DIL_LISTE     "languages/languages.txt"
#define     DOSYA_DIL_PAKETI    "languages/translations/"

// Proje
#define     PROJE_MAX_ISIM      32
#define     DOSYA_PROJE         "projects.db"
#define     DOSYA_PROJE_DB      "projects/%s.db"

// Proje Listesi
#define     PROJE_MAX_ICERIK    15

// Hud Listesi
#define     HUD_LISTE_ICERIK    15
#define     HUD_LISTE_BUFFER    2000

// İçe Aktar
#define     DOSYA_ICE_AKTAR     "import/%s"

// Dışa Aktar
#define     DOSYA_DISA_AKTAR    "export/%s.txt"

// Seçilen Textdrawın Kaybolma Süresi
#define     TEXT_SECILEN_TIMER  650