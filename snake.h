#pragma once
#include <stdlib.h>
#include "const.h"
#include "snake.c"

// 2Â÷¿ø ¹è¿­ ¸Ê
typedef int MData;

typedef struct _snakexp {
	int x;
	int y;
} SnakePos;

void Game_PlayDrawTail(MapData map[ MAP_SIZE ][MAP_SIZE], int snake_x, int snake_y);
void Game_PlayDrawHead(MapData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y);
void Game_PlayRemoveTail(MapData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y);
int Game_PlayPredictHead(int xy, int way);
int Game_PlayMoveSnake(MapData map[MAP_SIZE][MAP_SIZE], SnakePos * snake, int way);