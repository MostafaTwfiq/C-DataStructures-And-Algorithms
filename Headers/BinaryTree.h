#ifndef C_DATASTRUCTURES_BINARYTREE_H
#define C_DATASTRUCTURES_BINARYTREE_H
#include "Utils.h"
#define COUNT 10

typedef struct BTreeNode{
    void *key;
    struct BTreeNode * right;
    struct BTreeNode * left;
}BTreeNode;

typedef struct BinaryTree{
    BTreeNode *root;
    int sizeOfType;
    unsigned int nodeCount;
    int(*cmp)(const void*, const void*);
}BinaryTree;



BTreeNode* DeleteBinaryTreeNode(BinaryTree *binaryTree, BTreeNode* root, void *key);

int getMinStepsBinaryTree(BTreeNode* node);

int getMaxBinaryTreeSteps(BTreeNode* node);

int getSizeBinaryTree(BTreeNode *root);

int isPresentInBinaryTree(BinaryTree *binaryTree, BTreeNode *root, void *searchKey);

void printBinaryTree(BTreeNode *root, void (printFn)(void *));

void inOrderPredecessorBinaryTree(BinaryTree *binaryTree, BTreeNode *root, BTreeNode *targetNode, BTreeNode **rightMost);

void inOrderSuccessorBinaryTree(BinaryTree *binaryTree, BTreeNode* root, BTreeNode* targetNode, BTreeNode **leftMost);

BTreeNode* insertBinaryTree(BinaryTree * binaryTree, BTreeNode *node, void *key);

BTreeNode *searchBinaryTree(BinaryTree *avlTree,BTreeNode *node, char *key);

void** BinarytreeToArray(BinaryTree *binaryTree);

void freeBinaryTree(BTreeNode **node);

BinaryTree* BinaryTreeInitialize(int size, int(*cmp)(const void*, const void*));

void printBinaryTreeStats(BinaryTree *tree);

BTreeNode * maxValueBinaryTreeNode(BTreeNode* node);

BTreeNode * minValueBinaryTreeNode(BTreeNode* node);

void printInOrderBinaryTree(BTreeNode* node, void (printFn)(void *));


#endif //C_DATASTRUCTURES_BINARYTREE_H
