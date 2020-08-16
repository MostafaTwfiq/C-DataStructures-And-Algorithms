#include "../Headers/Set.h"
#include "../Headers/Vector.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"





Set *setInitialization(int initialLength, void (*freeFn)(void *), int (*cmp)(const void *, const void *)) {

    Set *set = (Set *) malloc(sizeof(Set));
    if (set == NULL) {

    }

    set->vector = vectorInitialization(initialLength, freeFn, cmp);

    return set;

}



void setAdd(Set *set, void *item) {

    int itemIndex = vectorGetIndex(set->vector, item);

    if (itemIndex == -1) {
        set->vector->freeItem(item);
        return;
    }

    vectorAdd(set->vector, item);


}



void setAddAtIndex(Set *set, void *item, int index) {

    int itemIndex = vectorGetIndex(set->vector, item);

    if (itemIndex == -1) {
        set->vector->freeItem(item);
        return;
    }

    vectorAddAtIndex(set->vector, item, index);

}



int setGetIndex(Set *set, void *item) {

    return vectorGetIndex(set->vector, item);

}


void *setGet(Set *set, int index) {

    return vectorGet(set, index);

}


int setContains(Set *set, void *item) {

    return vectorContains(set->vector, item);

}



void setDelete(Set *set, int index) {

    vectorRemoveAtIndex(set->vector, index);

}


void *setDeleteWtoFr(Set *set, int index) {

    return vectorRemoveAtIndexWtFr(set->vector, index);

}



int setGetLength(Set *set) {
    return vectorGetLength(set->vector);
}

int setIsEmpty(Set *set) {
    return vectorIsEmpty(set->vector);
}


void **setToArray(Set *set) {


    return vectorToArray(set->vector);

}


void clearSet(Set *set) {

    clearVector(set->vector);

}


void destroySet(Set *set) {

    destroyVector(set->vector);

    free(set);

}
