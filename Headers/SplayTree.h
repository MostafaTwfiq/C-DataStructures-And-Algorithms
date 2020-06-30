#ifndef C_DATASTRUCTURES_SPLAYTREE_H
#define C_DATASTRUCTURES_SPLAYTREE_H
#include "Utils.h"

typedef struct SplayNode{
    void * key;
    struct SplayNode *right;
    struct SplayNode *left;
}SplayNode;

typedef struct SplayTree{
    SplayNode *root;
    uint32_t sizeOfType;
    uint32_t nodeCount;
    uint16_t (*cmp)(const void *,const void *);
}SplayTree;



#endif //C_DATASTRUCTURES_SPLAYTREE_H
