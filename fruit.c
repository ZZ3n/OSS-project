#pragma once
#include "basic.h"
#include "fruit.h"
#include "game.h"

extern const int MAP_SIZE;

extern const int EMPTY;
extern const int FRUIT;

extern const int LIGHTGREEN;
extern const int LIGHTGRAY;

/*
Draw fruit
*/
int Game_DrawFruit(MapData map[22][22], FruitPos * fp, int color) 
{
	// i,j >0  &&  i,j < MAP_SIZE-1i
	HANDLE  hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i=0, j=0;

	srand((unsigned int)time(NULL));
	while (fp->numOfFruit < 1)
	{
		i = rand() % (MAP_SIZE - 2) + 1;
		j = rand() % (MAP_SIZE - 2) + 1;

		if (map[i][j] == EMPTY)
		{
			map[i][j] = FRUIT;
			fp->x = i;
			fp->y = j;
			(fp->numOfFruit)++;

			SetConsoleTextAttribute(hand, color);
			gotoxy(i, j);
			//Print star
			printf("\u2605");
			SetConsoleTextAttribute(hand, LIGHTGRAY);
			return 1;
		}
	}
}

/*
Remove Fruit
*/
int Game_RemoveFruit(MapData map[22][22], FruitPos * fp) 
{
	HANDLE  hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;

	i = fp->x;
	j = fp->y;

	if (map[i][j] == FRUIT)
	{
		map[i][j] = EMPTY;
		(fp->numOfFruit)--;

		SetConsoleTextAttribute(hand, LIGHTGREEN);
		gotoxy(i, j);
		printf("  ");
		SetConsoleTextAttribute(hand, LIGHTGRAY);
		return 1;
	}
	return 0;
}
