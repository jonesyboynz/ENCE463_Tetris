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

typedef struct game_stats_debug_timer_s {
	Timer input_latency_timer;
	Timer refresh_rate_timer;
	int average_input_latency;
	int max_input_latency;
	int refresh_rate;
	int refresh_rate_error; //max
	long average_refresh_rate_error;
	long refresh_rate_samples;
} GameDebugTimers;

extern GameDebugTimers DEBUG_TIMERS;

int has_timed_out(Timeout* timer);
//returns true or false depending on whether a timeout has occured

void start_timeout(Timeout* timer, int timeout_ms);
//starts a timeout

portTickType tick_difference(portTickType start_time, portTickType end_time);
//calculates the difference between two freeRTOS systick values. Overflow safe.

void timer_start(Timer* timer);
//starts a timer

void timer_update(Timer* timer);
//updates a timer (should be called pereodically while a timer is operating)

void timer_stop(Timer* timer);
//stops a timer

int elapsed_time_ms(Timer* timer);
//gets a timer's elapsed time in ms

#endif /* TIMER_H_ */
