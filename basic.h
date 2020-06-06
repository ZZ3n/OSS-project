#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

typedef struct _snakexp {
	int x;
	int y;
} SnakePos;

// Two dimensional array map
typedef int MapData;

// Fruit (x,y) and Fruit count
typedef struct _fruitxy {
	int x;
	int y;
	int numOfFruit;
} FruitPos;

//typedef int QData;
typedef struct _mynode {
	SnakePos data;
	struct _mynode *next;
} Node;

typedef struct _myqueue {
	Node * rear;
	Node * front;
} MyQueue;

/*
Front of queue is snake's tail
*/
typedef MyQueue Queue;

void gotoxy(int x, int y);
