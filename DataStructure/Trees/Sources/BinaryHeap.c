#include "../Headers/BinaryHeap.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


int binaryHeapContainsR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *));

void *binaryHeapGetR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *));


/** This function will return the parent index of the passed child index.
 *
 * Note: this function should only be called from the inside.
 *
 * @param childIndex the child index
 * @return it will return the parent index of the passed child
 */

int binaryHeapGetParentIndex(int childIndex) {

    return (childIndex - 1) / 2;

}


/** This function will return the first child index,
 * of the passed parent index.
 *
 * Note: this function should only be called from the inside.
 *
 * @param parentIndex the parent index
 * @return it will return the first child index of the passed parent index
 */

int binaryHeapGetFChildIndex(int parentIndex) {
    return parentIndex * 2 + 1;
}


/** This function will return the second child index,
 * of the passed parent index.
 *
 * Note: this function should only be called from the inside.
 *
 * @param parentIndex the parent index
 * @return it will return the second child index of the passed parent index
 */

int binaryHeapGetSChildIndex(int parentIndex) {
    return parentIndex * 2 + 2;
}


/** This function will swap the passed two indices.
 *
 * @param arr the array pointer
 * @param fIndex the first index
 * @param sIndex the second index
 */

void binaryHeapSwap(void **arr, int fIndex, int sIndex) {

    void *tempItem = arr[sIndex];
    arr[sIndex] = arr[fIndex];
    arr[fIndex] = tempItem;

}


/** This function will heap up the value in the passed index until it be in the right place.
 *
 * @param arr the array pointer
 * @param currentIndex the current index
 * @param cmp the comparator function pointer
 */

void binaryHeapUp(void **arr, int currentIndex, int (*cmp)(const void *, const void *)) {

    if (currentIndex <= 0)
        return;

    int parentIndex = binaryHeapGetParentIndex(currentIndex);
    if (cmp(arr[currentIndex], arr[parentIndex]) > 0) {
        binaryHeapSwap(arr, currentIndex, parentIndex);
        binaryHeapUp(arr, parentIndex, cmp);
    }

}


/** This function will heap down the value in the passed index until it be in the right place.
 *
 * @param arr the array pointer
 * @param currentIndex the current index
 * @param length the length of the array
 * @param cmp the comparator function pointer
 */

void binaryHeapDown(void **arr, int currentIndex, int length, int (*cmp)(const void *, const void *)) {

    if (currentIndex >= length)
        return;

    int fChildIndex = binaryHeapGetFChildIndex(currentIndex);
    int sChildIndex = binaryHeapGetSChildIndex(currentIndex);

    fChildIndex = fChildIndex >= length ? currentIndex : fChildIndex;
    sChildIndex = sChildIndex >= length ? currentIndex : sChildIndex;

    if (cmp(arr[currentIndex], arr[fChildIndex]) < 0 && cmp(arr[currentIndex], arr[sChildIndex]) < 0) {

        int biggestChildIndex = cmp(arr[fChildIndex], arr[sChildIndex]) < 0 ? sChildIndex : fChildIndex;
        binaryHeapSwap(arr, currentIndex, biggestChildIndex);
        binaryHeapDown(arr, biggestChildIndex, length, cmp);

    } else if (cmp(arr[currentIndex], arr[fChildIndex]) < 0) {

        binaryHeapSwap(arr, currentIndex, fChildIndex);
        binaryHeapDown(arr, fChildIndex, length, cmp);

    } else if (cmp(arr[currentIndex], arr[sChildIndex]) < 0) {

        binaryHeapSwap(arr, currentIndex, sChildIndex);
        binaryHeapDown(arr, sChildIndex, length, cmp);

    }

}


/** This function will initialize a new heap then it will return it's pointer.
 *
 * @param freeFun the free function pointer, that will be called to free the heap items
 * @param cmp the comparator function pointer, that will be called to compare the heap items
 * @return it will return the new initialized heap pointer
 */

BinaryHeap *binaryHeapInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *)) {

    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "binary heap data structure");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "binary heap data structure");
        exit(INVALID_ARG);
#endif
    }


    BinaryHeap *heap = (BinaryHeap *) malloc(sizeof(BinaryHeap));

    heap->freeFun = freeFun;
    heap->cmp = cmp;
    heap->count = 0;
    heap->length = 10;
    heap->arr = (void **) malloc(sizeof(void *) * heap->length);

    if (heap->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "heap", "binary heap data structure");
        exit(FAILED_ALLOCATION);
#endif
    }


    return heap;

}


/** This function will insert the passed item in the heap.
 *
 * @param heap the heap pointer
 * @param item the new item pointer
 */

void binaryHeapInsert(BinaryHeap *heap, void *item) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary heap data structure");
        exit(INVALID_ARG);
#endif
    }

    if (heap->count == heap->length) {
        heap->length *= 2;

        heap->arr = realloc(heap->arr, sizeof(void *) * heap->length);
        if (heap->arr == NULL) {
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "heap array", "binary heap data structure");
            exit(FAILED_REALLOCATION);
        }

    }

    heap->arr[heap->count++] = item;
    binaryHeapUp(heap->arr, heap->count - 1, heap->cmp);

}


/** This function will insert all the passed array items in the heap.
 *
 * @param heap the heap pointer
 * @param items the new items array pointer
 * @param length the length of the items array
 */

void binaryHeapInsertAll(BinaryHeap *heap, void **items, int length) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    } else if (items == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "binary heap data structure");
        exit(INVALID_ARG);
#endif
    }

    for (int i = 0; i < length; i++)
        binaryHeapInsert(heap, items[i]);

}


/** This function will delete and free the heap root.
 *
 * @param heap the heap pointer
 */

void binaryHeapDeleteRoot(BinaryHeap *heap) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    } else if (binaryHeapIsEmpty(heap)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "binary heap data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    heap->freeFun(heap->arr[0]);
    heap->arr[0] = heap->arr[--heap->count];

    binaryHeapDown(heap->arr, 0, heap->count, heap->cmp);

}


/** This function will delete the heap root without freeing it.
 *
 * @param heap the heap pointer
 */

void *binaryHeapDeleteRootWtoFr(BinaryHeap *heap) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    } else if (binaryHeapIsEmpty(heap)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "binary heap data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    void *itemToReturn = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->count];

    binaryHeapDown(heap->arr, 0, heap->count, heap->cmp);

    return itemToReturn;

}


/** This function will check if the passed item is in the heap or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param heap the heap pointer
 * @param item the item pointer
 * @return it will return 1 if the passed item is in the heap, other wise it will return 0
 */

int binaryHeapContains(BinaryHeap *heap, void *item) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary heap data structure");
        exit(INVALID_ARG);
#endif
    }

    return binaryHeapContainsR(heap->arr, 0, heap->count, item, heap->cmp);

}


/** This function will recursively check if the passed item is in the heap or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * Note: this function should only be called from the inside.
 *
 * @param arr the heap array pointer
 * @param currentIndex the current index
 * @param length the heap size
 * @param item the item pointer
 * @param cmp the comparator function pointer
 * @return it will return 1 if the passed item is in the heap, other wise it will return 0
 */

int binaryHeapContainsR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *)) {

    if (currentIndex >= length)
        return 0;


    if (cmp(item, arr[currentIndex]) == 0)
        return 1;
    else if (cmp(item, arr[currentIndex]) > 0)
        return 0;


    return
            binaryHeapContainsR(arr, binaryHeapGetFChildIndex(currentIndex), length, item, cmp)
            || binaryHeapContainsR(arr, binaryHeapGetSChildIndex(currentIndex), length, item, cmp);

}


/** This function will check if the passed item is in the heap or not,
 * and if it was the function will return the item pointer,
 * other wise it will return NULL.
 *
 * @param heap the heap pointer
 * @param item the item pointer
 * @return it will return the item pointer if found, other wise it will return NULL
 */

void *binaryHeapGet(BinaryHeap *heap, void *item) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary heap data structure");
        exit(INVALID_ARG);
#endif
    }

    return binaryHeapGetR(heap->arr, 0, heap->count, item, heap->cmp);

}


/** This function will recursively check if the passed item is in the heap or not,
 * and if it was the function will return the item pointer,
 * other wise it will return NULL.
 *
 * Note: this function should only be called from the inside.
 *
 * @param arr the heap array pointer
 * @param currentIndex the current item index
 * @param length the size of the heap
 * @param item the item pointer
 * @param cmp the comparator function pointer
 * @return it will return the item pointer if found, other wise it will return NULL
 */

void *binaryHeapGetR(void **arr, int currentIndex, int length, void *item, int (*cmp)(const void *, const void *)) {

    if (currentIndex >= length)
        return NULL;


    if (cmp(item, arr[currentIndex]) == 0)
        return arr[currentIndex];
    else if (cmp(item, arr[currentIndex]) > 0)
        return NULL;


    void *fVal = binaryHeapGetR(arr, binaryHeapGetFChildIndex(currentIndex), length, item, cmp);
    void *sVal = binaryHeapGetR(arr, binaryHeapGetSChildIndex(currentIndex), length, item, cmp);

    return fVal != NULL ? fVal : sVal;

}


/** This function will return the number of items in the heap.
 *
 * @param heap the heap pointer
 * @return it will return the number of items in the heap
 */

int binaryHeapGetSize(BinaryHeap *heap) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    }

    return heap->count;

}


/** This function will check if the heap is empty or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param heap the heap pointer
 * @return it will return 1 if the heap is empty, other wise it will return 0
 */

int binaryHeapIsEmpty(BinaryHeap *heap) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    }

    return heap->count == 0;

}


/** This function will return a double void array,
 * that contains the heap items.
 *
 * Note: the array will contain the same items addresses not a copy.
 *
 * @param heap the heap pointer
 * @return it will return an array that contains the heap items
 */

void **binaryHeapToArray(BinaryHeap *heap) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    }


    void **arr = (void **) malloc(sizeof(void *) * heap->count);

    memcpy(arr, heap->arr, sizeof(void *) * heap->count);

    return arr;

}


/** This function will clear and free all the heap items, without destroying the heap itself.
 *
 * @param heap the heap pointer
 */

void clearBinaryHeap(BinaryHeap *heap) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    }

    for (int i = 0; i < heap->count; i++)
        heap->freeFun(heap->arr[i]);


    heap->count = 0;

}


/** This function will destroy and free the heap with all it's items.
 *
 * @param heap the heap pointer
 */

void destroyBinaryHeap(void *heap) {

    if (heap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "heap", "binary heap data structure");
        exit(NULL_POINTER);
#endif
    }

    clearBinaryHeap(heap);

    free(((BinaryHeap *) heap)->arr);
    free(heap);

}


