/*
 * screen_draw.c
 *
 *  Created on: Aug 4, 2016
 *      Author: srj52
 */

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

//game system includes
#include "screen_draw.h"
#include "strings.h"
#include "display.h"
#include "images.h"

#define VERSION_STRING_X 1
#define VERSION_STRING_Y 1

#define VERSION_NUMBER_X 1
#define VERSION_NUMBER_Y 30
#define VERSION 3

#define AUTHOR_STRING_X 1
#define AUTHOR_STRING_Y 37

#define START_PROMPT_X 13
#define START_PROMPT_Y 12

#define BUTTON_GRID_X_CENTRE 45
#define BUTTON_GRID_Y_CENTRE 43
#define BUTTON_GRID_X_TOP 55
#define BUTTON_GRID_X_BOTTOM 35
#define BUTTON_GRID_Y_TOP 34
#define BUTTON_GRID_Y_BOTTOM 52

#define ROTATE_MSG_X (BUTTON_GRID_X_TOP + 11)
#define ROTATE_MSG_Y (BUTTON_GRID_Y_CENTRE - 7)
#define LEFT_MSG_X (BUTTON_GRID_X_CENTRE + 2)
#define LEFT_MSG_Y (BUTTON_GRID_Y_TOP - 16)
#define RIGHT_MSG_X (BUTTON_GRID_X_CENTRE + 2)
#define RIGHT_MSG_Y (BUTTON_GRID_Y_BOTTOM + 12)
#define DROP_MSG_X (BUTTON_GRID_X_BOTTOM - 9)
#define DROP_MSG_Y (BUTTON_GRID_Y_CENTRE - 14)

#define START_SCREEN_X (127 - 50)
#define START_SCREEN_Y 0

void draw_start_screen(Game* game){ //draws the start screen
	quick_clear_screen(&(game -> display_queue));
	quick_send_image(&(game -> display_queue), START_SCREEN_X, START_SCREEN_Y, &TETRIS_START_SCREEN);

	quick_send_string(&(game -> display_queue), VERSION_STRING_X, VERSION_STRING_Y, (char*) VERSION_STRING);
	quick_send_number(&(game -> display_queue), VERSION_NUMBER_X, VERSION_NUMBER_Y, VERSION);
	quick_send_string(&(game -> display_queue), AUTHOR_STRING_X, AUTHOR_STRING_Y, (char*) AUTHOR_STRING);

	quick_send_string(&(game -> display_queue), START_PROMPT_X, START_PROMPT_Y, (char*) ANY_KEY_TO_CONTINUE_STRING);

	quick_send_image(&(game -> display_queue), BUTTON_GRID_X_TOP, BUTTON_GRID_Y_CENTRE, &RIGHT_BUTTON_ICON); //up
	quick_send_image(&(game -> display_queue), BUTTON_GRID_X_CENTRE, BUTTON_GRID_Y_BOTTOM, &DOWN_BUTTON_ICON); //right
	quick_send_image(&(game -> display_queue), BUTTON_GRID_X_CENTRE, BUTTON_GRID_Y_TOP, &UP_BUTTON_ICON); //left
	quick_send_image(&(game -> display_queue), BUTTON_GRID_X_BOTTOM, BUTTON_GRID_Y_CENTRE, &LEFT_BUTTON_ICON); //down

	quick_send_string(&(game -> display_queue), ROTATE_MSG_X, ROTATE_MSG_Y, (char*) ROTATE_HELP_MSG);
	quick_send_string(&(game -> display_queue), DROP_MSG_X, DROP_MSG_Y, (char*) DROP_HELP_MSG);
	quick_send_string(&(game -> display_queue), LEFT_MSG_X, LEFT_MSG_Y, (char*) LEFT_HELP_MSG);
	quick_send_string(&(game -> display_queue), RIGHT_MSG_X, RIGHT_MSG_Y, (char*) RIGHT_HELP_MSG);
}


//position constants are defined in game_engine.h as the game engine makes use of them

void draw_tetris_background(Game* game){ //draws the background for the game
	quick_clear_screen(&(game -> display_queue));
	quick_send_image(&(game -> display_queue), BACKGROUND_OFFSET_Y, BACKGROUND_OFFSET_X, &TETRIS_BACKGROUND);
	quick_send_image(&(game -> display_queue), NEXT_TETROMINOE_BOARDER_X, NEXT_TETROMINOE_BOARDER_Y, &NEXT_TETROMINOE_BOARDER);
	quick_send_string(&(game -> display_queue), NEXT_TEXT_X, NEXT_TEXT_Y, (char*) NEXT_STRING);
	quick_send_string(&(game -> display_queue), LEVEL_TEXT_X, LEVEL_TEXT_Y, (char*) LEVEL_STRING);
	quick_send_string(&(game -> display_queue), SCORE_TEXT_X, SCORE_TEXT_Y, (char*) SCORE_STRING);
}

#define GAME_OVER_X 101
#define GAME_OVER_Y 0

#define SCORE_STRING_X 80
#define SCORE_STRING_Y 20

#define SCORE_NUMBER_X SCORE_STRING_X
#define SCORE_NUMBER_Y (SCORE_STRING_Y + 50)

#define LEVELS_STIRNG_X (SCORE_STRING_X - 21)
#define LEVELS_STIRNG_Y 17

#define LEVELS_NUMBER_X LEVELS_STIRNG_X
#define LEVELS_NUMBER_Y (LEVELS_STIRNG_Y + 60)

#define ROWS_STRING_X (LEVELS_STIRNG_X - 21)
#define ROWS_STRING_Y 15

#define ROWS_NUMBER_X ROWS_STRING_X
#define ROWS_NUMBER_Y (ROWS_STRING_Y + 63)

#define THANKS_STRING_X (ROWS_STRING_X - 21)
#define THANKS_STRING_Y 5

void draw_score_screen(Game* game){ //draws the score screen
	quick_clear_screen(&(game -> display_queue));
	quick_send_image(&(game -> display_queue), GAME_OVER_X, GAME_OVER_Y, &GAME_OVER_SCREEN);

	quick_send_string(&(game -> display_queue), SCORE_STRING_X, SCORE_STRING_Y, (char*) FINAL_SCORE_STRING);
	quick_send_number(&(game -> display_queue), SCORE_NUMBER_X, SCORE_NUMBER_Y, game -> score);

	quick_send_string(&(game -> display_queue), LEVELS_STIRNG_X, LEVELS_STIRNG_Y, (char*) LEVELS_CLEARED_STRING);
	quick_send_number(&(game -> display_queue), LEVELS_NUMBER_X, LEVELS_NUMBER_Y, game -> level);

	quick_send_string(&(game -> display_queue), ROWS_STRING_X, ROWS_STRING_Y, (char*) ROWS_COMPLETED_STRING);
	quick_send_number(&(game -> display_queue), ROWS_NUMBER_X, ROWS_NUMBER_Y, game -> completed_rows);

	quick_send_string(&(game -> display_queue), THANKS_STRING_X, THANKS_STRING_Y, (char*) THANKS_STRING);
}

#define DEBUG_TITLE_X 118
#define DEBUG_TITLE_Y 0

#define AVG_INPUT_DELAY_STRING_X (DEBUG_TITLE_X - 17)
#define AVG_INPUT_DELAY_STRING_Y 0

#define AVG_INPUT_DELAY_NUMBER_X (AVG_INPUT_DELAY_STRING_X - 6)
#define AVG_INPUT_DELAY_NUMBER_Y 0

#define MAX_INPUT_DELAY_STRING_X (AVG_INPUT_DELAY_NUMBER_X - 17)
#define MAX_INPUT_DELAY_STRING_Y 0

#define MAX_INPUT_DELAY_NUMBER_X (MAX_INPUT_DELAY_STRING_X - 6)
#define MAX_INPUT_DELAY_NUMBER_Y 0

#define SYSTEM_TICK_STRING_X (MAX_INPUT_DELAY_STRING_X - 17)
#define SYSTEM_TICK_STRING_Y 0

#define SYSTEM_TICK_NUMBER_X (SYSTEM_TICK_STRING_X - 6)
#define SYSTEM_TICK_NUMBER_Y 0

#define REFRESH_RATE_STRING_X (SYSTEM_TICK_STRING_X - 17)
#define REFRESH_RATE_STRING_Y 0

#define REFRESH_RATE_NUMBER_X (REFRESH_RATE_STRING_X - 6)
#define REFRESH_RATE_NUMBER_Y 0

void draw_debug_screen(Game* game){ //draws the debug screen
	quick_clear_screen(&(game -> display_queue));
	quick_send_string(&(game -> display_queue), DEBUG_TITLE_X, DEBUG_TITLE_Y, (char*) DEBUG_TITLE_STRING);

	quick_send_string(&(game -> display_queue), AVG_INPUT_DELAY_STRING_X, AVG_INPUT_DELAY_STRING_Y, (char*) DEBUG_AVERAGE_INPUT_DELAY_STRING);
	quick_send_number(&(game -> display_queue), AVG_INPUT_DELAY_NUMBER_X, AVG_INPUT_DELAY_NUMBER_Y, (int) game -> debug_timers -> average_input_latency);

	quick_send_string(&(game -> display_queue), MAX_INPUT_DELAY_STRING_X, MAX_INPUT_DELAY_STRING_Y, (char*) DEBUG_MAXIMUM_INPUT_DELAY_STRING);
	quick_send_number(&(game -> display_queue), MAX_INPUT_DELAY_NUMBER_X, MAX_INPUT_DELAY_NUMBER_Y, (int) game -> debug_timers -> max_input_latency);

	quick_send_string(&(game -> display_queue), SYSTEM_TICK_STRING_X, SYSTEM_TICK_STRING_Y, (char*) DEBUG_SYSTEM_TICK_RATE_STRING);
	quick_send_number(&(game -> display_queue), SYSTEM_TICK_NUMBER_X, SYSTEM_TICK_NUMBER_Y, (int) portTICK_RATE_MS);

	quick_send_string(&(game -> display_queue), REFRESH_RATE_STRING_X, REFRESH_RATE_STRING_Y, (char*) GAME_REFRESH_RATE_STRING);
	quick_send_number(&(game -> display_queue), REFRESH_RATE_NUMBER_X, REFRESH_RATE_NUMBER_Y, (int) game -> debug_timers -> refresh_rate);
}
