#include "../Headers/UndirectedGraph.h"
#include "../Headers/HashMap.h"
#include "../Headers/HashSet.h"
#include "../Headers/Stack.h"
#include "../Headers/ArrayQueue.h"
#include "../Headers/PriorityQueue.h"
#include "../Headers/ArrayList.h"
#include "../Headers/Utils.h"







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








/** This struct will be useful in getting shortest distance and minimum spanning. */

typedef struct DistanceHolder {
    UDGraphNode *toNode;
    UDGraphNode *fromNode;
    int distance;
} DistanceHolder;








HashMap *UDGraphGenerateDistancesMap(UDGraphNode *startNode);


int UDGraphNodePartOfCycleR(UDGraphNode *prevNode, UDGraphNode *currentNode, HashSet *visitedNodes);










/** This function take a node as it's parameter,
 * then it will free the node without freeing it's value
 * @param node the node address
 */

void UDGraphNodeFreeFun(void *node) {
    UDGraphNode *nodeToFree = (UDGraphNode *) node;
    destroyArrayList(nodeToFree->adjacentNodes);
    free(node);
}










/** This function will take an edge as it's parameter,
 * then it will free the edge without freeing it's node.
 * @param edge the edge pointer
 */

void UDGraphEdgeFreeFun(void *edge) {
    UDGraphEdge *edgeToFree = (UDGraphEdge *) edge;
    free(edgeToFree);
}










/** This function will take two edges then it will compare there nodes values.
 * If the function returned zero, then the two edges are equal.
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
 * @param freeFun the values freeing function pointer
 * @param compFun the values comparing function pointer
 * @return it will return the new initialized graph pointer
 */

UndirectedGraph *undirectedGraphInitialization(void (*freeFun)(void *), int (*compFun)(const void*, const void*)) {

    if (freeFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "freeing function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (compFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparing function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UndirectedGraph *graph = (UndirectedGraph *) malloc(sizeof(UndirectedGraph));
    if (graph == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "graph", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
    }

    graph->nodes = hashMapInitialization(freeFun, UDGraphNodeFreeFun, compFun);
    graph->freeFun = freeFun;
    graph->compFun = compFun;

    return graph;

}









/** This function will add the provided value in a new node in the graph.
 * Note: if the node is already exist in the graph, then the function will free the passed value
 * @param graph the graph pointer
 * @param value the new value pointer
 * @param sizeOfValue the size of the new value
 */

void UDGraphAddNode(UndirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    if (hashMapContains(graph->nodes, value, sizeOfValue)) {
        graph->freeFun(value);
        return;
    }

    UDGraphNode *newNode = (UDGraphNode *) malloc(sizeof(UDGraphNode));
    if (newNode == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
    }

    newNode->value = value;
    newNode->freeFun = graph->freeFun;
    newNode->compFun = graph->compFun;
    newNode->adjacentNodes = arrayListInitialization(5, UDGraphEdgeFreeFun, UDGraphEdgeComp);

    hashMapInsert(graph->nodes, value, sizeOfValue, newNode);

}









/** This function will take two nodes and then it will add a new edge between them.
 * Note: it there was already an edge between the two values then the function will update the weight.
 * Note: the function will note free the passed values.
 * @param graph the graph pointer
 * @param fValue the first value pointer
 * @param fSize the size of the first value in bytes
 * @param sValue the second value pointer
 * @param sSize the size of the second value in bytes
 * @param edgeWeight the weight of the new edge
 */

void UDGraphAddEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize, int edgeWeight) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (fValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "first value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (sValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "second value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *fNode = hashMapGet(graph->nodes, fValue, fSize);
    UDGraphNode *sNode = hashMapGet(graph->nodes, sValue, sSize);
    if (fNode == NULL || sNode == NULL)
        return;

    UDGraphEdge *fNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    UDGraphEdge *sNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    if (fNewEdge == NULL || sNewEdge == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new edge", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
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
 * Note: the function will not free the passed value.
 * @param graph the graph pointer
 * @param value the value pointer
 * @param sizeOfValue the size of the passed value in bytes
 */

void UDGraphRemoveNode(UndirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *node = hashMapGet(graph->nodes, value, sizeOfValue);

    if (node == NULL)
        return;

    UDGraphEdge *tempNodeEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    tempNodeEdge->node = node;

    for (int i = 0; i < arrayListGetLength(node->adjacentNodes); i++) {
        UDGraphEdge *tempEdge = (UDGraphEdge *) arrayListGet(node->adjacentNodes, i);
        arrayListRemoveAtIndex(tempEdge->node->adjacentNodes, arrayListGetIndex(tempEdge->node->adjacentNodes, tempNodeEdge));

    }

    free(tempNodeEdge);
    hashMapDelete(graph->nodes, value, sizeOfValue);

}









/** This function will take a node value,
 * then it will remove and free the node from the graph without freeing the node value.
 * Note: the function will not free the passed value.
 * @param graph the graph pointer
 * @param value the value pointer
 * @param sizeOfValue the size of the passed value in bytes
 */

void *UDGraphRemoveNodeWtoFr(UndirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *node = hashMapGet(graph->nodes, value, sizeOfValue);

    if (node == NULL)
        return NULL;

    UDGraphEdge *tempNodeEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    tempNodeEdge->node = node;

    for (int i = 0; i < arrayListGetLength(node->adjacentNodes); i++) {
        UDGraphEdge *tempEdge = (UDGraphEdge *) arrayListGet(node->adjacentNodes, i);
        arrayListRemoveAtIndex(tempEdge->node->adjacentNodes, arrayListGetIndex(tempEdge->node->adjacentNodes, tempNodeEdge));

    }

    free(tempNodeEdge);
    hashMapDeleteWtoFrAll(graph->nodes, value, sizeOfValue);
    void *returnValue = node->value;
    UDGraphNodeFreeFun(node);

    return returnValue;

}









/** This function will take two value,
 * then it will remove the edge between them it found.
 * Note: the function will not free the passed values.
 * @param graph the graph pointer
 * @param fValue the fist value pointer
 * @param fSize the size of the first value in bytes
 * @param sValue the second value pointer
 * @param sSize the size of the second value in butes
 */

void UDGraphRemoveEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (fValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "fist value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (sValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "second value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *fNode = hashMapGet(graph->nodes, fValue, fSize);
    UDGraphNode *sNode = hashMapGet(graph->nodes, sValue, sSize);
    if (fNode == NULL || sNode == NULL)
        return;

    UDGraphEdge *fNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    UDGraphEdge *sNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    if (fNewEdge == NULL || sNewEdge == NULL) {

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
 * Note: the function will not free the passed value.
 * @param graph the graph pointer
 * @param value the value pointer
 * @param sizeOfValue the size of the passed value in bytes
 * @return it will return one if the value exists in the graph, ohter wise it will return zero
 */

int UDGraphContainsNode(UndirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    return hashMapContains(graph->nodes, value, sizeOfValue);

}









/** This function will take two value then it will check if there is an edge between them,
 * if there was then the function will return one (1), other wise it will return zero (0).
 * Note: the function will not free the passed values.
 * @param graph the graph pointer
 * @param fValue the first value pointer
 * @param fSize the first value size in bytes
 * @param sValue the second value pointer
 * @param sSize the second value size in bytes
 * @return it will return one if the edge exist, other wise it wil lreturn zero
 */

int UDGraphContainsEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (fValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "first value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (sValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "second value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *fNode = hashMapGet(graph->nodes, fValue, fSize);
    UDGraphNode *sNode = hashMapGet(graph->nodes, sValue, sSize);
    if (fNode == NULL || sNode == NULL)
        return 0;

    UDGraphEdge *fNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    UDGraphEdge *sNewEdge = (UDGraphEdge *) malloc(sizeof(UDGraphEdge));
    if (fNewEdge == NULL || sNewEdge == NULL) {

    }

    fNewEdge->node = fNode;
    sNewEdge->node = sNode;

    int fEdgeIndex = arrayListGetIndex(fNode->adjacentNodes, fNewEdge);
    int sEdgeIndex = arrayListGetIndex(sNode->adjacentNodes, sNewEdge);

    free(fNewEdge);
    free(sNewEdge);


    return fEdgeIndex >= 0 && sEdgeIndex >= 0;

}









/** This function will print the graph nodes as following:
 * <<
 * The node: //the node name
 * Is connected to:
 * // the connected nodes names --weight--> (the edge weight)
 * .....
 * >>
 * @param graph the graph pointer
 * @param printFun the values printing function pointer
 */

void printUDGraph(UndirectedGraph *graph, void (*printFun)(void *)) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode **nodesArray = (UDGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        fprintf(stdout, "The node: ");
        printFun(nodesArray[i]->value);
        fprintf(stdout, "\nIs connected to:\n");
        for (int j = 0; j < arrayListGetLength(nodesArray[i]->adjacentNodes); j++) {
            UDGraphEdge *tempEdge = (UDGraphEdge *)arrayListGet(nodesArray[i]->adjacentNodes, j);
            printFun(tempEdge->node->value);
            fprintf(stdout, " --weight--> %d\n", tempEdge->weight);
        }

        fprintf(stdout, "\n");
    }

}








/** This function will return the number of nodes in the graph,
 * @param graph the graph pointer
 * @return it will return the number of nodes in the graph
 */

int UDGraphGetSize(UndirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    return hashMapGetLength(graph->nodes);

}







/** This function will check if the graph is empty,
 * and if it was the function will return one (1), other wise it will return zero (0).
 * @param graph the graph pointer
 * @return it will return one if the graph was empty, other wise it will return zero
 */

int UDGraphIsEmpty(UndirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    return hashMapIsEmpty(graph->nodes);

}









/** This function will clear and free the graph nodes and value,
 * without freeing the graph.
 * @param graph the graph pointer
 */

void clearUDGraph(UndirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    clearHashMap(graph->nodes);
}









/** This function will destroy and free the graph, with all it's nodes and values.
 * @param graph the graph pointer
 */

void destroyUDGraph(UndirectedGraph *graph) {
    if (graph == NULL) {

    }

    destroyHashMap(graph->nodes);
    free(graph);

}










/** This function will take an integer pointer as a parameter,
 * then it will free it.
 * This function will be useful in traversal functions.
 * @param integer the integer address
 */

void UDGFreeInt(void *integer) {
    free(integer);
}










/** This function will take two integers pointer as a parameters,
 * then it will compare the two integers.
 * This function will be useful in traversal functions.
 * @param int1 the first integer address
 * @param s1 the first integer size
 * @param int2 the second integer address
 * @param s2 the second integer size
 * @return it will return zero if the two integers are equal.
 */

int UDGCompInt(const void *int1, const void *int2) {
    return *(int *)int1 - *(int *)int2;
}










/** This function will depth first traverse the graph.
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 * @param graph the graph address
 * @param startVal the start node value address
 * @param the start value size in bytes
 * @param printVal the printing function address, that will be called to print the value
 */

void UDGraphDepthFirstTraversal(UndirectedGraph *graph, void *startVal, int sizeOfValue, void (*printFun)(void *)) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (startVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (printFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfValue);
    Stack *nodesStack = stackInitialization(UDGraphNodeFreeFun);
    HashSet *visitedNodes = hashSetInitialization(UDGFreeInt, UDGCompInt);

    pushStack(nodesStack, startNode);
    int *startNodeValAddress = (int *) malloc(sizeof(int));
    *startNodeValAddress = (int) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress, sizeof(int));


    while (!isEmptyStack(nodesStack)) {
        UDGraphNode *tempNode = popStack(nodesStack);
        printFun(tempNode->value);

        for (int i = 0; i < arrayListGetLength(tempNode->adjacentNodes); i++) {
            UDGraphNode *adjNode = ((UDGraphEdge *) arrayListGet(tempNode->adjacentNodes, i))->node;
            int *adjNodeValAddress = (int *) malloc(sizeof(int));
            *adjNodeValAddress = (int) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress, sizeof(int))) {
                pushStack(nodesStack, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress, sizeof(int));
            } else
                free(adjNodeValAddress);

        }
    }


    StackDestroy(nodesStack);
    destroyHashSet(visitedNodes);

}











/** This function will breadth first traverse the graph.
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 * @param graph the graph address
 * @param startVal the start node value address
 * @param the start value size in bytes
 * @param printVal the printing function address, that will be called to print the value
 */

void UDGraphBreadthFirstTraversal(UndirectedGraph *graph, void *startVal, int sizeOfValue, void (*printFun)(void *)) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (startVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (printFun == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfValue);
    ArrayQueue *nodesQueue = arrayQueueInitialization(UDGraphNodeFreeFun);
    HashSet *visitedNodes = hashSetInitialization(UDGFreeInt, UDGCompInt);

    arrayQueueEnqueue(nodesQueue, startNode);
    int *startNodeValAddress = (int *) malloc(sizeof(int));
    *startNodeValAddress = (int) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress, sizeof(int));


    while (!arrayQueueIsEmpty(nodesQueue)) {
        UDGraphNode *tempNode = arrayQueueDequeue(nodesQueue);
        printFun(tempNode->value);

        for (int i = 0; i < arrayListGetLength(tempNode->adjacentNodes); i++) {
            UDGraphNode *adjNode = ((UDGraphEdge *) arrayListGet(tempNode->adjacentNodes, i))->node;
            int *adjNodeValAddress = (int *) malloc(sizeof(int));
            *adjNodeValAddress = (int) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress, sizeof(int))) {
                arrayQueueEnqueue(nodesQueue, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress, sizeof(int));
            } else
                free(adjNodeValAddress);

        }
    }


    arrayQueueDestroy(nodesQueue);
    destroyHashSet(visitedNodes);

}











/** This function will take two distances holders,
 * then it will compare them with the distance.
 * Note: this function should only be called from the undirected graph functions.
 * @param holder1 the first holder pointer
 * @param holder2 the second holder pointer
 * @return it will return zero if they are equal, minus if the second one bigger, and positive if the first one bigger
 */

int distanceHolderComp(const void *holder1, const void *holder2) {
    return ((DistanceHolder *)holder1)->distance - ((DistanceHolder *)holder2)->distance;
}








/**  This function takes a distanceHolder, then it frees it.
 * Note: this function should only be called from the undirected graph functions.
 * @param holder the distance holder pointer
 */

void distanceHolderFreeFun(void *holder) {
    free(holder);
}












/** This function allocate a new integer pointer in the memory,
 * then it puts it's value with the address of the passed node value.
 * Note: this function should only be called from the undirected graph functions.
 * @param node the node pointer
 * @return it will return an integer pointer, holds the node value address
 */

int *generateNodeValAddress(UDGraphNode *node) {
    int *valAddress = (int *) malloc(sizeof(int));
    if (valAddress == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new node value address pointer", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
    }

    *valAddress = (int) node->value;

    return valAddress;
}










/** This function will allocate a new distance holder in the memory,
 * and return it's pointer.
 * Note: this function should only be called from the undirected graph functions.
 * @param fromNode the from node pointer
 * @param toNode the to node pointer
 * @param distance the distance (weight) between the two nodes
 * @return it will return the allocated distanceHolder pointer
 */

DistanceHolder *generateDisHolder(UDGraphNode *fromNode, UDGraphNode *toNode, int distance) {
    DistanceHolder *holder = (DistanceHolder *) malloc(sizeof(DistanceHolder));
    if (holder == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new distance holder pointer", "undirected graph data structure");
        exit(FAILED_ALLOCATION);
    }

    holder->fromNode = fromNode;
    holder->toNode = toNode;
    holder->distance = distance;
}










/** This function will take a holder pointer,
 * then it will update it's content.
 * Note: this function should only be called from the undirected graph functions.
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
 * Note: if there wasn't a path between the two nodes, or the nodes aren't exist then the function will return minus one (-1).
 * Note: the function will note free the passed values.
 * @param graph the graph pointer
 * @param startVal the start value pointer
 * @param sizeOfStartVal the size of the start value in bytes
 * @param endVal the end value pointer
 * @param sizeOfEndVal the size of the end value in bytes
 * @return it will return the shortest distance between the two nodes if found, other wise it will return -1
 */

int UDGraphGetShortestDistance(UndirectedGraph *graph, void *startVal, int sizeOfStartVal, void *endVal, int sizeOfEndVal) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (startVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (endVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "end value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfStartVal);
    UDGraphNode *endNode = hashMapGet(graph->nodes, endVal, sizeOfEndVal);
    if (startNode == NULL || endNode == NULL)
        return -1;

    HashMap *distancesMap = UDGraphGenerateDistancesMap(startNode);

    int endValAddress = (int) endNode->value;
    DistanceHolder *holder = hashMapGet(distancesMap, &endValAddress, sizeof(int));
    int ans = holder != NULL ? holder->distance : -1;

    destroyHashMap(distancesMap);
    return ans;

}











/** This function will take two nodes and then it will return an array list that contains the value,
 * of the shortest path between them.
 * Note: the function will not free the passed values.
 * @param graph the graph pointer
 * @param startVal the start value pointer
 * @param sizeOfStartVal the size of the start value in bytes
 * @param endVal the end value pointer
 * @param sizeOfEndVal the size of the end value in bytes
 * @return it will return an array list that consist of the values of the shortest path
 */

ArrayList *UDGraphGetShortestPath(UndirectedGraph *graph, void *startVal, int sizeOfStartVal, void *endVal, int sizeOfEndVal) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (startVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (endVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "end value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfStartVal);
    UDGraphNode *endNode = hashMapGet(graph->nodes, endVal, sizeOfEndVal);
    if (startNode == NULL || endNode == NULL)
        return NULL;

    HashMap *distancesMap = UDGraphGenerateDistancesMap(startNode);

    int endValAddress = (int) endNode->value;
    if (!hashMapContains(distancesMap, &endValAddress, sizeof(int))) {
        destroyHashMap(distancesMap);
        return NULL;
    }

    ArrayList *list = arrayListInitialization(5, graph->freeFun, graph->compFun);
    Stack *pathStack = stackInitialization(graph->freeFun);

    UDGraphNode *tempNode = endNode;
    int currentValAddress = (int) tempNode->value;
    DistanceHolder *tempHolder;

    do {
        tempHolder = hashMapGet(distancesMap, &currentValAddress, sizeof(int));
        tempNode = tempHolder->fromNode;
        currentValAddress = (int) tempNode->value;
        pushStack(pathStack, tempHolder->toNode->value);
    } while (tempHolder->toNode != startNode);

    while (!isEmptyStack(pathStack))
        arrayListAdd(list, popStack(pathStack));


    destroyHashMap(distancesMap);
    StackDestroy(pathStack);


    return list;

}











/** This function will take a node as it's parameter,
 * then it will return a hash map the contains all the the shortest paths between all the nodes starts from the passed node.
 * Note: this function should only be called from the undirected graph functions.
 *
 * >>> The function uses the Dijkstra's algorithm <<<.
 *
 * The hash map will represented like this:-
 *
 * the graph:
 * A -- 2 -- B
 * |         |
 * 1         4
 * |         |
 * C -- 3 -- D
 *
 * the hash map:
 * key: A <<The address of the A node value>> -----> value: distanceHolder <<fromNode: A, toNode: A, distance: 0>>
 * key: B <<The address of the B node value>> -----> value: distanceHolder <<fromNode: A, toNode: B, distance: 2>>
 * key: C <<The address of the C node value>> -----> value: distanceHolder <<fromNode: A, toNode: C, distance: 1>>
 * key: D <<The address of the D node value>> -----> value: distanceHolder <<fromNode: C, toNode: D, distance: 4>>
 *
 * @param startNode the start node pointer
 * @return it will return a hash map the contains all the the shortest paths between all the nodes
 */

HashMap *UDGraphGenerateDistancesMap(UDGraphNode *startNode) {


    // This queue will represent the upcoming node to check.
    PriorityQueue *distanceHolderPQueue = priorityQueueInitialization(distanceHolderFreeFun, distanceHolderComp);

    // visitingNodes hash set will represent the nodes that are in the queue.
    HashSet *visitingNodes = hashSetInitialization(UDGFreeInt, UDGCompInt);

    // visitedNodes hash set will represent the nodes that are visited (dequeued from the queue).
    HashSet *visitedNodes = hashSetInitialization(UDGFreeInt, UDGCompInt);

    // This hash map will hold the shortest distance to all the nodes
    HashMap *distancesMap = hashMapInitialization(UDGFreeInt, distanceHolderFreeFun, UDGCompInt);


    DistanceHolder *startNodeHolder = generateDisHolder(startNode, startNode, 0);
    pQueueEnqueue(distanceHolderPQueue, startNodeHolder);
    hashSetInsert(visitingNodes, generateNodeValAddress(startNode), sizeof(int));
    hashMapInsert(distancesMap, generateNodeValAddress(startNode), sizeof(int), startNodeHolder);

    while (!pQueueIsEmpty(distanceHolderPQueue)) {
        DistanceHolder *currentHolder = pQueueDequeue(distanceHolderPQueue);
        UDGraphNode *currentNode = currentHolder->toNode;
        hashSetInsert(visitedNodes, generateNodeValAddress(currentNode), sizeof(int));

        for (int i = 0; i < arrayListGetLength(currentNode->adjacentNodes); i++) {
            UDGraphEdge *edge = (UDGraphEdge *) arrayListGet(currentNode->adjacentNodes, i);
            int *childNodeValAddress = generateNodeValAddress(edge->node);

            if (!hashSetContains(visitedNodes, childNodeValAddress, sizeof(int))) {
                DistanceHolder *holder = hashMapGet(distancesMap, childNodeValAddress, sizeof(int));

                if (holder != NULL) {
                    if (currentHolder->distance + edge->weight < holder->distance) {
                        updateDisHolder(holder, currentNode,
                                holder->toNode,currentHolder->distance + edge->weight );

                    }
                } else {
                    holder = generateDisHolder(currentNode, edge->node, edge->weight + currentHolder->distance);//(DistanceHolder *) malloc(sizeof(DistanceHolder));
                    hashMapInsert(distancesMap, generateNodeValAddress(edge->node), sizeof(int), holder);
                }

                if (!hashSetContains(visitingNodes, childNodeValAddress, sizeof(int))) {
                    pQueueEnqueue(distanceHolderPQueue, holder);
                    hashSetInsert(visitingNodes, generateNodeValAddress(currentNode), sizeof(int));
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
 * Note: the function will not free the passed value.
 * @param graph the graph pointer
 * @param startVal the start node value pointer
 * @param sizeOfStartVal the size of the start node value in bytes
 * @return it will return one if the passed value is a part of a cycle, other wise it will return zero
 */

int UDGraphNodePartOfCycle(UndirectedGraph *graph, void *startVal, int sizeOfStartVal) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    } else if (startVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfStartVal);
    if (startVal == NULL)
        return 0;

    HashSet *visitedNodes = hashSetInitialization(UDGFreeInt, UDGCompInt);

    int cycleFlag = UDGraphNodePartOfCycleR(NULL, startNode, visitedNodes);

    destroyHashSet(visitedNodes);

    return cycleFlag;
}











/** This function will check if the graph hash any cycles,
 * if it has the function will return one (1), other wise the function will return zero (0).
 * Note: the function will not free the passed value.
 * @param graph the graph pointer
 * @return it will return one if the graph has a cycle, other wise it will return zero
 */

int UDGraphHasCycle(UndirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "undirected graph data structure");
        exit(INVALID_ARG);
    }

    UDGraphNode **nodesArray = (UDGraphNode **) hashMapToArray(graph->nodes);
    HashSet *visitedNodes = hashSetInitialization(UDGFreeInt, UDGCompInt);

    int cycleFlag = 0;
    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        int currentNodeValAddress = (int) nodesArray[i]->value;
        if (!hashSetContains(visitedNodes, &currentNodeValAddress, sizeof(int))
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
 * Note: this function should only be called from the undirected graph functions.
 * @param prevNode the prevNode pointer
 * @param currentNode the currentNode pointer
 * @param visitedNodes the visited nodes hash set
 * @return it will return one if the passed node is a part of a cycle, other wise it will return zero
 */

int UDGraphNodePartOfCycleR(UDGraphNode *prevNode, UDGraphNode *currentNode, HashSet *visitedNodes) {
    int *currentNodeValAddress = generateNodeValAddress(currentNode);
    if (hashSetContains(visitedNodes, currentNodeValAddress, sizeof(int))) {
        free(currentNodeValAddress);
        return 1;
    }

    hashSetInsert(visitedNodes, currentNodeValAddress, sizeof(int));

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
 * @param e1 the first edge pointer
 * @param e2 the second edge pointer
 * @return it will return zero if the two edges are equal, minus number if the second one bigger, and positive number if the first one bigger
 */

int edgeCompDis(const void *e1, const void *e2) {
    return ((UDGraphEdge *) e1)->weight - ((UDGraphEdge *) e2)->weight;
}










/** This function will take a start node value and a function pointer that take a value and then return it's size,
 * then this function will return a new undirectedGraph pointer that consist of the minimum spanning of the original graph.
 * Note: the new graph has the same values pointers of the original graph (be careful).
 * >>> The function uses the Prim's algorithm <<<.
 * @param graph the graph pointer
 * @param startVal the start value pointer
 * @param valSizeGetter the getting size function pointer
 * @return
 */

UndirectedGraph *UDGraphMinimumSpanningGraph(UndirectedGraph *graph, void *startVal, int valSizeGetter(const void *)) {
    if (graph == NULL) {

    }

    UndirectedGraph *newGraph = undirectedGraphInitialization(graph->freeFun, graph->compFun);

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, valSizeGetter(startVal));
    if (startNode == NULL)
        return newGraph;

    PriorityQueue *disHolderPQueue = priorityQueueInitialization(distanceHolderFreeFun, distanceHolderComp);

    for (int i = 0; i < arrayListGetLength(startNode->adjacentNodes); i++) {
        UDGraphEdge *edge = (UDGraphEdge *) arrayListGet(startNode->adjacentNodes, i);
        DistanceHolder *holder = generateDisHolder(startNode, edge->node, edge->weight);
        pQueueEnqueue(disHolderPQueue, holder);
    }

    UDGraphAddNode(newGraph, startVal, valSizeGetter(startVal));

    while (!pQueueIsEmpty(disHolderPQueue)) {
        DistanceHolder *currentHolder = pQueueDequeue(disHolderPQueue);

        if (UDGraphContainsNode(newGraph, currentHolder->toNode->value, valSizeGetter(currentHolder->toNode->value))) {
            distanceHolderFreeFun(currentHolder);
            continue;
        }

        UDGraphAddNode(newGraph, currentHolder->toNode->value, valSizeGetter(currentHolder->toNode->value));

        UDGraphAddEdge(newGraph, currentHolder->fromNode->value, valSizeGetter(currentHolder->fromNode->value),
                currentHolder->toNode->value, valSizeGetter(currentHolder->toNode->value),
                currentHolder->distance);

        for (int i = 0; i < arrayListGetLength(currentHolder->toNode->adjacentNodes); i++) {
            UDGraphEdge *edge = (UDGraphEdge *) arrayListGet(currentHolder->toNode->adjacentNodes, i);

            if (!UDGraphContainsNode(newGraph, edge->node->value, valSizeGetter(edge->node->value))) {
                DistanceHolder *holder = generateDisHolder(currentHolder->toNode, edge->node, edge->weight);
                pQueueEnqueue(disHolderPQueue, holder);
            }

        }

        distanceHolderFreeFun(currentHolder);

    }

    destroyPQueue(disHolderPQueue);

    return newGraph;

}
