#include "LinkedListQueueTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Queues/Headers/LinkedListQueue.h"

/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerLLQT(int integer) {
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

int compareIntPointersLLQT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerLLQT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidLinkedListQueueInitialization(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(NULL);

    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidLinkedListQueueInitialization(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);
    CuAssertPtrNotNull(cuTest, llQueue);

    destroyLLQueue(llQueue);

}


void testLinkedListQueueEnqueue(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    lLQueueEnqueue(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLQueueEnqueue(llQueue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(2));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(3));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(4));

    for (int i = lLQueueGetLength(llQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        int *currentItem = (int *) lLQueueDequeue(llQueue);
        CuAssertIntEquals(cuTest, currentValue, *(int *) currentItem);
        free(currentItem);
    }

    destroyLLQueue(llQueue);

}


void testLinkedListQueueEnqueueAll(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    lLQueueEnqueueAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLQueueEnqueueAll(llQueue, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
        arr[i] = generateIntPointerLLQT(i + 1);

    lLQueueEnqueueAll(llQueue, (void **) arr, 5);

    for (int i = lLQueueGetLength(llQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        int *currentItem = (int *) lLQueueDequeue(llQueue);
        CuAssertIntEquals(cuTest, currentValue, *(int *) currentItem);
        free(currentItem);
    }


    free(arr);
    destroyLLQueue(llQueue);

}


void testLinkedListQueueDequeue(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    lLQueueDequeue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLQueueDequeue(llQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(2));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(3));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(4));

    for (int i = lLQueueGetLength(llQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        int *currentItem = (int *) lLQueueDequeue(llQueue);
        CuAssertIntEquals(cuTest, currentValue, *(int *) currentItem);
        free(currentItem);
    }

    destroyLLQueue(llQueue);

}


void testLinkedListQueuePeek(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    lLQueuePeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLQueuePeek(llQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(2));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(3));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(4));

    for (int i = lLQueueGetLength(llQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        CuAssertIntEquals(cuTest, currentValue, *(int *) lLQueuePeek(llQueue));

        free(lLQueueDequeue(llQueue));
    }


    destroyLLQueue(llQueue);

}


void testLinkedListQueueGetLength(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    lLQueueGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, lLQueueGetLength(llQueue));

    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    CuAssertIntEquals(cuTest, 1, lLQueueGetLength(llQueue));

    lLQueueEnqueue(llQueue, generateIntPointerLLQT(2));
    CuAssertIntEquals(cuTest, 2, lLQueueGetLength(llQueue));

    lLQueueEnqueue(llQueue, generateIntPointerLLQT(3));
    CuAssertIntEquals(cuTest, 3, lLQueueGetLength(llQueue));

    lLQueueEnqueue(llQueue, generateIntPointerLLQT(4));
    CuAssertIntEquals(cuTest, 4, lLQueueGetLength(llQueue));


    free(lLQueueDequeue(llQueue));
    CuAssertIntEquals(cuTest, 3, lLQueueGetLength(llQueue));

    free(lLQueueDequeue(llQueue));
    CuAssertIntEquals(cuTest, 2, lLQueueGetLength(llQueue));

    destroyLLQueue(llQueue);

}


void testLinkedListQueueIsEmpty(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    lLQueueIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, lLQueueIsEmpty(llQueue));

    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    CuAssertIntEquals(cuTest, 0, lLQueueIsEmpty(llQueue));


    free(lLQueueDequeue(llQueue));
    CuAssertIntEquals(cuTest, 1, lLQueueIsEmpty(llQueue));

    destroyLLQueue(llQueue);

}


void testLinkedListQueueToArray(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    lLQueueToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(2));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(3));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(4));

    int **arr = (int **) lLQueueToArray(llQueue);

    for (int i = 0; i < lLQueueGetLength(llQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    destroyLLQueue(llQueue);

}


void testClearLinkedListQueue(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    clearLLQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, lLQueueGetLength(llQueue));

    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(2));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(3));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(4));

    CuAssertIntEquals(cuTest, 4, lLQueueGetLength(llQueue));

    clearLLQueue(llQueue);

    CuAssertIntEquals(cuTest, 0, lLQueueGetLength(llQueue));

    destroyLLQueue(llQueue);

}


void testDestroyLinkedListQueue(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(free);

    destroyLLQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLQueueEnqueue(llQueue, generateIntPointerLLQT(1));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(2));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(3));
    lLQueueEnqueue(llQueue, generateIntPointerLLQT(4));

    destroyLLQueue(llQueue);

}


typedef struct LLQueueTestStruct {

    int iData;
    char *cData;

} LLQueueTestStruct;


void freeLinkedListQueueTestStruct(void *item) {
    LLQueueTestStruct *q = (LLQueueTestStruct *) item;
    free(q->cData);
    free(q);
}


int lLQueueTestStructComp(const void *item1, const void *item2) {
    LLQueueTestStruct *q1 = (LLQueueTestStruct *) item1;
    LLQueueTestStruct *q2 = (LLQueueTestStruct *) item2;

    int iDataFlag = q1->iData == q2->iData;
    int cDataFlag = strcmp(q1->cData, q2->cData);

    return !iDataFlag || cDataFlag;

}


LLQueueTestStruct *generateLinkedListQueueTestStruct(int value, char *str) {

    LLQueueTestStruct *q = (LLQueueTestStruct *) malloc(sizeof(LLQueueTestStruct));
    q->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(q->cData, str);

    q->iData = value;

    return q;

}


void generalLinkedListQueueTest(CuTest *cuTest) {

    LinkedListQueue *llQueue = linkedListQueueInitialization(freeLinkedListQueueTestStruct);
    char numbersStr[14][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen", "fourteen"};


    CuAssertIntEquals(cuTest, 0, lLQueueGetLength(llQueue));
    CuAssertIntEquals(cuTest, 1, lLQueueIsEmpty(llQueue));

    lLQueueEnqueue(llQueue, generateLinkedListQueueTestStruct(1, "one"));
    lLQueueEnqueue(llQueue, generateLinkedListQueueTestStruct(2, "two"));
    lLQueueEnqueue(llQueue, generateLinkedListQueueTestStruct(3, "three"));

    CuAssertIntEquals(cuTest, 3, lLQueueGetLength(llQueue));
    CuAssertIntEquals(cuTest, 0, lLQueueIsEmpty(llQueue));

    CuAssertIntEquals(cuTest, 1, ((LLQueueTestStruct *) lLQueuePeek(llQueue))->iData);
    CuAssertStrEquals(cuTest, "one", ((LLQueueTestStruct *) lLQueuePeek(llQueue))->cData);

    free(lLQueueDequeue(llQueue));

    LLQueueTestStruct **structArr = (LLQueueTestStruct **) malloc(sizeof(LLQueueTestStruct *) * 11);
    for (int i = 0; i < 11; i++)
        structArr[i] = generateLinkedListQueueTestStruct(i + 4, numbersStr[i + 3]);

    lLQueueEnqueueAll(llQueue, (void **) structArr, 11);

    CuAssertIntEquals(cuTest, 13, lLQueueGetLength(llQueue));

    LLQueueTestStruct **llQueueArr = (LLQueueTestStruct **) lLQueueToArray(llQueue);

    for (int i = 0; i < lLQueueGetLength(llQueue); i++) {
        CuAssertIntEquals(cuTest, i + 2, llQueueArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i + 1], llQueueArr[i]->cData);
    }

    int currentValue = 1;
    while (!lLQueueIsEmpty(llQueue)) {
        currentValue += 1;
        LLQueueTestStruct *currentItem = lLQueueDequeue(llQueue);
        CuAssertIntEquals(cuTest, currentValue, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[currentValue - 1], currentItem->cData);

        freeLinkedListQueueTestStruct(currentItem);

    }


    free(structArr);
    free(llQueueArr);
    destroyLLQueue(llQueue);

}


CuSuite *createLinkedListQueueTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidLinkedListQueueInitialization);
    SUITE_ADD_TEST(suite, testValidLinkedListQueueInitialization);
    SUITE_ADD_TEST(suite, testLinkedListQueueEnqueue);
    SUITE_ADD_TEST(suite, testLinkedListQueueEnqueueAll);
    SUITE_ADD_TEST(suite, testLinkedListQueueDequeue);
    SUITE_ADD_TEST(suite, testLinkedListQueuePeek);
    SUITE_ADD_TEST(suite, testLinkedListQueueGetLength);
    SUITE_ADD_TEST(suite, testLinkedListQueueIsEmpty);
    SUITE_ADD_TEST(suite, testLinkedListQueueToArray);
    SUITE_ADD_TEST(suite, testClearLinkedListQueue);
    SUITE_ADD_TEST(suite, testDestroyLinkedListQueue);

    SUITE_ADD_TEST(suite, generalLinkedListQueueTest);

    return suite;

}


void linkedListQueueUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Linked List Queue Test**\n");

    CuSuite *suite = createLinkedListQueueTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}
