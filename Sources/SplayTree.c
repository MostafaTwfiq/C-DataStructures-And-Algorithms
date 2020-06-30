#include "../Headers/SplayTree.h"

void printSplayTreeHelper(SplayNode *root, int space, void (printFn)(void *));
void SplayTreeToArrayRecurs(SplayNode* node , void **arr, int *i);

///
/// \param key
/// \return
SplayNode* newSplayNode(void* key){
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
/// \param size
/// \param cmp
/// \return
SplayTree* SplayTreeInitialize(int size, int16_t (*cmp)(const void*, const void*)){
    SplayTree *t = (SplayTree *) malloc(sizeof(SplayTree));
    if(!t){
        fprintf(stderr,"Failed at allocating tree\n");
        exit(-1);
    }
    t->root = NULL;
    t->cmp = cmp;
    t->nodeCount =0;
    t->sizeOfType = size;
    return t;
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
void SplayTreeInsert(SplayTree* splayTree, void *key){
    if(splayTree->root==NULL) splayTree->root= newSplayNode(key);
    if((splayTree->cmp)(splayTree->root->key,key)==0) return;
    SplayNode* splayNode = newSplayNode(key);
    if((splayTree->cmp)(splayTree->root->key,key)>0){
        splayNode->right = splayTree->root;
        splayNode->left =splayTree->root->left;
        splayTree->root->left = NULL;
    } else{
        splayNode->left = splayTree->root;
        splayNode->right =splayTree->root->right;
        splayTree->root->right = NULL;
    }
    splayTree->nodeCount++;
    splayTree->root = splayNode;
}

///
/// \param splayTree
/// \param key
void  SplayTreeDelete(SplayTree* splayTree, void *key){
    if (splayTree->root==NULL) return;
    splayTree->root = splay(splayTree,splayTree->root,key);
    if((splayTree->cmp)(splayTree->root->key,key)!=0) return;
    SplayNode* temp;
    if (splayTree->root->left==NULL){
        temp = splayTree->root;
        splayTree->root = splayTree->root->right;
    }else{
        temp = splayTree->root;
        splayTree->root = splay(splayTree,splayTree->root->left, key);
        splayTree->root->right = temp->right;
    }
    freeSplayNode(&temp);
    splayTree->nodeCount--;
}

///
/// \param node
void freeSplayNode(SplayNode **node){
    if(*node) return;
    free((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

///
/// \param root
void freeSplayTree(SplayNode** root){
    if (*root == NULL) return;
    freeSplayTree(&(*root)->left);
    freeSplayTree(&(*root)->right);
    freeSplayNode(root);
    *root=NULL;
}

///
/// \param node
/// \param printFn
void printInOrderSplayTree(SplayNode* node, void (printFn)(void *)){
    if(node==NULL)return;
    printInOrderSplayTree(node->left, printFn);
    (printFn)(node->key);
    printInOrderSplayTree(node->right, printFn);
}


///
/// \param root
/// \param printFn
void printSplayTree(SplayNode *root, void (printFn)(void *)){
    printSplayTreeHelper(root, 0, printFn);
}

///
/// \param root
/// \param space
/// \param printFn
void printSplayTreeHelper(SplayNode *root, int space, void (printFn)(void *)){
    if (root == NULL)
        return;
    space += COUNT;
    printSplayTreeHelper(root->right, space, printFn);
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    (printFn)(root->key);
    printSplayTreeHelper(root->left, space, printFn);
}

/// 
/// \param splayTree 
/// \param array 
/// \param length 
void SplayTreeInsertAll(SplayTree* splayTree, void** array, int length){
    for(int i=0;i<length;i++){
        SplayTreeInsert(splayTree,array[i]);
    }
}

///
/// \param binaryTree
/// \return
void **SplayTreeToArray(SplayTree *splayTree){
    void **array = (void **) malloc(sizeof(void *) * splayTree->nodeCount);
    int i = 0;
    SplayTreeToArrayRecurs(splayTree->root, array, &i);
    return array;
}

///
/// \param node
/// \param arr
/// \param i
void SplayTreeToArrayRecurs(SplayNode* node , void **arr, int *i){
    if(!node) return;
    SplayTreeToArrayRecurs(node->left, arr, i);
    arr[*i] = node->key;
    *i += 1;
    SplayTreeToArrayRecurs(node->right, arr, i);
}

