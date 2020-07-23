#ifndef C_DATASTRUCTURES_SORTINGALG_H
#define C_DATASTRUCTURES_SORTINGALG_H



void bubbleSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void selectionSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void insertionSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void mergeSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void quickSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void countingSortA(unsigned int *arr, int length, unsigned int rangeStart, unsigned int rangeEnd);

void countingSortH(unsigned int *arr, int length, unsigned int rangeStart, unsigned int rangeEnd);


#endif //C_DATASTRUCTURES_SORTINGALG_H
