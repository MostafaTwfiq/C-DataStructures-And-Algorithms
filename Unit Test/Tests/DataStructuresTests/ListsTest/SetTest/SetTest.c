#include "SetTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../DataStructure/Lists/Headers/Set.h"
#include "../../../../../DataStructure/Lists/Headers/Vector.h"
#include "../../../../../System/Utils.h"


int setTestStrcmp(const void *c1, const void *c2) {
    return strcmp(c1, c2);
}


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerSetT(int integer) {
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

int compareIntPointersSetT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerSetT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidSetInitialization(CuTest *cuTest) {

    setInitialization(1, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    setInitialization(1, free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    setInitialization(-1, free, compareIntPointersSetT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidSetInitialization(CuTest *cuTest) {

    Set *set = setInitialization(1, free, compareIntPointersSetT);

    CuAssertPtrNotNull(cuTest, set);

    destroySet(set);

}


void testSetAdd(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setAdd(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setAdd(set, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    setAdd(set, generateIntPointerSetT(10));
    setAdd(set, generateIntPointerSetT(20));
    setAdd(set, generateIntPointerSetT(30));

    setAdd(set, generateIntPointerSetT(10));
    setAdd(set, generateIntPointerSetT(20));
    setAdd(set, generateIntPointerSetT(30));

    CuAssertIntEquals(cuTest, 3, setGetLength(set));


    for (int i = 0; i < set->vector->count; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) set->vector->arr[i]);


    destroySet(set);

}


void testSetAddAtIndex(CuTest *cuTest) {
    Set *set = setInitialization(1, free, setTestStrcmp);

    setAddAtIndex(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setAddAtIndex(set, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempVal = 10;
    setAddAtIndex(set, &tempVal, 1);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    setAdd(set, generateCharPointerSetT("0"));
    setAddAtIndex(set, generateCharPointerSetT("30"), 0);
    setAddAtIndex(set, generateCharPointerSetT("20"), 1);
    setAddAtIndex(set, generateCharPointerSetT("10"), 2);

    setAdd(set, generateCharPointerSetT("0"));
    setAddAtIndex(set, generateCharPointerSetT("30"), 0);
    setAddAtIndex(set, generateCharPointerSetT("20"), 1);
    setAddAtIndex(set, generateCharPointerSetT("10"), 2);

    CuAssertIntEquals(cuTest, 4, set->vector->count);

    //arr:  "30", "20", "10", "0"
    //index: 0,  1,  2, 3

    CuAssertStrEquals(cuTest, "30", (char *) set->vector->arr[0]);
    CuAssertStrEquals(cuTest, "20", (char *) set->vector->arr[1]);
    CuAssertStrEquals(cuTest, "10", (char *) set->vector->arr[2]);
    CuAssertStrEquals(cuTest, "0", (char *) set->vector->arr[3]);

    destroySet(set);

}


void testSetDelete(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setDelete(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setDelete(set, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    setAdd(set, generateIntPointerSetT(10));
    setAdd(set, generateIntPointerSetT(20));
    setAdd(set, generateIntPointerSetT(100));
    setAdd(set, generateIntPointerSetT(30));
    setAdd(set, generateIntPointerSetT(200));
    setAdd(set, generateIntPointerSetT(40));
    setAdd(set, generateIntPointerSetT(300));
    setAdd(set, generateIntPointerSetT(50));

    setDelete(set, 2);
    setDelete(set, 3);
    setDelete(set, 4);

    CuAssertIntEquals(cuTest, 5, set->vector->count);

    for (int i = 0; i < set->vector->count; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) set->vector->arr[i]);

    destroySet(set);

}


void testSetDeleteWtoFr(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setDeleteWtoFr(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setDeleteWtoFr(set, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);


    for (int i = 0; i < 5; i++)
        setAdd(set, generateIntPointerSetT((i + 1) * 10));

    int *tempPointer1 = setDeleteWtoFr(set, 4);
    int *tempPointer2 = setDeleteWtoFr(set, 0);

    CuAssertIntEquals(cuTest, 3, set->vector->count);

    for (int i = 0; i < set->vector->count; i++)
        CuAssertIntEquals(cuTest, (i + 2) * 10, *(int *) set->vector->arr[i]);


    CuAssertIntEquals(cuTest, 10, *tempPointer2);
    CuAssertIntEquals(cuTest, 50, *tempPointer1);

    free(tempPointer1);
    free(tempPointer2);
    destroySet(set);

}


void testSetGetIndex(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setGetIndex(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setGetIndex(set, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 0; i < 5; i++)
        setAdd(set, generateIntPointerSetT((i + 1) * 10));

    int tempValue;
    for (int i = 0; i < 5; i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, i, setGetIndex(set, &tempValue));
    }

    tempValue = 60;
    CuAssertIntEquals(cuTest, -1, setGetIndex(set, &tempValue));


    destroySet(set);

}


void testSetGet(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setGet(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setGet(set, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    for (int i = 0; i < 5; i++)
        setAdd(set, generateIntPointerSetT((i + 1) * 10));

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) setGet(set, i));


    destroySet(set);

}


void testSetContains(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setContains(set, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 0; i < 5; i++)
        setAdd(set, generateIntPointerSetT((i + 1) * 10));

    int tempValue;
    for (int i = 0; i < 5; i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, 1, setContains(set, &tempValue));
    }

    tempValue = 60;
    CuAssertIntEquals(cuTest, 0, setContains(set, &tempValue));


    destroySet(set);

}


void testSetToArray(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 5; i++)
        setAdd(set, generateIntPointerSetT((i + 1) * 10));

    int **generatedArr = (int **) setToArray(set);
    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) generatedArr[i]);


    free(generatedArr);
    destroySet(set);

}


void testSetGetLength(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, setGetLength(set));

    for (int i = 0; i < 5; i++) {
        setAdd(set, generateIntPointerSetT((i + 1) * 10));
        CuAssertIntEquals(cuTest, i + 1, setGetLength(set));
    }

    for (int i = 1; i <= 5; i++) {
        setDelete(set, 0);
        CuAssertIntEquals(cuTest, 5 - i, setGetLength(set));
    }


    destroySet(set);

}


void testSetIsEmpty(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    setIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, setIsEmpty(set));

    for (int i = 0; i < 5; i++) {
        setAdd(set, generateIntPointerSetT((i + 1) * 10));
        CuAssertIntEquals(cuTest, 0, setIsEmpty(set));
    }

    clearSet(set);
    CuAssertIntEquals(cuTest, 1, setIsEmpty(set));

    destroySet(set);

}


void testClearSet(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    clearSet(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    clearSet(set);
    CuAssertIntEquals(cuTest, 0, set->vector->count);

    setAdd(set, generateIntPointerSetT(30));
    setAdd(set, generateIntPointerSetT(20));

    CuAssertIntEquals(cuTest, 2, set->vector->count);

    clearSet(set);
    CuAssertIntEquals(cuTest, 0, set->vector->count);

    destroySet(set);

}


void testDestroySet(CuTest *cuTest) {
    Set *set = setInitialization(1, free, compareIntPointersSetT);

    destroySet(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    setAdd(set, generateIntPointerSetT(30));
    setAdd(set, generateIntPointerSetT(20));

    destroySet(set);

}


CuSuite *createSetTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidSetInitialization);
    SUITE_ADD_TEST(suite, testValidSetInitialization);
    SUITE_ADD_TEST(suite, testSetAdd);
    SUITE_ADD_TEST(suite, testSetAddAtIndex);
    SUITE_ADD_TEST(suite, testSetDelete);
    SUITE_ADD_TEST(suite, testSetDeleteWtoFr);
    SUITE_ADD_TEST(suite, testSetGetIndex);
    SUITE_ADD_TEST(suite, testSetGet);
    SUITE_ADD_TEST(suite, testSetContains);
    SUITE_ADD_TEST(suite, testSetToArray);
    SUITE_ADD_TEST(suite, testSetGetLength);
    SUITE_ADD_TEST(suite, testSetIsEmpty);
    SUITE_ADD_TEST(suite, testClearSet);
    SUITE_ADD_TEST(suite, testDestroySet);

    return suite;

}


void setUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Set Test**\n");

    CuSuite *suite = createSetTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}