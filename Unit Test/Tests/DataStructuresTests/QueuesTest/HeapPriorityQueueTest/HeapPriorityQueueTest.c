#include "HeapPriorityQueueTest.h"


#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Queues/Headers/HPriorityQueue.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerHPQT(int integer) {
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

int compareIntPointersHPQT(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerHPQT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidHPriorityQueueInitialization(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(NULL, compareIntPointersHPQT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidHPriorityQueueInitialization(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);
    CuAssertPtrNotNull(cuTest, pQueue);

    destroyHPQueue(pQueue);

}


void testHPriorityQueueEnqueue(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    hpQueueEnqueue(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hpQueueEnqueue(pQueue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(3));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(2));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(4));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));

    int **arr = (int **) hpQueueToArray(pQueue);

    for (int i = 0; i < hpQueueGetLength(pQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);

    free(arr);
    destroyHPQueue(pQueue);

}


void testHPriorityQueueEnqueueAll(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    hpQueueEnqueueAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hpQueueEnqueueAll(pQueue, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int **arr = (int **) malloc(sizeof(int *) * 5);
    arr[0] = generateIntPointerHPQT(3);
    arr[1] = generateIntPointerHPQT(2);
    arr[2] = generateIntPointerHPQT(1);
    arr[3] = generateIntPointerHPQT(5);
    arr[4] = generateIntPointerHPQT(4);

    hpQueueEnqueueAll(pQueue, (void **) arr, 5);


    int **queueArr = (int **) hpQueueToArray(pQueue);

    for (int i = 0; i < hpQueueGetLength(pQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *queueArr[i]);


    free(arr);
    free(queueArr);
    destroyHPQueue(pQueue);

}


void testHPriorityQueueDepQueue(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    hpQueueDequeue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hpQueueDequeue(pQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    hpQueueEnqueue(pQueue, generateIntPointerHPQT(2));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(3));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(4));

    int size = hpQueueGetLength(pQueue);
    for (int i = 0; i < size; i++) {

        int *currentItem = (int *) hpQueueDequeue(pQueue);
        CuAssertIntEquals(cuTest, i + 1, *(int *) currentItem);

        free(currentItem);
    }

    destroyHPQueue(pQueue);

}


void testHPriorityQueuePeek(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    hpQueuePeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hpQueuePeek(pQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(3));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(4));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(2));

    int size = hpQueueGetLength(pQueue);
    for (int i = 0; i < size; i++) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) hpQueuePeek(pQueue));

        free(hpQueueDequeue(pQueue));
    }


    destroyHPQueue(pQueue);

}


void testHPriorityQueueGetLength(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    hpQueueGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, hpQueueGetLength(pQueue));

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));
    CuAssertIntEquals(cuTest, 1, hpQueueGetLength(pQueue));

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(2));
    CuAssertIntEquals(cuTest, 2, hpQueueGetLength(pQueue));

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(3));
    CuAssertIntEquals(cuTest, 3, hpQueueGetLength(pQueue));

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(4));
    CuAssertIntEquals(cuTest, 4, hpQueueGetLength(pQueue));


    free(hpQueueDequeue(pQueue));
    CuAssertIntEquals(cuTest, 3, hpQueueGetLength(pQueue));

    free(hpQueueDequeue(pQueue));
    CuAssertIntEquals(cuTest, 2, hpQueueGetLength(pQueue));

    destroyHPQueue(pQueue);

}


void testHPriorityQueueIsEmpty(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    hpQueueIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, hpQueueIsEmpty(pQueue));

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));
    CuAssertIntEquals(cuTest, 0, hpQueueIsEmpty(pQueue));


    free(hpQueueDequeue(pQueue));
    CuAssertIntEquals(cuTest, 1, hpQueueIsEmpty(pQueue));

    destroyHPQueue(pQueue);

}


void testHPriorityQueueToArray(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    hpQueueToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(3));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(4));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(2));

    int **arr = (int **) hpQueueToArray(pQueue);

    for (int i = 0; i < hpQueueGetLength(pQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    destroyHPQueue(pQueue);

}


void testClearHPriorityQueue(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    clearHPQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, hpQueueGetLength(pQueue));

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(2));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(3));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(4));

    CuAssertIntEquals(cuTest, 4, hpQueueGetLength(pQueue));

    clearHPQueue(pQueue);

    CuAssertIntEquals(cuTest, 0, hpQueueGetLength(pQueue));

    destroyHPQueue(pQueue);

}


void testDestroyHPriorityQueue(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(free, compareIntPointersHPQT);

    destroyHPQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hpQueueEnqueue(pQueue, generateIntPointerHPQT(1));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(2));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(3));
    hpQueueEnqueue(pQueue, generateIntPointerHPQT(4));

    destroyHPQueue(pQueue);

}


typedef struct PQueueTestStruct {

    int iData;
    char *cData;

} PQueueTestStruct;


void freeHPriorityQueueTestStruct(void *item) {
    PQueueTestStruct *q = (PQueueTestStruct *) item;
    free(q->cData);
    free(q);
}


int hpQueueTestStructComp(const void *item1, const void *item2) {
    PQueueTestStruct *q1 = (PQueueTestStruct *) item1;
    PQueueTestStruct *q2 = (PQueueTestStruct *) item2;

    return q2->iData - q1->iData;

}


PQueueTestStruct *generateHPriorityQueueTestStruct(int value, char *str) {

    PQueueTestStruct *q = (PQueueTestStruct *) malloc(sizeof(PQueueTestStruct));
    q->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(q->cData, str);

    q->iData = value;

    return q;

}


void generalHPriorityQueueTest(CuTest *cuTest) {

    HPriorityQueue *pQueue = hPriorityQueueInitialization(freeHPriorityQueueTestStruct, hpQueueTestStructComp);
    char numbersStr[14][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen", "fourteen"};


    CuAssertIntEquals(cuTest, 0, hpQueueGetLength(pQueue));
    CuAssertIntEquals(cuTest, 1, hpQueueIsEmpty(pQueue));

    hpQueueEnqueue(pQueue, generateHPriorityQueueTestStruct(3, "three"));
    hpQueueEnqueue(pQueue, generateHPriorityQueueTestStruct(1, "one"));
    hpQueueEnqueue(pQueue, generateHPriorityQueueTestStruct(2, "two"));

    CuAssertIntEquals(cuTest, 3, hpQueueGetLength(pQueue));
    CuAssertIntEquals(cuTest, 0, hpQueueIsEmpty(pQueue));

    CuAssertIntEquals(cuTest, 1, ((PQueueTestStruct *) hpQueuePeek(pQueue))->iData);
    CuAssertStrEquals(cuTest, "one", ((PQueueTestStruct *) hpQueuePeek(pQueue))->cData);

    free(hpQueueDequeue(pQueue));

    PQueueTestStruct **structArr = (PQueueTestStruct **) malloc(sizeof(PQueueTestStruct *) * 11);
    for (int i = 0; i < 11; i++)
        structArr[i] = generateHPriorityQueueTestStruct(i + 4, numbersStr[i + 3]);

    hpQueueEnqueueAll(pQueue, (void **) structArr, 11);

    CuAssertIntEquals(cuTest, 13, hpQueueGetLength(pQueue));

    PQueueTestStruct **pQueueArr = (PQueueTestStruct **) hpQueueToArray(pQueue);
    for (int i = 0; i < hpQueueGetLength(pQueue); i++) {
        CuAssertIntEquals(cuTest, i + 2, pQueueArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i + 1], pQueueArr[i]->cData);
    }

    int currentValue = 1;
    while (!hpQueueIsEmpty(pQueue)) {
        currentValue += 1;
        PQueueTestStruct *currentItem = hpQueueDequeue(pQueue);
        CuAssertIntEquals(cuTest, currentValue, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[currentValue - 1], currentItem->cData);

        freeHPriorityQueueTestStruct(currentItem);

    }


    free(structArr);
    free(pQueueArr);
    destroyHPQueue(pQueue);

}


CuSuite *createHeapHPriorityQueueTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidHPriorityQueueInitialization);
    SUITE_ADD_TEST(suite, testValidHPriorityQueueInitialization);
    SUITE_ADD_TEST(suite, testHPriorityQueueEnqueue);
    SUITE_ADD_TEST(suite, testHPriorityQueueEnqueueAll);
    SUITE_ADD_TEST(suite, testHPriorityQueueDepQueue);
    SUITE_ADD_TEST(suite, testHPriorityQueuePeek);
    SUITE_ADD_TEST(suite, testHPriorityQueueGetLength);
    SUITE_ADD_TEST(suite, testHPriorityQueueIsEmpty);
    SUITE_ADD_TEST(suite, testHPriorityQueueToArray);
    SUITE_ADD_TEST(suite, testClearHPriorityQueue);
    SUITE_ADD_TEST(suite, testDestroyHPriorityQueue);

    SUITE_ADD_TEST(suite, generalHPriorityQueueTest);

    return suite;

}


void heapPriorityQueueUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Heap Priority Queue Test**\n");

    CuSuite *suite = createHeapHPriorityQueueTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}
