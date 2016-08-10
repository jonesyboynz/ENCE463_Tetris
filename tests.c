/*
 * tests.c
 *	a test module that contains some basic testing tasks. these include a few basic tasks to test apsects of the game engine.
 *
 *  Created on: Aug 10, 2016
 *      Author: srj52
 */

/* FreeRTOS includes. */
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"

#include "tests.h"

/* tetris game engine includes */
#include "display.h"
#include "game_engine.h"
#include "tetrominoe.h"
#include "bool.h"
#include "buttons.h"
#include "math.h"

void tetronimoe_drop_test(void* parameters){ //tests if the tetrominoe drop is working
	//portTickType xLastWakeTime;
	while (1){
		base_game.tetrominoes[base_game.current_peice_index] -> x = 0;
		draw_current_tetrominoe(&base_game);
		vTaskDelay(250 / portTICK_RATE_MS);
		erase_current_tetrominoe(&base_game);
		base_game.tetrominoes[base_game.current_peice_index] -> y = (base_game.tetrominoes[base_game.current_peice_index] -> y + 1) % 17;
		if (base_game.tetrominoes[base_game.current_peice_index] -> y == 0){
			rotate_tetromineo(base_game.tetrominoes[base_game.current_peice_index]);
			base_game.current_peice_index = (base_game.current_peice_index + 1) % base_game.num_tetrominoes;
		}
	}
}

void tetronimoe_drop_test2(void* parameters){ //tests if the tetrominoe drop is working and switches peices
	//portTickType xLastWakeTime;
	Game* game = (Game*) parameters;
	int x_pos = 0;
	while (1){
		game -> tetrominoes[game -> current_peice_index] -> x = x_pos;
		draw_current_tetrominoe(game);
		vTaskDelay(250 / portTICK_RATE_MS);
		if (can_drop_current_tetrominoe(game) == TRUE){
			erase_current_tetrominoe(game);
			get_current_tetrominoe(game) -> y = get_current_tetrominoe(game) -> y + 1;
		}
		else{
			place_current_tetrominoe(game);
			//debug_board(&game);
			//game.tetrominoes[game.current_peice_index] -> y = 0;
			//game.tetrominoes[game.current_peice_index] -> rotation_state = rand_range(0, 3);
			get_next_tetrominoe(game);
			if (spawn_new_tetrominoe(game) != TRUE){
				reset_game(game);
			}
			rotate_tetromineo(game -> tetrominoes[game -> current_peice_index]);
			//game.current_peice_index = rand_range(0, game.num_tetrominoes);
			//game.current_peice_index = (game.current_peice_index + 1) % game.num_tetrominoes;
			x_pos = (x_pos + 2) % 7;
		}
	}
}


void vDisplayRunning(void* parameters){ //plays a small animation in the bottom right cornor of the screen to show that the system is running
	xQueueHandle display_queue = (xQueueHandle) parameters;
	int index = 0;

	while (1){
		DisplayTask task1 ={(void*) RUNNING_ANIMATION[index], 0, 94};
		enqueue_display_task(&display_queue, &task1);
		vTaskDelay(50 / portTICK_RATE_MS);
		index = (index + 1)  % 4;
	}
}

void vButtonTest(void* parameters){ //tests the button queue by pereodically writing button events
	xQueueHandle ButtonQueue = (xQueueHandle) parameters;

	while (1){
		ButtonEvent event = {NAV_LEFT, PRESS_EVENT};
		enqueue_button_event(&ButtonQueue, &event);
		vTaskDelay(2000 / portTICK_RATE_MS);
	}
}


