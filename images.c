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

const Image* NUMBERS[10] = {&NUMBER0, &NUMBER1, &NUMBER2, &NUMBER3, &NUMBER4, &NUMBER5, &NUMBER6, &NUMBER7, &NUMBER8, &NUMBER9};

const Image RUNNING_ANIMATION0 = {RUNNING_ANIMATION0_DATA, 2, 2};
const Image RUNNING_ANIMATION1 = {RUNNING_ANIMATION1_DATA, 2, 2};
const Image RUNNING_ANIMATION2 = {RUNNING_ANIMATION2_DATA, 2, 2};
const Image RUNNING_ANIMATION3 = {RUNNING_ANIMATION3_DATA, 2, 2};

const Image* RUNNING_ANIMATION[4] = {&RUNNING_ANIMATION0, &RUNNING_ANIMATION1, &RUNNING_ANIMATION2, &RUNNING_ANIMATION3};

const Image LETTER_A = {LETTER_A_DATA, 6, 3};
const Image LETTER_B = {LETTER_B_DATA, 6, 3};
const Image LETTER_C = {LETTER_C_DATA, 6, 3};
const Image LETTER_D = {LETTER_D_DATA, 6, 3};
const Image LETTER_E = {LETTER_E_DATA, 6, 3};
const Image LETTER_F = {LETTER_F_DATA, 6, 3};
const Image LETTER_G = {LETTER_G_DATA, 6, 3};
const Image LETTER_H = {LETTER_H_DATA, 6, 3};
const Image LETTER_I = {LETTER_I_DATA, 6, 3};
const Image LETTER_J = {LETTER_J_DATA, 6, 3};
const Image LETTER_K = {LETTER_K_DATA, 6, 3};
const Image LETTER_L = {LETTER_L_DATA, 6, 3};
const Image LETTER_M = {LETTER_M_DATA, 6, 5};
const Image LETTER_N = {LETTER_N_DATA, 6, 3};
const Image LETTER_O = {LETTER_O_DATA, 6, 3};
const Image LETTER_P = {LETTER_P_DATA, 6, 3};
const Image LETTER_Q = {LETTER_Q_DATA, 6, 4};
const Image LETTER_R = {LETTER_R_DATA, 6, 3};
const Image LETTER_S = {LETTER_S_DATA, 6, 3};
const Image LETTER_T = {LETTER_T_DATA, 6, 3};
const Image LETTER_U = {LETTER_U_DATA, 6, 3};
const Image LETTER_V = {LETTER_V_DATA, 6, 3};
const Image LETTER_W = {LETTER_W_DATA, 6, 5};
const Image LETTER_X = {LETTER_X_DATA, 6, 3};
const Image LETTER_Y = {LETTER_Y_DATA, 6, 3};
const Image LETTER_Z = {LETTER_Z_DATA, 6, 3};
const Image LETTER__ = {LETTER___DATA, 6, 3};
const Image LETTER_UNDEFINED = {LETTER_UNDEFINED_DATA, 6, 3};

const Image* FONT[30] = {	&LETTER_A, &LETTER_B, &LETTER_C, &LETTER_D, &LETTER_E, &LETTER_F, &LETTER_G, &LETTER_H,
							&LETTER_I, &LETTER_J, &LETTER_K, &LETTER_L, &LETTER_M, &LETTER_N, &LETTER_O, &LETTER_P,
							&LETTER_Q, &LETTER_R, &LETTER_S, &LETTER_T, &LETTER_U, &LETTER_V, &LETTER_W, &LETTER_X,
							&LETTER_Y, &LETTER_Z, &LETTER__, &LETTER_UNDEFINED, &LETTER_UNDEFINED, &LETTER_UNDEFINED};

/*IMAGES TO ADD:
 * "game over"
 * start splash screen
 *
 */
