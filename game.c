#pragma once
#include "collision.h"
#include "const.h"
#include "fruit.h"
#include "game.h"
#include "map.h"
#include "queue.h"
#include "snake.h"

extern const int NORMAL;

extern const int UP;
extern const int DOWN;
extern const int LEFT;
extern const int RIGHT;

extern const int MAP_SIZE;

extern const int DEFAULT_X;
extern const int DEFAULT_Y;

///////////////////////////////////////////////////////////////////////////

/*
_kbhit() 함수는 키보드가 입력되었는지 확인 하는 함수로
입력 버퍼의 내용 확인 해 키 입력 있으면 true 없으면 false 반환
waiting 함수가 아니라 입력이 있든 없든 바로 반환하므로
( 만약 입력 함수를 통해 키의 입력을 확인하려고
입력 함수를 호출한 시점부터 대기 상태에 들어가서 입력이 들어올 때 까지 기다리게 된다)
반환 값에 따라 작업 진행 가능하다

_getch() 함수는 scanf_s()와 비슷하게 입력 받는 함수로 이 함수와 다른 점은 입력한 키보드의 내용이 화면에 출력되지 않는다는 점
또한 enter key 를 통해 입력 확인하는게 아니라 키를 누를 순간 입력 버퍼에 값이 들어가게 함.
_getch()는 정수를 반환한다.

_kbhit(), _getch()는 <conio.h> header include함.
*/
int getKeyDown(void) {
	if (_kbhit()) return _getch();
	return -1;
}

/*
원하는 특정 위치에 출력을 하고 싶을 때 사용하는 함수
SetconsoleCursorPosition()호출하려면  <Windows.h> include.
GetStdHandle()는 실체 핸들을 반환하는 함수로 안에 파라미터로 종류를 정해주면 핸들 값을 반환 함.
- 인자로 STD_OUTPUT_HANDLE를 주면 표준콘솔출력의 핸들 반환.
SetconsoleCursorPosition()는 첫 인자로 핸들 값을 주고 두 번째 인자에는 위치 값을 주면
정해진 위치로 커서가 이동한다.
*/
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = (short)(2 * x);
	Pos.Y = (short)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

/*
콘솔 커서 자체를 숨기는 함수
dwSize 는 커서의 두께 (1~100,얇~두껍)
bVisible는 콘솔에 커서 노출 여부에 대한 변수
SetConsoleCursorInfo()는 지정된 콘솔 스크린 버퍼에 대해 커서의 형태(두께,노출여부)를 설정하는 역할
매개변수 : 콘솔 스크린 버퍼에 대한 핸들, CONSOLE_CURSOR_INFO 구조체 넘김
*/
void hidecursor(void) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int isOverlap(int savedKey, int key) {
	if (savedKey == UP && key == DOWN)
		return TRUE;
	if (savedKey == DOWN && key == UP)
		return TRUE;
	if (savedKey == LEFT && key == RIGHT)
		return TRUE;
	if (savedKey == RIGHT && key == LEFT)
		return TRUE;

	return FALSE;
}

/*
스테이지별 최고점수를 기록하고, Queue를 전부 지움.
*/
void Game_GameOver(int mode, int score, int best, Queue *pq, int stage, int * scoreArr) {
	FILE * wfp;
	int errCode;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	if (mode == 1)
	{
		if (score >= best) {
			scoreArr[stage - 1] = score;
		}
		else {
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

	while (!isEmpty(pq)) { // 큐를 전부 삭제.
		Dequeue(pq);
	}
}

void Game_Start(MapData map[22][22], int stage, int * scoreArr, int mode) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int bestScore = 0;
	int score = 0;
	int key = 0, previousKey = 0;
	unsigned int repeatTimes = 0;
	Queue queue;
	SnakePos snakeHead = { MAP_SIZE / 4 - 2, MAP_SIZE / 4 + 1 };
	SnakePos snakeNeck;
	SnakePos snakeTail;
	int removeTail = FALSE;
	FruitPos fruit;
	double refreshInterval = 1200;

	int innerTimer = 0;
	// special fruit exist = 1 , nonexist = 0
	int specialFruit = FALSE;
	// special fruit appear time = 1
	int specialTime = FALSE;
	double wholeTime = 120 * 1000;
	QueueInit(&queue);
	fruit.numOfFruit = 0;
	//모드 선택에 따른 스코어 배열 선택
	if (mode == 1)
	{
		bestScore = scoreArr[stage - 1];
	}
	else
	{
		bestScore = scoreArr[stage - 1 + 4];
	}
	// 선택된 맵을 그림.
	if (stage == 1) {
		Map_GamemapInitStage1(map);
	}
	else if (stage == 2) {
		Map_GamemapInitStage2(map);
	}
	else if (stage == 3) {
		Map_GamemapInitStage3(map);
	}
	else {
		Map_GamemapInitStage4(map);
	}
	Map_GamemapDrawWall(map);
	Game_PlayDrawHead(map, snakeHead.x, snakeHead.y);

	while (1) {
		//화면 갱신 속도
		Sleep(refreshInterval / (DWORD)NORMAL); // 1200 / 10 = 0.12sec
		innerTimer++;
		//최소 interval => 500
		if (refreshInterval >= 500) {
			if ((refreshInterval * innerTimer) >= 150000) {
				refreshInterval -= 150;
				innerTimer = 0;
				specialTime = TRUE;
			}
		}

		// draw fruit
		if (specialTime == TRUE) {
			if (specialFruit == FALSE) { // if special fruit nonexist
				if (fruit.numOfFruit == 1) { // if normal fruit exist
					Game_RemoveFruit(map, &fruit); // normal fruit delete
				}
				Game_DrawSpecial(map, &fruit); // make set special fruit
				specialFruit = TRUE; //
			}
			else {
				if ((refreshInterval * innerTimer) >= 50000) {
					Game_RemoveFruit(map, &fruit);
					specialFruit = FALSE;
					specialTime = FALSE;
				}
			}
		}

		if (fruit.numOfFruit == 0) {
			Game_DrawFruit(map, &fruit);
		}
		Map_GamemapDrawScoreboard(score, bestScore, stage);

		//과일과 뱀의 충돌
		if (isColWithFruit(&snakeHead, &fruit) == TRUE) {
			(fruit.numOfFruit)--; //갯수 줄임.
			removeTail = FALSE;	// 변수 설정.

			if (specialFruit) {
				score += 10;
				specialFruit = 0;
				specialTime = 0;
			}
			else {
				score += 5; // 점수 + .
			}
		}

		// 처음 키 입력을 기다림.
		while (previousKey == 0) {
			if (_kbhit() != 0 && _getch() == 224) {
				previousKey = _getch();
				key = previousKey;
				break;
			}
		}

		//키 누를 시!
		if (_kbhit() != 0) {
			//키 입력받음
			key = _getch();
			//게임 종료
			if (key == 't' || key == 'T') {
				return;
			}
			//게임 멈춤.
			else if (key == 'p' || key == 'P') {

				system("pause");
				//	'아무키나 누르시오' 지움.
				gotoxy(DEFAULT_X, MAP_SIZE + 6);
				printf("                                            ");
				gotoxy(DEFAULT_X, DEFAULT_Y);
			}
			// 키 값이 방향키이면
			else if (key == 224) {
				//방향 입력받음.
				key = _getch();
				// 이전 방향과 반대일시 무시하고, 키 값 저장.
				if (isOverlap(previousKey, key) == TRUE) {
					key = previousKey;
				}
			}
			else { // not (t,p,arrow)
				key = previousKey;
			}

		}
		///////////// Snake Move Section

		// 머리는 움직일 것이니 머리부분을 저장함.
		snakeNeck = snakeHead;
		previousKey = Game_PlayMoveSnake(map, &snakeHead, key);
		Enqueue(&queue, snakeNeck); // 큐에 뱀머리였던 위치를 넣음.
		Game_PlayDrawTail(map, snakeNeck.x, snakeNeck.y);

		// 과일을 먹지못했다면,
		if (removeTail == TRUE) {
			snakeTail = Dequeue(&queue);
			Game_PlayRemoveTail(map, snakeTail.x, snakeTail.y);
		}
		//과일을 먹었다면, ( 뱀 꼬리를 지우지 않음. )
		else {
			removeTail = TRUE;
		}
		// 충돌 변수 체크. 게임 오버
		if (isCollision(previousKey)) {
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