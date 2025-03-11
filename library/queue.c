#include "queue.h"

typedef struct queueNode *queue;

struct queueNode
{
    int8_t data;
    queue next;
};

struct queueHeaderNode
{
    queue head;
    queue tail;
};

queueHeader initializeQueue()
{
    queueHeader q = (queueHeader)malloc(sizeof(struct queueHeaderNode));
    if (!q)
    {
        printf("RunOutOF memeory");
        return NULL;
    }

    q->head = q->tail = NULL;
    return q;
}

void enqueue(queueHeader q, int8_t data)
{
    queue newq = (queue)malloc(sizeof(struct queueNode));
    newq->next = NULL;
    newq->data = data;

    if (!q->head)
    {
        q->head = newq;
        q->tail = newq;
        return;
    }
    q->tail->next = newq;
    q->tail = newq;
}

bool dequeue(queueHeader q)
{
    if (!q->head)
    {
        printf("Empty Queue");
        return false;
    }

    if (q->tail == q->head)
    {
        q->tail = NULL;
    }

    queue temp = q->head;
    q->head = q->head->next;
    free(temp);
    return true;
}

void printQueue(queueHeader q)
{
    if (!q->head)
    {
        printf("Empty Queue");
        return;
    }

    queue temp = q->head;

    while (temp)
    {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
}

void freeQueue(queueHeader q)
{
    if (!q->head)
    {
        printf("Empty Queue");
        return;
    }

    queue temp = q->head;
    while (temp)
    {
        queue temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
}

bool isInTheQueue(queueHeader q, int8_t data)
{
    if (!q)
    {
        printf("ERROR: isInTheQueue - Empty Queue");
        return false;
    }

    queue temp = q->head;
    while (temp)
    {
        if (temp->data == data)
        {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

int8_t getQueueHead(queueHeader q)
{
    return (q->head) ? q->head->data : -1;
}