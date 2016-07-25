/*
 * display.h
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#define WRITE_IMAGE 0
#define CLEAR_SCREEN 1

#define DISPLAY_QUEUE_LENGTH 40

#include "images.h"
#include "include/queue.h"

typedef struct display_task_s {
	void* data;
	int x;
	int y;
	int command;
} DisplayTask;

void write_string(char* string, int x, int y, int brightness);

void write_image(const Image* image, int x, int y);

void initalise_display(void);

void clear_display(void);

void xDisplayTask(void* parameters);

void execute_display_task(DisplayTask* task);

void create_display_queue(xQueueHandle queue);

void enqueue_display_task(xQueueHandle* queue, DisplayTask* task);

#endif /* DISPLAY_H_ */
