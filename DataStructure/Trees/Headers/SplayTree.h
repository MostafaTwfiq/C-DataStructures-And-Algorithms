#ifndef C_DATASTRUCTURES_SPLAYTREE_H
#define C_DATASTRUCTURES_SPLAYTREE_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct SplayNode
 *  @brief This structure describes n Splay Tree Node.
 *  @var SplayNode::key
 *  Member 'key' is a pointer a pre-allocated object.
 *  @var SplayNode::left
 *  Member 'left' holds a reference to the left Node if present else it is Null.
 *  @var SplayNode::right
 *  Member 'right' holds a reference to the right Node if present else it is Null.
 */
typedef struct SplayNode {
    void *key;
    struct SplayNode *right;
    struct SplayNode *left;
} SplayNode;


/** @struct SplayTree
 *  @brief This structure implements a basic generic Splay Tree.
 *  @var SplayTree::root
 *  Member 'root' is a pointer to the root Node of the tree.
 *  @var SplayTree::count
 *  Member 'count' holds the number of nodes currently present in the tree.
 *  @var SplayTree::freeFn
 *  Member 'freeFn' is a pointer to the free function that is going to be used throughout the tree.
 *  @var SplayTree::cmp
 *  Member 'cmp' is a pointer to the comparison function that is going to be used throughout the tree.
 */
typedef struct SplayTree {
    SplayNode *root;
    int count;

    void (*freeFn)(void *);

    int (*cmp)(const void *, const void *);
} SplayTree;


SplayTree *splayTreeInitialization(void (*freeFn)(void *), int (*cmp)(const void *, const void *));

void splayTreeInsert(SplayTree *tree, void *item);

void splayTreeInsertAll(SplayTree *tree, void **items, int length);

void splayTreeDelete(SplayTree *tree, void *item);

void *splayTreeDeleteWtoFr(SplayTree *tree, void *item);

int splayTreeContains(SplayTree *tree, void *item);

void *splayTreeGet(SplayTree *tree, void *item);

int splayTreeGetSize(SplayTree *tree);

int splayTreeIsEmpty(SplayTree *tree);

void **splayTreeToArray(SplayTree *tree);

void clearSplayTree(SplayTree *tree);

void destroySplayTree(void *tree);


#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_SPLAYTREE_H
