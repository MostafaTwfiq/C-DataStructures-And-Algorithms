#ifndef C_DATASTRUCTURES_AVLTREE_H
#define C_DATASTRUCTURES_AVLTREE_H

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
    int height;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
} AVLTreeNode;


/** @struct AVLTree
 *  @brief This structure implements a basic generic AVL Tree.
 *  @var AVLTree::root
 *  Member 'root' is a pointer to the root Node of the tree.
 *  @var AVLTree::count
 *  Member 'count' holds the number of nodes currently present in the tree.
 *  @var AVLTree::freeFn
 *  Member 'freeFn' is a pointer to the free function that is going to be used throughout the tree.
 *  @var AVLTree::cmp
 *  Member 'cmp' is a pointer to the comparison function that is going to be used throughout the tree.
 */

typedef struct AVLTree {
    AVLTreeNode *root;
    int count;

    void (*freeFn)(void *);

    int (*cmp)(const void *, const void *);
} AVLTree;


AVLTree *avlTreeInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *));

void avlTreeInsert(AVLTree *tree, void *item);

void avlInsertAll(AVLTree *tree, void **items, int length);

void avlTreeDelete(AVLTree *tree, void *item);

void *avlTreeDeleteWtoFr(AVLTree *tree, void *item);

int avlTreeContains(AVLTree *tree, void *item);

void *avlTreeGet(AVLTree *tree, void *item);

int avlTreeGetSize(AVLTree *tree);

int avlTreeIsEmpty(AVLTree *tree);

void **avlTreeToArray(AVLTree *tree);

void avlTreePreOrderTraversal(AVLTree *tree, void (*printFun)(void *));

void avlTreeInOrderTraversal(AVLTree *tree, void (*printFun)(void *));

void avlTreePostOrderTraversal(AVLTree *tree, void (*printFun)(void *));

void avlTreeBreadthFirstTraversal(AVLTree *tree, void (*printFun)(void *));

void clearAVLTree(AVLTree *tree);

void destroyAVLTree(void *tree);


#ifdef __cplusplus
}
#endif

#endif//C_DATASTRUCTURES_AVLTREE_H
