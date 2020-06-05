#pragma once
#include "const.h"
#include "map.h"
#include "game.h"

extern const int MAP_SIZE;

extern const int DEFAULT_X;
extern const int DEFAULT_Y;

extern const int EMPTY;
extern const int WALL;

//show start menu
int Map_MenuDrawStart(void) {
	// SetConsoleTextAttribute()�Լ����� ���� �����Ǵ�  �����ڵ� ����, �ʱ�ȭ
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
	//  Ű�� 's'�� 't'�� �Է� �� �� ���� ���� �����̸� ǥ���ϰ� �ϵ��� �ϴ� while��
	while (1)
	{
		// Ű �Է¹��� �� ���� getKeyDown()�Լ� ȣ���ؼ� keyDown������ ����
		int keyDown = getKeyDown();
		// ���� ����
		if (keyDown == 's' || keyDown == 'S')
		{
			SetConsoleTextAttribute(hand, 7);
			return TRUE;
		}
		// ���� ����
		if (keyDown == 't' || keyDown == 'T')
		{
			SetConsoleTextAttribute(hand, 7);
			return FALSE;
		}
		/*
		"-- press 's' to start --" ���ڰ� �����Ÿ��� ��ó�� ǥ�� �ϱ� ���� Sleep()�Լ��� ����
		���ڿ� ��ĭ�� ������ ���� �Ѵ�.
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
SetConsoleTextAttribute(hand, 11); // �ܼ� ��ũ�� ���ۿ� �������� �ؽ�Ʈ���� �Ӽ� �����ϴ� �Լ�
�Ű����� - ��ũ�� ������ �ڵ�, ���� ���� ���� ��������(1~15)
Sleep()�Լ��� �����ð� ���� �۾��� ����(wait)�ϰ� ���� �� ����.
�ڵ� https://m.blog.naver.com/sharonichoya/220873844942
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

	while (1)
	{
		int keyDown = getKeyDown();
		if (keyDown == '1')
		{
			SetConsoleTextAttribute(hand, 7);
			return 1;
		}
		if (keyDown == '2')
		{
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
	// 'score.txt' ���� �б����� ������ ����, ��������  �����ͺ���
	FILE * readfp;
	int errCode;
	errCode = fopen_s(&readfp, "score.txt", "r");

	// ������ ���� �� ���� ��� 'score.txt' ������ ���� ����.
	if (readfp == NULL)
	{
		//���� ����
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
	// Score �о� ��.
	fscanf_s(readfp, "%d %d %d %d %d %d %d %d", &scoreArr[0], &scoreArr[1], &scoreArr[2], &scoreArr[3], &scoreArr[4], &scoreArr[5], &scoreArr[6], &scoreArr[7]);

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
	}// �ְ� ���� ����.

	fclose(readfp);

	//�������� ����
	while (1)
	{
		int keyDown = getKeyDown();
		if (keyDown == '1')
		{
			SetConsoleTextAttribute(hand, 7);
			return 1;
		}
		if (keyDown == '2')
		{
			SetConsoleTextAttribute(hand, 7);
			return 2;
		}
		if (keyDown == '3')
		{
			SetConsoleTextAttribute(hand, 7);
			return 3;
		}
		if (keyDown == '4')
		{
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
//stageOneInit~ stageFourInit ������ �Լ���  drawMainMap���� �ٷ� ���� �׸� �� �ְ� �̸� WALL�� ���� ������ ������

// stage 1�� �� ������ �Լ� <�׸� ��>
void Map_GamemapInitStage1(MapData map[22][22]) {
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

// stage 2�� �� ������ �Լ� < �׸� ���� �߰��� ��>
void Map_GamemapInitStage2(MapData map[22][22]) {
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

// stage 3�� �� ������ �Լ� < ���� ��>
void Map_GamemapInitStage3(MapData map[22][22]) {
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

// stage 4�� �� ������ �Լ� < ũ�ν� ��>
void Map_GamemapInitStage4(MapData map[22][22]) {
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

//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// D R A W ////////////////////////////////////////

//draw game map
void Map_GamemapDrawWall(MapData map[22][22]) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 15);

	int i, j;
	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == WALL)
			{
				gotoxy(i, j);
				//print ��
				printf("\u25A0");
			}
			else if (map[i][j] == EMPTY)
			{
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
