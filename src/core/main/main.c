/**
 * Name        : main.c
 * Version     :
 * Description : main definition for FreeRTOS application
 */

/*
 * FreeRTOS includes
 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "system_LPC177x_8x.h"
#include "lpc177x_8x_clkpwr.h"
#include "systasks.h"
#include "lpc_types.h"
#include "vardef.h"


void __error__(char *pcFilename, unsigned long ulLine) 
{
}

static void setupHardware(void) 
{
	
	SYSTICK_InternalInit(10);		/* Initialize System Tick with 10ms time interval */
	SYSTICK_IntCmd(ENABLE);			/* Enable System Tick interrupt */		 	
	SYSTICK_Cmd(ENABLE);			/* Enable System Tick counter */
}



/*	Program Entry Point */
int main(void) 
{
	setupHardware();	/* Set up hardware clock (systick) */
	
	vd_g_gameSystemInit();	/* Call system initialization function for initialization of all modules */

    xTaskCreate( vAppMgr_Task, ( signed portCHAR * ) "AppMgr_Task", USERTASK_STACK_SIZE, NULL, TASK_PRIORITY_LOW, NULL );		/* Start the task to manage app. */
    xTaskCreate( vIOMgr_Task, ( signed portCHAR * ) "IOMgr_Task", USERTASK_STACK_SIZE, NULL, TASK_PRIORITY_HIGH, NULL );		/* Start the task to manage IO. */

	vTaskStartScheduler();		/* Start the scheduler */

	
	
	/* 
	 * Will only get here if there was insufficient memory to create the idle task. 
	 */
	return 1;
}