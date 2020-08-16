#include "DoublyLinkedListDequeTest.h"


#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Deque/Headers/DLinkedListDeque.h"
#include "../../../../../DataStructure/LinkedLists/Headers/DoublyLinkedList.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerDLLDT(int integer) {
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

int compareIntPointersDLLDT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerDLLDT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidDLLDequeInitialization(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(NULL);

    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidDLLDequeInitialization(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    CuAssertPtrNotNull(cuTest, dLDeque);

    destroyDLDeque(dLDeque);

}


void testDLLDequeInsertFront(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequeInsertFront(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(4));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));

    for (int i = 0; i < doublyLinkedListGetLength(dLDeque->linkedList); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) doublyLinkedListGet(dLDeque->linkedList, i));


    destroyDLDeque(dLDeque);

}


void testDLLDequeInsertRear(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequeInsertRear(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertRear(dLDeque, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));

    for (int i = 0; i < doublyLinkedListGetLength(dLDeque->linkedList); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) doublyLinkedListGet(dLDeque->linkedList, i));


    destroyDLDeque(dLDeque);

}


void testDLLDequeGetFront(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequeGetFront(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));

    for (int i = 0; i < doublyLinkedListGetLength(dLDeque->linkedList); i++) {
        int *currentItem = (int *) dLDequeGetFront(dLDeque);
        CuAssertIntEquals(cuTest, i + 1, *currentItem);

        free(currentItem);

    }


    destroyDLDeque(dLDeque);

}


void testDLLDequeGetRear(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequeGetRear(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));

    for (int i = doublyLinkedListGetLength(dLDeque->linkedList) - 1; i >= 0; i--) {
        int *currentItem = (int *) dLDequeGetRear(dLDeque);
        CuAssertIntEquals(cuTest, i + 1, *currentItem);

        free(currentItem);

    }


    destroyDLDeque(dLDeque);

}


void testDLLDequePeekFront(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequePeekFront(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));

    for (int i = 0; i < doublyLinkedListGetLength(dLDeque->linkedList); i++) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) dLDequePeekFront(dLDeque));

        free(dLDequeGetFront(dLDeque));

    }


    destroyDLDeque(dLDeque);

}


void testDLLDequePeekRear(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequePeekRear(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));

    for (int i = doublyLinkedListGetLength(dLDeque->linkedList) - 1; i >= 0; i--) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) dLDequePeekRear(dLDeque));

        free(dLDequeGetRear(dLDeque));

    }


    destroyDLDeque(dLDeque);

}


void testDLLDequeToArray(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequeToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));

    int **arr = (int **) dLDequeToArray(dLDeque);

    for (int i = 0; i < doublyLinkedListGetLength(dLDeque->linkedList); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    destroyDLDeque(dLDeque);

}


void testDLLDequeGetLength(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequeGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, dLDequeGetLength(dLDeque));

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    CuAssertIntEquals(cuTest, 1, dLDequeGetLength(dLDeque));

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    CuAssertIntEquals(cuTest, 2, dLDequeGetLength(dLDeque));

    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    CuAssertIntEquals(cuTest, 3, dLDequeGetLength(dLDeque));

    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));
    CuAssertIntEquals(cuTest, 4, dLDequeGetLength(dLDeque));

    destroyDLDeque(dLDeque);

}


void testDLLDequeIsEmpty(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    dLDequeIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, dLDequeIsEmpty(dLDeque));

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));
    CuAssertIntEquals(cuTest, 0, dLDequeIsEmpty(dLDeque));

    while (!dLDequeIsEmpty(dLDeque))
        free(dLDequeGetRear(dLDeque));


    CuAssertIntEquals(cuTest, 1, dLDequeIsEmpty(dLDeque));

    destroyDLDeque(dLDeque);

}


void testClearDLLDeque(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    clearDLDeque(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, dLDequeIsEmpty(dLDeque));

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));
    CuAssertIntEquals(cuTest, 0, dLDequeIsEmpty(dLDeque));

    clearDLDeque(dLDeque);

    CuAssertIntEquals(cuTest, 1, dLDequeIsEmpty(dLDeque));

    destroyDLDeque(dLDeque);

}


void testDestroyDLLDeque(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(free);

    destroyDLDeque(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(2));
    dLDequeInsertFront(dLDeque, generateIntPointerDLLDT(1));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(3));
    dLDequeInsertRear(dLDeque, generateIntPointerDLLDT(4));


    destroyDLDeque(dLDeque);

}


typedef struct DLLDequeTestStruct {

    int iData;
    char *cData;

} DLLDequeTestStruct;


void freeDLLDequeTestStruct(void *item) {
    DLLDequeTestStruct *d = (DLLDequeTestStruct *) item;
    free(d->cData);
    free(d);
}


int dLLDequeTestStructComp(const void *item1, const void *item2) {
    DLLDequeTestStruct *d1 = (DLLDequeTestStruct *) item1;
    DLLDequeTestStruct *d2 = (DLLDequeTestStruct *) item2;

    int iDataFlag = d1->iData == d2->iData;
    int cDataFlag = strcmp(d1->cData, d2->cData);

    return !iDataFlag || cDataFlag;

}


DLLDequeTestStruct *generateDLLDequeTestStruct(int value, char *str) {

    DLLDequeTestStruct *d = (DLLDequeTestStruct *) malloc(sizeof(DLLDequeTestStruct));
    d->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(d->cData, str);

    d->iData = value;

    return d;

}


void generalDLLDequeTest(CuTest *cuTest) {

    DLDeque *dLDeque = dlDequeInitialization(freeDLLDequeTestStruct);
    char numbersStr[14][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen", "fourteen"};


    CuAssertIntEquals(cuTest, 0, dLDequeGetLength(dLDeque));
    CuAssertIntEquals(cuTest, 1, dLDequeIsEmpty(dLDeque));

    dLDequeInsertFront(dLDeque, generateDLLDequeTestStruct(7, numbersStr[6]));
    dLDequeInsertRear(dLDeque, generateDLLDequeTestStruct(8, numbersStr[7]));
    dLDequeInsertRear(dLDeque, generateDLLDequeTestStruct(9, numbersStr[8]));
    dLDequeInsertRear(dLDeque, generateDLLDequeTestStruct(10, numbersStr[9]));
    dLDequeInsertRear(dLDeque, generateDLLDequeTestStruct(11, numbersStr[10]));
    dLDequeInsertRear(dLDeque, generateDLLDequeTestStruct(12, numbersStr[11]));
    dLDequeInsertRear(dLDeque, generateDLLDequeTestStruct(13, numbersStr[12]));
    dLDequeInsertRear(dLDeque, generateDLLDequeTestStruct(14, numbersStr[13]));
    dLDequeInsertFront(dLDeque, generateDLLDequeTestStruct(6, numbersStr[5]));
    dLDequeInsertFront(dLDeque, generateDLLDequeTestStruct(5, numbersStr[4]));
    dLDequeInsertFront(dLDeque, generateDLLDequeTestStruct(4, numbersStr[3]));
    dLDequeInsertFront(dLDeque, generateDLLDequeTestStruct(3, numbersStr[2]));
    dLDequeInsertFront(dLDeque, generateDLLDequeTestStruct(2, numbersStr[1]));
    dLDequeInsertFront(dLDeque, generateDLLDequeTestStruct(1, numbersStr[0]));

    CuAssertIntEquals(cuTest, 14, dLDequeGetLength(dLDeque));

    DLLDequeTestStruct **queueArr = (DLLDequeTestStruct **) dLDequeToArray(dLDeque);
    for (int i = 0; i < dLDequeGetLength(dLDeque); i++) {
        CuAssertIntEquals(cuTest, i + 1, queueArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i], queueArr[i]->cData);
    }

    CuAssertIntEquals(cuTest, 1, ((DLLDequeTestStruct *) dLDequePeekFront(dLDeque))->iData);
    CuAssertIntEquals(cuTest, 14, ((DLLDequeTestStruct *) dLDequePeekRear(dLDeque))->iData);

    int currentValue = 0;
    while (!dLDequeIsEmpty(dLDeque)) {
        currentValue += 1;
        DLLDequeTestStruct *frontItem = dLDequeGetFront(dLDeque);
        DLLDequeTestStruct *rearItem = dLDequeGetRear(dLDeque);

        CuAssertIntEquals(cuTest, currentValue, frontItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[currentValue - 1], frontItem->cData);

        CuAssertIntEquals(cuTest, 15 - currentValue, rearItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[15 - currentValue - 1], rearItem->cData);

        freeDLLDequeTestStruct(frontItem);
        freeDLLDequeTestStruct(rearItem);

    }


    free(queueArr);
    destroyDLDeque(dLDeque);

}


CuSuite *createDoublyLinkedListDequeTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidDLLDequeInitialization);
    SUITE_ADD_TEST(suite, testValidDLLDequeInitialization);
    SUITE_ADD_TEST(suite, testDLLDequeInsertFront);
    SUITE_ADD_TEST(suite, testDLLDequeInsertRear);
    SUITE_ADD_TEST(suite, testDLLDequeGetFront);
    SUITE_ADD_TEST(suite, testDLLDequeGetRear);
    SUITE_ADD_TEST(suite, testDLLDequePeekFront);
    SUITE_ADD_TEST(suite, testDLLDequePeekRear);
    SUITE_ADD_TEST(suite, testDLLDequeToArray);
    SUITE_ADD_TEST(suite, testDLLDequeGetLength);
    SUITE_ADD_TEST(suite, testDLLDequeIsEmpty);
    SUITE_ADD_TEST(suite, testClearDLLDeque);
    SUITE_ADD_TEST(suite, testDestroyDLLDeque);

    SUITE_ADD_TEST(suite, generalDLLDequeTest);

    return suite;

}


void doublyLinkedListDequeUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Doubly Linked List dLDeque Test**\n");

    CuSuite *suite = createDoublyLinkedListDequeTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}