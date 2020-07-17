#include "../Headers/ArrayList.h"
#include "../Headers/Utils.h"
#include <math.h>






/** This function will take the initial length of the array list, and the freeing and comparator functions as a parameter,
 * then it will initialize a new array list in the memory and set it's fields then return it.
 * @param initialLength the initial length of the array list.
 * @param freeFun the function address that will be called to free the array list items.
 * @param comparator the comparator function address, that will be called to compare two items in the array list
 * @return
 */

ArrayList *arrayListInitialization(int initialLength, void (*freeFun)(void *), int (*comparator)(const void *, const void *)) {
    if (freeFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function", "array list data structure");
        exit(INVALID_ARG);
    }

    ArrayList *list = (ArrayList *) malloc(sizeof(ArrayList));
    if (list == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "data structure", "array list data structure");
        exit(FAILED_ALLOCATION);
    }

    list->arr = (void **) malloc(sizeof(void *) * initialLength);
    if (list->arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "items memory", "array list data structure");
        exit(FAILED_ALLOCATION);
    }

    list->length = initialLength > 0 ? initialLength : 1;
    list->count = 0;
    list->freeItem = freeFun;
    list->comparator = comparator;

    return list;
}




/** This function will take the array list address, and the item address as a parameters,
    then it will put the item in the end of the array list.
 * @param list the array list address
 * @param item the item address
 */

void arrayListAdd(ArrayList *list, void *item) {
    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "array list data structure");
        exit(INVALID_ARG);
    }

    if (list->count == list->length) {
        list->length = (int) ceil(list->length * 1.5);

        list->arr = (void **) realloc(list->arr, sizeof(void *) * list->length);
        if (list == NULL) {
            fprintf(stderr, FAILED_REALLOCATION_MESSAGE, "items memory", "array list data structure");
            exit(FAILED_REALLOCATION);
        }

    }


    list->arr[list->count++] = item;

}




/** This function will take the array list address, the items array, and the length of items array as a parameters,
    then it will copy the items array into the array list.
 * @param list the array list address
 * @param array the array address that will be inserted in the array list
 * @param arrayLength the length of the array that will be added
 */

void arrayListAddAll(ArrayList *list, void **array, int arrayLength) {
    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (array == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array", "array list data structure");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < arrayLength; i++)
        arrayListAdd(list, array[i]);

}




/** This function will take the array list as a parameter,
    then it will remove the last item in the array list.
 * Note: if the array list is empty then the program will be terminated.
 * @param list the array list address
 */

void arrayListRemove(ArrayList *list) {
    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (arrayListIsEmpty(list)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "array list data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }

    list->freeItem(list->arr[arrayListGetLength(list) - 1]);

    list->count--;

}



/** This function will take the array list as a parameter,
    then it will remove the last item in the array list, without freeing the item.
 * Note: if the array list is empty then the program will be terminated.
 * @param list the array list address
 */

void arrayListRemoveWtFr(ArrayList *list) {
    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (arrayListIsEmpty(list)) {
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "array list data structure");
        exit(EMPTY_DATA_STRUCTURE);
    }


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
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (index < 0 || index >= arrayListGetLength(list)) {
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "array list data structure");
        exit(OUT_OF_RANGE);
    }

    list->freeItem(list->arr[index]);
    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];


}



/** This function will take the array list address, and the index as a parameters,
    then it will remove the item in the given index from the array list, without freeing the item.
 * Note: if the index is out of the array list range then the program will be terminated.
 * @param list the array list address
 * @param index the index of the item that will be deleted
 */

void arrayListRemoveAtIndexWtFr(ArrayList *list, int index) {
    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (index < 0 || index >= arrayListGetLength(list)) {
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "array list data structure");
        exit(OUT_OF_RANGE);
    }

    list->count--;

    for (int i = index; i < list->count; i++) //this loop will shift the items to the left to delete the index.
        list->arr[i] = list->arr[i + 1];


}





/** This function will take the array list address, and the item address as a parameters,
    then it will return one (1) if the item is in the array list,
    other wise it will return zero (0).
 * Note: comparator function should return zero (0) when the two items are equal.
 * Note: this function will not free the passed item
 * @param list the array list address
 * @param item the item that will be compared by address
 * @return it will return one if the item is in the array list other wise it will return zero
 */

int arrayListContains(ArrayList *list, void *item) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (list->comparator == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "array list data structure");
        exit(NULL_POINTER);
    }

    for (int i = 0; i < list->count; i++) {

        if (list->comparator(item, list->arr[i]) == 0)
            return 1;

    }

    return 0;

}




/** This function will take the array list address, and the item address as a parameters,
    then it will return the index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * Note: this function will not free the passed item
 * @param list the array list address
 * @param item the item address that will be searching for
 * @return it will return the item address if found, other wise it will return minus one
 */

int arrayListGetIndex(ArrayList *list, void *item) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (list->comparator == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "array list data structure");
        exit(NULL_POINTER);
    }

    for (int i = 0; i < list->count; i++) {

        if (list->comparator(list->arr[i], item) == 0)
            return i;

    }

    return -1;

}




/** This function will take the array list address, and the item address as a parameters,
    then it will return the last index of the item if found,
    other wise it will return minus one (-1).
 * Note: comparator function should return zero (0) when the two items are equal.
 * Note: this function will not free the passed item
 * @param list the array list address
 * @param item the item address that will be searching for
 * @return it will return the item address if found, other wise it will return minus one
 */

int arrayListGetLastIndex(ArrayList *list, void *item) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (list->comparator == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "array list data structure");
        exit(NULL_POINTER);
    }

    for (int i = list->count - 1; i >= 0; i--) {

        if (list->comparator(list->arr[i], item) == 0)
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
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (index < 0 || index >= arrayListGetLength(list)) {
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "array list data structure");
        exit(OUT_OF_RANGE);
    }

    return list->arr[index];

}




/** This function will take the array list address as a parameter,
    then it will return a void pointer array that consist of the array list elements.
 * @param list the array list address
 * @return it will return a double void pointer to an array that has a copy of the items
 */

void **arrayListToArray(ArrayList *list) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    }

    void **array = (void **) malloc(sizeof(void *) * arrayListGetLength(list));
    if (array == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "array list data structure");
        exit(FAILED_ALLOCATION);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        array[i] = list->arr[i];

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
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (start < 0 || end > arrayListGetLength(list) || start > end) {
        fprintf(stderr, OUT_OF_RANGE_MESSAGE, "array list data structure");
        exit(OUT_OF_RANGE);
    }

    void **array = (void **) malloc(sizeof(void *) * (end - start) );
    if (array == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "array list data structure");
        exit(FAILED_ALLOCATION);
    }

    for (int i = start; i < end; i++)
        array[i] = list->arr[i];


    return array;

}




/** This function will take the array list address, and the sort comparator function as a parameter,
    then it will sort the array list using qsort algorithm.
 * Note: the pointer will be sent to the sort comparator function will be a double void pointer (void **) of an array list item.
 * @param list the array list address
 * Example of comparator function if the items are integers:
 * int comp(const void *item1, const void *item2) {
    return *(int *)(*(void **)item1)->item - *(int *)(*(void **)item2)->item;}
 */

void arrayListSort(ArrayList *list) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (list->comparator == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "comparator function", "array list data structure");
        exit(NULL_POINTER);
    }

    qsort(list->arr, arrayListGetLength(list), sizeof(void *), list->comparator);

}






/** This function will take the array list address as a parameter,
 * then it will return the length of the array list.
 * @param list the array list address
 * @return it will return the number of items in the array list
 */

int arrayListGetLength(ArrayList *list) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    }

    return list->count;

}




/** This function will take the array list address as a parameter,
    then it will return one if the array list is empty,
    other wise it will return 0.
 * @param list the array list address
 * @return it will return one if the array list is empty, other wise it will return zero
 */

int arrayListIsEmpty(ArrayList *list) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
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
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    } else if (printFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "array list data structure");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        printFun(list->arr[i]);


}




/** This function will take the array list address as a parameter,
    then it will destroy and free all the array list items.
 * Note: the function will just clear the array list, but it will not destroy the array list.
 * @param list the array list address
 */

void clearArrayList(ArrayList *list) {

    if (list == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array list pointer", "array list data structure");
        exit(INVALID_ARG);
    }

    for (int i = 0; i < arrayListGetLength(list); i++)
        list->freeItem(list->arr[i]);


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