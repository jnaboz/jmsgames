/*******************************************************************************************************************************
*	
*	Filename: iobtn.c
*	Rev Date: 2/14/2012
*
*	File Description:
*			IO manager for Buttons
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "pinmacro.h"
#include "iobtn.h"
#include "iobtn_cfg.h"
#include "lpc177x_8x_gpio.h"

/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOBTN_C_VERSION_MAJOR			(1)
#define IOBTN_C_VERSION_MINOR			(1)
#define IOBTN_C_VERSION_PATCH			(0)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_IoBtnUpd(void);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((IOBTN_C_VERSION_MAJOR == IOBTN_H_VERSION_MAJOR) && (IOBTN_C_VERSION_MAJOR == IOBTN_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOBTN_C_VERSION_MINOR == IOBTN_H_VERSION_MINOR) && (IOBTN_C_VERSION_MINOR == IOBTN_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOBTN_C_VERSION_PATCH == IOBTN_H_VERSION_PATCH) && (IOBTN_C_VERSION_PATCH == IOBTN_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoBtnInitTask
*	Called By:				vd_g_IoMgrInitTask
*	Timing:					Initialization
*	Description:			Initialize button configurations
*
*******************************************************************************************************************************/
void vd_g_IoBtnInitTask(void)
{
	U1 u1_t_index;
	U1 u1_t_index2;
	
	for(u1_t_index = (U1)0; u1_t_index < (U1)IO_BUTTON_NUMOF_PINS; u1_t_index++)
	{
		GPIO_SetDir(st_tp_g_Buttons[u1_t_index].u1_port, st_tp_g_Buttons[u1_t_index].u1_pin, GPIO_DIRECTION_INPUT);
	
		*(st_tp_g_Buttons[u1_t_index].u1_button_name) = (U1)IO_BUTTON_NOT_PRESSED;
		*(st_tp_g_Buttons[u1_t_index].u1_button_index) = (U1)0;
		
		for(u1_t_index2 = (U1)0; u1_t_index2 < (U1)IO_NUMOF_DEBOUNCE; u1_t_index2++)
		{
			*(st_tp_g_Buttons[u1_t_index].u1_button_array + u1_t_index2) = (U1)0;
		}
	}
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoBtnTask10ms
*	Called By:				vd_g_IoMgrTask10ms
*	Timing:					10 ms
*	Description:			Call functions to perform Button tasks
*
*******************************************************************************************************************************/
void vd_g_IoBtnTask10ms(void)
{
	vd_s_IoBtnUpd();
}


/*******************************************************************************************************************************
*	Function Name:		vd_s_IoBtnUpd
*	Called By:				vd_g_IoBtnTask10ms
*	Timing:					10 ms
*	Description:			Update state of Buttons
*
*******************************************************************************************************************************/
static void vd_s_IoBtnUpd(void)
{
	U1 u1_t_index;
	U4 u4_t_tmp;
	
	for(u1_t_index = (U1)0; u1_t_index < (U1)IO_BUTTON_NUMOF_PINS; u1_t_index++)
	{
		u4_t_tmp = GPIO_ReadValue(st_tp_g_Buttons[u1_t_index].u1_port);
		
		*(st_tp_g_Buttons[u1_t_index].u1_button_array + *(st_tp_g_Buttons[u1_t_index].u1_button_index)) = (U1)((u4_t_tmp & (1 << st_tp_g_Buttons[u1_t_index].u1_pin)) >> st_tp_g_Buttons[u1_t_index].u1_pin);
		
		if((*st_tp_g_Buttons[u1_t_index].u1_button_index) == (U1)0)
		{
			(*st_tp_g_Buttons[u1_t_index].u1_button_index) += (U1)1;
		}
		else
		{
			if(*(st_tp_g_Buttons[u1_t_index].u1_button_array + *st_tp_g_Buttons[u1_t_index].u1_button_index) == *(st_tp_g_Buttons[u1_t_index].u1_button_array + (*st_tp_g_Buttons[u1_t_index].u1_button_index - (U1)1)))
			{
				*(st_tp_g_Buttons[u1_t_index].u1_button_index) += (U1)1;
			}
			else
			{
				*(st_tp_g_Buttons[u1_t_index].u1_button_index) = (U1)0;
			}
		}
		
		if(*st_tp_g_Buttons[u1_t_index].u1_button_index >= (U1)IO_NUMOF_DEBOUNCE)
		{
			*(st_tp_g_Buttons[u1_t_index].u1_button_index) = (U1)RESET;	
			*(st_tp_g_Buttons[u1_t_index].u1_button_name) = (U1)((u4_t_tmp & (1 << st_tp_g_Buttons[u1_t_index].u1_pin)) >> st_tp_g_Buttons[u1_t_index].u1_pin);
		}
	}
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoGetBtnA
*	Called By:				Application (LED)
*	Timing:					Application
*	Description:			Call function to get the state of Button A
*
*******************************************************************************************************************************/
U1 u1_g_IoGetBtnA(void)
{
	return u1_g_button_A;
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoGetBtnB
*	Called By:				Application
*	Timing:					Application
*	Description:			Call function to get the state of Button B
*
*******************************************************************************************************************************/
U1 u1_g_IoGetBtnB(void)
{
	return u1_g_button_B;
}

/*******************************************************************************************************************************
*	Function Name:		vd_g_IoGetBtnC
*	Called By:				Application
*	Timing:					Application
*	Description:			Call function to get the state of Button C
*
*******************************************************************************************************************************/
U1 u1_g_IoGetBtnC(void)
{
	return u1_g_button_C;
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoGetBtnD
*	Called By:				Application
*	Timing:					Application
*	Description:			Call function to get the state of Button D
*
*******************************************************************************************************************************/
U1 u1_g_IoGetBtnD(void)
{
	return u1_g_button_D;
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoGetBtnR
*	Called By:				Application
*	Timing:					Application
*	Description:			Call functions to get the state of Button R
*
*******************************************************************************************************************************/
U1 u1_g_IoGetBtnR(void)
{
	return u1_g_button_R;
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoGetBtnL
*	Called By:				Application
*	Timing:					Application
*	Description:			Call functions to get the state of Button L
*
*******************************************************************************************************************************/
U1 u1_g_IoGetBtnL(void)
{
	return u1_g_button_L;
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoGetBtnStart
*	Called By:				Application
*	Timing:					Application
*	Description:			Call functions to get the state of Start Button
*
*******************************************************************************************************************************/
U1 u1_g_IoGetBtnStart(void)
{
	return u1_g_button_START;
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/14/2012		J. Nabozny			Created
*	1.0			2/16/2012		J. Nabozny			Add in functions to read button pins and to send data to application layer.
*	1.0.1		3/16/2012		J. Nabozny			Add in version control
*	1.1.0		3/23/2012		S. Cieslik			Add in initialization and button debouncing code
*
*******************************************************************************************************************************/

