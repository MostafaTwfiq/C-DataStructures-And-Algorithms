#ifndef C_DATASTRUCTURES_SPLAYTREE_H
#define C_DATASTRUCTURES_SPLAYTREE_H
#include "Utils.h"
#define COUNT 10

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
 *  @var SplayTree::nodeCount
 *  Member 'nodeCount' holds the number of nodes currently present in the tree.
 *  @var SplayTree::cmp
 *  Member 'cmp' is a pointer to the comparision function that is going to be used throughout the tree.
 */
typedef struct SplayTree {
    SplayNode *root;
    uint32_t nodeCount;
    int16_t (*cmp)(const void *, const void *);
    void (*freeFn)(void *);
} SplayTree;


SplayNode *newSplayNode(void *key);

SplayTree *SplayTreeInitialize(int16_t (*cmp)(const void *, const void *));

SplayNode *SplayRightRotate(SplayNode *x);

SplayNode *SplayLeftRotate(SplayNode *x);

SplayNode *splay(SplayTree *splayTree, SplayNode *root, void *key);

SplayNode *SplayTreeSearch(SplayTree *splayTree, void *key);

void SplayTreeInsert(SplayTree *splayTree, void *key);

void SplayTreeDelete(SplayTree *splayTree, void *key);

void freeSplayNode(SplayNode **node, void (*pFunction)(void *));

void SplayTreeFree(SplayNode **root, void (*pFunction)(void *));

void printInOrderSplayTree(SplayNode *node, void (printFn)(void *));

void printSplayTree(SplayNode *root, void (printFn)(void *));

void SplayTreeInsertAll(SplayTree *splayTree, void **array, int length);

void **SplayTreeToArray(SplayTree *splayTree);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_SPLAYTREE_H
