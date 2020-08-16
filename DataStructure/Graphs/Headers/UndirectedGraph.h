#ifndef C_DATASTRUCTURES_UNDIRECTEDGRAPH_H
#define C_DATASTRUCTURES_UNDIRECTEDGRAPH_H

#ifdef __cplusplus
extern "C" {
#endif


/** @struct UndirectedGraph
*  @brief This structure implements a basic generic undirected graph.
*  @var UndirectedGraph::nodes
*  Member 'nodes' is a pointer to the nodes hash map.
*  @var UndirectedGraph::freeFun
*  Member 'freeFun' is a pointer to the free function, that will free the graph values.
*  @var UndirectedGraph::compFun
*  Member 'compFun' is a pointer to the comparator function, that will compare the graph values.
*/

typedef struct UndirectedGraph {
    struct HashMap *nodes;

    void (*freeFun)(void *);

    int (*compFun)(const void *, const void *);

} UndirectedGraph;


UndirectedGraph *undirectedGraphInitialization(void (*freeFun)(void *), int (*compFun)(const void *, const void *),
                                               int (*hashFun)(const void *));

void udGraphAddNode(UndirectedGraph *graph, void *value);

void udGraphAddEdge(UndirectedGraph *graph, void *fValue, void *sValue, int edgeWeight);

void udGraphRemoveNode(UndirectedGraph *graph, void *value);

void *udGraphRemoveNodeWtoFr(UndirectedGraph *graph, void *value);

void udGraphRemoveEdge(UndirectedGraph *graph, void *fValue, void *sValue);

int udGraphContainsNode(UndirectedGraph *graph, void *value);

int udGraphContainsEdge(UndirectedGraph *graph, void *fValue, void *sValue);

int udGraphGetEdgeWeight(UndirectedGraph *graph, void *fValue, void *sValue);

void printUDGraph(UndirectedGraph *graph, void (*printFun)(void *));

int udGraphGetSize(UndirectedGraph *graph);

int udGraphIsEmpty(UndirectedGraph *graph);

void clearUDGraph(UndirectedGraph *graph);

void destroyUDGraph(void *graph);

int udGraphGetShortestDistance(UndirectedGraph *graph, void *startVal, void *endVal);

struct ArrayList *udGraphGetShortestPath(UndirectedGraph *graph, void *startVal, void *endVal);

int udGraphNodePartOfCycle(UndirectedGraph *graph, void *startVal);

int udGraphHasCycle(UndirectedGraph *graph);

UndirectedGraph *udGraphMinimumSpanningGraph(UndirectedGraph *graph, void *startVal);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_UNDIRECTEDGRAPH_H
