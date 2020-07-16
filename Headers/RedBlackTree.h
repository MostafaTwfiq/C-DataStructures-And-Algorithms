#ifndef C_DATASTRUCTURES_REDBLACKTREE_H
#define C_DATASTRUCTURES_REDBLACKTREE_H
#include "Utils.h"

typedef enum COLOR {
    RED,
    BLACK
}COLOR;




typedef struct  RBNode {
    void *key;
    COLOR color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
}RBNode;



typedef struct RBTree{
    struct RBNode *root;
    int nodeCount;
    void (*freeItem)(void *);
    int (*cmp)(const void*, const void *);
}RBTree;




RBTree *redBlackTreeInitialization(void (*freeItem)(void *), int (*cmp)(const void*, const void *));


void rBTreeInsert(RBTree *tree, void *item);


void rBInOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));


void rBTreeDelete(RBTree *tree, void *item);


void *rBTreeDeleteWtoFr(RBTree *tree, void *item);


void *rbTreeGet(RBTree *tree, char *item);


void **rBTreeToArray(RBTree *rbTree);


int rBTreeGetSize(RBTree *tree);


int rBTreeContains(RBTree *tree, void *item);


void rBPreOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));


void rBTreePrint(RBTree *tree, void (*printFun)(const void *, COLOR));


void rBPostOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));


void clearRBTree(RBTree *tree);


void destroyRBTree(RBTree *tree);


void rBInsertAll(RBTree* rbTree, void** array, int length);


#endif //C_DATASTRUCTURES_REDBLACKTREE_H
