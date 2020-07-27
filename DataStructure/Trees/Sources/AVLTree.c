#include "../Headers/AVLTree.h"
#include "../../../System/Utils.h"


void printAVLTreeHelper(AVLTreeNode *root, int space, void (printFn)(void *));
void AVLTreeIsPresentRecurs(AVLTree *avlTree, AVLTreeNode *root, void *searchValue, int* found );
int max(int a,int b);
void AVLTreeToArrayRecurs(AVLTreeNode *node, void **arr, int *i);
void freeAVLTreeNode(AVLTreeNode **node, void (*freeFn)(void *));
AVLTreeNode* newBinaryTreeNode(void* key);
int height(AVLTreeNode *node);
void AVLTreeGetMaxStepsRecurs(AVLTreeNode * node, int * steps);
void AVLTreeGetMinStepsRecurs(AVLTreeNode * node, int * steps);
AVLTreeNode* AVLTreeMirrorHelper(AVLTreeNode* root);

/** This function calculates the max between two integers. 
 * @param a Reference int of comparision.
 * @param b  int to compare against.
 * @return Returns which ever is the greater of the two.
 **/
int max(int a, int b){
    return (a > b)? a : b;
}

/** Function that Left Rotates a Tree at a certain node.
* @param n node to rotate at.
* @return Returns the rotated sub-Tree at reference node n.
**/
AVLTreeNode *AVLLeftRotate(AVLTreeNode *n);

/** Function that Right rotates a Tree at a certain node.
* @param n  node to rotate at.
* @return returns the rotated sub-tree at reference node n.
**/
AVLTreeNode *AVLRightRotate(AVLTreeNode *n);

/** Gets the balance at a certain node n.
* @param n node to get the balance at
* @return returns the int balance at node n
**/
int AVLGetBalance(AVLTreeNode *n);

/** Prints the Tree Statistics:
  - Number of Nodes,
  - Height,
  - Minimum Steps to the minimum node,
  - Maximum Steps to the max node.
  - Rule Satisfaction:
        - Maximum node Rule(2^(h+1)-1)
        - Minimum node Rule(2*1.6^h)
            where h is the height of the tree.
* @param tree Reference to the AVL tree.
**/
void AVLTreePrintStats(AVLTree *tree){
    if (tree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "tree", "AVLTreePrintStats");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

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

/** Initialization Function for AVL Tree. A comparison function must be provided
  for the tree to be able to level its Nodes. Returns a reference to an allocated AVLTree pointer on the heap.
* @param cmp Reference to the comparator function.
* @return Pointer to the allocated AVL tree on the heap.
**/
AVLTree *AVLTreeInitialize(int (*cmp)(const void *, const void *), void (*freeFn)(void *)) {
    if (cmp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "cmp", "AVLTreeInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if (freeFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeFn", "AVLTreeInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    AVLTree *t = (AVLTree *) malloc(sizeof(AVLTree));
    if(!t){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "AVLTree", "AVLTreeInitialize");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }
    t->root = NULL;
    t->cmp = cmp;
    t->nodeCount=0;
    t->freeFn = freeFn;
    return t;
}

/** Creates a new Avl TreeNode for a given key.
* @param key Reference pointer to preallocated key.
* @return Returns a pointer to an allocated node on the heap.
**/
AVLTreeNode* newAVLTreeNode(void* key){

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "newAVLTreeNode");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    AVLTreeNode *p =  (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    if(!p){
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "AVLTreeNode", "newAVLTreeNode");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }
    p->key = key;
    p->left=NULL;
    p->right=NULL;
    p->height = 1;
    return p;
}

/** Given an AVL Tree's root node it frees it's elements recursively.Setting the root node to Null. 
* @param node Exact Reference to root node to start freeing at.
**/
void AVLTreeFreeHelper(AVLTreeNode** node, void (*freeFn)(void *)){

    if (*node==NULL) return;
    AVLTreeFreeHelper(&(*node)->left,freeFn);
    AVLTreeFreeHelper(&(*node)->right,freeFn);
    freeAVLTreeNode(node,freeFn);
    *node=NULL;
}

void AVLTreeFree(AVLTree* avlTree){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLTreeFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    AVLTreeFreeHelper(&avlTree->root,avlTree->freeFn);
}

/** Given a node it frees it's Key and the node. Setting both to Null.
* @param node Exact Reference for node to Free.
**/
void freeAVLTreeNode(AVLTreeNode **node, void (*freeFn)(void *)){
    if(*node) return;
    freeFn((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

/** Inserts a node at the a reference node (preferably the root) with the provided key if not present
  in the tree and returns a reference to the new node.
* @param avlTree Reference to the AVL tree.
* @param node reference for node to start inserting at preferably the root.
* @param key Reference to key to inset in the Tree.
* @return Returns reference to the new root.
**/
AVLTreeNode* AVLTreeInsertHelper(AVLTree * avlTree, AVLTreeNode *node, void *key) {
    if (node == NULL) {
        avlTree->nodeCount++;
        return newAVLTreeNode(key);
    }
    if ( (avlTree->cmp)(key ,node->key)<0) node->left = AVLTreeInsertHelper(avlTree, node->left, key);
    else if ((avlTree->cmp)(key ,node->key)>0) node->right = AVLTreeInsertHelper(avlTree, node->right, key);

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

void AVLTreeInsert(AVLTree *avlTree, void *key){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVL data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "AVL data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }


    avlTree->root = AVLTreeInsertHelper(avlTree,avlTree->root,key);
}

AVLTreeNode *AVLRightRotate(AVLTreeNode *n){
    AVLTreeNode *leftNode = (AVLTreeNode*)n->left;
    //   if(!leftNode) return n;
    AVLTreeNode *rightOfLeft = (AVLTreeNode*)leftNode->right;

    leftNode->right = n;
    n->left = rightOfLeft;

    n->height = max(height(n->left), height(n->right)) + 1;
    leftNode->height = max(height(leftNode->left), height(leftNode->right)) + 1;

    return leftNode;
}

AVLTreeNode *AVLLeftRotate(AVLTreeNode *n){
    AVLTreeNode *rightNode =(AVLTreeNode*) n->right;
    if(!rightNode) return n;
    AVLTreeNode *leftOfright = (AVLTreeNode*)rightNode->left;

    rightNode->left = n;
    n->right = leftOfright;

    n->height = max(height(n->left), height(n->right)) + 1;
    rightNode->height = max(height(rightNode->left), height(rightNode->right)) + 1;

    return rightNode;
}

/** Given a node get the height at the reference node node.
* @param node Gets the height at a reference node n.
* @return Returns int height of the tree.
**/
int height(AVLTreeNode *node){
    if (!node) return 0;
    return node->height;
}

int AVLGetBalance(AVLTreeNode *n){
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

/** Given a root node (i.e a to start search at for the reference node n) find the reference node
 and stores to inorder Successor for that node in the leftMost param.
* @param avlTree Reference to the AVL tree.
* @param root Reference to the root node.
* @param referenceNode  Reference node to get the in-order successor for.
* @param leftMost Pointer to store the inorder successor for that node.
**/
void AVLTreeInOrderSuccessorHelper(AVLTree *avlTree, AVLTreeNode* root, void * referenceNode, AVLTreeNode **leftMost) {
    if (root == NULL) {
        leftMost = NULL;
        return;}
    if ((avlTree->cmp)(root->key, referenceNode) == 0){
        if (root->right)
            *leftMost = AVLTreeMinValueNode(root->right);
    }
    else if ((avlTree->cmp)(referenceNode, root->key) < 0){
        *leftMost = root;
        AVLTreeInOrderSuccessorHelper(avlTree, root->left, referenceNode, leftMost);
    }
    else{
        AVLTreeInOrderSuccessorHelper(avlTree, root->right, referenceNode, leftMost);
    }
}

/** Given a root node (i.e a to start search at for the reference node n) find the reference node
 and stores to inorder Predecessor for that node in the rightMost param.
* @param avlTree Reference to the AVL tree.
* @param root Reference to the root node.
* @param key Reference node to get the in-order Predecessor for.
* @param rightMost Pointer to store the inorder Predecessor for that node.
**/
void AVLTreeInOrderPredecessorHelper(AVLTree *avlTree, AVLTreeNode *root, void *key, AVLTreeNode **rightMost){
    if (root == NULL) {
        rightMost = NULL;
        return;
    }
    if ((avlTree->cmp)(root->key, key) == 0){
        if (root->left)
            *rightMost = AVLTreeMaxValueNode(root->left);
    }
    else if ((avlTree->cmp)(key, root->key) < 0){
        AVLTreeInOrderPredecessorHelper(avlTree, root->left, key, rightMost);
    }
    else{
        *rightMost = root;
        AVLTreeInOrderPredecessorHelper(avlTree, root->right, key, rightMost);
    }
}

/** Prints a tree in 2 space of the console.
* @param root Reference to the root node.
* @param printFn Pointer to the print function.
**/
void AVLTreePrint(AVLTreeNode *root, void (printFn)(void *)){
    if (root == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "root", "AVL data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (printFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printFn", "AVL data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    printAVLTreeHelper(root, 0, printFn);
}

/** Helper function for printing the tree in 2d space.
* @param root Reference to the root node.
* @param space Number of spaces to print at the current level.
* @param printFn Pointer to the print function.
**/
void printAVLTreeHelper(AVLTreeNode *root, int space, void (printFn)(void *)){
    if (root == NULL)
        return;
    space += COUNT;
    printAVLTreeHelper(root->right, space, printFn);
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    (printFn)(root->key);
    printAVLTreeHelper(root->left, space, printFn);
}

/** Given a key, and a tree to search in determines whether a key is present in the tree or not.
* @param avlTree Reference to the AVL tree.
* @param searchKey key to search for in the tree.
* @return returns int as bool. Returns 1 if is found else returns 0.
**/
int AVLTreeIsPresent(AVLTree *avlTree, void* searchKey){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVL data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (searchKey == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "searchKey", "AVL data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    int found = 0;
    AVLTreeIsPresentRecurs(avlTree, avlTree->root, searchKey, &found);
    return found;
}

/** Helper Function to @link AVLTreeIsPresent @endlink that recursively checks if a node is present in the tree.
* @param avlTree Reference to the AVL tree.
* @param root Reference to the root node.
* @param searchValue Value to search for.
* @param found Int to act as boolean. If found it is 1 else set to 0.
**/
void AVLTreeIsPresentRecurs(AVLTree *avlTree, AVLTreeNode *root, void *searchValue, int* found ){
    if (root) {
        if ((avlTree->cmp)(root->key, searchValue) == 0)
            *found = 1;
        else {
            AVLTreeIsPresentRecurs(avlTree, root->left, searchValue, found);
            if (!(*found))
                AVLTreeIsPresentRecurs(avlTree, root->right, searchValue, found);
        }
    }
}

/** Reference to the root node to start calculating the size of tree.
* @param root Reference to the root node.
* @return the number of nodes in the tree.
**/
int AVLTreeGetSize(AVLTreeNode* root){
    if (root) return 1 + AVLTreeGetSize(root->left) + AVLTreeGetSize(root->right);
    else return 0;
}

/** Gets the right most node which should be the minimum item node of the AVLTree.
* @param node Node to start traversing from.
* @return Returns a reference pointer to the right most node.
**/
AVLTreeNode * AVLTreeMinValueNode(AVLTreeNode* node){
    if(!node) return NULL;
    if(node->left )return AVLTreeMinValueNode(node->left);
    return node;
}

/** Gets the left most node which should be the maximum item node of the AVL Tree.
* @param node Node to start traversing from.
* @return Returns a reference pointer to the left most node.
**/
AVLTreeNode * AVLTreeMaxValueNode(AVLTreeNode* node){
    if (!node) return NULL;
    if (node->right) return AVLTreeMaxValueNode(node->right);
    return node;
}

/**  Gets the minimum steps to reach the right most node recursively.
* @param node Node to start traversing from
* @return int reference to increment it's contents.
**/
int AVLTreeGetMinSteps(AVLTreeNode* node){
    int steps=0;
    AVLTreeGetMinStepsRecurs(node, &steps);
    return steps;
}

/** Gets the minimum steps to reach the right most node recursively.
* @param node Node to start traversing from
* @param steps int refernce to increment it's contents.
**/
void AVLTreeGetMinStepsRecurs(AVLTreeNode *node, int *steps){
    if(!node) return;
    *steps = *steps +1;
    if(node->left )AVLTreeGetMinStepsRecurs(node->left, steps);
}

/**  Gets the maximum steps to reach the left most node recursively.
* @param node Node to start traversing from
* @return int reference to increment it's contents.
**/
int AVLTreeGetMaxSteps(AVLTreeNode* node ){
    int steps = 0;
    AVLTreeGetMaxStepsRecurs(node, &steps);
    return steps;
}

/** Recursively gets the max steps of the tree.
* @param node Root to get the max from.
* @param steps int reference to store the steps in.
**/
void AVLTreeGetMaxStepsRecurs(AVLTreeNode* node, int *steps){
    if (!node) return;
    *steps = *steps+1;
    if (node->right) AVLTreeGetMaxStepsRecurs(node->right, steps);
}

/** Takes a print function and starts printing from using the provided print function.
* @param node Reference node to start printing from.
* @param printFn print function to use for printing node keys.
**/
void AVLTreePrintInOrder(AVLTreeNode* node, void (printFn)(void *)){
    if (printFn == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "printFn", "AVLTreePrintInOrder");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    if(!node)return;
    AVLTreePrintInOrder(node->left, printFn);
    (printFn)(node->key);
    AVLTreePrintInOrder(node->right, printFn);
}

/** Given a Tree converts it to an array in-order
* @param avlTree Reference to the AVL tree.
* @return returns an array of pointer references to keys that were stored in the tree.
**/
void **AVLTreeToArray(AVLTree *avlTree){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLTreeToArray");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    void **array = (void **) malloc(sizeof(void *) * avlTree->nodeCount);
    int i = 0;
    AVLTreeToArrayRecurs(avlTree->root, array, &i);
    return array;
}

/** Recursively traverses the tree in order and adds elements to an allocated array by @link AVLTreeToArray @endlink .
* @param node Node reference node to start converting from.
* @param arr Preallocated array to start storing at.
* @param i index to insert at in the array.
**/
void AVLTreeToArrayRecurs(AVLTreeNode *node, void **arr, int *i) {
    if(!node) return;
    AVLTreeToArrayRecurs(node->left, arr, i);
    arr[*i] = node->key;
    *i += 1;
    AVLTreeToArrayRecurs(node->right, arr, i);
}

/** Given a tree and a reference node to start searching at (preferably the root) searches for node with the same key and return it.
* @param avlTree Reference to the AVL tree.
* @param node node to start searching from preferably the root.
* @param key Key object to search for in the AVLTree.
* @return Returns the found node.
**/
AVLTreeNode *AVLTreeSearchHelper(AVLTree *avlTree, AVLTreeNode *node, char *key){
    if(!node) return NULL;
    if (((avlTree->cmp)(key,node->key)==0))return node;
    if ((avlTree->cmp)(key,node->key)<0) return AVLTreeSearchHelper(avlTree, node->left, key);
    if ((avlTree->cmp)(key,node->key)>0) return AVLTreeSearchHelper(avlTree, node->right, key);
}

AVLTreeNode *AVLTreeSearch(AVLTree *avlTree, char *key){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLTreeSearch");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "AVLTreeSearch");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    return AVLTreeSearchHelper(avlTree,avlTree->root,key);
}

/** Given a Tree and it's root deletes a key with the same key and restores the tree order then returns the new node.
* @param avlTree Reference to the AVL tree. Reference to the AVL tree.
* @param root Reference to the root node.
* @param key Key object to add to the AVLTree.
* @return Returns the new root node of the AVL Tree.
**/
AVLTreeNode* AVLTreeDeleteNodeWithFreeHelper(AVLTree *avlTree, AVLTreeNode* root, void *key) {
    if(root==NULL) return root;
    if ((avlTree->cmp)(key ,root->key)<0) 		    root->left = AVLTreeDeleteNodeWithFreeHelper(avlTree, root->left,
                                                                                                   key);
    else if ((avlTree->cmp)(key ,root->key)>0)  	root->right = AVLTreeDeleteNodeWithFreeHelper(avlTree, root->right,
                                                                                                 key);
    else {
        if( (root->left == NULL) ||(root->right == NULL) ){
            AVLTreeNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp =root;
                root=NULL;
                avlTree->freeFn(temp->key);
            }else {
                AVLTreeNode * old = root;
                root = temp;
                avlTree->freeFn(old->key);
            }
        }
        else {
            AVLTreeNode* temp = AVLTreeMinValueNode(root->right);
            avlTree->freeFn(root->key);
            root->key= temp->key;
            root->right = AVLTreeDeleteNodeWithFreeHelper(avlTree, root->right, temp->key);
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


AVLTreeNode* AVLTreeDeleteNodeWithoutFreeHelper(AVLTree *avlTree, AVLTreeNode* root, void *key) {
    if(root==NULL) return root;
    if ((avlTree->cmp)(key ,root->key)<0) 		    root->left = AVLTreeDeleteNodeWithoutFreeHelper(avlTree, root->left,
                                                                                                   key);
    else if ((avlTree->cmp)(key ,root->key)>0)  	root->right = AVLTreeDeleteNodeWithoutFreeHelper(avlTree, root->right,
                                                                                                 key);
    else {
        if( (root->left == NULL) ||(root->right == NULL) ){
            AVLTreeNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp =root;
                root=NULL;
            }else {
                root = temp;
            }
        }
        else {
            AVLTreeNode* temp = AVLTreeMinValueNode(root->right);
            root->key= temp->key;
            root->right = AVLTreeDeleteNodeWithFreeHelper(avlTree, root->right, temp->key);
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

///
/// \param avlTree
/// \param key
void AVLTreeDeleteNodeWithFree(AVLTree *avlTree, void *key) {
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLTreeDeleteNodeWithFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "AVLTreeDeleteNodeWithFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    avlTree->root = AVLTreeDeleteNodeWithFreeHelper(avlTree, avlTree->root, key);
}

void AVLTreeDeleteNodeWithoutFree(AVLTree *avlTree, void *key) {
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLTreeDeleteNodeWithoutFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (key == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "key", "AVLTreeDeleteNodeWithoutFree");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    avlTree->root = AVLTreeDeleteNodeWithoutFreeHelper(avlTree, avlTree->root, key);
}

/** Adds an array of void pointers to elements of the same type as the nodes of the tree.
* @param avlTree Reference to the AVL tree.
* @param array Array to add data from.
* @param length The Length of the array to add from.
* @return Returns the new root node.
**/
AVLTreeNode * AVLTreeInsertAll(AVLTree* avlTree, void **array, uint32_t length){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLTreeInsertAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (array == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "array", "AVLTreeInsertAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (length == 0) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "length", "AVLTreeInsertAll");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    for(uint32_t i =0; i<length;i++)
      AVLTreeInsert(avlTree,array[i]);
    return avlTree->root;
}

AVLTreeNode* AVLInOrderPredecessor(AVLTree *avlTree,void *referenceNode){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLInOrderPredecessor");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (referenceNode == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "referenceNode", "AVLInOrderPredecessor");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    AVLTreeNode * rightMost  = malloc(sizeof(*rightMost));
    AVLTreeInOrderPredecessorHelper(avlTree,avlTree->root,referenceNode,&rightMost);
    return rightMost;
}


AVLTreeNode* AVLInOrderSuccessor(AVLTree *avlTree, void *referenceNode){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "AVLInOrderSuccessor");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    if (referenceNode == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "referenceNode", "AVLInOrderSuccessor");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }
    AVLTreeNode * leftMost  = malloc(sizeof(*leftMost));
    AVLTreeInOrderSuccessorHelper(avlTree, avlTree->root,referenceNode,&leftMost);
    return leftMost;
}

///
/// \param node1
/// \param node2
/// \param cmpFn
/// \param flag
void avlTreeIsEqualHelper(AVLTreeNode* node1,AVLTreeNode* node2,int (*cmpFn)(const void *, const void *), int * flag){
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
    avlTreeIsEqualHelper(node1->right, node2->right,cmpFn,flag);
    if((cmpFn)(node1->key,node2->key)) *flag = 1;
    avlTreeIsEqualHelper(node1->left, node2->left, cmpFn,flag);
}

///
/// \param avlTree
/// \param avlTree2
/// \return
uint32_t avlTreeIsEqual(AVLTree *avlTree,AVLTree *avlTree2){
    if (avlTree == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree", "isEqual");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif

    }

    if (avlTree2 == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "avlTree2", "isEqual");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }

    if(avlTree->nodeCount < avlTree2->nodeCount) return -1;
    if(avlTree->nodeCount > avlTree2->nodeCount) return  1;
    else {
        uint32_t areEqual = 0;
        avlTreeIsEqualHelper(avlTree->root,avlTree2->root,avlTree->cmp, &areEqual);
        return areEqual;
    }
}

///
/// \param tree
/// \param root
/// \param item
/// \return
uint32_t AVLTreeContainsHelper(AVLTree * tree, AVLTreeNode* root, void *item){
    if (root == NULL) return 0;
    if (tree->cmp(item, root->key) == 0) return 1;
    else if (tree->cmp(item, root->key) < 0)
        return AVLTreeContainsHelper(tree, root->left, item);

    else
        return AVLTreeContainsHelper(tree, root->right, item);
}

///
/// \param tree
/// \param item
/// \return
uint32_t AVLTreeContains(AVLTree * tree, void *item){

    if (tree == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "AVLTreeContains");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
        #else
                exit(NULL_POINTER);
        #endif

    } else if (item == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "item", "AVLTreeContains");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
        #else
                exit(INVALID_ARG);
        #endif
    }

    return AVLTreeContainsHelper(tree, tree->root, item);
}

AVLTreeNode* AVLTreeMirrorHelper(AVLTreeNode* root){
    if (root==NULL) return root;
    else{
        AVLTreeNode* temp;

        root->left = AVLTreeMirrorHelper(root->left);
        root->right = AVLTreeMirrorHelper(root->right);


        temp        = root->left;
        root->left  = root->right;
        root->right = temp;
    }
    return root;
}

///
/// \param avlTree
void AVLTreeMirror(AVLTree* avlTree){
    if (avlTree == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "avlTree", "AVLTreeMirror");
        #ifdef CU_TEST_H
                DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
        #else
                exit(NULL_POINTER);
        #endif
    }
        avlTree->root = AVLTreeMirrorHelper(avlTree->root);
}


