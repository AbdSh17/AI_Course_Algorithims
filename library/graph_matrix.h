#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_VERTEX_NUM 10

typedef struct graphMatrixNode *graphMatrix;

extern const int8_t NOT_CONNECTED;
extern const int8_t NULL_CONNECTED;
extern const int8_t CONNECTED;

struct graphMatrixNode
{
    char names[MAX_VERTEX_NUM];
    struct matrixCellNode ***cells;
};

struct matrixCellNode
{
    int8_t isConnected;
};

// Function declarations
graphMatrix initializeMatrixArray();
// matrixCell initializeMatrixCell();
void printMatrix(graphMatrix);
void addVertex(graphMatrix, char);
void createUndirectedEdge(graphMatrix, char, char);
void createDirectedEdge(graphMatrix, char, char);
int8_t getIndex(graphMatrix, char);
int8_t getMatrixLength(graphMatrix);

#endif