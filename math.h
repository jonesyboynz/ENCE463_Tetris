/*
 * math.h
 * Shares the mathematical functions with other files
 *  Created on: Jul 26, 2016
 *      Author: srj52
 */

#ifndef MATH_H_
#define MATH_H_

unsigned int urand(void);

int rand_range(int min, int max);

void initalise_random_number_generator(unsigned long seed);

int abs_modulo(int number, int divisor);

int symbols_in_number(int number);

#endif /* MATH_H_ */
