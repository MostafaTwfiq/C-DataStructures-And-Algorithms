#ifndef C_DATASTRUCTURES_LINEARSEARCH_H
#define C_DATASTRUCTURES_LINEARSEARCH_H


int linearSearch(void *oneBytePointer, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));

int linearSearchGetLast(void *oneBytePointer, void *value, int length, int elemSize,
                        int (*cmp)(const void *, const void *));

struct Vector *
linearSearchGetAll(void *oneBytePointer, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));


#endif //C_DATASTRUCTURES_LINEARSEARCH_H
