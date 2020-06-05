#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

// 2���� �迭 ��
typedef int MData;

typedef struct _snakexp {
	int x;
	int y;
} SnakePos;

// 2���� �迭 ��
typedef int MapData;

// ����� x,y ��ǥ�� ��� ����
typedef struct _fruitxy {
	int x;
	int y;
	int numOfFruit;
} FruitPos;


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
/*	front�� �ո� ����Ŵ. rear�� �ڸ� ����Ŵ
Queue�� �պκ� := �� ����.
*/
typedef MyQueue Queue;
/////////////////////////////////////////////////////////////////////////////////

void gotoxy(int x, int y);
