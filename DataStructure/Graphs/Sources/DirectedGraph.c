#include "../Headers/DirectedGraph.h"
#include "../../Lists/Headers/ArrayList.h"
#include "../../Tables/Headers/HashMap.h"
#include "../../Tables/Headers/HashSet.h"
#include "../../Stacks/Headers/Stack.h"
#include "../../Queues/Headers/Queue.h"
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


/** @struct DirGraphNode
*  @brief This structure implements a basic directed graph node.
*  @var DirGraphNode::value
*  Member 'value' is a pointer to the node value.
*  @var DirGraphNode::adjacentNodes
*  Member 'adjacentNodes' is a pointer to the adjacent nodes array list.
*  @var DirGraphNode::valueCompFun
*  Member 'valueCompFun' is a pointer to the comparator function, that will compare the graph values.
*/

typedef struct DirGraphNode {
    void *value;
    struct ArrayList *adjacentNodes;

    int (*valueCompFun)(const void *, const void *);
} DirGraphNode;


void dirGraphTopologicalSortR(DirGraphNode *node, HashSet *visitedNodes, Stack *sortStack);


int dirGraphNodeIsPartOfCycleR(DirGraphNode *node, HashSet *visitedNodes);


/** This function will be useful to free the graph nodes.
 *
 * @param node the node address
 */

void freeDGraphNode(void *node) {

    DirGraphNode *nodeToFree = (DirGraphNode *) node;

    if (nodeToFree->adjacentNodes != NULL) {

        for (int i = arrayListGetLength(nodeToFree->adjacentNodes) - 1; i >= 0; i--)
            arrayListRemoveWtFr(nodeToFree->adjacentNodes);


        destroyArrayList(nodeToFree->adjacentNodes);

    }

    free(nodeToFree);

}


/** Comparing two nodes values function.
 *
 * @param n1 the first node address
 * @param n2 the second node address
 * @return it will return zero if the two nodes are equal
 */

int dGraphNodeComp(const void *n1, const void *n2) {
    DirGraphNode *node1 = (DirGraphNode *) n1;
    DirGraphNode *node2 = (DirGraphNode *) n2;

    return node1->valueCompFun(node1->value, node2->value);

}


/** This function will initialize the directed graph then it will return a pointer to the graph address.
 *
 * Note: because the graph is implemented by hash map, you need to pass the hashing function.
 *
 * @param freeValue the freeing value function address
 * @param valueComp the comparing values function address
 * @param hashFun the hashing function that will return a unique integer representing the hash map key
 * @return it will return the initialized graph address
 */

DirectedGraph *directedGraphInitialization(
        void (*freeValue)(void *),
        int (*valueComp)(const void *, const void *),
        int (*hashFun)(const void *)
) {

    if (freeValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (valueComp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (hashFun == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash function pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif
    }

    DirectedGraph *directedGraph = (DirectedGraph *) malloc(sizeof(DirectedGraph));
    if (directedGraph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "directed graph", "directed graph data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    directedGraph->valueComp = valueComp;
    directedGraph->freeValue = freeValue;

    directedGraph->nodes = hashMapInitialization(freeValue, freeDGraphNode, valueComp, hashFun);

    return directedGraph;

}


/** This function will take a value and insert it in the graph.
 *
 * Note: if the value is already in the graph, then the graph will free the passed value immediately.
 *
 * @param graph the graph address
 * @param value the new value address
 */

void dirGraphAddNode(DirectedGraph *graph, void *value) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }


    if (hashMapContains(graph->nodes, value)) {
        graph->freeValue(value);
        return;
    }


    DirGraphNode *newNode = (DirGraphNode *) malloc(sizeof(DirGraphNode));
    newNode->value = value;
    newNode->valueCompFun = graph->valueComp;
    newNode->adjacentNodes = arrayListInitialization(5, freeDGraphNode, dGraphNodeComp);
    hashMapInsert(graph->nodes, value, newNode);

}


/** This function will take a value as a parameter, then it will check if the value is in the graph,
 * then it will remove and free the value that in the graph if found.
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph address
 * @param value the value address
 */

void dirGraphRemoveNode(DirectedGraph *graph, void *value) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }


    DirGraphNode *nodeToDelete = (DirGraphNode *) hashMapGet(graph->nodes, value);

    if (nodeToDelete == NULL)
        return;


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        int index = arrayListGetIndex(hashMapNodes[i]->adjacentNodes, nodeToDelete);
        if (index != -1)
            arrayListRemoveAtIndexWtFr(hashMapNodes[i]->adjacentNodes, index);

    }

    free(hashMapNodes);

    hashMapDelete(graph->nodes, value);

}


/** This function will take a value as a parameter, then it will check if the value is in the graph,
 * then it will remove the value that in the graph without freeing it if found.
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph address
 * @param value the value address
 * @return it will return the deleted value if found, other wise it will return NULL
 */

void *dirGraphRemoveNodeWtoFr(DirectedGraph *graph, void *value) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }


    DirGraphNode *nodeToDelete = (DirGraphNode *) hashMapGet(graph->nodes, value);

    if (nodeToDelete == NULL)
        return NULL;


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        int index = arrayListGetIndex(hashMapNodes[i]->adjacentNodes, nodeToDelete);
        if (index != -1)
            arrayListRemoveAtIndexWtFr(hashMapNodes[i]->adjacentNodes, index);

    }

    free(hashMapNodes);

    return hashMapDeleteWtoFrAll(graph->nodes, value)->key;

}


/** This function will take two nodes values, and then it will create an edge between them,
 * if they are found in the graph.
 *
 * Note: The function will not free the two passed values.
 *
 * @param graph the graph address
 * @param fromVal the first value address
 * @param toVal the second value address
 */

void dirGraphAddEdge(DirectedGraph *graph, void *fromVal, void *toVal) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (fromVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "from value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (toVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "to value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }


    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal);

    if (fromNode == NULL || toNode == NULL)
        return;


    if (!arrayListContains(fromNode->adjacentNodes, toNode))
        arrayListAdd(fromNode->adjacentNodes, toNode);

}


/** This function will take a two nodes value and then it will remove the edge between them if found.
 *
 * Note: The function will not free the passed values.
 *
 * @param graph the graph address
 * @param fromVal the first value address
 * @param toVal the second value address
 */

void dirGraphRemoveEdge(DirectedGraph *graph, void *fromVal, void *toVal) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (fromVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "from value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (toVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "to value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }


    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal);

    if (fromNode == NULL || toNode == NULL)
        return;

    int toNodeIndex = arrayListGetIndex(fromNode->adjacentNodes, toNode);
    if (toNodeIndex != -1)
        arrayListRemoveAtIndexWtFr(fromNode->adjacentNodes, toNodeIndex);

}


/** This function will check if the passed value is in the graph or not,
 * and if it was then the function will return one (1), other wise it will return zero (0).
 *
 * Note: the function will not free the passed value.
 *
 * @param graph the graph address
 * @param value the value address
 * @return it will return one if the value found, other wise in will return zero
 */

int dirGraphContainsNode(DirectedGraph *graph, void *value) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (value == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }

    return hashMapContains(graph->nodes, value);

}


/** This function will take two nodes value then it will check if there is an edge between them,
 * and if there was the function will return one, other wise it will return zero.
 *
 * Note: the function will not free the passed two values.
 *
 * @param graph the graph address
 * @param fromVal the first value address
 * @param toVal the second value address
 * @return it will return one it there was an edge between the two values, other wise it will return zero
 */

int dirGraphContainsEdge(DirectedGraph *graph, void *fromVal, void *toVal) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (fromVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "from value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (toVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "to value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }

    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal);

    if (fromNode == NULL || toNode == NULL)
        return 0;

    return arrayListContains(fromNode->adjacentNodes, toNode);

}


/** This function will return the number of nodes in the graph.
 *
 * @param graph the graph address
 * @return it will return the number of nodes in the graph
 */

int dirGraphGetSize(DirectedGraph *graph) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    }

    return hashMapGetLength(graph->nodes);

}


/** This function will check if the graph is empty,
 * and return one (1) if it was, other wise in will return zero (0).
 *
 * @param graph the graph address
 * @return it will return one if the graph was empty, other wise in will return zero
 */

int dirGraphIsEmpty(DirectedGraph *graph) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    }

    return hashMapGetLength(graph->nodes) == 0;

}


/** This function will clear and free the graph nodes without freeing the graph itself.
 *
 * @param graph the graph address
 */

void clearDirGraph(DirectedGraph *graph) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    }

    clearHashMap(graph->nodes);

}


/** This function will destroy and free the graph and all it's nodes.
 *
 * @param graph the graph address
 */

void destroyDirGraph(void *graph) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    }

    destroyHashMap(((DirectedGraph *) graph)->nodes);
    free(graph);

}


/** This function will print all the graph values in this from:
 *
 * <<
 *
 * The node: //the node name
 *
 * Is connected to:
 *
 * // the connected nodes names
 *
 * .....
 *
 * >>
 *
 * @param graph the graph address
 * @param printVal the printing function address, that will be called to print the values
 */

void dirGraphPrint(DirectedGraph *graph, void (*printVal)(void *)) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (printVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }


    DirGraphNode **arr = (DirGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
        printf("The node: ");
#endif

        printVal(arr[i]->value);

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
        printf("\nIs connected to:\n");
#endif

        for (int j = 0; j < arrayListGetLength(arr[i]->adjacentNodes); j++) {

            printVal(((DirGraphNode *) arrayListGet(arr[i]->adjacentNodes, j))->value);

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
            printf("\n");
#endif

        }

#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
#else
        printf("\n\n");
#endif

    }

}


/** This function will take an uintptr_tPointer pointer as a parameter,
 * then it will free it.
 *
 * This function will be useful in traversal functions.
 *
 * @param uintptr_tPointer the uintptr_tPointer address
 */

void freeUintptr_t(void *uintptr_tPointer) {
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

int compUintptr_t(const void *uintptr_tPointer1, const void *uintptr_tPointer2) {
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

int uintptr_tHashFunDirG(const void *item) {
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


void dirGraphDepthFirstTraversal(DirectedGraph *graph, void *startVal, void (*printVal)(void *)) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (printVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }

    DirGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    if (startNode == NULL)
        return;

    HashSet *visitedNodes = hashSetInitialization(freeUintptr_t, compUintptr_t, uintptr_tHashFunDirG);
    Stack *nodesStack = stackInitialization(freeDGraphNode);
    stackPush(nodesStack, startNode);

    uintptr_t *startNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
    *startNodeValAddress = (uintptr_t) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress);

    DirGraphNode *currentNode;

    while (!stackIsEmpty(nodesStack)) {
        currentNode = stackPop(nodesStack);
        printVal(currentNode->value);

        for (int i = 0; i < arrayListGetLength(currentNode->adjacentNodes); i++) {
            DirGraphNode *adjNode = (DirGraphNode *) arrayListGet(currentNode->adjacentNodes, i);
            uintptr_t *adjNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
            *adjNodeValAddress = (uintptr_t) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress)) {
                stackPush(nodesStack, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress);
            } else
                free(adjNodeValAddress);

        }


    }

    destroyHashSet(visitedNodes);
    destroyStack(nodesStack);

}


/** This function will breadth first traverse the graph.
 *
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 *
 * @param graph the graph address
 * @param startVal the start node value address
 * @param printVal the printing function address, that will be called to print the value
 */

void dirGraphBreadthFirstTraversal(DirectedGraph *graph, void *startVal, void (*printVal)(void *)) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    } else if (printVal == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }

    DirGraphNode *startNode = hashMapGet(graph->nodes, startVal);
    if (startNode == NULL)
        return;

    HashSet *visitedNodes = hashSetInitialization(freeUintptr_t, compUintptr_t, uintptr_tHashFunDirG);
    Queue *nodesQueue = queueInitialization(freeDGraphNode);
    queueEnqueue(nodesQueue, startNode);

    uintptr_t *startNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
    *startNodeValAddress = (uintptr_t) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress);

    DirGraphNode *currentNode;

    while (!queueIsEmpty(nodesQueue)) {
        currentNode = queueDequeue(nodesQueue);
        printVal(currentNode->value);

        for (int i = 0; i < arrayListGetLength(currentNode->adjacentNodes); i++) {
            DirGraphNode *adjNode = (DirGraphNode *) arrayListGet(currentNode->adjacentNodes, i);
            uintptr_t *adjNodeValAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
            *adjNodeValAddress = (uintptr_t) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress)) {
                queueEnqueue(nodesQueue, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress);
            } else
                free(adjNodeValAddress);

        }


    }

    destroyHashSet(visitedNodes);
    destroyQueue(nodesQueue);

}


/** This function will sort the graph nodes topologically, then it will return an array list that contains the values.
 *
 * @param graph the graph address
 * @return it will return an array list pointer that contains the values sorted
 */

ArrayList *dirGraphTopologicalSort(DirectedGraph *graph) {
    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    }


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);
    ArrayList *sortedArrayList = arrayListInitialization(hashMapGetLength(graph->nodes), graph->freeValue,
                                                         graph->valueComp);
    HashSet *visitedNodes = hashSetInitialization(freeUintptr_t, compUintptr_t, uintptr_tHashFunDirG);
    Stack *sortStack = stackInitialization(freeDGraphNode);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++)
        dirGraphTopologicalSortR(hashMapNodes[i], visitedNodes, sortStack);


    while (!stackIsEmpty(sortStack)) {
        DirGraphNode *tempNode = stackPop(sortStack);
        arrayListAdd(sortedArrayList, tempNode->value);
    }

    destroyStack(sortStack);
    destroyHashSet(visitedNodes);

    free(hashMapNodes);

    return sortedArrayList;

}


/** This function will sort the graph nodes topologically recursively, and it will fill the stack with the values.
 *
 * @param node the current node address
 * @param visitedNodes the visited nodes hash set address
 * @param sortStack the nodes stack address
 */

void dirGraphTopologicalSortR(DirGraphNode *node, HashSet *visitedNodes, Stack *sortStack) {
    uintptr_t *nodeValueAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
    *nodeValueAddress = (uintptr_t) node->value;

    if (hashSetContains(visitedNodes, nodeValueAddress)) {
        free(nodeValueAddress);
        return;
    }

    hashSetInsert(visitedNodes, nodeValueAddress);

    for (int i = 0; i < arrayListGetLength(node->adjacentNodes); i++)
        dirGraphTopologicalSortR(arrayListGet(node->adjacentNodes, i), visitedNodes, sortStack);


    stackPush(sortStack, node);

}


/** This function will check if the passed node value is a part of a cycle,
 * and if it was the function will return one (1) other wise it will return zero (0).
 *
 * Note: the passed item will not be freed in the end of the function.
 *
 * @param graph the directed graph address
 * @param startValue the start value address
 * @return it will return one if the node is a part of a cycle, other wise it will return zero
 */

int dirGraphNodeIsPartOfCycle(DirectedGraph *graph, void *startValue) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    } else if (startValue == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "directed graph data structure");
        exit(INVALID_ARG);
#endif

    }

    DirGraphNode *startNode = hashMapGet(graph->nodes, startValue);
    if (startNode == NULL)
        return 0;

    HashSet *visitedNodes = hashSetInitialization(freeUintptr_t, compUintptr_t, uintptr_tHashFunDirG);
    int cycleFlag = dirGraphNodeIsPartOfCycleR(startNode, visitedNodes);

    destroyHashSet(visitedNodes);

    return cycleFlag;

}


/** This function will check if there is a cycle recursively,
 * then it will return one if there was a cycle, other wise it will return zero.
 *
 * @param node the node address
 * @param visitedNodes the visited nodes hash set address
 * @return it will return one if there was a cycle, other wise it will return zero
 */

int dirGraphNodeIsPartOfCycleR(DirGraphNode *node, HashSet *visitedNodes) {
    uintptr_t *nodeValueAddress = (uintptr_t *) malloc(sizeof(uintptr_t));
    *nodeValueAddress = (uintptr_t) node->value;

    if (hashSetContains(visitedNodes, nodeValueAddress)) {
        free(nodeValueAddress);
        return 1;
    }

    hashSetInsert(visitedNodes, nodeValueAddress);

    for (int i = 0; i < arrayListGetLength(node->adjacentNodes); i++) {

        if (dirGraphNodeIsPartOfCycleR(arrayListGet(node->adjacentNodes, i), visitedNodes))
            return 1;

    }

    hashSetDelete(visitedNodes, nodeValueAddress);


    return 0;

}


/** This function will check if the is a cycle in the graph,
 * and if it was the function will return one (1) other wise it will return zero (0).
 *
 * @param graph the directed graph address
 * @return it will return one if the graph has a cycle, other wise it will return zero
 */

int dirGraphHasACycle(DirectedGraph *graph) {

    if (graph == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        exit(NULL_POINTER);
#endif

    }


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);
    HashSet *visitedNodes = hashSetInitialization(freeUintptr_t, compUintptr_t, uintptr_tHashFunDirG);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        uintptr_t currentNodeValAddress = (uintptr_t) hashMapNodes[i]->value;
        if (!hashSetContains(visitedNodes, &currentNodeValAddress)
            && dirGraphNodeIsPartOfCycleR(hashMapNodes[i], visitedNodes)) {
            destroyHashSet(visitedNodes);
            free(hashMapNodes);
            return 1;
        }

    }


    destroyHashSet(visitedNodes);
    free(hashMapNodes);

    return 0;

}