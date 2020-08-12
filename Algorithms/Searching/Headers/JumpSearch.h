#ifndef C_DATASTRUCTURES_JUMPSEARCH_H
#define C_DATASTRUCTURES_JUMPSEARCH_H


int jumpSearch(void *oneBytePointer, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));


#endif //C_DATASTRUCTURES_JUMPSEARCH_H
