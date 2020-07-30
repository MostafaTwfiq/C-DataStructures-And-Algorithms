
#include "../../CuTest/CuTest.h"
#include "../../../DataStructure/Lists/Headers/Vector.h"
#include "../../../System/Utils.h"





/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerVT(int integer) {
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

int compareIntPointersVT(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}





/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerVT(char *ch) {

    char *newCh = (char *) malloc( sizeof(char) * (strlen(ch) + 1) );

    strcpy(newCh, ch);

    return newCh;

}




void testInvalidInitialLengthInitialization(CuTest *cuTest) {
    Vector * vector = vectorInitialization(-1, free, NULL);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, INVALID_ARG);
}

void testOnNullFreeFunction(CuTest *cuTest){
    Vector * vector = vectorInitialization(1, NULL, NULL);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, INVALID_ARG);
}

void testProperInitialization(CuTest *cuTest){
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);
    CuAssertPtrNotNull(cuTest, vector);
    destroyVector(vector);
}

void testAddFun(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorAdd(NULL, NULL);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, NULL_POINTER);

    vectorAdd(vector, NULL);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, INVALID_ARG);

    vectorAdd(vector, generateIntPointerVT(10));
    vectorAdd(vector, generateIntPointerVT(20));
    vectorAdd(vector, generateIntPointerVT(30));
    CuAssertIntEquals(cuTest, vector->count, 3);


    for (int i = 0; i < vector->count; i++)
        CuAssertIntEquals(cuTest, *(int *) vector->arr[i], (i + 1) * 10 );


    destroyVector(vector);

}

void testAddAtIndexFun(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, strcmp);

    vectorAddAtIndex(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, NULL_POINTER);

    vectorAddAtIndex(vector, NULL, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, INVALID_ARG);

    int tempVal = 10;
    vectorAddAtIndex(vector, &tempVal, 1);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, OUT_OF_RANGE);

    vectorAdd(vector, generateCharPointerVT("0"));
    vectorAddAtIndex(vector, generateCharPointerVT("30"), 0);
    vectorAddAtIndex(vector, generateCharPointerVT("20"), 1);
    vectorAddAtIndex(vector, generateCharPointerVT("10"), 2);
    CuAssertIntEquals(cuTest, vector->count, 4);

    //30, 20, 10, 0
    //0,  1,  2,  3

    CuAssertStrEquals(cuTest, (char *) vector->arr[0], "30");
    CuAssertStrEquals(cuTest, (char *) vector->arr[1], "20");
    CuAssertStrEquals(cuTest, (char *) vector->arr[2], "10");
    CuAssertStrEquals(cuTest, (char *) vector->arr[3], "0");

    destroyVector(vector);

}

void testAddAll(CuTest *cuTest) {

    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);


    vectorAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, NULL_POINTER);

    vectorAddAll(vector, NULL, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, INVALID_ARG);


    int **valuesArr = (int **) malloc(sizeof(int *) * 3);

    for (int i = 1; i <= 3; i++) {
        valuesArr[i - 1] = malloc(sizeof(int));
        *valuesArr[i - 1] = (i + 6) * 10;
    }
    // valuesArr = [70, 80, 90]

    vectorAddAll(vector, (void **) valuesArr, 3);
    CuAssertIntEquals(cuTest, vector->count, 3);

    for (int i = vector->count - 1, index = 2; i > vector->count - 4; i--, index--)
        CuAssertIntEquals(cuTest, *(int *) vector->arr[i], *(int *) valuesArr[index]);


    free(valuesArr);

    destroyVector(vector);

}



void testRemove(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemove(NULL);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, NULL_POINTER);

    vectorAdd(vector, generateIntPointerVT(10));

    vectorRemove(vector);

    CuAssertIntEquals(cuTest, vector->count, 0);

    destroyVector(vector);

}



void testRemoveWtoFr(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemoveWtFr(NULL);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, NULL_POINTER);

    int *currentItem = generateIntPointerVT(10);
    vectorAdd(vector, currentItem);

    vectorRemoveWtFr(vector);

    CuAssertIntEquals(cuTest, vector->count, 0);
    CuAssertIntEquals(cuTest, *currentItem, 10);

    free(currentItem);
    destroyVector(vector);

}



void testRemoveAtIndex(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemoveAtIndex(NULL, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, NULL_POINTER);

    vectorRemoveAtIndex(vector, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, OUT_OF_RANGE);

    vectorAdd(vector, generateIntPointerVT(10));
    vectorAdd(vector, generateIntPointerVT(20));
    vectorAdd(vector, generateIntPointerVT(100));
    vectorAdd(vector, generateIntPointerVT(30));
    vectorAdd(vector, generateIntPointerVT(200));
    vectorAdd(vector, generateIntPointerVT(40));
    vectorAdd(vector, generateIntPointerVT(300));
    vectorAdd(vector, generateIntPointerVT(50));

    vectorRemoveAtIndex(vector, 2);
    vectorRemoveAtIndex(vector, 3);
    vectorRemoveAtIndex(vector, 4);

    CuAssertIntEquals(cuTest, vector->count, 5);

    for (int i = 0; i < vector->count; i++)
        CuAssertIntEquals(cuTest, *(int *) vector->arr[i], (i + 1) * 10);

    destroyVector(vector);

}



void testRemoveAtIndexWtoFr(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemoveAtIndexWtFr(NULL, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, NULL_POINTER);

    vectorRemoveAtIndexWtFr(vector, 0);
    CuAssertIntEquals(cuTest, DUMMY_TEST_DATASTRUCTURE->errorCode, OUT_OF_RANGE);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    vectorAddAll(vector, (void **) arr, 5);

    vectorRemoveAtIndexWtFr(vector, 4);
    vectorRemoveAtIndexWtFr(vector, 0);

    CuAssertIntEquals(cuTest, vector->count, 3);

    for (int i = 0; i < vector->count; i++)
        CuAssertIntEquals(cuTest, *(int *) vector->arr[i], (i + 2) * 10);


    CuAssertIntEquals(cuTest, *arr[0], 10);
    CuAssertIntEquals(cuTest, *arr[4], 50);

    free(arr[0]);
    free(arr[4]);
    free(arr);
    destroyVector(vector);

}




CuSuite *createTestsSuite() {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testProperInitialization);
    SUITE_ADD_TEST(suite, testOnNullFreeFunction);
    SUITE_ADD_TEST(suite, testInvalidInitialLengthInitialization);
    SUITE_ADD_TEST(suite, testAddFun);
    SUITE_ADD_TEST(suite, testAddAtIndexFun);
    SUITE_ADD_TEST(suite, testAddAll);
    SUITE_ADD_TEST(suite, testRemove);
    SUITE_ADD_TEST(suite, testRemoveWtoFr);
    SUITE_ADD_TEST(suite, testRemoveAtIndex);
    SUITE_ADD_TEST(suite, testRemoveAtIndexWtoFr);

    return suite;

}



int main(void ){

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuSuite *suite = createTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    return 0;
}



