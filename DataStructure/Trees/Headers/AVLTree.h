#ifndef C_DATASTRUCTURES_AVLTREE_H
#define C_DATASTRUCTURES_AVLTREE_H
#include "../../../System/Utils.h"
#include <math.h>
#define COUNT 10

#ifdef __cplusplus
extern "C" {
#endif


/** @struct AVLTreeNode
 *  @brief This structure describes n AVL Tree Node.
 *  @var AVLTreeNode::key
 *  Member 'key' is a pointer a pre-allocated object.
 *  @var AVLTreeNode::height
 *  Member 'height' holds the current height of the node.
 *  @var AVLTreeNode::left
 *  Member 'left' holds a reference to the left Node if present else it is Null.
 *  @var AVLTreeNode::right
 *  Member 'right' holds a reference to the right Node if present else it is Null.
 */
typedef struct AVLTreeNode {
    void *key;
    int32_t height;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
} AVLTreeNode;


/** @struct AVLTree
 *  @brief This structure implements a basic generic AVL Tree.
 *  @var AVLTree::root
 *  Member 'root' is a pointer to the root Node of the tree.
 *  @var AVLTree::nodeCount
 *  Member 'nodeCount' holds the number of nodes currently present in the tree.
 *  @var AVLTree::cmp
 *  Member 'cmp' is a pointer to the comparision function that is going to be used throughout the tree.
 */
typedef struct AVLTree {
    AVLTreeNode *root;
    uint32_t nodeCount;
    uint32_t sizeOfType;
    int (*cmp)(const void *, const void *);
    void    (*freeFn)(void *);
} AVLTree;


void AVLTreeDeleteNodeWithFree(AVLTree *avlTree, void *key);

void AVLTreeDeleteNodeWithoutFree(AVLTree *avlTree, void *key);

int32_t AVLTreeGetMinSteps(AVLTreeNode *node);

int32_t AVLTreeGetMaxSteps(AVLTreeNode *node);

int32_t AVLTreeGetSize(AVLTreeNode *root);

int32_t AVLTreeIsPresent(AVLTree *avlTree, void *searchKey);

void AVLTreePrint(AVLTreeNode *root, void (printFn)(void *));

AVLTreeNode* AVLInOrderPredecessor(AVLTree *avlTree,AVLTreeNode *referenceNode);

AVLTreeNode* AVLInOrderSuccessor(AVLTree *avlTree, AVLTreeNode *referenceNode);

void AVLTreeInsert(AVLTree *avlTree, void *key);

AVLTreeNode *AVLTreeSearch(AVLTree *avlTree, AVLTreeNode *node, char *key);

void **AVLTreeToArray(AVLTree *avlTree);

void AVLTreeFree(AVLTree* avlTree);

AVLTree *AVLTreeInitialize(int32_t size, int32_t (*cmp)(const void *, const void *), void (*freeFn)(void *));

void AVLTreePrintStats(AVLTree *tree);

AVLTreeNode *AVLTreeMaxValueNode(AVLTreeNode *node);

AVLTreeNode *AVLTreeMinValueNode(AVLTreeNode *node);

void AVLTreePrintInOrder(AVLTreeNode *node, void (printFn)(void *));

AVLTreeNode *AVLTreeInsertAll(AVLTree *avlTree, void **array, uint32_t length);

#ifdef __cplusplus
}
#endif

#endif//C_DATASTRUCTURES_AVLTREE_H
