/*******************************************************************************************************************************
*	
*	Filename: systasks.c
*	Rev Date: 2/7/2012
*
*	File Description:
*			Create various tasks to be called by the scheduler. Tasks will be called here and call out to application
*			code.
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
#include "iomgr.h"
#include "appmgr.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define SYSTASKS_C_VERSION_MAJOR			(1)
#define SYSTASKS_C_VERSION_MINOR			(3)
#define SYSTASKS_C_VERSION_PATCH			(0)

#define LCD_POWER_OFF		(0)
#define LCD_POWER_AVDD		(2)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static U1 u1_s_lcd_power_cntr;


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!(SYSTASKS_C_VERSION_MAJOR == SYSTASKS_H_VERSION_MAJOR))
#error "Software Version Numbers do not match"
#endif

#if(!(SYSTASKS_C_VERSION_MINOR == SYSTASKS_H_VERSION_MINOR))
#error "Software Version Numbers do not match"
#endif

#if(!(SYSTASKS_C_VERSION_PATCH == SYSTASKS_H_VERSION_PATCH))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		vd_g_gameSystemInit
*	Called By:				main
*	Timing:					Initialization
*	Description:			Call all initialization functions for each module.
*
*******************************************************************************************************************************/
void vd_g_gameSystemInit(void)
{
	/* Initialize static variables */
	u1_s_lcd_power_cntr = (U1)LCD_POWER_OFF;

	/* Call initialization functions from here */
	vd_g_IoMgrInitTask();
	vd_g_AppInitTask();
}


/*******************************************************************************************************************************
*	Function Name:		vIOMgr_Task
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Called every 10ms to toggle the state of an LED (on/off). A counter will be used to allow 
*								the timing to be set to different rates.
*
*******************************************************************************************************************************/
void vIOMgr_Task(void *pvParameters) 
{
	for(;;)
	{
		vd_g_IoMgrTask10ms();											/* Call LED Task */
		vTaskDelay(TASK_DELAY_10MS);							/* Delay the task for 10ms */
	}
}


/*******************************************************************************************************************************
*	Function Name:		vAppMgr_Task
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Called every 10ms to toggle the state of an LED (on/off). A counter will be used to allow 
*								the timing to be set to different rates.
*
*******************************************************************************************************************************/
void vAppMgr_Task(void *pvParameters) 
{
	for(;;)
	{
		vd_g_AppMgrTask10ms();
		vTaskDelay(TASK_DELAY_10MS);							/* Delay the task for 10ms */
	}
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev		Date		Author		Change Description
*	------	------		----------	------------------------------
*	0		2/7/2012	J. Nabozny	Created
*	1.0		2/14/2012	J. Nabozny	Separate app and drv layers. Set init to call in IO Manager
*	1.1		2/21/2012	J. Nabozny	Add in LCD Enable task to power the LCD screen correctly
*	1.2		3/11/2012	J. Nabozny	Add in vd_g_AppJsTask10ms call under vAppMgr_Task
*	1.3.0	3/19/2012	J. Nabozny	Add in software version control. Add in GPIO function to enable LCD screen properly.
*
*******************************************************************************************************************************/

