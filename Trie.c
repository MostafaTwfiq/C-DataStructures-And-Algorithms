#include "Trie.h"
#include "Headers/ArrayList.h"
#include "Headers/String.h"
#include <math.h>

char toLowerCase(char c);
Node *createNode(char value, int EOW);
void freeNode(Node *node);
int nodeHasChildren(Node *node);
Node *trieRemoveWordR(Node *root, const char *currentChar);
void trieAutoCompletionR(Node *root, String *string, ArrayList *wordsList, int numOfSuggestion);
void trieSuggestionR(Node *root, char *word, String *string, ArrayList *wordsList, int numOfSuggestion);
int *generateIndexes(char c);


Trie *trieInitialization() {
    Trie *trie = (Trie *) malloc(sizeof(Trie));

    trie->root = createNode('\0', 0);

    return trie;

}


void trieAddWord(Trie *trie, char *word) {

    if (trie == NULL) {
        fprintf(stderr, "Null pointer exception, the trie is null.");
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

int trieContains(Trie *trie, char *word) {

    if (trie == NULL) {
        fprintf(stderr, "Null pointer exception, the trie is null.");
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


void trieRemoveWord(Trie *trie, char *word) {

    if (trie == NULL) {
        fprintf(stderr, "Null pointer exception, the trie is null.");
        exit(-3);
    } else if (word == NULL)
        return;

    Node *root = trie->root;
    int index = toLowerCase(*word) - 'a';

    if (root->characters[index] != NULL)
        trieRemoveWordR(root->characters[index], word + 1);

}

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





ArrayList *trieAutoCompletion(Trie *trie, char *word, int numOfSuggestion) {

    if (trie == NULL) {
        fprintf(stderr, "Null pointer exception, the trie is null.");
        exit(-3);
    } else if (word == NULL)
        return NULL;

    char *currentChar = word;
    Node *root = trie->root;
    int index;

    String *string = stringInitialization(10);

    while (*currentChar != '\0') {
        index = toLowerCase(*currentChar) - 'a';

        if (root->characters[index] != NULL)
            root = root->characters[index];

        else
            break;

        stringAddCharAtLast(string, *currentChar);
        currentChar++;

    }

    ArrayList *wordsList = arrayListInitialization(numOfSuggestion, sizeof(char *));

    if (stringGetLength(string) != 0) {
        stringRemoveCharAtIndex(string, stringGetLength(string) - 1);
        trieAutoCompletionR(root, string, wordsList, numOfSuggestion);
    } else {
        for (int i = 0; i < 26; i++) {
            if (root->characters[i] != NULL)
                trieAutoCompletionR(root->characters[i], string, wordsList, numOfSuggestion);

        }
    }

    destroyString(string);
    return wordsList;

}

void trieAutoCompletionR(Node *root, String *string, ArrayList *wordsList, int numOfSuggestion) {
    stringAddCharAtLast(string, root->value);

    if (arrayListGetLength(wordsList) == numOfSuggestion)
        return;

    else if (root->EOW) {
        char *word = stringToArrayOfCharacters(string);
        arrayListAdd(wordsList, word);
    }

    for (int i = 0; i < 26; i++) {
        if (root->characters[i] != NULL)
            trieAutoCompletionR(root->characters[i], string, wordsList, numOfSuggestion);

    }

    stringRemoveCharAtIndex(string, stringGetLength(string) - 1);

}



ArrayList *trieSuggestion(Trie *trie, char *word, int numOfSuggestion) {
    String *string = stringInitialization(10);
    ArrayList *wordsList = arrayListInitialization(numOfSuggestion, sizeof(char *));

    trieSuggestionR(trie->root, word, string, wordsList, numOfSuggestion);
    destroyString(string);

    return wordsList;

}

void trieSuggestionR(Node *root, char *word, String *string, ArrayList *wordsList, int numOfSuggestion) {
    stringAddCharAtLast(string, root->value);

    if (*word == '\0') {

        if (arrayListGetLength(wordsList) == numOfSuggestion)
            return;

        else if (root->EOW) {
            if (stringGetCharAtIndex(string, 0) == '\0')
                stringRemoveCharAtIndex(string, 0);

            char *finalWord = stringToArrayOfCharacters(string);
            arrayListAdd(wordsList, finalWord);
        }

        for (int i = 0; i < 26; i++) {
            if (root->characters[i] != NULL)
                trieSuggestionR(root->characters[i], word, string, wordsList, numOfSuggestion);

        }

    } else {
        int index = toLowerCase(*word) - 'a';
        if (root->characters[index] != NULL) {
            trieSuggestionR(root->characters[index], word + 1, string, wordsList, numOfSuggestion);
        } else {
            int *indices = generateIndexes(toLowerCase(*word));

            for (int i = 0; i < 26; i++) {
                if (root->characters[indices[i]] != NULL)
                    trieSuggestionR(root->characters[indices[i]], word + 1, string, wordsList, numOfSuggestion);

            }

        }

    }

    if (stringGetLength(string) != 0)
        stringRemoveCharAtIndex(string, stringGetLength(string) - 1);

}




char toLowerCase(char c) {
    if (c >= 'A' && c <= 'Z')
        return (char) ((int) c + 32);


    return c;
}

int nodeHasChildren(Node *node) {
    for (int i = 0; i < 26; i++) {
        if (node->characters[i] != NULL)
            return 1;

    }

    return 0;
}

Node *createNode(char value, int EOW) {
    Node *node = (Node *) malloc(sizeof(Node));

    node->characters = (Node **) malloc(sizeof(void *) * 26);
    for (int i = 0; i < 26; i++)
        node->characters[i] = NULL;

    node->value = value;
    node->EOW = EOW;
}

void freeNode(Node *node) {
    free(node->characters);
    free(node);
}


typedef struct KeyHolder {

    char c;
    float weight;
} KeyHolder;


int comparator(const void *p1, const void *p2) {
    return (int) ceil(((KeyHolder *)p1)->weight - ((KeyHolder *)p2)->weight);
}

int *generateIndexes(char c) {
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
        if (row && col)
            break;

    }

    int keyIndex = 0;
    KeyHolder keys[26];
    int *arr = (int *) malloc(sizeof(int) * 26);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            if (matrix[i][j] == '\0')
                continue;

            keys[keyIndex].c = matrix[i][j];
            float pow1 = pow(i - row, 2);
            float pow2 = pow(j - col, 2);
            float root = sqrtf(pow1 + pow2);
            keys[keyIndex].weight = root;
           
        }
    }

    qsort(keys, 26, sizeof(KeyHolder), comparator);

    for (int i = 0; i < 26; i++) {
        arr[i] = keys[i].c - 'a';
    }

    return arr;


}