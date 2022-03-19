
/***
 *    88888888888                888        888                                    8888888888     888 d8b 888                          d888        d888   
 *        888                    888        888                                    888            888 Y8P 888                         d8888       d8888   
 *        888                    888        888                                    888            888     888                           888         888   
 *        888   .d88b.  888  888 888888 .d88888 888d888 8888b.  888  888  888      8888888    .d88888 888 888888 .d88b.  888d888        888         888   
 *        888  d8P  Y8b `Y8bd8P' 888   d88" 888 888P"      "88b 888  888  888      888       d88" 888 888 888   d88""88b 888P"          888         888   
 *        888  88888888   X88K   888   888  888 888    .d888888 888  888  888      888       888  888 888 888   888  888 888            888         888   
 *        888  Y8b.     .d8""8b. Y88b. Y88b 888 888    888  888 Y88b 888 d88P      888       Y88b 888 888 Y88b. Y88..88P 888            888   d8b   888   
 *        888   "Y8888  888  888  "Y888 "Y88888 888    "Y888888  "Y8888888P"       8888888888 "Y88888 888  "Y888 "Y88P"  888          8888888 Y8P 8888888
 *                                                                                                                                    
 *
 *      Kodlama:
 *          Burak (Nexor)
 *
 *      Güncelleme Notları:
 *
 *      (16.12.2021) v1.0:
 *          İlk Sürüm.
 *
 *      (18.03.2022) v1.1:
 *          Textdraw Editor yeniden yazıldı.
 *          YSI kütüphanesi eklendi.
 *          Genel performans arttırıldı.
 *          Çoklu dil desteği eklendi.
 *          Textdrawları boş bir ekran da veya oyun içi dünyada düzenleyebileceğiniz seçenek eklendi.
 *          Sprite browser eklendi.
 *          0.3.7 sürümünde kullanmak için (NexTDE.txd) dosyası hazırlandı.
 *          Silinen textdrawları geri alma özelliği eklendi.
 *          Yapılan değişiklikleri geri ve ileri alma özelliği eklendi.
 *          Gruplama özelliği geliştirildi.
 *          Bilgi text eskiden sürekli kalıyordu artık otomatik gizleniyor.
 *
 *      (19.03.2022) v1.1 - Düzenleme 1:
 *          0.3.7 sürümünde Sprite Browser'ın geri, ileri ve kapat simgelerinin gözükmeme sorunu düzeltildi.
 *          Varsayılan NexTDE.txd dosyası artık ingilizce olarak ayarlandı.
 */

// Kütüphaneler
#include    <a_samp>
#include    <player-limit>
#include    <zcmd>
#include    <YSI_Coding\y_va>
#include    <YSI_Data\y_iterate>
#include    <fi-timestamp>
#include    <easy-dialog>
#include    <sscanf2>
#include    <strlib>
#include    <RGB>

// Ayarlar, Makro, Renk
#include    "./kutuphane/ayarlar.pwn"
#include    "./kutuphane/makrolar.pwn"
#include    "./kutuphane/renkler.pwn"

// Değişkenler
#include    "./kutuphane/degiskenler-proje.pwn"
#include    "./kutuphane/degiskenler-oyuncu.pwn"
#include    "./kutuphane/degiskenler-textdraw.pwn"
#include    "./kutuphane/degiskenler-sayfa.pwn"
#include    "./kutuphane/hud/degiskenler.pwn"

// Dil Ve Spawn Seçimi
#include    "./kutuphane/dil-ve-spawn.pwn"

// Hud
#include    "./kutuphane/hud/fonksiyonlar.pwn"
#include    "./kutuphane/hud/hook.pwn"
#include    "./kutuphane/hud/proje.pwn"
#include    "./kutuphane/hud/ayarlar.pwn"
#include    "./kutuphane/hud/liste.pwn"
#include    "./kutuphane/hud/depo.pwn"
#include    "./kutuphane/hud/yeni.pwn"
#include    "./kutuphane/hud/kopyala.pwn"
#include    "./kutuphane/hud/sil.pwn"
#include    "./kutuphane/hud/konum.pwn"
#include    "./kutuphane/hud/textsize.pwn"
#include    "./kutuphane/hud/lettersize.pwn"
#include    "./kutuphane/hud/metin.pwn"
#include    "./kutuphane/hud/font.pwn"
#include    "./kutuphane/hud/hizalama.pwn"
#include    "./kutuphane/hud/oranti.pwn"
#include    "./kutuphane/hud/outline.pwn"
#include    "./kutuphane/hud/shadow.pwn"
#include    "./kutuphane/hud/renk.pwn"
#include    "./kutuphane/hud/box.pwn"
#include    "./kutuphane/hud/selectable.pwn"
#include    "./kutuphane/hud/preview-models.pwn"
#include    "./kutuphane/hud/global-player.pwn"
#include    "./kutuphane/hud/sprite-browser.pwn"
#include    "./kutuphane/hud/sayfa.pwn"

// Undo & Redo
#include    "./kutuphane/geri-ileri/degiskenler.pwn"
#include    "./kutuphane/geri-ileri/fonksiyonlar.pwn"
#include    "./kutuphane/geri-ileri/hook.pwn"

// Silinenler
#include    "./kutuphane/silinenler/degiskenler.pwn"
#include    "./kutuphane/silinenler/sil.pwn"
#include    "./kutuphane/silinenler/fonksiyonlar.pwn"

// Gruplar
#include    "./kutuphane/gruplama/degiskenler.pwn"
#include    "./kutuphane/gruplama/gruplama.pwn"
#include    "./kutuphane/gruplama/fonksiyonlar.pwn"

// Hook, Fonksiyonlar
#include    "./kutuphane/genel-hook.pwn"
#include    "./kutuphane/fonksiyonlar-genel.pwn"
#include    "./kutuphane/fonksiyonlar-textdraw.pwn"
#include    "./kutuphane/fonksiyonlar-database.pwn"

// Komutlar
#include    "./kutuphane/komutlar.pwn"

main()
{
    // YSI callbackfix dosyasını kaldır
    if(fexist("callbackfix.amx")) fremove("callbackfix.amx");

    // Bilgi
    new tarih[3], saat[3];
    gettime(saat[0], saat[1], saat[2]), getdate(tarih[0], tarih[1], tarih[2]);
    printf("\n\t=================================");
    printf("\t|                               |");
    printf("\t|      %s %s      |", TDE_HOSTNAME, TDE_VERSION);
    printf("\t|                               |");
    printf("\t|  Coding:                      |");
    printf("\t|                               |");
    printf("\t|  Burak (Nexor)                |");
    printf("\t|                               |");
    printf("\t|  Loaded Date:                 |");
    printf("\t|                               |");
    printf("\t|  %02d.%02d.%04d, %02d:%02d            |", tarih[2], tarih[1], tarih[0], saat[0], saat[1]);
    printf("\t|                               |");
    printf("\t|  Github:                      |");
    printf("\t|                               |");
    printf("\t|  github.com/nexquery          |");
    printf("\t|                               |");
    printf("\t|  Discord:                     |");
    printf("\t|                               |");
    printf("\t|  Nexor#4730                   |");
    printf("\t|                               |");
    printf("\t=================================\n");
}