#include "UndirectedGraph.h"
#include "Headers/HashMap.h"
#include "Headers/HashSet.h"
#include "Headers/Stack.h"
#include "Headers/ArrayQueue.h"
#include "Headers/PriorityQueue.h"
#include "Headers/ArrayList.h"
#include "Headers/Utils.h"




void UDGraphNodeFreeFun(void *node) {
    UDGraphNode *nodeToFree = (UDGraphNode *) node;
    //nodeToFree->freeFun(nodeToFree->value);
    destroyArrayList(nodeToFree->adjacentNodes);
    free(node);
}







void UDGraphEdgeFreeFun(void *edge) {
    UDGraphEdge *edgeToFree = (UDGraphEdge *) edge;
    //UDGraphNodeFreeFun(edgeToFree->node);
    free(edgeToFree);
}







int UDGraphEdgeComp(const void *e1, const void *e2) {
    UDGraphEdge *edge1 = (UDGraphEdge *) e1;
    UDGraphEdge *edge2 = (UDGraphEdge *) e2;

    return edge1->node->compFun(edge1->node->value, edge2->node->value);
}








int UDGraphNodeComp(const void *n1, const void *n2) {
    UDGraphNode *node1 = (UDGraphNode *) n1;
    UDGraphNode *node2 = (UDGraphNode *) n2;

    int returnValue = node1->compFun(node1->value, node2->value);
    return returnValue;
}







UndirectedGraph *undirectedGraphInitialization(void (*freeFun)(void *), int (*compFun)(const void*, const void*)) {

    if (freeFun == NULL) {

    } else if (compFun == NULL) {

    }

    UndirectedGraph *graph = (UndirectedGraph *) malloc(sizeof(UndirectedGraph));
    if (graph == NULL) {

    }

    graph->nodes = hashMapInitialization(freeFun, UDGraphNodeFreeFun, compFun);
    graph->freeFun = freeFun;
    graph->compFun = compFun;

    return graph;

}








void UDGraphAddNode(UndirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {

    } else if (value == NULL) {

    }

    if (hashMapContains(graph->nodes, value, sizeOfValue)) {
        graph->freeFun(value);
        return;
    }

    UDGraphNode *newNode = (UDGraphNode *) malloc(sizeof(UDGraphNode));
    newNode->value = value;
    newNode->freeFun = graph->freeFun;
    newNode->compFun = graph->compFun;
    newNode->adjacentNodes = arrayListInitialization(5, UDGraphEdgeFreeFun, UDGraphEdgeComp);

    hashMapInsert(graph->nodes, value, sizeOfValue, newNode);

}










void UDGraphAddEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize, int edgeWeight) {
    if (graph == NULL) {

    } else if (fValue == NULL) {

    } else if (sValue == NULL) {

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









void UDGraphRemoveNode(UndirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {

    } else if (value == NULL) {

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




void *UDGraphRemoveNodeWtoFr(UndirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {

    } else if (value == NULL) {

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








void UDGraphRemoveEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize) {
    if (graph == NULL) {

    } else if (fValue == NULL) {

    } else if (sValue == NULL) {

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




int UDGraphContainsNode(UndirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {

    } else if (value == NULL) {

    }

    return hashMapContains(graph->nodes, value, sizeOfValue);

}





int UDGraphContainsEdge(UndirectedGraph *graph, void *fValue, int fSize, void *sValue, int sSize) {
    if (graph == NULL) {

    } else if (fValue == NULL) {

    } else if (sValue == NULL) {

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




void printUDGraph(UndirectedGraph *graph, void (*printFun)(void *)) {

    if (graph == NULL) {

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



int UDGraphGetSize(UndirectedGraph *graph) {
    if (graph == NULL) {

    }

    return hashMapGetLength(graph->nodes);

}




int UDGraphIsEmpty(UndirectedGraph *graph) {
    if (graph == NULL) {

    }

    return hashMapIsEmpty(graph->nodes);

}




void clearUDGraph(UndirectedGraph *graph) {
    if (graph == NULL) {

    }

    clearHashMap(graph->nodes);
}


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






void UDGraphDepthFirstTraversal(UndirectedGraph *graph, void *startVal, int sizeOfValue, void (*printFun)(void *)) {
    if (graph == NULL) {

    } else if (printFun == NULL) {

    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfValue);
    Stack *nodesStack = stackInitialization(UDGraphNodeFreeFun);
    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt);

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




void UDGraphBreadthFirstTraversal(UndirectedGraph *graph, void *startVal, int sizeOfValue, void (*printFun)(void *)) {
    if (graph == NULL) {

    } else if (printFun == NULL) {

    }

    UDGraphNode *startNode = hashMapGet(graph->nodes, startVal, sizeOfValue);
    ArrayQueue *nodesQueue = arrayQueueInitialization(UDGraphNodeFreeFun);
    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt);

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

