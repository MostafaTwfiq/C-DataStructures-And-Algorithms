#ifndef C_DATASTRUCTURES_BINARYTREE_H
#define C_DATASTRUCTURES_BINARYTREE_H

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
 *  @var BinaryTree::count
 *  Member 'count' holds the number of nodes currently present in the tree.
 *  @var BinaryTree::cmp
 *  Member 'cmp' is a pointer to the comparison function that is going to be used throughout the tree.
 *  @var BinaryTree::freeFn
 *  Member 'freeFn' is a pointer to the free function that is going to be used throughout the tree.
 */

typedef struct BinaryTree {
    BinaryTreeNode *root;
    int count;

    int (*cmp)(const void *, const void *);

    void (*freeFn)(void *);
} BinaryTree;


BinaryTree *binaryTreeInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *));

void binaryTreeInsert(BinaryTree *tree, void *item);

void binaryTreeInsertAll(BinaryTree *tree, void **items, int length);

void binaryTreeDelete(BinaryTree *tree, void *item);

void *binaryTreeDeleteWtoFr(BinaryTree *tree, void *item);

int binaryTreeContains(BinaryTree *tree, void *item);

void *binaryTreeGet(BinaryTree *tree, void *item);

void binaryTreePreOrderTraversal(BinaryTree *tree, void (*printFun)(void *));

void binaryTreeInOrderTraversal(BinaryTree *tree, void (*printFun)(void *));

void binaryTreePostOrderTraversal(BinaryTree *tree, void (*printFun)(void *));

int binaryTreeGetSize(BinaryTree *tree);

int binaryTreeIsEmpty(BinaryTree *tree);

void **binaryTreeToArray(BinaryTree *tree);

void clearBinaryTree(BinaryTree *tree);

void destroyBinaryTree(void *tree);


#ifdef __cplusplus
}
#endif


#endif //C_DATASTRUCTURES_BINARYTREE_H
