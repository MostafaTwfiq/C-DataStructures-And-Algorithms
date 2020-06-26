#include "../Headers/ArrayList.h"




/** This function will take the initial length of the array list, and the size of the stored type as a parameter,
    then it will initialize a new array list in the memory and set it's fields then return it.
 * @param initialLength
 * @param sizeOfType
 * @return
 */

ArrayList *arrayListInitialization(int initialLength, int sizeOfType) {
    ArrayList *list = (ArrayList *) malloc(sizeof(ArrayList));
    list->arr = (void **) malloc(sizeof(void *) * initialLength);
    list->length = initialLength;
    list->count = 0;
    list->sizeOfType = sizeOfType;

    return list;
}




/** This function will take the array list address, and the item address as a parameters,
    then it will put the item in the end of the array list.
 * @param list
 * @param item
 */

void arrayListAdd(ArrayList *list, void *item) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    if (list->count == list->length) {
        list->length = (int) (list->length * 1.5);
        list->arr = (void **) realloc(list->arr, sizeof(void *) * list->length);
    }

    list->arr[list->count++] = item;

}




/** This function will take the array list address, the items array, and the length of items array as a parameters,
    then it will copy the items array into the array list.
 * @param list
 * @param array
 * @param arrayLength
 */

void arrayListAddAll(ArrayList *list, void *array, int arrayLength) {
    if (list == NULL || array == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    if (list->length - list->count < arrayLength) {
        list->length = (int) (( list->length + (arrayLength - (list->length - list->count)) ) * 1.5);
        list->arr = (void **) realloc(list->arr, sizeof(void *) * list->length);
    }

    void *item;
    for (int i = 0; i < arrayLength; i++) {
        item = (void *) malloc(list->sizeOfType);
        memcpy(item, (array + list->sizeOfType * i), list->sizeOfType);
        arrayListAdd(list, item);
    }

}




/** This function will take the array list as a parameter,
    then it will remove the last item in the array list.
 * Note: if the array list is empty then the program will be terminated.
 * @param list
 */

void arrayListRemove(ArrayList *list) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (arrayListIsEmpty(list)) {
         fprintf(stderr,"Array list out of range.");
        exit(-3);
    }

    free(list->arr[arrayListGetLength(list) - 1]);
    list->count--;

}




/** This function will take the array list address, and the index as a parameters,
    then it will remove the item in the given index from the array list.
 * Note: if the index is out of the array list range then the program will be terminated.
 * @param list
 * @param index
 */

void arrayListRemoveAtIndex(ArrayList *list, int index) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (index < 0 || index >= arrayListGetLength(list)) {
         fprintf(stderr,"Index out of array list range.");
        exit(-3);
    }

    free(list->arr[index]);
    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];


}





/** This function will take the array list  address, the item address, and the comparator function as a parameters,
    then it will return one (1) if the item is in the array list,
    other wise it will return zero (0).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list
 * @param item
 * @param comparator
 * @return
 */

int arrayListContains(ArrayList *list, void *item,
        int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i], item) == 0)
            return 1;

    }

    return 0;

}




/** This function will take the array list address, the item address, and the comparator function address as a parameters,
    then it will return the index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list
 * @param item
 * @param comparator
 * @return
 */

int arrayListGetIndex(ArrayList *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i], item) == 0)
            return i;

    }

    return -1;

}




/** This function will take the array list address, the item address, and the comparator function address as a parameters,
    then it will return the last index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list
 * @param item
 * @param comparator
 * @return
 */

int arrayListGetLastIndex(ArrayList *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = list->count - 1; i >= 0; i--) {

        if (comparator(list->arr[i], item) == 0)
            return i;

    }

    return -1;

}





/** This function will take the array list address, and the index as a parameters,
    then it will return the item at the given index.
 * Note: if the index is out of the array list range then the program will be terminated.
 * @param list
 * @param index
 * @return
 */

void *arrayListGet(ArrayList *list, int index) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (index < 0 || index >= arrayListGetLength(list)) {
         fprintf(stderr,"Index out of array list range.");
        exit(-3);
    }

    return list->arr[index];

}




/** This function will take the array list address as a parameter,
    then it will return a void pointer array that consist of the array list elements.
 * @param list
 * @return
 */

void *arrayListToArray(ArrayList *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    void *array = (void *) malloc(list->sizeOfType * arrayListGetLength(list));

    for (int i = 0; i < arrayListGetLength(list); i++)
        memcpy(array + list->sizeOfType * i, list->arr[i], list->sizeOfType);


    return array;

}




/** This function will take the array list address, the start index, and the end index as a parameters,
    then it will return a void pointer array that consist of the items at the start index to end index - 1.
 * @param list
 * @param start
 * @param end
 * @return
 */

void *arrayListToSubArray(ArrayList *list, int start, int end) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (start < 0 || end > arrayListGetLength(list) || start > end) {
         fprintf(stderr,"Index out of array list range.");
        exit(-3);
    }

    void *array = (void *) malloc(list->sizeOfType * (end - start) );

    for (int i = start; i < end; i++)
        memcpy(array + list->sizeOfType * (i - start), list->arr[i], list->sizeOfType);


    return array;

}




/** This function will take the array list address, and the sort comparator function as a parameter,
    then it will sort the array list using qsort algorithm.
 * Note: the pointer will be sent to the sort comparator function will be a double void pointer (void **).
 * @param list
 * @param comparator
 */

void arrayListSort(ArrayList *list, int (*comparator)(const void *, const void *)) {
    qsort(list->arr, arrayListGetLength(list), sizeof(void *), comparator);
}




/** This function will take the array list address as a parameter,
 * then it will return the length of the array list.
 * @param list
 * @return
 */

int arrayListGetLength(ArrayList *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    return list->count;
}




/** This function will take the array list address as a parameter,
    then it will return one if the array list is empty,
    other wise it will return 0.
 * @param list
 * @return
 */

int arrayListIsEmpty(ArrayList *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    return list->count == 0;
}




/** This function will take the array list address, and the print function address as a parameter,
 * then it will call the print function and send every item in the array list to be printed.
 * @param list
 * @param printFun
 */

void printArrayList(ArrayList *list, void (*printFun) (const void *)) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        printFun(list->arr[i]);


}




/** This function will take the array list address as a parameter,
    then it will destroy and free all the array list items.
 * Note: the function will just clear the array list, but it will not destroy the array list.
 * @param list
 */

void clearArrayList(ArrayList *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        free(list->arr[i]);

    list->count = 0;

}




/** This function will take the array list address as a parameter,
 * then it will destroy and free the array list and all it's items.
 * @param list
 */

void destroyArrayList(ArrayList *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        free(list->arr[i]);

    free(list);

}