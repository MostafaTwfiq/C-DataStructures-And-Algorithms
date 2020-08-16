#include "../Headers/Trie.h"
#include "../../Lists/Headers/ArrayList.h"
#include "../../Strings/Headers/String.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"
#include <math.h>


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


/** This struct will be useful in generating the best sequence in suggesting the words.*/
typedef struct KeyHolder {

    char c;
    float weight;
} KeyHolder;


void freeFun(void *item);

char toLowerCase(char c);

TrieNode *createNode(char value, int EOW);

void freeNode(TrieNode *node);

int nodeHasChildren(TrieNode *node);

TrieNode *trieRemoveWordR(TrieNode *root, const char *currentChar);

void trieAutoCompletionR(TrieNode *root, char *currentChar, int numOfSuggestion, String *string, ArrayList *wordsList);

void trieSuggestionR(TrieNode *root, char *word, String *string, ArrayList *wordsList, int numOfSuggestion);

void triePrintAllWordsR(TrieNode *root, String *string, FILE *dir);

int *generateIndices(char c);

TrieNode *destroyTrieNodes(TrieNode *root);

int wordsComparator(const void *word1, const void *word2);


/** This function will initialize a new trie in the memory, and initialize it's fields then,
 * the function will return it's address.
 *
 * @return it will return the initialized trie address
 */

Trie *trieInitialization() {
    Trie *trie = (Trie *) malloc(sizeof(Trie));
    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "trie", "trie data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    trie->root = createNode('\0', 0);

    return trie;

}


/** This function will take the trie address, and the word  address as a parameters,
 * then it will add the word into the trie.
 *
 * @param trie the trie address
 * @param word the word address
 */

void trieAddWord(Trie *trie, char *word) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    } else if (word == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "word", "trie data structure");
        exit(INVALID_ARG);
#endif

    }

    char *currentChar = word;
    TrieNode *root = trie->root;
    int index;

    while (*currentChar != '\0') {
        index = toLowerCase(*currentChar) - 'a';

        if (index >= 0 && index < 26) {

            if (root->characters[index] != NULL)
                root = root->characters[index];

            else
                root = root->characters[index] = createNode(*currentChar, 0);

        }

        currentChar++;

    }

    root->EOW = 1;


}


/** This function will take the trie address, and the word address as a parameter,
 * then it  will return one (1) if the word is in the trie,
 * other wise it will return zero (0).
 *
 * @param trie the trie address
 * @param word the word address
 * @return it will return one if the word is in the trie, other wise it will return zero
 */

int trieContains(Trie *trie, char *word) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    } else if (word == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "word", "trie data structure");
        exit(INVALID_ARG);
#endif

    }

    char *currentChar = word;
    TrieNode *root = trie->root;

    while (*currentChar != '\0') {

        int index = toLowerCase(*currentChar) - 'a';

        if (index >= 0 && index < 26) {
            if (root->characters[index] != NULL)
                root = root->characters[toLowerCase(*currentChar) - 'a'];

            else
                return 0;
        }

        currentChar++;

    }

    return root->EOW;
}


/** This function will take the trie address, and the word address as a parameters,
 * then it will remove the given word from the trie.
 *
 * @param trie the trie address
 * @param word the word address
 */

void trieRemoveWord(Trie *trie, char *word) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    } else if (word == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "word", "trie data structure");
        exit(INVALID_ARG);
#endif

    }

    TrieNode *root = trie->root;
    int index = toLowerCase(*word) - 'a';

    if (index >= 0 && index < 26) {
        if (root->characters[index] != NULL)
            trie->root->characters[index] = trieRemoveWordR(root->characters[index], word + 1);

    }

}


/** This function takes the root node address, and the current char address as a parameters,
 * then it will remove the given word from the trie recursively.
 *
 * Note: this function will be only called from the trieRemoveWord function only.
 *
 * @param root the node address
 * @param currentChar the current char address
 * @return it will return the node address to it's parent
 */

TrieNode *trieRemoveWordR(TrieNode *root, const char *currentChar) {

    if (*currentChar == '\0') {
        if (root->EOW) {
            root->EOW = 0;
            if (!nodeHasChildren(root)) {
                freeNode(root);
                return NULL;
            }

        }

        return root;
    }

    int index = toLowerCase(*currentChar) - 'a';
    if (index < 0 || index >= 26) {
        return root;
    }

    if (root->characters[index] != NULL)
        root->characters[index] = trieRemoveWordR(root->characters[index], currentChar + 1);
    else
        return root;

    if (!nodeHasChildren(root) && !root->EOW) {
        freeNode(root);
        return NULL;
    }

    return root;
}


/** This function will be useful to initialize the array lists that will be returned to the user,
 * after suggesting the words.
 *
 * @param word1 the first word pointer
 * @param word2 the second word pointer
 * @return
 */

int wordsComparator(const void *word1, const void *word2) {
    return strcmp((char *) word1, (char *) word2);
}


/** This function will take the trie address, the word address, and the number of suggestion needed as a parameters,
 * then it will return and array list pointer that contains all the words.
 *
 * Note: if the given word is wrong Linguistically then,
 * the function will start to complete starts from the first wrong character.
 *
 * @param trie the trie address
 * @param word the word address
 * @param numOfSuggestion the number of wanted suggestion
 * @return it will return an ArrayList address consisting the suggested words
 */

ArrayList *trieAutoCompletion(Trie *trie, char *word, int numOfSuggestion) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    } else if (word == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "word", "trie data structure");
        exit(INVALID_ARG);
#endif

    } else if (numOfSuggestion <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "number of suggestions", "trie data structure");
        exit(INVALID_ARG);
#endif

    }

    ArrayList *wordsList = arrayListInitialization(numOfSuggestion, freeFun, wordsComparator);
    String *string = stringInitialization(10);
    trieAutoCompletionR(trie->root, word, numOfSuggestion, string, wordsList);

    destroyString(string);
    return wordsList;
}


/** This function will take the the root node, the current char address,
 * the number of needed suggestion words,
 * a string address, and an array list to put the words in it, as a parameters,
 * then it will fill the array list with the words.
 *
 * Note: this function should be  called by the trieAutoCompletion function only.
 *
 * @param root the node address
 * @param currentChar the current char address
 * @param numOfSuggestion the number of wanted suggestions
 * @param string an initialized String address
 * @param wordsList an initialized ArrayList address
 */

void trieAutoCompletionR(TrieNode *root, char *currentChar, int numOfSuggestion, String *string, ArrayList *wordsList) {
    if (root->value != '\0')
        stringAppendChar(string, root->value);

    if (arrayListGetLength(wordsList) == numOfSuggestion)
        return;
    else if (root->EOW && *currentChar == '\0') {
        char *word = stringToCharArray(string);
        arrayListAdd(wordsList, word);
    }

    int index = toLowerCase(*currentChar) - 'a';

    if (*currentChar != '\0' && root->characters[index] != NULL) {
        trieAutoCompletionR(root->characters[index], currentChar + 1, numOfSuggestion, string, wordsList);
    } else {
        for (int i = 0; i < 26; i++) {
            if (root->characters[i] != NULL) {
                trieAutoCompletionR(root->characters[i], "\0", numOfSuggestion, string, wordsList);
            }
        }
    }

    if (stringGetLength(string) != 0)
        stringRemove(string, stringGetLength(string) - 1);

}


/** This function will take the trie address, the word address, the number of needed words to be suggested as a parameters,
 * then it will return an array list that contains the suggested words.
 *
 * @param trie the trie address
 * @param word the word address
 * @param numOfSuggestion the number of wanted suggestion
 * @return it will return an array list consisting of the suggested words
 */

ArrayList *trieSuggestion(Trie *trie, char *word, int numOfSuggestion) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    } else if (word == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "word", "trie data structure");
        exit(INVALID_ARG);
#endif

    } else if (numOfSuggestion <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "number of suggestions", "trie data structure");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);
    ArrayList *wordsList = arrayListInitialization(numOfSuggestion, freeFun, wordsComparator);


    trieSuggestionR(trie->root, word, string, wordsList, numOfSuggestion);


    destroyString(string);

    return wordsList;

}


/** This function will take the root node address, the words address, string address, array list address,
 * and the number of words thar needed to be suggested as a parameter,
 * then it will fill the array list with the words.
 *
 * Note: this function should only be called by the trieSuggestion function.
 *
 * @param root the node address
 * @param word the word address
 * @param string an initialized String address
 * @param wordsList an initialized ArrayList address
 * @param numOfSuggestion the number of wanted suggestion
 */

void trieSuggestionR(TrieNode *root, char *word, String *string, ArrayList *wordsList, int numOfSuggestion) {
    if (root->value != '\0')
        stringAppendChar(string, root->value);

    if (*word == '\0') {
        if (arrayListGetLength(wordsList) == numOfSuggestion)
            return;
        else if (root->EOW) {
            char *finalWord = stringToCharArray(string);
            arrayListAdd(wordsList, finalWord);
        }
    }

    int *indices = generateIndices(toLowerCase(*word));
    if (indices == NULL)
        return;

    for (int i = 0; i < 26; i++) {
        if (root->characters[indices[i]] != NULL)
            trieSuggestionR(root->characters[indices[i]], word + (*word == '\0' ? 0 : 1), string, wordsList,
                            numOfSuggestion);

    }

    free(indices);
    if (stringGetLength(string) != 0)
        stringRemove(string, stringGetLength(string) - 1);

}


/** This function will take the trie address as a parameter,
 * then it will print all the words in the trie.
 *
 * @param trie the trie address
 * @param dir the file pointer that the words will be printed in it
 */

void triePrintAllWords(Trie *trie, FILE *dir) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    } else if (dir == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "file pointer", "trie data structure");
        exit(INVALID_ARG);
#endif

    }

    String *string = stringInitialization(10);

    for (int i = 0; i < 26; i++) {

        if (trie->root->characters[i] != NULL)
            triePrintAllWordsR(trie->root->characters[i], string, dir);

    }

    destroyString(string);

}


/** This function will take the root node address, and a string address as a parameter,
 * then it will print all the words in the trie.
 *
 * Note: this function should only be called from the triePrintAllWords function.
 *
 * @param root the node address
 * @param string an initialized String address
 * @param dir the file pointer that the words will be  printed in it
 */

void triePrintAllWordsR(TrieNode *root, String *string, FILE *dir) {
    stringAppendChar(string, root->value);

    if (root->EOW) {
        printString(string, dir);
        fprintf(dir, "\n");
    }

    for (int i = 0; i < 26; i++) {
        if (root->characters[i] != NULL)
            triePrintAllWordsR(root->characters[i], string, dir);

    }

    stringRemove(string, stringGetLength(string) - 1);

}


/** This function will take the trie address as a parameter,
 * then it will clear and free all the trie nodes,
 * without destroying the trie.
 *
 * @param trie the trie address
 */

void clearTrie(Trie *trie) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < 26; i++) {
        if (trie->root->characters[i] != NULL)
            trie->root->characters[i] = destroyTrieNodes(trie->root->characters[i]);

    }

}


/** This function will take the trie address as a parameter,
 * then it will destroy and free the trie and all it's nodes.
 *
 * @param trie the trie address
 */

void destroyTrie(void *trie) {

    if (trie == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "trie", "trie data structure");
        exit(NULL_POINTER);
#endif

    }

    Trie *trieToFree = (Trie *) trie;
    trieToFree->root = destroyTrieNodes(trieToFree->root);
    free(trie);
}


/** This function takes the root node address as a parameter,
 * then it will destroy and free all the nodes.
 *
 * Note: This should only be called from the clearTrie and destroyTrie functions.
 *
 * @param root the node address
 * @return it will return NULL to the node parent
 */

TrieNode *destroyTrieNodes(TrieNode *root) {
    for (int i = 0; i < 26; i++) {
        if (root->characters[i] != NULL)
            root->characters[i] = destroyTrieNodes(root->characters[i]);

    }

    freeNode(root);

    return NULL;
}


/** This function takes a character as a parameter,
 * then it will return the lower case of the of the character if it's an alphabet.
 *
 * Note: this function private to be used by the tries function only.
 *
 * @param c the character
 * @return it will return the character in lower case
 */

char toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z')
        return (char) ((int) c + 32);


    return c;
}


/** This function will take a node address as a parameter,
 * then it will return one (1) if the node has al least one child,
 * other wise it will return zero (0).
 *
 * Note: This function is private to be used by the trie functions only.
 *
 * @param node the node address
 * @return it will return one if the node hash children, other wise it will return zero
 */

int nodeHasChildren(TrieNode *node) {
    for (int i = 0; i < 26; i++) {
        if (node->characters[i] != NULL)
            return 1;

    }

    return 0;
}


/** This function will take a character, and an end of word boolean as a parameters,
 * then it will return a new node address that has been initialized with the passed values.
 *
 * Note: this function should be only called from the inside of the trie.
 *
 * @param value the node character
 * @param EOW the end of word boolean
 * @return it will return a new initialized node address
 */

TrieNode *createNode(char value, int EOW) {
    TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
    if (node == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "trie data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    node->characters = (TrieNode **) calloc(sizeof(void *), 26);
    if (node->characters == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node characters array", "trie data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    node->value = value;
    node->EOW = EOW;

    return node;

}


/** This function will take a node address as a parameter,
 * then it will destroy and free that node.
 *
 * Note: this function should be only called from the inside if the trie.
 *
 * @param node the node address
 */

void freeNode(TrieNode *node) {
    free(node->characters);
    free(node);
}


/** This function is useful for the generateIndices function, to sort the keyHolder array*/

int comparator(const void *p1, const void *p2) {
    float subVal = ((KeyHolder *) p1)->weight - ((KeyHolder *) p2)->weight;
    return subVal >= 0 ? (int) ceilf(subVal) : (int) floorf(subVal);
}


/** This function will take a character as a parameter,
 * then it will generate a list of indices that depends on the distance between keys in the keyboard,
 * and return it as an integer array.
 *
 * @param c the character value
 * @return it will return an array of indices
 */

int *generateIndices(char c) {
    int *arr = (int *) malloc(sizeof(int) * 26);

    if (c == '\0') {
        for (int i = 0; i < 26; i++)
            arr[i] = i;

        return arr;
    } else if (!(c >= 'a' && c <= 'z')) {
        return NULL;
    }

    char matrix[3][10] = {
            {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',  'o',  'p'},
            {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k',  'l',  '\0'},
            {'z', 'x', 'c', 'v', 'b', 'n', 'm', '\0', '\0', '\0'}
    };

    int row = 0, col = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (matrix[i][j] == c) {
                row = i;
                col = j;
                break;
            }
        }
        if (row && col || (!row && !col && c == 'q'))
            break;

    }

    int keyIndex = 0;
    KeyHolder keys[26];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (matrix[i][j] == '\0')
                continue;

            keys[keyIndex].c = matrix[i][j];
            float pow1 = powf((float) i - (float) row, 2);
            float pow2 = powf((float) j - (float) col, 2);
            float root = sqrtf(pow1 + pow2);
            keys[keyIndex++].weight = root;

        }
    }

    qsort(keys, 26, sizeof(KeyHolder), comparator);

    for (int i = 0; i < 26; i++) {
        arr[i] = keys[i].c - 'a';
    }

    return arr;

}


/** The free function that will free the words in the array list that will be returned to the user,
 * holding the suggested words.
 */

void freeFun(void *item) {
    free((char *) item);
}