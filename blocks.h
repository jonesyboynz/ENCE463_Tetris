/*
Blocks.h
Prototype header file for a module that never materialised. The Idea here was to abstact the conecpt of a "block" in tetris, however the tetrominoe file implemented this functionality
By Simon Jones
*/

#ifndef BLOCKS_H
#define BLOCKS_H

typedef struct point_s{
	int x;
	int y;
} Point;

typedef struct pose_s {
	Point points[4];
} Pose;

typedef struct block_s {
	Pose pose[4];


} Block;


#endif