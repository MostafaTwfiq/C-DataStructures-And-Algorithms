#ifndef C_DATASTRUCTURES_ARRAYSALG_H
#define C_DATASTRUCTURES_ARRAYSALG_H


void reverseArray(void *arr, int length, int elemSize);

void *mostFrequentArrValueH(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *), int (*hashFun)(const void *));

void *mostFrequentArrValueA(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *));

void printArr(void *arr, int length, int elemSize, void (*printFun)(void *));

void *arrResize(void *arr, int length, int elemSize, int newLength);

void *arrResizeOfRange(void *arr, int length, int elemSize, int startIndex, int endIndex, int newLength);

void *arrResizeC(void *arr, int length, int elemSize, int newLength, void (*copyFun)(const void *, const void *));

void *arrResizeOfRangeC(void *arr, int length, int elemSize, int startIndex, int endIndex, int newLength, void (*copyFun)(const void *, const void *));

void *arrCopy(void *arr, int length, int elemSize);

void *arrCopyC(void *arr, int length, int elemSize, void (*copyFun)(const void *, const void *));

void *arrCopyOfRange(void *arr, int length, int elemSize, int startIndex, int endIndex);

void *arrCopyOfRangeC(void *arr, int length, int elemSize, int startIndex, int endIndex, void (*copyFun)(const void *, const void *));

void fillArr(void *arr, void *fillValue, int length, int elemSize);

void fillArrC(void *arr, void *fillValue, int length, int elemSize, void (*copyFun)(const void *, const void *));

void fillArrOfRange(void *arr, void *fillValue, int length, int elemSize, int startIndex, int endIndex);

void fillArrOfRangeC(void *arr, void *fillValue, int length, int elemSize, int startIndex, int endIndex, void (*copyFun)(const void *, const void *));

int arrCompare(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int (*cmp)(const void *, const void *));

int arrCompareOfRange(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int startIndex, int endIndex, int (*cmp)(const void *, const void *));

int arrMismatch(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int (*cmp)(const void *, const void *));

int arrMismatchOfRange(void *fArr, int fLength, void *sArr, int sLength, int elemSize, int startIndex, int endIndex, int (*cmp)(const void *, const void *));

int arrRemoveDuplicatesH(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *), int (*hashFun)(const void *), void (*freeFun)(void *));

int arrRemoveDuplicatesA(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *), void (*freeFun)(void *));

#endif //C_DATASTRUCTURES_ARRAYSALG_H
