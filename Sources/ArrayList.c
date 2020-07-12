#include "../Headers/ArrayList.h"


void arrayListDestroyItem(ArrayListItem *item, void (*freeFun)(void *));



/** This function will take the initial length of the array list, and the size of the stored type as a parameter,
 * then it will initialize a new array list in the memory and set it's fields then return it.
 * @param initialLength the initial length of the array list.
 * @param freeFun the function address that will be called to free the array list items.
 * @return it will return the new array list address
 */

ArrayList *arrayListInitialization(int initialLength, void (*freeFun)(void *)) {
    ArrayList *list = (ArrayList *) malloc(sizeof(ArrayList));
    list->arr = (ArrayListItem **) malloc(sizeof(ArrayListItem *) * initialLength);
    list->length = initialLength > 0 ? initialLength : 1;
    list->count = 0;
    list->freeItem = freeFun;

    return list;
}




/** This function will take the array list address, and the item address as a parameters,
    then it will put the item in the end of the array list.
 * @param list the array list address
 * @param item the item address
 * @param sizeOfItem the size of the new item in bytes
 */

void arrayListAdd(ArrayList *list, void *item, int sizeOfItem) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    if (list->count == list->length) {
        list->length = (int) ceil(list->length * 1.5);
        list->arr = (ArrayListItem **) realloc(list->arr, sizeof(ArrayListItem *) * list->length);
    }

    ArrayListItem *newItem = (ArrayListItem *) malloc(sizeof(ArrayListItem));
    newItem->value = item;
    newItem->sizeOfItem = sizeOfItem;
    list->arr[list->count++] = newItem;

}




/** This function will take the array list address, the items array, the length of items array, and the size if the items as a parameters,
    then it will copy the items array into the array list.
 * @param list the array list address
 * @param array the array address that will be inserted in the array list
 * @param arrayLength the length of the array that will be added
 * @param sizeOfItem the size of the array items in bytes
 */

void arrayListAddAll(ArrayList *list, void **array, int arrayLength, int sizeOfItem) {
    if (list == NULL || array == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < arrayLength; i++)
        arrayListAdd(list, array[i], sizeOfItem);

}




/** This function will take the array list as a parameter,
    then it will remove the last item in the array list.
 * Note: if the array list is empty then the program will be terminated.
 * @param list the array list address
 */

void arrayListRemove(ArrayList *list) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (arrayListIsEmpty(list)) {
         fprintf(stderr,"Array list out of range.");
        exit(-3);
    }

    arrayListDestroyItem(list->arr[arrayListGetLength(list) - 1], list->freeItem);
    list->count--;

}




/** This function will take the array list address, and the index as a parameters,
    then it will remove the item in the given index from the array list.
 * Note: if the index is out of the array list range then the program will be terminated.
 * @param list the array list address
 * @param index the index of the item that will be deleted
 */

void arrayListRemoveAtIndex(ArrayList *list, int index) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (index < 0 || index >= arrayListGetLength(list)) {
         fprintf(stderr,"Index out of array list range.");
        exit(-3);
    }

    arrayListDestroyItem(list->arr[index], list->freeItem);
    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];


}





/** This function will take the array list  address, the item address, and the comparator function as a parameters,
    then it will return one (1) if the item is in the array list,
    other wise it will return zero (0).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list the array list address
 * @param item the item that will be compared by address
 * @param comparator the comparator function address
 * @return it will return one if the item is in the array list other wise it will return zero
 */

int arrayListContains(ArrayList *list, void *item,
        int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i]->value, item) == 0)
            return 1;

    }

    return 0;

}




/** This function will take the array list address, the item address, and the comparator function address as a parameters,
    then it will return the index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list the array list address
 * @param item the item address that will be searching for
 * @param comparator the comparator function address
 * @return it will return the item address if found, other wise it will return minus one
 */

int arrayListGetIndex(ArrayList *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < list->count; i++) {

        if (comparator(list->arr[i]->value, item) == 0)
            return i;

    }

    return -1;

}




/** This function will take the array list address, the item address, and the comparator function address as a parameters,
    then it will return the last index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * @param list the array list address
 * @param item the item address that will be searching for
 * @param comparator the comparator function address
 * @return it will return the item address if found, other wise it will return minus one
 */

int arrayListGetLastIndex(ArrayList *list, void *item,
                      int (*comparator)(const void *, const void *)) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = list->count - 1; i >= 0; i--) {

        if (comparator(list->arr[i]->value, item) == 0)
            return i;

    }

    return -1;

}





/** This function will take the array list address, and the index as a parameters,
    then it will return the item at the given index.
 * Note: if the index is out of the array list range then the program will be terminated.
 * @param list the array list address
 * @param index the item index
 * @return it will return a void pointer to the item
 */

void *arrayListGet(ArrayList *list, int index) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (index < 0 || index >= arrayListGetLength(list)) {
         fprintf(stderr,"Index out of array list range.");
        exit(-3);
    }

    return list->arr[index]->value;

}




/** This function will take the array list address as a parameter,
    then it will return a void pointer array that consist of the array list elements.
 * @param list the array list address
 * @return it will return a double void pointer to an array that has a copy of the items
 */

void **arrayListToArray(ArrayList *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    void **array = (void **) malloc(sizeof(void *) * arrayListGetLength(list));

    for (int i = 0; i < arrayListGetLength(list); i++) {
        array[i] = (void *) malloc(list->arr[i]->sizeOfItem);
        memcpy(array[i], list->arr[i]->value, list->arr[i]->sizeOfItem);
    }

    return array;

}




/** This function will take the array list address, the start index, and the end index as a parameters,
    then it will return a void pointer array that consist of the items at the start index to end index - 1.
 * @param list the array list address
 * @param start the start index
 * @param end the end index
 * @return it will return a double void pointer that has a copy of the items in the array list
 */

void **arrayListToSubArray(ArrayList *list, int start, int end) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    } else if (start < 0 || end > arrayListGetLength(list) || start > end) {
         fprintf(stderr,"Index out of array list range.");
        exit(-3);
    }

    void **array = (void **) malloc(sizeof(void *) * (end - start) );

    for (int i = start; i < end; i++) {
        array[i] = (void *) malloc(list->arr[i]->sizeOfItem);
        memcpy(array[i - start], list->arr[i]->value, list->arr[i]->sizeOfItem);
    }


    return array;

}




/** This function will take the array list address, and the sort comparator function as a parameter,
    then it will sort the array list using qsort algorithm.
 * Note: the pointer will be sent to the sort comparator function will be a double void pointer (void **) of an array list item.
 * @param list the array list address
 * @param comparator the comparator function address
 * Example of comparator function if the items are integers:
 * int comp(const void *item1, const void *item2) {
    return *(int *)(*(ArrayListItem **)item1)->value - *(int *)(*(ArrayListItem **)item2)->value;}
 */

void arrayListSort(ArrayList *list, int (*comparator)(const void *, const void *)) {
    qsort(list->arr, arrayListGetLength(list), sizeof(ArrayListItem *), comparator);
}




/** This function will take the array list address as a parameter,
 * then it will return the length of the array list.
 * @param list the array list address
 * @return it will return the number of items in the array list
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
 * @param list the array list address
 * @return it will return one if the array is empty, other wise it will return zero
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
 * @param list the array list address
 * @param printFun the print function address
 */

void printArrayList(ArrayList *list, void (*printFun) (const void *)) {
    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        printFun(list->arr[i]->value);


}




/** This function will take the array list address as a parameter,
    then it will destroy and free all the array list items.
 * Note: the function will just clear the array list, but it will not destroy the array list.
 * @param list the array list address
 */

void clearArrayList(ArrayList *list) {

    if (list == NULL) {
         fprintf(stderr,"Illegal argument, the array list is NULL.");
        exit(-3);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        arrayListDestroyItem(list->arr[i], list->freeItem);


    list->count = 0;

}


/** This function will take the array list address as a parameter,
 * then it will destroy and free the array list and all it's items.
 * @param list the array list address
 */

void destroyArrayList(ArrayList *list) {

    clearArrayList(list);
    free(list->arr);
    free(list);

}




/** This function will take the item address, and the free function address as a parameters,
 * then it will free the item container and it's value.
 * Note: this function should only be called from the array list functions.
 * @param item the item container address
 * @param freeFun the free item function address
 */

void arrayListDestroyItem(ArrayListItem *item, void (*freeFun)(void *)) {
    freeFun(item->value);
    free(item);

}