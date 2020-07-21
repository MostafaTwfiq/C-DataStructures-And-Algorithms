#include "../Headers/SplayTree.h"

void printSplayTreeHelper(SplayNode *root, int space, void (printFn)(void *));
void SplayTreeToArrayRecurs(SplayNode* node , void **arr, int *i);

/** Creates a new Splay TreeNode for a given key.
* @param key Reference pointer to preallocated key.
* @return Returns a pointer to an allocated node on the heap.
**/
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

/** Initialization Function for Splay Tree. A comparison function must be provided
  for the tree to be able to level its Nodes. Returns a reference to an allocated Splay Tree pointer on the heap.
* @param cmp Reference to the comparator function.
* @return Pointer to the allocated Splay tree on the heap.
**/
SplayTree* SplayTreeInitialize( int16_t (*cmp)(const void*, const void*)){
    SplayTree *t = (SplayTree *) malloc(sizeof(SplayTree));
    if(!t){
        fprintf(stderr,"Failed at allocating tree\n");
        exit(-1);
    }
    t->root = NULL;
    t->cmp = cmp;
    t->nodeCount =0;
    return t;
}

/** Function that Right rotates a Tree at a certain node.
* @param x  node to rotate at.
* @return returns the rotated sub-tree at reference node x.
**/
SplayNode *SplayRightRotate(SplayNode *x){
    SplayNode *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

/** Function that Left Rotates a Tree at a certain node.
* @param x node to rotate at.
* @return Returns the rotated sub-Tree at reference node x.
**/
SplayNode *SplayLeftRotate(SplayNode *x){
    SplayNode *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

/** Splay function brings the target key to the reference node. If not Present returns NUll.
 * @param splayTree Reference to the Splay tree.
 * @param root Reference to the root node.
 * @param key Reference pointer to preallocated key.
 * @return Returns the SplayNode at the top of the tree.
 **/
SplayNode *splay(SplayTree *splayTree, SplayNode* root, void *key) {
        if (root == NULL || (splayTree->cmp)(root->key, key)==0)
            return root;
        if ((splayTree->cmp)(root->key, key)>0) {
            if (root->left == NULL) return root;

            // Zig-Zig (Left Left)
            if ((splayTree->cmp)(root->left->key, key)>0) {
                root->left->left = splay(splayTree,root->left->left, key);
                root = SplayRightRotate(root);
            }// Zig-Zag (Left Right)
            else if ((splayTree->cmp)(root->left->key, key)<0) {
                root->left->right = splay(splayTree,root->left->right, key);
                if (root->left->right != NULL)
                    root->left = SplayLeftRotate(root->left);
            }
            if(root->left == NULL)
                return root;
            else
                return SplayRightRotate(root);
        }
        else {
            if (root->right == NULL) return root;

            // Zag-Zig (Right Left)
            if ((splayTree->cmp)(root->right->key, key)>0) {
                root->right->left = splay(splayTree,root->right->left, key);
                if (root->right->left != NULL)
                    root->right = SplayRightRotate(root->right);
            }// Zag-Zag (Right Right)
            else if ((splayTree->cmp)(root->right->key , key)<0) {
                root->right->right = splay(splayTree,root->right->right, key);
                root = SplayLeftRotate(root);
            }

            if(root->right == NULL)
                return root;
            else
                return SplayRightRotate(root);
    }
}

/** Given a Splay tree searches for node with the same key and return it. The key node is pushed to the top of the tree.
 * @param splayTree Reference to the Splay tree.
 * @param key Key object to search for in the SplayTree.
 * @return Returns the found node.
 **/
SplayNode* SplayTreeSearch(SplayTree* splayTree,void *key){
    return splay(splayTree,splayTree->root,key);
}

/** Inserts a node at the at the root with the provided key if not present
  in the tree.
 * @param splayTree  Reference to the Splay tree.
 * @param key Reference to key to inset in the Tree.
 **/
void SplayTreeInsert(SplayTree* splayTree, void *key){
    if(splayTree->root==NULL) {
        splayTree->root= newSplayNode(key);
        splayTree->nodeCount++;
    }
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

/** Given a Tree and it's root deletes a key with the same key and restores the tree's order.
 * @param splayTree  Reference to the Splay tree.
 * @param key Key object to add to the Binary Tree.
 **/
void SplayTreeDeleteWithFree(SplayTree* splayTree, void *key){
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
    freeSplayNode(&temp,splayTree->freeFn);
    splayTree->nodeCount--;
}

///
/// \param splayTree
/// \param key
void SplayTreeDeleteWithoutFree(SplayTree* splayTree, void *key){
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
    splayTree->nodeCount--;
}

/** Given a node it frees it's Key and the node. Setting both to Null.
* @param node Exact Reference for node to Free.
**/
void freeSplayNode(SplayNode **node, void (*freeFn)(void*)){
    if(*node) return;
    freeFn((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

/** Given an splay Tree's root node it frees it's elements recursively.Setting the root node to Null.
* @param root Exact Reference to root node to start freeing at.
**/
void SplayTreeFree(SplayNode** root,void (*freeFn)(void*)){
    if (*root == NULL) return;
    SplayTreeFree(&(*root)->left,freeFn);
    SplayTreeFree(&(*root)->right,freeFn);
    freeSplayNode(root, NULL);
    *root=NULL;
}

/** Takes a print function and starts printing from using the provided print function.
* @param node Reference node to start printing from.
* @param printFn print function to use for printing node keys.
**/
void printInOrderSplayTree(SplayNode* node, void (printFn)(void *)){
    if(node==NULL)return;
    printInOrderSplayTree(node->left, printFn);
    (printFn)(node->key);
    printInOrderSplayTree(node->right, printFn);
}


/** Prints a tree in 2 space of the console.
* @param root Reference to the root node.
* @param printFn Pointer to the print function.
**/
void printSplayTree(SplayNode *root, void (printFn)(void *)){
    printSplayTreeHelper(root, 0, printFn);
}

/** Helper function for printing the tree in 2d space.
* @param root Reference to the root node.
* @param space Number of spaces to print at the current level.
* @param printFn Pointer to the print function.
**/
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

/** Adds an array of void pointers to elements of the same type as the nodes of the tree.
* @param splayTree Reference to the SplayTree.
* @param array Array to add data from.
* @param length The Length of the array to add from.
**/
void SplayTreeInsertAll(SplayTree* splayTree, void** array, int length){
    for(int i=0;i<length;i++){
        SplayTreeInsert(splayTree,array[i]);
    }
}

/** Given a Tree converts it to an array in-order
* @param splayTree Reference to the splay tree.
* @return returns an array of pointer references to keys that were stored in the tree.
**/
void **SplayTreeToArray(SplayTree *splayTree){
    void **array = (void **) malloc(sizeof(void *) * splayTree->nodeCount);
    int i = 0;
    SplayTreeToArrayRecurs(splayTree->root, array, &i);
    return array;
}

/** Recursively traverses the tree in order and adds elements to an allocated array by @link SplayTreeToArray @endlink .
* @param node Node reference node to start converting from.
* @param arr Preallocated array to start storing at.
* @param i index to insert at in the array.
**/
void SplayTreeToArrayRecurs(SplayNode* node , void **arr, int *i){
    if(!node) return;
    SplayTreeToArrayRecurs(node->left, arr, i);
    arr[*i] = node->key;
    *i += 1;
    SplayTreeToArrayRecurs(node->right, arr, i);
}

