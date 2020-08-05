#include "RedBlackTreeTest.h"
#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../DataStructure/Trees/Headers/RedBlackTree.h"


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BOLD_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BOLD_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BOLD_YELLOW  "\x1b[01;33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_BOLD_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BOLD_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BOLD_CYAN    "\x1b[1;36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"




/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
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
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is bigger, and positive number if the first integer is bigger.
 */

int compareIntPointersRBTT(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}





void testInvalidRBTreeInitialization(CuTest *cuTest) {

    redBlackTreeInitialization(NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    redBlackTreeInitialization(free, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

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

    if      (
            (parent != NULL && parent->color == RED && root->color == RED)
            || leftBlackCount != rightBlackCount
            || leftBlackCount == -1
            || rightBlackCount == -1
            )
    {

        return -1;

    }


    return leftBlackCount;

}




int checkIfValidBinaryTree(RBNode *root, RBNode *parent) {

    if (root == NULL)
        return 1;

    if (parent != NULL) {

        if (parent->right == root) {

            return
            compareIntPointersRBTT(parent->key, root->key) < 0
            ? checkIfValidBinaryTree(root->left, root) && checkIfValidBinaryTree(root->right, root)
            : 0;

        } else {

            return
            compareIntPointersRBTT(parent->key, root->key) > 0
            ? checkIfValidBinaryTree(root->left, root) && checkIfValidBinaryTree(root->right, root)
            : 0;

        }

    }

    return checkIfValidBinaryTree(root->left, root) && checkIfValidBinaryTree(root->right, root);


}


void printFunRBTT(const void *item, COLOR color) {
    if (color == RED) {
        printf(ANSI_COLOR_RED "%d" ANSI_COLOR_RESET, *(int *) item);
    } else {
        printf("%d", *(int *) item);
    }
}


void testRBTreeInsert(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeInsert(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    rBTreeInsert(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++) {

        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTree(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

    }


    destroyRBTree(tree);

}



void testRBTreeContains(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    rBTreeContains(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

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
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    rBTreeDelete(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    for (int i = 0; i < 13; i++) {
        rBTreeDelete(tree, valuesArr + i);
        CuAssertIntEquals(cuTest, 0, rBTreeContains(tree, valuesArr + i));
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTree(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);
    }


    destroyRBTree(tree);

}



void testRBTreeDeleteWtoFr(CuTest *cuTest) {

    RBTree *tree = redBlackTreeInitialization(free, compareIntPointersRBTT);

    rBTreeDeleteWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    rBTreeDeleteWtoFr(tree, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    int valuesArr[] = {10, 20, 8, 7, 9, 15, 21, 22, 25, 4, 1, 2, 100};

    for (int i = 0; i < 13; i++)
        rBTreeInsert(tree, generateIntPointerRBTT(valuesArr[i]));

    int *tempValue;

    for (int i = 0; i < 13; i++) {

        tempValue = (int *) rBTreeDeleteWtoFr(tree, valuesArr + i);
        CuAssertIntEquals(cuTest, valuesArr[i], *tempValue);
        CuAssertIntEquals(cuTest, 0, rBTreeContains(tree, valuesArr + i));
        CuAssertIntEquals(cuTest, 1, checkIfValidBinaryTree(tree->root, NULL));
        CuAssertIntEquals(cuTest, 1, checkIfValidRBTree(NULL, tree->root, 0) == -1 ? 0 : 1);

        free(tempValue);
        
    }


    destroyRBTree(tree);

}







CuSuite *createRedBlackTreeTestsSuite() {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidRBTreeInitialization);
    SUITE_ADD_TEST(suite, testValidRBTreeInitialization);
    SUITE_ADD_TEST(suite, testRBTreeInsert);
    SUITE_ADD_TEST(suite, testRBTreeContains);
    SUITE_ADD_TEST(suite, testRBTreeDelete);
    SUITE_ADD_TEST(suite, testRBTreeDeleteWtoFr);

    return suite;

}



void redBlackTreeUnitTest() {

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Red Black Tree Test**\n");

    CuSuite *suite = createRedBlackTreeTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}