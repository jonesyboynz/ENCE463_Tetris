/*
Main file for the freerots tetris project. Schedules all tasks
By Simon Jones
*/

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

/* Stellaris library includes. */
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"
#include "inc\hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "drivers/rit128x96x4.h"
#include "driverlib/interrupt.h"
#include "stdio.h"
#include "stdlib.h"

/* Demo includes. */
#include "demo_code\basic_io.h"

/* tetris game engine includes */
#include "display.h"
#include "game_engine.h"
#include "tetrominoe.h"
#include "bool.h"
#include "buttons.h"
#include "math.h"

/* test module include */
#include "tests.h"

/*-----------------------------------------------------------*/

int main( void )
{
	/* Set the clocking to run from the PLL at 50 MHz.  Assumes 8MHz XTAL,
	whereas some older eval boards used 6MHz. */
	SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );

	//game system initalisation
	initalise_random_number_generator(512512);
	initalise_buttons(BUTTONS);
	initalise_game(&base_game);

	//debugging tasks
	//xTaskCreate(tetronimoe_drop_test2, "Task 6", 600, &base_game, 1, NULL);
	//xTaskCreate(vButtonTest, "button test", 200, (void*) base_game.button_queue, 1, NULL);
	//xTaskCreate(vDisplayRunning, "display task test", 200, (void*) base_game.display_queue, 1, NULL);

	//game system tasks
	xTaskCreate(xGameEngineTask, "game engine", 600, (void*) &base_game, 1, NULL);
	xTaskCreate(xDisplayTask, "display task", 500, (void*) base_game.display_queue, 1, NULL);
	xTaskCreate(xButtonReadTask, "button poll task", 500, (void*) base_game.button_queue, 1, NULL);

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();	
	
	for( ;; );
}


void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}


