#ifndef C_DATASTRUCTURES_DIRECTEDGRAPH_H
#define C_DATASTRUCTURES_DIRECTEDGRAPH_H


#include "Headers/ArrayList.h"
#include "Headers/HashMap.h"
#include "Headers/HashSet.h"


typedef struct DirGraphNode {
    void *value;
    ArrayList *adjacentNodes;
} DirGraphNode;

typedef struct DirectedGraph {
    HashMap *nodes;
    int sizeOfType;
    void (*freeItem)(void *);
} DirectedGraph;


#endif //C_DATASTRUCTURES_DIRECTEDGRAPH_H
