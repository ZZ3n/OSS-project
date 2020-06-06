#pragma once
#include "basic.h"

int isColWithTail(MapData map[22][22], SnakePos * snakePos, int way);
int isColWithWall(MapData map[22][22], SnakePos * sp, int way);
int isColWithFruit(SnakePos * sp, FruitPos * fp);
int isCollision(int state);