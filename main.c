#include <stdio.h>
#include <stdlib.h>
#include "Headers/RedBlackTree.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BOLD_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BOLD_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BOLD_YELLOW  "\x1b[01;33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_BOLD_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BOLD_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BOLD_CYAN    "\x1b[1;36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int cmp(const void *p1, const void *p2) {
    return *(int *)p1 - *(int *)p2;
}

void printFun(const void *item, COLOR color) {
    if (color == RED)
        printf(ANSI_COLOR_RED);
    else
        printf(ANSI_COLOR_WHITE);

    printf("%d -- Parent: %d\n" ANSI_COLOR_RESET, *(int *)((RBNode *)item)->key, ((RBNode *)((RBNode *)item)->parent) != NULL ? *(int *)((RBNode *)((RBNode *)item)->parent)->key : 0);
}

int main() {
    RBTree *tree = redBlackTreeInitialization(sizeof(int), cmp);

    int *item;

    item = (int *) malloc(sizeof(int ));
    *item = 13;
    rBTreeInsert(tree, (void *) item);

    item = (int *) malloc(sizeof(int ));
    *item = 8;
    rBTreeInsert(tree, (void *) item);

    item = (int *) malloc(sizeof(int ));
    *item = 17;
    rBTreeInsert(tree, (void *) item);

    item = (int *) malloc(sizeof(int ));
    *item = 1;
    rBTreeInsert(tree, (void *) item);

    item = (int *) malloc(sizeof(int ));
    *item = 11;
    rBTreeInsert(tree, (void *) item);

    item = (int *) malloc(sizeof(int ));
    *item = 6;
    rBTreeInsert(tree, (void *) item);

    item = (int *) malloc(sizeof(int ));
    *item = 15;
    rBTreeInsert(tree, (void *) item);

    item = (int *) malloc(sizeof(int ));
    *item = 25;
    rBTreeInsert(tree, (void *) item);

    printf("\n\n");
    item = (int *) malloc(sizeof(int ));
    *item = 22;
    rBTreeInsert(tree, (void *) item);
    //RBTreePrint(tree->root,myPrint);printf("\n\n");

    item = (int *) malloc(sizeof(int ));
    *item = 27;
    rBTreeInsert(tree, (void *) item);
    rBPreOrderTraversal(tree, printFun);
    printf("\n\n");

    item = (int *) malloc(sizeof(int ));
    *item = 8;
    rBTreeDelete(tree, (void *) item);

    rBPreOrderTraversal(tree, printFun);
    return 0;

}