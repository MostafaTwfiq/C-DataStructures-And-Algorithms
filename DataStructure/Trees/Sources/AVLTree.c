#include "../Headers/AVLTree.h"
#include "../../../System/Utils.h"


typedef enum AVLTreeRotationType {
    LEFT, RIGHT, LEFT_RIGHT, RIGHT_LEFT
}AVLTreeRotationType;




AVLTreeNode *avlTreeInsertR(AVLTree *tree, AVLTreeNode *root, void *item);

AVLTreeNode *avlTreeDeleteR(AVLTree *tree, AVLTreeNode *root, void *item);

void *avlTreeDeleteWtoFrR(AVLTree *tree, AVLTreeNode *parent, AVLTreeNode *root, void *item);




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



void destroyAVLTreeNode(AVLTreeNode *node, void (*freeFun)(void *)) {

    freeFun(node->key);

    node->left = node->right = NULL;
    free(node);

}



void destroyAVLTreeNodeWtoFr(AVLTreeNode *node) {

    node->left = node->right = NULL;
    free(node);

}



int avlTreeGetNodeHeight(AVLTreeNode *node) {
    return node == NULL ? -1 : node->height;
}


int avlTreeGetMaxInt(int a, int b) {
    return a > b ? a : b;
}


void avlTreeCalculateNodeHeight(AVLTreeNode *node) {
    node->height = avlTreeGetMaxInt(avlTreeGetNodeHeight(node->left), avlTreeGetNodeHeight(node->right)) + 1;
}



int avlTreeIsRequiredRotation(AVLTreeNode *node) {
    return abs(avlTreeGetNodeHeight(node->left) - avlTreeGetNodeHeight(node->right)) >= 2;
}


AVLTreeRotationType avlTreeGetRotationType(AVLTreeNode *node) {

    int heightDifferance = avlTreeGetNodeHeight(node->left) - avlTreeGetNodeHeight(node->right);

    if (heightDifferance < 0) {
        AVLTreeNode *rightNode = node->right;
        return rightNode->right != NULL ? LEFT : RIGHT_LEFT;
    } else {
        AVLTreeNode *leftNode = node->left;
        return leftNode->left != NULL ? RIGHT : LEFT_RIGHT;
    }

}




AVLTreeNode *avlTreeLeftRotation(AVLTreeNode *node) {

    AVLTreeNode *newParent = node->right;
    node->right = newParent->left;
    newParent->left = node;

    avlTreeCalculateNodeHeight(node);
    avlTreeCalculateNodeHeight(newParent);

    return newParent;

}




AVLTreeNode *avlTreeRightRotation(AVLTreeNode *node) {

    AVLTreeNode *newParent = node->left;
    node->left = newParent->right;
    newParent->right = node;

    avlTreeCalculateNodeHeight(node);
    avlTreeCalculateNodeHeight(newParent);

    return newParent;

}



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




AVLTreeNode *avlTreeGetRightSuccessor(AVLTreeNode *root) {

    AVLTreeNode *currentNode = root->right;

    while (currentNode->left != NULL)
        currentNode = currentNode->left;

    return currentNode;

}



AVLTree *avlTreeInitialization(void (*freeFun)(void *), int (*cmp)(const void *, const void *)) {

    if (freeFun == NULL) {

    } else if (cmp == NULL) {

    }

    AVLTree *tree = (AVLTree *) malloc(sizeof(AVLTree));
    if (tree == NULL) {

    }

    tree->root = NULL;
    tree->count = 0;
    tree->freeFn = freeFun;
    tree->cmp = cmp;


    return tree;

}





void avlTreeInsert(AVLTree *tree, void *item) {

    tree->root = avlTreeInsertR(tree, tree->root, item);
}


AVLTreeNode *avlTreeInsertR(AVLTree *tree, AVLTreeNode *root, void *item) {

    if (root == NULL) {
        tree->count++;
        return createAVLTreeNode(item);
    }

    if ( tree->cmp(item, root->key) > 0 || tree->cmp(item, root->key) == 0 )
        root->right = avlTreeInsertR(tree, root->right, item);
    else
        root->left = avlTreeInsertR(tree, root->left, item);


    avlTreeCalculateNodeHeight(root);

    if (avlTreeIsRequiredRotation(root))
        return avlTreePerformRotation(root, avlTreeGetRotationType(root));

    return root;

}





void avlTreeDelete(AVLTree *tree, void *item) {

    tree->root = avlTreeDeleteR(tree, tree->root, item);
}


AVLTreeNode *avlTreeDeleteR(AVLTree *tree, AVLTreeNode *root, void *item) {

    if (root == NULL)
        return NULL;

    if ( tree->cmp(item, root->key) == 0 ) {

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
        }

        tree->count--;

    }

    else if ( tree->cmp(item, root->key) > 0 )
        root->right = avlTreeDeleteR(tree, root->right, item);
    else
        root->left = avlTreeDeleteR(tree, root->left, item);


    avlTreeCalculateNodeHeight(root);

    if (avlTreeIsRequiredRotation(root))
        return avlTreePerformRotation(root, avlTreeGetRotationType(root));

    return root;

}





void *avlTreeDeleteWtoFr(AVLTree *tree, void *item) {

    return avlTreeDeleteWtoFrR(tree, NULL, tree->root, item);

}


void *avlTreeDeleteWtoFrR(AVLTree *tree, AVLTreeNode *parent, AVLTreeNode *root, void *item) {

    if (root == NULL)
        return NULL;

    void *itemToReturn;

    if ( tree->cmp(item, root->key) == 0 ) {

        itemToReturn = root->key;

        if (root->right == NULL && root->left == NULL) {

            if (parent == NULL)
                tree->root = NULL;
            else {

                if (parent->right == root)
                    parent->right = NULL;
                else
                    parent->left = NULL;

            }

            destroyAVLTreeNodeWtoFr(root);

        } else if (root->right != NULL && root->left != NULL) {

            AVLTreeNode *rightSuccessorNode = avlTreeGetRightSuccessor(root);
            void *tempValue = root->key;
            root->key = rightSuccessorNode->key;
            rightSuccessorNode->key = tempValue;
            avlTreeDeleteWtoFrR(tree, root, root->right, rightSuccessorNode->key);

        } else {

            AVLTreeNode *newRoot = root->right != NULL ? root->right : root->left;

            if (parent == NULL)
                tree->root = newRoot;
            else {

                if (parent->right == root)
                    parent->right = newRoot;
                else
                    parent->left = newRoot;

            }

            destroyAVLTreeNodeWtoFr(root);

        }

        tree->count--;

    }

    else if ( tree->cmp(item, root->key) > 0 )
        itemToReturn = root->right = avlTreeDeleteR(tree, root->right, item);
    else
        itemToReturn = root->left = avlTreeDeleteR(tree, root->left, item);


    if (parent != NULL) {
        avlTreeCalculateNodeHeight(parent);

        if (avlTreeIsRequiredRotation(parent))
            return avlTreePerformRotation(parent, avlTreeGetRotationType(parent));

    }

    return itemToReturn;

}





int avlTreeContains(AVLTree *tree, void *item) {


    AVLTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if ( tree->cmp(item, currentNode->key) == 0)
            break;
        else if ( tree->cmp(item, currentNode->key) < 0 )
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;

    }

    return currentNode != NULL ? 1 : 0;

}




void *avlTreeGet(AVLTree *tree, void *item) {


    AVLTreeNode *currentNode = tree->root;

    while (currentNode != NULL) {

        if ( tree->cmp(item, currentNode->key) == 0)
            break;
        else if ( tree->cmp(item, currentNode->key) < 0 )
            currentNode = currentNode->left;
        else
            currentNode = currentNode->right;

    }

    return currentNode != NULL ? currentNode->key : NULL;

}




int avlTreeGetSize(AVLTree *tree) {

    return tree->count;

}


int avlTreeIsEmpty(AVLTree *tree) {

    return tree->count == 0;

}


