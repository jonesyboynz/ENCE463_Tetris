//Game engine API - Contains functions to drive the game engine
//By Simon Jones

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

/* Demo includes. */
#include "demo_code\basic_io.h"

/* Tetris engine includes*/
#include "game_engine.h"
#include "tetrominoe.h"
#include "display.h"
#include "bool.h"
#include "board.h"
#include "buttons.h"
#include "math.h"
#include "timer.h"
#include "strings.h"

#define DEBUG_SCREEN_ENABLE

//Setup for the default game grid. This grid will be used most of the time
int grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
Board game_board = {grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};

//setup for the game engine
Tetrominoe* tetrominoes[7] = {&block0, &block1, &block2, &block3, &block4, &block5, &block6};
int tick_rates[20] = {500, 475, 450, 325, 300, 290, 280, 270, 260, 250, 240, 230, 210, 200, 166, 133, 100, 50, 30, 16};
Game base_game = {&game_board, tetrominoes, 7, 0, 0, 0, NULL, NULL, 0, 0, 1, tick_rates, 0};

//setup some temporary variables needed to clear completed rows
int temp_board_grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
int differences_grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
Board temp_board = {temp_board_grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};
Board differences = {temp_board_grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};


void xGameEngineTask(void* parameters){ //the main task for the game engine
	Game* game = (Game*) parameters;

	//create the button and display tasks
	xTaskCreate(xDisplayTask, "display task", 500, (void*) game -> display_queue, 1, NULL);
	xTaskCreate(xButtonReadTask, "button poll task", 500, (void*) game -> button_queue, 1, NULL);

	while (TRUE){
		//start screen loop
		//
		splash_screen_loop(game);
		reset_game(game);
		game_loop(game);
		score_screen_loop(game);
#ifdef DEBUG_SCREEN_ENABLE
		debug_screen_loop(game);
#endif

	}
}

void game_loop(Game* game){ //loop in which the game runs
	spawn_new_tetrominoe(game);
	update_score_and_level(game, 0);
	int running = TRUE;
	while (running == TRUE){
		draw_current_tetrominoe(game);
		button_process_loop(game);
		if (can_drop_current_tetrominoe(game) == TRUE){
			erase_current_tetrominoe(game);
			shift_tetrominoe(get_current_tetrominoe(game), 0 , 1);
			//get_current_tetrominoe(game) -> y = get_current_tetrominoe(game) -> y + 1;
		}
		else{
			place_current_tetrominoe(game);
			int completed_rows = num_complete_rows(game -> board);
			if (completed_rows > 0){
				clear_full_rows(game);
				update_score_and_level(game, completed_rows);
			}
			get_next_tetrominoe(game);
			if (spawn_new_tetrominoe(game) != TRUE){
				running = FALSE;
			}

		}
	}
}

void button_process_loop(Game* game){ //a loop in which the game waits for button events
	int running = TRUE;
	Timeout timer;
	ButtonEvent event;
	start_timeout(&timer, game -> current_tick_rate);
	while (running){
		if (xQueueReceive(game -> button_queue, &event, 0) != pdPASS){
		}
		else{
			process_button_event(&event, game);
		}
		if (has_timed_out(&timer) == TRUE){
			running = FALSE;
		}
	}
}

void process_button_event(ButtonEvent* event, Game* game){ //processes a button event
	if (event -> event_type == PRESSED){
		if (event -> button_id == NAV_UP){
			try_rotate_current_tetrominoe(game);
		}
		else if (event -> button_id == NAV_LEFT){
			try_shift_current_tetrominoe(game, LEFT);
		}
		else if (event -> button_id == NAV_RIGHT){
			try_shift_current_tetrominoe(game, RIGHT);
		}
		else if (event -> button_id == NAV_DOWN){
			full_drop_current_tetrominoe(game);
		}
	}
}

void splash_screen_loop(Game* game){
	quick_clear_screen(&(game -> display_queue));
	quick_send_string(&(game -> display_queue), 100, 35, (char*) TEMP_TETRIS_STRING);
	quick_send_string(&(game -> display_queue), 1, 1, (char*) VERSION_STRING);
	quick_send_number(&(game -> display_queue), 1, 30, 1);
	quick_send_string(&(game -> display_queue), 1, 37, (char*) AUTHOR_STRING);

	quick_send_image(&(game -> display_queue), 64, 44, &BUTTON_ICON);
	quick_send_image(&(game -> display_queue), 56, 52, &BUTTON_ICON);
	quick_send_image(&(game -> display_queue), 56, 36, &BUTTON_ICON);
	quick_send_image(&(game -> display_queue), 48, 44, &BUTTON_ICON);

	quick_send_string(&(game -> display_queue), 75, 36, (char*) ROTATE_HELP_MSG);
	quick_send_string(&(game -> display_queue), 39, 30, (char*) DROP_HELP_MSG);
	quick_send_string(&(game -> display_queue), 57, 19, (char*) LEFT_HELP_MSG);
	quick_send_string(&(game -> display_queue), 57, 62, (char*) RIGHT_HELP_MSG);

	generic_wait_loop(game);
}

void score_screen_loop(Game* game){
	quick_clear_screen(&(game -> display_queue));
	quick_send_string(&(game -> display_queue), 106, 30, (char*) TEMP_GAME_OVER_STRING);

	quick_send_string(&(game -> display_queue), 85, 15, (char*) FINAL_SCORE_STRING);
	quick_send_number(&(game -> display_queue), 85, 65, game -> score);

	quick_send_string(&(game -> display_queue), 64, 15, (char*) LEVELS_CLEARED_STRING);
	quick_send_number(&(game -> display_queue), 64, 75, game -> level);

	quick_send_string(&(game -> display_queue), 44, 20, (char*) ROWS_COMPLETED_STRING);
	quick_send_number(&(game -> display_queue), 44, 70, game -> completed_rows);

	quick_send_string(&(game -> display_queue), 21, 5, (char*) THANKS_STRING);

	generic_wait_loop(game);
}

void debug_screen_loop(Game* game){ //displays debug information
	quick_clear_screen(&(game -> display_queue));
	quick_send_string(&(game -> display_queue), 118, 0, (char*) DEBUG_TITLE_STRING);
	quick_send_string(&(game -> display_queue), 103, 0, (char*) DEBUG_AVERAGE_INPUT_DELAY_STRING);
	quick_send_string(&(game -> display_queue), 88, 0, (char*) DEBUG_MAXIMUM_INPUT_DELAY_STRING);

	quick_send_string(&(game -> display_queue), 73, 0, (char*) DEBUG_SYSTEM_TICK_RATE_STRING);
	quick_send_number(&(game -> display_queue), 67, 0, (int) portTICK_RATE_MS);

	quick_send_string(&(game -> display_queue), 58, 0, (char*) GAME_REFRESH_RATE_STRING);
	generic_wait_loop(game);
}

void generic_wait_loop(Game* game){ //a generic loop which exits on button input
	int waiting = TRUE;
	ButtonEvent event;
	while (waiting == TRUE){
		if (xQueueReceive(game -> button_queue, &event, 0) != pdPASS){
		}
		else if (event.event_type == PRESSED){
			waiting = FALSE;
		}
	}
}

void initalise_game(Game* game){ //intalises the game. Mainly clears data
	initalise_display_queue(&(game -> display_queue));
	initalise_button_event_queue(&(game -> button_queue));
}

void reset_game(Game* game){ //resets the game
	int i;
	for (i = 0; i < game -> num_tetrominoes; i++){
		reset_tetromineo(game -> tetrominoes[i]);
	}
	game -> current_peice_index = 0;
	game -> next_peice_index = 0;
	game -> peice_repetitions = 0;
	game -> score = 0;
	game -> level = 1;
	game -> completed_rows = 0;
	game -> current_tick_rate = game -> tick_rates[game -> level - 1];
	clear_board(game -> board);
	quick_clear_screen(&(game -> display_queue));
	quick_send_image(&(game -> display_queue), BACKGROUND_OFFSET_Y, BACKGROUND_OFFSET_X, &TETRIS_BACKGROUND);
	quick_send_string(&(game -> display_queue), NEXT_TEXT_X, NEXT_TEXT_Y, (char*) NEXT_STRING);
	quick_send_string(&(game -> display_queue), LEVEL_TEXT_X, LEVEL_TEXT_Y, (char*) LEVEL_STRING);
	quick_send_string(&(game -> display_queue), SCORE_TEXT_X, SCORE_TEXT_Y, (char*) SCORE_STRING);
	get_next_tetrominoe(game); //initalise the tetrominoes
	get_next_tetrominoe(game); //the next tetrominoe is known
	//todo clear the button queue
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
	draw_tetrominoe(game, current_tetrominoe, image, current_tetrominoe -> x, current_tetrominoe -> y);
}

void draw_tetrominoe(Game* game, Tetrominoe* selected_tetrominoe, const Image* cell_image, int x, int y){ //draw a tetrominoe at some x, y coordinates
	const int* tetrominoe_array = get_tetromineo_grid(selected_tetrominoe);
	int i;
	for (i = 0; i < TETROMINOE_GRID_LENGTH; i++){
		if (tetrominoe_array[i] != 0){
			int y_pos = calculate_tetris_grid_y_position(game -> board, x + i % TETROMINOE_GRID_WIDTH, cell_image -> height);
			int x_pos = calculate_tetris_grid_x_position(game -> board, y + i / TETROMINOE_GRID_HEIGHT, cell_image -> width);
			quick_send_image(&(game -> display_queue), x_pos, y_pos, cell_image);
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
		if (is_off_board(game -> board, selected_tetrominoe -> x + x_shift + i % TETROMINOE_GRID_WIDTH, selected_tetrominoe -> y + y_shift + i / TETROMINOE_GRID_HEIGHT) == TRUE){
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

void place_current_tetrominoe(Game* game){//places the current tetrominoe on the board

	Tetrominoe* current_tetrominoe = get_current_tetrominoe(game);
	const int* tetrominoe_array = get_tetromineo_grid(current_tetrominoe);
	int i;
	for (i = 0; i < TETROMINOE_GRID_LENGTH; i++){
		int x_pos = (current_tetrominoe -> x + (i % TETROMINOE_GRID_WIDTH));
		int y_pos = (current_tetrominoe -> y + (i / TETROMINOE_GRID_HEIGHT));
		if (is_off_board(game -> board, x_pos, y_pos) == FALSE && tetrominoe_array[i] != 0){
			set_board_value(game -> board, x_pos, y_pos, tetrominoe_array[i]);
		}
	}
}

void debug_board(Board* board){//prints the current state of the board in the CCS console
	char text[DEFAULT_GRID_WIDTH + 4];
	const char *new_line1 = "\n";
	const char *new_line2 = "END\n";
	int i;
	int j;
	for (j = 0; j < DEFAULT_GRID_HEIGHT; j++){
		for (i = 0; i < DEFAULT_GRID_WIDTH; i++){
			text[i] = (char) (48 + board -> grid[i + j * board -> width]);
		}
		text[DEFAULT_GRID_WIDTH + 1] = '\n';
		text[DEFAULT_GRID_WIDTH + 2] = '\00';
		text[DEFAULT_GRID_WIDTH + 3] = '\00';
		vPrintString(text);
		vPrintString(new_line1);
	}
	vPrintString(new_line2);
}

int spawn_new_tetrominoe(Game* game){//spawns the current block
	Tetrominoe* current_tetrominoe = get_current_tetrominoe(game);
	current_tetrominoe -> rotation_state = 0;
	current_tetrominoe -> x = game -> board -> width / 2 - 2;
	current_tetrominoe -> y = -1;
	if (current_tetrominoe_can_occupy(game, 0, 0, 0) == TRUE){
		return TRUE;
	}
	else if (current_tetrominoe_can_occupy(game, 0, 1, 0) == TRUE){
		current_tetrominoe -> y += 1;
		return TRUE;
	}
	else{
		return FALSE; //cannot place tetrominoe. game over
	}
}

void get_next_tetrominoe(Game* game){ //shifts the next tetrominoe index into the current tetrominoe and randomly selects the next tetrominoe
	erase_next_tetrominoe_on_side(game);
	game -> current_peice_index = game -> next_peice_index;
	int next = rand_range(0, game -> num_tetrominoes - 1);
	while (game -> current_peice_index == next && game -> peice_repetitions > 4){
		next = rand_range(0, game -> num_tetrominoes - 1);
	}
	game -> next_peice_index = next;
	if (game -> next_peice_index == game -> current_peice_index){
		game -> peice_repetitions += 1;
	}
	else{
		game -> peice_repetitions = 0;
	}
	draw_next_tetrominoe_on_side(game);
}

void draw_next_tetrominoe_on_side(Game* game){ //draws the next tetrominoe on the side
	game -> tetrominoes[game -> next_peice_index] -> rotation_state = 0;
	draw_tetrominoe(game, game -> tetrominoes[game -> next_peice_index], &FULL_CELL, NEXT_TETROMINOE_X_GRID_POSITION, NEXT_TETROMINOE_Y_GRID_POSITION);
}

void erase_next_tetrominoe_on_side(Game* game){ //erases the current drawing of the next tetromominoe
	game -> tetrominoes[game -> next_peice_index] -> rotation_state = 0;
	draw_tetrominoe(game, game -> tetrominoes[game -> next_peice_index], &EMPTY_CELL, NEXT_TETROMINOE_X_GRID_POSITION, NEXT_TETROMINOE_Y_GRID_POSITION);
}

void clear_full_rows(Game* game){ //clears the full rows in the game board
	int rows = num_complete_rows(game -> board);
	copy_board(game -> board, &temp_board);
	//debug_board(game);
	while (rows > 0){
		int row_index = get_next_complete_row(game -> board);
		clear_row(game -> board, row_index);
		rows -= 1;
	}
	board_difference(game -> board, &temp_board, &differences);
	draw_differences(game, &differences);
	//debug_board(game);
}

void draw_differences(Game* game, Board* differences){ //draws the differences given by the difference board
	int x;
	int y;
	//debug_board(differences);
	for (y = 0; y < differences -> height; y++){
		for (x = 0; x < differences -> width; x++){
			int value = get_board_value(differences, x, y);
			if (value == CHANGE_CLEARED){
				int y_pos = calculate_tetris_grid_y_position(game -> board, x, EMPTY_CELL.height);
				int x_pos = calculate_tetris_grid_x_position(game -> board, y, EMPTY_CELL.width);
				quick_send_image(&(game -> display_queue), x_pos, y_pos, &EMPTY_CELL);
			}
			else if (value == CHANGE_FILLED){
				int y_pos = calculate_tetris_grid_y_position(game -> board, x, FULL_CELL.height);
				int x_pos = calculate_tetris_grid_x_position(game -> board, y, FULL_CELL.width);
				quick_send_image(&(game -> display_queue), x_pos, y_pos, &FULL_CELL);
			}
		}
	}
}

void temp_fill_cells(Game* game, int column, int bottom_row, int top_row){ //draws all emtpry cells as full cells withing a given column range
	int y;
	for (y = bottom_row; y <= top_row; y++){
		if (get_board_value(game -> board, column, y) == EMPTY_CELL_VALUE){
			const Image* image = &FULL_CELL;
			int y_pos = calculate_tetris_grid_y_position(game -> board, column, image -> height);
			int x_pos = calculate_tetris_grid_x_position(game -> board, y, image -> width);
			DisplayTask task = {(void*) image, x_pos, y_pos, COMMAND_WRITE_IMAGE};
			enqueue_display_task(&(game -> display_queue), &task);
		}
	}
}

void redraw_empty_cells(Game* game, int column, int bottom_row, int top_row){ //redraws the emptry cells in a given column
	int y;
	for (y = bottom_row; y <= top_row; y++){
		if (get_board_value(game -> board, column, y) == EMPTY_CELL_VALUE){
			const Image* image = &EMPTY_CELL;
			int y_pos = calculate_tetris_grid_y_position(game -> board, column, image -> height);
			int x_pos = calculate_tetris_grid_x_position(game -> board, y, image -> width);
			DisplayTask task = {(void*) image, x_pos, y_pos, COMMAND_WRITE_IMAGE};
			enqueue_display_task(&(game -> display_queue), &task);
		}
	}
}

void try_rotate_current_tetrominoe(Game* game){ //attempts to rotate the current tetrominoe
	if (can_rotate_current_tetrominoe(game) == TRUE){
		erase_current_tetrominoe(game);
		rotate_tetromineo(get_current_tetrominoe(game));
		draw_current_tetrominoe(game);
	}
}

void try_shift_current_tetrominoe(Game* game, int direction){
	if (can_shift_current_tetrominoe(game, direction) == TRUE){
		erase_current_tetrominoe(game);
		shift_tetrominoe(get_current_tetrominoe(game), direction, 0);
		draw_current_tetrominoe(game);
	}
}

void full_drop_current_tetrominoe(Game* game){//drops a tetrominoe till it can go no lower
	erase_current_tetrominoe(game);
	while(can_drop_current_tetrominoe(game)){
		shift_tetrominoe(get_current_tetrominoe(game), 0, 1);
	}
	draw_current_tetrominoe(game);
}

void update_score_display(Game* game){
	quick_send_number(&(game -> display_queue), SCORE_POSITION_X, SCORE_POSITION_Y, game -> score);
}

void update_level_display(Game* game){
	quick_send_number(&(game -> display_queue), LEVEL_POSITION_X, LEVEL_POSITION_Y, game -> level);
}

void update_score_and_level(Game* game, int rows_broken){
	if (rows_broken >= 1){ //catch the initial case
		game -> score += ((rows_broken * rows_broken) + 2) / 2 * 100;
		game -> completed_rows += rows_broken;
		game -> level = game -> completed_rows / ROWS_TILL_LEVEL_ADVANCE + 1;
	}

	if (game -> level <= 20){
		game -> current_tick_rate = game -> tick_rates[game -> level];
	}
	update_level_display(game);
	update_score_display(game);
}
