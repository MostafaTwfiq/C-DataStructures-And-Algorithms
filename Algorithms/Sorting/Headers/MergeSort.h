#ifndef C_DATASTRUCTURES_MERGESORT_H
#define C_DATASTRUCTURES_MERGESORT_H


void mergeSortWS(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));
void mergeSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

#endif //C_DATASTRUCTURES_MERGESORT_H
