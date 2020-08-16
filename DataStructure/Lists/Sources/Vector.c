#include "../Headers/Vector.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will take the initial length of the vector, and the freeing and comparator functions as a parameter,
 * then it will initialize a new vector in the memory and set it's fields then return it.
 *
 * @param initialLength the initial length of the vector.
 * @param freeFun the function address that will be called to free the vector items.
 * @param comparator the comparator function address, that will be called to compare two items in the vector
 * @return it will return the initialized vector pointer
 */

Vector *
vectorInitialization(int initialLength, void (*freeFun)(void *), int (*comparator)(const void *, const void *)) {
    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function", "vector data structure");
        exit(INVALID_ARG);
#endif

    } else if (initialLength <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "initial length", "vector data structure");
        exit(INVALID_ARG);
#endif

    }

    Vector *list = (Vector *) malloc(sizeof(Vector));
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "data structure", "vector data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    list->arr = (void **) malloc(sizeof(void *) * initialLength);
    if (list->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "items memory", "vector data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    list->length = initialLength > 0 ? initialLength : 1;
    list->count = 0;
    list->freeItem = freeFun;
    list->comparator = comparator;

    return list;
}


/** This function will take the vector address, and the item address as a parameters,
 * then it will put the item in the end of the vector.
 *
 * @param list the vector address
 * @param item the item address
 */

void vectorAdd(Vector *list, void *item) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "vector data structure");
        exit(INVALID_ARG);
#endif

    }

    if (list->count == list->length) {
        list->length *= 2;

        list->arr = (void **) realloc(list->arr, sizeof(void *) * list->length);
        if (list->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "items memory", "vector data structure");
            exit(FAILED_REALLOCATION);
#endif

        }

    }


    list->arr[list->count++] = item;

}


/** This function will take the vector address, and the item address as a parameters,
 * then it will put the new item in provided index.
 *
 * @param list the vector address
 * @param item the item address
 * @param index the index of the new item
 */

void vectorAddAtIndex(Vector *list, void *item, int index) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "vector data structure");
        exit(INVALID_ARG);
#endif

    } else if (index < 0 || index >= vectorGetLength(list)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "vector data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    if (list->count == list->length) {
        list->length *= 2;

        list->arr = (void **) realloc(list->arr, sizeof(void *) * list->length);
        if (list->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_REALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "items memory", "vector data structure");
            exit(FAILED_REALLOCATION);
#endif

        }

    }


    for (int i = list->count++; i > index; i--)
        list->arr[i] = list->arr[i - 1];


    list->arr[index] = item;

}


/** This function will take the vector address, the items array, and the length of items array as a parameters,
 * then it will copy the items array into the vector.
 *
 * @param list the vector address
 * @param array the array address that will be inserted in the vector
 * @param arrayLength the length of the array that will be added
 */

void vectorAddAll(Vector *list, void **array, int arrayLength) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array", "vector data structure");
        exit(INVALID_ARG);
#endif

    }

    for (int i = 0; i < arrayLength; i++)
        vectorAdd(list, array[i]);

}


/** This function will take the vector as a parameter,
 * then it will remove the last item in the vector.
 *
 * Note: if the vector is empty then the program will be terminated.
 *
 * @param list the vector address
 */

void vectorRemove(Vector *list) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (vectorIsEmpty(list)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "vector data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    list->freeItem(list->arr[vectorGetLength(list) - 1]);

    list->count--;

}


/** This function will take the vector as a parameter,
 * then it will remove the last item in the vector, without freeing the item.
 *
 * Note: if the vector is empty then the program will be terminated.
 *
 * @param list the vector address
 * @return it will return the deleted item pointer
 */

void *vectorRemoveWtFr(Vector *list) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (vectorIsEmpty(list)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "vector data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return list->arr[--list->count];

}


/** This function will take the vector address, and the index as a parameters,
 * then it will remove the item in the given index from the vector.
 *
 * Note: if the index is out of the vector range then the program will be terminated.
 *
 * @param list the vector address
 * @param index the index of the item that will be deleted
 */

void vectorRemoveAtIndex(Vector *list, int index) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (index < 0 || index >= vectorGetLength(list)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "vector data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    list->freeItem(list->arr[index]);
    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];


}


/** This function will take the vector address, and the index as a parameters,
 * then it will remove the item in the given index from the vector, without freeing the item.
 *
 * Note: if the index is out of the vector range then the program will be terminated.
 *
 * @param list the vector address
 * @param index the index of the item that will be deleted
 * @return it will return the deleted item pointer
 */

void *vectorRemoveAtIndexWtFr(Vector *list, int index) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (index < 0 || index >= vectorGetLength(list)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "vector data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    void *itemToReturn = list->arr[index];
    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];

    return itemToReturn;

}


/** This function will take the vector address, and the item address as a parameters,
 * then it will return one (1) if the item is in the vector,
 * other wise it will return zero (0).
 *
 * Note: comparator function should return zero (0) when the two items are equal.
 *
 * Note: this function will not free the passed item.
 *
 * @param list the vector address
 * @param item the item that will be compared by address
 * @return it will return one if the item is in the vector other wise it will return zero
 */

int vectorContains(Vector *list, void *item) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return 0;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return 0;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "vector data structure");
        exit(INVALID_ARG);
#endif

    } else if (list->comparator == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return 0;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < list->count; i++) {

        if (list->comparator(item, list->arr[i]) == 0)
            return 1;

    }

    return 0;

}


/** This function will take the vector address, and the item address as a parameters,
 * then it will return the index of the item if found,
 * other wise it will return minus one (-1).
 *
 * Note: comparator function should return zero (0) when the two items are equal.
 *
 * Note: this function will not free the passed item.
 *
 * @param list the vector address
 * @param item the item address that will be searching for
 * @return it will return the item address if found, other wise it will return minus one
 */

int vectorGetIndex(Vector *list, void *item) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "vector data structure");
        exit(INVALID_ARG);
#endif

    } else if (list->comparator == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < list->count; i++) {

        if (list->comparator(list->arr[i], item) == 0)
            return i;

    }

    return -1;

}


/** This function will take the vector address, and the item address as a parameters,
 * then it will return the last index of the item if found,
 * other wise it will return minus one (-1).
 *
 * Note: comparator function should return zero (0) when the two items are equal.
 *
 * Note: this function will not free the passed item.
 *
 * @param list the vector address
 * @param item the item address that will be searching for
 * @return it will return the item address if found, other wise it will return minus one
 */

int vectorGetLastIndex(Vector *list, void *item) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "vector data structure");
        exit(INVALID_ARG);
#endif

    } else if (list->comparator == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = list->count - 1; i >= 0; i--) {

        if (list->comparator(list->arr[i], item) == 0)
            return i;

    }

    return -1;

}


/** This function will take the vector address, and the index as a parameters,
 * then it will return the item at the given index.
 *
 * Note: if the index is out of the vector range then the program will be terminated.
 *
 * @param list the vector address
 * @param index the item index
 * @return it will return a void pointer to the item
 */

void *vectorGet(Vector *list, int index) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (index < 0 || index >= vectorGetLength(list)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "vector data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    return list->arr[index];

}


/** This function will take the vector address as a parameter,
 * then it will return a void pointer array that consist of the vector elements.
 *
 * @param list the vector address
 * @return it will return a double void pointer to an array that has a copy of the items
 */

void **vectorToArray(Vector *list) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    void **array = (void **) malloc(sizeof(void *) * vectorGetLength(list));
    if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "vector data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = 0; i < vectorGetLength(list); i++)
        array[i] = list->arr[i];

    return array;

}


/** This function will take the vector address, the start index, and the end index as a parameters,
 * then it will return a void pointer array that consist of the items at the start index to end index.
 *
 * @param list the vector address
 * @param start the start index
 * @param end the end index
 * @return it will return a double void pointer that has a copy of the items in the vector
 */

void **vectorToSubArray(Vector *list, int start, int end) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (start < 0 || end > vectorGetLength(list) || start > end) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "vector data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    void **array = (void **) malloc(sizeof(void *) * (end - start + 1));
    if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "vector data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = start; i <= end; i++)
        array[i - start] = list->arr[i];


    return array;

}


/** This function will take the vector address, and the sort comparator function as a parameter,
 * then it will sort the vector using qsort algorithm.
 *
 * Note: the pointer will be sent to the sort comparator function will be a double void pointer (void **) of an vector item.
 *
 * Example of comparator function if the items are integers:
 *
 * int comp(const void *item1, const void *item2) { return *(int *)(*(void **)item1)->item - *(int *)(*(void **)item2)->item; }
 *
 * @param list the vector address
 * @param sortComp the sort comparator function address
 */

void vectorSort(Vector *list, int (*sortComp)(const void *, const void *)) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (sortComp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "sort comparator function", "vector data structure");
        exit(INVALID_ARG);
#endif

    }

    qsort(list->arr, vectorGetLength(list), sizeof(void *), sortComp);

}


/** This function will take the vector address as a parameter,
 * then it will return the length of the vector.
 *
 * @param list the vector address
 * @return it will return the number of items in the vector
 */

int vectorGetLength(Vector *list) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    return list->count;

}


/** This function will take the vector address as a parameter,
 * then it will return one if the vector is empty,
 * other wise it will return 0.
 *
 * @param list the vector address
 * @return it will return one if the vector is empty, other wise it will return zero
 */

int vectorIsEmpty(Vector *list) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    return list->count == 0;

}


/** This function will take the vector address, and the print function address as a parameter,
 * then it will call the print function and send every item in the vector to be printed.
 *
 * @param list the vector address
 * @param printFun the print function address
 */

void printVector(Vector *list, void (*printFun)(const void *)) {
    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "vector data structure");
        exit(INVALID_ARG);
#endif

    }

    for (int i = 0; i < vectorGetLength(list); i++)
        printFun(list->arr[i]);


}


/** This function will take the vector address as a parameter,
 * then it will destroy and free all the vector items.
 *
 * Note: the function will just clear the vector, but it will not destroy the vector.
 *
 * @param list the vector address
 */

void clearVector(Vector *list) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < vectorGetLength(list); i++)
        list->freeItem(list->arr[i]);


    list->count = 0;

}


/** This function will take the vector address as a parameter,
 * then it will destroy and free the vector and all it's items.
 *
 * @param list the vector address
 */

void destroyVector(void *list) {

    if (list == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "vector", "vector data structure");
        exit(NULL_POINTER);
#endif

    }

    clearVector(list);
    free(((Vector *) list)->arr);
    free(list);

}