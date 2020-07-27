#ifndef C_DATASTRUCTURES_BINARYTREE_H
#define C_DATASTRUCTURES_BINARYTREE_H
#include "stdint.h"
#define COUNT 10

#ifdef __cplusplus
extern "C" {
#endif


/** @struct BinaryTreeNode
 *  @brief This structure describes n Binary Tree Node.
 *  @var BinaryTreeNode:: key
 *  Member 'key' is a pointer a pre-allocated object.
 *  @var BinaryTreeNode::left
 *  Member 'left' holds a reference to the left Node if present else it is Null.
 *  @var BinaryTreeNode::right
 *  Member 'right' holds a reference to the right Node if present else it is Null.
 */
typedef struct BinaryTreeNode {
    void *key;
    struct BinaryTreeNode *right;
    struct BinaryTreeNode *left;
} BinaryTreeNode;

/** @struct BinaryTree
 *  @brief This structure implements a basic generic Binary Tree.
 *  @var BinaryTree:: root
 *  Member 'root' is a pointer to the root Node of the tree.
 *  @var BinaryTree::nodeCount
 *  Member 'nodeCount' holds the number of nodes currently present in the tree.
 *  @var BinaryTree::cmp
 *  Member 'cmp' is a pointer to the comparision function that is going to be used throughout the tree.
 */
typedef struct BinaryTree {
    BinaryTreeNode *root;
    uint32_t nodeCount;
    int (*cmp)(const void *, const void *);
    void (*freeFn)(void *);
} BinaryTree;


void DeleteBinaryTreeNodeWithFree(BinaryTree *binaryTree, void *key);

void DeleteBinaryTreeNodeWithoutFree(BinaryTree *binaryTree, void *key);

int BinaryTreeGetMinSteps(BinaryTreeNode *node);

int BinaryTreeGetMaxSteps(BinaryTreeNode *node);

int BinaryTreeGetSize(BinaryTreeNode *root);

int BinaryTreeIsPresent(BinaryTree *binaryTree, void *searchKey);

void BinaryTreePrint(BinaryTreeNode *root, void (printFn)(void *));

BinaryTreeNode* BinaryTreeInOrderPredecessor(BinaryTree *binaryTree, void *key);

BinaryTreeNode* BinaryTreeInOrderSuccessor(BinaryTree *binaryTree, void *key);

void BinaryTreeInsert(BinaryTree *binaryTree, void *key);

BinaryTreeNode* BinaryTreeSearch(BinaryTree* binaryTree, void * key);

void **BinaryTreeToArray(BinaryTree *binaryTree);

void destroyBinaryTree(BinaryTree* binaryTree);

BinaryTree* binaryTreeInitialization(void (*freeFn)(void *), int (*cmp)(const void*, const void*));

void printBinaryTreeStats(BinaryTree *tree);

BinaryTreeNode *maxValueBinaryTreeNode(BinaryTreeNode *node);

BinaryTreeNode *BinaryTreeMinValueNode(BinaryTreeNode *node);

void BinaryTreePrintInOrder(BinaryTreeNode *node, void (printFn)(void *));

void BinaryTreeInsertAll(BinaryTree *binaryTree, void **array, uint32_t length);

uint32_t BinaryTreeContains(BinaryTree * tree, void *item);

uint32_t isEqual(BinaryTree *binaryTree,BinaryTree *binaryTree2);

void BinaryTreeMirror(BinaryTree* tree);

#ifdef __cplusplus
}
#endif


#endif //C_DATASTRUCTURES_BINARYTREE_H
