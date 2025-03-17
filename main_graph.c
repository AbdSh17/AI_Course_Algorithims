#include "./library/graph_matrix.h"
#include "./library/queue.h"
#include "./library/stack.h"
#include "./library/heap.h"
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
graphMatrix initializeMyMatrixIMG3();
graphMatrix initializeMyMatrixIMG4();
int8_t BFS(graphMatrix matrix, char, char);
int8_t DFS(graphMatrix matrix, char, char);
void printBFSPath(graphMatrix, char, char);
void printDFSPath(graphMatrix, char, char);
void printUniformCostSearchPath(graphMatrix, char, char);
int8_t itterativeDFS(graphMatrix, char, char, int8_t);
void printItterativeDFSPath(graphMatrix, char, char);
int8_t uniformCostSearch(graphMatrix, char, char);
// void printbiDirectionalSearchPATH(graphMatrix, char, char);
int8_t visitStatus(int8_t);
// int8_t *biDirectionalSearch(graphMatrix, char, char);

int main()
{

    printf("\n");

    graphMatrix matrix = initializeMyMatrixIMG3();

    // minHeap heap = makeEmptyMinHeap();
    // insertMinHeap(heap, 2, 1);
    // insertMinHeap(heap, 3, 1);
    // insertMinHeap(heap, 9, 1);
    // insertMinHeap(heap, 4, 1);
    // insertMinHeap(heap, 1, 1);
    // insertMinHeap(heap, 8, 1);
    // deleteMinHeap(heap);
    // deleteMinHeap(heap);
    // deleteMinHeap(heap);
    // printMinHeap(heap);

    printUniformCostSearchPath(matrix, 'G', 'S');
    // printMatrix(matrix);

    return 0;
}

void printBFSPath(graphMatrix matrix, char src1, char src2)
{
    int8_t BFS_index = BFS(matrix, src1, src2);
    if (BFS_index == -1)
    {
        printf("BFS printPath ERROR: Failed to find the path\n");
        return;
    }

    char name = matrix->names[BFS_index];
    printf("%c", src2);
    while (name != src1)
    {
        printf(" <- %c", name);
        name = matrix->names[BFS(matrix, src1, name)];
    }

    printf(" <- %c\n", src1);
    printf("\n===================\n");
}

void printDFSPath(graphMatrix matrix, char src1, char src2)
{
    int8_t BFS_index = DFS(matrix, src1, src2);
    if (BFS_index == -1)
    {
        printf("BFS printPath ERROR: Failed to find the path\n");
        return;
    }

    char name = matrix->names[BFS_index];
    printf("%c", src2);
    while (name != src1)
    {
        printf(" <- %c", name);
        name = matrix->names[DFS(matrix, src1, name)];
    }

    printf(" <- %c", src1);
}

void printItterativeDFSPath(graphMatrix matrix, char src1, char src2)
{
    int8_t depth = 0;
    int8_t dfsLoop = itterativeDFS(matrix, src1, src2, depth);
    while (dfsLoop == -1)
    {
        depth++;
        dfsLoop = itterativeDFS(matrix, src1, src2, depth);
    }
    printf("\n");
}

void printUniformCostSearchPath(graphMatrix matrix, char src1, char src2)
{
    int8_t UCS_index = uniformCostSearch(matrix, src1, src2);
    if (UCS_index == -1)
    {
        printf("printUniformCostSearchPath printPath ERROR: Failed to find the path\n");
        return;
    }

    char name = matrix->names[UCS_index];
    printf("%c", src2);
    while (name != src1)
    {
        printf(" <- %c", name);
        name = matrix->names[uniformCostSearch(matrix, src1, name)];
    }

    printf(" <- %c\n", src1);
    printf("\n===================\n");
}

int8_t BFS(graphMatrix matrix, char src1, char src2)
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
    matrix->visitStatus[getQueueHead(q)] = VISITED;

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
            int8_t connectionStatus = matrix->cells[header][j]->connection;
            int8_t visitStatus = matrix->visitStatus[j];

            if (connectionStatus == CONNECTED && visitStatus == NOT_VISITED)
            {
                if (matrix->names[j] == src2)
                {
                    removeVisitedState(matrix, length);
                    freeQueue(q);
                    return header;
                }
                enqueue(q, j);
                matrix->visitStatus[j] = VISITED;
            }
        }
        dequeue(q);
    }

    removeVisitedState(matrix, length);
    return -1;
}

int8_t DFS(graphMatrix matrix, char src1, char src2)
{
    stackHeader s = initializeStackHeadder();
    push(s, getIndex(matrix, src1)); // Sorce index
    matrix->visitStatus[getTop(s)] = VISITED;

    int8_t length = getMatrixLength(matrix);

    // while Queue is not empty;
    int8_t count = 0;
    while (s)
    {
        int8_t header = getTop(s);
        pop(s);
        if (header == -1)
        {
            break;
        }

        for (size_t j = 0; j < length; j++)
        {
            int8_t visitStatus = matrix->visitStatus[j];
            int8_t connectionStatus = matrix->cells[header][j]->connection;

            if (connectionStatus == CONNECTED && visitStatus == NOT_VISITED)
            {
                if (matrix->names[j] == src2)
                {
                    removeVisitedState(matrix, length);
                    // freeQueue(q);
                    return header;
                }
                push(s, j);
                matrix->visitStatus[j] = VISITED;
            }
        }
        count++;
        if (count == length * 10)
        {
            break;
        }

        // printStack(s);
        // printf("\n================================\n");
    }

    removeVisitedState(matrix, length);
    return -1;
}

int8_t itterativeDFS(graphMatrix matrix, char src1, char src2, int8_t depth)
{
    stackHeader s = initializeStackHeadder();
    push(s, getIndex(matrix, src1)); // Sorce index
    matrix->visitStatus[getTop(s)] = VISITED;

    int8_t length = getMatrixLength(matrix);

    int8_t nodeDepth[length];
    char previousPath[length];

    for (int8_t i = 0; i < length; i++)
    {
        nodeDepth[i] = -1;
    }

    nodeDepth[getTop(s)] = depth;

    // while Queue is not empty;
    int8_t count = 0;
    while (s)
    {
        int8_t header = getTop(s);

        if (header == -1)
        {
            break;
        }

        int8_t currentDepth = nodeDepth[header] - 1;

        if (matrix->names[header] == src2)
        {
            int8_t node = header;
            printf("%c", matrix->names[node]);
            node = previousPath[node];

            while (matrix->names[node] != src1)
            {
                printf(" <- %c", matrix->names[node]);
                node = previousPath[node];
            }

            printf(" <- %c", src1);

            removeVisitedState(matrix, length);
            // freeQueue(q);
            return header;
        }

        pop(s);

        for (size_t j = 0; j < length; j++)
        {
            int8_t visitStatus = matrix->visitStatus[j];
            int8_t connectionStatus = matrix->cells[header][j]->connection;

            if (connectionStatus == CONNECTED && visitStatus == NOT_VISITED && currentDepth != -1)
            {
                previousPath[j] = header;
                push(s, j);
                matrix->visitStatus[j] = VISITED;
                nodeDepth[j] = currentDepth;
            }
        }
        count++;
        // printStack(s);
        // printf("\n================================\n");
    }

    removeVisitedState(matrix, length);
    return -1;
}

int8_t uniformCostSearch(graphMatrix matrix, char src1, char src2)
{
    minHeap heap = makeEmptyMinHeap();
    insertMinHeap(heap, 0, getIndex(matrix, src1));
    matrix->visitStatus[getMinHeapTop(heap)->data] = VISITED;

    int8_t length = getMatrixLength(matrix);

    int count = 0;
    int8_t previousConnection = 0;
    int8_t lastConnectionForSrc2 = -1;

    int8_t weights[length];

    while (getMinHeapTop(heap))
    {
        struct minHeapArray *top = deleteMinHeap(heap);
        int8_t header = top->data;
        previousConnection = top->weight;

        if (matrix->names[top->data] == src2)
        {
            removeVisitedState(matrix, length);
            // freeQueue(q);
            return lastConnectionForSrc2;
        }

        for (size_t j = 0; j < length; j++)
        {
            // int8_t currentionConnection = matrix->cells[header][j]->connection;
            int8_t connectionStatus = matrix->cells[header][j]->connection;
            int8_t weight = connectionStatus + previousConnection;
            int8_t visitStatus = matrix->visitStatus[j];

            if (connectionStatus != NOT_CONNECTED && (visitStatus == NOT_VISITED || weight < weights[j]))
            {
                if (matrix->names[j] == src2)
                {
                    lastConnectionForSrc2 = top->data;
                }
                weights[j] = weight;
                insertMinHeap(heap, weight, j);
                matrix->visitStatus[j] = VISITED;
            }
        }
    }

    removeVisitedState(matrix, length);
    return -1;
}

void printMinHeapGraph(minHeap h, graphMatrix matrix)
{
    printf("Index:  VALUE:  WEIGHT\n");
    for (int8_t i = 1; i < h->current; i++)
    {
        printf("%-5d:  %-5c:  %-5d\n", i, matrix->names[h->array[i]->data], h->array[i]->weight);
    }
}

void printMatrixArray(int8_t *arr, graphMatrix matrix, int8_t length)
{
    for (int8_t i = 0; i < length; i++)
    {
        printf("%c:   %c\n", matrix->names[i], arr[i]);
    }
    printf("\n");
}

const int8_t SOURCE_QUEUE = 1;
const int8_t GOAL_QUEUE = 2;
const int8_t SOURCE_AND_GOAL_QUEUE = 3;

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
    matrix->visitStatus[getQueueHead(sourceQ)] = VISITED;

    queueHeader goalQ = initializeQueue();
    int8_t src2Index = getIndex(matrix, src2);
    enqueue(goalQ, src2Index); // goal index
    matrix->visitStatus[getQueueHead(goalQ)] = VISITED;

    if (matrix->cells[src1Index][src2Index]->connection == CONNECTED)
    {
        soulation[0] = src1Index;
        soulation[1] = src2Index;
        return soulation;
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
            int8_t visitStatus = matrix->visitStatus[j];
            int8_t connectionStatus = matrix->cells[sourceHeader][j]->connection;
            if (connectionStatus == CONNECTED && visitStatus != SOURCE_QUEUE) // connection == 1
            {
                if (visitStatus == NOT_VISITED)
                {
                    matrix->visitStatus[j] = SOURCE_QUEUE;
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
            if (matrix->cells[sourceHeader][j]->connection == GOAL_QUEUE)
            {
                matrix->cells[sourceHeader][j]->connection = SOURCE_AND_GOAL_QUEUE;
            }

            else if (matrix->cells[sourceHeader][j]->connection == SOURCE_AND_GOAL_QUEUE)
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

            int8_t visitStatus = matrix->visitStatus[j];
            int8_t connectionStatus = matrix->cells[goalHeader][j]->connection;

            if (connectionStatus == CONNECTED && visitStatus != GOAL_QUEUE) // connection == 1
            {
                if (visitStatus == NOT_VISITED)
                {
                    matrix->visitStatus[j] = GOAL_QUEUE;
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
            if (matrix->cells[goalHeader][j]->connection == SOURCE_QUEUE)
            {
                matrix->cells[goalHeader][j]->connection = SOURCE_AND_GOAL_QUEUE;
            }

            else if (matrix->cells[goalHeader][j]->connection == SOURCE_AND_GOAL_QUEUE)
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

graphMatrix initializeMyMatrixIMG3()
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

    createUndirectedWeightedEdge(matrix, 'A', 'S', 1);
    createUndirectedWeightedEdge(matrix, 'A', 'C', 1);
    createUndirectedWeightedEdge(matrix, 'A', 'H', 10);
    createUndirectedWeightedEdge(matrix, 'B', 'S', 4);
    createUndirectedWeightedEdge(matrix, 'B', 'G', 3);
    createUndirectedWeightedEdge(matrix, 'B', 'H', 2);
    createUndirectedWeightedEdge(matrix, 'C', 'G', 3);
    createUndirectedWeightedEdge(matrix, 'C', 'H', 3);
    createUndirectedWeightedEdge(matrix, 'G', 'D', 1);
    createUndirectedWeightedEdge(matrix, 'A', 'D', 9);
    createUndirectedWeightedEdge(matrix, 'D', 'E', 2);

    return matrix;
}

graphMatrix initializeMyMatrixIMG4()
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

    createUndirectedWeightedEdge(matrix, 'A', 'I', 0);
    createUndirectedWeightedEdge(matrix, 'A', 'B', 0);
    createUndirectedWeightedEdge(matrix, 'A', 'C', 0);
    createUndirectedWeightedEdge(matrix, 'C', 'K', 0);
    createUndirectedWeightedEdge(matrix, 'C', 'G', 0);
    createUndirectedWeightedEdge(matrix, 'G', 'K', 0);
    createUndirectedWeightedEdge(matrix, 'G', 'J', 0);
    createUndirectedWeightedEdge(matrix, 'G', 'F', 0);
    createUndirectedWeightedEdge(matrix, 'G', 'H', 0);
    createUndirectedWeightedEdge(matrix, 'H', 'F', 0);
    createUndirectedWeightedEdge(matrix, 'F', 'E', 0);
    createUndirectedWeightedEdge(matrix, 'F', 'J', 0);
    createUndirectedWeightedEdge(matrix, 'D', 'E', 0);
    createUndirectedWeightedEdge(matrix, 'D', 'J', 0);
    createUndirectedWeightedEdge(matrix, 'D', 'K', 0);
    createUndirectedWeightedEdge(matrix, 'D', 'I', 0);
    createUndirectedWeightedEdge(matrix, 'K', 'B', 0);

    return matrix;
}
