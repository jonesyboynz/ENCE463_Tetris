/*
A file that contains various peices of image artwork
by simon jones
22/07/2016
*/

#ifndef IMAGES_H
#define IMAGES_H

typedef struct image_s {
	const unsigned char* image;
	int width;
	int height;
} Image;

extern const Image SMALL_CUBE;
extern const Image CUBE;
extern const Image FULL_CELL;
extern const Image EMPTY_CELL;
extern const Image TETRIS_BACKGROUND;

#endif
