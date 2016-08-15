/*
 * tests.h
 * Prototypes the test functions so the main file can access them
 *  Created on: Aug 10, 2016
 *      Author: srj52
 */

#ifndef TESTS_H_
#define TESTS_H_

void tetronimoe_drop_test(void* parameters);
//tests if the tetrominoe drop is working

void tetronimoe_drop_test2(void* parameters);
//tests if the tetrominoe drop is working and switches peices

void vDisplayRunning(void* parameters);
//plays a small animation in the bottom right cornor of the screen to show that the system is running

void vButtonTest(void* parameters);
//tests the button queue by pereodically writing button events


#endif /* TESTS_H_ */
