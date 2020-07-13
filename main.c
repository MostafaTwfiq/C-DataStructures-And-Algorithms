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

#include "Headers/HashSet.h"

void freeItem(void *item) {
    free(item);
}

void freeKey(void *key) {
    free(key);
}

/*int comp(const void *p1, const void *p2) {
    return strcmp((char *)p1, (char *)p2);
}*/

int main() {
    HashSet *hashSet = hashSetInitialization(freeItem);

    char *item;

    item = (char *) malloc(sizeof(char) * (strlen("One") + 1) );
    strcpy(item, "One");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Two") + 1) );
    strcpy(item, "Two");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Three") + 1) );
    strcpy(item, "Three");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Four") + 1) );
    strcpy(item, "Four");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Five") + 1) );
    strcpy(item, "Five");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    hashSetDelete(hashSet, "Five", 5);

    printf("Contains four: %d\nContains five: %d\n\n", hashSetContains(hashSet, "Four", 5), hashSetContains(hashSet, "Five", 5));

    item = (char *) malloc(sizeof(char) * (strlen("Six") + 1) );
    strcpy(item, "Six");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Seven") + 1) );
    strcpy(item, "Seven");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Eight") + 1) );
    strcpy(item, "Eight");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Nine") + 1) );
    strcpy(item, "Nine");
    hashSetInsert(hashSet, item, strlen(item) + 1);

    item = (char *) malloc(sizeof(char) * (strlen("Ten") + 1) );
    strcpy(item, "Ten");
    hashSetInsert(hashSet, item, strlen(item) + 1);



    char **arr = (char **) hashSetToArray(hashSet);
    for (int i = 0; i < hashSetGetLength(hashSet); i++)
        printf("%s\n", arr[i]);


    destroyHashSet(hashSet);

    return 0;

}