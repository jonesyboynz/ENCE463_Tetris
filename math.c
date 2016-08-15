/*
 * math.c
 * Implements basic mathematical functions including randomnumber generation
 *  Created on: Jul 26, 2016
 *      Author: srj52
 */

//FREEROTS incldues
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "eeprom.c"

#include "math.h"

unsigned long seed;

unsigned int urand(void){ //compute an unsigned random number

	seed = seed ^ ((unsigned int ) xTaskGetTickCount());
	seed = (seed * (seed % 29)) % 1777 + 3;
	return (unsigned int) seed;
}

int rand_range(int min, int max){ //generates a random integer withing a given range

	unsigned int num = urand();

	unsigned int difference = (unsigned int) ((max + 1) - min);
	unsigned int ranged = num % difference;
	return (min + (int) ranged);
}

void initalise_random_number_generator(unsigned long new_seed){ //intalises the random number generator
	//taskENTER_CRITICAL();
//	EEPROMInit();
//	unsigned long test = 0;
//	EEPROMRead(&test, 0, 4);
//	if (test == 0){
		seed = new_seed;
//		EEPROMProgram(&new_seed, 4, 4);
//		EEPROMProgram(&new_seed, 0, test + 1);
//	}
//	else{
//		EEPROMRead(&new_seed, 4, 4);
//	}
	//taskEXIT_CRITICAL();
}

int abs_modulo(int number, int divisor){ //executes a modulus functions which always returns a positive value
	int result = number % divisor;
	while (result < 0){
		result += divisor;
	}
	return result;
}

int symbols_in_number(int number){ //returns the number of sumbols needed to display a number
	int count = 1;
	while (number > 0){
		number /= 10;
		count += 1;
	}
	return count;
}

