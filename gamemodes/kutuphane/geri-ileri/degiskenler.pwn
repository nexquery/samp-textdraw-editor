/***
 *    888     888               888               8888888b.               888          
 *    888     888               888               888   Y88b              888          
 *    888     888               888               888    888              888          
 *    888     888 88888b.   .d88888  .d88b.       888   d88P .d88b.   .d88888  .d88b.  
 *    888     888 888 "88b d88" 888 d88""88b      8888888P" d8P  Y8b d88" 888 d88""88b 
 *    888     888 888  888 888  888 888  888      888 T88b  88888888 888  888 888  888 
 *    Y88b. .d88P 888  888 Y88b 888 Y88..88P      888  T88b Y8b.     Y88b 888 Y88..88P 
 *     "Y88888P"  888  888  "Y88888  "Y88P"       888   T88b "Y8888   "Y88888  "Y88P"  
 *                                                                                     
 *                                                                                     
 *                                                                                     
 */

#define     MAX_UNDO_REDO       300

new
    // Değişiklik yapılmış veriler burada tutulacak
    uRedo[MAX_UNDO_REDO][textdraw_yapilandirmasi],

    // SID
    uRedo_SID[MAX_UNDO_REDO],

    // Toplam yüklenen veri
    uRedo_Total,

    // Değişiklikler arasında gezinme
    uRedo_Index,

    // Enter tuşuna basınca oluşan hızlı işlemi engellemek için
    uRedo_onay_Count
;