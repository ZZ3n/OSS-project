#pragma once
#include "const.h"

// ����� x,y ��ǥ�� ��� ����
typedef struct _fruitxy {
	int x;
	int y;
	int numOfFruit;
} FruitPos;

int Game_DrawFruit(MapData map[MAP_SIZE][MAP_SIZE], FruitPos * fp);
int Game_DrawSpecial(MapData map[MAP_SIZE][MAP_SIZE], FruitPos * fp);
int Game_RemoveFruit(MapData map[MAP_SIZE][MAP_SIZE], FruitPos * fp);