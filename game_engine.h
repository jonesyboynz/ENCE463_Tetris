#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#define DEFAULT_GRID_HEIGHT 20
#define DEFAULT_GRID_WIDTH 10

#define BACKGROUND_OFFSET_X 0
#define BACKGROUND_OFFSET_Y 2
#define BACKGROUND_HOLDOFF_X 2
#define BACKGROUND_HOLDOFF_Y 2

#define LEFT -1
#define RIGHT 1

#define CELL_SIZE 6

#define INITIAL_SCORE 0
#define INITIAL_COMPLETED_ROWS 0
#define INITIAL_LEVEL 1
#define INITIAL_CURRENT_PEICE 0
#define INITIAL_NEXT_PEICE 0
#define INITIAL_PEICE_REPETITIONS 0

#include "tetrominoe.h"
#include "images.h"
#include "include/queue.h"
#include "board.h"
#include "buttons.h"

typedef struct game_s {
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
} Game;

extern Game base_game;

void xGameEngineTask(void* parameters);

void game_loop(Game* game);

void splash_screen_loop(Game* game);

void score_screen_loop(Game* game);

void clear_board(Board* board);

void initalise_game(Game* game);

void reset_game(Game* game);

void game_loop(Game* game);

void button_process_loop(Game* game);

void process_button_event(ButtonEvent* event, Game* game);

Tetrominoe* get_current_tetrominoe(Game* game);

void draw_current_tetrominoe(Game* game);

void erase_current_tetrominoe(Game* game);

void draw_current_tetrominoe_as(Game* game, const Image* image);

int calculate_tetris_grid_y_position(Board* board, int grid_position, int size);

int calculate_tetris_grid_x_position(Board* board, int grid_position, int size);

int current_tetrominoe_can_occupy(Game* game, int x_shift, int y_shift, int rotation);

int abs_modulo(int number, int divisor);

int can_drop_current_tetrominoe(Game* game);

int can_rotate_current_tetrominoe(Game* game);

int can_shift_current_tetrominoe(Game* game, int direction);

void place_current_tetrominoe(Game* game);

void debug_board(Game* game);

int spawn_new_tetrominoe(Game* game);

void get_next_tetrominoe(Game* game);

void clear_full_rows(Game* game);

void temp_fill_cells(Game* game, int column, int bottom_row, int top_row);

void redraw_empty_cells(Game* game, int column, int bottom_row, int top_row);

void try_rotate_current_tetrominoe(Game* game);

#endif
