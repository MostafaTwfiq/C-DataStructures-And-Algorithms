#ifndef C_DATASTRUCTURES_TRIE_H
#define C_DATASTRUCTURES_TRIE_H

#include "../Headers/ArrayList.h"

typedef struct Node {

    struct Node **characters;
    char value;
    int EOW;

} Node;

typedef struct Trie {
    Node *root;

} Trie;


Trie *trieInitialization();
void trieAddWord(Trie *trie, char *word);
int trieContains(Trie *trie, char *word);
void trieRemoveWord(Trie *trie, char *word);
ArrayList *trieAutoCompletion(Trie *trie, char *word, int numOfSuggestion);
ArrayList *trieSuggestion(Trie *trie, char *word, int numOfSuggestion);

#endif //C_DATASTRUCTURES_TRIE_H
