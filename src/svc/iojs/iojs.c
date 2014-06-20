/*******************************************************************************************************************************
*	
*	Filename: iojs.c
*	Rev Date: 2/14/2012
*
*	File Description:
*			IO manager for joystick
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "pinmacro.h"
#include "lpc_types.h"
#include "vardef.h"
#include "iojs.h"
#include "iojs_cfg.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_adc.h"
#include "lpc177x_8x_pinsel.h"

/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOJS_C_VERSION_MAJOR			(1)
#define IOJS_C_VERSION_MINOR			(2)
#define IOJS_C_VERSION_PATCH			(1)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_IoJsPinInit(void);
static void vd_s_IoJsUpd(void);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((IOJS_C_VERSION_MAJOR == IOJS_H_VERSION_MAJOR) && (IOJS_C_VERSION_MAJOR == IOJS_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOJS_C_VERSION_MINOR == IOJS_H_VERSION_MINOR) && (IOJS_C_VERSION_MINOR == IOJS_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOJS_C_VERSION_PATCH == IOJS_H_VERSION_PATCH) && (IOJS_C_VERSION_PATCH == IOJS_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:			vd_g_IoJsInitTask
*	Called By:				vd_g_IoMgrInitTask
*	Timing:					Initialization
*	Description:			Initialization function for Joysticks
*
*******************************************************************************************************************************/
void vd_g_IoJsInitTask(void)
{
    U1 u1_t_index;

	vd_s_IoJsPinInit();
	ADC_Init(LPC_ADC, IOJS_SAMPLE_RATE);
	
	/* Set interrupts for ADC pins */
	ADC_IntConfig (LPC_ADC, ADC_ADGINTEN, DISABLE);
	
	for(u1_t_index = (U1)0; u1_t_index < (U1)IO_JS_NUM; u1_t_index++) 
    {
        *(st_tp_g_Joysticks[u1_t_index].STATE) = (U1)CENTER; 
        ADC_ChannelCmd(LPC_ADC, st_tp_g_Joysticks[u1_t_index].u1_ADC_Channel, ENABLE);
        ADC_IntConfig(LPC_ADC, st_tp_g_Joysticks[u1_t_index].u1_ADC_Interrupt, DISABLE);
    }
}


/*******************************************************************************************************************************
*	Function Name:			vd_s_IoJsPinInit
*	Called By:				vd_g_IoJsInitTask
*	Timing:					Initialization
*	Description:			Initialization function for Joystick Pins
*
*******************************************************************************************************************************/
static void vd_s_IoJsPinInit(void)
{
	PINSEL_ConfigPin (ADC_JOYSTICK_LX_PORT, ADC_JOYSTICK_LX_PIN, ADC_JOYSTICK_LX_FUNCTION);
	PINSEL_ConfigPin (ADC_JOYSTICK_LY_PORT, ADC_JOYSTICK_LY_PIN, ADC_JOYSTICK_LY_FUNCTION);
	PINSEL_ConfigPin (ADC_JOYSTICK_RX_PORT, ADC_JOYSTICK_RX_PIN, ADC_JOYSTICK_RX_FUNCTION);
	PINSEL_ConfigPin (ADC_JOYSTICK_RY_PORT, ADC_JOYSTICK_RY_PIN, ADC_JOYSTICK_RY_FUNCTION);
}


/*******************************************************************************************************************************
*	Function Name:			vd_g_IoJsTask10ms
*	Called By:				vd_g_IoMgrTask10ms
*	Timing:					10 ms
*	Description:			Call functions to update joystick values
*
*******************************************************************************************************************************/
void vd_g_IoJsTask10ms(void)
{
	vd_s_IoJsUpd();
}


/*******************************************************************************************************************************
*	Function Name:			vd_s_IoJsUpd
*	Called By:				vd_g_IoJsTask10ms
*	Timing:					10 ms
*	Description:			Function to update Joystick ADC Values
*
*******************************************************************************************************************************/
static void vd_s_IoJsUpd(void)
{
    U1 u1_t_state;
    U1 u1_t_channel;
	U2 u2_t_temp2;
	U1 u1_t_i;

	ADC_BurstCmd(LPC_ADC, ENABLE);                                                              /* Start Burst Conversion */
	
	for(u1_t_i = (U1)0; u1_t_i < (U1)IO_JS_NUM; u1_t_i++)                                       /* Loop through all Joystick channels */
	{
        while(!(ADC_ChannelGetStatus(LPC_ADC, st_tp_g_Joysticks[u1_t_i].u1_ADC_Channel, ADC_DATA_DONE)))    /* Wait for conversion */
        {
            /* Wait for ADC Conversion */
        }
	}

    for(u1_t_i = (U1)0; u1_t_i < (U1)IO_JS_NUM; u1_t_i++) 
    {
        u1_t_channel = st_tp_g_Joysticks[u1_t_i].u1_ADC_Channel;                                /* Get Channel */
        u1_t_state = *(st_tp_g_Joysticks[u1_t_i].STATE);                                        /* Get State */

    	u2_t_temp2 = ADC_ChannelGetData(LPC_ADC, u1_t_channel);                                 /* Get ADC Value */

        if(u2_t_temp2 > st_tp_g_Joysticks[u1_t_i].ST_STATE_CFG[u1_t_state].u2_max)              /* Above State Threshold ? */
    	{
            (*(st_tp_g_Joysticks[u1_t_i].STATE))++;                                             /* Increment State */
    	}
    	else if(u2_t_temp2 < st_tp_g_Joysticks[u1_t_i].ST_STATE_CFG[u1_t_state].u2_min)         /* Below State Threshold ? */
    	{
            (*(st_tp_g_Joysticks[u1_t_i].STATE))--;                                             /* Decrement State */
    	}
        else                                                                                    /* Still within state limits */
        {
            /* Do Nothing */
        }
    }
}


/*******************************************************************************************************************************
*	Function Name:			u1_g_IoGetJsState
*	Called By:				Application
*	Timing:					Application
*	Description:			Call function to get the value of the Left Joystick X-Axis
*
*******************************************************************************************************************************/
U1 u1_g_IoGetJsState(U1 u1_a_js)
{
	return *(st_tp_g_Joysticks[u1_a_js].STATE);
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/14/2012		J. Nabozny			Created
*	1.0			3/11/2012		J. Nabozny			Edit AD read functions. Change joystick values to U2 instead of U4.
*													Fix pin configurations and ADC clock/power configurations.
*	1.1			3/13/2012		J. Nabozny			Add Joystick LED update functions and initialization functions
*	1.1.1		3/16/2012		J. Nabozny			Add in version control
*   1.1.2		3/30/2012		J. Nabozny			Add in new sample rate for ADC conversion
*   1.2.0       4/9/2012        S. Cieslik          Add in code to handle hysteresis and lookup table information for joysticks
*                               J. Nabozny          Edit update code to handle only states instead of values.
*   1.2.1       5/3/2012        J. Nabozny          Remove unused code
*
*******************************************************************************************************************************/

