#ifndef C_DATASTRUCTURES_BINARYTREE_H
#define C_DATASTRUCTURES_BINARYTREE_H
#include "Utils.h"
#define COUNT 10

typedef struct BinaryTreeNode{
    void *key;
    struct BinaryTreeNode * right;
    struct BinaryTreeNode * left;
}BinaryTreeNode;

typedef struct BinaryTree{
    BinaryTreeNode *root;
    int sizeOfType;
    unsigned int nodeCount;
    int(*cmp)(const void*, const void*);
}BinaryTree;



BinaryTreeNode* DeleteBinaryTreeNode(BinaryTree *binaryTree, BinaryTreeNode* root, void *key);

int getMinStepsBinaryTree(BinaryTreeNode* node);

int getMaxBinaryTreeSteps(BinaryTreeNode* node);

int getSizeBinaryTree(BinaryTreeNode *root);

int isPresentInBinaryTree(BinaryTree *binaryTree, BinaryTreeNode *root, void *searchKey);

void printBinaryTree(BinaryTreeNode *root, void (printFn)(void *));

void inOrderPredecessorBinaryTree(BinaryTree *binaryTree, BinaryTreeNode *root, BinaryTreeNode *targetNode, BinaryTreeNode **rightMost);

void inOrderSuccessorBinaryTree(BinaryTree *binaryTree, BinaryTreeNode* root, BinaryTreeNode* targetNode, BinaryTreeNode **leftMost);

BinaryTreeNode* insertBinaryTree(BinaryTree * binaryTree, BinaryTreeNode *node, void *key);

BinaryTreeNode *searchBinaryTree(BinaryTree *avlTree, BinaryTreeNode *node, char *key);

void **BinaryTreeToArray(BinaryTree *binaryTree);

void freeBinaryTree(BinaryTreeNode **node);

BinaryTree* BinaryTreeInitialize(int size, int(*cmp)(const void*, const void*));

void printBinaryTreeStats(BinaryTree *tree);

BinaryTreeNode * maxValueBinaryTreeNode(BinaryTreeNode* node);

BinaryTreeNode * minValueBinaryTreeNode(BinaryTreeNode* node);

void printInOrderBinaryTree(BinaryTreeNode* node, void (printFn)(void *));

BinaryTreeNode * BinaryTreeInsertAll(BinaryTree* binaryTree, void** array, int length);


#endif //C_DATASTRUCTURES_BINARYTREE_H
