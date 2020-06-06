#pragma once
#include "basic.h"

int Map_MenuDrawStart(void);
int Map_MenuDrawMode(void);
int Map_MenuDrawStage(int mode, int * scoreArr);

void Map_GamemapInitStage1(MapData map[22][22]);
void Map_GamemapInitStage2(MapData map[22][22]);
void Map_GamemapInitStage3(MapData map[22][22]);
void Map_GamemapInitStage4(MapData map[22][22]);
void Map_GamemapDrawWall(MapData map[22][22]);
void Map_GamemapDrawScoreboard(int score, int best, int stage);