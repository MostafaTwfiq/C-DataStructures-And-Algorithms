#ifndef C_DATASTRUCTURES_AVLTREE_H
#define C_DATASTRUCTURES_AVLTREE_H
#include "Utils.h"
#include <math.h>
#define COUNT 10

#ifndef BINTREE_STRUCT_
#define BINTREE_STRUCT_

typedef struct AVLTNode{
    void ** key;
    int height;
    struct AVLTNode *left;
    struct AVLTNode *right;
}AVLTNode;

typedef struct AVLTree{
    AVLTNode *root;
    int sizeOfType;
    unsigned int nodeCount;
    int(*cmp)(void*,void*);
}AVLTree;

#endif



AVLTNode* Delete(AVLTree *avlTree, AVLTNode* root, void *key);

int getMinSteps(AVLTNode* node);


int getMaxSteps(AVLTNode* node);
int getSizeBinaryTree(AVLTNode *root);


int isPresent(AVLTree *avlTree,AVLTNode *root, void *searchKey);


void printTree(AVLTNode *root,void (printFn)(void *));

void inOrderPredecessor(AVLTree *avlTree,AVLTNode *root, AVLTNode *targetNode, AVLTNode **rightMost);

void inOrderSuccessor(AVLTree *avlTree,AVLTNode* root, AVLTNode* targetNode, AVLTNode **leftMost);

AVLTNode* insert(AVLTree * avlTree,AVLTNode *node, void *key);
AVLTNode *search(AVLTree *avlTree,AVLTNode *node, char *key);

void** treeToArray(AVLTree *avlTree);

void freeTree(AVLTNode **node);

AVLTree* createNewTree(int size,int(*cmp)(void*,void*));

void printTreeStats(AVLTree *tree);

AVLTNode * maxValueNode(AVLTNode* node);
AVLTNode * minValueNode(AVLTNode* node);

void printInOrder(AVLTNode* node,void (printFn)(void *));


#endif //C_DATASTRUCTURES_AVLTREE_H
