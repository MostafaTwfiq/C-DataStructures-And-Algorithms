#include "../Headers/RedBlackTree.h"


typedef enum RotationType{
    NONE, RIGHT, LEFT, RIGHT_LEFT, LEFT_RIGHT
} RotationType;

RBNode *rBTreeInsertR(RBNode *root, RBNode *parent, void *item, int (*cmp)(const void*, const void *));
RBNode *rBTreeDeleteR(RBNode *root, void *item, int sizeOfType, int (*cmp)(const void*, const void *));
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
void doubleBlackCase(RBNode *root, RBNode *parent);
RBNode *deleteNodeLeafCase(RBNode *root, int sizeOfType, int (*cmp)(const void*, const void *));
RBNode *deleteRightNullNode(RBNode *root, int sizeOfType, int (*cmp)(const void*, const void *));
RBNode *deleteRightNoneNullNode(RBNode *root, int sizeOfType, int (*cmp)(const void*, const void *));



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
    tree->root = rBTreeDeleteR(tree->root, item, tree->sizeOfType, tree->cmp);
    if (tree->root != NULL)
        tree->root->color = BLACK;

}

RBNode *rBTreeDeleteR(RBNode *root, void *item, int sizeOfType, int (*cmp)(const void*, const void *)) {
    if (root == NULL)
        return root;
    else if (cmp(root->key, item) == 0) {
        if (root->right == NULL && root->left == NULL) {
            return deleteNodeLeafCase(root,  sizeOfType, cmp);
        } else if (root->right == NULL) {
            return deleteRightNullNode(root, sizeOfType, cmp);
        } else {
            return deleteRightNoneNullNode(root,  sizeOfType, cmp);
        }

    } else if (cmp(root->key, item) > 0) {
        root->left = rBTreeDeleteR(root->left, item, sizeOfType, cmp);
    } else if (cmp(root->key, item) < 0) {
        root->right = rBTreeDeleteR(root->right, item, sizeOfType, cmp);
    }

    if (isRequiredRotation(root)) {
        RotationType rotationType = getRotationType(root);
        RBNode *newRoot = performRotation(root, rotationType);
        performRotationRecoloring(newRoot, rotationType);
        return newRoot;
    }

    return root;

}

RBNode *deleteNodeLeafCase(RBNode *root, int sizeOfType, int (*cmp)(const void*, const void *)) {
    COLOR rootColor = root->color;
    RBNode *parent = root->parent;
    free(root->key);
    free(root);
    if (rootColor == RED || root->parent == NULL) // parent = NULL mean it's the tree root node.
        return NULL;
    else {
        doubleBlackCase(NULL, parent);
    }

    return NULL;
}

RBNode *deleteRightNullNode(RBNode *root, int sizeOfType, int (*cmp)(const void*, const void *)) {
    COLOR rootColor = root->color;
    RBNode *returnNode = root->left;
    returnNode->parent = root->parent;
    free(root->key);
    free(root);

    if (root == RED)
        return returnNode;
    else if (returnNode->color == RED) {
        returnNode->color = BLACK;
        return returnNode;
    }
    else {
        doubleBlackCase(returnNode, returnNode->parent);
    }

    return returnNode;

}

RBNode *deleteRightNoneNullNode(RBNode *root, int sizeOfType, int (*cmp)(const void*, const void *)) {
    COLOR rootColor = root->color;
    RBNode *successorNode = getSuccessorNode(root);
    COLOR successorNodeColor = successorNode->color;
    void *itemCopy = (void *) malloc(sizeOfType);
    memcpy(itemCopy, successorNode->key, sizeOfType);
    free(root->key);
    root->key = itemCopy;
    root->right = rBTreeDeleteR(root->right, successorNode->key, sizeOfType, cmp);

    if (root == RED) {
        root->color = successorNodeColor;
        return root;
    }
    else if (successorNodeColor == RED) {
        root->color = BLACK;
        return root;
    }
    else {
        doubleBlackCase(root, root->parent);
    }

    return root;

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

void doubleBlackCase(RBNode *root, RBNode *parent) {
    if (parent == NULL)
        return;

    RBNode *sibling = parent->right == root ? parent->left : parent->right;
    if (sibling->color == BLACK && (getNodeColor(sibling->right) == RED || getNodeColor(sibling->left) == RED)) {
        RBNode *sRedChild = getNodeColor(sibling->right) == RED ? sibling->right : sibling->left;
        RotationType rotationType = doubleBlackCaseRotationType(sibling->parent, sibling, sRedChild);
        performRotation(sibling->parent, rotationType);
        return;
    } else if (sibling->color == BLACK && parent->color == RED){
            sibling->color = RED;
            parent->color = RED;
            return;
    } else if (sibling->color == BLACK && parent->color == BLACK){
        doubleBlackCase(parent, parent->parent);
    } else if (sibling->color == RED) {
        RotationType rotationType = doubleBlackCaseRotationType(sibling->parent, sibling, sibling->right != NULL ? sibling->right : sibling->left);
        RBNode *newRoot = performRotation(sibling->parent, rotationType);
        performRotationRecoloring(newRoot, rotationType);
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

    printFun(root->key, root->color);
    rBPreOrderTraversalR(root->left, printFun);
    rBPreOrderTraversalR(root->right, printFun);

}