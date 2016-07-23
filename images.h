/*
A file that contains various peices of image artwork
by simon jones
22/07/2016
*/

#ifndef IMAGES_H
#define IMAGES_H


const unsigned char BASE_CUBE[8] = {0x77, 0x77,
									0x7f, 0x7f,
									0x7f, 0x7f,
									0x77, 0x77};

const unsigned char BASE_SMALL_CUBE[4] = {	0xff,
											0xff};


Image CUBE = {BASE_CUBE, 4, 4};

Image SMALL_CUBE = {BASE_SMALL_CUBE, 2, 2};

typedef struct image_s {
	const unsigned char* image;
	int width;
	int height;
} Image;

void draw_image(Image* image, int x, int y);

#endif