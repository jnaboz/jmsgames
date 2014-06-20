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
#include "bsp.h"
#include "system_LPC177x_8x.h"
#include "lpc177x_8x_gpio.h"
#include "lpc177x_8x_clkpwr.h"
#include "sdram_k4s561632j.h"



#define USERTASK_STACK_SIZE configMINIMAL_STACK_SIZE


uint8_t value = 1;

void __error__(char *pcFilename, unsigned long ulLine) {
}

static void setupHardware(void) {
	// TODO: Put hardware configuration and initialisation in here
	// Warning: If you do not initialize the hardware clock, the timings will be inaccurate
	SYSTICK_InternalInit(10);
	SystemCoreClockUpdate();
}

/**
 * Simple task that just toggles between to states
 */
void vUserTask1(void *pvParameters) {

	//value = !value;
	GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, 0);	
		
	vTaskDelay(100 / portTICK_RATE_MS);
}

/**
 * Simple task that increments a counter
 */
void vUserTask2(void *pvParameters) {

	vTaskDelay(100) ;
}

/**
 * Program entry point 
 */
int main(void) {

	setupHardware();

	GPIO_SetDir(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, GPIO_DIRECTION_OUTPUT);					   
	GPIO_OutputValue(BRD_LED_2_CONNECTED_PORT, BRD_LED_2_CONNECTED_MASK, 0);
	/* 
	 * Start the tasks defined within this file/specific to this demo. 
	 */
	xTaskCreate( vUserTask1, ( signed portCHAR * ) "Task1", USERTASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	xTaskCreate( vUserTask2, ( signed portCHAR * ) "Task2", USERTASK_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

	/* 
	 * Start the scheduler. 
	 */
	vTaskStartScheduler();

	/* 
	 * Will only get here if there was insufficient memory to create the idle task. 
	 */
	return 1;
}
