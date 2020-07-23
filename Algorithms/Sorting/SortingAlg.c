#include "SortingAlg.h"
#include "../../System/Utils.h"
#include "../../DataStructure/Tables/Headers/HashMap.h"



void swap(void *first, void *second, int elemSize);

void mergeSortHelper(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void quickSortHelper(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));










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
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "insertion sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "insertion sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "insertion sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "insertion sort");
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
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "merge sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "merge sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "merge sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "merge sort");
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

    for (int i = middleLength - 1; i >= 0; i--) {

        for (int j = i; j < length - 1; j++) {
            if ( cmp(arr + j * elemSize, arr + (j + 1) * elemSize ) > 0 )
                swap(arr + j * elemSize, arr + (j + 1) * elemSize, elemSize);
            else
                break;


        }

    }

}



void quickSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "quick sort");
        exit(NULL_POINTER);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "quick sort");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "quick sort");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "quick sort");
        exit(INVALID_ARG);
    }

    quickSortHelper(arr, length, elemSize, cmp);

    //TODO: try to improve the quick sort because the worst case << O(n^2) >>.

}

void quickSortHelper(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {
    if (length <= 0)
        return;

    void *boundaryPointer = arr - elemSize;


    for (int i = 0; i < length; i++) {
        if ( cmp(arr + (length - 1) * elemSize, arr + i * elemSize) >= 0) {
            boundaryPointer += elemSize;
            swap(boundaryPointer, arr + i * elemSize, elemSize);
        }

    }

    int firstHalfLength = ( (boundaryPointer - arr) / elemSize );
    int secondHalfLength = length - firstHalfLength - 1;


    quickSortHelper(arr, firstHalfLength, elemSize, cmp);
    quickSortHelper(boundaryPointer + elemSize, secondHalfLength, elemSize, cmp);

}




void countingSortA(unsigned int *arr, int length, unsigned int rangeStart, unsigned int rangeEnd) {
    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "counting sort");
        exit(NULL_POINTER);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "counting sort");
        exit(INVALID_ARG);
    } else if (rangeEnd < rangeStart) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start and end range", "counting sort");
        exit(INVALID_ARG);
    }

    unsigned int countingArrLength = rangeEnd - rangeStart + 1;
    unsigned int *countingArr = (unsigned int *) calloc(sizeof(unsigned int ), countingArrLength);
    for (int i = 0; i < length; i++)
        countingArr[arr[i] - rangeStart]++;

    int index = 0;
    for (int i = 0; i < countingArrLength; i++) {

        while (countingArr[i] != 0) {
            arr[index++] = i + rangeStart;
            countingArr[i]--;
        }

    }


}







void intFreeFun(void *n) {
    free(n);
}

int intCmpAl(const void *n1, const void * n2) {
    return *(int *)n1 - *(int *)n2;
}

unsigned int *generateIntPointer(unsigned int *num) {
    unsigned int *newInt = (unsigned int *) malloc(sizeof(unsigned int));
    memcpy(newInt, num, sizeof(unsigned int));

    return newInt;
}



void countingSortH(unsigned int *arr, int length, unsigned int rangeStart, unsigned int rangeEnd) {
    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "counting sort");
        exit(NULL_POINTER);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "counting sort");
        exit(INVALID_ARG);
    } else if (rangeEnd < rangeStart) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start and end range", "counting sort");
        exit(INVALID_ARG);
    }

    HashMap *countingMap = hashMapInitialization(intFreeFun, intFreeFun, intCmpAl);

    for (int i = 0; i < length; i++) {
        unsigned int *newNumPointer = generateIntPointer(arr + i );

        if (!hashMapContains(countingMap, newNumPointer, sizeof(unsigned int))) {
            unsigned int initialCount = 1;
            unsigned int *countPointer = generateIntPointer(&initialCount);
            hashMapInsert(countingMap, newNumPointer, sizeof(unsigned int), countPointer);
        } else {
            unsigned int *currentCount = hashMapGet(countingMap, newNumPointer, sizeof(unsigned int));
            *currentCount += 1;
            unsigned int *newCount = generateIntPointer(currentCount);
            hashMapInsert(countingMap, newNumPointer, sizeof(unsigned int), newCount);
        }

    }

    for (unsigned int i = rangeStart, index = 0; i <= rangeEnd; i++) {

        unsigned int *currentCount = (unsigned int *) hashMapGet(countingMap, &i, sizeof(unsigned int));

        while (currentCount != NULL && *currentCount > 0) {
            arr[index++] = i;
            *currentCount -= 1;
        }

    }

    destroyHashMap(countingMap);


}



void swap(void *first, void *second, int elemSize) {

    void *temp = (void *) malloc(elemSize);
    memcpy(temp, first, elemSize);
    memcpy(first, second, elemSize);
    memcpy(second, temp, elemSize);

    free(temp);

}



