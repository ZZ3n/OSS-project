#pragma once
#include "basic.h"

void Game_GameOver(int mode, int score, int best, Queue *pq, int stage, int * scoreArr);
void Game_Start(MapData map[22][22], int stage, int * scoreArr, int mode);
int getKeyDown(void);
void hidecursor(void);
int isOverlap(int savedKey, int key);