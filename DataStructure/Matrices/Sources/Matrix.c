#include "../Headers/Matrix.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will allocate a new matrix,
 * and initialize it's fields, then it will return the new allocated matrix pointer.
 *
 * @param rowsNum the initial number of rows
 * @param colNum the initial number of columns
 * @param freeFun the free  function pointer, that will be called to free the matrix items
 * @param comparator the comparator function pointer, that will be called to compare the matrix items
 * @return it will return the new initialized matrix pointer
 */

Matrix *matrixInitialization(int rowsNum, int colNum,
                             void (*freeFun)(void *), int (*comparator)(const void *, const void *)) {

    if (rowsNum <= 0 || colNum <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "number of rows or the number of columns", "matrix data structure");
        exit(INVALID_ARG);
#endif
    } else if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeing function pointer", "matrix data structure");
        exit(INVALID_ARG);
#endif
    } else if (comparator == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    Matrix *matrix = (Matrix *) malloc(sizeof(Matrix));
    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "matrix pointer", "matrix data structure");
        exit(FAILED_ALLOCATION);
#endif
    }

    matrix->freeFun = freeFun;
    matrix->comparator = comparator;
    matrix->rowsNum = rowsNum;
    matrix->rowsArrLength = rowsNum;
    matrix->colNum = colNum;
    matrix->count = 0;

    matrix->rows = (void ***) malloc(sizeof(void **) * rowsNum);
    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "matrix rows", "matrix data structure");
        exit(FAILED_ALLOCATION);
#endif

    }


    for (int i = 0; i < rowsNum; i++) {
        matrix->rows[i] = (void **) calloc(sizeof(void *), colNum);
        if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_ALLOCATION;
            return NULL;
#else
            fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "matrix columns", "matrix data structure");
            exit(FAILED_ALLOCATION);
#endif

        }

    }


    return matrix;

}


/** This function will take a new item,
 * then it will insert the new item into the provided index.
 *
 * @param matrix the matrix pointer
 * @param item the new item pointer
 * @param rowIndex the index of the row
 * @param colIndex the index of the column
 */

void matrixInsert(Matrix *matrix, void *item, int rowIndex, int colIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item", "matrix data structure");
        exit(INVALID_ARG);
#endif
    } else if (rowIndex < 0 || rowIndex >= matrix->rowsNum || colIndex < 0 || colIndex >= matrix->colNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "row index or the column index", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    if (matrix->rows[rowIndex][colIndex] != NULL) {
        matrix->freeFun(matrix->rows[rowIndex][colIndex]);
        matrix->rows[rowIndex][colIndex] = NULL;
    } else
        matrix->count++;


    matrix->rows[rowIndex][colIndex] = item;

}


/** This function will remove and free the item in the provided index.
 *
 * @param matrix the matrix pointer
 * @param rowIndex the index of the row
 * @param colIndex the index of the column
 */

void matrixRemove(Matrix *matrix, int rowIndex, int colIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (rowIndex < 0 || rowIndex >= matrix->rowsNum || colIndex < 0 || colIndex >= matrix->colNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "matrix data structure");
        exit(OUT_OF_RANGE);
#endif
    }


    if (matrix->rows[rowIndex][colIndex] != NULL) {
        matrix->freeFun(matrix->rows[rowIndex][colIndex]);
        matrix->count--;
    }

    matrix->rows[rowIndex][colIndex] = NULL;

}


/** This function will remove the item in the provided index without freeing it.
 *
 * @param matrix the matrix pointer
 * @param rowIndex the index of the row
 * @param colIndex the index of the column
 */

void matrixRemoveWtoFr(Matrix *matrix, int rowIndex, int colIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (rowIndex < 0 || rowIndex >= matrix->rowsNum || colIndex < 0 || colIndex >= matrix->colNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "matrix data structure");
        exit(OUT_OF_RANGE);
#endif
    }

    matrix->rows[rowIndex][colIndex] = NULL;

}


/** This function will take an index,
 * then it will return the item in the provided index if found,
 * other wise it will return NULL.
 *
 * @param matrix the matrix pointer
 * @param rowIndex the index of the row
 * @param colIndex the index of the column
 * @return it will return the item in the provided index if found, other wise it will return NULL
 */

void *matrixGet(Matrix *matrix, int rowIndex, int colIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (rowIndex < 0 || rowIndex >= matrix->rowsNum || colIndex < 0 || colIndex >= matrix->colNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "row index or the column index", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }

    return matrix->rows[rowIndex][colIndex];

}


/** This function will check if the provided item,
 * exist in the matrix or not, and if it exist the function will return one (1),
 * other wise it will return zero (0).
 *
 * Note: the function will not free the passed item.
 *
 * @param matrix the matrix pointer
 * @param item the item pointer
 * @return it will return one (1) if the item exist in the matrix, other wise it will return zero (0).
 */

int matrixContains(Matrix *matrix, void *item) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    for (int i = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (matrix->rows[i][j] != NULL) {

                if (matrix->comparator(item, matrix->rows[i][j]) == 0)
                    return 1;

            }
        }

    }

    return 0;

}


/** This function will return the index, of the passed item in a MatrixIndex if found,
 * other wise it will return NULL.
 *
 * Note: the function will not free the passed item.
 *
 * @param matrix the matrix pointer
 * @param item the item pointer
 * @return it will return a MatrixIndex pointer that contains the index of the item if found, other wise it will return NULL
 */

MatrixIndex *matrixGetIndex(Matrix *matrix, void *item) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    for (int i = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (matrix->rows[i][j] != NULL) {

                if (matrix->comparator(item, matrix->rows[i][j]) == 0) {
                    MatrixIndex *index = (MatrixIndex *) malloc(sizeof(MatrixIndex));
                    index->row = i;
                    index->col = j;
                    return index;
                }

            }
        }

    }

    return NULL;

}


/** This function will add a new row at the end of the matrix.
 *
 * @param matrix the matrix pointer
 */

void matrixAddRow(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    if (matrix->rowsNum == matrix->rowsArrLength) {

        matrix->rows = (void ***) realloc(matrix->rows, sizeof(void **) * (matrix->rowsNum + 1));
        if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "matrix rows", "matrix data structure");
            exit(FAILED_REALLOCATION);
#endif
        }

        matrix->rowsArrLength++;
    }


    matrix->rows[matrix->rowsNum] = (void **) calloc(sizeof(void *), matrix->colNum);
    if (matrix->rows[matrix->rowsNum] == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new matrix row", "matrix data structure");
        exit(FAILED_ALLOCATION);
#endif
    }

    matrix->rowsNum++;

}


/** This function will add a new row at the provided index.
 *
 * @param matrix the matrix pointer
 * @param index the index of the new row
 */

void matrixAddRowAtIndex(Matrix *matrix, int index) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (index < 0 || index >= matrix->rowsNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "row index", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    if (matrix->rowsNum == matrix->rowsArrLength) {

        matrix->rows = (void ***) realloc(matrix->rows, sizeof(void **) * (matrix->rowsNum + 1));
        if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "matrix rows", "matrix data structure");
            exit(FAILED_REALLOCATION);
#endif
        }

        matrix->rowsArrLength++;

    }

    for (int i = matrix->rowsNum; i > index; i--)
        memcpy(matrix->rows + i, matrix->rows + i - 1, sizeof(void **));

    matrix->rows[index] = (void **) calloc(sizeof(void *), matrix->colNum);

    matrix->rowsNum++;

}


/** This function will add a new column at the end of the matrix.
 *
 * @param matrix the matrix pointer
 */

void matrixAddCol(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < matrix->rowsNum; i++) {
        matrix->rows[i] = (void **) realloc(matrix->rows[i], sizeof(void *) * (matrix->colNum + 1));
        if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "matrix column", "matrix data structure");
            exit(FAILED_REALLOCATION);
#endif
        }

        matrix->rows[i][matrix->colNum] = NULL;
    }

    matrix->colNum++;

}


/** This function will add a new column at the provided index.
 *
 * @param matrix the matrix pointer
 * @param index the index of the new column
 */

void matrixAddColAtIndex(Matrix *matrix, int index) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < matrix->rowsNum; i++) {
        matrix->rows[i] = (void **) realloc(matrix->rows[i], sizeof(void *) * (matrix->colNum + 1));
        if (matrix->rows[i] == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "matrix column", "matrix data structure");
            exit(FAILED_REALLOCATION);
#endif
        }

        for (int j = matrix->colNum; j > index; j--)
            memcpy(matrix->rows[i] + j, matrix->rows[i] + j - 1, sizeof(void *));

        matrix->rows[i][index] = NULL;
    }


    matrix->colNum++;


}


/** This function will remove the row in the provided index,
 * and it will free the row items.
 *
 * @param matrix the matrix pointer
 * @param rowIndex the index of the row that will be deleted
 */

void matrixRemoveRow(Matrix *matrix, int rowIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (rowIndex < 0 || rowIndex >= matrix->rowsNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "row index", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }

    for (int i = 0; i < matrix->colNum; i++) {
        if (matrix->rows[rowIndex][i] != NULL) {
            matrix->freeFun(matrix->rows[rowIndex][i]);
            matrix->rows[rowIndex][i] = NULL;
            matrix->count--;
        }

    }

    free(matrix->rows[rowIndex]);

    for (int i = rowIndex; i < matrix->rowsNum - 1; i++)
        memcpy(matrix->rows + i, matrix->rows + i + 1, sizeof(void **));

    matrix->rowsNum--;

}


/** This function will remove the row in the provided index,
 * without freeing the row items.
 *
 * @param matrix the matrix pointer
 * @param rowIndex the index of the row that will be deleted
 */

void matrixRemoveRowWtoFr(Matrix *matrix, int rowIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (rowIndex < 0 || rowIndex >= matrix->rowsNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "row index", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    for (int i = 0; i < matrix->colNum; i++) {

        if (matrix->rows[rowIndex][i] != NULL) {
            matrix->rows[rowIndex][i] = NULL;
            matrix->count--;
        }

    }

    free(matrix->rows[rowIndex]);

    for (int i = rowIndex; i < matrix->rowsNum - 1; i++)
        memcpy(matrix->rows + i, matrix->rows + i + 1, sizeof(void **));

    matrix->rowsNum--;

}


/** This function will remove the column in the provided index,
 * and it will free the column items.
 *
 * @param matrix the matrix pointer
 * @param colIndex the index of the column that will be removed
 */

void matrixRemoveCol(Matrix *matrix, int colIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (colIndex < 0 || colIndex >= matrix->colNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "column index", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    for (int i = 0; i < matrix->rowsNum; i++) {

        if (matrix->rows[i][colIndex] != NULL) {
            matrix->freeFun(matrix->rows[i][colIndex]);
            matrix->count--;
        }

        for (int j = colIndex; j < matrix->colNum - 1; j++)
            memcpy(matrix->rows[i] + j, matrix->rows[i] + j + 1, sizeof(void *));

        matrix->rows[i][matrix->colNum - 1] = NULL;

    }

    matrix->colNum--;

}


/** This function will remove the column in the provided index,
 * without freeing the column items.
 *
 * @param matrix the matrix pointer
 * @param colIndex the index of the column that will be removed
 */

void matrixRemoveColWtoFr(Matrix *matrix, int colIndex) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (colIndex < 0 || colIndex >= matrix->colNum) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "column index", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


    for (int i = 0; i < matrix->rowsNum; i++) {

        if (matrix->rows[i][colIndex] != NULL)
            matrix->count--;

        for (int j = colIndex; j < matrix->colNum - 1; j++)
            memcpy(matrix->rows[i] + j, matrix->rows[i] + j + 1, sizeof(void *));

        matrix->rows[i][matrix->colNum - 1] = NULL;

    }

    matrix->colNum--;

}


/** This function will print the matrix as following:
 *
 * [item1, item2, item3]
 *
 * [item4, item5, item6]
 *
 * Note: you must print the item without any additions.
 *
 * @param matrix the matrix pointer
 * @param printFun the printing function pointer, that will be called to print the items
 */

void printMatrix(Matrix *matrix, void (*printFun)(void *)) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "matrix data structure");
        exit(INVALID_ARG);
#endif
    }


#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
    for (int i = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (matrix->rows[i][j] != NULL)
                printFun(matrix->rows[i][j]);

        }

    }
#else
    for (int i = 0; i < matrix->rowsNum; i++) {
        fprintf(stdout, "[");
        for (int j = 0; j < matrix->colNum; j++) {
            if (matrix->rows[i][j] != NULL)
                printFun(matrix->rows[i][j]);
            else
                fprintf(stdout, "NULL");

            if (j != matrix->colNum - 1)
                fprintf(stdout, ", ");

        }

        fprintf(stdout, "]%c", i != matrix->rowsNum - 1 ? '\n' : '\0');

    }
#endif


}


/** This function will return the number of rows in the matrix.
 *
 * @param matrix the matrix pointer
 * @return it will return the number of rows in the matrix
 */

int matrixGetNumberOfRows(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    return matrix->rowsNum;

}


/** This function will return the number of columns in the matrix.
 *
 * @param matrix the matrix pointer
 * @return it will return the number of columns in the matrix
 */

int matrixGetNumberOfCols(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    return matrix->colNum;

}


/** This function will return the number of items in the matrix.
 *
 * @param matrix the matrix pointer
 * @return it will return the number of items in the matrix
 */

int matrixGetSize(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    return matrix->count;

}


/** This function will check if the matrix is empty or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param matrix the matrix pointer
 * @return it will return 1 if the matrix is empty, other wise it will return 0
 */

int matrixIsEmpty(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    return matrix->count == 0;

}


/** This function will return a double void array that contains the matrix items.
 *
 * Note: the returned array will contains the items in the same order of every row sequentially.
 *
 * @param matrix the matrix pointer
 * @return it will return an array that contains the matrix items
 */

void **matrixToArray(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }


    void **arr = (void **) malloc(sizeof(void *) * matrixGetSize(matrix));
    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "array pointer", "matrix data structure");
        exit(FAILED_ALLOCATION);
#endif
    }

    for (int i = 0, index = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (matrix->rows[i][j] != NULL)
                arr[index++] = matrix->rows[i][j];

        }

    }

    return arr;

}


/** This function will clear the matrix and free it's items,
 * without destroying the matrix.
 *
 * @param matrix the matrix pointer
 */

void clearMatrix(Matrix *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < matrix->rowsNum; i++) {

        for (int j = 0; j < matrix->colNum; j++) {

            if (matrix->rows[i][j] != NULL)
                matrixRemove(matrix, i, j);

        }

    }

}


/** This function will destroy and free the matrix with all it's items.
 *
 * @param matrix the matrix pointer
 */

void destroyMatrix(void *matrix) {

    if (matrix == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "matrix", "matrix data structure");
        exit(NULL_POINTER);
#endif

    }

    clearMatrix(matrix);

    for (int i = 0; i < ((Matrix *) matrix)->rowsNum; i++)
        free(((Matrix *) matrix)->rows[i]);

    free(((Matrix *) matrix)->rows);
    free(matrix);

}