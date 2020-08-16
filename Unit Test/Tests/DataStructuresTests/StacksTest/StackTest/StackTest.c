#include "StackTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Stacks/Headers/Stack.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerST(int integer) {
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

int compareIntPointersST(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerST(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testInvalidStackInitialization(CuTest *cuTest) {

    Stack *stack = stackInitialization(NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidStackInitialization(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    CuAssertPtrNotNull(cuTest, stack);

    destroyStack(stack);

}


void testStackPush(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    stackPush(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackPush(stack, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));

    for (int i = 0; i < stack->top + 1; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) stack->memory[i]);

    destroyStack(stack);

}


void testStackAddAll(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    stackAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackAddAll(stack, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++)
        arr[i] = generateIntPointerST(i + 1);

    stackAddAll(stack, (void **) arr, 5);

    for (int i = 0; i < stack->top + 1; i++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) stack->memory[i]);


    free(arr);
    destroyStack(stack);

}


void testStackPop(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    stackPop(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackPop(stack);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));

    int currentValue = 50;

    while (stack->top != -1) {
        currentValue -= 10;
        int *currentItem = stackPop(stack);
        CuAssertIntEquals(cuTest, currentValue, *currentItem);
        free(currentItem);
    }

    destroyStack(stack);

}


void testStackPeek(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    stackPeek(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackPeek(stack);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);

    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));

    int currentValue = 50;

    while (stack->top != -1) {
        currentValue -= 10;
        int *currentItem = stackPeek(stack);
        CuAssertIntEquals(cuTest, currentValue, *currentItem);
        CuAssertIntEquals(cuTest, currentValue, *(int *) stackPop(stack));
        free(currentItem);
    }

    destroyStack(stack);

}


void testStackIsEmpty(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    stackIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, stackIsEmpty(stack));

    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));

    CuAssertIntEquals(cuTest, 0, stackIsEmpty(stack));

    while (!stackIsEmpty(stack))
        free(stackPop(stack));

    CuAssertIntEquals(cuTest, 1, stackIsEmpty(stack));

    destroyStack(stack);

}


void testStackToArray(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    stackToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));

    int **arr = (int **) stackToArray(stack);

    for (int i = 0; i < stackGetLength(stack); i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *arr[i]);


    free(arr);
    destroyStack(stack);

}


void testStackGetLength(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    stackGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, stackGetLength(stack));

    stackPush(stack, generateIntPointerST(10));
    CuAssertIntEquals(cuTest, 1, stackGetLength(stack));

    stackPush(stack, generateIntPointerST(20));
    CuAssertIntEquals(cuTest, 2, stackGetLength(stack));

    stackPush(stack, generateIntPointerST(30));
    CuAssertIntEquals(cuTest, 3, stackGetLength(stack));

    stackPush(stack, generateIntPointerST(40));
    CuAssertIntEquals(cuTest, 4, stackGetLength(stack));

    while (stackGetLength(stack) != 0)
        free(stackPop(stack));

    destroyStack(stack);

}


void testStackContains(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);
    int tempValue;

    stackContains(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackContains(stack, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    stackContains(stack, &tempValue, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));


    for (int i = 0; i < stackGetLength(stack); i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, 1, stackContains(stack, &tempValue, compareIntPointersST));
    }


    tempValue = 100;
    CuAssertIntEquals(cuTest, 0, stackContains(stack, &tempValue, compareIntPointersST));

    destroyStack(stack);

}


void testStackEquals(CuTest *cuTest) {

    Stack *stack1 = stackInitialization(free);
    Stack *stack2 = stackInitialization(free);

    stackEquals(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackEquals(stack1, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    stackEquals(stack1, stack2, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    stackPush(stack1, generateIntPointerST(10));
    stackPush(stack1, generateIntPointerST(20));
    stackPush(stack1, generateIntPointerST(30));
    stackPush(stack1, generateIntPointerST(40));

    stackPush(stack2, generateIntPointerST(10));
    stackPush(stack2, generateIntPointerST(20));
    stackPush(stack2, generateIntPointerST(30));
    stackPush(stack2, generateIntPointerST(40));

    CuAssertIntEquals(cuTest, 1, stackEquals(stack1, stack2, compareIntPointersST));

    int *tempValue = stackPop(stack2);
    CuAssertIntEquals(cuTest, 0, stackEquals(stack1, stack2, compareIntPointersST));

    *tempValue = 100;
    stackPush(stack2, tempValue);

    CuAssertIntEquals(cuTest, 0, stackEquals(stack1, stack2, compareIntPointersST));

    destroyStack(stack1);
    destroyStack(stack2);

}


void testClearStack(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    clearStack(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, stackGetLength(stack));

    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));
    CuAssertIntEquals(cuTest, 4, stackGetLength(stack));


    clearStack(stack);
    CuAssertIntEquals(cuTest, 0, stackGetLength(stack));

    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));

    CuAssertIntEquals(cuTest, 2, stackGetLength(stack));

    clearStack(stack);
    CuAssertIntEquals(cuTest, 0, stackGetLength(stack));

    destroyStack(stack);

}


void testDestroyStack(CuTest *cuTest) {

    Stack *stack = stackInitialization(free);

    destroyStack(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    stackPush(stack, generateIntPointerST(10));
    stackPush(stack, generateIntPointerST(20));
    stackPush(stack, generateIntPointerST(30));
    stackPush(stack, generateIntPointerST(40));

    destroyStack(stack);

}


typedef struct StackTestStruct {

    int iData;
    char *cData;

} StackTestStruct;


void freeStackTestStruct(void *item) {
    StackTestStruct *s = (StackTestStruct *) item;
    free(s->cData);
    free(s);
}


int stackTestStructComp(const void *item1, const void *item2) {
    StackTestStruct *s1 = (StackTestStruct *) item1;
    StackTestStruct *s2 = (StackTestStruct *) item2;

    int iDataFlag = s1->iData == s2->iData;
    int cDataFlag = strcmp(s1->cData, s2->cData);

    return !iDataFlag || cDataFlag;

}


StackTestStruct *generateStackTestStruct(int value, char *str) {

    StackTestStruct *s = (StackTestStruct *) malloc(sizeof(StackTestStruct));
    s->cData = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(s->cData, str);

    s->iData = value;

    return s;

}


void generalStackTest(CuTest *cuTest) {

    Stack *stack = stackInitialization(freeStackTestStruct);
    char numbersStr[14][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen", "fourteen"};


    CuAssertIntEquals(cuTest, 0, stackGetLength(stack));
    CuAssertIntEquals(cuTest, 1, stackIsEmpty(stack));

    stackPush(stack, generateStackTestStruct(1, "one"));
    stackPush(stack, generateStackTestStruct(2, "two"));
    stackPush(stack, generateStackTestStruct(3, "three"));

    CuAssertIntEquals(cuTest, 3, stackGetLength(stack));
    CuAssertIntEquals(cuTest, 0, stackIsEmpty(stack));

    CuAssertIntEquals(cuTest, 3, ((StackTestStruct *) stackPeek(stack))->iData);
    CuAssertStrEquals(cuTest, "three", ((StackTestStruct *) stackPeek(stack))->cData);

    StackTestStruct **structArr = (StackTestStruct **) malloc(sizeof(StackTestStruct *) * 11);
    for (int i = 0; i < 11; i++)
        structArr[i] = generateStackTestStruct(i + 4, numbersStr[i + 3]);

    stackAddAll(stack, (void **) structArr, 11);

    CuAssertIntEquals(cuTest, 14, stackGetLength(stack));

    StackTestStruct **stackArr = (StackTestStruct **) stackToArray(stack);
    for (int i = 0; i < stackGetLength(stack); i++) {
        CuAssertIntEquals(cuTest, i + 1, stackArr[i]->iData);
        CuAssertStrEquals(cuTest, numbersStr[i], stackArr[i]->cData);
    }

    while (!stackIsEmpty(stack)) {
        StackTestStruct *currentItem = stackPop(stack);
        CuAssertIntEquals(cuTest, stackGetLength(stack) + 1, currentItem->iData);
        CuAssertStrEquals(cuTest, numbersStr[stackGetLength(stack)], currentItem->cData);

        freeStackTestStruct(currentItem);

    }


    free(structArr);
    free(stackArr);
    destroyStack(stack);

}


CuSuite *createStackTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidStackInitialization);
    SUITE_ADD_TEST(suite, testValidStackInitialization);
    SUITE_ADD_TEST(suite, testStackPush);
    SUITE_ADD_TEST(suite, testStackAddAll);
    SUITE_ADD_TEST(suite, testStackPop);
    SUITE_ADD_TEST(suite, testStackPeek);
    SUITE_ADD_TEST(suite, testStackIsEmpty);
    SUITE_ADD_TEST(suite, testStackToArray);
    SUITE_ADD_TEST(suite, testStackGetLength);
    SUITE_ADD_TEST(suite, testStackContains);
    SUITE_ADD_TEST(suite, testStackEquals);
    SUITE_ADD_TEST(suite, testClearStack);
    SUITE_ADD_TEST(suite, testDestroyStack);

    SUITE_ADD_TEST(suite, generalStackTest);

    return suite;

}


void stackUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Stack Test**\n");

    CuSuite *suite = createStackTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}
