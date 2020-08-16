#include "HashMapTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Tables/Headers/HashMap.h"


int hashMapTestStrcmp(const void *c1, const void *c2) {
    return strcmp(c1, c2);
}


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerHMT(int integer) {
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

int compareIntPointersHMT(const void *a, const void *b) {
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

int intHashFunHMT(const void *integer) {
    return *(int *) integer;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerHMT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


/** This function will take an char array pointer,
 * then it will return the sum of the ASCII value of the array characters.
 *
 * Note: this function will be useful to use in the hash set and hash map data structures.
 *
 * @param ch the char array pointer
 * @return it will return the sum of the ASCII value of the array characters.
 */

int charArrHashFunHMT(const void *ch) {
    int sumASCII = 0;
    char *tempPointer = (char *) ch;

    while (*tempPointer != '\0')
        sumASCII += *tempPointer++;

    return sumASCII;

}


void testInvalidHashMapInitialization(CuTest *cuTest) {

    hashMapInitialization(NULL, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInitialization(free, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInitialization(free, free, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInitialization(free, free, compareIntPointersHMT, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidHashMapInitialization(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    CuAssertPtrNotNull(cuTest, hashMap);

    destroyHashMap(hashMap);

}


void testHashMapInsert(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    hashMapInsert(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashMapInsert(hashMap, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempKey = 10;
    hashMapInsert(hashMap, &tempKey, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++) {
        hashMapInsert(hashMap, generateIntPointerHMT(i + 1), generateCharPointerHMT(numbersArr[i]));
    }

    int arr[13] = {0};
    for (int i = 0; i < hashMap->length; i++) {

        if (hashMap->arr[i] != NULL) {
            CuAssertStrEquals(cuTest, numbersArr[*(int *) hashMap->arr[i]->key - 1], (char *) hashMap->arr[i]->item);
            arr[*(int *) hashMap->arr[i]->key - 1]++;
        }

    }

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    destroyHashMap(hashMap);

}


void testHashMapContains(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    hashMapContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashMapContains(hashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInsert(hashMap, generateIntPointerHMT(1), generateCharPointerHMT(numbersArr[0]));
    hashMapInsert(hashMap, generateIntPointerHMT(2), generateCharPointerHMT(numbersArr[1]));
    hashMapInsert(hashMap, generateIntPointerHMT(3), generateCharPointerHMT(numbersArr[2]));
    hashMapInsert(hashMap, generateIntPointerHMT(4), generateCharPointerHMT(numbersArr[3]));
    hashMapInsert(hashMap, generateIntPointerHMT(5), generateCharPointerHMT(numbersArr[4]));

    int tempValue = 1;

    for (int i = 0; i < 5; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, hashMapContains(hashMap, &tempValue));

    tempValue = 6;
    CuAssertIntEquals(cuTest, 0, hashMapContains(hashMap, &tempValue));

    destroyHashMap(hashMap);

}


void testHashMapGet(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    hashMapGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashMapGet(hashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInsert(hashMap, generateIntPointerHMT(1), generateCharPointerHMT(numbersArr[0]));
    hashMapInsert(hashMap, generateIntPointerHMT(2), generateCharPointerHMT(numbersArr[1]));
    hashMapInsert(hashMap, generateIntPointerHMT(3), generateCharPointerHMT(numbersArr[2]));
    hashMapInsert(hashMap, generateIntPointerHMT(4), generateCharPointerHMT(numbersArr[3]));
    hashMapInsert(hashMap, generateIntPointerHMT(5), generateCharPointerHMT(numbersArr[4]));

    int tempValue = 1;

    for (int i = 0; i < 5; i++, tempValue++)
        CuAssertStrEquals(cuTest, numbersArr[i], (char *) hashMapGet(hashMap, &tempValue));

    tempValue = 6;
    CuAssertPtrEquals(cuTest, NULL, hashMapGet(hashMap, &tempValue));

    destroyHashMap(hashMap);

}


void testHashMapGetKey(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    hashMapGetKey(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashMapGetKey(hashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInsert(hashMap, generateIntPointerHMT(1), generateCharPointerHMT(numbersArr[0]));
    hashMapInsert(hashMap, generateIntPointerHMT(2), generateCharPointerHMT(numbersArr[1]));
    hashMapInsert(hashMap, generateIntPointerHMT(3), generateCharPointerHMT(numbersArr[2]));
    hashMapInsert(hashMap, generateIntPointerHMT(4), generateCharPointerHMT(numbersArr[3]));
    hashMapInsert(hashMap, generateIntPointerHMT(5), generateCharPointerHMT(numbersArr[4]));

    int tempValue = 1;

    for (int i = 0; i < 5; i++, tempValue++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) hashMapGetKey(hashMap, &tempValue));

    tempValue = 6;
    CuAssertPtrEquals(cuTest, NULL, hashMapGetKey(hashMap, &tempValue));

    destroyHashMap(hashMap);

}


void testHashMapDelete(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    hashMapDelete(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashMapDelete(hashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInsert(hashMap, generateIntPointerHMT(1), generateCharPointerHMT(numbersArr[0]));
    hashMapInsert(hashMap, generateIntPointerHMT(2), generateCharPointerHMT(numbersArr[1]));
    hashMapInsert(hashMap, generateIntPointerHMT(3), generateCharPointerHMT(numbersArr[2]));
    hashMapInsert(hashMap, generateIntPointerHMT(4), generateCharPointerHMT(numbersArr[3]));
    hashMapInsert(hashMap, generateIntPointerHMT(5), generateCharPointerHMT(numbersArr[4]));

    int tempValue = 5;
    hashMapDelete(hashMap, &tempValue);

    tempValue = 4;
    hashMapDelete(hashMap, &tempValue);

    tempValue = 1;

    for (int i = 0; i < 3; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, hashMapContains(hashMap, &tempValue));

    tempValue = 4;
    CuAssertIntEquals(cuTest, 0, hashMapContains(hashMap, &tempValue));

    tempValue = 5;
    CuAssertIntEquals(cuTest, 0, hashMapContains(hashMap, &tempValue));

    destroyHashMap(hashMap);

}


void testHashMapDeleteWtoFr(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    hashMapDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashMapDeleteWtoFrAll(hashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInsert(hashMap, generateIntPointerHMT(1), generateCharPointerHMT(numbersArr[0]));
    hashMapInsert(hashMap, generateIntPointerHMT(2), generateCharPointerHMT(numbersArr[1]));
    hashMapInsert(hashMap, generateIntPointerHMT(3), generateCharPointerHMT(numbersArr[2]));
    hashMapInsert(hashMap, generateIntPointerHMT(4), generateCharPointerHMT(numbersArr[3]));
    hashMapInsert(hashMap, generateIntPointerHMT(5), generateCharPointerHMT(numbersArr[4]));

    int tempValue = 5;
    char *tempCharPointer = hashMapDeleteWtoFr(hashMap, &tempValue);
    CuAssertStrEquals(cuTest, "five", tempCharPointer);
    free(tempCharPointer);

    tempValue = 4;
    tempCharPointer = hashMapDeleteWtoFr(hashMap, &tempValue);
    CuAssertStrEquals(cuTest, "four", tempCharPointer);
    free(tempCharPointer);

    tempValue = 1;

    for (int i = 0; i < 3; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, hashMapContains(hashMap, &tempValue));

    tempValue = 4;
    CuAssertIntEquals(cuTest, 0, hashMapContains(hashMap, &tempValue));

    tempValue = 5;
    CuAssertIntEquals(cuTest, 0, hashMapContains(hashMap, &tempValue));

    destroyHashMap(hashMap);

}


void testHashMapDeleteWtoFrAll(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    hashMapDeleteWtoFrAll(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    hashMapDeleteWtoFrAll(hashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    hashMapInsert(hashMap, generateIntPointerHMT(1), generateCharPointerHMT(numbersArr[0]));
    hashMapInsert(hashMap, generateIntPointerHMT(2), generateCharPointerHMT(numbersArr[1]));
    hashMapInsert(hashMap, generateIntPointerHMT(3), generateCharPointerHMT(numbersArr[2]));
    hashMapInsert(hashMap, generateIntPointerHMT(4), generateCharPointerHMT(numbersArr[3]));
    hashMapInsert(hashMap, generateIntPointerHMT(5), generateCharPointerHMT(numbersArr[4]));

    int tempValue = 5;
    Entry *tempEntry = hashMapDeleteWtoFrAll(hashMap, &tempValue);
    CuAssertIntEquals(cuTest, 5, *(int *) tempEntry->key);
    CuAssertStrEquals(cuTest, numbersArr[4], (char *) tempEntry->item);
    free(tempEntry->item);
    free(tempEntry->key);
    free(tempEntry);

    tempValue = 4;
    tempEntry = hashMapDeleteWtoFrAll(hashMap, &tempValue);
    CuAssertIntEquals(cuTest, 4, *(int *) tempEntry->key);
    CuAssertStrEquals(cuTest, numbersArr[3], (char *) tempEntry->item);
    free(tempEntry->item);
    free(tempEntry->key);
    free(tempEntry);


    tempValue = 1;

    for (int i = 0; i < 3; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, hashMapContains(hashMap, &tempValue));

    tempValue = 4;
    CuAssertIntEquals(cuTest, 0, hashMapContains(hashMap, &tempValue));

    tempValue = 5;
    CuAssertIntEquals(cuTest, 0, hashMapContains(hashMap, &tempValue));

    destroyHashMap(hashMap);

}


void testHashMapToArray(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, hashMapTestStrcmp, charArrHashFunHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    hashMapToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++)
        hashMapInsert(hashMap, generateCharPointerHMT(numbersArr[i]), generateIntPointerHMT(i + 1));

    int arr[13] = {0};
    int **itemArr = (int **) hashMapToArray(hashMap);

    for (int i = 0; i < hashMap->count; i++)
        arr[*itemArr[i] - 1]++;

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);


    free(itemArr);
    destroyHashMap(hashMap);

}


void testHashMapToEntryArray(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, hashMapTestStrcmp, charArrHashFunHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    hashMapToEntryArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++)
        hashMapInsert(hashMap, generateCharPointerHMT(numbersArr[i]), generateIntPointerHMT(i + 1));

    int arr[13] = {0};
    Entry **entriesArr = hashMapToEntryArray(hashMap);

    for (int i = 0; i < hashMap->count; i++) {
        arr[*(int *) entriesArr[i]->item - 1]++;
        CuAssertStrEquals(cuTest, numbersArr[*(int *) entriesArr[i]->item - 1], (char *) entriesArr[i]->key);
    }

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);


    free(entriesArr);
    destroyHashMap(hashMap);

}


void testHashMapGetLength(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    hashMapGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, hashMapGetLength(hashMap));

    for (int i = 0; i < 13; i++) {
        hashMapInsert(hashMap, generateIntPointerHMT(i + 1), generateCharPointerHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, i + 1, hashMapGetLength(hashMap));
    }


    int tempValue = 1;
    hashMapDelete(hashMap, &tempValue);
    CuAssertIntEquals(cuTest, 12, hashMapGetLength(hashMap));

    tempValue = 2;
    hashMapDelete(hashMap, &tempValue);
    CuAssertIntEquals(cuTest, 11, hashMapGetLength(hashMap));

    tempValue = 1;
    hashMapDelete(hashMap, &tempValue);
    CuAssertIntEquals(cuTest, 11, hashMapGetLength(hashMap));


    destroyHashMap(hashMap);

}


void testHashMapIsEmpty(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    hashMapIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, hashMapIsEmpty(hashMap));

    for (int i = 0; i < 13; i++) {
        hashMapInsert(hashMap, generateIntPointerHMT(i + 1), generateCharPointerHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, 0, hashMapIsEmpty(hashMap));
    }

    for (int i = 1; i <= 13; i++) {
        CuAssertIntEquals(cuTest, 0, hashMapIsEmpty(hashMap));
        hashMapDelete(hashMap, &i);
    }

    CuAssertIntEquals(cuTest, 1, hashMapIsEmpty(hashMap));


    destroyHashMap(hashMap);

}


void testClearHashMap(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    clearHashMap(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, hashMapIsEmpty(hashMap));

    for (int i = 0; i < 13; i++) {
        hashMapInsert(hashMap, generateIntPointerHMT(i + 1), generateCharPointerHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, 0, hashMapIsEmpty(hashMap));
    }

    clearHashMap(hashMap);

    CuAssertIntEquals(cuTest, 1, hashMapIsEmpty(hashMap));


    destroyHashMap(hashMap);

}


void testDestroyHashMap(CuTest *cuTest) {

    HashMap *hashMap = hashMapInitialization(free, free, compareIntPointersHMT, intHashFunHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    destroyHashMap(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++) {
        hashMapInsert(hashMap, generateIntPointerHMT(i + 1), generateCharPointerHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, 0, hashMapIsEmpty(hashMap));
    }


    destroyHashMap(hashMap);

}


CuSuite *createHashMapTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidHashMapInitialization);
    SUITE_ADD_TEST(suite, testValidHashMapInitialization);
    SUITE_ADD_TEST(suite, testHashMapInsert);
    SUITE_ADD_TEST(suite, testHashMapContains);
    SUITE_ADD_TEST(suite, testHashMapGet);
    SUITE_ADD_TEST(suite, testHashMapGetKey);
    SUITE_ADD_TEST(suite, testHashMapDelete);
    SUITE_ADD_TEST(suite, testHashMapDeleteWtoFr);
    SUITE_ADD_TEST(suite, testHashMapDeleteWtoFrAll);
    SUITE_ADD_TEST(suite, testHashMapToArray);
    SUITE_ADD_TEST(suite, testHashMapToEntryArray);
    SUITE_ADD_TEST(suite, testHashMapGetLength);
    SUITE_ADD_TEST(suite, testHashMapIsEmpty);
    SUITE_ADD_TEST(suite, testClearHashMap);
    SUITE_ADD_TEST(suite, testDestroyHashMap);

    return suite;

}


void hashMapUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Hashmap Test**\n");

    CuSuite *suite = createHashMapTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}