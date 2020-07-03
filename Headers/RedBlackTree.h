#ifndef C_DATASTRUCTURES_REDBLACKTREE_H
#define C_DATASTRUCTURES_REDBLACKTREE_H
#include "Utils.h"

typedef enum COLOR {
    RED,
    BLACK
}COLOR;


typedef struct  RBNode {
    void * key;
    COLOR color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
}RBNode;


typedef struct RBTree{
    RBNode *root;
    uint32_t nodeCount;
    int sizeOfType;
    int (*cmp)(const void*, const void *);
}RBTree;

RBTree *redBlackTreeInitialization(int sizeOfType, int (*cmp)(const void*, const void *));
void rBTreeInsert(RBTree *tree, void *item);
void rBPreOrderTraversal(RBTree *tree, void (*printFun)(const void *item, COLOR color));
void rBTreeDelete(RBTree *tree, void *item);
void RBTreePrint(RBNode *root, void (printFn)(void *,int type));
RBNode *RBTreeSearch(RBTree *rbTree, RBNode *node, char *key);
#endif //C_DATASTRUCTURES_REDBLACKTREE_H
