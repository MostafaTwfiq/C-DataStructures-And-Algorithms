#include "Headers/BinaryTree.h"

int comp(const void *p1, const void *p2) {
    return *((int *)p1) - *((int *)p2);
}

int main(void){
    BinaryTree* btree = BinaryTreeInitialize(sizeof(int), comp);

    int *item;

    item = (int *) malloc(sizeof(int));
    *item = 10;
    btree->root = insertBinaryTree(btree, btree->root, item);

    item = (int *) malloc(sizeof(int));
    *item = 50;
    btree->root = insertBinaryTree(btree, btree->root, item);

    item = (int *) malloc(sizeof(int));
    *item = 5;
    btree->root = insertBinaryTree(btree, btree->root, item);

    item = (int *) malloc(sizeof(int));
    *item = 12;
    btree->root = insertBinaryTree(btree, btree->root, item);

    int *arr = BinarytreeToArray(btree);

    for (int i = 0; i < btree->nodeCount; i++)
        printf("%d\n", arr[i]);

    DeleteBinaryTreeNode(btree,btree->root,item);


     arr = BinarytreeToArray(btree);

    for (int i = 0; i < btree->nodeCount; i++)
        printf("%d\n", arr[i]);

    return 0;
}