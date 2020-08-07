#include "../Headers/BinaryTree.h"
#include "../../../System/Utils.h"




BinaryTreeNode *binaryTreeInsertR(BinaryTree *tree, BinaryTreeNode *root, void *item);

BinaryTreeNode *binaryTreeDeleteR(BinaryTree *tree, BinaryTreeNode *root, void *item);

void binaryTreePreOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *));

void binaryTreeInOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *));

void binaryTreePostOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *));

void clearBinaryTreeR(BinaryTree *tree, BinaryTreeNode *root);

void binaryTreeToArrayR(BinaryTreeNode *root, void **arr, int *index);



BinaryTreeNode *createBinaryTreeNode(void *item) {

    BinaryTreeNode *newNode = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "binary tree data structure");
        exit(FAILED_ALLOCATION);
    }

    newNode->key = item;
    newNode->right = NULL;
    newNode->left= NULL;

}




void destroyBinaryTreeNode(BinaryTreeNode *node, void (*freeFun)(void *)) {

    freeFun(node->key);
    node->right = NULL;
    node->left = NULL;
    free(node);

}



void destroyBinaryTreeNodeWtoFr(BinaryTreeNode *node) {

    node->right = NULL;
    node->left = NULL;
    free(node);

}



BinaryTreeNode *getRightSuccessorBT(BinaryTreeNode *node) {

    BinaryTreeNode *currentNode = node->right;

    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;

}



BinaryTree *binaryTreeInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *)) {


    if (freeFun == NULL) {

    } else if (cmp == NULL) {

    }

    BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree));

    tree->root = NULL;
    tree->count = 0;
    tree->freeFn = freeFun;
    tree->cmp = cmp;

}




void binaryTreeInsert(BinaryTree *tree, void *item) {

    if (tree == NULL) {

    } else if (item == NULL) {

    }

    tree->root = binaryTreeInsertR(tree, tree->root, item);

}



BinaryTreeNode *binaryTreeInsertR(BinaryTree *tree, BinaryTreeNode *root, void *item) {

    if (root == NULL) {
        tree->count++;
        root = createBinaryTreeNode(item);
    }

    else if ( tree->cmp(item, root->key) > 0 )
        root->right = binaryTreeInsertR(tree, root->right, item);
    else if ( tree->cmp(item, root->key) < 0 )
        root->left = binaryTreeInsertR(tree, root->left, item);
    else
        tree->freeFn(item);

    return root;

}





void binaryTreeInsertAll(BinaryTree *tree, void **items, int length) {

    if (tree == NULL) {

    } else if (items == NULL) {

    }

    for (int i = 0; i < length; i++)
        binaryTreeInsert(tree, items[i]);

}






void binaryTreeDelete(BinaryTree *tree, void *item) {

    if (tree == NULL) {

    } else if (item == NULL) {

    }

    tree->root = binaryTreeDeleteR(tree, tree->root, item);

}



BinaryTreeNode *binaryTreeDeleteR(BinaryTree *tree, BinaryTreeNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if ( tree->cmp(item, root->key) == 0 ) {

        if (root->right == NULL && root->left == NULL) {
            destroyBinaryTreeNode(root, tree->freeFn);
            root = NULL;
        } else if (root->right != NULL && root->left != NULL) {
            BinaryTreeNode *rightSuccessor = getRightSuccessorBT(root);
            void *tempValue = root->key;
            root->key = rightSuccessor->key;
            rightSuccessor->key = tempValue;
            root->right = binaryTreeDeleteR(tree, root->right, rightSuccessor->key);
        } else {
            BinaryTreeNode *newRoot = root->right != NULL ? root->right : root->left;
            destroyBinaryTreeNode(root, tree->freeFn);
            root = newRoot;
        }

        tree->count--;

    }

    else if ( tree->cmp(item, root->key) > 0 )
        root->right = binaryTreeDeleteR(tree, root->right, item);
    else
        root->left = binaryTreeDeleteR(tree, root->left, item);

    return root;

}




void binaryTreeDeleteWtoFr(BinaryTree *tree, void *item) {

    if (tree == NULL) {

    } else if (item == NULL) {

    }

    tree->root = binaryTreeDeleteR(tree, tree->root, item);

}



BinaryTreeNode *binaryTreeDeleteWtoFrR(BinaryTree *tree, BinaryTreeNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if ( tree->cmp(item, root->key) == 0 ) {

        if (root->right == NULL && root->left == NULL) {
            destroyBinaryTreeNodeWtoFr(root);
            root = NULL;
        } else if (root->right != NULL && root->left != NULL) {
            BinaryTreeNode *rightSuccessor = getRightSuccessorBT(root);
            void *tempValue = root->key;
            root->key = rightSuccessor->key;
            rightSuccessor->key = tempValue;
            root->right = binaryTreeDeleteR(tree, root->right, rightSuccessor->key);
        } else {
            BinaryTreeNode *newRoot = root->right != NULL ? root->right : root->left;
            destroyBinaryTreeNodeWtoFr(root);
            root = newRoot;
        }

        tree->count--;

    }

    else if ( tree->cmp(item, root->key) > 0 )
        root->right = binaryTreeDeleteR(tree, root->right, item);
    else
        root->left = binaryTreeDeleteR(tree, root->left, item);

    return root;

}





int binaryTreeContains(BinaryTree *tree, void *item) {


    BinaryTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if ( tree->cmp(item, currentNode->key) == 0 )
            break;
        else if ( tree->cmp(item, currentNode->key) > 0 )
            currentNode = currentNode->right;
        else
            currentNode = currentNode->left;

    }

    return currentNode == NULL ? 0 : 1 ;

}



void *binaryTreeGet(BinaryTree *tree, void *item) {


    BinaryTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if ( tree->cmp(item, currentNode->key) == 0 )
            break;
        else if ( tree->cmp(item, currentNode->key) > 0 )
            currentNode = currentNode->right;
        else
            currentNode = currentNode->left;

    }

    return currentNode == NULL ? NULL : currentNode->key ;

}





void binaryTreePreOrderTraversal(BinaryTree *tree, void (*printFun)(void *)) {

    if (tree = NULL) {

    } else if (printFun == NULL) {

    }

    binaryTreePreOrderTraversalR(tree->root, printFun);

}


void binaryTreePreOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    printFun(root->key);
    binaryTreePreOrderTraversalR(root->left, printFun);
    binaryTreePreOrderTraversalR(root->right, printFun);

}




void binaryTreeInOrderTraversal(BinaryTree *tree, void (*printFun)(void *)) {

    if (tree = NULL) {

    } else if (printFun == NULL) {

    }

    binaryTreeInOrderTraversalR(tree->root, printFun);

}


void binaryTreeInOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    binaryTreeInOrderTraversalR(root->left, printFun);
    printFun(root->key);
    binaryTreeInOrderTraversalR(root->right, printFun);

}



void binaryTreePostOrderTraversal(BinaryTree *tree, void (*printFun)(void *)) {

    if (tree = NULL) {

    } else if (printFun == NULL) {

    }

    binaryTreePostOrderTraversalR(tree->root, printFun);

}


void binaryTreePostOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    binaryTreePostOrderTraversalR(root->left, printFun);
    binaryTreePostOrderTraversalR(root->right, printFun);
    printFun(root->key);

}



int binaryTreeGetSize(BinaryTree *tree) {

    return tree->count;

}


int binaryTreeIsEmpty(BinaryTree *tree) {

    return tree->count == 0;

}




void **binaryTreeToArray(BinaryTree *tree) {


    void *arr = (void **) malloc(sizeof(void *) * tree->count);

    int *index = (int *) malloc(sizeof(int));
    *index = 0;

    binaryTreeToArrayR(tree->root, arr, index);

    free(index);

    return arr;

}



void binaryTreeToArrayR(BinaryTreeNode *root, void **arr, int *index) {

    if (root == NULL)
        return;

    binaryTreeToArrayR(root->left, arr, index);
    arr[(*index)++] = root->key;
    binaryTreeToArrayR(root->right, arr, index);

}



void clearBinaryTree(BinaryTree *tree) {

    clearBinaryTreeR(tree, tree->root);

    tree->root = NULL;

}



void clearBinaryTreeR(BinaryTree *tree, BinaryTreeNode *root) {

    if (root == NULL)
        return;

    clearBinaryTreeR(tree, root->left);
    clearBinaryTreeR(tree, root->right);

    destroyBinaryTreeNode(root, tree->freeFn);

}



void destroyBinaryTree(BinaryTree *tree) {

    clearBinaryTree(tree);
    free(tree);

}