/*
 * display.c
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

#include "drivers/rit128x96x4.h"
#include "display.h"
#include "images.h"

/* Demo includes. */
#include "demo_code\basic_io.h"

#include "stdlib.h"

//#define ENABLE_DEBUG_MSG

void write_string(char* string, int x, int y, int brightness){ //thread safe string draw
	taskENTER_CRITICAL();
	RIT128x96x4StringDraw(string, x, y, brightness);
	taskEXIT_CRITICAL();
}

void write_image(const Image* image, int x, int y){ //thread safe image draw
	taskENTER_CRITICAL();
	RIT128x96x4ImageDraw(image -> image, x, y, image -> width, image -> height);
	taskEXIT_CRITICAL();
}

void initalise_display(void){ //thread safe screen initalisation
	taskENTER_CRITICAL();
	RIT128x96x4Init(1000000);
	taskEXIT_CRITICAL();
}

void clear_display(void){
	taskENTER_CRITICAL();
	RIT128x96x4Clear();
	taskEXIT_CRITICAL();
}

void xDisplayTask(void* parameters){ //display task

	xQueueHandle display_queue = (xQueueHandle) parameters;
	DisplayTask task;
	while (1){
		if (xQueueReceive(display_queue, &task, 0) != pdPASS){
			/* NOTHING WAS RECIEVED */
//			const char *fail_message = "Nothing in display queue\n";
//			vPrintString(fail_message);
		}
		else{
			//process task
			execute_display_task(&task);
#ifdef ENABLE_DEBUG_MSG
			const char *success_message = "processing display task\n";
			vPrintString(success_message);
#endif
		}
	}
}

void execute_display_task(DisplayTask* task){ //executes a display task and frees the task structure
	if (task -> command == WRITE_IMAGE){
		write_image((const Image*) task -> data, task -> x, task -> y);
	}
	else if (task -> command == CLEAR_SCREEN){
		clear_display();
	}
	free(task);
}

void create_display_queue(xQueueHandle queue){ //initalises a display queue
	//DO NOT CALL THIS FUNCTION. IT IS 100% BROKEN
	queue = xQueueCreate(DISPLAY_QUEUE_LENGTH, sizeof(DisplayTask));
	if (queue == NULL){
		/* FAILED to create queue */
#ifdef ENABLE_DEBUG_MSG
		const char *fail_message = "Failed to create queue\n";
		vPrintString(fail_message);
#endif
	}
}

void enqueue_display_task(xQueueHandle* queue, DisplayTask* task){

	if (xQueueSendToBack(*queue, task, 0) != pdPASS){
		// data could not be put on the queue
#ifdef ENABLE_DEBUG_MSG
		const char *fail_message = "Failed to push data onto queue\n";
		vPrintString(fail_message);
#endif
	}
}
