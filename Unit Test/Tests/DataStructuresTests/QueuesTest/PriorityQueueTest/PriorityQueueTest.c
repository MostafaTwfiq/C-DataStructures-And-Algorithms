#include "PriorityQueueTest.h"


#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Queues/Headers/PriorityQueue.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerPQT(int integer) {
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

int compareIntPointersPQT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerPQT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidPriorityQueueInitialization(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(NULL, compareIntPointersPQT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidPriorityQueueInitialization(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);
    CuAssertPtrNotNull(cuTest, pQueue);

    destroyPQueue(pQueue);

}


void testPriorityQueueEnqueue(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    pQueueEnqueue(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pQueueEnqueue(pQueue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    pQueueEnqueue(pQueue, generateIntPointerPQT(3));
    pQueueEnqueue(pQueue, generateIntPointerPQT(2));
    pQueueEnqueue(pQueue, generateIntPointerPQT(4));
    pQueueEnqueue(pQueue, generateIntPointerPQT(1));


    for (int i = 0; i < pQueueGetLength(pQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) pQueue->arr[i]);

    destroyPQueue(pQueue);

}


void testPriorityQueueEnqueueAll(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    pQueueEnqueueAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pQueueEnqueueAll(pQueue, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int **arr = (int **) malloc(sizeof(int *) * 5);
    arr[0] = generateIntPointerPQT(3);
    arr[1] = generateIntPointerPQT(2);
    arr[2] = generateIntPointerPQT(1);
    arr[3] = generateIntPointerPQT(5);
    arr[4] = generateIntPointerPQT(4);

    pQueueEnqueueAll(pQueue, (void **) arr, 5);

    for (int i = 0; i < pQueueGetLength(pQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) pQueue->arr[i]);


    free(arr);
    destroyPQueue(pQueue);

}


void testPriorityQueueDepQueue(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    pQueueDequeue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pQueueDequeue(pQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    pQueueEnqueue(pQueue, generateIntPointerPQT(2));
    pQueueEnqueue(pQueue, generateIntPointerPQT(1));
    pQueueEnqueue(pQueue, generateIntPointerPQT(3));
    pQueueEnqueue(pQueue, generateIntPointerPQT(4));

    int size = pQueueGetLength(pQueue);
    for (int i = 0; i < size; i++) {

        int *currentItem = (int *) pQueueDequeue(pQueue);
        CuAssertIntEquals(cuTest, i + 1, *(int *) currentItem);

        free(currentItem);
    }

    destroyPQueue(pQueue);

}


void testPriorityQueuePeek(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    pQueuePeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pQueuePeek(pQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    pQueueEnqueue(pQueue, generateIntPointerPQT(1));
    pQueueEnqueue(pQueue, generateIntPointerPQT(3));
    pQueueEnqueue(pQueue, generateIntPointerPQT(4));
    pQueueEnqueue(pQueue, generateIntPointerPQT(2));

    int size = pQueueGetLength(pQueue);
    for (int i = 0; i < size; i++) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) pQueuePeek(pQueue));

        free(pQueueDequeue(pQueue));
    }


    destroyPQueue(pQueue);

}


void testPriorityQueueGetLength(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    pQueueGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, pQueueGetLength(pQueue));

    pQueueEnqueue(pQueue, generateIntPointerPQT(1));
    CuAssertIntEquals(cuTest, 1, pQueueGetLength(pQueue));

    pQueueEnqueue(pQueue, generateIntPointerPQT(2));
    CuAssertIntEquals(cuTest, 2, pQueueGetLength(pQueue));

    pQueueEnqueue(pQueue, generateIntPointerPQT(3));
    CuAssertIntEquals(cuTest, 3, pQueueGetLength(pQueue));

    pQueueEnqueue(pQueue, generateIntPointerPQT(4));
    CuAssertIntEquals(cuTest, 4, pQueueGetLength(pQueue));


    free(pQueueDequeue(pQueue));
    CuAssertIntEquals(cuTest, 3, pQueueGetLength(pQueue));

    free(pQueueDequeue(pQueue));
    CuAssertIntEquals(cuTest, 2, pQueueGetLength(pQueue));

    destroyPQueue(pQueue);

}


void testPriorityQueueIsEmpty(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    pQueueIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, pQueueIsEmpty(pQueue));

    pQueueEnqueue(pQueue, generateIntPointerPQT(1));
    CuAssertIntEquals(cuTest, 0, pQueueIsEmpty(pQueue));


    free(pQueueDequeue(pQueue));
    CuAssertIntEquals(cuTest, 1, pQueueIsEmpty(pQueue));

    destroyPQueue(pQueue);

}


void testPriorityQueueToArray(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    pQueueToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    pQueueEnqueue(pQueue, generateIntPointerPQT(1));
    pQueueEnqueue(pQueue, generateIntPointerPQT(3));
    pQueueEnqueue(pQueue, generateIntPointerPQT(4));
    pQueueEnqueue(pQueue, generateIntPointerPQT(2));

    int **arr = (int **) pQueueToArray(pQueue);

    for (int i = 0; i < pQueueGetLength(pQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    destroyPQueue(pQueue);

}


void testClearPriorityQueue(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    clearPQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, pQueueGetLength(pQueue));

    pQueueEnqueue(pQueue, generateIntPointerPQT(1));
    pQueueEnqueue(pQueue, generateIntPointerPQT(2));
    pQueueEnqueue(pQueue, generateIntPointerPQT(3));
    pQueueEnqueue(pQueue, generateIntPointerPQT(4));

    CuAssertIntEquals(cuTest, 4, pQueueGetLength(pQueue));

    clearPQueue(pQueue);

    CuAssertIntEquals(cuTest, 0, pQueueGetLength(pQueue));

    destroyPQueue(pQueue);

}


void testDestroyPriorityQueue(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(free, compareIntPointersPQT);

    destroyPQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pQueueEnqueue(pQueue, generateIntPointerPQT(1));
    pQueueEnqueue(pQueue, generateIntPointerPQT(2));
    pQueueEnqueue(pQueue, generateIntPointerPQT(3));
    pQueueEnqueue(pQueue, generateIntPointerPQT(4));

    destroyPQueue(pQueue);

}


typedef struct PQueueTestStruct {

    int iData;
    char *cData;

} PQueueTestStruct;


void freePriorityQueueTestStruct(void *item) {
    PQueueTestStruct *q = (PQueueTestStruct *) item;
    free(q->cData);
    free(q);
}


int pQueueTestStructComp(const void *item1, const void *item2) {
    PQueueTestStruct *q1 = (PQueueTestStruct *) item1;
    PQueueTestStruct *q2 = (PQueueTestStruct *) item2;

    return q1->iData - q2->iData;

}


PQueueTestStruct *generatePriorityQueueTestStruct(int value, char *str) {

    PQueueTestStruct *q = (PQueueTestStruct *) malloc(sizeof(PQueueTestStruct));
    q->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(q->cData, str);

    q->iData = value;

    return q;

}


void generalPriorityQueueTest(CuTest *cuTest) {

    PriorityQueue *pQueue = priorityQueueInitialization(freePriorityQueueTestStruct, pQueueTestStructComp);
    char numbersStr[14][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen", "fourteen"};


    CuAssertIntEquals(cuTest, 0, pQueueGetLength(pQueue));
    CuAssertIntEquals(cuTest, 1, pQueueIsEmpty(pQueue));

    pQueueEnqueue(pQueue, generatePriorityQueueTestStruct(3, "three"));
    pQueueEnqueue(pQueue, generatePriorityQueueTestStruct(1, "one"));
    pQueueEnqueue(pQueue, generatePriorityQueueTestStruct(2, "two"));

    CuAssertIntEquals(cuTest, 3, pQueueGetLength(pQueue));
    CuAssertIntEquals(cuTest, 0, pQueueIsEmpty(pQueue));

    CuAssertIntEquals(cuTest, 1, ((PQueueTestStruct *) pQueuePeek(pQueue))->iData);
    CuAssertStrEquals(cuTest, "one", ((PQueueTestStruct *) pQueuePeek(pQueue))->cData);

    free(pQueueDequeue(pQueue));

    PQueueTestStruct **structArr = (PQueueTestStruct **) malloc(sizeof(PQueueTestStruct *) * 11);
    for (int i = 0; i < 11; i++)
        structArr[i] = generatePriorityQueueTestStruct(i + 4, numbersStr[i + 3]);

    pQueueEnqueueAll(pQueue, (void **) structArr, 11);

    CuAssertIntEquals(cuTest, 13, pQueueGetLength(pQueue));

    PQueueTestStruct **pQueueArr = (PQueueTestStruct **) pQueueToArray(pQueue);
    for (int i = 0; i < pQueueGetLength(pQueue); i++) {
        CuAssertIntEquals(cuTest, i + 2, pQueueArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i + 1], pQueueArr[i]->cData);
    }

    int currentValue = 1;
    while (!pQueueIsEmpty(pQueue)) {
        currentValue += 1;
        PQueueTestStruct *currentItem = pQueueDequeue(pQueue);
        CuAssertIntEquals(cuTest, currentValue, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[currentValue - 1], currentItem->cData);

        freePriorityQueueTestStruct(currentItem);

    }


    free(structArr);
    free(pQueueArr);
    destroyPQueue(pQueue);

}


CuSuite *createPriorityQueueTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidPriorityQueueInitialization);
    SUITE_ADD_TEST(suite, testValidPriorityQueueInitialization);
    SUITE_ADD_TEST(suite, testPriorityQueueEnqueue);
    SUITE_ADD_TEST(suite, testPriorityQueueEnqueueAll);
    SUITE_ADD_TEST(suite, testPriorityQueueDepQueue);
    SUITE_ADD_TEST(suite, testPriorityQueuePeek);
    SUITE_ADD_TEST(suite, testPriorityQueueGetLength);
    SUITE_ADD_TEST(suite, testPriorityQueueIsEmpty);
    SUITE_ADD_TEST(suite, testPriorityQueueToArray);
    SUITE_ADD_TEST(suite, testClearPriorityQueue);
    SUITE_ADD_TEST(suite, testDestroyPriorityQueue);

    SUITE_ADD_TEST(suite, generalPriorityQueueTest);

    return suite;

}


void priorityQueueUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Priority Queue Test**\n");

    CuSuite *suite = createPriorityQueueTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}
