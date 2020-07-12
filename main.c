#include <stdio.h>
#include <stdlib.h>
#include "Headers/HashSet.h"
#include "Headers/ArrayList.h"


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



void freeFuno(void *item) {
    free(item);
}

int comp(const void *item1, const void *item2) {
    return *(int *)(*(ArrayListItem **)item1)->value - *(int *)(*(ArrayListItem **)item2)->value;
}

int main() {

    ArrayList *arrayList = arrayListInitialization(1, freeFuno);

    int *item;

    item = (int *) malloc(sizeof(int));
    *item = 20;
    arrayListAdd(arrayList, item, sizeof(int));

    item = (int *) malloc(sizeof(int));
    *item = 30;
    arrayListAdd(arrayList, item, sizeof(int));

    item = (int *) malloc(sizeof(int));
    *item = 10;
    arrayListAdd(arrayList, item, sizeof(int));

    item = (int *) malloc(sizeof(int));
    *item = 40;
    arrayListAdd(arrayList, item, sizeof(int));

    arrayListSort(arrayList, comp);
    //arrayListRemoveAtIndex(arrayList, 3);

    //clearArrayList(arrayList);
    int **arr = (int **) arrayListToArray(arrayList);

    for (int i = 0; i < arrayListGetLength(arrayList); i++) {
        printf("%d\n", *arr[i]);
    }

    destroyArrayList(arrayList);

    return 0;

}