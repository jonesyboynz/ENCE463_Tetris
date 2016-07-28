/*
 * display.c
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */
 //freertos includes
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

#include "drivers/rit128x96x4.h"
#include "display.h"
#include "images.h"
#include "strings.h"

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

void clear_display(void){ //thread safe display clear
	taskENTER_CRITICAL();
	RIT128x96x4Clear();
	taskEXIT_CRITICAL();
}

void write_tetris_number(int number, int x, int y){ //displays a number in the tetris screen mode (rotated 90deg)
	int numsize = 10;
	int y_shift = 0;
	int number_copy = number;
	while (numsize <= number){
		numsize *= 10;
	}
	while (numsize > 1){
		numsize /= 10;
		int value = number_copy / numsize;
		number_copy = number_copy - (numsize * value);
		write_image(NUMBERS[value], x, y + y_shift);
		y_shift += NUMBERS[value] -> height + 1;
	}

}

void write_tetris_string(char* string, int x, int y){ //displays a string in the tetris screen mode (rotated 90deg)
	int index = 0;
	int y_shift = 0;
	int x_shift = 0;
	while (string[index] != '\00'){
		char current_character = string[index];
		if (current_character == '\n'){
			x_shift -= FONT[0] -> height + 1;
			y_shift = 0;
		}
		else{
			if (current_character == ' '){
				current_character = 28;
			}
			current_character -= 'A';
			if (current_character > 29){
				current_character = 29;
			}
			write_image (FONT[current_character], x + x_shift, y + y_shift);
			y_shift += FONT[current_character] -> width + 1;
		}
		index += 1;
	}
}

void xDisplayTask(void* parameters){ //display task. handles all output to the rit display

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
	if (task -> command == COMMAND_WRITE_IMAGE){
		write_image((const Image*) task -> data, task -> x, task -> y);
	}
	else if (task -> command == COMMAND_CLEAR_SCREEN){
		clear_display();
	}
	else if (task -> command == COMMAND_INITALISE_SCREEN){
		initalise_display();
	}
	else if (task -> command == COMMAND_WRITE_NUMBER){
		write_tetris_number((int) task -> data, task -> x, task -> y);
	}
	else if (task -> command == COMMAND_WRITE_STRING){
		write_tetris_string((char*) task -> data, task -> x, task -> y);
	}
	else if (task -> command == COMMAND_WRITE_RIT_STRING){
		write_string((char*) task -> data, task -> x, task -> y, MAX_BRIGHTNESS);
	}
}

void initalise_display_queue(xQueueHandle* queue){ //initalises a display queue
	*queue = xQueueCreate(DISPLAY_QUEUE_LENGTH, sizeof(DisplayTask));
	if (queue == NULL){
		/* FAILED to create queue */
#ifdef ENABLE_DEBUG_MSG
		const char *fail_message = "Failed to create queue\n";
		vPrintString(fail_message);
#endif
	}
}

void enqueue_display_task(xQueueHandle* queue, DisplayTask* task){ //enqueues a display task

	if (xQueueSendToBack(*queue, task, 0) != pdPASS){
		// data could not be put on the queue
#ifdef ENABLE_DEBUG_MSG
		const char *fail_message = "Failed to push data onto queue\n";
		vPrintString(fail_message);
#endif
	}
}

void quick_initalise_screen(xQueueHandle* queue){ //sends the commands needed to initalise the screen
	DisplayTask task1 = {NULL, 0, 0, COMMAND_INITALISE_SCREEN};
	DisplayTask task2 = {NULL, 0, 0, COMMAND_CLEAR_SCREEN};
	enqueue_display_task(queue, &task1);
	enqueue_display_task(queue, &task2);
}

void quick_send_image(xQueueHandle* queue, int x, int y, const Image* image){ //sends an image to the display task
	DisplayTask task = {(void*) image, x, y, COMMAND_WRITE_IMAGE};
	enqueue_display_task(queue, &task);
}

void quick_clear_screen(xQueueHandle* queue){ //sends the commands needed to clear the screen
	DisplayTask task = {NULL, 0, 0, COMMAND_CLEAR_SCREEN};
	enqueue_display_task(queue, &task);
}

void quick_send_number(xQueueHandle* queue, int x, int y, int number){ //sends an number to the display task
	DisplayTask task = {(void*) number, x, y, COMMAND_WRITE_NUMBER};
	enqueue_display_task(queue, &task);
}

void quick_send_string(xQueueHandle* queue, int x, int y, char* string){ //sends a string
	DisplayTask task = {(void*) string, x, y, COMMAND_WRITE_STRING};
	enqueue_display_task(queue, &task);
}

void quick_send_string_rit(xQueueHandle* queue, int x, int y, char* string){ //sends a rit string
	DisplayTask task = {(void*) string, x, y, COMMAND_WRITE_RIT_STRING};
	enqueue_display_task(queue, &task);
}
