#ifndef C_DATASTRUCTURES_SPLAYTREE_H
#define C_DATASTRUCTURES_SPLAYTREE_H
#include "Utils.h"
#define COUNT 10

typedef struct SplayNode{
    void * key;
    struct SplayNode *right;
    struct SplayNode *left;
}SplayNode;

typedef struct SplayTree{
    SplayNode *root;
    uint32_t nodeCount;
    int16_t (*cmp)(const void *,const void *);
}SplayTree;


SplayNode* newSplayNode(void* key);

SplayTree *SplayTreeInitialize(int16_t (*cmp)(const void *,const void *));

SplayNode *rightRotateSplay(SplayNode *x);

SplayNode *leftRotateSplay(SplayNode *x);

SplayNode *splay(SplayTree *splayTree,SplayNode *root,void *key);

SplayNode *SplayTreeSearch(SplayTree *splayTree,void *key);

void SplayTreeInsert(SplayTree* splayTree, void *key);

void  SplayTreeDelete(SplayTree* splayTree, void *key);

void freeSplayNode(SplayNode **node);

void freeSplayTree(SplayNode **root);

void printInOrderSplayTree(SplayNode* node, void (printFn)(void *));

void printSplayTree(SplayNode *root, void (printFn)(void *));

void SplayTreeInsertAll(SplayTree* splayTree, void** array, int length);

void **SplayTreeToArray(SplayTree *splayTree);

#endif //C_DATASTRUCTURES_SPLAYTREE_H
