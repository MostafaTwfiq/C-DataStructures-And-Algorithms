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

void freeKey(void *key) {
    free(key);
}

/*int comp(const void *p1, const void *p2) {
    return strcmp((char *)p1, (char *)p2);
}*/

int main() {
    HashMap *hashMap = hashMapInitialization(freeItem, freeKey);

    char *key;
    int *item;

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("One") + 1) );
    strcpy(key, "One");
    item = (int *) malloc(sizeof(int));
    *item = 1;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Two") + 1) );
    strcpy(key, "Two");
    item = (int *) malloc(sizeof(int));
    *item = 2;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Three") + 1) );
    strcpy(key, "Three");
    item = (int *) malloc(sizeof(int));
    *item = 3;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Four") + 1) );
    strcpy(key, "Four");
    item = (int *) malloc(sizeof(int));
    *item = 4;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Five") + 1) );
    strcpy(key, "Five");
    item = (int *) malloc(sizeof(int));
    *item = 5;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");


    hashMapDelete(hashMap, "Five", 5);
    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("Contains five: %d\n", hashMapContains(hashMap, "Five", 5));
    printf("Contains four: %d\n", hashMapContains(hashMap, "Four", 5));
    printf("------------------------------------\n");


    key = (char *) malloc(sizeof(char ) * (strlen("Six") + 1) );
    strcpy(key, "Six");
    item = (int *) malloc(sizeof(int));
    *item = 6;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Seven") + 1) );
    strcpy(key, "Seven");
    item = (int *) malloc(sizeof(int));
    *item = 7;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Eight") + 1) );
    strcpy(key, "Eight");
    item = (int *) malloc(sizeof(int));
    *item = 8;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Nine") + 1) );
    strcpy(key, "Nine");
    item = (int *) malloc(sizeof(int));
    *item = 9;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));

    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");

    key = (char *) malloc(sizeof(char ) * (strlen("Ten") + 1) );
    strcpy(key, "Ten");
    item = (int *) malloc(sizeof(int));
    *item = 10;
    hashMapInsert(hashMap, key, strlen(key) + 1, item, sizeof(int));


    printf("Array length: %d , BPrime: %d\n", hashMap->length, hashMap->bPrime);
    for (int i = 0; i < hashMap->length; i++)
        printf("%p   ----> index: %d\n", hashMap->arr[i], i);
    printf("------------------------------------\n");


    clearHashMap(hashMap);
    Entry **arr = (Entry **) hashMapToEntryArray(hashMap);

    for (int i = 0; i < hashMapGetLength(hashMap); i++)
        printf("I: %d -- Key: %s -- Value: %d\n", i, arr[i]->key, *((int *)arr[i]->item->value));


    destroyHashMap(hashMap);

    return 0;

}