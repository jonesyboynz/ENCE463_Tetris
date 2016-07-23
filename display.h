/*
 * display.h
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "images.h"

void write_string(char* string, int x, int y, int brightness);

void write_image(const Image* image, int x, int y);

void initalise_display(void);

void clear_display(void);

#endif /* DISPLAY_H_ */
