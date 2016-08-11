/*
 * display.h
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define COMMAND_WRITE_IMAGE 0
#define COMMAND_CLEAR_SCREEN 1
#define COMMAND_INITALISE_SCREEN 2
#define COMMAND_WRITE_NUMBER 3
#define COMMAND_WRITE_STRING 4
#define COMMAND_WRITE_RIT_STRING 5
#define COMMAND_UPDATE_LATENCY 6

#define DISPLAY_QUEUE_LENGTH 80

 #define MAX_BRIGHTNESS 15

#include "images.h"
#include "include/queue.h"

typedef struct display_task_s {
	void* data;
	int x;
	int y;
	int command;
} DisplayTask;

extern int MAX_TIMEOUT;
extern long AVERAGE_TIMEOUT;
extern long TIMEOUT_SAMPLES;

void xDisplayTask(void* parameters);
//Display task

void execute_display_task(DisplayTask* task);
//executes a dispay task

void update_latency(DisplayTask* task);
//update the screen update latency recordings

void initalise_display_queue(xQueueHandle* queue);
//initalize the display queue

void enqueue_display_task(xQueueHandle* queue, DisplayTask* task);
//enqueue a display task on the display queue

void quick_initalise_screen(xQueueHandle* queue);
//initalize the screen

void quick_send_image(xQueueHandle* queue, int x, int y, const Image* image);
//send an image to the screen

void quick_clear_screen(xQueueHandle* queue);
//clear the screen

void quick_send_number(xQueueHandle* queue, int x, int y, int number);
//sends a number to the screen

void quick_send_string(xQueueHandle* queue, int x, int y, char* string);
//send a string to the screen

void quick_send_string_rit(xQueueHandle* queue, int x, int y, char* string);
//send a "normal" strin to the screen

#endif /* DISPLAY_H_ */
