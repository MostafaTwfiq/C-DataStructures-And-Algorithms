#include "PairTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Pairs/Headers/Pair.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerPT(int integer) {
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

int compareIntPointersPT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerPT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidPairInitialization(CuTest *cuTest) {

    int fElem, sElem;

    pairInitialization(NULL, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    pairInitialization(&fElem, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    pairInitialization(&fElem, &sElem, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    pairInitialization(&fElem, &sElem, free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidPairInitialization(CuTest *cuTest) {

    int fElem, sElem;

    Pair *pair = pairInitialization(&fElem, &sElem, free, free);
    CuAssertPtrNotNull(cuTest, pair);

    free(pair);

}

void testPairGetFElem(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);

    pairGetFElem(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertStrEquals(cuTest, "one", pairGetFElem(pair));

    destroyPair(pair);

}


void testPairGetSElem(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);

    pairGetSElem(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, *(int *) pairGetSElem(pair));

    destroyPair(pair);

}


void testPairSetFElem(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);

    pairSetFElem(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pairSetFElem(pair, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    pairSetFElem(pair, generateCharPointerPT("number one"));
    CuAssertStrEquals(cuTest, "number one", pair->fElem);

    destroyPair(pair);

}


void testPairSetSElem(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);


    pairSetSElem(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pairSetSElem(pair, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    pairSetSElem(pair, generateIntPointerPT(2));
    CuAssertIntEquals(cuTest, 2, *(int *) pair->sElem);

    destroyPair(pair);

}


void testPairSetFElemWtoFr(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);


    pairSetFElemWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pairSetFElemWtoFr(pair, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    char *tempFElem;

    tempFElem = pairSetFElemWtoFr(pair, generateCharPointerPT("number one"));
    CuAssertStrEquals(cuTest, "number one", pair->fElem);
    CuAssertStrEquals(cuTest, "one", tempFElem);

    free(tempFElem);
    destroyPair(pair);

}


void testPairSetSElemWtoFr(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);


    pairSetSElemWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    pairSetSElemWtoFr(pair, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int *tempSElem;

    tempSElem = pairSetSElemWtoFr(pair, generateIntPointerPT(2));
    CuAssertIntEquals(cuTest, 2, *(int *) pair->sElem);
    CuAssertIntEquals(cuTest, 1, *tempSElem);

    free(tempSElem);
    destroyPair(pair);

}


void testPairSwapElements(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);

    pairSwapElements(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertStrEquals(cuTest, "one", pair->fElem);
    CuAssertIntEquals(cuTest, 1, *(int *) pair->sElem);

    pairSwapElements(pair);

    CuAssertIntEquals(cuTest, 1, *(int *) pair->fElem);
    CuAssertStrEquals(cuTest, "one", pair->sElem);

    destroyPair(pair);

}


void testDestroyPair(CuTest *cuTest) {

    Pair *pair = pairInitialization(generateCharPointerPT("one"), generateIntPointerPT(1), free, free);

    destroyPair(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    destroyPair(pair);

}


CuSuite *createPairTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidPairInitialization);
    SUITE_ADD_TEST(suite, testValidPairInitialization);
    SUITE_ADD_TEST(suite, testPairGetFElem);
    SUITE_ADD_TEST(suite, testPairGetSElem);
    SUITE_ADD_TEST(suite, testPairSetFElem);
    SUITE_ADD_TEST(suite, testPairSetSElem);
    SUITE_ADD_TEST(suite, testPairSetFElemWtoFr);
    SUITE_ADD_TEST(suite, testPairSetSElemWtoFr);
    SUITE_ADD_TEST(suite, testPairSwapElements);
    SUITE_ADD_TEST(suite, testDestroyPair);

    return suite;

}


void pairUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Pair Test**\n");

    CuSuite *suite = createPairTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}