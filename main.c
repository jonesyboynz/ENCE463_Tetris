/*
    FreeRTOS V6.0.5 - Copyright (C) 2009 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"

/* Stellaris library includes. */
#include "inc\hw_types.h"
#include "inc\hw_memmap.h"
#include "inc\hw_sysctl.h"
#include "driverlib/sysctl.h"
#include "drivers/rit128x96x4.h"
#include "stdio.h"
#include "stdlib.h"

/* Demo includes. */
#include "demo_code\basic_io.h"

/* tetris game engine includes */
#include "display.h"
#include "game_engine.h"
#include "tetrominoe.h"
#include "bool.h"

/* Used as a loop counter to create a very crude delay. */
#define mainDELAY_LOOP_COUNT		( 0xfffff )

/* The task function. */
void vTaskFunction( void *pvParameters );
void vTaskDelayTest(void* pvParameters);
void vTaskImageFun(void* pvParameters);
void write_background(void* parameters);
void tetronimoe_drop_test(void* parameters);
void tetronimoe_drop_test2(void* parameters);

/* Define the strings that will be passed in as the task parameters.  These are
defined const and off the stack to ensure they remain valid when the tasks are
executing. */
const char *pcTextForTask1 = "Task 1 is running\n";
const char *pcTextForTask2 = "Task 2 is running\n";

/*-----------------------------------------------------------*/

int main( void )
{
	/* Set the clocking to run from the PLL at 50 MHz.  Assumes 8MHz XTAL,
	whereas some older eval boards used 6MHz. */
	SysCtlClockSet( SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_8MHZ );
	RIT128x96x4Init(1000000);

	initalise_game(&game);

	/* Create one of the two tasks. */
//	xTaskCreate(	vTaskFunction,			/* Pointer to the function that implements the task. */
//					"Task 1",				/* Text name for the task.  This is to facilitate debugging only. */
//					240,					/* Stack depth in words. */
//					(void*)pcTextForTask1,	/* Pass the text to be printed in as the task parameter. */
//					1,						/* This task will run at priority 1. */
//					NULL );					/* We are not using the task handle. */

	/* Create the other task in exactly the same way.  Note this time that we
	are creating the SAME task, but passing in a different parameter.  We are
	creating two instances of a single task implementation. */
	//xTaskCreate( vTaskFunction, "Task 2", 240, (void*)pcTextForTask2, 1, NULL );

	//xTaskCreate(vTaskDelayTest, "Task 3", 240, NULL, 1, NULL);
	//xTaskCreate(vTaskImageFun, "Task 4", 240, NULL, 1, NULL);
	//xTaskCreate(write_background, "Task 5", 500, NULL, 1, NULL);
	xTaskCreate(tetronimoe_drop_test2, "Task 6", 500, NULL, 1, NULL);

	/* Start the scheduler so our tasks start executing. */
	vTaskStartScheduler();	
	
	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
char *pcTaskName;
volatile unsigned long ul;

	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */
	pcTaskName = ( char * ) pvParameters;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		vPrintString( pcTaskName );
		/* Delay for a period. */
		for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
		{
			/* This loop is just a very crude delay implementation.  There is
			nothing to do in here.  Later exercises will replace this crude
			loop with a proper delay/sleep function. */
		}
	}
}
/*-----------------------------------------------------------*/

void vTaskDelayTest(void* pvParameters){
	portTickType xLastWakeTime;
	while (1){
		taskENTER_CRITICAL();
		RIT128x96x4StringDraw("    Hz", 30, 24, 15);
		taskEXIT_CRITICAL();
		vTaskDelayUntil(&xLastWakeTime, (500 / portTICK_RATE_MS));
		taskENTER_CRITICAL();
		RIT128x96x4StringDraw("One   ", 30, 24, 15);
		taskEXIT_CRITICAL();
		vTaskDelayUntil(&xLastWakeTime, (500 / portTICK_RATE_MS));
	}
}

void write_background(void* parameters){
	write_image(&TETRIS_BACKGROUND, 0, 0);
	vTaskDelete(NULL);
}

void tetronimoe_drop_test(void* parameters){
	//portTickType xLastWakeTime;
	while (1){
		game.tetrominoes[game.current_peice_index] -> x = 0;
		draw_current_tetrominoe(&game);
		vTaskDelay(250 / portTICK_RATE_MS);
		erase_current_tetrominoe(&game);
		game.tetrominoes[game.current_peice_index] -> y = (game.tetrominoes[game.current_peice_index] -> y + 1) % 17;
		if (game.tetrominoes[game.current_peice_index] -> y == 0){
			rotate_tetromineo(game.tetrominoes[game.current_peice_index]);
			game.current_peice_index = (game.current_peice_index + 1) % game.num_tetrominoes;
		}
	}
}

void tetronimoe_drop_test2(void* parameters){
	//portTickType xLastWakeTime;
	int x_pos = 0;
	while (1){
		game.tetrominoes[game.current_peice_index] -> x = x_pos;
		draw_current_tetrominoe(&game);
		vTaskDelay(250 / portTICK_RATE_MS);
		if (can_drop_current_tetrominoe(&game) == TRUE){
			erase_current_tetrominoe(&game);
			game.tetrominoes[game.current_peice_index] -> y = (game.tetrominoes[game.current_peice_index] -> y + 1);
		}
		else{
			place_current_tetrominoe(&game);
			//debug_board(&game);
			game.tetrominoes[game.current_peice_index] -> y = 0;
			rotate_tetromineo(game.tetrominoes[game.current_peice_index]);
			game.current_peice_index = (game.current_peice_index + 1) % game.num_tetrominoes;
			x_pos = (x_pos + 2) % 7;
		}
	}
}

void vTaskImageFun(void* pvParameters){
	int x = 0;
	portTickType xLastWakeTime;
	while (1){
		write_image(&EMPTY_CELL, x, 60);
		x = (x + 1) % 100;
		write_image(&FULL_CELL, x, 60);
		vTaskDelayUntil(&xLastWakeTime, (500 / portTICK_RATE_MS));
	}
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


