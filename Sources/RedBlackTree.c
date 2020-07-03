#include "../Headers/RedBlackTree.h"


typedef enum RotationType{
    NONE, RIGHT, LEFT, RIGHT_LEFT, LEFT_RIGHT
} RotationType;

RBNode *rBTreeInsertR(RBNode *root, RBNode *parent, void *item, int (*cmp)(const void*, const void *));
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
void RBTreeToArrayRecurs(RBNode* node , void **arr, int *i , int size);


RBTree *redBlackTreeInitialization(int sizeOfType, int (*cmp)(const void*, const void *)) {
    RBTree *tree = (RBTree *) malloc(sizeof(RBTree));
    tree->root = NULL;
    tree->nodeCount = 0;
    tree->sizeOfType = sizeOfType;
    tree->cmp = cmp;

    return tree;

}

RBNode *createRBNode(RBNode *parent, COLOR color, void *item) {
    RBNode *node = (RBNode *) malloc(sizeof(RBNode));
    node->color = color;
    node->key = item;
    node->right = node->left = NULL;
    node->parent = parent;

    return node;
}

void rBTreeInsert(RBTree *tree, void *item) {
    tree->root = rBTreeInsertR(tree->root, NULL, item, tree->cmp);
    tree->root->color = BLACK;
}

RBNode *rBTreeInsertR(RBNode *root, RBNode *parent, void *item, int (*cmp)(const void*, const void *)) {
    if (root == NULL) {
        root = createRBNode(parent, parent == NULL ? BLACK : RED, item);

        //Case 1:
        if (isCaseOne(root)) {
            root->parent->color = BLACK;
            getUncle(root)->color = BLACK;
            root->parent->parent->color = RED;
        }

    } else if (cmp(root->key, item) > 0) {
        root->left = rBTreeInsertR(root->left, root, item, cmp);
    } else if (cmp(root->key, item) < 0) {
        root->right = rBTreeInsertR(root->right, root, item, cmp);
    }

    //Case 2:
    if (isRequiredRotation(root)) {
        RotationType rotationType = getRotationType(root);
        RBNode *newRoot = performRotation(root, rotationType);
        performRotationRecoloring(newRoot, rotationType);
        return newRoot;
    }

    return root;

}


void rBTreeDelete(RBTree *tree, void *item) {
    rBTreeDeleteR(tree, tree->root, item);
    if (tree->root != NULL) {
        tree->root->color = BLACK;
        tree->root->parent = NULL;
    }

}

void rBTreeDeleteR(RBTree *tree, RBNode *root, void *item) {
    if (root == NULL)
        return;
    else if (tree->cmp(root->key, item) == 0) {
        if (root->right == NULL && root->left == NULL) {
            deleteNodeLeafCase(tree, root);
        } else if (root->right == NULL) {
            deleteRightNullNode(tree, root);
        } else if (root->left == NULL) {
            deleteLeftNullNode(tree, root);
        }else {
            deleteRightNoneNullNode(tree, root);
        }

    } else if (tree->cmp(root->key, item) > 0) {
        rBTreeDeleteR(tree, root->left, item);
    } else if (tree->cmp(root->key, item) < 0) {
        rBTreeDeleteR(tree, root->right, item);
    }

    /*else if (isRequiredRotation(root)) {
        RotationType rotationType = getRotationType(root);
        RBNode *parent = root->parent;
        RBNode *newRoot = performRotation(root, rotationType);
        performRotationRecoloring(newRoot, rotationType);
        if (parent == NULL)
            tree->root = newRoot;
        else if (parent->right == parent) {
            parent->right = newRoot;
        } else if (parent->left == parent) {
            parent->left = newRoot;
        }
    }*/

}

void deleteNodeLeafCase(RBTree *tree, RBNode *root) {
    COLOR rootColor = root->color;
    RBNode *parent = root->parent;
    if (parent != NULL) {
        if (parent->right == root) {
            parent->right = NULL;
        } else {
            parent->left = NULL;
        }
    } else {
        tree->root = NULL;
    }

    if (rootColor != RED) {
        doubleBlackCase(tree, NULL, parent);
    }

    free(root->key);
    free(root);

}

void deleteRightNullNode(RBTree *tree, RBNode *root) {
    RBNode *returnNode = root->left;
    RBNode *parent = root->parent;
    returnNode->parent = parent;
    COLOR rootColor = root->color;

    if (parent != NULL) {
        if (parent->right == root) {
            parent->right = returnNode;
        } else {
            parent->left = returnNode;
        }
    } else {
        tree->root = NULL;
    }

    free(root->key);
    free(root);

    if (rootColor == RED)
        return;
    else if (returnNode->color == RED) { //This case mean the current node is black and it's child is red colored.
        returnNode->color = BLACK;
        return;
    }
    else {
        doubleBlackCase(tree, returnNode, returnNode->parent);
    }

}

void deleteLeftNullNode(RBTree *tree, RBNode *root) {
    RBNode *returnNode = root->right;
    RBNode *parent = root->parent;
    returnNode->parent = parent;
    COLOR rootColor = root->color;

    if (parent != NULL) {
        if (parent->right == root) {
            parent->right = returnNode;
        } else {
            parent->left = returnNode;
        }
    }

    free(root->key);
    free(root);

    if (rootColor == RED)
        return;
    else if (returnNode->color == RED) { //This case mean the current node is black and it's child is red colored.
        returnNode->color = BLACK;
        return;
    }
    else {
        doubleBlackCase(tree, returnNode, returnNode->parent);
    }

}

void deleteRightNoneNullNode(RBTree *tree, RBNode *root) {
    RBNode *successorNode = getSuccessorNode(root);
    void *temp = root->key;
    root->key = successorNode->key;
    successorNode->key = temp;
    /*COLOR successorNodeColor = successorNode->color;
    void *itemCopy = (void *) malloc(tree->sizeOfType);
    memcpy(itemCopy, successorNode->key, tree->sizeOfType);
    free(root->key);
    root->key = itemCopy;*/
    rBTreeDeleteR(tree, root->right, successorNode->key);

    /*if (root == RED) {
        root->color = successorNodeColor;
        return;
    }
    else if (successorNodeColor == RED) { //This case mean the current node is black and it's child is red colored.
        root->color = BLACK;
        return;
    }
    else {
        doubleBlackCase(tree, root, root->parent);
    }*/

}

void doubleBlackCase(RBTree *tree, RBNode *root, RBNode *parent) {
    if (parent == NULL)
        return;

    RBNode *sibling = parent->right == root ? parent->left : parent->right;
    if (sibling->color == BLACK && (getNodeColor(sibling->right) == RED || getNodeColor(sibling->left) == RED)) {
        RBNode *sRedChild = getNodeColor(sibling->right) == RED ? sibling->right : sibling->left;
        RotationType rotationType = doubleBlackCaseRotationType(sibling->parent, sibling, sRedChild);
        RBNode *grandParent = parent->parent;
        sRedChild->color = parent->color;
        parent->color = BLACK;
        if (grandParent == NULL) {
            tree->root = performRotation(sibling->parent, rotationType);
        } else if (grandParent->right == parent) {
            grandParent->right = performRotation(sibling->parent, rotationType);
        } else if (grandParent->left == parent) {
            grandParent->left = performRotation(sibling->parent, rotationType);
        }
        return;
    } else if (sibling->color == BLACK && parent->color == RED){
        sibling->color = RED;
        parent->color = BLACK;
        return;
    } else if (sibling->color == BLACK && parent->color == BLACK){
        sibling->color = RED;
        doubleBlackCase(tree, parent, parent->parent);
    } else if (sibling->color == RED) {
        //RotationType rotationType = doubleBlackCaseRotationType(sibling->parent, sibling, sibling->right != NULL ? sibling->right : sibling->left);
        RotationType rotationType = parent->right == sibling ? LEFT : RIGHT;
        parent->color = RED;
        sibling->color = BLACK;
        RBNode *grandParent = parent->parent;
        if (grandParent == NULL) {
            tree->root = performRotation(sibling->parent, rotationType);
        } else if (grandParent->right == parent) {
            grandParent->right = performRotation(sibling->parent, rotationType);
        } else if (grandParent->left == parent) {
            grandParent->left = performRotation(sibling->parent, rotationType);
        }
        return;
    }

}

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

RBNode *getSuccessorNode(RBNode *node) {
    RBNode *currentNode = node->right;
    if (currentNode == NULL)
        return node;

    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;

}

int isCaseOne(RBNode *root) {
    return root->color == RED
           && getNodeColor(root->parent) == RED
           && root->parent->parent != NULL
           && getNodeColor(getUncle(root)) == RED;

}

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


RBNode *getUncle(RBNode *currentNode) {
    RBNode *parent = currentNode->parent;
    RBNode *grandParent = parent->parent;
    return grandParent->right == parent ? grandParent->left : grandParent->right;
}

COLOR getNodeColor(RBNode *node) {
    return node == NULL ? BLACK : node->color;
}

void rBPreOrderTraversal(RBTree *tree, void (*printFun)(const void *item, COLOR color)) {
    rBPreOrderTraversalR(tree->root, printFun);
}

void rBPreOrderTraversalR(RBNode *root, void (*printFun)(const void *item, COLOR color)) {
    if (root == NULL)
        return;

    printFun(root, root->color);
    rBPreOrderTraversalR(root->left, printFun);
    rBPreOrderTraversalR(root->right, printFun);

}


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
    if ((rbTree->cmp)(key,node->key)<0) return BinaryTreeSearch(rbTree, node->left, key);
    if ((rbTree->cmp)(key,node->key)>0) return BinaryTreeSearch(rbTree, node->right, key);
}


/** Adds an array of void pointers to elements of the same type as the nodes of the tree.
* @param rbTree Reference to the Binary tree.
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
    *i += 1;
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

