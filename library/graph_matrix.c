#include "graph_matrix.h"

const int8_t NOT_CONNECTED = 0;
const int8_t NULL_CONNECTED = -1;
const int8_t CONNECTED = 1;

const int8_t NOT_VISITED = 0;
const int8_t VISITED = 1;

typedef struct matrixCellNode *matrixCell;
matrixCell initializeMatrixCell();

graphMatrix initializeMatrixArray()
{
    graphMatrix matrix = (graphMatrix)malloc(sizeof(struct graphMatrixNode));
    if (!matrix)
    {
        return NULL;
    }

    for (size_t i = 0; i < MAX_VERTEX_NUM; i++)
    {
        matrix->names[i] = '\0';
        matrix->visitStatus[i] = NOT_VISITED;
    }

    matrix->cells = (matrixCell **)malloc(sizeof(matrixCell *) * MAX_VERTEX_NUM);
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
    {
        matrix->cells[i] = (matrixCell *)malloc(sizeof(matrixCell) * MAX_VERTEX_NUM);
        for (int j = 0; j < MAX_VERTEX_NUM; j++)
        {
            matrix->cells[i][j] = initializeMatrixCell();
        }
    }

    return matrix;
}

matrixCell initializeMatrixCell()
{
    matrixCell cell = (matrixCell)malloc(sizeof(struct matrixCellNode));
    if (cell == NULL)
    {
        return NULL;
    }
    cell->connection = NULL_CONNECTED;
    return cell;
}

void addVertex(graphMatrix matrix, char name)
{
    int8_t length = -1;
    for (size_t i = 0; i < MAX_VERTEX_NUM; i++)
    {
        length++;
        if (!matrix->names[i])
        {
            matrix->names[i] = name;
            break;
        }
    }

    for (int8_t i = 0; i <= length; i++)
    {
        matrix->cells[i][length]->connection = NOT_CONNECTED;
    }

    for (int8_t j = 0; j <= length; j++)
    {
        matrix->cells[length][j]->connection = NOT_CONNECTED;
    }
}

void createUndirectedEdge(graphMatrix matrix, char src1, char src2)
{
    int8_t src1_index = -1, src2_index = -1;
    src1_index = getIndex(matrix, src1);
    src2_index = getIndex(matrix, src2);

    if (src1_index == -1 || src2_index == -1)
    {
        printf("Invalid Name");
        return;
    }

    matrix->cells[src1_index][src2_index]->connection = CONNECTED;
    matrix->cells[src2_index][src1_index]->connection = CONNECTED;
}

void createDirectedEdge(graphMatrix matrix, char src1, char src2)
{
    int8_t src1_index = -1, src2_index = -1;
    src1_index = getIndex(matrix, src1);
    src2_index = getIndex(matrix, src2);

    if (src1_index == -1 || src2_index == -1)
    {
        printf("Invalid Name");
        return;
    }

    matrix->cells[src1_index][src2_index]->connection = CONNECTED;
}

void createUndirectedWeightedEdge(graphMatrix matrix, char src1, char src2, int8_t weight)
{
    if (weight < 0)
    {
        printf("ERROR createUndirectedWeightedEdge: Unvalid weight\n");
        return;
    }

    int8_t src1_index = -1, src2_index = -1;
    src1_index = getIndex(matrix, src1);
    src2_index = getIndex(matrix, src2);

    if (src1_index == -1 || src2_index == -1)
    {
        printf("Invalid Name");
        return;
    }

    matrix->cells[src1_index][src2_index]->connection = weight;
    matrix->cells[src2_index][src1_index]->connection = weight;
}

void createDirectedWeightedEdge(graphMatrix matrix, char src1, char src2, int8_t weight)
{
    if (weight < 0)
    {
        printf("ERROR createUndirectedWeightedEdge: Unvalid weight\n");
        return;
    }

    int8_t src1_index = -1, src2_index = -1;
    src1_index = getIndex(matrix, src1);
    src2_index = getIndex(matrix, src2);

    if (src1_index == -1 || src2_index == -1)
    {
        printf("Invalid Name");
        return;
    }

    matrix->cells[src1_index][src2_index]->connection = weight;
}

int8_t getIndex(graphMatrix matrix, char src)
{
    int index = 0;
    while (matrix->names[index])
    {
        if (matrix->names[index] == src)
        {
            return index;
        }
        index++;
    }

    return -1;
}

void printMatrix(graphMatrix matrix)
{
    int size = 0;
    printf("  ");
    while (size < MAX_VERTEX_NUM && matrix->names[size] != '\0')
    {
        printf("%c ", matrix->names[size]);
        size++;
    }
    printf("\n");

    for (int i = 0; i < size; i++)
    {
        printf("%c ", matrix->names[i]);
        for (int j = 0; j < size; j++)
        {
            printf("%d ", matrix->cells[i][j]->connection);
        }
        printf("\n");
    }
}

int8_t getMatrixLength(graphMatrix matrix)
{
    int8_t length = 0;
    while (matrix->names[length])
    {
        length++;
    }

    return length;
}

void removeVisitedState(graphMatrix matrix, int8_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        matrix->visitStatus[i] = NOT_VISITED;
    }
}

void removeConnections(graphMatrix matrix, int8_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; j < length; j++)
        {
            matrix->cells[i][j]->connection = NOT_CONNECTED;
        }
    }
}

char getNodeName(graphMatrix matrix, int8_t index)
{
    return matrix->names[index];
}
