/*
 * board.h
 * abstacts the idea of a simple grid on which to layout the game data
 *  Created on: Jul 26, 2016
 *      Author: srj52
 */

#ifndef BOARD_H_
#define BOARD_H_

typedef struct board_s {
	int* grid;
	int width;
	int height;
} Board;

#define NO_COMPLETE_ROW -1

#define NO_CELL_OCCUPIED -1

#define FULL_CELL_VALUE 1
#define EMPTY_CELL_VALUE 0
#define CELL_OFF_BOARD_VALUE 0

void clear_board(Board* board);

int get_board_value(Board* board, int x, int y);

void set_board_value(Board* board, int x, int y, int value);

int get_next_complete_row(Board* board);

int num_complete_rows(Board* board);

int is_off_board(Board* board, int x, int y);

int is_occupied(Board* board, int x, int y);

void clear_row(Board* board, int row);

void trickle_down_column(Board* board, int base_row, int column);

int highest_occupied_cell_in_column(Board* board, int column);

#endif /* BOARD_H_ */
