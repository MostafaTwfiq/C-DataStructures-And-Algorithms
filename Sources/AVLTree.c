#include "../Headers/AVLTree.h"


void printAVLTreeHelper(AVLTNode *root, int space, void (printFn)(void *));
void isPresentInAVLTreeRecurs(AVLTree *avlTree, AVLTNode *root, void *searchedValue, int* found );
int max(int a,int b);
void AVLTreeToArrayRecurs(AVLTNode* node, int sizeOfType , void *arr, int *i);
void freeAVLTreeNode(AVLTNode **node);
AVLTNode* newBinaryTreeNode(void* key);
int height(AVLTNode *node);
void getMaxStepsAVLTreeRecurs(AVLTNode * node, int * steps);
void getMinStepsAVLTreeRecurs(AVLTNode * node, int * steps);


///
/// \param a
/// \param b
/// \return
int max(int a, int b){
    return (a > b)? a : b;
}

///
/// \param n
/// \return
AVLTNode *leftRotate(AVLTNode *n);

///
/// \param n
/// \return
AVLTNode *rightRotate(AVLTNode *n);

///
/// \param N
/// \return
int getBalance(AVLTNode *N);

///
/// \param tree
void printAVLTreeStats(AVLTree *tree){
    if(tree&&tree->root){
        printf("............................\n");
        printf("Size = %d\n", tree->nodeCount);
        printf("............................\n");
        printf("Height = %d\n",tree->root->height);
        printf("............................\n");
        printf("Minimum Steps %d\n", getMinStepsAVLTree(tree->root));
        printf("............................\n");
        printf("Maximum Steps %d\n", getMaxStepsAVLTree(tree->root));
        printf("............................\n");
        printf("Maximum node Rule(2^(h+1)-1) : ");
        if(tree->nodeCount<pow(2,tree->root->height+1)-1){
            printf("SATISFIED\n");
        }else{
            printf("NOT SATISFIED\n");
        }
        printf("............................\n");

        printf("Minimum node Rule(2*1.6^h) : ");
        if(tree->nodeCount>2*pow(1.6,tree->root->height)){
            printf("SATISFIED\n");
        }else{
            printf("NOT SATISFIED\n");
        }
    }else{
        printf("AVL Tree Did Not Load Successfully...!\n");
    }
}

///
/// \param cmp
/// \return
AVLTree* AVLTreeInitialize(int size, int(*cmp)(const void*, const void*)){
    AVLTree *t = (AVLTree *) malloc(sizeof(AVLTree));
    if(!t){
        fprintf(stderr,"Failed at allocating tree\n");
        exit(-1);
    }
    t->root = NULL;
    t->cmp = cmp;
    t->nodeCount=0;
    t->sizeOfType = size;
    return t;
}

///
/// \param key
/// \return
AVLTNode* newAVLTreeNode(void* key){
    AVLTNode *p =  (AVLTNode*)malloc(sizeof(AVLTNode));
    if(!p){
        printf("Failed at allocating node\n");
        exit(-1);
    }
    p->key = key;
    p->left=NULL;
    p->right=NULL;
    p->height = 1;
    return p;
}

///
/// \param node
void freeAVLTree(AVLTNode** node){
    if (*node==NULL) return;
    freeAVLTree(&(*node)->left);
    freeAVLTree(&(*node)->right);
    freeAVLTreeNode(node);
    *node=NULL;
}

///
/// \param node
void freeAVLTreeNode(AVLTNode **node){
    if(*node) return;
    free((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

///
/// \param avlTree
/// \param node
/// \param key
/// \return
AVLTNode* insertAVLTree(AVLTree * avlTree, AVLTNode *node, void *key) {
    if (node == NULL) {
        avlTree->nodeCount++;
        return newAVLTreeNode(key);
    }
    if ( (avlTree->cmp)(key ,node->key)<0) node->left = insertAVLTree(avlTree, node->left, key);
    else if ((avlTree->cmp)(key ,node->key)>0) node->right = insertAVLTree(avlTree, node->right, key);

    node->height = max(height(node->left),height(node->right))+1;

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && (avlTree->cmp)(key, node->left->key)<0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && (avlTree->cmp)(key, node->right->key)>0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && (avlTree->cmp)(key, node->left->key)>0){
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && (avlTree->cmp)(key,node->right->key)<0){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

///
/// \param n
/// \return
AVLTNode *rightRotate(AVLTNode *n){
    AVLTNode *leftNode = (AVLTNode*)n->left;
    //   if(!leftNode) return n;
    AVLTNode *rightOfLeft = (AVLTNode*)leftNode->right;

    leftNode->right = n;
    n->left = rightOfLeft;

    n->height = max(height(n->left), height(n->right)) + 1;
    leftNode->height = max(height(leftNode->left), height(leftNode->right)) + 1;

    return leftNode;
}

///
/// \param n
/// \return
AVLTNode *leftRotate(AVLTNode *n){
    AVLTNode *rightNode =(AVLTNode*) n->right;
    //   if(!rightNode) return n;
    AVLTNode *leftOfright = (AVLTNode*)rightNode->left;

    rightNode->left = n;
    n->right = leftOfright;

    n->height = max(height(n->left), height(n->right)) + 1;
    rightNode->height = max(height(rightNode->left), height(rightNode->right)) + 1;

    return rightNode;
}

///
/// \param node
/// \return
int height(AVLTNode *node){
    if (!node) return 0;
    return node->height;
}

///
/// \param N
/// \return
int getBalance(AVLTNode *N){
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

///
/// \param avlTree
/// \param root
/// \param referenceNode
/// \param leftMost
void inOrderSuccessorAVLTree(AVLTree *avlTree, AVLTNode* root, AVLTNode* referenceNode, AVLTNode **leftMost) {
    if (root == NULL) {
        leftMost = NULL;
        return;}
    if ((avlTree->cmp)(root->key, referenceNode->key) == 0){
        if (root->right)
            *leftMost = minValueNodeAVLTree(root->right);
    }
    else if ((avlTree->cmp)(referenceNode->key, root->key) < 0){
        *leftMost = root;
        inOrderSuccessorAVLTree(avlTree, root->left, referenceNode, leftMost);
    }
    else{
        inOrderSuccessorAVLTree(avlTree, root->right, referenceNode, leftMost);
    }
}

///
/// \param avlTree
/// \param root
/// \param referenceNode
/// \param rightMost
void inOrderPredecessorAVLTree(AVLTree *avlTree, AVLTNode *root, AVLTNode *referenceNode, AVLTNode **rightMost){
    if (root == NULL) {
        rightMost = NULL;
        return;
    }
    if ((avlTree->cmp)(root->key, referenceNode->key) == 0){
        if (root->left)
            *rightMost = maxValueNodeAVLTree(root->left);
    }
    else if ((avlTree->cmp)(referenceNode->key, root->key) < 0){
        inOrderPredecessorAVLTree(avlTree, root->left, referenceNode, rightMost);
    }
    else{
        *rightMost = root;
        inOrderPredecessorAVLTree(avlTree, root->right, referenceNode, rightMost);
    }
}

///
/// \param root
/// \param printFn
void printAVLTree(AVLTNode *root, void (printFn)(void *)){
    printAVLTreeHelper(root, 0, printFn);
}

///
/// \param root
/// \param space
/// \param printFn
void printAVLTreeHelper(AVLTNode *root, int space, void (printFn)(void *)){
    if (root == NULL)
        return;
    space += COUNT;
    printAVLTreeHelper(root->right, space, printFn);
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    (printFn)(root->key);
    printAVLTreeHelper(root->left, space, printFn);
}

///
/// \param avlTree
/// \param root
/// \param searchKey
/// \return
int isPresentInAVLTree(AVLTree *avlTree, AVLTNode* root, void* searchKey){
    int found = 0;
    isPresentInAVLTreeRecurs(avlTree, root, searchKey, &found);
    return found;
}

///
/// \param avlTree
/// \param root
/// \param searchedValue
/// \param found
void isPresentInAVLTreeRecurs(AVLTree *avlTree, AVLTNode *root, void *searchedValue, int* found ){
    if (root) {
        if ((avlTree->cmp)(root->key,searchedValue)==0)
            *found = 1;
        else {
            isPresentInAVLTreeRecurs(avlTree, root->left, searchedValue, found);
            if (!(*found))
                isPresentInAVLTreeRecurs(avlTree, root->right, searchedValue, found);
        }
    }
}

///
/// \param root
/// \return
int getSizeAVLTree(AVLTNode* root){
    if (root) return 1 +getSizeAVLTree( root->left ) + getSizeAVLTree( root->right );
    else return 0;
}

///
/// \param node
/// \return
AVLTNode * minValueNodeAVLTree(AVLTNode* node){
    if(!node) return NULL;
    if(node->left )return minValueNodeAVLTree(node->left);
    return node;
}

///
/// \param node
/// \return
AVLTNode * maxValueNodeAVLTree(AVLTNode* node){
    if (!node) return NULL;
    if (node->right) return maxValueNodeAVLTree(node->right);
    return node;
}

///
/// \param node
/// \return
int getMinStepsAVLTree(AVLTNode* node){
    int steps=0;
    getMinStepsAVLTreeRecurs(node, &steps);
    return steps;
}

///
/// \param node
/// \param steps
void getMinStepsAVLTreeRecurs(AVLTNode *node, int *steps){
    if(!node) return;
    *steps = *steps +1;
    if(node->left )getMinStepsAVLTreeRecurs(node->left, steps);
}

///
/// \param node
/// \return
int getMaxStepsAVLTree(AVLTNode* node ){
    int steps = 0;
    getMaxStepsAVLTreeRecurs(node, &steps);
    return steps;
}

///
/// \param node
/// \param steps
void getMaxStepsAVLTreeRecurs(AVLTNode* node, int *steps){
    if (!node) return;
    *steps = *steps+1;
    if (node->right) getMaxStepsAVLTreeRecurs(node->right, steps);
}

///
/// \param node
/// \param printFn
void printInOrderAVLTree(AVLTNode* node, void (printFn)(void *)){
    if(!node)return;
    printInOrderAVLTree(node->left, printFn);
    (printFn)(node->key);
    printInOrderAVLTree(node->right, printFn);
}

///
/// \param avlTree
/// \return
void** AVLTreeToArray(AVLTree *avlTree){
    void *array = malloc(avlTree->sizeOfType * avlTree->nodeCount);
    int i = 0;
    AVLTreeToArrayRecurs(avlTree->root, avlTree->sizeOfType, array, &i);
    return array;
}

///
/// \param node
/// \param arr
/// \param i
void AVLTreeToArrayRecurs(AVLTNode* node, int sizeOfType , void *arr, int *i){
    if(!node) return;
    AVLTreeToArrayRecurs(node->left, sizeOfType, arr, i);
    memcpy(arr + sizeOfType * *i, node->key, sizeOfType);
    *i += 1;
    AVLTreeToArrayRecurs(node->right, sizeOfType, arr, i);
}

///
/// \param avlTree
/// \param node
/// \param key
/// \return
AVLTNode *searchAVLTree(AVLTree *avlTree,AVLTNode *node, char *key){
    if(!node) return NULL;
    if (((avlTree->cmp)(key,node->key)==0))return node;
    if ((avlTree->cmp)(key,node->key)<0) return searchAVLTree(avlTree,node->left, key);
    if ((avlTree->cmp)(key,node->key)>0) return searchAVLTree(avlTree,node->right, key);
}

///
/// \param avlTree
/// \param root
/// \param key
/// \return
AVLTNode* DeleteAVLTreeNode(AVLTree *avlTree, AVLTNode* root, void *key) {
    if(root==NULL) return root;
    if ((avlTree->cmp)(key ,root->key)<0) 		    root->left = DeleteAVLTreeNode(avlTree, root->left, key);
    else if ((avlTree->cmp)(key ,root->key)>0)  	root->right = DeleteAVLTreeNode(avlTree, root->right, key);
    else {
        if( (root->left == NULL) ||(root->right == NULL) ){
            AVLTNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp =root;
                root=NULL;
            }else {*root = *temp;}
        }
        else {
            AVLTNode* temp = minValueNodeAVLTree(root->right);
            root->key= temp->key;
            root->right = DeleteAVLTreeNode(avlTree, root->right, temp->key);
        }
        avlTree->nodeCount--;
    }
    if(root==NULL) return root;
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = getBalance(root);

    //Left Left Case
    if(balance > 1 && getBalance(root->left) >=0)   return rightRotate(root);

    // Right Right Case
    if(balance < -1 && getBalance(root->right) <=0)	return leftRotate(root);

    // Left Right Case
    if(balance > 1 && getBalance(root->left) < 0)	{
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //Right Left Case
    if(balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}