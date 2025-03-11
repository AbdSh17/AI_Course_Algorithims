#include "./library/graph_matrix.h"
#include "./library/queue.h"
#include <stdio.h>

graphMatrix initializeMyMatrix();
int8_t bfs(graphMatrix, char);

int main()
{
    printf("\n");
    graphMatrix matrix = initializeMyMatrix();

    printPath(matrix, 'O');

    return 0;
}

void printPath(graphMatrix matrix, char src)
{
    int8_t bfs_index = bfs(matrix, src);
    if (bfs_index == -1)
    {
        printf("BFS printPath ERROR: Failed to find the path\n");
        return;
    }

    char name = matrix->names[bfs_index];
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
    enqueue(q, 0);

    int8_t length = getMatrixLength(matrix);

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
            if (matrix->cells[header][j]->isConnected && !matrix->cells[header][j]->isVisited)
            {
                if (matrix->names[j] == src)
                {
                    removeVisitedState(matrix, length);
                    freeQueue(q);
                    return header;
                }
                enqueue(q, j);
                matrix->cells[header][j]->isVisited = true;
            }
        }
        dequeue(q);
    }

    removeVisitedState(matrix, length);
    return -1;
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
