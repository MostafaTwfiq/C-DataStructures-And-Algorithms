#include "ArrayListTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../DataStructure/Lists/Headers/ArrayList.h"
#include "../../../../../System/Utils.h"


int arrayListTestStrcmp(const void *c1, const void *c2) {
    return strcmp(c1, c2);
}


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerALT(int integer) {
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

int compareIntPointersALT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerALT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


void testArrayListInvalidInitialization(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(-1, free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrayList = arrayListInitialization(1, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}

void testArrayListProperInitialization(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);
    CuAssertPtrNotNull(cuTest, arrayList);

    destroyArrayList(arrayList);
}

void testArrayListAddFun(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListAdd(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListAdd(arrayList, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrayListAdd(arrayList, generateIntPointerALT(10));
    arrayListAdd(arrayList, generateIntPointerALT(20));
    arrayListAdd(arrayList, generateIntPointerALT(30));
    CuAssertIntEquals(cuTest, 3, arrayList->count);


    for (int i = 0; i < arrayList->count; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) arrayList->arr[i]);


    destroyArrayList(arrayList);

}

void testArrayListAddAtIndexFun(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, arrayListTestStrcmp);

    arrayListAddAtIndex(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListAddAtIndex(arrayList, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempVal = 10;
    arrayListAddAtIndex(arrayList, &tempVal, 1);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    arrayListAdd(arrayList, generateCharPointerALT("0"));
    arrayListAddAtIndex(arrayList, generateCharPointerALT("30"), 0);
    arrayListAddAtIndex(arrayList, generateCharPointerALT("20"), 1);
    arrayListAddAtIndex(arrayList, generateCharPointerALT("10"), 2);
    CuAssertIntEquals(cuTest, 4, arrayList->count);

    //arr:  "30", "20", "10", "0"
    //index: 0,  1,  2, 3

    CuAssertStrEquals(cuTest, "30", (char *) arrayList->arr[0]);
    CuAssertStrEquals(cuTest, "20", (char *) arrayList->arr[1]);
    CuAssertStrEquals(cuTest, "10", (char *) arrayList->arr[2]);
    CuAssertStrEquals(cuTest, "0", (char *) arrayList->arr[3]);

    destroyArrayList(arrayList);

}

void testArrayListAddAll(CuTest *cuTest) {

    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);


    arrayListAddAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListAddAll(arrayList, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int **valuesArr = (int **) malloc(sizeof(int *) * 3);

    for (int i = 1; i <= 3; i++) {
        valuesArr[i - 1] = malloc(sizeof(int));
        *valuesArr[i - 1] = (i + 6) * 10;
    }
    // valuesArr = [70, 80, 90]

    arrayListAddAll(arrayList, (void **) valuesArr, 3);
    CuAssertIntEquals(cuTest, 3, arrayList->count);

    for (int i = arrayList->count - 1, index = 2; i > arrayList->count - 4; i--, index--)
        CuAssertIntEquals(cuTest, *(int *) valuesArr[index], *(int *) arrayList->arr[i]);


    free(valuesArr);
    destroyArrayList(arrayList);

}


void testArrayListRemove(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListRemove(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListAdd(arrayList, generateIntPointerALT(10));

    arrayListRemove(arrayList);

    CuAssertIntEquals(cuTest, 0, arrayList->count);

    destroyArrayList(arrayList);

}


void testArrayListRemoveWtoFr(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListRemoveWtFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    int *currentItem;
    arrayListAdd(arrayList, generateIntPointerALT(10));

    currentItem = arrayListRemoveWtFr(arrayList);

    CuAssertIntEquals(cuTest, 0, arrayList->count);
    CuAssertIntEquals(cuTest, 10, *currentItem);

    free(currentItem);
    destroyArrayList(arrayList);

}


void testArrayListRemoveAtIndex(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListRemoveAtIndex(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListRemoveAtIndex(arrayList, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    arrayListAdd(arrayList, generateIntPointerALT(10));
    arrayListAdd(arrayList, generateIntPointerALT(20));
    arrayListAdd(arrayList, generateIntPointerALT(100));
    arrayListAdd(arrayList, generateIntPointerALT(30));
    arrayListAdd(arrayList, generateIntPointerALT(200));
    arrayListAdd(arrayList, generateIntPointerALT(40));
    arrayListAdd(arrayList, generateIntPointerALT(300));
    arrayListAdd(arrayList, generateIntPointerALT(50));

    arrayListRemoveAtIndex(arrayList, 2);
    arrayListRemoveAtIndex(arrayList, 3);
    arrayListRemoveAtIndex(arrayList, 4);

    CuAssertIntEquals(cuTest, 5, arrayList->count);

    for (int i = 0; i < arrayList->count; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) arrayList->arr[i]);

    destroyArrayList(arrayList);

}


void testArrayListRemoveAtIndexWtoFr(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListRemoveAtIndexWtFr(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListRemoveAtIndexWtFr(arrayList, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    arrayListAddAll(arrayList, (void **) arr, 5);

    int *tempPointer1 = arrayListRemoveAtIndexWtFr(arrayList, 4);
    int *tempPointer2 = arrayListRemoveAtIndexWtFr(arrayList, 0);

    CuAssertIntEquals(cuTest, 3, arrayList->count);

    for (int i = 0; i < arrayList->count; i++)
        CuAssertIntEquals(cuTest, (i + 2) * 10, *(int *) arrayList->arr[i]);


    CuAssertIntEquals(cuTest, 10, *tempPointer2);
    CuAssertIntEquals(cuTest, 50, *tempPointer1);

    free(tempPointer1);
    free(tempPointer2);
    free(arr);
    destroyArrayList(arrayList);

}


void testArrayListExpansion(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    CuAssertIntEquals(cuTest, 1, arrayList->length);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50
    arrayListAdd(arrayList, arr[0]);
    arrayListAdd(arrayList, arr[1]);
    CuAssertIntEquals(cuTest, 2, arrayList->length);
    arrayListAdd(arrayList, arr[2]);
    CuAssertIntEquals(cuTest, 3, arrayList->length);
    arrayListAdd(arrayList, arr[3]);
    arrayListAdd(arrayList, arr[4]);
    CuAssertIntEquals(cuTest, 5, arrayList->length);


    free(arr);
    destroyArrayList(arrayList);

}


void testArrayListContains(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListContains(arrayList, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    arrayListAddAll(arrayList, (void **) arr, 5);

    int tempValue;
    for (int i = 0; i < 5; i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, 1, arrayListContains(arrayList, &tempValue));
    }

    tempValue = 60;
    CuAssertIntEquals(cuTest, 0, arrayListContains(arrayList, &tempValue));


    free(arr);
    destroyArrayList(arrayList);

}


void testArrayListGetIndex(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListGetIndex(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListGetIndex(arrayList, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    arrayListAddAll(arrayList, (void **) arr, 5);

    int tempValue;
    for (int i = 0; i < 5; i++) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, i, arrayListGetIndex(arrayList, &tempValue));
    }

    tempValue = 60;
    CuAssertIntEquals(cuTest, -1, arrayListGetIndex(arrayList, &tempValue));


    free(arr);
    destroyArrayList(arrayList);

}


void testArrayListGetLastIndex(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListGetLastIndex(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListGetLastIndex(arrayList, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 6);
    for (int i = 0; i < 6; i += 2) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;

        arr[i + 1] = (int *) malloc(sizeof(int));
        *arr[i + 1] = (i + 1) * 10;

    }

    // 10, 10, 30, 30, 70, 70

    arrayListAddAll(arrayList, (void **) arr, 6);

    int tempValue;
    for (int i = 0; i < 6; i += 2) {
        tempValue = (i + 1) * 10;
        CuAssertIntEquals(cuTest, i + 1, arrayListGetLastIndex(arrayList, &tempValue));
    }

    tempValue = 100;
    CuAssertIntEquals(cuTest, -1, arrayListGetLastIndex(arrayList, &tempValue));


    free(arr);
    destroyArrayList(arrayList);

}


void testArrayListGet(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListGet(NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListGet(arrayList, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    arrayListAddAll(arrayList, (void **) arr, 5);

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) arrayListGet(arrayList, i));


    free(arr);
    destroyArrayList(arrayList);

}


void testArrayListToArray(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 5);
    for (int i = 0; i < 5; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50

    arrayListAddAll(arrayList, (void **) arr, 5);

    int **generatedArr = (int **) arrayListToArray(arrayList);
    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) generatedArr[i]);


    free(arr);
    free(generatedArr);
    destroyArrayList(arrayList);

}


void testArrayListToSubArray(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListToSubArray(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListToSubArray(arrayList, -10, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    arrayListToSubArray(arrayList, 0, 1);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50, 60, 70, 80, 90, 100

    arrayListAddAll(arrayList, (void **) arr, 10);

    int **generatedArr = (int **) arrayListToSubArray(arrayList, 3, 8);
    for (int i = 0; i < 6; i++)
        CuAssertIntEquals(cuTest, (i + 4) * 10, *(int *) generatedArr[i]);


    free(arr);
    free(generatedArr);
    destroyArrayList(arrayList);

}


int sortTestComparatorFunALT(const void *i1, const void *i2) {
    return **(int **) i1 - **(int **) i2;
}


void testArrayListSort(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListSort(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListSort(arrayList, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    arrayListAdd(arrayList, generateIntPointerALT(30));
    arrayListAdd(arrayList, generateIntPointerALT(20));
    arrayListAdd(arrayList, generateIntPointerALT(10));
    arrayListAdd(arrayList, generateIntPointerALT(50));
    arrayListAdd(arrayList, generateIntPointerALT(40));
    //arrayList before sort: 30, 20, 10, 50, 40

    arrayListSort(arrayList, sortTestComparatorFunALT);
    //arrayList after sort: 10, 20, 30, 40, 50

    for (int i = 0; i < 5; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) arrayList->arr[i]);


    destroyArrayList(arrayList);

}


ArrayList *printingArrayList;

void printFunTestALT(const void *item) {
    arrayListAdd(printingArrayList, (void *) item);
}

void testArrayListPrintFun(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListToSubArray(NULL, 0, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListToSubArray(arrayList, -10, 0);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    arrayListToSubArray(arrayList, 0, 1);
    CuAssertIntEquals(cuTest, OUT_OF_RANGE, ERROR_TEST->errorCode);

    int **arr = (int **) malloc(sizeof(int *) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        *arr[i] = (i + 1) * 10;
    }

    // 10, 20, 30, 40, 50, 60, 70, 80, 90, 100

    arrayListAddAll(arrayList, (void **) arr, 10);

    printingArrayList = arrayListInitialization(10, free, NULL);

    printArrayList(arrayList, printFunTestALT);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, (i + 1) * 10, *(int *) printingArrayList->arr[i]);

    printingArrayList->count = 0;

    free(arr);
    destroyArrayList(printingArrayList);
    destroyArrayList(arrayList);

}


void testArrayListGetLength(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, arrayListGetLength(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(30));
    CuAssertIntEquals(cuTest, 1, arrayListGetLength(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(20));
    CuAssertIntEquals(cuTest, 2, arrayListGetLength(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(10));
    CuAssertIntEquals(cuTest, 3, arrayListGetLength(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(50));
    CuAssertIntEquals(cuTest, 4, arrayListGetLength(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(40));
    CuAssertIntEquals(cuTest, 5, arrayListGetLength(arrayList));


    destroyArrayList(arrayList);

}


void testArrayListIsEmpty(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    arrayListIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, arrayListIsEmpty(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(30));
    CuAssertIntEquals(cuTest, 0, arrayListIsEmpty(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(20));
    CuAssertIntEquals(cuTest, 0, arrayListIsEmpty(arrayList));

    arrayListRemove(arrayList);
    CuAssertIntEquals(cuTest, 0, arrayListIsEmpty(arrayList));

    arrayListRemove(arrayList);
    CuAssertIntEquals(cuTest, 1, arrayListIsEmpty(arrayList));

    arrayListAdd(arrayList, generateIntPointerALT(30));
    clearArrayList(arrayList);
    CuAssertIntEquals(cuTest, 1, arrayListIsEmpty(arrayList));

    destroyArrayList(arrayList);

}


void testClearArrayList(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    clearArrayList(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    clearArrayList(arrayList);
    CuAssertIntEquals(cuTest, 0, arrayList->count);

    arrayListAdd(arrayList, generateIntPointerALT(30));
    arrayListAdd(arrayList, generateIntPointerALT(20));

    CuAssertIntEquals(cuTest, 2, arrayList->count);

    clearArrayList(arrayList);
    CuAssertIntEquals(cuTest, 0, arrayList->count);

    destroyArrayList(arrayList);

}


void testDestroyArrayList(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(1, free, compareIntPointersALT);

    destroyArrayList(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    arrayListAdd(arrayList, generateIntPointerALT(30));
    arrayListAdd(arrayList, generateIntPointerALT(20));

    destroyArrayList(arrayList);

}


typedef struct ArrayListTestStruct {

    int iData;
    char *cData;

} ArrayListTestStruct;

void freeArrayListTestStruct(void *item) {
    ArrayListTestStruct *a = (ArrayListTestStruct *) item;
    free(a->cData);
    free(a);
}


int arrayListTestStructComp(const void *item1, const void *item2) {
    ArrayListTestStruct *a1 = (ArrayListTestStruct *) item1;
    ArrayListTestStruct *a2 = (ArrayListTestStruct *) item2;

    int iDataFlag = a1->iData == a2->iData;
    int cDataFlag = strcmp(a1->cData, a2->cData);

    return !iDataFlag || cDataFlag;

}


void generalArrayListTest(CuTest *cuTest) {
    ArrayList *arrayList = arrayListInitialization(5, freeArrayListTestStruct, arrayListTestStructComp);
    char numbersStr[10][6] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};
    ArrayListTestStruct *item;

    CuAssertIntEquals(cuTest, 1, arrayListIsEmpty(arrayList));

    item = (ArrayListTestStruct *) malloc(sizeof(ArrayListTestStruct));
    item->iData = 1;
    item->cData = (char *) malloc(sizeof(char) * (strlen("one") + 1));
    strcpy(item->cData, "one");
    arrayListAdd(arrayList, item);

    item = (ArrayListTestStruct *) malloc(sizeof(ArrayListTestStruct));
    item->iData = 3;
    item->cData = (char *) malloc(sizeof(char) * (strlen("three") + 1));
    strcpy(item->cData, "three");
    arrayListAdd(arrayList, item);

    item = (ArrayListTestStruct *) malloc(sizeof(ArrayListTestStruct));
    item->iData = 2;
    item->cData = (char *) malloc(sizeof(char) * (strlen("two") + 1));
    strcpy(item->cData, "two");
    arrayListAddAtIndex(arrayList, item, 1);

    CuAssertIntEquals(cuTest, 3, arrayListGetLength(arrayList));

    ArrayListTestStruct **itemsArr = (ArrayListTestStruct **) malloc(sizeof(ArrayListTestStruct *) * 3);

    item = (ArrayListTestStruct *) malloc(sizeof(ArrayListTestStruct));
    item->iData = 4;
    item->cData = (char *) malloc(sizeof(char) * (strlen("four") + 1));
    strcpy(item->cData, "four");
    itemsArr[0] = item;

    item = (ArrayListTestStruct *) malloc(sizeof(ArrayListTestStruct));
    item->iData = 5;
    item->cData = (char *) malloc(sizeof(char) * (strlen("five") + 1));
    strcpy(item->cData, "five");
    itemsArr[1] = item;

    item = (ArrayListTestStruct *) malloc(sizeof(ArrayListTestStruct));
    item->iData = 6;
    item->cData = (char *) malloc(sizeof(char) * (strlen("six") + 1));
    strcpy(item->cData, "six");
    itemsArr[2] = item;

    arrayListAddAll(arrayList, (void **) itemsArr, 3);

    CuAssertIntEquals(cuTest, 6, arrayListGetLength(arrayList));

    for (int i = 0; i < arrayListGetLength(arrayList); i++) {
        item = (ArrayListTestStruct *) arrayListGet(arrayList, i);
        CuAssertIntEquals(cuTest, i + 1, item->iData);
        CuAssertStrEquals(cuTest, numbersStr[i], item->cData);
        CuAssertIntEquals(cuTest, i, arrayListGetIndex(arrayList, item));
        CuAssertIntEquals(cuTest, i, arrayListGetLastIndex(arrayList, item));
    }

    CuAssertIntEquals(cuTest, 0, arrayListIsEmpty(arrayList));

    for (int i = 0; i < arrayListGetLength(arrayList);) {
        item = (ArrayListTestStruct *) arrayListGet(arrayList, i);
        CuAssertIntEquals(cuTest, 1, arrayListContains(arrayList, item));
        arrayListRemoveAtIndexWtFr(arrayList, i);
        CuAssertIntEquals(cuTest, 0, arrayListContains(arrayList, item));

        freeArrayListTestStruct(item);
    }

    clearArrayList(arrayList);

    free(itemsArr);
    destroyArrayList(arrayList);

}


CuSuite *createArrayListTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testArrayListInvalidInitialization);
    SUITE_ADD_TEST(suite, testArrayListProperInitialization);
    SUITE_ADD_TEST(suite, testArrayListAddFun);
    SUITE_ADD_TEST(suite, testArrayListAddAtIndexFun);
    SUITE_ADD_TEST(suite, testArrayListAddAll);
    SUITE_ADD_TEST(suite, testArrayListRemove);
    SUITE_ADD_TEST(suite, testArrayListRemoveWtoFr);
    SUITE_ADD_TEST(suite, testArrayListRemoveAtIndex);
    SUITE_ADD_TEST(suite, testArrayListRemoveAtIndexWtoFr);
    SUITE_ADD_TEST(suite, testArrayListExpansion);
    SUITE_ADD_TEST(suite, testArrayListContains);
    SUITE_ADD_TEST(suite, testArrayListGetIndex);
    SUITE_ADD_TEST(suite, testArrayListGetLastIndex);
    SUITE_ADD_TEST(suite, testArrayListGet);
    SUITE_ADD_TEST(suite, testArrayListToArray);
    SUITE_ADD_TEST(suite, testArrayListToSubArray);
    SUITE_ADD_TEST(suite, testArrayListSort);
    SUITE_ADD_TEST(suite, testArrayListPrintFun);
    SUITE_ADD_TEST(suite, testArrayListGetLength);
    SUITE_ADD_TEST(suite, testArrayListIsEmpty);
    SUITE_ADD_TEST(suite, testClearArrayList);
    SUITE_ADD_TEST(suite, testDestroyArrayList);

    SUITE_ADD_TEST(suite, generalArrayListTest);

    return suite;

}


void arrayListUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Array List Test**\n");

    CuSuite *suite = createArrayListTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}