#ifndef C_DATASTRUCTURES_REDBLACKTREE_H
#define C_DATASTRUCTURES_REDBLACKTREE_H
#include "Utils.h"

typedef enum COLOR {
    RED,
    BLACK
}COLOR;




typedef struct RBTreeItem {
    void *value;
    int sizeOfItem;
} RBTreeItem;




typedef struct  RBNode {
    RBTreeItem *key;
    COLOR color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
}RBNode;



typedef struct RBTree{
    struct RBNode *root;
    int nodeCount;
    void (*freeItem)(void *item);
    int (*cmp)(const void*, int, const void *, int);
}RBTree;




RBTree *redBlackTreeInitialization(void (*freeItem)(void *item), int (*cmp)(const void*, int, const void *, int));


void rBTreeInsert(RBTree *tree, void *item, int sizeOfItem);


void rBInOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));


void rBTreeDelete(RBTree *tree, void *item, int sizeOfItem);


void *rbTreeGet(RBTree *tree, char *item, int sizeOfItem);


void **rBTreeToArray(RBTree *rbTree);


int rBTreeGetSize(RBTree *tree);


int rBTreeContains(RBTree *tree, void *item, int sizeOfItem);


void rBPreOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));


void rBTreePrint(RBTree *tree, void (*printFun)(const void *, COLOR));


void rBPostOrderTraversal(RBTree *tree, void (*printFun)(const void *, COLOR));


void clearRBTree(RBTree *tree);


void destroyRBTree(RBTree *tree);


void rBInsertAll(RBTree* rbTree, void** array, int length, int sizeOfItem);


#endif //C_DATASTRUCTURES_REDBLACKTREE_H
