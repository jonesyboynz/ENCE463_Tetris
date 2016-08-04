/*
 * buttons.h
 *
 *  Created on: Jul 25, 2016
 *      Author: srj52
 */


#ifndef BUTTONS_H_
#define BUTTONS_H_

//system includes
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "stdio.h"
#include "stdlib.h"

#include "timer.h"


#define NAV_UP GPIO_PIN_6
#define NAV_DOWN GPIO_PIN_5
#define NAV_LEFT GPIO_PIN_3
#define NAV_RIGHT GPIO_PIN_4

#define NAV_BUTTONS NAV_UP | NAV_DOWN | NAV_LEFT | NAV_RIGHT

#define BUTTON_EVENT_QUEUE_LENGTH 20
#define PRESS_EVENT 0
#define RELEASE_EVENT 1

#define PRESSED 0
#define RELEASED 1

#define NUM_BUTTONS 4
#define BUTTON_DEBOUNCE_MS 1

#include "include/FreeRTOS.h"
#include "include/queue.h"

typedef struct button_event_s {
	int button_id;
	int event_type;
	int occurance_tick;
} ButtonEvent;

typedef struct button_s {
	int id;
	int port;
	int current_state;
	int debouncing;
	Timeout debounce;
} Button;

extern Button* BUTTONS[NUM_BUTTONS];

void initalise_buttons(Button** button);

void initalise_button (Button* button);

int read_button(Button* button);

int button_event_occurred(Button* button, ButtonEvent* event);

void xButtonReadTask(void* parameters);

void initalise_button_event_queue(xQueueHandle* queue);

void enqueue_button_event(xQueueHandle* queue, ButtonEvent* event);

//ALL THE INTERRUPT-BASED BUTTON PROCESSING IS BROKE

void button_ish(void);

void initalise_button_interrupts(void);

int read_buttons(void);

#endif /* BUTTONS_H_ */
