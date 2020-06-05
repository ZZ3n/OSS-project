#pragma once
#include "collision.h"
#include "const.h"
#include "fruit.h"
#include "game.h"
#include "map.h"
#include "queue.h"
#include "snake.h"

extern const int MAP_SIZE;

extern const int DEFAULT_X;
extern const int DEFAULT_Y;

extern const int NORMAL;

extern const int RIGHT;
extern const int LEFT;
extern const int DOWN;
extern const int UP;

extern const int GREEN;
extern const int RED;

///////////////////////////////////////////////////////////////////////////

/*
getKeyDown function is checking keyboard input through _kbhit()
return value is keyboard input
*/
int getKeyDown(void) {
	if (_kbhit())
	{
		return _getch();
	}
	return -1;
}

/*
Console cursor move to (x,y)
*/
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = (short)(2 * x);
	Pos.Y = (short)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

/*
Hide cursor before game start
*/
void hidecursor(void) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
/*
Ignore input key that reverse to peviousKey
*/
int isOverlap(int previousKey, int key) {
	if (previousKey == UP && key == DOWN)
	{
			return TRUE;
	}
	if (previousKey == DOWN && key == UP)
	{
			return TRUE;
	}
	if (previousKey == LEFT && key == RIGHT)
	{
		return TRUE;
	}
	if (previousKey == RIGHT && key == LEFT)
	{
		return TRUE;
	}
	return FALSE;
}

/*
Delete all queue and record best score
When game ends, call this function
*/
void Game_GameOver(int mode, int score, int best, Queue *pq, int stage, int * scoreArr) {
	FILE * wfp;
	int errCode;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	if (mode == 1)
	{
		if (score >= best)
		 {
			scoreArr[stage - 1] = score;
		}
		else
		{
			scoreArr[stage - 1] = best;
		}
	}
	else
	{
		if (score >= best) {
			scoreArr[stage - 1 + 4] = score;
		}
		else {
			scoreArr[stage - 1 + 4] = best;
		}
	}
	errCode = fopen_s(&wfp, "score.txt", "w");

	fprintf(wfp, "%d %d %d %d %d %d %d %d", scoreArr[0], scoreArr[1], scoreArr[2], scoreArr[3], scoreArr[4], scoreArr[5], scoreArr[6], scoreArr[7]);
	fclose(wfp);

	SetConsoleTextAttribute(hand, 14);
	gotoxy(MAP_SIZE / 2 - 4, MAP_SIZE / 2 - 5);
	printf("===<GAME OVER>===\n");
	gotoxy(MAP_SIZE / 2 - 3, MAP_SIZE / 2 - 3);
	printf("Your Score : %d\n", score);
	gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);
	printf("\n");
	SetConsoleTextAttribute(hand, 7);

	// Delete all queue
	while (!isEmpty(pq))
	{
		Dequeue(pq);
	}
}

/*
Main game loop
*/
void Game_Start(MapData map[22][22], int stage, int * scoreArr, int mode) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	SnakePos snakeHead = { 22 / 4 - 2, 22 / 4 + 1 };
	SnakePos snakeNeck;
	SnakePos snakeTail;
	FruitPos fruit;

	Queue queue;

	int previousKey = 0;
	int key = 0;
	int bestScore = 0;
	int score = 0;

	unsigned int repeatTimes = 0;
	double wholeTime = 120 * 1000;

	double refreshInterval = 1200;
	int innerTimer = 0;

	// special fruit exist = 1 , nonexist = 0
	int specialFruit = FALSE;
	// special fruit appear time = 1
	int specialTime = FALSE;

	int removeTail = FALSE;

	QueueInit(&queue);
	fruit.numOfFruit = 0;

	//Choose best score array
	if (mode == 1)
	{
		bestScore = scoreArr[stage - 1];
	}
	else
	{
		bestScore = scoreArr[stage - 1 + 4];
	}
	// Stage init
	if (stage == 1)
	{
		Map_GamemapInitStage1(map);
	}
	else if (stage == 2)
	{
		Map_GamemapInitStage2(map);
	}
	else if (stage == 3)
	{
		Map_GamemapInitStage3(map);
	}
	else
	{
		Map_GamemapInitStage4(map);
	}

	Map_GamemapDrawWall(map);
	Game_PlayDrawHead(map, snakeHead.x, snakeHead.y);

	while (1)
	{
		//Console refresh
		Sleep(refreshInterval / (DWORD)NORMAL); // 1200 / 10 = 0.12sec
		innerTimer++;
		//Minimal interval => 500
		if (refreshInterval >= 500)
		{
			if ((refreshInterval * innerTimer) >= 150000)
			{
				refreshInterval -= 150;
				innerTimer = 0;
				specialTime = TRUE;
			}
		}

		// Draw fruit
		if (specialTime == TRUE)
		{
			// If special fruit nonexist
			if (specialFruit == FALSE)
			{
				// If normal fruit exist
				if (fruit.numOfFruit == 1)
				{
					// Normal fruit delete
					Game_RemoveFruit(map, &fruit);
				}
				// Make set special fruit
				Game_DrawFruit(map, &fruit, RED);
				specialFruit = TRUE;
			}
			else
			{
				if ((refreshInterval * innerTimer) >= 50000)
				{
					Game_RemoveFruit(map, &fruit);
					specialFruit = FALSE;
					specialTime = FALSE;
				}
			}
		}

		if (fruit.numOfFruit == 0)
		{
			Game_DrawFruit(map, &fruit, GREEN);
		}
		Map_GamemapDrawScoreboard(score, bestScore, stage);

		//Checking collision between snake and fruit
		if (isColWithFruit(&snakeHead, &fruit) == TRUE)
		{
			(fruit.numOfFruit)--;
			// INdicates that the tail collides
			removeTail = FALSE;

			if (specialFruit)
			{
				score += 10;
				specialFruit = FALSE;
				specialTime = FALSE;
			}
			else
			{
				score += 5;
			}
		}

		// Wait for keyboard input
		while (previousKey == 0)
		{
			if (_kbhit() != 0 && _getch() == 224)
			{
				previousKey = _getch();
				key = previousKey;
				break;
			}
		}

		//If key input exist
		if (_kbhit() != 0)
		{
			key = _getch();

			//Game exit
			if (key == 't' || key == 'T')
			{
				return;
			}
			//Game pause
			else if (key == 'p' || key == 'P')
			{
				system("pause");
				//Delete "press any key to continue..."
				gotoxy(DEFAULT_X, MAP_SIZE + 6);
				printf("                                            ");
				gotoxy(DEFAULT_X, DEFAULT_Y);
			}
			// If key is arrowkey
			else if (key == 224)
			{
				key = _getch();
				// Reverse key check
				if (isOverlap(previousKey, key) == TRUE)
				{
					key = previousKey;
				}
			}
			//If key is not t,p,arrow 
			else
			{
				key = previousKey;
			}
		}
		///////////// Snake Move Section

		// Save head position
		snakeNeck = snakeHead;
		previousKey = Game_PlayMoveSnake(map, &snakeHead, key);
		Enqueue(&queue, snakeNeck); 
		Game_PlayDrawTail(map, snakeNeck.x, snakeNeck.y);

		// If snake can't eat fruit
		if (removeTail == TRUE)
		{
			snakeTail = Dequeue(&queue);
			Game_PlayRemoveTail(map, snakeTail.x, snakeTail.y);
		}
		//If snake eat fruit
		else
		{
			removeTail = TRUE;
		}
		// Checking collision (wall, tail)
		if (isCollision(previousKey))
		{
			Game_GameOver(mode, score, bestScore, &queue, stage, scoreArr);
			return;
		}

		//Time limit mode
		if (mode == 2)
		{
			SetConsoleTextAttribute(hand, 15);
			gotoxy(DEFAULT_X, DEFAULT_Y + 25);
			wholeTime = wholeTime - (refreshInterval / 10);
			printf("%.1lf", wholeTime / 1000);

			if (wholeTime <= 0.0)
			{
				gotoxy(1, 1);
				printf(" > Time Over ");
				Game_GameOver(mode, score, bestScore, &queue, stage, scoreArr);
				return;
			}
		}
		repeatTimes++;
	}
}
