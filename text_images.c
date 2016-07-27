/*
 * text_images.c
 *
 *  Created on: Jul 26, 2016
 *      Author: srj52
 */

//numbers from 0 to 9

const unsigned char NUMBER0_DATA[9] = {	0x0f, 0xff, 0xff,
										0x0f, 0x00, 0x0f,
										0x0f, 0xff, 0xff};


const unsigned char NUMBER1_DATA[9] = {	0x0f, 0xff, 0xff,
										0x00, 0x00, 0x00,
										0x00, 0x00, 0x00;

const unsigned char NUMBER2_DATA[9] = {	0x0f, 0xff, 0x0f,
										0x0f, 0x0f, 0x0f,
										0x0f, 0x0f, 0xff};

const unsigned char NUMBER3_DATA[9] = {	0x0f, 0xff, 0xff,
										0x0f, 0x0f, 0x0f,
										0x0f, 0x0f, 0x0f};

const unsigned char NUMBER4_DATA[9] = {	0x0f, 0xff, 0xff,
										0x00, 0x0f, 0x00,
										0x00, 0x0f, 0xff};

const unsigned char NUMBER5_DATA[9] = {	0x0f, 0x0f, 0xff,
										0x0f, 0x0f, 0x0f,
										0x0f, 0xff, 0x0f};

const unsigned char NUMBER6_DATA[9] = {	0x0f, 0xff, 0xff,
										0x0f, 0x0f, 0x0f,
										0x0f, 0xff, 0x0f};

const unsigned char NUMBER7_DATA[9] = {	0x0f, 0xff, 0xff,
										0x00, 0x00, 0x0f,
										0x00, 0x00, 0xff};

const unsigned char NUMBER8_DATA[9] = {	0x0f, 0xff, 0xff,
										0x0f, 0x0f, 0x0f,
										0x0f, 0xff, 0xff};

const unsigned char NUMBER9_DATA[9] = {	0x0f, 0x0f, 0xff,
										0x0f, 0x0f, 0x0f,
										0x0f, 0xff, 0xff};

//running animation

const unsigned char RUNNING_ANIMATION0_DATA[2] = {	0x7f,
													0x30};
const unsigned char RUNNING_ANIMATION1_DATA[2] = {	0x37,
													0x0f};
const unsigned char RUNNING_ANIMATION2_DATA[2] = {	0x03,
													0xf7};
const unsigned char RUNNING_ANIMATION3_DATA[2] = {	0xf0,
													0x73};

//"score"

const unsigned char SCORE_IMAGE_DATA[57] = {0xf0, 0xff, 0xf0,
											0xf0, 0xf0, 0xf0,
											0xff, 0xf0, 0xf0,

											0x00, 0x00, 0x00,

											0x0f, 0xff, 0x00,
											0xf0, 0x00, 0xf0,
											0xf0, 0x00, 0xf0,

											0x00, 0x00, 0x00,

											0xff, 0xff, 0xf0,
											0xf0, 0x00, 0xf0,
											0xff, 0xff, 0xf0,

											0x00, 0x00, 0x00,

											0xff, 0xff, 0xf0,
											0x00, 0xf0, 0xf0,
											0xff, 0x0f, 0x00,

											0x00, 0x00, 0x00,

											0xff, 0xff, 0xf0,
											0xf0, 0xf0, 0xf0,
											0xf0, 0xf0, 0xf0};

const unsigned char NEXT_IMAGE_DATA[45] = {0xff, 0xff, 0xf0,
										0x00, 0x00, 0xf0,
										0xff, 0xff, 0xf0,

										0x00, 0x00, 0x00,

										0xff, 0xff, 0xf0,
										0xf0, 0xf0, 0xf0,
										0xf0, 0xf0, 0xf0,

										0x00, 0x00, 0x00,

										0xff, 0x0f, 0xf0,
										0x00, 0xf0, 0x00,
										0xff, 0x0f, 0xf0,

										0x00, 0x00, 0x00,

										0x00, 0x00, 0xf0,
										0xff, 0xff, 0xf0,
										0x00, 0x00, 0xf0};

const unsigned char LEVEL_IMAGE_DATA[57] = {0xff, 0xff, 0xf0,
											0xf0, 0x00, 0x00,
											0xf0, 0x00, 0x00,

											0x00, 0x00, 0x00,

											0xff, 0xff, 0xf0,
											0xf0, 0xf0, 0xf0,
											0xf0, 0xf0, 0xf0,

											0x00, 0x00, 0x00,

											0x0f, 0xff, 0xf0,
											0xf0, 0x00, 0x00,
											0x0f, 0xff, 0xf0,

											0x00, 0x00, 0x00,

											0xff, 0xff, 0xf0,
											0xf0, 0xf0, 0xf0,
											0xf0, 0xf0, 0xf0,

											0x00, 0x00, 0x00,

											0xff, 0xff, 0xf0,
											0xf0, 0x00, 0x00,
											0xf0, 0x00, 0x00};


