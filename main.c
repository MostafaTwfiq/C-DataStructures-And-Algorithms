#include <stdio.h>
#include <stdlib.h>
#include "Headers/HashSet.h"

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

int main() {

    HashSet *hashSet = hashSetInitialization(sizeof(int));

    int *item;

    item = (int *) malloc(sizeof(int));
    *item = 10;
    hashSetInsert(hashSet, item);


    item = (int *) malloc(sizeof(int));
    *item = 100;
    hashSetInsert(hashSet, item);

    item = (int *) malloc(sizeof(int));
    *item = 30;
    hashSetInsert(hashSet, item);

    item = (int *) malloc(sizeof(int));
    *item = 40;
    hashSetInsert(hashSet, item);

    item = (int *) malloc(sizeof(int));
    *item = 100;
    hashSetDelete(hashSet, item);


    *item = 40;
    printf("has 40: %d\n", hashSetContains(hashSet, item));
    *item = 100;
    printf("has 100: %d\n", hashSetContains(hashSet, item));


    destroyHashSet(hashSet);
    int **arr = (int **) hashSetToArray(hashSet);

    for (int i = 0; i < hashSetGetLength(hashSet); i++) {
        printf("%d\n", *arr[i]);
    }

    return 0;

}