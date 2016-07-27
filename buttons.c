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

void button_handler(void){ //interrupt handler for button events
//	unsigned int up_state = 0;
//	unsigned int down_state = 0;
//	unsigned int left_state = 0;
//	unsigned int right_state = 0;
//
//	up_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_UP) == NAV_UP;
//	down_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_DOWN) == NAV_DOWN;
//	left_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_LEFT) == NAV_LEFT;
//	right_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_RIGHT) == NAV_LEFT;
//
//	//do something with the data
//
	GPIOPinIntClear (GPIO_PORTG_BASE, NAV_BUTTONS);
}

void initalise_button_interrupts(void) { //intialises the buttons for interrupt mode

	GPIOPortIntRegister (GPIO_PORTG_BASE, button_handler);

	SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);

    GPIOPadConfigSet (GPIO_PORTG_BASE, NAV_BUTTONS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOIntTypeSet (GPIO_PORTG_BASE, NAV_BUTTONS, GPIO_RISING_EDGE);

    GPIOPinIntEnable (GPIO_PORTG_BASE, NAV_BUTTONS);

    IntEnable (INT_GPIOG);

    IntMasterEnable ();
}

void initalise_buttons(void){ //initalises the buttons for standard polling mode
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);
    GPIOPadConfigSet (GPIO_PORTG_BASE, NAV_BUTTONS, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

int read_buttons(void){ //reads the buttons
	unsigned int up_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_UP) == NAV_UP;
	unsigned int down_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_DOWN) == NAV_DOWN;
	unsigned int left_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_LEFT) == NAV_LEFT;
	unsigned int right_state = GPIOPinRead(GPIO_PORTG_BASE, NAV_RIGHT) == NAV_LEFT;
	return (up_state * 1 + down_state * 2 + left_state * 4 + right_state * 8);
}

unsigned int read_button(int button_id){ //reads a button
	return  GPIOPinRead(GPIO_PORTG_BASE, button_id);
}

void xButtonReadTask(void* parameters){ //task to pereodically poll the buttons
	xQueueHandle button_queue = (xQueueHandle) parameters;
	unsigned int up_state = read_button(NAV_UP);
	unsigned int down_state = read_button(NAV_DOWN);
	unsigned int left_state = read_button(NAV_LEFT);
	unsigned int right_state = read_button(NAV_RIGHT);
	ButtonEvent event;
	while (TRUE){
		

	}
}

void initalise_button_event_queue(xQueueHandle* queue){ //initalises a button event queue
	*queue = xQueueCreate(BUTTON_EVENT_QUEUE_LENGTH, sizeof(ButtonEvent));
	if (queue == NULL){
				/* FAILED to create queue */
	}
}



