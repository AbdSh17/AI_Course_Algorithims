#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_VERTEX_NUM 20

typedef struct graphMatrixNode *graphMatrix;

extern const int8_t NOT_CONNECTED;
extern const int8_t NULL_CONNECTED;
extern const int8_t CONNECTED;

extern const int8_t VISITED;
extern const int8_t NOT_VISITED;

struct graphMatrixNode
{
    char names[MAX_VERTEX_NUM];
    int8_t visitStatus[MAX_VERTEX_NUM];
    struct matrixCellNode ***cells;
};

struct matrixCellNode
{
    int8_t connection;
};

// Function declarations
graphMatrix initializeMatrixArray();
// matrixCell initializeMatrixCell();
void printMatrix(graphMatrix);
void addVertex(graphMatrix, char);
void createUndirectedEdge(graphMatrix, char, char);
void createDirectedEdge(graphMatrix, char, char);
void createUndirectedWeightedEdge(graphMatrix, char, char, int8_t);
void createDirectedWeightedEdge(graphMatrix, char, char, int8_t);
int8_t getIndex(graphMatrix, char);
int8_t getMatrixLength(graphMatrix);
void removeVisitedState(graphMatrix, int8_t);
void removeConnections(graphMatrix, int8_t);
char getNodeName(graphMatrix, int8_t);

#endif