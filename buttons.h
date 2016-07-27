/*
 * buttons.h
 *
 *  Created on: Jul 25, 2016
 *      Author: srj52
 */


#ifndef BUTTONS_H_
#define BUTTONS_H_

#define NAV_UP GPIO_PIN_3
#define NAV_DOWN GPIO_PIN_4
#define NAV_LEFT GPIO_PIN_5
#define NAV_RIGHT GPIO_PIN_6
#define NAV_BUTTONS NAV_UP | NAV_DOWN | NAV_LEFT | NAV_RIGHT

#define BUTTON_EVENT_QUEUE_LENGTH 20
#define PRESS_EVENT 0
#define RELEASE_EVENT 1

#define PRESSED 0
#define RELEASED 1

#include "include/FreeRTOS.h"
#include "include/queue.h"

typedef struct button_event_s {
	int button_id;
	int event_type;
} ButtonEvent;

typedef struct button_s {
	int port;
} Button;

void button_handler(void);

void initalise_button_interrupts(void);

void initalise_buttons(void);

int read_buttons(void);

unsigned int read_button(int button_id);

void xButtonReadTask(void* parameters);

void initalise_button_event_queue(xQueueHandle* queue);


#endif /* BUTTONS_H_ */
