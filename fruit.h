#pragma once
#include "const.h"

// 사과의 x,y 좌표와 사과 갯수
typedef struct _fruitxy {
	int x;
	int y;
	int numOfFruit;
} FruitPos;

int Game_DrawFruit(MapData map[MAP_SIZE][MAP_SIZE], FruitPos * fp);
int Game_DrawSpecial(MapData map[MAP_SIZE][MAP_SIZE], FruitPos * fp);
int Game_RemoveFruit(MapData map[MAP_SIZE][MAP_SIZE], FruitPos * fp);