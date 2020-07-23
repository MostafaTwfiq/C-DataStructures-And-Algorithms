#ifndef C_DATASTRUCTURES_SEARCHINGALG_H
#define C_DATASTRUCTURES_SEARCHINGALG_H


int linearSearch(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));

int linearSearchGetLast(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));

struct Vector *linearSearchGetAll(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));


#endif //C_DATASTRUCTURES_SEARCHINGALG_H
