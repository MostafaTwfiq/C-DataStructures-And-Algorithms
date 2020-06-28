#ifndef C_DATASTRUCTURES_TRIE_H
#define C_DATASTRUCTURES_TRIE_H



#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"



typedef struct Trie {
    struct Node *root;

} Trie;




Trie *trieInitialization();


void trieAddWord(Trie *trie, char *word);


int trieContains(Trie *trie, char *word);


void trieRemoveWord(Trie *trie, char *word);


ArrayList *trieAutoCompletion(Trie *trie, char *word, int numOfSuggestion);


ArrayList *trieSuggestion(Trie *trie, char *word, int numOfSuggestion);


void triePrintAllWords(Trie *trie);


void clearTrie(Trie *trie);


void destroyTrie(Trie *trie);


#endif //C_DATASTRUCTURES_TRIE_H
