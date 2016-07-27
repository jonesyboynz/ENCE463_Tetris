/*
 * timer.h
 *
 *  Created on: Jul 28, 2016
 *      Author: srj52
 */

#ifndef TIMER_H_
#define TIMER_H_

typedef struct timeout_s {
	portTickType starting_time;
	int timeout_ms;
} Timeout;

int has_timed_out(Timeout* timer);

void start_timeout(Timeout* timer, int timeout_ms);

#endif /* TIMER_H_ */
