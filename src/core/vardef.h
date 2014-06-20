/*******************************************************************************************************************************
*	
*	Filename: vardef.h
*	Rev Date: 2/9/2012
*
*	File Description:
*			Header file for global macro definitions
*
*******************************************************************************************************************************/

#include <stdint.h>

/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/

/* 	Clock configurations
*	__MAIN_OSC_CLK_CFG
*	0: Use PLL Clock cfg
*	1: Use OSC Clock cfg
*/
#define	__MAIN_OSC_CLK_CFG		(0)

/* 0 or 1 macros */
#define OFF						(0)
#define ON						(1)

#define LCD_AVDD_ON				(0)
#define LCD_AVDD_OFF			(1)

#define IO_BUTTON_PRESSED		(0)
#define IO_BUTTON_NOT_PRESSED	(1)	

/* Counter Value Macros */
#define COUNTER_100MS			(10)
#define COUNTER_1000MS			(100)

/* Task Delay Timing Macros */
#define TASK_DELAY_10MS			(10 / portTICK_RATE_MS)
#define TASK_DELAY_100MS		(100 / portTICK_RATE_MS)
#define TASK_DELAY_1000MS		(1000 / portTICK_RATE_MS)

/* Task Priority Macros */
#define TASK_PRIORITY_LOW 		(1)
#define TASK_PRIORITY_MED		(2)
#define TASK_PRIORITY_HIGH		(3)

/* Joystick States */
#define FULLLEFT                (0)
#define HALFLEFT                (1)
#define X_CENTER                (2)
#define HALFRIGHT               (3)
#define FULLRIGHT               (4)

#define FULLDOWN                (0)
#define HALFDOWN                (1)
#define Y_CENTER                (2)
#define HALFUP                  (3)
#define FULLUP                  (4)

#define CENTER                  (2)

#define JS_LEFTX                (0)
#define JS_LEFTY                (1)
#define JS_RIGHTX               (2)
#define JS_RIGHTY               (3)

/* Note Configurations */
#define SPKR_NOTE_B0			(258065)
#define SPKR_NOTE_C1			(242425)
#define SPKR_NOTE_CS1			(228572)
#define SPKR_NOTE_D1			(216217)
#define SPKR_NOTE_DS1			(205129)
#define SPKR_NOTE_E1			(195122)
#define SPKR_NOTE_F1			(181819)
#define SPKR_NOTE_FS1			(173914)
#define SPKR_NOTE_G1			(163266)
#define SPKR_NOTE_GS1			(153847)
#define SPKR_NOTE_A1			(145455)
#define SPKR_NOTE_AS1			(137932)
#define SPKR_NOTE_B1			(129033)
#define SPKR_NOTE_C2			(123077)
#define SPKR_NOTE_CS2			(115943)
#define SPKR_NOTE_D2			(109590)
#define SPKR_NOTE_DS2			(102565)
#define SPKR_NOTE_E2			(97561)
#define SPKR_NOTE_F2			(91955)
#define SPKR_NOTE_FS2			(86022)
#define SPKR_NOTE_G2			(81633)
#define SPKR_NOTE_GS2			(76924)
#define SPKR_NOTE_A2			(72728)
#define SPKR_NOTE_AS2			(68377)
#define SPKR_NOTE_B2			(65041)
#define SPKR_NOTE_C3			(61069)
#define SPKR_NOTE_CS3			(57554)
#define SPKR_NOTE_D3			(54422)
#define SPKR_NOTE_DS3			(51283)
#define SPKR_NOTE_E3			(48485)
#define SPKR_NOTE_F3			(45715)
#define SPKR_NOTE_FS3			(43244)
#define SPKR_NOTE_G3			(40817)
#define SPKR_NOTE_GS3			(38462)
#define SPKR_NOTE_A3			(36364)
#define SPKR_NOTE_AS3			(34335)
#define SPKR_NOTE_B3			(32389)
#define SPKR_NOTE_C4			(30535)
#define SPKR_NOTE_CS4			(28881)
#define SPKR_NOTE_D4			(27211)
#define SPKR_NOTE_DS4			(25724)
#define SPKR_NOTE_E4			(24243)
#define SPKR_NOTE_F4			(22923)
#define SPKR_NOTE_FS4			(21622)
#define SPKR_NOTE_G4			(20409)
#define SPKR_NOTE_GS4			(19278)
#define SPKR_NOTE_A4			(18182)
#define SPKR_NOTE_AS4			(17168)
#define SPKR_NOTE_B4			(16195)
#define SPKR_NOTE_C5			(15297)
#define SPKR_NOTE_CS5			(14441)
#define SPKR_NOTE_D5			(13629)
#define SPKR_NOTE_DS5			(12862)
#define SPKR_NOTE_E5			(12140)
#define SPKR_NOTE_F5			(11462)
#define SPKR_NOTE_FS5			(10811)
#define SPKR_NOTE_G5			(10205)
#define SPKR_NOTE_GS5			(9627)
#define SPKR_NOTE_A5			(9091)
#define SPKR_NOTE_AS5			(8584)
#define SPKR_NOTE_B5			(8098)
#define SPKR_NOTE_C6			(7641)
#define SPKR_NOTE_CS6			(7214)
#define SPKR_NOTE_D6			(6809)
#define SPKR_NOTE_DS6			(6426)
#define SPKR_NOTE_E6			(6066)
#define SPKR_NOTE_F6			(5727)
#define SPKR_NOTE_FS6			(5406)
#define SPKR_NOTE_G6			(5103)
#define SPKR_NOTE_GS6			(4817)
#define SPKR_NOTE_A6			(4546)
#define SPKR_NOTE_AS6			(4290)
#define SPKR_NOTE_B6			(4049)
#define SPKR_NOTE_C7			(3823)
#define SPKR_NOTE_CS7			(3609)
#define SPKR_NOTE_D7			(3406)
#define SPKR_NOTE_DS7			(3215)
#define SPKR_NOTE_E7			(3034)
#define SPKR_NOTE_F7			(2864)
#define SPKR_NOTE_FS7			(2703)
#define SPKR_NOTE_G7			(2552)
#define SPKR_NOTE_GS7			(2409)
#define SPKR_NOTE_A7			(2273)
#define SPKR_NOTE_AS7			(2146)
#define SPKR_NOTE_B7			(2025)
#define SPKR_NOTE_C8			(1912)
#define SPKR_NOTE_CS8			(1804)
#define SPKR_NOTE_D8			(1703)
#define SPKR_NOTE_DS8			(1608)

/* Total number of notes */
#define SPKR_NUMOF_NOTES		(89)


/* LCD Values */
#define LCD_BACKLIGHT_100       (2)
#define LCD_BACKLIGHT_50        (4) 


/* SDRAM Characteristics */
#define SDRAM_BASE_ADDR			(0xA0000000)
#define SDRAM_SIZE_U1			(2097152)
#define SDRAM_SIZE_U2           (SDRAM_SIZE_U1 / 2)
#define SDRAM_SIZE_U4           (SDRAM_SIZE_U1 / 4)
#define SDRAM_SIZE              (0x10000000)

#define FRAMEBUFFER_PRIMARY     (SDRAM_BASE_ADDR)
#define FRAMEBUFFER_SECONDARY   (0xA003FD00)

#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE

/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/9/2012		J. Nabozny			Created
*	1.0			2/21/2012		J. Nabozny			Add in LCD_AVDD_ON/OFF
*	1.1			3/13/2012		J. Nabozny			Add Joystick LED states
*	1.1.1		3/16/2012		J. Nabozny			Add in speaker note configuration
*	1.1.2		3/19/2012		J. Nabozny			Update Note Frequencies for faster clock
*   1.1.3		3/23/2012		J. Nabozny			Add in values for Button pressed/not pressed
*   1.1.4       4/9/2012        J. Nabozny          Add in Steve's code for joystick updating
*
*******************************************************************************************************************************/
