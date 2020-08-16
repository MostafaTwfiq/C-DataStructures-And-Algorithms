#include "../Headers/Deque.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will initialize a new deque then it will return it's pointer.
 *
 * @param freeFun the items free function address, that will be called to free the deque items
 * @return it will return the initialized deque pointer
 */

Deque *dequeInitialization(void (*freeFun)(void *)) {
    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "deque data structure");
        exit(INVALID_ARG);
#endif

    }

    Deque *deque = (Deque *) malloc(sizeof(Deque));
    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "deque", "deque data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    deque->length = 10;
    deque->arr = (void **) malloc(sizeof(void *) * deque->length);
    if (deque->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "deque array", "deque data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    deque->front = deque->rear = 0;
    deque->freeFun = freeFun;


    return deque;

}


/** This function will take the new item address,
 * then it will insert the new item in the front of the deque array.
 *
 * @param deque the deque pointer
 * @param item the new item pointer
 */

void dequeInsertFront(Deque *deque, void *item) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "deque data structure");
        exit(INVALID_ARG);
#endif

    }

    if (deque->rear == deque->length && deque->front == 0) {
        deque->length *= 2;
        void **tempArr = (void **) malloc(sizeof(void *) * deque->length);
        if (tempArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_ALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new deque array", "deque data structure");
            exit(FAILED_ALLOCATION);
#endif

        }

        if (!memcpy(tempArr, deque->arr + deque->front, sizeof(void *) * (deque->rear - deque->front))) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_COPY;
            return;
#else
            fprintf(stderr, FAILED_COPY_MESSAGE, "deque array to the new array", "deque data structure");
            exit(FAILED_COPY);
#endif

        }

        free(deque->arr);
        deque->arr = tempArr;
    }

    if (deque->front != 0) {
        deque->front--;
    } else {
        for (int i = deque->rear++; i > deque->front; i--)
            deque->arr[i] = deque->arr[i - 1];

    }

    deque->arr[deque->front] = item;

}


/** This function will take the new item pointer,
 * then it will insert the item in the end of the deque array.
 *
 * @param deque the deque pointer
 * @param item the new item pointer
 */

void dequeInsertRear(Deque *deque, void *item) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "deque data structure");
        exit(INVALID_ARG);
#endif

    }

    if (deque->rear == deque->length) {
        deque->length *= 2;
        void **tempArr = (void **) malloc(sizeof(void *) * deque->length);
        if (tempArr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_ALLOCATION;
            return;
#else
            fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new deque array", "deque data structure");
            exit(FAILED_ALLOCATION);
#endif

        }

        if (!memcpy(tempArr, deque->arr + deque->front, sizeof(void *) * (deque->rear - deque->front))) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
            ERROR_TEST->errorCode = FAILED_COPY;
            return;
#else
            fprintf(stderr, FAILED_COPY_MESSAGE, "deque array to the new array", "deque data structure");
            exit(FAILED_COPY);
#endif

        }

        free(deque->arr);
        deque->arr = tempArr;
    }

    deque->arr[deque->rear++] = item;


}


/** This function will return the front item in the deque array,
 * then it will remove the item from the deque array.
 *
 * @param deque the deque pointer
 * @return it will return the front item in the deque array
 */

void *dequeGetFront(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    } else if (dequeIsEmpty(deque)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return deque->arr[deque->front++];

}


/** This function will return the item pointer in the end of the deque array,
 * then it will return the item from the end of the deque array.
 *
 * @param deque the deque pointer
 * @return it will return the item pointer in the end of the deque
 */

void *dequeGetRear(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    } else if (dequeIsEmpty(deque)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return deque->arr[--deque->rear];

}


/** This function will return the front item in the deque array,
 * without removing the item from the deque.
 *
 * @param deque the deque pointer
 * @return it will return the front item in the deque
 */

void *dequePeekFront(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    } else if (dequeIsEmpty(deque)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return deque->arr[deque->front];

}


/** This function will return the item pointer in the end of the deque array,
 * without removing the item from the deque.
 *
 * @param deque the deque pointer
 * @return it will return the item in the end of the deque
 */

void *dequePeekRear(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    } else if (dequeIsEmpty(deque)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "deque data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif

    }

    return deque->arr[deque->rear - 1];

}


/** This function will return a double void pointer array,
 * that consisting of the deque items.
 *
 * @param deque the deque pointer
 * @return it will return the deque items in a double void array
 */

void **dequeToArray(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    }

    void **array = (void **) malloc(sizeof(void *) * dequeGetLength(deque));
    if (array == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "deque data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    for (int i = deque->front; i < deque->rear; i++)
        array[i - deque->front] = deque->arr[i];

    return array;

}


/** This function will return the number of items in the deque.
 *
 * @param deque the deque pointer
 * @return it will return the number of items in the deque
 */

int dequeGetLength(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    }

    return deque->rear - deque->front;

}


/** This function will return one (1) if the deque is empty,
 * other wise it will return zero (0).
 *
 * @param deque the deque pointer
 * @return it will return one if the deque is empty, other wise it will return zero
 */

int dequeIsEmpty(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    }

    return deque->rear == deque->front;

}


/** This function will clear and free the deque items,
 * without destroying the deque.
 *
 * @param deque the deque pointer
 */

void clearDeque(Deque *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = deque->rear - 1; i >= deque->front; i--)
        deque->freeFun(deque->arr[i]);

    deque->front = deque->rear = 0;

}


/** This function will clear and free the deque items,
 * then it will destroy the deque and free it.
 *
 * @param deque the deque pointer
 */

void destroyDeque(void *deque) {

    if (deque == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "deque", "deque data structure");
        exit(NULL_POINTER);
#endif

    }

    clearDeque(deque);
    free(((Deque *) deque)->arr);
    free(deque);
}