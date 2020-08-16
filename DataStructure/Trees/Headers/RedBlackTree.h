#ifndef C_DATASTRUCTURES_REDBLACKTREE_H
#define C_DATASTRUCTURES_REDBLACKTREE_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum COLOR {
    RED,
    BLACK
} COLOR;


/** @struct RBNode
*  @brief This structure implements a basic RED BLACK Tree node.
*  @var RBNode::key
*  Member 'key' is a pointer to the node value.
*  @var RBNode::color
*  Member 'color' hold the current color of the node.
*  @var RBNode::left
*  Member 'left' is a pointer to the left node.
*  @var RBNode::right
*  Member 'right' is a pointer to the right node.
*  @var RBNode::parent
*  Member 'parent' is a pointer to the parent node.
*/

typedef struct RBNode {
    void *key;
    COLOR color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;


/** @struct RBTree
*  @brief This structure implements a basic generic RED BLACK Tree.
*  @var RBTree::root
*  Member 'root' is a pointer to the root node.
*  @var RBTree::count
*  Member 'count' hold the current number of nodes.
*  @var RBTree::freeItem
*  Member 'freeItem' is a pointer to the free function, that will be called to free the tree values.
*  @var RBTree::cmp
*  Member 'cmp' is a pointer to the comparator function, that will be called to compare the tree values.
*/

typedef struct RBTree {
    struct RBNode *root;
    int nodeCount;

    void (*freeItem)(void *);

    int (*cmp)(const void *, const void *);
} RBTree;


RBTree *redBlackTreeInitialization(void (*freeItem)(void *), int (*cmp)(const void *, const void *));

void rBTreeInsert(RBTree *tree, void *item);

void rBTreeDelete(RBTree *tree, void *item);

void *rBTreeDeleteWtoFr(RBTree *tree, void *item);

void *rbTreeGet(RBTree *tree, void *item);

void **rBTreeToArray(RBTree *rbTree);

int rBTreeGetSize(RBTree *tree);

int rBTreeContains(RBTree *tree, void *item);

void rBTreePrint(RBTree *tree, void (*printFun)(const void *, COLOR));

void rBPreOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));

void rBInOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));

void rBPostOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));

void clearRBTree(RBTree *tree);

void destroyRBTree(void *tree);

void rBInsertAll(RBTree *rbTree, void **array, int length);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_REDBLACKTREE_H
