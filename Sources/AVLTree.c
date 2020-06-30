#include "../Headers/AVLTree.h"


void printAVLTreeHelper(AVLTNode *root, int space, void (printFn)(void *));
void isPresentInAVLTreeRecurs(AVLTree *avlTree, AVLTNode *root, void *searchValue, int* found );
int max(int a,int b);
void AVLTreeToArrayRecurs(AVLTNode* node, void **arr, int *i);
void freeAVLTreeNode(AVLTNode **node);
AVLTNode* newBinaryTreeNode(void* key);
int height(AVLTNode *node);
void getMaxStepsAVLTreeRecurs(AVLTNode * node, int * steps);
void getMinStepsAVLTreeRecurs(AVLTNode * node, int * steps);


/* This function calculates the max between two integers. 
 * @param a Reference int of comparision.
 * @param b  int to compare against.
 * @return Returns which ever is the greater of the two.
 **/
int max(int a, int b){
    return (a > b)? a : b;
}

/* Function that Left Rotates a Tree at a certain Node.
* @param n Node to rotate at.
* @return Returns the rotated sub-Tree.
**/
AVLTNode *AVLLeftRotate(AVLTNode *n);

/* Function that Right rotates a Tree at a certain Node.
* @param n  Node to rotate at.
* @return
**/
AVLTNode *AVLRightRotate(AVLTNode *n);

/* Gets the balance at a certain Node n.
* @param n Node to get the balance at
* @return
**/
int AVLGetBalance(AVLTNode *n);

/* Prints the Tree Statistics:
  - Number of Nodes,
  - Height,
  - Minimum Steps to the minimum Node,
  - Maximum Steps to the max Node.
  - Rule Satisfaction:
        - Maximum node Rule(2^(h+1)-1)
        - Minimum node Rule(2*1.6^h)
            where h is the height of the tree.
* @param tree
**/
void AVLTreePrintStats(AVLTree *tree){
    if(tree&&tree->root){
        printf("............................\n");
        printf("Size = %d\n", tree->nodeCount);
        printf("............................\n");
        printf("Height = %d\n",tree->root->height);
        printf("............................\n");
        printf("Minimum Steps %d\n", AVLTreeGetMinSteps(tree->root));
        printf("............................\n");
        printf("Maximum Steps %d\n", AVLTreeGetMaxSteps(tree->root));
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

/* Initialization Function for AVL Tree. A comparison function must be provided
  for the tree to be able to level its Nodes. Returns a reference to an allocated AVLTree pointer on the heap.
* @param cmp Reference to the comparator function.
* @return Pointer to the allocated AVL tree on the heap.
**/
AVLTree* AVLTreeInitialize(int(*cmp)(const void*, const void*)){
    AVLTree *t = (AVLTree *) malloc(sizeof(AVLTree));
    if(!t){
        fprintf(stderr,"Failed at allocating tree\n");
        exit(-1);
    }
    t->root = NULL;
    t->cmp = cmp;
    t->nodeCount=0;
    return t;
}

/* Creates a new Avl TreeNode for a given key.
* @param key Reference pointer to preallocated key.
* @return Returns a pointer to an allocated Node on the Stack. 
**/
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

/* Given an AVL Tree's root node it frees it's elements recursively.Setting the root node to Null. 
* @param node root Node to start freeing at.
**/
void AVLTreeFree(AVLTNode** node){
    if (*node==NULL) return;
    AVLTreeFree(&(*node)->left);
    AVLTreeFree(&(*node)->right);
    freeAVLTreeNode(node);
    *node=NULL;
}

/* Given a Node it frees it's Key and the Node. Setting both to Null.
* @param node
**/
void freeAVLTreeNode(AVLTNode **node){
    if(*node) return;
    free((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

/*
* @param avlTree Reference to the AVL tree.
* @param node
* @param key
* @return
**/
AVLTNode* AVLTreeInsert(AVLTree * avlTree, AVLTNode *node, void *key) {
    if (node == NULL) {
        avlTree->nodeCount++;
        return newAVLTreeNode(key);
    }
    if ( (avlTree->cmp)(key ,node->key)<0) node->left = AVLTreeInsert(avlTree, node->left, key);
    else if ((avlTree->cmp)(key ,node->key)>0) node->right = AVLTreeInsert(avlTree, node->right, key);

    node->height = max(height(node->left),height(node->right))+1;

    int balance = AVLGetBalance(node);

    // Left Left Case
    if (balance > 1 && (avlTree->cmp)(key, node->left->key)<0)
        return AVLRightRotate(node);

    // Right Right Case
    if (balance < -1 && (avlTree->cmp)(key, node->right->key)>0)
        return AVLLeftRotate(node);

    // Left Right Case
    if (balance > 1 && (avlTree->cmp)(key, node->left->key)>0){
        node->left = AVLLeftRotate(node->left);
        return AVLRightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && (avlTree->cmp)(key,node->right->key)<0){
        node->right = AVLRightRotate(node->right);
        return AVLLeftRotate(node);
    }

    return node;
}


AVLTNode *AVLRightRotate(AVLTNode *n){
    AVLTNode *leftNode = (AVLTNode*)n->left;
    //   if(!leftNode) return n;
    AVLTNode *rightOfLeft = (AVLTNode*)leftNode->right;

    leftNode->right = n;
    n->left = rightOfLeft;

    n->height = max(height(n->left), height(n->right)) + 1;
    leftNode->height = max(height(leftNode->left), height(leftNode->right)) + 1;

    return leftNode;
}

AVLTNode *AVLLeftRotate(AVLTNode *n){
    AVLTNode *rightNode =(AVLTNode*) n->right;
    //   if(!rightNode) return n;
    AVLTNode *leftOfright = (AVLTNode*)rightNode->left;

    rightNode->left = n;
    n->right = leftOfright;

    n->height = max(height(n->left), height(n->right)) + 1;
    rightNode->height = max(height(rightNode->left), height(rightNode->right)) + 1;

    return rightNode;
}

/*
* @param node Gets the height at a reference node n.
* @return Returns int height of the tree.
**/
int height(AVLTNode *node){
    if (!node) return 0;
    return node->height;
}

int AVLGetBalance(AVLTNode *n){
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

/*
* @param avlTree Reference to the AVL tree.
* @param root Reference to the root Node.
* @param referenceNode  Reference Node to get the in-order successor for.
* @param leftMost Pointer to store the inorder successor for that Node.
**/
void AVLTreeInOrderSuccessor(AVLTree *avlTree, AVLTNode* root, AVLTNode* referenceNode, AVLTNode **leftMost) {
    if (root == NULL) {
        leftMost = NULL;
        return;}
    if ((avlTree->cmp)(root->key, referenceNode->key) == 0){
        if (root->right)
            *leftMost = AVLTreeMinValueNode(root->right);
    }
    else if ((avlTree->cmp)(referenceNode->key, root->key) < 0){
        *leftMost = root;
        AVLTreeInOrderSuccessor(avlTree, root->left, referenceNode, leftMost);
    }
    else{
        AVLTreeInOrderSuccessor(avlTree, root->right, referenceNode, leftMost);
    }
}

/*
* @param avlTree Reference to the AVL tree.
* @param root Reference to the root Node.
* @param referenceNode Reference Node to get the in-order Predecessor for.
* @param rightMost Pointer to store the inorder Predecessor for that Node.
**/
void inOrderPredecessorAVLTree(AVLTree *avlTree, AVLTNode *root, AVLTNode *referenceNode, AVLTNode **rightMost){
    if (root == NULL) {
        rightMost = NULL;
        return;
    }
    if ((avlTree->cmp)(root->key, referenceNode->key) == 0){
        if (root->left)
            *rightMost = AVLTreeMaxValueNode(root->left);
    }
    else if ((avlTree->cmp)(referenceNode->key, root->key) < 0){
        inOrderPredecessorAVLTree(avlTree, root->left, referenceNode, rightMost);
    }
    else{
        *rightMost = root;
        inOrderPredecessorAVLTree(avlTree, root->right, referenceNode, rightMost);
    }
}

/*
* @param root Reference to the root Node.
* @param printFn
**/
void AVLTreePrint(AVLTNode *root, void (printFn)(void *)){
    printAVLTreeHelper(root, 0, printFn);
}

/*
* @param root Reference to the root Node.
* @param space
* @param printFn
**/
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

/*
* @param avlTree Reference to the AVL tree.
* @param root Reference to the root Node.
* @param searchKey
* @return
**/
int AVLTreeIsPresent(AVLTree *avlTree, void* searchKey){
    int found = 0;
    isPresentInAVLTreeRecurs(avlTree, avlTree->root, searchKey, &found);
    return found;
}

/*
* @param avlTree Reference to the AVL tree.
* @param root Reference to the root Node.
* @param searchValue Value to search for.
* @param found Int to act as boolean. If found it is 1 else set to 0.
**/
void isPresentInAVLTreeRecurs(AVLTree *avlTree, AVLTNode *root, void *searchValue, int* found ){
    if (root) {
        if ((avlTree->cmp)(root->key, searchValue) == 0)
            *found = 1;
        else {
            isPresentInAVLTreeRecurs(avlTree, root->left, searchValue, found);
            if (!(*found))
                isPresentInAVLTreeRecurs(avlTree, root->right, searchValue, found);
        }
    }
}

/*
* @param root Reference to the root Node.
* @return
**/
int AVLTreeGetSize(AVLTNode* root){
    if (root) return 1 + AVLTreeGetSize(root->left) + AVLTreeGetSize(root->right);
    else return 0;
}

/*
* @param node
* @return
**/
AVLTNode * AVLTreeMinValueNode(AVLTNode* node){
    if(!node) return NULL;
    if(node->left )return AVLTreeMinValueNode(node->left);
    return node;
}

/*
* @param node
* @return
**/
AVLTNode * AVLTreeMaxValueNode(AVLTNode* node){
    if (!node) return NULL;
    if (node->right) return AVLTreeMaxValueNode(node->right);
    return node;
}

/*
* @param node
* @return
* */
int AVLTreeGetMinSteps(AVLTNode* node){
    int steps=0;
    getMinStepsAVLTreeRecurs(node, &steps);
    return steps;
}

/*
* @param node
* @param steps
**/
void getMinStepsAVLTreeRecurs(AVLTNode *node, int *steps){
    if(!node) return;
    *steps = *steps +1;
    if(node->left )getMinStepsAVLTreeRecurs(node->left, steps);
}

/*
* @param node
* @return
**/
int AVLTreeGetMaxSteps(AVLTNode* node ){
    int steps = 0;
    getMaxStepsAVLTreeRecurs(node, &steps);
    return steps;
}

/*
* @param node
* @param steps
**/
void getMaxStepsAVLTreeRecurs(AVLTNode* node, int *steps){
    if (!node) return;
    *steps = *steps+1;
    if (node->right) getMaxStepsAVLTreeRecurs(node->right, steps);
}

/*
* @param node
* @param printFn
**/
void AVLTreePrintInOrder(AVLTNode* node, void (printFn)(void *)){
    if(!node)return;
    AVLTreePrintInOrder(node->left, printFn);
    (printFn)(node->key);
    AVLTreePrintInOrder(node->right, printFn);
}

/*
* @param avlTree Reference to the AVL tree.
* @return
**/
void **AVLTreeToArray(AVLTree *avlTree){
    void **array = (void **) malloc(sizeof(void *) * avlTree->nodeCount);
    int i = 0;
    AVLTreeToArrayRecurs(avlTree->root,array, &i);
    return array;
}

/*
* @param node
* @param arr
* @param i
**/
void AVLTreeToArrayRecurs(AVLTNode* node, void **arr, int *i){
    if(!node) return;
    AVLTreeToArrayRecurs(node->left, arr, i);
    arr[*i] = node->key;
    *i += 1;
    AVLTreeToArrayRecurs(node->right, arr, i);
}

/*
* @param avlTree Reference to the AVL tree.
* @param node Node to start searching from preferably the root.
* @param key Key object to search for in the AVLTree.
* @return Returns the Found Node.
**/
AVLTNode *AVLTreeSearch(AVLTree *avlTree, AVLTNode *node, char *key){
    if(!node) return NULL;
    if (((avlTree->cmp)(key,node->key)==0))return node;
    if ((avlTree->cmp)(key,node->key)<0) return AVLTreeSearch(avlTree, node->left, key);
    if ((avlTree->cmp)(key,node->key)>0) return AVLTreeSearch(avlTree, node->right, key);
}

/*
* @param avlTree Reference to the AVL tree. Reference to the AVL tree.
* @param root Reference to the root Node.
* @param key Key object to add to the AVLTree.
* @return Returns the new root Node of the AVL Tree.
**/
AVLTNode* AVLTreeDeleteNode(AVLTree *avlTree, AVLTNode* root, void *key) {
    if(root==NULL) return root;
    if ((avlTree->cmp)(key ,root->key)<0) 		    root->left = AVLTreeDeleteNode(avlTree, root->left, key);
    else if ((avlTree->cmp)(key ,root->key)>0)  	root->right = AVLTreeDeleteNode(avlTree, root->right, key);
    else {
        if( (root->left == NULL) ||(root->right == NULL) ){
            AVLTNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp =root;
                root=NULL;
            }else {*root = *temp;}
        }
        else {
            AVLTNode* temp = AVLTreeMinValueNode(root->right);
            root->key= temp->key;
            root->right = AVLTreeDeleteNode(avlTree, root->right, temp->key);
        }
        avlTree->nodeCount--;
    }
    if(root==NULL) return root;
    root->height = 1 + max(height(root->left),height(root->right));
    int balance = AVLGetBalance(root);

    //Left Left Case
    if(balance > 1 && AVLGetBalance(root->left) >= 0)   return AVLRightRotate(root);

    // Right Right Case
    if(balance < -1 && AVLGetBalance(root->right) <= 0)	return AVLLeftRotate(root);

    // Left Right Case
    if(balance > 1 && AVLGetBalance(root->left) < 0)	{
        root->left = AVLLeftRotate(root->left);
        return AVLRightRotate(root);
    }

    //Right Left Case
    if(balance < -1 && AVLGetBalance(root->right) > 0) {
        root->right = AVLRightRotate(root->right);
        return AVLLeftRotate(root);
    }
    return root;
}

/* Adds an array of void pointers to elements of the same type as the nodes of the tree.
* @param avlTree Reference to the AVL tree.
* @param array Array to add data from.
* @param length The Length of the array to add from.
* @return Returns the new root Node.
**/
AVLTNode * AVLTreeAddAll(AVLTree* avlTree,void **array, int length){
    for(int i =0; i<length;i++){
        avlTree->root = AVLTreeInsert(avlTree,avlTree->root,array[i]);
    }
    return avlTree->root;
}