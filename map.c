#pragma once
#include "basic.h"
#include "map.h"
#include "game.h"

extern const int MAP_SIZE;

extern const int DEFAULT_X;
extern const int DEFAULT_Y;

extern const int EMPTY;
extern const int WALL;

extern const int LIGHTMAGENTA;
extern const int YELLOW;
extern const int LIGHTCYAN;
extern const int WHITE;
extern const int LIGHTGRAY;

/*
Draw start menu
*/
int Map_MenuDrawStart(void) 
{
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int keyDown = 0;

	SetConsoleTextAttribute(hand, LIGHTMAGENTA);
	gotoxy(DEFAULT_X, DEFAULT_Y);
	printf("============================================");
	SetConsoleTextAttribute(hand, YELLOW);
	printf("================ Snake Game ================");
	SetConsoleTextAttribute(hand, LIGHTCYAN);
	printf("============================================");
	SetConsoleTextAttribute(hand, WHITE);
	gotoxy(DEFAULT_X, DEFAULT_Y + 4);
	printf("> Key  : up, down, left, right,");
	gotoxy(DEFAULT_X, DEFAULT_Y + 5);
	printf("> Exit : 't'");

	gotoxy(DEFAULT_X + 11, DEFAULT_Y + 14);
	printf("<Made by BlockDMask.>");
	gotoxy(DEFAULT_X + 11, DEFAULT_Y + 15);
	printf("<BlockDMask@gmail.com>");

	SetConsoleTextAttribute(hand, YELLOW);

	// Blinking console output
	while (keyDown != 't')
	{
		// Key input
		keyDown = getKeyDown();
		SetConsoleTextAttribute(hand, LIGHTGRAY);

		// Game start
		if (keyDown == 's' || keyDown == 'S')
		{
			return TRUE;
		}
		// Game exit
		if (keyDown == 't' || keyDown == 'T')
		{
			return FALSE;
		}

		/*
		Blinking "-- press 's' to start --" 
		*/
		gotoxy(DEFAULT_X + 5, DEFAULT_Y + 9);
		printf("-- press 's' to start --");
		Sleep(1000 / 3);
		gotoxy(DEFAULT_X + 5, DEFAULT_Y + 9);
		printf("                           ");
		Sleep(1000 / 3);
	}
	return FALSE;
}

/*
Draw mode menu
*/
int Map_MenuDrawMode(void)
{
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int keyDown = 0;

	SetConsoleTextAttribute(hand, LIGHTCYAN);
	gotoxy(DEFAULT_X, DEFAULT_Y);
	printf("============================================");
	SetConsoleTextAttribute(hand, YELLOW);
	gotoxy(DEFAULT_X, DEFAULT_Y + 1);
	printf("================ CHOOSE MODE ================");
	SetConsoleTextAttribute(hand, LIGHTMAGENTA);
	gotoxy(DEFAULT_X, DEFAULT_Y + 2);
	printf("============================================");
	SetConsoleTextAttribute(hand, WHITE);

	gotoxy(DEFAULT_X, DEFAULT_Y + 4);
	printf(" Classic Mode      [%d] ", 1);
	gotoxy(DEFAULT_X, DEFAULT_Y + 5);
	printf(" Time Limit Mode   [%d] ", 2);

	while (keyDown != '1' && keyDown != '2')
	{
		keyDown = getKeyDown();
		SetConsoleTextAttribute(hand, LIGHTGRAY);

		//Classic mode
		if (keyDown == '1')
		{
			return 1;
		}
		//Time limit mode
		if (keyDown == '2')
		{
			return 2;
		}

		SetConsoleTextAttribute(hand, YELLOW);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">> Choose Mode : 1, 2");
		Sleep(1000 / 3);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">>                          ");

		Sleep(1000 / 3);
	}
}

//show stage Menu and score;
int Map_MenuDrawStage(int mode, int * scoreArr) 
{
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	//Pointer that associated to 'score.txt' 
	FILE * readfp;

    int keyDown = 0;
	int i;

	int errCode;
	errCode = fopen_s(&readfp, "score.txt", "r");

	// If doesn't exist "score.txt"
	if (readfp == NULL)
	{
		//Create file
		errCode = fopen_s(&readfp, "score.txt", "w+");
		fclose(readfp);
		errCode = fopen_s(&readfp, "score.txt", "r");
	}

	SetConsoleTextAttribute(hand, LIGHTCYAN);
	gotoxy(DEFAULT_X, DEFAULT_Y);
	printf("============================================");
	SetConsoleTextAttribute(hand, YELLOW);
	gotoxy(DEFAULT_X, DEFAULT_Y + 1);
	printf("================ BEST SCORE ================");
	SetConsoleTextAttribute(hand, LIGHTMAGENTA);
	gotoxy(DEFAULT_X, DEFAULT_Y + 2);
	printf("============================================");
	SetConsoleTextAttribute(hand, WHITE);

	// Read "score.txt"
	fscanf_s(readfp, "%d %d %d %d %d %d %d %d", &scoreArr[0], &scoreArr[1], &scoreArr[2], &scoreArr[3], &scoreArr[4], &scoreArr[5], &scoreArr[6], &scoreArr[7]);

	// Print best score by mode
	if (mode == 1)
	{
		for (i = 0; i < 4; i++)
		{
			gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
			printf(" Stage [%d] : %d", i + 1, scoreArr[i]);
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
			printf(" Stage [%d] : %d", i + 1, scoreArr[i + 4]);
		}
	}

	fclose(readfp);

	//Choose stage
	while (keyDown < '1' || keyDown > '4')
	{
		keyDown = getKeyDown();
		SetConsoleTextAttribute(hand, LIGHTGRAY);

		if (keyDown == '1')
		{
			return 1;
		}
		if (keyDown == '2')
		{
			return 2;
		}
		if (keyDown == '3')
		{
			return 3;
		}
		if (keyDown == '4')
		{
			return 4;
		}

		SetConsoleTextAttribute(hand, YELLOW);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">> Choose Stage : 1, 2, 3, 4");
		Sleep(1000 / 3);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">>                          ");

		Sleep(1000 / 3);
	}
}

// Stage 1 create and init(Square shape) { 22 = MAP_SIZE }
void Map_GamemapInitStage1(MapData map[22][22]) 
{
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		if (i == 0 || i == MAP_SIZE - 1)
		{
			for (j = 0; j < MAP_SIZE; j++)
			{
				map[i][j] = WALL;
			}
		}
		else {
			for (j = 0; j < MAP_SIZE; j++)
			{
				if (j == 0 || j == MAP_SIZE - 1)
				{
					map[i][j] = WALL;
				}
				else
				{
					map[i][j] = EMPTY;
				}
			}
		}
	}
}

// Stage 2 create and init( ][ shape) { 22 = MAP_SIZE }
void Map_GamemapInitStage2(MapData map[22][22]) 
{
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (i == (int)MAP_SIZE / 2 || j == 0 || j == MAP_SIZE - 1)
			{
				map[i][j] = WALL;
			}
			else
			{
				map[i][j] = EMPTY;
			}
		}

	}
}

// Stage 3 create and init(+ shape) { 22 = MAP_SIZE }
void Map_GamemapInitStage3(MapData map[22][22]) 
{
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (i == MAP_SIZE / 2 || j == MAP_SIZE / 2)
			{
				map[i][j] = WALL;
			}
			else
			{
				map[i][j] = EMPTY;
			}
		}
	}
}

// Stage 4 create and init(X shape) { 22 = MAP_SIZE }
void Map_GamemapInitStage4(MapData map[22][22]) 
{
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (i == j || i + j == MAP_SIZE - 1)
			{
				if (i == MAP_SIZE / 2 - 1 || i == MAP_SIZE / 2)
				{
					map[i][j] = EMPTY;
				}
				else
				{
					map[i][j] = WALL;
				}
			}
			else
			{
				map[i][j] = EMPTY;
			}
		}
	}
}

//Draw game map { 22 = MAP_SIZE }
void Map_GamemapDrawWall(MapData map[22][22]) 
{
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i, j;

	SetConsoleTextAttribute(hand, WHITE);

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == WALL)
			{
				gotoxy(i, j);
				//print filled squre
				printf("\u25A0");
			}
			else if (map[i][j] == EMPTY)
			{
				gotoxy(i, j);
				printf(" ");
			}
		}
	}
	SetConsoleTextAttribute(hand, LIGHTGRAY);
}

/*
Draw score board
*/
void Map_GamemapDrawScoreboard(int score, int best, int stage) 
{
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, WHITE);

	gotoxy(DEFAULT_X, MAP_SIZE + 1);
	printf(" Stage[%d] Best Score : %4d", stage, best);
	gotoxy(DEFAULT_X, MAP_SIZE + 2);
	printf(" Stage[%d] Your Score : %4d", stage, score);
	gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);
	printf("[Exit - 't' / Pause - 'p']\n");
	SetConsoleTextAttribute(hand, LIGHTGRAY);
}
