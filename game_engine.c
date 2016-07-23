#include "game_engine.h"
#include "tetrominoe.h"
#include "display.h"

//Setup for the default game grid. This grid will be used most of the time
int grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
Board game_board = {grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};
Tetrominoe* tetrominoes[2] = {&block0, &block6}; //will need to be extended once new tetrominoes are coded
Game game = {&game_board, tetrominoes, 2, 0};

void clear_board(Board* board){
	int i;
	for (i = 0; i < board -> width * board -> height; i++){
		board -> grid[i] = 0;
	}
}

void initalise_game(Game* game){
	clear_board(game -> board);
	int i;
	for (i = 0; i < game -> num_tetrominoes; i++){
		reset_tetromineo(game -> tetrominoes[i]);
	}
	game -> current_peice_index = 0;
	draw_background();
}

void draw_background(void){
	write_image(&TETRIS_BACKGROUND, BACKGROUND_OFFSET_Y, BACKGROUND_OFFSET_X);
}

void draw_current_tetrominoe(Game* game){ //draws the current tetronimoe
	draw_current_tetrominoe_as(game, &FULL_CELL);
}

void erase_current_tetrominoe(Game* game){ //removes the current tetronimoe
	draw_current_tetrominoe_as(game, &EMPTY_CELL);
}

void draw_current_tetrominoe_as(Game* game, const Image* image){ //draws a tetronome from a series of given images
	Tetrominoe* current_tetrominoe = game -> tetrominoes[game -> current_peice_index];
	const int* tetrominoe_array = get_tetromineo_grid(current_tetrominoe);
	int i;
	for (i = 0; i < TETROMINOE_GRID_LENGTH; i++){
		if (tetrominoe_array[i] != 0){
			int y_pos = calculate_tetris_grid_y_position(current_tetrominoe -> x + i % TETROMINE_GIRD_WIDTH, image -> height);
			int x_pos = calculate_tetris_grid_x_position(current_tetrominoe -> y + i / TETROMINE_GRID_HEIGHT, image -> width);
			write_image(image, x_pos, y_pos);
		}
	}
}

int calculate_tetris_grid_y_position(int grid_position, int size){ //converts a grid coordinate to a screen pixel coordinate (for displaying blocks)
	//NOTE: as the screen is played in a rotated state the y position calculation must use the tetronimoe's X-coordinate information
	return BACKGROUND_OFFSET_X + BACKGROUND_HOLDOFF_X + grid_position * size;
}

int calculate_tetris_grid_x_position(int grid_position, int size){ //converts a grid coordinate to a screen pixel coordinate (for displaying blocks)
	//NOTE: as the screen is played in a rotated state the y position calculation must use the tetronimoe's Y-coordinate information
	return BACKGROUND_OFFSET_Y + BACKGROUND_HOLDOFF_Y + grid_position * size;
}
