#include "Pair.h"
#include "../../System/Utils.h"
#include "../../Unit Test/CuTest/CuTest.h"





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