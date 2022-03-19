
/***
 *     .d8888b.                   d8b 888                 888888b.                                                           
 *    d88P  Y88b                  Y8P 888                 888  "88b                                                          
 *    Y88b.                           888                 888  .88P                                                          
 *     "Y888b.   88888b.  888d888 888 888888 .d88b.       8888888K.  888d888 .d88b.  888  888  888 .d8888b   .d88b.  888d888 
 *        "Y88b. 888 "88b 888P"   888 888   d8P  Y8b      888  "Y88b 888P"  d88""88b 888  888  888 88K      d8P  Y8b 888P"   
 *          "888 888  888 888     888 888   88888888      888    888 888    888  888 888  888  888 "Y8888b. 88888888 888     
 *    Y88b  d88P 888 d88P 888     888 Y88b. Y8b.          888   d88P 888    Y88..88P Y88b 888 d88P      X88 Y8b.     888     
 *     "Y8888P"  88888P"  888     888  "Y888 "Y8888       8888888P"  888     "Y88P"   "Y8888888P"   88888P'  "Y8888  888     
 *               888                                                                                                         
 *               888                                                                                                         
 *               888                                                                                                         
 */

#include    <YSI_Coding\y_hooks>

#define     SPRITE_MAX_LIB_LIST         50
#define     SPRITE_MAX_LIB_LEN          64

#define     SPRITE_BROWSER_MAX_LIB      10
#define     SPRITE_BROWSER_MAX_ICERIK   12

#define     SPRITE_MAX_ICERIK           70

new sprite_Icerik[][] = 
{
    // Index 0, 1, 2, 3
    {"INTRO1:intro1"},              {"INTRO2:intro2"},                  {"INTRO3:intro3"},              {"INTRO4:intro4"},
    
    // Index 4
    {"HUD:arrow"},                  {"HUD:fist"},                       {"HUD:radardisc"},              {"HUD:radarRingPlane"},
    {"HUD:radar_airYard"},          {"HUD:radar_ammugun"},              {"HUD:radar_barbers"},          {"HUD:radar_BIGSMOKE"},
    {"HUD:radar_boatyard"},         {"HUD:radar_bulldozer"},            {"HUD:radar_burgerShot"},       {"HUD:radar_cash"},
    {"HUD:radar_CATALINAPINK"},     {"HUD:radar_centre"},               {"HUD:radar_CESARVIAPANDO"},    {"HUD:radar_chicken"},
    {"HUD:radar_CJ"},               {"HUD:radar_CRASH1"},               {"HUD:radar_dateDisco"},        {"HUD:radar_dateDrink"},
    {"HUD:radar_dateFood"},         {"HUD:radar_diner"},                {"HUD:radar_emmetGun"},         {"HUD:radar_enemyAttack"},
    {"HUD:radar_fire"},             {"HUD:radar_Flag"},                 {"HUD:radar_gangB"},            {"HUD:radar_gangG"},
    {"HUD:radar_gangN"},            {"HUD:radar_gangP"},                {"HUD:radar_gangY"},            {"HUD:radar_girlfriend"},
    {"HUD:radar_gym"},              {"HUD:radar_hostpital"},            {"HUD:radar_impound"},          {"HUD:radar_light"},
    {"HUD:radar_LocoSyndicate"},    {"HUD:radar_MADDOG"},               {"HUD:radar_mafiaCasino"},      {"HUD:radar_MCSTRAP"},
    {"HUD:radar_modGarage"},        {"HUD:radar_north"},                {"HUD:radar_OGLOC"},            {"HUD:radar_pizza"},
    {"HUD:radar_police"},           {"HUD:radar_propertyG"},            {"HUD:radar_propertyR"},        {"HUD:radar_qmark"},
    {"HUD:radar_race"},             {"HUD:radar_runway"},               {"HUD:radar_RYDER"},            {"HUD:radar_saveGame"},
    {"HUD:radar_school"},           {"HUD:radar_spray"},                {"HUD:radar_SWEET"},            {"HUD:radar_tattoo"},
    {"HUD:radar_THETRUTH"},         {"HUD:radar_TORENO"},               {"HUD:radar_TorenoRanch"},      {"HUD:radar_triads"},
    {"HUD:radar_triadsCasino"},     {"HUD:radar_truck"},                {"HUD:radar_tshirt"},           {"HUD:radar_waypoint"},
    {"HUD:radar_WOOZIE"},           {"HUD:radar_ZERO"},                 {"HUD:siteM16"},                {"HUD:siterocket"},
    {"HUD:skipicon"},

    // Index 5
    {"PARTICLE:bloodpool_64"},      {"PARTICLE:carfx1"},                {"PARTICLE:cloud1"},            {"PARTICLE:cloudhigh"},
    {"PARTICLE:cloudmasked"},       {"PARTICLE:coronaheadlightline"},   {"PARTICLE:coronamoon"},        {"PARTICLE:coronareflect"},
    {"PARTICLE:coronaringb"},       {"PARTICLE:coronastar"},            {"PARTICLE:finishFlag"},        {"PARTICLE:handman"},
    {"PARTICLE:headlight"},         {"PARTICLE:headlight1"},            {"PARTICLE:lamp_shad_64"},      {"PARTICLE:lockon"},
    {"PARTICLE:lockonFire"},        {"PARTICLE:lunar"},                 {"PARTICLE:particleskid"},      {"PARTICLE:roadsignfont"},
    {"PARTICLE:seabd32"},           {"PARTICLE:shad_bike"},             {"PARTICLE:shad_car"},          {"PARTICLE:shad_exp"},
    {"PARTICLE:shad_heli"},         {"PARTICLE:shad_ped"},              {"PARTICLE:shad_rcbaron"},      {"PARTICLE:target256"},
    {"PARTICLE:txgrassbig0"},       {"PARTICLE:txgrassbig1"},           {"PARTICLE:waterclear256"},     {"PARTICLE:waterwake"},
    {"PARTICLE:white"},             {"PARTICLE:wincrack_32"},

    // Index 6
    {"LD_SPAC:white"},              {"LD_SPAC:backgnd"},                {"LD_SPAC:black"},              {"LD_SPAC:dark"},
    {"LD_SPAC:DUALITY"},            {"LD_SPAC:ex1"},                    {"LD_SPAC:ex2"},                {"LD_SPAC:ex3"},
    {"LD_SPAC:ex4"},                {"LD_SPAC:Health"},                 {"LD_SPAC:layer"},              {"LD_SPAC:light"},
    {"LD_SPAC:power"},              {"LD_SPAC:rockshp"},                {"LD_SPAC:shoot"},              {"LD_SPAC:thrustG"},
    {"LD_SPAC:tvcorn"},

    // Index 7
    {"LD_BEAT:chit"},               {"LD_BEAT:circle"},                 {"LD_BEAT:cring"},              {"LD_BEAT:cross"},
    {"LD_BEAT:down"},               {"LD_BEAT:downl"},                  {"LD_BEAT:downr"},              {"LD_BEAT:left"},
    {"LD_BEAT:right"},              {"LD_BEAT:square"},                 {"LD_BEAT:triang"},             {"LD_BEAT:up"},
    {"LD_BEAT:upl"},                {"LD_BEAT:upr"},

    // Index 8
    {"LD_BUM:blkdot"},              {"LD_BUM:bum1"},                    {"LD_BUM:bum2"},
    
    // Index 9
    {"LD_CARD:cd10c"},              {"LD_CARD:cd10d"},                  {"LD_CARD:cd10h"},              {"LD_CARD:cd10s"},
    {"LD_CARD:cd11c"},              {"LD_CARD:cd11d"},                  {"LD_CARD:cd11h"},              {"LD_CARD:cd11s"},
    {"LD_CARD:cd12c"},              {"LD_CARD:cd12d"},                  {"LD_CARD:cd12h"},              {"LD_CARD:cd12s"},
    {"LD_CARD:cd13c"},              {"LD_CARD:cd13d"},                  {"LD_CARD:cd13h"},              {"LD_CARD:cd13s"},
    {"LD_CARD:cd1c"},               {"LD_CARD:cd1d"},                   {"LD_CARD:cd1h"},               {"LD_CARD:cd1s"},
    {"LD_CARD:cd2c"},               {"LD_CARD:cd2d"},                   {"LD_CARD:cd2h"},               {"LD_CARD:cd2s"},
    {"LD_CARD:cd3c"},               {"LD_CARD:cd3d"},                   {"LD_CARD:cd3h"},               {"LD_CARD:cd3s"},
    {"LD_CARD:cd4c"},               {"LD_CARD:cd4d"},                   {"LD_CARD:cd4h"},               {"LD_CARD:cd4s"},
    {"LD_CARD:cd5c"},               {"LD_CARD:cd5d"},                   {"LD_CARD:cd5h"},               {"LD_CARD:cd5s"},
    {"LD_CARD:cd6c"},               {"LD_CARD:cd6d"},                   {"LD_CARD:cd6h"},               {"LD_CARD:cd6s"},
    {"LD_CARD:cd7c"},               {"LD_CARD:cd7d"},                   {"LD_CARD:cd7h"},               {"LD_CARD:cd7s"},
    {"LD_CARD:cd8c"},               {"LD_CARD:cd8d"},                   {"LD_CARD:cd8h"},               {"LD_CARD:cd8s"},
    {"LD_CARD:cd9c"},               {"LD_CARD:cd9d"},                   {"LD_CARD:cd9h"},               {"LD_CARD:cd9s"},
    {"LD_CARD:cdback"},

    // Index 10
    {"LD_CHAT:badchat"},            {"LD_CHAT:dpad_64"},                {"LD_CHAT:dpad_lr"},            {"LD_CHAT:goodcha"},
    {"LD_CHAT:thumbdn"},            {"LD_CHAT:thumbup"},

    // Index 11
    {"LD_DRV:blkdot"},              {"LD_DRV:brboat"},                  {"LD_DRV:brfly"},               {"LD_DRV:bronze"},
    {"LD_DRV:goboat"},              {"LD_DRV:gold"},                    {"LD_DRV:golfly"},              {"LD_DRV:naward"},
    {"LD_DRV:nawtxt"},              {"LD_DRV:ribb"},                    {"LD_DRV:ribbw"},               {"LD_DRV:silboat"},
    {"LD_DRV:silfly"},              {"LD_DRV:silver"},                  {"LD_DRV:tvbase"},              {"LD_DRV:tvcorn"},

    // Index 12
    {"LD_DUAL:backgnd"},            {"LD_DUAL:black"},                  {"LD_DUAL:dark"},               {"LD_DUAL:DUALITY"},
    {"LD_DUAL:ex1"},                {"LD_DUAL:ex2"},                    {"LD_DUAL:ex3"},                {"LD_DUAL:ex4"},
    {"LD_DUAL:Health"},             {"LD_DUAL:layer"},                  {"LD_DUAL:light"},              {"LD_DUAL:power"},
    {"LD_DUAL:rockshp"},            {"LD_DUAL:shoot"},                  {"LD_DUAL:thrustG"},            {"LD_DUAL:tvcorn"},
    {"LD_DUAL:white"},

    // Index 13
    {"LD_GRAV:bee1"},               {"LD_GRAV:bee2"},                   {"LD_GRAV:beea"},               {"LD_GRAV:bumble"},
    {"LD_GRAV:exitw"},              {"LD_GRAV:exity"},                  {"LD_GRAV:flwr"},               {"LD_GRAV:flwra"},
    {"LD_GRAV:ghost"},              {"LD_GRAV:hiscorew"},               {"LD_GRAV:hiscorey"},           {"LD_GRAV:hive"},
    {"LD_GRAV:hon"},                {"LD_GRAV:leaf"},                   {"LD_GRAV:playw"},              {"LD_GRAV:playy"},
    {"LD_GRAV:sky"},                {"LD_GRAV:thorn"},                  {"LD_GRAV:timer"},              {"LD_GRAV:tvcorn"},
    {"LD_GRAV:tvl"},                {"LD_GRAV:tvr"},

    // Index 14
    {"LD_NONE:explm01"},            {"LD_NONE:explm02"},                {"LD_NONE:explm03"},            {"LD_NONE:explm04"},
    {"LD_NONE:explm05"},            {"LD_NONE:explm06"},                {"LD_NONE:explm07"},            {"LD_NONE:explm08"},
    {"LD_NONE:explm09"},            {"LD_NONE:explm10"},                {"LD_NONE:explm11"},            {"LD_NONE:explm12"},
    {"LD_NONE:force"},              {"LD_NONE:light"},                  {"LD_NONE:ship"},               {"LD_NONE:ship2"},
    {"LD_NONE:ship3"},              {"LD_NONE:shoot"},                  {"LD_NONE:shpnorm"},            {"LD_NONE:shpwarp"},
    {"LD_NONE:thrust"},             {"LD_NONE:title"},                  {"LD_NONE:tvcorn"},             {"LD_NONE:warp"},

    // Index 15
    {"LD_OTB:bckgrnd"},             {"LD_OTB:blue"},                    {"LD_OTB:bride1"},              {"LD_OTB:bride2"},
    {"LD_OTB:bride3"},              {"LD_OTB:bride4"},                  {"LD_OTB:bride5"},              {"LD_OTB:bride6"},
    {"LD_OTB:bride7"},              {"LD_OTB:bride8"},                  {"LD_OTB:bushes"},              {"LD_OTB:fen"},
    {"LD_OTB:gride1"},              {"LD_OTB:gride2"},                  {"LD_OTB:gride3"},              {"LD_OTB:gride4"},
    {"LD_OTB:gride5"},              {"LD_OTB:gride6"},                  {"LD_OTB:gride7"},              {"LD_OTB:gride8"},
    {"LD_OTB:hrs1"},                {"LD_OTB:hrs2"},                    {"LD_OTB:hrs3"},                {"LD_OTB:hrs4"},
    {"LD_OTB:hrs5"},                {"LD_OTB:hrs6"},                    {"LD_OTB:hrs7"},                {"LD_OTB:hrs8"},
    {"LD_OTB:pole2"},               {"LD_OTB:pride1"},                  {"LD_OTB:pride2"},              {"LD_OTB:pride3"},
    {"LD_OTB:pride4"},              {"LD_OTB:pride5"},                  {"LD_OTB:pride6"},              {"LD_OTB:pride7"},
    {"LD_OTB:pride8"},              {"LD_OTB:rride1"},                  {"LD_OTB:rride2"},              {"LD_OTB:rride3"},
    {"LD_OTB:rride4"},              {"LD_OTB:rride5"},                  {"LD_OTB:rride6"},              {"LD_OTB:rride7"},
    {"LD_OTB:rride8"},              {"LD_OTB:trees"},                   {"LD_OTB:tvcorn"},              {"LD_OTB:tvl"},
    {"LD_OTB:tvr"},                 {"LD_OTB:yride1"},                  {"LD_OTB:yride2"},              {"LD_OTB:yride3"},
    {"LD_OTB:yride4"},              {"LD_OTB:yride5"},                  {"LD_OTB:yride6"},              {"LD_OTB:yride7"},
    {"LD_OTB:yride8"},

    // Index 16
    {"LD_OTB2:backbet"},            {"LD_OTB2:butnA"},                  {"LD_OTB2:butnAo"},             {"LD_OTB2:butnB"},
    {"LD_OTB2:butnBo"},             {"LD_OTB2:butnC"},                  {"LD_OTB2:Ric1"},               {"LD_OTB2:Ric2"},
    {"LD_OTB2:Ric3"},               {"LD_OTB2:Ric4"},                   {"LD_OTB2:Ric5"},

    // Index 17
    {"LD_PLAN:AirLogo"},            {"LD_PLAN:blkdot"},                 {"LD_PLAN:tvbase"},             {"LD_PLAN:tvcorn"},

    // Index 18
    {"LD_POKE:addcoin"},            {"LD_POKE:backcyan"},               {"LD_POKE:backred"},            {"LD_POKE:cd10c"},
    {"LD_POKE:cd10d"},              {"LD_POKE:cd10h"},                  {"LD_POKE:cd10s"},              {"LD_POKE:cd11c"},
    {"LD_POKE:cd11d"},              {"LD_POKE:cd11h"},                  {"LD_POKE:cd11s"},              {"LD_POKE:cd12c"},
    {"LD_POKE:cd12d"},              {"LD_POKE:cd12h"},                  {"LD_POKE:cd12s"},              {"LD_POKE:cd13c"},
    {"LD_POKE:cd13d"},              {"LD_POKE:cd13h"},                  {"LD_POKE:cd13s"},              {"LD_POKE:cd1c"},
    {"LD_POKE:cd1d"},               {"LD_POKE:cd1h"},                   {"LD_POKE:cd1s"},               {"LD_POKE:cd2c"},
    {"LD_POKE:cd2d"},               {"LD_POKE:cd2h"},                   {"LD_POKE:cd2s"},               {"LD_POKE:cd3c"},
    {"LD_POKE:cd3d"},               {"LD_POKE:cd3h"},                   {"LD_POKE:cd3s"},               {"LD_POKE:cd4c"},
    {"LD_POKE:cd4d"},               {"LD_POKE:cd4h"},                   {"LD_POKE:cd4s"},               {"LD_POKE:cd5c"},
    {"LD_POKE:cd5d"},               {"LD_POKE:cd5h"},                   {"LD_POKE:cd5s"},               {"LD_POKE:cd6c"},
    {"LD_POKE:cd6d"},               {"LD_POKE:cd6h"},                   {"LD_POKE:cd6s"},               {"LD_POKE:cd7c"},
    {"LD_POKE:cd7d"},               {"LD_POKE:cd7h"},                   {"LD_POKE:cd7s"},               {"LD_POKE:cd8c"},
    {"LD_POKE:cd8d"},               {"LD_POKE:cd8h"},                   {"LD_POKE:cd8s"},               {"LD_POKE:cd9c"},
    {"LD_POKE:cd9d"},               {"LD_POKE:cd9h"},                   {"LD_POKE:cd9s"},               {"LD_POKE:cdback"},
    {"LD_POKE:deal"},               {"LD_POKE:holdmid"},                {"LD_POKE:holdoff"},            {"LD_POKE:holdon"},
    {"LD_POKE:tvcorn"},

    // Index 19
    {"LD_POOL:ball"},               {"LD_POOL:nib"},

    // Index 20
    {"LD_RACE:race00"},             {"LD_RACE:race01"},                 {"LD_RACE:race02"},             {"LD_RACE:race03"},
    {"LD_RACE:race04"},             {"LD_RACE:race05"},                 {"LD_RACE:race06"},             {"LD_RACE:race07"},
    {"LD_RACE:race08"},             {"LD_RACE:race09"},                 {"LD_RACE:race10"},             {"LD_RACE:race11"},
    {"LD_RACE:race12"},
    
    // Index 21
    {"LD_RCE1:race00"},             {"LD_RCE1:race01"},                 {"LD_RCE1:race02"},             {"LD_RCE1:race03"},
    {"LD_RCE1:race04"},             {"LD_RCE1:race05"},

    // Index 22
    {"LD_RCE2:race06"},             {"LD_RCE2:race07"},                 {"LD_RCE2:race08"},             {"LD_RCE2:race09"},
    {"LD_RCE2:race10"},             {"LD_RCE2:race11"},

    // Index 23
    {"LD_RCE3:race12"},             {"LD_RCE3:race13"},                 {"LD_RCE3:race14"},             {"LD_RCE3:race15"},
    {"LD_RCE3:race16"},             {"LD_RCE3:race17"},

    // Index 24
    {"LD_RCE4:race18"},             {"LD_RCE4:race19"},                 {"LD_RCE4:race20"},             {"LD_RCE4:race21"},
    {"LD_RCE4:race22"},             {"LD_RCE4:race23"},

    // Index 25
    {"LD_RCE5:race24"},

    // Index 26
    {"LD_ROUL:roulbla"},            {"LD_ROUL:roulgre"},                {"LD_ROUL:roulred"},

    // Index 27
    {"LD_SHTR:bstars"},             {"LD_SHTR:cbarl"},                  {"LD_SHTR:cbarm"},              {"LD_SHTR:cbarr"},
    {"LD_SHTR:ex1"},                {"LD_SHTR:ex2"},                    {"LD_SHTR:ex3"},                {"LD_SHTR:ex4"},
    {"LD_SHTR:fire"},               {"LD_SHTR:fstar"},                  {"LD_SHTR:hbarl"},              {"LD_SHTR:hbarm"},
    {"LD_SHTR:hbarr"},              {"LD_SHTR:hi_a"},                   {"LD_SHTR:hi_b"},               {"LD_SHTR:hi_c"},
    {"LD_SHTR:kami"},               {"LD_SHTR:nmef"},                   {"LD_SHTR:pa"},                 {"LD_SHTR:pm2"},
    {"LD_SHTR:pm3"},                {"LD_SHTR:ps1"},                    {"LD_SHTR:ps2"},                {"LD_SHTR:ps3"},
    {"LD_SHTR:ship"},               {"LD_SHTR:splsh"},                  {"LD_SHTR:tvcorn"},             {"LD_SHTR:tvl"},
    {"LD_SHTR:tvr"},                {"LD_SHTR:ufo"},                    {"LD_SHTR:un_a"},               {"LD_SHTR:un_b"},
    {"LD_SHTR:un_c"},

    // Index 28
    {"LD_SLOT:bar1_o"},             {"LD_SLOT:bar2_o"},                 {"LD_SLOT:bell"},               {"LD_SLOT:cherry"},
    {"LD_SLOT:grapes"},             {"LD_SLOT:r_69"},

    // Index 29
    {"LD_TATT:10ls"},               {"LD_TATT:10ls2"},                  {"LD_TATT:10ls3"},              {"LD_TATT:10ls4"},
    {"LD_TATT:10ls5"},              {"LD_TATT:10og"},                   {"LD_TATT:10weed"},             {"LD_TATT:11dice"},
    {"LD_TATT:11dice2"},            {"LD_TATT:11ggift"},                {"LD_TATT:11grov2"},            {"LD_TATT:11grov3"},
    {"LD_TATT:11grove"},            {"LD_TATT:11jail"},                 {"LD_TATT:12angel"},            {"LD_TATT:12bndit"},
    {"LD_TATT:12cross"},            {"LD_TATT:12dager"},                {"LD_TATT:12maybr"},            {"LD_TATT:12myfac"},
    {"LD_TATT:4rip"},               {"LD_TATT:4spider"},                {"LD_TATT:4weed"},              {"LD_TATT:5cross"},
    {"LD_TATT:5cross2"},            {"LD_TATT:5cross3"},                {"LD_TATT:5gun"},               {"LD_TATT:6africa"},
    {"LD_TATT:6aztec"},             {"LD_TATT:6clown"},                 {"LD_TATT:6crown"},             {"LD_TATT:7cross"},
    {"LD_TATT:7cross2"},            {"LD_TATT:7cross3"},                {"LD_TATT:7mary"},              {"LD_TATT:8gun"},
    {"LD_TATT:8poker"},             {"LD_TATT:8sa"},                    {"LD_TATT:8sa2"},               {"LD_TATT:8sa3"},
    {"LD_TATT:8santos"},            {"LD_TATT:8westsd"},                {"LD_TATT:9bullt"},             {"LD_TATT:9crown"},
    {"LD_TATT:9gun"},               {"LD_TATT:9gun2"},                  {"LD_TATT:9homby"},             {"LD_TATT:9rasta"},

    // Index 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45
    {"LOAD0UK:load0uk"},            {"LOADSC0:loadsc0"},                {"LOADSC1:loadsc1"},            {"LOADSC2:loadsc2"},
    {"LOADSC3:loadsc3"},            {"LOADSC4:loadsc4"},                {"LOADSC5:loadsc5"},            {"LOADSC6:loadsc6"},
    {"LOADSC7:loadsc7"},            {"LOADSC8:loadsc8"},                {"LOADSC9:loadsc9"},            {"LOADSC10:loadsc10"},
    {"LOADSC11:loadsc11"},          {"LOADSC12:loadsc12"},              {"LOADSC13:loadsc13"},          {"LOADSC14:loadsc14"},
    
    // Index 46
    {"LOADSUK:loadsc1"},            {"LOADSUK:loadsc10"},               {"LOADSUK:loadsc11"},           {"LOADSUK:loadsc12"},
    {"LOADSUK:loadsc13"},           {"LOADSUK:loadsc14"},               {"LOADSUK:loadsc2"},            {"LOADSUK:loadsc3"},
    {"LOADSUK:loadsc4"},            {"LOADSUK:loadsc5"},                {"LOADSUK:loadsc6"},            {"LOADSUK:loadsc7"},
    {"LOADSUK:loadsc8"},            {"LOADSUK:loadsc9"},                {"LOADSUK:loadscuk"},

    // Index 47
    //{"OUTRO:outro"},

    // Index 48, 49
    {"SPLASH1:splash1"},            {"SPLASH2:splash2"}
};

// Kütüphane adı
new
    sprite_Lib_Count = 0,
    sprite_Lib[SPRITE_MAX_LIB_LIST][SPRITE_MAX_LIB_LEN]
;

// GUI
new Text:sprite_GUI[33] = {Text: -1, ...};

// İçerik listesi
new
    sprite_lib_Icerik[SPRITE_MAX_ICERIK][SPRITE_MAX_LIB_LEN],
    sprite_lib_Icerik_Count
;

// Sol panel sayfa
new sprite_sayfa_Sol = 1;

// Sağ panel sayfa
new sprite_sayfa_Sag = 1;

// Const bugu oluşmasını engelle
new lib_cache_isim[SPRITE_MAX_LIB_LEN + 1];

hook OnGameModeInit()
{
    new lib_sz1[SPRITE_MAX_LIB_LEN], lib_sz2[SPRITE_MAX_LIB_LEN], pos = -1;
    for(new i = 0, j = 0; i < sizeof(sprite_Icerik); i++)
    {
        pos = strfind(sprite_Icerik[i], ":", false), strmid(lib_sz2, sprite_Icerik[i], 0, pos);
        if(!isequal(lib_sz1, lib_sz2))
        {
            format(lib_sz1, SPRITE_MAX_LIB_LEN, lib_sz2);

            format(sprite_Lib[j], SPRITE_MAX_LIB_LEN, lib_sz1);

            sprite_Lib_Count++;

            j++;
        }
    }

    for(new i = 0; i < sizeof(sprite_GUI); i++)
    {
        sprite_GUI[i] = Text: -1;
    }
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text: clickedid)
{
    // ESC
    if(TextMod == TEXTMOD_SPRITE && clickedid == INVALID_TEXT_DRAW) {
        return Sprite_Kapat(), Yeni_Menu(playerid);
    }

    // Kapat
    if(TextMod == TEXTMOD_SPRITE && clickedid == sprite_GUI[3]) {
        return Sprite_Kapat(), Yeni_Menu(playerid);
    }

    // Sol panel - Sayfa geri
    if(TextMod == TEXTMOD_SPRITE && clickedid == sprite_GUI[15]) {
        if(sprite_sayfa_Sol-- <= 1) sprite_sayfa_Sol = 1;
        return Sprite_Sol_Panel_Update();
    }

    // Sol panel - Sayfa ileri
    if(TextMod == TEXTMOD_SPRITE && clickedid == sprite_GUI[16])
    {
        if(sprite_sayfa_Sol++ >= Max_Page(sprite_Lib_Count, SPRITE_BROWSER_MAX_LIB))
        {
            sprite_sayfa_Sol = Max_Page(sprite_Lib_Count, SPRITE_BROWSER_MAX_LIB);
        }
        return Sprite_Sol_Panel_Update();
    }

    // Sol panel - Tıklanan Lib
    if(TextMod == TEXTMOD_SPRITE)
    {
        for(new i = 5, j = 0; i <= 14; i++, j++)
        {
            if(clickedid == sprite_GUI[i])
            {
                new index = Page_Index_Array(sprite_sayfa_Sol, SPRITE_BROWSER_MAX_LIB, j);

                TextDrawSetString(sprite_GUI[2], fex("Sprite Browser :: %s", sprite_Lib[index]));

                Sprite_Lib_Yukle(index);

                sprite_sayfa_Sag = 1;

                Sprite_Sag_Panel_Update();

                return 1;
            }
        }
    }

    // Sağ panel - Sayfa geri
    if(TextMod == TEXTMOD_SPRITE && clickedid == sprite_GUI[30])
    {
        if(sprite_sayfa_Sag-- <= 1) sprite_sayfa_Sag = 1;
        return Sprite_Sag_Panel_Update();
    }

    // Sağ panel - Sayfa ileri
    if(TextMod == TEXTMOD_SPRITE && clickedid == sprite_GUI[31])
    {
        if(sprite_sayfa_Sag++ >= Max_Page(sprite_lib_Icerik_Count, SPRITE_BROWSER_MAX_ICERIK))
        {
            sprite_sayfa_Sag = Max_Page(sprite_lib_Icerik_Count, SPRITE_BROWSER_MAX_ICERIK);
        }
        return Sprite_Sag_Panel_Update();
    }

    // sağ panel - Tıklanan Lib
    if(TextMod == TEXTMOD_SPRITE)
    {
        for(new i = 18, j = 0; i <= 29; i++, j++)
        {
            if(clickedid == sprite_GUI[i])
            {
                new index = Page_Index_Array(sprite_sayfa_Sag, SPRITE_BROWSER_MAX_ICERIK, j);

                format(lib_cache_isim, SPRITE_MAX_LIB_LEN + 1, sprite_lib_Icerik[index]);

                Mouse(playerid, true, TEXTMOD_NORMAL);
                
                Sprite_Kapat();

                Textdraw_Sprite();
                return 1;
            }
        }
    }
    return 0;
}

Sprite_Menu()
{
    // Version
    new version = Server_Version();
    
    // Hudu ve textdrawları kaldır
    Hud_Kaldir();
    Textdraw_Kaldir();

    // Sprite browser kalıntıları varsa onları da kaldır
    for(new i = 0; i < sizeof(sprite_GUI); i++)
    {
        if(sprite_GUI[i] != Text: -1)
        {
            TextDrawDestroy(sprite_GUI[i]);
            sprite_GUI[i] = Text: -1;
        }
    }

    // Üst panel
    sprite_GUI[0] = TextDrawCreate(130.000000, 100.000000, "LD_SPAC:white");
    TextDrawBackgroundColor(sprite_GUI[0], 255);
    TextDrawFont(sprite_GUI[0], 4);
    TextDrawLetterSize(sprite_GUI[0], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[0], 1213489407);
    TextDrawSetOutline(sprite_GUI[0], 0);
    TextDrawSetProportional(sprite_GUI[0], 1);
    TextDrawSetShadow(sprite_GUI[0], 1);
    TextDrawUseBox(sprite_GUI[0], 1);
    TextDrawBoxColor(sprite_GUI[0], 255);
    TextDrawTextSize(sprite_GUI[0], 350.000000, 250.000000);
    TextDrawSetSelectable(sprite_GUI[0], 0);

    sprite_GUI[1] = TextDrawCreate(130.000000, 100.000000, "LD_SPAC:white");
    TextDrawBackgroundColor(sprite_GUI[1], -16776961);
    TextDrawFont(sprite_GUI[1], 4);
    TextDrawLetterSize(sprite_GUI[1], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[1], 153);
    TextDrawSetOutline(sprite_GUI[1], 1);
    TextDrawSetProportional(sprite_GUI[1], 1);
    TextDrawUseBox(sprite_GUI[1], 1);
    TextDrawBoxColor(sprite_GUI[1], 255);
    TextDrawTextSize(sprite_GUI[1], 350.000000, 16.000000);
    TextDrawSetSelectable(sprite_GUI[1], 0);

    sprite_GUI[2] = TextDrawCreate(135.000000, 103.000000, "Sprite Browser");
    TextDrawBackgroundColor(sprite_GUI[2], 0);
    TextDrawFont(sprite_GUI[2], 1);
    TextDrawLetterSize(sprite_GUI[2], 0.170000, 1.000000);
    TextDrawColor(sprite_GUI[2], -136866561);
    TextDrawSetOutline(sprite_GUI[2], 1);
    TextDrawSetProportional(sprite_GUI[2], 1);
    TextDrawSetSelectable(sprite_GUI[2], 0);

    sprite_GUI[3] = TextDrawCreate(466.000000, 101.000000, (version == VER_03DL) ? ("mdl-2000:kapat") : ("NexTDE:kapat"));
    TextDrawBackgroundColor(sprite_GUI[3], 255);
    TextDrawFont(sprite_GUI[3], 4);
    TextDrawLetterSize(sprite_GUI[3], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[3], -1);
    TextDrawSetOutline(sprite_GUI[3], 0);
    TextDrawSetProportional(sprite_GUI[3], 1);
    TextDrawSetShadow(sprite_GUI[3], 1);
    TextDrawUseBox(sprite_GUI[3], 1);
    TextDrawBoxColor(sprite_GUI[3], 255);
    TextDrawTextSize(sprite_GUI[3], 11.000000, 15.000000);
    TextDrawSetSelectable(sprite_GUI[3], 1);

    // Sol panel
    sprite_GUI[4] = TextDrawCreate(130.000000, 116.000000, "LD_SPAC:white");
    TextDrawBackgroundColor(sprite_GUI[4], -16776961);
    TextDrawFont(sprite_GUI[4], 4);
    TextDrawLetterSize(sprite_GUI[4], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[4], 80);
    TextDrawSetOutline(sprite_GUI[4], 1);
    TextDrawSetProportional(sprite_GUI[4], 1);
    TextDrawUseBox(sprite_GUI[4], 1);
    TextDrawBoxColor(sprite_GUI[4], 255);
    TextDrawTextSize(sprite_GUI[4], 70.000000, 234.000000);
    TextDrawSetSelectable(sprite_GUI[4], 0);

    sprite_GUI[5] = TextDrawCreate(135.000000, 125.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[5], 64);
    TextDrawFont(sprite_GUI[5], 1);
    TextDrawLetterSize(sprite_GUI[5], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[5], -1);
    TextDrawSetOutline(sprite_GUI[5], 1);
    TextDrawSetProportional(sprite_GUI[5], 1);
    TextDrawUseBox(sprite_GUI[5], 1);
    TextDrawBoxColor(sprite_GUI[5], 0);
    TextDrawTextSize(sprite_GUI[5], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[5], 1);

    sprite_GUI[6] = TextDrawCreate(135.000000, 145.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[6], 64);
    TextDrawFont(sprite_GUI[6], 1);
    TextDrawLetterSize(sprite_GUI[6], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[6], -1);
    TextDrawSetOutline(sprite_GUI[6], 1);
    TextDrawSetProportional(sprite_GUI[6], 1);
    TextDrawUseBox(sprite_GUI[6], 1);
    TextDrawBoxColor(sprite_GUI[6], 0);
    TextDrawTextSize(sprite_GUI[6], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[6], 1);

    sprite_GUI[7] = TextDrawCreate(135.000000, 165.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[7], 64);
    TextDrawFont(sprite_GUI[7], 1);
    TextDrawLetterSize(sprite_GUI[7], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[7], -1);
    TextDrawSetOutline(sprite_GUI[7], 1);
    TextDrawSetProportional(sprite_GUI[7], 1);
    TextDrawUseBox(sprite_GUI[7], 1);
    TextDrawBoxColor(sprite_GUI[7], 0);
    TextDrawTextSize(sprite_GUI[7], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[7], 1);

    sprite_GUI[8] = TextDrawCreate(135.000000, 185.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[8], 64);
    TextDrawFont(sprite_GUI[8], 1);
    TextDrawLetterSize(sprite_GUI[8], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[8], -1);
    TextDrawSetOutline(sprite_GUI[8], 1);
    TextDrawSetProportional(sprite_GUI[8], 1);
    TextDrawUseBox(sprite_GUI[8], 1);
    TextDrawBoxColor(sprite_GUI[8], 0);
    TextDrawTextSize(sprite_GUI[8], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[8], 1);

    sprite_GUI[9] = TextDrawCreate(135.000000, 205.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[9], 64);
    TextDrawFont(sprite_GUI[9], 1);
    TextDrawLetterSize(sprite_GUI[9], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[9], -1);
    TextDrawSetOutline(sprite_GUI[9], 1);
    TextDrawSetProportional(sprite_GUI[9], 1);
    TextDrawUseBox(sprite_GUI[9], 1);
    TextDrawBoxColor(sprite_GUI[9], 0);
    TextDrawTextSize(sprite_GUI[9], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[9], 1);

    sprite_GUI[10] = TextDrawCreate(135.000000, 225.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[10], 64);
    TextDrawFont(sprite_GUI[10], 1);
    TextDrawLetterSize(sprite_GUI[10], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[10], -1);
    TextDrawSetOutline(sprite_GUI[10], 1);
    TextDrawSetProportional(sprite_GUI[10], 1);
    TextDrawUseBox(sprite_GUI[10], 1);
    TextDrawBoxColor(sprite_GUI[10], 0);
    TextDrawTextSize(sprite_GUI[10], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[10], 1);

    sprite_GUI[11] = TextDrawCreate(135.000000, 245.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[11], 64);
    TextDrawFont(sprite_GUI[11], 1);
    TextDrawLetterSize(sprite_GUI[11], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[11], -1);
    TextDrawSetOutline(sprite_GUI[11], 1);
    TextDrawSetProportional(sprite_GUI[11], 1);
    TextDrawUseBox(sprite_GUI[11], 1);
    TextDrawBoxColor(sprite_GUI[11], 0);
    TextDrawTextSize(sprite_GUI[11], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[11], 1);

    sprite_GUI[12] = TextDrawCreate(135.000000, 265.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[12], 64);
    TextDrawFont(sprite_GUI[12], 1);
    TextDrawLetterSize(sprite_GUI[12], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[12], -1);
    TextDrawSetOutline(sprite_GUI[12], 1);
    TextDrawSetProportional(sprite_GUI[12], 1);
    TextDrawUseBox(sprite_GUI[12], 1);
    TextDrawBoxColor(sprite_GUI[12], 0);
    TextDrawTextSize(sprite_GUI[12], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[12], 1);

    sprite_GUI[13] = TextDrawCreate(135.000000, 285.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[13], 64);
    TextDrawFont(sprite_GUI[13], 1);
    TextDrawLetterSize(sprite_GUI[13], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[13], -1);
    TextDrawSetOutline(sprite_GUI[13], 1);
    TextDrawSetProportional(sprite_GUI[13], 1);
    TextDrawUseBox(sprite_GUI[13], 1);
    TextDrawBoxColor(sprite_GUI[13], 0);
    TextDrawTextSize(sprite_GUI[13], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[13], 1);

    sprite_GUI[14] = TextDrawCreate(135.000000, 305.000000, "LOADSC11");
    TextDrawBackgroundColor(sprite_GUI[14], 64);
    TextDrawFont(sprite_GUI[14], 1);
    TextDrawLetterSize(sprite_GUI[14], 0.200000, 1.000000);
    TextDrawColor(sprite_GUI[14], -1);
    TextDrawSetOutline(sprite_GUI[14], 1);
    TextDrawSetProportional(sprite_GUI[14], 1);
    TextDrawUseBox(sprite_GUI[14], 1);
    TextDrawBoxColor(sprite_GUI[14], 0);
    TextDrawTextSize(sprite_GUI[14], 195.000000, 10.000000);
    TextDrawSetSelectable(sprite_GUI[14], 1);

    sprite_GUI[15] = TextDrawCreate(135.000000, 332.000000, (version == VER_03DL) ? ("mdl-2000:sol") : ("NexTDE:sol"));
    TextDrawBackgroundColor(sprite_GUI[15], 255);
    TextDrawFont(sprite_GUI[15], 4);
    TextDrawLetterSize(sprite_GUI[15], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[15], -104192769);
    TextDrawSetOutline(sprite_GUI[15], 0);
    TextDrawSetProportional(sprite_GUI[15], 1);
    TextDrawSetShadow(sprite_GUI[15], 1);
    TextDrawUseBox(sprite_GUI[15], 1);
    TextDrawBoxColor(sprite_GUI[15], 255);
    TextDrawTextSize(sprite_GUI[15], 9.000000, 15.000000);
    TextDrawSetSelectable(sprite_GUI[15], 1);

    sprite_GUI[16] = TextDrawCreate(188.000000, 332.000000, (version == VER_03DL) ? ("mdl-2000:sag") : ("NexTDE:sag"));
    TextDrawBackgroundColor(sprite_GUI[16], 255);
    TextDrawFont(sprite_GUI[16], 4);
    TextDrawLetterSize(sprite_GUI[16], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[16], -104192769);
    TextDrawSetOutline(sprite_GUI[16], 0);
    TextDrawSetProportional(sprite_GUI[16], 1);
    TextDrawSetShadow(sprite_GUI[16], 1);
    TextDrawUseBox(sprite_GUI[16], 1);
    TextDrawBoxColor(sprite_GUI[16], 255);
    TextDrawTextSize(sprite_GUI[16], 9.000000, 15.000000);
    TextDrawSetSelectable(sprite_GUI[16], 1);

    sprite_GUI[17] = TextDrawCreate(165.000000, 333.000000, "1 / 1");
    TextDrawAlignment(sprite_GUI[17], 2);
    TextDrawBackgroundColor(sprite_GUI[17], 53);
    TextDrawFont(sprite_GUI[17], 1);
    TextDrawLetterSize(sprite_GUI[17], 0.210000, 1.000000);
    TextDrawColor(sprite_GUI[17], -846925313);
    TextDrawSetOutline(sprite_GUI[17], 1);
    TextDrawSetProportional(sprite_GUI[17], 1);
    TextDrawSetSelectable(sprite_GUI[17], 0);

    // İç kısım
    sprite_GUI[18] = TextDrawCreate(230.000000, 130.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[18], 255);
    TextDrawFont(sprite_GUI[18], 4);
    TextDrawLetterSize(sprite_GUI[18], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[18], -1);
    TextDrawSetOutline(sprite_GUI[18], 0);
    TextDrawSetProportional(sprite_GUI[18], 1);
    TextDrawSetShadow(sprite_GUI[18], 1);
    TextDrawUseBox(sprite_GUI[18], 1);
    TextDrawBoxColor(sprite_GUI[18], 255);
    TextDrawTextSize(sprite_GUI[18], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[18], 1);

    sprite_GUI[19] = TextDrawCreate(290.000000, 130.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[19], 255);
    TextDrawFont(sprite_GUI[19], 4);
    TextDrawLetterSize(sprite_GUI[19], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[19], -1);
    TextDrawSetOutline(sprite_GUI[19], 0);
    TextDrawSetProportional(sprite_GUI[19], 1);
    TextDrawSetShadow(sprite_GUI[19], 1);
    TextDrawUseBox(sprite_GUI[19], 1);
    TextDrawBoxColor(sprite_GUI[19], 255);
    TextDrawTextSize(sprite_GUI[19], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[19], 1);

    sprite_GUI[20] = TextDrawCreate(350.000000, 130.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[20], 255);
    TextDrawFont(sprite_GUI[20], 4);
    TextDrawLetterSize(sprite_GUI[20], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[20], -1);
    TextDrawSetOutline(sprite_GUI[20], 0);
    TextDrawSetProportional(sprite_GUI[20], 1);
    TextDrawSetShadow(sprite_GUI[20], 1);
    TextDrawUseBox(sprite_GUI[20], 1);
    TextDrawBoxColor(sprite_GUI[20], 255);
    TextDrawTextSize(sprite_GUI[20], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[20], 1);

    sprite_GUI[21] = TextDrawCreate(410.000000, 130.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[21], 255);
    TextDrawFont(sprite_GUI[21], 4);
    TextDrawLetterSize(sprite_GUI[21], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[21], -1);
    TextDrawSetOutline(sprite_GUI[21], 0);
    TextDrawSetProportional(sprite_GUI[21], 1);
    TextDrawSetShadow(sprite_GUI[21], 1);
    TextDrawUseBox(sprite_GUI[21], 1);
    TextDrawBoxColor(sprite_GUI[21], 255);
    TextDrawTextSize(sprite_GUI[21], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[21], 1);

    sprite_GUI[22] = TextDrawCreate(230.000000, 190.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[22], 255);
    TextDrawFont(sprite_GUI[22], 4);
    TextDrawLetterSize(sprite_GUI[22], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[22], -1);
    TextDrawSetOutline(sprite_GUI[22], 0);
    TextDrawSetProportional(sprite_GUI[22], 1);
    TextDrawSetShadow(sprite_GUI[22], 1);
    TextDrawUseBox(sprite_GUI[22], 1);
    TextDrawBoxColor(sprite_GUI[22], 255);
    TextDrawTextSize(sprite_GUI[22], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[22], 1);

    sprite_GUI[23] = TextDrawCreate(290.000000, 190.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[23], 255);
    TextDrawFont(sprite_GUI[23], 4);
    TextDrawLetterSize(sprite_GUI[23], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[23], -1);
    TextDrawSetOutline(sprite_GUI[23], 0);
    TextDrawSetProportional(sprite_GUI[23], 1);
    TextDrawSetShadow(sprite_GUI[23], 1);
    TextDrawUseBox(sprite_GUI[23], 1);
    TextDrawBoxColor(sprite_GUI[23], 255);
    TextDrawTextSize(sprite_GUI[23], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[23], 1);

    sprite_GUI[24] = TextDrawCreate(350.000000, 190.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[24], 255);
    TextDrawFont(sprite_GUI[24], 4);
    TextDrawLetterSize(sprite_GUI[24], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[24], -1);
    TextDrawSetOutline(sprite_GUI[24], 0);
    TextDrawSetProportional(sprite_GUI[24], 1);
    TextDrawSetShadow(sprite_GUI[24], 1);
    TextDrawUseBox(sprite_GUI[24], 1);
    TextDrawBoxColor(sprite_GUI[24], 255);
    TextDrawTextSize(sprite_GUI[24], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[24], 1);

    sprite_GUI[25] = TextDrawCreate(410.000000, 190.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[25], 255);
    TextDrawFont(sprite_GUI[25], 4);
    TextDrawLetterSize(sprite_GUI[25], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[25], -1);
    TextDrawSetOutline(sprite_GUI[25], 0);
    TextDrawSetProportional(sprite_GUI[25], 1);
    TextDrawSetShadow(sprite_GUI[25], 1);
    TextDrawUseBox(sprite_GUI[25], 1);
    TextDrawBoxColor(sprite_GUI[25], 255);
    TextDrawTextSize(sprite_GUI[25], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[25], 1);

    sprite_GUI[26] = TextDrawCreate(230.000000, 250.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[26], 255);
    TextDrawFont(sprite_GUI[26], 4);
    TextDrawLetterSize(sprite_GUI[26], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[26], -1);
    TextDrawSetOutline(sprite_GUI[26], 0);
    TextDrawSetProportional(sprite_GUI[26], 1);
    TextDrawSetShadow(sprite_GUI[26], 1);
    TextDrawUseBox(sprite_GUI[26], 1);
    TextDrawBoxColor(sprite_GUI[26], 255);
    TextDrawTextSize(sprite_GUI[26], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[26], 1);

    sprite_GUI[27] = TextDrawCreate(290.000000, 250.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[27], 255);
    TextDrawFont(sprite_GUI[27], 4);
    TextDrawLetterSize(sprite_GUI[27], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[27], -1);
    TextDrawSetOutline(sprite_GUI[27], 0);
    TextDrawSetProportional(sprite_GUI[27], 1);
    TextDrawSetShadow(sprite_GUI[27], 1);
    TextDrawUseBox(sprite_GUI[27], 1);
    TextDrawBoxColor(sprite_GUI[27], 255);
    TextDrawTextSize(sprite_GUI[27], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[27], 1);

    sprite_GUI[28] = TextDrawCreate(350.000000, 250.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[28], 255);
    TextDrawFont(sprite_GUI[28], 4);
    TextDrawLetterSize(sprite_GUI[28], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[28], -1);
    TextDrawSetOutline(sprite_GUI[28], 0);
    TextDrawSetProportional(sprite_GUI[28], 1);
    TextDrawSetShadow(sprite_GUI[28], 1);
    TextDrawUseBox(sprite_GUI[28], 1);
    TextDrawBoxColor(sprite_GUI[28], 255);
    TextDrawTextSize(sprite_GUI[28], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[28], 1);

    sprite_GUI[29] = TextDrawCreate(410.000000, 250.000000, "LD_CARD:cd8s");
    TextDrawBackgroundColor(sprite_GUI[29], 255);
    TextDrawFont(sprite_GUI[29], 4);
    TextDrawLetterSize(sprite_GUI[29], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[29], -1);
    TextDrawSetOutline(sprite_GUI[29], 0);
    TextDrawSetProportional(sprite_GUI[29], 1);
    TextDrawSetShadow(sprite_GUI[29], 1);
    TextDrawUseBox(sprite_GUI[29], 1);
    TextDrawBoxColor(sprite_GUI[29], 255);
    TextDrawTextSize(sprite_GUI[29], 32.000000, 32.000000);
    TextDrawSetSelectable(sprite_GUI[29], 1);

    sprite_GUI[30] = TextDrawCreate(295.000000, 332.000000, (version == VER_03DL) ? ("mdl-2000:sol") : ("NexTDE:sol"));
    TextDrawBackgroundColor(sprite_GUI[30], 255);
    TextDrawFont(sprite_GUI[30], 4);
    TextDrawLetterSize(sprite_GUI[30], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[30], -104192769);
    TextDrawSetOutline(sprite_GUI[30], 0);
    TextDrawSetProportional(sprite_GUI[30], 1);
    TextDrawSetShadow(sprite_GUI[30], 1);
    TextDrawUseBox(sprite_GUI[30], 1);
    TextDrawBoxColor(sprite_GUI[30], 255);
    TextDrawTextSize(sprite_GUI[30], 9.000000, 15.000000);
    TextDrawSetSelectable(sprite_GUI[30], 1);

    sprite_GUI[31] = TextDrawCreate(368.000000, 332.000000, (version == VER_03DL) ? ("mdl-2000:sag") : ("NexTDE:sag"));
    TextDrawBackgroundColor(sprite_GUI[31], 255);
    TextDrawFont(sprite_GUI[31], 4);
    TextDrawLetterSize(sprite_GUI[31], 0.500000, 1.000000);
    TextDrawColor(sprite_GUI[31], -104192769);
    TextDrawSetOutline(sprite_GUI[31], 0);
    TextDrawSetProportional(sprite_GUI[31], 1);
    TextDrawSetShadow(sprite_GUI[31], 1);
    TextDrawUseBox(sprite_GUI[31], 1);
    TextDrawBoxColor(sprite_GUI[31], 255);
    TextDrawTextSize(sprite_GUI[31], 9.000000, 15.000000);
    TextDrawSetSelectable(sprite_GUI[31], 1);

    sprite_GUI[32] = TextDrawCreate(335.000000, 333.000000, "1 / 5");
    TextDrawAlignment(sprite_GUI[32], 2);
    TextDrawBackgroundColor(sprite_GUI[32], 53);
    TextDrawFont(sprite_GUI[32], 1);
    TextDrawLetterSize(sprite_GUI[32], 0.210000, 1.000000);
    TextDrawColor(sprite_GUI[32], -846925313);
    TextDrawSetOutline(sprite_GUI[32], 1);
    TextDrawSetProportional(sprite_GUI[32], 1);
    TextDrawSetSelectable(sprite_GUI[32], 0);

    // Sol panelin içeriklerini hazırla
    Sprite_Sol_Panel_Update();

    // Browserı yükle
    for(new i = 0; i <= 17; i++)
    {
        TextDrawShowForAll(sprite_GUI[i]);
    }
    return 1;
}

Sprite_Sol_Panel_Update()
{
    // İsimleri gizle
    for(new i = 5; i <= 14; i++)
    {
        TextDrawHideForAll(sprite_GUI[i]);
    }

    // Kütüphaneleri yükle
    new pos1 = Page_Pos1(sprite_sayfa_Sol, SPRITE_BROWSER_MAX_LIB);
    new pos2 = Page_Pos2(sprite_sayfa_Sol, sprite_Lib_Count, SPRITE_BROWSER_MAX_LIB);

    for(new i = pos1, j = 5; i < pos2; i++, j++)
    {
        TextDrawSetString(sprite_GUI[j], sprite_Lib[i]);
        TextDrawShowForAll(sprite_GUI[j]);
    }

    // Sayfa sayısını ayarla
    TextDrawSetString(sprite_GUI[17], fex("%d / %d", sprite_sayfa_Sol, Max_Page(sprite_Lib_Count, SPRITE_BROWSER_MAX_LIB)));
    return 1;
}

Sprite_Sag_Panel_Update()
{
    // İsimleri gizle
    for(new i = 18; i <= 29; i++)
    {
        TextDrawHideForAll(sprite_GUI[i]);
    }

    // Kütüphaneleri yükle
    new pos1 = Page_Pos1(sprite_sayfa_Sag, SPRITE_BROWSER_MAX_ICERIK);
    new pos2 = Page_Pos2(sprite_sayfa_Sag, sprite_lib_Icerik_Count, SPRITE_BROWSER_MAX_ICERIK);

    for(new i = pos1, j = 18; i < pos2; i++, j++)
    {
        TextDrawSetString(sprite_GUI[j], sprite_lib_Icerik[i]);
        TextDrawShowForAll(sprite_GUI[j]);
    }

    // Sayfa sayısını ayarla
    TextDrawSetString(sprite_GUI[32], fex("%d / %d", sprite_sayfa_Sag, Max_Page(sprite_lib_Icerik_Count, SPRITE_BROWSER_MAX_ICERIK)));

    TextDrawShowForAll(sprite_GUI[30]);
    TextDrawShowForAll(sprite_GUI[31]);
    TextDrawShowForAll(sprite_GUI[32]);
    return 1;
}

Sprite_Lib_Yukle(index)
{
    // Totali sıfırla
    sprite_lib_Icerik_Count = 0;

    // Array verilerini sıfırla
    for(new i = 0; i < SPRITE_MAX_ICERIK; i++)
    {
        sprite_lib_Icerik[i][0] = '\0';
    }

    // Indexdeki verileri çek
    new lib_sz1[SPRITE_MAX_LIB_LEN], lib_sz2[SPRITE_MAX_LIB_LEN], pos = -1;
    for(new i = 0, j = -1; i < sizeof(sprite_Icerik); i++)
    {
        pos = strfind(sprite_Icerik[i], ":", false), strmid(lib_sz2, sprite_Icerik[i], 0, pos);
        if(!isequal(lib_sz1, lib_sz2))
        {
            j++;
            if(j > index)
            {
                break;
            }
            format(lib_sz1, SPRITE_MAX_LIB_LEN, lib_sz2);
            if(j == index)
            {
                format(sprite_lib_Icerik[sprite_lib_Icerik_Count], SPRITE_MAX_LIB_LEN, sprite_Icerik[i]);
                sprite_lib_Icerik_Count++;
            }
        }
        else
        {
            if(j == index)
            {
                format(sprite_lib_Icerik[sprite_lib_Icerik_Count], SPRITE_MAX_LIB_LEN, sprite_Icerik[i]);
                sprite_lib_Icerik_Count++;
            }
        }
    }
    return;
}

Sprite_Kapat()
{
    for(new i = 0; i < sizeof(sprite_GUI); i++)
    {
        if(sprite_GUI[i] != Text: -1)
        {
            TextDrawDestroy(sprite_GUI[i]);
            sprite_GUI[i] = Text: -1;
        }
    }

    for(new i = 0; i < SPRITE_MAX_ICERIK; i++)
    {
        sprite_lib_Icerik[i][0] = '\0';
    }

    sprite_lib_Icerik_Count = 0;

    sprite_sayfa_Sol = 1;

    sprite_sayfa_Sag = 1;

    // Textdraw ve Hudu yeniden yükle
    foreach(new id : Text_List) { Textdraw_Render(id, true); }
    Hud_Render(false), Hud_Goster(true);
    return 1;
}

Sprite_Cache_Get()
{
    new buffer[SPRITE_MAX_LIB_LEN + 1];
    format(buffer, sizeof(buffer), lib_cache_isim);
    return buffer;
}