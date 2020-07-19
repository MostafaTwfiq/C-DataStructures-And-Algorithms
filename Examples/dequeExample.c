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

    printf("%d\n", *(int *) dequeGetRear(deque));
    printf("%d\n\n", *(int *) dequeGetFront(deque));

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
        printf("%d\n", *(int *) dequeGetRear(deque));
        //printf("%d\n", *(int *)dequeGetFront(deque));
    }

    destroyDeque(deque);

}