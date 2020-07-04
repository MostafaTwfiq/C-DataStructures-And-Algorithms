#include "../Headers/RedBlackTree.h"
typedef enum RotationType{
    NONE, RIGHT, LEFT, RIGHT_LEFT, LEFT_RIGHT
} RotationType;

RBNode *rBTreeInsertR(RBNode *root, RBNode *parent, void *item, int (*cmp)(const void *, const void *));
void rBTreeDeleteR(RBTree *tree, RBNode *root, void *item);
RBNode *getUncle(RBNode *currentNode);
COLOR getNodeColor(RBNode *node);
RotationType getRotationType(RBNode *grandParent);
RBNode *performRotation(RBNode *node, RotationType rotationType);
RBNode *leftRotation(RBNode *grandParent);
RBNode *rightRotation(RBNode *grandParent);
int isRequiredRotation(RBNode *grandParent);
void rBPreOrderTraversalR(RBNode *root, void (*printFun)(const void *item, COLOR color));
int isCaseOne(RBNode *root);
RBNode *getSuccessorNode(RBNode *node);
void performRotationRecoloring(RBNode *root, RotationType rotationType);
void doubleBlackCase(RBTree *tree, RBNode *root, RBNode *parent);
void deleteNodeLeafCase(RBTree *tree, RBNode *root);
void deleteRightNullNode(RBTree *tree, RBNode *root);
void deleteRightNoneNullNode(RBTree *tree, RBNode *root);
void deleteLeftNullNode(RBTree *tree, RBNode *root);
RotationType doubleBlackCaseRotationType(RBNode *grandParent, RBNode *parent, RBNode *grandSon);
void doubleBlackCasePerformRotation(RBTree *tree, RBNode *parent, RotationType rotationType);
void RBTreeToArrayRecurs(RBNode *node, void **arr, int *i, int size);
void RBIsPresentRecurs(RBTree *rbTree, RBNode *root, void *searchValue, int *found);


/** Initialization Function for Red Black Tree. A comparison function must be provided
  for the tree to be able to level its Nodes. Returns a reference to an allocated Red Black Tree pointer on the heap.
 * @param sizeOfType size of the data type that is going to be stored in the tree 
 * @param cmp Reference to the comparator function. Reference to the comparator function.
 * @return Pointer to the allocated Red Black tree on the heap.
 * */
RBTree *redBlackTreeInitialization(int sizeOfType, int (*cmp)(const void*, const void *)) {
    RBTree *tree = (RBTree *) malloc(sizeof(RBTree));
    tree->root = NULL;
    tree->nodeCount = 0;
    tree->sizeOfType = sizeOfType;
    tree->cmp = cmp;
    return tree;
}

/** Creates a new Red Black TreeNode for a given key, and parent and if rrequired a certain color.
 * @param  parent Reference to the Red Black tree's root 's or insertion point's parent.
 * @param color color of the node to be created.
 * @param item Reference pointer to preallocated key.
 * @return Returns a pointer to an allocated node on the heap.
 * */
RBNode *createRBNode(RBNode *parent, COLOR color, void *item) {
    RBNode *node = (RBNode *) malloc(sizeof(RBNode));
    node->color = color;
    node->key = item;
    node->right = node->left = NULL;
    node->parent = parent;
    return node;
}

/** Given a node it frees it's Key and the node. Setting both to Null.
 * @param node Exact Reference for node to Free.
**/
void freeRBNode(RBNode **node){
    if(*node) return;
    free((*node)->key);
    (*node)->key = NULL;
    free(*node);
}

/** Given an Red Black Tree's root node it frees it's elements recursively.Setting the root node to Null.
 * @param node Exact Reference to root node to start freeing at.
**/
void RBTreeFree(RBNode** node){
    if (*node==NULL) return;
    RBTreeFree(&(*node)->left);
    RBTreeFree(&(*node)->right);
    freeRBNode(node);
 *  node=NULL;
}

/** Inserts a node at the a reference node (preferably the root) with the provided key.
 * @param  tree Reference to the Red Black tree.
 * @param item eference pointer to preallocated key.
**/
void rBTreeInsert(RBTree *tree, void *item) {
    tree->root = rBTreeInsertR(tree->root, NULL, item, tree->cmp);
    tree->root->color = BLACK;
}

/** Helper function to insert into the tree a node with given key item.
 * @param  root Reference to the Red Black tree's root or insertion point.
 * @param  parent Reference to the Red Black tree's root 's or insertion point's parent.
 * @param item Reference pointer to preallocated key.
 * @param cmp Reference to the comparator function. 
 * @return 
**/
RBNode *rBTreeInsertR(RBNode *root, RBNode *parent, void *item, int (*cmp)(const void*, const void *)) {
    if (root == NULL) {
        root = createRBNode(parent, parent == NULL ? BLACK : RED, item);
        //Case 1:
        if (isCaseOne(root)) {
            root->parent->color = BLACK;
            getUncle(root)->color = BLACK;
            root->parent->parent->color = RED;
        }
    }
    else if (cmp(root->key, item) > 0)
        root->left = rBTreeInsertR(root->left, root, item, cmp);
    else if (cmp(root->key, item) < 0)
        root->right = rBTreeInsertR(root->right, root, item, cmp);
    //Case 2:
    if (isRequiredRotation(root)) {
        RotationType rotationType = getRotationType(root);
        RBNode *newRoot = performRotation(root, rotationType);
        performRotationRecoloring(newRoot, rotationType);
        return newRoot;
    }
    return root;
}

/** if present Deletes a gien Node of key item from the tree.
 * @param  tree Reference to the Red Black tree.
 * @param item   Reference pointer to preallocated key.
**/
void rBTreeDelete(RBTree *tree, void *item) {
    rBTreeDeleteR(tree, tree->root, item);
}

/** Helper function to the @link rBTreeDelete @endlink function.
 * @param  tree Reference to the Red Black tree.
 * @param  root Reference to the Red Black tree's root or insertion point.
 * @param item Reference to key to delete from the tree.
**/
void rBTreeDeleteR(RBTree *tree, RBNode *root, void *item) {
    if (root == NULL)
        return;
    else if (tree->cmp(root->key, item) == 0) {
        if (root->right == NULL && root->left == NULL)
            deleteNodeLeafCase(tree, root);
        else if (root->right == NULL)
            deleteRightNullNode(tree, root);
        else if (root->left == NULL)
            deleteLeftNullNode(tree, root);
        else
            deleteRightNoneNullNode(tree, root);
    }
    else if (tree->cmp(root->key, item) > 0)
        rBTreeDeleteR(tree, root->left, item);
    else if (tree->cmp(root->key, item) < 0)
        rBTreeDeleteR(tree, root->right, item);
}

/** if the node to be deleted has no children this function handles it's deletion.
 * @param  tree Reference to the Red Black tree.
 * @param  root Reference to the Red Black tree's root or insertion point.
**/
void deleteNodeLeafCase(RBTree *tree, RBNode *root) {
    COLOR rootColor = root->color;
    RBNode *parent = root->parent;
    free(root->key);
    free(root);
    if (parent == NULL)
        tree->root = NULL;
    else {
        if (parent->right == root)
            parent->right = NULL;
        else
            parent->left = NULL;
    }
    if (rootColor != RED)
        doubleBlackCase(tree, NULL, parent);
}

/** If the node has no right child this function handles it's deletion.
 * @param  tree Reference to the Red Black tree.
 * @param  root Reference to the Red Black tree's root or insertion point.
**/
void deleteRightNullNode(RBTree *tree, RBNode *root) {
    RBNode *returnNode = root->left;
    RBNode *parent = root->parent;
    returnNode->parent = parent;
    COLOR rootColor = root->color;
    if (parent == NULL)
        tree->root = NULL;
    else {
        if (parent->right == root)
            parent->right = returnNode;
        else
            parent->left = returnNode;
    }
    free(root->key);
    free(root);
    //This case mean the current node is black and it's child is red colored.
    if (returnNode->color == RED && rootColor == BLACK)
        returnNode->color = BLACK;
        //This case mean the deleted node is black and the replaced node is also black.
    else if (returnNode->color == BLACK && rootColor == BLACK)
        doubleBlackCase(tree, returnNode, returnNode->parent);
}

/** If the node has no left child this function handles it's deletion.
 * @param  tree Reference to the Red Black tree.
 * @param  root Reference to the Red Black tree's root or insertion point.
**/
void deleteLeftNullNode(RBTree *tree, RBNode *root) {
    RBNode *returnNode = root->right;
    RBNode *parent = root->parent;
    returnNode->parent = parent;
    COLOR rootColor = root->color;
    if (parent == NULL)
        tree->root = NULL;
    else {
        if (parent->right == root)
            parent->right = returnNode;
        else
            parent->left = returnNode;
    }
    free(root->key);
    free(root);
    //This case mean the current node is black and it's child is red colored.
    if (returnNode->color == RED && rootColor == BLACK)
        returnNode->color = BLACK;
        //This case mean the deleted node is black and the replaced node is also black.
    else if (returnNode->color == BLACK && rootColor == BLACK)
        doubleBlackCase(tree, returnNode, returnNode->parent);
}

/** If the node has both a right and a left child this function handles it's deletion.
 * @param  tree Reference to the Red Black tree.
 * @param  root Reference to the Red Black tree's root or insertion point.
**/
void deleteRightNoneNullNode(RBTree *tree, RBNode *root) {
    RBNode *successorNode = getSuccessorNode(root);
    void *temp = root->key;
    root->key = successorNode->key;
    successorNode->key = temp;
    rBTreeDeleteR(tree, root->right, successorNode->key);
}

/** Handles cases where a double black node is caused by deletion.
 * @param  tree Reference to the Red Black tree.
 * @param  root Reference to the Red Black tree's root or insertion point.
 * @param  parent Reference to the Red Black tree's root 's or insertion point's parent.
**/
void doubleBlackCase(RBTree *tree, RBNode *root, RBNode *parent) {
    if (parent == NULL)
        return;
    RBNode *sibling = parent->right == root ? parent->left : parent->right;
    if (sibling->color == BLACK && (getNodeColor(sibling->right) == RED || getNodeColor(sibling->left) == RED)) {
        RBNode *sRedChild = getNodeColor(sibling->right) == RED ? sibling->right : sibling->left;
        RotationType rotationType = doubleBlackCaseRotationType(sibling->parent, sibling, sRedChild);
        sRedChild->color = parent->color;
        parent->color = BLACK;
        doubleBlackCasePerformRotation(tree, parent, rotationType);
    } else if (sibling->color == RED) {
        RotationType rotationType = parent->right == sibling ? LEFT : RIGHT;
        parent->color = RED;
        sibling->color = BLACK;
        doubleBlackCasePerformRotation(tree, parent, rotationType);
    } else if (sibling->color == BLACK) {
        sibling->color = RED;
        if (parent->color == BLACK)
            doubleBlackCase(tree, parent, parent->parent);
        else
            parent->color = BLACK;
    }
}

/** Handles the rotation for cases where a double black node is caused by deletion.
 * @param  tree Reference to the Red Black tree.
 * @param  parent Reference to the Red Black tree's root 's or insertion point's parent.
 * @param rotationType Type of rotation to perform.
**/
void doubleBlackCasePerformRotation(RBTree *tree, RBNode *parent, RotationType rotationType) {
    RBNode *grandParent = parent->parent;
    if (grandParent == NULL) {
        tree->root = performRotation(parent, rotationType);
    } else if (grandParent->right == parent) {
        grandParent->right = performRotation(parent, rotationType);
    } else if (grandParent->left == parent) {
        grandParent->left = performRotation(parent, rotationType);
    }
}

/** Gets the rotation type to fix the double black case.
 * @param  grandParent Reference to the Red Black tree's root 's or point's grandparent.
 * @param  parent Reference to the Red Black tree's root 's or insertion point's parent.
 * @param grandSon Reference to the grandson relative to the grandparent . 
 * @return Returns Rotation type of values from the @link RotationType @endlink enum.
**/
RotationType doubleBlackCaseRotationType(RBNode *grandParent, RBNode *parent, RBNode *grandSon) {
    if (grandParent->left == parent && parent->left == grandSon) {
        return RIGHT;
    } else if (grandParent->right == parent && parent->right == grandSon) {
        return LEFT;
    } else if (grandParent->left == parent && parent->right == grandSon) {
        return LEFT_RIGHT;
    } else if (grandParent->right == parent && parent->left == grandSon) {
        return RIGHT_LEFT;
    } else {
        return NONE;
    }
}

/** Given a reference node it returns a reference to it's successor.
 * @param node Reference node to get the in-order successor for.
 * @return  Pointer to the inorder successor for that node.
**/
RBNode *getSuccessorNode(RBNode *node) {
    RBNode *currentNode = node->right;
    if (currentNode == NULL)
        return node;
    while (currentNode->left != NULL)
        currentNode = currentNode->left;
    return currentNode;
}

/** if a node is red and it's parent and uncle and red, the function returns 1 ie true else 0, false.
 * @param  root Reference to the Red Black tree's root or insertion point.
 * @return 1 is the current node matches the description else 0.
**/
int isCaseOne(RBNode *root) {
    return root->color == RED
           && getNodeColor(root->parent) == RED
           && root->parent->parent != NULL
           && getNodeColor(getUncle(root)) == RED;
}

/* If the parent and the uncle aren't of the same color (ie one of them is red) whose children
 * are also red then a rotation is also required.
 * @param  grandParent Reference to the Red Black tree's root 's or point's grandparent.
 * @return 
**/
int isRequiredRotation(RBNode *grandParent) {
    if (getNodeColor(grandParent->right) != getNodeColor(grandParent->left)) {
        RBNode *redNode = getNodeColor(grandParent->right) == RED ? grandParent->right : grandParent->left;
        if (getNodeColor(redNode->right) == RED || getNodeColor(redNode->left) == RED)
            return 1;
        else
            return 0;
    } else
        return 0;
}

/** Given a reference to a grandparent node determine what rotation to perform.
 * @param  grandParent Reference to the Red Black tree's root 's or point's grandparent.
 * @return Rotation to perform of values from the @link RotationType enum.
**/
RotationType getRotationType(RBNode *grandParent) {
    RBNode *redChild = getNodeColor(grandParent->right) == RED ? grandParent->right : grandParent->left;
    RBNode *redGrandSon = getNodeColor(redChild->right) == RED ? redChild->right : redChild->left;
    if (grandParent->right == redChild && redChild->right == redGrandSon)
        return LEFT;
    else if (grandParent->left == redChild && redChild->left == redGrandSon)
        return RIGHT;
    else if (grandParent->left == redChild && redChild->right == redGrandSon)
        return LEFT_RIGHT;
    else if (grandParent->right == redChild && redChild->left == redGrandSon)
        return RIGHT_LEFT;
    else
        return NONE;
}

/** Given a rotaion type and a node to rotate about,the subtree of the node is rotated with respect tot he rotation type.
 * @param node Reference to the Red Black tree's root or reference node to rotated at.
 * @param rotationType Type of rotation to perform.
 * @return Returns the newly rotated subtree
**/
RBNode *performRotation(RBNode *node, RotationType rotationType) {
    RBNode *newRoot;
    switch (rotationType) {
        case LEFT:
            newRoot = leftRotation(node);
            return newRoot;
        case RIGHT:
            newRoot = rightRotation(node);
            return newRoot;
        case LEFT_RIGHT:
            node->left = leftRotation(node->left);
            newRoot = rightRotation(node);
            return newRoot;
        case RIGHT_LEFT:
            node->right = rightRotation(node->right);
            newRoot = leftRotation(node);
            return newRoot;
        case NONE:
            return node;
    }
}

/** Recolours nodes after rotation to maintain the reb black tree property.
 * @param  root Reference to the Red Black tree's root or insertion point.
 * @param rotationType Type of rotation to perform.
**/
void performRotationRecoloring(RBNode *root, RotationType rotationType) {
    switch (rotationType) {
        case LEFT:
            root->color = BLACK;
            root->left->color = RED;
            break;
        case RIGHT:
            root->color = BLACK;
            root->right->color = RED;
            break;
        case LEFT_RIGHT:
            root->color = BLACK;
            root->right->color = RED;
            break;
        case RIGHT_LEFT:
            root->color = BLACK;
            root->left->color = RED;
            break;
    }
}

/** Given a grandparent node it performs left rotation at it.
 * @param  grandParent Reference to the Red Black tree's root 's or point's grandparent.
 * @return  returns pointer to the newly left rotated subtree.
**/
RBNode *leftRotation(RBNode *grandParent) {
    RBNode *newGrandParent = grandParent->right;
    grandParent->right = newGrandParent->left;
    newGrandParent->left = grandParent;
    newGrandParent->parent = grandParent->parent;
    grandParent->parent = newGrandParent;
    if (grandParent->right != NULL)
        grandParent->right->parent = grandParent;
    return newGrandParent;
}

/** Given a grandparent node it performs right rotation at it.
 * @param  grandParent Reference to the Red Black tree's root 's or point's grandparent.
 * @return returns pointer to the newly right rotated subtree.
**/
RBNode *rightRotation(RBNode *grandParent) {
    RBNode *newGrandParent = grandParent->left;
    grandParent->left = newGrandParent->right;
    newGrandParent->right = grandParent;
    newGrandParent->parent = grandParent->parent;
    grandParent->parent = newGrandParent;
    if (grandParent->left != NULL)
        grandParent->left->parent = grandParent;
    return newGrandParent;
}

/** Proved with a node it gets it's returns a pointer to it's uncle.
 * @param currentNode Reference node to get the uncle at.
 * @return Pointer to the uncle of the given node.
**/
RBNode *getUncle(RBNode *currentNode) {
    RBNode *parent = currentNode->parent;
    RBNode *grandParent = parent->parent;
    return grandParent->right == parent ? grandParent->left : grandParent->right;
}

/** Returns the Node's Color, if the node is null it is considered black else returns the actual node's color.
 * @param node Node to get the color at
 * @return Color information about the given node.
**/
COLOR getNodeColor(RBNode *node) {
    return node == NULL ? BLACK : node->color;
}

/** Prints the Tree inOrder traversing it recursively.
 * @param  tree Reference to the Red Black tree.
 * @param printFun Pointer to the print function.
**/
void rBPreOrderTraversal(RBTree *tree, void (*printFun)(const void *item, COLOR color)) {
    rBPreOrderTraversalR(tree->root, printFun);
}

/** Helper function for @link rBPreOrderTraversal @endlink printing tree traversing it in order. Sends a pointer ot the node directly.
 * @param  root Reference to the Red Black tree's root or insertion point.Reference to the root node.
 * @param printFun Pointer to the print function.
**/
void rBPreOrderTraversalR(RBNode *root, void (*printFun)(const void *item, COLOR color)) {
    if (root == NULL)
        return;
    printFun(root, root->color);
    rBPreOrderTraversalR(root->left, printFun);
    rBPreOrderTraversalR(root->right, printFun);
}

/** Helper function for @link RBTreePrint @endlink for printing the tree recursively visiting every node.
 * @param  root Reference to the Red Black tree's root or insertion point.
 * @param space Offset form position 0 of the line yo where the node charater should end.
 * @param printFn Pointer to the print function.
**/
 void printRBTreeHelper(RBNode *root, int space, void (printFn)(void *,int type));

/** Prints a tree in 2 space of the console.
 * @param root Reference to the root node.
 * @param printFn Pointer to the print function.
**/
void RBTreePrint(RBNode *root, void (printFn)(void *,int type)){
    printRBTreeHelper(root, 0, printFn);
}

/** Helper function for printing the tree in 2d space.
 * @param root Reference to the root node.
 * @param space Number of spaces to print at the current level.
 * @param printFn Pointer to the print function.
**/
void printRBTreeHelper(RBNode *root, int space, void (printFn)(void *,int type)){
    if (root == NULL){
        return;
    }
    space += 10;
    printRBTreeHelper(root->right, space, printFn);
    printf("\n");
    for (int i = 10; i < space; i++) printf(" ");
    (printFn)(root->key,root->color);
    printRBTreeHelper(root->left, space, printFn);
}

/** Given a tree and a reference node to start searching at (preferably the root) searches for node with the same key and return it.
 * @param rbTree Reference to the Red Black tree.
 * @param node node to start searching from preferably the root.
 * @param key Key object to search for in the  Red Black tree.
 * @return Returns the Found node.
**/
RBNode *RBTreeSearch(RBTree *rbTree, RBNode *node, char *key){
    if(!node) return NULL;
    if (((rbTree->cmp)(key,node->key)==0))return node;
    if ((rbTree->cmp)(key,node->key)<0) return RBTreeSearch(rbTree, node->left, key);
    if ((rbTree->cmp)(key,node->key)>0) return RBTreeSearch(rbTree, node->right, key);
}

/** Adds an array of void pointers to elements of the same type as the nodes of the tree.
 * @param rbTree Reference to the red black tree.
 * @param array Array to add data from.
 * @param length The Length of the array to add from.
 * @return Returns the new root node.
**/
RBNode * RBInsertAll(RBTree* rbTree, void** array, int length){
    for(int i=0;i<length;i++){
        rBTreeInsert(rbTree, array[i]);
    }
    return rbTree->root;
}

/** Given a Tree converts it to an array in-order
 * @param rbTree Reference to the Red Black tree.
 * @return returns an array of pointer references to keys that were stored in the tree.
**/
void **RBTreeToArray(RBTree *rbTree){
    void **array = (void **) malloc(sizeof(void *) * rbTree->nodeCount);
    int i = 0;
    RBTreeToArrayRecurs(rbTree->root, array, &i,rbTree->sizeOfType);
    return array;
}

/** Recursively traverses the tree in order and adds elements to an allocated array by @link RBTreeToArray @endlink .
 * @param node Node reference node to start converting from.
 * @param arr Preallocated array to start storing at.
 * @param i index to insert at in the array.
**/
void RBTreeToArrayRecurs(RBNode* node , void **arr, int *i , int size){
    if(!node) return;
    RBTreeToArrayRecurs(node->left, arr, i,size);
    arr[*i] = (void *) malloc(size);
    memcpy(arr[*i], node->key, size);
 *  i += 1;
    RBTreeToArrayRecurs(node->right, arr, i,size);
}

/** Reference to the root node to start calculating the size of tree.
 * @param root Reference to the root node.
 * @return the number of nodes in the tree.
**/
int RBGetSize(RBNode* root){
    if (root) return 1 + RBGetSize(root->left) + RBGetSize(root->right);
    else return 0;
}

/** Given a key, and a tree to search in determines whether a key is present in the tree or not.
 * @param rbTree Reference to the Red Black tree.
 * @param searchKey key to search for in the tree.
 * @return returns int as bool. Returns 1 if is found else returns 0.
**/
int RBIsPresent(RBTree *rbTree, void* searchKey){
    int found = 0;
    RBIsPresentRecurs(rbTree, rbTree->root, searchKey, &found);
    return found;
}

/** Helper Function to @link RBIsPresent @endlink that recursively checks if a node is present in the tree.
 * @param rbTree Reference to the Red Black tree.
 * @param root Reference to the root node.
 * @param searchValue Value to search for.
 * @param found Int to act as boolean. If found it is 1 else set to 0.
**/
void RBIsPresentRecurs(RBTree *rbTree, RBNode *root, void *searchValue, int* found ){
    if (root) {
        if ((rbTree->cmp)(root->key, searchValue) == 0)
 *  found = 1;
        else {
            RBIsPresentRecurs(rbTree, root->left, searchValue, found);
            if (!(*found))
                RBIsPresentRecurs(rbTree, root->right, searchValue, found);
        }
    }
}
