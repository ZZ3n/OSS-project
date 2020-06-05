#pragma once
#include "const.h"
#include "queue.h"

// ť�� rear�� front�� ���� NULL�� �ʱ�ȭ��.
void QueueInit(Queue * pq) {
	pq->rear = NULL;
	pq->front = NULL;
}

int isEmpty(Queue * pq)
{
	if (pq->front == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void Enqueue(Queue * positionQueue, SnakePos data) {
	Node * newNode = (Node *)malloc(sizeof(Node));
	// data�� ��ġ�� ����
	newNode->data = data;
	newNode->next = NULL;
	// ť�� ������ ó���� ����.
	if (positionQueue->front == NULL)
	{
		positionQueue->rear = newNode;
		positionQueue->front = newNode;
	}
	// ť�� �޺κп� ���� �߰�.
	else
	{
		positionQueue->rear->next = newNode;
		positionQueue->rear = newNode;
	}
}

/*
Queue* pq�� ť�� ��ġ�� ����
SnakePos data �� ���� ��ġ
*/
SnakePos Dequeue(Queue * pq) {
	Node * deletedNode;
	SnakePos deletedData = { 0,0 };
	// Queue Empty Check
	if (isEmpty(pq))
	{
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
