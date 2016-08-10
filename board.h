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

#define CHANGE_NONE 0
#define CHANGE_FILLED 1
#define CHANGE_CLEARED -1

void clear_board(Board* board);
//clears a board (sets all cells to zero)

int get_board_value(Board* board, int x, int y);
//accesses the board at some x,y coordiates (board is actually a 1d array)

void set_board_value(Board* board, int x, int y, int value);
//sets the value of a board cell at some x,y coordinates

int get_next_complete_row(Board* board);
//returns the row index of the next row that is complete (all 1s)

int num_complete_rows(Board* board);
//returns the number of completed rows on the board

int is_off_board(Board* board, int x, int y);
//calculates whether an x,y position is on the board

int is_occupied(Board* board, int x, int y);
//calculates whether an x,y position is occupied

void clear_row(Board* board, int row);
//clears a row (sets it all to zero)

void trickle_down_column(Board* board, int base_row, int column);
//lowers all cells in a column from a given row index and upwards

int highest_occupied_cell_in_column(Board* board, int column);
//retuens the row index of the highest occupied cell in  column

void copy_board(Board* source, Board* dest);
//copies a board from source to dest

void board_difference(Board* board_a, Board* board_b, Board* output);
//copies the differences between board A and board B into output

#endif /* BOARD_H_ */
