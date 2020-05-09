//<V1.0>
//move snake                    o
//collision with wall           o
//collision with itself         o
//collision with fruit          o
//read best score from file.    o
//write best score to file      o
//what about using Queue ?      o
//<V2.0>
//separate tail with head       o
//added collision
//map changing                  o
//<v3.0>

#pragma warning (disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define DEFAULT_X 0
#define DEFAULT_Y 0

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define MAP_SIZE 22

#define WALL 1
#define EMPTY 0
#define HEAD 2
#define TAIL 3
#define FRUIT 5
#define COLLISION 10

#define TRUE 1
#define FALSE 0

#define NORMAL 10

// 2���� �迭 ��
typedef int MData;

// ����� x,y ��ǥ�� ��� ����
typedef struct _fruitxy {
	int x;
	int y;
	int numOfFruit;
} FruitPos;
// snake x,y ��ǥ
typedef struct _snakexp {
	int x;
	int y;
} SnakePos;



///////////////////////////QUEUE//////////////////////////////////////////

//typedef int QData;
typedef struct _mynode {
	SnakePos data;
	struct _mynode *next;
} Node;

typedef struct _myqueue {
	Node * rear;
	Node * front;
} MyQueue;
/*	front�� �ո� ����Ŵ. rear�� �ڸ� ����Ŵ.
Queue�� �պκ� := �� ����.
*/
typedef MyQueue Queue;
// ť�� rear�� front�� ���� NULL�� �ʱ�ȭ��.
void QueueInit(Queue * pq) {
	pq->rear = NULL;
	pq->front = NULL;
}

int isEmpty(Queue * pq) {
	if (pq->front == NULL)
		return TRUE;
	else
		return FALSE;
}

/*
Queue* pq�� ť�� ��ġ�� ����
SnakePos data �� ���� ��ġ
*/
void Enqueue(Queue * pq, SnakePos data) {
	Node * newNode = (Node *)malloc(sizeof(Node));
	// data�� ��ġ�� ����
	newNode->data = data;
	newNode->next = NULL;
	// ť�� ������ ó���� ���.
	if (pq->front == NULL) {
		pq->rear = newNode;
		pq->front = newNode;
	}
	// ť�� �޺κп� ��� �߰�.
	else {
		pq->rear->next = newNode;
		pq->rear = newNode;
	}
}
/*
Queue pq�� Dequeue�� ����.
*/
SnakePos Dequeue(Queue * pq) {
	Node * delNode;
	SnakePos delData = { 0,0 };
	// Queue Empty Check
	if (isEmpty(pq)) {
		return delData;
	}
	delNode = pq->front;
	delData = delNode->data;
	pq->front = pq->front->next;
	free(delNode);
	return delData;
}

SnakePos Peek(Queue * pq) {
	return pq->front->data;
}
///////////////////////////////////////////////////////////////////////////

/*
_kbhit() �Լ��� Ű���尡 �ԷµǾ����� Ȯ�� �ϴ� �Լ���
�Է� ������ ���� Ȯ�� �� Ű �Է� ������ true ������ false ��ȯ
waiting �Լ��� �ƴ϶� �Է��� �ֵ� ���� �ٷ� ��ȯ�ϹǷ�
( ���� �Է� �Լ��� ���� Ű�� �Է��� Ȯ���Ϸ���
�Է� �Լ��� ȣ���� �������� ��� ���¿� ���� �Է��� ���� �� ���� ��ٸ��� �ȴ�)
��ȯ ���� ���� �۾� ���� �����ϴ�

_getch() �Լ��� scanf_s()�� ����ϰ� �Է� �޴� �Լ��� �� �Լ��� �ٸ� ���� �Է��� Ű������ ������ ȭ�鿡 ��µ��� �ʴ´ٴ� ��
���� enter key �� ���� �Է� Ȯ���ϴ°� �ƴ϶� Ű�� ���� ���� �Է� ���ۿ� ���� ���� ��.
_getch()�� ������ ��ȯ�Ѵ�.

_kbhit(), _getch()�� <conio.h> header include��.
*/
int getKeyDown(void) {
	if (_kbhit()) return _getch();
	return -1;
}




/*
���ϴ� Ư�� ��ġ�� ����� �ϰ� ���� �� ����ϴ� �Լ�
SetconsoleCursorPosition()ȣ���Ϸ���  <Windows.h> include.
GetStdHandle()�� ��ü �ڵ��� ��ȯ�ϴ� �Լ��� �ȿ� �Ķ���ͷ� ������ �����ָ� �ڵ� ���� ��ȯ ��.
- ���ڷ� STD_OUTPUT_HANDLE�� �ָ� ǥ���ܼ������ �ڵ� ��ȯ.
SetconsoleCursorPosition()�� ù ���ڷ� �ڵ� ���� �ְ� �� ��° ���ڿ��� ��ġ ���� �ָ�
������ ��ġ�� Ŀ���� �̵��Ѵ�.
*/
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = (short)(2 * x);
	Pos.Y = (short)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}



/*
�ܼ� Ŀ�� ��ü�� ����� �Լ�
dwSize �� Ŀ���� �β� (1~100,��~�β�)
bVisible�� �ֿܼ� Ŀ�� ���� ���ο� ���� ����
SetConsoleCursorInfo()�� ������ �ܼ� ��ũ�� ���ۿ� ���� Ŀ���� ����(�β�,���⿩��)�� �����ϴ� ����
�Ű����� : �ܼ� ��ũ�� ���ۿ� ���� �ڵ�, CONSOLE_CURSOR_INFO ����ü �ѱ�
*/
void hidecursor(void) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


//show start menu
int drawStartMenu(void) {
	// SetConsoleTextAttribute()�Լ����� ��� ���Ǵ�  ����ڵ� ����, �ʱ�ȭ
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
	//  Ű�� 's'�� 't'�� �Է� �� �� ���� ��� �����̸� ǥ���ϰ� �ϵ��� �ϴ� while��
	while (1) {
		// Ű �Է¹��� �� ���� getKeyDown()�Լ� ȣ���ؼ� keyDown������ ����
		int keyDown = getKeyDown();
		// ���� ����
		if (keyDown == 's' || keyDown == 'S') {
			SetConsoleTextAttribute(hand, 7);
			return TRUE;
		}
		// ���� ����
		if (keyDown == 't' || keyDown == 'T') {
			SetConsoleTextAttribute(hand, 7);
			return FALSE;
		}
		/*
		"-- press 's' to start --" ���ڰ� �����Ÿ��� ��ó�� ǥ�� �ϱ� ���� Sleep()�Լ��� ����
		���ڿ� ��ĭ�� ������ ��� �Ѵ�.
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
�Ű����� - ��ũ�� ������ �ڵ�, ���� ���� ���� �������(1~15)
Sleep()�Լ��� �����ð� ���� �۾��� ���(wait)�ϰ� ���� �� ���.
�ڵ� https://m.blog.naver.com/sharonichoya/220873844942
*/

//show stage Menu and score;
int drawSpeedMenu(int * scoreArr) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	int i;
	// 'score.txt' ���� �б����� ������ ����, ��������  �����ͺ���
	FILE * rfp, *wfp;
	int errCode;
	errCode = fopen_s(&rfp, "score.txt", "r");

	// ������ ���� �� ���� ��� 'score.txt' ������ ���� ���.
	if (rfp == NULL) {
		errCode = fopen_s(&rfp, "score.txt", "w+");
		fclose(rfp);
		errCode = fopen_s(&rfp, "score.txt", "r");
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

	if (errCode != 0) { // ������ �� ������ �ʾ��� ���.
						//�� ���� ����
		errCode = fopen_s(&wfp, "score.txt", "w");
		// �ְ���� �ʱ�ȭ.
		fprintf(wfp, "%d %d %d %d", scoreArr[0], scoreArr[1], scoreArr[2], scoreArr[3]);
		for (i = 0; i<4; i++) {
			gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
			printf(" Stage [%d] : %d", i + 1, scoreArr[i]);
		}
		fclose(wfp);
	}
	// Score �о� ��.
	fscanf_s(rfp, "%d %d %d %d", &scoreArr[0], &scoreArr[1], &scoreArr[2], &scoreArr[3]);

	for (i = 0; i<4; i++) {
		gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
		printf(" Stage [%d] : %d", i + 1, scoreArr[i]);
	} // �ְ� ���� ���.

	fclose(rfp);
	//�������� ����
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

// HANDLE �� �ü���� ���� ������ ���ҽ��� ������Ʈ�� �����ϱ� ���� 32bit�� ������
//  GetStdHandle()�� ��ü �ڵ��� ��ȯ�ϴ� �Լ��� �ȿ� �Ķ���ͷ� ������ �����ָ� �ڵ� ���� ��ȯ ��.
//      - ���ڷ� STD_OUTPUT_HANDLE�� �ָ� ǥ���ܼ������ �ڵ� ��ȯ.
// HANDLE�� ����ü�� �޸��Ҵ�� �̿� ���� ������ ���ؼ� �Լ�ȣ�⿡ ����ϴ� �Ͱ� ����ϴ�
// �ٸ� ���� �ü���� ��Ÿ �ý��� ���α׷�ó�� ����ü ������ ������ ���� ���Ϸ��ϰų� ���α׷��ӿ��� �ϰ���
//    ���α׷��� ȯ���� �����ϱ� ���� ��� �ϴ� ��. ( ���α׷� �Ը� Ŀ���ų� ��������� ���� �۾��� �ϴ� ��� ����)



//////////////////////////////////////STAGE MAP SETTING////////////////////////////////
//stageOneInit~ stageFourInit ������ �Լ���  drawMainMap���� �ٷ� ���� �׸� �� �ְ� �̸� WALL�� ���� ������ ������
void stageClear(MData map[MAP_SIZE][MAP_SIZE]) {
	int i, j;
	for (i = 0; i <= MAP_SIZE; i++) {
		for (j = 0; i <= MAP_SIZE; j++) {
			map[i][j] = EMPTY;
		}
	}
}
// stage 1�� �� ����� �Լ� <�׸� ��>
void stageOneInit(MData map[MAP_SIZE][MAP_SIZE]) {
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
// stage 2�� �� ����� �Լ� < �׸� ���� �߰��� ��>
void stageTwoInit(MData map[MAP_SIZE][MAP_SIZE]) {
	int i, j;
	for (i = 0; i<MAP_SIZE; i++) {
		for (j = 0; j<MAP_SIZE; j++) {
			if (i == (int)MAP_SIZE / 2 || j == 0 || j == MAP_SIZE - 1) {
				map[i][j] = WALL;
			}
			else {
				map[i][j] = EMPTY;
			}
		}

	}
}
// stage 3�� �� ����� �Լ� < ���� ��>
void stageThreeInit(MData map[MAP_SIZE][MAP_SIZE]) {
	int i, j;
	for (i = 0; i<MAP_SIZE; i++) {
		for (j = 0; j<MAP_SIZE; j++) {
			if (i == MAP_SIZE / 2 || j == MAP_SIZE / 2) {
				map[i][j] = WALL;
			}
			else {
				map[i][j] = EMPTY;
			}
		}
	}
}
// stage 4�� �� ����� �Լ� < ũ�ν� ��>
void stageFourinit(MData map[MAP_SIZE][MAP_SIZE]) {
	int i, j;
	for (i = 0; i<MAP_SIZE; i++) {
		for (j = 0; j<MAP_SIZE; j++) {
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
void drawMainMap(MData map[MAP_SIZE][MAP_SIZE]) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 15);

	int i, j;
	for (i = 0; i<MAP_SIZE; i++) {
		for (j = 0; j<MAP_SIZE; j++) {
			if (map[i][j] == WALL) {
				gotoxy(i, j);
				printf("��");
			}
			else if (map[i][j] == EMPTY) {
				gotoxy(i, j);
				printf(" ");
			}
		}
	}
	SetConsoleTextAttribute(hand, 7);
}
void drawSubMap(int score, int best, int stage) {
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
/////////////////////////////////////////////////////////////////////////////////////

int setFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos * fp) {
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
			printf("��");
			SetConsoleTextAttribute(hand, 7);

			return 1;
		}
	}
}
// �Ⱦ��̴� �ڵ�
/*
int setBonusFruit(MData map[MAP_SIZE][MAP_SIZE], FruitPos * fp) {
int i, j, numOfFruit = 0;
for (i = 0; i<MAP_SIZE - 1; i++) {
for (j = 0; j<MAP_SIZE; j++) {
if (map[i][j] == EMPTY) {
map[i][j] = FRUIT;
numOfFruit++;
}
}
}
return numOfFruit;
}
*/
//
/*
�ܼ� (x,y) �� Tail("��") �� �׸�
�ʿ� ������ ��ġ�� ������.
*/
void setSnakeTail(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 14);
	gotoxy(snake_x, snake_y);
	printf("��");
	map[snake_x][snake_y] = TAIL; // �ʿ� ������ ��ġ�� ������.
	SetConsoleTextAttribute(hand, 7);

}
// ���� x,y ��ġ�� �׸�.
void setSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(snake_x, snake_y);
	SetConsoleTextAttribute(hand, 14);
	printf("��");
	SetConsoleTextAttribute(hand, 7);
	map[snake_x][snake_y] = HEAD;
}
/*
x,y�� " "�� �־ ������ �ֿܼ��� ������� �ʰ� ��.
map���� x,y �κ��� EMPTY �� �ʱ�ȭ.
*/
void removeSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	gotoxy(snake_x, snake_y);
	printf("  ");
	map[snake_x][snake_y] = EMPTY;
}

int rotate(int xy, int way) {
	if (way == UP || way == LEFT) {
		if (xy - 1 == -1) {
			xy = MAP_SIZE - 1;
		}
		else {
			--(xy);
		}
		return xy;
	}
	if (way == DOWN || way == RIGHT) {
		if (xy + 1 == MAP_SIZE) {
			xy = 0;
		}
		else {
			++xy;
		}
		return xy;
	}
	return FALSE;
}


int colWithTail(MData map[MAP_SIZE][MAP_SIZE], SnakePos * sp, int way) {
	if (way == UP) {
		if (map[sp->x][rotate(sp->y, way)] == TAIL)
			return TRUE;
	}
	if (way == DOWN) {
		if (map[sp->x][rotate(sp->y, way)] == TAIL)
			return TRUE;
	}
	if (way == LEFT) {
		if (map[rotate(sp->x, way)][sp->y] == TAIL)
			return TRUE;
	}
	if (way == RIGHT) {
		if (map[rotate(sp->x, way)][sp->y] == TAIL)
			return TRUE;
	}
	return FALSE;
}

int colWithWall(MData map[MAP_SIZE][MAP_SIZE], SnakePos * sp, int way) {
	if (way == UP) {
		if (map[sp->x][rotate(sp->y, way)] == WALL)
			return TRUE;
	}
	if (way == DOWN) {
		if (map[sp->x][rotate(sp->y, way)] == WALL)
			return TRUE;
	}
	if (way == LEFT) {
		if (map[rotate(sp->x, way)][sp->y] == WALL)
			return TRUE;
	}
	if (way == RIGHT) {
		if (map[rotate(sp->x, way)][sp->y] == WALL)
			return TRUE;
	}
	return FALSE;
}

//get snake x, y and move snake
int moveSnakeHead(MData map[MAP_SIZE][MAP_SIZE], SnakePos * snake, int way) {
	removeSnake(map, snake->x, snake->y);
	if (colWithWall(map, snake, way) == TRUE) {
		gotoxy(1, 1);
		printf("> Hit : wall");
		return COLLISION;
	}
	if (colWithTail(map, snake, way) == TRUE) {
		gotoxy(1, 1);
		printf("> Hit : tail");
		return COLLISION;
	}

	if (way == UP) {
		if (snake->y - 1 == -1) {
			snake->y = MAP_SIZE - 1;
		}
		else {
			--(snake->y);
		}
		setSnake(map, snake->x, (snake->y));
		return UP;
	}
	if (way == DOWN) {
		if (snake->y + 1 == MAP_SIZE) {
			snake->y = 0;
		}
		else {
			++(snake->y);
		}
		setSnake(map, snake->x, (snake->y));
		return DOWN;
	}
	if (way == LEFT) {
		if (snake->x - 1 == -1) {
			snake->x = MAP_SIZE - 1;
		}
		else {
			--(snake->x);
		}
		setSnake(map, (snake->x), snake->y);
		return LEFT;
	}
	if (way == RIGHT) {
		if (snake->x + 1 == MAP_SIZE) {
			snake->x = 0;
		}
		else {
			++(snake->x);
		}
		setSnake(map, snake->x, snake->y);
		return RIGHT;
	}
	return way;
}

int overlap(int savedKey, int key) {
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
// sp�� fp �ܼ� �񱳷� �浹 üũ
int colWithFruit(SnakePos * sp, FruitPos * fp) {
	//meet;->x == fp->x
	if ((sp->x == fp->x && sp->y == fp->y)) {
		return TRUE;
	}
	return FALSE;
}
/*	savedKey�� COLLISION���� �����Ǿ��ִ��� üũ
if (state == COLLISION) return TRUE;
*/
int isCollision(int state) {
	if (state == COLLISION) return TRUE;
	return FALSE;
}
/*
���������� �ְ������� ����ϰ�, Queue�� ���� ����.
*/
void GameOver(int score, int best, Queue *pq, int stage, int * scoreArr) {
	FILE * wfp;
	int errCode;
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	if (score >= best) {
		scoreArr[stage - 1] = score;
	}
	else {
		scoreArr[stage - 1] = best;
	}
	errCode = fopen_s(&wfp, "score.txt", "w");
	fprintf(wfp, "%d %d %d %d", scoreArr[0], scoreArr[1], scoreArr[2], scoreArr[3]);
	fclose(wfp);
	SetConsoleTextAttribute(hand, 14);
	gotoxy(MAP_SIZE / 2 - 4, MAP_SIZE / 2 - 5);
	printf("===<GAME OVER>===\n");
	gotoxy(MAP_SIZE / 2 - 3, MAP_SIZE / 2 - 3);
	printf("Your Score : %d\n", score);
	gotoxy(DEFAULT_X + 8, MAP_SIZE + 5);
	printf("\n");
	SetConsoleTextAttribute(hand, 7);

	while (!isEmpty(pq)) { // ť�� ���� ����.
		Dequeue(pq);
	}
}

void GameStart(MData map[MAP_SIZE][MAP_SIZE], int stage, int * scoreArr) {
	int best = scoreArr[stage - 1];
	int score = 0;
	int key, savedKey = 0;
	Queue queue;
	QueueInit(&queue);
	SnakePos snake = { MAP_SIZE / 4 - 2, MAP_SIZE / 4 + 1 };
	SnakePos snakeSecond;
	SnakePos snakeTail;
	int time = FALSE;
	FruitPos fruit;
	fruit.numOfFruit = 0;

	// ���õ� ���� �׸�.
	if (stage == 1) {
		stageOneInit(map);
	}
	else if (stage == 2) {
		stageTwoInit(map);
	}
	else if (stage == 3) {
		stageThreeInit(map);
	}
	else {
		stageFourinit(map);
	}

	drawMainMap(map);
	setSnake(map, snake.x, snake.y);

	while (1) {
		//ȭ�� ���� �ӵ�
		Sleep(1000 / (DWORD)NORMAL);
		// draw fruit
		if (fruit.numOfFruit == 0) {
			setFruit(map, &fruit);
		}
		drawSubMap(score, best, stage);

		//���ϰ� ���� �浹
		if (colWithFruit(&snake, &fruit) == TRUE) {
			(fruit.numOfFruit)--; //���� ����.
			time = FALSE;	// ���� ����.
			score += 5; // ���� + .
		}
		//Ű ���� ��
		if (_kbhit()) {
			//Ű �Է¹���
			key = _getch();
			//���� ����
			if (key == 't' || key == 'T') {
				return;
			}
			//���� ����.
			if (key == 'p' || key == 'P') {

				system("pause");
				//	'�ƹ�Ű�� �����ÿ�' ����.
				gotoxy(DEFAULT_X, MAP_SIZE + 6);
				printf("                                            ");
				gotoxy(DEFAULT_X, DEFAULT_Y);
			}
			// Ű ���� ����Ű�̸�
			if (key == 224 || key == 0) {
				//���� �Է¹���.
				key = _getch();
				// ���� ����� �ݴ��Ͻ� �����ϰ�, Ű �� ����.
				if (overlap(savedKey, key) == TRUE) {
					key = savedKey;
				}
				// �Ӹ��� ������ ���̴� �Ӹ��κ��� ������.
				snakeSecond = snake;
				savedKey = moveSnakeHead(map, &snake, key);
				// ť�� ��Ӹ����� ��ġ�� ����.
				Enqueue(&queue, snakeSecond);
				setSnakeTail(map, snakeSecond.x, snakeSecond.y); // �ֿܼ� ���� �׸���, �ʿ� ����.
				if (time == TRUE) {	// ������ �������ߴٸ�,
					snakeTail = Dequeue(&queue); //�� ������ ������ Dequeue
					removeSnake(map, snakeTail.x, snakeTail.y); // map�� console�� �� ���� ����.
				}
				else {	//������ �Ծ��ٸ�, ( �� ������ ������ ����. )
					time = TRUE;
				}

				if (isCollision(savedKey)) { // �浹 ���� üũ.
					GameOver(score, best, &queue, stage, scoreArr); // ���� ����
					return;
				}
			}
		}
		else {
			snakeSecond = snake;
			savedKey = moveSnakeHead(map, &snake, savedKey);
			Enqueue(&queue, snakeSecond); // ť�� ��Ӹ����� ��ġ�� ����.
			setSnakeTail(map, snakeSecond.x, snakeSecond.y);

			// ������ �������ߴٸ�,
			if (time == TRUE) {
				snakeTail = Dequeue(&queue);
				removeSnake(map, snakeTail.x, snakeTail.y);
			}
			//������ �Ծ��ٸ�, ( �� ������ ������ ����. )
			else {
				time = TRUE;
			}
			// �浹 ���� üũ. ���� ����
			if (isCollision(savedKey)) {
				GameOver(score, best, &queue, stage, scoreArr);
				return;
			}

		}
	}
}

int main(void) {
	// ���� map������ ������ ���� 2���� �迭
	MData map[MAP_SIZE][MAP_SIZE];
	// console ��� �� ����
	system("color 7");
	hidecursor();
	// �������� ���� ����Ű ���� ����.
	int stage;
	// �� stage �ְ� ��� ���� �迭
	int scoreArr[4] = { 0 };
	while (1) {
		system("mode con: cols=44 lines=30");   //console size
		if (drawStartMenu() == FALSE) break;
		// �ܼ� ȭ�� �ʱ�ȭ
		system("cls");
		stage = drawSpeedMenu(scoreArr);
		system("cls");
		GameStart(map, stage, scoreArr);
		system("pause");
	}
	return 0;
}