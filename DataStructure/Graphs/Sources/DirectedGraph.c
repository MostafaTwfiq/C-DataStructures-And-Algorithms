#include "../Headers/DirectedGraph.h"
#include "../../Lists/Headers/ArrayList.h"
#include "../../Tables/Headers/HashMap.h"
#include "../../Tables/Headers/HashSet.h"
#include "../../Stacks/Headers/Stack.h"
#include "../../Queues/Headers/ArrayQueue.h"
#include "../../../System/Utils.h"






typedef struct DirGraphNode {
    void *value;
    struct ArrayList *adjacentNodes;
    int (*valueCompFun)(const void *, const void *);
} DirGraphNode;





void dirGraphTopologicalSortR(DirGraphNode *node, HashSet *visitedNodes, Stack *sortStack);


int dirGraphNodeIsPartOfCycleR(DirGraphNode *node, HashSet *visitedNodes);









/** This function will be useful to free the graph nodes.
 * @param node the node address
 */

void freeDGraphNode(void *node) {

    DirGraphNode *nodeToFree =  (DirGraphNode *) node;

    if (nodeToFree->adjacentNodes != NULL) {

        for (int i = arrayListGetLength(nodeToFree->adjacentNodes) - 1; i >= 0; i--)
            arrayListRemoveWtFr(nodeToFree->adjacentNodes);


        destroyArrayList(nodeToFree->adjacentNodes);

    }

    free(nodeToFree);

}








/** Comparing two nodes values function.
 * @param n1 the first node address
 * @param n2 the second node address
 * @return it will return zero if the two nodes are equal
 */

int dGraphNodeComp (const void *n1, const void *n2) {
    DirGraphNode *node1 = (DirGraphNode *) n1;
    DirGraphNode *node2 = (DirGraphNode *) n2;

    return node1->valueCompFun(node1->value, node2->value);

}









/** This function will initialize the directed graph then it will return a pointer to the graph address.
 * @param freeValue the freeing value function address
 * @param valueComp the comparing values function address
 * @return it will return the initialized graph address
 */

DirectedGraph *directedGraphInitialization(
        void (*freeValue)(void *),
        int (*valueComp)(const void *, const void *)
        ) {

    if (freeValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "free function pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (valueComp == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    DirectedGraph *directedGraph = (DirectedGraph *) malloc(sizeof(DirectedGraph));
    if (directedGraph == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "directed graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = FAILED_ALLOCATION;
     	#else
     		exit(FAILED_ALLOCATION);
     	#endif

    }

    directedGraph->valueComp = valueComp;
    directedGraph->freeValue = freeValue;

    directedGraph->nodes = hashMapInitialization(freeValue, freeDGraphNode, valueComp);

    return directedGraph;

}









/** This function will take a value and insert it in the graph.
 * Note: if the value is already in the graph, then the graph will free the passed value immediately.
 * @param graph the graph address
 * @param value the new value address
 * @param sizeOfValue the size of the new value in bytes
 */

void dirGraphAddNode(DirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }


    if (hashMapContains(graph->nodes, value, sizeOfValue)) {
        graph->freeValue(value);
        return;
    }


    DirGraphNode *newNode = (DirGraphNode *) malloc(sizeof(DirGraphNode));
    newNode->value = value;
    newNode->adjacentNodes = arrayListInitialization(5, freeDGraphNode, dGraphNodeComp);
    hashMapInsert(graph->nodes, value, sizeOfValue, newNode);

}








/** This function will take a value as a parameter, then it will check if the value is in the graph,
 * then it will remove and free the value that in the graph if found.
 * Note: the function will not free the passed value
 * @param graph the graph address
 * @param value the value address
 * @param sizeOfValue the size of the passed value in bytes
 */

void dirGraphRemoveNode(DirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }


    DirGraphNode *nodeToDelete = (DirGraphNode *) hashMapGet(graph->nodes, value, sizeOfValue);

    if (nodeToDelete == NULL)
        return;


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        int index = arrayListGetIndex( hashMapNodes[i]->adjacentNodes, nodeToDelete );
        if (index != -1)
            arrayListRemoveAtIndexWtFr( hashMapNodes[i]->adjacentNodes, index );

    }

    free(hashMapNodes);

    hashMapDelete(graph->nodes, value, sizeOfValue);

}







/** This function will take a value as a parameter, then it will check if the value is in the graph,
 * then it will remove the value that in the graph without freeing it if found.
 * Note: the function will not free the passed value
 * @param graph the graph address
 * @param value the value address
 * @param sizeOfValue the size of the passed value in bytes
 * @return it will return the deleted value if found, other wise it will return NULL
 */

void *dirGraphRemoveNodeWtoFr(DirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }


    DirGraphNode *nodeToDelete = (DirGraphNode *) hashMapGet(graph->nodes, value, sizeOfValue);

    if (nodeToDelete == NULL)
        return NULL;


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        int index = arrayListGetIndex( hashMapNodes[i]->adjacentNodes, nodeToDelete );
        if (index != -1)
            arrayListRemoveAtIndexWtFr( hashMapNodes[i]->adjacentNodes, index );

    }

    free(hashMapNodes);

    return hashMapDeleteWtoFrAll(graph->nodes, value, sizeOfValue)->key;

}










/** This function will take two nodes values, and then it will create an edge between them,
 * if they are found in the graph.
 * Note: The function will not free the two passed values.
 * @param graph the graph address
 * @param fromVal the first value address
 * @param sizeOfFromVal the first value size in bytes
 * @param toVal the second value address
 * @param sizeOfToVal the second value size in bytes
 */

void dirGraphAddEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (fromVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "from value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (toVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "to value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }


    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal, sizeOfFromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal, sizeOfToVal);

    if(fromNode == NULL || toNode == NULL)
        return;


    if (!arrayListContains(fromNode->adjacentNodes, toNode))
        arrayListAdd(fromNode->adjacentNodes, toNode);

}










/** This function will take a two nodes value and then it will remove the edge between them if found.
 * Note: The function will not free the passed values.
 * @param graph the graph address
 * @param fromVal the first value address
 * @param sizeOfFromVal the first value size in bytes
 * @param toVal the second value address
 * @param sizeOfToVal the second value size in bytes
 */

void dirGraphRemoveEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (fromVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "from value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (toVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "to value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }


    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal, sizeOfFromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal, sizeOfToVal);

    if (fromNode == NULL || toNode == NULL)
        return;

    int toNodeIndex = arrayListGetIndex(fromNode->adjacentNodes, toNode);
    if (toNodeIndex != -1)
        arrayListRemoveAtIndexWtFr(fromNode->adjacentNodes, toNodeIndex);

}









/** This function will check if the passed value is in the graph,
 * Note: the function will not free the passed value.
 * and if it was then the function will return one (1), other wise it will return zero.
 * @param graph the graph address
 * @param value the value address
 * @param sizeOfValue the value size in bytes
 * @return it will return one if the value found, other wise in will return zero
 */

int dirGraphContainsNode(DirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (value == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    return hashMapContains(graph->nodes, value, sizeOfValue);

}









/** This function will take two nodes value then it will check if there is an edge between them,
 * and if there was the function will return one, other wise it will return zero.
 * Note: the function will not free the passed two values.
 * @param graph the graph address
 * @param fromVal the first value address
 * @param sizeOfFromVal the first value size in bytes
 * @param toVal the second value address
 * @param sizeOfToVal the second value size in bytes
 * @return it will return one it there was an edge between the two values, other wise it will return zero
 */

int dirGraphContainsEdge(DirectedGraph *graph, void *fromVal, int sizeOfFromVal, void *toVal, int sizeOfToVal) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (fromVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "from value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (toVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "to value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal, sizeOfFromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal, sizeOfToVal);

    if (fromNode == NULL || toNode == NULL)
        return 0;

    return arrayListContains(fromNode->adjacentNodes, toNode);

}










/** This function will return the number of nodes in the graph.
 * @param graph the graph address
 * @return it will reutrn the numebr of nodes in the graph
 */

int dirGraphGetNumOfNodes(DirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    return hashMapGetLength(graph->nodes);

}









/** This function will check if the graph is empty,
 * and return one (1) if it was, other wise in will retyrn zero (0).
 * @param graph the graph address
 * @return it will return one if the graph was empty, other wise in will return zero
 */

int dirGraphIsEmpty(DirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    return hashMapGetLength(graph->nodes) == 0;

}









/** This function will clear and free the graph nodes without freeing the graph itself.
 * @param graph the graph address
 */

void clearDirGraph(DirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    clearHashMap(graph->nodes);

}










/** This function will destroy and free the graph and all it's nodes.
 * @param graph the graph address
 */

void destroyDirGraph(DirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }

    destroyHashMap(graph->nodes);
    free(graph);

}









/** This function will print all the graph values in this from,
 * <<
 * The node: //the node name
 * Is connected to:
 * // the connected nodes names
 * .....
 * >>
 * @param graph the graph address
 * @param printVal the printing function address, that will be called to print the values
 */

void dirGraphPrint(DirectedGraph *graph, void (*printVal)(void *)) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (printVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    DirGraphNode **arr = (DirGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        printf("The node: ");
        printVal(arr[i]->value);
        printf("\nIs connected to:\n");
        for (int j = 0; j < arrayListGetLength(arr[i]->adjacentNodes); j++) {
            printVal( ((DirGraphNode *) arrayListGet(arr[i]->adjacentNodes, j))->value );
            printf("\n");
        }
        printf("\n\n");

    }

}









/** This function will take an integer pointer as a parameter,
 * then it will free it.
 * This function will be useful in traversal functions.
 * @param integer the integer address
 */

void freeInt(void *integer) {
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

int compInt(const void *int1, const void *int2) {
    return *(int *)int1 - *(int *)int2;
}





/** This function will take an integer pointer as a parameter,
 * then it will return the value of the integer.
 * Note: this function will be useful to use in the hash map and hash set data structures
 * @param item the integer pointer
 * @return it will return the value of the integer as the unique hash key
 */

int intHashFunDirG(const void *item) {
    return *(int *)item;
}






/** This function will depth first traverse the graph.
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 * @param graph the graph address
 * @param startVal the start node value address
 * @param the start value size in bytes
 * @param printVal the printing function address, that will be called to print the value
 */


void dirGraphDepthFirstTraversal(DirectedGraph *graph, void *startVal, int sizeOfValue, void (*printVal)(void *)) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (startVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (printVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    DirGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfValue);
    if (startNode == NULL)
        return;

    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt, intHashFunDirG);
    Stack *nodesStack = stackInitialization(freeDGraphNode);
    pushStack(nodesStack, startNode);

    int *startNodeValAddress = (int *) malloc(sizeof(int));
    *startNodeValAddress = (int) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress);

    DirGraphNode *currentNode;

    while (!isEmptyStack(nodesStack)) {
        currentNode = popStack(nodesStack);
        printVal(currentNode->value);

        for (int i = 0; i < arrayListGetLength(currentNode->adjacentNodes); i++) {
            DirGraphNode *adjNode = (DirGraphNode *) arrayListGet(currentNode->adjacentNodes, i);
            int *adjNodeValAddress = (int *) malloc(sizeof(int));
            *adjNodeValAddress = (int) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress)) {
                pushStack(nodesStack, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress);
            } else
                free(adjNodeValAddress);

        }


    }

    destroyHashSet(visitedNodes);
    StackDestroy(nodesStack);

}









/** This function will breadth first traverse the graph.
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 * @param graph the graph address
 * @param startVal the start node value address
 * @param the start value size in bytes
 * @param printVal the printing function address, that will be called to print the value
 */

void dirGraphBreadthFirstTraversal(DirectedGraph *graph, void *startVal, int sizeOfValue, void (*printVal)(void *)) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (startVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    } else if (printVal == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "print function pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    DirGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfValue);
    if (startNode == NULL)
        return;

    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt, intHashFunDirG);
    ArrayQueue *nodesQueue = arrayQueueInitialization(freeDGraphNode);
    arrayQueueEnqueue(nodesQueue, startNode);

    int *startNodeValAddress = (int *) malloc(sizeof(int));
    *startNodeValAddress = (int) startNode->value;
    hashSetInsert(visitedNodes, startNodeValAddress);

    DirGraphNode *currentNode;

    while (!arrayQueueIsEmpty(nodesQueue)) {
        currentNode = arrayQueueDequeue(nodesQueue);
        printVal(currentNode->value);

        for (int i = 0; i < arrayListGetLength(currentNode->adjacentNodes); i++) {
            DirGraphNode *adjNode = (DirGraphNode *) arrayListGet(currentNode->adjacentNodes, i);
            int *adjNodeValAddress = (int *) malloc(sizeof(int));
            *adjNodeValAddress = (int) adjNode->value;
            if (!hashSetContains(visitedNodes, adjNodeValAddress)) {
                arrayQueueEnqueue(nodesQueue, adjNode);
                hashSetInsert(visitedNodes, adjNodeValAddress);
            } else
                free(adjNodeValAddress);

        }


    }

    destroyHashSet(visitedNodes);
    arrayQueueDestroy(nodesQueue);

}








/** This function will sort the graph nodes topologically, then it will return an array list that contains the values.
 * @param graph the graph address
 * @return it will return an array list pointer that contains the values sorted
 */

ArrayList *dirGraphTopologicalSort(DirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);
    ArrayList *sortedArrayList = arrayListInitialization(hashMapGetLength(graph->nodes), graph->freeValue, graph->valueComp);
    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt, intHashFunDirG);
    Stack *sortStack = stackInitialization(freeDGraphNode);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++)
        dirGraphTopologicalSortR(hashMapNodes[i], visitedNodes, sortStack);


    while (!isEmptyStack(sortStack)) {
        DirGraphNode *tempNode = popStack(sortStack);
        arrayListAdd(sortedArrayList, tempNode->value);
    }

    StackDestroy(sortStack);
    destroyHashSet(visitedNodes);

    free(hashMapNodes);

    return sortedArrayList;

}








/** This function will sort the graph nodes topologically recursively, and it will fill the stack with the values.
 * @param node the current node address
 * @param visitedNodes the visited nodes hash set address
 * @param sortStack the nodes stack address
 */

void dirGraphTopologicalSortR(DirGraphNode *node, HashSet *visitedNodes, Stack *sortStack) {
    int *nodeValueAddress = (int *) malloc(sizeof(int));
    *nodeValueAddress = (int) node->value;

    if (hashSetContains(visitedNodes, nodeValueAddress)) {
        free(nodeValueAddress);
        return;
    }

    hashSetInsert(visitedNodes, nodeValueAddress);

    for (int i = 0; i < arrayListGetLength(node->adjacentNodes); i++)
        dirGraphTopologicalSortR(arrayListGet(node->adjacentNodes, i), visitedNodes, sortStack);


    pushStack(sortStack, node);

}






/** This function will check if the passed node value is a part of a cycle,
 * and if it was the function will return one (1) other wise it will return zero (0).
 * Note: the passed item will not be freed in the end of the function.
 * @param graph the directed graph address
 * @param startValue the start value address
 * @param sizeOfValue the size of the passed value in bytes
 * @return it will return one if the node is a part of a cycle, other wise it will return zero
 */

int dirGraphNodeIsPartOfCycle(DirectedGraph *graph, void *startValue, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    } else if (startValue == NULL) {
        fprintf(stderr, INVALID_ARG_MESSAGE, "start value pointer", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = INVALID_ARG;
     	#else
     		exit(INVALID_ARG);
     	#endif

    }

    DirGraphNode *startNode = hashMapGet(graph->nodes, startValue, sizeOfValue);
    if (startNode == NULL)
        return 0;

    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt, intHashFunDirG);
    int cycleFlag = dirGraphNodeIsPartOfCycleR(startNode, visitedNodes);

    destroyHashSet(visitedNodes);

    return cycleFlag;

}








/** This function will check if there is a cycle recursively,
 * then it will return one if there was a cycle, other wise it will return zero.
 * @param node the node address
 * @param visitedNodes the visited nodes hash set address
 * @return it will return one if there was a cycle, other wise it will return zero
 */

int dirGraphNodeIsPartOfCycleR(DirGraphNode *node, HashSet *visitedNodes) {
    int *nodeValueAddress = (int *) malloc(sizeof(int));
    *nodeValueAddress = (int) node->value;

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
 * @param graph the directed graph address
 * @return it will return one if the graph has a cycle, other wise it will return zero
 */

int dirGraphHasACycle(DirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, NULL_POINTER_MESSAGE, "graph", "directed graph data structure");
        #ifdef CU_TEST_H
     		DUMMY_TEST_DATASTRUCTURE->errorCode = NULL_POINTER;
     	#else
     		exit(NULL_POINTER);
     	#endif

    }


    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);
    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt, intHashFunDirG);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        int currentNodeValAddress = (int) hashMapNodes[i]->value;
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