#include "TrieTest.h"
#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Trees/Headers/Trie.h"
#include "../../../../../DataStructure/Lists/Headers/ArrayList.h"


int hasNoChildrenTrT(TrieNode *node) {

    for (int i = 0; i < 26; i++) {

        if (node->characters[i] != NULL)
            return 0;

    }

    return 1;

}


int checkOnlyWordCharactersExistInTheArrTrT(const int *arr, char *word) {

    for (int i = 0; i < 26; i++) {
        char *tempPointer = word;
        int isIndexFlag = 0;
        while (*tempPointer != '\0') {

            if (*tempPointer - 'a' == i) {
                isIndexFlag = 1;
                break;
            }

            tempPointer++;

        }

        if ((!isIndexFlag && arr[i] != 0) || (isIndexFlag && arr[i] == 0))
            return 0;

    }

    return 1;

}


void testValidTrieInitialization(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    CuAssertPtrNotNull(cuTest, trie);

    destroyTrie(trie);

}


void testTrieAddWord(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    trieAddWord(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    trieAddWord(trie, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");

    int indicesArr[] = {'w' - 'a', 'o' - 'a', 'r' - 'a', 'd' - 'a'};
    int charactersCounterArr[26] = {0};

    TrieNode *tempNode = trie->root;
    int index = 0;

    while (!hasNoChildrenTrT(tempNode)) {
        CuAssertPtrNotNull(cuTest, tempNode);
        tempNode = tempNode->characters[indicesArr[index++]];
        charactersCounterArr[tempNode->value - 'a']++;
    }

    CuAssertIntEquals(cuTest, 1, tempNode->EOW);
    CuAssertIntEquals(cuTest, 1, checkOnlyWordCharactersExistInTheArrTrT(charactersCounterArr, "word"));


    trieAddWord(trie, "worm");

    int indicesArr2[] = {'w' - 'a', 'o' - 'a', 'r' - 'a', 'm' - 'a'};
    int charactersCounterArr2[26] = {0};

    tempNode = trie->root;
    index = 0;

    while (!hasNoChildrenTrT(tempNode)) {
        CuAssertPtrNotNull(cuTest, tempNode);
        tempNode = tempNode->characters[indicesArr2[index++]];
        charactersCounterArr2[tempNode->value - 'a']++;
    }

    CuAssertIntEquals(cuTest, 1, tempNode->EOW);
    CuAssertIntEquals(cuTest, 1, checkOnlyWordCharactersExistInTheArrTrT(charactersCounterArr2, "worm"));


    destroyTrie(trie);

}


void testTrieContains(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    trieContains(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    trieContains(trie, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");
    trieAddWord(trie, "world");
    trieAddWord(trie, "soon");
    trieAddWord(trie, "stole");
    trieAddWord(trie, "cold");
    trieAddWord(trie, "cat");
    trieAddWord(trie, "cart");

    CuAssertIntEquals(cuTest, 1, trieContains(trie, "word"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "world"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "soon"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "stole"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "cold"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "cat"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "cart"));

    CuAssertIntEquals(cuTest, 0, trieContains(trie, "worm"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "worst"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "sole"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "cool"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "card"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, ""));


    destroyTrie(trie);

}


void testTrieRemoveWord(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    trieRemoveWord(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    trieRemoveWord(trie, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");
    trieAddWord(trie, "world");
    trieAddWord(trie, "soon");
    trieAddWord(trie, "stole");
    trieAddWord(trie, "cold");
    trieAddWord(trie, "cat");
    trieAddWord(trie, "cart");

    trieAddWord(trie, "worm");
    trieAddWord(trie, "worst");
    trieAddWord(trie, "sole");
    trieAddWord(trie, "cool");
    trieAddWord(trie, "card");


    trieRemoveWord(trie, "worm");
    trieRemoveWord(trie, "worst");
    trieRemoveWord(trie, "sole");
    trieRemoveWord(trie, "cool");
    trieRemoveWord(trie, "card");

    CuAssertIntEquals(cuTest, 1, trieContains(trie, "word"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "world"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "soon"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "stole"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "cold"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "cat"));
    CuAssertIntEquals(cuTest, 1, trieContains(trie, "cart"));

    CuAssertIntEquals(cuTest, 0, trieContains(trie, "worm"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "worst"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "sole"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "cool"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "card"));

    destroyTrie(trie);

}


void testTrieAutoCompletion(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    trieAutoCompletion(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    trieAutoCompletion(trie, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieAutoCompletion(trie, "word", 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");
    trieAddWord(trie, "world");
    trieAddWord(trie, "soon");
    trieAddWord(trie, "stole");
    trieAddWord(trie, "cold");
    trieAddWord(trie, "cat");
    trieAddWord(trie, "cart");
    trieAddWord(trie, "worm");
    trieAddWord(trie, "worst");
    trieAddWord(trie, "sole");
    trieAddWord(trie, "cool");
    trieAddWord(trie, "card");


    ArrayList *suggestionsList = trieAutoCompletion(trie, "ca", 10);
    CuAssertIntEquals(cuTest, 3, arrayListGetLength(suggestionsList));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "cat"));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "cart"));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "card"));
    destroyArrayList(suggestionsList);

    suggestionsList = trieAutoCompletion(trie, "wor", 4);
    CuAssertIntEquals(cuTest, 4, arrayListGetLength(suggestionsList));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "word"));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "world"));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "worm"));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "worst"));
    destroyArrayList(suggestionsList);


    suggestionsList = trieAutoCompletion(trie, "w", 2);
    CuAssertIntEquals(cuTest, 2, arrayListGetLength(suggestionsList));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "word"));
    CuAssertIntEquals(cuTest, 1, arrayListContains(suggestionsList, "world"));
    CuAssertIntEquals(cuTest, 0, arrayListContains(suggestionsList, "worm"));
    CuAssertIntEquals(cuTest, 0, arrayListContains(suggestionsList, "worst"));
    destroyArrayList(suggestionsList);


    suggestionsList = trieAutoCompletion(trie, "", 20);
    CuAssertIntEquals(cuTest, 12, arrayListGetLength(suggestionsList));
    destroyArrayList(suggestionsList);

    destroyTrie(trie);

}


void testTrieSuggestion(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    trieSuggestion(NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    trieSuggestion(trie, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieSuggestion(trie, "word", 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");
    trieAddWord(trie, "world");
    trieAddWord(trie, "soon");
    trieAddWord(trie, "stole");
    trieAddWord(trie, "cold");
    trieAddWord(trie, "cat");
    trieAddWord(trie, "cart");
    trieAddWord(trie, "worm");
    trieAddWord(trie, "worst");
    trieAddWord(trie, "sole");
    trieAddWord(trie, "cool");
    trieAddWord(trie, "card");


    ArrayList *suggestionsList = trieSuggestion(trie, "cat", 3);
    CuAssertIntEquals(cuTest, 3, arrayListGetLength(suggestionsList));
    CuAssertStrEquals(cuTest, "cat", (char *) arrayListGet(suggestionsList, 0));
    CuAssertStrEquals(cuTest, "card", (char *) arrayListGet(suggestionsList, 1));
    CuAssertStrEquals(cuTest, "cart", (char *) arrayListGet(suggestionsList, 2));
    destroyArrayList(suggestionsList);


    suggestionsList = trieSuggestion(trie, "work", 4);
    CuAssertIntEquals(cuTest, 4, arrayListGetLength(suggestionsList));
    CuAssertStrEquals(cuTest, "world", (char *) arrayListGet(suggestionsList, 0));
    CuAssertStrEquals(cuTest, "worm", (char *) arrayListGet(suggestionsList, 1));
    CuAssertStrEquals(cuTest, "word", (char *) arrayListGet(suggestionsList, 2));
    CuAssertStrEquals(cuTest, "worst", (char *) arrayListGet(suggestionsList, 3));
    destroyArrayList(suggestionsList);


    suggestionsList = trieSuggestion(trie, "", 20);
    CuAssertIntEquals(cuTest, 12, arrayListGetLength(suggestionsList));
    for (int i = 0; i < arrayListGetLength(suggestionsList); i++)
        CuAssertIntEquals(cuTest, 1, trieContains(trie, arrayListGet(suggestionsList, i)));

    destroyArrayList(suggestionsList);


    destroyTrie(trie);


}


void testTriePrintAllWords(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    triePrintAllWords(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    triePrintAllWords(trie, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");
    trieAddWord(trie, "world");
    trieAddWord(trie, "worm");

    FILE *dir = fopen("triePrintWordsTestTextFile.txt", "w+");
    if (dir == NULL) {
        fprintf(stderr, "Can't open the scan file in input scanner unit test.");
        exit(SOMETHING_WENT_WRONG);
    }

    triePrintAllWords(trie, dir);

    fseek(dir, 0, SEEK_SET);
    char input[20];
    int index = 0;
    char c;

    while ((c = fgetc(dir)) != EOF)
        input[index++] = c;

    input[index] = '\0';

    CuAssertIntEquals(cuTest, 0, strcmp("word\nworld\nworm\n", input));

    fclose(dir);

    destroyTrie(trie);

}


void testClearTrie(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    clearTrie(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");
    trieAddWord(trie, "world");
    trieAddWord(trie, "soon");
    trieAddWord(trie, "stole");
    trieAddWord(trie, "cold");
    trieAddWord(trie, "cat");
    trieAddWord(trie, "cart");

    clearTrie(trie);

    CuAssertIntEquals(cuTest, 0, trieContains(trie, "word"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "world"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "soon"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "stole"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "cold"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "cat"));
    CuAssertIntEquals(cuTest, 0, trieContains(trie, "cart"));


    destroyTrie(trie);

}


void testDestroyTrie(CuTest *cuTest) {

    Trie *trie = trieInitialization();

    destroyTrie(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    trieAddWord(trie, "word");
    trieAddWord(trie, "world");
    trieAddWord(trie, "soon");
    trieAddWord(trie, "stole");
    trieAddWord(trie, "cold");
    trieAddWord(trie, "cat");
    trieAddWord(trie, "cart");

    destroyTrie(trie);

}


CuSuite *createTrieTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testValidTrieInitialization);
    SUITE_ADD_TEST(suite, testTrieAddWord);
    SUITE_ADD_TEST(suite, testTrieContains);
    SUITE_ADD_TEST(suite, testTrieRemoveWord);
    SUITE_ADD_TEST(suite, testTrieAutoCompletion);
    SUITE_ADD_TEST(suite, testTrieSuggestion);
    SUITE_ADD_TEST(suite, testTriePrintAllWords);
    SUITE_ADD_TEST(suite, testClearTrie);
    SUITE_ADD_TEST(suite, testDestroyTrie);

    return suite;

}


void trieUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Trie Test**\n");

    CuSuite *suite = createTrieTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}