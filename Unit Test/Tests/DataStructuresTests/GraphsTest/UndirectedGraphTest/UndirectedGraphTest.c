#include "UndirectedGraphTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Graphs/Headers/UndirectedGraph.h"
#include "../../../../../DataStructure/Tables/Headers/HashMap.h"
#include "../../../../../DataStructure/Lists/Headers/ArrayList.h"


int undirectedGraphTestStrcmp(const void *c1, const void *c2) {
    return strcmp(c1, c2);
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerUDGT(char *ch) {

    char *newCh = (char *) malloc(sizeof(char) * (strlen(ch) + 1));

    strcpy(newCh, ch);

    return newCh;

}


/** This function will take an char array pointer,
 * then it will return the sum of the ASCII value of the array characters.
 *
 * Note: this function will be useful to use in the hash set and hash map data structures.
 *
 * @param ch the char array pointer
 * @return it will return the sum of the ASCII value of the array characters.
 */

int charArrHashFunUDGT(const void *ch) {
    int sumASCII = 0;
    char *tempPointer = (char *) ch;

    while (*tempPointer != '\0')
        sumASCII += *tempPointer++;

    return sumASCII;

}


void testInvalidUndirectedGraphInitialization(CuTest *cuTest) {

    undirectedGraphInitialization(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    undirectedGraphInitialization(free, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    undirectedGraphInitialization(free, undirectedGraphTestStrcmp, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidUndirectedGraphInitialization(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    CuAssertPtrNotNull(cuTest, undirectedGraph);

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphAddNode(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphAddNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphAddNode(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    int arr[4] = {0};

    for (int i = 0; i < undirectedGraph->nodes->length; i++) {

        if (undirectedGraph->nodes->arr[i] != NULL)
            arr[*(char *) undirectedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 4; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphRemoveNode(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphRemoveNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphRemoveNode(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    udGraphRemoveNode(undirectedGraph, "D");
    udGraphRemoveNode(undirectedGraph, "C");

    int arr[4] = {0};

    for (int i = 0; i < undirectedGraph->nodes->length; i++) {

        if (undirectedGraph->nodes->arr[i] != NULL)
            arr[*(char *) undirectedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 2; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    for (int i = 2; i < 4; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphRemoveNodeWtoFr(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphRemoveNodeWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphRemoveNodeWtoFr(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    char *tempPointer = (char *) udGraphRemoveNodeWtoFr(undirectedGraph, "D");
    CuAssertStrEquals(cuTest, "D", tempPointer);
    free(tempPointer);

    tempPointer = (char *) udGraphRemoveNodeWtoFr(undirectedGraph, "C");
    CuAssertStrEquals(cuTest, "C", tempPointer);
    free(tempPointer);

    CuAssertPtrEquals(cuTest, NULL, udGraphRemoveNodeWtoFr(undirectedGraph, "F"));

    int arr[4] = {0};

    for (int i = 0; i < undirectedGraph->nodes->length; i++) {

        if (undirectedGraph->nodes->arr[i] != NULL)
            arr[*(char *) undirectedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 2; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    for (int i = 2; i < 4; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphAddEdge(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphAddEdge(NULL, NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphAddEdge(undirectedGraph, NULL, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    udGraphAddEdge(undirectedGraph, &tempChar, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    udGraphAddEdge(undirectedGraph, &tempChar, &tempChar, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    udGraphAddEdge(undirectedGraph, "A", "B", 1);
    udGraphAddEdge(undirectedGraph, "C", "D", 2);


    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, udGraphGetEdgeWeight(undirectedGraph, "A", "B"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 2, udGraphGetEdgeWeight(undirectedGraph, "C", "D"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "A", "C"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "A", "D"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "B", "C"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "B", "D"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "B", "A"));
    CuAssertIntEquals(cuTest, 1, udGraphGetEdgeWeight(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 2, udGraphGetEdgeWeight(undirectedGraph, "D", "C"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "D", "A"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "D", "A"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "C", "B"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "C", "B"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "D", "B"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "D", "B"));

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphRemoveEdge(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphRemoveEdge(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphRemoveEdge(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    udGraphRemoveEdge(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    udGraphAddEdge(undirectedGraph, "A", "B", 1);
    udGraphAddEdge(undirectedGraph, "C", "D", 2);
    udGraphAddEdge(undirectedGraph, "B", "D", 3);
    udGraphAddEdge(undirectedGraph, "A", "D", 4);

    udGraphRemoveEdge(undirectedGraph, "C", "D");
    udGraphRemoveEdge(undirectedGraph, "B", "D");
    udGraphRemoveEdge(undirectedGraph, "A", "D");


    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "D", "A"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "D", "B"));

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphContainsNode(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphContainsNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphContainsNode(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "D"));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    CuAssertIntEquals(cuTest, 1, udGraphContainsNode(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsNode(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsNode(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsNode(undirectedGraph, "D"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "E"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "F"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "G"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsNode(undirectedGraph, "H"));

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphContainsEdge(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphContainsEdge(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphContainsEdge(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    udGraphContainsEdge(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    udGraphAddEdge(undirectedGraph, "A", "B", 1);
    udGraphAddEdge(undirectedGraph, "C", "D", 2);
    udGraphAddEdge(undirectedGraph, "B", "D", 3);
    udGraphAddEdge(undirectedGraph, "A", "D", 4);


    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "D", "C"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "D", "A"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(undirectedGraph, "D", "B"));

    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(undirectedGraph, "C", "B"));

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphGetEdgeWeight(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphGetEdgeWeight(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphGetEdgeWeight(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    udGraphGetEdgeWeight(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    udGraphAddEdge(undirectedGraph, "A", "B", 1);
    udGraphAddEdge(undirectedGraph, "C", "D", 2);
    udGraphAddEdge(undirectedGraph, "B", "D", 3);
    udGraphAddEdge(undirectedGraph, "A", "D", 4);


    CuAssertIntEquals(cuTest, 1, udGraphGetEdgeWeight(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, udGraphGetEdgeWeight(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 2, udGraphGetEdgeWeight(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 2, udGraphGetEdgeWeight(undirectedGraph, "D", "C"));

    CuAssertIntEquals(cuTest, 3, udGraphGetEdgeWeight(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 3, udGraphGetEdgeWeight(undirectedGraph, "D", "B"));

    CuAssertIntEquals(cuTest, 4, udGraphGetEdgeWeight(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 4, udGraphGetEdgeWeight(undirectedGraph, "D", "A"));

    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, -1, udGraphGetEdgeWeight(undirectedGraph, "C", "B"));

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphGetSize(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, udGraphGetSize(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    CuAssertIntEquals(cuTest, 1, udGraphGetSize(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    CuAssertIntEquals(cuTest, 2, udGraphGetSize(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    CuAssertIntEquals(cuTest, 3, udGraphGetSize(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    CuAssertIntEquals(cuTest, 4, udGraphGetSize(undirectedGraph));


    udGraphRemoveNode(undirectedGraph, "A");
    CuAssertIntEquals(cuTest, 3, udGraphGetSize(undirectedGraph));

    udGraphRemoveNode(undirectedGraph, "B");
    CuAssertIntEquals(cuTest, 2, udGraphGetSize(undirectedGraph));

    udGraphRemoveNode(undirectedGraph, "C");
    CuAssertIntEquals(cuTest, 1, udGraphGetSize(undirectedGraph));

    udGraphRemoveNode(undirectedGraph, "D");
    CuAssertIntEquals(cuTest, 0, udGraphGetSize(undirectedGraph));

    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphIsEmpty(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, udGraphIsEmpty(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));


    udGraphRemoveNode(undirectedGraph, "A");
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));

    udGraphRemoveNode(undirectedGraph, "B");
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));

    udGraphRemoveNode(undirectedGraph, "C");
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));

    udGraphRemoveNode(undirectedGraph, "D");
    CuAssertIntEquals(cuTest, 1, udGraphIsEmpty(undirectedGraph));

    destroyUDGraph(undirectedGraph);

}


void testClearUndirectedGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    clearUDGraph(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, udGraphIsEmpty(undirectedGraph));

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    CuAssertIntEquals(cuTest, 0, udGraphIsEmpty(undirectedGraph));

    clearUDGraph(undirectedGraph);
    CuAssertIntEquals(cuTest, 1, udGraphIsEmpty(undirectedGraph));

    destroyUDGraph(undirectedGraph);

}


void testDestroyUndirectedGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    destroyUDGraph(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    destroyUDGraph(undirectedGraph);

}


ArrayList *printUDTingList;

void printFunUDTDGT(void *item) {
    arrayListAdd(printUDTingList, item);
}

void nullFreeFunUDGT(void *item) {}


void testPrintUndirectedGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    printUDGraph(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    printUDGraph(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    udGraphAddEdge(undirectedGraph, "A", "B", 1);
    udGraphAddEdge(undirectedGraph, "C", "D", 2);

    printUDTingList = arrayListInitialization(8, nullFreeFunUDGT, NULL);
    printUDGraph(undirectedGraph, printFunUDTDGT);

    CuAssertIntEquals(cuTest, 8, arrayListGetLength(printUDTingList));
    CuAssertStrEquals(cuTest, "A", arrayListGet(printUDTingList, 0));
    CuAssertStrEquals(cuTest, "B", arrayListGet(printUDTingList, 1));
    CuAssertStrEquals(cuTest, "D", arrayListGet(printUDTingList, 2));
    CuAssertStrEquals(cuTest, "C", arrayListGet(printUDTingList, 3));
    CuAssertStrEquals(cuTest, "C", arrayListGet(printUDTingList, 4));
    CuAssertStrEquals(cuTest, "D", arrayListGet(printUDTingList, 5));
    CuAssertStrEquals(cuTest, "B", arrayListGet(printUDTingList, 6));
    CuAssertStrEquals(cuTest, "A", arrayListGet(printUDTingList, 7));


    destroyArrayList(printUDTingList);
    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphGetShortestDistance(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphGetShortestDistance(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphGetShortestDistance(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    udGraphGetShortestDistance(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    udGraphAddEdge(undirectedGraph, "A", "B", 3);
    udGraphAddEdge(undirectedGraph, "A", "D", 2);
    udGraphAddEdge(undirectedGraph, "A", "C", 4);
    udGraphAddEdge(undirectedGraph, "B", "D", 6);
    udGraphAddEdge(undirectedGraph, "B", "E", 1);
    udGraphAddEdge(undirectedGraph, "D", "E", 5);
    udGraphAddEdge(undirectedGraph, "C", "D", 1);

    CuAssertIntEquals(cuTest, 3, udGraphGetShortestDistance(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 3, udGraphGetShortestDistance(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 4, udGraphGetShortestDistance(undirectedGraph, "A", "E"));
    CuAssertIntEquals(cuTest, 1, udGraphGetShortestDistance(undirectedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 6, udGraphGetShortestDistance(undirectedGraph, "C", "B"));


    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphGetShortestPath(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphGetShortestPath(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphGetShortestPath(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    udGraphGetShortestPath(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    udGraphAddEdge(undirectedGraph, "A", "B", 3);
    udGraphAddEdge(undirectedGraph, "A", "D", 2);
    udGraphAddEdge(undirectedGraph, "A", "C", 4);
    udGraphAddEdge(undirectedGraph, "B", "D", 6);
    udGraphAddEdge(undirectedGraph, "B", "E", 1);
    udGraphAddEdge(undirectedGraph, "D", "E", 5);
    udGraphAddEdge(undirectedGraph, "C", "D", 1);

    ArrayList *pathList = udGraphGetShortestPath(undirectedGraph, "A", "E");
    CuAssertIntEquals(cuTest, 3, arrayListGetLength(pathList));
    CuAssertStrEquals(cuTest, "A", (char *) arrayListGet(pathList, 0));
    CuAssertStrEquals(cuTest, "B", (char *) arrayListGet(pathList, 1));
    CuAssertStrEquals(cuTest, "E", (char *) arrayListGet(pathList, 2));
    while (!arrayListIsEmpty(pathList))
        arrayListRemoveWtFr(pathList);
    destroyArrayList(pathList);

    pathList = udGraphGetShortestPath(undirectedGraph, "A", "C");
    CuAssertIntEquals(cuTest, 3, arrayListGetLength(pathList));
    CuAssertStrEquals(cuTest, "A", (char *) arrayListGet(pathList, 0));
    CuAssertStrEquals(cuTest, "D", (char *) arrayListGet(pathList, 1));
    CuAssertStrEquals(cuTest, "C", (char *) arrayListGet(pathList, 2));
    while (!arrayListIsEmpty(pathList))
        arrayListRemoveWtFr(pathList);
    destroyArrayList(pathList);

    pathList = udGraphGetShortestPath(undirectedGraph, "C", "B");
    CuAssertIntEquals(cuTest, 4, arrayListGetLength(pathList));
    CuAssertStrEquals(cuTest, "C", (char *) arrayListGet(pathList, 0));
    CuAssertStrEquals(cuTest, "D", (char *) arrayListGet(pathList, 1));
    CuAssertStrEquals(cuTest, "A", (char *) arrayListGet(pathList, 2));
    CuAssertStrEquals(cuTest, "B", (char *) arrayListGet(pathList, 3));
    while (!arrayListIsEmpty(pathList))
        arrayListRemoveWtFr(pathList);
    destroyArrayList(pathList);


    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphNodePartOfCycle(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphNodePartOfCycle(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphNodePartOfCycle(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    udGraphAddEdge(undirectedGraph, "A", "B", 3);
    udGraphAddEdge(undirectedGraph, "A", "D", 2);
    udGraphAddEdge(undirectedGraph, "A", "C", 4);
    udGraphAddEdge(undirectedGraph, "B", "D", 6);
    udGraphAddEdge(undirectedGraph, "B", "E", 1);
    udGraphAddEdge(undirectedGraph, "D", "E", 5);
    udGraphAddEdge(undirectedGraph, "C", "D", 1);

    CuAssertIntEquals(cuTest, 1, udGraphNodePartOfCycle(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 1, udGraphNodePartOfCycle(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 1, udGraphNodePartOfCycle(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 1, udGraphNodePartOfCycle(undirectedGraph, "D"));
    CuAssertIntEquals(cuTest, 1, udGraphNodePartOfCycle(undirectedGraph, "E"));

    udGraphRemoveEdge(undirectedGraph, "A", "B");
    udGraphRemoveEdge(undirectedGraph, "B", "E");
    udGraphRemoveEdge(undirectedGraph, "A", "D");
    udGraphRemoveEdge(undirectedGraph, "C", "D");

    CuAssertIntEquals(cuTest, 0, udGraphNodePartOfCycle(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 0, udGraphNodePartOfCycle(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 0, udGraphNodePartOfCycle(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 0, udGraphNodePartOfCycle(undirectedGraph, "D"));
    CuAssertIntEquals(cuTest, 0, udGraphNodePartOfCycle(undirectedGraph, "E"));


    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphHasCycle(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphHasCycle(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    udGraphAddEdge(undirectedGraph, "A", "B", 3);
    udGraphAddEdge(undirectedGraph, "A", "D", 2);
    udGraphAddEdge(undirectedGraph, "A", "C", 4);
    udGraphAddEdge(undirectedGraph, "B", "D", 6);
    udGraphAddEdge(undirectedGraph, "B", "E", 1);
    udGraphAddEdge(undirectedGraph, "D", "E", 5);
    udGraphAddEdge(undirectedGraph, "C", "D", 1);

    CuAssertIntEquals(cuTest, 1, udGraphHasCycle(undirectedGraph));

    udGraphRemoveEdge(undirectedGraph, "A", "B");
    udGraphRemoveEdge(undirectedGraph, "B", "E");
    udGraphRemoveEdge(undirectedGraph, "A", "D");
    udGraphRemoveEdge(undirectedGraph, "C", "D");

    CuAssertIntEquals(cuTest, 0, udGraphHasCycle(undirectedGraph));


    destroyUDGraph(undirectedGraph);

}


void testUndirectedGraphMinimumSpanningGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, undirectedGraphTestStrcmp,
                                                                     charArrHashFunUDGT);

    udGraphMinimumSpanningGraph(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    udGraphMinimumSpanningGraph(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    udGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // |       / |
    // |      /  |
    // |     /   |
    // 1    2    4
    // |   /     |
    // |  /      |
    // | /       |
    // C ---5--- D

    udGraphAddEdge(undirectedGraph, "A", "B", 3);
    udGraphAddEdge(undirectedGraph, "A", "C", 1);
    udGraphAddEdge(undirectedGraph, "B", "D", 4);
    udGraphAddEdge(undirectedGraph, "B", "C", 2);
    udGraphAddEdge(undirectedGraph, "C", "D", 5);

    UndirectedGraph *spanningGraph = udGraphMinimumSpanningGraph(undirectedGraph, "A");

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(spanningGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 1, udGraphGetEdgeWeight(spanningGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(spanningGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(spanningGraph, "A", "D"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(spanningGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 2, udGraphGetEdgeWeight(spanningGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 0, udGraphContainsEdge(spanningGraph, "C", "D"));

    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(spanningGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 4, udGraphGetEdgeWeight(spanningGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 1, udGraphContainsEdge(spanningGraph, "B", "C"));

    udGraphRemoveNodeWtoFr(spanningGraph, "A");
    udGraphRemoveNodeWtoFr(spanningGraph, "B");
    udGraphRemoveNodeWtoFr(spanningGraph, "C");
    udGraphRemoveNodeWtoFr(spanningGraph, "D");

    destroyUDGraph(spanningGraph);
    destroyUDGraph(undirectedGraph);

}


CuSuite *createUndirectedGraphTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidUndirectedGraphInitialization);
    SUITE_ADD_TEST(suite, testValidUndirectedGraphInitialization);
    SUITE_ADD_TEST(suite, testUndirectedGraphAddNode);
    SUITE_ADD_TEST(suite, testUndirectedGraphRemoveNode);
    SUITE_ADD_TEST(suite, testUndirectedGraphRemoveNodeWtoFr);
    SUITE_ADD_TEST(suite, testUndirectedGraphAddEdge);
    SUITE_ADD_TEST(suite, testUndirectedGraphRemoveEdge);
    SUITE_ADD_TEST(suite, testUndirectedGraphContainsEdge);
    SUITE_ADD_TEST(suite, testUndirectedGraphContainsNode);
    SUITE_ADD_TEST(suite, testUndirectedGraphGetEdgeWeight);
    SUITE_ADD_TEST(suite, testUndirectedGraphGetSize);
    SUITE_ADD_TEST(suite, testUndirectedGraphIsEmpty);
    SUITE_ADD_TEST(suite, testClearUndirectedGraph);
    SUITE_ADD_TEST(suite, testDestroyUndirectedGraph);
    SUITE_ADD_TEST(suite, testPrintUndirectedGraph);
    SUITE_ADD_TEST(suite, testUndirectedGraphGetShortestDistance);
    SUITE_ADD_TEST(suite, testUndirectedGraphGetShortestPath);
    SUITE_ADD_TEST(suite, testUndirectedGraphNodePartOfCycle);
    SUITE_ADD_TEST(suite, testUndirectedGraphHasCycle);
    SUITE_ADD_TEST(suite, testUndirectedGraphMinimumSpanningGraph);

    return suite;

}


void undirectedGraphUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Undirected Graph Test**\n");

    CuSuite *suite = createUndirectedGraphTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}