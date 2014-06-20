/*******************************************************************************************************************************
*	
*	Filename: iomgr.c
*	Rev Date: 2/14/2012
*
*	File Description:
*			Perform IO Tasks Here
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "pinmacro.h"
#include "iomgr.h"
#include "iomgr_cfg.h"
#include "iolcd.h"
#include "iobtn.h"
#include "iojs.h" 
#include "iospkr.h"
#include "iosdram.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOMGR_C_VERSION_MAJOR			(1)
#define IOMGR_C_VERSION_MINOR			(1)
#define IOMGR_C_VERSION_PATCH			(1)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((IOMGR_C_VERSION_MAJOR == IOMGR_H_VERSION_MAJOR) && (IOMGR_C_VERSION_MAJOR == IOMGR_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOMGR_C_VERSION_MINOR == IOMGR_H_VERSION_MINOR) && (IOMGR_C_VERSION_MINOR == IOMGR_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOMGR_C_VERSION_PATCH == IOMGR_H_VERSION_PATCH) && (IOMGR_C_VERSION_PATCH == IOMGR_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoMgrInitTask
*	Called By:			vd_g_gameSystemInit
*	Timing:				Initialization
*	Description:		Task to initialize IO
*
*******************************************************************************************************************************/
void vd_g_IoMgrInitTask(void) 
{
	vd_g_IoSdramInitTask();
	vd_g_IoLcdInitTask();
	vd_g_IoBtnInitTask();
	vd_g_IoJsInitTask();
    vd_g_IoSpkrInitTask();
}


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoMgrTask10ms
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Called every 10ms to update values in the IO layer.
*
*******************************************************************************************************************************/
void vd_g_IoMgrTask10ms(void) 
{
	vd_g_IoBtnTask10ms();
	vd_g_IoJsTask10ms();
    vd_g_IoLcdTask10ms();
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev		Date		Author			Change Description
*	------	------		----------		------------------------------
*	0		2/14/2012	J. Nabozny		Created
*	1.0.0	3/16/2012	J. Nabozny		Add in version control
*   1.0.1	3/28/2012	J. Nabozny		Add in SDRAM initialization and task
*   1.1.0   5/1/2012    J. Nabozny      Add LCD 10ms task for backlight enabling and delay
*   1.1.1   5/3/2012    J. Nabozny      Remove unused code
*
*******************************************************************************************************************************/

