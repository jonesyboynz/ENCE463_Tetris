/*
 * buttons.c
 *
 *  Created on: Jul 25, 2016
 *      Author: srj52
 */

#include "buttons.h"
#include "bool.h"

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

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

Button UP = {NAV_UP, GPIO_PORTG_BASE, 0, 0, {0, 0}};
Button DOWN = {NAV_DOWN, GPIO_PORTG_BASE, 0, 0, {0, 0}};
Button RIGHT = {NAV_RIGHT, GPIO_PORTG_BASE, 0, 0, {0, 0}};
Button LEFT = {NAV_LEFT, GPIO_PORTG_BASE, 0, 0, {0, 0}};

Button* BUTTONS[NUM_BUTTONS] = {&UP, &DOWN, &LEFT, &RIGHT};

void initalise_buttons(Button** buttons){ //initalises the buttons for standard polling mode
	int i;
	//Do a fancy button initalizer here if there is time
	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);
	GPIOPadConfigSet (GPIO_PORTG_BASE, NAV_BUTTONS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	for (i = 0; i < NUM_BUTTONS; i++){
		initalise_button(buttons[i]);
	}
}

void initalise_button (Button* button){//initalises a single button
	button -> current_state = read_button(button);
	button -> debouncing = FALSE;
}

int read_button(Button* button){ //reads a button
	taskENTER_CRITICAL();
	int value = GPIOPinRead(button -> port, button -> id) == button -> id;
	taskEXIT_CRITICAL();
	return value;
}

int button_event_occurred(Button* button, ButtonEvent* event){ //reads a button event
	int current_state = read_button(button);
	if (current_state != button -> current_state){
		event -> button_id = button -> id;
		event -> event_type = current_state;
		button -> debouncing = TRUE;
		button -> current_state = current_state;
		start_timeout(&(button -> debounce), BUTTON_DEBOUNCE_MS);
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void xButtonReadTask(void* parameters){ //task to pereodically poll the buttons
	xQueueHandle button_queue = (xQueueHandle) parameters;
	ButtonEvent event;
	int i;
	while (TRUE){
		for (i = 0; i < NUM_BUTTONS; i++){
			if (TRUE | BUTTONS[i] -> debouncing == FALSE){
				if (button_event_occurred(BUTTONS[i], &event) == TRUE){
					enqueue_button_event(&button_queue, &event);
				}
			}
			else if (has_timed_out(&(BUTTONS[i] -> debounce)) == TRUE){
				BUTTONS[i] -> debouncing = FALSE;
			}
		}
		//event = {NAV_UP, PRESS_EVENT};
	}
}

void initalise_button_event_queue(xQueueHandle* queue){ //initalises a button event queue
	*queue = xQueueCreate(BUTTON_EVENT_QUEUE_LENGTH, sizeof(ButtonEvent));
	if (queue == NULL){
				/* FAILED to create queue */
	}
}

void enqueue_button_event(xQueueHandle* queue, ButtonEvent* event){ //enqueues a button event
	if (xQueueSendToBack(*queue, event, 0) != pdPASS){
		// data could not be put on the queue
	}
}

//ALL THE INTERRUPT-BASED BUTTON PROCESSING IS BROKE

//void button_ish(void){ //interrupt handler for button events
//	//THIS FUNCTION IS A DISASTER. DO NOT USE.
////	unsigned int up_state = 0;
////	unsigned int down_state = 0;
////	unsigned int left_state = 0;
////	unsigned int right_state = 0;
////	up_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_UP) == NAV_UP;
////	down_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_DOWN) == NAV_DOWN;
////	left_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_LEFT) == NAV_LEFT;
////	right_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_RIGHT) == NAV_LEFT;
////	//do something with the data
//	GPIOPinIntClear (GPIO_PORTG_BASE, NAV_BUTTONS);
//}
//
//void initalise_button_interrupts(void) { //intialises the buttons for interrupt mode
//	GPIOPortIntRegister (GPIO_PORTG_BASE, button_handler);
//	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);
//    GPIOPadConfigSet (GPIO_PORTG_BASE, NAV_BUTTONS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
//    GPIOIntTypeSet (GPIO_PORTG_BASE, NAV_BUTTONS, GPIO_RISING_EDGE);
//    GPIOPinIntEnable (GPIO_PORTG_BASE, NAV_BUTTONS);
//    IntEnable (INT_GPIOG);
//    IntMasterEnable ();
//}
//
//int read_buttons(void){ //reads the buttons
//	unsigned int up_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_UP) == NAV_UP;
//	unsigned int down_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_DOWN) == NAV_DOWN;
//	unsigned int left_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_LEFT) == NAV_LEFT;
//	unsigned int right_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_RIGHT) == NAV_LEFT;
//	return (up_state * 1 + down_state * 2 + left_state * 4 + right_state * 8);
//}



