#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Headers/Trie.h"
#include "Headers/ArrayList.h"
#include "Headers/Heap.h"

int16_t mycmp(void * v1, void*v2){
    if(*(int*)(v1)>*(int*)(v2)){
        return 1;
    }
    else if(*(int*)(v1)<*(int*)(v2)) {
        return -1;
    }
}

void myPrint(void * var){
    printf("%d , ",*(int*)var);
}

int main() {
    Heap* h = HeapInitialize(MAX_HEAP,sizeof(int),mycmp);

    int a = 1,
     b =    2,
     c =    3,
     d =    4,
     e =    5,
     f =    6,
     g =    7,
     hi =   8,
     j =    9,
     k =   10;


    void    *p1=&a,
            *p2=&b,
            *p3=&c,
            *p4=&d,
            *p5=&e,
            *p6=&f,
            *p7=&g,
            *p8=&hi,
            *p9=&j,
            *p10=&k;


    insertInHeap(h,p1);
    insertInHeap(h,p3);
    insertInHeap(h,p5);
    insertInHeap(h,p7);
    insertInHeap(h,p9);

    insertInHeap(h,p2);
    insertInHeap(h,p4);
    insertInHeap(h,p6);
    insertInHeap(h,p8);
    insertInHeap(h,p10);



    //printf("%d",(h->cmp)(&p5,&p4));
    printHeap(h,myPrint);

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
