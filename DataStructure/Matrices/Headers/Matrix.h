#ifndef C_DATASTRUCTURES_MATRIX_H
#define C_DATASTRUCTURES_MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct Matrix
*  @brief This structure implements a basic generic Matrix.
*  @var Matrix::rows
*  Member 'rows' is a pointer to the matrix rows (arrays).
*  @var Matrix::rowsNum
*  Member 'rowsNum' holds the current number of rows.
*  @var Matrix::rowsArrLength
*  Member 'rowsArrLength' holds the current allocated rows number.
*  @var Matrix::colNum
*  Member 'colNum' holds the current number of columns
*  @var Matrix:: 'freeFun'
*  Member 'freeFun' holds pointer to the function responsible for freeing the elements stored in the matrix.
*  @var Matrix:: 'comparator'
*  Member 'comparator' holds pointer to the function responsible for comparing the elements stored in the matrix.
*/

typedef struct Matrix {

    void ***rows;
    int rowsNum;
    int rowsArrLength;
    int colNum;
    int count;

    void (*freeFun)(void *);

    int (*comparator)(const void *, const void *);

} Matrix;


/** @struct MatrixIndex
*  @brief This structure will be useful to hold a matrix item index.
*  @var MatrixIndex::row
*  Member 'row' holds the index of the item row.
*  @var MatrixIndex::col
*  Member 'col' holds the index of the item column.
*/

typedef struct MatrixIndex {

    int row;
    int col;

} MatrixIndex;


Matrix *
matrixInitialization(int rowsNum, int colNum, void (*freeFun)(void *), int (*comparator)(const void *, const void *));

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

int matrixIsEmpty(Matrix *matrix);

void **matrixToArray(Matrix *matrix);

void clearMatrix(Matrix *matrix);

void destroyMatrix(void *matrix);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_MATRIX_H
