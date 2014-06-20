/***********************************************************************
 * $Id:: lpc_colors.h 745 2008-05-13 19:59:29Z pdurgesh                $
 *
 * Project: Color definitions
 *
 * Description:
 *     This package contains functions for color mapping, color
 *     conversion, and common defines.
 *
 *     The palette table function can be configured for 555 or 565
 *     color.
 *
 * Notes:
 *     Color entries are stored in BGR format, with blue mapped to the
 *     most significant bits of a color type.
 *
 ***********************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 **********************************************************************/

#ifndef LPC_COLOR_TYPES_H
#define LPC_COLOR_TYPES_H

#include "lpc_types.h"

#if defined (__cplusplus)
extern "C"
{
#endif

/***********************************************************************
 * Default configuration values
 **********************************************************************/

/* Pick the appropriate define for 8- or 16-bit color modes. Only ONE
   of these lines should be uncommented */
#ifndef COLORS_DEF
//#define COLORS_DEF 24     /* 24-bit 888 color mode */
#define COLORS_DEF 16      /* 16-bit 565 color mode */
//#define COLORS_DEF 15      /* 15-bit 555 color mode */
//#define COLORS_DEF 12      /* 12-bit 444 color mode */
//*#define COLORS_DEF 8      /* 8-bit color mode */
#endif



/* Extended color scheme for 24-bit per pixel implementation */
#define COLORS_EXTENDED     (0)

/* 24-bit per pixel color scheme */
#if COLORS_DEF == 24

/*****************************************************************************
*	Red Colors 8-8-8 Mode
*****************************************************************************/
#define SALMON						(0x00FA8072)
#define RED							(0x00FF0000)
#define CRIMSON						(0x00DC143C)
#define DARKRED						(0x008B0000)

#if (COLORS_EXTENDED)
    #define INDIANRED					(0x00CD5C5C)
    #define LIGHTCORAL					(0x00F08080)
    #define DARKSALMON					(0x00E9967A)
    #define LIGHTSALMON					(0x00FFA07A)
    #define FIREBRICK					(0x00B22222)
#endif

/*****************************************************************************
*	Pink Colors 8-8-8 Mode
*****************************************************************************/
#define PINK						(0x00FFC0CB)
#define HOTPINK						(0x00FF69B4)
#define MEDIUMVIOLETRED				(0x00C71585)

#if (COLORS_EXTENDED)
    #define LIGHTPINK					(0x00FFB6C1)
    #define DEEPPINK					(0x00FF1493)
    #define PALEVIOLETRED				(0x00DB7093)
#endif

/*****************************************************************************
*	Orange Colors 8-8-8 Mode
*****************************************************************************/
#define TOMATO						(0x00FF6347)
#define ORANGERED					(0x00FF4500)
#define ORANGE						(0x00FFA500)

#if (COLORS_EXTENDED)
    #define LIGHTSALMON					(0x00FFA07A)
    #define CORAL						(0x00FF7F50)
    #define DARKORANGE					(0x00FF8C00)
#endif

/*****************************************************************************
*	Yellow Colors 8-8-8 Mode
*****************************************************************************/
#define GOLD						(0x00FFD700)
#define YELLOW						(0x00FFFF00)
#define KHAKI						(0x00F0E68C)
#define DARKKHAKI					(0x00BDB76B)

#if (COLORS_EXTENDED)
    #define LIGHTYELLOW					(0x00FFFFE0)
    #define LEMONCHIFFON				(0x00FFFACD)
    #define LIGHTGOLDENRODYELLOW		(0x00FAFAD2)
    #define PAPAYAWHIP					(0x00FFEFD5)
    #define MOCCASIN					(0x00FFE4B5)
    #define PEACHPUFF					(0x00FFDAB9)
    #define PALEGOLDENROD				(0x00EEE8AA)
#endif

/*****************************************************************************
*	Purple Colors 8-8-8 Mode
*****************************************************************************/
#define LAVENDER					(0x00E6E6FA)
#define VIOLET						(0x00EE82EE)
#define MAGENTA						(0x00FF00FF)
#define DARKVIOLET					(0x009400D3)
#define PURPLE						(0x00800080)
#define INDIGO						(0x004B0082)
#define SLATEBLUE					(0x006A5ACD)
#define MEDIUMSLATEBLUE				(0x007B68EE)

#if (COLORS_EXTENDED)
    #define THISTLE						(0x00D8BFD8)
    #define PLUM						(0x00DDA0DD)
    #define ORCHID						(0x00DA70D6)
    #define FUCHSIA						(0x00FF00FF)
    #define MEDIUMORCHID				(0x00BA55D3)
    #define MEDIUMPURPLE				(0x009370DB)
    #define BLUEVIOLET					(0x008A2BE2)
    #define DARKORCHID					(0x009932CC)
    #define DARKMAGENTA					(0x008B008B)
    #define DARKSLATEBLUE				(0x00483D8B)
    #define MEDIUMSLATEBLUE				(0x007B68EE)
#endif

/*****************************************************************************
*	Green Colors 8-8-8 Mode
*****************************************************************************/
#define GREENYELLOW					(0x00ADFF2F)
#define LIME						(0x0000FF00)
#define LIMEGREEN					(0x0032CD32)
#define SEAGREEN					(0x002E8B57)
#define FORESTGREEN					(0x00228B22)
#define GREEN						(0x00008000)
#define DARKGREEN					(0x00006400)
#define LIGHTSEAGREEN				(0x0020B2AA)
#define TEAL						(0x00008080)

#if (COLORS_EXTENDED)
    #define CHARTREUSE					(0x007FFF00)
    #define LAWNGREEN					(0x007CFC00)
    #define PALEGREEN					(0x0098FB98)
    #define LIGHTGREEN					(0x0090EE90)
    #define MEDIUMSPRINGGREEN			(0x0000FA9A)
    #define SPRINGGREEN					(0x0000FF7F)
    #define MEDIUMSEAGREEN				(0x003CB371)
    #define YELLOWGREEN					(0x009ACD32)
    #define OLIVEDRAB					(0x006B8E23)
    #define OLIVE						(0x00808000)
    #define DARKOLIVEGREEN				(0x00556B2F)
    #define MEDIUMAQUAMARINE			(0x0066CDAA)
    #define DARKSEAGREEN				(0x008FBC8F)
    #define DARKCYAN					(0x00008B8B)
#endif

/*****************************************************************************
*	Blue/Cyan Colors 8-8-8 Mode
*****************************************************************************/
#define AQUA						(0x0000FFFF)
#define AQUAMARINE					(0x007FFFD4)
#define TURQUOISE					(0x0040E0D0)
#define STEELBLUE					(0x004682B4)
#define SKYBLUE						(0x0087CEEB)
#define ROYALBLUE					(0x004169E1)
#define BLUE						(0x000000FF)
#define DARKBLUE					(0x0000008B)
#define NAVY						(0x00000080)

#if (COLORS_EXTENDED)
    #define CYAN						(0x0000FFFF)
    #define LIGHTCYAN					(0x00E0FFFF)
    #define PALETURQUOISE				(0x00AFEEEE)
    #define MEDIUMTURQUOISE				(0x0048D1CC)
    #define DARKTURQUOISE				(0x0000CED1)
    #define CADETBLUE					(0x005F9EA0)
    #define LIGHTSTEELBLUE				(0x00B0C4DE)
    #define POWDERBLUE					(0x00B0E0E6)
    #define LIGHTBLUE					(0x00ADD8E6)
    #define LIGHTSKYBLUE				(0x0087CEFA)
    #define DEEPSKYBLUE					(0x0000BFFF)
    #define DODGERBLUE					(0x001E90FF)
    #define CORNFLOWERBLUE				(0x006495ED)
    #define MEDIUMBLUE					(0x000000CD)
    #define MIDNIGHTBLUE				(0x00191970)
#endif

/*****************************************************************************
*	Brown Colors 8-8-8 Mode
*****************************************************************************/
#define BURLYWOOD					(0x00DEB887)
#define TAN							(0x00D2B48C)
#define SADDLEBROWN					(0x008B4513)
#define BROWN						(0x00A52A2A)
#define MAROON						(0x00800000)

#if (COLORS_EXTENDED)
    #define CORNSILK					(0x00FFF8DC)
    #define BLANCHEDALMOND				(0x00FFEBCD)
    #define BISQUE						(0x00FFE4C4)
    #define NAVAJOWHITE					(0x00FFDEAD)
    #define WHEAT						(0x00F5DEB3)
    #define ROSYBROWN					(0x00BC8F8F)
    #define SANDYBROWN					(0x00F4A460)
    #define GOLDENROD					(0x00DAA520)
    #define DARKGOLDENROD				(0x00B8860B)
    #define PERU						(0x00CD853F)
    #define CHOCOLATE					(0x00D2691E)
    #define SIENNA						(0x00A0522D)
#endif

/*****************************************************************************
*	White Colors 8-8-8 Mode
*****************************************************************************/
#define WHITE						(0x00FFFFFF)
#define LAVENDERBLUSH				(0x00FFF0F5)
#define MISTYROSE					(0x00FFE4E1)

#if (COLORS_EXTENDED)
    #define SNOW						(0x00FFFAFA)
    #define HONEYDEW					(0x00F0FFF0)
    #define MINTCREAM					(0x00F5FFFA)
    #define AZURE						(0x00F0FFFF)
    #define ALICEBLUE					(0x00F0F8FF)
    #define GHOSTWHITE					(0x00F8F8FF)
    #define WHITESMOKE					(0x00F5F5F5)
    #define SEASHELL					(0x00FFF5EE)
    #define BEIGE						(0x00F5F5DC)
    #define OLDLACE						(0x00FDF5E6)
    #define FLORALWHITE					(0x00FFFAF0)
    #define IVORY						(0x00FFFFF0)
    #define ANTIQUEWHITE				(0x00FAEBD7)
    #define LINEN						(0x00FAF0E6)
#endif

/*****************************************************************************
*	Gray Colors 8-8-8 Mode
*****************************************************************************/
#define LIGHTGREY					(0x00D3D3D3)
#define SILVER						(0x00C0C0C0)
#define DARKGRAY					(0x00A9A9A9)
#define GRAY						(0x00808080)
#define SLATEGRAY					(0x00708090)
#define BLACK						(0x00000000)

#if (COLORS_EXTENDED)
    #define GAINSBORO					(0x00DCDCDC)
    #define DIMGRAY						(0x00696969)
    #define LIGHTSLATEGRAY				(0x00778899)
    #define DARKSLATEGRAY				(0x002F4F4F)
#endif


#define REDMASK       (0x00FF0000)  /* Red color mask, 888 mode */
#define REDSHIFT      (16)          /* Red shift value, 888 mode */
#define GREENMASK     (0x0000FF00)  /* Green color mask, 888 mode */
#define GREENSHIFT    (8)           /* Green shift value, 888 mode */
#define BLUEMASK      (0x000000FF)  /* Blue color mask, 888 mode */
#define BLUESHIFT     (0)           /* Blue shift value, 888 mode */

#define NUM_COLORS    (16777216)    /* Number of colors in 888 mode */
#define RED_COLORS    (0x100)       /* Number of red colors in 888 mode */
#define GREEN_COLORS  (0x100)       /* Number of green colors in 888 mode */
#define BLUE_COLORS   (0x100)       /* Number of blue colors in 888 mode */

/* Color type is a 32-bit value */
typedef UNS_32 COLOR_T;

#endif

/* If COLORS_8 is used, then uncomment the following line to use 565
   output mode in the palette table, otherwise 555 mode will be used */
/*#define COLORS_8_565_MODE */

#if COLORS_DEF == 16
/* Black color, 565 mode */
#define BLACK         0x0000
/* Light gray color, 565 mode */
#define LIGHTGRAY     0X7BEF
/* Dark gray color, 565 mode */
#define DARKGRAY      0x39E7
/* White color, 565 mode */
#define WHITE         0x7fff
/* Red color, 565 mode */
#define RED           0xF800
/* Green color, 565 mode */
#define GREEN         0x07E0
/* Blue color, 565 mode */
#define BLUE          0x001F
/* Magenta color, 565 mode */
#define MAGENTA       (RED | BLUE)
/* Cyan color, 565 mode */
#define CYAN          (GREEN | BLUE)
/* Yellow color, 565 mode */
#define YELLOW        (RED | GREEN)
/* Light red color, 565 mode */
#define LIGHTRED      0x7800
/* Light green color, 565 mode */
#define LIGHTGREEN    0x03E0
/* Light blue color, 565 mode */
#define LIGHTBLUE     0x000F
/* Light magenta color, 565 mode */
#define LIGHTMAGENTA  (LIGHTRED | LIGHTBLUE)
/* Light cyan color, 565 mode */
#define LIGHTCYAN     (LIGHTGREEN | LIGHTBLUE)
/* Light yellow color, 565 mode */
#define LIGHTYELLOW   (LIGHTRED | LIGHTGREEN)

/* Red color mask, 565 mode */
#define REDMASK       0xF800
/* Red shift value, 565 mode */
#define REDSHIFT      11
/* Green color mask, 565 mode */
#define GREENMASK     0x07E0
/* Green shift value, 565 mode */
#define GREENSHIFT    5
/* Blue color mask, 565 mode */
#define BLUEMASK      0x001F
/* Blue shift value, 565 mode */
#define BLUESHIFT     0

/* Number of colors in 565 mode */
#define NUM_COLORS    65536
/* Number of red colors in 565 mode */
#define RED_COLORS    0x20
/* Number of green colors in 565 mode */
#define GREEN_COLORS  0x40
/* Number of blue colors in 565 mode */
#define BLUE_COLORS   0x20

/* Color type is a 16-bit value */
typedef UNS_16 COLOR_T;
#endif

#if COLORS_DEF == 15
/* Black color, 555 mode */
#define BLACK         0x0000
/* Llight gray color, 555 mode */
#define LIGHTGRAY     0x3DEF
/* Drak gray color, 555 mode */
#define DARKGRAY      0x1CE7
/* White color, 555 mode */
#define WHITE         0x7fff
/* Red color, 555 mode */
#define RED           0x7C00
/* Green color, 555 mode */
#define GREEN         0x03E0
/* Blue color, 555 mode */
#define BLUE          0x001F
/* Magenta color, 555 mode */
#define MAGENTA       (RED | BLUE)
/* Cyan color, 555 mode */
#define CYAN          (GREEN | BLUE)
/* Yellow color, 555 mode */
#define YELLOW        (RED | GREEN)
/* Light red color, 555 mode */
#define LIGHTRED      0x3C00
/* Light green color, 555 mode */
#define LIGHTGREEN    0x01E0
/* Light blue color, 555 mode */
#define LIGHTBLUE     0x000F
/* Light magenta color, 555 mode */
#define LIGHTMAGENTA  (LIGHTRED | LIGHTBLUE)
/* Light cyan color, 555 mode */
#define LIGHTCYAN     (LIGHTGREEN | LIGHTBLUE)
/* Light yellow color, 555 mode */
#define LIGHTYELLOW   (LIGHTRED | LIGHTGREEN)

/* Red color mask, 555 mode */
#define REDMASK       0x7C00
/* Red shift value, 555 mode */
#define REDSHIFT      10
/* Green color mask, 555 mode */
#define GREENMASK     0x03E0
/* Green shift value, 555 mode */
#define GREENSHIFT    5
/* Blue color mask, 555 mode */
#define BLUEMASK      0x001F
/* Blue shift value, 555 mode */
#define BLUESHIFT     0

/* Number of colors in 555 mode */
#define NUM_COLORS    32768
/* Number of red colors in 555 mode */
#define RED_COLORS    0x20
/* Number of green colors in 555 mode */
#define GREEN_COLORS  0x20
/* Number of blue colors in 555 mode */
#define BLUE_COLORS   0x20

/* Color type is a 16-bit value */
typedef UNS_16 COLOR_T;
#endif

#if COLORS_DEF == 12
/* Black color, 444 mode */
#define BLACK         0x0000
/* Llight gray color, 444 mode */
#define LIGHTGRAY     0x3DEF
/* Drak gray color, 444 mode */
#define DARKGRAY      0x1CE7
/* White color, 444 mode */
#define WHITE         0x7fff
/* Red color, 444 mode */
#define RED           0x3C00
/* Green color, 444 mode */
#define GREEN         0x01E0
/* Blue color, 444 mode */
#define BLUE          0x000F
/* Magenta color, 444 mode */
#define MAGENTA       (RED | BLUE)
/* Cyan color, 444 mode */
#define CYAN          (GREEN | BLUE)
/* Yellow color, 444 mode */
#define YELLOW        (RED | GREEN)
/* Light red color, 444 mode */
#define LIGHTRED      0x3C00
/* Light green color, 444 mode */
#define LIGHTGREEN    0x01E0
/* Light blue color, 444 mode */
#define LIGHTBLUE     0x000F
/* Light magenta color, 444 mode */
#define LIGHTMAGENTA  (LIGHTRED | LIGHTBLUE)
/* Light cyan color, 444 mode */
#define LIGHTCYAN     (LIGHTGREEN | LIGHTBLUE)
/* Light yellow color, 444 mode */
#define LIGHTYELLOW   (LIGHTRED | LIGHTGREEN)

/* Red color mask, 444 mode */
#define REDMASK       0x3C00
/* Red shift value, 444 mode */
#define REDSHIFT      10
/* Green color mask, 444 mode */
#define GREENMASK     0x01E0
/* Green shift value, 444 mode */
#define GREENSHIFT    5
/* Blue color mask, 444 mode */
#define BLUEMASK      0x000F
/* Blue shift value, 444 mode */
#define BLUESHIFT     0

/* Number of colors in 444 mode */
#define NUM_COLORS    4096
/* Number of red colors in 444 mode */
#define RED_COLORS    0x10
/* Number of green colors in 444 mode */
#define GREEN_COLORS  0x10
/* Number of blue colors in 444 mode */
#define BLUE_COLORS   0x10

/* Color type is a 16-bit value */
typedef UNS_16 COLOR_T;
#endif

#if COLORS_DEF == 8
/* Black color, 323 mode */
#define BLACK         0x00
/* Light gray color, 323 mode */
#define LIGHTGRAY     0x6E
/* Dark gray color, 323 mode */
#define DARKGRAY      0x25
/* White color, 323 mode */
#define WHITE         0xFF
/* Red color, 323 mode */
#define RED           0xE0
/* Green color, 323 mode */
#define GREEN         0x1C
/* Blue color, 323 mode */
#define BLUE          0x03
/* Magenta color, 323 mode */
#define MAGENTA       (RED | BLUE)
/* Cyan color, 323 mode */
#define CYAN          (GREEN | BLUE)
/* Yellow color, 323 mode */
#define YELLOW        (RED | GREEN)
/* Light red color, 323 mode */
#define LIGHTRED      0x60
/* Light green color, 323 mode */
#define LIGHTGREEN    0x0C
/* Light blue color, 323 mode */
#define LIGHTBLUE     0x01
/* Light magenta color, 323 mode */
#define LIGHTMAGENTA  (LIGHTRED | LIGHTBLUE)
/* Light cyan color, 323 mode */
#define LIGHTCYAN     (LIGHTGREEN | LIGHTBLUE)
/* Light yellow color, 323 mode */
#define LIGHTYELLOW   (LIGHTRED | LIGHTGREEN)

/* Red color mask, 323 mode */
#define REDMASK       0xE0
/* Red shift value, 323 mode */
#define REDSHIFT      5
/* Green color mask, 323 mode */
#define GREENMASK     0x1C
/* Green shift value, 323 mode */
#define GREENSHIFT    2
/* Blue color mask, 323 mode */
#define BLUEMASK      0x3
/* Blue shift value, 323 mode */
#define BLUESHIFT     0

/* Number of colors in 332 mode */
#define NUM_COLORS    256
/* Number of red colors in 332 mode */
#define RED_COLORS    0x08
/* Number of green colors in 332 mode */
#define GREEN_COLORS  0x08
/* Number of blue colors in 332 mode */
#define BLUE_COLORS   0x08

/* Color type is a 8-bit value */
typedef UNS_8 COLOR_T;
#endif

/***********************************************************************
 * Color configuration functions
 **********************************************************************/

/* Generate a palette table (only in 8-bit mode). If compiled in 16-bit
   color mode, this will be a NULL function. */
void lpc_colors_set_palette(UNS_16 *palette_table);

#if defined (__cplusplus)
}
#endif /*__cplusplus */

#endif /* LPC_COLOR_TYPES_H */
