#include "stack.h"

typedef struct stackNode *stack;

struct stackHeaderNode
{
    stack top;
};

struct stackNode
{
    stack next;
    int8_t data;
};

stackHeader initializeStackHeadder()
{
    stackHeader s = (stackHeader)malloc(sizeof(struct stackHeaderNode));
    if (!s)
    {
        printf("ERROR initializeStackHeadder: Failed to allocate\n");
        return NULL;
    }

    s->top = NULL;
    return s;
}

void push(stackHeader s, int8_t data)
{
    stack newStack = (stack)malloc(sizeof(struct stackNode));
    newStack->data = data;

    newStack->next = s->top;
    s->top = newStack;
}

bool pop(stackHeader s)
{
    if (!s->top)
    {
        // printf("ERROR POP: empty stack\n");
        return false;
    }

    stack temp = s->top;
    s->top = s->top->next;
    free(temp);
    return true;
}

int8_t getTop(stackHeader s)
{
    return (s->top) ? s->top->data : -1;
}

void printStack(stackHeader s)
{
    if (!s)
    {
        printf("ERORR PRINT STACK: empty head");
        return;
    }

    stack temp = s->top;
    while (temp)
    {
        printf("%d  ", temp->data);
        temp = temp->next;
    }
}