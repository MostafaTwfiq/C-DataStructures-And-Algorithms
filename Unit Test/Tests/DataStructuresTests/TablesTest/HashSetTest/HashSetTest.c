#include "HashSetTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Tables/Headers/HashSet.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerHST(int integer) {
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

int compareIntPointersHST(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will take an integer pointer,
 * then it will return the value of the integer.
 *
 * Note: this function will be useful to use hash set and hash map data structure.
 *
 * @param integer the integer pointer
 * @return it will return the passed integer pointer value
 */

int intHashFunHST(const void *integer) {
    return *(int *) integer;
}


void testInvalidHashSetInitialization(CuTest *cuTest) {

    hashSetInitialization(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashSetInitialization(free, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashSetInitialization(free, compareIntPointersHST, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidHashSetInitialization(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);
    CuAssertPtrNotNull(cuTest, hashSet);

    destroyHashSet(hashSet);

}


void testHashSetInsert(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetInsert(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashSetInsert(hashSet, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));

    int arr[20] = {0};

    for (int i = 0; i < hashSet->length; i++) {

        if (hashSet->arr[i] != NULL)
            arr[*(int *) hashSet->arr[i] - 1]++;

    }

    for (int i = 0; i < 20; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    destroyHashSet(hashSet);

}


void testHashSetDelete(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetDelete(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashSetDelete(hashSet, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));

    int arr[20] = {0};

    for (int i = 1; i <= 20; i++)
        hashSetDelete(hashSet, &i);

    for (int i = 0; i < hashSet->length; i++) {

        if (hashSet->arr[i] != NULL)
            arr[*(int *) hashSet->arr[i] - 1]++;

    }

    for (int i = 0; i < 20; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    destroyHashSet(hashSet);

}


void testHashSetDeleteWtoFr(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashSetDeleteWtoFr(hashSet, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));

    int arr[20] = {0};

    int *tempIntPointer = NULL;
    for (int i = 1; i <= 20; i++) {
        tempIntPointer = (int *) hashSetDeleteWtoFr(hashSet, &i);
        CuAssertIntEquals(cuTest, i, *tempIntPointer);

        free(tempIntPointer);
    }

    for (int i = 0; i < hashSet->length; i++) {

        if (hashSet->arr[i] != NULL)
            arr[*(int *) hashSet->arr[i] - 1]++;

    }

    for (int i = 0; i < 20; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    int tempValue = 10;
    CuAssertPtrEquals(cuTest, NULL, hashSetDeleteWtoFr(hashSet, &tempValue));

    destroyHashSet(hashSet);

}


void testHashSetContains(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashSetContains(hashSet, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));


    for (int i = 1; i <= hashSet->count; i++)
        CuAssertIntEquals(cuTest, 1, hashSetContains(hashSet, &i));

    int tempValue = 21;
    CuAssertIntEquals(cuTest, 0, hashSetContains(hashSet, &tempValue));


    destroyHashSet(hashSet);

}


void testHashSetGet(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashSetGet(hashSet, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));


    for (int i = 1; i <= hashSet->count; i++)
        CuAssertIntEquals(cuTest, i, *(int *) hashSetGet(hashSet, &i));

    int tempValue = 21;
    CuAssertPtrEquals(cuTest, NULL, hashSetGet(hashSet, &tempValue));


    destroyHashSet(hashSet);

}


void testHashSetToArray(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));

    int arr[20] = {0};
    int **hashSetArr = (int **) hashSetToArray(hashSet);

    for (int i = 0; i < hashSet->count; i++)
        arr[*hashSetArr[i] - 1]++;

    for (int i = 0; i < 20; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);


    free(hashSetArr);
    destroyHashSet(hashSet);

}


void testHashSetGetLength(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, hashSetGetLength(hashSet));


    for (int i = 0; i < 20; i++) {
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));
        CuAssertIntEquals(cuTest, i + 1, hashSetGetLength(hashSet));
    }

    for (int i = 20; i >= 1; i--) {
        CuAssertIntEquals(cuTest, i, hashSetGetLength(hashSet));
        hashSetDelete(hashSet, &i);
    }

    CuAssertIntEquals(cuTest, 0, hashSetGetLength(hashSet));


    destroyHashSet(hashSet);

}


void testHashSetIsEmpty(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    hashSetIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, hashSetIsEmpty(hashSet));


    for (int i = 0; i < 20; i++) {
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));
        CuAssertIntEquals(cuTest, 0, hashSetIsEmpty(hashSet));
    }

    for (int i = 20; i >= 1; i--)
        hashSetDelete(hashSet, &i);

    CuAssertIntEquals(cuTest, 1, hashSetIsEmpty(hashSet));


    destroyHashSet(hashSet);

}


void testClearHashSet(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    clearHashSet(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, hashSetIsEmpty(hashSet));


    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));


    CuAssertIntEquals(cuTest, 20, hashSetGetLength(hashSet));
    CuAssertIntEquals(cuTest, 0, hashSetIsEmpty(hashSet));


    clearHashSet(hashSet);

    CuAssertIntEquals(cuTest, 0, hashSetGetLength(hashSet));
    CuAssertIntEquals(cuTest, 1, hashSetIsEmpty(hashSet));


    destroyHashSet(hashSet);

}


void testDestroyHashSet(CuTest *cuTest) {

    HashSet *hashSet = hashSetInitialization(free, compareIntPointersHST, intHashFunHST);

    destroyHashSet(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 20; i++)
        hashSetInsert(hashSet, generateIntPointerHST(i + 1));


    destroyHashSet(hashSet);

}


CuSuite *createHashSetTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidHashSetInitialization);
    SUITE_ADD_TEST(suite, testValidHashSetInitialization);
    SUITE_ADD_TEST(suite, testHashSetInsert);
    SUITE_ADD_TEST(suite, testHashSetDelete);
    SUITE_ADD_TEST(suite, testHashSetDeleteWtoFr);
    SUITE_ADD_TEST(suite, testHashSetContains);
    SUITE_ADD_TEST(suite, testHashSetGet);
    SUITE_ADD_TEST(suite, testHashSetToArray);
    SUITE_ADD_TEST(suite, testHashSetGetLength);
    SUITE_ADD_TEST(suite, testHashSetIsEmpty);
    SUITE_ADD_TEST(suite, testClearHashSet);
    SUITE_ADD_TEST(suite, testDestroyHashSet);

    return suite;

}


void hashSetUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Hashset Test**\n");

    CuSuite *suite = createHashSetTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}