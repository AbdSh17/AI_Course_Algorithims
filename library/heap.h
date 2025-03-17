#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct minHeapNode *minHeap;

#define HEAPSIZE 100

struct minHeapArray
{
    int8_t weight;
    int8_t data;
};

struct minHeapNode
{
    int8_t current;
    struct minHeapArray **array;
};

minHeap makeEmptyMinHeap();
void insertMinHeap(minHeap, int8_t, int8_t);
struct minHeapArray *deleteMinHeap(minHeap);
void printMinHeap(minHeap);
struct minHeapArray *getMinHeapTop(minHeap);

#endif