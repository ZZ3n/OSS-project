#pragma once
#include "basic.h"

void Game_PlayDrawTail(MapData map[22][22], int snake_x, int snake_y);
void Game_PlayDrawHead(MapData map[22][22], int snake_x, int snake_y);
void Game_PlayRemoveTail(MapData map[22][22], int snake_x, int snake_y);
int Game_PlayPredictHead(int xy, int way);
int Game_PlayMoveSnake(MapData map[22][22], SnakePos * snake, int way);