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







void testInvalidDequeInitialization(CuTest *cuTest) {

    Deque *deque = dequeInitialization(NULL);

    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

}



void testValidDequeInitialization(CuTest *cuTest) {

    Deque *deque = dequeInitialization(free);

    CuAssertPtrNotNull(cuTest, deque);

    destroyDeque(deque);
}



CuSuite *createDequeTestsSuite() {

    CuSuite *suite = CuSuiteNew();

    //SUITE_ADD_TEST(suite, testInvalidQueueInitialization);

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

