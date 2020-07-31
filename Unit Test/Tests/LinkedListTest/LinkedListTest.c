#include "LinkedListTest.h"
#include "../../CuTest/CuTest.h"
#include "../../../System/Utils.h"
#include "../../../DataStructure/LinkedLists/Headers/LinkedList.h"


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
    return *(int *)a - *(int *)b;
}





/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerLLT(char *ch) {

    char *newCh = (char *) malloc( sizeof(char) * (strlen(ch) + 1) );

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
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

}


void testValidLinkedListInitialization(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    CuAssertPtrNotNull(cuTest, list);

    destroyLinkedList(list);

}


void testLinkedListAddFirst(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddFirst(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddFirst(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddFirst(list, generateIntPointerLLT(10));
    linkedListAddFirst(list, generateIntPointerLLT(20));
    linkedListAddFirst(list, generateIntPointerLLT(30));

    for (int i = list->length - 1; i >= 0; i--)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *)linkedListGet(list, list->length - 1 - i));

    destroyLinkedList(list);

}



void testLinkedListAddLast(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddLast(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddLast(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddLast(list, generateIntPointerLLT(10));
    linkedListAddLast(list, generateIntPointerLLT(20));
    linkedListAddLast(list, generateIntPointerLLT(30));

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}




void testLinkedListAddAtIndex(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddAtIndex(NULL, 0, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddAtIndex(list, 0, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int tempValue = 10;
    linkedListAddAtIndex(list, 0, &tempValue);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddLast(list, generateIntPointerLLT(10));
    linkedListAddLast(list, generateIntPointerLLT(30));
    linkedListAddLast(list, generateIntPointerLLT(50));

    linkedListAddAtIndex(list, 1, generateIntPointerLLT(20));
    linkedListAddAtIndex(list, 3, generateIntPointerLLT(40));

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}




void testLinkedListAddAll(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddAll(list, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = i + 1;
    }

    linkedListAddAll(list, (void **) arr, 10);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *)linkedListGet(list, i));

    free(arr);
    destroyLinkedList(list);

}




void testLinkedListDeleteFirst(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteFirst(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListDeleteFirst(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddFrom1To10Values(list);

    linkedListDeleteFirst(list);
    linkedListDeleteFirst(list);
    linkedListDeleteFirst(list);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}



void testLinkedListDeleteFirstWtoFr(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteFirstWtoFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListDeleteFirstWtoFr(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);

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
        CuAssertIntEquals(cuTest, (i + 4), *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}




void testLinkedListDeleteLast(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteLast(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListDeleteLast(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddFrom1To10Values(list);

    linkedListDeleteLast(list);
    linkedListDeleteLast(list);
    linkedListDeleteLast(list);

    CuAssertIntEquals(cuTest, 7, list->length);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 1), *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}




void testLinkedListDeleteLastWtoFr(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteLastWtoFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListDeleteLastWtoFr(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);

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
        CuAssertIntEquals(cuTest, (i + 1), *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}




void testLinkedListDeleteAtIndex(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteAtIndex(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListDeleteAtIndex(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);


    linkedListAddFrom1To10Values(list);

    linkedListDeleteAtIndex(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListDeleteAtIndex(list, 2);
    linkedListDeleteAtIndex(list, 1);
    linkedListDeleteAtIndex(list, 0);

    CuAssertIntEquals(cuTest, 7, list->length);

    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}




void testLinkedListDeleteAtIndexWtoFr(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListDeleteAtIndexWtoFr(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListDeleteAtIndexWtoFr(list, 0);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddFrom1To10Values(list);

    linkedListDeleteAtIndexWtoFr(list, 11);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);


    int *currentItem;
    currentItem = (int *) linkedListDeleteAtIndexWtoFr(list, 2);
    CuAssertIntEquals(cuTest, 3, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteAtIndexWtoFr(list,1);
    CuAssertIntEquals(cuTest, 2, *currentItem);
    free(currentItem);

    currentItem = (int *) linkedListDeleteAtIndexWtoFr(list, 0);
    CuAssertIntEquals(cuTest, 1, *currentItem);
    free(currentItem);

    CuAssertIntEquals(cuTest, 7, list->length);


    for (int i = 0; i < list->length; i++)
        CuAssertIntEquals(cuTest, (i + 4), *(int *)linkedListGet(list, i));

    destroyLinkedList(list);

}





void testLinkedListContains(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListContains(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


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
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListGetIndex(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


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
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListGetItem(list, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


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
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListGetFirst(list);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddFrom1To10Values(list);


    CuAssertIntEquals(cuTest, 1, *(int *) linkedListGetFirst(list));

    destroyLinkedList(list);

}




void testLinkedListGetLast(CuTest *cuTest) {
    LinkedList *list = linkedListInitialization(free, compareIntPointersLLT);

    linkedListGetLast(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListGetLast(list);
    CuAssertPtrEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    linkedListAddFrom1To10Values(list);


    CuAssertIntEquals(cuTest, 10, *(int *) linkedListGetLast(list));

    destroyLinkedList(list);

}






CuSuite *createLinkedListTestsSuite() {

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

    return suite;

}



void linkedListUnitTest() {

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Linked List Test**\n");

    CuSuite *suite = createLinkedListTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}