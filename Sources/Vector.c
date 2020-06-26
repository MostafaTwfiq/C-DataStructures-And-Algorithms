#include "../Headers/Vector.h"




/** This function will take the initial length of the vector, and the size of the stored type as a parameter,
    then it will initialize a new vector in the memory and set it's fields then return it.
 * @param initialLength
 * @param sizeOfType
 * @return
 */

Vector *vectorInitialization(int initialLength, int sizeOfType) {
    Vector *list = (Vector *) malloc(sizeof(Vector));
    list->arr = (void **) malloc(sizeof(void *) * initialLength);
    list->length = initialLength;
    list->count = 0;
    list->sizeOfType = sizeOfType;

    return list;
}




/** This function will take the vector address, and the item address as a parameters,
    then it will put the item in the end of the vector.
 * @param list
 * @param item
 */

void vectorAdd(Vector *list, void *item) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    if (list->count == list->length) {
        list->length = (int) (list->length * 2);
        list->arr = (void **) realloc(list->arr, sizeof(void *) * list->length);
    }

    list->arr[list->count++] = item;

}




/** This function will take the vector address, the items array, and the length of items array as a parameters,
    then it will copy the items array into the vector.
 * @param list
 * @param array
 * @param arrayLength
 */

void vectorAddAll(Vector *list, void *array, int arrayLength) {
    if (list == NULL || array == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    if (list->length - list->count < arrayLength) {
        list->length = (int) (( list->length + (arrayLength - (list->length - list->count)) ) * 2);
        list->arr = (void **) realloc(list->arr, sizeof(void *) * list->length);
    }

    void *item;
    for (int i = 0; i < arrayLength; i++) {
        item = (void *) malloc(list->sizeOfType);
        memcpy(item, (array + list->sizeOfType * i), list->sizeOfType);
        vectorAdd(list, item);
    }

}




/** This function will take the vector as a parameter,
    then it will remove the last item in the vector.
 * Note: if the vector is empty then the program will be terminated.
 * @param list
 */

void vectorRemove(Vector *list) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (vectorGetLength(list)) {
         fprintf(stderr,"Vector out of range.");
        exit(-3);
    }

    free(list->arr[vectorGetLength(list) - 1]);
    list->count--;

}




/** This function will take the vector address, and the index as a parameters,
    then it will remove the item in the given index from the vector.
 * Note: if the index is out of the vector range then the program will be terminated.
 * @param list
 * @param index
 */

void vectorRemoveAtIndex(Vector *list, int index) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (index < 0 || index >= vectorGetLength(list)) {
         fprintf(stderr,"Index out of vector range.");
        exit(-3);
    }

    free(list->arr[index]);
    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];


}





/** This function will take the vector address, the item address, and the comparator function as a parameters,
    then it will return one (1) if the item is in the vector,
    other wise it will return zero (0).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list
 * @param item
 * @param comparator
 * @return
 */

int vectorContains(Vector *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i], item) == 0)
            return 1;

    }

    return 0;

}




/** This function will take the vector address, the item address, and the comparator function address as a parameters,
    then it will return the index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list
 * @param item
 * @param comparator
 * @return
 */

int vectorGetIndex(Vector *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i], item) == 0)
            return i;

    }

    return -1;

}




/** This function will take the vector address, the item address, and the comparator function address as a parameters,
    then it will return the last index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list
 * @param item
 * @param comparator
 * @return
 */

int vectorGetLastIndex(Vector *list, void *item,
                          int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = list->count - 1; i >= 0; i--) {

        if (comparator(list->arr[i], item) == 0)
            return i;

    }

    return -1;

}





/** This function will take the vector address, and the index as a parameters,
    then it will return the item at the given index.
 * Note: if the index is out of the vector range then the program will be terminated.
 * @param list
 * @param index
 * @return
 */

void *vectorGet(Vector *list, int index) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (index < 0 || index >= vectorGetLength(list)) {
         fprintf(stderr,"Index out of vector range.");
        exit(-3);
    }

    return list->arr[index];

}




/** This function will take the vector address as a parameter,
    then it will return a void pointer array that consist of the vector elements.
 * @param list
 * @return
 */

void *vectorToArray(Vector *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    void *array = (void *) malloc(list->sizeOfType * vectorGetLength(list));

    for (int i = 0; i < vectorGetLength(list); i++)
        memcpy(array + list->sizeOfType * i, list->arr[i], list->sizeOfType);


    return array;

}




/** This function will take the vector address, the start index, and the end index as a parameters,
    then it will return a void pointer array that consist of the items at the start index to end index - 1.
 * @param list
 * @param start
 * @param end
 * @return
 */

void *vectorToSubArray(Vector *list, int start, int end) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    } else if (start < 0 || end > vectorGetLength(list) || start > end) {
         fprintf(stderr,"Index out of vector range.");
        exit(-3);
    }

    void *array = (void *) malloc(list->sizeOfType * (end - start) );

    for (int i = start; i < end; i++)
        memcpy(array + list->sizeOfType * (i - start), list->arr[i], list->sizeOfType);


    return array;

}




/** This function will take the vector address, and the sort comparator function as a parameter,
    then it will sort the vector using qsort algorithm.
 * Note: the pointer will be sent to the sort comparator function will be a double void pointer (void **).
 * @param list
 * @param comparator
 */

void vectorSort(Vector *list, int (*comparator)(const void *, const void *)) {
    qsort(list->arr, vectorGetLength(list), sizeof(void *), comparator);
}




/** This function will take the vector address as a parameter,
 * then it will return the length of the vector.
 * @param list
 * @return
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
 * @param list
 * @return
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
 * @param list
 * @param printFun
 */

void printVector(Vector *list, void (*printFun) (const void *)) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < vectorGetLength(list); i++)
        printFun(list->arr[i]);


}




/** This function will take the vector address as a parameter,
    then it will destroy and free all the vector items.
 * Note: the function will just clear the vector, but it will not destroy the vector.
 * @param list
 */

void clearVector(Vector *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < vectorGetLength(list); i++)
        free(list->arr[i]);

    list->count = 0;

}




/** This function will take the vector address as a parameter,
 * then it will destroy and free the vector and all it's items.
 * @param list
 */

void destroyVector(Vector *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the vector is NULL.");
        exit(-3);
    }

    for (int i = 0; i < vectorGetLength(list); i++)
        free(list->arr[i]);

    free(list);

}