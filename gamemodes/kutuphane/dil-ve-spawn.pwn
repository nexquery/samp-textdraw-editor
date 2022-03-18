
/***
 *    8888888b.       8888888      888      
 *    888  "Y88b        888        888      
 *    888    888        888        888      
 *    888    888        888        888      
 *    888    888        888        888      
 *    888    888        888        888      
 *    888  .d88P        888        888      
 *    8888888P"       8888888      88888888 
 *
 */

#include    <YSI_Coding\y_hooks>

enum DIL_YAPILANDIRMASI
{
    // Editor
    dil@secimi[DIL_MAX_BUFFER],

    // Kısayollar
    kisayollar[DIL_MAX_BUFFER],

    // Çalışma Ortamı
    co_baslik[DIL_MAX_BUFFER],
    co_icerik_1[DIL_MAX_BUFFER],
    co_icerik_2[DIL_MAX_BUFFER],
    co_buton_1[DIL_MAX_BUFFER],
    co_mesaj_1[DIL_MAX_BUFFER],
    co_mesaj_2[DIL_MAX_BUFFER],

    // Sayfaya Git
    sayfa_baslik[DIL_MAX_BUFFER],
    sayfa_icerik[DIL_MAX_BUFFER],
    sayfa_btn1[DIL_MAX_BUFFER],
    sayfa_btn2[DIL_MAX_BUFFER],
    sayfa_hata[DIL_MAX_BUFFER],

    // Proje
    proje_baslik[DIL_MAX_BUFFER],
    proje_icerik_1[DIL_MAX_BUFFER],
    proje_icerik_2[DIL_MAX_BUFFER],
    proje_icerik_3[DIL_MAX_BUFFER],
    proje_icerik_4[DIL_MAX_BUFFER],
    proje_icerik_5[DIL_MAX_BUFFER],
    proje_buton_1[DIL_MAX_BUFFER],
    proje_buton_2[DIL_MAX_BUFFER],

    // Proje Oluştur
    po_baslik[DIL_MAX_BUFFER],
    po_metin[DIL_MAX_BUFFER],
    po_buton_1[DIL_MAX_BUFFER],
    po_buton_2[DIL_MAX_BUFFER],
    po_hata_1[DIL_MAX_BUFFER],
    po_hata_2[DIL_MAX_BUFFER],
    po_hata_3[DIL_MAX_BUFFER],
    po_hata_4[DIL_MAX_BUFFER],
    po_hata_5[DIL_MAX_BUFFER],
    po_bilgi_1[DIL_MAX_BUFFER],

    // Projeler
    pler_baslik[DIL_MAX_BUFFER],
    pler_icerik_1[DIL_MAX_BUFFER],
    pler_icerik_2[DIL_MAX_BUFFER],
    pler_icerik_3[DIL_MAX_BUFFER],
    pler_buton_1[DIL_MAX_BUFFER],
    pler_buton_2[DIL_MAX_BUFFER],
    pler_hata[DIL_MAX_BUFFER],

    // Proje Islemi
    pi_baslik[DIL_MAX_BUFFER],
    pi_icerik_1[DIL_MAX_BUFFER],
    pi_icerik_2[DIL_MAX_BUFFER],
    pi_buton_1[DIL_MAX_BUFFER],
    pi_buton_2[DIL_MAX_BUFFER],
    pi_hata_1[DIL_MAX_BUFFER],
    pi_hata_2[DIL_MAX_BUFFER],
    pi_hata_3[DIL_MAX_BUFFER],
    pi_bilgi[DIL_MAX_BUFFER],
    pi_uyari_bslk[DIL_MAX_BUFFER],
    pi_uyari_icrk[DIL_MAX_BUFFER],
    pi_uyari_btn1[DIL_MAX_BUFFER],
    pi_uyari_btn2[DIL_MAX_BUFFER],
    pi_uyari_bilgi[DIL_MAX_BUFFER],
    pi_uyari_hata[DIL_MAX_BUFFER],

    // Ice Aktar
    ia_baslik[DIL_MAX_BUFFER],
    ia_icerik_1[DIL_MAX_BUFFER],
    ia_icerik_2[DIL_MAX_BUFFER],
    ia_btn1[DIL_MAX_BUFFER],
    ia_btn2[DIL_MAX_BUFFER],
    ia_hata_1[DIL_MAX_BUFFER],
    ia_hata_2[DIL_MAX_BUFFER],
    ia_hata_3[DIL_MAX_BUFFER],
    ia_hata_4[DIL_MAX_BUFFER],
    ia_hata_5[DIL_MAX_BUFFER],
    ia_bilgi[DIL_MAX_BUFFER],

    // Dışa Aktar
    da_baslik[DIL_MAX_BUFFER],
    da_icerik_1[DIL_MAX_BUFFER],
    da_icerik_2[DIL_MAX_BUFFER],
    da_btn1[DIL_MAX_BUFFER],
    da_btn2[DIL_MAX_BUFFER],
    da_hata[DIL_MAX_BUFFER],
    da_hata2[DIL_MAX_BUFFER],
    da_bilgi[DIL_MAX_BUFFER],

    // Projeyi Kapat
    pk_hata[DIL_MAX_BUFFER],
    pk_bilgi[DIL_MAX_BUFFER],

    // Ayarlar
    ayar_baslik[DIL_MAX_BUFFER],
    ayar_header_1[DIL_MAX_BUFFER],
    ayar_header_2[DIL_MAX_BUFFER],
    ayar_icerik_1[DIL_MAX_BUFFER],
    ayar_icerik_2[DIL_MAX_BUFFER],
    ayar_icerik_3[DIL_MAX_BUFFER],
    ayar_icerik_4[DIL_MAX_BUFFER],
    ayar_buton1[DIL_MAX_BUFFER],
    ayar_buton2[DIL_MAX_BUFFER],

    // Saat
    saat_baslik[DIL_MAX_BUFFER],
    saat_buton1[DIL_MAX_BUFFER],
    saat_buton2[DIL_MAX_BUFFER],
    saat_bilgi[DIL_MAX_BUFFER],

    // Hud Konumu
    hkonum_bilgi[DIL_MAX_BUFFER],

    // Degisken - Global | Player
    dg_baslik[DIL_MAX_BUFFER],
    dg_icerik_1[DIL_MAX_BUFFER],
    dg_icerik_2[DIL_MAX_BUFFER],
    dg_buton1[DIL_MAX_BUFFER],
    dg_buton2[DIL_MAX_BUFFER],
    dg_hata[DIL_MAX_BUFFER],
    dg_bilgi[DIL_MAX_BUFFER],

    // Yeni
    yeni_baslik[DIL_MAX_BUFFER],
    yeni_icerik[DIL_MAX_BUFFER],
    yeni_btn1[DIL_MAX_BUFFER],
    yeni_btn2[DIL_MAX_BUFFER],
    yeni_textdraw[DIL_MAX_BUFFER],

    // Liste
    liste_baslik[DIL_MAX_BUFFER],
    liste_header1[DIL_MAX_BUFFER],
    liste_header2[DIL_MAX_BUFFER],
    liste_header3[DIL_MAX_BUFFER],
    liste_header4[DIL_MAX_BUFFER],
    liste_icerik[DIL_MAX_BUFFER],
    liste_btn1[DIL_MAX_BUFFER],
    liste_btn2[DIL_MAX_BUFFER],

    // Liste Islem
    lislem_baslik[DIL_MAX_BUFFER],
    lislem_icerik1[DIL_MAX_BUFFER],
    lislem_icerik2[DIL_MAX_BUFFER],
    lislem_icerik3[DIL_MAX_BUFFER],
    lislem_icerik4[DIL_MAX_BUFFER],
    lislem_icerik5[DIL_MAX_BUFFER],
    lislem_icerik6[DIL_MAX_BUFFER],
    lislem_btn1[DIL_MAX_BUFFER],
    lislem_btn2[DIL_MAX_BUFFER],

    // Liste Islem Bilgi
    tdraw_sec[DIL_MAX_BUFFER],
    tdraw_sil[DIL_MAX_BUFFER],
    tdraw_kopyala[DIL_MAX_BUFFER],
    tdraw_kopyala2[DIL_MAX_BUFFER],

    // Liste Islem Bilgi
    idgstr_bslk[DIL_MAX_BUFFER],
    idgstr_btn1[DIL_MAX_BUFFER],
    idgstr_btn2[DIL_MAX_BUFFER],
    idgstr_bilgi[DIL_MAX_BUFFER],

    // Degisken Adi
    degadi_bslk[DIL_MAX_BUFFER],
    degadi_icrk_1[DIL_MAX_BUFFER],
    degadi_icrk_2[DIL_MAX_BUFFER],
    degadi_btn1[DIL_MAX_BUFFER],
    degadi_btn2[DIL_MAX_BUFFER],
    degadi_hata[DIL_MAX_BUFFER],
    degadi_bilgi[DIL_MAX_BUFFER],
    degadi_bilgi2[DIL_MAX_BUFFER],

    // Depo
    depo_baslik[DIL_MAX_BUFFER],
    depo_icerik_1[DIL_MAX_BUFFER],
    depo_icerik_2[DIL_MAX_BUFFER],
    depo_btn_1[DIL_MAX_BUFFER],
    depo_btn_2[DIL_MAX_BUFFER],

    // Kopyala
    kopyala_bilgi[DIL_MAX_BUFFER],

    // Sil
    sil_bilgi[DIL_MAX_BUFFER],

    // Boyut | Textsize | Lettersize
    btl_baslik[DIL_MAX_BUFFER],
    btl_icrk_1[DIL_MAX_BUFFER],
    btl_icrk_2[DIL_MAX_BUFFER],
    btl_icrk_3[DIL_MAX_BUFFER],
    btl_icrk_4[DIL_MAX_BUFFER],
    btl_icrk_5[DIL_MAX_BUFFER],
    btl_icrk_6[DIL_MAX_BUFFER],
    btl_icrk_7[DIL_MAX_BUFFER],
    btl_icrk_8[DIL_MAX_BUFFER],
    btl_icrk_9[DIL_MAX_BUFFER],
    btl_icrk_10[DIL_MAX_BUFFER],
    btl_icrk_11[DIL_MAX_BUFFER],
    btl_buton_1[DIL_MAX_BUFFER],
    btl_buton_2[DIL_MAX_BUFFER],
    btl_hata_1[DIL_MAX_BUFFER],
    btl_bilgi_1[DIL_MAX_BUFFER],

    // Metin
    metin_baslik[DIL_MAX_BUFFER],
    metin_icerik[DIL_MAX_BUFFER],
    metin_icerik2[DIL_MAX_BUFFER],
    metin_buton1[DIL_MAX_BUFFER],
    metin_buton2[DIL_MAX_BUFFER],
    metin_hata[DIL_MAX_BUFFER],
    metin_bilgi[DIL_MAX_BUFFER],

    // Outline | Shadow
    os_baslik[DIL_MAX_BUFFER],
    os_icerik_1[DIL_MAX_BUFFER],
    os_icerik_2[DIL_MAX_BUFFER],
    os_buton_1[DIL_MAX_BUFFER],
    os_buton_2[DIL_MAX_BUFFER],
    os_hata[DIL_MAX_BUFFER],
    os_bilgi_1[DIL_MAX_BUFFER],

    // Renk
    renk_baslik[DIL_MAX_BUFFER],
    renk_icerik[DIL_MAX_BUFFER],
    renk_buton1[DIL_MAX_BUFFER],
    renk_buton2[DIL_MAX_BUFFER],

    // Renk - Hex
    rhex_baslik[DIL_MAX_BUFFER],
    rhex_icerik_1[DIL_MAX_BUFFER],
    rhex_icerik_2[DIL_MAX_BUFFER],
    rhex_icerik_3[DIL_MAX_BUFFER],
    rhex_icerik_4[DIL_MAX_BUFFER],
    rhex_icerik_5[DIL_MAX_BUFFER],
    rhex_icerik_6[DIL_MAX_BUFFER],
    rhex_buton_1[DIL_MAX_BUFFER],
    rhex_buton_2[DIL_MAX_BUFFER],
    rhex_hata[DIL_MAX_BUFFER],

    // Renk - RGB
    rgb_baslik[DIL_MAX_BUFFER],
    rgb_icerik_1[DIL_MAX_BUFFER],
    rgb_icerik_2[DIL_MAX_BUFFER],
    rgb_icerik_3[DIL_MAX_BUFFER],
    rgb_icerik_4[DIL_MAX_BUFFER],
    rgb_icerik_5[DIL_MAX_BUFFER],
    rgb_icerik_6[DIL_MAX_BUFFER],
    rgb_buton_1[DIL_MAX_BUFFER],
    rgb_buton_2[DIL_MAX_BUFFER],
    rgb_hata[DIL_MAX_BUFFER],

    // Renk - RGBA
    rgba_baslik[DIL_MAX_BUFFER],
    rgba_icerik_1[DIL_MAX_BUFFER],
    rgba_icerik_2[DIL_MAX_BUFFER],
    rgba_icerik_3[DIL_MAX_BUFFER],
    rgba_icerik_4[DIL_MAX_BUFFER],
    rgba_icerik_5[DIL_MAX_BUFFER],
    rgba_icerik_6[DIL_MAX_BUFFER],
    rgba_buton_1[DIL_MAX_BUFFER],
    rgba_buton_2[DIL_MAX_BUFFER],
    rgba_hata[DIL_MAX_BUFFER],

    // Preview Models
    pmdls_buton_1[DIL_MAX_BUFFER],
    pmdls_buton_2[DIL_MAX_BUFFER],
    pmdls_hata[DIL_MAX_BUFFER],
    pmdls_bilgi_1[DIL_MAX_BUFFER],

    // Preview Models Manuel
    pmdls_mbaslik[DIL_MAX_BUFFER],
    pmdls_icerik_1[DIL_MAX_BUFFER],
    pmdls_icerik_2[DIL_MAX_BUFFER],
    pmdls_icerik_3[DIL_MAX_BUFFER],
    pmdls_buton_3[DIL_MAX_BUFFER],
    pmdls_buton_4[DIL_MAX_BUFFER],

    // Geri, İleri Al
    gi_baslik[DIL_MAX_BUFFER],
    gi_icerik_1[DIL_MAX_BUFFER],
    gi_buton_1[DIL_MAX_BUFFER],
    gi_buton_2[DIL_MAX_BUFFER],
    gi_hata[DIL_MAX_BUFFER],

    // Geri, Ileri Al | Onay
    gio_baslik[DIL_MAX_BUFFER],
    gio_icerik_1[DIL_MAX_BUFFER],
    gio_buton_1[DIL_MAX_BUFFER],
    gio_buton_2[DIL_MAX_BUFFER],
    gio_bilgi_1[DIL_MAX_BUFFER],
    gio_bilgi_2[DIL_MAX_BUFFER],

    // Silinenler
    s_baslik[DIL_MAX_BUFFER],
    s_header1[DIL_MAX_BUFFER],
    s_header2[DIL_MAX_BUFFER],
    s_header3[DIL_MAX_BUFFER],
    s_header4[DIL_MAX_BUFFER],
    s_icerik1[DIL_MAX_BUFFER],
    s_icerik2[DIL_MAX_BUFFER],
    s_icerik3[DIL_MAX_BUFFER],
    s_buton1[DIL_MAX_BUFFER],
    s_buton2[DIL_MAX_BUFFER],
    s_hata[DIL_MAX_BUFFER],
    s_bilgi[DIL_MAX_BUFFER],

    // Silinenler - Temizle
    st_baslik[DIL_MAX_BUFFER],
    st_icerik1[DIL_MAX_BUFFER],
    st_icerik2[DIL_MAX_BUFFER],
    st_buton1[DIL_MAX_BUFFER],
    st_buton2[DIL_MAX_BUFFER],
    st_bilgi[DIL_MAX_BUFFER],

    // Silinenler - Tum Verileri Geri Yükle
    stgy_baslik[DIL_MAX_BUFFER],
    stgy_icerik1[DIL_MAX_BUFFER],
    stgy_buton1[DIL_MAX_BUFFER],
    stgy_buton2[DIL_MAX_BUFFER],
    stgy_bilgi[DIL_MAX_BUFFER],

    // Gruplar
    grp_hata[DIL_MAX_BUFFER],
    grp_baslik[DIL_MAX_BUFFER],
    grp_icerik1[DIL_MAX_BUFFER],
    grp_icerik2[DIL_MAX_BUFFER],
    grp_icerik3[DIL_MAX_BUFFER],
    grp_icerik4[DIL_MAX_BUFFER],
    grp_icerik5[DIL_MAX_BUFFER],
    grp_icerik6[DIL_MAX_BUFFER],
    grp_icerik7[DIL_MAX_BUFFER],
    grp_icerik8[DIL_MAX_BUFFER],
    grp_icerik9[DIL_MAX_BUFFER],
    grp_icerik10[DIL_MAX_BUFFER],
    grp_icerik11[DIL_MAX_BUFFER],
    grp_icerik12[DIL_MAX_BUFFER],
    grp_icerik13[DIL_MAX_BUFFER],
    grp_icerik14[DIL_MAX_BUFFER],
    grp_icerik15[DIL_MAX_BUFFER],
    grp_icerik16[DIL_MAX_BUFFER],
    grp_icerik17[DIL_MAX_BUFFER],
    grp_icerik18[DIL_MAX_BUFFER],
    grp_icerik19[DIL_MAX_BUFFER],
    grp_icerik20[DIL_MAX_BUFFER],
    grp_icerik21[DIL_MAX_BUFFER],
    grp_icerik22[DIL_MAX_BUFFER],
    grp_icerik23[DIL_MAX_BUFFER],
    grp_icerik24[DIL_MAX_BUFFER],
    grp_icerik25[DIL_MAX_BUFFER],
    grp_icerik26[DIL_MAX_BUFFER],
    grp_icerik27[DIL_MAX_BUFFER],
    grp_icerik28[DIL_MAX_BUFFER],
    grp_icerik29[DIL_MAX_BUFFER],
    grp_icerik30[DIL_MAX_BUFFER],
    grp_icerik31[DIL_MAX_BUFFER],
    grp_icerik32[DIL_MAX_BUFFER],
    grp_icerik33[DIL_MAX_BUFFER],
    grp_icerik34[DIL_MAX_BUFFER],
    grp_icerik35[DIL_MAX_BUFFER],
    grp_icerik36[DIL_MAX_BUFFER],
    grp_icerik37[DIL_MAX_BUFFER],
    grp_icerik38[DIL_MAX_BUFFER],
    grp_icerik39[DIL_MAX_BUFFER],
    grp_icerik40[DIL_MAX_BUFFER],
    grp_icerik41[DIL_MAX_BUFFER],
    grp_icerik42[DIL_MAX_BUFFER],
    grp_icerik43[DIL_MAX_BUFFER],
    grp_icerik44[DIL_MAX_BUFFER],
    grp_icerik45[DIL_MAX_BUFFER],
    grp_icerik46[DIL_MAX_BUFFER],
    grp_icerik47[DIL_MAX_BUFFER],
    grp_icerik48[DIL_MAX_BUFFER],
    grp_icerik49[DIL_MAX_BUFFER],
    grp_icerik50[DIL_MAX_BUFFER],
    grp_icerik51[DIL_MAX_BUFFER],
    grp_icerik52[DIL_MAX_BUFFER],
    grp_icerik53[DIL_MAX_BUFFER],
    grp_buton1[DIL_MAX_BUFFER],
    grp_buton2[DIL_MAX_BUFFER],

    // Renk Modu
    renk_modu_1[DIL_MAX_BUFFER],
    renk_modu_2[DIL_MAX_BUFFER],
    renk_modu_3[DIL_MAX_BUFFER],

    // Gruplar Bilgi
    grp_hata1[DIL_MAX_BUFFER],
    grp_hata2[DIL_MAX_BUFFER],
    grp_bilgi1[DIL_MAX_BUFFER],
    grp_bilgi2[DIL_MAX_BUFFER],
    grp_bilgi3[DIL_MAX_BUFFER],
    grp_bilgi4[DIL_MAX_BUFFER],
    grp_bilgi5[DIL_MAX_BUFFER],
    grp_bilgi6[DIL_MAX_BUFFER],
    grp_bilgi7[DIL_MAX_BUFFER],
    grp_bilgi8[DIL_MAX_BUFFER],
    grp_bilgi9[DIL_MAX_BUFFER],
    grp_bilgi10[DIL_MAX_BUFFER],
    grp_bilgi11[DIL_MAX_BUFFER],
    grp_bilgi12[DIL_MAX_BUFFER],
    grp_bilgi13[DIL_MAX_BUFFER],
    grp_bilgi14[DIL_MAX_BUFFER],
    grp_bilgi15[DIL_MAX_BUFFER],
    grp_bilgi16[DIL_MAX_BUFFER],
    grp_bilgi17[DIL_MAX_BUFFER],
    grp_bilgi18[DIL_MAX_BUFFER],

    // Gruplanacak Öğeler
    go_baslik[DIL_MAX_BUFFER],
    go_header1[DIL_MAX_BUFFER],
    go_header2[DIL_MAX_BUFFER],
    go_header3[DIL_MAX_BUFFER],
    go_header4[DIL_MAX_BUFFER],
    go_header4_n[DIL_MAX_BUFFER],
    go_header4_y[DIL_MAX_BUFFER],
    go_icerik1[DIL_MAX_BUFFER],
    go_icerik2[DIL_MAX_BUFFER],
    go_icerik3[DIL_MAX_BUFFER],
    go_buton1[DIL_MAX_BUFFER],
    go_buton2[DIL_MAX_BUFFER],

    // Gruplama: Metin Degistir
    gmd_baslik[DIL_MAX_BUFFER],
    gmd_icerik[DIL_MAX_BUFFER],
    gmd_buton1[DIL_MAX_BUFFER],
    gmd_buton2[DIL_MAX_BUFFER],
    gmd_hata[DIL_MAX_BUFFER],

    // Gruplama Outline
    goline_baslik[DIL_MAX_BUFFER],
    goline_icerik[DIL_MAX_BUFFER],
    goline_buton1[DIL_MAX_BUFFER],
    goline_buton2[DIL_MAX_BUFFER],
    goline_bilgi[DIL_MAX_BUFFER],
    goline_hata[DIL_MAX_BUFFER],

    // Gruplama Shadow
    gshdow_baslik[DIL_MAX_BUFFER],
    gshdow_icerik[DIL_MAX_BUFFER],
    gshdow_buton1[DIL_MAX_BUFFER],
    gshdow_buton2[DIL_MAX_BUFFER],
    gshdow_bilgi[DIL_MAX_BUFFER],
    gshdow_hata[DIL_MAX_BUFFER],
};

new
    // Diller bu array üzerinden okunacak
    Dil_Mesaji[DIL_YAPILANDIRMASI],

    // Dil seçildiyse sunucudan çık gir yapınca tekrar dil sormasın
    bool: dil_secimi = false,

    // Spawn modu seçildiyse sunucudan çık gir yapınca tekrar sormasın
    spawn_modu = -1
;

hook OnPlayerConnect(playerid)
{
    // Sunucuya ilk bağlanmasında izleme moduna geçir
    TogglePlayerSpectating(playerid, true);

    // Proje saatini ayarla
    SetPlayerTime(playerid, proje_saat, 00);

    // Eğer sürüm 037 ise aşağıdaki işlemleri kontrol et
    if(Server_Version() == VER_037)
    {
        // Dil seçimi yapılmadı
        if(dil_secimi == false) return Dil_Paketi(playerid);

        // Spawn modu ayarlanmadı
        if(spawn_modu == -1) return Calisma_Ortami(playerid);

        // Eğer tüm modlar seçiliyse textdrawları göster
        if(dil_secimi == true && spawn_modu != -1)
        {
            foreach(new id : Text_List)
            {
                TextDrawShowForAll(Textler[id][text.id]);
            }
        }

        // İki veri ayarlıysa hudu yükle
        Hud_Tumunu_Yukle(playerid);

        // Boş ekran
        if(spawn_modu == 0)
        {
            TogglePlayerSpectating(playerid, false);
            SetSpawnInfo(playerid, NO_TEAM, 299, 3152.7117, 410.9289, 659.6792, 267.2523, 0, 0, 0, 0, 0, 0);
            SpawnPlayer(playerid);
        }

        // Dünya
        if(spawn_modu == 1)
        {
            TogglePlayerSpectating(playerid, false);
            SetSpawnInfo(playerid, NO_TEAM, 299, 1923.5066, -2547.8245, 13.5469, 89.9278, 0, 0, 0, 0, 0, 0);
            SpawnPlayer(playerid);
            Mouse(playerid, false, TEXTMOD_YOK);
        }
    }
    return 1;
}

hook OnPlayerFinishedDwn(playerid, virtualworld)
{
    // Dil seçimi yapılmadı
    if(dil_secimi == false) return Dil_Paketi(playerid);

    // Spawn modu ayarlanmadı
    if(spawn_modu == -1) return Calisma_Ortami(playerid);

    // Eğer tüm modlar seçiliyse textdrawları göster
    if(dil_secimi == true && spawn_modu != -1)
    {
        foreach(new id : Text_List)
        {
            TextDrawShowForAll(Textler[id][text.id]);
        }
    }

    // İki veri ayarlıysa hudu yükle
    Hud_Tumunu_Yukle(playerid);

    // Boş ekran
    if(spawn_modu == 0)
    {
        TogglePlayerSpectating(playerid, false);
        SetSpawnInfo(playerid, NO_TEAM, 299, 3152.7117, 410.9289, 659.6792, 267.2523, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
    }

    // Dünya
    if(spawn_modu == 1)
    {
        TogglePlayerSpectating(playerid, false);
        SetSpawnInfo(playerid, NO_TEAM, 299, 1923.5066, -2547.8245, 13.5469, 89.9278, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
        Mouse(playerid, false, TEXTMOD_YOK);
    }
    return 1;
}

Dil_Paketi(playerid)
{
    new File: m_Dosya, buffer[100], dil[50], dosya[32], max_buffer[1024] = "{badc58}Language\t{badc58}File\n";
    if(!fexist(DOSYA_DIL_LISTE))
    {
        return printf("\nLanguage file not found: \"%s\"\n", DOSYA_DIL_LISTE), Kick(playerid);
    }
    m_Dosya = fopen(DOSYA_DIL_LISTE, io_read);
    while(fread(m_Dosya, buffer))
    {
        New_Line(buffer);
        if(!sscanf(buffer, "p<=>s[32]s[50]", dosya, dil))
        {
            strdel(dosya, strlen(dosya) - 1, strlen(dosya));
            format(max_buffer, sizeof(max_buffer), "%s%s\t%s\n", max_buffer, dil, dosya);
        }
    }
    fclose(m_Dosya);
    Dialog_Show(playerid, DIL_SECIMI, DIALOG_STYLE_TABLIST_HEADERS, "Language Selection", max_buffer, "Load", "");
    return 1;
}

Dialog:DIL_SECIMI(playerid, response, listitem, inputtext[])
{
    if(!response) return Dil_Paketi(playerid);
    if(response)
    {
        new File: m_Dosya, buffer[100], dil[50], dosya[32], index = 0;
        if(!fexist(DOSYA_DIL_LISTE))
        {
            return printf("\nLanguage file not found: \"%s\"\n", DOSYA_DIL_LISTE), Kick(playerid);
        }
        m_Dosya = fopen(DOSYA_DIL_LISTE, io_read);
        while(fread(m_Dosya, buffer))
        {
            New_Line(buffer);
            if(index == listitem && !sscanf(buffer, "p<=>s[32]s[50]", dosya, dil))
            {
                strdel(dosya, strlen(dosya) - 1, strlen(dosya));
                Dil_Yukle(playerid, dosya);
                break;
            }
            index++;
        }
        fclose(m_Dosya);
    }
    return 1;
}

Dil_Yukle(playerid, const dil_dosyasi[])
{
    new File: m_Dosya, buffer[DIL_MAX_BUFFER], pos = -1, index = 0;
    if(!fexist(fex("%s%s", DOSYA_DIL_PAKETI, dil_dosyasi)))
    {
        return printf("\nLanguage file not found: \"%s%s\"\n", DOSYA_DIL_PAKETI, dil_dosyasi), Kick(playerid);
    }
    m_Dosya = fopen(fex("%s%s", DOSYA_DIL_PAKETI, dil_dosyasi), io_read);
    while(fread(m_Dosya, buffer))
    {
        New_Line(buffer);
        if(buffer[0] == '.' && (pos = strfind(buffer, "=", false)) != -1)
        {
            strdel(buffer, 0, pos + ( (buffer[pos + 1] != ' ') ? (1) : (2) ) );
            format(Dil_Mesaji[DIL_YAPILANDIRMASI: (index * DIL_MAX_BUFFER)], DIL_MAX_BUFFER, buffer);
            index++;
        }
    }
    fclose(m_Dosya);
    dil_secimi = true;
    ChatTemizle();
    Mesaj_Bilgi(playerid, Dil_Mesaji[dil@secimi]);
    Calisma_Ortami(playerid);
    return 1;
}


/***
 *     .d8888b.                                           
 *    d88P  Y88b                                          
 *    Y88b.                                               
 *     "Y888b.   88888b.   8888b.  888  888  888 88888b.  
 *        "Y88b. 888 "88b     "88b 888  888  888 888 "88b 
 *          "888 888  888 .d888888 888  888  888 888  888 
 *    Y88b  d88P 888 d88P 888  888 Y88b 888 d88P 888  888 
 *     "Y8888P"  88888P"  "Y888888  "Y8888888P"  888  888 
 *               888                                      
 *               888                                      
 *               888                                      
 */

Calisma_Ortami(playerid)
{
    Dialog_Show(playerid, CALISMA_ORTAMI, DIALOG_STYLE_LIST, Dil_Mesaji[co_baslik], "\
    %s\n%s", Dil_Mesaji[co_buton_1], ""
    ,
        Dil_Mesaji[co_icerik_1], 
        Dil_Mesaji[co_icerik_2]
    );
    return 1;
}

Dialog:CALISMA_ORTAMI(playerid, response, listitem, inputtext[])
{
    if(!response) return Calisma_Ortami(playerid);
    if(response)
    {
        ChatTemizle();
        spawn_modu = listitem; // 0->boşEkran, 1->SpawnModu
        TogglePlayerSpectating(playerid, false);
        if(listitem == 0) SetSpawnInfo(playerid, NO_TEAM, 299, 3152.7117, 410.9289, 659.6792, 267.2523, 0, 0, 0, 0, 0, 0), Mesaj_Bilgi(playerid, Dil_Mesaji[co_mesaj_1]);
        if(listitem == 1) SetSpawnInfo(playerid, NO_TEAM, 299, 1923.5066, -2547.8245, 13.5469, 89.9278, 0, 0, 0, 0, 0, 0), Mesaj_Bilgi(playerid, Dil_Mesaji[co_mesaj_2]);
        SpawnPlayer(playerid);
        Hud_Tumunu_Yukle(playerid);
        if(spawn_modu == 1) Mouse(playerid, false, TEXTMOD_YOK);
    }
    return 1;
}

hook OnPlayerSpawn(playerid)
{
    if(spawn_modu == 0)
    {
        TogglePlayerControllable(playerid, 0);
        SetPlayerCameraPos(playerid, 3152.7117, 410.9289, 659.6792 + 45.0), SetPlayerCameraLookAt(playerid, 3152.7117, 410.9289, 659.6792 + 50.0);
    }
    return 1;
}