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
	portTickType current_time = xTaskGetTickCount();
	portTickType difference = tick_difference(timer -> starting_time, current_time);
	if ((int) (difference / portTICK_RATE_MS) > timer -> timeout_ms){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

portTickType tick_difference(portTickType start_time, portTickType end_time){//gets the difference between two portTickTypes
	portTickType difference;
	if (end_time <= start_time){
		difference = (MAX_PORT_TICK_VALUE - start_time) + end_time;
	}
	else{
		difference = end_time - start_time;
	}
	return difference;
}

void start_timeout(Timeout* timer, int timeout_ms){ //begins a timeout
	timer -> starting_time = xTaskGetTickCount();
	timer -> timeout_ms = timeout_ms;
}

void timer_start(Timer* timer){ //starts the timer
	timer -> elapsed_ticks = 0;
	timer -> reference = xTaskGetTickCount();
	timer -> running = TRUE;
}

void timer_update(Timer* timer){ //updates the timer's information. should be called periodically while the timer is running
	if (timer -> running == TRUE){
		portTickType current_time = xTaskGetTickCount();
		portTickType difference = tick_difference(timer -> reference, current_time);
		timer -> reference = current_time;
		timer -> elapsed_ticks += difference;
	}
}

void timer_stop(Timer* timer){
	timer_update(timer);
	timer -> running = FALSE;
}

int elapsed_time_ms(Timer* timer){
	timer_update(timer);
	return (int) (portTICK_RATE_MS * timer -> elapsed_ticks);
}


