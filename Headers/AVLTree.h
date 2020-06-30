#ifndef C_DATASTRUCTURES_AVLTREE_H
#define C_DATASTRUCTURES_AVLTREE_H
#include "Utils.h"
#include <math.h>
#define COUNT 10

#ifndef AVL_BINTREE_STRUCT_
#define AVL_BINTREE_STRUCT_

typedef struct AVLTNode{
    void * key;
    int height;
    struct AVLTNode *left;
    struct AVLTNode *right;
}AVLTNode;

typedef struct AVLTree{
    AVLTNode *root;
    int sizeOfType;
    unsigned int nodeCount;
    int(*cmp)(const void*,const void*);
}AVLTree;

#endif


AVLTNode* AVLTreeDeleteNode(AVLTree *avlTree, AVLTNode* root, void *key);

int AVLTreeGetMinSteps(AVLTNode* node);

int AVLTreeGetMaxSteps(AVLTNode* node);

int AVLTreeGetSize(AVLTNode *root);

int AVLTreeIsPresent(AVLTree *avlTree, AVLTNode *root, void *searchKey);

void AVLTreePrint(AVLTNode *root, void (printFn)(void *));

void inOrderPredecessorAVLTree(AVLTree *avlTree, AVLTNode *root, AVLTNode *referenceNode, AVLTNode **rightMost);

void AVLTreeInOrderSuccessor(AVLTree *avlTree, AVLTNode* root, AVLTNode* referenceNode, AVLTNode **leftMost);

AVLTNode* AVLTreeInsert(AVLTree * avlTree, AVLTNode *node, void *key);

AVLTNode *AVLTreeSearch(AVLTree *avlTree, AVLTNode *node, char *key);

void **AVLTreeToArray(AVLTree *avlTree);

void AVLTreeFree(AVLTNode **node);

AVLTree* AVLTreeInitialize(int size, int (*cmp)(const void*, const void*));

void printAVLTreeStats(AVLTree *tree);

AVLTNode * AVLTreeMaxValueNode(AVLTNode* node);

AVLTNode * AVLTreeMinValueNode(AVLTNode* node);

void AVLTreePrintInOrder(AVLTNode* node, void (printFn)(void *));

AVLTNode * AVLTreeAddAll(AVLTree* avlTree,void **array, int length);

#endif //C_DATASTRUCTURES_AVLTREE_H
