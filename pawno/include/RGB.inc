/*
 RGB.inc
 Copyright © 2022 Abyss Morgan. All rights reserved.

 Website: https://adm.ct8.pl

 Plugins: None
 Modules: None

 File Version: 2.5.0

 Functions:
 RGB::RGBAToHex(color,&red,&green,&blue,&alpha);
 RGB::RGBToHex(color,&red,&green,&blue);
 RGB::HexToRGBA(red,green,blue,alpha);
 RGB::HexToARGB(red,green,blue,alpha);
 RGB::HexToRGB(red,green,blue);
 RGB::RGBAToRGB(color);
 RGB::RGBToRGBA(color,alpha);
 RGB::RGBToARGB(color,alpha);
 RGB::ARGBToRGB(color);
 RGB::RGBAToARGB(color);
 RGB::ARGBToRGBA(color);
 RGB::GetRFromRGBA(color);                       //RGBA:0xFAB0A0FF R:0xFA000000
 RGB::GetGFromRGBA(color);                       //RGBA:0xFAB0A0FF G:0x00B00000
 RGB::GetBFromRGBA(color);                       //RGBA:0xFAB0A0FF B:0x0000A000
 RGB::GetAFromRGBA(color);                       //RGBA:0xFAB0A0FF A:0x000000FF
 RGB::GetRHexFromRGBA(color);                    //RGBA:0xFAB0A0FF R:0xFA
 RGB::GetGHexFromRGBA(color);                    //RGBA:0xFAB0A0FF G:0xB0
 RGB::GetBHexFromRGBA(color);                    //RGBA:0xFAB0A0FF B:0xA0
 RGB::GetAHexFromRGBA(color);                    //RGBA:0xFAB0A0FF A:0xFF
 RGB::GetColorRGBA(color);                       //Return {RGB}
 RGB::GetColorRGB(color);                        //Return {RGB}
 RGB::GetColorARGB(color);                       //Return {RGB}
 RGB::AdjustColorLuminance(color,Float:adjust);

*/

#if defined _rgb_function
	#endinput
#endif
#define _rgb_function

#define RGB::							RGB_

#define RGB_RGBAToHex(%0,%1,%2,%3,%4)	(((%1) = ((%0) >>> 24)),((%2) = (((%0) >>> 16) & 0xFF)),((%3) = (((%0) >>> 8) & 0xFF)),((%4) = ((%0) & 0xFF)))
#define RGB_RGBToHex(%0,%1,%2,%3)		(((%1) = (((%0) >>> 16) & 0xFF)),((%2) = (((%0) >>> 8) & 0xFF)),((%3) = ((%0) & 0xFF)))

#define RGB_HexToRGBA(%1,%2,%3,%4)		(((%4) & 0xFF) | (((%3) & 0xFF) << 8) | (((%2) & 0xFF) << 16) | ((%1) << 24))
#define RGB_HexToARGB(%1,%2,%3,%4)		(((%3) & 0xFF) | (((%2) & 0xFF) << 8) | (((%1) & 0xFF) << 16) | ((%4) << 24))
#define RGB_HexToRGB(%1,%2,%3)			(((%3) & 0xFF) | (((%2) & 0xFF) << 8) | (((%1) & 0xFF) << 16))

#define RGB_RGBAToRGB(%0)				(((%0) >>> 8) & 0xFFFFFF)
#define RGB_RGBToRGBA(%0,%1)			(((%0) << 8) | (%1))

#define RGB_RGBToARGB(%0,%1)			((%0) | ((%1) << 24))
#define RGB_ARGBToRGB(%0)				((%0) & 0x00FFFFFF)

#define RGB_RGBAToARGB(%0)				((((%0) << 24) & 0xFF000000) | (((%0) >>> 8) & 0xFFFFFF))
#define RGB_ARGBToRGBA(%0)				((((%0) << 8) & 0xFFFFFF00) | (((%0) >>> 24) & 0xFF))

#define RGB_GetRFromRGBA(%0)			((%0) & 0xFF000000)
#define RGB_GetGFromRGBA(%0)			((%0) & 0x00FF0000)
#define RGB_GetBFromRGBA(%0)			((%0) & 0x0000FF00)
#define RGB_GetAFromRGBA(%0)			((%0) & 0x000000FF)

#define RGB_GetRHexFromRGBA(%0)			(((%0) >>> 24) & 0xFF)
#define RGB_GetGHexFromRGBA(%0)			(((%0) >>> 16) & 0xFF)
#define RGB_GetBHexFromRGBA(%0)			(((%0) >>> 8) & 0xFF)
#define RGB_GetAHexFromRGBA(%0)			((%0) & 0xFF)

stock RGB::GetColorRGBA(color){
    new rgb_string[10];
    format(rgb_string,sizeof(rgb_string),"{%06x}",RGB::RGBAToRGB(color));
    return rgb_string;
}

stock RGB::GetColorARGB(color){
    new rgb_string[10];
    format(rgb_string,sizeof(rgb_string),"{%06x}",RGB::ARGBToRGB(color));
    return rgb_string;
}

stock RGB::GetColorRGB(color){
    new rgb_string[10];
    format(rgb_string,sizeof(rgb_string),"{%06x}",(color & 0x00FFFFFF));
    return rgb_string;
}

stock RGB::AdjustColorLuminance(color,Float:adjust){
	new rgb_r,rgb_g,rgb_b,rgb_a; 
	RGB::RGBAToHex(color,rgb_r,rgb_g,rgb_b,rgb_a);
	rgb_r = (floatround(rgb_r*adjust) & 0xFF);
	rgb_g = (floatround(rgb_g*adjust) & 0xFF);
	rgb_b = (floatround(rgb_b*adjust) & 0xFF);
	return RGB::HexToRGBA(rgb_r,rgb_g,rgb_b,rgb_a);
}

//EOF