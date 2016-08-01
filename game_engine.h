#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#define DEFAULT_GRID_HEIGHT 20
#define DEFAULT_GRID_WIDTH 10

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

#define NEXT_TETROMINOE_X_GRID_POSITION (DEFAULT_GRID_WIDTH + 2)
#define NEXT_TETROMINOE_Y_GRID_POSITION 5

#define LEFT -1
#define RIGHT 1

#define CELL_SIZE 6

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
	int* tick_rates;
	int current_tick_rate;
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

void splash_screen_loop(Game* game);

void score_screen_loop(Game* game);

void debug_screen_loop(Game* game);

void generic_wait_loop(Game* game);

Tetrominoe* get_current_tetrominoe(Game* game);

void draw_current_tetrominoe(Game* game);

void erase_current_tetrominoe(Game* game);

void draw_current_tetrominoe_as(Game* game, const Image* image);

void draw_tetrominoe(Game* game, Tetrominoe* tetrominoe, const Image* cell_image, int x, int y);

int calculate_tetris_grid_y_position(Board* board, int grid_position, int size);

int calculate_tetris_grid_x_position(Board* board, int grid_position, int size);

int current_tetrominoe_can_occupy(Game* game, int x_shift, int y_shift, int rotation);

int abs_modulo(int number, int divisor);

int can_drop_current_tetrominoe(Game* game);

int can_rotate_current_tetrominoe(Game* game);

int can_shift_current_tetrominoe(Game* game, int direction);

void place_current_tetrominoe(Game* game);

void debug_board(Board* board);

int spawn_new_tetrominoe(Game* game);

void get_next_tetrominoe(Game* game);

void draw_next_tetrominoe_on_side(Game* game);

void erase_next_tetrominoe_on_side(Game* game);

void clear_full_rows(Game* game);

void draw_differences(Game* game, Board* differences);

void temp_fill_cells(Game* game, int column, int bottom_row, int top_row);

void redraw_empty_cells(Game* game, int column, int bottom_row, int top_row);

void try_rotate_current_tetrominoe(Game* game);

void try_shift_current_tetrominoe(Game* game, int direction);

void full_drop_current_tetrominoe(Game* game);

void draw_next_tetrominoe_on_side(Game* game);

void erase_next_tetrominoe_on_side(Game* game);

void update_score_display(Game* game);

void update_level_display(Game* game);

void update_score_and_level(Game* game, int rows_broken);

#endif
