#ifndef C_DATASTRUCTURES_MATRIX_H
#define C_DATASTRUCTURES_MATRIX_H


typedef struct Matrix {

    void ***rows;
    int rowsNum;
    int rowsArrLength;
    int colNum;
    int count;
    void (*freeFun)(void *);
    int (*comparator)(const void *, const void *);

} Matrix;



typedef struct MatrixIndex {

    int row;
    int col;

} MatrixIndex;



Matrix *matrixInitialization(int rowsNum, int colNum, void (*freeFun)(void *), int (*comparator)(const void *, const void *));

void matrixInsert(Matrix *matrix, void *item, int rowIndex, int colIndex);

void matrixRemove(Matrix *matrix, int rowIndex, int colIndex);

void matrixRemoveWtoFr(Matrix *matrix, int rowIndex, int colIndex);

void *matrixGet(Matrix *matrix, int rowIndex, int colIndex);

int matrixContains(Matrix *matrix, void *item);

MatrixIndex *matrixGetIndex(Matrix *matrix, void *item);

void matrixAddRow(Matrix *matrix);

void matrixAddRowAtIndex(Matrix *matrix, int index);

void matrixAddCol(Matrix *matrix);

void matrixAddColAtIndex(Matrix *matrix, int index);

void matrixRemoveRow(Matrix *matrix, int rowIndex);

void matrixRemoveRowWtoFr(Matrix *matrix, int rowIndex);

void matrixRemoveCol(Matrix *matrix, int colIndex);

void matrixRemoveColWtoFr(Matrix *matrix, int colIndex);

void printMatrix(Matrix *matrix, void (*printFun)(void *));

int matrixGetNumberOfRows(Matrix *matrix);

int matrixGetNumberOfCols(Matrix *matrix);

int matrixGetSize(Matrix *matrix);

void **matrixToArray(Matrix *matrix);

void clearMatrix(Matrix *matrix);

void destroyMatrix(Matrix *matrix);

#endif //C_DATASTRUCTURES_MATRIX_H
