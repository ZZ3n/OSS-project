
#include "basic.h"
#include "queue.h"

/* 
Setting value Null 
*/
void QueueInit(Queue * pq) 
{
	pq->rear = NULL;
	pq->front = NULL;
}

/*
Queue empty check
*/
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

/*
Insert snake body into queue
*/
void Enqueue(Queue * positionQueue, SnakePos data) 
{
	Node * newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;

	//First enqueue
	if (positionQueue->front == NULL)
	{
		positionQueue->rear = newNode;
		positionQueue->front = newNode;
	}
	//Insert node into Queue
	else
	{
		positionQueue->rear->next = newNode;
		positionQueue->rear = newNode;
	}
}

/*
Dequeue snake's tail
*/
SnakePos Dequeue(Queue * positionQueue) 
{
	Node * deletedNode;
	SnakePos deletedData = { 0,0 };

	// Queue Empty Check
	if (isEmpty(positionQueue))
	{
		return deletedData;
	}

	deletedNode = positionQueue->front;
	deletedData = deletedNode->data;
	positionQueue->front = positionQueue->front->next;

	free(deletedNode);
	return deletedData;
}

/*
Peek the queue
*/
SnakePos Peek(Queue * pq) 
{
	return pq->front->data;
}
