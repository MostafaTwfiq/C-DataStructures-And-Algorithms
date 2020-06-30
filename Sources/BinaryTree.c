#include "../Headers/BinaryTree.h"


void printBinaryTreeHelper(BinaryTreeNode *root, int space, void (printFn)(void *));
void isPresentInBinaryTreeRecurs(BinaryTree *binaryTree, BinaryTreeNode *root, void *searchedValue, int* found );
void BinaryTreeToArrayRecurs(BinaryTreeNode* node , int sizeOfType, void **arr, int *i);
void freeBinaryTreeNode(BinaryTreeNode **node);
BinaryTreeNode* newBinaryTreeNode(void* key);
void getMaxStepsBinaryTreeRecurs(BinaryTreeNode * node, int * steps);
void getMinStepsBinaryTreeRecurs(BinaryTreeNode * node, int * steps);

///
/// \param tree
void printBinaryTreeStats(BinaryTree *tree){
    if(tree&&tree->root){
        printf("............................\n");
        printf("Size = %d\n", tree->nodeCount);
        printf("............................\n");
        printf("............................\n");
        printf("Minimum Steps %d\n", getMinStepsBinaryTree(tree->root));
        printf("............................\n");
        printf("Maximum Steps %d\n", getMaxBinaryTreeSteps(tree->root));
        printf("............................\n");
    }else{
        printf("AVL Tree Did Not Load Successfully...!\n");
    }
}

///
/// \param cmp
/// \return
BinaryTree* BinaryTreeInitialize(int size, int(*cmp)(const void*, const void*)){
    BinaryTree *t = (BinaryTree *) malloc(sizeof(BinaryTree));
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
/// \param key
/// \return
BinaryTreeNode* newBinaryTreeNode(void* key){
    BinaryTreeNode *p =  (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
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
/// \param node
void freeBinaryTree(BinaryTreeNode** node){
    if (*node==NULL) return;
    freeBinaryTree(&(*node)->left);
    freeBinaryTree(&(*node)->right);
    freeBinaryTreeNode(node);
    *node=NULL;
}

///
/// \param node
void freeBinaryTreeNode(BinaryTreeNode **node){
    if(*node) return;
    free((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

///
/// \param binaryTree
/// \param node
/// \param key
/// \return
BinaryTreeNode* insertBinaryTree(BinaryTree * binaryTree, BinaryTreeNode *node, void *key) {
    if (node == NULL) {
        binaryTree->nodeCount++;
        return newBinaryTreeNode(key);
    }
    if ( (binaryTree->cmp)(key ,node->key)<0) node->left = insertBinaryTree(binaryTree, node->left, key);
    else if ((binaryTree->cmp)(key ,node->key)>0) node->right = insertBinaryTree(binaryTree, node->right, key);

    return node;
}

///
/// \param binaryTree
/// \param root
/// \param targetNode
/// \param leftMost
void inOrderSuccessorBinaryTree(BinaryTree *binaryTree, BinaryTreeNode* root, BinaryTreeNode* targetNode, BinaryTreeNode **leftMost) {
    if (root == NULL) {
        leftMost = NULL;
        return;}
    if ((binaryTree->cmp)(root->key,targetNode->key)==0){
        if (root->right)
            *leftMost = minValueBinaryTreeNode(root->right);
    }
    else if ((binaryTree->cmp)(targetNode->key, root->key)<0){
        *leftMost = root;
        inOrderSuccessorBinaryTree(binaryTree, root->left, targetNode, leftMost);
    }
    else{
        inOrderSuccessorBinaryTree(binaryTree, root->right, targetNode, leftMost);
    }
}

///
/// \param binaryTree
/// \param root
/// \param targetNode
/// \param rightMost
void inOrderPredecessorBinaryTree(BinaryTree *binaryTree, BinaryTreeNode *root, BinaryTreeNode *targetNode, BinaryTreeNode **rightMost){
    if (root == NULL) {
        rightMost = NULL;
        return;}
    if ((binaryTree->cmp)(root->key,targetNode->key)==0){
        if (root->left)
            *rightMost = maxValueBinaryTreeNode(root->left);
    }
    else if ((binaryTree->cmp)(targetNode->key, root->key)<0){
        inOrderPredecessorBinaryTree(binaryTree, root->left, targetNode, rightMost);
    }
    else{
        *rightMost = root;
        inOrderPredecessorBinaryTree(binaryTree, root->right, targetNode, rightMost);
    }
}

///
/// \param root
/// \param printFn
void printBinaryTree(BinaryTreeNode *root, void (printFn)(void *)){
    printBinaryTreeHelper(root, 0, printFn);
}

///
/// \param root
/// \param space
/// \param printFn
void printBinaryTreeHelper(BinaryTreeNode *root, int space, void (printFn)(void *)){
    if (root == NULL)
        return;
    space += COUNT;
    printBinaryTreeHelper(root->right, space, printFn);
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    (printFn)(root->key);
    printBinaryTreeHelper(root->left, space, printFn);
}

///
/// \param binaryTree
/// \param root
/// \param searchKey
/// \return
int isPresentInBinaryTree(BinaryTree *binaryTree, BinaryTreeNode* root, void* searchKey){
    int found = 0;
    isPresentInBinaryTreeRecurs(binaryTree, root, searchKey, &found);
    return found;
}

///
/// \param binaryTree
/// \param root
/// \param searchedValue
/// \param found
void isPresentInBinaryTreeRecurs(BinaryTree *binaryTree, BinaryTreeNode *root, void *searchedValue, int* found ){
    if (root) {
        if ((binaryTree->cmp)(root->key,searchedValue)==0)
            *found = 1;
        else {
            isPresentInBinaryTreeRecurs(binaryTree, root->left, searchedValue, found);
            if (!(*found))
                isPresentInBinaryTreeRecurs(binaryTree, root->right, searchedValue, found);

        }
    }
}

///
/// \param root
/// \return
int getSizeBinaryTree(BinaryTreeNode* root){
    if (root) return 1 +getSizeBinaryTree( root->left ) + getSizeBinaryTree( root->right );
    else return 0;
}

///
/// \param node
/// \return
BinaryTreeNode * minValueBinaryTreeNode(BinaryTreeNode* node){
    if(!node) return NULL;
    if(node->left )return minValueBinaryTreeNode(node->left);
    return node;
}

///
/// \param node
/// \return
BinaryTreeNode * maxValueBinaryTreeNode(BinaryTreeNode* node){
    if (!node) return NULL;
    if (node->right) return maxValueBinaryTreeNode(node->right);
    return node;
}

///
/// \param node
/// \return
int getMinStepsBinaryTree(BinaryTreeNode* node){
    int steps=0;
    getMinStepsBinaryTreeRecurs(node, &steps);
    return steps;
}

///
/// \param node
/// \param steps
void getMinStepsBinaryTreeRecurs(BinaryTreeNode *node, int *steps){
    if(!node) return;
    *steps = *steps +1;
    if(node->left )getMinStepsBinaryTreeRecurs(node->left, steps);
}

///
/// \param node
/// \return
int getMaxBinaryTreeSteps(BinaryTreeNode* node ){
    int steps = 0;
    getMaxStepsBinaryTreeRecurs(node, &steps);
    return steps;
}

///
/// \param node
/// \param steps
void getMaxStepsBinaryTreeRecurs(BinaryTreeNode* node, int *steps){
    if (!node) return;
    *steps = *steps+1;
    if (node->right) getMaxStepsBinaryTreeRecurs(node->right, steps);
}

///
/// \param node
/// \param printFn
void printInOrderBinaryTree(BinaryTreeNode* node, void (printFn)(void *)){
    if(!node)return;
    printInOrderBinaryTree(node->left, printFn);
    (printFn)(node->key);
    printInOrderBinaryTree(node->right, printFn);
}

///
/// \param binaryTree
/// \return
void **BinaryTreeToArray(BinaryTree *binaryTree){
    void **array = (void **) malloc(sizeof(void *) * binaryTree->nodeCount);
    int i = 0;
    BinaryTreeToArrayRecurs(binaryTree->root, binaryTree->sizeOfType, array, &i);
    return array;
}

///
/// \param node
/// \param arr
/// \param i
void BinaryTreeToArrayRecurs(BinaryTreeNode* node , int sizeOfType, void **arr, int *i){
    if(!node) return;
    BinaryTreeToArrayRecurs(node->left, sizeOfType, arr, i);
    arr[*i] = (void *) malloc(sizeOfType);
    memcpy(arr[*i], node->key, sizeOfType);
    *i += 1;
    BinaryTreeToArrayRecurs(node->right, sizeOfType, arr, i);
}

///
/// \param binaryTree
/// \param node
/// \param key
/// \return
BinaryTreeNode *searchBinaryTree(BinaryTree *binaryTree, BinaryTreeNode *node, char *key){
    if(!node) return NULL;
    if (((binaryTree->cmp)(key,node->key)==0))return node;
    if ((binaryTree->cmp)(key,node->key)<0) return searchBinaryTree(binaryTree,node->left, key);
    if ((binaryTree->cmp)(key,node->key)>0) return searchBinaryTree(binaryTree,node->right, key);
}

///
/// \param binaryTree
/// \param root
/// \param key
/// \return
BinaryTreeNode* DeleteBinaryTreeNode(BinaryTree *binaryTree, BinaryTreeNode* root, void *key) {
    if(root==NULL) return root;
    if ((binaryTree->cmp)(key ,root->key)<0) 		root->left = DeleteBinaryTreeNode(binaryTree, root->left, key);
    else if ((binaryTree->cmp)(key ,root->key)>0)  	root->right = DeleteBinaryTreeNode(binaryTree, root->right, key);
    else {
        if( (root->left == NULL) ||(root->right == NULL) ){
            BinaryTreeNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp =root;
                root=NULL;
            }else {*root = *temp;}
        }
        else {
            BinaryTreeNode* temp = minValueBinaryTreeNode(root->right);
            root->key= temp->key;
            root->right = DeleteBinaryTreeNode(binaryTree, root->right, temp->key);
        }
        binaryTree->nodeCount--;
    }
    return root;
}

BinaryTreeNode * BinaryTreeInsertAll(BinaryTree* binaryTree, void** array, int length){
    for(int i=0;i<length;i++){
        binaryTree->root = insertBinaryTree(binaryTree,binaryTree->root,array[i]);
    }
    return binaryTree->root;
}