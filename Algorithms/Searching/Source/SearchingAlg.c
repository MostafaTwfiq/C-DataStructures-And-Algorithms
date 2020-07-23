#include "../Header/SearchingAlg.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/Lists/Headers/Vector.h"



int binarySearchHelper(void *arr, void *value, int fIndex, int lIndex, int elemSize, int (*cmp)(const void *, const void *));


int ternarySearchHelper(void *arr, void *value, int fIndex, int lIndex, int elemSize, int (*cmp)(const void *, const void *));



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
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "binary search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "binary search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "binary search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "binary search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "binary search");
        exit(INVALID_ARG);
    }

    int fIndex = 0, lIndex = length - 1, middleIndex;
    while (fIndex <= lIndex) {

        middleIndex = (fIndex + lIndex) / 2;

        if ( cmp(value, arr + middleIndex * elemSize) == 0 )
            return middleIndex;
        else if ( cmp(value, arr + middleIndex * elemSize) < 0 )
            lIndex = middleIndex - 1;
        else
            fIndex = middleIndex + 1;

    }

    return -1;

}



int binarySearchR(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "binary search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "binary search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "binary search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "binary search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "binary search");
        exit(INVALID_ARG);
    }

    return binarySearchHelper(arr, value, 0, length - 1, elemSize, cmp);

}




int binarySearchHelper(void *arr, void *value, int fIndex, int lIndex, int elemSize, int (*cmp)(const void *, const void *)) {
    if (fIndex > lIndex)
        return -1;

    int middleIndex = (fIndex + lIndex) / 2;

    if ( cmp(value, arr + middleIndex * elemSize) == 0 )
        return middleIndex;
    else if ( cmp(value, arr + middleIndex * elemSize) < 0 )
        return binarySearchHelper(arr, value, fIndex, middleIndex - 1, elemSize, cmp);
    else
        return binarySearchHelper(arr, value, middleIndex + 1, lIndex, elemSize, cmp);


}







int ternarySearchI(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "ternary search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "ternary search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "ternary search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "ternary search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "ternary search");
        exit(INVALID_ARG);
    }


    int fIndex = 0, lIndex = length - 1, partitionSize, fMiddle, sMiddle;
    while (fIndex <= lIndex) {

        partitionSize = (lIndex - fIndex) / 3;
        fMiddle = fIndex + partitionSize;
        sMiddle = lIndex - partitionSize;

        if ( cmp(value, arr + fMiddle * elemSize) == 0 )
            return fMiddle;
        else if (cmp(value, arr + sMiddle * elemSize) == 0)
            return sMiddle;
        else if ( cmp(value, arr + fMiddle * elemSize) < 0 )
            lIndex = fMiddle - 1;
        else if ( cmp(value, arr + sMiddle * elemSize) > 0)
           fIndex = sMiddle + 1;
        else {
            fIndex = fMiddle + 1;
            lIndex = sMiddle - 1;
        }

    }

    return -1;

}





int ternarySearchR(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "ternary search");
        exit(NULL_POINTER);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "ternary search");
        exit(INVALID_ARG);
    } else if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "ternary search");
        exit(INVALID_ARG);
    } else if (length < 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "ternary search");
        exit(INVALID_ARG);
    } else if (elemSize <= 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "ternary search");
        exit(INVALID_ARG);
    }

    return ternarySearchHelper(arr, value, 0, length - 1, elemSize, cmp);

}




int ternarySearchHelper(void *arr, void *value, int fIndex, int lIndex, int elemSize, int (*cmp)(const void *, const void *)) {
    if (fIndex > lIndex)
        return -1;


    int partitionSize = (lIndex - fIndex) / 3;
    int fMiddle = fIndex + partitionSize;
    int sMiddle = lIndex - partitionSize;

    if ( cmp(value, arr + fMiddle * elemSize) == 0 )
        return fMiddle;
    else if (cmp(value, arr + sMiddle * elemSize) == 0)
        return sMiddle;
    else if ( cmp(value, arr + fMiddle * elemSize) < 0 )
        return ternarySearchHelper(arr, value, fIndex, fMiddle - 1, elemSize, cmp);
    else if ( cmp(value, arr + sMiddle * elemSize) > 0)
        return ternarySearchHelper(arr, value, sMiddle + 1, lIndex, elemSize, cmp);
    else
        return ternarySearchHelper(arr, value, fMiddle + 1, sMiddle - 1, elemSize, cmp);


}





