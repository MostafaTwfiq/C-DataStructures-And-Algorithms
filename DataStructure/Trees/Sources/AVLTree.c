#include "../Headers/AVLTree.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


typedef enum AVLTreeRotationType {
    LEFT, RIGHT, LEFT_RIGHT, RIGHT_LEFT
} AVLTreeRotationType;


AVLTreeNode *avlTreeInsertR(AVLTree *tree, AVLTreeNode *root, void *item);

AVLTreeNode *avlTreeDeleteR(AVLTree *tree, AVLTreeNode *root, void *item);

AVLTreeNode *avlTreeDeleteWtoFrR(AVLTree *tree, AVLTreeNode *root, void *item, void **deletedItemHolder);

void avlTreeToArrayR(void **arr, AVLTreeNode *root, int *index);

void avlTreePreOrderTraversalR(AVLTreeNode *root, void (*printFun)(void *));

void avlTreeInOrderTraversalR(AVLTreeNode *root, void (*printFun)(void *));

void avlTreePostOrderTraversalR(AVLTreeNode *root, void (*printFun)(void *));

void clearAVLTreeR(AVLTreeNode *root, void (*freeFun)(void *));

void avlTreeBreadthFirstTraversalR(AVLTreeNode *root, int currentLevel, int targetLevel, void (*printFun)(void *));


/** This function will create a new avl tree node,
 * then it will return the new node pointer.
 *
 * Note: this function should only be called from the inside.
 *
 * @param item the new node item pointer
 * @return it will return the new initialized node
 */

AVLTreeNode *createAVLTreeNode(void *item) {

    AVLTreeNode *newNode = (AVLTreeNode *) malloc(sizeof(AVLTreeNode));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "avl tree data structure");
        exit(FAILED_ALLOCATION);
    }

    newNode->key = item;
    newNode->left = newNode->right = NULL;
    newNode->height = 0;

    return newNode;

}


/** This function will destroy and free the node with it's item.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @param freeFun the item free function pointer
 */

void destroyAVLTreeNode(AVLTreeNode *node, void (*freeFun)(void *)) {

    freeFun(node->key);

    node->left = node->right = NULL;
    free(node);

}


/** This function will destroy and free the node without freeing it's item.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 */

void destroyAVLTreeNodeWtoFr(AVLTreeNode *node) {

    node->left = node->right = NULL;
    free(node);

}


/** This function returns the passed node height,
 * and if the node was NULL, the function will return minus one (-1).
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the node height, and if the node was NULL the function will return -1
 */

int avlTreeGetNodeHeight(AVLTreeNode *node) {
    return node == NULL ? -1 : node->height;
}


/** This function takes two integers,
 * then it returns  the largest integer.
 *
 * Note: this function should only be called from the inside.
 *
 * @param a the first integer value
 * @param b the second integer value
 * @return it will return the largest integer
 */

int avlTreeGetMaxInt(int a, int b) {
    return a > b ? a : b;
}


/** This function calculate the passed node height,
 * and then store it in the node height variable.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 */

void avlTreeCalculateNodeHeight(AVLTreeNode *node) {
    node->height = avlTreeGetMaxInt(avlTreeGetNodeHeight(node->left), avlTreeGetNodeHeight(node->right)) + 1;
}


/** This function checks if the passed node require rotation or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return 1 if the node require rotation, other wise it will return 0
 */

int avlTreeIsRequiredRotation(AVLTreeNode *node) {
    int value = avlTreeGetNodeHeight(node->left) - avlTreeGetNodeHeight(node->right);
    value = value < 0 ? value * -1 : value;
    return value >= 2;
}


/** This function return the rotate type that the node needs to balance the tree.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the rotation type that the node needs
 */

AVLTreeRotationType avlTreeGetRotationType(AVLTreeNode *node) {

    int heightDifferance = avlTreeGetNodeHeight(node->left) - avlTreeGetNodeHeight(node->right);

    if (heightDifferance < 0) {
        AVLTreeNode *rightNode = node->right;
        int heightComp = avlTreeGetNodeHeight(rightNode->left) - avlTreeGetNodeHeight(rightNode->right);
        return heightComp <= 0 ? LEFT : RIGHT_LEFT;
    } else {
        AVLTreeNode *leftNode = node->left;
        int heightComp = avlTreeGetNodeHeight(leftNode->left) - avlTreeGetNodeHeight(leftNode->right);
        return heightComp >= 0 ? RIGHT : LEFT_RIGHT;
    }

}


/** This function will apply a left rotation on the passed node,
 * then it will return the new root (parent) node.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the new root (parent) node
 */

AVLTreeNode *avlTreeLeftRotation(AVLTreeNode *node) {

    AVLTreeNode *newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    avlTreeCalculateNodeHeight(node);
    avlTreeCalculateNodeHeight(newParent);

    return newParent;

}


/** This function will apply a right rotation on the passed node,
 * then it will return the new root (parent) node.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the new root (parent) node
 */

AVLTreeNode *avlTreeRightRotation(AVLTreeNode *node) {

    AVLTreeNode *newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    avlTreeCalculateNodeHeight(node);
    avlTreeCalculateNodeHeight(newParent);

    return newParent;

}


/** This function will check for the passed rotation type,
 * then it will perform it.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @param rotationType the rotation type
 * @return it will return the new root (parent) node after the rotation
 */

AVLTreeNode *avlTreePerformRotation(AVLTreeNode *node, AVLTreeRotationType rotationType) {

    switch (rotationType) {

        case LEFT: {
            return avlTreeLeftRotation(node);
        };

        case RIGHT: {
            return avlTreeRightRotation(node);
        };

        case LEFT_RIGHT: {
            node->left = avlTreeLeftRotation(node->left);
            node = avlTreeRightRotation(node);
            return node;
        };

        case RIGHT_LEFT: {
            node->right = avlTreeRightRotation(node->right);
            node = avlTreeLeftRotation(node);
            return node;
        };

    }

    return node;

}


/** This function will return the right successor of the passed node.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the right successor of the passed node
 */

AVLTreeNode *avlTreeGetRightSuccessor(AVLTreeNode *node) {

    AVLTreeNode *currentNode = node->right;

    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;

}


/** This function will initialize a new avl tree and setup  it's fields,
 * then return it's pointer.
 *
 * @param freeFun the free function pointer, that will be called to free the avl tree items
 * @param cmp it comparator function pointer, that will be called to compare the avl tree items
 * @return it will return the new initialized avl tree pointer
 */

AVLTree *avlTreeInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *)) {

    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "compare function pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    AVLTree *tree = (AVLTree *) malloc(sizeof(AVLTree));
    if (tree == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "tree", "binary tree data structure");
        exit(FAILED_ALLOCATION);
    }

    tree->root = NULL;
    tree->count = 0;
    tree->freeFn = freeFun;
    tree->cmp = cmp;


    return tree;

}


/** This function will insert the passed item in the tree.
 *
 * @param tree the tree pointer
 * @param item the new item pointer
 */

void avlTreeInsert(AVLTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    tree->root = avlTreeInsertR(tree, tree->root, item);
}


/** This function will recursively insert the passed item in the tree.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 * @param item the new item pointer
 * @return it will return the current node pointer
 */

AVLTreeNode *avlTreeInsertR(AVLTree *tree, AVLTreeNode *root, void *item) {

    if (root == NULL) {
        tree->count++;
        return createAVLTreeNode(item);
    }

    if (tree->cmp(item, root->key) > 0 || tree->cmp(item, root->key) == 0)
        root->right = avlTreeInsertR(tree, root->right, item);
    else
        root->left = avlTreeInsertR(tree, root->left, item);


    avlTreeCalculateNodeHeight(root);

    if (avlTreeIsRequiredRotation(root))
        return avlTreePerformRotation(root, avlTreeGetRotationType(root));

    return root;

}


/** This function will take an items array,
 * then it will insert all the items in the tree.
 *
 * @param tree the tree pointer
 * @param items the items array pointer
 * @param length the length of the items array
 */

void avlInsertAll(AVLTree *tree, void **items, int length) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (items == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    for (int i = 0; i < length; i++)
        avlTreeInsert(tree, items[i]);

}


/** This function will search for the passed item then it will destroy and remove the item node from the tree
 * if found, other wise it will do nothing.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 */

void avlTreeDelete(AVLTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (avlTreeIsEmpty(tree)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "avl tree data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    tree->root = avlTreeDeleteR(tree, tree->root, item);

}


/** This function will recursively search for the passed node item, then it will remove the node from the tree
 * if found, other wise the function will do nothing.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @return it will return the current node pointer
 */

AVLTreeNode *avlTreeDeleteR(AVLTree *tree, AVLTreeNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if (tree->cmp(item, root->key) == 0) {

        if (root->right == NULL && root->left == NULL) {
            destroyAVLTreeNode(root, tree->freeFn);
            tree->count--;
            return NULL;
        } else if (root->right != NULL && root->left != NULL) {
            AVLTreeNode *rightSuccessorNode = avlTreeGetRightSuccessor(root);
            void *tempValue = root->key;
            root->key = rightSuccessorNode->key;
            rightSuccessorNode->key = tempValue;
            root->right = avlTreeDeleteR(tree, root->right, rightSuccessorNode->key);
        } else {
            AVLTreeNode *newRoot = root->right != NULL ? root->right : root->left;
            destroyAVLTreeNode(root, tree->freeFn);
            root = newRoot;
            tree->count--;
        }

    } else if (tree->cmp(item, root->key) > 0)
        root->right = avlTreeDeleteR(tree, root->right, item);
    else
        root->left = avlTreeDeleteR(tree, root->left, item);


    avlTreeCalculateNodeHeight(root);

    if (avlTreeIsRequiredRotation(root))
        return avlTreePerformRotation(root, avlTreeGetRotationType(root));

    return root;

}


/** This function will search for the passed item in the tree,
 * and if it found it the function will remove the node and free it without freeing the node item and then return the item pointer,
 * other wise it will return NULL.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return the deleted item pointer
 */

void *avlTreeDeleteWtoFr(AVLTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (avlTreeIsEmpty(tree)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "avl tree data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    void **deletedItemHolder = (void **) malloc(sizeof(void *));
    *deletedItemHolder = NULL;

    tree->root = avlTreeDeleteWtoFrR(tree, tree->root, item, deletedItemHolder);

    void *deletedItem = *deletedItemHolder;
    free(deletedItemHolder);

    return deletedItem;

}


/** This function will recursively search for the passed item,
 * then it will delete the item from the tree without freeing it's item if found and then return the item pointer,
 * other wise it will return NULL.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @param deletedItemHolder a pointer to a holder that will hold the address of the deleted item
 * @return it will return the deleted item pointer if found, other wise it will return NULL
 */

AVLTreeNode *avlTreeDeleteWtoFrR(AVLTree *tree, AVLTreeNode *root, void *item, void **deletedItemHolder) {

    if (root == NULL)
        return NULL;

    if (tree->cmp(item, root->key) == 0) {

        *deletedItemHolder = root->key;

        if (root->right == NULL && root->left == NULL) {
            destroyAVLTreeNodeWtoFr(root);
            tree->count--;
            return NULL;
        } else if (root->right != NULL && root->left != NULL) {
            AVLTreeNode *rightSuccessorNode = avlTreeGetRightSuccessor(root);
            void *tempValue = root->key;
            root->key = rightSuccessorNode->key;
            rightSuccessorNode->key = tempValue;
            root->right = avlTreeDeleteWtoFrR(tree, root->right, rightSuccessorNode->key, deletedItemHolder);
        } else {
            AVLTreeNode *newRoot = root->right != NULL ? root->right : root->left;
            destroyAVLTreeNodeWtoFr(root);
            root = newRoot;
            tree->count--;
        }

    } else if (tree->cmp(item, root->key) > 0)
        root->right = avlTreeDeleteWtoFrR(tree, root->right, item, deletedItemHolder);
    else
        root->left = avlTreeDeleteWtoFrR(tree, root->left, item, deletedItemHolder);


    avlTreeCalculateNodeHeight(root);

    if (avlTreeIsRequiredRotation(root))
        return avlTreePerformRotation(root, avlTreeGetRotationType(root));

    return root;

}


/** This function will check if the passed item exists in the tree or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return 1 if the item exist in the tree, other wise it will return 0
 */

int avlTreeContains(AVLTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    AVLTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if (tree->cmp(item, currentNode->key) == 0)
            break;
        else if (tree->cmp(item, currentNode->key) < 0)
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;

    }

    return currentNode != NULL ? 1 : 0;

}


/** This function will check if the passed item is in the tree or not,
 * and if it was the function will return the item pointer,
 * other wise it will return NULL.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return the item pointer if found, other wise it will return NULL
 */

void *avlTreeGet(AVLTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    AVLTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if (tree->cmp(item, currentNode->key) == 0)
            break;
        else if (tree->cmp(item, currentNode->key) < 0)
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;

    }

    return currentNode != NULL ? currentNode->key : NULL;

}


/** This function will return the current number of nodes in the tree.
 *
 * @param tree the tree pointer
 * @return it will return the number of the nodes existing in the tree
 */

int avlTreeGetSize(AVLTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    }

    return tree->count;

}


/** This function will check if the tree is empty or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * @param tree the tree pointer
 * @return it will return 1 if the tree was empty, other wise it will return 0
 */

int avlTreeIsEmpty(AVLTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    }

    return tree->count == 0;

}


/** This function will return a double void pointer array,
 * that contains the tree items sorted in ascending order.
 *
 * @param tree the tree pointer
 * @return it will return an array that contains the tree items sorted in ascending order
 */

void **avlTreeToArray(AVLTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    }

    void **arr = (void **) malloc(sizeof(void *) * tree->count);
    if (arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "avl tree data structure");
    }
    int *index = (int *) malloc(sizeof(int));
    *index = 0;

    avlTreeToArrayR(arr, tree->root, index);

    free(index);

    return arr;

}


/** This function will recursively fill the passed array,
 * with the tree items sorted in ascending order.
 *
 * Note: this function should only be called from the inside.
 *
 * @param arr the array pointer
 * @param root the current node pointer
 * @param index the current index pointer
 */

void avlTreeToArrayR(void **arr, AVLTreeNode *root, int *index) {

    if (root == NULL)
        return;

    avlTreeToArrayR(arr, root->left, index);
    arr[(*index)++] = root->key;
    avlTreeToArrayR(arr, root->right, index);

}


/** This function will pre order traverse the tree.
 *
 * Note: you can do any thing else the printing.
 *
 * @param tree the tree pointer
 * @param printFun the printing function pointer
 */

void avlTreePreOrderTraversal(AVLTree *tree, void (*printFun)(void *)) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    avlTreePreOrderTraversalR(tree->root, printFun);

}


/** This function will pre order traverse the tree recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param printFun the printing function pointer
 */

void avlTreePreOrderTraversalR(AVLTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    printFun(root->key);
    avlTreePreOrderTraversalR(root->left, printFun);
    avlTreePreOrderTraversalR(root->right, printFun);

}


/** This function will in order traverse the tree.
 *
 * Note: you can do any thing else the printing.
 *
 * @param tree the tree pointer
 * @param printFun the printing function pointer
 */

void avlTreeInOrderTraversal(AVLTree *tree, void (*printFun)(void *)) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    avlTreeInOrderTraversalR(tree->root, printFun);

}


/** This function will in order traverse the tree recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param printFun the printing function pointer
 */

void avlTreeInOrderTraversalR(AVLTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    avlTreeInOrderTraversalR(root->left, printFun);
    printFun(root->key);
    avlTreeInOrderTraversalR(root->right, printFun);

}


/** This function will post order traverse the tree.
 *
 * Note: you can do any thing else the printing.
 *
 * @param tree the tree pointer
 * @param printFun the printing function pointer
 */

void avlTreePostOrderTraversal(AVLTree *tree, void (*printFun)(void *)) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    avlTreePostOrderTraversalR(tree->root, printFun);

}


/** This function will post order traverse the tree recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param printFun the printing function pointer
 */

void avlTreePostOrderTraversalR(AVLTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    avlTreePostOrderTraversalR(root->left, printFun);
    avlTreePostOrderTraversalR(root->right, printFun);
    printFun(root->key);

}


/** This function will breadth first traverse the tree.
 *
 * Note: you can do any thing else the printing.
 *
 * @param tree the tree pointer
 * @param printFun the printing function pointer
 */

void avlTreeBreadthFirstTraversal(AVLTree *tree, void (*printFun)(void *)) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "avl tree data structure");
        exit(INVALID_ARG);
#endif
    }

    if (tree->root == NULL)
        return;

    for (int i = 0; i < tree->root->height + 1; i++)
        avlTreeBreadthFirstTraversalR(tree->root, 0, i, printFun);

}


/** This function will breadth first traverse the tree recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param currentLevel the current level
 * @param targetLevel the target level that the function will stop when reached it
 * @param printFun the printing function pointer
 */

void avlTreeBreadthFirstTraversalR(AVLTreeNode *root, int currentLevel, int targetLevel, void (*printFun)(void *)) {

    if (root == NULL || currentLevel > targetLevel)
        return;

    else if (currentLevel == targetLevel) {
        printFun(root->key);
        return;
    }

    avlTreeBreadthFirstTraversalR(root->left, currentLevel + 1, targetLevel, printFun);
    avlTreeBreadthFirstTraversalR(root->right, currentLevel + 1, targetLevel, printFun);

}


/** This function will destroy and clear the tree nodes, without destroying the tree itself.
 *
 * @param tree the tree pointer
 */

void clearAVLTree(AVLTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    }

    clearAVLTreeR(tree->root, tree->freeFn);


    tree->root = NULL;
    tree->count = 0;

}


/** This function will recursively destroy and free the tree nodes.
 *
 * @param root the current node pointer
 * @param freeFun the item free function pointer
 */

void clearAVLTreeR(AVLTreeNode *root, void (*freeFun)(void *)) {

    if (root == NULL)
        return;

    clearAVLTreeR(root->left, freeFun);
    clearAVLTreeR(root->right, freeFun);

    destroyAVLTreeNode(root, freeFun);

}


/** This function will destroy and free the tree with all it's nodes.
 *
 * @param tree the tree pointer
 */

void destroyAVLTree(void *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "avl tree data structure");
        exit(NULL_POINTER);
#endif
    }

    clearAVLTree(tree);

    free(tree);

}