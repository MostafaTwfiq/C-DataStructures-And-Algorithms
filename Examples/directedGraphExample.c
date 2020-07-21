#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BOLD_RED     "\x1b[1;31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BOLD_GREEN   "\x1b[1;32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BOLD_YELLOW  "\x1b[01;33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_BOLD_BLUE    "\x1b[1;34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_BOLD_MAGENTA "\x1b[1;35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BOLD_CYAN    "\x1b[1;36m"
#define ANSI_COLOR_WHITE    "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include "Headers/DirectedGraph.h"

void freeItem(void *item) {
    free(item);
}

int comp(const void *p1, int s1, const void *p2, int s2) {
    return strcmp((char *)p1, (char *)p2);
}

void print(void *item) {
    printf("%s\n", (char *)item);
}

int main() {
    DirectedGraph *graph = directedGraphInitialization(freeItem, comp);

    char *node;

    node = (char *) malloc(sizeof(char) * (strlen("A") + 1) );
    strcpy(node, "A");
    dirGraphAddNode(graph, node, strlen(node) + 1);

    node = (char *) malloc(sizeof(char) * (strlen("B") + 1) );
    strcpy(node, "B");
    dirGraphAddNode(graph, node, strlen(node) + 1);

    node = (char *) malloc(sizeof(char) * (strlen("C") + 1) );
    strcpy(node, "C");
    dirGraphAddNode(graph, node, strlen(node) + 1);

    node = (char *) malloc(sizeof(char) * (strlen("D") + 1) );
    strcpy(node, "D");
    dirGraphAddNode(graph, node, strlen(node) + 1);

    node = (char *) malloc(sizeof(char) * (strlen("E") + 1) );
    strcpy(node, "E");
    dirGraphAddNode(graph, node, strlen(node) + 1);


    dirGraphAddEdge(graph, "A", strlen("A") + 1, "B", strlen("B") + 1);
    dirGraphAddEdge(graph, "A", strlen("A") + 1, "E", strlen("E") + 1);
    dirGraphAddEdge(graph, "D", strlen("D") + 1, "E", strlen("E") + 1);
    dirGraphAddEdge(graph, "B", strlen("B") + 1, "E", strlen("E") + 1);
    dirGraphAddEdge(graph, "C", strlen("C") + 1, "D", strlen("D") + 1);
    dirGraphAddEdge(graph, "C", strlen("C") + 1, "E", strlen("E") + 1);
    dirGraphAddEdge(graph, "C", strlen("C") + 1, "B", strlen("B") + 1);
    //dirGraphRemoveEdge(graph, "Mostafa", strlen("Mostafa") + 1, "Mohammed", strlen("Mohammed") + 1);
    //dirGraphRemoveNode(graph, "Tawfiq", strlen("Tawfiq") + 1);
    //print("done");
    //dirGraphPrint(graph, print);

    //dirGraphDepthFirstTraversal(graph, print);
    //printf("\n\n%d", dirGraphContainsEdge(graph, "Mohammed", strlen("Mohammed") + 1, "Tawfiq", strlen("Tawfiq") + 1));

    //printf("%d", dirGraphGetNumOfNodes(graph));

    dirGraphBreadthFirstTraversal(graph, "C", strlen("C") + 1, print);

    destroyDirGraph(graph);
    return 0;

}