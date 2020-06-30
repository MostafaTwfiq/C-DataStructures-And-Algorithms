#include "../Headers/SplayTree.h"

///
/// \param key
/// \return
SplayNode* newSplayTreeNode(void* key){
    SplayNode *p =  (SplayNode*)malloc(sizeof(SplayNode));
    if(!p){
        printf("Failed at allocating node\n");
        exit(-1);
    }
    p->key = key;
    p->left=NULL;
    p->right=NULL;
    return p;
}

///
/// \param x
/// \return
SplayNode *rightRotateSplay(SplayNode *x){
    SplayNode *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

///
/// \param x
/// \return
SplayNode *leftRotateSplay(SplayNode *x){
    SplayNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

///
/// \param splayTree
/// \param root
/// \param key
/// \return
SplayNode *splay(SplayTree *splayTree, SplayNode* root, void *key) {
        if (root == NULL || (splayTree->cmp)(root->key, key)==0)
            return root;
        if ((splayTree->cmp)(root->key, key)>0) {
            if (root->left == NULL) return root;

            // Zig-Zig (Left Left)
            if ((splayTree->cmp)(root->left->key, key)>0) {
                root->left->left = splay(splayTree,root->left->left, key);
                root = rightRotateSplay(root);
            }// Zig-Zag (Left Right)
            else if ((splayTree->cmp)(root->left->key, key)<0) {
                root->left->right = splay(splayTree,root->left->right, key);
                if (root->left->right != NULL)
                    root->left = leftRotateSplay(root->left);
            }
            if(root->left == NULL)
                return root;
            else
                return rightRotateSplay(root);
        }
        else {
            if (root->right == NULL) return root;

            // Zag-Zig (Right Left)
            if ((splayTree->cmp)(root->right->key, key)>0) {
                root->right->left = splay(splayTree,root->right->left, key);
                if (root->right->left != NULL)
                    root->right = rightRotateSplay(root->right);
            }// Zag-Zag (Right Right)
            else if ((splayTree->cmp)(root->right->key , key)<0) {
                root->right->right = splay(splayTree,root->right->right, key);
                root = leftRotateSplay(root);
            }

            if(root->right == NULL)
                return root;
            else
                return rightRotateSplay(root);
    }
}

///
/// \param splayTree
/// \param key
/// \return
SplayNode* SplayTreeSearch(SplayTree* splayTree,void *key){
    return splay(splayTree,splayTree->root,key);
}

///
/// \param splayTree
/// \param root
/// \param key
/// \return
SplayNode* SplayTreeInsert(SplayTree* splayTree,SplayNode* root, void *key){
    if(root==NULL) return newSplayTreeNode(key);
    if((splayTree->cmp)(root->key,key)==0) return root;
    SplayNode* newSplayNode = newSplayTreeNode(key);
    if((splayTree->cmp)(root->key,key)>0){
        newSplayNode->right = root;
        newSplayNode->left =root->left;
        root->left = NULL;
    } else{
        newSplayNode->left = root;
        newSplayNode->right =root->right;
        root->right = NULL;
    }
    return newSplayNode;
}

