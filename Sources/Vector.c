#include "../Headers/Vector.h"


void vectorDestroyItem(VectorItem *item, void (*freeFun)(void *));



/** This function will take the initial length of the vector, and the size of the stored type as a parameter,
 * then it will initialize a new vector in the memory and set it's fields then return it.
 * @param initialLength the initial length of the vector.
 * @param freeFun the function address that will be called to free the vector items.
 * @return
 */

Vector *vectorInitialization(int initialLength, void (*freeFun)(void *)) {
    Vector *list = (Vector *) malloc(sizeof(Vector));
    list->arr = (VectorItem **) malloc(sizeof(VectorItem *) * initialLength);
    list->length = initialLength > 0 ? initialLength : 1;
    list->count = 0;
    list->freeItem = freeFun;

    return list;
}




/** This function will take the vector address, and the item address as a parameters,
    then it will put the item in the end of the vector.
 * @param list the vector address
 * @param item the item address
 * @param sizeOfItem the size of the new item in bytes
 */

void vectorAdd(Vector *list, void *item, int sizeOfItem) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    if (list->count == list->length) {
        list->length *= 2;
        list->arr = (VectorItem **) realloc(list->arr, sizeof(VectorItem *) * list->length);
    }

    VectorItem *newItem = (VectorItem *) malloc(sizeof(VectorItem));
    newItem->value = item;
    newItem->sizeOfItem = sizeOfItem;
    list->arr[list->count++] = newItem;

}




/** This function will take the vector address, the items array, the length of items array, and the size if the items as a parameters,
    then it will copy the items array into the vector.
 * @param list the vector address
 * @param array the array address that will be inserted in the vector
 * @param arrayLength the length of the array that will be added
 * @param sizeOfItem the size of the array items in bytes
 */

void vectorAddAll(Vector *list, void **array, int arrayLength, int sizeOfItem) {
    if (list == NULL || array == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < arrayLength; i++)
        vectorAdd(list, array[i], sizeOfItem);

}




/** This function will take the vector as a parameter,
    then it will remove the last item in the vector.
 * Note: if the vector is empty then the program will be terminated.
 * @param list the vector address
 */

void vectorRemove(Vector *list) {
    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (vectorIsEmpty(list)) {
        fprintf(stderr,"Vector out of range.");
        exit(-3);
    }

    vectorDestroyItem(list->arr[vectorGetLength(list) - 1], list->freeItem);
    list->count--;

}




/** This function will take the vector address, and the index as a parameters,
    then it will remove the item in the given index from the vector.
 * Note: if the index is out of the vector range then the program will be terminated.
 * @param list the vector address
 * @param index the index of the item that will be deleted
 */

void vectorRemoveAtIndex(Vector *list, int index) {
    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (index < 0 || index >= vectorGetLength(list)) {
        fprintf(stderr,"Index out of vector range.");
        exit(-3);
    }

    vectorDestroyItem(list->arr[index], list->freeItem);
    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];


}





/** This function will take the vector address, the item address, and the comparator function as a parameters,
    then it will return one (1) if the item is in the vector,
    other wise it will return zero (0).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list the vector address
 * @param item the item that will be compared by address
 * @param comparator the comparator function address
 * @return it will return one if the item is in the vector other wise it will return zero
 */

int vectorContains(Vector *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i]->value, item) == 0)
            return 1;

    }

    return 0;

}




/** This function will take the vector address, the item address, and the comparator function address as a parameters,
    then it will return the index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list the vector address
 * @param item the item address that will be searching for
 * @param comparator the comparator function address
 * @return it will return the item address if found, other wise it will return minus one
 */

int vectorGetIndex(Vector *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i]->value, item) == 0)
            return i;

    }

    return -1;

}




/** This function will take the vector address, the item address, and the comparator function address as a parameters,
    then it will return the last index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list the vector address
 * @param item the item address that will be searching for
 * @param comparator the comparator function address
 * @return it will return the item address if found, other wise it will return minus one
 */

int vectorGetLastIndex(Vector *list, void *item,
                          int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = list->count - 1; i >= 0; i--) {

        if (comparator(list->arr[i]->value, item) == 0)
            return i;

    }

    return -1;

}





/** This function will take the vector address, and the index as a parameters,
    then it will return the item at the given index.
 * Note: if the index is out of the vector range then the program will be terminated.
 * @param list the vector address
 * @param index the item index
 * @return it will return a void pointer to the item
 */

void *vectorGet(Vector *list, int index) {
    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (index < 0 || index >= vectorGetLength(list)) {
        fprintf(stderr,"Index out of vector range.");
        exit(-3);
    }

    return list->arr[index]->value;

}




/** This function will take the vector address as a parameter,
    then it will return a void pointer array that consist of the vector elements.
 * @param list the vector address
 * @return it will return a double void pointer to an array that has a copy of the items
 */

void **vectorToArray(Vector *list) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    void **array = (void **) malloc(sizeof(void *) * vectorGetLength(list));

    for (int i = 0; i < vectorGetLength(list); i++) {
        array[i] = (void *) malloc(list->arr[i]->sizeOfItem);
        memcpy(array[i], list->arr[i]->value, list->arr[i]->sizeOfItem);
    }

    return array;

}




/** This function will take the vector address, the start index, and the end index as a parameters,
    then it will return a void pointer array that consist of the items at the start index to end index - 1.
 * @param list the vector address
 * @param start the start index
 * @param end the end index
 * @return it will return a double void pointer that has a copy of the items in the vector
 */

void **vectorToSubArray(Vector *list, int start, int end) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (start < 0 || end > vectorGetLength(list) || start > end) {
        fprintf(stderr,"Index out of vector range.");
        exit(-3);
    }

    void **array = (void **) malloc(sizeof(void *) * (end - start) );

    for (int i = start; i < end; i++) {
        array[i] = (void *) malloc(list->arr[i]->sizeOfItem);
        memcpy(array[i - start], list->arr[i]->value, list->arr[i]->sizeOfItem);
    }


    return array;

}




/** This function will take the vector address, and the sort comparator function as a parameter,
    then it will sort the vector using qsort algorithm.
 * Note: the pointer will be sent to the sort comparator function will be a double void pointer (void **) of an vector item.
 * @param list the vector address
 * @param comparator the comparator function address
 * Example of comparator function if the items are integers:
 * int comp(const void *item1, const void *item2) {
    return *(int *)(*(VectorItem **)item1)->value - *(int *)(*(VectorItem **)item2)->value;}
 */

void vectorSort(Vector *list, int (*comparator)(const void *, const void *)) {
    qsort(list->arr, vectorGetLength(list), sizeof(VectorItem *), comparator);
}






/** This function will take the vector address as a parameter,
 * then it will return the length of the vector.
 * @param list the vector address
 * @return it will return the number of items in the vector
 */

int vectorGetLength(Vector *list) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    return list->count;

}




/** This function will take the vector address as a parameter,
    then it will return one if the vector is empty,
    other wise it will return 0.
 * @param list the vector address
 * @return it will return one if the vector is empty, other wise it will return zero
 */

int vectorIsEmpty(Vector *list) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    return list->count == 0;

}




/** This function will take the vector address, and the print function address as a parameter,
 * then it will call the print function and send every item in the vector to be printed.
 * @param list the vector address
 * @param printFun the print function address
 */

void printVector(Vector *list, void (*printFun) (const void *)) {
    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < vectorGetLength(list); i++)
        printFun(list->arr[i]->value);


}




/** This function will take the vector address as a parameter,
    then it will destroy and free all the vector items.
 * Note: the function will just clear the vector, but it will not destroy the vector.
 * @param list the vector address
 */

void clearVector(Vector *list) {

    if (list == NULL) {
        fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < vectorGetLength(list); i++)
        vectorDestroyItem(list->arr[i], list->freeItem);


    list->count = 0;

}


/** This function will take the vector address as a parameter,
 * then it will destroy and free the vector and all it's items.
 * @param list the vector address
 */

void destroyVector(Vector *list) {

    clearVector(list);
    free(list->arr);
    free(list);

}




/** This function will take the item address, and the free function address as a parameters,
 * then it will free the item container and it's value.
 * Note: this function should only be called from the vector functions.
 * @param item the item container address
 * @param freeFun the free item function address
 */

void vectorDestroyItem(VectorItem *item, void (*freeFun)(void *)) {
    freeFun(item->value);
    free(item);

}