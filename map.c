#pragma once
#include "const.h"
#include "map.h"
#include "game.h"

extern const int DEFAULT_X;
extern const int DEFAULT_Y;

extern const int WALL;
extern const int MAP_SIZE;
extern const int EMPTY;

//show start menu
int Map_MenuDrawStart(void) {
	// SetConsoleTextAttribute()함수에서 계속 사용되는  출력핸들 선언, 초기화
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 13);
	gotoxy(DEFAULT_X, DEFAULT_Y);
	printf("============================================");
	SetConsoleTextAttribute(hand, 14);
	printf("================ Snake Game ================");
	SetConsoleTextAttribute(hand, 11);
	printf("============================================");
	SetConsoleTextAttribute(hand, 15);
	gotoxy(DEFAULT_X, DEFAULT_Y + 4);
	printf("> Key  : up, down, left, right,");
	gotoxy(DEFAULT_X, DEFAULT_Y + 5);
	printf("> Exit : 't'");

	gotoxy(DEFAULT_X + 11, DEFAULT_Y + 14);
	printf("<Made by BlockDMask.>");
	gotoxy(DEFAULT_X + 11, DEFAULT_Y + 15);
	printf("<BlockDMask@gmail.com>");


	SetConsoleTextAttribute(hand, 14);
	//  키값 's'나 't'가 입력 될 때 까지 계속 깜빡이며 표시하게 하도록 하는 while문
	while (1) {
		// 키 입력받을 때 마다 getKeyDown()함수 호출해서 keyDown변수에 저장
		int keyDown = getKeyDown();
		// 게임 시작
		if (keyDown == 's' || keyDown == 'S') {
			SetConsoleTextAttribute(hand, 7);
			return TRUE;
		}
		// 게임 종료
		if (keyDown == 't' || keyDown == 'T') {
			SetConsoleTextAttribute(hand, 7);
			return FALSE;
		}
		/*
		"-- press 's' to start --" 글자가 깜빡거리는 것처럼 표현 하기 위해 Sleep()함수를 쓰며
		글자와 빈칸을 번갈아 출력 한다.
		*/
		gotoxy(DEFAULT_X + 5, DEFAULT_Y + 9);
		printf("-- press 's' to start --");
		Sleep(1000 / 3);
		gotoxy(DEFAULT_X + 5, DEFAULT_Y + 9);
		printf("                         ");
		Sleep(1000 / 3);
	}

}

/*
SetConsoleTextAttribute(hand, 11); // 콘솔 스크린 버퍼에 쓰여지는 텍스트들의 속성 설정하는 함수
매개변수 - 스크린 버퍼의 핸들, 글자 색에 대한 상수숫자(1~15)
Sleep()함수는 일정시간 동안 작업을 대기(wait)하고 싶을 때 사용.
핸들 https://m.blog.naver.com/sharonichoya/220873844942
*/
int Map_MenuDrawMode(int *scoreArr)
{
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hand, 11);
	gotoxy(DEFAULT_X, DEFAULT_Y);
	printf("============================================");
	SetConsoleTextAttribute(hand, 14);
	gotoxy(DEFAULT_X, DEFAULT_Y + 1);
	printf("================ CHOOSE MODE ================");
	SetConsoleTextAttribute(hand, 13);
	gotoxy(DEFAULT_X, DEFAULT_Y + 2);
	printf("============================================");
	SetConsoleTextAttribute(hand, 15);


	gotoxy(DEFAULT_X, DEFAULT_Y + 4);
	printf(" Classic Mode      [%d] ", 1);
	gotoxy(DEFAULT_X, DEFAULT_Y + 5);
	printf(" Time Limit Mode   [%d] ", 2);

	while (1) {
		int keyDown = getKeyDown();
		if (keyDown == '1') {
			SetConsoleTextAttribute(hand, 7);
			return 1;
		}
		if (keyDown == '2') {
			SetConsoleTextAttribute(hand, 7);
			return 2;
		}
		SetConsoleTextAttribute(hand, 14);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">> Choose Mode : 1, 2");
		Sleep(1000 / 3);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">>                          ");
		Sleep(1000 / 3);
	}

}

//show stage Menu and score;
int Map_MenuDrawStage(int mode, int * scoreArr) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	int i;
	// 'score.txt' 파일 읽기위한 포인터 변수, 쓰기위한  포인터변수
	FILE * readfp;
	int errCode;
	errCode = fopen_s(&readfp, "score.txt", "r");

	// 게임을 실행 한 적이 없어서 'score.txt' 파일이 없는 경우.
	if (readfp == NULL) {
		//파일 생성
		errCode = fopen_s(&readfp, "score.txt", "w+");
		fclose(readfp);
		errCode = fopen_s(&readfp, "score.txt", "r");
	}
	SetConsoleTextAttribute(hand, 11);
	gotoxy(DEFAULT_X, DEFAULT_Y);
	printf("============================================");
	SetConsoleTextAttribute(hand, 14);
	gotoxy(DEFAULT_X, DEFAULT_Y + 1);
	printf("================ BEST SCORE ================");
	SetConsoleTextAttribute(hand, 13);
	gotoxy(DEFAULT_X, DEFAULT_Y + 2);
	printf("============================================");
	SetConsoleTextAttribute(hand, 15);
	// Score 읽어 옴.
	fscanf_s(readfp, "%d %d %d %d %d %d %d %d", &scoreArr[0], &scoreArr[1], &scoreArr[2], &scoreArr[3], &scoreArr[4], &scoreArr[5], &scoreArr[6], &scoreArr[7]);

	if (mode == 1)
	{
		for (i = 0; i < 4; i++) {
			gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
			printf(" Stage [%d] : %d", i + 1, scoreArr[i]);
		}
	}
	else
	{
		for (i = 0; i < 4; i++) {
			gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
			printf(" Stage [%d] : %d", i + 1, scoreArr[i + 4]);
		}
	}// 최고 점수 출력.

	fclose(readfp);

	//스테이지 선택
	while (1) {
		int keyDown = getKeyDown();
		if (keyDown == '1') {
			SetConsoleTextAttribute(hand, 7);
			return 1;
		}
		if (keyDown == '2') {
			SetConsoleTextAttribute(hand, 7);
			return 2;
		}
		if (keyDown == '3') {
			SetConsoleTextAttribute(hand, 7);
			return 3;
		}
		if (keyDown == '4') {
			SetConsoleTextAttribute(hand, 7);
			return 4;
		}
		SetConsoleTextAttribute(hand, 14);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">> Choose Stage : 1, 2, 3, 4");
		Sleep(1000 / 3);
		gotoxy(DEFAULT_X, DEFAULT_Y + 9);
		printf(">>                          ");
		Sleep(1000 / 3);
	}

}


//////////////////////////////////////STAGE MAP SETTING////////////////////////////////
//stageOneInit~ stageFourInit 까지의 함수는  drawMainMap에서 바로 맵을 그릴 수 있게 미리 WALL이 생길 공간을 지정함

// stage 1의 맵 만드는 함수 <네모 벽>
void Map_GamemapInitStage1(MapData map[22][22]) {
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		if (i == 0 || i == MAP_SIZE - 1) {
			for (j = 0; j < MAP_SIZE; j++) {
				map[i][j] = WALL;
			}
		}
		else {
			for (j = 0; j < MAP_SIZE; j++) {
				if (j == 0 || j == MAP_SIZE - 1)
					map[i][j] = WALL;
				else
					map[i][j] = EMPTY;
			}
		}
	}
}

// stage 2의 맵 만드는 함수 < 네모 벽에 중간에 벽>
void Map_GamemapInitStage2(MapData map[22][22]) {
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (i == (int)MAP_SIZE / 2 || j == 0 || j == MAP_SIZE - 1) {
				map[i][j] = WALL;
			}
			else {
				map[i][j] = EMPTY;
			}
		}

	}
}

// stage 3의 맵 만드는 함수 < 십자 벽>
void Map_GamemapInitStage3(MapData map[22][22]) {
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (i == MAP_SIZE / 2 || j == MAP_SIZE / 2) {
				map[i][j] = WALL;
			}
			else {
				map[i][j] = EMPTY;
			}
		}
	}
}

// stage 4의 맵 만드는 함수 < 크로스 벽>
void Map_GamemapInitStage4(MapData map[22][22]) {
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (i == j || i + j == MAP_SIZE - 1) {
				if (i == MAP_SIZE / 2 - 1 || i == MAP_SIZE / 2)
					map[i][j] = EMPTY;
				else
					map[i][j] = WALL;

			}
			else {
				map[i][j] = EMPTY;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// D R A W ////////////////////////////////////////

//draw game map
void Map_GamemapDrawWall(MapData map[22][22]) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 15);

	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == WALL) {
				gotoxy(i, j);
				//print ■
				printf("\u25A0");
			}
			else if (map[i][j] == EMPTY) {
				gotoxy(i, j);
				printf(" ");
			}
		}
	}
	SetConsoleTextAttribute(hand, 7);
}

void Map_GamemapDrawScoreboard(int score, int best, int stage) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 15);

	gotoxy(DEFAULT_X, MAP_SIZE + 1);
	printf(" Stage[%d] Best Score : %4d", stage, best);
	gotoxy(DEFAULT_X, MAP_SIZE + 2);
	printf(" Stage[%d] Your Score : %4d", stage, score);
	gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);
	printf("[Exit - 't' / Pause - 'p']\n");
	SetConsoleTextAttribute(hand, 7);


}
