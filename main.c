#include <stdio.h>
#include <stdlib.h>


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

#include "Headers/DoublyLinkedList.h"

void freeFuno(void *item) {
    free(item);
}

int comp(const void *p1, const void *p2) {
    return strcmp((char *)p1, (char *)p2);
}

int main() {
    DoublyLinkedList *linkedList = doublyLinkedListInitialization(freeFuno);

    char *item;

    item = malloc(sizeof(char ) * strlen("Mostafa") + 1);
    strcpy(item, "Mostafa");
    doublyLinkedListAddFirst(linkedList, item, strlen(item) + 1);

    item = malloc(sizeof(char ) * strlen("Mohammed") + 1);
    strcpy(item, "Mohammed");
    doublyLinkedListAddFirst(linkedList, item, strlen(item) + 1);

    item = malloc(sizeof(char ) * strlen("Tawfiq") + 1);
    strcpy(item, "Tawfiq");
    doublyLinkedListAddFirst(linkedList, item, strlen(item) + 1);


    item = malloc(sizeof(char ) * strlen("Ibrahim") + 1);
    strcpy(item, "Ibrahim");
    doublyLinkedListAddLast(linkedList, item, strlen(item) + 1);

    item = malloc(sizeof(char ) * strlen("Ali") + 1);
    strcpy(item, "Ali");
    doublyLinkedListAddLast(linkedList, item, strlen(item) + 1);


    doublyLinkedListDeleteAtIndex(linkedList, 3);

    item = malloc(sizeof(char ) * strlen("Ali") + 1);
    strcpy(item, "Ali");
    printf("%d\n\n\n", doublyLinkedListContains(linkedList, item, comp));


    //linkedListClear(linkedList);
    char **arr = (char **) doublyLinkedListToArray(linkedList);

    for (int i = 0; i < doublyLinkedListGetLength(linkedList); i++)
        printf("%s\n", arr[i]);


    destroyDoublyLinkedList(linkedList);

    return 0;

}