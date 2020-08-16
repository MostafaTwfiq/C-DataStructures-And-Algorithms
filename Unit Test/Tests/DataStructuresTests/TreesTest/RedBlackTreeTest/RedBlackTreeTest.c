#include "RedBlackTreeTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Trees/Headers/RedBlackTree.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 *
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerRBTT(int integer) {
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

int compareIntPointersRBTT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


void testInvalidRBTreeInitialization(CuTest *cuTest) {

    redBlackTreeInitialization(NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    redBlackTreeInitialization(free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidRBTreeInitialization(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    CuAssertPtrNotNull(cuTest, tree);

    destroyRBTree(tree);

}


int checkIfValidRBTree(RBNode *parent, RBNode *root, int blackCount) {

    if (root == NULL)
        return blackCount;

    int leftBlackCount = checkIfValidRBTree(root, root->left, root->color == BLACK ? blackCount + 1 : blackCount);
    int rightBlackCount = checkIfValidRBTree(root, root->right, root->color == BLACK ? blackCount + 1 : blackCount);

    if (
            (parent != NULL && parent->color == RED && root->color == RED)
            || leftBlackCount != rightBlackCount
            || leftBlackCount == -1
            || rightBlackCount == -1
            ) {

        return -1;

    }


    return leftBlackCount;

}


int checkIfValidBinaryTreeRBTT(RBNode *root, RBNode *parent) {

    if (root == NULL)
        return 1;

    if (parent != NULL) {

        if (parent->right == root) {

            return
                    compareIntPointersRBTT(parent->key, root->key) < 0 ||
                    compareIntPointersRBTT(parent->key, root->key) == 0
                    ? checkIfValidBinaryTreeRBTT(root->left, root) && checkIfValidBinaryTreeRBTT(root->right, root)
                    : 0;

        } else {

            return
                    compareIntPointersRBTT(parent->key, root->key) > 0
                    ? checkIfValidBinaryTreeRBTT(root->left, root) && checkIfValidBinaryTreeRBTT(root->right, root)
                    : 0;

        }

    }

    return checkIfValidBinaryTreeRBTT(root->left, root) && checkIfValidBinaryTreeRBTT(root->right, root);


}


void testRBTreeInsert(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeInsert(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBTreeInsert(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++) {

        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeRBTT(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

    }


    destroyRBTree(tree);

}


void testRBTreeInsert2(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++) {

        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeRBTT(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

    }


    for (int i = 0; i < 7; i++) {

        rBTreeDelete(tree, valuesArr + i);

        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeRBTT(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

    }


    int valuesArr2[] = {477, 43, 23, 1, 2, 33, 66, 67, 85, 4};
    for (int i = 0; i < 10; i++) {

        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr2[i]));

        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeRBTT(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

    }


    destroyRBTree(tree);

}


void testRBTreeInsertAll(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBInsertAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBInsertAll(tree, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};
    int **tempArr = (int **) malloc(sizeof(int *) * 13);

    for (int i = 0; i < 13; i++)
        tempArr[i] = generateIntPointerRBTT(valuesArr[i]);


    rBInsertAll(tree, (void **) tempArr, 13);

    CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeRBTT(tree->root, NULL));
    CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, rBTreeContains(tree, tempArr[i]));

    free(tempArr);
    destroyRBTree(tree);

}


void testRBTreeContains(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBTreeContains(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, 1, rBTreeContains(tree, valuesArr + i));


    int doesNotExistValuesArr[] = {3, 11, 12, 13, 23, 24, 50, 101, 33, 234};
    for (int i = 0; i < 10; i++)
        CuAssertIntEquals(cuTest, 0, rBTreeContains(tree, doesNotExistValuesArr + i));

    destroyRBTree(tree);

}


void testRBTreeDelete(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeDelete(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBTreeDelete(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    for (int i = 0; i < 13; i++) {
        rBTreeDelete(tree, valuesArr + i);
        CuAssertIntEquals(cuTest, 0, rBTreeContains(tree, valuesArr + i));
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeRBTT(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);
    }


    destroyRBTree(tree);

}


void testRBTreeDeleteWtoFr(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBTreeDeleteWtoFr(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    int *tempValue;

    for (int i = 0; i < 13; i++) {

        tempValue = (int *) rBTreeDeleteWtoFr(tree, valuesArr + i);
        CuAssertIntEquals(cuTest, valuesArr[i], *tempValue);
        CuAssertIntEquals(cuTest, 0, rBTreeContains(tree, valuesArr + i));
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTreeRBTT(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

        free(tempValue);

    }


    destroyRBTree(tree);

}


void testRBTreeGet(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rbTreeGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rbTreeGet(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, valuesArr[i], *(int *) rbTreeGet(tree, valuesArr + i));

    int tempValue = 122;
    CuAssertPtrEquals(cuTest, NULL, rbTreeGet(tree, &tempValue));

    destroyRBTree(tree);

}


void testRBTreeToArray(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    int **treeArr = (int **) rBTreeToArray(tree);

    qsort(valuesArr, 13, sizeof(int), compareIntPointersRBTT);

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, valuesArr[i], *treeArr[i]);


    free(treeArr);
    destroyRBTree(tree);

}


void testRBTreeGetSize(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++) {
        CuAssertIntEquals(cuTest, i, rBTreeGetSize(tree));
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));
    }

    CuAssertIntEquals(cuTest, 13, rBTreeGetSize(tree));

    destroyRBTree(tree);

}


void testClearRBTree(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    clearRBTree(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};


    CuAssertIntEquals(cuTest, 0, rBTreeGetSize(tree));

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    CuAssertIntEquals(cuTest, 13, rBTreeGetSize(tree));

    clearRBTree(tree);

    CuAssertIntEquals(cuTest, 0, rBTreeGetSize(tree));

    destroyRBTree(tree);

}


void testDestroyRBTree(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    destroyRBTree(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    destroyRBTree(tree);

}


int *RBTreeTestTraversalArr;

void printFunRBTT(const void *item, COLOR color) {
    *RBTreeTestTraversalArr++ = *(int *) item;
}


void testRBTreePreOrderTraversal(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBPreOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBPreOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    int traversalArr[] = {10, 8, 4, 1, 2, 7, 9, 20, 15, 22, 21, 25, 100};

    RBTreeTestTraversalArr = (int *) malloc(sizeof(int) * 13);
    int *tempPointer = RBTreeTestTraversalArr;

    rBPreOrderTraversal(tree, printFunRBTT);

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, traversalArr[i], tempPointer[i]);

    free(tempPointer);
    destroyRBTree(tree);

}


void testRBTreeInOrderTraversal(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBInOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBInOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    int traversalArr[] = {1, 2, 4, 7, 8, 9, 10, 15, 20, 21, 22, 25, 100};

    RBTreeTestTraversalArr = (int *) malloc(sizeof(int) * 13);
    int *tempPointer = RBTreeTestTraversalArr;

    rBInOrderTraversal(tree, printFunRBTT);

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, traversalArr[i], tempPointer[i]);

    free(tempPointer);
    destroyRBTree(tree);

}


void testRBTreePostOrderTraversal(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBPostOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBPostOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    int traversalArr[] = {2, 1, 7, 4, 9, 8, 15, 21, 100, 25, 22, 20, 10};

    RBTreeTestTraversalArr = (int *) malloc(sizeof(int) * 13);
    int *tempPointer = RBTreeTestTraversalArr;

    rBPostOrderTraversal(tree, printFunRBTT);

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, traversalArr[i], tempPointer[i]);

    free(tempPointer);
    destroyRBTree(tree);

}


void testRBTreePrint(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreePrint(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    rBTreePrint(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    int traversalArr[] = {100, 25, 22, 21, 20, 15, 10, 9, 8, 7, 4, 2, 1};

    RBTreeTestTraversalArr = (int *) malloc(sizeof(int) * 13);
    int *tempPointer = RBTreeTestTraversalArr;

    rBTreePrint(tree, printFunRBTT);

    for (int i = 0; i < 13; i++)
        CuAssertIntEquals(cuTest, traversalArr[i], tempPointer[i]);

    free(tempPointer);
    destroyRBTree(tree);

}


CuSuite *createRedBlackTreeTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidRBTreeInitialization);
    SUITE_ADD_TEST(suite, testValidRBTreeInitialization);
    SUITE_ADD_TEST(suite, testRBTreeInsert);
    SUITE_ADD_TEST(suite, testRBTreeInsertAll);
    SUITE_ADD_TEST(suite, testRBTreeContains);
    SUITE_ADD_TEST(suite, testRBTreeDelete);
    SUITE_ADD_TEST(suite, testRBTreeDeleteWtoFr);
    SUITE_ADD_TEST(suite, testRBTreeInsert2);
    SUITE_ADD_TEST(suite, testRBTreeGet);
    SUITE_ADD_TEST(suite, testRBTreeToArray);
    SUITE_ADD_TEST(suite, testRBTreeGetSize);
    SUITE_ADD_TEST(suite, testClearRBTree);
    SUITE_ADD_TEST(suite, testDestroyRBTree);
    SUITE_ADD_TEST(suite, testRBTreePreOrderTraversal);
    SUITE_ADD_TEST(suite, testRBTreeInOrderTraversal);
    SUITE_ADD_TEST(suite, testRBTreePostOrderTraversal);
    SUITE_ADD_TEST(suite, testRBTreePrint);

    return suite;

}


void redBlackTreeUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Red Black Tree Test**\n");

    CuSuite *suite = createRedBlackTreeTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}