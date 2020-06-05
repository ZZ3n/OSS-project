#pragma once
#include "const.h"

void Game_GameOver(int mode, int score, int best, Queue *pq, int stage, int * scoreArr);
void Game_Start(MapData map[22][22], int stage, int * scoreArr, int mode);
int getKeyDown(void);
///############################void gotoxy(int x, int y);
void hidecursor(void);
int isOverlap(int savedKey, int key);