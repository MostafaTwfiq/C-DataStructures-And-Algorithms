#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Headers/Trie.h"
#include "Headers/ArrayList.h"
int main() {


    printf("%d", ceil(-0.5));

    Trie *trie = trieInitialization();

    trieAddWord(trie, "mostafa");

    //trieRemoveWord(trie, "mostafa");

    trieAddWord(trie, "mohammad");

    //triePrintAllWords(trie);

    /*ArrayList *list = try(trie, "", 10);

    for (int i = 0; i < arrayListGetLength(list); i++) {
        char *word = arrayListGet(list, i);
        printf("%s\n", word);
    }*/

}
