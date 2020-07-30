#include "VectorTest.h"

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




void testVectorInvalidInitialization(CuTest *cuTest) {
    Vector * vector = vectorInitialization(-1, free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vector = vectorInitialization(1, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

}

void testVectorProperInitialization(CuTest *cuTest){
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);
    CuAssertPtrNotNull(cuTest, vector);
    destroyVector(vector);
}

void testVectorAddFun(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorAdd(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAdd(vector, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAdd(vector, generateIntPointerVT(10));
    vectorAdd(vector, generateIntPointerVT(20));
    vectorAdd(vector, generateIntPointerVT(30));
    CuAssertIntEquals(cuTest, 3, vector->count);


    for (int i = 0; i < vector->count; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) vector->arr[i]);


    destroyVector(vector);

}

void testVectorAddAtIndexFun(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, strcmp);

    vectorAddAtIndex(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAddAtIndex(vector, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int tempVal = 10;
    vectorAddAtIndex(vector, &tempVal, 1);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAdd(vector, generateCharPointerVT("0"));
    vectorAddAtIndex(vector, generateCharPointerVT("30"), 0);
    vectorAddAtIndex(vector, generateCharPointerVT("20"), 1);
    vectorAddAtIndex(vector, generateCharPointerVT("10"), 2);
    CuAssertIntEquals(cuTest, 4, vector->count);

    //arr:  "30", "20", "10", "0"
    //index: 0,  1,  2, 3

    CuAssertStrEquals(cuTest, "30", (char *) vector->arr[0]);
    CuAssertStrEquals(cuTest, "20", (char *) vector->arr[1]);
    CuAssertStrEquals(cuTest, "10", (char *) vector->arr[2]);
    CuAssertStrEquals(cuTest, "0", (char *) vector->arr[3]);

    destroyVector(vector);

}

void testVectorAddAll(CuTest *cuTest) {

    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);


    vectorAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAddAll(vector, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    int **valuesArr = (int **) malloc(sizeof(int *) * 3);

    for (int i = 1; i <= 3; i++) {
        valuesArr[i - 1] = malloc(sizeof(int));
        *valuesArr[i - 1] = (i + 6) * 10;
    }
    // valuesArr = [70, 80, 90]

    vectorAddAll(vector, (void **) valuesArr, 3);
    CuAssertIntEquals(cuTest, 3, vector->count);

    for (int i = vector->count - 1, index = 2; i > vector->count - 4; i--, index--)
        CuAssertIntEquals(cuTest, *(int *) valuesArr[index], *(int *) vector->arr[i]);


    free(valuesArr);
    destroyVector(vector);

}



void testVectorRemove(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemove(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAdd(vector, generateIntPointerVT(10));

    vectorRemove(vector);

    CuAssertIntEquals(cuTest, 0, vector->count);

    destroyVector(vector);

}



void testVectorRemoveWtoFr(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemoveWtFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int *currentItem = generateIntPointerVT(10);
    vectorAdd(vector, currentItem);

    vectorRemoveWtFr(vector);

    CuAssertIntEquals(cuTest, 0, vector->count);
    CuAssertIntEquals(cuTest, 10, *currentItem);

    free(currentItem);
    destroyVector(vector);

}



void testVectorRemoveAtIndex(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemoveAtIndex(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorRemoveAtIndex(vector, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

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

    CuAssertIntEquals(cuTest, 5, vector->count);

    for (int i = 0; i < vector->count; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) vector->arr[i]);

    destroyVector(vector);

}



void testVectorRemoveAtIndexWtoFr(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorRemoveAtIndexWtFr(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorRemoveAtIndexWtFr(vector, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    vectorAddAll(vector, (void **) arr, 5);

    vectorRemoveAtIndexWtFr(vector, 4);
    vectorRemoveAtIndexWtFr(vector, 0);

    CuAssertIntEquals(cuTest, 3, vector->count);

    for (int i = 0; i < vector->count; i++)
        CuAssertIntEquals(cuTest, (i + 2) * 10, *(int *) vector->arr[i]);


    CuAssertIntEquals(cuTest, 10, *arr[0]);
    CuAssertIntEquals(cuTest, 50, *arr[4]);

    free(arr[0]);
    free(arr[4]);
    free(arr);
    destroyVector(vector);

}




void testVectorExpansion(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    CuAssertIntEquals(cuTest, 1, vector->length);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50
    vectorAdd(vector, arr[0]);
    vectorAdd(vector, arr[1]);
    CuAssertIntEquals(cuTest, 2, vector->length);
    vectorAdd(vector, arr[2]);
    CuAssertIntEquals(cuTest, 4, vector->length);
    vectorAdd(vector, arr[3]);
    vectorAdd(vector, arr[4]);
    CuAssertIntEquals(cuTest, 8, vector->length);


    free(arr);
    destroyVector(vector);

}




void testVectorContains(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorContains(vector, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    vectorAddAll(vector, (void **) arr, 5);

    int tempValue;
    for (int i = 0; i < 5; i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, 1, vectorContains(vector, &tempValue));
    }

    tempValue = 60;
    CuAssertIntEquals(cuTest, 0, vectorContains(vector, &tempValue));


    free(arr);
    destroyVector(vector);

}






void testVectorGetIndex(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorGetIndex(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorGetIndex(vector, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    vectorAddAll(vector, (void **) arr, 5);

    int tempValue;
    for (int i = 0; i < 5; i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, i, vectorGetIndex(vector, &tempValue));
    }

    tempValue = 60;
    CuAssertIntEquals(cuTest, -1, vectorGetIndex(vector, &tempValue));


    free(arr);
    destroyVector(vector);

}






void testVectorGetLastIndex(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorGetLastIndex(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorGetLastIndex(vector, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 6);
    for (int i = 0; i < 6; i += 2) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;

        arr[i + 1] = (int *) malloc(sizeof(int));
        *arr[i + 1] = (i + 1) * 10;

    }

    // 10, 10, 30, 30, 70, 70

    vectorAddAll(vector, (void **) arr, 6);

    int tempValue;
    for (int i = 0; i < 6; i +=2 ) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, i + 1, vectorGetLastIndex(vector, &tempValue));
    }

    tempValue = 100;
    CuAssertIntEquals(cuTest, -1, vectorGetLastIndex(vector, &tempValue));


    free(arr);
    destroyVector(vector);

}






void testVectorGet(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorGet(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorGet(vector, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    vectorAddAll(vector, (void **) arr, 5);

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) vectorGet(vector, i));


    free(arr);
    destroyVector(vector);

}





void testVectorToArray(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    vectorAddAll(vector, (void **) arr, 5);

    int **generatedArr = (int **) vectorToArray(vector);
    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) generatedArr[i]);


    free(arr);
    free(generatedArr);
    destroyVector(vector);

}




void testVectorToSubArray(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorToSubArray(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorToSubArray(vector, -10, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorToSubArray(vector, 0, 1);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50, 60, 70, 80, 90, 100

    vectorAddAll(vector, (void **) arr, 10);

    int **generatedArr = (int **) vectorToSubArray(vector, 3, 8);
    for (int i = 0; i < 6; i++)
        CuAssertIntEquals(cuTest, (i + 4) * 10, *(int *) generatedArr[i]);


    free(arr);
    free(generatedArr);
    destroyVector(vector);

}





int sortTestComparatorFunVT(const void *i1, const void *i2) {
    return **(int **)i1 - **(int **)i2;
}


void testVectorSort(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorSort(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorSort(vector, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAdd(vector, generateIntPointerVT(30));
    vectorAdd(vector, generateIntPointerVT(20));
    vectorAdd(vector, generateIntPointerVT(10));
    vectorAdd(vector, generateIntPointerVT(50));
    vectorAdd(vector, generateIntPointerVT(40));
    //vector before sort: 30, 20, 10, 50, 40

    vectorSort(vector, sortTestComparatorFunVT);
    //vector after sort: 10, 20, 30, 40, 50

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) vector->arr[i]);


    destroyVector(vector);

}





Vector *printingVector;

void printFunTestVT(const void *item) {
    vectorAdd(printingVector, (void *) item);
}

void testVectorPrintFun(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorToSubArray(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorToSubArray(vector, -10, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorToSubArray(vector, 0, 1);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50, 60, 70, 80, 90, 100

    vectorAddAll(vector, (void **) arr, 10);

    printingVector = vectorInitialization(10, free, NULL);

    printVector(vector, printFunTestVT);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) printingVector->arr[i]);

    printingVector->count = 0;

    free(arr);
    destroyVector(printingVector);
    destroyVector(vector);

}



void testVectorGetLength(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    CuAssertIntEquals(cuTest, 0, vectorGetLength(vector));

    vectorAdd(vector, generateIntPointerVT(30));
    CuAssertIntEquals(cuTest, 1, vectorGetLength(vector));

    vectorAdd(vector, generateIntPointerVT(20));
    CuAssertIntEquals(cuTest, 2, vectorGetLength(vector));

    vectorAdd(vector, generateIntPointerVT(10));
    CuAssertIntEquals(cuTest, 3, vectorGetLength(vector));

    vectorAdd(vector, generateIntPointerVT(50));
    CuAssertIntEquals(cuTest, 4, vectorGetLength(vector));

    vectorAdd(vector, generateIntPointerVT(40));
    CuAssertIntEquals(cuTest, 5, vectorGetLength(vector));


    destroyVector(vector);

}



void testVectorIsEmpty(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    vectorIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    CuAssertIntEquals(cuTest, 1, vectorIsEmpty(vector));

    vectorAdd(vector, generateIntPointerVT(30));
    CuAssertIntEquals(cuTest, 0, vectorIsEmpty(vector));

    vectorAdd(vector, generateIntPointerVT(20));
    CuAssertIntEquals(cuTest, 0, vectorIsEmpty(vector));

    vectorRemove(vector);
    CuAssertIntEquals(cuTest, 0, vectorIsEmpty(vector));

    vectorRemove(vector);
    CuAssertIntEquals(cuTest, 1, vectorIsEmpty(vector));

    vectorAdd(vector, generateIntPointerVT(30));
    clearVector(vector);
    CuAssertIntEquals(cuTest, 1, vectorIsEmpty(vector));

    destroyVector(vector);

}




void testClearVector(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    clearVector(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    clearVector(vector);
    CuAssertIntEquals(cuTest, 0, vector->count);

    vectorAdd(vector, generateIntPointerVT(30));
    vectorAdd(vector, generateIntPointerVT(20));

    CuAssertIntEquals(cuTest, 2, vector->count);

    clearVector(vector);
    CuAssertIntEquals(cuTest, 0, vector->count);

    destroyVector(vector);

}






void testDestroyVector(CuTest *cuTest) {
    Vector *vector = vectorInitialization(1, free, compareIntPointersVT);

    destroyVector(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    vectorAdd(vector, generateIntPointerVT(30));
    vectorAdd(vector, generateIntPointerVT(20));

    destroyVector(vector);

}




void generalVectorTest(CuTest *cuTest) {

}





CuSuite *createVectorTestsSuite() {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testVectorInvalidInitialization);
    SUITE_ADD_TEST(suite, testVectorProperInitialization);
    SUITE_ADD_TEST(suite, testVectorAddFun);
    SUITE_ADD_TEST(suite, testVectorAddAtIndexFun);
    SUITE_ADD_TEST(suite, testVectorAddAll);
    SUITE_ADD_TEST(suite, testVectorRemove);
    SUITE_ADD_TEST(suite, testVectorRemoveWtoFr);
    SUITE_ADD_TEST(suite, testVectorRemoveAtIndex);
    SUITE_ADD_TEST(suite, testVectorRemoveAtIndexWtoFr);
    SUITE_ADD_TEST(suite, testVectorExpansion);
    SUITE_ADD_TEST(suite, testVectorContains);
    SUITE_ADD_TEST(suite, testVectorGetIndex);
    SUITE_ADD_TEST(suite, testVectorGetLastIndex);
    SUITE_ADD_TEST(suite, testVectorGet);
    SUITE_ADD_TEST(suite, testVectorToArray);
    SUITE_ADD_TEST(suite, testVectorToSubArray);
    SUITE_ADD_TEST(suite, testVectorSort);
    SUITE_ADD_TEST(suite, testVectorPrintFun);
    SUITE_ADD_TEST(suite, testVectorGetLength);
    SUITE_ADD_TEST(suite, testVectorIsEmpty);
    SUITE_ADD_TEST(suite, testClearVector);
    SUITE_ADD_TEST(suite, testDestroyVector);

    SUITE_ADD_TEST(suite, generalVectorTest);

    return suite;

}



void vectorUnitTest() {

    printf("**Vector Test**\n");
    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuSuite *suite = createVectorTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}