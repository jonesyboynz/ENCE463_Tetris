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