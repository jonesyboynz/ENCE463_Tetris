/*
 * board.c
 *
 *  Created on: Jul 26, 2016
 *      Author: srj52
 */

#include "board.h"
#include "bool.h"

void clear_board(Board* board){ //clears the board
	int i;
	for (i = 0; i < board -> width * board -> height; i++){
		board -> grid[i] = EMPTY_CELL_VALUE;
	}
}

int get_board_value(Board* board, int x, int y){ //gets the value at specific coordinates on the board
	return board -> grid[y * board -> width + x];
}

void set_board_value(Board* board, int x, int y, int value){ //sets the value of a cell on the board at a specific location
	board -> grid[y * board -> width + x] = value;
}

int get_next_complete_row(Board* board){//returns the highest complete row
	int y;
	int x;
	for (y = 0; y < board -> height; y++){
		int is_complete = TRUE;
		for (x = 0; x < board -> width; x++){
			if (get_board_value(board, x, y) == EMPTY_CELL_VALUE){
				break;
			}
		}
		if (is_complete == TRUE){
			return y;
		}
	}
	return NO_COMPLETE_ROW;
}

int num_complete_rows(Board* board){ //returns the number of comleted rows on the board
	int y;
	int x;
	int count = 0;
	for (y = 0; y < board -> height; y++){
		int is_complete = TRUE;
		for (x = 0; x < board -> width; x++){
			if (get_board_value(board, x, y) == EMPTY_CELL_VALUE){
				is_complete = FALSE;
				break;
			}
		}
		if (is_complete == TRUE){
			count += 1;
		}
	}
	return count;
}

int is_off_board(Board* board, int x, int y){ //indicates whether or not a coordinate is on the board
	if (x >= board -> width || x < 0 || y >= board -> height || y < 0){
		return TRUE;
	}
	else{
		return FALSE;
	}

}

int is_occupied(Board* board, int x, int y){ //calculates whether or not a cell on the board is occupied
	if (board -> grid[y * board -> width + x] != EMPTY_CELL_VALUE){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

void clear_row(Board* board, int row){ //does a complete tetris row clear and drops down the bricks above
	int x;
	for (x = 0; x < board -> width; x++){
		set_board_value(board, x, row, EMPTY_CELL_VALUE);
		int target = highest_occupied_cell_in_column(board, x);
		if (target > row){
			//trickle down
		}
	}
}

void trickle_down_column(Board* board, int base_row, int column){ //trickles a column down. used to when rows are being destroyed.
	int y;
	for (y = base_row; y < board -> height - 2; y++){
		set_board_value(board, column, y, get_board_value(board, column, y + 1));
	}
	set_board_value(board, column, board -> height - 1, EMPTY_CELL_VALUE);
}

int highest_occupied_cell_in_column(Board* board, int column){ //returns the height of the highest occupied cell in a column
	int i = board -> height - 1;
	while (i >= 0){
		if (get_board_value(board, column, i) != EMPTY_CELL_VALUE){
			return i;
		}
		i -= 1;
	}
	return NO_CELL_OCCUPIED;
}


