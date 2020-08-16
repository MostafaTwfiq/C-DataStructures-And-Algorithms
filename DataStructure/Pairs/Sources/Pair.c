#include "../Headers/Pair.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


/** This function will allocate a new pair then it will return it's pointer.
 *
 * @param fElem the first element pointer
 * @param sElem the second element pointer
 * @param fFreeFn the first element free function pointer, that will be called to free the first element
 * @param sFreeFn the second element free function pointer, that will be called to free the second element
 * @return it will return the new allocated pair pointer
 */

Pair *pairInitialization(void *fElem, void *sElem, void (*fFreeFn)(void *), void (*sFreeFn)(void *)) {

    if (fElem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "first element pointer", "pair data structure");
        exit(INVALID_ARG);
#endif
    } else if (sElem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second element pointer", "pair data structure");
        exit(INVALID_ARG);
#endif
    } else if (fFreeFn == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "first element free function pointer", "pair data structure");
        exit(INVALID_ARG);
#endif
    } else if (sFreeFn == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second element free function pointer", "pair data structure");
        exit(INVALID_ARG);
#endif
    }

    Pair *pair = (Pair *) malloc(sizeof(Pair));
    if (pair == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "pair", "pair data structure");
        exit(FAILED_ALLOCATION);
    }

    pair->fElem = fElem;
    pair->sElem = sElem;
    pair->fFreeFn = fFreeFn;
    pair->sFreeFn = sFreeFn;

    return pair;

}


/** This function will return the first element in the pair.
 *
 * @param pair the pair pointer
 * @return it will return the first element in the pair
 */

void *pairGetFElem(Pair *pair) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    }

    return pair->fElem;

}


/** This function will return the second element in the pair.
 *
 * @param pair the pair pointer
 * @return it will return the second element in the pair
 */

void *pairGetSElem(Pair *pair) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    }

    return pair->sElem;

}


/** This function will set the first element in the pair.
 *
 * Note: this function will free the old element
 *
 * @param pair the pair pointer
 * @param newElem the new element pointer
 */

void pairSetFElem(Pair *pair, void *newElem) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    } else if (newElem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new element", "pair data structure");
        exit(INVALID_ARG);
#endif
    }

    pair->fFreeFn(pair->fElem);

    pair->fElem = newElem;

}


/** This function will set the second element in the pair.
 *
 * Note: this function will free the old element
 *
 * @param pair the pair pointer
 * @param newElem the new element pointer
 */

void pairSetSElem(Pair *pair, void *newElem) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    } else if (newElem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new element", "pair data structure");
        exit(INVALID_ARG);
#endif
    }

    pair->sFreeFn(pair->sElem);

    pair->sElem = newElem;

}


/** This function will set the first element in the pair,
 * without freeing the old element.
 *
 * @param pair the pair pointer
 * @param newElem the new element pointer
 * @return it will return the deleted element pointer
 */

void *pairSetFElemWtoFr(Pair *pair, void *newElem) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    } else if (newElem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new element", "pair data structure");
        exit(INVALID_ARG);
#endif
    }

    void *itemToReturn = pair->fElem;

    pair->fElem = newElem;

    return itemToReturn;

}


/** This function will set the second element in the pair,
 * without freeing the old element.
 *
 * @param pair the pair pointer
 * @param newElem the new element pointer
 * @return it will return the deleted element pointer
 */

void *pairSetSElemWtoFr(Pair *pair, void *newElem) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    } else if (newElem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new element", "pair data structure");
        exit(INVALID_ARG);
#endif
    }

    void *itemToReturn = pair->sElem;

    pair->sElem = newElem;

    return itemToReturn;

}


/** This function will swap the pair elements.
 *
 * @param pair the pair pointer
 */

void pairSwapElements(Pair *pair) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    }

    void *tempElem = pair->fElem;
    pair->fElem = pair->sElem;
    pair->sElem = tempElem;

    void (*tempFreeFn)(void *) = pair->fFreeFn;
    pair->fFreeFn = pair->sFreeFn;
    pair->sFreeFn = tempFreeFn;

}


/** This function will destroy and free the pair and its elements.
 *
 * @param pair the pair pointer
 */

void destroyPair(Pair *pair) {

    if (pair == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "pair", "pair data structure");
        exit(NULL_POINTER);
#endif
    }

    pair->fFreeFn(pair->fElem);
    pair->sFreeFn(pair->sElem);

    free(pair);

}