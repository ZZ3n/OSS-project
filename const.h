#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

// 2Â÷¿ø ¹è¿­ ¸Ê
typedef int MData;

typedef struct _snakexp {
	int x;
	int y;
} SnakePos;

// 2Â÷¿ø ¹è¿­ ¸Ê
typedef int MapData;

// »ç°úÀÇ x,y ÁÂÇ¥¿Í »ç°ú °¹¼ö
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
/*	front´Â ¾Õ¸¦ °¡¸®Å´. rear´Â µÚ¸¦ °¡¸®Å´
QueueÀÇ ¾ÕºÎºÐ := ¹ì ²¿¸®.
*/
typedef MyQueue Queue;
/////////////////////////////////////////////////////////////////////////////////

void gotoxy(int x, int y);
