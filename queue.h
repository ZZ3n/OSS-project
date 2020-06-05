#pragma once
#include "const.h"

void QueueInit(Queue * pq);
int isEmpty(Queue * pq);
void Enqueue(Queue * positionQueue, SnakePos data);
SnakePos Dequeue(Queue * pq);
SnakePos Peek(Queue * pq);