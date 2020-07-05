#ifndef C_DATASTRUCTURES_BINARYTREE_H
#define C_DATASTRUCTURES_BINARYTREE_H
#include "Utils.h"
#define COUNT 10

/** @struct BinaryTreeNode
 *  @brief This structure describes n Binary Tree Node.
 *  @var BinaryTreeNode:: key
 *  Member 'key' is a pointer a pre-allocated object.
 *  @var BinaryTreeNode::left
 *  Member 'left' holds a reference to the left Node if present else it is Null.
 *  @var BinaryTreeNode::right
 *  Member 'right' holds a reference to the right Node if present else it is Null.
 */
typedef struct BinaryTreeNode{
    void *key;
    struct BinaryTreeNode * right;
    struct BinaryTreeNode * left;
}BinaryTreeNode;

/** @struct BinaryTree
 *  @brief This structure implements a basic generic Binary Tree.
 *  @var BinaryTree:: root
 *  Member 'root' is a pointer to the root Node of the tree.
 *  @var BinaryTree::nodeCount
 *  Member 'nodeCount' holds the number of nodes currently present in the tree.
 *  @var BinaryTree::cmp
 *  Member 'cmp' is a pointer to the comparision function that is going to be used throughout the tree.
 */
typedef struct BinaryTree{
    BinaryTreeNode *root;
    uint32_t  nodeCount;
    uint32_t sizeOfType;
    int(*cmp)(const void*, const void*);
}BinaryTree;



BinaryTreeNode* DeleteBinaryTreeNode(BinaryTree *binaryTree, BinaryTreeNode* root, void *key);

int BinaryTreeGetMinSteps(BinaryTreeNode* node);

int BinaryTreeGetMaxSteps(BinaryTreeNode* node);

int BinaryTreeGetSize(BinaryTreeNode *root);

int BinaryTreeIsPresent(BinaryTree *binaryTree, void *searchKey);

void BinaryTreePrint(BinaryTreeNode *root, void (printFn)(void *));

void BinaryTreeInOrderPredecessor(BinaryTree *binaryTree, BinaryTreeNode *root, BinaryTreeNode *referenceNode, BinaryTreeNode **rightMost);

void BinaryTreeInOrderSuccessor(BinaryTree *binaryTree, BinaryTreeNode* root, BinaryTreeNode* referenceNode, BinaryTreeNode **leftMost);

BinaryTreeNode* BinaryTreeInsert(BinaryTree * binaryTree, BinaryTreeNode *node, void *key);

BinaryTreeNode *BinaryTreeSearch(BinaryTree *binaryTree, BinaryTreeNode *node, char *key);

void **BinaryTreeToArray(BinaryTree *binaryTree);

void BinaryTreeFree(BinaryTreeNode **node);

BinaryTree* BinaryTreeInitialize(int size,int(*cmp)(const void*, const void*));

void printBinaryTreeStats(BinaryTree *tree);

BinaryTreeNode * maxValueBinaryTreeNode(BinaryTreeNode* node);

BinaryTreeNode * BinaryTreeMinValueNode(BinaryTreeNode* node);

void BinaryTreePrintInOrder(BinaryTreeNode* node, void (printFn)(void *));

BinaryTreeNode * BinaryTreeInsertAll(BinaryTree* binaryTree, void** array, int length);


#endif //C_DATASTRUCTURES_BINARYTREE_H
