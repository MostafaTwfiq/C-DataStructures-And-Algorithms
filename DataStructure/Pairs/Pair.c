#include "Pair.h"
#include "../../System/Utils.h"
#include "../../Unit Test/CuTest/CuTest.h"





Pair *pairInitialization(void *fElem, void *sElem, void (*fFreeFn)(void *), void (*sFreeFn)(void *)) {

    if (fElem == NULL) {

    } else if (sElem == NULL) {

    } else if (fFreeFn == NULL) {

    } else if (sFreeFn == NULL) {

    }

    Pair *pair = (Pair *) malloc(sizeof(Pair));
    if (pair == NULL) {

    }

    pair->fElem = fElem;
    pair->sElem = sElem;
    pair->fFreeFn = fFreeFn;
    pair->sFreeFn = sFreeFn;

    return pair;

}




void *pairGetFElem(Pair *pair) {

    if (pair == NULL) {

    }

    return pair->fElem;

}


void *pairGetSElem(Pair *pair) {

    if (pair == NULL) {

    }

    return pair->sElem;

}


void pairSetFElem(Pair *pair, void *newElem) {

    if (pair == NULL) {

    }

    pair->fFreeFn(pair->fElem);

    pair->fElem = newElem;

}


void pairSetSElem(Pair *pair, void *newElem) {

    if (pair == NULL) {

    }

    pair->sFreeFn(pair->sElem);

    pair->sElem = newElem;

}



void pairSwapElements(Pair *pair) {

    if (pair == NULL) {

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

    }

    pair->fFreeFn(pair->fElem);
    pair->sFreeFn(pair->sElem);

    free(pair);


}