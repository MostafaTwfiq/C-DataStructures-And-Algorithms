#include "DequeTest.h"

#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../DataStructure/Deque/Headers/Deque.h"



/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerDT(int integer) {
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

int compareIntPointersDT(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}





/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerDT(char *ch) {

    char *newCh = (char *) malloc( sizeof(char) * (strlen(ch) + 1) );

    strcpy(newCh, ch);

    return newCh;

}







void testInvalidDequeInitialization(CuTest *cuTest) {

    Deque *deque = dequeInitialization(NULL);

    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

}



void testValidDequeInitialization(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    CuAssertPtrNotNull(cuTest, deque);

    destroyDeque(deque);
}




void testDequeInsertFront(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequeInsertFront(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, generateIntPointerDT(4));
    dequeInsertFront(deque, generateIntPointerDT(3));
    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));

    for (int i = 0; i < deque->rear - deque->front; i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) deque->arr[i + deque->front]);


    destroyDeque(deque);

}





void testDequeInsertRear(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequeInsertRear(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertRear(deque, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertRear(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(2));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));

    for (int i = 0; i < deque->rear - deque->front; i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) deque->arr[i + deque->front]);


    destroyDeque(deque);

}





void testDequeGetFront(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequeGetFront(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));

    for (int i = 0; i < deque->rear - deque->front; i++) {
        int *currentItem = (int *) dequeGetFront(deque);
        CuAssertIntEquals(cuTest, i + 1, *currentItem);

        free(currentItem);

    }


    destroyDeque(deque);

}





void testDequeGetRear(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequeGetRear(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));

    for (int i = deque->rear - deque->front - 1; i >= 0; i--) {
        int *currentItem = (int *) dequeGetRear(deque);
        CuAssertIntEquals(cuTest, i + 1, *currentItem);

        free(currentItem);

    }


    destroyDeque(deque);

}







void testDequePeekFront(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequePeekFront(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));

    for (int i = 0; i < deque->rear - deque->front; i++) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) dequePeekFront(deque));

        free(dequeGetFront(deque));

    }


    destroyDeque(deque);

}






void testDequePeekRear(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequePeekRear(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));

    for (int i = deque->rear - deque->front - 1; i >= 0; i--) {
        CuAssertIntEquals(cuTest, i + 1, *(int *) dequePeekRear(deque));

        free(dequeGetRear(deque));

    }


    destroyDeque(deque);

}






void testDequeToArray(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequeToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));

    int **arr = (int **) dequeToArray(deque);

    for (int i = 0; i < deque->rear - deque->front; i++)
        CuAssertIntEquals(cuTest, i + 1, *arr[i]);


    free(arr);
    destroyDeque(deque);

}






void testDequeGetLength(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequeGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    CuAssertIntEquals(cuTest, 0, dequeGetLength(deque));

    dequeInsertFront(deque, generateIntPointerDT(2));
    CuAssertIntEquals(cuTest, 1, dequeGetLength(deque));

    dequeInsertFront(deque, generateIntPointerDT(1));
    CuAssertIntEquals(cuTest, 2, dequeGetLength(deque));

    dequeInsertRear(deque, generateIntPointerDT(3));
    CuAssertIntEquals(cuTest, 3, dequeGetLength(deque));

    dequeInsertRear(deque, generateIntPointerDT(4));
    CuAssertIntEquals(cuTest, 4, dequeGetLength(deque));

    destroyDeque(deque);

}







void testDequeIsEmpty(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    dequeIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    CuAssertIntEquals(cuTest, 1, dequeIsEmpty(deque));

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));
    CuAssertIntEquals(cuTest, 0, dequeIsEmpty(deque));

    while (!dequeIsEmpty(deque))
        free(dequeGetRear(deque));


    CuAssertIntEquals(cuTest, 1, dequeIsEmpty(deque));

    destroyDeque(deque);

}






void testClearDeque(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    clearDeque(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    CuAssertIntEquals(cuTest, 1, dequeIsEmpty(deque));

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));
    CuAssertIntEquals(cuTest, 0, dequeIsEmpty(deque));

    clearDeque(deque);

    CuAssertIntEquals(cuTest, 1, dequeIsEmpty(deque));

    destroyDeque(deque);

}




void testDestroyDeque(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    destroyDeque(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    dequeInsertFront(deque, generateIntPointerDT(2));
    dequeInsertFront(deque, generateIntPointerDT(1));
    dequeInsertRear(deque, generateIntPointerDT(3));
    dequeInsertRear(deque, generateIntPointerDT(4));


    destroyDeque(deque);

}






CuSuite *createDequeTestsSuite() {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidDequeInitialization);
    SUITE_ADD_TEST(suite, testValidDequeInitialization);
    SUITE_ADD_TEST(suite, testDequeInsertFront);
    SUITE_ADD_TEST(suite, testDequeInsertRear);
    SUITE_ADD_TEST(suite, testDequeGetFront);
    SUITE_ADD_TEST(suite, testDequeGetRear);
    SUITE_ADD_TEST(suite, testDequePeekFront);
    SUITE_ADD_TEST(suite, testDequePeekRear);
    SUITE_ADD_TEST(suite, testDequeToArray);
    SUITE_ADD_TEST(suite, testDequeGetLength);
    SUITE_ADD_TEST(suite, testDequeIsEmpty);
    SUITE_ADD_TEST(suite, testClearDeque);
    SUITE_ADD_TEST(suite, testDestroyDeque);

    return suite;

}



void dequeUnitTest() {

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Deque Test**\n");

    CuSuite *suite = createDequeTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}

