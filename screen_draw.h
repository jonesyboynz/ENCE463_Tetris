/*
 * screen_draw.h
 *
 *  Created on: Aug 4, 2016
 *      Author: srj52
 */

#ifndef SCREEN_DRAW_H_
#define SCREEN_DRAW_H_

#include "game_engine.h"

void draw_start_screen(Game* game);
//draws the start screen

void draw_tetris_background(Game* game);
//draws the background for the tetris game

void draw_score_screen(Game* game);
//draws the score screen

void draw_debug_screen(Game* game);
//draws the debug screen

#endif /* SCREEN_DRAW_H_ */
