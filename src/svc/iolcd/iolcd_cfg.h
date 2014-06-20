/*******************************************************************************************************************************
*	
*	Filename: iolcd_cfg.h
*	Rev Date: 2/14/2012
*
*	File Description:
*			Configuration file for IO LCD.
*
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc18xx_lcd.h"

/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOLCD_CFG_H_VERSION_MAJOR			(1)
#define IOLCD_CFG_H_VERSION_MINOR			(2)
#define IOLCD_CFG_H_VERSION_PATCH			(0)

#define LCD_PWM_PORT_NO						(0)
#define LCD_PWM_PORT_CHNL					(6)
#define LCD_PWM_MATCH_CHNL					(6)
#define LCD_PWM_BASE_MATCH_CHNL				(1)

#define LCD_BACKLIGHT_BASE_FREQ             (16)

/* Configuration macros for LCD_CFG_Type */
#define LCD_WIDTH			(480)
#define LCD_HEIGHT			(272)
#define LCD_H_PORCH			(2)
#define LCD_V_PORCH			(2)
#define LCD_HSYNC_PW		(41)
#define LCD_VSYNC_PW		(10)
#define LCD_AC_BIAS_FR		(0)
#define LCD_HSYNC_POLARITY	(LCD_SIGNAL_ACTIVE_LOW)
#define LCD_VSYNC_POLARITY	(LCD_SIGNAL_ACTIVE_LOW)
#define LCD_PANEL_CLK_EDGE	(LCD_CLK_FALLING)
#define LCD_OUTPUT_POLARITY	(LCD_SIGNAL_ACTIVE_HIGH)
#define LCD_LINEEND_DELAY	(0)
#define LCD_BPP_RES			(LCD_BPP16)
#define LCD_PANEL_TYPE		(LCD_TFT)
#define LCD_COLOR_FORMAT	(LCD_COLOR_FORMAT_BGR)
#define LCD_DUAL_PANEL		(FALSE)

/* Macro definitions for LCD Interface Pinout */
#define LCD_INTERFACE_NUMOF_PINS	(28)

/*******************************************************************************************************************************
*			Constant Definitions
*******************************************************************************************************************************/
const LCD_CFG_Type Sharp_LCD = 
{
	(U2)LCD_WIDTH,
	(U2)LCD_HEIGHT,
	{(U2)LCD_H_PORCH,(U2)LCD_H_PORCH},
	{(U2)LCD_V_PORCH,(U2)LCD_V_PORCH},
	(U2)LCD_HSYNC_PW,
	(U2)LCD_VSYNC_PW,
	(U1)LCD_AC_BIAS_FR,
	LCD_HSYNC_POLARITY,
	LCD_VSYNC_POLARITY,
	LCD_PANEL_CLK_EDGE,
	LCD_OUTPUT_POLARITY,
	(U4)LCD_LINEEND_DELAY,
	LCD_BPP_RES,
	LCD_PANEL_TYPE,
	LCD_COLOR_FORMAT,
	LCD_DUAL_PANEL
};


const LCD_INTERFACE_PINOUT st_tp_LCD_INTERFACE_PINOUT[LCD_INTERFACE_NUMOF_PINS] = 
{
								/* 0. Data Pin R0 */
	(U1)LCD_DATA_R0_PORT,		/* Port Number */
	(U1)LCD_DATA_R0_PIN,		/* Pin Number */
	(U1)LCD_DATA_R0_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 1. Data Pin R1 */
	(U1)LCD_DATA_R1_PORT,		/* Port Number */
	(U1)LCD_DATA_R1_PIN,		/* Pin Number */
	(U1)LCD_DATA_R1_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 2. Data Pin R2 */
	(U1)LCD_DATA_R2_PORT,		/* Port Number */
	(U1)LCD_DATA_R2_PIN,		/* Pin Number */
	(U1)LCD_DATA_R2_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */

								/* 3. Data Pin R3 */
	(U1)LCD_DATA_R3_PORT,		/* Port Number */
	(U1)LCD_DATA_R3_PIN,		/* Pin Number */
	(U1)LCD_DATA_R3_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 4. Data Pin R4 */
	(U1)LCD_DATA_R4_PORT,		/* Port Number */
	(U1)LCD_DATA_R4_PIN,		/* Pin Number */
	(U1)LCD_DATA_R4_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 5. Data Pin R5 */
	(U1)LCD_DATA_R5_PORT,		/* Port Number */
	(U1)LCD_DATA_R5_PIN,		/* Pin Number */
	(U1)LCD_DATA_R5_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 6. Data Pin R6 */
	(U1)LCD_DATA_R6_PORT,		/* Port Number */
	(U1)LCD_DATA_R6_PIN,		/* Pin Number */
	(U1)LCD_DATA_R6_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 7. Data Pin R7 */
	(U1)LCD_DATA_R7_PORT,		/* Port Number */
	(U1)LCD_DATA_R7_PIN,		/* Pin Number */
	(U1)LCD_DATA_R7_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 8. Data Pin G0 */
	(U1)LCD_DATA_G0_PORT,		/* Port Number */
	(U1)LCD_DATA_G0_PIN,		/* Pin Number */
	(U1)LCD_DATA_G0_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 9. Data Pin G1 */
	(U1)LCD_DATA_G1_PORT,		/* Port Number */
	(U1)LCD_DATA_G1_PIN,		/* Pin Number */
	(U1)LCD_DATA_G1_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 10. Data Pin G2 */
	(U1)LCD_DATA_G2_PORT,		/* Port Number */
	(U1)LCD_DATA_G2_PIN,		/* Pin Number */
	(U1)LCD_DATA_G2_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 11. Data Pin G3 */
	(U1)LCD_DATA_G3_PORT,		/* Port Number */
	(U1)LCD_DATA_G3_PIN,		/* Pin Number */
	(U1)LCD_DATA_G3_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 12. Data Pin G4 */
	(U1)LCD_DATA_G4_PORT,		/* Port Number */
	(U1)LCD_DATA_G4_PIN,		/* Pin Number */
	(U1)LCD_DATA_G4_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 13. Data Pin G5 */
	(U1)LCD_DATA_G5_PORT,		/* Port Number */
	(U1)LCD_DATA_G5_PIN,		/* Pin Number */
	(U1)LCD_DATA_G5_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 14. Data Pin G6 */
	(U1)LCD_DATA_G6_PORT,		/* Port Number */
	(U1)LCD_DATA_G6_PIN,		/* Pin Number */
	(U1)LCD_DATA_G6_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 15. Data Pin G7 */
	(U1)LCD_DATA_G7_PORT,		/* Port Number */
	(U1)LCD_DATA_G7_PIN,		/* Pin Number */
	(U1)LCD_DATA_G7_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 16. Data Pin B0 */
	(U1)LCD_DATA_B0_PORT,		/* Port Number */
	(U1)LCD_DATA_B0_PIN,		/* Pin Number */
	(U1)LCD_DATA_B0_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 17. Data Pin B1 */
	(U1)LCD_DATA_B1_PORT,		/* Port Number */
	(U1)LCD_DATA_B1_PIN,		/* Pin Number */
	(U1)LCD_DATA_B1_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 18. Data Pin B2 */
	(U1)LCD_DATA_B2_PORT,		/* Port Number */
	(U1)LCD_DATA_B2_PIN,		/* Pin Number */
	(U1)LCD_DATA_B2_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 19. Data Pin B3 */
	(U1)LCD_DATA_B3_PORT,		/* Port Number */
	(U1)LCD_DATA_B3_PIN,		/* Pin Number */
	(U1)LCD_DATA_B3_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 20. Data Pin B4 */
	(U1)LCD_DATA_B4_PORT,		/* Port Number */
	(U1)LCD_DATA_B4_PIN,		/* Pin Number */
	(U1)LCD_DATA_B4_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 21. Data Pin B5 */
	(U1)LCD_DATA_B5_PORT,		/* Port Number */
	(U1)LCD_DATA_B5_PIN,		/* Pin Number */
	(U1)LCD_DATA_B5_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 22. Data Pin B6 */
	(U1)LCD_DATA_B6_PORT,		/* Port Number */
	(U1)LCD_DATA_B6_PIN,		/* Pin Number */
	(U1)LCD_DATA_B6_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 23. Data Pin B7 */
	(U1)LCD_DATA_B7_PORT,		/* Port Number */
	(U1)LCD_DATA_B7_PIN,		/* Pin Number */
	(U1)LCD_DATA_B7_FUNCTION,	/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 24. LCD Vsync Pin */
	(U1)LCD_VSYNC_PORT,			/* Port Number */
	(U1)LCD_VSYNC_PIN,			/* Pin Number */
	(U1)LCD_VSYNC_FUNCTION,		/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 25. LCD Hsync Pin */
	(U1)LCD_HSYNC_PORT,			/* Port Number */
	(U1)LCD_HSYNC_PIN,			/* Pin Number */
	(U1)LCD_HSYNC_FUNCTION,		/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
								/* 26. LCD DClock Pin */
	(U1)LCD_DCLK_PORT,			/* Port Number */
	(U1)LCD_DCLK_PIN,			/* Pin Number */
	(U1)LCD_DCLK_FUNCTION,		/* Pin Function Number */
	(U1)IOCON_MODE_PLAIN,		/* Pull Up, Pull Down Status */
	
};


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/14/2012		J. Nabozny			Created
*	1.0.0		3/16/2012		J. Nabozny			Add in version control
*   1.0.1		3/19/2012		J. Nabozny			Remove power pin from lookup table. Add code to power LCD screen properly.
*   1.1.0       4/11/2012       J. Nabozny          Add in framebuffer function
*   1.2.0       5/1/2012        J. Nabozny          Functionality for screen finalized
*
*******************************************************************************************************************************/
