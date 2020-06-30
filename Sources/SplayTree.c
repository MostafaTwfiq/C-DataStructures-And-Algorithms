#include "../Headers/SplayTree.h"

SplayNode *rightRotateSplay(SplayNode *x){
    SplayNode *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayNode *leftRotateSplay(SplayNode *x){
    SplayNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

SplayNode *splay(SplayTree *splayTree, SplayNode* node, void *key) {

}