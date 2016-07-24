/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"

/* Demo includes. */
#include "demo_code\basic_io.h"

/* Tetris engine includes*/
#include "game_engine.h"
#include "tetrominoe.h"
#include "display.h"
#include "bool.h"

//Setup for the default game grid. This grid will be used most of the time
int grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
Board game_board = {grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};
Tetrominoe* tetrominoes[7] = {&block0, &block1, &block2, &block3, &block4, &block5, &block6};
Game game = {&game_board, tetrominoes, 7, 0};

void clear_board(Board* board){ //clears all the 
	int i;
	for (i = 0; i < board -> width * board -> height; i++){
		board -> grid[i] = 0;
	}
}

void initalise_game(Game* game){ //intalises the game. Mainly clears data
	clear_board(game -> board);
	int i;
	for (i = 0; i < game -> num_tetrominoes; i++){
		reset_tetromineo(game -> tetrominoes[i]);
	}
	game -> current_peice_index = 0;
	draw_background();
}

void draw_background(void){ //draws the background at pre-defined offset
	write_image(&TETRIS_BACKGROUND, BACKGROUND_OFFSET_Y, BACKGROUND_OFFSET_X);
}

Tetrominoe* get_current_tetrominoe(Game* game){ //grabs the currently active tetrominoe
	return game -> tetrominoes[game -> current_peice_index];
}

void draw_current_tetrominoe(Game* game){ //draws the current tetronimoe
	draw_current_tetrominoe_as(game, &FULL_CELL);
}

void erase_current_tetrominoe(Game* game){ //removes the current tetronimoe
	draw_current_tetrominoe_as(game, &EMPTY_CELL);
}

void draw_current_tetrominoe_as(Game* game, const Image* image){ //draws a tetronome from a series of given images
	Tetrominoe* current_tetrominoe = get_current_tetrominoe(game);
	const int* tetrominoe_array = get_tetromineo_grid(current_tetrominoe);
	int i;
	for (i = 0; i < TETROMINOE_GRID_LENGTH; i++){
		if (tetrominoe_array[i] != 0){
			int y_pos = calculate_tetris_grid_y_position(game -> board, current_tetrominoe -> x + i % TETROMINOE_GRID_WIDTH, image -> height);
			int x_pos = calculate_tetris_grid_x_position(game -> board, current_tetrominoe -> y + i / TETROMINOE_GRID_HEIGHT, image -> width);
			write_image(image, x_pos, y_pos);
		}
	}
}

int calculate_tetris_grid_y_position(Board* board, int grid_position, int size){ //converts a grid coordinate to a screen pixel coordinate (for displaying blocks)
	//NOTE: as the screen is played in a rotated state the y position calculation must use the tetronimoe's X-coordinate information
	return BACKGROUND_OFFSET_X + BACKGROUND_HOLDOFF_X + (grid_position) * size;
}

int calculate_tetris_grid_x_position(Board* board, int grid_position, int size){ //converts a grid coordinate to a screen pixel coordinate (for displaying blocks)
	//NOTE: as the screen is played in a rotated state the y position calculation must use the tetronimoe's Y-coordinate information
	return BACKGROUND_OFFSET_Y + BACKGROUND_HOLDOFF_Y + (board -> height - grid_position - 1) * size;
}

int current_tetrominoe_can_occupy(Game* game, int x_shift, int y_shift, int rotation){ //checks if a tetrominoe can occupy a specific location. can shift and rotate the tetrominoe to allow convenient use for checking movements and rotationes
	//get tetrominoe for specified rotation
	//for every "peice" : if peice is 1 and (peice is not on board or board at piece is 1) return 0
	//I.E: check if the piece is hanging off the board or overlapping on an occupied cell
	Tetrominoe* selected_tetrominoe = get_current_tetrominoe(game);
	int selected_tetrominoe_pose = abs_modulo(selected_tetrominoe -> rotation_state + rotation, TETROMINOE_STATES);
	const int* tetrominoe_array = selected_tetrominoe -> poses[selected_tetrominoe_pose] -> array;
	int i;
	for (i = 0; i < TETROMINOE_GRID_LENGTH; i++){
		if (is_off_grid(game -> board, selected_tetrominoe -> x + x_shift + i % TETROMINOE_GRID_WIDTH, selected_tetrominoe -> y + y_shift + i / TETROMINOE_GRID_HEIGHT) == TRUE){
			if (tetrominoe_array[i] != 0){
				return FALSE;
			}
		}
		else if (tetrominoe_array[i] != 0){
			if (is_occupied(game -> board, selected_tetrominoe -> x + x_shift + i % TETROMINOE_GRID_WIDTH, selected_tetrominoe -> y + y_shift + i / TETROMINOE_GRID_HEIGHT) == TRUE){
				return FALSE;
			}
		}
	}
	return TRUE;
}

int can_drop_current_tetrominoe(Game* game){ //calculates whether or not the current tetrominoe can drop
	return current_tetrominoe_can_occupy(game, 0, 1, 0);
}

int can_rotate_current_tetrominoe(Game* game){//calculates whether or not the current tetrominoe can rotate
	return current_tetrominoe_can_occupy(game, 0, 0, 1);
}

int can_shift_current_tetrominoe(Game* game, int direction){//calculates whether or not the current tetrominoe can shift
	return current_tetrominoe_can_occupy(game, direction, 0, 0);
}

int is_off_grid(Board* board, int x, int y){ //indicates whether or not a coordinate is on the board
	if (x >= board -> width || x < 0 || y >= board -> height || y < 0){
		return TRUE;
	}
	else{
		return FALSE;
	}

}

int is_occupied(Board* board, int x, int y){ //calculates whether or not a cell on the board is occupied
	if (board -> grid[y * board -> width + x] != 0){
		return TRUE;
	}
	else{
		return FALSE;
	}
}

int abs_modulo(int number, int divisor){ //executes a modulus functions which always returns a positive value
	int result = number % divisor;
	while (result < 0){
		result += divisor;
	}
	return result;
}

void place_current_tetrominoe(Game* game){//places the current tetrominoe on the board

	Tetrominoe* current_tetrominoe = get_current_tetrominoe(game);
	const int* tetrominoe_array = get_tetromineo_grid(current_tetrominoe);
	int i;
	for (i = 0; i < TETROMINOE_GRID_LENGTH; i++){
		int x_pos = (current_tetrominoe -> x + (i % TETROMINOE_GRID_WIDTH));
		int y_pos = (current_tetrominoe -> y + (i / TETROMINOE_GRID_HEIGHT));
		if (is_off_grid(game -> board, x_pos, y_pos) == FALSE && tetrominoe_array[i] != 0){
			game -> board -> grid[x_pos + y_pos * game -> board -> width] = tetrominoe_array[i];
		}
	}
}

void debug_board(Game* game){
	char text[DEFAULT_GRID_WIDTH + 4];
	const char *new_line1 = "\n";
	const char *new_line2 = "END\n";
	int i;
	int j;
	for (j = 0; j < DEFAULT_GRID_HEIGHT; j++){
		for (i = 0; i < DEFAULT_GRID_WIDTH; i++){
			text[i] = (char) (48 + game -> board -> grid[i + j * game -> board -> width]);
		}
		text[DEFAULT_GRID_WIDTH + 1] = '\n';
		text[DEFAULT_GRID_WIDTH + 2] = '\00';
		text[DEFAULT_GRID_WIDTH + 3] = '\00';
		vPrintString(text);
		vPrintString(new_line1);
	}
	vPrintString(new_line2);
}
