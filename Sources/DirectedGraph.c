#include "../Headers/DirectedGraph.h"






/** freeing graph values function address*/
void (*dGFreeValue)(void *value);






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






/** Comparing values function address.
 * @param val1 the first value address
 * @param s1 the first value size in bytes
 * @param val2 the second value address
 * @param s2 the second value size in bytes
 * @return it will return zero (0) if the two value are equal
 */

int (*valueCompFun)(const void *val1, int s1, const void *val2, int s2);







/** Comparing two nodes values function.
 * @param n1 the first node address
 * @param n2 the second node address
 * @return it will return zero if the two nodes are equal
 */

int dGraphNodeComp (const void *n1, const void *n2) {
    DirGraphNode *node1 = (DirGraphNode *) n1;
    DirGraphNode *node2 = (DirGraphNode *) n2;

    return valueCompFun(node1->value, node1->sizeOfValue, node2->value, node2->sizeOfValue);

}









/** This function will initialize the directed graph then it will return a pointer to the graph address.
 * @param freeValue the freeing value function address
 * @param valueComp the comparing values function address
 * @return it will return the initialized graph address
 */

DirectedGraph *directedGraphInitialization(
        void (*freeValue)(void *),
        int (*valueComp)(const void *key1, int s1, const void *key2, int s2)
        ) {

    DirectedGraph *directedGraph = (DirectedGraph *) malloc(sizeof(DirectedGraph));

    valueCompFun = valueComp;

    dGFreeValue = freeValue;
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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }


    if (hashMapContains(graph->nodes, value, sizeOfValue)) {
        dGFreeValue(value);
        return;
    }


    DirGraphNode *newNode = (DirGraphNode *) malloc(sizeof(DirGraphNode));
    newNode->value = value;
    newNode->sizeOfValue = sizeOfValue;
    newNode->adjacentNodes = arrayListInitialization(5, freeDGraphNode);
    hashMapInsert(graph->nodes, value, sizeOfValue, newNode, sizeof(DirGraphNode));

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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }


    DirGraphNode *nodeToDelete = (DirGraphNode *) hashMapGet(graph->nodes, value, sizeOfValue);

    if (nodeToDelete == NULL)
        return;


    void **hashMapNodes = (void **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {
        int index = arrayListGetIndex( ((DirGraphNode *) hashMapNodes[i])->adjacentNodes , nodeToDelete, dGraphNodeComp);
        if (index != -1)
            arrayListRemoveAtIndexWtFr(((DirGraphNode *) hashMapNodes[i])->adjacentNodes, index);

    }


    //TODO: if we changed the toArray function to return the original addresses instead of a copy,
    // then don't forget to edit here too.

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++)
        free(hashMapNodes[i]);

    free(hashMapNodes);

    hashMapDelete(graph->nodes, value, sizeOfValue);

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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }


    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal, sizeOfFromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal, sizeOfToVal);

    if(fromNode == NULL || toNode == NULL)
        return;


    arrayListAdd(fromNode->adjacentNodes, toNode, sizeof(DirGraphNode));

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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }


    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal, sizeOfFromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal, sizeOfToVal);

    if (fromNode == NULL || toNode == NULL)
        return;

    int toNodeIndex = arrayListGetIndex(fromNode->adjacentNodes, toNode, dGraphNodeComp);
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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    DirGraphNode *fromNode = hashMapGet(graph->nodes, fromVal, sizeOfFromVal);
    DirGraphNode *toNode = hashMapGet(graph->nodes, toVal, sizeOfToVal);

    if (fromNode == NULL || toNode == NULL)
        return 0;

    return arrayListContains(fromNode->adjacentNodes, toNode, dGraphNodeComp);

}










/** This function will return the number of nodes in the graph.
 * @param graph the graph address
 * @return it will reutrn the numebr of nodes in the graph
 */

int dirGraphGetNumOfNodes(DirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    return hashMapGetLength(graph->nodes) == 0;

}









/** This function will clear and free the graph nodes without freeing the graph itself.
 * @param graph the graph address
 */

void clearDirGraph(DirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    clearHashMap(graph->nodes);

}










/** This function will destroy and free the graph and all it's nodes.
 * @param graph the graph address
 */

void destroyDirGraph(DirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    destroyHashMap(graph->nodes);
    free(graph);

}









/** This function will print all the graph values in this from,
 * >>
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
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
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

int compInt(const void *int1, int s1, const void *int2, int s2) {
    return *(int *)int1 - *(int *)int2;
}








/** This function will depth first traverse the graph.
 * Note: actually you can do more than printing values, the printing function will take the value as a parameter.
 * @param graph the graph address
 * @param printVal the printing function address, that will be called to print the value
 */

void dirGraphDepthFirstTraversal(DirectedGraph *graph, void (*printVal)(void *)) {
    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    HashSet *visitedNodes = hashSetInitialization(freeInt, compInt);

    DirGraphNode **hashMapNodes = (DirGraphNode **) hashMapToArray(graph->nodes);

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++) {

        DirGraphNode *currentNode = hashMapNodes[i];
        int *address = (int *) malloc(sizeof(int));
        *address = (int) currentNode->value;

        if (!hashSetContains(visitedNodes, address, sizeof(int))) {

            printVal(currentNode->value);
            printf("\n");
            hashSetInsert(visitedNodes, address, sizeof(int));

            for (int j = 0; j < arrayListGetLength(currentNode->adjacentNodes); j++) {

                DirGraphNode *childNode = arrayListGet(currentNode->adjacentNodes, j);
                int *childAddress = (int *) malloc(sizeof(int));
                *childAddress = (int) childNode->value;


                if (!hashSetContains(visitedNodes, childAddress, sizeof(int))) {
                    printVal(childNode->value);
                    printf("\n");
                    hashSetInsert(visitedNodes, childAddress, sizeof(int));
                }

                else {
                    free(childAddress);
                }


            }

        }

        else {
            free(address);
        }

    }

    //TODO: if we changed the toArray function to return the original addresses instead of a copy,
    // then don't forget to edit here too.

    for (int i = 0; i < hashMapGetLength(graph->nodes); i++)
        free(hashMapNodes[i]);

    free(hashMapNodes);
    destroyHashSet(visitedNodes);

}