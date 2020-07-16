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
    printf("%d->", *(int*)item);
}

int main() {
    ArrayDeque *ad  = ArrayDequeInitialize(3);

    printf("size %d\n",ArrayDequeLength(ad));

    int a=1;
    ArrayDequeInsertFront(ad,&a);
    printf("size %d\n",ArrayDequeLength(ad));

    int b=2;
    ArrayDequeInsertFront(ad,&b);
    printf("size %d\n",ArrayDequeLength(ad));

    int c=3;
    ArrayDequeInsertFront(ad,&c);
    printf("size %d\n",ArrayDequeLength(ad));

    int d=4;
    ArrayDequeInsertFront(ad,&d);
    printf("size %d\n",ArrayDequeLength(ad));

    int e=5;
    ArrayDequeInsertFront(ad,&e);
    printf("size %d\n",ArrayDequeLength(ad));

    int f=6;
    ArrayDequeInsertFront(ad,&f);
    printf("size %d\n",ArrayDequeLength(ad));

    int g=7;
    ArrayDequeInsertFront(ad,&g);
    printf("size %d\n",ArrayDequeLength(ad));

    int h=8;
    ArrayDequeInsertFront(ad,&h);
    printf("size %d\n",ArrayDequeLength(ad));

    int i=9;
    ArrayDequeInsertRear(ad,&i);
    printf("size %d\n",ArrayDequeLength(ad));

    int j=10;
    ArrayDequeInsertRear(ad,&j);
    printf("size %d\n",ArrayDequeLength(ad));

    int k=11;
    ArrayDequeInsertRear(ad,&k);
    printf("size %d\n",ArrayDequeLength(ad));

    int l=12;
    ArrayDequeInsertRear(ad,&l);
    printf("size %d\n",ArrayDequeLength(ad));

    //ad->front=6;
    ArrayDequePrint(ad,print);

    return 0;

}