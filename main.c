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

#include "DataStructure/Graphs/Headers/DirectedGraph.h"
#include "DataStructure/Lists/Headers/ArrayList.h"
#include "DataStructure/Graphs/Headers/UndirectedGraph.h"
#include "DataStructure/Lists/Headers/Vector.h"
#include "DataStructure/Tables/Headers/HashSet.h"
#include "DataStructure/Strings/Headers/String.h"
#include "DataStructure/Deque/Headers/DLinkedListDeque.h"
#include "DataStructure/Trees/Headers/BinaryMaxHeap.h"
#include "Algorithms/Sorting/Headers/Sorting.h"
#include "Algorithms/Searching/Headers/Searching.h"
#include "Algorithms/ArraysAlgo/Headers/ArraysAlg.h"
#include "Algorithms/ArraysAlgo/Headers/CharArrayAlg.h"
#include "Algorithms/IntegersAlg/Headers/IntegerAlg.h"
#include "Algorithms/Sorting/Headers/HeapSort.h"
#include "DataStructure/Trees/Headers/BinaryMaxHeap.h"

void freeItem(void *item) {
    free(item);
}

int comp(const void *p1, const void *p2) {
    return strcmp((char *)p1, (char *)p2);
}

void print(void *item) {
    printf("%s", *(char **)item);
}

int getSize(const void *item) {
    return strlen((char *)item) + 1;
}


int intCmp(const void *p1, const void *p2) {
    return *(int *)p1 - *(int *)p2;
}


void printInt(void *item) {
    printf("%d->", *(int *)item);
}

void copyInt(const void *int1, const void *int2) {
    memcpy((void *) int1, int2, sizeof(int));
}

int comparatorFun(const void *i1, const void *i2) {
    return *(int *)*(int **)i1 - *(int *)*(int **)i2;
}


int intHashFuno(const void *item) {
    return *(int *)item;
}


int stringHashFun(const void *item) {
    char *string = (char *) item;
    int counter = 0;
    for (int i = 0; i < strlen(string); i++)
        counter += string[i];

    return counter;

}

int stringCmp(const void *s1, const void *s2) {
    return strcmp(s1, s2);
}

// ██████████████                      ████████████   ██████████████                      ██████████████ ██████
// ██░░░░░░░░░░██                      ██░░░░░░░░████ ██░░░░░░░░░░██                      ██░░░░░░░░░░██ ██░░██
// ██░░██████████                      ██░░████░░░░██ ██░░██████████                      ██░░██████░░██ ██░░██
// ██░░██                              ██░░██  ██░░██ ██░░██                              ██░░██  ██░░██ ██░░██
// ██░░██            ██████████████    ██░░██  ██░░██ ██░░██████████    ██████████████    ██░░██████░░██ ██░░██
// ██░░██            ██░░░░░░░░░░██    ██░░██  ██░░██ ██░░░░░░░░░░██    ██░░░░░░░░░░██    ██░░░░░░░░░░██ ██░░██
// ██░░██            ██████████████    ██░░██  ██░░██ ██████████░░██    ██████████████    ██░░██████░░██ ██░░██
// ██░░██                              ██░░██  ██░░██         ██░░██                      ██░░██  ██░░██ ██░░██
// ██░░██████████                      ██░░████░░░░██ ██████████░░██                      ██░░██  ██░░██ ██░░██████████
// ██░░░░░░░░░░██                      ██░░░░░░░░████ ██░░░░░░░░░░██                      ██░░██  ██░░██ ██░░░░░░░░░░██
// ██████████████                      ████████████   ██████████████                      ██████  ██████ ██████████████



int main() {

    int fArr[] = {1, 2, 3, 2, 1};
    int sArr[] = {11};
    printf("%d", arrIsPalindrome(fArr, 5, sizeof(int), intCmp));
    int arr[] = {1, 2, 3, 4, 5, 5, 3, 3, 2, 10}; // length = 10;
    printf("Most frequent: %d\n\n", *(int*)mostFrequentArrValueA(arr, 10, sizeof(int), intCmp));
    int newLength = arrRemoveDuplicatesA(arr, 10, sizeof(int), intCmp, NULL);
    printArr(arr, newLength, sizeof(int), printInt);
    return 0;
}