#ifndef C_DATASTRUCTURES_UNDIRECTEDGRAPH_H
#define C_DATASTRUCTURES_UNDIRECTEDGRAPH_H

#ifdef __cplusplus
extern "C" {
#endif





typedef struct UndirectedGraph {
    struct HashMap *nodes;
    void (*freeFun)(void *);
    int (*compFun)(const void *, const void*);

} UndirectedGraph;






UndirectedGraph *undirectedGraphInitialization(void (*freeFun)(void *), int (*compFun)(const void*, const void*), int (*hashFun)(const void *));

void UDGraphAddNode(UndirectedGraph *graph, void *value);

void UDGraphAddEdge(UndirectedGraph *graph, void *fValue, void *sValue, int edgeWeight);

void UDGraphRemoveNode(UndirectedGraph *graph, void *value);

void *UDGraphRemoveNodeWtoFr(UndirectedGraph *graph, void *value);

void UDGraphRemoveEdge(UndirectedGraph *graph, void *fValue, void *sValue);

int UDGraphContainsNode(UndirectedGraph *graph, void *value);

int UDGraphContainsEdge(UndirectedGraph *graph, void *fValue, void *sValue);

void printUDGraph(UndirectedGraph *graph, void (*printFun)(void *));

int UDGraphGetSize(UndirectedGraph *graph);

int UDGraphIsEmpty(UndirectedGraph *graph);

void clearUDGraph(UndirectedGraph *graph);

void destroyUDGraph(UndirectedGraph *graph);

int UDGraphGetShortestDistance(UndirectedGraph *graph, void *startVal, void *endVal);

struct ArrayList *UDGraphGetShortestPath(UndirectedGraph *graph, void *startVal, void *endVal);

int UDGraphNodePartOfCycle(UndirectedGraph *graph, void *startVal);

int UDGraphHasCycle(UndirectedGraph *graph);

UndirectedGraph *UDGraphMinimumSpanningGraph(UndirectedGraph *graph, void *startVal);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_UNDIRECTEDGRAPH_H
