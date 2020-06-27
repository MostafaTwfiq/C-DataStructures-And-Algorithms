#include <stdio.h>
#include <stdlib.h>
#include "Headers/ArrayList.h"


int comparator(const void *p1, const void *p2) {
    return *((int *) (*((void **) p1))) - *((int *) (*((void **) p2)));
}

int main() {
    ArrayList *list = arrayListInitialization(10, sizeof(int));

    int arr[] = {40, 34, 45, 9};
    arrayListAddAll(list, arr, 4);

    arrayListSort(list, comparator);

    int *array = arrayListToArray(list);

    for (int i = 0; i < arrayListGetLength(list); i++) {
        printf("%d\n", array[i]);
    }
}