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
#include "screen_draw.h"

#define DEBUG_SCREEN_ENABLE
#define GENERIC_LOOP_WAIT_TIME_MS 250

//Setup for the default game grid. This grid will be used most of the time
int grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
Board game_board = {grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};

//setup for the game engine
Tetrominoe* tetrominoes[7] = {&block0, &block1, &block2, &block3, &block4, &block5, &block6};
int tick_rates[20] = {500, 480, 460, 440, 420, 400, 380, 360, 340, 320, 300, 280, 260, 240, 220, 200, 150, 100, 50, 16};
Game base_game = {&game_board, tetrominoes, 7, 0, 0, 0, NULL, NULL, 0, 0, 1, tick_rates, 0, &DEBUG_TIMERS};
int score_bonuses[4] = {100, 250, 525, 800};

//setup some temporary variables needed to clear completed rows
int temp_board_grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
int differences_grid[DEFAULT_GRID_HEIGHT * DEFAULT_GRID_WIDTH];
Board temp_board = {temp_board_grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};
Board differences = {temp_board_grid, DEFAULT_GRID_WIDTH, DEFAULT_GRID_HEIGHT};

void game_loop(Game* game);

void splash_screen_loop(Game* game);

void score_screen_loop(Game* game);

void clear_board(Board* board);

void game_loop(Game* game);

void button_process_loop(Game* game);

void update_refresh_rate(Game* game);

void process_button_event(ButtonEvent* event, Game* game);

void splash_screen_loop(Game* game);

void score_screen_loop(Game* game);

void debug_screen_loop(Game* game);

void generic_wait_loop(Game* game);

void draw_current_tetrominoe_as(Game* game, const Image* image);

void draw_tetrominoe(Game* game, Tetrominoe* tetrominoe, const Image* cell_image, int x, int y);

int calculate_tetris_grid_y_position(Board* board, int grid_position, int size);

int calculate_tetris_grid_x_position(Board* board, int grid_position, int size);

int current_tetrominoe_can_occupy(Game* game, int x_shift, int y_shift, int rotation);

int abs_modulo(int number, int divisor);

int can_rotate_current_tetrominoe(Game* game);

int can_shift_current_tetrominoe(Game* game, int direction);

void debug_board(Board* board);

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

void draw_shadow_tetrominoe(Game* game);

void erase_shadow_tetrominoe(Game* game);

void reset_debug_timers(Game* game);

void xGameEngineTask(void* parameters){ //the main task for the game engine
	Game* game = (Game*) parameters;
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
		timer_start(&(game -> debug_timers -> refresh_rate_timer));
		//draw_shadow_tetrominoe(game);
		draw_current_tetrominoe(game);
		button_process_loop(game);
		if (can_drop_current_tetrominoe(game) == TRUE){
			erase_shadow_tetrominoe(game);
			erase_current_tetrominoe(game);
			shift_tetrominoe(get_current_tetrominoe(game), 0 , 1);
		}
		else{
			//erase_shadow_tetrominoe(game);
			draw_current_tetrominoe(game);
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
			timer_stop(&(game -> debug_timers -> refresh_rate_timer));
			update_refresh_rate(game);
		}
	}
}

void reset_debug_timers(Game* game){
	AVERAGE_TIMEOUT = 0;
	MAX_TIMEOUT = 0;
	TIMEOUT_SAMPLES = 0;
	game -> debug_timers -> refresh_rate_error = 0;
	game -> debug_timers -> max_input_latency = 0;
	game -> debug_timers -> refresh_rate = 0;
	game -> debug_timers -> refresh_rate_samples = 0;
	game -> debug_timers -> average_refresh_rate_error = 0;
}

void update_refresh_rate(Game* game){ //updates the refresh rate
	game -> debug_timers -> refresh_rate = (int) (game -> debug_timers -> refresh_rate_timer.elapsed_ticks);
	int error = (((game -> debug_timers -> refresh_rate) - (game -> current_tick_rate)) * 100) / (game -> current_tick_rate);
	if (error > game -> debug_timers -> refresh_rate_error){
		game -> debug_timers -> refresh_rate_error = error;
	}
	game -> debug_timers -> average_refresh_rate_error += (long) error;
	game -> debug_timers -> refresh_rate_samples += 1;


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
			//erase_shadow_tetrominoe(game);
			process_button_event(&event, game);
#ifdef DEBUG_SCREEN_ENABLE
			DisplayTask d_task = {(void*) (event.occurance_tick), 0, 0, COMMAND_UPDATE_LATENCY}; //for debugging button latency
			enqueue_display_task(&(game -> display_queue), &d_task);
#endif
		}
		if (has_timed_out(&timer) == TRUE){
			running = FALSE;
		}
		//timer_update(&(game -> debug_timers -> refresh_rate_timer)); //this function causes bugs. cause: unknown
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
	draw_start_screen(game);
	generic_wait_loop(game);
}

void score_screen_loop(Game* game){
	draw_score_screen(game);
	generic_wait_loop(game);
}

void debug_screen_loop(Game* game){ //displays debug information
	game -> debug_timers -> average_input_latency = (int) (AVERAGE_TIMEOUT / TIMEOUT_SAMPLES); //no semaphore. completely reliant on the fixed score screen delay to prevent resource collision
	game -> debug_timers -> max_input_latency = MAX_TIMEOUT;

	draw_debug_screen(game);
	generic_wait_loop(game);
}

void generic_wait_loop(Game* game){ //a generic loop which exits on button input
	int waiting = TRUE;
	ButtonEvent event;
	Timeout timeout;
	start_timeout(&timeout, GENERIC_LOOP_WAIT_TIME_MS);
	while (has_timed_out(&timeout) == FALSE){ //sit in this loop for 500ms
		xQueueReceive(game -> button_queue, &event, 0); //discard any button inputs
	}
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
	reset_debug_timers(game);
	draw_tetris_background(game);
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
	const int* tetrominoe_array = get_tetromineo_grid(selected_tetrominoe); //NOTE: could use the board as an imput parameter rather than the game
	int i;
	for (i = 0; i < TETROMINOE_GRID_LENGTH; i++){
		if (tetrominoe_array[i] != 0){
			int y_pos = calculate_tetris_grid_y_position(game -> board, x + i % TETROMINOE_GRID_WIDTH, cell_image -> height);
			int x_pos = calculate_tetris_grid_x_position(game -> board, y + i / TETROMINOE_GRID_HEIGHT, cell_image -> width);
			quick_send_image(&(game -> display_queue), x_pos, y_pos, cell_image);
		}
	}
}

void draw_shadow_tetrominoe(Game* game){ //draws a shadow tetrominoe
	//drop the tetrominoe down as far as possible
	//draw it using the shadow grid
	//raise it back up again
	int drops = 0;
	while(can_drop_current_tetrominoe(game)){
		shift_tetrominoe(get_current_tetrominoe(game), 0, 1);
		drops += 1;
	}
	draw_current_tetrominoe_as(game, &SHADOW_CELL);
	while(drops > 0){
		shift_tetrominoe(get_current_tetrominoe(game), 0, -1);
		drops -= 1;
	}
}

void erase_shadow_tetrominoe(Game* game){
	//drop the tetrominoe down as far as possible
	//draw it using the shadow grid
	//raise it back up again
	int drops = 0;
	while(can_drop_current_tetrominoe(game)){
		shift_tetrominoe(get_current_tetrominoe(game), 0, 1);
		drops += 1;
	}
	draw_current_tetrominoe_as(game, &EMPTY_CELL);
	while(drops > 0){
		shift_tetrominoe(get_current_tetrominoe(game), 0, -1);
		drops -= 1;
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
		game -> score += score_bonuses[rows_broken - 1];
		game -> completed_rows += rows_broken;
		game -> level = game -> completed_rows / ROWS_TILL_LEVEL_ADVANCE + 1;
	}

	if (game -> level <= 20){
		game -> current_tick_rate = game -> tick_rates[game -> level];
	}
	update_level_display(game);
	update_score_display(game);
}
