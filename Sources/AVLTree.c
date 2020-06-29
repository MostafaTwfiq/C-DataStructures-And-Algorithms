#include "../Headers/AVLTree.h"


void printTreeS(AVLTNode *root, int space, void (printFn)(void *));
void isPresentRecurs(AVLTree *avlTree,AVLTNode *root, void *searchedValue, int* found );
int max(int a,int b);
void treeToArrayRecurs(AVLTNode* node , void **arr, int *i);
void freeAVLTNode(AVLTNode **node);
AVLTNode* newNode( void* key);
int height(AVLTNode *node);
void getMaxStepsRecurs(AVLTNode * node, int * steps);
void getMinStepsRecurs(AVLTNode * node, int * steps);


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
void printTreeStats(AVLTree *tree){
    if(tree&&tree->root){
        printf("............................\n");
        printf("Size = %d\n", tree->nodeCount);
        printf("............................\n");
        printf("Height = %d\n",tree->root->height);
        printf("............................\n");
        printf("Minimum Steps %d\n", getMinSteps(tree->root));
        printf("............................\n");
        printf("Maximum Steps %d\n",getMaxSteps(tree->root));
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
AVLTree* createNewTree(int size,int(*cmp)(void*,void*)){
    AVLTree *t = (AVLTree *) malloc(sizeof(AVLTree));
    if(!t){
        fprintf(stderr,"Failed at allocating tree\n");
        exit(-1);
    }
    t->root = NULL;
    t->cmp = cmp;
    t->sizeOfType = size;
    return t;
}

///
/// \param key
/// \return
AVLTNode* newNode( void* key){
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
void freeTree(AVLTNode** node){
    if (*node==NULL) return;
    freeTree(&(*node)->left);
    freeTree(&(*node)->right);
    freeAVLTNode(node);
    *node=NULL;
}

///
/// \param node
void freeAVLTNode(AVLTNode **node){
    if(*node) return;
    free(*(*node)->key);
    *(*node)->key = NULL;
    free(*node);
}

///
/// \param avlTree
/// \param node
/// \param key
/// \return
AVLTNode* insert(AVLTree * avlTree,AVLTNode *node, void *key) {
    if (node == NULL) return newNode(key);
    if ( (avlTree->cmp)(key ,node->key)<0) node->left = insert(avlTree,node->left, key);
    else if ((avlTree->cmp)(key ,node->key)>0) node->right = insert(avlTree,node->right, key);

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
/// \param targetNode
/// \param leftMost
void inOrderSuccessor(AVLTree *avlTree,AVLTNode* root, AVLTNode* targetNode, AVLTNode **leftMost) {
    if (root == NULL) {
        leftMost = NULL;
        return;}
    if ((avlTree->cmp)(root->key,targetNode->key)==0){
        if (root->right)
            *leftMost = minValueNode(root->right);
    }
    else if ((avlTree->cmp)(targetNode->key, root->key)<0){
        *leftMost = root;
        inOrderSuccessor(avlTree,root->left, targetNode,leftMost);
    }
    else{
        inOrderSuccessor(avlTree,root->right, targetNode, leftMost);
    }
}

///
/// \param avlTree
/// \param root
/// \param targetNode
/// \param rightMost
void inOrderPredecessor(AVLTree *avlTree,AVLTNode *root, AVLTNode *targetNode, AVLTNode **rightMost){
    if (root == NULL) {
        rightMost = NULL;
        return;}
    if ((avlTree->cmp)(root->key,targetNode->key)==0){
        if (root->left)
            *rightMost = maxValueNode(root->left);
    }
    else if ((avlTree->cmp)(targetNode->key, root->key)<0){
        inOrderPredecessor(avlTree,root->left, targetNode,rightMost);
    }
    else{
        *rightMost = root;
        inOrderPredecessor(avlTree,root->right, targetNode, rightMost);
    }
}

///
/// \param root
/// \param printFn
void printTree(AVLTNode *root,void (printFn)(void *)){
    printTreeS(root, 0,printFn);
}

///
/// \param root
/// \param space
/// \param printFn
void printTreeS(AVLTNode *root, int space, void (printFn)(void *)){
    if (root == NULL)
        return;
    space += COUNT;
    printTreeS(root->right, space,printFn);
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    (printFn)(root->key);
    printTreeS(root->left, space,printFn);
}

///
/// \param avlTree
/// \param root
/// \param searchKey
/// \return
int isPresent(AVLTree *avlTree,AVLTNode* root, void* searchKey){
    int found = 0;
    isPresentRecurs(avlTree,root, searchKey, &found );
    return found;
}

///
/// \param avlTree
/// \param root
/// \param searchedValue
/// \param found
void isPresentRecurs(AVLTree *avlTree,AVLTNode *root, void *searchedValue, int* found ){
    if (root) {
        if ((avlTree->cmp)(root->key,searchedValue)==0)
            *found = 1;
        else {
            isPresentRecurs(avlTree,root->left, searchedValue, found);
            if (!(*found))
                isPresentRecurs( avlTree,root->right, searchedValue, found);
        }
    }
}

///
/// \param root
/// \return
int getSizeBinaryTree(AVLTNode* root){
    if (root) return 1 +getSizeBinaryTree( root->left ) + getSizeBinaryTree( root->right );
    else return 0;
}

///
/// \param node
/// \return
AVLTNode * minValueNode(AVLTNode* node){
    if(!node) return NULL;
    if(node->left )return minValueNode(node->left);
    return node;
}

///
/// \param node
/// \return
AVLTNode * maxValueNode(AVLTNode* node){
    if (!node) return NULL;
    if (node->right) return maxValueNode(node->right);
    return node;
}

///
/// \param node
/// \return
int getMinSteps(AVLTNode* node){
    int steps=0;
    getMinStepsRecurs(node, &steps);
    return steps;
}

///
/// \param node
/// \param steps
void getMinStepsRecurs(AVLTNode *node, int *steps){
    if(!node) return;
    *steps = *steps +1;
    if(node->left )getMinStepsRecurs(node->left,steps);
}

///
/// \param node
/// \return
int getMaxSteps(AVLTNode* node ){
    int steps = 0;
    getMaxStepsRecurs(node, &steps);
    return steps;
}

///
/// \param node
/// \param steps
void getMaxStepsRecurs(AVLTNode* node, int *steps){
    if (!node) return;
    *steps = *steps+1;
    if (node->right) getMaxStepsRecurs(node->right,steps);
}

///
/// \param node
/// \param printFn
void printInOrder(AVLTNode* node,void (printFn)(void *)){
    if(!node)return;
    printInOrder(node->left,printFn);
    (printFn)(node->key);
    printInOrder(node->right,printFn);
}

///
/// \param avlTree
/// \return
void** treeToArray(AVLTree *avlTree){
    void **array = malloc(sizeof(void *)*avlTree->nodeCount);
    int i =0;
    treeToArrayRecurs(avlTree->root,array,&i);
    return array;
}

///
/// \param node
/// \param arr
/// \param i
void treeToArrayRecurs(AVLTNode* node , void **arr, int *i){
    if(!node) return;
    treeToArrayRecurs(node->left, arr, i);
    arr[*i] = node->key;
    ++*i;
    treeToArrayRecurs(node->right, arr, i);
}

///
/// \param avlTree
/// \param node
/// \param key
/// \return
AVLTNode *search(AVLTree *avlTree,AVLTNode *node, char *key){
    if(!node) return NULL;
    if (((avlTree->cmp)(key,node->key)==0))return node;
    if ((avlTree->cmp)(key,node->key)<0) return search(avlTree,node->left, key);
    if ((avlTree->cmp)(key,node->key)>0) return search(avlTree,node->right, key);
}

///
/// \param avlTree
/// \param root
/// \param key
/// \return
AVLTNode* Delete(AVLTree *avlTree, AVLTNode* root, void *key) {
    if(root==NULL) return root;
    if ((avlTree->cmp)(key ,root->key)<0) 		    root->left =  Delete(avlTree,root->left,key);
    else if ((avlTree->cmp)(key ,root->key)>0)  	root->right = Delete(avlTree,root->right,key);
    else {
        if( (root->left == NULL) ||(root->right == NULL) ){
            AVLTNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp =root;
                root=NULL;
            }else {*root = *temp;}
        }
        else {
            AVLTNode* temp = minValueNode(root->right);
            root->key= temp->key;
            root->right = Delete(avlTree,root->right,*temp->key);
        }
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
}/**/