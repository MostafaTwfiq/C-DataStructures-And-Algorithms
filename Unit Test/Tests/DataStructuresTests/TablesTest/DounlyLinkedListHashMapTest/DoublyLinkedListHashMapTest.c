#include "DoublyLinkedListHashMapTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Tables/Headers/LinkedListHashMap.h"
#include "../../../../../DataStructure/LinkedLists/Headers/DoublyLinkedList.h"


int doublyLinkedListHashMapTestStrcmp(const void *c1, const void *c2) {
    return strcmp(c1, c2);
}


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerDLLHMT(int integer) {
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

int compareIntPointersDLLHMT(const void *a, const void *b) {
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

int intHashFunDLLHMT(const void *integer) {
    return *(int *) integer;
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerDLLHMT(char *ch) {

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

int charArrHashFunDLLHMT(const void *ch) {
    int sumASCII = 0;
    char *tempPointer = (char *) ch;

    while (*tempPointer != '\0')
        sumASCII += *tempPointer++;

    return sumASCII;

}


void testInvalidDLLHashMapInitialization(CuTest *cuTest) {

    linkedListHashMapInitialization(0, NULL, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linkedListHashMapInitialization(1, NULL, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linkedListHashMapInitialization(1, free, NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linkedListHashMapInitialization(1, free, free, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    linkedListHashMapInitialization(1, free, free, compareIntPointersDLLHMT, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidDLLHashMapInitialization(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(1, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    CuAssertPtrNotNull(cuTest, llHashMap);

    destroyLLHashMap(llHashMap);

}


void testDLLHashMapInsert(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    lLHashMapInsert(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLHashMapInsert(llHashMap, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempKey = 10;
    lLHashMapInsert(llHashMap, &tempKey, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++)
        lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(i + 1), generateCharPointerDLLHMT(numbersArr[i]));

    int arr[13] = {0};
    for (int i = 0; i < llHashMap->length; i++) {

        if (llHashMap->arr[i] == NULL)
            continue;

        for (int j = 0; j < doublyLinkedListGetLength(llHashMap->arr[i]); j++) {
            Entry *currentEntry = (Entry *) doublyLinkedListGet(llHashMap->arr[i], j);
            CuAssertStrEquals(cuTest, numbersArr[*(int *) currentEntry->key - 1], (char *) currentEntry->item);
            arr[*(int *) currentEntry->key - 1]++;
        }

    }

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    destroyLLHashMap(llHashMap);

}


void testDLLHashMapContains(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    lLHashMapContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLHashMapContains(llHashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(1), generateCharPointerDLLHMT(numbersArr[0]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(2), generateCharPointerDLLHMT(numbersArr[1]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(3), generateCharPointerDLLHMT(numbersArr[2]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(4), generateCharPointerDLLHMT(numbersArr[3]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(5), generateCharPointerDLLHMT(numbersArr[4]));

    int tempValue = 1;

    for (int i = 0; i < 5; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, lLHashMapContains(llHashMap, &tempValue));

    tempValue = 6;
    CuAssertIntEquals(cuTest, 0, lLHashMapContains(llHashMap, &tempValue));

    destroyLLHashMap(llHashMap);

}


void testDLLHashMapGet(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    lLHashMapGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLHashMapGet(llHashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(1), generateCharPointerDLLHMT(numbersArr[0]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(2), generateCharPointerDLLHMT(numbersArr[1]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(3), generateCharPointerDLLHMT(numbersArr[2]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(4), generateCharPointerDLLHMT(numbersArr[3]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(5), generateCharPointerDLLHMT(numbersArr[4]));

    int tempValue = 1;

    for (int i = 0; i < 5; i++, tempValue++)
        CuAssertStrEquals(cuTest, numbersArr[i], (char *) lLHashMapGet(llHashMap, &tempValue));

    tempValue = 6;
    CuAssertPtrEquals(cuTest, NULL, lLHashMapGet(llHashMap, &tempValue));

    destroyLLHashMap(llHashMap);

}


void testDLLHashMapGetKey(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    lLHashMapGetKey(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLHashMapGetKey(llHashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(1), generateCharPointerDLLHMT(numbersArr[0]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(2), generateCharPointerDLLHMT(numbersArr[1]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(3), generateCharPointerDLLHMT(numbersArr[2]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(4), generateCharPointerDLLHMT(numbersArr[3]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(5), generateCharPointerDLLHMT(numbersArr[4]));

    int tempValue = 1;

    for (int i = 0; i < 5; i++, tempValue++)
        CuAssertIntEquals(cuTest, i + 1, *(int *) lLHashMapGetKey(llHashMap, &tempValue));

    tempValue = 6;
    CuAssertPtrEquals(cuTest, NULL, lLHashMapGetKey(llHashMap, &tempValue));

    destroyLLHashMap(llHashMap);

}


void testDlLHashMapDelete(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    lLHashMapDelete(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLHashMapDelete(llHashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(1), generateCharPointerDLLHMT(numbersArr[0]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(2), generateCharPointerDLLHMT(numbersArr[1]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(3), generateCharPointerDLLHMT(numbersArr[2]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(4), generateCharPointerDLLHMT(numbersArr[3]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(5), generateCharPointerDLLHMT(numbersArr[4]));

    int tempValue = 5;
    lLHashMapDelete(llHashMap, &tempValue);

    tempValue = 4;
    lLHashMapDelete(llHashMap, &tempValue);

    tempValue = 1;

    for (int i = 0; i < 3; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, lLHashMapContains(llHashMap, &tempValue));

    tempValue = 4;
    CuAssertIntEquals(cuTest, 0, lLHashMapContains(llHashMap, &tempValue));

    tempValue = 5;
    CuAssertIntEquals(cuTest, 0, lLHashMapContains(llHashMap, &tempValue));

    destroyLLHashMap(llHashMap);

}


void testDLLHashMapDeleteWtoFr(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    lLHashMapDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLHashMapDeleteWtoFrAll(llHashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(1), generateCharPointerDLLHMT(numbersArr[0]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(2), generateCharPointerDLLHMT(numbersArr[1]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(3), generateCharPointerDLLHMT(numbersArr[2]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(4), generateCharPointerDLLHMT(numbersArr[3]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(5), generateCharPointerDLLHMT(numbersArr[4]));

    int tempValue = 5;
    char *tempCharPointer = lLHashMapDeleteWtoFr(llHashMap, &tempValue);
    CuAssertStrEquals(cuTest, "five", tempCharPointer);
    free(tempCharPointer);

    tempValue = 4;
    tempCharPointer = lLHashMapDeleteWtoFr(llHashMap, &tempValue);
    CuAssertStrEquals(cuTest, "four", tempCharPointer);
    free(tempCharPointer);

    tempValue = 1;

    for (int i = 0; i < 3; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, lLHashMapContains(llHashMap, &tempValue));

    tempValue = 4;
    CuAssertIntEquals(cuTest, 0, lLHashMapContains(llHashMap, &tempValue));

    tempValue = 5;
    CuAssertIntEquals(cuTest, 0, lLHashMapContains(llHashMap, &tempValue));

    destroyLLHashMap(llHashMap);

}


void testDLLHashMapDeleteWtoFrAll(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[5][6] = {"one", "two", "three", "four", "five"};

    lLHashMapDeleteWtoFrAll(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    lLHashMapDeleteWtoFrAll(llHashMap, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(1), generateCharPointerDLLHMT(numbersArr[0]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(2), generateCharPointerDLLHMT(numbersArr[1]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(3), generateCharPointerDLLHMT(numbersArr[2]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(4), generateCharPointerDLLHMT(numbersArr[3]));
    lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(5), generateCharPointerDLLHMT(numbersArr[4]));

    int tempValue = 5;
    Entry *tempEntry = lLHashMapDeleteWtoFrAll(llHashMap, &tempValue);
    CuAssertIntEquals(cuTest, 5, *(int *) tempEntry->key);
    CuAssertStrEquals(cuTest, numbersArr[4], (char *) tempEntry->item);
    free(tempEntry->item);
    free(tempEntry->key);
    free(tempEntry);

    tempValue = 4;
    tempEntry = lLHashMapDeleteWtoFrAll(llHashMap, &tempValue);
    CuAssertIntEquals(cuTest, 4, *(int *) tempEntry->key);
    CuAssertStrEquals(cuTest, numbersArr[3], (char *) tempEntry->item);
    free(tempEntry->item);
    free(tempEntry->key);
    free(tempEntry);


    tempValue = 1;

    for (int i = 0; i < 3; i++, tempValue++)
        CuAssertIntEquals(cuTest, 1, lLHashMapContains(llHashMap, &tempValue));

    tempValue = 4;
    CuAssertIntEquals(cuTest, 0, lLHashMapContains(llHashMap, &tempValue));

    tempValue = 5;
    CuAssertIntEquals(cuTest, 0, lLHashMapContains(llHashMap, &tempValue));

    destroyLLHashMap(llHashMap);

}


void testDLLHashMapToArray(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, doublyLinkedListHashMapTestStrcmp,
                                                                   charArrHashFunDLLHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    lLHashMapToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++)
        lLHashMapInsert(llHashMap, generateCharPointerDLLHMT(numbersArr[i]), generateIntPointerDLLHMT(i + 1));

    int arr[13] = {0};
    int **itemArr = (int **) lLHashMapToArray(llHashMap);

    for (int i = 0; i < llHashMap->count; i++)
        arr[*itemArr[i] - 1]++;

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);


    free(itemArr);
    destroyLLHashMap(llHashMap);

}


void testDLLHashMapToEntryArray(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, doublyLinkedListHashMapTestStrcmp,
                                                                   charArrHashFunDLLHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    lLHashMapToEntryArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++)
        lLHashMapInsert(llHashMap, generateCharPointerDLLHMT(numbersArr[i]), generateIntPointerDLLHMT(i + 1));

    int arr[13] = {0};
    Entry **entriesArr = lLHashMapToEntryArray(llHashMap);

    for (int i = 0; i < llHashMap->count; i++) {
        arr[*(int *) entriesArr[i]->item - 1]++;
        CuAssertStrEquals(cuTest, numbersArr[*(int *) entriesArr[i]->item - 1], (char *) entriesArr[i]->key);
    }

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);


    free(entriesArr);
    destroyLLHashMap(llHashMap);

}


void testDLLHashMapGetLength(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    lLHashMapGetLength(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, lLHashMapGetLength(llHashMap));

    for (int i = 0; i < 13; i++) {
        lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(i + 1), generateCharPointerDLLHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, i + 1, lLHashMapGetLength(llHashMap));
    }


    int tempValue = 1;
    lLHashMapDelete(llHashMap, &tempValue);
    CuAssertIntEquals(cuTest, 12, lLHashMapGetLength(llHashMap));

    tempValue = 2;
    lLHashMapDelete(llHashMap, &tempValue);
    CuAssertIntEquals(cuTest, 11, lLHashMapGetLength(llHashMap));

    tempValue = 1;
    lLHashMapDelete(llHashMap, &tempValue);
    CuAssertIntEquals(cuTest, 11, lLHashMapGetLength(llHashMap));


    destroyLLHashMap(llHashMap);

}


void testDLLHashMapIsEmpty(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    lLHashMapIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, lLHashMapIsEmpty(llHashMap));

    for (int i = 0; i < 13; i++) {
        lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(i + 1), generateCharPointerDLLHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, 0, lLHashMapIsEmpty(llHashMap));
    }

    for (int i = 1; i <= 13; i++) {
        CuAssertIntEquals(cuTest, 0, lLHashMapIsEmpty(llHashMap));
        lLHashMapDelete(llHashMap, &i);
    }

    CuAssertIntEquals(cuTest, 1, lLHashMapIsEmpty(llHashMap));


    destroyLLHashMap(llHashMap);

}


void testClearDLLHashMap(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    clearLLHashMap(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, lLHashMapIsEmpty(llHashMap));

    for (int i = 0; i < 13; i++) {
        lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(i + 1), generateCharPointerDLLHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, 0, lLHashMapIsEmpty(llHashMap));
    }

    clearLLHashMap(llHashMap);

    CuAssertIntEquals(cuTest, 1, lLHashMapIsEmpty(llHashMap));


    destroyLLHashMap(llHashMap);

}


void testDestroyDLLHashMap(CuTest *cuTest) {

    LinkedListHashMap *llHashMap = linkedListHashMapInitialization(3, free, free, compareIntPointersDLLHMT,
                                                                   intHashFunDLLHMT);

    char numbersArr[13][10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven",
                               "twelve", "thirteen"};

    destroyLLHashMap(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    for (int i = 0; i < 13; i++) {
        lLHashMapInsert(llHashMap, generateIntPointerDLLHMT(i + 1), generateCharPointerDLLHMT(numbersArr[i]));
        CuAssertIntEquals(cuTest, 0, lLHashMapIsEmpty(llHashMap));
    }


    destroyLLHashMap(llHashMap);

}


CuSuite *createDoublyLinkedListHashMapTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidDLLHashMapInitialization);
    SUITE_ADD_TEST(suite, testValidDLLHashMapInitialization);
    SUITE_ADD_TEST(suite, testDLLHashMapInsert);
    SUITE_ADD_TEST(suite, testDLLHashMapContains);
    SUITE_ADD_TEST(suite, testDLLHashMapGet);
    SUITE_ADD_TEST(suite, testDLLHashMapGetKey);
    SUITE_ADD_TEST(suite, testDlLHashMapDelete);
    SUITE_ADD_TEST(suite, testDLLHashMapDeleteWtoFr);
    SUITE_ADD_TEST(suite, testDLLHashMapDeleteWtoFrAll);
    SUITE_ADD_TEST(suite, testDLLHashMapToArray);
    SUITE_ADD_TEST(suite, testDLLHashMapToEntryArray);
    SUITE_ADD_TEST(suite, testDLLHashMapGetLength);
    SUITE_ADD_TEST(suite, testDLLHashMapIsEmpty);
    SUITE_ADD_TEST(suite, testClearDLLHashMap);
    SUITE_ADD_TEST(suite, testDestroyDLLHashMap);

    return suite;

}


void doublyLinkedListHashMapUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Doubly Linked List HashMap Test**\n");

    CuSuite *suite = createDoublyLinkedListHashMapTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}
