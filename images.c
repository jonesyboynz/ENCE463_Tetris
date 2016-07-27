/*
 * images.c
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */

#include "images.h"
#include "tetris_background.h" //includes the (extremely large) tetris background image
#include "text_images.h"

const unsigned char CUBE_DATA[8] = {0x77, 0x77,
									0x7f, 0x7f,
									0x7f, 0x7f,
									0x77, 0x77};

const unsigned char SMALL_CUBE_DATA[4] = {	0xff,
											0xff};

const unsigned char FULL_CELL_DATA[18] = {	0x77, 0x77, 0x77,
											0x7f, 0xff, 0xf7,
											0x7f, 0xff, 0xf7,
											0x7f, 0xff, 0xf7,
											0x7f, 0xff, 0xf7,
											0x77, 0x77, 0x77};

const unsigned char EMPTY_CELL_DATA[18] = {	0x00, 0x00, 0x00,
											0x00, 0x00, 0x00,
											0x00, 0x00, 0x00,
											0x00, 0x00, 0x00,
											0x00, 0x00, 0x00,
											0x00, 0x00, 0x00};


const Image CUBE = {CUBE_DATA, 4, 4};

const Image SMALL_CUBE = {SMALL_CUBE_DATA, 2, 2};

const Image FULL_CELL = {FULL_CELL_DATA, 6, 6};

const Image EMPTY_CELL = {EMPTY_CELL_DATA, 6, 6};

const Image TETRIS_BACKGROUND = {TETRIS_BACKGROUND_DATA, 124, 64};

const Image NUMBER0 = {NUMBER0_DATA, 6, 3};
const Image NUMBER1 = {NUMBER1_DATA, 6, 3};
const Image NUMBER2 = {NUMBER2_DATA, 6, 3};
const Image NUMBER3 = {NUMBER3_DATA, 6, 3};
const Image NUMBER4 = {NUMBER4_DATA, 6, 3};
const Image NUMBER5 = {NUMBER5_DATA, 6, 3};
const Image NUMBER6 = {NUMBER6_DATA, 6, 3};
const Image NUMBER7 = {NUMBER7_DATA, 6, 3};
const Image NUMBER8 = {NUMBER8_DATA, 6, 3};
const Image NUMBER9 = {NUMBER9_DATA, 6, 3};

const Image NUMBERS[10] = {NUMBER0, NUMBER1, NUMBER2, NUMBER3, NUMBER4, NUMBER5, NUMBER6, NUMBER7, NUMBER8, NUMBER9};

const Image RUNNING_ANIMATION0 = {RUNNING_ANIMATION0_DATA, 2, 2};
const Image RUNNING_ANIMATION1 = {RUNNING_ANIMATION1_DATA, 2, 2};
const Image RUNNING_ANIMATION2 = {RUNNING_ANIMATION2_DATA, 2, 2};
const Image RUNNING_ANIMATION3 = {RUNNING_ANIMATION3_DATA, 2, 2};

const Image RUNNING_ANIMATION[4] = {RUNNING_ANIMATION0, RUNNING_ANIMATION1, RUNNING_ANIMATION2, RUNNING_ANIMATION3}

const Image SCORE_IMAGE = {SCORE_IMAGE_DATA, 6, 19};

const Image NEXT_IMAGE = {NEXT_IMAGE_DATA, 6, 15};

const Image LEVEL_IMAGE = {LEVEL_IMAGE_DATA, 6, 19};

/*IMAGES TO ADD:
 * "game over"
 * start splash screen
 *
 */
