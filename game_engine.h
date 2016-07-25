#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#define DEFAULT_GRID_HEIGHT 20
#define DEFAULT_GRID_WIDTH 10

#define BACKGROUND_OFFSET_X 16
#define BACKGROUND_OFFSET_Y 2
#define BACKGROUND_HOLDOFF_X 2
#define BACKGROUND_HOLDOFF_Y 2

#define LEFT -1
#define RIGHT 1

#define CELL_SIZE 6

#include "tetrominoe.h"
#include "images.h"
#include "include/queue.h"

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
	xQueueHandle* display_queue;
} Game;

extern Game game;

void clear_board(Board* board);

void initalise_game(Game* game);

void draw_background(void);

Tetrominoe* get_current_tetrominoe(Game* game);

void draw_current_tetrominoe(Game* game);

void erase_current_tetrominoe(Game* game);

void draw_current_tetrominoe_as(Game* game, const Image* image);

int calculate_tetris_grid_y_position(Board* board, int grid_position, int size);

int calculate_tetris_grid_x_position(Board* board, int grid_position, int size);

int current_tetrominoe_can_occupy(Game* game, int x_shift, int y_shift, int rotation);

int is_off_grid(Board* board, int x, int y);

int is_occupied(Board* board, int x, int y);

int abs_modulo(int number, int divisor);

int can_drop_current_tetrominoe(Game* game);

int can_rotate_current_tetrominoe(Game* game);

int can_shift_current_tetrominoe(Game* game, int direction);

void place_current_tetrominoe(Game* game);

void debug_board(Game* game);

int spawn_block(Game* game);

void get_next_tetrominie(Game* game);

#endif
