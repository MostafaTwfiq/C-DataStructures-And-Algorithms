#ifndef C_DATASTRUCTURES_TRIE_H
#define C_DATASTRUCTURES_TRIE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef CU_TEST_H

/** @struct Node
*  @brief This structure implements a basic trie node.
*  @var Trie::characters
*  Member 'characters' is a pointer to characters nodes array.
*  @var Trie::value
*  Member 'value' holds the nodes value.
*  @var Trie::EOW
*  Member 'EOW' is a boolean to hold if  the node us an end of a word or not.
*/

typedef struct TrieNode {

    struct TrieNode **characters;
    char value;
    int EOW;

} TrieNode;

#else
#endif

/** @struct Trie
*  @brief This structure implements a basic Trie.
*  @var Trie::root
*  Member 'root' is a pointer to the root node.
*/

typedef struct Trie {
    struct TrieNode *root;
} Trie;

Trie *trieInitialization();

void trieAddWord(Trie *trie, char *word);

int trieContains(Trie *trie, char *word);

void trieRemoveWord(Trie *trie, char *word);

struct ArrayList *trieAutoCompletion(Trie *trie, char *word, int numOfSuggestion);

struct ArrayList *trieSuggestion(Trie *trie, char *word, int numOfSuggestion);

void triePrintAllWords(Trie *trie, FILE *dir);

void clearTrie(Trie *trie);

void destroyTrie(void *trie);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_TRIE_H