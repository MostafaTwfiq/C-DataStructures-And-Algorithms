#ifndef C_DATASTRUCTURES_ARRAYSALG_H
#define C_DATASTRUCTURES_ARRAYSALG_H


void reverseArray(void *arr, int length, int elemSize);

void *mostFrequentArrValue(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void printArr(void *arr, int length, int elemSize, void (*printFun)(void *));

void *arrCopy(void *arr, int length, int elemSize);

void *arrCopyC(void *arr, int length, int elemSize, void *copyFun(const void *, const void *));

void *arrCopyOfRange(void *arr, int length, int elemSize, int startIndex, int endIndex);

void *arrCopyOfRangeC(void *arr, int length, int elemSize, int startIndex, int endIndex, void *copyFun(const void *, const void *));

#endif //C_DATASTRUCTURES_ARRAYSALG_H
