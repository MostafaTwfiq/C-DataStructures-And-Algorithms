#include "BinaryHeapTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Trees/Headers/BinaryHeap.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 *
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerBHT(int integer) {
    int *newInt = (int *) malloc(sizeof(int));

    *newInt = integer;
    return newInt;

}


/** This function will compare to integers pointers,
 * then it will return zero if they are equal, negative number if the second integer is bigger,
 * and positive number if the first integer is bigger.
 *
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is bigger, and positive number if the first integer is bigger.
 */

int compareIntPointersBHT1(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will compare to integers pointers,
 * then it will return zero if they are equal, negative number if the second integer is smaller,
 * and positive number if the first integer is smaller.
 *
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is smaller, and positive number if the first integer is smaller.
 */

int compareIntPointersBHT2(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}


int isValidBinaryHeap(void **arr, int currentIndex, int length, int (*cmp)(const void *, const void *)) {

    if (currentIndex >= length)
        return 1;


    int fChildIndex = currentIndex * 2 + 1;
    int sChildIndex = currentIndex * 2 + 2;

    if ((fChildIndex < length && cmp(arr[currentIndex], arr[fChildIndex]) < 0)
        || (sChildIndex < length && cmp(arr[currentIndex], arr[sChildIndex]) < 0)) {

        return 0;

    }


    return isValidBinaryHeap(arr, fChildIndex, length, cmp) && isValidBinaryHeap(arr, sChildIndex, length, cmp);

}


void testInvalidBinaryHeapInitialization(CuTest *cuTest) {

    binaryHeapInitialization(NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binaryHeapInitialization(free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidBinaryHeapInitialization(CuTest *cuTest) {

    BinaryHeap *heap = binaryHeapInitialization(free, compareIntPointersBHT1);

    CuAssertPtrNotNull(cuTest, heap);

    destroyBinaryHeap(heap);

}


void testBinaryHeapInsert(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapInsert(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryHeapInsert(maxHeap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};
    int maxHeapValues[] = {20, 15, 20, 12, 11, 10, 5, 4, 3, 2};
    int minHeapValues[] = {2, 3, 10, 5, 4, 20, 15, 20, 11, 12};

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }


    CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(maxHeap->arr, 0, maxHeap->count, maxHeap->cmp));
    CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(minHeap->arr, 0, minHeap->count, minHeap->cmp));

    for (int i = 0; i < 10; i++) {
        CuAssertIntEquals(cuTest, maxHeapValues[i], *(int *) maxHeap->arr[i]);
        CuAssertIntEquals(cuTest, minHeapValues[i], *(int *) minHeap->arr[i]);
    }


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapInsertAll(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapInsertAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryHeapInsertAll(maxHeap, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};
    int maxHeapValues[] = {20, 15, 20, 12, 11, 10, 5, 4, 3, 2};
    int minHeapValues[] = {2, 3, 10, 5, 4, 20, 15, 20, 11, 12};

    int **maxHeapValuesArr = (int **) malloc(sizeof(int *) * 10);
    int **minHeapValuesArr = (int **) malloc(sizeof(int *) * 10);

    for (int i = 0; i < 10; i++) {
        maxHeapValuesArr[i] = generateIntPointerBHT(values[i]);
        minHeapValuesArr[i] = generateIntPointerBHT(values[i]);
    }


    binaryHeapInsertAll(maxHeap, (void **) maxHeapValuesArr, 10);
    binaryHeapInsertAll(minHeap, (void **) minHeapValuesArr, 10);


    CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(maxHeap->arr, 0, maxHeap->count, maxHeap->cmp));
    CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(minHeap->arr, 0, minHeap->count, minHeap->cmp));

    for (int i = 0; i < 10; i++) {
        CuAssertIntEquals(cuTest, maxHeapValues[i], *(int *) maxHeap->arr[i]);
        CuAssertIntEquals(cuTest, minHeapValues[i], *(int *) minHeap->arr[i]);
    }


    free(maxHeapValuesArr);
    free(minHeapValuesArr);
    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapDeleteRoot(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapDeleteRoot(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }

    for (int i = 0; i < 10; i++) {

        binaryHeapDeleteRoot(maxHeap);
        binaryHeapDeleteRoot(minHeap);

        CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(maxHeap->arr, 0, maxHeap->count, maxHeap->cmp));
        CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(minHeap->arr, 0, minHeap->count, minHeap->cmp));

    }


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapDeleteRootWtoFr(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapDeleteRootWtoFr(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};
    int valuesSortedInDescendingOrder[] = {20, 20, 15, 12, 11, 10, 5, 4, 3, 2};
    int valuesSortedInAscendingOrder[] = {2, 3, 4, 5, 10, 11, 12, 15, 20, 20};

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }

    for (int i = 0; i < 10; i++) {

        int *maxValue = (int *) binaryHeapDeleteRootWtoFr(maxHeap);
        int *minValue = (int *) binaryHeapDeleteRootWtoFr(minHeap);

        CuAssertIntEquals(cuTest, valuesSortedInDescendingOrder[i], *maxValue);
        CuAssertIntEquals(cuTest, valuesSortedInAscendingOrder[i], *minValue);
        free(maxValue);
        free(minValue);

        CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(maxHeap->arr, 0, maxHeap->count, maxHeap->cmp));
        CuAssertIntEquals(cuTest, 1, isValidBinaryHeap(minHeap->arr, 0, minHeap->count, minHeap->cmp));

    }


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapContains(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryHeapContains(maxHeap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};
    int nonExistingValues[] = {100, 50, 30, 1, 6, 7, 8, 9, 13, 14, 16, 17, 18, 19};

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }


    for (int i = 0; i < 10; i++) {
        CuAssertIntEquals(cuTest, 1, binaryHeapContains(maxHeap, values + i));
        CuAssertIntEquals(cuTest, 1, binaryHeapContains(minHeap, values + i));
    }

    for (int i = 0; i < 14; i++) {
        CuAssertIntEquals(cuTest, 0, binaryHeapContains(maxHeap, nonExistingValues + i));
        CuAssertIntEquals(cuTest, 0, binaryHeapContains(minHeap, nonExistingValues + i));
    }


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapGet(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryHeapGet(maxHeap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};
    int nonExistingValues[] = {100, 50, 30, 1, 6, 7, 8, 9, 13, 14, 16, 17, 18, 19};

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }


    for (int i = 0; i < 10; i++) {
        CuAssertIntEquals(cuTest, values[i], *(int *) binaryHeapGet(maxHeap, values + i));
        CuAssertIntEquals(cuTest, values[i], *(int *) binaryHeapGet(minHeap, values + i));
    }

    for (int i = 0; i < 14; i++) {
        CuAssertPtrEquals(cuTest, NULL, binaryHeapGet(maxHeap, nonExistingValues + i));
        CuAssertPtrEquals(cuTest, NULL, binaryHeapGet(minHeap, nonExistingValues + i));
    }


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapGetSize(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};


    CuAssertIntEquals(cuTest, 0, binaryHeapGetSize(maxHeap));
    CuAssertIntEquals(cuTest, 0, binaryHeapGetSize(minHeap));

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));

        CuAssertIntEquals(cuTest, i + 1, binaryHeapGetSize(maxHeap));
        CuAssertIntEquals(cuTest, i + 1, binaryHeapGetSize(minHeap));

    }

    for (int i = 0; i < 10; i++) {

        binaryHeapDeleteRoot(maxHeap);
        binaryHeapDeleteRoot(minHeap);

        CuAssertIntEquals(cuTest, 9 - i, binaryHeapGetSize(maxHeap));
        CuAssertIntEquals(cuTest, 9 - i, binaryHeapGetSize(minHeap));

    }

    CuAssertIntEquals(cuTest, 0, binaryHeapGetSize(maxHeap));
    CuAssertIntEquals(cuTest, 0, binaryHeapGetSize(minHeap));


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapIsEmpty(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};


    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(maxHeap));
    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(minHeap));

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));

        CuAssertIntEquals(cuTest, 0, binaryHeapIsEmpty(maxHeap));
        CuAssertIntEquals(cuTest, 0, binaryHeapIsEmpty(minHeap));

    }

    for (int i = 0; i < 10; i++) {

        CuAssertIntEquals(cuTest, 0, binaryHeapIsEmpty(maxHeap));
        CuAssertIntEquals(cuTest, 0, binaryHeapIsEmpty(minHeap));

        binaryHeapDeleteRoot(maxHeap);
        binaryHeapDeleteRoot(minHeap);

    }

    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(maxHeap));
    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(minHeap));


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testBinaryHeapToArray(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    binaryHeapToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};
    int maxHeapValues[] = {20, 15, 20, 12, 11, 10, 5, 4, 3, 2};
    int minHeapValues[] = {2, 3, 10, 5, 4, 20, 15, 20, 11, 12};

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }

    int **maxHeapArr = (int **) binaryHeapToArray(maxHeap);
    int **minHeapArr = (int **) binaryHeapToArray(minHeap);

    for (int i = 0; i < 10; i++) {
        CuAssertIntEquals(cuTest, maxHeapValues[i], *maxHeapArr[i]);
        CuAssertIntEquals(cuTest, minHeapValues[i], *minHeapArr[i]);
    }


    free(maxHeapArr);
    free(minHeapArr);
    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testClearBinaryHeap(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    clearBinaryHeap(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};

    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(maxHeap));
    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(minHeap));

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }


    CuAssertIntEquals(cuTest, 0, binaryHeapIsEmpty(maxHeap));
    CuAssertIntEquals(cuTest, 0, binaryHeapIsEmpty(minHeap));

    clearBinaryHeap(maxHeap);
    clearBinaryHeap(minHeap);

    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(maxHeap));
    CuAssertIntEquals(cuTest, 1, binaryHeapIsEmpty(minHeap));


    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


void testDestroyBinaryHeap(CuTest *cuTest) {

    BinaryHeap *maxHeap = binaryHeapInitialization(free, compareIntPointersBHT1);
    BinaryHeap *minHeap = binaryHeapInitialization(free, compareIntPointersBHT2);


    destroyBinaryHeap(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {20, 15, 10, 12, 11, 20, 5, 4, 3, 2};

    for (int i = 0; i < 10; i++) {
        binaryHeapInsert(maxHeap, generateIntPointerBHT(values[i]));
        binaryHeapInsert(minHeap, generateIntPointerBHT(values[i]));
    }

    destroyBinaryHeap(maxHeap);
    destroyBinaryHeap(minHeap);

}


CuSuite *createBinaryHeapTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidBinaryHeapInitialization);
    SUITE_ADD_TEST(suite, testValidBinaryHeapInitialization);
    SUITE_ADD_TEST(suite, testBinaryHeapInsert);
    SUITE_ADD_TEST(suite, testBinaryHeapInsertAll);
    SUITE_ADD_TEST(suite, testBinaryHeapDeleteRoot);
    SUITE_ADD_TEST(suite, testBinaryHeapDeleteRootWtoFr);
    SUITE_ADD_TEST(suite, testBinaryHeapContains);
    SUITE_ADD_TEST(suite, testBinaryHeapGet);
    SUITE_ADD_TEST(suite, testBinaryHeapGetSize);
    SUITE_ADD_TEST(suite, testBinaryHeapIsEmpty);
    SUITE_ADD_TEST(suite, testBinaryHeapToArray);
    SUITE_ADD_TEST(suite, testClearBinaryHeap);
    SUITE_ADD_TEST(suite, testDestroyBinaryHeap);

    return suite;

}


void binaryHeapUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Binary Heap Test**\n");

    CuSuite *suite = createBinaryHeapTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}