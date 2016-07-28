/*
 * timer.h
 *
 *  Created on: Jul 28, 2016
 *      Author: srj52
 */

#ifndef TIMER_H_
#define TIMER_H_

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

typedef struct timeout_s {
	portTickType starting_time;
	int timeout_ms;
} Timeout;

typedef struct timer_s {
	portTickType reference;
	unsigned long elapsed_ticks;
	int running;
} Timer;

int has_timed_out(Timeout* timer);

void start_timeout(Timeout* timer, int timeout_ms);

portTickType tick_difference(portTickType start_time, portTickType end_time);

void timer_start(Timer* timer);

void timer_update(Timer* timer);

void timer_stop(Timer* timer);

int elapsed_time_ms(Timer* timer);

#endif /* TIMER_H_ */
