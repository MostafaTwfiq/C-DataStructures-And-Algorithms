#ifndef C_DATASTRUCTURES_BINARYSEARCH_H
#define C_DATASTRUCTURES_BINARYSEARCH_H


int binarySearchI(void *oneBytePointer, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));

int binarySearchR(void *arr, void *value, int length, int elemSize, int (*cmp)(const void *, const void *));


#endif //C_DATASTRUCTURES_BINARYSEARCH_H
