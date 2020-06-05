#pragma once
#include "const.h"
#include "queue.h"

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

void Enqueue(Queue * positionQueue, SnakePos data) {
	Node * newNode = (Node *)malloc(sizeof(Node));
	// data의 위치를 저장
	newNode->data = data;
	newNode->next = NULL;
	// 큐에 삽입이 처음인 경우.
	if (positionQueue->front == NULL) {
		positionQueue->rear = newNode;
		positionQueue->front = newNode;
	}
	// 큐의 뒷부분에 노드 추가.
	else {
		positionQueue->rear->next = newNode;
		positionQueue->rear = newNode;
	}
}

/*
Queue* pq는 큐의 위치를 참조
SnakePos data 는 뱀의 위치
*/
SnakePos Dequeue(Queue * pq) {
	Node * deletedNode;
	SnakePos deletedData = { 0,0 };
	// Queue Empty Check
	if (isEmpty(pq)) {
		return deletedData;
	}
	deletedNode = pq->front;
	deletedData = deletedNode->data;
	pq->front = pq->front->next;
	free(deletedNode);
	return deletedData;
}

SnakePos Peek(Queue * pq) {
	return pq->front->data;
}
