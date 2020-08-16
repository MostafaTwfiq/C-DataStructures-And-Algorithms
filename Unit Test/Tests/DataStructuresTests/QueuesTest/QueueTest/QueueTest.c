#include "QueueTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Queues/Headers/Queue.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerQT(int integer) {
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

int compareIntPointersQT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerQT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidQueueInitialization(CuTest *cuTest) {

    Queue *queue = queueInitialization(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidQueueInitialization(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);
    CuAssertPtrNotNull(cuTest, queue);

    destroyQueue(queue);

}


void testQueueEnqueue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueEnqueue(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    queueEnqueue(queue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    for (int i = 0; i < queueGetLength(queue); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) queue->memory[i]);

    destroyQueue(queue);

}


void testQueueEnqueueAll(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueEnqueueAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    queueEnqueueAll(queue, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
        arr[i] = generateIntPointerQT(i + 1);

    queueEnqueueAll(queue, (void **) arr, 5);

    for (int i = 0; i < queueGetLength(queue); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) queue->memory[i]);


    free(arr);
    destroyQueue(queue);

}


void testQueueDequeue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueDequeue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    queueDequeue(queue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    int size = queueGetLength(queue);
    for (int i = 0; i < size; i++) {

        int *currentItem = (int *) queueDequeue(queue);
        CuAssertIntEquals(cuTest, i + 1, *(int *) currentItem);

        free(currentItem);
    }

    destroyQueue(queue);

}


void testQueuePeek(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queuePeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    queuePeek(queue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    int size = queueGetLength(queue);
    for (int i = 0; i < size; i++) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) queuePeek(queue));

        free(queueDequeue(queue));
    }


    destroyQueue(queue);

}


void testQueueGetLength(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, queueGetLength(queue));

    queueEnqueue(queue, generateIntPointerQT(1));
    CuAssertIntEquals(cuTest, 1, queueGetLength(queue));

    queueEnqueue(queue, generateIntPointerQT(2));
    CuAssertIntEquals(cuTest, 2, queueGetLength(queue));

    queueEnqueue(queue, generateIntPointerQT(3));
    CuAssertIntEquals(cuTest, 3, queueGetLength(queue));

    queueEnqueue(queue, generateIntPointerQT(4));
    CuAssertIntEquals(cuTest, 4, queueGetLength(queue));


    free(queueDequeue(queue));
    CuAssertIntEquals(cuTest, 3, queueGetLength(queue));

    free(queueDequeue(queue));
    CuAssertIntEquals(cuTest, 2, queueGetLength(queue));

    destroyQueue(queue);

}


void testQueueIsEmpty(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, queueIsEmpty(queue));

    queueEnqueue(queue, generateIntPointerQT(1));
    CuAssertIntEquals(cuTest, 0, queueIsEmpty(queue));


    free(queueDequeue(queue));
    CuAssertIntEquals(cuTest, 1, queueIsEmpty(queue));

    destroyQueue(queue);

}


void testQueueToArray(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    int **arr = (int **) queueToArray(queue);

    for (int i = 0; i < queueGetLength(queue); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    destroyQueue(queue);

}


void testClearQueue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    clearQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, queueGetLength(queue));

    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    CuAssertIntEquals(cuTest, 4, queueGetLength(queue));

    clearQueue(queue);

    CuAssertIntEquals(cuTest, 0, queueGetLength(queue));

    destroyQueue(queue);

}


void testDestroyQueue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    destroyQueue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    destroyQueue(queue);

}


typedef struct QueueTestStruct {

    int iData;
    char *cData;

} QueueTestStruct;


void freeQueueTestStruct(void *item) {
    QueueTestStruct *q = (QueueTestStruct *) item;
    free(q->cData);
    free(q);
}


int queueTestStructComp(const void *item1, const void *item2) {
    QueueTestStruct *q1 = (QueueTestStruct *) item1;
    QueueTestStruct *q2 = (QueueTestStruct *) item2;

    int iDataFlag = q1->iData == q2->iData;
    int cDataFlag = strcmp(q1->cData, q2->cData);

    return !iDataFlag || cDataFlag;

}


QueueTestStruct *generateQueueTestStruct(int value, char *str) {

    QueueTestStruct *q = (QueueTestStruct *) malloc(sizeof(QueueTestStruct));
    q->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(q->cData, str);

    q->iData = value;

    return q;

}


void generalQueueTest(CuTest *cuTest) {

    Queue *queue = queueInitialization(freeQueueTestStruct);
    char numbersStr[14][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen", "fourteen"};


    CuAssertIntEquals(cuTest, 0, queueGetLength(queue));
    CuAssertIntEquals(cuTest, 1, queueIsEmpty(queue));

    queueEnqueue(queue, generateQueueTestStruct(1, "one"));
    queueEnqueue(queue, generateQueueTestStruct(2, "two"));
    queueEnqueue(queue, generateQueueTestStruct(3, "three"));

    CuAssertIntEquals(cuTest, 3, queueGetLength(queue));
    CuAssertIntEquals(cuTest, 0, queueIsEmpty(queue));

    CuAssertIntEquals(cuTest, 1, ((QueueTestStruct *) queuePeek(queue))->iData);
    CuAssertStrEquals(cuTest, "one", ((QueueTestStruct *) queuePeek(queue))->cData);

    free(queueDequeue(queue));

    QueueTestStruct **structArr = (QueueTestStruct **) malloc(sizeof(QueueTestStruct *) * 11);
    for (int i = 0; i < 11; i++)
        structArr[i] = generateQueueTestStruct(i + 4, numbersStr[i + 3]);

    queueEnqueueAll(queue, (void **) structArr, 11);

    CuAssertIntEquals(cuTest, 13, queueGetLength(queue));

    QueueTestStruct **queueArr = (QueueTestStruct **) queueToArray(queue);
    for (int i = 0; i < queueGetLength(queue); i++) {
        CuAssertIntEquals(cuTest, i + 2, queueArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i + 1], queueArr[i]->cData);
    }

    int currentValue = 1;
    while (!queueIsEmpty(queue)) {
        currentValue += 1;
        QueueTestStruct *currentItem = queueDequeue(queue);
        CuAssertIntEquals(cuTest, currentValue, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[currentValue - 1], currentItem->cData);

        freeQueueTestStruct(currentItem);

    }


    free(structArr);
    free(queueArr);
    destroyQueue(queue);

}


CuSuite *createQueueTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidQueueInitialization);
    SUITE_ADD_TEST(suite, testValidQueueInitialization);
    SUITE_ADD_TEST(suite, testQueueEnqueue);
    SUITE_ADD_TEST(suite, testQueueEnqueueAll);
    SUITE_ADD_TEST(suite, testQueueDequeue);
    SUITE_ADD_TEST(suite, testQueuePeek);
    SUITE_ADD_TEST(suite, testQueueGetLength);
    SUITE_ADD_TEST(suite, testQueueIsEmpty);
    SUITE_ADD_TEST(suite, testQueueToArray);
    SUITE_ADD_TEST(suite, testClearQueue);
    SUITE_ADD_TEST(suite, testDestroyQueue);

    SUITE_ADD_TEST(suite, generalQueueTest);

    return suite;

}


void queueUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Queue Test**\n");

    CuSuite *suite = createQueueTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}

