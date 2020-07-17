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
#include "Headers/ArrayList.h"

void freeItem(void *item) {
    free(item);
}

int comp(const void *p1, const void *p2) {
    return strcmp((char *)p1, (char *)p2);
}

void print(void *item) {
    printf("%s", (char *)item);
}

int main() {

    DirectedGraph *graph = directedGraphInitialization(freeItem, comp);
    char *item;

    item = (char *) malloc(sizeof(char ) * (strlen("Mostafa") + 1));
    strcpy(item, "Mostafa");
    dirGraphAddNode(graph, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char ) * (strlen("Mohammed") + 1));
    strcpy(item, "Mohammed");
    dirGraphAddNode(graph, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char ) * (strlen("Tawfiq") + 1));
    strcpy(item, "Tawfiq");
    dirGraphAddNode(graph, item, strlen(item) + 1);


    dirGraphAddEdge(graph, "Mostafa", strlen("Mostafa") + 1, "Mohammed", strlen("Mohammed") + 1);
    dirGraphAddEdge(graph, "Mohammed", strlen("Mohammed") + 1, "Tawfiq", strlen("Tawfiq") + 1);
    dirGraphAddEdge(graph, "Mostafa", strlen("Mostafa") + 1, "Tawfiq", strlen("Tawfiq") + 1);


    ArrayList *arrayList = dirGraphTopologicalSort(graph);
    for (int i = 0; i < arrayListGetLength(arrayList); i++)
        printf("%s\n", (char *) arrayListGet(arrayList, i));

    return 0;

}