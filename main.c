#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

#include "Headers/ArrayDeque.h"

void freeItem(void *item) {
    free(item);
}

int comp(const void *p1, const void *p2) {
    return *(int *)p1 - *(int *)p2;
}

void print(void *item) {

}

int main(){
    ArrayDeque  *arrayDeque = ArrayDequeInitialize(freeItem);

    int *item;

    item = (int *) malloc(sizeof(int));
    *item = 20;
    ArrayDequeInsertFront(arrayDeque, item);

    item = (int *) malloc(sizeof(int));
    *item = 10;
    ArrayDequeInsertFront(arrayDeque, item);

    item = (int *) malloc(sizeof(int));
    *item = 30;
    ArrayDequeInsertRear(arrayDeque, item);

    item = (int *) malloc(sizeof(int));
    *item = 40;
    ArrayDequeInsertRear(arrayDeque, item);


    while (!ArrayDequeIsEmpty(arrayDeque)) {
        printf("%d\n", *(int *)ArrayDequeGetFront(arrayDeque));
        printf("%d\n", *(int *)ArrayDequeGetRear(arrayDeque));
    }
    return 0;

}