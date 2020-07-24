#ifndef C_DATASTRUCTURES_ARRAYSALG_H
#define C_DATASTRUCTURES_ARRAYSALG_H


void reverseArray(void *arr, int length, int elemSize);

void *mostFrequentArrValue(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));


#endif //C_DATASTRUCTURES_ARRAYSALG_H
