#ifndef C_DATASTRUCTURES_DIRECTEDGRAPH_H
#define C_DATASTRUCTURES_DIRECTEDGRAPH_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct DirGraphNode {
    void *value;
    struct ArrayList *adjacentNodes;
    int (*valueCompFun)(const void *, const void *);
} DirGraphNode;


typedef struct DirectedGraph {
    struct HashMap *nodes;
    void (*freeValue)(void *);
    int (*valueComp)(const void *, const void *);
} DirectedGraph;



DirectedGraph *directedGraphInitialization(void (*freeValue)(void *), int (*valueComp)(const void *, const void *));


void dirGraphAddNode(DirectedGraph *graph, void *value, int sizeOfValue);


void dirGraphRemoveNode(DirectedGraph *graph, void *value, int sizeOfValue);


void *dirGraphRemoveNodeWtoFr(DirectedGraph *graph, void *value, int sizeOfValue);


void dirGraphAddEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal);


void dirGraphRemoveEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal);


int dirGraphContainsEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal);


int dirGraphContainsNode(DirectedGraph *graph, void *value, int sizeOfValue);


int dirGraphGetNumOfNodes(DirectedGraph *graph);


int dirGraphIsEmpty(DirectedGraph *graph);


void clearDirGraph(DirectedGraph *graph);


void destroyDirGraph(DirectedGraph *graph);


void dirGraphPrint(DirectedGraph *graph, void (*printVal)(void *));


void dirGraphDepthFirstTraversal(DirectedGraph *graph, void *startVal, int sizeOfValue, void (*printVal)(void *));


void dirGraphBreadthFirstTraversal(DirectedGraph *graph, void *startVal, int sizeOfValue, void (*printVal)(void *));


struct ArrayList *dirGraphTopologicalSort(DirectedGraph *graph);


#ifdef __cplusplus
}
#endif


#endif //C_DATASTRUCTURES_DIRECTEDGRAPH_H
