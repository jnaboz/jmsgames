/***********************************************************************
 * File:   lcd_params.c
 * Rev:    1.0
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains parameters for LCD panel used on FCC1 board.
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#include "lcd_params.h"

/* Sharp LQ035 portrait mode ADTFT display parameters */
const LCD_PARAM_T sharp_lq035_portrait =
{
    1,        /* Horizontal back porch */
    15,       /* Horizontal front porch */
    14,       /* HSYNC pulse width */
    240,      /* Pixels per line */
    6,        /* Vertical back porch */
    10,       /* Vertical front porch */
    3,        /* VSYNC pulse width */
    320,      /* Lines per panel */
    0,        /* Do not invert output enable */
    1,        /* Invert panel clock */
    0,        /* Do not Invert HSYNC */
    0,        /* Do not invert VSYNC */
    1,        /* AC bias frequency (not used) */
    18,       /* Bits per pixel */
    6300000,  /* Optimal clock rate (Hz) */
    ADTFT,    /* LCD panel type */
    0,        /* Single panel display */
};

/* Sharp LQ035 landscape mode ADTFT display parameters */
const LCD_PARAM_T sharp_lq035_landscape =
{
    21,       /* Horizontal back porch */
    11,       /* Horizontal front porch */
    14,       /* HSYNC pulse width */
    320,      /* Pixels per line */
    3,        /* Vertical back porch */
    4,        /* Vertical front porch */
    3,        /* VSYNC pulse width */
    240,      /* Lines per panel */
    0,        /* Do not invert output enable */
    1,        /* Invert panel clock */
    0,        /* Do not Invert HSYNC */
    0,        /* Do not invert VSYNC */
    1,        /* AC bias frequency (not used) */
    18,       /* Bits per pixel */
    6300000,  /* Optimal clock rate (Hz) */
    ADTFT,    /* LCD panel type */
    0,        /* Single panel display */
};
