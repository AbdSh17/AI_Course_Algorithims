#include "./library/graph_matrix.h"
#include "./library/queue.h"
#include "./library/stack.h"
#include <stdio.h>

// ======================= STRUCT_2D_GRAPH=========================
/*
        MATRIX->names[]
    A   B   C   D   E   F   G
        MATRIX->cells[][]
    0   1   0   1   0   0   0
    1   0   1   0   0   0   0
    0   1   0   1   1   0   1
    0   1   0   1   1   0   1
    0   1   0   1   1   0   1
    0   1   0   1   1   0   1
    0   1   0   1   1   0   1
*/

graphMatrix initializeMyMatrixIMG1();
graphMatrix initializeMyMatrixIMG2();
int8_t bfs(graphMatrix matrix, char, char);
int8_t dfs(graphMatrix matrix, char, char);
void printBFSPath(graphMatrix, char, char);
void printDFSPath(graphMatrix, char, char);
void printbiDirectionalSearchPATH(graphMatrix, char, char);
int8_t dfs(graphMatrix, char, char);
int8_t visitStatus(int8_t);
int8_t *biDirectionalSearch(graphMatrix, char, char);

int main()
{

    printf("\n");

    graphMatrix matrix = initializeMyMatrixIMG1();

    // printBFSPath(matrix, 'S', 'E');
    printDFSPath(matrix, 'A', 'E');
    // printMatrix(matrix);

    return 0;
}

void printBFSPath(graphMatrix matrix, char src1, char src2)
{
    int8_t bfs_index = bfs(matrix, src1, src2);
    if (bfs_index == -1)
    {
        printf("BFS printPath ERROR: Failed to find the path\n");
        return;
    }

    char name = matrix->names[bfs_index];
    printf("%c", src2);
    while (name != src1)
    {
        printf(" <- %c", name);
        name = matrix->names[bfs(matrix, src1, name)];
    }

    printf(" <- %c\n", src1);
    printf("\n===================\n");
}

void printDFSPath(graphMatrix matrix, char src1, char src2)
{
    int8_t bfs_index = dfs(matrix, src1, src2);
    if (bfs_index == -1)
    {
        printf("BFS printPath ERROR: Failed to find the path\n");
        return;
    }

    char name = matrix->names[bfs_index];
    printf("%c", src2);
    while (name != src1)
    {
        printf(" <- %c", name);
        name = matrix->names[dfs(matrix, src1, name)];
    }

    printf(" <- %c", src1);
}

const int8_t NOT_VISITED = 0;
const int8_t SOURCE_QUEUE = 1;
const int8_t GOAL_QUEUE = 2;
const int8_t SOURCE_AND_GOAL_QUEUE = 3;

int8_t bfs(graphMatrix matrix, char src1, char src2)
{

    // ======================= STRUCT =========================
    /*
            MATRIX->names[]
        A   B   C   D   E   F   G
            MATRIX->cells[][]
        0   1   0   1   0   0   0
        1   0   1   0   0   0   0
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
    */
    queueHeader q = initializeQueue();
    enqueue(q, getIndex(matrix, src1)); // Sorce index

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
            int8_t visitStatus = matrix->cells[header][j]->isVisited;
            int8_t connectionStatus = matrix->cells[header][j]->isConnected;

            if (connectionStatus == CONNECTED && visitStatus == NOT_VISITED)
            {
                if (matrix->names[j] == src2)
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

int8_t dfs(graphMatrix matrix, char src1, char src2)
{
    stackHeader s = initializeStackHeadder();
    push(s, getIndex(matrix, src1)); // Sorce index

    int8_t length = getMatrixLength(matrix);

    // while Queue is not empty;
    int8_t count = 0;
    while (s)
    {
        int8_t header = getTop(s);
        if (header == -1)
        {
            break;
        }

        for (size_t j = 0; j < length; j++)
        {
            int8_t visitStatus = matrix->cells[header][j]->isVisited;
            int8_t connectionStatus = matrix->cells[header][j]->isConnected;

            if (connectionStatus == CONNECTED && visitStatus == NOT_VISITED)
            {
                if (matrix->names[j] == src2)
                {
                    removeVisitedState(matrix, length);
                    // freeQueue(q);
                    return header;
                }
                push(s, j);
                matrix->cells[header][j]->isVisited = true;
            }
        }
        pop(s);
        count++;
        if (count == 9)
        {
            break;
        }

        printStack(s);
        printf("\n================================\n");
    }

    removeVisitedState(matrix, length);
    return -1;
}

int8_t *biDirectionalSearch(graphMatrix matrix, char src1, char src2)
{

    // ======================= STRUCT =========================
    /*
            MATRIX->names[]
        A   B   C   D   E   F   G
            MATRIX->cells[][]
        0   1   0   1   0   0   0
        1   0   1   0   0   0   0
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
        0   1   0   1   1   0   1
    */

    int8_t *soulation = (int8_t *)malloc(sizeof(int8_t) * 2);
    queueHeader sourceQ = initializeQueue();
    int8_t src1Index = getIndex(matrix, src1);
    enqueue(sourceQ, src1Index); // Sorce index

    queueHeader goalQ = initializeQueue();
    int8_t src2Index = getIndex(matrix, src2);
    enqueue(goalQ, src2Index); // goal index

    if (matrix->cells[src1Index][src2Index]->isConnected == CONNECTED)
    {
        return src1Index;
    }

    int8_t length = getMatrixLength(matrix);

    // while 2 Queues are not empty;
    while (sourceQ && goalQ)
    {
        int8_t sourceHeader = getQueueHead(sourceQ);
        int8_t goalHeader = getQueueHead(goalQ);

        if (sourceHeader == -1 && goalHeader == -1)
        {
            break;
        }

        for (size_t j = 0; j < length; j++)
        {
            int8_t visitStatus = matrix->cells[sourceHeader][j]->isVisited;
            int8_t connectionStatus = matrix->cells[sourceHeader][j]->isConnected;
            if (connectionStatus == CONNECTED && visitStatus != SOURCE_QUEUE) // connection == 1
            {
                if (visitStatus == NOT_VISITED)
                {
                    matrix->cells[sourceHeader][j]->isVisited = SOURCE_QUEUE;
                    matrix->cells[j][sourceHeader]->isVisited = SOURCE_QUEUE;
                    enqueue(sourceQ, j);
                }

                // if (visitStatus == GOAL_QUEUE)
                // {
                //     matrix->cells[sourceHeader][j]->isVisited = SOURCE_AND_GOAL_QUEUE;
                //     matrix->cells[j][sourceHeader]->isVisited = SOURCE_AND_GOAL_QUEUE;
                // }

                // else if (visitStatus == SOURCE_AND_GOAL_QUEUE)
                // {
                //     removeVisitedState(matrix, length);
                //     freeQueue(goalQ);
                //     freeQueue(sourceQ);
                //     soulation[0] = sourceHeader;
                //     soulation[1] = j;
                //     return soulation;
                // }
            }
        }

        for (int8_t j = 0; j < length; j++)
        {
            if (matrix->cells[sourceHeader][j]->isConnected == GOAL_QUEUE)
            {
                matrix->cells[sourceHeader][j]->isConnected = SOURCE_AND_GOAL_QUEUE;
            }

            else if (matrix->cells[sourceHeader][j]->isConnected == SOURCE_AND_GOAL_QUEUE)
            {
                removeVisitedState(matrix, length);
                freeQueue(goalQ);
                freeQueue(sourceQ);
                soulation[0] = sourceHeader;
                soulation[1] = j;
                return soulation;
            }
        }

        dequeue(sourceQ);
        for (size_t j = 0; j < length; j++)
        {

            int8_t visitStatus = matrix->cells[goalHeader][j]->isVisited;
            int8_t connectionStatus = matrix->cells[goalHeader][j]->isConnected;

            if (connectionStatus == CONNECTED && visitStatus != GOAL_QUEUE) // connection == 1
            {
                if (visitStatus == NOT_VISITED)
                {
                    matrix->cells[goalHeader][j]->isVisited = GOAL_QUEUE;
                    matrix->cells[j][goalHeader]->isVisited = GOAL_QUEUE;
                    enqueue(goalQ, j);
                }

                // if (visitStatus == SOURCE_QUEUE)
                // {
                //     matrix->cells[goalHeader][j]->isVisited = SOURCE_AND_GOAL_QUEUE;
                //     matrix->cells[j][goalHeader]->isVisited = SOURCE_AND_GOAL_QUEUE;
                // }

                // else if (visitStatus == SOURCE_AND_GOAL_QUEUE)
                // {
                // removeVisitedState(matrix, length);
                // freeQueue(goalQ);
                // freeQueue(sourceQ);
                // soulation[0] = j;
                // soulation[1] = goalHeader;
                // return soulation;
                // }
            }
        }

        for (int8_t j = 0; j < length; j++)
        {
            if (matrix->cells[goalHeader][j]->isConnected == SOURCE_QUEUE)
            {
                matrix->cells[goalHeader][j]->isConnected = SOURCE_AND_GOAL_QUEUE;
            }

            else if (matrix->cells[goalHeader][j]->isConnected == SOURCE_AND_GOAL_QUEUE)
            {
                removeVisitedState(matrix, length);
                freeQueue(goalQ);
                freeQueue(sourceQ);
                soulation[0] = j;
                soulation[1] = goalHeader;
                return soulation;
            }
        }

        dequeue(goalQ);
        // printf("\n========================= source QUEUE =========================\n");
        // printQueue(sourceQ);
        // printf("\n========================= goal QUEUE =========================\n");
        // printQueue(goalQ);
    }

    removeVisitedState(matrix, length);
    return NULL;
}

int8_t visitStatus(int8_t visit)
{
    return visit;
}

graphMatrix initializeMyMatrixIMG1()
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

graphMatrix initializeMyMatrixIMG2()
{
    graphMatrix matrix = initializeMatrixArray();

    addVertex(matrix, 'A');
    addVertex(matrix, 'B');
    addVertex(matrix, 'C');
    addVertex(matrix, 'D');
    addVertex(matrix, 'E');
    addVertex(matrix, 'F');
    addVertex(matrix, 'G');
    addVertex(matrix, 'H');
    addVertex(matrix, 'I');
    addVertex(matrix, 'J');
    addVertex(matrix, 'K');

    createUndirectedEdge(matrix, 'A', 'I');
    createUndirectedEdge(matrix, 'A', 'B');
    createUndirectedEdge(matrix, 'A', 'C');
    createUndirectedEdge(matrix, 'C', 'K');
    createUndirectedEdge(matrix, 'C', 'G');
    createUndirectedEdge(matrix, 'G', 'K');
    createUndirectedEdge(matrix, 'G', 'J');
    createUndirectedEdge(matrix, 'G', 'F');
    createUndirectedEdge(matrix, 'G', 'H');
    createUndirectedEdge(matrix, 'H', 'F');
    createUndirectedEdge(matrix, 'F', 'E');
    createUndirectedEdge(matrix, 'F', 'J');
    createUndirectedEdge(matrix, 'D', 'E');
    createUndirectedEdge(matrix, 'D', 'J');
    createUndirectedEdge(matrix, 'D', 'K');
    createUndirectedEdge(matrix, 'D', 'I');
    createUndirectedEdge(matrix, 'K', 'B');

    return matrix;
}
