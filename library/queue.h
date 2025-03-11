#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct queueHeaderNode *queueHeader;

queueHeader initializeQueue();
void enqueue(queueHeader, int8_t);
bool dequeue(queueHeader);
void printQueue(queueHeader);
void freeQueue(queueHeader);
bool isInTheQueue(queueHeader, int8_t);
int8_t getQueueHead(queueHeader);

#endif