/*
 * tetrominoe.c
 *	
 *  Created on: Jul 23, 2016
 *      Author: srj52
 *  a tetrominoe is the name for a block in tetris. this file contains basic functions for operating on these blocks as well as constants for the tetromineos present int the game
 */
#include "tetrominoe.h"

//line block definition


void reset_tetromineo(Tetrominoe* block){ //resets the tetrominoe
	block -> x = 0;
	block -> y = 0;
	block -> rotation_state = 0;
}

const int* get_tetromineo_grid(Tetrominoe* block){ //grabs the grid that defines the tetrominoe
	return block -> poses[block -> rotation_state] -> array;
}

void rotate_tetromineo(Tetrominoe* block){ //rotates the tetrominoe 90degrees
	block -> rotation_state = (block -> rotation_state + 1) % TETROMINOE_STATES;
}

void shift_tetrominoe(Tetrominoe* block, int x, int y){ //translates the current tetrominoe by some given values
	block -> x += x;
	block -> y += y;
}


//line block definition

const TetrominoeGrid i_pose1 = {0, 1, 0, 0,
								0, 1, 0, 0,
								0, 1, 0, 0,
								0, 1, 0, 0};

const TetrominoeGrid i_pose2 = {0, 0, 0, 0,
								1, 1, 1, 1,
								0, 0, 0, 0,
								0, 0, 0, 0};

Tetrominoe block0 = {0, 0, 0, {&i_pose2, &i_pose1, &i_pose2, &i_pose1}};

//square block defintion
const TetrominoeGrid s_pose1 = {0, 0, 0, 0,
								0, 1, 1, 0,
								0, 1, 1, 0,
								0, 0, 0, 0};

Tetrominoe block1 = {0, 0, 0, {&s_pose1, &s_pose1, &s_pose1, &s_pose1}};

//left L block definition

const TetrominoeGrid ll_pose1 = {	1, 1, 0, 0,
									0, 1, 0, 0,
									0, 1, 0, 0,
									0, 0, 0, 0};

const TetrominoeGrid ll_pose2 = {	0, 0, 1, 0,
									1, 1, 1, 0,
									0, 0, 0, 0,
									0, 0, 0, 0};

const TetrominoeGrid ll_pose3 = {	0, 1, 0, 0,
									0, 1, 0, 0,
									0, 1, 1, 0,
									0, 0, 0, 0};

const TetrominoeGrid ll_pose4 = {	0, 0, 0, 0,
									1, 1, 1, 0,
									1, 0, 0, 0,
									0, 0, 0, 0};

Tetrominoe block2 = {0, 0, 0, {&ll_pose4, &ll_pose1, &ll_pose2, &ll_pose3}};

//right L block definition

const TetrominoeGrid rl_pose1 = {	0, 1, 1, 0,
									0, 1, 0, 0,
									0, 1, 0, 0,
									0, 0, 0, 0};

const TetrominoeGrid rl_pose2 = {	0, 0, 0, 0,
									1, 1, 1, 0,
									0, 0, 1, 0,
									0, 0, 0, 0};

const TetrominoeGrid rl_pose3 = {	0, 1, 0, 0,
									0, 1, 0, 0,
									1, 1, 0, 0,
									0, 0, 0, 0};

const TetrominoeGrid rl_pose4 = {	1, 0, 0, 0,
									1, 1, 1, 0,
									0, 0, 0, 0,
									0, 0, 0, 0};

Tetrominoe block3 = {0, 0, 0, {&rl_pose2, &rl_pose3, &rl_pose4, &rl_pose1}};

//left Z block definition

const TetrominoeGrid lz_pose1 = {	1, 0, 0, 0,
									1, 1, 0, 0,
									0, 1, 0, 0,
									0, 0, 0, 0};

const TetrominoeGrid lz_pose2 = {	0, 1, 1, 0,
									1, 1, 0, 0,
									0, 0, 0, 0,
									0, 0, 0, 0};

Tetrominoe block4 = {0, 0, 0, {&lz_pose2, &lz_pose1, &lz_pose2, &lz_pose1}};

//right Z block definition

const TetrominoeGrid rz_pose1 = {	0, 1, 0, 0,
									1, 1, 0, 0,
									1, 0, 0, 0,
									0, 0, 0, 0};

const TetrominoeGrid rz_pose2 = {	1, 1, 0, 0,
									0, 1, 1, 0,
									0, 0, 0, 0,
									0, 0, 0, 0};

Tetrominoe block5 = {0, 0, 0, {&rz_pose2, &rz_pose1, &rz_pose2, &rz_pose1}};


//t block definition

const TetrominoeGrid t_pose1 = {0, 1, 0, 0,
								1, 1, 1, 0,
								0, 0, 0, 0,
								0, 0, 0, 0};

const TetrominoeGrid t_pose2 = {0, 1, 0, 0,
								0, 1, 1, 0,
								0, 1, 0, 0,
								0, 0, 0, 0};

const TetrominoeGrid t_pose3 = {0, 0, 0, 0,
								1, 1, 1, 0,
								0, 1, 0, 0,
								0, 0, 0, 0};

const TetrominoeGrid t_pose4 = {0, 1, 0, 0,
								1, 1, 0, 0,
								0, 1, 0, 0,
								0, 0, 0, 0};

Tetrominoe block6 = {0, 0, 0, {&t_pose3, &t_pose4, &t_pose1, &t_pose2}};

