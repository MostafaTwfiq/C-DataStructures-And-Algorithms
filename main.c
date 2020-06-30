#include <stdio.h>
#include <stdlib.h>
#include "Headers/PriorityQueue.h"


int comp(const void *p1, const void *p2) {
    return *((int *)p1) - *((int *)p2);
}

int main() {
    PriorityQueue *queue = priorityQueueInitialization(sizeof(int), comp);

    int temp[] = {20, 4, 10, 5, 3, 34, 33, 5, 2};
    int **arr = (int **) malloc(sizeof(int *) * 9);
    for (int i = 0; i < 9; i++) {
        arr[i] = (int *) malloc(sizeof(int));
        arr[i][0] = temp[i];
    }

    pQueueEnqueueAll(queue, (void **) arr, 9);
    free(pQueueDequeue(queue));

    int *temp2;

    temp2 = (int *) malloc(sizeof(int));
    *temp2 = 65;
    pQueueEnqueue(queue, temp2);

    temp2 = (int *) malloc(sizeof(int));
    *temp2 = 63;
    pQueueEnqueue(queue, temp2);

    temp2 = (int *) malloc(sizeof(int));
    *temp2 = 62;
    pQueueEnqueue(queue, temp2);

    int **array = (int **) pQueueToArray(queue);
    for (int i = 0; i < pQueueGetLength(queue); i++)
        printf("%d\n", *array[i]);

    destroyPQueue(queue);

}