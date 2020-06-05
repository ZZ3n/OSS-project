#pragma once
#include "const.h"
#include "collision.h"
#include "snake.h"

extern const int COLLISION;

extern const int TAIL;

extern const int WALL;

extern const int RIGHT;
extern const int LEFT;
extern const int DOWN;
extern const int UP;

int isColWithTail(MapData map[22][22], SnakePos * snakePos, int way) {
	if (way == UP)
	{
		if (map[snakePos->x][Game_PlayPredictHead(snakePos->y, way)] == TAIL)
		{
			return TRUE;
		}
	}
	if (way == DOWN)
	{
		if (map[snakePos->x][Game_PlayPredictHead(snakePos->y, way)] == TAIL)
			return TRUE;
	}
	if (way == LEFT) {
		if (map[Game_PlayPredictHead(snakePos->x, way)][snakePos->y] == TAIL)
		{
			return TRUE;
		}
	}
	if (way == RIGHT)
	{
		if (map[Game_PlayPredictHead(snakePos->x, way)][snakePos->y] == TAIL)
		{
			return TRUE;
		}
	}
	return FALSE;
}

int isColWithWall(MapData map[22][22], SnakePos * sp, int way) {
	if (way == UP)
	{
		if (map[sp->x][Game_PlayPredictHead(sp->y, way)] == WALL)
		{
			return TRUE;
		}
	}
	if (way == DOWN)
	{
		if (map[sp->x][Game_PlayPredictHead(sp->y, way)] == WALL)
		{
			return TRUE;
		}
	}
	if (way == LEFT)
	{
		if (map[Game_PlayPredictHead(sp->x, way)][sp->y] == WALL)
		{
			return TRUE;
		}
	}
	if (way == RIGHT)
	{
		if (map[Game_PlayPredictHead(sp->x, way)][sp->y] == WALL)
		{
			return TRUE;
		}
	}
	return FALSE;
}

// sp�� fp �ܼ� �񱳷� �浹 üũ
int isColWithFruit(SnakePos * sp, FruitPos * fp) {
	//meet;->x == fp->x
	if ((sp->x == fp->x) && (sp->y == fp->y))
	{
		return TRUE;
	}
	return FALSE;
}

/*	savedKey�� COLLISION���� �����Ǿ��ִ��� üũ
if (state == COLLISION) return TRUE;
*/
int isCollision(int state) {
	if (state == COLLISION)
	{
		return TRUE;
	}
	return FALSE;
}
