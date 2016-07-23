/*
 * display.c
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */
#include "include/FreeRTOS.h"
#include "include/task.h"

#include "drivers/rit128x96x4.h"
#include "display.h"
#include "images.h"


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
