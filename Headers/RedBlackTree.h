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
    RBNode * root;
    uint32_t nodeCount;
    int16_t (*cmp)(const void*,const void *);
}RBTree;

RBNode* RBTreeInsert(RBTree *pRBTree,void *key);

#endif //C_DATASTRUCTURES_REDBLACKTREE_H
