#include "../Headers/SplayTree.h"
#include "../../../System/Utils.h"


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

SplayNode *splayTreeDeleteWtoFreR(SplayTree *tree, SplayNode *root, void *item);

void clearSplayTreeR(SplayTree *tree, SplayNode *root);




SplayNode *splayTreeGetRightSuccessor(SplayNode *node) {

    SplayNode *currentNode = node->right;

    if (currentNode == NULL)
        return NULL;

    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;

}




int compareSplayTreeNodeWithValue(SplayNode *node, void *value, int (*cmp)(const void *, const void *)) {

    if (node == NULL)
        return -1;

    return cmp(value, node->key);

}


SplayTreeRotationType splayTreeGetRotationType(SplayNode *parent, SplayNode *root, SplayNode *child, void *item, int (*cmp) (const void *, const void *)) {

    if (parent != NULL && compareSplayTreeNodeWithValue(child, item, cmp) == 0)
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

    } else if (cmp == NULL) {

    }


    SplayTree *tree = (SplayTree *) malloc(sizeof(SplayTree));
    if (tree == NULL) {

    }


    tree->root = NULL;
    tree->count = 0;
    tree->freeFn = freeFn;
    tree->cmp = cmp;


    return tree;

}







SplayNode *splayNode(SplayTree *tree, SplayNode *parent, SplayNode *root, void *item) {

    if (root == NULL)
        return NULL;


    else if (tree->cmp(item, root->key) == 0)
        return root;

    else if (tree->cmp(item, root->key) > 0) {
        root->right = splayTreeInsertR(tree, root, root->right, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->right, item, tree->cmp));
    }
    else {
        root->left = splayTreeInsertR(tree, root, root->left, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->left, item, tree->cmp));
    }

}






void splayTreeInsert(SplayTree *tree, void *item) {

    splayTreeInsertR(tree, NULL, tree->root, item);

}



SplayNode *splayTreeInsertR(SplayTree *tree, SplayNode *parent, SplayNode *root, void *item) {

    if (root == NULL) {
        tree->count++;
        return createSplayTreeNode(item);
    }


    if ( tree->cmp(item, root->key) > 0 || tree->cmp(item, root->key) == 0 ) {
        root->right = splayTreeInsertR(tree, root, root->right, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->right, item, tree->cmp));
    }
    else {
        root->left = splayTreeInsertR(tree, root, root->left, item);
        return splayTreePerformRotation(root, splayTreeGetRotationType(parent, root, root->left, item, tree->cmp));
    }

}





void splayTreeInsertAll(SplayTree *tree, void **items, int length) {


    for (int i = 0; i < length; i++)
        splayTreeInsert(tree, items[i]);

}






void splayTreeDelete(SplayTree *tree, void *item) {

    tree->root = splayNode(tree, NULL, tree->root, item);

    if ( tree->cmp(item, tree->root->key) != 0)
        return;

    tree->root = splayTreeDeleteR(tree, tree->root, item);

}



SplayNode *splayTreeDeleteR(SplayTree *tree, SplayNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if ( tree->cmp(item, root->key) == 0 ) {

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

    }

    else if ( tree->cmp(item, root->key) > 0 )
        root->right = splayTreeDeleteR(tree, root->right, item);
    else
        root->left = splayTreeDeleteR(tree, root->left, item);

    return root;


}





void *splayTreeDeleteWtoFr(SplayTree *tree, void *item) {

    tree->root = splayNode(tree, NULL, tree->root, item);

    if ( tree->cmp(item, tree->root->key) != 0 )
        return NULL;

    void *itemToReturn = tree->root->key;

    tree->root = splayTreeDeleteWtoFreR(tree, tree->root, item);

    return itemToReturn;

}



SplayNode *splayTreeDeleteWtoFreR(SplayTree *tree, SplayNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if ( tree->cmp(item, root->key) == 0 ) {

        if (root->right == NULL && root->left == NULL) {
            destroySplayTreeNodeWtoFr(root);
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
            destroySplayTreeNodeWtoFr(root);
            root = newRoot;
        }

        tree->count--;

    }

    else if ( tree->cmp(item, root->key) > 0 )
        root->right = splayTreeDeleteR(tree, root->right, item);
    else
        root->left = splayTreeDeleteR(tree, root->left, item);

    return root;


}





int splayTreeContains(SplayTree *tree, void *item) {

    tree->root = splayNode(tree, NULL, tree->root, item);

    if (tree->root == NULL)
        return 0;

    return tree->cmp(item, tree->root->key) == 0 ? 1 : 0;

}




void *splayTreeGet(SplayTree *tree, void *item) {

    tree->root = splayNode(tree, NULL, tree->root, item);

    if (tree->root == NULL)
        return NULL;

    return tree->cmp(item, tree->root->key) == 0 ? tree->root->key : NULL;

}





int splayTreeGetSize(SplayTree *tree) {

    return tree->count;

}





int splayTreeIsEmpty(SplayTree *tree) {

    return tree->count == 0;

}




/** This function will destroy and clear the tree nodes, without destroying the tree itself.
 *
 * @param tree the tree pointer
 */

void clearSplayTree(SplayTree *tree) {

    if (tree == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
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

void destroyBinaryTree(SplayTree *tree) {

    if (tree == NULL) {
        #ifdef CU_TEST_H
            DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     		return;
        #else
            fprintf(stderr, NULL_POINTER_MESSAGE, "tree", "splay tree data structure");
            exit(NULL_POINTER);
        #endif
    }

    clearSplayTree(tree);
    free(tree);

}



