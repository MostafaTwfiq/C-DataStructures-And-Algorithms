#include "StackQueueTest.h"


#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Queues/Headers/StackQueue.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerSQT(int integer) {
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

int compareIntPointersSQT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerSQT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidStackQueueInitialization(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(NULL);

    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidStackQueueInitialization(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);
    CuAssertPtrNotNull(cuTest, sQueue);

    destroySQueue(sQueue);

}


void testStackQueueEnqueue(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    sQueueEnqueue(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    sQueueEnqueue(sQueue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    sQueueEnqueue(sQueue, generateIntPointerSQT(2));
    sQueueEnqueue(sQueue, generateIntPointerSQT(3));
    sQueueEnqueue(sQueue, generateIntPointerSQT(4));

    for (int i = sQueueGetLength(sQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        int *currentItem = (int *) sQueueDequeue(sQueue);
        CuAssertIntEquals(cuTest, currentValue, *(int *) currentItem);
        free(currentItem);
    }

    destroySQueue(sQueue);

}


void testStackQueueEnqueueAll(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    sQueueAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    sQueueAddAll(sQueue, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
        arr[i] = generateIntPointerSQT(i + 1);

    sQueueAddAll(sQueue, (void **) arr, 5);

    for (int i = sQueueGetLength(sQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        int *currentItem = (int *) sQueueDequeue(sQueue);
        CuAssertIntEquals(cuTest, currentValue, *(int *) currentItem);
        free(currentItem);
    }


    free(arr);
    destroySQueue(sQueue);

}


void testStackQueueDequeue(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    sQueueDequeue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    sQueueDequeue(sQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    sQueueEnqueue(sQueue, generateIntPointerSQT(2));
    sQueueEnqueue(sQueue, generateIntPointerSQT(3));
    sQueueEnqueue(sQueue, generateIntPointerSQT(4));

    for (int i = sQueueGetLength(sQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        int *currentItem = (int *) sQueueDequeue(sQueue);
        CuAssertIntEquals(cuTest, currentValue, *(int *) currentItem);
        free(currentItem);
    }

    destroySQueue(sQueue);

}


void testStackQueuePeek(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    sQueuePeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    sQueuePeek(sQueue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    sQueueEnqueue(sQueue, generateIntPointerSQT(2));
    sQueueEnqueue(sQueue, generateIntPointerSQT(3));
    sQueueEnqueue(sQueue, generateIntPointerSQT(4));

    for (int i = sQueueGetLength(sQueue) - 1, currentValue = 1; i >= 0; i--, currentValue++) {
        CuAssertIntEquals(cuTest, currentValue, *(int *) sQueuePeek(sQueue));

        free(sQueueDequeue(sQueue));
    }


    destroySQueue(sQueue);

}


void testStackQueueGetLength(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    sQueueGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, sQueueGetLength(sQueue));

    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    CuAssertIntEquals(cuTest, 1, sQueueGetLength(sQueue));

    sQueueEnqueue(sQueue, generateIntPointerSQT(2));
    CuAssertIntEquals(cuTest, 2, sQueueGetLength(sQueue));

    sQueueEnqueue(sQueue, generateIntPointerSQT(3));
    CuAssertIntEquals(cuTest, 3, sQueueGetLength(sQueue));

    sQueueEnqueue(sQueue, generateIntPointerSQT(4));
    CuAssertIntEquals(cuTest, 4, sQueueGetLength(sQueue));


    free(sQueueDequeue(sQueue));
    CuAssertIntEquals(cuTest, 3, sQueueGetLength(sQueue));

    free(sQueueDequeue(sQueue));
    CuAssertIntEquals(cuTest, 2, sQueueGetLength(sQueue));

    destroySQueue(sQueue);

}


void testStackQueueIsEmpty(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    sQueueIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, sQueueIsEmpty(sQueue));

    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    CuAssertIntEquals(cuTest, 0, sQueueIsEmpty(sQueue));


    free(sQueueDequeue(sQueue));
    CuAssertIntEquals(cuTest, 1, sQueueIsEmpty(sQueue));

    destroySQueue(sQueue);

}


void testStackQueueToArray(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    sQueueToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    sQueueEnqueue(sQueue, generateIntPointerSQT(2));
    sQueueEnqueue(sQueue, generateIntPointerSQT(3));
    sQueueEnqueue(sQueue, generateIntPointerSQT(4));

    int **arr = (int **) sQueueToArray(sQueue);

    for (int i = 0; i < sQueueGetLength(sQueue); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    destroySQueue(sQueue);

}


void testClearStackQueue(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    clearSQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, sQueueGetLength(sQueue));

    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    sQueueEnqueue(sQueue, generateIntPointerSQT(2));
    sQueueEnqueue(sQueue, generateIntPointerSQT(3));
    sQueueEnqueue(sQueue, generateIntPointerSQT(4));

    CuAssertIntEquals(cuTest, 4, sQueueGetLength(sQueue));

    clearSQueue(sQueue);

    CuAssertIntEquals(cuTest, 0, sQueueGetLength(sQueue));

    destroySQueue(sQueue);

}


void testDestroyStackQueue(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(free);

    destroySQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    sQueueEnqueue(sQueue, generateIntPointerSQT(1));
    sQueueEnqueue(sQueue, generateIntPointerSQT(2));
    sQueueEnqueue(sQueue, generateIntPointerSQT(3));
    sQueueEnqueue(sQueue, generateIntPointerSQT(4));

    destroySQueue(sQueue);

}


typedef struct SQueueTestStruct {

    int iData;
    char *cData;

} SQueueTestStruct;


void freeStackQueueTestStruct(void *item) {
    SQueueTestStruct *q = (SQueueTestStruct *) item;
    free(q->cData);
    free(q);
}


int sQueueTestStructComp(const void *item1, const void *item2) {
    SQueueTestStruct *q1 = (SQueueTestStruct *) item1;
    SQueueTestStruct *q2 = (SQueueTestStruct *) item2;

    int iDataFlag = q1->iData == q2->iData;
    int cDataFlag = strcmp(q1->cData, q2->cData);

    return !iDataFlag || cDataFlag;

}


SQueueTestStruct *generateStackQueueTestStruct(int value, char *str) {

    SQueueTestStruct *q = (SQueueTestStruct *) malloc(sizeof(SQueueTestStruct));
    q->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(q->cData, str);

    q->iData = value;

    return q;

}


void generalsQueueTest(CuTest *cuTest) {

    SQueue *sQueue = stackQueueInitialization(freeStackQueueTestStruct);
    char numbersStr[14][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen", "fourteen"};


    CuAssertIntEquals(cuTest, 0, sQueueGetLength(sQueue));
    CuAssertIntEquals(cuTest, 1, sQueueIsEmpty(sQueue));

    sQueueEnqueue(sQueue, generateStackQueueTestStruct(1, "one"));
    sQueueEnqueue(sQueue, generateStackQueueTestStruct(2, "two"));
    sQueueEnqueue(sQueue, generateStackQueueTestStruct(3, "three"));

    CuAssertIntEquals(cuTest, 3, sQueueGetLength(sQueue));
    CuAssertIntEquals(cuTest, 0, sQueueIsEmpty(sQueue));

    CuAssertIntEquals(cuTest, 1, ((SQueueTestStruct *) sQueuePeek(sQueue))->iData);
    CuAssertStrEquals(cuTest, "one", ((SQueueTestStruct *) sQueuePeek(sQueue))->cData);

    free(sQueueDequeue(sQueue));

    SQueueTestStruct **structArr = (SQueueTestStruct **) malloc(sizeof(SQueueTestStruct *) * 11);
    for (int i = 0; i < 11; i++)
        structArr[i] = generateStackQueueTestStruct(i + 4, numbersStr[i + 3]);

    sQueueAddAll(sQueue, (void **) structArr, 11);

    CuAssertIntEquals(cuTest, 13, sQueueGetLength(sQueue));

    SQueueTestStruct **sQueueArr = (SQueueTestStruct **) sQueueToArray(sQueue);

    for (int i = 0; i < sQueueGetLength(sQueue); i++) {
        CuAssertIntEquals(cuTest, i + 2, sQueueArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i + 1], sQueueArr[i]->cData);
    }

    int currentValue = 1;
    while (!sQueueIsEmpty(sQueue)) {
        currentValue += 1;
        SQueueTestStruct *currentItem = sQueueDequeue(sQueue);
        CuAssertIntEquals(cuTest, currentValue, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[currentValue - 1], currentItem->cData);

        freeStackQueueTestStruct(currentItem);

    }


    free(structArr);
    free(sQueueArr);
    destroySQueue(sQueue);

}


CuSuite *createStackQueueTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidStackQueueInitialization);
    SUITE_ADD_TEST(suite, testValidStackQueueInitialization);
    SUITE_ADD_TEST(suite, testStackQueueEnqueue);
    SUITE_ADD_TEST(suite, testStackQueueEnqueueAll);
    SUITE_ADD_TEST(suite, testStackQueueDequeue);
    SUITE_ADD_TEST(suite, testStackQueuePeek);
    SUITE_ADD_TEST(suite, testStackQueueGetLength);
    SUITE_ADD_TEST(suite, testStackQueueIsEmpty);
    SUITE_ADD_TEST(suite, testStackQueueToArray);
    SUITE_ADD_TEST(suite, testClearStackQueue);
    SUITE_ADD_TEST(suite, testDestroyStackQueue);

    SUITE_ADD_TEST(suite, generalsQueueTest);

    return suite;

}


void stackQueueUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Stack Queue Test**\n");

    CuSuite *suite = createStackQueueTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}