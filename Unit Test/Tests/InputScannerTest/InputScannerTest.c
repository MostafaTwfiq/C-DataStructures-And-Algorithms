#include "InputScannerTest.h"
#include "../../CuTest/CuTest.h"
#include "../../../System/Utils.h"
#include "../../../Files/Headers/InputScanner.h"
#include "../../../DataStructure/Strings/Headers/String.h"




void testScanStrS(CuTest *cuTest) {

    fprintf(stdout, "\nPlease enter (my input) to confirm the stringScannerS:- ");
    String *input = scanStrS();
    CuAssertStrEquals(cuTest, "my input", input->string);

    fprintf(stdout, "\n");

    destroyString(input);

}


void testScanStrC(CuTest *cuTest) {

    fprintf(stdout, "\nPlease enter (my input) to confirm the stringScannerC:- ");
    char *input = scanStrC();
    CuAssertStrEquals(cuTest, "my input", input);

    fprintf(stdout, "\n");

    free(input);

}



void testScanChar(CuTest *cuTest) {

    fprintf(stdout, "\nPlease enter the character (d) to confirm the charScanner:- ");
    CuAssertIntEquals(cuTest, (int) 'd', (int) scanChar());

    fprintf(stdout, "\n");

}



void testScanInt(CuTest *cuTest) {

    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;
    fprintf(stdout, "\nPlease enter non valid integer to confirm the integerScanner error catching:- ");
    scanInt();
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    fprintf(stdout, "\nPlease enter the integer (123) to confirm the integerScanner:- ");
    CuAssertIntEquals(cuTest, 123, scanInt());

    fprintf(stdout, "\n");

}




void testScanDouble(CuTest *cuTest) {

    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;
    fprintf(stdout, "\nPlease enter non valid double to confirm the doubleScanner error catching:- ");
    scanDouble();
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    fprintf(stdout, "\nPlease enter the double (123.123) to confirm the doubleScanner:- ");
    CuAssertIntEquals(cuTest, 1, scanDouble() == 123.123);

    fprintf(stdout, "\n");

}



void testScanFloat(CuTest *cuTest) {

    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;
    fprintf(stdout, "\nPlease enter non valid float to confirm the floatScanner error catching:- ");
    scanFloat();
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    fprintf(stdout, "\nPlease enter the float (123.5) to confirm the floatScanner:- ");

    CuAssertIntEquals(cuTest, 1, scanFloat() == 123.5);

    fprintf(stdout, "\n");

}



void testScanLong(CuTest *cuTest) {

    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;
    fprintf(stdout, "\nPlease enter non valid long to confirm the longScanner error catching:- ");
    scanLong();
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    fprintf(stdout, "\nPlease enter the long (123) to confirm the longScanner:- ");
    CuAssertIntEquals(cuTest, 123, scanLong());

    fprintf(stdout, "\n");

}


void testScanLongLong(CuTest *cuTest) {

    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;
    fprintf(stdout, "\nPlease enter non valid long long to confirm the longLongScanner error catching:- ");
    scanLongLong();
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    fprintf(stdout, "\nPlease enter the long (123) to confirm the longLongScanner:- ");
    CuAssertIntEquals(cuTest, 123, scanLongLong());

    fprintf(stdout, "\n");

}



void testScanShort(CuTest *cuTest) {

    DUMMY_TEST_DATASTRUCTURE->errorCode = 0;
    fprintf(stdout, "\nPlease enter non valid short to confirm the shortScanner error catching:- ");
    scanShort();
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    fprintf(stdout, "\nPlease enter the long (123) to confirm the shortScanner:- ");
    CuAssertIntEquals(cuTest, 123, scanShort());

    fprintf(stdout, "\n");

}



CuSuite *createInputScannerTestsSuite() {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testScanStrS);
    SUITE_ADD_TEST(suite, testScanStrC);
    SUITE_ADD_TEST(suite, testScanChar);
    SUITE_ADD_TEST(suite, testScanInt);
    SUITE_ADD_TEST(suite, testScanDouble);
    SUITE_ADD_TEST(suite, testScanFloat);
    SUITE_ADD_TEST(suite, testScanLong);
    SUITE_ADD_TEST(suite, testScanLongLong);
    SUITE_ADD_TEST(suite, testScanShort);

    return suite;

}



void inputScannerUnitTest() {

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Input Scanner Test**\n");

    CuSuite *suite = createInputScannerTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}