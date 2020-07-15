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

int comp(const void *p1, int s1, const void *p2, int s2) {
    return strcmp((char *)p1, (char *)p2);
}

void print(void *item) {
    printf("%d\n", *((int*)((ArrayDequeItem*)item)->value));
}

int main() {
    ArrayDeque *ad  = ArrayDequeInitialize(10,free);
    int a=1;
    ArrayDequeItem *i1 = ArrayDequeNewItem(4,&a);
    ArrayDequeInsertFront(ad,i1);
    int b=2;
     i1 = ArrayDequeNewItem(4,&b);
    ArrayDequeInsertFront(ad,i1);
    int c=3;
     i1 = ArrayDequeNewItem(4,&c);
    ArrayDequeInsertFront(ad,i1);
    int d=4;
     i1 = ArrayDequeNewItem(4,&d);
    ArrayDequeInsertFront(ad,i1);
    int e=5;
     i1 = ArrayDequeNewItem(4,&e);
    ArrayDequeInsertFront(ad,i1);
    int f=6;
     i1 = ArrayDequeNewItem(4,&f);
    ArrayDequeInsertFront(ad,i1);
    int g=7;
     i1 = ArrayDequeNewItem(4,&g);
    ArrayDequeInsertFront(ad,i1);

    ArrayDequePrint(ad,print);
    return 0;

}