#include "../Headers/BinaryTree.h"

void freeBinaryTreeNode(BinaryTreeNode **node,void (*freeFn)(void *));
void printBinaryTreeHelper(BinaryTreeNode *root, int space, void (printFn)(void *));
void BinaryTreeIsPresentRecurs(BinaryTree *binaryTree, BinaryTreeNode *root, void *searchValue, int* found );
void BinaryTreeToArrayRecurs(BinaryTreeNode* node , void **arr, int *i,int size );
BinaryTreeNode* newBinaryTreeNode(void* key);
void BinaryTreeGetMaxStepsRecurs(BinaryTreeNode * node, int * steps);
void BinaryTreeGetMinStepsRecurs(BinaryTreeNode * node, int * steps);
BinaryTreeNode* DeleteBinaryTreeNodeWrapper(BinaryTree *binaryTree, BinaryTreeNode* root, void *key);

/** Prints the Tree Statistics:
  - Number of Nodes,
  - Height,
  - Minimum Steps to the minimum node,
  - Maximum Steps to the max node.
  - Rule Satisfaction:
        - Maximum node Rule(2^(h+1)-1)
        - Minimum node Rule(2*1.6^h)
            where h is the height of the tree.
* @param tree Reference to the Binary tree.
**/
void printBinaryTreeStats(BinaryTree *tree){
    if(tree&&tree->root){
        printf("............................\n");
        printf("Size = %d\n", tree->nodeCount);
        printf("............................\n");
        printf("............................\n");
        printf("Minimum Steps %d\n", BinaryTreeGetMinSteps(tree->root));
        printf("............................\n");
        printf("Maximum Steps %d\n", BinaryTreeGetMaxSteps(tree->root));
        printf("............................\n");
    }else{
        printf("Binary Tree Did Not Load Successfully...!\n");
    }
}

/** Initialization Function for Binary Tree. A comparison function must be provided
  for the tree to be able to level its Nodes. Returns a reference to an allocated BinaryTree pointer on the heap.
* @param cmp Reference to the comparator function.
* @return Pointer to the allocated Binary tree on the heap.
**/
BinaryTree* BinaryTreeInitialize( int size, int(*cmp)(const void*, const void*), void (*freeFn)(void *)){
    BinaryTree *t = (BinaryTree *) malloc(sizeof(BinaryTree));
    if(!t){
        fprintf(stderr,"Failed at allocating tree\n");
        exit(-1);
    }
    t->root = NULL;
    t->sizeOfType =size;
    t->cmp = cmp;
    t->nodeCount =0;
    t->freeFn = freeFn;
    return t;
}

/** Creates a new Binary TreeNode for a given key.
* @param key Reference pointer to preallocated key.
* @return Returns a pointer to an allocated node on the heap.
**/
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

/** Given an Binary Tree's root node it frees it's elements recursively.Setting the root node to Null.
* @param node Exact Reference to root node to start freeing at.
**/
void BinaryTreeFreeWrapper(BinaryTreeNode** node,void (*freeFn)(void*)){
    if (*node==NULL) return;
    BinaryTreeFreeWrapper(&(*node)->left,freeFn);
    BinaryTreeFreeWrapper(&(*node)->right,freeFn);
    freeBinaryTreeNode(node,freeFn);
    *node=NULL;
}

void BinaryTreeFree(BinaryTree* binaryTree){
    BinaryTreeFreeWrapper(&binaryTree->root,binaryTree->freeFn);
}

/** Given a node it frees it's Key and the node. Setting both to Null.
* @param node Exact Reference for node to Free.
**/
void freeBinaryTreeNode(BinaryTreeNode **node,void (*freeFn)(void *)){
    if(*node) return;
    freeFn((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

/** Inserts a node at the a reference node (preferably the root) with the provided key if not present
  in the tree and returns a reference to the new node.
* @param binaryTree Reference to the Binary tree.
* @param node reference for node to start inserting at preferably the root.
* @param key Reference to key to inset in the Tree.
* @return Returns reference to the new root.
**/
BinaryTreeNode* BinaryTreeInsertWrapper(BinaryTree * binaryTree, BinaryTreeNode *node, void *key) {
    if (node == NULL) {
        binaryTree->nodeCount++;
        return newBinaryTreeNode(key);
    }
    if ( (binaryTree->cmp)(key ,node->key)<0) node->left = BinaryTreeInsertWrapper(binaryTree, node->left, key);
    else if ((binaryTree->cmp)(key ,node->key)>0) node->right = BinaryTreeInsertWrapper(binaryTree, node->right, key);

    return node;
}

/** Given a root node (i.e a to start search at for the reference node n) find the reference node
 and stores to inorder Successor for that node in the leftMost param.
* @param binaryTree Reference to the binary tree.
* @param root Reference to the root node.
* @param referenceNode  Reference node to get the in-order successor for.
* @param leftMost Pointer to store the inorder successor for that node.
**/
void BinaryTreeInOrderSuccessorWrapper(BinaryTree *binaryTree, BinaryTreeNode* root, BinaryTreeNode* referenceNode, BinaryTreeNode **leftMost) {
    if (root == NULL) {
        leftMost = NULL;
        return;}
    if ((binaryTree->cmp)(root->key, referenceNode->key) == 0){
        if (root->right)
            *leftMost = BinaryTreeMinValueNode(root->right);
    }
    else if ((binaryTree->cmp)(referenceNode->key, root->key) < 0){
        *leftMost = root;
        BinaryTreeInOrderSuccessorWrapper(binaryTree, root->left, referenceNode, leftMost);
    }
    else{
        BinaryTreeInOrderSuccessorWrapper(binaryTree, root->right, referenceNode, leftMost);
    }
}

/** Given a root node (i.e a to start search at for the reference node n) find the reference node
 and stores to inorder Predecessor for that node in the rightMost param.
* @param binaryTree Reference to the Binary tree.
* @param root Reference to the root node.
* @param referenceNode Reference node to get the in-order Predecessor for.
* @param rightMost Pointer to store the inorder Predecessor for that node.
**/
void BinaryTreeInOrderPredecessorWrapper(BinaryTree *binaryTree, BinaryTreeNode *root, BinaryTreeNode *referenceNode, BinaryTreeNode **rightMost){
    if (root == NULL) {
        rightMost = NULL;
        return;}
    if ((binaryTree->cmp)(root->key, referenceNode->key) == 0){
        if (root->left)
            *rightMost = maxValueBinaryTreeNode(root->left);
    }
    else if ((binaryTree->cmp)(referenceNode->key, root->key) < 0){
        BinaryTreeInOrderPredecessorWrapper(binaryTree, root->left, referenceNode, rightMost);
    }
    else{
        *rightMost = root;
        BinaryTreeInOrderPredecessorWrapper(binaryTree, root->right, referenceNode, rightMost);
    }
}

/** Prints a tree in 2 space of the console.
* @param root Reference to the root node.
* @param printFn Pointer to the print function.
**/
void BinaryTreePrint(BinaryTreeNode *root, void (printFn)(void *)){
    printBinaryTreeHelper(root, 0, printFn);
}

/** Helper function for printing the tree in 2d space.
* @param root Reference to the root node.
* @param space Number of spaces to print at the current level.
* @param printFn Pointer to the print function.
**/
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

/** Given a key, and a tree to search in determines whether a key is present in the tree or not.
* @param binaryTree Reference to the Binary tree.
* @param searchKey key to search for in the tree.
* @return returns int as bool. Returns 1 if is found else returns 0.
**/
int BinaryTreeIsPresent(BinaryTree *binaryTree, void* searchKey){
    int found = 0;
    BinaryTreeIsPresentRecurs(binaryTree, binaryTree->root, searchKey, &found);
    return found;
}

/** Helper Function to @link BinaryTreeIsPresent @endlink that recursively checks if a node is present in the tree.
* @param binaryTree Reference to the Binary tree.
* @param root Reference to the root node.
* @param searchValue Value to search for.
* @param found Int to act as boolean. If found it is 1 else set to 0.
**/
void BinaryTreeIsPresentRecurs(BinaryTree *binaryTree, BinaryTreeNode *root, void *searchValue, int* found ){
    if (root) {
        if ((binaryTree->cmp)(root->key, searchValue) == 0)
            *found = 1;
        else {
            BinaryTreeIsPresentRecurs(binaryTree, root->left, searchValue, found);
            if (!(*found))
                BinaryTreeIsPresentRecurs(binaryTree, root->right, searchValue, found);

        }
    }
}

/** Reference to the root node to start calculating the size of tree.
* @param root Reference to the root node.
* @return the number of nodes in the tree.
**/
int BinaryTreeGetSize(BinaryTreeNode* root){
    if (root) return 1 + BinaryTreeGetSize(root->left) + BinaryTreeGetSize(root->right);
    else return 0;
}

/** Gets the right most node which should be the minimum item node of the Binary Tree.
* @param node Node to start traversing from.
* @return Returns a reference pointer to the right most node.
**/
BinaryTreeNode * BinaryTreeMinValueNode(BinaryTreeNode* node){
    if(!node) return NULL;
    if(node->left )return BinaryTreeMinValueNode(node->left);
    return node;
}

/** Gets the left most node which should be the maximum item node of the Binary Tree.
* @param node Node to start traversing from.
* @return Returns a reference pointer to the left most node.
**/
BinaryTreeNode * maxValueBinaryTreeNode(BinaryTreeNode* node){
    if (!node) return NULL;
    if (node->right) return maxValueBinaryTreeNode(node->right);
    return node;
}

/**  Gets the minimum steps to reach the right most node recursively.
* @param node Node to start traversing from
* @return int reference to increment it's contents.
**/
int BinaryTreeGetMinSteps(BinaryTreeNode* node){
    int steps=0;
    BinaryTreeGetMinStepsRecurs(node, &steps);
    return steps;
}

/**  Gets the maximum steps to reach the left most node recursively.
* @param node Node to start traversing from
* @param steps int reference to increment it's contents.
**/
void BinaryTreeGetMinStepsRecurs(BinaryTreeNode *node, int *steps){
    if(!node) return;
    *steps = *steps +1;
    if(node->left )BinaryTreeGetMinStepsRecurs(node->left, steps);
}

/** Recursively gets the max steps of the tree.
* @param node Root to get the max from.
* @return int steps to max left most node.
**/
int BinaryTreeGetMaxSteps(BinaryTreeNode* node ){
    int steps = 0;
    BinaryTreeGetMaxStepsRecurs(node, &steps);
    return steps;
}

/** Recursively gets the max steps of the tree.
* @param node Root to get the max from.
* @param steps int refernce to store the steps in.
**/
void BinaryTreeGetMaxStepsRecurs(BinaryTreeNode* node, int *steps){
    if (!node) return;
    *steps = *steps+1;
    if (node->right) BinaryTreeGetMaxStepsRecurs(node->right, steps);
}

/** Takes a print function and starts printing from using the provided print function.
* @param node Reference node to start printing from.
* @param printFn print function to use for printing node keys.
**/
void BinaryTreePrintInOrder(BinaryTreeNode* node, void (printFn)(void *)){
    if(!node)return;
    BinaryTreePrintInOrder(node->left, printFn);
    (printFn)(node->key);
    BinaryTreePrintInOrder(node->right, printFn);
}

/** Given a Tree converts it to an array in-order
* @param binaryTree Reference to the Binary tree.
* @return returns an array of pointer references to keys that were stored in the tree.
**/
void **BinaryTreeToArray(BinaryTree *binaryTree){
    void **array = (void **) malloc(sizeof(void *) * binaryTree->nodeCount);
    int i = 0;
    BinaryTreeToArrayRecurs(binaryTree->root, array, &i,binaryTree->sizeOfType);
    return array;
}

/** Recursively traverses the tree in order and adds elements to an allocated array by @link BinaryTreeToArray @endlink .
* @param node Node reference node to start converting from.
* @param arr Preallocated array to start storing at.
* @param i index to insert at in the array.
**/
void BinaryTreeToArrayRecurs(BinaryTreeNode* node , void **arr, int *i,int size ){
    if(!node) return;
    BinaryTreeToArrayRecurs(node->left, arr, i,size);
    arr[*i] = malloc(size);
    memcpy(arr+*i,node->key,size);
    *i += 1;
    BinaryTreeToArrayRecurs(node->right, arr, i,size);
}

/** Given a tree and a reference node to start searching at (preferably the root) searches for node with the same key and return it.
* @param binaryTree Reference to the Binary tree.
* @param node node to start searching from preferably the root.
* @param key Key object to search for in the Binary Tree.
* @return Returns the Found node.
**/
BinaryTreeNode *BinaryTreeSearchWrapper(BinaryTree *binaryTree, BinaryTreeNode *node, char *key){
    if(!node) return NULL;
    if (((binaryTree->cmp)(key,node->key)==0))return node;
    if ((binaryTree->cmp)(key,node->key)<0) return BinaryTreeSearchWrapper(binaryTree, node->left, key);
    if ((binaryTree->cmp)(key,node->key)>0) return BinaryTreeSearchWrapper(binaryTree, node->right, key);
}

///
/// \param binaryTree
/// \param key
/// \return
BinaryTreeNode* BinaryTreeSearch(BinaryTree* binaryTree, void * key){
    return BinaryTreeSearchWrapper(binaryTree,binaryTree->root,key);
}

///
/// \param binaryTree
/// \param key
void DeleteBinaryTreeNode(BinaryTree *binaryTree, void *key) {
    binaryTree->root = DeleteBinaryTreeNodeWrapper(binaryTree,binaryTree->root,key);
}

/** Given a Tree and it's root deletes a key with the same key and restores the tree order then returns the new node.
* @param binaryTree Reference to the Binary tree. Reference to the Binary tree.
* @param root Reference to the root node.
* @param key Key object to add to the Binary Tree.
* @return Returns the new root node of the Binary Tree.
**/
BinaryTreeNode* DeleteBinaryTreeNodeWrapper(BinaryTree *binaryTree, BinaryTreeNode* root, void *key) {
    if(root==NULL) return root;
    if ((binaryTree->cmp)(key ,root->key)<0) 		root->left = DeleteBinaryTreeNodeWrapper(binaryTree, root->left, key);
    else if ((binaryTree->cmp)(key ,root->key)>0)  	root->right = DeleteBinaryTreeNodeWrapper(binaryTree, root->right, key);
    else {
        if( (root->left == NULL) ||(root->right == NULL) ){
            BinaryTreeNode *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp =root;
                root=NULL;
            }else {*root = *temp;}
        }
        else {
            BinaryTreeNode* temp = BinaryTreeMinValueNode(root->right);
            root->key= temp->key;
            root->right = DeleteBinaryTreeNodeWrapper(binaryTree, root->right, temp->key);
        }
        binaryTree->nodeCount--;
    }
    return root;
}

/** Adds an array of void pointers to elements of the same type as the nodes of the tree.
* @param binaryTree Reference to the Binary tree.
* @param array Array to add data from.
* @param length The Length of the array to add from.
**/
void  BinaryTreeInsertAll(BinaryTree* binaryTree, void** array, uint32_t length){
    for(uint32_t i=0;i<length;i++)
        BinaryTreeInsert(binaryTree, array[i]);

}
///
/// \param binaryTree
/// \param referenceNode
/// \return
BinaryTreeNode* BinaryTreeInOrderPredecessor(BinaryTree *binaryTree,BinaryTreeNode *referenceNode){
    BinaryTreeNode * rightMost  = malloc(sizeof(*rightMost));
    BinaryTreeInOrderPredecessorWrapper(binaryTree,binaryTree->root,referenceNode,&rightMost);
    return rightMost;
}

///
/// \param binaryTree
/// \param referenceNode
/// \return
BinaryTreeNode* BinaryTreeInOrderSuccessor(BinaryTree *binaryTree, BinaryTreeNode *referenceNode){
    BinaryTreeNode * leftMost  = malloc(sizeof(*leftMost));
    BinaryTreeInOrderSuccessorWrapper(binaryTree, binaryTree->root,referenceNode,&leftMost);
    return leftMost;
}

///
/// \param binaryTree
/// \param key
/// \return
void BinaryTreeInsert(BinaryTree *binaryTree, void *key){
    binaryTree->root = BinaryTreeInsertWrapper(binaryTree,binaryTree->root,key);
}