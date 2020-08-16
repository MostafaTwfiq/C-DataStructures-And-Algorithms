#include "AVLTreeTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Trees/Headers/AVLTree.h"


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 *
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerAVLTT(int integer) {
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

int compareIntPointersAVLTT(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function returns the passed node height,
 * and if the node was NULL, the function will return minus one (-1).
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the node height, and if the node was NULL the function will return -1
 */

int avlTreeGetNodeHeightAVLTT(AVLTreeNode *node) {
    return node == NULL ? -1 : node->height;
}


/** This function takes two integers,
 * then it returns  the largest integer.
 *
 * Note: this function should only be called from the inside.
 *
 * @param a the first integer value
 * @param b the second integer value
 * @return it will return the largest integer
 */

int avlTreeGetMaxIntAVLTT(int a, int b) {
    return a > b ? a : b;
}


int avlTreeCalculateNodeHeightAVLTT(AVLTreeNode *node) {
    return avlTreeGetMaxIntAVLTT(avlTreeGetNodeHeightAVLTT(node->left), avlTreeGetNodeHeightAVLTT(node->right)) + 1;
}


int avlTreeIsRequiredRotationAVLTT(AVLTreeNode *node) {
    int value = avlTreeGetNodeHeightAVLTT(node->left) - avlTreeGetNodeHeightAVLTT(node->right);
    value = value < 0 ? value * -1 : value;
    return value >= 2;
}


int checkIfValidAVLTreeAVLTT(AVLTreeNode *root, AVLTreeNode *parent) {

    if (root == NULL)
        return 1;

    if (parent != NULL) {

        if (parent->right == root) {

            return
                    !avlTreeIsRequiredRotationAVLTT(root)
                    && (compareIntPointersAVLTT(parent->key, root->key) < 0 ||
                        compareIntPointersAVLTT(parent->key, root->key) == 0)

                    ? checkIfValidAVLTreeAVLTT(root->left, root) && checkIfValidAVLTreeAVLTT(root->right, root)

                    : 0;

        } else {

            return
                    !avlTreeIsRequiredRotationAVLTT(root)
                    && compareIntPointersAVLTT(parent->key, root->key) > 0

                    ? checkIfValidAVLTreeAVLTT(root->left, root) && checkIfValidAVLTreeAVLTT(root->right, root)

                    : 0;

        }

    }

    return !avlTreeIsRequiredRotationAVLTT(root)
           && checkIfValidAVLTreeAVLTT(root->left, root)
           && checkIfValidAVLTreeAVLTT(root->right, root);


}


void testInvalidAVLTreeInitialization(CuTest *cuTest) {

    avlTreeInitialization(NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    avlTreeInitialization(free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidAVLTreeInitialization(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    CuAssertPtrNotNull(cuTest, tree);

    destroyAVLTree(tree);

}


void testAVLTreeInsert(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeInsert(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreeInsert(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));

    destroyAVLTree(tree);

}


void testAVLTreeInsert2(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};
    int values2[] = {13, 16, 3, 6, 9, 7, 28, 21};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    int tempValue;

    tempValue = 10;
    avlTreeDelete(tree, &tempValue);

    tempValue = 25;
    avlTreeDelete(tree, &tempValue);

    tempValue = 5;
    avlTreeDelete(tree, &tempValue);


    for (int i = 0; i < 8; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values2[i]));

    CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));

    destroyAVLTree(tree);

}


void testAVLTreeInsert3(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    for (int i = 0; i < 11; i++) {
        avlTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));

        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));
        CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));

    }

    destroyAVLTree(tree);

}


void testAVLTreeInsertAll(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlInsertAll(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlInsertAll(tree, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};
    int **valuesArr = (int **) malloc(sizeof(int *) * 11);

    for (int i = 0; i < 11; i++)
        valuesArr[i] = generateIntPointerAVLTT(values[i]);


    avlInsertAll(tree, (void **) valuesArr, 11);
    CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));


    free(valuesArr);
    destroyAVLTree(tree);

}


void testAVLTreeDelete(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeDelete(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreeDelete(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 0;
    avlTreeDelete(tree, &tempValue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    for (int i = 0; i < 11; i++) {

        avlTreeDelete(tree, values + i);

        CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));

    }

    destroyAVLTree(tree);

}


void testAVLTreeDeleteWtoFr(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreeDeleteWtoFr(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    int tempValue = 0;
    avlTreeDeleteWtoFr(tree, &tempValue);
    CuAssertIntEquals(cuTest, EMPTY_DATA_STRUCTURE, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    for (int i = 0; i < 11; i++) {

        void *item = avlTreeDeleteWtoFr(tree, values + i);

        CuAssertPtrNotNull(cuTest, item);
        CuAssertIntEquals(cuTest, values[i], *(int *) item);
        free(item);
        CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));

    }


    CuAssertPtrEquals(cuTest, NULL, avlTreeDeleteWtoFr(tree, values));

    destroyAVLTree(tree);

}


void testAVLTreeContains(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreeContains(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, 1, avlTreeContains(tree, values + i));


    int tempValue = 233;
    CuAssertIntEquals(cuTest, 0, avlTreeContains(tree, &tempValue));

    destroyAVLTree(tree);

}


void testAVLTreeGet(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeGet(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreeGet(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    for (int i = 0; i < 11; i++) {

        void *item = avlTreeGet(tree, values + i);

        CuAssertPtrNotNull(cuTest, item);
        CuAssertIntEquals(cuTest, values[i], *(int *) item);

    }


    int tempValue = 100;
    CuAssertPtrEquals(cuTest, NULL, avlTreeGet(tree, &tempValue));

    destroyAVLTree(tree);

}


int **printingArrBTT;

void printFunBTT(void *item) {

    *printingArrBTT++ = item;

}


void testAVLTreePreOrderTraversal(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreePreOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreePreOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};
    int preOrderArr[] = {20, 5, 3, 2, 4, 13, 10, 15, 35, 30, 40};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    printingArrBTT = (int **) malloc(sizeof(int *) * tree->count);
    int **tempPointer = printingArrBTT;

    avlTreePreOrderTraversal(tree, printFunBTT);

    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, preOrderArr[i], *tempPointer[i]);

    free(tempPointer);
    destroyAVLTree(tree);

}


void testAVLTreeInOrderTraversal(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeInOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreeInOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};
    int inOrderArr[] = {2, 3, 4, 5, 10, 13, 15, 20, 30, 35, 40};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    printingArrBTT = (int **) malloc(sizeof(int *) * tree->count);
    int **tempPointer = printingArrBTT;

    avlTreeInOrderTraversal(tree, printFunBTT);

    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, inOrderArr[i], *tempPointer[i]);

    free(tempPointer);
    destroyAVLTree(tree);

}


void testAVLTreePostOrderTraversal(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreePostOrderTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreePostOrderTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};
    int postOrderArr[] = {2, 4, 3, 10, 15, 13, 5, 30, 40, 35, 20};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    printingArrBTT = (int **) malloc(sizeof(int *) * tree->count);
    int **tempPointer = printingArrBTT;

    avlTreePostOrderTraversal(tree, printFunBTT);

    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, postOrderArr[i], *tempPointer[i]);

    free(tempPointer);
    destroyAVLTree(tree);

}


void testAVLTreeBreadthFirstTraversal(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeBreadthFirstTraversal(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    avlTreeBreadthFirstTraversal(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};
    int postOrderArr[] = {20, 5, 35, 3, 13, 30, 40, 2, 4, 10, 15};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    printingArrBTT = (int **) malloc(sizeof(int *) * tree->count);
    int **tempPointer = printingArrBTT;

    avlTreeBreadthFirstTraversal(tree, printFunBTT);

    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, postOrderArr[i], *tempPointer[i]);

    free(tempPointer);
    destroyAVLTree(tree);

}


void testAVLTreeGetSize(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, avlTreeGetSize(tree));


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++) {
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));
        CuAssertIntEquals(cuTest, i + 1, avlTreeGetSize(tree));
    }

    CuAssertIntEquals(cuTest, 11, avlTreeGetSize(tree));

    for (int i = 0; i < 11; i++) {
        avlTreeDelete(tree, values + i);
        CuAssertIntEquals(cuTest, 10 - i, avlTreeGetSize(tree));
    }


    CuAssertIntEquals(cuTest, 0, avlTreeGetSize(tree));

    destroyAVLTree(tree);

}


void testAVLTreeIsEmpty(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, avlTreeIsEmpty(tree));


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));

    CuAssertIntEquals(cuTest, 0, avlTreeIsEmpty(tree));

    for (int i = 0; i < 11; i++)
        avlTreeDelete(tree, values + i);


    CuAssertIntEquals(cuTest, 1, avlTreeIsEmpty(tree));

    destroyAVLTree(tree);

}


void testAVLTreeToArray(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    avlTreeToArray(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));


    int **treeArr = (int **) avlTreeToArray(tree);

    qsort(values, 11, sizeof(int), compareIntPointersAVLTT);

    for (int i = 0; i < 11; i++)
        CuAssertIntEquals(cuTest, values[i], *treeArr[i]);


    free(treeArr);
    destroyAVLTree(tree);

}


void testClearAVLTree(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    clearAVLTree(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 1, avlTreeIsEmpty(tree));

    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));

    CuAssertIntEquals(cuTest, 0, avlTreeIsEmpty(tree));

    clearAVLTree(tree);

    CuAssertIntEquals(cuTest, 1, checkIfValidAVLTreeAVLTT(tree->root, NULL));

    CuAssertIntEquals(cuTest, 1, avlTreeIsEmpty(tree));

    destroyAVLTree(tree);

}


void testDestroyAVLTree(CuTest *cuTest) {

    AVLTree *tree = avlTreeInitialization(free, compareIntPointersAVLTT);

    destroyAVLTree(NULL);

    int values[] = {10, 20, 30, 5, 4, 40, 35, 15, 13, 2, 3};

    for (int i = 0; i < 11; i++)
        avlTreeInsert(tree, generateIntPointerAVLTT(values[i]));

    destroyAVLTree(tree);

}


CuSuite *createAVLTreeTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidAVLTreeInitialization);
    SUITE_ADD_TEST(suite, testValidAVLTreeInitialization);
    SUITE_ADD_TEST(suite, testAVLTreeInsert);
    SUITE_ADD_TEST(suite, testAVLTreeInsert2);
    SUITE_ADD_TEST(suite, testAVLTreeInsert3);
    SUITE_ADD_TEST(suite, testAVLTreeInsertAll);
    SUITE_ADD_TEST(suite, testAVLTreeDelete);
    SUITE_ADD_TEST(suite, testAVLTreeDeleteWtoFr);
    SUITE_ADD_TEST(suite, testAVLTreeContains);
    SUITE_ADD_TEST(suite, testAVLTreeGet);
    SUITE_ADD_TEST(suite, testAVLTreePreOrderTraversal);
    SUITE_ADD_TEST(suite, testAVLTreeInOrderTraversal);
    SUITE_ADD_TEST(suite, testAVLTreePostOrderTraversal);
    SUITE_ADD_TEST(suite, testAVLTreeBreadthFirstTraversal);
    SUITE_ADD_TEST(suite, testAVLTreeGetSize);
    SUITE_ADD_TEST(suite, testAVLTreeIsEmpty);
    SUITE_ADD_TEST(suite, testClearAVLTree);
    SUITE_ADD_TEST(suite, testDestroyAVLTree);

    return suite;

}


void avlTreeUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**AVL Tree Test**\n");

    CuSuite *suite = createAVLTreeTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}