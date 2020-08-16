#include "DoublyLinkedListTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/LinkedLists/Headers/DoublyLinkedList.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 *
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerDLLT(int integer) {
    int *newInt = (int *) malloc(sizeof(int));

    *newInt = integer;
    return newInt;

}


/** This function will compare to integers pointers,
 * then it will return zero if they are equal, negative number if the second integer is bigger,
 * and positive number if the first integer is bigger.
 *
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is bigger, and positive number if the first integer is bigger.
 */

int compareIntPointersDLLT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 *
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerDLLT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


/** This function will take a linked list then it will insert,
 * from one to ten values into the linked list.
 *
 * @param list the linked list pointer
 */

void doublyLinkedListAddFrom1To10Values(DoublyLinkedList *list) {

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = i + 1;
    }

    doublyLinkedListAddAll(list, (void **) arr, 10);

    free(arr);

}


void testInvalidDoublyLinkedListInitialization(CuTest *cuTest) {

    DoublyLinkedList *list = doublyLinkedListInitialization(NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidDoublyLinkedListInitialization(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    CuAssertPtrNotNull(cuTest, list);

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListAddFirst(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListAddFirst(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListAddFirst(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    doublyLinkedListAddFirst(list, generateIntPointerDLLT(10));
    doublyLinkedListAddFirst(list, generateIntPointerDLLT(20));
    doublyLinkedListAddFirst(list, generateIntPointerDLLT(30));

    for (int i = list->length - 1; i >= 0; i--)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) doublyLinkedListGet(list, list->length - 1 - i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListAddLast(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListAddLast(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListAddLast(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    doublyLinkedListAddLast(list, generateIntPointerDLLT(10));
    doublyLinkedListAddLast(list, generateIntPointerDLLT(20));
    doublyLinkedListAddLast(list, generateIntPointerDLLT(30));

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListAddAtIndex(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListAddAtIndex(NULL, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListAddAtIndex(list, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 10;
    doublyLinkedListAddAtIndex(list, 0, &tempValue);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    doublyLinkedListAddLast(list, generateIntPointerDLLT(10));
    doublyLinkedListAddLast(list, generateIntPointerDLLT(30));
    doublyLinkedListAddLast(list, generateIntPointerDLLT(50));

    doublyLinkedListAddAtIndex(list, 1, generateIntPointerDLLT(20));
    doublyLinkedListAddAtIndex(list, 3, generateIntPointerDLLT(40));

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListAddAll(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListAddAll(list, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = i + 1;
    }

    doublyLinkedListAddAll(list, (void **) arr, 10);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *) doublyLinkedListGet(list, i));

    free(arr);
    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListDeleteFirst(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListDeleteFirst(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListDeleteFirst(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);

    doublyLinkedListDeleteFirst(list);
    doublyLinkedListDeleteFirst(list);
    doublyLinkedListDeleteFirst(list);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListDeleteFirstWtoFr(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListDeleteFirstWtoFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);

    int *currentItem;
    currentItem = (int *) doublyLinkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, 1, *currentItem);
    free(currentItem);

    currentItem = (int *) doublyLinkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, 2, *currentItem);
    free(currentItem);

    currentItem = (int *) doublyLinkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, 3, *currentItem);
    free(currentItem);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListDeleteLast(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListDeleteLast(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListDeleteLast(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);

    doublyLinkedListDeleteLast(list);
    doublyLinkedListDeleteLast(list);
    doublyLinkedListDeleteLast(list);

    CuAssertIntEquals(cuTest, 7, list->length);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListDeleteLastWtoFr(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListDeleteLastWtoFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);

    int *currentItem;
    currentItem = (int *) doublyLinkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, 10, *currentItem);
    free(currentItem);

    currentItem = (int *) doublyLinkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, 9, *currentItem);
    free(currentItem);

    currentItem = (int *) doublyLinkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, 8, *currentItem);
    free(currentItem);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListDeleteAtIndex(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListDeleteAtIndex(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListDeleteAtIndex(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    doublyLinkedListAddFrom1To10Values(list);

    doublyLinkedListDeleteAtIndex(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    doublyLinkedListDeleteAtIndex(list, 2);
    doublyLinkedListDeleteAtIndex(list, 1);
    doublyLinkedListDeleteAtIndex(list, 0);

    CuAssertIntEquals(cuTest, 7, list->length);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListDeleteAtIndexWtoFr(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListDeleteAtIndexWtoFr(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListDeleteAtIndexWtoFr(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);

    doublyLinkedListDeleteAtIndexWtoFr(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);


    int *currentItem;
    currentItem = (int *) doublyLinkedListDeleteAtIndexWtoFr(list, 2);
    CuAssertIntEquals(cuTest, 3, *currentItem);
    free(currentItem);

    currentItem = (int *) doublyLinkedListDeleteAtIndexWtoFr(list, 1);
    CuAssertIntEquals(cuTest, 2, *currentItem);
    free(currentItem);

    currentItem = (int *) doublyLinkedListDeleteAtIndexWtoFr(list, 0);
    CuAssertIntEquals(cuTest, 1, *currentItem);
    free(currentItem);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) doublyLinkedListGet(list, i));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListContains(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListContains(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    doublyLinkedListAddFrom1To10Values(list);

    int tempValue;
    for (int i = 0; i < list->length; i++) {
        tempValue = i + 1;
        CuAssertIntEquals(cuTest, 1, doublyLinkedListContains(list, &tempValue));
    }

    tempValue = 11;
    CuAssertIntEquals(cuTest, 0, doublyLinkedListContains(list, &tempValue));


    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListGetIndex(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListGetIndex(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListGetIndex(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    doublyLinkedListAddFrom1To10Values(list);

    int tempValue;
    for (int i = 0; i < list->length; i++) {
        tempValue = i + 1;
        CuAssertIntEquals(cuTest, i, doublyLinkedListGetIndex(list, &tempValue));
    }

    tempValue = 11;
    CuAssertIntEquals(cuTest, -1, doublyLinkedListGetIndex(list, &tempValue));


    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListGetItem(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListGetItem(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListGetItem(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    doublyLinkedListAddFrom1To10Values(list);

    int tempValue;
    for (int i = 0; i < list->length; i++) {
        tempValue = i + 1;
        CuAssertIntEquals(cuTest, tempValue, *(int *) doublyLinkedListGetItem(list, &tempValue));
    }

    tempValue = 11;
    CuAssertPtrEquals(cuTest, NULL, doublyLinkedListGetItem(list, &tempValue));


    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListGetFirst(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListGetFirst(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListGetFirst(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);


    CuAssertIntEquals(cuTest, 1, *(int *) doublyLinkedListGetFirst(list));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListGetLast(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListGetLast(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListGetLast(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);


    CuAssertIntEquals(cuTest, 10, *(int *) doublyLinkedListGetLast(list));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListGet(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListGet(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListGet(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    doublyLinkedListAddFrom1To10Values(list);

    doublyLinkedListGet(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) doublyLinkedListGet(list, i));


    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListGetLength(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, doublyLinkedListGetLength(list));


    doublyLinkedListAddFrom1To10Values(list);

    CuAssertIntEquals(cuTest, 10, doublyLinkedListGetLength(list));
    doublyLinkedListDeleteFirst(list);

    CuAssertIntEquals(cuTest, 9, doublyLinkedListGetLength(list));

    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListToArray(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);

    int **arr = (int **) doublyLinkedListToArray(list);

    for (int i = 0; i < doublyLinkedListGetLength(list); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) arr[i]);


    free(arr);
    destroyDoublyLinkedList(list);

}


DoublyLinkedList *printingDoublyLinkedList;

void printDoublyLinkedListFunLLT(const void *item) {
    doublyLinkedListAddLast(printingDoublyLinkedList, generateIntPointerDLLT(*(int *) item));
}

void testPrintDoublyLinkedList(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);
    printingDoublyLinkedList = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    printDoublyLinkedList(NULL, printDoublyLinkedListFunLLT);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    printDoublyLinkedList(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    doublyLinkedListAddFrom1To10Values(list);

    printDoublyLinkedList(list, printDoublyLinkedListFunLLT);

    for (int i = 0; i < doublyLinkedListGetLength(printingDoublyLinkedList); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) doublyLinkedListGet(printingDoublyLinkedList, i));


    destroyDoublyLinkedList(printingDoublyLinkedList);
    destroyDoublyLinkedList(list);

}


void testDoublyLinkedListIsEmpty(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, doublyLinkedListIsEmpty(list));

    doublyLinkedListAddFirst(list, generateIntPointerDLLT(1));

    CuAssertIntEquals(cuTest, 0, doublyLinkedListIsEmpty(list));

    destroyDoublyLinkedList(list);

}


void testClearDoublyLinkedList(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    doublyLinkedListClear(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, doublyLinkedListGetLength(list));

    doublyLinkedListAddFrom1To10Values(list);

    CuAssertIntEquals(cuTest, 10, doublyLinkedListGetLength(list));

    doublyLinkedListClear(list);

    CuAssertIntEquals(cuTest, 0, doublyLinkedListGetLength(list));

    destroyDoublyLinkedList(list);

}


void testDestroyDoublyLinkedList(CuTest *cuTest) {
    DoublyLinkedList *list = doublyLinkedListInitialization(free, compareIntPointersDLLT);

    destroyDoublyLinkedList(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    destroyDoublyLinkedList(list);

}


typedef struct DoublyLinkedListTestStruct {

    int iData;
    char *cData;

} DoublyLinkedListTestStruct;


void freeDoublyLinkedListStruct(void *item) {
    DoublyLinkedListTestStruct *l = (DoublyLinkedListTestStruct *) item;
    free(l->cData);
    free(l);
}


int doublyLinkedListTestStructComp(const void *item1, const void *item2) {
    DoublyLinkedListTestStruct *l1 = (DoublyLinkedListTestStruct *) item1;
    DoublyLinkedListTestStruct *l2 = (DoublyLinkedListTestStruct *) item2;

    int iDataFlag = l1->iData == l2->iData;
    int cDataFlag = strcmp(l1->cData, l2->cData);

    return !iDataFlag || cDataFlag;

}


void generalDoublyLinkedListTest(CuTest *cuTest) {

    DoublyLinkedList *list = doublyLinkedListInitialization(freeDoublyLinkedListStruct, doublyLinkedListTestStructComp);
    char numbersStr[10][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    DoublyLinkedListTestStruct *item;


    CuAssertIntEquals(cuTest, 1, doublyLinkedListIsEmpty(list));
    CuAssertIntEquals(cuTest, 0, doublyLinkedListGetLength(list));

    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 2;
    item->cData = (char *) malloc(sizeof(char) * (strlen("two") + 1));
    strcpy(item->cData, "two");
    doublyLinkedListAddFirst(list, item);


    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 1;
    item->cData = (char *) malloc(sizeof(char) * (strlen("one") + 1));
    strcpy(item->cData, "one");
    doublyLinkedListAddFirst(list, item);


    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 3;
    item->cData = (char *) malloc(sizeof(char) * (strlen("three") + 1));
    strcpy(item->cData, "three");
    doublyLinkedListAddLast(list, item);


    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 4;
    item->cData = (char *) malloc(sizeof(char) * (strlen("four") + 1));
    strcpy(item->cData, "four");
    doublyLinkedListAddLast(list, item);


    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 5;
    item->cData = (char *) malloc(sizeof(char) * (strlen("five") + 1));
    strcpy(item->cData, "five");
    doublyLinkedListAddLast(list, item);

    CuAssertIntEquals(cuTest, 5, doublyLinkedListGetLength(list));

    DoublyLinkedListTestStruct **structArr = (DoublyLinkedListTestStruct **) malloc(
            sizeof(DoublyLinkedListTestStruct *) * 3);

    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 6;
    item->cData = (char *) malloc(sizeof(char) * (strlen("six") + 1));
    strcpy(item->cData, "six");
    structArr[0] = item;

    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 7;
    item->cData = (char *) malloc(sizeof(char) * (strlen("seven") + 1));
    strcpy(item->cData, "seven");
    structArr[1] = item;

    item = (DoublyLinkedListTestStruct *) malloc(sizeof(DoublyLinkedListTestStruct));
    item->iData = 8;
    item->cData = (char *) malloc(sizeof(char) * (strlen("eight") + 1));
    strcpy(item->cData, "eight");
    structArr[2] = item;

    doublyLinkedListAddAll(list, (void **) structArr, 3);

    CuAssertIntEquals(cuTest, 8, doublyLinkedListGetLength(list));
    CuAssertIntEquals(cuTest, 0, doublyLinkedListIsEmpty(list));

    for (int i = 0; i < doublyLinkedListGetLength(list); i++) {
        DoublyLinkedListTestStruct *currentItem = (DoublyLinkedListTestStruct *) doublyLinkedListGet(list, i);
        CuAssertIntEquals(cuTest, i + 1, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[i], currentItem->cData);
        CuAssertIntEquals(cuTest, 1, doublyLinkedListContains(list, currentItem));
        CuAssertIntEquals(cuTest, i, doublyLinkedListGetIndex(list, currentItem));
        CuAssertPtrEquals(cuTest, currentItem, doublyLinkedListGetItem(list, currentItem));
    }

    doublyLinkedListDeleteFirst(list);
    doublyLinkedListDeleteLast(list);

    for (int i = 0, counter = 0; i < doublyLinkedListGetLength(list); counter++) {
        DoublyLinkedListTestStruct *currentItem = (DoublyLinkedListTestStruct *) doublyLinkedListDeleteAtIndexWtoFr(
                list, i);
        CuAssertIntEquals(cuTest, counter + 2, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[counter + 1], currentItem->cData);
        freeDoublyLinkedListStruct(currentItem);

    }


    free(structArr);
    destroyDoublyLinkedList(list);

}


CuSuite *createDoublyLinkedListTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidDoublyLinkedListInitialization);
    SUITE_ADD_TEST(suite, testValidDoublyLinkedListInitialization);
    SUITE_ADD_TEST(suite, testDoublyLinkedListAddFirst);
    SUITE_ADD_TEST(suite, testDoublyLinkedListAddLast);
    SUITE_ADD_TEST(suite, testDoublyLinkedListAddAtIndex);
    SUITE_ADD_TEST(suite, testDoublyLinkedListAddAll);
    SUITE_ADD_TEST(suite, testDoublyLinkedListDeleteFirst);
    SUITE_ADD_TEST(suite, testDoublyLinkedListDeleteFirstWtoFr);
    SUITE_ADD_TEST(suite, testDoublyLinkedListDeleteLast);
    SUITE_ADD_TEST(suite, testDoublyLinkedListDeleteLastWtoFr);
    SUITE_ADD_TEST(suite, testDoublyLinkedListDeleteAtIndex);
    SUITE_ADD_TEST(suite, testDoublyLinkedListDeleteAtIndexWtoFr);
    SUITE_ADD_TEST(suite, testDoublyLinkedListContains);
    SUITE_ADD_TEST(suite, testDoublyLinkedListGetIndex);
    SUITE_ADD_TEST(suite, testDoublyLinkedListGetItem);
    SUITE_ADD_TEST(suite, testDoublyLinkedListGetFirst);
    SUITE_ADD_TEST(suite, testDoublyLinkedListGetLast);
    SUITE_ADD_TEST(suite, testDoublyLinkedListGet);
    SUITE_ADD_TEST(suite, testDoublyLinkedListGetLength);
    SUITE_ADD_TEST(suite, testDoublyLinkedListToArray);
    SUITE_ADD_TEST(suite, testDoublyLinkedListIsEmpty);
    SUITE_ADD_TEST(suite, testPrintDoublyLinkedList);
    SUITE_ADD_TEST(suite, testClearDoublyLinkedList);
    SUITE_ADD_TEST(suite, testDestroyDoublyLinkedList);

    SUITE_ADD_TEST(suite, generalDoublyLinkedListTest);

    return suite;

}


void doublyLinkedListUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Doubly Linked List Test**\n");

    CuSuite *suite = createDoublyLinkedListTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}