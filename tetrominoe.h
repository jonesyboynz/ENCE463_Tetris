/*
 * tetrominoe.h
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 */

#ifndef TETROMINOE_H_
#define TETROMINOE_H_

#define TETROMINOE_STATES 4
#define TETROMINOE_GRID_WIDTH 4
#define TETROMINOE_GRID_HEIGHT 4
#define TETROMINOE_GRID_LENGTH (TETROMINOE_GRID_WIDTH * TETROMINOE_GRID_HEIGHT)


typedef struct tetrominoe_grid_s {
	const int array[TETROMINOE_GRID_LENGTH];
} TetrominoeGrid;

typedef struct tetrominoe_s {
	int rotation_state;
	int x;
	int y;
	const TetrominoeGrid* poses[TETROMINOE_STATES];
} Tetrominoe;

extern Tetrominoe block0; //line
extern Tetrominoe block1; //square
extern Tetrominoe block2; //left L
extern Tetrominoe block3; //right L
extern Tetrominoe block4; //left Z
extern Tetrominoe block5; //right Z
extern Tetrominoe block6; //t

void reset_tetromineo(Tetrominoe* block);

const int* get_tetromineo_grid(Tetrominoe* block);

void rotate_tetromineo(Tetrominoe* block);

#endif /* TETROMINOE_H_ */
