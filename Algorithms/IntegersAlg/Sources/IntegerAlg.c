#include "../Headers/IntegerAlg.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"
#include <math.h>


/** This function will an integer,
 * then it will return the number of digits of the integer, without considering the sign.
 *
 * @param num the integer value
 * @return it will return the number of digits
 */

int integerNumOfDigits(int num) {

    if (num == 0)
        return 1;

    return (int) floor(log10(num < 0 ? num * -1 : num) + 1);

}


/** This function will take an integer number,
 * then it will return a char array pointer, that consist of the passed integer.
 *
 * @param num the number value
 * @return it will return the integer value as a char array pointer
 */

char *intToCharArr(int num) {

    short negativeNumFlag = num < 0 ? 1 : 0;
    int numOfDigits = integerNumOfDigits(num);

    char *numCharArr = (char *) malloc(sizeof(char) * (numOfDigits + 1 + negativeNumFlag));
    if (numCharArr == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "integer char array", "int to char array function");
        exit(FAILED_ALLOCATION);
    }

    numCharArr[numOfDigits + negativeNumFlag] = '\0';
    if (negativeNumFlag) {
        *numCharArr = '-';
        num *= -1;
    }

    for (int i = 0; i < numOfDigits; i++, num /= 10)
        numCharArr[numOfDigits + negativeNumFlag - 1 - i] = (num % 10) + '0';

    return numCharArr;

}


/** This function will return the integer with the larger value.
 *
 * @param a the first integer
 * @param b the second integer
 * @return it will return the max integer value
 */

int maxInt(int a, int b) {
    return a > b ? a : b;
}


/** This function will return the integer with the smallest value.
 *
 * @param a the first integer value
 * @param b the second integer value
 * @return it will return the minimum integer value
 */

int minInt(int a, int b) {
    return a > b ? b : a;
}


/** This function will compare to integers,
 * then it will return zero if they are equal, negative number if the second integer is bigger,
 * and positive number if the first integer is bigger.
 *
 * @param a the first integer value
 * @param b the second integer value
 * @return it will return zero if they are equal, negative number if the second integer is bigger, and positive number if the first integer is bigger.
 */

int compareInt(int a, int b) {
    return a - b;
}


/** This function will compare to integers,
 * then it will return zero if they are equal, negative number if the second integer is smaller,
 * and positive number if the first integer is smaller.
 *
 * @param a the first integer value
 * @param b the second integer value
 * @return it will return zero if they are equal, negative number if the second integer is smaller, and positive number if the first integer is smaller.
 */

int compareIntR(int a, int b) {
    return b - a;
}


/** This function will compare to integers pointers,
 * then it will return zero if they are equal, negative number if the second integer is bigger,
 * and positive number if the first integer is bigger.
 *
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is bigger, and positive number if the first integer is bigger.
 */

int compareIntPointers(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}


/** This function will compare to integers pointers,
 * then it will return zero if they are equal, negative number if the second integer is bigger,
 * and positive number if the first integer is bigger.
 *
 * @param a the first integer pointer
 * @param b the second integer pointer
 * @return it will return zero if they are equal, negative number if the second integer is smaller, and positive number if the first integer is smaller.
 */

int compareIntPointerR(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}


/** This function will take an integer pointer,
 * then it will allocate a new integer and copy the passed pointer value into the new one,
 * and finally return the new integer pointer.
 *
 * @param integer the integer pointer
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerP(int *integer) {

    int *newInt = (int *) malloc(sizeof(int));
    if (newInt == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new integer", "generate integer pointer function");
        exit(FAILED_ALLOCATION);
    }

    memcpy(newInt, integer, sizeof(int));
    return newInt;

}


/** This function will take an integer,
 * then it will allocate a new integer and copy the passed integer value into the new pointer,
 * and finally return the new integer pointer.
 *
 * @param integer the integer value
 * @return it will return the new allocated integer pointer
 */

int *generateIntPointerI(int integer) {
    int *newInt = (int *) malloc(sizeof(int));
    if (newInt == NULL) {
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new integer", "generate integer pointer function");
        exit(FAILED_ALLOCATION);
    }

    *newInt = integer;
    return newInt;

}


/** This function will take an integer pointer,
 * then it will return the value of the integer.
 *
 * Note: this function will be useful to use hash set and hash map data structure.
 *
 * @param integer the integer pointer
 * @return it will return the passed integer pointer value
 */

int intHashFun(const void *integer) {
    return *(int *) integer;
}


/** This function will take two integers,
 * then it will return the sum of the integers using the ( + ) operation.
 *
 * @param a the first integer value
 * @param b the second integer value
 * @return it will return the sum of the passed integers
 */

int intSum(int a, int b) {
    return a + b;
}


/** This function will take an integer array,
 * then it will return the sum of the array values.
 *
 * @param arr the integer array pointer
 * @param length the length of the array
 * @return it will return the sum if the array values.
 */

int intArrSum(const int *arr, int length) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "array", "int array sum function");
        exit(NULL_POINTER);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "int array sum function");
        exit(INVALID_ARG);
#endif
    }

    int sum = 0;
    for (int i = 0; i < length; i++)
        sum += arr[i];

    return sum;

}


