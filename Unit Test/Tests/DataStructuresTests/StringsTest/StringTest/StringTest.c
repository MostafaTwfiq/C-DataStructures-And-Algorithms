#include "StringTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Strings/Headers/String.h"
#include "../../../../../DataStructure/Lists/Headers/Vector.h"


void testInvalidStringInitialization(CuTest *cuTest) {

    String *string = stringInitialization(0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidStringInitialization(CuTest *cuTest) {

    String *string = stringInitialization(1);
    CuAssertPtrNotNull(cuTest, string);

    destroyString(string);

}


void testStringAppendChar(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringAppendChar(NULL, '\0');
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAppendChar(string, 'c');
    stringAppendChar(string, '-');
    stringAppendChar(string, 'd');
    stringAppendChar(string, 'a');
    stringAppendChar(string, 't');
    stringAppendChar(string, 'a');
    stringAppendChar(string, '-');
    stringAppendChar(string, 's');
    stringAppendChar(string, 't');
    stringAppendChar(string, 'r');
    stringAppendChar(string, 'u');
    stringAppendChar(string, 'c');
    stringAppendChar(string, 't');
    stringAppendChar(string, 'u');
    stringAppendChar(string, 'r');
    stringAppendChar(string, 'e');

    CuAssertStrEquals(cuTest, "c-data-structure", string->string);

    destroyString(string);

}


void testStringAddChar(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringAddChar(NULL, 0, '\0');
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAddChar(string, 0, '\0');
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);


    stringAppendChar(string, 'd');
    stringAddChar(string, 0, 'o');
    stringAddChar(string, 1, 'r');
    stringAddChar(string, 0, 'w');

    CuAssertStrEquals(cuTest, "word", string->string);

    destroyString(string);

}


void testStringUpdateChar(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringUpdateChar(NULL, 0, '\0');
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringUpdateChar(string, 0, '\0');
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    stringAppendChar(string, 'w');
    stringAppendChar(string, 'o');
    stringAppendChar(string, 'r');
    stringAppendChar(string, 'd');

    stringUpdateChar(string, 0, 'n');
    stringUpdateChar(string, 1, 'i');
    stringUpdateChar(string, 2, 'c');
    stringUpdateChar(string, 3, 'e');


    CuAssertStrEquals(cuTest, "nice", string->string);

    destroyString(string);

}


void testStringRemove(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringRemove(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringRemove(string, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    stringAppendChar(string, 'w');
    stringAppendChar(string, 'o');
    stringAppendChar(string, 'r');
    stringAppendChar(string, 'd');

    stringRemove(string, 2);
    stringRemove(string, 2);

    stringAppendChar(string, 'w');


    CuAssertStrEquals(cuTest, "wow", string->string);

    destroyString(string);

}


void testStringAppendC(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringAppendC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAppendC(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "a long sentence");


    CuAssertStrEquals(cuTest, "a long sentence", string->string);

    destroyString(string);

}


void testStringAppendS(CuTest *cuTest) {

    String *string = stringInitialization(1);

    String *tempString = stringInitialization(strlen("a long sentence"));
    strcpy(tempString->string, "a long sentence");

    stringAppendS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAppendS(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendS(string, tempString);


    CuAssertStrEquals(cuTest, "a long sentence", string->string);

    destroyString(tempString);
    destroyString(string);

}


void testStringChangeStringC(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringChangeStringC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringChangeStringC(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringChangeStringC(string, "a long sentence");


    CuAssertStrEquals(cuTest, "a long sentence", string->string);

    destroyString(string);

}


void testStringChangeStringS(CuTest *cuTest) {

    String *string = stringInitialization(1);

    String *tempString = stringInitialization(strlen("a long sentence"));
    stringChangeStringC(tempString, "a long sentence");

    stringChangeStringS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringChangeStringS(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringChangeStringS(string, tempString);


    CuAssertStrEquals(cuTest, "a long sentence", string->string);

    destroyString(tempString);
    destroyString(string);

}


void testStringGetIndex(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringGetIndex(NULL, '\0');
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringChangeStringC(string, "my name is");


    CuAssertIntEquals(cuTest, 0, stringGetIndex(string, 'm'));
    CuAssertIntEquals(cuTest, 1, stringGetIndex(string, 'y'));
    CuAssertIntEquals(cuTest, 2, stringGetIndex(string, ' '));
    CuAssertIntEquals(cuTest, 3, stringGetIndex(string, 'n'));
    CuAssertIntEquals(cuTest, 6, stringGetIndex(string, 'e'));
    CuAssertIntEquals(cuTest, 9, stringGetIndex(string, 's'));

    destroyString(string);

}


void testStringGet(CuTest *cuTest) {

    String *string = stringInitialization(1);
    char tempCharArr[] = "my name is";

    stringGet(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringGet(string, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    stringChangeStringC(string, tempCharArr);

    for (int i = 0; i < string->count; i++)
        CuAssertIntEquals(cuTest, (int) tempCharArr[i], (int) stringGet(string, i));


    destroyString(string);

}


void testStringSubStringC(CuTest *cuTest) {

    String *string = stringInitialization(1);
    char tempCharArr[] = "i love programming";

    stringSubStringC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringSubStringC(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringChangeStringC(string, tempCharArr);

    for (int i = 0; i < string->count; i++)
        CuAssertIntEquals(cuTest, 1, stringSubStringC(string, tempCharArr + i));

    CuAssertIntEquals(cuTest, 0, stringSubStringC(string, "lover"));
    CuAssertIntEquals(cuTest, 0, stringSubStringC(string, "nothing"));
    CuAssertIntEquals(cuTest, 0, stringSubStringC(string, "null"));
    CuAssertIntEquals(cuTest, 0, stringSubStringC(string, "i love programming."));

    destroyString(string);

}


void testStringSubStringS(CuTest *cuTest) {

    String *string = stringInitialization(1);
    String *secondString = stringInitialization(10);

    stringAppendC(secondString, "i love programming");

    stringSubStringS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringSubStringS(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringChangeStringS(string, secondString);

    for (int i = 0; i < string->count; i++) {
        CuAssertIntEquals(cuTest, 1, stringSubStringS(string, secondString));
        stringRemove(secondString, 0);
    }

    stringChangeStringC(secondString, "lover");
    CuAssertIntEquals(cuTest, 0, stringSubStringS(string, secondString));

    stringChangeStringC(secondString, "nothing");
    CuAssertIntEquals(cuTest, 0, stringSubStringS(string, secondString));

    stringChangeStringC(secondString, "null");
    CuAssertIntEquals(cuTest, 0, stringSubStringS(string, secondString));

    stringChangeStringC(secondString, "i love programming.");
    CuAssertIntEquals(cuTest, 0, stringSubStringS(string, secondString));

    destroyString(secondString);
    destroyString(string);

}


void testStringToCharArr(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringToCharArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAppendC(string, "to char array");

    char *stringCharArr = stringToCharArray(string);

    CuAssertStrEquals(cuTest, "to char array", stringCharArr);


    free(stringCharArr);
    destroyString(string);

}

void testStringToCustomCharArr(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringToCustomCharArray(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringToCustomCharArray(string, 0, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    stringAppendC(string, "to char array.");

    char *stringCharArr = stringToCustomCharArray(string, 3, 12);

    CuAssertStrEquals(cuTest, "char array", stringCharArr);


    free(stringCharArr);
    destroyString(string);

}


void testStringEqualsC(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringEqualsC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringEqualsC(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "string equals");


    CuAssertIntEquals(cuTest, 1, stringEqualsC(string, "string equals"));
    CuAssertIntEquals(cuTest, 0, stringEqualsC(string, "string equals."));
    CuAssertIntEquals(cuTest, 0, stringEqualsC(string, "string"));
    CuAssertIntEquals(cuTest, 0, stringEqualsC(string, ""));


    destroyString(string);

}


void testStringEqualsS(CuTest *cuTest) {

    String *string = stringInitialization(1);
    String *secondString = stringInitialization(10);

    stringEqualsS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringEqualsS(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "string equals");


    stringChangeStringC(secondString, "string equals");
    CuAssertIntEquals(cuTest, 1, stringEqualsS(string, secondString));

    stringChangeStringC(secondString, "string equals.");
    CuAssertIntEquals(cuTest, 0, stringEqualsS(string, secondString));

    stringChangeStringC(secondString, "string");
    CuAssertIntEquals(cuTest, 0, stringEqualsS(string, secondString));

    stringChangeStringC(secondString, "");
    CuAssertIntEquals(cuTest, 0, stringEqualsS(string, secondString));


    destroyString(secondString);
    destroyString(string);

}


void testStringCompareC(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringCompareC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringCompareC(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "string compare");


    CuAssertIntEquals(cuTest, 0, stringCompareC(string, "string compare") == 0 ? 0 : -1);
    CuAssertIntEquals(cuTest, -1, stringCompareC(string, "string compare1") < 0 ? -1 : 1);
    CuAssertIntEquals(cuTest, 1, stringCompareC(string, "string") > 0 ? 1 : -1);
    CuAssertIntEquals(cuTest, -1, stringCompareC(string, "strinh compare") < 0 ? -1 : 1);
    CuAssertIntEquals(cuTest, 1, stringCompareC(string, "") > 0 ? 1 : -1);


    destroyString(string);

}


void testStringCompareS(CuTest *cuTest) {

    String *string = stringInitialization(1);
    String *secondString = stringInitialization(10);

    stringCompareS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringCompareS(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "string compare");


    stringChangeStringC(secondString, "string compare");
    CuAssertIntEquals(cuTest, 0, stringCompareS(string, secondString) == 0 ? 0 : -1);

    stringChangeStringC(secondString, "string compare1");
    CuAssertIntEquals(cuTest, -1, stringCompareS(string, secondString) < 0 ? -1 : 1);

    stringChangeStringC(secondString, "string");
    CuAssertIntEquals(cuTest, 1, stringCompareS(string, secondString) > 0 ? 1 : -1);

    stringChangeStringC(secondString, "strinh compare");
    CuAssertIntEquals(cuTest, -1, stringCompareS(string, secondString) < 0 ? -1 : 1);

    stringChangeStringC(secondString, "");
    CuAssertIntEquals(cuTest, 1, stringCompareS(string, secondString) > 0 ? 1 : -1);


    destroyString(secondString);
    destroyString(string);

}


void testStringGetLength(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, stringGetLength(string));

    stringAppendC(string, "string compare");
    CuAssertIntEquals(cuTest, 14, stringGetLength(string));


    stringAppendChar(string, '.');
    CuAssertIntEquals(cuTest, 15, stringGetLength(string));

    stringRemove(string, 0);
    CuAssertIntEquals(cuTest, 14, stringGetLength(string));

    stringChangeStringC(string, "123");
    CuAssertIntEquals(cuTest, 3, stringGetLength(string));


    destroyString(string);

}


void testStringCustomTrimStart(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringCustomTrimStart(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringCompareC(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "\n    \t   @@!!!$%string trim  \n    \t   @@!!!$%");

    stringCustomTrimStart(string, "");
    CuAssertStrEquals(cuTest, "\n    \t   @@!!!$%string trim  \n    \t   @@!!!$%", string->string);

    stringCustomTrimStart(string, "\n\t @!$%");
    CuAssertStrEquals(cuTest, "string trim  \n    \t   @@!!!$%", string->string);

    stringCustomTrimStart(string, "string trim  \n    \t   @@!!!$%");
    CuAssertStrEquals(cuTest, "", string->string);

    destroyString(string);

}


void testStringCustomTrimEnd(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringCustomTrimEnd(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringCustomTrimEnd(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "\n    \t   @@!!!$%string trim  \n    \t   @@!!!$%");

    stringCustomTrimEnd(string, "");
    CuAssertStrEquals(cuTest, "\n    \t   @@!!!$%string trim  \n    \t   @@!!!$%", string->string);

    stringCustomTrimEnd(string, "\n\t @!$%");
    CuAssertStrEquals(cuTest, "\n    \t   @@!!!$%string trim", string->string);

    stringCustomTrimEnd(string, "\n    \t   @@!!!$%string trim");
    CuAssertStrEquals(cuTest, "", string->string);

    destroyString(string);

}


void testStringTrimStart(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringTrimStart(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAppendC(string, "\n    \t   @@!!!$%string trim  \n    \t   @@!!!$%");

    stringTrimStart(string);
    CuAssertStrEquals(cuTest, "@@!!!$%string trim  \n    \t   @@!!!$%", string->string);

    destroyString(string);

}


void testStringTrimEnd(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringTrimEnd(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAppendC(string, "\n    \t   @@!!!$%string trim  \n    \t   @@!!!$% \t \n  \n\n\n\n");

    stringTrimEnd(string);
    CuAssertStrEquals(cuTest, "\n    \t   @@!!!$%string trim  \n    \t   @@!!!$%", string->string);

    destroyString(string);

}


void testStringTrim(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringTrim(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringAppendC(string, "\n    \t   @@!!!$%string trim  \n    \t");

    stringTrim(string);
    CuAssertStrEquals(cuTest, "@@!!!$%string trim", string->string);

    destroyString(string);

}


void testStringCustomTrim(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringCustomTrim(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringCustomTrim(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringAppendC(string, "\n    \t   @@!!!$%string trim  \n    \t");

    stringCustomTrim(string, "\n \t@!$%");
    CuAssertStrEquals(cuTest, "string trim", string->string);

    destroyString(string);

}


void testStringScanInput(CuTest *cuTest) {

    String *string = stringInitialization(1);

    stringScanInput(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringScanInput(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("stringInputScannerTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in string unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    fprintf(dir, "my input");
    fseek(dir, 0, SEEK_SET);

    stringScanInput(string, dir);

    fclose(dir);

    CuAssertStrEquals(cuTest, "my input", string->string);

    destroyString(string);

}


void testPrintString(CuTest *cuTest) {

    String *string = stringInitialization(1);

    printString(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringScanInput(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    FILE *dir = fopen("stringPrintTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in string unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    stringChangeStringC(string, "i love programming");
    printString(string, dir);

    clearString(string);

    fseek(dir, 0, SEEK_SET);
    stringScanInput(string, dir);

    CuAssertStrEquals(cuTest, "i love programming", string->string);

    fclose(dir);

    destroyString(string);

}


void testStringSplit(CuTest *cuTest) {

    String *string = stringInitialization(1);

    char numberArr[5][6] = {"one", "two", "three", "four", "five"};

    stringSplit(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringSplit(string, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    stringChangeStringC(string, "one\ntwo\tthree four@five");

    Vector *wordsVector = stringSplit(string, "\n\t @");

    for (int i = 0; i < vectorGetLength(wordsVector); i++)
        CuAssertStrEquals(cuTest, numberArr[i], ((String *) vectorGet(wordsVector, i))->string);


    destroyVector(wordsVector);
    destroyString(string);

}


void testClearString(CuTest *cuTest) {

    String *string = stringInitialization(1);

    clearString(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringChangeStringC(string, "this is my string");

    CuAssertStrEquals(cuTest, "this is my string", string->string);

    clearString(string);
    CuAssertStrEquals(cuTest, "", string->string);

    CuAssertIntEquals(cuTest, 0, string->count);

    destroyString(string);

}


void tesDestroyString(CuTest *cuTest) {

    String *string = stringInitialization(1);

    destroyString(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stringChangeStringC(string, "this is my string");

    destroyString(string);

}


CuSuite *createStringTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidStringInitialization);
    SUITE_ADD_TEST(suite, testValidStringInitialization);
    SUITE_ADD_TEST(suite, testStringAppendChar);
    SUITE_ADD_TEST(suite, testStringAddChar);
    SUITE_ADD_TEST(suite, testStringUpdateChar);
    SUITE_ADD_TEST(suite, testStringRemove);
    SUITE_ADD_TEST(suite, testStringAppendC);
    SUITE_ADD_TEST(suite, testStringAppendS);
    SUITE_ADD_TEST(suite, testStringChangeStringC);
    SUITE_ADD_TEST(suite, testStringChangeStringS);
    SUITE_ADD_TEST(suite, testStringGetIndex);
    SUITE_ADD_TEST(suite, testStringGet);
    SUITE_ADD_TEST(suite, testStringSubStringC);
    SUITE_ADD_TEST(suite, testStringSubStringS);
    SUITE_ADD_TEST(suite, testStringToCharArr);
    SUITE_ADD_TEST(suite, testStringToCustomCharArr);
    SUITE_ADD_TEST(suite, testStringEqualsC);
    SUITE_ADD_TEST(suite, testStringEqualsS);
    SUITE_ADD_TEST(suite, testStringCompareC);
    SUITE_ADD_TEST(suite, testStringCompareS);
    SUITE_ADD_TEST(suite, testStringGetLength);
    SUITE_ADD_TEST(suite, testStringCustomTrimStart);
    SUITE_ADD_TEST(suite, testStringCustomTrimEnd);
    SUITE_ADD_TEST(suite, testStringTrimStart);
    SUITE_ADD_TEST(suite, testStringTrimEnd);
    SUITE_ADD_TEST(suite, testStringTrim);
    SUITE_ADD_TEST(suite, testStringCustomTrim);
    SUITE_ADD_TEST(suite, testStringScanInput);
    SUITE_ADD_TEST(suite, testPrintString);
    SUITE_ADD_TEST(suite, testStringSplit);
    SUITE_ADD_TEST(suite, testClearString);
    SUITE_ADD_TEST(suite, tesDestroyString);

    return suite;

}


void stringUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**String Test**\n");

    CuSuite *suite = createStringTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}