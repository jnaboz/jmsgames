/*******************************************************************************************************************************
*	
*	Filename: iolcd.c
*	Rev Date: 2/14/2012
*
*	File Description:
*			IO manager for LCD
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "pinmacro.h"
#include "FreeRTOS.h"
#include "task.h"
#include "systasks.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_gpio.h"
#include "iolcd.h"
#include "iolcd_cfg.h"
#include "LPC177x_8x.h"
#include "lpc177x_8x_pwm.h"

/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOLCD_C_VERSION_MAJOR			(1)
#define IOLCD_C_VERSION_MINOR			(2)
#define IOLCD_C_VERSION_PATCH			(0)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static U2 u2_s_bklt_tmr;        /* Backlight Enable timer:   bit 15: Backlight ON flag,   bit 14..0: Backlight Timer*/


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_LcdPinInit(void);
static void vd_s_IoLcdBacklightInit(void);
static void vd_s_IoLcdInitSplashScreen(void);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((IOLCD_C_VERSION_MAJOR == IOLCD_H_VERSION_MAJOR) && (IOLCD_C_VERSION_MAJOR == IOLCD_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOLCD_C_VERSION_MINOR == IOLCD_H_VERSION_MINOR) && (IOLCD_C_VERSION_MINOR == IOLCD_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOLCD_C_VERSION_PATCH == IOLCD_H_VERSION_PATCH) && (IOLCD_C_VERSION_PATCH == IOLCD_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoLcdInitTask
*	Called By:			vd_g_IoMgrInitTask
*	Timing:				Initialization
*	Description:		Task to initialize LCD Screen
*
*******************************************************************************************************************************/
void vd_g_IoLcdInitTask(void) 
{
	U4 u4_t_px;
    U4 u4_t_idx;

    u2_s_bklt_tmr = (U1)0;

    GPIO_SetDir(LCD_POWER_PORT, LCD_POWER_MASK, GPIO_DIRECTION_OUTPUT);		/* Set pin to OUTPUT */
	GPIO_OutputValue(LCD_POWER_PORT, LCD_POWER_MASK, (U1)OFF);			    /* Initialize to OFF */

    for(u4_t_idx = (U4)0; u4_t_idx < 0x500; u4_t_idx++)
    {
    }

    GPIO_SetDir(LCD_ENABLE_PORT, LCD_ENABLE_MASK, GPIO_DIRECTION_OUTPUT);		/* Set pin to OUTPUT */
	GPIO_OutputValue(LCD_ENABLE_PORT, LCD_ENABLE_MASK, (U1)ON);			        /* Initialize to ON */

	vd_s_LcdPinInit();
    vd_s_IoLcdBacklightInit();
	
    LPC_SC->PCONP   	|= 0x00000001;

#if(__MAIN_OSC_CLK_CFG)
	LPC_SC->LCD_CFG = (uint32_t)1;
#else /* Main PLL Clock CFG */
	LPC_SC->LCD_CFG = (uint32_t)5;
#endif

	LCD_Init(LPC_LCD, (LCD_CFG_Type*)&Sharp_LCD);
    LCD_SetFrameBuffer(LPC_LCD, (void*)0xA0000000);
    LCD_Power(LPC_LCD, ENABLE);

    //vd_s_IoLcdInitSplashScreen();					                            
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_LcdPinInit
*	Called By:				vd_g_IoLcdInitTask
*	Timing:					Initialization
*	Description:			Initialize LCD pins.
*
*******************************************************************************************************************************/
static void vd_s_LcdPinInit(void)
{ 
	U1 u1_t_index;
	U1 u1_t_port;
	U1 u1_t_pin;
	U1 u1_t_function;
	U1 u1_t_pintype;
	
	for(u1_t_index = (U1)0; u1_t_index < (U1)LCD_INTERFACE_NUMOF_PINS; u1_t_index++)	/* Loop through pin table */
	{
		u1_t_port = st_tp_LCD_INTERFACE_PINOUT[u1_t_index].u1_port;
		u1_t_pin = st_tp_LCD_INTERFACE_PINOUT[u1_t_index].u1_pin;
		u1_t_function = st_tp_LCD_INTERFACE_PINOUT[u1_t_index].u1_function;
		u1_t_pintype = st_tp_LCD_INTERFACE_PINOUT[u1_t_index].u1_pintype;
	
		PINSEL_ConfigPin(u1_t_port, u1_t_pin, u1_t_function);			/* Set pin to specific function */
		PINSEL_SetPinMode(u1_t_port, u1_t_pin, u1_t_pintype);		/* Set pin type to pull-up or pull-down or NA */
	}
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_IoLcdBacklightInit
*	Called By:				vd_s_IoLcdInitTask
*	Timing:					Initialization
*	Description:			Initialize backlighting
*
*******************************************************************************************************************************/
static void vd_s_IoLcdBacklightInit(void)
{
    GPIO_SetDir(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_MASK, GPIO_DIRECTION_OUTPUT);		    /* Set pin to OUTPUT */
    PINSEL_SetPinMode(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_PIN, IOCON_MODE_PLAIN);         /* Disable pull-up / pull-down resistors */
    GPIO_OutputValue(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_MASK, (U1)OFF);			        /* Initialize to OFF */
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_IoLcdBacklightInit
*	Called By:				vd_s_IoLcdInitTask
*	Timing:					Initialization
*	Description:			Initialize backlighting
*
*******************************************************************************************************************************/
static void vd_s_IoLcdInitSplashScreen(void)
{
    U4 u4_t_max;
    U4 u4_t_idx;
    U2 u2_t_horiz;
    U2 u2_t_vert;
    volatile uint32_t *short_wr_ptr;

    u4_t_max = (480 * 272) / 2;
    short_wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;

    /* Set Background Color */
    short_wr_ptr = (U4 *)SDRAM_BASE_ADDR;

    for (u4_t_idx = (U4)0; u4_t_idx < (SDRAM_SIZE_U4/4); u4_t_idx++ )
    {
        *short_wr_ptr++ = (U4)((BLACK << 16) | BLACK);
    }

}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoLcdTask10ms
*	Called By:				vd_g_IoMgrTask10ms
*	Timing:					10 ms
*	Description:			Call functions to perform LED tasks
*
*******************************************************************************************************************************/
void vd_g_IoLcdTask10ms(void)
{
    if((u2_s_bklt_tmr & 0x7FF) >= (U2)10)
    {
        if((u2_s_bklt_tmr & 0x8000) == (U2)0)
        {
            GPIO_OutputValue(LCD_BACKLIGHT_PORT, LCD_BACKLIGHT_MASK, (U1)ON);			        /* Turn on backlighting */
            u2_s_bklt_tmr |= 0x8000;  /* Set flag to say that backlight is ON */
        }
        else
        {
            /* Do Nothing */
        }
    }
    else
    {
        u2_s_bklt_tmr++;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_IoLcdSetBuffer
*	Called By:				Application
*	Timing:					Application
*	Description:			Change LCD buffer
*
*******************************************************************************************************************************/
void vd_g_IoLcdSetBuffer(U4 u4_a_buffer)
{
    LCD_SetFrameBuffer(LPC_LCD, (void*)u4_a_buffer);
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/14/2012		J. Nabozny			Created
*	1.0.0		3/16/2012		J. Nabozny			Add in version control
*   1.0.1		3/19/2012		J. Nabozny			Add in code to enable power pin correctly
*   1.1.0       4/11/2012       J. Nabozny          Add in framebuffer function
*   1.2.0       5/1/2012        J. Nabozny          Clean up unused code and add vd_g_IoLcdSetColor to update screen color
*
*******************************************************************************************************************************/

