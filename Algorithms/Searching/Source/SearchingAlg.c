#include "../Header/SearchingAlg.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Lists/Headers/Vector.h"



int binarySearchHelper(void *arr, void *value, int fIndex, int sIndex, int elemSize, int (*cmp)(const void *, const void *));




int linearSearch(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < length; i++) {
        if ( cmp(value, arr + i * elemSize) == 0)
            return i;

    }

    return -1;

}


int linearSearchGetLast(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
    }

    for (int i = length - 1; i >= 0; i--) {
        if ( cmp(value, arr + i * elemSize) == 0)
            return i;

    }

    return -1;

}



void intFreeFunSeAl(void *n) {
    free(n);
}

int intCmpSeAl(const void *n1, const void * n2) {
    return *(int *)n1 - *(int *)n2;
}

unsigned int *generateIntPointerSeAl(unsigned int *num) {
    unsigned int *newInt = (unsigned int *) malloc(sizeof(unsigned int));
    memcpy(newInt, num, sizeof(unsigned int));

    return newInt;
}


Vector *linearSearchGetAll(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
    }

    Vector *indicesVector = vectorInitialization(2, intFreeFunSeAl, intCmpSeAl);

    for (unsigned int i = 0; i < length; i++) {
        if ( cmp(value, arr + i * elemSize) == 0)
            vectorAdd(indicesVector, generateIntPointerSeAl(&i));

    }

    return indicesVector;

}









int binarySearchI(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
    }

    if (length == 0)
        return -1;


    int fIndex = 0, sIndex = length, middleIndex;
    while (fIndex <= sIndex) {
        middleIndex = (fIndex + sIndex) / 2;

        if ( cmp(value, arr + middleIndex * elemSize) == 0 )
            return middleIndex;
        else if ( cmp(value, arr + middleIndex * elemSize) < 0 )
            sIndex = middleIndex - 1;
        else
            fIndex = middleIndex + 1;
    }

    return -1;

}



int binarySearchR(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "linear search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "linear search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "linear search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "linear search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "linear search");
        exit(INVALID_ARG);
    }

    if (length == 0)
        return -1;

    return binarySearchHelper(arr, value, 0, length, elemSize, cmp);

}

int binarySearchHelper(void *arr, void *value, int fIndex, int sIndex, int elemSize, int (*cmp)(const void *, const void *)) {
    if (fIndex > sIndex)
        return -1;

    int middleIndex = (fIndex + sIndex) / 2;

    if ( cmp(value, arr + middleIndex * elemSize) == 0 )
        return middleIndex;
    else if ( cmp(value, arr + middleIndex * elemSize) < 0 )
        return binarySearchHelper(arr, value, fIndex, middleIndex - 1, elemSize, cmp);
    else
        return binarySearchHelper(arr, value, middleIndex + 1, sIndex, elemSize, cmp);


}