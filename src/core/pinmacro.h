/*******************************************************************************************************************************
*
*	Filename: pinmacro.h
*	Rev Date: 2/7/2012
*
*	File Description:
*			Define all pins as port/pin/mask in order to access pins correctly
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc177x_8x_adc.h"

/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/


/* Button Pin Macro Definition */
#define GPIO_BUTTON_A_PORT			(1)
#define GPIO_BUTTON_A_PIN			(1)
#define GPIO_BUTTON_A_MASK			(1 << GPIO_BUTTON_A_PIN)
#define GPIO_BUTTON_A_FUNCTION		(0)

#define GPIO_BUTTON_B_PORT			(1)
#define GPIO_BUTTON_B_PIN			(2)
#define GPIO_BUTTON_B_MASK			(1 << GPIO_BUTTON_B_PIN)
#define GPIO_BUTTON_B_FUNCTION		(0)

#define GPIO_BUTTON_C_PORT			(1)
#define GPIO_BUTTON_C_PIN			(3)
#define GPIO_BUTTON_C_MASK			(1 << GPIO_BUTTON_C_PIN)
#define GPIO_BUTTON_C_FUNCTION		(0)

#define GPIO_BUTTON_D_PORT			(1)
#define GPIO_BUTTON_D_PIN			(4)
#define GPIO_BUTTON_D_MASK			(1 << GPIO_BUTTON_D_PIN)
#define GPIO_BUTTON_D_FUNCTION		(0)

#define GPIO_BUTTON_R_PORT			(1)
#define GPIO_BUTTON_R_PIN			(5)
#define GPIO_BUTTON_R_MASK			(1 << GPIO_BUTTON_R_PIN)
#define GPIO_BUTTON_R_FUNCTION		(0)

#define GPIO_BUTTON_L_PORT			(1)
#define GPIO_BUTTON_L_PIN			(6)
#define GPIO_BUTTON_L_MASK			(1 << GPIO_BUTTON_L_PIN)
#define GPIO_BUTTON_L_FUNCTION		(0)

#define GPIO_BUTTON_START_PORT		(1)
#define GPIO_BUTTON_START_PIN		(7)
#define GPIO_BUTTON_START_MASK		(1 << GPIO_BUTTON_START_PIN)
#define GPIO_BUTTON_START_FUNCTION	(0)


/* Joystick Pin Macro Definitions */
#define ADC_JOYSTICK_LX_PORT		(0)
#define ADC_JOYSTICK_LX_PIN			(12)
#define ADC_JOYSTICK_LX_MASK		(1 << ADC_JOYSTICK_LX_PIN)
#define ADC_JOYSTICK_LX_FUNCTION	(3)
#define ADC_JOYSTICK_LX_CHANNEL		(ADC_CHANNEL_6)
#define ADC_JOYSTICK_LX_INTERRUPT	(ADC_ADINTEN6)

#define ADC_JOYSTICK_LY_PORT		(0)
#define ADC_JOYSTICK_LY_PIN			(13)
#define ADC_JOYSTICK_LY_MASK		(1 << ADC_JOYSTICK_LY_PIN)
#define ADC_JOYSTICK_LY_FUNCTION	(3)
#define ADC_JOYSTICK_LY_CHANNEL		(ADC_CHANNEL_7)
#define ADC_JOYSTICK_LY_INTERRUPT	(ADC_ADINTEN7)

#define ADC_JOYSTICK_RX_PORT		(1)
#define ADC_JOYSTICK_RX_PIN			(30)
#define ADC_JOYSTICK_RX_MASK		(1 << ADC_JOYSTICK_RX_PIN)
#define ADC_JOYSTICK_RX_FUNCTION	(3)
#define ADC_JOYSTICK_RX_CHANNEL		(ADC_CHANNEL_4)
#define ADC_JOYSTICK_RX_INTERRUPT	(ADC_ADINTEN4)

#define ADC_JOYSTICK_RY_PORT		(1)
#define ADC_JOYSTICK_RY_PIN			(31)
#define ADC_JOYSTICK_RY_MASK		(1 << ADC_JOYSTICK_RY_PIN)
#define ADC_JOYSTICK_RY_FUNCTION	(3)
#define ADC_JOYSTICK_RY_CHANNEL		(ADC_CHANNEL_5)
#define ADC_JOYSTICK_RY_INTERRUPT	(ADC_ADINTEN5)


/* Audio Pin Macro Definitions */
#define PWM_SPEAKER_PORT		(3)							/* PWM1[5] */
#define PWM_SPEAKER_PIN			(28)
#define PWM_SPEAKER_MASK		(1 << PWM_SPEAKER_PIN)
#define PWM_SPEAKER_FUNCTION	(2)


/* LCD Pin Macro Definitions */
#define LCD_DATA_R0_PORT		(0)	
#define LCD_DATA_R0_PIN			(4)	
#define LCD_DATA_R0_MASK		(1 << LCD_DATA_R0_PIN)
#define LCD_DATA_R0_FUNCTION	(7)

#define LCD_DATA_R1_PORT		(0)	
#define LCD_DATA_R1_PIN			(5)	
#define LCD_DATA_R1_MASK		(1 << LCD_DATA_R1_PIN)
#define LCD_DATA_R1_FUNCTION	(7)

#define LCD_DATA_R2_PORT		(2)	
#define LCD_DATA_R2_PIN			(8)	
#define LCD_DATA_R2_MASK		(1 << LCD_DATA_R2_PIN)
#define LCD_DATA_R2_FUNCTION	(6)

#define LCD_DATA_R3_PORT		(2)	
#define LCD_DATA_R3_PIN			(9)	
#define LCD_DATA_R3_MASK		(1 << LCD_DATA_R3_PIN)
#define LCD_DATA_R3_FUNCTION	(6)

#define LCD_DATA_R4_PORT		(2)	
#define LCD_DATA_R4_PIN			(6)	
#define LCD_DATA_R4_MASK		(1 << LCD_DATA_R4_PIN)
#define LCD_DATA_R4_FUNCTION	(7)

#define LCD_DATA_R5_PORT		(0)	
#define LCD_DATA_R5_PIN			(10)	
#define LCD_DATA_R5_MASK		(1 << LCD_DATA_R5_PIN)
#define LCD_DATA_R5_FUNCTION	(7)

#define LCD_DATA_R6_PORT		(1)	
#define LCD_DATA_R6_PIN			(20)	
#define LCD_DATA_R6_MASK		(1 << LCD_DATA_R6_PIN)
#define LCD_DATA_R6_FUNCTION	(6)

#define LCD_DATA_R7_PORT		(1)	
#define LCD_DATA_R7_PIN			(21)	
#define LCD_DATA_R7_MASK		(1 << LCD_DATA_R7_PIN)
#define LCD_DATA_R7_FUNCTION	(6)

#define LCD_DATA_G0_PORT		(0)	
#define LCD_DATA_G0_PIN			(6)	
#define LCD_DATA_G0_MASK		(1 << LCD_DATA_G0_PIN)
#define LCD_DATA_G0_FUNCTION	(7)

#define LCD_DATA_G1_PORT		(1)	
#define LCD_DATA_G1_PIN			(23)	
#define LCD_DATA_G1_MASK		(1 << LCD_DATA_G1_PIN)
#define LCD_DATA_G1_FUNCTION	(6)

#define LCD_DATA_G2_PORT		(1)	
#define LCD_DATA_G2_PIN			(24)	
#define LCD_DATA_G2_MASK		(1 << LCD_DATA_G2_PIN)
#define LCD_DATA_G2_FUNCTION	(6)

#define LCD_DATA_G3_PORT		(4)	
#define LCD_DATA_G3_PIN			(29)	
#define LCD_DATA_G3_MASK		(1 << LCD_DATA_G3_PIN)
#define LCD_DATA_G3_FUNCTION	(6)

#define LCD_DATA_G4_PORT		(1)	
#define LCD_DATA_G4_PIN			(22)	
#define LCD_DATA_G4_MASK		(1 << LCD_DATA_G4_PIN)
#define LCD_DATA_G4_FUNCTION	(7)

#define LCD_DATA_G5_PORT		(0)	
#define LCD_DATA_G5_PIN			(19)	
#define LCD_DATA_G5_MASK		(1 << LCD_DATA_G5_PIN)
#define LCD_DATA_G5_FUNCTION	(7)

#define LCD_DATA_G6_PORT		(0)	
#define LCD_DATA_G6_PIN			(20)	
#define LCD_DATA_G6_MASK		(1 << LCD_DATA_G6_PIN)
#define LCD_DATA_G6_FUNCTION	(7)

#define LCD_DATA_G7_PORT		(1)	
#define LCD_DATA_G7_PIN			(25)	
#define LCD_DATA_G7_MASK		(1 << LCD_DATA_G7_PIN)
#define LCD_DATA_G7_FUNCTION	(7)

#define LCD_DATA_B0_PORT		(0)	
#define LCD_DATA_B0_PIN			(8)	
#define LCD_DATA_B0_MASK		(1 << LCD_DATA_B0_PIN)
#define LCD_DATA_B0_FUNCTION	(7)

#define LCD_DATA_B1_PORT		(0)	
#define LCD_DATA_B1_PIN			(9)	
#define LCD_DATA_B1_MASK		(1 << LCD_DATA_B1_PIN)
#define LCD_DATA_B1_FUNCTION	(7)

#define LCD_DATA_B2_PORT		(2)	
#define LCD_DATA_B2_PIN			(12)	
#define LCD_DATA_B2_MASK		(1 << LCD_DATA_B2_PIN)
#define LCD_DATA_B2_FUNCTION	(7)

#define LCD_DATA_B3_PORT		(2)	
#define LCD_DATA_B3_PIN			(13)	
#define LCD_DATA_B3_MASK		(1 << LCD_DATA_B3_PIN)
#define LCD_DATA_B3_FUNCTION	(7)

#define LCD_DATA_B4_PORT		(1)	
#define LCD_DATA_B4_PIN			(26)	
#define LCD_DATA_B4_MASK		(1 << LCD_DATA_B4_PIN)
#define LCD_DATA_B4_FUNCTION	(7)

#define LCD_DATA_B5_PORT		(1)	
#define LCD_DATA_B5_PIN			(27)	
#define LCD_DATA_B5_MASK		(1 << LCD_DATA_B5_PIN)
#define LCD_DATA_B5_FUNCTION	(7)

#define LCD_DATA_B6_PORT		(1)	
#define LCD_DATA_B6_PIN			(28)	
#define LCD_DATA_B6_MASK		(1 << LCD_DATA_B6_PIN)
#define LCD_DATA_B6_FUNCTION	(7)

#define LCD_DATA_B7_PORT		(1)	
#define LCD_DATA_B7_PIN			(29)	
#define LCD_DATA_B7_MASK		(1 << LCD_DATA_B7_PIN)
#define LCD_DATA_B7_FUNCTION	(7)

#define LCD_POWER_PORT			(2)	
#define LCD_POWER_PIN			(0)	
#define LCD_POWER_MASK			(1 << LCD_POWER_PIN)
#define LCD_POWER_FUNCTION		(7)

#define LCD_VSYNC_PORT			(2)	
#define LCD_VSYNC_PIN			(3)	
#define LCD_VSYNC_MASK			(1 << LCD_VSYNC_PIN)
#define LCD_VSYNC_FUNCTION		(7)

#define LCD_HSYNC_PORT			(2)	
#define LCD_HSYNC_PIN			(5)	
#define LCD_HSYNC_MASK			(1 << LCD_HSYNC_PIN)
#define LCD_HSYNC_FUNCTION		(7)

#define LCD_DCLK_PORT			(2)	
#define LCD_DCLK_PIN			(2)	
#define LCD_DCLK_MASK			(1 << LCD_DCLK_PIN)
#define LCD_DCLK_FUNCTION		(7)

#define LCD_LE_PORT				(2)	
#define LCD_LE_PIN				(1)	
#define LCD_LE_MASK				(1 << LCD_LE_PIN)
#define LCD_LE_FUNCTION			(7)

#define LCD_ENABLE_PORT			(2)	
#define LCD_ENABLE_PIN			(4)	
#define LCD_ENABLE_MASK			(1 << LCD_ENABLE_PIN)
#define LCD_ENABLE_FUNCTION		(7)

#define LCD_BACKLIGHT_PORT		(3)	                    /* PWM1[6] */
#define LCD_BACKLIGHT_PIN		(29)	
#define LCD_BACKLIGHT_MASK		(1 << LCD_BACKLIGHT_PIN)
#define LCD_BACKLIGHT_FUNCTION	(2)


/*******************************************************************************************************************************
*			Extern Functions
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/7/2012		J. Nabozny			Created
*	1.0			2/17/2012		J. Nabozny			Added in ADC Pin Configuration
* 	1.1	 		2/21/2012		J. Nabozny			Add in LCD_GPIO_AVDD information
*   1.2			3/12/2012		J. Nabozny			Add macros for Joystick LED outputs and extra Button LED outputs
*   1.3         5/3/2012        J. Nabozny          Remove unused pins
*
*******************************************************************************************************************************/



















