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

extern const Image NUMBER0;
extern const Image NUMBER1;
extern const Image NUMBER2;
extern const Image NUMBER3;
extern const Image NUMBER4;
extern const Image NUMBER5;
extern const Image NUMBER6;
extern const Image NUMBER7;
extern const Image NUMBER8;
extern const Image NUMBER9;

extern const Image NUMBERS[10];
extern const Image RUNNING_ANIMATION[4];

extern const Image SCORE_IMAGE;

extern const Image NEXT_IMAGE;

extern const Image LEVEL_IMAGE;

#endif
