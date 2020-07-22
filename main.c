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

#include "DataStructure/Graphs/Headers/DirectedGraph.h"
#include "DataStructure/Lists/Headers/ArrayList.h"
#include "DataStructure/Graphs/Headers/UndirectedGraph.h"
#include "DataStructure/Lists/Headers/Vector.h"
#include "DataStructure/Deque/Headers/DLinkedListDeque.h"
#include "Algorithms/Sorting/SortingAlg.h"

void freeItem(void *item) {
    free(item);
}

int comp(const void *p1, const void *p2) {
    return strcmp((char *)p1, (char *)p2);
}

void print(void *item) {
    printf("%s", (char *)item);
}

int getSize(const void *item) {
    return strlen((char *)item) + 1;
}


int intCmp(const void *p1, const void *p2) {
    return *(int *)p1 - *(int *)p2;
}

int main() {


    int arr[] = {55, 4, 33, 2, 0, 1, 3};
    mergeSort(arr, 7, sizeof(int), intCmp);
    for (int i = 0; i < 7; i++) {
        printf("%d ", arr[i]);
    }

    /*DLDeque *deque = dlDequeInitialization(freeItem);
    int *value;

    value = (int *) malloc(sizeof(int));
    *value = 30;
    dLDequeInsertFront(deque, value);

    value = (int *) malloc(sizeof(int));
    *value = 20;
    dLDequeInsertFront(deque, value);

    value = (int *) malloc(sizeof(int));
    *value = 10;
    dLDequeInsertFront(deque, value);

    value = (int *) malloc(sizeof(int));
    *value = 40;
    dLDequeInsertRear(deque, value);

    value = (int *) malloc(sizeof(int));
    *value = 50;
    dLDequeInsertRear(deque, value);

    value = (int *) malloc(sizeof(int));
    *value = 60;
    dLDequeInsertRear(deque, value);


    int **arr = (int **) dLDequeToArray(deque);

    for (int i = 0; i < dLDequeGetLength(deque); i++) {
        printf("%d\n", arr[i][0]);
    }

    //60
    //10
    //50
    //20
    //40
    //30


*/

    exit(0);




    UndirectedGraph *graph = undirectedGraphInitialization(freeItem, comp);
    char *item;

    item = (char *) malloc(sizeof(char ) * (strlen("A") + 1));
    strcpy(item, "A");
    UDGraphAddNode(graph, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char ) * (strlen("B") + 1));
    strcpy(item, "B");
    UDGraphAddNode(graph, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char ) * (strlen("C") + 1));
    strcpy(item, "C");
    UDGraphAddNode(graph, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char ) * (strlen("D") + 1));
    strcpy(item, "D");
    UDGraphAddNode(graph, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char ) * (strlen("E") + 1));
    strcpy(item, "E");
    UDGraphAddNode(graph, item, strlen(item) + 1);

    UDGraphAddEdge(graph, "A", strlen("A") + 1, "B", strlen("B") + 1, 3);
    UDGraphAddEdge(graph, "A", strlen("A") + 1, "C", strlen("C") + 1, 1);
    //UDGraphAddEdge(graph, "A", strlen("A") + 1, "D", strlen("D") + 1, 2);
    UDGraphAddEdge(graph, "D", strlen("D") + 1, "B", strlen("B") + 1, 4);
    UDGraphAddEdge(graph, "D", strlen("D") + 1, "C", strlen("C") + 1, 5);
    UDGraphAddEdge(graph, "B", strlen("B") + 1, "C", strlen("C") + 1, 2);
    //UDGraphAddEdge(graph, "D", strlen("D") + 1, "E", strlen("E") + 1, 5);
    //UDGraphAddEdge(graph, "B", strlen("B") + 1, "E", strlen("E") + 1, 1);

    //UDGraphRemoveEdge(graph, "Mostafa", strlen("Mostafa") + 1, "Mohammed", strlen("Mohammed") + 1);
    //UDGraphRemoveNode(graph, "Mostafa", strlen("Mostafa") + 1);

    //printf("Add");

    /*ArrayList *list = UDGraphGetShortestPath(graph, "A", strlen("A") + 1, "A", strlen("A") + 1);
    for (int i = 0; i < arrayListGetLength(list); i++)
        printf("%s ", arrayListGet(list, i));

    printf("\n\n");
    printf("%d", UDGraphNodePartOfCycle(graph, "A", strlen("A") + 1));*/
    printUDGraph(UDGraphMinimumSpanningGraph(graph, "A", getSize), print);

    //destroyUDGraph(graph);

    /*DirectedGraph *graph = directedGraphInitialization(freeItem, comp);
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
    dirGraphAddEdge(graph, "Tawfiq", strlen("Tawfiq") + 1, "Mostafa", strlen("Mostafa") + 1);

    //Mostafa --> Mohammed --> Tawfiq
    //Mostafa ---------------> Tawfiq

    printf("%d\n\n", dirGraphHasACycle(graph));
    ArrayList *arrayList = dirGraphTopologicalSort(graph);
    for (int i = 0; i < arrayListGetLength(arrayList); i++)
        printf("%s\n", (char *) arrayListGet(arrayList, i));

     */
    return 0;

}