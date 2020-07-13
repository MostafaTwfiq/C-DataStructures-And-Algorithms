#include "DirectedGraph.h"




DirectedGraph *directedGraphInitialization(int sizeOfType, void (*freeItem)(void *)) {
    DirectedGraph *directedGraph = (DirectedGraph *) malloc(sizeof(DirectedGraph));

    //directedGraph->nodes = hashMapInitialization(sizeof(DirGraphNode));
    directedGraph->sizeOfType = sizeOfType;
    directedGraph->freeItem = freeItem;

    return directedGraph;

}


void dirGraphAddNode(DirectedGraph *graph, void *value) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    if (hashMapContains(graph->nodes, value, graph->sizeOfType))
        return;

    DirGraphNode *newNode = (DirGraphNode *) malloc(sizeof(DirGraphNode));
    newNode->value = value;
    //newNode->adjacentNodes = arrayListInitialization(5, sizeof(DirGraphNode));
    //hashMapInsert(graph->nodes, value, newNode, graph->sizeOfItem);

}


void dirGraphRemoveNode(DirectedGraph *graph, void *value) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    DirGraphNode *node = (DirectedGraph *) hashMapGet(graph->nodes, value, graph->sizeOfType);
}