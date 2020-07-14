#ifndef C_DATASTRUCTURES_DIRECTEDGRAPH_H
#define C_DATASTRUCTURES_DIRECTEDGRAPH_H


#include "ArrayList.h"
#include "HashMap.h"
#include "HashSet.h"


typedef struct DirGraphNode {
    void *value;
    int sizeOfValue;
    ArrayList *adjacentNodes;
} DirGraphNode;




typedef struct DirectedGraph {
    HashMap *nodes;
} DirectedGraph;



DirectedGraph *directedGraphInitialization(void (*freeValue)(void *), int (*valueComp)(const void *key1, int s1, const void *key2, int s2));


void dirGraphAddNode(DirectedGraph *graph, void *value, int sizeOfValue);


void dirGraphRemoveNode(DirectedGraph *graph, void *value, int sizeOfValue);


void dirGraphAddEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal);


void dirGraphRemoveEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal);


int dirGraphContainsEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal);


int dirGraphContainsNode(DirectedGraph *graph, void *value, int sizeOfValue);


int dirGraphGetNumOfNodes(DirectedGraph *graph);


int dirGraphIsEmpty(DirectedGraph *graph);


void clearDirGraph(DirectedGraph *graph);


void destroyDirGraph(DirectedGraph *graph);


void dirGraphPrint(DirectedGraph *graph, void (*printVal)(void *));


void dirGraphDepthFirstTraversal(DirectedGraph *graph, void (*printVal)(void *));


#endif //C_DATASTRUCTURES_DIRECTEDGRAPH_H
