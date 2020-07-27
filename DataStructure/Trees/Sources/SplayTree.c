#include "../Headers/SplayTree.h"

void printSplayTreeHelper(SplayNode *root, int space, void (printFn)(void *));
void SplayTreeToArrayRecurs(SplayNode* node , void **arr, int *i);

/** Creates a new Splay TreeNode for a given key.
* @param key Reference pointer to preallocated key.
* @return Returns a pointer to an allocated node on the heap.
**/
SplayNode* newSplayNode(void* key){
    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "newSplayNode");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    SplayNode *p =  (SplayNode*)malloc(sizeof(SplayNode));
    if(!p){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "SplayNode", "newSplayNode");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

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
SplayTree *SplayTreeInitialize(int16_t (*cmp)(const void *, const void *), void (*freeFn)(void *)) {

    if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmp", "SplayTreeInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (freeFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeFn", "SplayTreeInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    SplayTree *t = (SplayTree *) malloc(sizeof(SplayTree));
    if(!t){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "SplayTree", "SplayTreeInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }
    t->root = NULL;
    t->cmp = cmp;
    t->nodeCount =0;
    t->freeFn = freeFn;
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
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "SplayTreeSearch");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "SplayTreeSearch");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    return splay(splayTree,splayTree->root,key);
}

/** Inserts a node at the at the root with the provided key if not present
  in the tree.
 * @param splayTree  Reference to the Splay tree.
 * @param key Reference to key to inset in the Tree.
 **/
void SplayTreeInsert(SplayTree* splayTree, void *key){
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "SplayTreeInsert");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "SplayTreeInsert");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

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
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "SplayTreeDeleteWithFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "SplayTreeDeleteWithFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

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
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "SplayTreeDeleteWithoutFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "SplayTreeDeleteWithoutFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
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
void SplayTreeFreeHelper(SplayNode **root,void (*freeFn)(void*)) {
    if (*root == NULL) return;
    SplayTreeFreeHelper(&(*root)->left,freeFn);
    SplayTreeFreeHelper(&(*root)->right,freeFn);
    freeSplayNode(root, NULL);
    *root=NULL;
}
///
/// \param splayTree
void SplayTreeFree(SplayTree *splayTree){
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "SplayTreeFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    SplayTreeFreeHelper(splayTree->root,splayTree->freeFn);
}

/** Takes a print function and starts printing from using the provided print function.
* @param node Reference node to start printing from.
* @param printFn print function to use for printing node keys.
**/
void printInOrderSplayTreeHelper(SplayNode* node, void (printFn)(void *)){
    if(node==NULL)return;
    printInOrderSplayTreeHelper(node->left, printFn);
    (printFn)(node->key);
    printInOrderSplayTreeHelper(node->right, printFn);
}

///
/// \param splayTree
/// \param printFn
void printInOrderSplayTree(SplayTree *splayTree, void (printFn)(void *)){
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "printInOrderSplayTree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (printFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printFn", "printInOrderSplayTree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    printInOrderSplayTreeHelper(splayTree->root,printFn);
}

/** Prints a tree in 2 space of the console.
* @param root Reference to the root node.
* @param printFn Pointer to the print function.
**/
void printSplayTree(SplayNode *root, void (printFn)(void *)){
    if (root == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "root", "printSplayTree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (printFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printFn", "printSplayTree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

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
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "SplayTreeInsertAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (array == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array", "SplayTreeInsertAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (length == 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "length", "SplayTreeInsertAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    for(int i=0;i<length;i++){
        SplayTreeInsert(splayTree,array[i]);
    }
}

/** Given a Tree converts it to an array in-order
* @param splayTree Reference to the splay tree.
* @return returns an array of pointer references to keys that were stored in the tree.
**/
void **SplayTreeToArray(SplayTree *splayTree){
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "SplayTreeToArray");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
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

///
/// \param node1
/// \param node2
/// \param cmpFn
/// \param flag
void isEqualHelper(SplayNode* node1,SplayNode* node2,int (*cmpFn)(const void *, const void *), int * flag){
    if (cmpFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmpFn", "isEqualHelper");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }
    if(!flag) return;
    if (node1 == NULL || node2 ==NULL) return;
    isEqualHelper(node1->right, node2->right,cmpFn,flag);
    if((cmpFn)(node1->key,node2->key)) *flag = 1;
    isEqualHelper(node1->left, node2->left, cmpFn,flag);
}


///
/// \param splayTree
/// \param splayTree2
/// \return
uint32_t isEqual(SplayTree *splayTree, SplayTree *splayTree2){
    if (splayTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree", "isEqual");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }

    if (splayTree2 == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "splayTree2", "isEqual");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }

    if(splayTree->nodeCount < splayTree2->nodeCount) return -1;
    if(splayTree->nodeCount > splayTree2->nodeCount) return  1;
    else {
        uint32_t areEqual = 0;
        isEqualHelper(splayTree->root, splayTree2->root, splayTree->cmp, &areEqual);
        return areEqual;
    }
}

///
/// \param tree
/// \param root
/// \param item
/// \return
uint32_t SplayTreeContainsHelper(SplayTree * tree, SplayNode* root,void *item){
    if (root == NULL) return 0;
    if (tree->cmp(item, root->key) == 0) return 1;
    else if (tree->cmp(item, root->key) < 0)
        return SplayTreeContainsHelper(tree, root->left, item);

    else
        return SplayTreeContainsHelper(tree, root->right, item);
}

///
/// \param tree
/// \param item
/// \return
uint32_t SplayTreeContains(SplayTree * tree, void *item){

    if (tree == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "SplayTreeContains");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
        #else
                exit(NULL_POINTER);
        #endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item", "SplayTreeContains");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }

    return SplayTreeContainsHelper(tree, tree->root, item);
}


SplayNode* SplayTreeMirrorHelper(SplayNode* root){
    if (root==NULL) return root;
    else{
        SplayNode* temp;

        root->left  = SplayTreeMirrorHelper(root->left);
        root->right = SplayTreeMirrorHelper(root->right);


        temp        = root->left;
        root->left  = root->right;
        root->right = temp;
    }
    return root;
}

///
/// \param tree
void SplayTreeMirror(SplayTree* tree){
    if (tree == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "SplayTreeMirror");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
        #else
                exit(NULL_POINTER);
        #endif
    }
    tree->root = SplayTreeMirrorHelper(tree->root);
}