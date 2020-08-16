#include "SplayTreeTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Trees/Headers/SplayTree.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 *
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerSTT(int integer) {
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

int compareIntPointersSTT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


int checkIfValidSplayTreeSTT(SplayNode *root, SplayNode *parent) {

    if (root == NULL)
        return 1;

    /*if (parent != NULL) {
        printf("Parent: %d, ", *(int *) parent->key);
        if (parent->right == root)
            printf("Right node, ");
        else
            printf("Left node, ");
    }
    else
        printf("Parent: Root, ");
    printf("node: %d\n", *(int *) root->key);*/

    if (parent != NULL) {

        if (parent->right == root) {

            return
                    compareIntPointersSTT(parent->key, root->key) < 0
                    || compareIntPointersSTT(parent->key, root->key) == 0
                    ? checkIfValidSplayTreeSTT(root->left, root) && checkIfValidSplayTreeSTT(root->right, root)
                    : 0;

        } else {

            return
                    compareIntPointersSTT(parent->key, root->key) > 0
                    || compareIntPointersSTT(parent->key, root->key) == 0
                    ? checkIfValidSplayTreeSTT(root->left, root) && checkIfValidSplayTreeSTT(root->right, root)
                    : 0;

        }

    }

    return checkIfValidSplayTreeSTT(root->left, root) && checkIfValidSplayTreeSTT(root->right, root);


}


void testInvalidSplayTreeInitialization(CuTest *cutest) {

    splayTreeInitialization(NULL, NULL);
    CuAssertIntEquals(cutest, INVALID_ARG, ERROR_TEST->errorCode);


    splayTreeInitialization(free, NULL);
    CuAssertIntEquals(cutest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidSplayTreeInitialization(CuTest *cutest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    CuAssertPtrNotNull(cutest, tree);

}


void testSplayTreeInsert(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeInsert(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    splayTreeInsert(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++) {
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));
        CuAssertIntEquals(cuTest, values[i], *(int *) tree->root->key);
    }

    CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

    destroySplayTree(tree);

}


void testSplayTreeInsert2(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};
    int values2[] = {13, 16, 3, 6, 9, 7, 28, 21};

    for (int i = 0; i < 11; i++) {
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));
        CuAssertIntEquals(cuTest, values[i], *(int *) tree->root->key);
    }


    int tempValue;

    tempValue = 10;
    splayTreeDelete(tree, &tempValue);
    CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

    tempValue = 25;
    splayTreeDelete(tree, &tempValue);
    CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

    tempValue = 5;
    splayTreeDelete(tree, &tempValue);
    CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));


    for (int i = 0; i < 8; i++) {
        splayTreeInsert(tree, generateIntPointerSTT(values2[i]));
        CuAssertIntEquals(cuTest, values2[i], *(int *) tree->root->key);
    }

    CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

    destroySplayTree(tree);

}


void testSplayTreeInsert3(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++) {
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));
        CuAssertIntEquals(cuTest, values[i], *(int *) tree->root->key);
    }


    for (int i = 0; i < 11; i++) {
        splayTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

        splayTreeInsert(tree, generateIntPointerSTT(values[i]));
        CuAssertIntEquals(cuTest, values[i], *(int *) tree->root->key);
        CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

    }

    destroySplayTree(tree);

}


void testSplayTreeInsertAll(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeInsertAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    splayTreeInsertAll(tree, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};
    int **valuesArr = (int **) malloc(sizeof(int *) * 11);

    for (int i = 0; i < 11; i++)
        valuesArr[i] = generateIntPointerSTT(values[i]);


    splayTreeInsertAll(tree, (void **) valuesArr, 11);
    CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));


    free(valuesArr);
    destroySplayTree(tree);

}


void testSplayTreeDelete(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeDelete(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    splayTreeDelete(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 0;
    splayTreeDelete(tree, &tempValue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));


    for (int i = 0; i < 11; i++) {
        splayTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));
    }

    destroySplayTree(tree);

}


void testSplayTreeDeleteWtoFr(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    splayTreeDeleteWtoFr(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 0;
    splayTreeDeleteWtoFr(tree, &tempValue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};

    for (int i = 0; i < 10; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));


    for (int i = 0; i < 10; i++) {

        void *item = splayTreeDeleteWtoFr(tree, values + i);

        CuAssertPtrNotNull(cuTest, item);
        CuAssertIntEquals(cuTest, values[i], *(int *) item);
        free(item);
        CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

    }


    CuAssertPtrEquals(cuTest, NULL, splayTreeDeleteWtoFr(tree, values));

    destroySplayTree(tree);

}


void testSplayTreeContains(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    splayTreeContains(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};

    for (int i = 0; i < 10; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));


    for (int i = 0; i < 10; i++) {
        CuAssertIntEquals(cuTest, 1, splayTreeContains(tree, values + i));
        CuAssertIntEquals(cuTest, values[i], *(int *) tree->root->key);
    }


    int tempValue = 233;
    CuAssertIntEquals(cuTest, 0, splayTreeContains(tree, &tempValue));

    destroySplayTree(tree);

}


void testSplayTreeGet(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    splayTreeGet(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};

    for (int i = 0; i < 10; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));


    for (int i = 0; i < 10; i++) {

        void *item = splayTreeGet(tree, values + i);

        CuAssertPtrNotNull(cuTest, item);
        CuAssertIntEquals(cuTest, values[i], *(int *) item);
        CuAssertIntEquals(cuTest, values[i], *(int *) tree->root->key);

    }


    int tempValue = 100;
    CuAssertPtrEquals(cuTest, NULL, splayTreeGet(tree, &tempValue));

    destroySplayTree(tree);

}


void testSplayTreeGetSize(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, splayTreeGetSize(tree));


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++) {
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));
        CuAssertIntEquals(cuTest, i + 1, splayTreeGetSize(tree));
    }

    CuAssertIntEquals(cuTest, 11, splayTreeGetSize(tree));

    for (int i = 0; i < 11; i++) {
        splayTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 10 - i, splayTreeGetSize(tree));
    }


    CuAssertIntEquals(cuTest, 0, splayTreeGetSize(tree));

    destroySplayTree(tree);

}


void testSplayTreeIsEmpty(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, splayTreeIsEmpty(tree));


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));

    CuAssertIntEquals(cuTest, 0, splayTreeIsEmpty(tree));

    for (int i = 0; i < 11; i++)
        splayTreeDelete(tree, values + i);


    CuAssertIntEquals(cuTest, 1, splayTreeIsEmpty(tree));

    destroySplayTree(tree);

}


void testSplayTreeToArray(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    splayTreeToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));


    int **treeArr = (int **) splayTreeToArray(tree);

    qsort(values, 11, sizeof(int), compareIntPointersSTT);

    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, values[i], *treeArr[i]);


    free(treeArr);
    destroySplayTree(tree);

}


void testClearSplayTree(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    clearSplayTree(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, splayTreeIsEmpty(tree));

    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));

    CuAssertIntEquals(cuTest, 0, splayTreeIsEmpty(tree));

    clearSplayTree(tree);

    CuAssertIntEquals(cuTest, 1, checkIfValidSplayTreeSTT(tree->root, NULL));

    CuAssertIntEquals(cuTest, 1, splayTreeIsEmpty(tree));

    destroySplayTree(tree);

}


void testDestroySplayTree(CuTest *cuTest) {

    SplayTree *tree = splayTreeInitialization(free, compareIntPointersSTT);

    destroySplayTree(NULL);

    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        splayTreeInsert(tree, generateIntPointerSTT(values[i]));

    destroySplayTree(tree);

}


CuSuite *createSplayTreeTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidSplayTreeInitialization);
    SUITE_ADD_TEST(suite, testValidSplayTreeInitialization);
    SUITE_ADD_TEST(suite, testSplayTreeInsert);
    SUITE_ADD_TEST(suite, testSplayTreeInsert2);
    SUITE_ADD_TEST(suite, testSplayTreeInsert3);
    SUITE_ADD_TEST(suite, testSplayTreeInsertAll);
    SUITE_ADD_TEST(suite, testSplayTreeDelete);
    SUITE_ADD_TEST(suite, testSplayTreeDeleteWtoFr);
    SUITE_ADD_TEST(suite, testSplayTreeContains);
    SUITE_ADD_TEST(suite, testSplayTreeGet);
    SUITE_ADD_TEST(suite, testSplayTreeGetSize);
    SUITE_ADD_TEST(suite, testSplayTreeIsEmpty);
    SUITE_ADD_TEST(suite, testSplayTreeToArray);
    SUITE_ADD_TEST(suite, testClearSplayTree);
    SUITE_ADD_TEST(suite, testDestroySplayTree);

    return suite;

}


void splayTreeUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Splay Tree Test**\n");

    CuSuite *suite = createSplayTreeTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}