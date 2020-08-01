#include "QueueTest.h"

#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../DataStructure/Queues/Headers/Queue.h"


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
    return *(int *)a - *(int *)b;
}





/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerQT(char *ch) {

    char *newCh = (char *) malloc( sizeof(char) * (strlen(ch) + 1) );

    strcpy(newCh, ch);

    return newCh;

}



void testInvalidQueueInitialization(CuTest *cuTest) {

    Queue *queue = queueInitialization(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

}



void testValidQueueInitialization(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);
    CuAssertPtrNotNull(cuTest, queue);

}




void testQueueEnqueue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueEnqueue(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    queueEnqueue(queue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    for (int i = 0; i < queueGetLength(queue); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) queue->memory[i]);

    queueDestroy(queue);

}





void testQueueEnqueueAll(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueEnqueueAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    queueEnqueueAll(queue, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
        arr[i] = generateIntPointerQT(i + 1);

    queueEnqueueAll(queue, (void **) arr, 5);

    for (int i = 0; i < queueGetLength(queue); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) queue->memory[i]);


    free(arr);
    queueDestroy(queue);

}





void testQueueDequeue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueDequeue(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    queueDequeue(queue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    for (int i = 0; i < queueGetLength(queue); i++) {

        int *currentItem = (int *) queueDequeue(queue);
        CuAssertIntEquals(cuTest, i + 1, *(int *) currentItem);

        free(currentItem);
    }

    queueDestroy(queue);

}






void testQueuePeek(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queuePeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    queuePeek(queue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, DUMMY_TEST_DATASTRUCTURE->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    for (int i = 0; i < queueGetLength(queue); i++) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) queuePeek(queue));

        free(queueDequeue(queue));
    }


    queueDestroy(queue);

}





void testQueueGetLength(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


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

    queueDestroy(queue);

}




void testQueueIsEmpty(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


    CuAssertIntEquals(cuTest, 1, queueIsEmpty(queue));

    queueEnqueue(queue, generateIntPointerQT(1));
    CuAssertIntEquals(cuTest, 0, queueIsEmpty(queue));


    free(queueDequeue(queue));
    CuAssertIntEquals(cuTest, 1, queueIsEmpty(queue));

    queueDestroy(queue);

}





void testQueueToArray(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    int **arr = (int **) queueToArray(queue);

    for (int i = 0; i < queueGetLength(queue); i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    queueDestroy(queue);

}






void testClearQueue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueClear(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


    CuAssertIntEquals(cuTest, 0, queueGetLength(queue));

    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    CuAssertIntEquals(cuTest, 4, queueGetLength(queue));

    queueClear(queue);

    CuAssertIntEquals(cuTest, 0, queueGetLength(queue));

    queueDestroy(queue);

}






void testDestroyQueue(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);

    queueDestroy(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    queueDestroy(queue);

}



Queue *printingQueue;

void printQueueItemFunQT(void *item) {
    queueEnqueue(printingQueue, generateIntPointerQT(*(int *)item));
}



void testQueueDisplay(CuTest *cuTest) {

    Queue *queue = queueInitialization(free);
    printingQueue = queueInitialization(free);

    queueDisplay(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    queueDisplay(queue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    queueEnqueue(queue, generateIntPointerQT(1));
    queueEnqueue(queue, generateIntPointerQT(2));
    queueEnqueue(queue, generateIntPointerQT(3));
    queueEnqueue(queue, generateIntPointerQT(4));

    queueDisplay(queue, printQueueItemFunQT);

    for (int i = 0; i < queueGetLength(queue); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) printingQueue->memory[i]);

    queueDestroy(printingQueue);
    queueDestroy(queue);

}





CuSuite *createQueueTestsSuite() {

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
    SUITE_ADD_TEST(suite, testQueueDisplay);
    SUITE_ADD_TEST(suite, testClearQueue);
    SUITE_ADD_TEST(suite, testDestroyQueue);

    return suite;

}



void queueUnitTest() {

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Queue Test**\n");

    CuSuite *suite = createQueueTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}

