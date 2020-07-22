#include "SortingAlg.h"
#include "../../System/Utils.h"



void swap(void *first, void *second, int elemSize);

void mergeSortHelper(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));










void bubbleSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "bubble sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "bubble sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "bubble sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "bubble sort");
        exit(INVALID_ARG);
    }

    short swapFlag = 0;

    for (int i = length - 1; i > 0; i--) {

        swapFlag = 0;

        for (int j = 0; j < i; j++) {

            if (cmp( arr + j * elemSize, arr + (j + 1) * elemSize ) > 0) {
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);
                swapFlag = 1;
            }

        }

        if (!swapFlag)
            break;

    }

}











void selectionSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "selection sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "selection sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "selection sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "selection sort");
        exit(INVALID_ARG);
    }

    void *currentElement = NULL;

    for (int i = 0; i < length; i++) {
        currentElement = arr + i * elemSize; // the min or max element depends on if the sorting descending order or not
        for (int j = i; j < length; j++) {

            if ( cmp(currentElement, arr + j * elemSize ) > 0 )
                currentElement = arr + j * elemSize;

        }

        if (currentElement != arr + i * elemSize)
            swap(arr + i * elemSize, currentElement, elemSize);

    }
}









void insertionSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "selection sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "selection sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "selection sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "selection sort");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < length; i++) {
        void *currentElement = (void *) malloc(elemSize);
        memcpy(currentElement, arr + i * elemSize, elemSize);
        int rightIndex = 0;
        for (int j = 0; j < i; j++) {

            if ( cmp(currentElement, arr + j * elemSize) <= 0) {
                rightIndex = j;
                break;
            }

        }

        for (int j = i; j > rightIndex; j--)
            memcpy(arr + j * elemSize, arr + (j - 1) * elemSize, elemSize);

        memcpy(arr + rightIndex * elemSize, currentElement, elemSize);

    }



}






void mergeSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "selection sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "selection sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "selection sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "selection sort");
        exit(INVALID_ARG);
    }

    mergeSortHelper(arr, length, elemSize, cmp);

}


void mergeSortHelper(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (length <= 0)
        return;

    int middleLength = (int) (length / 2);
    int secondHalfLength = length - middleLength == length ? 0 : length - middleLength;

    mergeSortHelper(arr, middleLength, elemSize, cmp);
    mergeSortHelper(arr + middleLength * elemSize, secondHalfLength, elemSize, cmp);

    //bubbleSort(arr, length, elemSize, cmp);

    for (int i = middleLength - 1; i >= 0; i--) {

        for (int j = i; j < length - 1; j++) {
            if ( cmp(arr + j * elemSize, arr + (j + 1) * elemSize ) > 0 )
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);
            else
                break;


        }

    }

}





void swap(void *first, void *second, int elemSize) {

    void *temp = (void *) malloc(elemSize);
    memcpy(temp, first, elemSize);
    memcpy(first, second, elemSize);
    memcpy(second, temp, elemSize);

    free(temp);

}