/***
 *    8888888b.                           d8b                             888b     d888               888          888          
 *    888   Y88b                          Y8P                             8888b   d8888               888          888          
 *    888    888                                                          88888b.d88888               888          888          
 *    888   d88P 888d888 .d88b.  888  888 888  .d88b.  888  888  888      888Y88888P888  .d88b.   .d88888  .d88b.  888 .d8888b  
 *    8888888P"  888P"  d8P  Y8b 888  888 888 d8P  Y8b 888  888  888      888 Y888P 888 d88""88b d88" 888 d8P  Y8b 888 88K      
 *    888        888    88888888 Y88  88P 888 88888888 888  888  888      888  Y8P  888 888  888 888  888 88888888 888 "Y8888b. 
 *    888        888    Y8b.      Y8bd8P  888 Y8b.     Y88b 888 d88P      888   "   888 Y88..88P Y88b 888 Y8b.     888      X88 
 *    888        888     "Y8888    Y88P   888  "Y8888   "Y8888888P"       888       888  "Y88P"   "Y88888  "Y8888  888  88888P' 
 *
 */

#include    <YSI_Coding\y_hooks>

// 0.000001

Preview_Models(playerid)
{
    Dialog_Show(playerid, PREVIEW_MODELS, DIALOG_STYLE_TABLIST, "Preview Models", "\
    Model ID\t%d\n\
    X\t%.2f\n\
    Y\t%.2f\n\
    Z\t%.2f\n\
    Zoom\t%.2f\n\
    Vehicle Color 1\t%d\n\
    Vehicle Color 2\t%d\n\
    ", Dil_Mesaji[pmdls_buton_1], Dil_Mesaji[pmdls_buton_2]
    ,
        Textler[gIndex][text.preview_model],
        Textler[gIndex][text.preview_rot][0],
        Textler[gIndex][text.preview_rot][1],
        Textler[gIndex][text.preview_rot][2],
        Textler[gIndex][text.preview_rot][3],
        Textler[gIndex][text.preview_vc][0],
        Textler[gIndex][text.preview_vc][1]
    );
    return 1;
}

Preview_Models_Manuel(playerid)
{
    switch(index_pModels)
    {
        // Model ID
        case 0:
        {
            Dialog_Show(playerid, PREVIEW_MODELS_MANUEL, DIALOG_STYLE_INPUT, Dil_Mesaji[pmdls_mbaslik], "%s\n%s", Dil_Mesaji[pmdls_buton_3], Dil_Mesaji[pmdls_buton_4],
            Dil_Mesaji[pmdls_icerik_1], fex(fmt(Dil_Mesaji[pmdls_icerik_2]), Textler[gIndex][text.preview_model]));
        }

        // X
        case 1:
        {
            Dialog_Show(playerid, PREVIEW_MODELS_MANUEL, DIALOG_STYLE_INPUT, Dil_Mesaji[pmdls_mbaslik], "%s\n%s", Dil_Mesaji[pmdls_buton_3], Dil_Mesaji[pmdls_buton_4],
            Dil_Mesaji[pmdls_icerik_1], fex(fmt(Dil_Mesaji[pmdls_icerik_3]), Textler[gIndex][text.preview_rot][0]));
        }

        // Y
        case 2:
        {
            Dialog_Show(playerid, PREVIEW_MODELS_MANUEL, DIALOG_STYLE_INPUT, Dil_Mesaji[pmdls_mbaslik], "%s\n%s", Dil_Mesaji[pmdls_buton_3], Dil_Mesaji[pmdls_buton_4],
            Dil_Mesaji[pmdls_icerik_1], fex(fmt(Dil_Mesaji[pmdls_icerik_3]), Textler[gIndex][text.preview_rot][1]));
        }

        // Z
        case 3:
        {
            Dialog_Show(playerid, PREVIEW_MODELS_MANUEL, DIALOG_STYLE_INPUT, Dil_Mesaji[pmdls_mbaslik], "%s\n%s", Dil_Mesaji[pmdls_buton_3], Dil_Mesaji[pmdls_buton_4],
            Dil_Mesaji[pmdls_icerik_1], fex(fmt(Dil_Mesaji[pmdls_icerik_3]), Textler[gIndex][text.preview_rot][2]));
        }

        // Zoom
        case 4:
        {
            Dialog_Show(playerid, PREVIEW_MODELS_MANUEL, DIALOG_STYLE_INPUT, Dil_Mesaji[pmdls_mbaslik], "%s\n%s", Dil_Mesaji[pmdls_buton_3], Dil_Mesaji[pmdls_buton_4],
            Dil_Mesaji[pmdls_icerik_1], fex(fmt(Dil_Mesaji[pmdls_icerik_3]), Textler[gIndex][text.preview_rot][3]));
        }

        // Araç Rengi 1
        case 5:
        {
            Dialog_Show(playerid, PREVIEW_MODELS_MANUEL, DIALOG_STYLE_INPUT, Dil_Mesaji[pmdls_mbaslik], "%s\n%s", Dil_Mesaji[pmdls_buton_3], Dil_Mesaji[pmdls_buton_4],
            Dil_Mesaji[pmdls_icerik_1], fex(fmt(Dil_Mesaji[pmdls_icerik_2]), Textler[gIndex][text.preview_vc][0]));
        }

        // Araç Rengi 2
        case 6:
        {
            Dialog_Show(playerid, PREVIEW_MODELS_MANUEL, DIALOG_STYLE_INPUT, Dil_Mesaji[pmdls_mbaslik], "%s\n%s", Dil_Mesaji[pmdls_buton_3], Dil_Mesaji[pmdls_buton_4],
            Dil_Mesaji[pmdls_icerik_1], fex(fmt(Dil_Mesaji[pmdls_icerik_2]), Textler[gIndex][text.preview_vc][1]));
        }
    }
    return 1;
}

Dialog:PREVIEW_MODELS(playerid, response, listitem, inputtext[])
{
    if(!response) return Mouse(playerid, true, TEXTMOD_NORMAL);
    if(response)
    {
        if(timer_pModels != -1) KillTimer(timer_pModels), timer_pModels = -1;
        
        Hud_Oncelik_Textdraw();
        Hud_Goster(false);

        Textler_TMP = Textler[gIndex];

        ChatTemizle();

        Mesaj_Bilgi(playerid, Dil_Mesaji[kisayollar]);

        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 0);
        }

        index_pModels = listitem;
        timer_pModels = SetTimerEx("PreviewModels_Timer", 30, true, "d", playerid);
    }
    return 1;
}

forward PreviewModels_Timer(playerid);
public PreviewModels_Timer(playerid)
{
    new keys, ud, lr, bool: tus = false;
    GetPlayerKeys(playerid, keys, ud, lr);
    if(timer_pModels != -1)
    {
        tus = false;
        BilgiText_Gizle();

        // Sol
        if(lr < -1)
        {
            tus = true;
            switch(index_pModels)
            {
                // Model ID
                case 0:
                {
                    Textler[gIndex][text.preview_model] -= (keys == KEY_SPRINT) ? (5) : (1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Model ID: ~w~~h~%d", Textler[gIndex][text.preview_model]));
                }

                // X
                case 1:
                {
                    Textler[gIndex][text.preview_rot][0] -= (keys == KEY_SPRINT) ? (5.0) : (1.0);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~X: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][0]));
                }

                // Y
                case 2:
                {
                    Textler[gIndex][text.preview_rot][1] -= (keys == KEY_SPRINT) ? (5.0) : (1.0);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Y: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][1]));
                }

                // Z
                case 3:
                {
                    Textler[gIndex][text.preview_rot][2] -= (keys == KEY_SPRINT) ? (5.0) : (1.0);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Z: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][2]));
                }

                // Zoom
                case 4:
                {
                    Textler[gIndex][text.preview_rot][3] -= (keys == KEY_SPRINT) ? (5.0) : (0.1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Zoom: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][3]));
                }

                // Araç Rengi 1
                case 5:
                {
                    Textler[gIndex][text.preview_vc][0] -= (keys == KEY_SPRINT) ? (5) : (1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Vehicle Color 1: ~w~~h~%d", Textler[gIndex][text.preview_vc][0]));
                }

                // Araç Rengi 2
                case 6:
                {
                    Textler[gIndex][text.preview_vc][1] -= (keys == KEY_SPRINT) ? (5) : (1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Vehicle Color 2: ~w~~h~%d", Textler[gIndex][text.preview_vc][1]));
                }
            }
        }

        // Sağ
        if(lr > 1)
        {
            tus = true;
            switch(index_pModels)
            {
                // Model ID
                case 0:
                {
                    Textler[gIndex][text.preview_model] += (keys == KEY_SPRINT) ? (5) : (1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Model ID: ~w~~h~%d", Textler[gIndex][text.preview_model]));
                }

                // X
                case 1:
                {
                    Textler[gIndex][text.preview_rot][0] += (keys == KEY_SPRINT) ? (5.0) : (1.0);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~X: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][0]));
                }

                // Y
                case 2:
                {
                    Textler[gIndex][text.preview_rot][1] += (keys == KEY_SPRINT) ? (5.0) : (1.0);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Y: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][1]));
                }

                // Z
                case 3:
                {
                    Textler[gIndex][text.preview_rot][2] += (keys == KEY_SPRINT) ? (5.0) : (1.0);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Z: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][2]));
                }

                // Zoom
                case 4:
                {
                    Textler[gIndex][text.preview_rot][3] += (keys == KEY_SPRINT) ? (5.0) : (0.1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Zoom: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][3]));
                }

                // Araç Rengi 1
                case 5:
                {
                    Textler[gIndex][text.preview_vc][0] += (keys == KEY_SPRINT) ? (5) : (1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Vehicle Color 1: ~w~~h~%d", Textler[gIndex][text.preview_vc][0]));
                }

                // Araç Rengi 2
                case 6:
                {
                    Textler[gIndex][text.preview_vc][1] += (keys == KEY_SPRINT) ? (5) : (1);
                    BilgiText_Update();
                    TextDrawSetString(Bilgi_Text, fex("~g~~h~Vehicle Color 2: ~w~~h~%d", Textler[gIndex][text.preview_vc][1]));
                }
            }
        }
        if(tus) {
            Textdraw_Render(gIndex, true);
        }
    }
    return 1;
}

hook OnPlayerDisconnect(playerid, reason)
{
    if(timer_pModels != -1)
    {
        KillTimer(timer_pModels), timer_pModels = -1;
    }
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    if(PRESSED(KEY_SECONDARY_ATTACK) && timer_pModels != -1)
    {
        Bilgi_Text_Kaldir();
        KillTimer(timer_pModels), timer_pModels = -1;
        DB_Guncelle(gIndex);
        switch(index_pModels)
        {
            // Model ID
            case 0:
            {
                if(Textler_TMP[text.preview_model] != Textler[gIndex][text.preview_model])
                {
                    new orijinal_data[textdraw_yapilandirmasi];
                    
                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // X
            case 1:
            {
                if(Textler_TMP[text.preview_rot][0] != Textler[gIndex][text.preview_rot][0])
                {
                    new orijinal_data[textdraw_yapilandirmasi];
                    
                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // Y
            case 2:
            {
                if(Textler_TMP[text.preview_rot][1] != Textler[gIndex][text.preview_rot][1])
                {
                    new orijinal_data[textdraw_yapilandirmasi];
                    
                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // Z
            case 3:
            {
                if(Textler_TMP[text.preview_rot][2] != Textler[gIndex][text.preview_rot][2])
                {
                    new orijinal_data[textdraw_yapilandirmasi];
                    
                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // Zoom
            case 4:
            {
                if(Textler_TMP[text.preview_rot][3] != Textler[gIndex][text.preview_rot][3])
                {
                    new orijinal_data[textdraw_yapilandirmasi];
                    
                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // Araç Rengi 1
            case 5:
            {
                if(Textler_TMP[text.preview_vc][0] != Textler[gIndex][text.preview_vc][0])
                {
                    new orijinal_data[textdraw_yapilandirmasi];
                    
                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }

            // Araç Rengi 2
            case 6:
            {
                if(Textler_TMP[text.preview_vc][1] != Textler[gIndex][text.preview_vc][1])
                {
                    new orijinal_data[textdraw_yapilandirmasi];
                    
                    orijinal_data = Textler[gIndex];

                    Textler[gIndex] = Textler_TMP;
                    
                    gIleri_Ekle(gIndex);
                    
                    Textler[gIndex] = orijinal_data;
                }
            }
        }
        Hud_Render(true), Hud_Goster(true), Mouse(playerid, true, TEXTMOD_NORMAL);
        ChatTemizle();
        Mesaj_Bilgi(playerid, Dil_Mesaji[pmdls_bilgi_1]);
        if(spawn_modu == 1)
        {
            TogglePlayerControllable(playerid, 1);
        }
    }

    if(PRESSED(KEY_NO) && timer_pModels != -1)
    {
        Preview_Models_Manuel(playerid);
    }
    return 1;
}

Dialog:PREVIEW_MODELS_MANUEL(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        new deger, Float: f;

        ChatTemizle();

        if(isnull(inputtext)) {
            return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
        }

        switch(index_pModels)
        {
            // Model ID
            case 0:
            {
                if(sscanf(inputtext, "d", deger)) {
                    return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
                }

                if(Textler[gIndex][text.preview_model] != deger) {
                    gIleri_Ekle(gIndex);
                }

                Textler[gIndex][text.preview_model] = deger;
                BilgiText_Update();
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Model ID: ~w~~h~%d", Textler[gIndex][text.preview_model]));
            }

            // X
            case 1:
            {
                if(sscanf(inputtext, "f", f)) {
                    return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
                }

                if(Textler[gIndex][text.preview_rot][0] != f) {
                    gIleri_Ekle(gIndex);
                }

                Textler[gIndex][text.preview_rot][0] = f;
                BilgiText_Update();
                TextDrawSetString(Bilgi_Text, fex("~g~~h~X: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][0]));
            }

            // Y
            case 2:
            {
                if(sscanf(inputtext, "f", f)) {
                    return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
                }

                if(Textler[gIndex][text.preview_rot][1] != f) {
                    gIleri_Ekle(gIndex);
                }

                Textler[gIndex][text.preview_rot][1] = f;
                BilgiText_Update();
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Y: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][1]));
            }

            // Z
            case 3:
            {
                if(sscanf(inputtext, "f", f)) {
                    return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
                }

                if(Textler[gIndex][text.preview_rot][2] != f) {
                    gIleri_Ekle(gIndex);
                }

                Textler[gIndex][text.preview_rot][2] = f;
                BilgiText_Update();
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Z: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][2]));
            }

            // Zoom
            case 4:
            {
                if(sscanf(inputtext, "f", f)) {
                    return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
                }

                if(Textler[gIndex][text.preview_rot][3] != f) {
                    gIleri_Ekle(gIndex);
                }

                Textler[gIndex][text.preview_rot][3] = f;
                BilgiText_Update();
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Zoom: ~w~~h~%.2f", Textler[gIndex][text.preview_rot][3]));
            }

            // Araç Rengi 1
            case 5:
            {
                if(sscanf(inputtext, "d", deger)) {
                    return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
                }

                if(Textler[gIndex][text.preview_vc][0] != deger) {
                    gIleri_Ekle(gIndex);
                }

                Textler[gIndex][text.preview_vc][0] = deger;
                BilgiText_Update();
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Vehicle Color 1: ~w~~h~%d", Textler[gIndex][text.preview_vc][0]));
            }

            // Araç Rengi 2
            case 6:
            {
                if(sscanf(inputtext, "d", deger)) {
                    return Mesaj_Hata(playerid, Dil_Mesaji[pmdls_hata]), Preview_Models_Manuel(playerid);
                }

                if(Textler[gIndex][text.preview_vc][1] != deger) {
                    gIleri_Ekle(gIndex);
                }

                Textler[gIndex][text.preview_vc][1] = deger;
                BilgiText_Update();
                TextDrawSetString(Bilgi_Text, fex("~g~~h~Vehicle Color 2: ~w~~h~%d", Textler[gIndex][text.preview_vc][1]));
            }
        }

        DB_Guncelle(gIndex);

        Mesaj_Bilgi(playerid, Dil_Mesaji[pmdls_bilgi_1]);

        Textdraw_Render(gIndex, true);
    }
    return 1;
}