#include "InputScannerTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../FilesHandler/Headers/InputScanner.h"
#include "../../../../DataStructure/Strings/Headers/String.h"


void testScanStrS(CuTest *cuTest) {

    scanStrS(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "my input");
    fseek(dir, 0, SEEK_SET);

    String *input = scanStrS(dir);

    fclose(dir);

    CuAssertStrEquals(cuTest, "my input", input->string);

    destroyString(input);

}


void testScanStrC(CuTest *cuTest) {

    scanStrC(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "my input");
    fseek(dir, 0, SEEK_SET);

    char *input = scanStrC(dir);

    fclose(dir);

    CuAssertStrEquals(cuTest, "my input", input);

    free(input);

}


void testScanChar(CuTest *cuTest) {

    scanChar(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "d");
    fseek(dir, 0, SEEK_SET);

    CuAssertIntEquals(cuTest, (int) 'd', (int) scanChar(dir));

    fclose(dir);

}


void testScanInt(CuTest *cuTest) {

    scanInt(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "122not a number33");
    fseek(dir, 0, SEEK_SET);

    scanInt(dir);
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, ERROR_TEST->errorCode);


    fclose(dir);
    dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }
    fprintf(dir, "123");
    fseek(dir, 0, SEEK_SET);

    CuAssertIntEquals(cuTest, 123, scanInt(dir));

    fclose(dir);

}


void testScanDouble(CuTest *cuTest) {

    scanDouble(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "123.123not a number");
    fseek(dir, 0, SEEK_SET);

    scanDouble(dir);
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, ERROR_TEST->errorCode);


    fclose(dir);
    dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }
    fprintf(dir, "123.123");
    fseek(dir, 0, SEEK_SET);

    CuAssertIntEquals(cuTest, 1, scanDouble(dir) == 123.123);

    fclose(dir);

}


void testScanFloat(CuTest *cuTest) {

    scanFloat(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "123..5");
    fseek(dir, 0, SEEK_SET);

    scanFloat(dir);

    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, ERROR_TEST->errorCode);


    fclose(dir);
    dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }
    fprintf(dir, "123.5");
    fseek(dir, 0, SEEK_SET);

    CuAssertIntEquals(cuTest, 1, scanFloat(dir) == 123.5);

    fclose(dir);

}


void testScanLong(CuTest *cuTest) {

    scanLong(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "123n");
    fseek(dir, 0, SEEK_SET);

    scanLong(dir);

    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, ERROR_TEST->errorCode);


    fclose(dir);
    dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }
    fprintf(dir, "123");
    fseek(dir, 0, SEEK_SET);

    CuAssertIntEquals(cuTest, 123, scanLong(dir));

    fclose(dir);

}


void testScanLongLong(CuTest *cuTest) {

    scanLongLong(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "123n");
    fseek(dir, 0, SEEK_SET);

    scanLongLong(dir);
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, ERROR_TEST->errorCode);


    fclose(dir);
    dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }
    fprintf(dir, "123");
    fseek(dir, 0, SEEK_SET);

    CuAssertIntEquals(cuTest, 123, scanLongLong(dir));

    fclose(dir);

}


void testScanShort(CuTest *cuTest) {

    scanShort(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "n123");
    fseek(dir, 0, SEEK_SET);

    scanShort(dir);
    CuAssertIntEquals(cuTest, SOMETHING_WENT_WRONG, ERROR_TEST->errorCode);


    fclose(dir);
    dir = fopen("inputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }
    fprintf(dir, "123");
    fseek(dir, 0, SEEK_SET);

    CuAssertIntEquals(cuTest, 123, scanShort(dir));

    fclose(dir);

}


CuSuite *createInputScannerTestsSuite(void) {

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


void inputScannerUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Input Scanner Test**\n");

    CuSuite *suite = createInputScannerTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}