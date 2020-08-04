#include "UndirectedGraphTest.h"

#include "../../../CuTest/CuTest.h"
#include "../../../../System/Utils.h"
#include "../../../../DataStructure/Graphs/Headers/UndirectedGraph.h"
#include "../../../../DataStructure/Tables/Headers/HashMap.h"
#include "../../../../DataStructure/Lists/Headers/ArrayList.h"


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerUDGT(char *ch) {

    char *newCh = (char *) malloc( sizeof(char) * (strlen(ch) + 1) );

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
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    undirectedGraphInitialization(free, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    undirectedGraphInitialization(free, strcmp, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

}



void testValidUndirectedGraphInitialization(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    CuAssertPtrNotNull(cuTest, undirectedGraph);

    destroyUDGraph(undirectedGraph);

}



void testUndirectedGraphAddNode(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphAddNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphAddNode(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    int arr[4] = {0};

    for (int i = 0; i < undirectedGraph->nodes->length; i++) {

        if (undirectedGraph->nodes->arr[i] != NULL)
            arr[*(char *)undirectedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 4; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    destroyUDGraph(undirectedGraph);

}




void testUndirectedGraphRemoveNode(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphRemoveNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphRemoveNode(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    UDGraphRemoveNode(undirectedGraph, "D");
    UDGraphRemoveNode(undirectedGraph, "C");

    int arr[4] = {0};

    for (int i = 0; i < undirectedGraph->nodes->length; i++) {

        if (undirectedGraph->nodes->arr[i] != NULL)
            arr[*(char *)undirectedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 2; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    for (int i = 2; i < 4; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    destroyUDGraph(undirectedGraph);

}




void testUndirectedGraphRemoveNodeWtoFr(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphRemoveNodeWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphRemoveNodeWtoFr(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    char *tempPointer = (char *) UDGraphRemoveNodeWtoFr(undirectedGraph, "D");
    CuAssertStrEquals(cuTest, "D", tempPointer);
    free(tempPointer);

    tempPointer = (char *) UDGraphRemoveNodeWtoFr(undirectedGraph, "C");
    CuAssertStrEquals(cuTest, "C", tempPointer);
    free(tempPointer);

    CuAssertPtrEquals(cuTest, NULL, UDGraphRemoveNodeWtoFr(undirectedGraph, "F"));

    int arr[4] = {0};

    for (int i = 0; i < undirectedGraph->nodes->length; i++) {

        if (undirectedGraph->nodes->arr[i] != NULL)
            arr[*(char *)undirectedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 2; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    for (int i = 2; i < 4; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    destroyUDGraph(undirectedGraph);

}





void testUndirectedGraphAddEdge(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphAddEdge(NULL, NULL, NULL, 0);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphAddEdge(undirectedGraph, NULL, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    char tempChar = 'A';
    UDGraphAddEdge(undirectedGraph, &tempChar, NULL, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphAddEdge(undirectedGraph, &tempChar, &tempChar, 0);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    UDGraphAddEdge(undirectedGraph, "A", "B", 1);
    UDGraphAddEdge(undirectedGraph, "C", "D", 2);


    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, UDGraphGetEdgeWeight(undirectedGraph, "A", "B"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 2, UDGraphGetEdgeWeight(undirectedGraph, "C", "D"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "A", "C"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "A", "D"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "B", "C"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "B", "D"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "B", "A"));
    CuAssertIntEquals(cuTest, 1, UDGraphGetEdgeWeight(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 2, UDGraphGetEdgeWeight(undirectedGraph, "D", "C"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "D", "A"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "D", "A"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "C", "B"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "C", "B"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "D", "B"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "D", "B"));

    destroyUDGraph(undirectedGraph);

}





void testUndirectedGraphRemoveEdge(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphRemoveEdge(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphRemoveEdge(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    char tempChar = 'A';
    UDGraphRemoveEdge(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    UDGraphAddEdge(undirectedGraph, "A", "B", 1);
    UDGraphAddEdge(undirectedGraph, "C", "D", 2);
    UDGraphAddEdge(undirectedGraph, "B", "D", 3);
    UDGraphAddEdge(undirectedGraph, "A", "D", 4);

    UDGraphRemoveEdge(undirectedGraph, "C", "D");
    UDGraphRemoveEdge(undirectedGraph, "B", "D");
    UDGraphRemoveEdge(undirectedGraph, "A", "D");


    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "D", "A"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "D", "B"));

    destroyUDGraph(undirectedGraph);

}





void testUndirectedGraphContainsNode(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphContainsNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphContainsNode(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "D"));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    CuAssertIntEquals(cuTest, 1, UDGraphContainsNode(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsNode(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsNode(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsNode(undirectedGraph, "D"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "E"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "F"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "G"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsNode(undirectedGraph, "H"));

    destroyUDGraph(undirectedGraph);

}




void testUndirectedGraphContainsEdge(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphContainsEdge(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphContainsEdge(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    char tempChar = 'A';
    UDGraphContainsEdge(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    UDGraphAddEdge(undirectedGraph, "A", "B", 1);
    UDGraphAddEdge(undirectedGraph, "C", "D", 2);
    UDGraphAddEdge(undirectedGraph, "B", "D", 3);
    UDGraphAddEdge(undirectedGraph, "A", "D", 4);


    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "D", "C"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "D", "A"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(undirectedGraph, "D", "B"));

    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(undirectedGraph, "C", "B"));

    destroyUDGraph(undirectedGraph);

}






void testUndirectedGraphGetEdgeWeight(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphGetEdgeWeight(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphGetEdgeWeight(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    char tempChar = 'A';
    UDGraphGetEdgeWeight(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    UDGraphAddEdge(undirectedGraph, "A", "B", 1);
    UDGraphAddEdge(undirectedGraph, "C", "D", 2);
    UDGraphAddEdge(undirectedGraph, "B", "D", 3);
    UDGraphAddEdge(undirectedGraph, "A", "D", 4);


    CuAssertIntEquals(cuTest, 1, UDGraphGetEdgeWeight(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, UDGraphGetEdgeWeight(undirectedGraph, "B", "A"));

    CuAssertIntEquals(cuTest, 2, UDGraphGetEdgeWeight(undirectedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 2, UDGraphGetEdgeWeight(undirectedGraph, "D", "C"));

    CuAssertIntEquals(cuTest, 3, UDGraphGetEdgeWeight(undirectedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 3, UDGraphGetEdgeWeight(undirectedGraph, "D", "B"));

    CuAssertIntEquals(cuTest, 4, UDGraphGetEdgeWeight(undirectedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 4, UDGraphGetEdgeWeight(undirectedGraph, "D", "A"));

    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, -1, UDGraphGetEdgeWeight(undirectedGraph, "C", "B"));

    destroyUDGraph(undirectedGraph);

}




void testUndirectedGraphGetSize(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


    CuAssertIntEquals(cuTest, 0, UDGraphGetSize(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    CuAssertIntEquals(cuTest, 1, UDGraphGetSize(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    CuAssertIntEquals(cuTest, 2, UDGraphGetSize(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    CuAssertIntEquals(cuTest, 3, UDGraphGetSize(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    CuAssertIntEquals(cuTest, 4, UDGraphGetSize(undirectedGraph));


    UDGraphRemoveNode(undirectedGraph, "A");
    CuAssertIntEquals(cuTest, 3, UDGraphGetSize(undirectedGraph));

    UDGraphRemoveNode(undirectedGraph, "B");
    CuAssertIntEquals(cuTest, 2, UDGraphGetSize(undirectedGraph));

    UDGraphRemoveNode(undirectedGraph, "C");
    CuAssertIntEquals(cuTest, 1, UDGraphGetSize(undirectedGraph));

    UDGraphRemoveNode(undirectedGraph, "D");
    CuAssertIntEquals(cuTest, 0, UDGraphGetSize(undirectedGraph));

    destroyUDGraph(undirectedGraph);

}






void testUndirectedGraphIsEmpty(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


    CuAssertIntEquals(cuTest, 1, UDGraphIsEmpty(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));


    UDGraphRemoveNode(undirectedGraph, "A");
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));

    UDGraphRemoveNode(undirectedGraph, "B");
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));

    UDGraphRemoveNode(undirectedGraph, "C");
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));

    UDGraphRemoveNode(undirectedGraph, "D");
    CuAssertIntEquals(cuTest, 1, UDGraphIsEmpty(undirectedGraph));

    destroyUDGraph(undirectedGraph);

}





void testClearUndirectedGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    clearUDGraph(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


    CuAssertIntEquals(cuTest, 1, UDGraphIsEmpty(undirectedGraph));

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    CuAssertIntEquals(cuTest, 0, UDGraphIsEmpty(undirectedGraph));

    clearUDGraph(undirectedGraph);
    CuAssertIntEquals(cuTest, 1, UDGraphIsEmpty(undirectedGraph));

    destroyUDGraph(undirectedGraph);

}




void testDestroyUndirectedGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    destroyUDGraph(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));

    destroyUDGraph(undirectedGraph);

}



ArrayList *printUDTingList;
void printFunUDTDGT(void *item) {
    arrayListAdd(printUDTingList, item);
}

void nullFreeFunUDGT(){}


void testPrintUndirectedGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    printUDGraph(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    printUDGraph(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));


    UDGraphAddEdge(undirectedGraph, "A", "B", 1);
    UDGraphAddEdge(undirectedGraph, "C", "D", 2);

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

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphGetShortestDistance(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphGetShortestDistance(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    char tempChar = 'A';
    UDGraphGetShortestDistance(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    UDGraphAddEdge(undirectedGraph, "A", "B", 3);
    UDGraphAddEdge(undirectedGraph, "A", "D", 2);
    UDGraphAddEdge(undirectedGraph, "A", "C", 4);
    UDGraphAddEdge(undirectedGraph, "B", "D", 6);
    UDGraphAddEdge(undirectedGraph, "B", "E", 1);
    UDGraphAddEdge(undirectedGraph, "D", "E", 5);
    UDGraphAddEdge(undirectedGraph, "C", "D", 1);

    CuAssertIntEquals(cuTest, 3, UDGraphGetShortestDistance(undirectedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 3, UDGraphGetShortestDistance(undirectedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 4, UDGraphGetShortestDistance(undirectedGraph, "A", "E"));
    CuAssertIntEquals(cuTest, 1, UDGraphGetShortestDistance(undirectedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 6, UDGraphGetShortestDistance(undirectedGraph, "C", "B"));


    destroyUDGraph(undirectedGraph);

}






void testUndirectedGraphGetShortestPath(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphGetShortestPath(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphGetShortestPath(undirectedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);

    char tempChar = 'A';
    UDGraphGetShortestPath(undirectedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    UDGraphAddEdge(undirectedGraph, "A", "B", 3);
    UDGraphAddEdge(undirectedGraph, "A", "D", 2);
    UDGraphAddEdge(undirectedGraph, "A", "C", 4);
    UDGraphAddEdge(undirectedGraph, "B", "D", 6);
    UDGraphAddEdge(undirectedGraph, "B", "E", 1);
    UDGraphAddEdge(undirectedGraph, "D", "E", 5);
    UDGraphAddEdge(undirectedGraph, "C", "D", 1);

    ArrayList *pathList = UDGraphGetShortestPath(undirectedGraph, "A", "E");
    CuAssertIntEquals(cuTest, 3,  arrayListGetLength(pathList));
    CuAssertStrEquals(cuTest, "A", (char *) arrayListGet(pathList, 0));
    CuAssertStrEquals(cuTest, "B", (char *) arrayListGet(pathList, 1));
    CuAssertStrEquals(cuTest, "E", (char *) arrayListGet(pathList, 2));
    while (!arrayListIsEmpty(pathList))
        arrayListRemoveWtFr(pathList);
    destroyArrayList(pathList);

    pathList = UDGraphGetShortestPath(undirectedGraph, "A", "C");
    CuAssertIntEquals(cuTest, 3,  arrayListGetLength(pathList));
    CuAssertStrEquals(cuTest, "A", (char *) arrayListGet(pathList, 0));
    CuAssertStrEquals(cuTest, "D", (char *) arrayListGet(pathList, 1));
    CuAssertStrEquals(cuTest, "C", (char *) arrayListGet(pathList, 2));
    while (!arrayListIsEmpty(pathList))
        arrayListRemoveWtFr(pathList);
    destroyArrayList(pathList);

    pathList = UDGraphGetShortestPath(undirectedGraph, "C", "B");
    CuAssertIntEquals(cuTest, 4,  arrayListGetLength(pathList));
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

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphNodePartOfCycle(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphNodePartOfCycle(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    UDGraphAddEdge(undirectedGraph, "A", "B", 3);
    UDGraphAddEdge(undirectedGraph, "A", "D", 2);
    UDGraphAddEdge(undirectedGraph, "A", "C", 4);
    UDGraphAddEdge(undirectedGraph, "B", "D", 6);
    UDGraphAddEdge(undirectedGraph, "B", "E", 1);
    UDGraphAddEdge(undirectedGraph, "D", "E", 5);
    UDGraphAddEdge(undirectedGraph, "C", "D", 1);

    CuAssertIntEquals(cuTest, 1, UDGraphNodePartOfCycle(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 1, UDGraphNodePartOfCycle(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 1, UDGraphNodePartOfCycle(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 1, UDGraphNodePartOfCycle(undirectedGraph, "D"));
    CuAssertIntEquals(cuTest, 1, UDGraphNodePartOfCycle(undirectedGraph, "E"));

    UDGraphRemoveEdge(undirectedGraph, "A", "B");
    UDGraphRemoveEdge(undirectedGraph, "B", "E");
    UDGraphRemoveEdge(undirectedGraph, "A", "D");
    UDGraphRemoveEdge(undirectedGraph, "C", "D");

    CuAssertIntEquals(cuTest, 0, UDGraphNodePartOfCycle(undirectedGraph, "A"));
    CuAssertIntEquals(cuTest, 0, UDGraphNodePartOfCycle(undirectedGraph, "B"));
    CuAssertIntEquals(cuTest, 0, UDGraphNodePartOfCycle(undirectedGraph, "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphNodePartOfCycle(undirectedGraph, "D"));
    CuAssertIntEquals(cuTest, 0, UDGraphNodePartOfCycle(undirectedGraph, "E"));


    destroyUDGraph(undirectedGraph);

}








void testUndirectedGraphHasCycle(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphHasCycle(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // | \       | \
    // |  \      |  1
    // |   \     |   \
    // 4    2    6    E
    // |     \   |   /
    // |      \  |  5
    // |       \ | /
    // C ---1--- D

    UDGraphAddEdge(undirectedGraph, "A", "B", 3);
    UDGraphAddEdge(undirectedGraph, "A", "D", 2);
    UDGraphAddEdge(undirectedGraph, "A", "C", 4);
    UDGraphAddEdge(undirectedGraph, "B", "D", 6);
    UDGraphAddEdge(undirectedGraph, "B", "E", 1);
    UDGraphAddEdge(undirectedGraph, "D", "E", 5);
    UDGraphAddEdge(undirectedGraph, "C", "D", 1);

    CuAssertIntEquals(cuTest, 1, UDGraphHasCycle(undirectedGraph));

    UDGraphRemoveEdge(undirectedGraph, "A", "B");
    UDGraphRemoveEdge(undirectedGraph, "B", "E");
    UDGraphRemoveEdge(undirectedGraph, "A", "D");
    UDGraphRemoveEdge(undirectedGraph, "C", "D");

    CuAssertIntEquals(cuTest, 0, UDGraphHasCycle(undirectedGraph));


    destroyUDGraph(undirectedGraph);

}





void testUndirectedGraphMinimumSpanningGraph(CuTest *cuTest) {

    UndirectedGraph *undirectedGraph = undirectedGraphInitialization(free, strcmp, charArrHashFunUDGT);

    UDGraphMinimumSpanningGraph(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, DUMMY_TEST_DATASTRUCTURE->errorCode);

    UDGraphMinimumSpanningGraph(undirectedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, DUMMY_TEST_DATASTRUCTURE->errorCode);


    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("A"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("B"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("C"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("D"));
    UDGraphAddNode(undirectedGraph, generateCharPointerUDGT("E"));

    // A ---3--- B
    // |       / |
    // |      /  |
    // |     /   |
    // 1    2    4
    // |   /     |
    // |  /      |
    // | /       |
    // C ---5--- D

    UDGraphAddEdge(undirectedGraph, "A", "B", 3);
    UDGraphAddEdge(undirectedGraph, "A", "C", 1);
    UDGraphAddEdge(undirectedGraph, "B", "D", 4);
    UDGraphAddEdge(undirectedGraph, "B", "C", 2);
    UDGraphAddEdge(undirectedGraph, "C", "D", 5);

    UndirectedGraph *spanningGraph = UDGraphMinimumSpanningGraph(undirectedGraph, "A");

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(spanningGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 1, UDGraphGetEdgeWeight(spanningGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(spanningGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(spanningGraph, "A", "D"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(spanningGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 2, UDGraphGetEdgeWeight(spanningGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 0, UDGraphContainsEdge(spanningGraph, "C", "D"));

    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(spanningGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 4, UDGraphGetEdgeWeight(spanningGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 1, UDGraphContainsEdge(spanningGraph, "B", "C"));

    UDGraphRemoveNodeWtoFr(spanningGraph, "A");
    UDGraphRemoveNodeWtoFr(spanningGraph, "B");
    UDGraphRemoveNodeWtoFr(spanningGraph, "C");
    UDGraphRemoveNodeWtoFr(spanningGraph, "D");

    destroyUDGraph(spanningGraph);
    destroyUDGraph(undirectedGraph);

}



CuSuite *createUndirectedGraphTestsSuite() {

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



void undirectedGraphUnitTest() {

    DUMMY_TEST_DATASTRUCTURE =  (TestStruct*) malloc(sizeof(TestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Undirected Graph Test**\n");

    CuSuite *suite = createUndirectedGraphTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(DUMMY_TEST_DATASTRUCTURE);

}