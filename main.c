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

#include "Headers/HashMap.h"

void freeItem(void *item) {
    free(item);
}

int comp(void *p1, int s1, void *p2, int s2) {
    return strcmp((char *)p1, (char *)p2);
}


typedef struct try {
    int *m;
} try;


int main() {

    HashMap *hashMap = hashMapInitialization(freeItem, freeItem, comp);

    char *key;
    int *item;


    key = (char *) malloc(sizeof(char ) * (strlen("One") + 1));
    strcpy(key, "One");
    item = (int *) malloc(sizeof(int));
    *item = 1;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    key = (char *) malloc(sizeof(char ) * (strlen("Two") + 1));
    strcpy(key, "Two");
    item = (int *) malloc(sizeof(int));
    *item = 2;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    key = (char *) malloc(sizeof(char ) * (strlen("Three") + 1));
    strcpy(key, "Three");
    item = (int *) malloc(sizeof(int));
    *item = 3;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    key = (char *) malloc(sizeof(char ) * (strlen("Three") + 1));
    strcpy(key, "Three");
    item = (int *) malloc(sizeof(int));
    *item = 1000;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));


    Entry **entries = hashMapToEntryArray(hashMap);

    for (int i = 0; i < hashMapGetLength(hashMap); i++) {
        printf("Key: %s , Value: %d\n", entries[i]->key, *(int *)entries[i]->item->value);
    }
    return 0;

}