#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#define DEFAULT_GRID_HEIGHT 20
#define DEFAULT_GRID_WIDTH 10

#define BACKGROUND_OFFSET_X 0
#define BACKGROUND_OFFSET_Y 0
#define BACKGROUND_HOLDOFF_X 2
#define BACKGROUND_HOLDOFF_Y 2

#define CELL_SIZE 6

#include "tetrominoe.h"
#include "images.h"

typedef struct board_s {
	int* grid;
	int width;
	int height;
} Board;

typedef struct game_s {
	Board* board;
	Tetrominoe** tetrominoes;
	int num_tetrominoes;
	int current_peice_index;
} Game;

extern Game game;

void clear_board(Board* board);

void initalise_game(Game* game);

void draw_background(void);

void draw_current_tetrominoe(Game* game);

void erase_current_tetrominoe(Game* game);

void draw_current_tetrominoe_as(Game* game, const Image* image);

int calculate_tetris_grid_y_position(int grid_position, int size);

int calculate_tetris_grid_x_position(int grid_position, int size);

#endif
