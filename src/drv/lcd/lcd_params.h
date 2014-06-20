/***********************************************************************
 * File:   lcd_params.h
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

#ifndef LCD_PARAM_H
#define LCD_PARAM_H

#include "data_types.h"

/* LCD display types */
typedef enum {
    TFT = 0,      /* standard TFT */
    ADTFT,        /* advanced TFT */
    HRTFT,        /* highly reflective TFT */
    MONO_4BIT,    /* 4-bit mono */
    MONO_8BIT,    /* 8-bit mono */
    CSTN          /* color STN */
} LCD_PANEL_T;

/* Structure containing the parameters for the LCD panel */
typedef struct {
    INT8U           h_back_porch;         /* Horizontal back porch in clocks */
    INT8U           h_front_porch;        /* Horizontal front porch in clocks */
    INT8U           h_sync_pulse_width;   /* HSYNC pulse width in clocks */
    INT16U          pixels_per_line;      /* Pixels per line (horizontal resolution) */
    INT8U           v_back_porch;         /* Vertical back porch in clocks */
    INT8U           v_front_porch;        /* Vertical front porch in clocks */
    INT8U           v_sync_pulse_width;   /* VSYNC pulse width in clocks */
    INT16U          lines_per_panel;      /* Lines per panel (vertical resolution) */
    INT8U           invert_output_enable; /* Invert output enable, 1 = invert*/
    INT8U           invert_panel_clock;   /* Invert panel clock, 1 = invert*/
    INT8U           invert_hsync;         /* Invert HSYNC, 1 = invert */
    INT8U           invert_vsync;         /* Invert VSYNC, 1 = invert */
    INT8U           ac_bias_frequency;    /* AC bias frequency in clocks */
    INT8U           bits_per_pixel;       /* Maximum bits per pixel the display supports */
    INT32U          optimal_clock;        /* Optimal clock rate (Hz) */
    LCD_PANEL_T     lcd_panel_type;       /* LCD panel type */
    INT8U           dual_panel;           /* Dual panel, 1 = dual panel display */
} LCD_PARAM_T;

/* Sharp LQ035 portrait mode ADTFT display */
extern const LCD_PARAM_T sharp_lq035_portrait;

/* Sharp LQ035 landscape mode ADTFT display */
extern const LCD_PARAM_T sharp_lq035_landscape;

#endif /* LCD_PARAM_H */
