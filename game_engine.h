/*
Shares a few of the game engine functions as some of them are used in the debug modules (Ideally none of them should be shared)
By Simon Jones
*/

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#define DEFAULT_GRID_HEIGHT 20
#define DEFAULT_GRID_WIDTH 10

#define CELL_SIZE 6

#define BACKGROUND_OFFSET_X 1
#define BACKGROUND_OFFSET_Y 2
#define BACKGROUND_HOLDOFF_X 2
#define BACKGROUND_HOLDOFF_Y 2

#define SCORE_TEXT_X 64 - 3
#define SCORE_TEXT_Y 72

#define LEVEL_TEXT_X 32 - 3
#define LEVEL_TEXT_Y 72

#define NEXT_TEXT_X 104 - 3
#define NEXT_TEXT_Y 74

#define SCORE_POSITION_X (SCORE_TEXT_X - 9)
#define SCORE_POSITION_Y (SCORE_TEXT_Y)

#define LEVEL_POSITION_X (LEVEL_TEXT_X - 9)
#define LEVEL_POSITION_Y (LEVEL_TEXT_Y)

#define NEXT_TETROMINOE_X_GRID_POSITION (DEFAULT_GRID_WIDTH + 1)
#define NEXT_TETROMINOE_Y_GRID_POSITION 5

#define NEXT_TETROMINOE_BOARDER_X (((DEFAULT_GRID_HEIGHT - NEXT_TETROMINOE_Y_GRID_POSITION - 3) * CELL_SIZE) + BACKGROUND_OFFSET_X + BACKGROUND_HOLDOFF_X)
#define NEXT_TETROMINOE_BOARDER_Y ((NEXT_TETROMINOE_X_GRID_POSITION * CELL_SIZE) + BACKGROUND_OFFSET_Y + BACKGROUND_HOLDOFF_Y - 3)

#define LEFT -1
#define RIGHT 1

#define INITIAL_SCORE 0
#define INITIAL_COMPLETED_ROWS 0
#define INITIAL_LEVEL 1
#define INITIAL_CURRENT_PEICE 0
#define INITIAL_NEXT_PEICE 0
#define INITIAL_PEICE_REPETITIONS 0

#define ROWS_TILL_LEVEL_ADVANCE 2

#include "tetrominoe.h"
#include "images.h"
#include "include/queue.h"
#include "board.h"
#include "buttons.h"

typedef struct game_s { //Game structure. Contains all of the variables needed by the game engine. 
	Board* board;
	Tetrominoe** tetrominoes;
	int num_tetrominoes;
	int current_peice_index;
	int next_peice_index;
	int peice_repetitions;
	xQueueHandle display_queue;
	xQueueHandle button_queue;
	int score;
	int completed_rows;
	int level;
	int* tick_rates;
	int current_tick_rate;
	GameDebugTimers* debug_timers;
} Game;

extern Game base_game;

void xGameEngineTask(void* parameters);
//game engine task. runs the game engine

void reset_game(Game* game);
//resets a game structure

Tetrominoe* get_current_tetrominoe(Game* game);
//gets the currenly active tetrominoe from the game

void draw_current_tetrominoe(Game* game);
//draws the currently active tetrominoe form a game

void erase_current_tetrominoe(Game* game);
//erases the currently active tetrominoe from a game

int spawn_new_tetrominoe(Game* game);
//attempts to place the next tetrominoe on the game grid. returns a TRUE/FALSE value to indicate success and failure

void get_next_tetrominoe(Game* game);
//shifts the next tetrominoe into the current tetrominoe and randomly selects a new next tetrominoe

void initalise_game(Game* game);
//initalizes a game structure

void place_current_tetrominoe(Game* game);
//places the currently active tetrominoe in the game grid array

int can_drop_current_tetrominoe(Game* game);
//indicates whether or not the currently active tetrominoe can drop down.

#endif
