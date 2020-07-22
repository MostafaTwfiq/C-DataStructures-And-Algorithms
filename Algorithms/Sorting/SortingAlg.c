#include "SortingAlg.h"
#include "../../System/Utils.h"



void swap(void *first, void *second, int elemSize);



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


    for (int i = length - 1; i > 0; i--) {

        for (int j = 0; j < i; j++) {

            if (cmp( arr + j * elemSize, arr + (j + 1) * elemSize ) > 0)
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);

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