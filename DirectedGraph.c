#include "DirectedGraph.h"






void (*dGFreeValue)(void *key);


void freeDGraphNode(void *item) {
    DirGraphNode *itemToFree =  (DirGraphNode *) item;
    dGFreeValue(itemToFree->value);

    if (itemToFree->adjacentNodes != NULL)
        destroyArrayList(itemToFree->adjacentNodes);

    free(itemToFree);

}

int (*valueCompFun)(const void *key1, int s1, const void *key2, int s2);

int dGraphNodeComp (const void *n1, const void *n2) {
    DirGraphNode *node1 = (DirGraphNode *) n1;
    DirGraphNode *node2 = (DirGraphNode *) n2;

    return valueCompFun(node1->value, node1->sizeOfValue, node2->value, node2->sizeOfValue);

}





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


void dirGraphAddNode(DirectedGraph *graph, void *value, int sizeOfValue) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }


    if (hashMapContains(graph->nodes, value, sizeOfValue))
        return;


    DirGraphNode *newNode = (DirGraphNode *) malloc(sizeof(DirGraphNode));
    newNode->value = value;
    newNode->sizeOfValue = sizeOfValue;
    newNode->adjacentNodes = arrayListInitialization(5, freeDGraphNode);
    hashMapInsert(graph->nodes, value, sizeOfValue, newNode, sizeof(DirGraphNode));

}

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

    hashMapDelete(graph->nodes, value, sizeOfValue);

}


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


int dirGraphContainsNode(DirectedGraph *graph, void *value, int sizeOfValue) {
    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    return hashMapContains(graph->nodes, value, sizeOfValue);

}


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


int dirGraphGetNumOfNodes(DirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    return hashMapGetLength(graph->nodes);

}


int dirGraphIsEmpty(DirectedGraph *graph) {
    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    return hashMapGetLength(graph->nodes) == 0;

}

void clearDirGraph(DirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    clearHashMap(graph->nodes);

}



void destroyDirGraph(DirectedGraph *graph) {

    if (graph == NULL) {
        fprintf(stderr, "Illegal argument, the directed graph is null.");
        exit(-3);
    }

    destroyHashMap(graph->nodes);
    free(graph);

}


void dirGraphPrint(DirectedGraph *graph, void (*printVal)(void *)) {
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

