#include "DLinkedListStackTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Stacks/Headers/DLinkedListStack.h"
#include "../../../../../DataStructure/LinkedLists/Headers/DoublyLinkedList.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerDLST(int integer) {
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

int compareIntPointersDLST(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerDLST(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidDLStackInitialization(CuTest *cuTest) {
    DLinkedListStack *dlStack = dlStackInitialization(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidDLStackInitialization(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    CuAssertPtrNotNull(cuTest, dlStack);

    destroyDLStack(dlStack);

}


void testDLStackPush(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    dlStackPush(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackPush(dlStack, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));

    for (int i = 0; i < dlStackGetLength(dlStack); i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) doublyLinkedListGet(dlStack->linkedList, i));

    destroyDLStack(dlStack);

}


void testDLStackAddAll(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    dlStackAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackAddAll(dlStack, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
        arr[i] = generateIntPointerDLST(i + 1);

    dlStackAddAll(dlStack, (void **) arr, 5);

    for (int i = 0; i < dlStackGetLength(dlStack); i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) doublyLinkedListGet(dlStack->linkedList, i));


    free(arr);
    destroyDLStack(dlStack);

}


void testDLStackPop(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    dlStackPop(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackPop(dlStack);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));

    int currentValue = 50;

    while (!dlStackIsEmpty(dlStack)) {
        currentValue -= 10;
        int *currentItem = dlStackPop(dlStack);
        CuAssertIntEquals(cuTest, currentValue, *currentItem);
        free(currentItem);
    }

    destroyDLStack(dlStack);

}


void testDLStackPeek(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    dlStackPeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackPeek(dlStack);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));

    int currentValue = 50;

    while (!dlStackIsEmpty(dlStack)) {
        currentValue -= 10;
        int *currentItem = dlStackPeek(dlStack);
        CuAssertIntEquals(cuTest, currentValue, *currentItem);
        CuAssertIntEquals(cuTest, currentValue, *(int *) dlStackPop(dlStack));
        free(currentItem);
    }

    destroyDLStack(dlStack);

}


void testDLStackIsEmpty(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    dlStackIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, dlStackIsEmpty(dlStack));

    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));

    CuAssertIntEquals(cuTest, 0, dlStackIsEmpty(dlStack));

    while (!dlStackIsEmpty(dlStack))
        free(dlStackPop(dlStack));

    CuAssertIntEquals(cuTest, 1, dlStackIsEmpty(dlStack));

    destroyDLStack(dlStack);

}


void testDLStackToArray(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    dlStackToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));

    int **arr = (int **) dlStackToArray(dlStack);

    for (int i = 0; i < dlStackGetLength(dlStack); i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *arr[i]);


    free(arr);
    destroyDLStack(dlStack);

}


void testDLStackGetLength(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    dlStackGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, dlStackGetLength(dlStack));

    dlStackPush(dlStack, generateIntPointerDLST(10));
    CuAssertIntEquals(cuTest, 1, dlStackGetLength(dlStack));

    dlStackPush(dlStack, generateIntPointerDLST(20));
    CuAssertIntEquals(cuTest, 2, dlStackGetLength(dlStack));

    dlStackPush(dlStack, generateIntPointerDLST(30));
    CuAssertIntEquals(cuTest, 3, dlStackGetLength(dlStack));

    dlStackPush(dlStack, generateIntPointerDLST(40));
    CuAssertIntEquals(cuTest, 4, dlStackGetLength(dlStack));

    while (dlStackGetLength(dlStack) != 0)
        free(dlStackPop(dlStack));

    destroyDLStack(dlStack);

}


void testDLStackContains(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);
    int tempValue;

    dlStackContains(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackContains(dlStack, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dlStackContains(dlStack, &tempValue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));


    for (int i = 0; i < dlStackGetLength(dlStack); i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, 1, dlStackContains(dlStack, &tempValue, compareIntPointersDLST));
    }


    tempValue = 100;
    CuAssertIntEquals(cuTest, 0, dlStackContains(dlStack, &tempValue, compareIntPointersDLST));

    destroyDLStack(dlStack);

}


void testDLStackEquals(CuTest *cuTest) {

    DLinkedListStack *dlStack1 = dlStackInitialization(free);
    DLinkedListStack *dlStack2 = dlStackInitialization(free);

    dlStackEquals(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackEquals(dlStack1, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dlStackEquals(dlStack1, dlStack2, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dlStackPush(dlStack1, generateIntPointerDLST(10));
    dlStackPush(dlStack1, generateIntPointerDLST(20));
    dlStackPush(dlStack1, generateIntPointerDLST(30));
    dlStackPush(dlStack1, generateIntPointerDLST(40));

    dlStackPush(dlStack2, generateIntPointerDLST(10));
    dlStackPush(dlStack2, generateIntPointerDLST(20));
    dlStackPush(dlStack2, generateIntPointerDLST(30));
    dlStackPush(dlStack2, generateIntPointerDLST(40));

    CuAssertIntEquals(cuTest, 1, dlStackEquals(dlStack1, dlStack2, compareIntPointersDLST));

    int *tempValue = dlStackPop(dlStack2);
    CuAssertIntEquals(cuTest, 0, dlStackEquals(dlStack1, dlStack2, compareIntPointersDLST));

    *tempValue = 100;
    dlStackPush(dlStack2, tempValue);

    CuAssertIntEquals(cuTest, 0, dlStackEquals(dlStack1, dlStack2, compareIntPointersDLST));

    destroyDLStack(dlStack1);
    destroyDLStack(dlStack2);

}


void testClearDLStack(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    clearDLStack(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, dlStackGetLength(dlStack));

    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));
    CuAssertIntEquals(cuTest, 4, dlStackGetLength(dlStack));


    clearDLStack(dlStack);
    CuAssertIntEquals(cuTest, 0, dlStackGetLength(dlStack));

    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));

    CuAssertIntEquals(cuTest, 2, dlStackGetLength(dlStack));

    clearDLStack(dlStack);
    CuAssertIntEquals(cuTest, 0, dlStackGetLength(dlStack));

    clearDLStack(dlStack);

}


void testDestroyDLStack(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(free);

    destroyDLStack(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dlStackPush(dlStack, generateIntPointerDLST(10));
    dlStackPush(dlStack, generateIntPointerDLST(20));
    dlStackPush(dlStack, generateIntPointerDLST(30));
    dlStackPush(dlStack, generateIntPointerDLST(40));

    destroyDLStack(dlStack);

}


typedef struct DLStackTestStruct {

    int iData;
    char *cData;

} DLStackTestStruct;


void freeDLStackTestStruct(void *item) {
    DLStackTestStruct *s = (DLStackTestStruct *) item;
    free(s->cData);
    free(s);
}


int dlStackTestStructComp(const void *item1, const void *item2) {
    DLStackTestStruct *s1 = (DLStackTestStruct *) item1;
    DLStackTestStruct *s2 = (DLStackTestStruct *) item2;

    int iDataFlag = s1->iData == s2->iData;
    int cDataFlag = strcmp(s1->cData, s2->cData);

    return !iDataFlag || cDataFlag;

}


DLStackTestStruct *generateDLStackTestStruct(int value, char *str) {

    DLStackTestStruct *s = (DLStackTestStruct *) malloc(sizeof(DLStackTestStruct));
    s->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(s->cData, str);

    s->iData = value;

    return s;

}


void generalDLStackTest(CuTest *cuTest) {

    DLinkedListStack *dlStack = dlStackInitialization(freeDLStackTestStruct);
    char numbersStr[10][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};


    CuAssertIntEquals(cuTest, 0, dlStackGetLength(dlStack));
    CuAssertIntEquals(cuTest, 1, dlStackIsEmpty(dlStack));

    dlStackPush(dlStack, generateDLStackTestStruct(1, "one"));
    dlStackPush(dlStack, generateDLStackTestStruct(2, "two"));
    dlStackPush(dlStack, generateDLStackTestStruct(3, "three"));

    CuAssertIntEquals(cuTest, 3, dlStackGetLength(dlStack));
    CuAssertIntEquals(cuTest, 0, dlStackIsEmpty(dlStack));

    CuAssertIntEquals(cuTest, 3, ((DLStackTestStruct *) dlStackPeek(dlStack))->iData);
    CuAssertStrEquals(cuTest, "three", ((DLStackTestStruct *) dlStackPeek(dlStack))->cData);

    DLStackTestStruct **structArr = (DLStackTestStruct **) malloc(sizeof(DLStackTestStruct *) * 3);
    for (int i = 0; i < 3; i++)
        structArr[i] = generateDLStackTestStruct(i + 4, numbersStr[i + 3]);

    dlStackAddAll(dlStack, (void **) structArr, 3);

    CuAssertIntEquals(cuTest, 6, dlStackGetLength(dlStack));

    DLStackTestStruct **dlStackArr = (DLStackTestStruct **) dlStackToArray(dlStack);
    for (int i = 0; i < dlStackGetLength(dlStack); i++) {
        CuAssertIntEquals(cuTest, i + 1, dlStackArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i], dlStackArr[i]->cData);
    }

    while (!dlStackIsEmpty(dlStack)) {
        DLStackTestStruct *currentItem = dlStackPop(dlStack);
        CuAssertIntEquals(cuTest, dlStackGetLength(dlStack) + 1, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[dlStackGetLength(dlStack)], currentItem->cData);

        freeDLStackTestStruct(currentItem);

    }


    free(structArr);
    free(dlStackArr);
    destroyDLStack(dlStack);

}


CuSuite *createDLinkedListStackTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidDLStackInitialization);
    SUITE_ADD_TEST(suite, testValidDLStackInitialization);
    SUITE_ADD_TEST(suite, testDLStackPush);
    SUITE_ADD_TEST(suite, testDLStackAddAll);
    SUITE_ADD_TEST(suite, testDLStackPop);
    SUITE_ADD_TEST(suite, testDLStackPeek);
    SUITE_ADD_TEST(suite, testDLStackIsEmpty);
    SUITE_ADD_TEST(suite, testDLStackToArray);
    SUITE_ADD_TEST(suite, testDLStackGetLength);
    SUITE_ADD_TEST(suite, testDLStackContains);
    SUITE_ADD_TEST(suite, testDLStackEquals);
    SUITE_ADD_TEST(suite, testClearDLStack);
    SUITE_ADD_TEST(suite, testDestroyDLStack);

    SUITE_ADD_TEST(suite, generalDLStackTest);

    return suite;

}


void doublyLinkedListStackUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Doubly Linked List stack Test**\n");

    CuSuite *suite = createDLinkedListStackTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}
