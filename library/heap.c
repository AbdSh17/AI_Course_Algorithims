#include "heap.h"

typedef struct minHeapArray *heapArray;

void initializeMinHeap(minHeap);

heapArray initializeMinHeapArray();

heapArray initializeMinHeapArray()
{
    heapArray array = (heapArray)malloc(sizeof(struct minHeapArray));
    if (!array)
    {
        printf("ERROR initializeMinHeapArray: can't allocate more");
        return NULL;
    }

    array->data = -1;
    array->weight = -1;
    return array;
}

void initializeMinHeap(minHeap h)
{
    for (int8_t i = 0; i < HEAPSIZE; i++)
    {
        h->array[i] = initializeMinHeapArray();
    }
}

minHeap makeEmptyMinHeap()
{
    minHeap h = (minHeap)malloc(sizeof(struct minHeapNode));
    h->current = 1;
    h->array = (heapArray *)malloc(sizeof(heapArray) * HEAPSIZE);
    initializeMinHeap(h);
    return h;
}

void insertMinHeap(minHeap h, int8_t weight, int8_t data)
{
    int8_t current = h->current;
    if (h->current == 1)
    {
        h->array[current]->weight = weight;
        h->array[current]->data = data;
        h->current++;
        return;
    }

    while (h->array[current / 2]->weight > weight && current != 1)
    {
        h->array[current]->weight = h->array[current / 2]->weight;
        h->array[current]->data = h->array[current / 2]->data;
        current /= 2;
    }

    h->array[current]->weight = weight;
    h->array[current]->data = data;
    h->current++;
}

heapArray deleteMinHeap(minHeap h)
{

    if (h->current == 1)
    {
        return NULL;
    }

    int8_t current = h->current;

    heapArray top = initializeMinHeapArray();

    top->data = getMinHeapTop(h)->data;
    top->weight = getMinHeapTop(h)->weight;

    h->array[1]->weight = h->array[current - 1]->weight;
    h->array[1]->data = h->array[current - 1]->data;

    h->array[current - 1]->weight = 0;
    h->array[current - 1]->data = 0;

    h->current--;

    int8_t i = 1;
    while (i < h->current / 2 && (h->array[i]->weight > h->array[i * 2]->weight || h->array[i]->weight > h->array[i * 2 + 1]->weight))
    {
        if (h->array[i * 2 + 1]->weight > h->array[i * 2]->weight)
        {
            heapArray temp = h->array[i];
            h->array[i] = h->array[i * 2];
            h->array[i * 2] = temp;
            i *= 2;
        }
        else
        {
            heapArray temp = h->array[i];
            h->array[i] = h->array[i * 2 + 1];
            h->array[i * 2 + 1] = temp;
            i = i * 2 + 1;
        }
    }

    return top;
}

heapArray getMinHeapTop(minHeap h)
{
    // printf()
    return (h->current == 1) ? NULL : h->array[1];
}

void printMinHeap(minHeap h)
{
    printf("Index:  VALUE:  WEIGHT\n");
    for (int8_t i = 1; i < h->current; i++)
    {
        printf("%-5d:  %-5d:  %-5d\n", i, h->array[i]->data, h->array[i]->weight);
    }
}