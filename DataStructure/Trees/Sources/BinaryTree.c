#include "../Headers/BinaryTree.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


BinaryTreeNode *binaryTreeInsertR(BinaryTree *tree, BinaryTreeNode *root, void *item);

BinaryTreeNode *binaryTreeDeleteR(BinaryTree *tree, BinaryTreeNode *root, void *item);

void *binaryTreeDeleteWtoFrR(BinaryTree *tree, BinaryTreeNode *parent, BinaryTreeNode *root, void *item);

void binaryTreePreOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *));

void binaryTreeInOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *));

void binaryTreePostOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *));

void clearBinaryTreeR(BinaryTree *tree, BinaryTreeNode *root);

void binaryTreeToArrayR(BinaryTreeNode *root, void **arr, int *index);


/** This function will create a new node and return it's pointer.
 *
 * Note: this function should only be called from the inside.
 *
 * @param item the node item pointer
 * @return it will return the new allocated node
 */

BinaryTreeNode *createBinaryTreeNode(void *item) {

    BinaryTreeNode *newNode = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "binary tree data structure");
        exit(FAILED_ALLOCATION);
    }

    newNode->key = item;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;

}


/** This function will destroy and free the passed node with it's item.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @param freeFun the item free function pointer
 */

void destroyBinaryTreeNode(BinaryTreeNode *node, void (*freeFun)(void *)) {

    freeFun(node->key);
    node->right = NULL;
    node->left = NULL;
    free(node);

}


/** This function will destroy and free the passed node without freeing it's item.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 */

void destroyBinaryTreeNodeWtoFr(BinaryTreeNode *node) {

    node->right = NULL;
    node->left = NULL;
    free(node);

}


/** This function will take a node then it will return the right successor node.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the right successor node pointer
 */

BinaryTreeNode *getRightSuccessorBT(BinaryTreeNode *node) {

    BinaryTreeNode *currentNode = node->right;

    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;

}


/** This function will initialize a new binary tree,
 * then it will return the allocated tree pointer.
 *
 * @param freeFun the freeing function pointer, that will be called to free the tree items.
 * @param cmp the comparator function pointer, that will be called to compare the tree items.
 * @return it will return the new initialized tree pointer
 */

BinaryTree *binaryTreeInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *)) {

    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "compare function pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }

    BinaryTree *tree = (BinaryTree *) malloc(sizeof(BinaryTree));
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


/** This function will insert the passed new item into the tree.
 *
 * @param tree the tree pointer
 * @param item the new item pointer
 */

void binaryTreeInsert(BinaryTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }

    tree->root = binaryTreeInsertR(tree, tree->root, item);

}


/** This function will insert the tree new item recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 * @param item the new item pointer
 * @return it will return the current node pointer
 */

BinaryTreeNode *binaryTreeInsertR(BinaryTree *tree, BinaryTreeNode *root, void *item) {

    if (root == NULL) {
        tree->count++;
        root = createBinaryTreeNode(item);
    } else if (tree->cmp(item, root->key) > 0 || tree->cmp(item, root->key) == 0)
        root->right = binaryTreeInsertR(tree, root->right, item);
    else if (tree->cmp(item, root->key) < 0)
        root->left = binaryTreeInsertR(tree, root->left, item);

    return root;

}


/** This function will take an items array,
 * then it will insert all the items in the tree.
 *
 * @param tree the tree pointer
 * @param items the items array pointer
 * @param length the length of the items array
 */

void binaryTreeInsertAll(BinaryTree *tree, void **items, int length) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (items == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "items array pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }

    for (int i = 0; i < length; i++)
        binaryTreeInsert(tree, items[i]);

}


/** This function will delete and free the passed item from the tree if found,
 * other wise the function will do nothing.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 */

void binaryTreeDelete(BinaryTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (binaryTreeIsEmpty(tree)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "binary tree data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    tree->root = binaryTreeDeleteR(tree, tree->root, item);

}


/** This function will delete the passed item recursively from the tree.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @return it will return the current node pointer
 */

BinaryTreeNode *binaryTreeDeleteR(BinaryTree *tree, BinaryTreeNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if (tree->cmp(item, root->key) == 0) {

        if (root->right == NULL && root->left == NULL) {
            destroyBinaryTreeNode(root, tree->freeFn);
            root = NULL;
        } else if (root->right != NULL && root->left != NULL) {
            BinaryTreeNode *rightSuccessor = getRightSuccessorBT(root);
            void *tempValue = root->key;
            root->key = rightSuccessor->key;
            rightSuccessor->key = tempValue;
            root->right = binaryTreeDeleteR(tree, root->right, rightSuccessor->key);
            return root;
        } else {
            BinaryTreeNode *newRoot = root->right != NULL ? root->right : root->left;
            destroyBinaryTreeNode(root, tree->freeFn);
            root = newRoot;
        }

        tree->count--;

    } else if (tree->cmp(item, root->key) > 0)
        root->right = binaryTreeDeleteR(tree, root->right, item);
    else
        root->left = binaryTreeDeleteR(tree, root->left, item);

    return root;

}


/** This function will delete the passed item from the tree without freeing it,
 * then it will return the deleted item pointer if found, other wise it will return NULL.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return the deleted item pointer if found, other wise it will return NULL
 */

void *binaryTreeDeleteWtoFr(BinaryTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (binaryTreeIsEmpty(tree)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "binary tree data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    return binaryTreeDeleteWtoFrR(tree, NULL, tree->root, item);

}


/** This function will delete the passed item from the tree recursively without freeing it,
 * and after that the function will return the passed item pointer if found, other wise it will return NULL.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param parent the parent node pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @return it will return the deleted item pointer if found, other wise it will return NULL
 */
void *binaryTreeDeleteWtoFrR(BinaryTree *tree, BinaryTreeNode *parent, BinaryTreeNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if (tree->cmp(item, root->key) == 0) {

        void *itemToReturn = root->key;

        if (root->right == NULL && root->left == NULL) {

            if (parent == NULL)
                tree->root = NULL;
            else {

                if (parent->right == root)
                    parent->right = NULL;
                else
                    parent->left = NULL;

            }

            destroyBinaryTreeNodeWtoFr(root);

        } else if (root->right != NULL && root->left != NULL) {

            BinaryTreeNode *rightSuccessor = getRightSuccessorBT(root);
            void *tempValue = root->key;
            root->key = rightSuccessor->key;
            rightSuccessor->key = tempValue;
            return binaryTreeDeleteWtoFrR(tree, root, root->right, rightSuccessor->key);

        } else {

            if (parent == NULL) {
                tree->root = root->right != NULL ? root->right : root->left;
            } else {

                if (parent->right == root)
                    parent->right = root->right != NULL ? root->right : root->left;
                else
                    parent->left = root->right != NULL ? root->right : root->left;
            }

            destroyBinaryTreeNodeWtoFr(root);

        }

        tree->count--;

        return itemToReturn;

    } else if (tree->cmp(item, root->key) > 0)
        return binaryTreeDeleteWtoFrR(tree, root, root->right, item);
    else
        return binaryTreeDeleteWtoFrR(tree, root, root->left, item);

}


/** This function will check if the passed item is in the tree or not,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return 1 if the item was in the tree, other wise it will return 0
 */

int binaryTreeContains(BinaryTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }


    BinaryTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if (tree->cmp(item, currentNode->key) == 0)
            break;
        else if (tree->cmp(item, currentNode->key) > 0)
            currentNode = currentNode->right;
        else
            currentNode = currentNode->left;

    }

    return currentNode == NULL ? 0 : 1;

}


/** This function will check for the passed item in the tree,
 * and if it found it the function will return the item pointer, other wise it will return NULL.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return the item pointer if found, other wise it will return NULL
 */

void *binaryTreeGet(BinaryTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }

    BinaryTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if (tree->cmp(item, currentNode->key) == 0)
            break;
        else if (tree->cmp(item, currentNode->key) > 0)
            currentNode = currentNode->right;
        else
            currentNode = currentNode->left;

    }

    return currentNode == NULL ? NULL : currentNode->key;

}


/** This function will pre order traverse the tree.
 *
 * Note: you can do any thing else the printing.
 *
 * @param tree the tree pointer
 * @param printFun the printing function pointer
 */

void binaryTreePreOrderTraversal(BinaryTree *tree, void (*printFun)(void *)) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }

    binaryTreePreOrderTraversalR(tree->root, printFun);

}


/** This function will pre order traverse the tree recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param printFun the printing function pointer
 */

void binaryTreePreOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    printFun(root->key);
    binaryTreePreOrderTraversalR(root->left, printFun);
    binaryTreePreOrderTraversalR(root->right, printFun);

}


/** This function will in order traverse the tree.
 *
 * Note: you can do any thing else the printing.
 *
 * @param tree the tree pointer
 * @param printFun the printing function pointer
 */

void binaryTreeInOrderTraversal(BinaryTree *tree, void (*printFun)(void *)) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }

    binaryTreeInOrderTraversalR(tree->root, printFun);

}


/** This function will in order traverse the tree recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param printFun the printing function pointer
 */

void binaryTreeInOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    binaryTreeInOrderTraversalR(root->left, printFun);
    printFun(root->key);
    binaryTreeInOrderTraversalR(root->right, printFun);

}


/** This function will post order traverse the tree.
 *
 * Note: you can do any thing else the printing.
 *
 * @param tree the tree pointer
 * @param printFun the printing function pointer
 */

void binaryTreePostOrderTraversal(BinaryTree *tree, void (*printFun)(void *)) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "printing function pointer", "binary tree data structure");
        exit(INVALID_ARG);
#endif
    }

    binaryTreePostOrderTraversalR(tree->root, printFun);

}


/** This function will post order traverse the tree recursively.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param printFun the printing function pointer
 */

void binaryTreePostOrderTraversalR(BinaryTreeNode *root, void (*printFun)(void *)) {

    if (root == NULL)
        return;


    binaryTreePostOrderTraversalR(root->left, printFun);
    binaryTreePostOrderTraversalR(root->right, printFun);
    printFun(root->key);

}


/** This function will return the number of nodes in the tree.
 *
 * @param tree the tree pointer
 * @return it will return the number of nodes in the tree
 */

int binaryTreeGetSize(BinaryTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
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

int binaryTreeIsEmpty(BinaryTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
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

void **binaryTreeToArray(BinaryTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    }

    void *arr = (void **) malloc(sizeof(void *) * tree->count);
    if (arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "binary tree data structure");
        exit(FAILED_ALLOCATION);
    }

    int *index = (int *) malloc(sizeof(int));
    *index = 0;

    binaryTreeToArrayR(tree->root, arr, index);

    free(index);

    return arr;

}


/** This function will recursively fill the passed array,
 * with the tree items sorted in ascending order.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the current node pointer
 * @param arr the array pointer
 * @param index the current index pointer
 */

void binaryTreeToArrayR(BinaryTreeNode *root, void **arr, int *index) {

    if (root == NULL)
        return;

    binaryTreeToArrayR(root->left, arr, index);
    arr[(*index)++] = root->key;
    binaryTreeToArrayR(root->right, arr, index);

}


/** This function will destroy and clear the tree nodes, without destroying the tree itself.
 *
 * @param tree the tree pointer
 */

void clearBinaryTree(BinaryTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    }

    clearBinaryTreeR(tree, tree->root);

    tree->root = NULL;

    tree->count = 0;

}


/** This function will recursively destroy and free the tree nodes.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 */

void clearBinaryTreeR(BinaryTree *tree, BinaryTreeNode *root) {

    if (root == NULL)
        return;

    clearBinaryTreeR(tree, root->left);
    clearBinaryTreeR(tree, root->right);

    destroyBinaryTreeNode(root, tree->freeFn);

}


/** This function will destroy and free the tree with all it's nodes.
 *
 * @param tree the tree pointer
 */

void destroyBinaryTree(void *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "binary tree data structure");
        exit(NULL_POINTER);
#endif
    }

    clearBinaryTree(tree);
    free(tree);

}




