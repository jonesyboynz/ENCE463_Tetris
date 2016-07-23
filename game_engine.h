#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

typedef struct board_s {
	int* grid;
	int rows;
	int columns;
} Board;

typedef struct game_s {
	Board board;

} Game;

#endif