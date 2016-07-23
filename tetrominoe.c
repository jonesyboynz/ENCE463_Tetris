/*
 * tetrominoe.c
 *
 *  Created on: Jul 23, 2016
 *      Author: srj52
 *  a tetrominoe is the name for a block in tetris. this file contains basic functions for operating on these blocks as well as constants for the tetromineos present int the game
 */
#include "tetrominoe.h"

//line block definition


void reset_tetromineo(Tetrominoe* block){
	block -> x = 0;
	block -> y = 0;
	block -> rotation_state = 0;
}

const int* get_tetromineo_grid(Tetrominoe* block){
	return block -> poses[block -> rotation_state] -> array;
}

void rotate_tetromineo(Tetrominoe* block){
	block -> rotation_state = (block -> rotation_state + 1) % TETROMINOE_STATES;
}


const TetrominoeGrid i_pose1 = {0, 1, 0, 0,
								0, 1, 0, 0,
								0, 1, 0, 0,
								0, 1, 0, 0};

const TetrominoeGrid i_pose2 = {0, 0, 0, 0,
								0, 0, 0, 0,
								1, 1, 1, 1,
								0, 0, 0, 0};

Tetrominoe block0 = {0, 0, 0, {&i_pose1, &i_pose2, &i_pose1, &i_pose2}};

//t block definition

const TetrominoeGrid t_pose1 = {0, 0, 0, 0,
								0, 1, 0, 0,
								1, 1, 1, 0,
								0, 0, 0, 0};

const TetrominoeGrid t_pose2 = {0, 0, 0, 0,
								0, 1, 0, 0,
								0, 1, 1, 0,
								0, 1, 0, 0};

const TetrominoeGrid t_pose3 = {0, 0, 0, 0,
								0, 0, 0, 0,
								1, 1, 1, 0,
								0, 1, 0, 0};

const TetrominoeGrid t_pose4 = {0, 0, 0, 0,
								0, 1, 0, 0,
								1, 1, 0, 0,
								0, 1, 0, 0};

Tetrominoe block6 = {0, 0, 0, {&t_pose1, &t_pose2, &t_pose3, &t_pose4}};


