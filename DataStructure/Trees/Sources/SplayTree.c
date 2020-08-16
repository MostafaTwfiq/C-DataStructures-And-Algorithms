#include "../Headers/SplayTree.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


typedef enum SplayTreeRotationType {

    ZIG // right rotation
    , ZAG // left rotation
    , ZIG_ZAG // right right rotation
    , ZAG_ZIG // left right rotation
    , ZAG_ZAG // left left rotation
    , ZIG_ZIG // right right rotation
    , NONE // none rotation

} SplayTreeRotationType;


SplayNode *splayTreeInsertR(SplayTree *tree, SplayNode *parent, SplayNode *root, void *item);

SplayNode *splayTreeDeleteR(SplayTree *tree, SplayNode *root, void *item);

SplayNode *splayTreeDeleteWtoFrR(SplayTree *tree, SplayNode *root, void *item);

void clearSplayTreeR(SplayTree *tree, SplayNode *root);

void splayTreeToArrayR(SplayNode *root, void **arr, int *index);


/** This function will return the right successor of the passed node.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the right successor of the passed node
 */

SplayNode *splayTreeGetRightSuccessor(SplayNode *node) {

    SplayNode *currentNode = node->right;

    if (currentNode == NULL)
        return NULL;

    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;

}


/** This function will compare the passed node value with the passed item.
 *
 * @param node the node pointer
 * @param value the value pointer
 * @param cmp the comparator function pointer
 * @return it will return the result of the comparison
 */

int compareSplayTreeNodeWithValue(SplayNode *node, void *value, int (*cmp)(const void *, const void *)) {

    if (node == NULL)
        return -1;

    return cmp(value, node->key);

}


/** This function will return the current needed rotation do splay up the current node.
 *
 * @param parent the parent node pointer
 * @param root the current node pointer
 * @param child the child node pointer
 * @param item the item pointer
 * @param cmp the comparator function pointer
 * @return it will return the appropriate rotation type
 */

SplayTreeRotationType splayTreeGetRotationType(SplayNode *parent, SplayNode *root, SplayNode *child, void *item,
                                               int (*cmp)(const void *, const void *)) {

    if (child == NULL)
        return NONE;

    else if (parent != NULL && compareSplayTreeNodeWithValue(child, item, cmp) == 0)
        return NONE;

    else if (parent == NULL && compareSplayTreeNodeWithValue(child, item, cmp) == 0)
        return root->left == child ? ZIG : ZAG;

    else if (compareSplayTreeNodeWithValue(child->right, item, cmp) == 0) {

        return root->right == child ? ZAG_ZAG : ZAG_ZIG;

    } else if (compareSplayTreeNodeWithValue(child->left, item, cmp) == 0) {

        return root->right == child ? ZIG_ZAG : ZIG_ZIG;

    } else
        return NONE;

}


/** This function will apply a left rotation on the passed node,
 * then it will return the new root (parent) node.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @return it will return the new root (parent) node
 */

SplayNode *splayTreeLeftRotation(SplayNode *node) {

    SplayNode *newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

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

SplayNode *splayTreeRightRotation(SplayNode *node) {

    SplayNode *newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    return newParent;

}


/** This function will apply the passed rotation type on the passed node,
 * then it will return the new root node.
 *
 * Note: this function should only be called from the inside.
 *
 * @param root the node pointer
 * @param rotationType the rotation type
 * @return it will return the new root node
 */

SplayNode *splayTreePerformRotation(SplayNode *root, SplayTreeRotationType rotationType) {

    switch (rotationType) {

        case ZIG: {
            return splayTreeRightRotation(root);
        };

        case ZAG: {
            return splayTreeLeftRotation(root);
        };

        case ZIG_ZIG: {
            root = splayTreeRightRotation(root);
            return splayTreeRightRotation(root);
        };

        case ZAG_ZAG: {
            root = splayTreeLeftRotation(root);
            return splayTreeLeftRotation(root);
        };

        case ZIG_ZAG: {
            root->right = splayTreeRightRotation(root->right);
            return splayTreeLeftRotation(root);
        };

        case ZAG_ZIG: {
            root->left = splayTreeLeftRotation(root->left);
            return splayTreeRightRotation(root);
        }

        case NONE:
            return root;

    }

    return root;

}


/** This function will create a new splay tree node,
 * then it will return the new node pointer.
 *
 * Note: this function should only be called from the inside.
 *
 * @param item the new node item pointer
 * @return it will return the new initialized node
 */

SplayNode *createSplayTreeNode(void *item) {

    SplayNode *newNode = (SplayNode *) malloc(sizeof(SplayNode));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "splay tree data structure");
        exit(FAILED_ALLOCATION);
    }

    newNode->key = item;
    newNode->left = newNode->right = NULL;

    return newNode;

}


/** This function will destroy and free the node with it's item.
 *
 * Note: this function should only be called from the inside.
 *
 * @param node the node pointer
 * @param freeFun the item free function pointer
 */

void destroySplayTreeNode(SplayNode *node, void (*freeFun)(void *)) {

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

void destroySplayTreeNodeWtoFr(SplayNode *node) {

    node->left = node->right = NULL;
    free(node);

}


SplayTree *splayTreeInitialization(void (*freeFn)(void *), int (*cmp)(const void *, const void *)) {

    if (freeFn == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "compare function pointer", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    }


    SplayTree *tree = (SplayTree *) malloc(sizeof(SplayTree));
    if (tree == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "tree", "splay tree data structure");
        exit(FAILED_ALLOCATION);
    }


    tree->root = NULL;
    tree->count = 0;
    tree->freeFn = freeFn;
    tree->cmp = cmp;


    return tree;

}


/** This function will splay up the node with the passed value if found.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param parent the current parent node pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @return it will return the current node pointer
 */

SplayNode *splayNode(SplayTree *tree, SplayNode *parent, SplayNode *root, void *item) {

    if (root == NULL)
        return NULL;


    else if (tree->cmp(item, root->key) == 0)
        return root;

    else if (tree->cmp(item, root->key) > 0) {
        root->right = splayNode(tree, root, root->right, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->right, item, tree->cmp));
    } else {
        root->left = splayNode(tree, root, root->left, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->left, item, tree->cmp));
    }

}


/** This function will insert the passed item in the tree.
 *
 * @param tree the tree pointer
 * @param item the new item pointer
 */

void splayTreeInsert(SplayTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    }

    tree->root = splayTreeInsertR(tree, NULL, tree->root, item);

}


/** This function will recursively insert the passed item in the tree.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param parent the current parent node pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @return it will return the current node pointer
 */

SplayNode *splayTreeInsertR(SplayTree *tree, SplayNode *parent, SplayNode *root, void *item) {

    if (root == NULL) {
        tree->count++;
        return createSplayTreeNode(item);
    }


    if (tree->cmp(item, root->key) > 0 || tree->cmp(item, root->key) == 0) {
        root->right = splayTreeInsertR(tree, root, root->right, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->right, item, tree->cmp));
    } else {
        root->left = splayTreeInsertR(tree, root, root->left, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->left, item, tree->cmp));
    }

}


/** This function will insert all the array items in the tree.
 *
 * @param tree the tree pointer
 * @param items the items array pointer
 * @param length the length of the items array
 */

void splayTreeInsertAll(SplayTree *tree, void **items, int length) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (items == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "new items array", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    }

    for (int i = 0; i < length; i++)
        splayTreeInsert(tree, items[i]);

}


/** This function will delete and free the passed item from the tree if found,
 * other wise the function will do nothing.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 */

void splayTreeDelete(SplayTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (splayTreeIsEmpty(tree)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "splay tree data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }


    tree->root = splayNode(tree, NULL, tree->root, item);

    if (tree->cmp(item, tree->root->key) != 0)
        return;

    tree->root = splayTreeDeleteR(tree, tree->root, item);

}


/** This function will recursively delete and free the passed item from the tree if found.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @return it will return the current node pointer
 */

SplayNode *splayTreeDeleteR(SplayTree *tree, SplayNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if (tree->cmp(item, root->key) == 0) {

        if (root->right == NULL && root->left == NULL) {
            destroySplayTreeNode(root, tree->freeFn);
            root = NULL;
        } else if (root->right != NULL && root->left != NULL) {
            SplayNode *rightSuccessor = splayTreeGetRightSuccessor(root);
            void *tempValue = root->key;
            root->key = rightSuccessor->key;
            rightSuccessor->key = tempValue;
            root->right = splayTreeDeleteR(tree, root->right, rightSuccessor->key);
            return root;
        } else {
            SplayNode *newRoot = root->right != NULL ? root->right : root->left;
            destroySplayTreeNode(root, tree->freeFn);
            root = newRoot;
        }

        tree->count--;

    } else if (tree->cmp(item, root->key) > 0)
        root->right = splayTreeDeleteR(tree, root->right, item);
    else
        root->left = splayTreeDeleteR(tree, root->left, item);

    return root;


}


/** This function will delete the passed item from the tree without freeing it and then return the item pointer if found,
 * other wise it will return NULL.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return the deleted item pointer if found, other wise it will return NULL
 */

void *splayTreeDeleteWtoFr(SplayTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    } else if (splayTreeIsEmpty(tree)) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = EMPTY_DATA_STRUCTURE;
        return NULL;
#else
        fprintf(stderr, EMPTY_DATA_STRUCTURE_MESSAGE, "splay tree data structure");
        exit(EMPTY_DATA_STRUCTURE);
#endif
    }

    tree->root = splayNode(tree, NULL, tree->root, item);

    if (tree->cmp(item, tree->root->key) != 0)
        return NULL;

    void *itemToReturn = tree->root->key;

    tree->root = splayTreeDeleteWtoFrR(tree, tree->root, item);

    return itemToReturn;

}


/** This function will recursively delete the passed item from the tree without freeing it.
 *
 * Note: this function should only be called from the inside.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 * @param item the item pointer
 * @return it will return the current node pointer
 */

SplayNode *splayTreeDeleteWtoFrR(SplayTree *tree, SplayNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if (tree->cmp(item, root->key) == 0) {

        if (root->right == NULL && root->left == NULL) {
            destroySplayTreeNodeWtoFr(root);
            root = NULL;
        } else if (root->right != NULL && root->left != NULL) {
            SplayNode *rightSuccessor = splayTreeGetRightSuccessor(root);
            void *tempValue = root->key;
            root->key = rightSuccessor->key;
            rightSuccessor->key = tempValue;
            root->right = splayTreeDeleteWtoFrR(tree, root->right, rightSuccessor->key);
            return root;
        } else {
            SplayNode *newRoot = root->right != NULL ? root->right : root->left;
            destroySplayTreeNodeWtoFr(root);
            root = newRoot;
        }

        tree->count--;

    } else if (tree->cmp(item, root->key) > 0)
        root->right = splayTreeDeleteWtoFrR(tree, root->right, item);
    else
        root->left = splayTreeDeleteWtoFrR(tree, root->left, item);

    return root;


}


/** This function will search for the passed item in the tree,
 * and if it found it the function will return one (1), other wise it will return zero (0).
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return 1 if the item exists in the tree, other wise it will return 0
 */

int splayTreeContains(SplayTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    }


    tree->root = splayNode(tree, NULL, tree->root, item);

    if (tree->root == NULL)
        return 0;

    return tree->cmp(item, tree->root->key) == 0 ? 1 : 0;

}


/** This function will search for the passed item in the tree,
 * and if it found it the function will return the item pointer, other wise it will return NULL.
 *
 * @param tree the tree pointer
 * @param item the item pointer
 * @return it will return the item pointer, if found other wise it will return NULL
 */

void *splayTreeGet(SplayTree *tree, void *item) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "splay tree data structure");
        exit(INVALID_ARG);
#endif
    }

    tree->root = splayNode(tree, NULL, tree->root, item);

    if (tree->root == NULL)
        return NULL;

    return tree->cmp(item, tree->root->key) == 0 ? tree->root->key : NULL;

}


/** This function will return the number of nodes in the tree.
 *
 * @param tree the tree pointer
 * @return it will return the number of nodes in the tree
 */

int splayTreeGetSize(SplayTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
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

int splayTreeIsEmpty(SplayTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
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

void **splayTreeToArray(SplayTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    }

    void *arr = (void **) malloc(sizeof(void *) * tree->count);
    if (arr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "splay tree data structure");
        exit(FAILED_ALLOCATION);
    }

    int *index = (int *) malloc(sizeof(int));
    *index = 0;

    splayTreeToArrayR(tree->root, arr, index);

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

void splayTreeToArrayR(SplayNode *root, void **arr, int *index) {

    if (root == NULL)
        return;

    splayTreeToArrayR(root->left, arr, index);
    arr[(*index)++] = root->key;
    splayTreeToArrayR(root->right, arr, index);

}


/** This function will destroy and clear the tree nodes, without destroying the tree itself.
 *
 * @param tree the tree pointer
 */

void clearSplayTree(SplayTree *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    }

    clearSplayTreeR(tree, tree->root);

    tree->root = NULL;

    tree->count = 0;

}


/** This function will recursively destroy and free the tree nodes.
 *
 * @param tree the tree pointer
 * @param root the current node pointer
 */

void clearSplayTreeR(SplayTree *tree, SplayNode *root) {

    if (root == NULL)
        return;

    clearSplayTreeR(tree, root->left);
    clearSplayTreeR(tree, root->right);

    destroySplayTreeNode(root, tree->freeFn);

}


/** This function will destroy and free the tree with all it's nodes.
 *
 * @param tree the tree pointer
 */

void destroySplayTree(void *tree) {

    if (tree == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
        exit(NULL_POINTER);
#endif
    }

    clearSplayTree(tree);
    free(tree);

}



