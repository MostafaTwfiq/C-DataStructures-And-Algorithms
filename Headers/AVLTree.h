#ifndef C_DATASTRUCTURES_AVLTREE_H
#define C_DATASTRUCTURES_AVLTREE_H
#include "Utils.h"
#include <math.h>
#define COUNT 10

#ifndef BINTREE_STRUCT_
#define BINTREE_STRUCT_

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



AVLTNode* DeleteAVLTreeNode(AVLTree *avlTree, AVLTNode* root, void *key);

int getMinStepsAVLTree(AVLTNode* node);


int getMaxStepsAVLTree(AVLTNode* node);
int getSizeAVLTree(AVLTNode *root);


int isPresentInAVLTree(AVLTree *avlTree, AVLTNode *root, void *searchKey);


void printAVLTree(AVLTNode *root, void (printFn)(void *));

void inOrderPredecessorAVLTree(AVLTree *avlTree, AVLTNode *root, AVLTNode *targetNode, AVLTNode **rightMost);

void inOrderSuccessorAVLTree(AVLTree *avlTree, AVLTNode* root, AVLTNode* targetNode, AVLTNode **leftMost);

AVLTNode* insertAVLTree(AVLTree * avlTree, AVLTNode *node, void *key);

AVLTNode *searchAVLTree(AVLTree *avlTree,AVLTNode *node, char *key);

void** AVLTreeToArray(AVLTree *avlTree);

void freeAVLTree(AVLTNode **node);

AVLTree* AVLTreeInitialize(int size, int(*cmp)(void*, void*));

void printAVLTreeStats(AVLTree *tree);

AVLTNode * maxValueNodeAVLTree(AVLTNode* node);
AVLTNode * minValueNodeAVLTree(AVLTNode* node);

void printInOrderAVLTree(AVLTNode* node, void (printFn)(void *));


#endif //C_DATASTRUCTURES_AVLTREE_H
