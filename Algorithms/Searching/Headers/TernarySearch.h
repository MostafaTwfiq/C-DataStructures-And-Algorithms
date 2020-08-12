#ifndef C_DATASTRUCTURES_TERNARYSEARCH_H
#define C_DATASTRUCTURES_TERNARYSEARCH_H


int ternarySearchI(void *oneBytePointer, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));

int ternarySearchR(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));


#endif //C_DATASTRUCTURES_TERNARYSEARCH_H
