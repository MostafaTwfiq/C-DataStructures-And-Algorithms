#include "IntegerAlgTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../Algorithms/IntegersAlg/Headers/IntegerAlg.h"


void testIntegerNumOfDigits(CuTest *cuTest) {

    CuAssertIntEquals(cuTest, 1, integerNumOfDigits(0));
    CuAssertIntEquals(cuTest, 2, integerNumOfDigits(10));
    CuAssertIntEquals(cuTest, 9, integerNumOfDigits(123456874));
    CuAssertIntEquals(cuTest, 4, integerNumOfDigits(-1223));
    CuAssertIntEquals(cuTest, 1, integerNumOfDigits(-0));
    CuAssertIntEquals(cuTest, 1, integerNumOfDigits(00000));
    CuAssertIntEquals(cuTest, 1, integerNumOfDigits(2));

}


void testIntegerToCharArray(CuTest *cuTest) {

    char *integerCharArr;

    integerCharArr = intToCharArr(1);
    CuAssertStrEquals(cuTest, "1", integerCharArr);
    CuAssertIntEquals(cuTest, 1, strlen(integerCharArr));
    free(integerCharArr);

    integerCharArr = intToCharArr(123456);
    CuAssertStrEquals(cuTest, "123456", integerCharArr);
    CuAssertIntEquals(cuTest, 6, strlen(integerCharArr));
    free(integerCharArr);

    integerCharArr = intToCharArr(0);
    CuAssertStrEquals(cuTest, "0", integerCharArr);
    CuAssertIntEquals(cuTest, 1, strlen(integerCharArr));
    free(integerCharArr);

    integerCharArr = intToCharArr(-92334);
    CuAssertStrEquals(cuTest, "-92334", integerCharArr);
    CuAssertIntEquals(cuTest, 6, strlen(integerCharArr));
    free(integerCharArr);


}


void testMaxInt(CuTest *cuTest) {

    CuAssertIntEquals(cuTest, 2, maxInt(0, 2));
    CuAssertIntEquals(cuTest, 39, maxInt(-10, 39));
    CuAssertIntEquals(cuTest, 123456874, maxInt(123456874, 23));
    CuAssertIntEquals(cuTest, 1, maxInt(1, -1223));
    CuAssertIntEquals(cuTest, 0, maxInt(0, 0));
    CuAssertIntEquals(cuTest, 22, maxInt(22, 22));
    CuAssertIntEquals(cuTest, -11, maxInt(-12, -11));

}


void testMinInt(CuTest *cuTest) {

    CuAssertIntEquals(cuTest, 0, minInt(0, 2));
    CuAssertIntEquals(cuTest, -10, minInt(-10, 39));
    CuAssertIntEquals(cuTest, 23, minInt(123456874, 23));
    CuAssertIntEquals(cuTest, -1223, minInt(1, -1223));
    CuAssertIntEquals(cuTest, 0, minInt(0, 0));
    CuAssertIntEquals(cuTest, 22, minInt(22, 22));
    CuAssertIntEquals(cuTest, -12, minInt(-12, -11));

}


void testCompareInt(CuTest *cuTest) {

    CuAssertIntEquals(cuTest, 0, compareInt(0, 0));
    CuAssertIntEquals(cuTest, 0, compareInt(-10, -10));
    CuAssertIntEquals(cuTest, 0, compareInt(12, 12));
    CuAssertIntEquals(cuTest, 1, compareInt(1, -1223) > 0 ? 1 : -1);
    CuAssertIntEquals(cuTest, -1, compareInt(22, 32) > 0 ? 1 : -1);
    CuAssertIntEquals(cuTest, 1, compareInt(-100, -200) > 0 ? 1 : -1);

}


void testCompareIntR(CuTest *cuTest) {

    CuAssertIntEquals(cuTest, 0, compareIntR(0, 0));
    CuAssertIntEquals(cuTest, 0, compareIntR(-10, -10));
    CuAssertIntEquals(cuTest, 0, compareIntR(12, 12));
    CuAssertIntEquals(cuTest, -1, compareIntR(1, -1223) > 0 ? 1 : -1);
    CuAssertIntEquals(cuTest, 1, compareIntR(22, 32) > 0 ? 1 : -1);
    CuAssertIntEquals(cuTest, -1, compareIntR(-100, -200) > 0 ? 1 : -1);

}


void testCompareIntPointers(CuTest *cuTest) {

    int fValue, sValue;

    fValue = 0, sValue = 0;
    CuAssertIntEquals(cuTest, 0, compareIntPointers(&fValue, &sValue));

    fValue = -10, sValue = -10;
    CuAssertIntEquals(cuTest, 0, compareIntPointers(&fValue, &sValue));

    fValue = 12, sValue = 12;
    CuAssertIntEquals(cuTest, 0, compareIntPointers(&fValue, &sValue));

    fValue = 1, sValue = -1223;
    CuAssertIntEquals(cuTest, 1, compareIntPointers(&fValue, &sValue) > 0 ? 1 : -1);

    fValue = 22, sValue = 32;
    CuAssertIntEquals(cuTest, -1, compareIntPointers(&fValue, &sValue) > 0 ? 1 : -1);

    fValue = -100, sValue = -200;
    CuAssertIntEquals(cuTest, 1, compareIntPointers(&fValue, &sValue) > 0 ? 1 : -1);

}


void testCompareIntPointerR(CuTest *cuTest) {

    int fValue, sValue;

    fValue = 0, sValue = 0;
    CuAssertIntEquals(cuTest, 0, compareIntPointerR(&fValue, &sValue));

    fValue = -10, sValue = -10;
    CuAssertIntEquals(cuTest, 0, compareIntPointerR(&fValue, &sValue));

    fValue = 12, sValue = 12;
    CuAssertIntEquals(cuTest, 0, compareIntPointerR(&fValue, &sValue));

    fValue = 1, sValue = -1223;
    CuAssertIntEquals(cuTest, -1, compareIntPointerR(&fValue, &sValue) > 0 ? 1 : -1);

    fValue = 22, sValue = 32;
    CuAssertIntEquals(cuTest, 1, compareIntPointerR(&fValue, &sValue) > 0 ? 1 : -1);

    fValue = -100, sValue = -200;
    CuAssertIntEquals(cuTest, -1, compareIntPointerR(&fValue, &sValue) > 0 ? 1 : -1);

}


void testGenerateIntPointerP(CuTest *cuTest) {

    int value;
    int *valuePointer;

    value = 10;
    valuePointer = generateIntPointerP(&value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = -20;
    valuePointer = generateIntPointerP(&value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = 100;
    valuePointer = generateIntPointerP(&value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = 0;
    valuePointer = generateIntPointerP(&value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = -232333;
    valuePointer = generateIntPointerP(&value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

}


void testGenerateIntPointerI(CuTest *cuTest) {

    int value;
    int *valuePointer;

    value = 10;
    valuePointer = generateIntPointerI(value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = -20;
    valuePointer = generateIntPointerI(value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = 100;
    valuePointer = generateIntPointerI(value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = 0;
    valuePointer = generateIntPointerI(value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

    value = -232333;
    valuePointer = generateIntPointerI(value);
    CuAssertIntEquals(cuTest, value, *valuePointer);
    free(valuePointer);

}


void testIntHashFun(CuTest *cuTest) {

    int value;

    value = 10;
    CuAssertIntEquals(cuTest, value, intHashFun(&value));

    value = 20;
    CuAssertIntEquals(cuTest, value, intHashFun(&value));

    value = -100;
    CuAssertIntEquals(cuTest, value, intHashFun(&value));

    value = 0;
    CuAssertIntEquals(cuTest, value, intHashFun(&value));

    value = 23;
    CuAssertIntEquals(cuTest, value, intHashFun(&value));

    value = -1233;
    CuAssertIntEquals(cuTest, value, intHashFun(&value));

}


void testIntSum(CuTest *cuTest) {

    CuAssertIntEquals(cuTest, 20, intSum(10, 10));
    CuAssertIntEquals(cuTest, -300, intSum(-100, -200));
    CuAssertIntEquals(cuTest, 0, intSum(0, 0));
    CuAssertIntEquals(cuTest, 10, intSum(0, 10));
    CuAssertIntEquals(cuTest, 46464, intSum(23232, 23232));
    CuAssertIntEquals(cuTest, -111, intSum(-211, 100));

}


void testIntArrSum(CuTest *cuTest) {

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    intArrSum(NULL, -1);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    intArrSum(arr, -1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 55, intArrSum(arr, 10));

}


CuSuite *createIntegerAlgTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testIntegerNumOfDigits);
    SUITE_ADD_TEST(suite, testIntegerToCharArray);
    SUITE_ADD_TEST(suite, testMaxInt);
    SUITE_ADD_TEST(suite, testMinInt);
    SUITE_ADD_TEST(suite, testCompareInt);
    SUITE_ADD_TEST(suite, testCompareIntR);
    SUITE_ADD_TEST(suite, testCompareIntPointers);
    SUITE_ADD_TEST(suite, testCompareIntPointerR);
    SUITE_ADD_TEST(suite, testGenerateIntPointerP);
    SUITE_ADD_TEST(suite, testGenerateIntPointerI);
    SUITE_ADD_TEST(suite, testIntHashFun);
    SUITE_ADD_TEST(suite, testIntSum);
    SUITE_ADD_TEST(suite, testIntArrSum);

    return suite;

}


void integerAlgUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Integer Algorithms Test**\n");

    CuSuite *suite = createIntegerAlgTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}