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

#include "Headers/PriorityQueue.h"

void freeItem(void *item) {
    free(item);
}

int comp(const void *p1, int s1, const void *p2, int s2) {
    return *(int *)p1 - *(int *)p2;
}


int main() {

    PriorityQueue *queue = priorityQueueInitialization(freeItem, comp);

    int *item;

    item = (int *) malloc(sizeof(int));
    *item = 20;
    pQueueEnqueue(queue, item, sizeof(int));

    item = (int *) malloc(sizeof(int));
    *item = 10;
    pQueueEnqueue(queue, item, sizeof(int));

    item = (int *) malloc(sizeof(int));
    *item = 55;
    pQueueEnqueue(queue, item, sizeof(int));

    item = (int *) malloc(sizeof(int));
    *item = 23;
    pQueueEnqueue(queue, item, sizeof(int));



    int **arr = (int **) pQueueToArray(queue);

    for (int i = 0; i < pQueueGetLength(queue); i++)
        printf("%d\n", *arr[i]);

    destroyPQueue(queue);

    return 0;

}