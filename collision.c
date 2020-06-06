#pragma once
#include "basic.h"
#include "collision.h"
#include "snake.h"

extern const int COLLISION;

extern const int TAIL;

extern const int WALL;

extern const int RIGHT;
extern const int LEFT;
extern const int DOWN;
extern const int UP;

/*
Checking collision with tail
*/
int isColWithTail(MapData map[22][22], SnakePos * snakePos, int way) 
{
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
	if (way == LEFT) 
	{
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

/*
Checking collision with wall
*/
int isColWithWall(MapData map[22][22], SnakePos * sp, int way) 
{
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

// Checking collision with fruit
int isColWithFruit(SnakePos * sp, FruitPos * fp) 
{
	//meet;->x == fp->x
	if ((sp->x == fp->x) && (sp->y == fp->y))
	{
		return TRUE;
	}
	return FALSE;
}

/*	
Check collision
Collision state saved in previousKey
*/
int isCollision(int previousKey)
{
	if (previousKey == COLLISION)
	{
		return TRUE;
	}
	return FALSE;
}
