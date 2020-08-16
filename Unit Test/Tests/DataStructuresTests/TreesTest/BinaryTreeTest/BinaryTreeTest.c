#include "BinaryTreeTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Trees/Headers/BinaryTree.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 *
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerBTT(int integer) {
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

int compareIntPointersBTT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


int checkIfValidBinaryTreeBTT(BinaryTreeNode *root, BinaryTreeNode *parent) {

    if (root == NULL)
        return 1;

    if (parent != NULL) {

        if (parent->right == root) {

            return
                    compareIntPointersBTT(parent->key, root->key) < 0 ||
                    compareIntPointersBTT(parent->key, root->key) == 0
                    ? checkIfValidBinaryTreeBTT(root->left, root) && checkIfValidBinaryTreeBTT(root->right, root)
                    : 0;

        } else {

            return
                    compareIntPointersBTT(parent->key, root->key) > 0
                    ? checkIfValidBinaryTreeBTT(root->left, root) && checkIfValidBinaryTreeBTT(root->right, root)
                    : 0;

        }

    }

    return checkIfValidBinaryTreeBTT(root->left, root) && checkIfValidBinaryTreeBTT(root->right, root);


}


void testInvalidBinaryTreeInitialization(CuTest *cuTest) {

    binaryTreeInitialization(NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    binaryTreeInitialization(free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidBinaryTreeInitialization(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertPtrNotNull(cuTest, tree);

    destroyBinaryTree(tree);

}


void testBinaryTreeInsert(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeInsert(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreeInsert(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));

    CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));

    destroyBinaryTree(tree);

}


void testBinaryTreeInsert2(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};
    int values2[] = {13, 16, 3, 6, 9, 7, 28, 21};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    int tempValue;

    tempValue = 10;
    binaryTreeDelete(tree, &tempValue);

    tempValue = 25;
    binaryTreeDelete(tree, &tempValue);

    tempValue = 5;
    binaryTreeDelete(tree, &tempValue);


    for (int i = 0; i < 8; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values2[i]));

    CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));

    destroyBinaryTree(tree);

}


void testBinaryTreeInsert3(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    for (int i = 0; i < 11; i++) {
        binaryTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));

        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));

    }

    destroyBinaryTree(tree);

}


void testBinaryTreeInsertAll(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeInsertAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreeInsertAll(tree, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};
    int **valuesArr = (int **) malloc(sizeof(int *) * 11);

    for (int i = 0; i < 11; i++)
        valuesArr[i] = generateIntPointerBTT(values[i]);


    binaryTreeInsertAll(tree, (void **) valuesArr, 11);
    CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));


    free(valuesArr);
    destroyBinaryTree(tree);

}


void testBinaryTreeDelete(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeDelete(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreeDelete(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 0;
    binaryTreeDelete(tree, &tempValue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    for (int i = 0; i < 11; i++) {
        binaryTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));
    }

    destroyBinaryTree(tree);

}


void testBinaryTreeDeleteWtoFr(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreeDeleteWtoFr(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 0;
    binaryTreeDeleteWtoFr(tree, &tempValue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};

    for (int i = 0; i < 10; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    for (int i = 0; i < 10; i++) {

        void *item = binaryTreeDeleteWtoFr(tree, values + i);

        CuAssertPtrNotNull(cuTest, item);
        CuAssertIntEquals(cuTest, values[i], *(int *) item);
        free(item);
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));

    }


    CuAssertPtrEquals(cuTest, NULL, binaryTreeDeleteWtoFr(tree, values));

    destroyBinaryTree(tree);

}


void testBinaryTreeContains(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreeContains(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};

    for (int i = 0; i < 10; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, 1, binaryTreeContains(tree, values + i));


    int tempValue = 233;
    CuAssertIntEquals(cuTest, 0, binaryTreeContains(tree, &tempValue));

    destroyBinaryTree(tree);

}


void testBinaryTreeGet(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreeGet(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};

    for (int i = 0; i < 10; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    for (int i = 0; i < 10; i++) {

        void *item = binaryTreeGet(tree, values + i);

        CuAssertPtrNotNull(cuTest, item);
        CuAssertIntEquals(cuTest, values[i], *(int *) item);

    }


    int tempValue = 100;
    CuAssertPtrEquals(cuTest, NULL, binaryTreeGet(tree, &tempValue));

    destroyBinaryTree(tree);

}


int **printingArrAVLTT;

void printFunAVLTT(void *item) {

    *printingArrAVLTT++ = item;

}


void testBinaryTreePreOrderTraversal(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreePreOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreePreOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};
    int preOrderArr[] = {10, 5, 4, 2, 1, 8, 20, 15, 18, 25};

    for (int i = 0; i < 10; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    printingArrAVLTT = (int **) malloc(sizeof(int *) * tree->count);
    int **tempPointer = printingArrAVLTT;

    binaryTreePreOrderTraversal(tree, printFunAVLTT);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, preOrderArr[i], *tempPointer[i]);

    free(tempPointer);
    destroyBinaryTree(tree);

}


void testBinaryTreeInOrderTraversal(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeInOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreeInOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};
    int inOrderArr[] = {1, 2, 4, 5, 8, 10, 15, 18, 20, 25};

    for (int i = 0; i < 10; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    printingArrAVLTT = (int **) malloc(sizeof(int *) * tree->count);
    int **tempPointer = printingArrAVLTT;

    binaryTreeInOrderTraversal(tree, printFunAVLTT);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, inOrderArr[i], *tempPointer[i]);

    free(tempPointer);
    destroyBinaryTree(tree);

}


void testBinaryTreePostOrderTraversal(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreePostOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    binaryTreePostOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 18};
    int postOrderArr[] = {1, 2, 4, 8, 5, 18, 15, 25, 20, 10};

    for (int i = 0; i < 10; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    printingArrAVLTT = (int **) malloc(sizeof(int *) * tree->count);
    int **tempPointer = printingArrAVLTT;

    binaryTreePostOrderTraversal(tree, printFunAVLTT);

    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, postOrderArr[i], *tempPointer[i]);

    free(tempPointer);
    destroyBinaryTree(tree);

}


void testBinaryTreeGetSize(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, binaryTreeGetSize(tree));


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++) {
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));
        CuAssertIntEquals(cuTest, i + 1, binaryTreeGetSize(tree));
    }

    CuAssertIntEquals(cuTest, 11, binaryTreeGetSize(tree));

    for (int i = 0; i < 11; i++) {
        binaryTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 10 - i, binaryTreeGetSize(tree));
    }


    CuAssertIntEquals(cuTest, 0, binaryTreeGetSize(tree));

    destroyBinaryTree(tree);

}


void testBinaryTreeIsEmpty(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, binaryTreeIsEmpty(tree));


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));

    CuAssertIntEquals(cuTest, 0, binaryTreeIsEmpty(tree));

    for (int i = 0; i < 11; i++)
        binaryTreeDelete(tree, values + i);


    CuAssertIntEquals(cuTest, 1, binaryTreeIsEmpty(tree));

    destroyBinaryTree(tree);

}


void testBinaryTreeToArray(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    binaryTreeToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));


    int **treeArr = (int **) binaryTreeToArray(tree);

    qsort(values, 11, sizeof(int), compareIntPointersBTT);

    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, values[i], *treeArr[i]);


    free(treeArr);
    destroyBinaryTree(tree);

}


void testClearBinaryTree(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    clearBinaryTree(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, binaryTreeIsEmpty(tree));

    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));

    CuAssertIntEquals(cuTest, 0, binaryTreeIsEmpty(tree));

    clearBinaryTree(tree);

    CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeBTT(tree->root, NULL));

    CuAssertIntEquals(cuTest, 1, binaryTreeIsEmpty(tree));

    destroyBinaryTree(tree);

}


void testDestroyBinaryTree(CuTest *cuTest) {

    BinaryTree *tree = binaryTreeInitialization(free, compareIntPointersBTT);

    destroyBinaryTree(NULL);

    int values[] = {10, 20, 5, 8, 15, 25, 4, 2, 1, 10, 18};

    for (int i = 0; i < 11; i++)
        binaryTreeInsert(tree, generateIntPointerBTT(values[i]));

    destroyBinaryTree(tree);

}


CuSuite *createBinaryTreeTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidBinaryTreeInitialization);
    SUITE_ADD_TEST(suite, testValidBinaryTreeInitialization);
    SUITE_ADD_TEST(suite, testBinaryTreeInsert);
    SUITE_ADD_TEST(suite, testBinaryTreeInsert2);
    SUITE_ADD_TEST(suite, testBinaryTreeInsert3);
    SUITE_ADD_TEST(suite, testBinaryTreeInsertAll);
    SUITE_ADD_TEST(suite, testBinaryTreeDelete);
    SUITE_ADD_TEST(suite, testBinaryTreeDeleteWtoFr);
    SUITE_ADD_TEST(suite, testBinaryTreeContains);
    SUITE_ADD_TEST(suite, testBinaryTreeGet);
    SUITE_ADD_TEST(suite, testBinaryTreePreOrderTraversal);
    SUITE_ADD_TEST(suite, testBinaryTreeInOrderTraversal);
    SUITE_ADD_TEST(suite, testBinaryTreePostOrderTraversal);
    SUITE_ADD_TEST(suite, testBinaryTreeGetSize);
    SUITE_ADD_TEST(suite, testBinaryTreeIsEmpty);
    SUITE_ADD_TEST(suite, testBinaryTreeToArray);
    SUITE_ADD_TEST(suite, testClearBinaryTree);
    SUITE_ADD_TEST(suite, testDestroyBinaryTree);

    return suite;

}


void binaryTreeUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Binary Tree Test**\n");

    CuSuite *suite = createBinaryTreeTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}