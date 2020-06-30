#include <stdio.h>
#include <stdlib.h>
#include "Headers/SplayTree.h"

int16_t mycmp(const void * v1,const void * v2){
    return  *(int *)v1 - *(int*)v2;
}

void myPrint(void *val){
    printf("%d, ",*(int*)val );
}
int main() {
    SplayTree* st = SplayTreeInitialize(sizeof(int),mycmp);

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


    SplayTreeInsert(st,p1);
    SplayTreeInsert(st,p2);
    SplayTreeInsert(st,p3);
    SplayTreeInsert(st,p4);
    SplayTreeInsert(st,p5);
    SplayTreeInsert(st,p6);
    SplayTreeInsert(st,p7);
    SplayTreeInsert(st,p8);
    SplayTreeInsert(st,p9);
    SplayTreeInsert(st,p10);

    printInOrderSplayTree(st->root,myPrint);
    puts("\n");
    printSplayTree(st->root,myPrint);
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