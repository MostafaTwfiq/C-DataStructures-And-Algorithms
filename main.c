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
#include "Headers/Deque.h"

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

    Deque *deque = dequeInitialization(freeItem);
    int *item1;

    item1 = (int *) malloc(sizeof(int));
    *item1 = 10;
    dequeInsertRear(deque, item1);

    item1 = (int *) malloc(sizeof(int));
    *item1 = 20;
    dequeInsertRear(deque, item1);

    item1 = (int *) malloc(sizeof(int));
    *item1 = 30;
    dequeInsertRear(deque, item1);

    item1 = (int *) malloc(sizeof(int));
    *item1 = 40;
    dequeInsertRear(deque, item1);

    // 10 20 30 40

    printf("%d\n", *(int *)dequeGetRear(deque));
    printf("%d\n\n", *(int *)dequeGetFront(deque));

    // 20 30

    item1 = (int *) malloc(sizeof(int));
    *item1 = 50;
    dequeInsertFront(deque, item1);

    item1 = (int *) malloc(sizeof(int));
    *item1 = 60;
    dequeInsertFront(deque, item1);

    item1 = (int *) malloc(sizeof(int));
    *item1 = 70;
    dequeInsertFront(deque, item1);

    // 70 60 50 20 30

    while (!dequeIsEmpty(deque)) {
        printf("%d\n", *(int *)dequeGetRear(deque));
        //printf("%d\n", *(int *)dequeGetFront(deque));
    }

    destroyDeque(deque);
    exit(0);


















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
    dirGraphAddEdge(graph, "Tawfiq", strlen("Tawfiq") + 1, "Mostafa", strlen("Mostafa") + 1);

    //Mostafa --> Mohammed --> Tawfiq
    //Mostafa ---------------> Tawfiq

    printf("%d\n\n", dirGraphHasACycle(graph));
    ArrayList *arrayList = dirGraphTopologicalSort(graph);
    for (int i = 0; i < arrayListGetLength(arrayList); i++)
        printf("%s\n", (char *) arrayListGet(arrayList, i));

    return 0;

}