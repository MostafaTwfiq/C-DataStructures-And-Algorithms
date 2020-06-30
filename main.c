#include <stdio.h>
#include <stdlib.h>
#include "Headers/ArrayDeque.h"

int16_t mycmp(const void * v1,const void * v2){
    return  *(int *)v1 - *(int*)v2;
}

void myPrint(void *val){
    printf("%d, ",*(int*)val );
}
int main() {


    int a = 1,
            b = 2,
            c = 3,
            d = 4,
            e = 5,
            f = 6,
            g = 7,
            hi = 8,
            j = 9,
            k = 10;


    void *p1 = &a,
            *p2 = &b,
            *p3 = &c,
            *p4 = &d,
            *p5 = &e,
            *p6 = &f,
            *p7 = &g,
            *p8 = &hi,
            *p9 = &j,
            *p10 = &k;

    ArrayDeque *dq = ArrayDequeInitialize(12);
    ArrayDequeInsertRear(dq,p1);
    ArrayDequeInsertRear(dq,p3);
    ArrayDequeInsertRear(dq,p5);
    ArrayDequeInsertRear(dq,p7);
    ArrayDequeInsertRear(dq,p9);

    ArrayDequeInsertFront(dq,p2);
    ArrayDequeInsertFront(dq,p4);
    ArrayDequeInsertFront(dq,p6);
    ArrayDequeInsertFront(dq,p8);
    ArrayDequeInsertFront(dq,p10);
    //ArrayDequeDeleteRear(dq);
    ArrayDequeInsertFront(dq,p8);
    //ArrayDequeDeleteFront(dq);

    ArrayDequePrint(dq,myPrint);

    return 0;
}