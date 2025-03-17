#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct stackHeaderNode *stackHeader;

stackHeader initializeStackHeadder();
void push(stackHeader, int8_t);
bool pop(stackHeader);
int8_t getTop(stackHeader);
void printStack(stackHeader);

#endif