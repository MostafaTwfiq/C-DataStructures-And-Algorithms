#include "DirectedGraphTest.h"

#include "../../../../CuTest/CuTest.h"
#include "../../../../../System/Utils.h"
#include "../../../../../DataStructure/Graphs/Headers/DirectedGraph.h"
#include "../../../../../DataStructure/Tables/Headers/HashMap.h"
#include "../../../../../DataStructure/Lists/Headers/ArrayList.h"


int directedGraphTestStrcmp(const void *c1, const void *c2) {
    return strcmp(c1, c2);
}


/** This function will take a char array
 * then it will allocate a new one and copy the original char array into the new one,
 * and finally return the new allocated char array.
 * @param ch the char array pointer
 * @return it will return the new allocated char array pointer
 */

char *generateCharPointerDGT(char *ch) {

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

int charArrHashFunDGT(const void *ch) {
    int sumASCII = 0;
    char *tempPointer = (char *) ch;

    while (*tempPointer != '\0')
        sumASCII += *tempPointer++;

    return sumASCII;

}


void testInvalidDirectedGraphInitialization(CuTest *cuTest) {

    directedGraphInitialization(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    directedGraphInitialization(free, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    directedGraphInitialization(free, directedGraphTestStrcmp, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

}


void testValidDirectedGraphInitialization(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    CuAssertPtrNotNull(cuTest, directedGraph);

    destroyDirGraph(directedGraph);

}


void testDirectedGraphAddNode(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphAddNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphAddNode(directedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));

    int arr[4] = {0};

    for (int i = 0; i < directedGraph->nodes->length; i++) {

        if (directedGraph->nodes->arr[i] != NULL)
            arr[*(char *) directedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 4; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    destroyDirGraph(directedGraph);

}


void testDirectedGraphRemoveNode(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphRemoveNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphRemoveNode(directedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));

    dirGraphRemoveNode(directedGraph, "D");
    dirGraphRemoveNode(directedGraph, "C");

    int arr[4] = {0};

    for (int i = 0; i < directedGraph->nodes->length; i++) {

        if (directedGraph->nodes->arr[i] != NULL)
            arr[*(char *) directedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 2; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    for (int i = 2; i < 4; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    destroyDirGraph(directedGraph);

}


void testDirectedGraphRemoveNodeWtoFr(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphRemoveNodeWtoFr(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphRemoveNodeWtoFr(directedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));

    char *tempPointer1 = (char *) dirGraphRemoveNodeWtoFr(directedGraph, "D");
    CuAssertStrEquals(cuTest, "D", tempPointer1);
    free(tempPointer1);

    char *tempPointer2 = (char *) dirGraphRemoveNodeWtoFr(directedGraph, "C");
    CuAssertStrEquals(cuTest, "C", tempPointer2);
    free(tempPointer2);

    CuAssertPtrEquals(cuTest, NULL, dirGraphRemoveNodeWtoFr(directedGraph, "F"));

    int arr[4] = {0};

    for (int i = 0; i < directedGraph->nodes->length; i++) {

        if (directedGraph->nodes->arr[i] != NULL)
            arr[*(char *) directedGraph->nodes->arr[i]->key - 'A']++;

    }

    for (int i = 0; i < 2; i++)
        CuAssertIntEquals(cuTest, 1, arr[i]);

    for (int i = 2; i < 4; i++)
        CuAssertIntEquals(cuTest, 0, arr[i]);

    destroyDirGraph(directedGraph);

}


void testDirectedGraphAddEdge(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphAddEdge(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphAddEdge(directedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    dirGraphAddEdge(directedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "C", "D");


    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "A"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "A"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "B"));

    destroyDirGraph(directedGraph);

}


void testDirectedGraphRemoveEdge(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphRemoveEdge(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphRemoveEdge(directedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    dirGraphRemoveEdge(directedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "C", "D");
    dirGraphAddEdge(directedGraph, "B", "D");
    dirGraphAddEdge(directedGraph, "A", "D");

    dirGraphRemoveEdge(directedGraph, "C", "D");
    dirGraphRemoveEdge(directedGraph, "B", "D");
    dirGraphRemoveEdge(directedGraph, "A", "D");


    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "A"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "A"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "B"));

    destroyDirGraph(directedGraph);

}


void testDirectedGraphContainsNode(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphContainsNode(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphContainsNode(directedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "A"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "B"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "D"));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    CuAssertIntEquals(cuTest, 1, dirGraphContainsNode(directedGraph, "A"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsNode(directedGraph, "B"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsNode(directedGraph, "C"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsNode(directedGraph, "D"));

    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "E"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "F"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "G"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsNode(directedGraph, "H"));

    destroyDirGraph(directedGraph);

}


void testDirectedGraphContainsEdge(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphContainsEdge(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphContainsEdge(directedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    char tempChar = 'A';
    dirGraphContainsEdge(directedGraph, &tempChar, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "C", "D");
    dirGraphAddEdge(directedGraph, "B", "D");
    dirGraphAddEdge(directedGraph, "A", "D");


    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "A", "B"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "C", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "A", "C"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "A", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "C"));
    CuAssertIntEquals(cuTest, 1, dirGraphContainsEdge(directedGraph, "B", "D"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "B", "A"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "C"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "A"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "C", "B"));
    CuAssertIntEquals(cuTest, 0, dirGraphContainsEdge(directedGraph, "D", "B"));

    destroyDirGraph(directedGraph);

}


void testDirectedGraphGetSize(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphGetSize(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 0, dirGraphGetSize(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    CuAssertIntEquals(cuTest, 1, dirGraphGetSize(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    CuAssertIntEquals(cuTest, 2, dirGraphGetSize(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    CuAssertIntEquals(cuTest, 3, dirGraphGetSize(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));
    CuAssertIntEquals(cuTest, 4, dirGraphGetSize(directedGraph));


    dirGraphRemoveNode(directedGraph, "A");
    CuAssertIntEquals(cuTest, 3, dirGraphGetSize(directedGraph));

    dirGraphRemoveNode(directedGraph, "B");
    CuAssertIntEquals(cuTest, 2, dirGraphGetSize(directedGraph));

    dirGraphRemoveNode(directedGraph, "C");
    CuAssertIntEquals(cuTest, 1, dirGraphGetSize(directedGraph));

    dirGraphRemoveNode(directedGraph, "D");
    CuAssertIntEquals(cuTest, 0, dirGraphGetSize(directedGraph));

    destroyDirGraph(directedGraph);

}


void testDirectedGraphIsEmpty(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphIsEmpty(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, dirGraphIsEmpty(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));


    dirGraphRemoveNode(directedGraph, "A");
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));

    dirGraphRemoveNode(directedGraph, "B");
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));

    dirGraphRemoveNode(directedGraph, "C");
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));

    dirGraphRemoveNode(directedGraph, "D");
    CuAssertIntEquals(cuTest, 1, dirGraphIsEmpty(directedGraph));

    destroyDirGraph(directedGraph);

}


void testClearDirectedGraph(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    clearDirGraph(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    CuAssertIntEquals(cuTest, 1, dirGraphIsEmpty(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));
    CuAssertIntEquals(cuTest, 0, dirGraphIsEmpty(directedGraph));

    clearDirGraph(directedGraph);
    CuAssertIntEquals(cuTest, 1, dirGraphIsEmpty(directedGraph));

    destroyDirGraph(directedGraph);

}


void testDestroyDirectedGraph(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    destroyDirGraph(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));

    destroyDirGraph(directedGraph);

}


ArrayList *printingDTList;

void printFunDGT(void *item) {
    arrayListAdd(printingDTList, item);
}

void nullFreeFunDGT(void *item) {}


void testDirectedGraphPrint(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphPrint(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphPrint(directedGraph, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "C", "D");

    printingDTList = arrayListInitialization(6, nullFreeFunDGT, NULL);
    dirGraphPrint(directedGraph, printFunDGT);

    CuAssertIntEquals(cuTest, 6, arrayListGetLength(printingDTList));
    CuAssertStrEquals(cuTest, "A", arrayListGet(printingDTList, 0));
    CuAssertStrEquals(cuTest, "B", arrayListGet(printingDTList, 1));
    CuAssertStrEquals(cuTest, "D", arrayListGet(printingDTList, 2));
    CuAssertStrEquals(cuTest, "C", arrayListGet(printingDTList, 3));
    CuAssertStrEquals(cuTest, "D", arrayListGet(printingDTList, 4));
    CuAssertStrEquals(cuTest, "B", arrayListGet(printingDTList, 5));


    destroyArrayList(printingDTList);
    destroyDirGraph(directedGraph);

}


void testDirectedGraphDepthFirstTraversal(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphDepthFirstTraversal(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphDepthFirstTraversal(directedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    dirGraphDepthFirstTraversal(directedGraph, "A", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    // A ----- B
    // |       |
    // |       |
    // C ----- D
    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "B", "D");
    dirGraphAddEdge(directedGraph, "A", "C");
    dirGraphAddEdge(directedGraph, "C", "D");

    printingDTList = arrayListInitialization(4, nullFreeFunDGT, NULL);
    dirGraphDepthFirstTraversal(directedGraph, "A", printFunDGT);

    CuAssertIntEquals(cuTest, 4, arrayListGetLength(printingDTList));
    CuAssertStrEquals(cuTest, "A", arrayListGet(printingDTList, 0));
    CuAssertStrEquals(cuTest, "C", arrayListGet(printingDTList, 1));
    CuAssertStrEquals(cuTest, "D", arrayListGet(printingDTList, 2));
    CuAssertStrEquals(cuTest, "B", arrayListGet(printingDTList, 3));


    destroyArrayList(printingDTList);
    destroyDirGraph(directedGraph);

}


void testDirectedGraphBreadthFirstTraversal(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphBreadthFirstTraversal(NULL, NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphBreadthFirstTraversal(directedGraph, NULL, NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);

    dirGraphBreadthFirstTraversal(directedGraph, "A", NULL);
    CuAssertIntEquals(cuTest, INVALID_ARG, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    // A ----- B
    // |       |
    // |       |
    // C ----- D
    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "B", "D");
    dirGraphAddEdge(directedGraph, "A", "C");
    dirGraphAddEdge(directedGraph, "C", "D");

    printingDTList = arrayListInitialization(4, nullFreeFunDGT, NULL);
    dirGraphBreadthFirstTraversal(directedGraph, "A", printFunDGT);

    CuAssertIntEquals(cuTest, 4, arrayListGetLength(printingDTList));
    CuAssertStrEquals(cuTest, "A", arrayListGet(printingDTList, 0));
    CuAssertStrEquals(cuTest, "B", arrayListGet(printingDTList, 1));
    CuAssertStrEquals(cuTest, "C", arrayListGet(printingDTList, 2));
    CuAssertStrEquals(cuTest, "D", arrayListGet(printingDTList, 3));


    destroyArrayList(printingDTList);
    destroyDirGraph(directedGraph);

}


void testDirectedGraphTopologicalSort(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphTopologicalSort(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    //          A
    //         / \
    //        /   \
    //       B     C
    //        \   /
    //         \ /
    //          D

    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "A", "C");
    dirGraphAddEdge(directedGraph, "B", "D");
    dirGraphAddEdge(directedGraph, "C", "D");

    ArrayList *valuesList = dirGraphTopologicalSort(directedGraph);

    CuAssertIntEquals(cuTest, 4, arrayListGetLength(valuesList));
    CuAssertStrEquals(cuTest, "A", arrayListGet(valuesList, 0));
    CuAssertStrEquals(cuTest, "C", arrayListGet(valuesList, 1));
    CuAssertStrEquals(cuTest, "B", arrayListGet(valuesList, 2));
    CuAssertStrEquals(cuTest, "D", arrayListGet(valuesList, 3));


    destroyArrayList(valuesList);
    destroyDirGraph(directedGraph);

}


void testDirectedGraphNodeIsPartOfCycle(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphNodeIsPartOfCycle(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    dirGraphNodeIsPartOfCycle(NULL, NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);


    dirGraphAddNode(directedGraph, generateCharPointerDGT("Z"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    //          Z
    //          |
    //          |
    //          A
    //         / \
    //        /   \
    //       B     C
    //        \   /
    //         \ /
    //          D

    dirGraphAddEdge(directedGraph, "A", "Z");
    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "A", "C");
    dirGraphAddEdge(directedGraph, "B", "D");
    dirGraphAddEdge(directedGraph, "D", "C");
    dirGraphAddEdge(directedGraph, "C", "A");

    CuAssertIntEquals(cuTest, 0, dirGraphNodeIsPartOfCycle(directedGraph, "Z"));
    CuAssertIntEquals(cuTest, 1, dirGraphNodeIsPartOfCycle(directedGraph, "A"));
    CuAssertIntEquals(cuTest, 1, dirGraphNodeIsPartOfCycle(directedGraph, "B"));
    dirGraphRemoveEdge(directedGraph, "C", "A");

    CuAssertIntEquals(cuTest, 0, dirGraphNodeIsPartOfCycle(directedGraph, "B"));
    CuAssertIntEquals(cuTest, 0, dirGraphNodeIsPartOfCycle(directedGraph, "A"));

    destroyDirGraph(directedGraph);

}


void testDirectedGraphHasACycle(CuTest *cuTest) {

    DirectedGraph *directedGraph = directedGraphInitialization(free, directedGraphTestStrcmp, charArrHashFunDGT);

    dirGraphHasACycle(NULL);
    CuAssertIntEquals(cuTest, NULL_POINTER, ERROR_TEST->errorCode);

    CuAssertIntEquals(cuTest, 0, dirGraphHasACycle(directedGraph));

    dirGraphAddNode(directedGraph, generateCharPointerDGT("Z"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("A"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("B"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("C"));
    dirGraphAddNode(directedGraph, generateCharPointerDGT("D"));


    //          Z
    //          |
    //          |
    //          A
    //         / \
    //        /   \
    //       B     C
    //        \   /
    //         \ /
    //          D

    dirGraphAddEdge(directedGraph, "Z", "A");
    dirGraphAddEdge(directedGraph, "A", "B");
    dirGraphAddEdge(directedGraph, "A", "C");
    dirGraphAddEdge(directedGraph, "B", "D");
    dirGraphAddEdge(directedGraph, "D", "C");
    dirGraphAddEdge(directedGraph, "C", "A");

    CuAssertIntEquals(cuTest, 1, dirGraphHasACycle(directedGraph));
    dirGraphRemoveEdge(directedGraph, "C", "A");

    CuAssertIntEquals(cuTest, 0, dirGraphHasACycle(directedGraph));

    destroyDirGraph(directedGraph);

}


CuSuite *createDirectedGraphTestsSuite(void) {

    CuSuite *suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, testInvalidDirectedGraphInitialization);
    SUITE_ADD_TEST(suite, testValidDirectedGraphInitialization);
    SUITE_ADD_TEST(suite, testDirectedGraphAddNode);
    SUITE_ADD_TEST(suite, testDirectedGraphRemoveNode);
    SUITE_ADD_TEST(suite, testDirectedGraphRemoveNodeWtoFr);
    SUITE_ADD_TEST(suite, testDirectedGraphAddEdge);
    SUITE_ADD_TEST(suite, testDirectedGraphRemoveEdge);
    SUITE_ADD_TEST(suite, testDirectedGraphContainsNode);
    SUITE_ADD_TEST(suite, testDirectedGraphContainsEdge);
    SUITE_ADD_TEST(suite, testDirectedGraphGetSize);
    SUITE_ADD_TEST(suite, testDirectedGraphIsEmpty);
    SUITE_ADD_TEST(suite, testClearDirectedGraph);
    SUITE_ADD_TEST(suite, testDestroyDirectedGraph);
    SUITE_ADD_TEST(suite, testDirectedGraphPrint);
    SUITE_ADD_TEST(suite, testDirectedGraphDepthFirstTraversal);
    SUITE_ADD_TEST(suite, testDirectedGraphBreadthFirstTraversal);
    SUITE_ADD_TEST(suite, testDirectedGraphTopologicalSort);
    SUITE_ADD_TEST(suite, testDirectedGraphNodeIsPartOfCycle);
    SUITE_ADD_TEST(suite, testDirectedGraphHasACycle);

    return suite;

}


void directedGraphUnitTest(void) {

    ERROR_TEST = (ErrorTestStruct *) malloc(sizeof(ErrorTestStruct));

    CuString *output = CuStringNew();
    CuStringAppend(output, "**Directed Graph Test**\n");

    CuSuite *suite = createDirectedGraphTestsSuite();

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);

    free(ERROR_TEST);

}