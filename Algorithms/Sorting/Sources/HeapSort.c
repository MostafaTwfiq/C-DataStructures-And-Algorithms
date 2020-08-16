#include "../Headers/HeapSort.h"
#include "../Headers/SwapFunction.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"



// Formulas:
// child 1: parentIndex * 2 + 1
// child 2: parentIndex * 2 + 2
// parentIndex = (childIndex - 1) / 2

// Ex array:
// 5, 3, 4, 10, 6

// Step 1: build a valid heap
// **we don't need to allocate a new array we can use the original array to convert it to a valid heap**

// add 5
// 5

// add 3
// 5, 3

// add 4
// 5, 3, 4

// add 10
// 5, 3, 4, 10
// 10, 5, 4, 3

// add 6
// 10, 5, 4, 3, 6
// 10, 6, 4, 3, 5

// The heap in 2D:
//          10
//       6      4
//     3   5


// Step 2: delete the tree root and balance the heap the number of times the length of the array.

// 10, 6, 4, 3, 5

// 5, 6, 4, 3, 10
// 6, 5, 4, 3, 10

// 3, 5, 4, 6, 10
// 5, 3, 4, 6, 10

// 4, 3, 5, 6, 10

// 3, 4, 5, 6, 10







/** This function will take a child index,
 * then it will return the parent index.
 *
 * @param childIndex the child index
 * @return it will return the parent index
 */

int getParentIndex(int childIndex) {
    return (childIndex - 1) / 2;
}


/** This function will take a parent index,
 * then it will return the first child index.
 *
 * @param parentIndex the parent index
 * @return it will return the first child index
 */

int getFirstChildIndex(int parentIndex) {
    return parentIndex * 2 + 1;
}


/** This function will take a parent index,
 * then it will return the second child index.
 *
 * @param parentIndex the parent index
 * @return the second child index
 */

int getSecondChildIndex(int parentIndex) {
    return parentIndex * 2 + 2;
}


/** This function will swap up the element with the given index,
 * until it's in the right place.
 *
 * @param arr the array pointer
 * @param index the index of the element
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function, that will be called to compare the elements
 */

void heapUp(char *arr, int index, int elemSize, int (*cmp)(const void *, const void *)) {
    if (index <= 0)
        return;

    int parentIndex = getParentIndex(index);

    if (cmp(arr + index * elemSize, arr + parentIndex * elemSize) > 0) {
        swap(arr + index * elemSize, arr + parentIndex * elemSize, elemSize);
        heapUp(arr, parentIndex, elemSize, cmp);
    }

}


/** This function will swap down the element with the given index,
 * until it's in the right place.
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param index the index of the element
 * @param elemSize the array elements size in bytes
 * @param cmp the the comparator function, that will be called to compare the elements
 */

void heapDown(char *arr, int length, int index, int elemSize, int (*cmp)(const void *, const void *)) {
    int firstChildIndex = getFirstChildIndex(index);
    int secondChildIndex = getSecondChildIndex(index);


    // if the current element in smaller than his children.
    if (firstChildIndex < length
        && secondChildIndex < length
        && cmp(arr + index * elemSize, arr + firstChildIndex * elemSize) < 0
        && cmp(arr + index * elemSize, arr + secondChildIndex * elemSize) < 0) {

        // the biggest child index.
        int biggestChildIndex = cmp(arr + firstChildIndex * elemSize, arr + secondChildIndex * elemSize) > 0
                                ? firstChildIndex
                                : secondChildIndex;

        swap(arr + index * elemSize, arr + biggestChildIndex * elemSize, elemSize);
        heapDown(arr, length, biggestChildIndex, elemSize, cmp);

    }

        // if the current element is only less that his first child.
    else if (firstChildIndex < length && cmp(arr + index * elemSize, arr + firstChildIndex * elemSize) < 0) {

        swap(arr + index * elemSize, arr + firstChildIndex * elemSize, elemSize);
        heapDown(arr, length, firstChildIndex, elemSize, cmp);

    }

        // if the current element is only less that his second child.
    else if (secondChildIndex < length && cmp(arr + index * elemSize, arr + secondChildIndex * elemSize) < 0) {

        swap(arr + index * elemSize, arr + secondChildIndex * elemSize, elemSize);
        heapDown(arr, length, secondChildIndex, elemSize, cmp);

    }


}


/** This function will take an array then it sort it with the heap sort algorithm.
 *
 * Time Complexity: worst: O( n log(n) ) , best: O ( n log(n) ).
 *
 * Space Complexity: O ( 1 ).
 *
 * @param arr the array pointer
 * @param length the length of the array
 * @param elemSize the size of the array elements in bytes
 * @param cmp the comparator function pointer
 */

void heapSort(void *arr, int length, int elemSize, int (*cmp)(const void *, const void *)) {

    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "passed array", "heap sort");
        exit(NULL_POINTER);
#endif
    } else if (cmp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "comparator function pointer", "heap sort");
        exit(INVALID_ARG);
#endif
    } else if (length < 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "array length", "heap sort");
        exit(INVALID_ARG);
#endif
    } else if (elemSize <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "element size", "heap sort");
        exit(INVALID_ARG);
#endif
    }


    char *oneBytePointer = (char *) arr;

    // to build a valid heap.
    for (int i = 0; i < length; i++)
        heapUp(oneBytePointer, i, elemSize, cmp);

    // to sort the heap (delete the tree root and balance the heap the number of times the length of the array).
    while (length-- > 0) {
        swap(oneBytePointer, oneBytePointer + length * elemSize, elemSize);
        heapDown(oneBytePointer, length, 0, elemSize, cmp);
    }

}