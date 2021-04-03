#include "../Headers/UndirectedGraph.h"
#include "../../Tables/Headers/HashMap.h"
#include "../../Tables/Headers/HashSet.h"
#include "../../Stacks/Headers/Stack.h"
#include "../../Queues/Headers/Queue.h"
#include "../../Queues/Headers/PriorityQueue.h"
#include "../../Lists/Headers/ArrayList.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"


#if defined(__BORLANDC__)
typedef unsigned char uint8_t;
typedef __int64 int64_t;
typedef unsigned long uintptr_t;
#elif defined(_MSC_VER)
typedef unsigned char uint8_t;
typedef __int64 int64_t;
#else

#include <stdint.h>

#endif


/** @struct UDGraphNode
*  @brief This structure implements a basic directed graph node.
*  @var UDGraphNode::value
*  Member 'value' is a pointer to the node value.
*  @var UDGraphNode::adjacentNodes
*  Member 'adjacentNodes' is a pointer to the adjacent nodes array list.
* @var UDGraphNode::freeFun
*  Member 'freeFun' is a pointer to the free function, that will free the graph values.
*  @var UDGraphNode::compFun
*  Member 'compFun' is a pointer to the comparator function, that will compare the graph values.
*/

typedef struct UDGraphNode {
    void *value;
    ArrayList *adjacentNodes;

    void (*freeFun)(void *);

    int (*compFun)(const void *, const void *);
} UDGraphNode;


typedef struct UDGraphEdge {
    UDGraphNode *node;
    int weight;
} UDGraphEdge;


/** This struct will be useful in getting shortest distance and minimum spanning. */

typedef struct DistanceHolder {
    UDGraphNode *toNode;
    UDGraphNode *fromNode;
    int distance;
} DistanceHolder;


HashMap *UDGraphGenerateDistancesMap(UDGraphNode *startNode);


int UDGraphNodePartOfCycleR(UDGraphNode *prevNode, UDGraphNode *currentNode, HashSet *visitedNodes);


/** This function take a node as it's parameter,
 * then it will free the node without freeing it's value.
 *
 * @param node the node address
 */

void UDGraphNodeFreeFun(void *node) {
    UDGraphNode *nodeToFree = (UDGraphNode *) node;
    destroyArrayList(nodeToFree->adjacentNodes);
    free(node);
}


/** This function will take an edge as it's parameter,
 * then it will free the edge without freeing it's node.
 *
 * @param edge the edge pointer
 */

void UDGraphEdgeFreeFun(void *edge) {
    UDGraphEdge *edgeToFree = (UDGraphEdge *) edge;
    free(edgeToFree);
}


/** This function will take two edges then it will compare there nodes values.
 *
 * Note: if the function returned zero, then the two edges are equal.
 *
 * @param e1 the first edge pointer
 * @param e2 the second edge pointer
 * @return it will return zero if the two nodes are equal, minus if the second bigger, and positive if the first bigger
 */

int UDGraphEdgeComp(const void *e1, const void *e2) {
    UDGraphEdge *edge1 = (UDGraphEdge *) e1;
    UDGraphEdge *edge2 = (UDGraphEdge *) e2;

    return edge1->node->compFun(edge1->node->value, edge2->node->value);
}


/** This function will take two nodes then it will compare them by there value.
 *
 * @param n1 the first node pointer
 * @param n2 the second node pointer
 * @return it will return zero if the two nodes are equal
 */

int UDGraphNodeComp(const void *n1, const void *n2) {
    UDGraphNode *node1 = (UDGraphNode *) n1;
    UDGraphNode *node2 = (UDGraphNode *) n2;

    int returnValue = node1->compFun(node1->value, node2->value);
    return returnValue;
}


/** This function will initialize a new undirected graph in the memory,
 * then return it.
 *
 * Note: because the graph is implemented by hash map, you need to pass the hashing function.
 *
 * @param freeFun the values freeing function pointer
 * @param compFun the values comparing function pointer
 * @param hashFun the hashing function that will return a unique integer representing the hash map key
 * @return it will return the new initialized graph pointer
 */

UndirectedGraph *undirectedGraphInitialization(void (*freeFun)(void *), int (*compFun)(const void *, const void *),
                                               int (*hashFun)(const void *)) {

    if (freeFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeing function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (compFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparing function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (compFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif
    }

    UndirectedGraph *graph = (UndirectedGraph *) malloc(sizeof(UndirectedGraph));
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "graph", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    graph->nodes = hashMapInitialization(freeFun, UDGraphNodeFreeFun, compFun, hashFun);
    graph->freeFun = freeFun;
    graph->compFun = compFun;

    return graph;

}


/** This function will add the provided value in a new node in the graph.
 *
 * Note: if the node is already exist in the graph, then the function will free the passed value.
 *
 * @param graph the graph pointer
 * @param value the new value pointer
 */

void udGraphAddNode(UndirectedGraph *graph, void *value) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    if (hashMapContains(graph->nodes, value)) {
        graph->freeFun(value);
        return;
    }

    UDGraphNode *newNode = (UDGraphNode *) malloc(sizeof(UDGraphNode));
    if (newNode == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    newNode->value = value;
    newNode->freeFun = graph->freeFun;
    newNode->compFun = graph->compFun;
    newNode->adjacentNodes = arrayListInitialization(5, UDGraphEdgeFreeFun, UDGraphEdgeComp);

    hashMapInsert(graph->nodes, value, newNode);

}


/** This function will take two nodes and then it will add a new edge between them.
 *
 * Note: it there was already an edge between the two values then the function will update the weight.
 *
 * Note: the function will note free the passed values.
 *
 * @param graph the graph pointer
 * @param fValue the first value pointer
 * @param sValue the second value pointer
 * @param edgeWeight the weight of the new edge
 */

void udGraphAddEdge(UndirectedGraph *graph, void *fValue, void *sValue, int edgeWeight) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (fValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "first value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (sValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (edgeWeight < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "edge weight", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *fNode = hashMapGet(graph->nodes, fValue);
    UDGraphNode *sNode = hashMapGet(graph->nodes, sValue);
    if (fNode == NULL || sNode == NULL)
        return;

    UDGraphEdge *fNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    UDGraphEdge *sNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    if (fNewEdge == NULL || sNewEdge == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new edge", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
#endif

    }


    fNewEdge->node = sNode;
    fNewEdge->weight = edgeWeight;

    sNewEdge->node = fNode;
    sNewEdge->weight = edgeWeight;

    int fEdgeIndex = arrayListGetIndex(fNode->adjacentNodes, fNewEdge);
    int sEdgeIndex = arrayListGetIndex(sNode->adjacentNodes, sNewEdge);
    if (fEdgeIndex >= 0 && sEdgeIndex >= 0) {
        UDGraphEdge *fTempEdge = arrayListGet(fNode->adjacentNodes, fEdgeIndex);
        UDGraphEdge *sTempEdge = arrayListGet(sNode->adjacentNodes, sEdgeIndex);
        fTempEdge->weight = sTempEdge->weight = edgeWeight;

        free(fNewEdge);
        free(sNewEdge);
        return;
    }


    arrayListAdd(fNode->adjacentNodes, fNewEdge);
    arrayListAdd(sNode->adjacentNodes, sNewEdge);

}


/** This function will take a node value,
 * then it will remove and free the node with it's value from the graph.
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph pointer
 * @param value the value pointer
 */

void udGraphRemoveNode(UndirectedGraph *graph, void *value) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *node = hashMapGet(graph->nodes, value);

    if (node == NULL)
        return;

    UDGraphEdge *tempNodeEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    tempNodeEdge->node = node;

    for (int i = 0; i < arrayListGetLength(node->adjacentNodes); i++) {
        UDGraphEdge *tempEdge = (UDGraphEdge *) arrayListGet(node->adjacentNodes, i);
        arrayListRemoveAtIndex(tempEdge->node->adjacentNodes,
                               arrayListGetIndex(tempEdge->node->adjacentNodes, tempNodeEdge));

    }

    free(tempNodeEdge);
    hashMapDelete(graph->nodes, value);

}


/** This function will take a node value,
 * then it will remove and free the node from the graph without freeing the node value.
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph pointer
 * @param value the value pointer
 */

void *udGraphRemoveNodeWtoFr(UndirectedGraph *graph, void *value) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *node = hashMapGet(graph->nodes, value);

    if (node == NULL)
        return NULL;

    UDGraphEdge *tempNodeEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    tempNodeEdge->node = node;

    for (int i = 0; i < arrayListGetLength(node->adjacentNodes); i++) {
        UDGraphEdge *tempEdge = (UDGraphEdge *) arrayListGet(node->adjacentNodes, i);
        arrayListRemoveAtIndex(tempEdge->node->adjacentNodes,
                               arrayListGetIndex(tempEdge->node->adjacentNodes, tempNodeEdge));

    }

    free(tempNodeEdge);
    hashMapDeleteWtoFrAll(graph->nodes, value);
    void *returnValue = node->value;
    UDGraphNodeFreeFun(node);

    return returnValue;

}


/** This function will take two value,
 * then it will remove the edge between them it found.
 *
 * Note: the function will not free the passed values.
 *
 * @param graph the graph pointer
 * @param fValue the fist value pointer
 * @param sValue the second value pointer
 */

void udGraphRemoveEdge(UndirectedGraph *graph, void *fValue, void *sValue) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (fValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "fist value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (sValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *fNode = hashMapGet(graph->nodes, fValue);
    UDGraphNode *sNode = hashMapGet(graph->nodes, sValue);
    if (fNode == NULL || sNode == NULL)
        return;

    UDGraphEdge *fNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    UDGraphEdge *sNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    if (fNewEdge == NULL || sNewEdge == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "graph nodes", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
    }

    fNewEdge->node = sNode;
    sNewEdge->node = fNode;

    int fEdgeIndex = arrayListGetIndex(fNode->adjacentNodes, fNewEdge);
    int sEdgeIndex = arrayListGetIndex(sNode->adjacentNodes, sNewEdge);
    if (fEdgeIndex >= 0 && sEdgeIndex >= 0) {
        arrayListRemoveAtIndex(fNode->adjacentNodes, fEdgeIndex);
        arrayListRemoveAtIndex(sNode->adjacentNodes, sEdgeIndex);
    }

    free(fNewEdge);
    free(sNewEdge);

}


/** This function will check if the passed value exist in the graph or not.
 * The function will return one (1) if the value exists, other wise it will return zero (0).
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph pointer
 * @param value the value pointer
 * @return it will return one if the value exists in the graph, other wise it will return zero
 */

int udGraphContainsNode(UndirectedGraph *graph, void *value) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    return hashMapContains(graph->nodes, value);

}


/** This function will take two value then it will check if there is an edge between them,
 * if there was then the function will return one (1), other wise it will return zero (0).
 *
 * Note: the function will not free the passed values.
 *
 * @param graph the graph pointer
 * @param fValue the first value pointer
 * @param sValue the second value pointer
 * @return it will return one if the edge exist, other wise it will return zero
 */

int udGraphContainsEdge(UndirectedGraph *graph, void *fValue, void *sValue) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (fValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "first value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (sValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *fNode = hashMapGet(graph->nodes, fValue);
    UDGraphNode *sNode = hashMapGet(graph->nodes, sValue);
    if (fNode == NULL || sNode == NULL)
        return 0;

    UDGraphEdge *fNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    UDGraphEdge *sNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    if (fNewEdge == NULL || sNewEdge == NULL) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return -1;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new edge", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    fNewEdge->node = fNode;
    sNewEdge->node = sNode;

    int fEdgeIndex = arrayListGetIndex(fNode->adjacentNodes, sNewEdge);
    int sEdgeIndex = arrayListGetIndex(sNode->adjacentNodes, fNewEdge);

    free(fNewEdge);
    free(sNewEdge);


    return fEdgeIndex >= 0 && sEdgeIndex >= 0;

}


/** This function will take two value then it will check if there is an edge between them,
 * if there was then the function will return the weight of the edge, other wise it will return minus one (-1).
 *
 * Note: the function will not free the passed values.
 *
 * @param graph the graph pointer
 * @param fValue the first value pointer
 * @param sValue the second value pointer
 * @return it will return the edge weight, other wise it will return -1
 */

int udGraphGetEdgeWeight(UndirectedGraph *graph, void *fValue, void *sValue) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (fValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "first value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (sValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "second value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *fNode = hashMapGet(graph->nodes, fValue);
    UDGraphNode *sNode = hashMapGet(graph->nodes, sValue);
    if (fNode == NULL || sNode == NULL)
        return -1;

    UDGraphEdge *tempEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    tempEdge->node = sNode;
    UDGraphEdge *targetEdge = (UDGraphEdge *) arrayListGet(fNode->adjacentNodes,
                                                           arrayListGetIndex(fNode->adjacentNodes, tempEdge));

    UDGraphEdgeFreeFun(tempEdge);

    return targetEdge != NULL ? targetEdge->weight : -1;

}


/** This function will print the graph nodes as following:
 *
 * <<
 *
 * The node: //the node name
 *
 * Is connected to:
 *
 * // the connected nodes names --weight--> (the edge weight)
 *
 * .....
 *
 * >>
 *
 * @param graph the graph pointer
 * @param printFun the values printing function pointer
 */

void printUDGraph(UndirectedGraph *graph, void (*printFun)(void *)) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    }
    if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode **nodesArray = (UDGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
        printf("The node: ");
#endif

        printFun(nodesArray[i]->value);

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
        printf("\nIs connected to:\n");
#endif

        for (int j = 0; j < arrayListGetLength(nodesArray[i]->adjacentNodes); j++) {

            UDGraphEdge *tempEdge = (UDGraphEdge *) arrayListGet(nodesArray[i]->adjacentNodes, j);
            printFun(tempEdge->node->value);

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
            fprintf(stdout, " --weight--> %d\n", tempEdge->weight);
#endif

        }

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
        printf("\n\n");
#endif

    }

}


/** This function will return the number of nodes in the graph.
 *
 * @param graph the graph pointer
 * @return it will return the number of nodes in the graph
 */

int udGraphGetSize(UndirectedGraph *graph) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    }

    return hashMapGetLength(graph->nodes);

}


/** This function will check if the graph is empty,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * @param graph the graph pointer
 * @return it will return one if the graph was empty, other wise it will return zero
 */

int udGraphIsEmpty(UndirectedGraph *graph) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    }

    return hashMapIsEmpty(graph->nodes);

}


/** This function will clear and free the graph nodes and value,
 * without freeing the graph.
 *
 * @param graph the graph pointer
 */

void clearUDGraph(UndirectedGraph *graph) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    }

    clearHashMap(graph->nodes);

}


/** This function will destroy and free the graph, with all it's nodes and values.
 *
 * @param graph the graph pointer
 */

void destroyUDGraph(void *graph) {

    if (graph == NULL) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    }

    destroyHashMap(((UndirectedGraph *) graph)->nodes);
    free(graph);

}


/** This function will take an uintptr_t pointer as a parameter,
 * then it will free it.
 *
 * This function will be useful in traversal functions.
 *
 * @param uintptr_tPointer the uintptr_t address
 */

void UDGFreeUintptr_t(void *uintptr_tPointer) {
    free(uintptr_tPointer);
}


/** This function will take two uintptr_t pointer as a parameters,
 * then it will compare the two uintptr_t.
 *
 * This function will be useful in traversal functions.
 *
 * @param uintptr_tPointer1 the first uintptr_t address
 * @param uintptr_tPointer2 the second uintptr_t address
 * @return it will return zero if the two uintptr_t are equal.
 */

int UDGCompUintptr_t(const void *uintptr_tPointer1, const void *uintptr_tPointer2) {
    return (int) (*(uintptr_t *) uintptr_tPointer1 - *(uintptr_t *) uintptr_tPointer2);
}


/** This function will take an uintptr_t pointer as a parameter,
 * then it will return the value of the uintptr_t.
 *
 * Note: this function will be useful to use in the hash map and hash set data structures.
 *
 * @param item the uintptr_t pointer
 * @return it will return the value of the uintptr_t as the unique hash key
 */

int uintptr_tHashFunUDirG(const void *item) {
    return (int) *(uintptr_t *) item;
}


/** This function will depth first traverse the graph.
 *
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 *
 * @param graph the graph address
 * @param startVal the start node value address
 * @param printVal the printing function address, that will be called to print the value
 */

void UDGraphDepthFirstTraversal(UndirectedGraph *graph, void *startVal, void (*printFun)(void *)) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    Stack *nodesStack = stackInitialization(UDGraphNodeFreeFun);
    HashSet *visitedNodes = hashSetInitialization(UDGFreeUintptr_t, UDGCompUintptr_t, uintptr_tHashFunUDirG);

    stackPush(nodesStack, startNode);
    uintptr_t *startNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
    *startNodeValAddress = (uintptr_t) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress);


    while (!stackIsEmpty(nodesStack)) {
        UDGraphNode *tempNode = stackPop(nodesStack);
        printFun(tempNode->value);

        for (int i = 0; i < arrayListGetLength(tempNode->adjacentNodes); i++) {
            UDGraphNode *adjNode = ((UDGraphEdge *) arrayListGet(tempNode->adjacentNodes, i))->node;
            uintptr_t *adjNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
            *adjNodeValAddress = (uintptr_t) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress)) {
                stackPush(nodesStack, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress);
            } else
                free(adjNodeValAddress);

        }
    }


    destroyStack(nodesStack);
    destroyHashSet(visitedNodes);

}


/** This function will breadth first traverse the graph.
 *
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 *
 * @param graph the graph address
 * @param startVal the start node value address
 * @param printVal the printing function address, that will be called to print the value
 */

void UDGraphBreadthFirstTraversal(UndirectedGraph *graph, void *startVal, void (*printFun)(void *)) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (printFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    Queue *nodesQueue = queueInitialization(UDGraphNodeFreeFun);
    HashSet *visitedNodes = hashSetInitialization(UDGFreeUintptr_t, UDGCompUintptr_t, uintptr_tHashFunUDirG);

    queueEnqueue(nodesQueue, startNode);
    uintptr_t *startNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
    *startNodeValAddress = (uintptr_t) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress);


    while (!queueIsEmpty(nodesQueue)) {
        UDGraphNode *tempNode = queueDequeue(nodesQueue);
        printFun(tempNode->value);

        for (int i = 0; i < arrayListGetLength(tempNode->adjacentNodes); i++) {
            UDGraphNode *adjNode = ((UDGraphEdge *) arrayListGet(tempNode->adjacentNodes, i))->node;
            uintptr_t *adjNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
            *adjNodeValAddress = (uintptr_t) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress)) {
                queueEnqueue(nodesQueue, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress);
            } else
                free(adjNodeValAddress);

        }
    }


    destroyQueue(nodesQueue);
    destroyHashSet(visitedNodes);

}


/** This function will take two distances holders,
 * then it will compare them with the distance.
 *
 * Note: this function should only be called from the undirected graph functions.
 *
 * @param holder1 the first holder pointer
 * @param holder2 the second holder pointer
 * @return it will return zero if they are equal, minus if the second one bigger, and positive if the first one bigger
 */

int distanceHolderComp(const void *holder1, const void *holder2) {
    return ((DistanceHolder *) holder1)->distance - ((DistanceHolder *) holder2)->distance;
}


/**  This function takes a distanceHolder, then it frees it.
 *
 * Note: this function should only be called from the undirected graph functions.
 *
 * @param holder the distance holder pointer
 */

void distanceHolderFreeFun(void *holder) {
    free(holder);
}


/** This function allocate a new uintptr_t pointer in the memory,
 * then it puts it's value with the address of the passed node value.
 *
 * Note: this function should only be called from the undirected graph functions.
 *
 * @param node the node pointer
 * @return it will return an uintptr_t pointer, holds the node value address
 */

uintptr_t *generateNodeValAddress(UDGraphNode *node) {

    uintptr_t *valAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
    if (valAddress == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node value address pointer", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    *valAddress = (uintptr_t) node->value;

    return valAddress;

}


/** This function will allocate a new distance holder in the memory,
 * and return it's pointer.
 *
 * Note: this function should only be called from the undirected graph functions.
 *
 * @param fromNode the from node pointer
 * @param toNode the to node pointer
 * @param distance the distance (weight) between the two nodes
 * @return it will return the allocated distanceHolder pointer
 */

DistanceHolder *generateDisHolder(UDGraphNode *fromNode, UDGraphNode *toNode, int distance) {
    DistanceHolder *holder = (DistanceHolder *) malloc(sizeof(DistanceHolder));
    if (holder == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new distance holder pointer", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    holder->fromNode = fromNode;
    holder->toNode = toNode;
    holder->distance = distance;

    return holder;

}


/** This function will take a holder pointer,
 * then it will update it's content.
 *
 * Note: this function should only be called from the undirected graph functions.
 *
 * @param holder the holder pointer
 * @param fromNode the from node pointer
 * @param toNode the to node pointer
 * @param distance the distance (weight) between the two nodes
 */

void updateDisHolder(DistanceHolder *holder, UDGraphNode *fromNode, UDGraphNode *toNode, int distance) {
    holder->fromNode = fromNode;
    holder->toNode = toNode;
    holder->distance = distance;
}


/** This function will take two nodes values,
 * then it will return the value of the shortest distance between the two nodes.
 *
 * Note: if there wasn't a path between the two nodes, or the nodes aren't exist then the function will return minus one (-1).
 *
 * Note: the function will note free the passed values.
 *
 * @param graph the graph pointer
 * @param startVal the start value pointer
 * @param endVal the end value pointer
 * @return it will return the shortest distance between the two nodes if found, other wise it will return -1
 */

int udGraphGetShortestDistance(UndirectedGraph *graph, void *startVal, void *endVal) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (endVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "end value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    UDGraphNode *endNode = hashMapGet(graph->nodes, endVal);
    if (startNode == NULL || endNode == NULL)
        return -1;

    HashMap *distancesMap = UDGraphGenerateDistancesMap(startNode);

    uintptr_t endValAddress = (uintptr_t) endNode->value;
    DistanceHolder *holder = hashMapGet(distancesMap, &endValAddress);
    int ans = holder != NULL ? holder->distance : -1;

    destroyHashMap(distancesMap);
    return ans;

}


/** This function will take two nodes and then it will return an array list that contains the values,
 * of the shortest path between them.
 *
 * Note: the function will not free the passed values.
 *
 * @param graph the graph pointer
 * @param startVal the start value pointer
 * @param endVal the end value pointer
 * @return it will return an array list that consist of the values of the shortest path
 */

ArrayList *udGraphGetShortestPath(UndirectedGraph *graph, void *startVal, void *endVal) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (endVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "end value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    UDGraphNode *endNode = hashMapGet(graph->nodes, endVal);
    if (startNode == NULL || endNode == NULL)
        return NULL;

    HashMap *distancesMap = UDGraphGenerateDistancesMap(startNode);

    uintptr_t endValAddress = (uintptr_t) endNode->value;
    if (!hashMapContains(distancesMap, &endValAddress)) {
        destroyHashMap(distancesMap);
        return NULL;
    }

    ArrayList *list = arrayListInitialization(5, graph->freeFun, graph->compFun);
    Stack *pathStack = stackInitialization(graph->freeFun);

    UDGraphNode *tempNode = endNode;
    uintptr_t currentValAddress = (uintptr_t) tempNode->value;
    DistanceHolder *tempHolder;

    do {
        tempHolder = hashMapGet(distancesMap, &currentValAddress);
        tempNode = tempHolder->fromNode;
        currentValAddress = (uintptr_t) tempNode->value;
        stackPush(pathStack, tempHolder->toNode->value);
    } while (tempHolder->toNode != startNode);

    while (!stackIsEmpty(pathStack))
        arrayListAdd(list, stackPop(pathStack));


    destroyHashMap(distancesMap);
    destroyStack(pathStack);


    return list;

}


/** This function will take a node as it's parameter,
 * then it will return a hash map the contains all the the shortest paths between all the nodes starts from the passed node.
 *
 * Note: this function should only be called from the undirected graph functions.
 *
 * >>> The function uses the Dijkstra's algorithm <<<.
 *
 * The hash map will represented like this:-
 *
 * the graph:
 *
 * A -- 2 -- B
 * |         |
 * 1         4
 * |         |
 * C -- 3 -- D
 *
 * the hash map:
 *
 * key: A <<The address of the A node value>> -----> value: distanceHolder <<fromNode: A, toNode: A, distance: 0>>
 *
 * key: B <<The address of the B node value>> -----> value: distanceHolder <<fromNode: A, toNode: B, distance: 2>>
 *
 * key: C <<The address of the C node value>> -----> value: distanceHolder <<fromNode: A, toNode: C, distance: 1>>
 *
 * key: D <<The address of the D node value>> -----> value: distanceHolder <<fromNode: C, toNode: D, distance: 4>>
 *
 * @param startNode the start node pointer
 * @return it will return a hash map the contains all the the shortest paths between all the nodes
 */

HashMap *UDGraphGenerateDistancesMap(UDGraphNode *startNode) {


    // This queue will represent the upcoming node to check.
    PriorityQueue *distanceHolderPQueue = priorityQueueInitialization(distanceHolderFreeFun, distanceHolderComp);

    // visitingNodes hash set will represent the nodes that are in the queue.
    HashSet *visitingNodes = hashSetInitialization(UDGFreeUintptr_t, UDGCompUintptr_t, uintptr_tHashFunUDirG);

    // visitedNodes hash set will represent the nodes that are visited (dequeued from the queue).
    HashSet *visitedNodes = hashSetInitialization(UDGFreeUintptr_t, UDGCompUintptr_t, uintptr_tHashFunUDirG);

    // This hash map will hold the shortest distance to all the nodes
    HashMap *distancesMap = hashMapInitialization(UDGFreeUintptr_t, distanceHolderFreeFun, UDGCompUintptr_t,
                                                  uintptr_tHashFunUDirG);


    DistanceHolder *startNodeHolder = generateDisHolder(startNode, startNode, 0);
    pQueueEnqueue(distanceHolderPQueue, startNodeHolder);
    hashSetInsert(visitingNodes, generateNodeValAddress(startNode));
    hashMapInsert(distancesMap, generateNodeValAddress(startNode), startNodeHolder);

    while (!pQueueIsEmpty(distanceHolderPQueue)) {
        DistanceHolder *currentHolder = pQueueDequeue(distanceHolderPQueue);
        UDGraphNode *currentNode = currentHolder->toNode;
        hashSetInsert(visitedNodes, generateNodeValAddress(currentNode));

        for (int i = 0; i < arrayListGetLength(currentNode->adjacentNodes); i++) {
            UDGraphEdge *edge = (UDGraphEdge *) arrayListGet(currentNode->adjacentNodes, i);
            uintptr_t *childNodeValAddress = generateNodeValAddress(edge->node);

            if (!hashSetContains(visitedNodes, childNodeValAddress)) {
                DistanceHolder *holder = hashMapGet(distancesMap, childNodeValAddress);

                if (holder != NULL) {
                    if (currentHolder->distance + edge->weight < holder->distance) {
                        updateDisHolder(holder, currentNode,
                                        holder->toNode, currentHolder->distance + edge->weight);

                    }
                } else {
                    holder = generateDisHolder(currentNode, edge->node, edge->weight +
                                                                        currentHolder->distance);//(DistanceHolder *) malloc(sizeof(DistanceHolder));
                    hashMapInsert(distancesMap, generateNodeValAddress(edge->node), holder);
                }

                if (!hashSetContains(visitingNodes, childNodeValAddress)) {
                    pQueueEnqueue(distanceHolderPQueue, holder);
                    hashSetInsert(visitingNodes, generateNodeValAddress(currentNode));
                }

            }

            free(childNodeValAddress);

        }
    }


    destroyPQueue(distanceHolderPQueue);
    destroyHashSet(visitedNodes);
    destroyHashSet(visitingNodes);

    return distancesMap;


}


/** This function will check if the passed node it a part of a cycle or it leads to a cycle,
 * if it was the function will return oen (1), other wise the function will return zero (0).
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph pointer
 * @param startVal the start node value pointer
 * @return it will return one if the passed value is a part of a cycle, other wise it will return zero
 */

int udGraphNodePartOfCycle(UndirectedGraph *graph, void *startVal) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
#endif

    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    if (startVal == NULL)
        return 0;

    HashSet *visitedNodes = hashSetInitialization(UDGFreeUintptr_t, UDGCompUintptr_t, uintptr_tHashFunUDirG);

    int cycleFlag = UDGraphNodePartOfCycleR(NULL, startNode, visitedNodes);

    destroyHashSet(visitedNodes);

    return cycleFlag;

}


/** This function will check if the graph hash any cycles,
 * if it has the function will return one (1), other wise the function will return zero (0).
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph pointer
 * @return it will return one if the graph has a cycle, other wise it will return zero
 */

int udGraphHasCycle(UndirectedGraph *graph) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    }

    UDGraphNode **nodesArray = (UDGraphNode **) hashMapToArray(graph->nodes);
    HashSet *visitedNodes = hashSetInitialization(UDGFreeUintptr_t, UDGCompUintptr_t, uintptr_tHashFunUDirG);

    int cycleFlag = 0;
    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        uintptr_t currentNodeValAddress = (uintptr_t) nodesArray[i]->value;
        if (!hashSetContains(visitedNodes, &currentNodeValAddress)
            && UDGraphNodePartOfCycleR(NULL, nodesArray[i], visitedNodes)) {

            cycleFlag = 1;
            break;
        }

    }

    free(nodesArray);
    destroyHashSet(visitedNodes);

    return cycleFlag;

}


/** This function will check if the passed node is a part of a cycle recursively,
 * and if it was the function will return one (1), other wise it will return zero (0).
 *
 * Note: this function should only be called from the undirected graph functions.
 *
 * @param prevNode the prevNode pointer
 * @param currentNode the currentNode pointer
 * @param visitedNodes the visited nodes hash set
 * @return it will return one if the passed node is a part of a cycle, other wise it will return zero
 */

int UDGraphNodePartOfCycleR(UDGraphNode *prevNode, UDGraphNode *currentNode, HashSet *visitedNodes) {
    uintptr_t *currentNodeValAddress = generateNodeValAddress(currentNode);
    if (hashSetContains(visitedNodes, currentNodeValAddress)) {
        free(currentNodeValAddress);
        return 1;
    }

    hashSetInsert(visitedNodes, currentNodeValAddress);

    for (int i = 0; i < arrayListGetLength(currentNode->adjacentNodes); i++) {
        UDGraphEdge *edge = (UDGraphEdge *) arrayListGet(currentNode->adjacentNodes, i);
        if (edge->node == prevNode)
            continue;

        if (UDGraphNodePartOfCycleR(currentNode, edge->node, visitedNodes)) {
            return 1;
        }
    }

    return 0;


}


/** This function will take two edges,
 * then it will compare them by there weight.
 *
 * @param e1 the first edge pointer
 * @param e2 the second edge pointer
 * @return it will return zero if the two edges are equal, minus number if the second one bigger, and positive number if the first one bigger
 */

int edgeCompDis(const void *e1, const void *e2) {
    return ((UDGraphEdge *) e1)->weight - ((UDGraphEdge *) e2)->weight;
}


/** This function will take a start node value and a function pointer that take a value and then return it's size,
 * then this function will return a new undirectedGraph pointer that consist of the minimum spanning of the original graph.
 *
 * Note: the new graph has the same values pointers of the original graph (be careful).
 *
 * >>> The function uses the Prim's algorithm <<<.
 *
 * @param graph the graph pointer
 * @param startVal the start value pointer
 * @return it will return the minimum spanning graph pointer
 */

UndirectedGraph *udGraphMinimumSpanningGraph(UndirectedGraph *graph, void *startVal) {

    if (graph == NULL) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(NULL_POINTER);
#endif

    }

    UndirectedGraph *newGraph = undirectedGraphInitialization(graph->freeFun, graph->compFun, graph->nodes->hashFun);

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    if (startNode == NULL)
        return newGraph;

    PriorityQueue *disHolderPQueue = priorityQueueInitialization(distanceHolderFreeFun, distanceHolderComp);

    for (int i = 0; i < arrayListGetLength(startNode->adjacentNodes); i++) {
        UDGraphEdge *edge = (UDGraphEdge *) arrayListGet(startNode->adjacentNodes, i);
        DistanceHolder *holder = generateDisHolder(startNode, edge->node, edge->weight);
        pQueueEnqueue(disHolderPQueue, holder);
    }

    udGraphAddNode(newGraph, startVal);

    while (!pQueueIsEmpty(disHolderPQueue)) {
        DistanceHolder *currentHolder = pQueueDequeue(disHolderPQueue);

        if (udGraphContainsNode(newGraph, currentHolder->toNode->value)) {
            distanceHolderFreeFun(currentHolder);
            continue;
        }

        udGraphAddNode(newGraph, currentHolder->toNode->value);

        udGraphAddEdge(newGraph, currentHolder->fromNode->value, currentHolder->toNode->value, currentHolder->distance);

        for (int i = 0; i < arrayListGetLength(currentHolder->toNode->adjacentNodes); i++) {
            UDGraphEdge *edge = (UDGraphEdge *) arrayListGet(currentHolder->toNode->adjacentNodes, i);

            if (!udGraphContainsNode(newGraph, edge->node->value)) {
                DistanceHolder *holder = generateDisHolder(currentHolder->toNode, edge->node, edge->weight);
                pQueueEnqueue(disHolderPQueue, holder);
            }

        }

        distanceHolderFreeFun(currentHolder);

    }

    destroyPQueue(disHolderPQueue);

    return newGraph;

}