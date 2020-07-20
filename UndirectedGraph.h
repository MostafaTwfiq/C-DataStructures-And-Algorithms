#ifndef C_DATASTRUCTURES_UNDIRECTEDGRAPH_H
#define C_DATASTRUCTURES_UNDIRECTEDGRAPH_H

#include "Headers/HashMap.h"
#include "Headers/ArrayList.h"


typedef struct UDGraphNode {
    void *value;
    ArrayList *adjacentNodes;
    void (*freeFun)(void *);
    int (*compFun)(const void *, const void*);
} UDGraphNode;


typedef struct UDGraphEdge {
    UDGraphNode *node;
    int weight;
} UDGraphEdge;


typedef struct UndirectedGraph {
    HashMap *nodes;
    void (*freeFun)(void *);
    int (*compFun)(const void *, const void*);

} UndirectedGraph;



UndirectedGraph *undirectedGraphInitialization(void (*freeFun)(void *), int (*compFun)(const void*, const void*));

void UDGraphAddNode(UndirectedGraph *graph, void *value, int sizeOfValue);

void UDGraphAddEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize, int edgeWeight);

void UDGraphRemoveNode(UndirectedGraph *graph, void *value, int sizeOfValue);

void *UDGraphRemoveNodeWtoFr(UndirectedGraph *graph, void *value, int sizeOfValue);

void UDGraphRemoveEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize);

int UDGraphContainsNode(UndirectedGraph *graph, void *value, int sizeOfValue);

int UDGraphContainsEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize);

void printUDGraph(UndirectedGraph *graph, void (*printFun)(void *));

int UDGraphGetSize(UndirectedGraph *graph);

int UDGraphIsEmpty(UndirectedGraph *graph);

void clearUDGraph(UndirectedGraph *graph);

void destroyUDGraph(UndirectedGraph *graph);

#endif //C_DATASTRUCTURES_UNDIRECTEDGRAPH_H
