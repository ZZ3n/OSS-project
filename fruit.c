#pragma once
#include "const.h"
#include "fruit.h"
#include "game.h"


extern const int MAP_SIZE;
extern const int EMPTY;
extern const int FRUIT;

int Game_DrawFruit(MapData map[22][22], FruitPos * fp) {
	// i,j >0  &&  i,j < MAP_SIZE-1i
	HANDLE  hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	srand((unsigned int)time(NULL));
	while (1) {
		i = rand() % (MAP_SIZE - 2) + 1;
		j = rand() % (MAP_SIZE - 2) + 1;
		if (map[i][j] == EMPTY) {
			map[i][j] = FRUIT;
			fp->x = i;
			fp->y = j;
			(fp->numOfFruit)++;
			SetConsoleTextAttribute(hand, 10);
			gotoxy(i, j);
			//print ¡Ú
			printf("\u2605");
			SetConsoleTextAttribute(hand, 7);

			return 1;
		}
	}
}

int Game_DrawSpecial(MapData map[22][22], FruitPos * fp) {
	// i,j >0  &&  i,j < MAP_SIZE-1i
	HANDLE  hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	srand((unsigned int)time(NULL));
	while (1) {
		i = rand() % (MAP_SIZE - 2) + 1;
		j = rand() % (MAP_SIZE - 2) + 1;
		if (map[i][j] == EMPTY) {
			map[i][j] = FRUIT;
			fp->x = i;
			fp->y = j;
			(fp->numOfFruit)++;
			SetConsoleTextAttribute(hand, 12);
			gotoxy(i, j);
			//print ¡Ú
			printf("\u2605");
			SetConsoleTextAttribute(hand, 7);

			return 1;
		}
	}
}

int Game_RemoveFruit(MapData map[22][22], FruitPos * fp) {
	HANDLE  hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;
	i = fp->x;
	j = fp->y;

	if (map[i][j] == FRUIT) {
		map[i][j] = EMPTY;
		(fp->numOfFruit)--;
		SetConsoleTextAttribute(hand, 10);
		gotoxy(i, j);
		printf("  ");
		SetConsoleTextAttribute(hand, 7);
		return 1;
	}

	return 0;
}
