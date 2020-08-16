#ifndef C_DATASTRUCTURES_INTEGERALG_H
#define C_DATASTRUCTURES_INTEGERALG_H

int integerNumOfDigits(int num);

char *intToCharArr(int num);

int maxInt(int a, int b);

int minInt(int a, int b);

int compareInt(int a, int b);

int compareIntR(int a, int b);

int compareIntPointers(const void *a, const void *b);

int compareIntPointerR(const void *a, const void *b);

int *generateIntPointerP(int *integer);

int *generateIntPointerI(int integer);

int intHashFun(const void *integer);

int intSum(int a, int b);

int intArrSum(const int *arr, int length);


#endif //C_DATASTRUCTURES_INTEGERALG_H
