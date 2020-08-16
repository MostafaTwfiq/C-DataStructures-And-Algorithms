#include "TxtFileLoaderTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../FilesHandler//Headers/TxtFileLoader.h"
#include "../../../../DataStructure/Strings/Headers/String.h"
#include "../../../../DataStructure/Lists/Headers/Vector.h"


char *filePath = "testFile.txt";


void createFileToBeTested() {

    FILE *dir = fopen(filePath, "w");

    if (dir == NULL) {
        fprintf(stderr, "can't create the text file in text file loader unit test");
        exit(-1);
    }

    fclose(dir);

}


void testInvalidTextFileLoaderInitialization(CuTest *cuTest) {

    txtFileLoaderInitialization(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidTextFileLoaderInitialization(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);
    CuAssertPtrNotNull(cuTest, txtFileLoader);

    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderWriteC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderWriteC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char *dataToWrite = "i love programming\nso much.";
    txtLoaderWriteC(txtFileLoader, dataToWrite);

    String *tempString = stringInitialization(10);

    txtFileLoader->fileP = fopen(txtFileLoader->dir, "r");
    char c;
    while ((c = fgetc(txtFileLoader->fileP)) != EOF)
        stringAppendChar(tempString, c);


    fclose(txtFileLoader->fileP);

    CuAssertStrEquals(cuTest, dataToWrite, tempString->string);

    destroyString(tempString);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderWriteS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderWriteS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderWriteS(txtFileLoader, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char *dataToWrite = "c data structure and algorithms";
    String *stringToWrite = stringInitialization(10);
    stringChangeStringC(stringToWrite, dataToWrite);
    txtLoaderWriteS(txtFileLoader, stringToWrite);

    String *tempString = stringInitialization(10);

    txtFileLoader->fileP = fopen(txtFileLoader->dir, "r");
    char c;
    while ((c = fgetc(txtFileLoader->fileP)) != EOF)
        stringAppendChar(tempString, c);


    fclose(txtFileLoader->fileP);

    CuAssertStrEquals(cuTest, dataToWrite, tempString->string);

    destroyString(stringToWrite);
    destroyString(tempString);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderReadFileS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderReadFileS(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    char *data = "one\ntwo\nthree";
    txtLoaderWriteC(txtFileLoader, data);

    String *dataS = txtLoaderReadFileS(txtFileLoader);

    CuAssertStrEquals(cuTest, data, dataS->string);

    destroyString(dataS);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderReadFileC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderReadFileC(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    char *data = "four\nfive\nsix";
    txtLoaderWriteC(txtFileLoader, data);

    char *fileData = txtLoaderReadFileC(txtFileLoader);

    CuAssertStrEquals(cuTest, data, fileData);

    free(fileData);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderReadFileLines(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderReadFileLines(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    char *data = "c\ndata\nstructure";
    txtLoaderWriteC(txtFileLoader, data);

    Vector *lines = txtLoaderReadFileLines(txtFileLoader);

    CuAssertIntEquals(cuTest, 3, vectorGetLength(lines));
    CuAssertStrEquals(cuTest, "c", ((String *) vectorGet(lines, 0))->string);
    CuAssertStrEquals(cuTest, "data", ((String *) vectorGet(lines, 1))->string);
    CuAssertStrEquals(cuTest, "structure", ((String *) vectorGet(lines, 2))->string);

    destroyVector(lines);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderReadFileWthDelimiter(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderReadFileWthDelimiter(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderReadFileWthDelimiter(txtFileLoader, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char *data = "c\ndata structure\tand,algorithms";
    txtLoaderWriteC(txtFileLoader, data);

    Vector *lines = txtLoaderReadFileWthDelimiter(txtFileLoader, "\n\t, ");

    CuAssertIntEquals(cuTest, 5, vectorGetLength(lines));
    CuAssertStrEquals(cuTest, "c", ((String *) vectorGet(lines, 0))->string);
    CuAssertStrEquals(cuTest, "data", ((String *) vectorGet(lines, 1))->string);
    CuAssertStrEquals(cuTest, "structure", ((String *) vectorGet(lines, 2))->string);
    CuAssertStrEquals(cuTest, "and", ((String *) vectorGet(lines, 3))->string);
    CuAssertStrEquals(cuTest, "algorithms", ((String *) vectorGet(lines, 4))->string);

    destroyVector(lines);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderCountLines(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderCountLines(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "c\ndata\nstructure");
    int linesNum = txtLoaderCountLines(txtFileLoader);
    CuAssertIntEquals(cuTest, 3, linesNum);

    txtLoaderWriteC(txtFileLoader, "");
    linesNum = txtLoaderCountLines(txtFileLoader);
    CuAssertIntEquals(cuTest, 0, linesNum);

    txtLoaderWriteC(txtFileLoader, "\n\n");
    linesNum = txtLoaderCountLines(txtFileLoader);
    CuAssertIntEquals(cuTest, 2, linesNum);

    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderReadLineS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderReadLineS(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");
    CuAssertPtrEquals(cuTest, NULL, txtLoaderReadLineS(txtFileLoader, 1));

    char lines[4][6] = {"one", "two", "three", "four"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour");

    for (int i = 0; i < 4; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderReadLineC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderReadLineC(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");
    CuAssertPtrEquals(cuTest, NULL, txtLoaderReadLineC(txtFileLoader, 1));

    char lines[4][6] = {"one", "two", "three", "four"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour");

    for (int i = 0; i < 4; i++) {
        char *line = txtLoaderReadLineC(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line);
        free(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAppendC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAppendC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAppendC(txtFileLoader, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[6][6] = {"one", "two", "three", "four", "five", "six"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\n");

    txtLoaderAppendC(txtFileLoader, "five\n");
    txtLoaderAppendC(txtFileLoader, "six");

    for (int i = 0; i < 6; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAppendS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAppendS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAppendS(txtFileLoader, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[6][6] = {"one", "two", "three", "four", "five", "six"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\n");

    String *stringToAppend = stringInitialization(6);

    stringChangeStringC(stringToAppend, "five\n");
    txtLoaderAppendS(txtFileLoader, stringToAppend);

    stringChangeStringC(stringToAppend, "six");
    txtLoaderAppendS(txtFileLoader, stringToAppend);

    destroyString(stringToAppend);

    for (int i = 0; i < 6; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAppendAllC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAppendAllC(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAppendAllC(txtFileLoader, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[7][6] = {"one", "two", "three", "four", "five", "six", "seven"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\n");

    Vector *newLines = vectorInitialization(2, free, NULL);

    char *newLn = (char *) malloc(sizeof(char) * (strlen("five") + 1));
    strcpy(newLn, "five");
    vectorAdd(newLines, newLn);

    newLn = (char *) malloc(sizeof(char) * (strlen("six") + 1));
    strcpy(newLn, "six");
    vectorAdd(newLines, newLn);

    newLn = (char *) malloc(sizeof(char) * (strlen("seven") + 1));
    strcpy(newLn, "seven");
    vectorAdd(newLines, newLn);

    txtLoaderAppendAllC(txtFileLoader, newLines);

    for (int i = 0; i < 7; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }

    destroyVector(newLines);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAppendAllS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAppendAllS(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAppendAllS(txtFileLoader, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[7][6] = {"one", "two", "three", "four", "five", "six", "seven"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\n");

    Vector *newLines = vectorInitialization(2, destroyString, NULL);

    String *newLnS = stringInitialization(6);
    stringChangeStringC(newLnS, "five");
    vectorAdd(newLines, newLnS);

    newLnS = stringInitialization(6);
    stringChangeStringC(newLnS, "six");
    vectorAdd(newLines, newLnS);

    newLnS = stringInitialization(6);
    stringChangeStringC(newLnS, "seven");
    vectorAdd(newLines, newLnS);

    txtLoaderAppendAllS(txtFileLoader, newLines);

    for (int i = 0; i < 7; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }

    destroyVector(newLines);
    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAppendToLineC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAppendToLineC(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAppendToLineC(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");
    txtLoaderAppendToLineC(txtFileLoader, "", 1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[4][12] = {"oneone", "twotwo", "threethree", "fourfour"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\n");


    for (int i = 0; i < 4; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        txtLoaderAppendToLineC(txtFileLoader, line->string, i);
        destroyString(line);
    }

    for (int i = 0; i < 4; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAppendToLineS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAppendToLineS(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAppendToLineS(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");

    String *tempString = stringInitialization(1);
    txtLoaderAppendToLineS(txtFileLoader, tempString, 1);
    destroyString(tempString);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[4][12] = {"oneone", "twotwo", "threethree", "fourfour"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\n");


    for (int i = 0; i < 4; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        txtLoaderAppendToLineS(txtFileLoader, line, i);
        destroyString(line);
    }

    for (int i = 0; i < 4; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAddLineC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAddLineC(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAddLineC(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");
    txtLoaderAddLineC(txtFileLoader, "", 1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[4][12] = {"one", "two", "three", "four"};
    txtLoaderWriteC(txtFileLoader, "one\nfour\n");

    txtLoaderAddLineC(txtFileLoader, "two", 1);
    txtLoaderAddLineC(txtFileLoader, "three", 2);

    for (int i = 0; i < 4; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAddLineS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAddLineS(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAddLineS(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");
    String *s = stringInitialization(1);
    txtLoaderAddLineS(txtFileLoader, s, 1);
    destroyString(s);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[4][12] = {"one", "two", "three", "four"};
    txtLoaderWriteC(txtFileLoader, "one\nfour\n");


    String *lineS = stringInitialization(5);

    stringChangeStringC(lineS, "two");
    txtLoaderAddLineS(txtFileLoader, lineS, 1);

    stringChangeStringC(lineS, "three");
    txtLoaderAddLineS(txtFileLoader, lineS, 2);

    destroyString(lineS);

    for (int i = 0; i < 4; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAddAllC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAddAllC(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAddAllC(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");

    Vector *v = vectorInitialization(1, free, NULL);
    txtLoaderAddAllC(txtFileLoader, v, 1);
    destroyVector(v);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[5][12] = {"one", "two", "three", "four", "five"};
    txtLoaderWriteC(txtFileLoader, "one\nfive\n");

    Vector *newLines = vectorInitialization(3, free, NULL);

    char *lnC = (char *) malloc(sizeof(char) * (strlen("two") + 1));
    strcpy(lnC, "two");
    vectorAdd(newLines, lnC);

    lnC = (char *) malloc(sizeof(char) * (strlen("three") + 1));
    strcpy(lnC, "three");
    vectorAdd(newLines, lnC);

    lnC = (char *) malloc(sizeof(char) * (strlen("four") + 1));
    strcpy(lnC, "four");
    vectorAdd(newLines, lnC);

    txtLoaderAddAllC(txtFileLoader, newLines, 1);

    destroyVector(newLines);

    for (int i = 0; i < 5; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderAddAllS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderAddAllS(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderAddAllS(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");

    Vector *v = vectorInitialization(1, free, NULL);
    txtLoaderAddAllS(txtFileLoader, v, 1);
    destroyVector(v);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[5][12] = {"one", "two", "three", "four", "five"};
    txtLoaderWriteC(txtFileLoader, "one\nfive\n");

    Vector *newLines = vectorInitialization(3, destroyString, NULL);

    String *lnS = stringInitialization(5);
    stringChangeStringC(lnS, "two");
    vectorAdd(newLines, lnS);

    lnS = stringInitialization(5);
    stringChangeStringC(lnS, "three");
    vectorAdd(newLines, lnS);

    lnS = stringInitialization(5);
    stringChangeStringC(lnS, "four");
    vectorAdd(newLines, lnS);

    txtLoaderAddAllS(txtFileLoader, newLines, 1);

    destroyVector(newLines);

    for (int i = 0; i < 5; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderUpdateLineC(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderUpdateLineC(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderUpdateLineC(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");

    txtLoaderUpdateLineC(txtFileLoader, "", 1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[5][12] = {"one", "two", "three", "four", "five"};
    txtLoaderWriteC(txtFileLoader, "five\nfour\nthree\ntwo\none");

    for (int i = 0; i < 5; i++)
        txtLoaderUpdateLineC(txtFileLoader, lines[i], i);

    for (int i = 0; i < 5; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderUpdateLineS(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderUpdateLineS(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    txtLoaderUpdateLineS(txtFileLoader, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    txtLoaderWriteC(txtFileLoader, "");

    String *s = stringInitialization(1);
    txtLoaderUpdateLineS(txtFileLoader, s, 1);
    destroyString(s);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[5][12] = {"one", "two", "three", "four", "five"};
    txtLoaderWriteC(txtFileLoader, "five\nfour\nthree\ntwo\none");

    for (int i = 0; i < 5; i++) {
        String *tempString = stringInitialization(6);
        stringChangeStringC(tempString, lines[i]);
        txtLoaderUpdateLineS(txtFileLoader, tempString, i);
        destroyString(tempString);
    }

    for (int i = 0; i < 5; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderRemoveLine(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderRemoveLine(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    txtLoaderWriteC(txtFileLoader, "");
    txtLoaderRemoveLine(txtFileLoader, 1);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char lines[2][6] = {"three", "five"};
    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\nfive");

    txtLoaderRemoveLine(txtFileLoader, 3);
    txtLoaderRemoveLine(txtFileLoader, 1);
    txtLoaderRemoveLine(txtFileLoader, 0);

    for (int i = 0; i < 2; i++) {
        String *line = txtLoaderReadLineS(txtFileLoader, i);
        CuAssertStrEquals(cuTest, lines[i], line->string);
        destroyString(line);
    }


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderChangeFile(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    CuAssertStrEquals(cuTest, filePath, txtFileLoader->dir);


    char *newPath = "C:/c/data/structure/and/algorithms";
    txtLoaderChangeFile(txtFileLoader, newPath);


    CuAssertStrEquals(cuTest, newPath, txtFileLoader->dir);


    destroyTxtFileLoader(txtFileLoader);

}


void testTxtLoaderClearFile(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    txtLoaderClearFile(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    txtLoaderClearFile(txtFileLoader);
    CuAssertIntEquals(cuTest, 0, txtLoaderCountLines(txtFileLoader));

    txtLoaderWriteC(txtFileLoader, "one\ntwo\nthree\nfour\nfive");
    CuAssertIntEquals(cuTest, 5, txtLoaderCountLines(txtFileLoader));

    txtLoaderClearFile(txtFileLoader);
    CuAssertIntEquals(cuTest, 0, txtLoaderCountLines(txtFileLoader));


    destroyTxtFileLoader(txtFileLoader);

}


void testDestroyTxtFileLoader(CuTest *cuTest) {

    TxtFileLoader *txtFileLoader = txtFileLoaderInitialization(filePath);

    destroyTxtFileLoader(txtFileLoader);

}


CuSuite *createTxtFileLoaderTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidTextFileLoaderInitialization);
    SUITE_ADD_TEST(suite, testValidTextFileLoaderInitialization);
    SUITE_ADD_TEST(suite, testTxtLoaderWriteC);
    SUITE_ADD_TEST(suite, testTxtLoaderWriteS);
    SUITE_ADD_TEST(suite, testTxtLoaderReadFileS);
    SUITE_ADD_TEST(suite, testTxtLoaderReadFileC);
    SUITE_ADD_TEST(suite, testTxtLoaderReadFileLines);
    SUITE_ADD_TEST(suite, testTxtLoaderReadFileWthDelimiter);
    SUITE_ADD_TEST(suite, testTxtLoaderCountLines);
    SUITE_ADD_TEST(suite, testTxtLoaderReadLineS);
    SUITE_ADD_TEST(suite, testTxtLoaderReadLineC);
    SUITE_ADD_TEST(suite, testTxtLoaderAppendC);
    SUITE_ADD_TEST(suite, testTxtLoaderAppendS);
    SUITE_ADD_TEST(suite, testTxtLoaderAppendAllC);
    SUITE_ADD_TEST(suite, testTxtLoaderAppendAllS);
    SUITE_ADD_TEST(suite, testTxtLoaderAppendToLineC);
    SUITE_ADD_TEST(suite, testTxtLoaderAppendToLineS);
    SUITE_ADD_TEST(suite, testTxtLoaderAddLineC);
    SUITE_ADD_TEST(suite, testTxtLoaderAddLineS);
    SUITE_ADD_TEST(suite, testTxtLoaderAddAllC);
    SUITE_ADD_TEST(suite, testTxtLoaderAddAllS);
    SUITE_ADD_TEST(suite, testTxtLoaderUpdateLineC);
    SUITE_ADD_TEST(suite, testTxtLoaderUpdateLineS);
    SUITE_ADD_TEST(suite, testTxtLoaderRemoveLine);
    SUITE_ADD_TEST(suite, testTxtLoaderChangeFile);
    SUITE_ADD_TEST(suite, testTxtLoaderClearFile);
    SUITE_ADD_TEST(suite, testDestroyTxtFileLoader);

    return suite;

}


void txtFileLoaderAlgUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Text File Loader Test**\n");

    CuSuite *suite = createTxtFileLoaderTestsSuite();


    createFileToBeTested();


    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}