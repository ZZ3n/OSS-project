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

// 2차원 배열 맵
typedef int MData;

// 사과의 x,y 좌표와 사과 갯수
typedef struct _fruitxy {
	int x;
	int y;
	int numOfFruit;
} FruitPos;
// snake x,y 좌표
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
/*	front는 앞를 가리킴. rear는 뒤를 가리킴.
Queue의 앞부분 := 뱀 꼬리.
*/
typedef MyQueue Queue;
// 큐의 rear와 front를 전부 NULL로 초기화함.
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
Queue* pq는 큐의 위치를 참조
SnakePos data 는 뱀의 위치
*/
void Enqueue(Queue * pq, SnakePos data) {
	Node * newNode = (Node *)malloc(sizeof(Node));
	// data의 위치를 저장
	newNode->data = data;
	newNode->next = NULL;
	// 큐에 삽입이 처음인 경우.
	if (pq->front == NULL) {
		pq->rear = newNode;
		pq->front = newNode;
	}
	// 큐의 뒷부분에 노드 추가.
	else {
		pq->rear->next = newNode;
		pq->rear = newNode;
	}
}
/*
Queue pq의 Dequeue를 진행.
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


//show start menu
int drawStartMenu(void) {
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

//show stage Menu and score;
int drawSpeedMenu(int * scoreArr) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

	int i;
	// 'score.txt' 파일 읽기위한 포인터 변수, 쓰기위한  포인터변수
	FILE * rfp, *wfp;
	int errCode;
	errCode = fopen_s(&rfp, "score.txt", "r");

	// 게임을 실행 한 적이 없어서 'score.txt' 파일이 없는 경우.
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

	if (errCode != 0) { // 파일이 잘 열리지 않았을 경우.
						//새 파일 생성
		errCode = fopen_s(&wfp, "score.txt", "w");
		// 최고기록 초기화.
		fprintf(wfp, "%d %d %d %d", scoreArr[0], scoreArr[1], scoreArr[2], scoreArr[3]);
		for (i = 0; i<4; i++) {
			gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
			printf(" Stage [%d] : %d", i + 1, scoreArr[i]);
		}
		fclose(wfp);
	}
	// Score 읽어 옴.
	fscanf_s(rfp, "%d %d %d %d", &scoreArr[0], &scoreArr[1], &scoreArr[2], &scoreArr[3]);

	for (i = 0; i<4; i++) {
		gotoxy(DEFAULT_X, DEFAULT_Y + (i + 4));
		printf(" Stage [%d] : %d", i + 1, scoreArr[i]);
	} // 최고 점수 출력.

	fclose(rfp);
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

// HANDLE 은 운영체제에 의해 생성된 리소스나 오브젝트를 제어하기 위한 32bit의 정수값
//  GetStdHandle()는 실체 핸들을 반환하는 함수로 안에 파라미터로 종류를 정해주면 핸들 값을 반환 함.
//      - 인자로 STD_OUTPUT_HANDLE를 주면 표준콘솔출력의 핸들 반환.
// HANDLE은 구조체의 메모리할당과 이에 대한 포인터 구해서 함수호출에 사용하는 것과 비슷하다
// 다른 점은 운영체제나 기타 시스템 프로그램처럼 구조체 내부의 정보를 공개 안하려하거나 프로그래머에게 일관된
//    프로그래밍 환경을 제공하기 위해 사용 하는 것. ( 프로그램 규모 커지거나 여러사람이 공동 작업을 하는 경우 좋음)



//////////////////////////////////////STAGE MAP SETTING////////////////////////////////
//stageOneInit~ stageFourInit 까지의 함수는  drawMainMap에서 바로 맵을 그릴 수 있게 미리 WALL이 생길 공간을 지정함
void stageClear(MData map[MAP_SIZE][MAP_SIZE]) {
	int i, j;
	for (i = 0; i <= MAP_SIZE; i++) {
		for (j = 0; i <= MAP_SIZE; j++) {
			map[i][j] = EMPTY;
		}
	}
}
// stage 1의 맵 만드는 함수 <네모 벽>
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
// stage 2의 맵 만드는 함수 < 네모 벽에 중간에 벽>
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
// stage 3의 맵 만드는 함수 < 십자 벽>
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
// stage 4의 맵 만드는 함수 < 크로스 벽>
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
				printf("■");
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
			printf("★");
			SetConsoleTextAttribute(hand, 7);

			return 1;
		}
	}
}
// 안쓰이는 코드
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
콘솔 (x,y) 에 Tail("○") 을 그림
맵에 꼬리의 위치를 저장함.
*/
void setSnakeTail(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hand, 14);
	gotoxy(snake_x, snake_y);
	printf("○");
	map[snake_x][snake_y] = TAIL; // 맵에 꼬리의 위치를 저장함.
	SetConsoleTextAttribute(hand, 7);

}
// 뱀을 x,y 위치에 그림.
void setSnake(MData map[MAP_SIZE][MAP_SIZE], int snake_x, int snake_y) {
	HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(snake_x, snake_y);
	SetConsoleTextAttribute(hand, 14);
	printf("●");
	SetConsoleTextAttribute(hand, 7);
	map[snake_x][snake_y] = HEAD;
}
/*
x,y에 " "를 넣어서 꼬리를 콘솔에서 출력하지 않게 함.
map에서 x,y 부분을 EMPTY 로 초기화.
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
// sp와 fp 단순 비교로 충돌 체크
int colWithFruit(SnakePos * sp, FruitPos * fp) {
	//meet;->x == fp->x
	if ((sp->x == fp->x && sp->y == fp->y)) {
		return TRUE;
	}
	return FALSE;
}
/*	savedKey가 COLLISION으로 설정되어있는지 체크
if (state == COLLISION) return TRUE;
*/
int isCollision(int state) {
	if (state == COLLISION) return TRUE;
	return FALSE;
}
/*
스테이지별 최고점수를 기록하고, Queue를 전부 지움.
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

	while (!isEmpty(pq)) { // 큐를 전부 삭제.
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

	// 선택된 맵을 그림.
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
		//화면 갱신 속도
		Sleep(1000 / (DWORD)NORMAL);
		// draw fruit
		if (fruit.numOfFruit == 0) {
			setFruit(map, &fruit);
		}
		drawSubMap(score, best, stage);

		//과일과 뱀의 충돌
		if (colWithFruit(&snake, &fruit) == TRUE) {
			(fruit.numOfFruit)--; //갯수 줄임.
			time = FALSE;	// 변수 설정.
			score += 5; // 점수 + .
		}
		//키 누를 시
		if (_kbhit()) {
			//키 입력받음
			key = _getch();
			//게임 종료
			if (key == 't' || key == 'T') {
				return;
			}
			//게임 멈춤.
			if (key == 'p' || key == 'P') {

				system("pause");
				//	'아무키나 누르시오' 지움.
				gotoxy(DEFAULT_X, MAP_SIZE + 6);
				printf("                                            ");
				gotoxy(DEFAULT_X, DEFAULT_Y);
			}
			// 키 값이 방향키이면
			if (key == 224 || key == 0) {
				//방향 입력받음.
				key = _getch();
				// 이전 방향과 반대일시 무시하고, 키 값 저장.
				if (overlap(savedKey, key) == TRUE) {
					key = savedKey;
				}
				// 머리는 움직일 것이니 머리부분을 저장함.
				snakeSecond = snake;
				savedKey = moveSnakeHead(map, &snake, key);
				// 큐에 뱀머리였던 위치를 넣음.
				Enqueue(&queue, snakeSecond);
				setSnakeTail(map, snakeSecond.x, snakeSecond.y); // 콘솔에 뱀을 그리고, 맵에 저장.
				if (time == TRUE) {	// 과일을 먹지못했다면,
					snakeTail = Dequeue(&queue); //뱀 꼬리의 데이터 Dequeue
					removeSnake(map, snakeTail.x, snakeTail.y); // map과 console에 뱀 꼬리 삭제.
				}
				else {	//과일을 먹었다면, ( 뱀 꼬리를 지우지 않음. )
					time = TRUE;
				}

				if (isCollision(savedKey)) { // 충돌 변수 체크.
					GameOver(score, best, &queue, stage, scoreArr); // 게임 오버
					return;
				}
			}
		}
		else {
			snakeSecond = snake;
			savedKey = moveSnakeHead(map, &snake, savedKey);
			Enqueue(&queue, snakeSecond); // 큐에 뱀머리였던 위치를 넣음.
			setSnakeTail(map, snakeSecond.x, snakeSecond.y);

			// 과일을 먹지못했다면,
			if (time == TRUE) {
				snakeTail = Dequeue(&queue);
				removeSnake(map, snakeTail.x, snakeTail.y);
			}
			//과일을 먹었다면, ( 뱀 꼬리를 지우지 않음. )
			else {
				time = TRUE;
			}
			// 충돌 변수 체크. 게임 오버
			if (isCollision(savedKey)) {
				GameOver(score, best, &queue, stage, scoreArr);
				return;
			}

		}
	}
}

int main(void) {
	// 게임 map정보를 가지기 위한 2차원 배열
	MData map[MAP_SIZE][MAP_SIZE];
	// console 배경 색 설정
	system("color 7");
	hidecursor();
	// 스테이지 선택 저장키 위한 변수.
	int stage;
	// 각 stage 최고 기록 저장 배열
	int scoreArr[4] = { 0 };
	while (1) {
		system("mode con: cols=44 lines=30");   //console size
		if (drawStartMenu() == FALSE) break;
		// 콘솔 화면 초기화
		system("cls");
		stage = drawSpeedMenu(scoreArr);
		system("cls");
		GameStart(map, stage, scoreArr);
		system("pause");
	}
	return 0;
}