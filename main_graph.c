#include "./library/graph_matrix.h"
#include "./library/queue.h"
#include <stdio.h>

graphMatrix initializeMyMatrix();
int8_t bfs(graphMatrix, char);

int main()
{
    // printhii();
    graphMatrix matrix = initializeMyMatrix();

    // printf("last node to the goal: %c", matrix->names[bfs(matrix, 'G')]);
    printPath(matrix, 'E');

    // printMatrix(matrix);

    return 0;
}

void printPath(graphMatrix matrix, char src)
{
    char name = matrix->names[bfs(matrix, src)];
    printf("%c", src);
    int count = 0;
    while (name != 'S')
    {
        printf(" <- %c", name);
        name = matrix->names[bfs(matrix, name)];
        count++;
        if (count == 9)
        {
            break;
        }
    }

    printf(" <- S");
}

int8_t bfs(graphMatrix matrix, char src)
{
    queueHeader q = initializeQueue();
    queueHeader visitedNodes = initializeQueue();
    enqueue(q, 0);
    enqueue(visitedNodes, 0);

    int8_t length = getMatrixLength(matrix);

    int count = 1;

    // while Queue is not empty;
    while (q)
    {
        int8_t header = getQueueHead(q);
        if (header == -1)
        {
            break;
        }

        for (size_t j = 0; j < length; j++)
        {
            if (matrix->cells[header][j]->isConnected && !isInTheQueue(q, j) && !isInTheQueue(visitedNodes, j))
            {

                if (matrix->names[j] == src)
                {
                    return header;
                }
                enqueue(q, j);
                enqueue(visitedNodes, j);
            }
        }

        dequeue(q);
    }

    return getQueueHead(q);
}

graphMatrix initializeMyMatrix()
{
    graphMatrix matrix = initializeMatrixArray();
    addVertex(matrix, 'S');
    addVertex(matrix, 'A');
    addVertex(matrix, 'B');
    addVertex(matrix, 'C');
    addVertex(matrix, 'H');
    addVertex(matrix, 'G');
    addVertex(matrix, 'D');
    addVertex(matrix, 'E');

    createUndirectedEdge(matrix, 'A', 'S');
    createUndirectedEdge(matrix, 'A', 'C');
    createUndirectedEdge(matrix, 'A', 'H');
    createUndirectedEdge(matrix, 'B', 'S');
    createUndirectedEdge(matrix, 'B', 'G');
    createUndirectedEdge(matrix, 'B', 'H');
    createUndirectedEdge(matrix, 'C', 'G');
    createUndirectedEdge(matrix, 'C', 'H');
    createUndirectedEdge(matrix, 'G', 'D');
    createUndirectedEdge(matrix, 'A', 'D');
    createUndirectedEdge(matrix, 'D', 'E');

    return matrix;
}
