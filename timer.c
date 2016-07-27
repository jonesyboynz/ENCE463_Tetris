/*
 * timer.c
 *
 *  Created on: Jul 28, 2016
 *      Author: srj52
 */

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

#include "timer.h"
#include "bool.h"

portTickType MAX_PORT_TICK_VALUE = 0xffffffff;

int has_timed_out(Timeout* timer){ //checks if a timeout has occured
	portTickType difference;
	portTickType current_time = xTaskGetTickCount();
	if (current_time <= timer -> starting_time){
		difference = (MAX_PORT_TICK_VALUE - timer -> starting_time) + current_time;
	}
	else{
		difference = current_time - timer -> starting_time;
	}
	if ((int) (difference / portTICK_RATE_MS) > timer -> timeout_ms){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void start_timeout(Timeout* timer, int timeout_ms){ //begins a timeout
	timer -> starting_time = xTaskGetTickCount();
	timer -> timeout_ms = timeout_ms;
}


