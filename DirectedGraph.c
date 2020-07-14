#include "DirectedGraph.h"






 ///Note: The directed graph will copy any passed values as a parameter, because a lot of nodes will be connected,
 ///so we don't want the graph to access inaccessible memory because it's already freed,
 ///so after you pass any value as a parameter, the graph will free the passed values immediately.






void (*dGFreeItem)(void *key);


void freeDGraphItem(void *item) {
    DirGraphNode *itemToFree =  (DirGraphNode *) item;
    dGFreeItem(itemToFree->value);
    destroyArrayList(itemToFree->adjacentNodes);
    free(itemToFree);

}


DirectedGraph *directedGraphInitialization(void (*freeItem)(void *)) {
    DirectedGraph *directedGraph = (DirectedGraph *) malloc(sizeof(DirectedGraph));

    dGFreeItem = freeItem;
    //directedGraph->nodes = hashMapInitialization(freeItem, freeDGraphItem);

    return directedGraph;

}


void dirGraphAddNode(DirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }


    if (hashMapContains(graph->nodes, value, sizeOfValue))
        return;


    void *copiedValue = (void *) malloc(sizeOfValue);
    memcpy(copiedValue, value, sizeOfValue);

    DirGraphNode *newNode = (DirGraphNode *) malloc(sizeof(DirGraphNode));
    newNode->value = copiedValue;
    newNode->sizeOfValue = sizeOfValue;
    newNode->adjacentNodes = arrayListInitialization(5, freeDGraphItem);
    hashMapInsert(graph->nodes, value, sizeOfValue, newNode, sizeof(DirGraphNode));

}




/*int comp(const void *p1, const void *p2) {

}*/

void dirGraphRemoveNode(DirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    hashMapDelete(graph->nodes, value, sizeOfValue);
    void **hashMapNodes = (void **) hashMapToArray(graph->nodes);
    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        //int index = arrayListGetIndex( ((DirGraphNode *) hashMapNodes)->adjacentNodes , value, sizeOfValue);

    }

}