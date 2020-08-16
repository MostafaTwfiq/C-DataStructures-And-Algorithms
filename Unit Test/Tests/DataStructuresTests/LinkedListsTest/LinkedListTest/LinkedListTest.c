#include "LinkedListTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/LinkedLists/Headers/LinkedList.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerLLT(int integer) {
    int *newInt = (int *) malloc(sizeof(int));

    *newInt = integer;
    return newInt;

}


/** This function will compare to integers pointers,
 * then it will return zero if they are equal, negative number if the second integer is bigger,
 * and positive number if the first integer is bigger.
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is bigger, and positive number if the first integer is bigger.
 */

int compareIntPointersLLT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerLLT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


/** This function will take a linked list then it will insert,
 * from one to ten values into the linked list.
 * @param list the linked list pointer
 */

void linkedListAddFrom1To10Values(LinkedList *list) {

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = i + 1;
    }

    linkedListAddAll(list, (void **) arr, 10);

    free(arr);

}


void testInvalidLinkedListInitialization(CuTest *cuTest) {

    LinkedList *list = linkedListInitialization(NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidLinkedListInitialization(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    CuAssertPtrNotNull(cuTest, list);

    destroyLinkedList(list);

}


void testLinkedListAddFirst(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddFirst(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListAddFirst(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linkedListAddFirst(list, generateIntPointerLLT(10));
    linkedListAddFirst(list, generateIntPointerLLT(20));
    linkedListAddFirst(list, generateIntPointerLLT(30));

    for (int i = list->length - 1; i >= 0; i--)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) linkedListGet(list, list->length - 1 - i));

    destroyLinkedList(list);

}


void testLinkedListAddLast(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddLast(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListAddLast(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linkedListAddLast(list, generateIntPointerLLT(10));
    linkedListAddLast(list, generateIntPointerLLT(20));
    linkedListAddLast(list, generateIntPointerLLT(30));

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListAddAtIndex(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddAtIndex(NULL, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListAddAtIndex(list, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 10;
    linkedListAddAtIndex(list, 0, &tempValue);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    linkedListAddLast(list, generateIntPointerLLT(10));
    linkedListAddLast(list, generateIntPointerLLT(30));
    linkedListAddLast(list, generateIntPointerLLT(50));

    linkedListAddAtIndex(list, 1, generateIntPointerLLT(20));
    linkedListAddAtIndex(list, 3, generateIntPointerLLT(40));

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListAddAll(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListAddAll(list, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = i + 1;
    }

    linkedListAddAll(list, (void **) arr, 10);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *) linkedListGet(list, i));

    free(arr);
    destroyLinkedList(list);

}


void testLinkedListDeleteFirst(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteFirst(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListDeleteFirst(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);

    linkedListDeleteFirst(list);
    linkedListDeleteFirst(list);
    linkedListDeleteFirst(list);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListDeleteFirstWtoFr(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteFirstWtoFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);

    int *currentItem;
    currentItem = (int *) linkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, 1, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, 2, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, 3, *currentItem);
    free(currentItem);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListDeleteLast(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteLast(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListDeleteLast(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);

    linkedListDeleteLast(list);
    linkedListDeleteLast(list);
    linkedListDeleteLast(list);

    CuAssertIntEquals(cuTest, 7, list->length);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListDeleteLastWtoFr(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteLastWtoFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);

    int *currentItem;
    currentItem = (int *) linkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, 10, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, 9, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, 8, *currentItem);
    free(currentItem);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListDeleteAtIndex(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteAtIndex(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListDeleteAtIndex(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    linkedListAddFrom1To10Values(list);

    linkedListDeleteAtIndex(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    linkedListDeleteAtIndex(list, 2);
    linkedListDeleteAtIndex(list, 1);
    linkedListDeleteAtIndex(list, 0);

    CuAssertIntEquals(cuTest, 7, list->length);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListDeleteAtIndexWtoFr(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteAtIndexWtoFr(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListDeleteAtIndexWtoFr(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);

    linkedListDeleteAtIndexWtoFr(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);


    int *currentItem;
    currentItem = (int *) linkedListDeleteAtIndexWtoFr(list, 2);
    CuAssertIntEquals(cuTest, 3, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteAtIndexWtoFr(list, 1);
    CuAssertIntEquals(cuTest, 2, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteAtIndexWtoFr(list, 0);
    CuAssertIntEquals(cuTest, 1, *currentItem);
    free(currentItem);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *) linkedListGet(list, i));

    destroyLinkedList(list);

}


void testLinkedListContains(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListContains(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    linkedListAddFrom1To10Values(list);

    int tempValue;
    for (int i = 0; i < list->length; i++) {
        tempValue = i + 1;
        CuAssertIntEquals(cuTest, 1, linkedListContains(list, &tempValue));
    }

    tempValue = 11;
    CuAssertIntEquals(cuTest, 0, linkedListContains(list, &tempValue));


    destroyLinkedList(list);

}


void testLinkedListGetIndex(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListGetIndex(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListGetIndex(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    linkedListAddFrom1To10Values(list);

    int tempValue;
    for (int i = 0; i < list->length; i++) {
        tempValue = i + 1;
        CuAssertIntEquals(cuTest, i, linkedListGetIndex(list, &tempValue));
    }

    tempValue = 11;
    CuAssertIntEquals(cuTest, -1, linkedListGetIndex(list, &tempValue));


    destroyLinkedList(list);

}


void testLinkedListGetItem(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListGetItem(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListGetItem(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    linkedListAddFrom1To10Values(list);

    int tempValue;
    for (int i = 0; i < list->length; i++) {
        tempValue = i + 1;
        CuAssertIntEquals(cuTest, tempValue, *(int *) linkedListGetItem(list, &tempValue));
    }

    tempValue = 11;
    CuAssertPtrEquals(cuTest, NULL, linkedListGetItem(list, &tempValue));


    destroyLinkedList(list);

}


void testLinkedListGetFirst(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListGetFirst(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListGetFirst(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);


    CuAssertIntEquals(cuTest, 1, *(int *) linkedListGetFirst(list));

    destroyLinkedList(list);

}


void testLinkedListGetLast(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListGetLast(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListGetLast(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);


    CuAssertIntEquals(cuTest, 10, *(int *) linkedListGetLast(list));

    destroyLinkedList(list);

}


void testLinkedListGet(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListGet(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListGet(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    linkedListAddFrom1To10Values(list);

    linkedListGet(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) linkedListGet(list, i));


    destroyLinkedList(list);

}


void testLinkedListGetLength(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, linkedListGetLength(list));


    linkedListAddFrom1To10Values(list);

    CuAssertIntEquals(cuTest, 10, linkedListGetLength(list));
    linkedListDeleteFirst(list);

    CuAssertIntEquals(cuTest, 9, linkedListGetLength(list));

    destroyLinkedList(list);

}


void testLinkedListToArray(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);

    int **arr = (int **) linkedListToArray(list);

    for (int i = 0; i < linkedListGetLength(list); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) arr[i]);


    free(arr);
    destroyLinkedList(list);

}


LinkedList *printingLinkedList;

void printLinkedListFunLLT(const void *item) {
    linkedListAddLast(printingLinkedList, generateIntPointerLLT(*(int *) item));
}

void testPrintLinkedList(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);
    printingLinkedList = linkedListInitialization(free, compareIntPointersLLT);

    printLinkedList(NULL, printLinkedListFunLLT);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    printLinkedList(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linkedListAddFrom1To10Values(list);

    printLinkedList(list, printLinkedListFunLLT);

    for (int i = 0; i < linkedListGetLength(printingLinkedList); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) linkedListGet(printingLinkedList, i));


    destroyLinkedList(printingLinkedList);
    destroyLinkedList(list);

}


void testLinkedListIsEmpty(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, linkedListIsEmpty(list));

    linkedListAddFirst(list, generateIntPointerLLT(1));

    CuAssertIntEquals(cuTest, 0, linkedListIsEmpty(list));

    destroyLinkedList(list);

}


void testClearLinkedList(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListClear(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, linkedListGetLength(list));

    linkedListAddFrom1To10Values(list);

    CuAssertIntEquals(cuTest, 10, linkedListGetLength(list));

    linkedListClear(list);

    CuAssertIntEquals(cuTest, 0, linkedListGetLength(list));

    destroyLinkedList(list);

}


void testDestroyLinkedList(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    destroyLinkedList(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    destroyLinkedList(list);

}


typedef struct LinkedListTestStruct {

    int iData;
    char *cData;

} LinkedListTestStruct;


void freeLinkedListStruct(void *item) {
    LinkedListTestStruct *l = (LinkedListTestStruct *) item;
    free(l->cData);
    free(l);
}


int linkedListTestStructComp(const void *item1, const void *item2) {
    LinkedListTestStruct *l1 = (LinkedListTestStruct *) item1;
    LinkedListTestStruct *l2 = (LinkedListTestStruct *) item2;

    int iDataFlag = l1->iData == l2->iData;
    int cDataFlag = strcmp(l1->cData, l2->cData);

    return !iDataFlag || cDataFlag;

}


void generalLinkedListTest(CuTest *cuTest) {

    LinkedList *list = linkedListInitialization(freeLinkedListStruct, linkedListTestStructComp);
    char numbersStr[10][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    LinkedListTestStruct *item;


    CuAssertIntEquals(cuTest, 1, linkedListIsEmpty(list));
    CuAssertIntEquals(cuTest, 0, linkedListGetLength(list));

    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 2;
    item->cData = (char *) malloc(sizeof(char) * (strlen("two") + 1));
    strcpy(item->cData, "two");
    linkedListAddFirst(list, item);


    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 1;
    item->cData = (char *) malloc(sizeof(char) * (strlen("one") + 1));
    strcpy(item->cData, "one");
    linkedListAddFirst(list, item);


    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 3;
    item->cData = (char *) malloc(sizeof(char) * (strlen("three") + 1));
    strcpy(item->cData, "three");
    linkedListAddLast(list, item);


    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 4;
    item->cData = (char *) malloc(sizeof(char) * (strlen("four") + 1));
    strcpy(item->cData, "four");
    linkedListAddLast(list, item);


    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 5;
    item->cData = (char *) malloc(sizeof(char) * (strlen("five") + 1));
    strcpy(item->cData, "five");
    linkedListAddLast(list, item);

    CuAssertIntEquals(cuTest, 5, linkedListGetLength(list));

    LinkedListTestStruct **structArr = (LinkedListTestStruct **) malloc(sizeof(LinkedListTestStruct *) * 3);

    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 6;
    item->cData = (char *) malloc(sizeof(char) * (strlen("six") + 1));
    strcpy(item->cData, "six");
    structArr[0] = item;

    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 7;
    item->cData = (char *) malloc(sizeof(char) * (strlen("seven") + 1));
    strcpy(item->cData, "seven");
    structArr[1] = item;

    item = (LinkedListTestStruct *) malloc(sizeof(LinkedListTestStruct));
    item->iData = 8;
    item->cData = (char *) malloc(sizeof(char) * (strlen("eight") + 1));
    strcpy(item->cData, "eight");
    structArr[2] = item;

    linkedListAddAll(list, (void **) structArr, 3);

    CuAssertIntEquals(cuTest, 8, linkedListGetLength(list));
    CuAssertIntEquals(cuTest, 0, linkedListIsEmpty(list));

    for (int i = 0; i < linkedListGetLength(list); i++) {
        LinkedListTestStruct *currentItem = (LinkedListTestStruct *) linkedListGet(list, i);
        CuAssertIntEquals(cuTest, i + 1, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[i], currentItem->cData);
        CuAssertIntEquals(cuTest, 1, linkedListContains(list, currentItem));
        CuAssertIntEquals(cuTest, i, linkedListGetIndex(list, currentItem));
        CuAssertPtrEquals(cuTest, currentItem, linkedListGetItem(list, currentItem));
    }

    linkedListDeleteFirst(list);
    linkedListDeleteLast(list);

    for (int i = 0, counter = 0; i < linkedListGetLength(list); counter++) {
        LinkedListTestStruct *currentItem = (LinkedListTestStruct *) linkedListDeleteAtIndexWtoFr(list, i);
        CuAssertIntEquals(cuTest, counter + 2, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[counter + 1], currentItem->cData);
        freeLinkedListStruct(currentItem);

    }


    free(structArr);
    destroyLinkedList(list);

}


CuSuite *createLinkedListTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidLinkedListInitialization);
    SUITE_ADD_TEST(suite, testValidLinkedListInitialization);
    SUITE_ADD_TEST(suite, testLinkedListAddFirst);
    SUITE_ADD_TEST(suite, testLinkedListAddLast);
    SUITE_ADD_TEST(suite, testLinkedListAddAtIndex);
    SUITE_ADD_TEST(suite, testLinkedListAddAll);
    SUITE_ADD_TEST(suite, testLinkedListDeleteFirst);
    SUITE_ADD_TEST(suite, testLinkedListDeleteFirstWtoFr);
    SUITE_ADD_TEST(suite, testLinkedListDeleteLast);
    SUITE_ADD_TEST(suite, testLinkedListDeleteLastWtoFr);
    SUITE_ADD_TEST(suite, testLinkedListDeleteAtIndex);
    SUITE_ADD_TEST(suite, testLinkedListDeleteAtIndexWtoFr);
    SUITE_ADD_TEST(suite, testLinkedListContains);
    SUITE_ADD_TEST(suite, testLinkedListGetIndex);
    SUITE_ADD_TEST(suite, testLinkedListGetItem);
    SUITE_ADD_TEST(suite, testLinkedListGetFirst);
    SUITE_ADD_TEST(suite, testLinkedListGetLast);
    SUITE_ADD_TEST(suite, testLinkedListGet);
    SUITE_ADD_TEST(suite, testLinkedListGetLength);
    SUITE_ADD_TEST(suite, testLinkedListToArray);
    SUITE_ADD_TEST(suite, testLinkedListIsEmpty);
    SUITE_ADD_TEST(suite, testPrintLinkedList);
    SUITE_ADD_TEST(suite, testClearLinkedList);
    SUITE_ADD_TEST(suite, testDestroyLinkedList);

    SUITE_ADD_TEST(suite, generalLinkedListTest);

    return suite;

}


void linkedListUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Linked List Test**\n");

    CuSuite *suite = createLinkedListTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}