#include <stdio.h>
#include <stdlib.h>
#include "Headers/BinaryMinHeap.h"

int16_t mycmp(const void * v1,const void * v2){
    return  *(int *)v1 - *(int*)v2;
} 

void myPrint(void *val){
    printf("%d, ",*(int*)val );
}
int main() {
    BinaryMinHeap *h = MinHeapInitialize(sizeof(int), mycmp);

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

//3, 5, 6, 8, 2, 4, 7, 9, 10,
    insertInMinHeap(h, p1);
    insertInMinHeap(h, p3);
    insertInMinHeap(h, p5);
    insertInMinHeap(h, p7);
    insertInMinHeap(h, p9);

    insertInMinHeap(h, p2);
    insertInMinHeap(h, p4);
    insertInMinHeap(h, p6);
    insertInMinHeap(h, p8);
    insertInMinHeap(h, p10);

    int   array[10];
    void *varray[10];

    void *item;
    for(int o=0;o<10;o++){
        array[o] = 20+o;
        varray[o]= &array[o];
    }

    MinHeapAddAll(h,varray,10);

    //printf("%d",(h->cmp)(&p5,&p4));
    printMinHeap(h, myPrint);
    void * res;
    MinHeapDelete(h,&res);
    printMinHeap(h, myPrint);

/*
    Trie *trie = trieInitialization();

    trieAddWord(trie, "mostafa");

    //trieRemoveWord(trie, "mostafa");

    trieAddWord(trie, "mohammad");

    ArrayList *list = trieSuggestion(trie, "moytafa", 1);

    for (int i = 0; i < arrayListGetLength(list); i++) {
        char *word = arrayListGet(list, i);
        printf("%s\n", word);
    }*/

}