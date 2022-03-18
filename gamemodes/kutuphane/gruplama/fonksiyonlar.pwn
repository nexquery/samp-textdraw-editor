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

Grup_Set(deger)
{
    grup_Sayfa = deger;
    return 1;
}

Grup_Renk_Reset()
{
    gRenkModu = 0;
    return 1;
}

Grup_MAX_OGE()
{
    return MAX_GRUP_OGE_ICERIK;
}

Grup_Kontrol(index)
{
    new buffer[32];
    if(Textler[index][text.grup] == 0)
    {
        format(buffer, sizeof(buffer), Dil_Mesaji[go_header4_n]);
    }
    else
    {
        format(buffer, sizeof(buffer), Dil_Mesaji[go_header4_y]);
    }
    return buffer;
}

Grup_Total()
{
    new total;
    foreach(new id : Text_List)
    {
        if(Textler[id][text.grup] == 1)
        {
            total++;
        }
    }
    return total;
}

Grup_Renk_Modu()
{
    new buffer[32];
    switch(gRenkModu)
    {
        case 0: format(buffer, sizeof(buffer), Dil_Mesaji[renk_modu_1]);
        case 1: format(buffer, sizeof(buffer), Dil_Mesaji[renk_modu_2]);
        case 2: format(buffer, sizeof(buffer), Dil_Mesaji[renk_modu_3]);
    }
    return buffer;
}