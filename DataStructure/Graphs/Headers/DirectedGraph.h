#ifndef C_DATASTRUCTURES_DIRECTEDGRAPH_H
#define C_DATASTRUCTURES_DIRECTEDGRAPH_H

#ifdef __cplusplus
extern "C" {
#endif



typedef struct DirectedGraph {
    struct HashMap *nodes;
    void (*freeValue)(void *);
    int (*valueComp)(const void *, const void *);
} DirectedGraph;



DirectedGraph *directedGraphInitialization(void (*freeValue)(void *), int (*valueComp)(const void *, const void *), int (*hashFun)(const void *));

void dirGraphAddNode(DirectedGraph *graph, void *value);

void dirGraphRemoveNode(DirectedGraph *graph, void *value);

void *dirGraphRemoveNodeWtoFr(DirectedGraph *graph, void *value);

void dirGraphAddEdge(DirectedGraph *graph, void *fromVal, void *toVal);

void dirGraphRemoveEdge(DirectedGraph *graph, void *fromVal, void *toVal);

int dirGraphContainsEdge(DirectedGraph *graph, void *fromVal, void *toVal);

int dirGraphContainsNode(DirectedGraph *graph, void *value);

int dirGraphGetNumOfNodes(DirectedGraph *graph);

int dirGraphIsEmpty(DirectedGraph *graph);

void clearDirGraph(DirectedGraph *graph);

void destroyDirGraph(DirectedGraph *graph);

void dirGraphPrint(DirectedGraph *graph, void (*printVal)(void *));

void dirGraphDepthFirstTraversal(DirectedGraph *graph, void *startVal, void (*printVal)(void *));

void dirGraphBreadthFirstTraversal(DirectedGraph *graph, void *startVal, void (*printVal)(void *));

struct ArrayList *dirGraphTopologicalSort(DirectedGraph *graph);

int dirGraphNodeIsPartOfCycle(DirectedGraph *graph, void *startValue);

int dirGraphHasACycle(DirectedGraph *graph);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_DIRECTEDGRAPH_H
