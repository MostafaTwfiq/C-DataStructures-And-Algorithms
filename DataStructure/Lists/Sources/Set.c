#include "../Headers/Set.h"
#include "../Headers/Vector.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will allocate a new set then it will return its pointer.
 *
 * @param initialLength the initial length of the set
 * @param freeFn the free function pointer, that will be called to free the set items
 * @param cmp the comparison function pointer, that will be called to compare the set items
 * @return it will return the new allocated set pointer
 */

Set *setInitialization(int initialLength, void (*freeFn)(void *), int (*cmp)(const void *, const void *)) {

    if (freeFn == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function", "set data structure");
        exit(INVALID_ARG);
#endif

    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparison function", "set data structure");
        exit(INVALID_ARG);
#endif

    } else if (initialLength <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "initial length", "set data structure");
        exit(INVALID_ARG);
#endif

    }

    Set *set = (Set *) malloc(sizeof(Set));
    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "set", "set data structure");
        exit(FAILED_ALLOCATION);
#endif
    }

    set->vector = vectorInitialization(initialLength, freeFn, cmp);

    return set;

}


/** This function will add the passed item in the end of the set,
 * if the item doesn't exist in the set, other wise the function will free the passed item.
 *
 * @param set the set pointer
 * @param item the new item pointer
 */

void setAdd(Set *set, void *item) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "set data structure");
        exit(INVALID_ARG);
#endif

    }

    int itemIndex = vectorGetIndex(set->vector, item);

    if (itemIndex != -1) {
        set->vector->freeItem(item);
        return;
    }

    vectorAdd(set->vector, item);


}


/** This function will add the passed item in the passed index,
 * if the item doesn't exist in the set, other wise the function will free the passed item,
 *
 * @param set the set pointer
 * @param item the new item pointer
 * @param index the index that the new item will be inserted in
 */

void setAddAtIndex(Set *set, void *item, int index) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "set data structure");
        exit(INVALID_ARG);
#endif

    } else if (index < 0 || index >= setGetLength(set)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "set data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    int itemIndex = vectorGetIndex(set->vector, item);

    if (itemIndex != -1) {
        set->vector->freeItem(item);
        return;
    }

    vectorAddAtIndex(set->vector, item, index);

}


/** This function will return the index of the passed item if found,
 * other wise the function will return minus one (-1).
 *
 * @param set the set pointer
 * @param item the item pointer
 * @return it will return the item index if found, other wise it will return -1
 */

int setGetIndex(Set *set, void *item) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "set data structure");
        exit(INVALID_ARG);
#endif

    }

    return vectorGetIndex(set->vector, item);

}


/** This function will return the item pointer in the passed index.
 *
 * @param set the set pointer
 * @param index the index of the item
 * @return it will return the item in the passed index
 */

void *setGet(Set *set, int index) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    } else if (index < 0 || index >= setGetLength(set)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "set data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    return vectorGet(set->vector, index);

}


/** This function will check if the passed item exist in the set or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param set the set pointer
 * @param item the item pointer
 * @return it will return 1 if the item exist in the set, other wise it will return 0
 */

int setContains(Set *set, void *item) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "set data structure");
        exit(INVALID_ARG);
#endif

    }

    return vectorContains(set->vector, item);

}


/** This function will delete and free the item in the passed index.
 *
 * @param set the set pointer
 * @param index the index of the item
 */

void setDelete(Set *set, int index) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    } else if (index < 0 || index >= setGetLength(set)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "set data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    vectorRemoveAtIndex(set->vector, index);

}


/** This function will delete the item in the passed index from the set without freeing it,
 * then the function will return the deleted item pointer.
 *
 * @param set the set pointer
 * @param index the item index
 * @return it will return the deleted item pointer
 */

void *setDeleteWtoFr(Set *set, int index) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    } else if (index < 0 || index >= setGetLength(set)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = OUT_OF_RANGE;
        return NULL;
#else
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "set data structure");
        exit(OUT_OF_RANGE);
#endif

    }

    return vectorRemoveAtIndexWtFr(set->vector, index);

}


/** This function will return the number of items in the set.
 *
 * @param set the set pointer
 * @return it will return the number of items in the set
 */

int setGetLength(Set *set) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    }

    return vectorGetLength(set->vector);
}


/** This function will check if the set is empty or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param set the set pointer
 * @return it will return 1 if the set was empty, other wise it will return 0
 */

int setIsEmpty(Set *set) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    }

    return vectorIsEmpty(set->vector);
}


/** This function will return a double void pointer,
 * that contains the set items.
 *
 * @param set the set pointer
 * @return it will return a double void pointer, that contains the set items
 */

void **setToArray(Set *set) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    }

    return vectorToArray(set->vector);

}


/** This function will clear and free the set items,
 * without freeing the set itself.
 *
 * @param set the set pointer
 */

void clearSet(Set *set) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    }

    clearVector(set->vector);

}


/** This function will destroy and free the set with all it's items.
 *
 * @param set the set pointer
 */

void destroySet(Set *set) {

    if (set == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "set", "set data structure");
        exit(NULL_POINTER);
#endif

    }

    destroyVector(set->vector);

    free(set);

}
