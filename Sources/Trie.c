#include "../Headers/Trie.h"
#include "../Headers/ArrayList.h"
#include "../Headers/String.h"
#include <math.h>

typedef struct Node {

    struct Node **characters;
    char value;
    int EOW;

} Node;


/** This struct will be useful in generating the best sequence in suggesting the words.*/
typedef struct KeyHolder {

    char c;
    float weight;
} KeyHolder;


char toLowerCase(char c);

Node *createNode(char value, int EOW);

void freeNode(Node *node);

int nodeHasChildren(Node *node);

Node *trieRemoveWordR(Node *root, const char *currentChar);

void trieAutoCompletionR(Node *root, char *currentChar, int numOfSuggestion, String *string, ArrayList *wordsList);

void trieSuggestionR(Node *root, char *word, String *string, ArrayList *wordsList, int numOfSuggestion);

void triePrintAllWordsR(Node *root, String *string);

int *generateIndexes(char c);

Node *destroyTrieNodes(Node *root);






/** This function will initialize a new trie in the memory, and initialize it's fields then,
    the function will return it's address.
 * @return
 */

Trie *trieInitialization() {
    Trie *trie = (Trie *) malloc(sizeof(Trie));

    trie->root = createNode('\0', 0);

    return trie;

}







/** This function will take the trie address, and the word  address as a parameters,
 * then it will add the word into the trie.
 * @param trie
 * @param word
 */

void trieAddWord(Trie *trie, char *word) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    } else if (word == NULL)
        return;

    char *currentChar = word;
    Node *root = trie->root;
    int index;

    while (*currentChar != '\0') {
        index = toLowerCase(*currentChar) - 'a';

        if (root->characters[index] != NULL)
            root = root->characters[index];

        else
            root = root->characters[index] = createNode(*currentChar, 0);


        currentChar++;

    }

    root->EOW = 1;


}





/** This function will take the trie address, and the word address as a parameter,
    then it  will return one (1) if the word is in the trie,
    other wise it will return zero (0).
 * @param trie
 * @param word
 * @return
 */

int trieContains(Trie *trie, char *word) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    } else if (word == NULL)
        return 0;

    char *currentChar = word;
    Node *root = trie->root;

    while (*currentChar != '\0') {

        if (root->characters[toLowerCase(*currentChar) - 'a'] != NULL)
            root = root->characters[toLowerCase(*currentChar) - 'a'];

        else
            return 0;

        currentChar++;

    }

    return root->EOW;
}






/** This function will take the trie address, and the word address as a parameters,
    then it will remove the given word from the trie.
 * @param trie
 * @param word
 */

void trieRemoveWord(Trie *trie, char *word) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    } else if (word == NULL)
        return;

    Node *root = trie->root;
    int index = toLowerCase(*word) - 'a';

    if (root->characters[index] != NULL)
        trie->root->characters[index] = trieRemoveWordR(root->characters[index], word + 1);

}





/** This function takes the root node address, and the current char address as a parameters,
    then it will remove the given word from the trie recursively.
 * Note: this function will be only called from the trieRemoveWord function only.
 * @param root
 * @param currentChar
 * @return
 */

Node *trieRemoveWordR(Node *root, const char *currentChar) {
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






/** This function will take the trie address, the word address, and the number of suggestion needed as a parameters,
    then it will return and array list pointer that contains all the words.
 * Note: if the given word is wrong Linguistically then,
   the function will start to complete starts from the first wrong character.
 * @param trie
 * @param word
 * @param numOfSuggestion
 * @return
 */

ArrayList *trieAutoCompletion(Trie *trie, char *word, int numOfSuggestion) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    } else if (word == NULL)
        return NULL;

    ArrayList *wordsList = arrayListInitialization(numOfSuggestion, sizeof(char *));
    String *string = stringInitialization(10);
    trieAutoCompletionR(trie->root, word, numOfSuggestion, string, wordsList);

    destroyString(string);
    return wordsList;
}







/** This function will take the the root node, the current char address,
    the number of needed suggestion words,
    a string address, and an array list to put the words in it, as a parameters,
    then it will fill the array list with the words.
 * Note: this function should be  called by the trieAutoCompletion function only.
 * @param root
 * @param currentChar
 * @param numOfSuggestion
 * @param string
 * @param wordsList
 */

void trieAutoCompletionR(Node *root, char *currentChar, int numOfSuggestion, String *string, ArrayList *wordsList) {
    if (root->value != '\0')
        stringAddCharAtLast(string, root->value);

    if (arrayListGetLength(wordsList) == numOfSuggestion)
        return;
    else if (root->EOW && *currentChar == '\0') {
        char *word = stringToArrayOfCharacters(string);
        arrayListAdd(wordsList, word);
    }

    int index = toLowerCase(*currentChar) - 'a';
    if (*currentChar!= '\0' && root->characters[index] != NULL) {
        trieAutoCompletionR(root->characters[index], currentChar + 1, numOfSuggestion, string, wordsList);
    } else {
        for (int i = 0; i < 26; i++) {
            if (root->characters[i] != NULL) { trieAutoCompletionR(root->characters[i], "\0", numOfSuggestion, string, wordsList); }
        }
    }

    if (stringGetLength(string) != 0)
        stringRemoveCharAtIndex(string, stringGetLength(string) - 1);

}






/** This function will take the trie address, the word address, the number of needed words to be suggested as a parameters,
 * then it will return an array list that contains the suggested words.
 * @param trie
 * @param word
 * @param numOfSuggestion
 * @return
 */

ArrayList *trieSuggestion(Trie *trie, char *word, int numOfSuggestion) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    } else if (word == NULL)
        return NULL;

    String *string = stringInitialization(10);
    ArrayList *wordsList = arrayListInitialization(numOfSuggestion, sizeof(char *));


    trieSuggestionR(trie->root, word, string, wordsList, numOfSuggestion);


    destroyString(string);

    return wordsList;

}






/** This function will take the root node addres, the words address, string address, array list address,
    and the number of words thar needed to be suggested as a parameter,
    then it will fill the array list with the words.
 * Note: this function should only be called by the trieSuggestion function.
 * @param root
 * @param word
 * @param string
 * @param wordsList
 * @param numOfSuggestion
 */

void trieSuggestionR(Node *root, char *word, String *string, ArrayList *wordsList, int numOfSuggestion) {
    if (root->value != '\0')
        stringAddCharAtLast(string, root->value);

    if (*word == '\0') {
        if (arrayListGetLength(wordsList) == numOfSuggestion)
            return;
        else if (root->EOW) {
            char *finalWord = stringToArrayOfCharacters(string);
            arrayListAdd(wordsList, finalWord);
        }
    }

    int *indices = generateIndexes(toLowerCase(*word));
    for (int i = 0; i < 26; i++) {
        if (root->characters[indices[i]] != NULL)
            trieSuggestionR(root->characters[indices[i]], word + (*word == '\0' ? 0 : 1) , string, wordsList, numOfSuggestion);

    }

    free(indices);
    if (stringGetLength(string) != 0)
        stringRemoveCharAtIndex(string, stringGetLength(string) - 1);

}






/** This function will take the trie address as a parameter,
 * then it will print all the words in the trie.
 * @param trie
 */

void triePrintAllWords(Trie *trie) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    }

    String *string = stringInitialization(10);

    for (int i = 0; i < 26; i++) {

        if (trie->root->characters[i] != NULL)
            triePrintAllWordsR(trie->root->characters[i], string);

    }

    destroyString(string);
}






/** This function will take the root node address, and a string address as a parameter,
 * then it will print all the words in the trie.
 * Note: this function should only be called from the triePrintAllWords function.
 * @param root
 * @param string
 */

void triePrintAllWordsR(Node *root, String *string) {
    stringAddCharAtLast(string, root->value);

    if (root->EOW) {
        printString(string);
        printf("\n");
    }

    for (int i = 0; i < 26; i++) {
        if (root->characters[i] != NULL)
            triePrintAllWordsR(root->characters[i], string);

    }

    stringRemoveCharAtIndex(string, stringGetLength(string) - 1);

}





/** This function will take the trie address as a parameter,
    then it will clear and free all the trie nodes,
    without destroying the trie.
 * @param trie
 */

void clearTrie(Trie *trie) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    }

    for (int i = 0; i < 26; i++) {
        if (trie->root->characters[i] != NULL)
            trie->root->characters[i] = destroyTrieNodes(trie->root->characters[i]);

    }

}





/** This function will take the trie address as a parameter,
    then it will destroy and free the trie and all it's nodes.
 * @param trie
 */

void destroyTrie(Trie *trie) {

    if (trie == NULL) {
        fprintf(stderr, "Illegal argument, the trie is null.");
        exit(-3);
    }

    trie->root = destroyTrieNodes(trie->root);
    free(trie);
}







/** This function takes the root node address as a parameter,
    then it will destroy and free all the nodes.
 * Note: This should only be called from the clearTrie and destroyTrie functions.
 * @param root
 * @return
 */

Node *destroyTrieNodes(Node *root) {
    for (int i = 0; i < 26; i++) {
        if (root->characters[i] != NULL)
            root->characters[i] = destroyTrieNodes(root->characters[i]);

    }

    freeNode(root);

    return NULL;
}



/** This function takes a character as a parameter,
    then it will return the lower case of the of the character if it's an alphabet.
    Note: this function private to be used by the tries function only.
 * @param c
 * @return
 */

char toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z')
        return (char) ((int) c + 32);


    return c;
}




/** This function will take a node address as a parameter,
    then it will return one (1) if the node has al least one child,
    other wise it will return zero (0).
 * Note: This function is private to be used by the trie functions only.
 * @param node
 * @return
 */

int nodeHasChildren(Node *node) {
    for (int i = 0; i < 26; i++) {
        if (node->characters[i] != NULL)
            return 1;

    }

    return 0;
}






/** This function will take a character, and an end of word boolean as a parameters,
    then it will return a new node address that has been initialized with the passed values.
 * Note: this function should be only called from the inside of the trie.
 * @param value
 * @param EOW
 * @return
 */

Node *createNode(char value, int EOW) {
    Node *node = (Node *) malloc(sizeof(Node));

    node->characters = (Node **) malloc(sizeof(void *) * 26);
    for (int i = 0; i < 26; i++)
        node->characters[i] = NULL;

    node->value = value;
    node->EOW = EOW;
}





/** This function will take a node address as a parameter,
    then it will destroy and free that node.
 * Note: this function should be only called from the inside if the trie.
 * @param node
 */

void freeNode(Node *node) {
    free(node->characters);
    free(node);
}




/** This function is useful for the generateIndexes function, to sort the keyHolder array*/
int comparator(const void *p1, const void *p2) {
    float subVal = ((KeyHolder *)p1)->weight - ((KeyHolder *)p2)->weight;
    return subVal >= 0 ? (int) ceilf(subVal) : (int) floorf(subVal);
}





/** This function will take a character as a parameter,
 * then it will generate a list of indices that depends on the distance between keys in the keyboard,
 * and return it as an integer array.
 * @param c
 * @return
 */

int *generateIndexes(char c) {
    int *arr = (int *) malloc(sizeof(int) * 26);

    if (c == '\0') {
        for (int i = 0; i < 26; i++)
            arr[i] = i;

        return arr;
    }

    char matrix[3][10] = {
            {'q' , 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
            {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\0'},
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
        if (row && col || (!row && !col && c == 'q') )
            break;

    }

    int keyIndex = 0;
    KeyHolder keys[26];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (matrix[i][j] == '\0')
                continue;

            keys[keyIndex].c = matrix[i][j];
            float pow1 = pow(i - row, 2);
            float pow2 = pow(j - col, 2);
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