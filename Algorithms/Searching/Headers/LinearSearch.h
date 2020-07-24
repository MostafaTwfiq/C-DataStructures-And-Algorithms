#ifndef C_DATASTRUCTURES_LINEARSEARCH_H
#define C_DATASTRUCTURES_LINEARSEARCH_H




int linearSearch(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));

int linearSearchGetLast(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));

struct Vector *linearSearchGetAll(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));


#endif //C_DATASTRUCTURES_LINEARSEARCH_H
