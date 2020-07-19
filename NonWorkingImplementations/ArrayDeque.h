#ifndef C_DATASTRUCTURES_ARRAYDEQUE_H
#define C_DATASTRUCTURES_ARRAYDEQUE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @struct ArrayDeque
 *  @brief This structure implements a basic generic Deque.
 *  @var ArrayDeque::arr
 *  Member 'memory' is a pointer the deque's allocated array.
 *  @var ArrayDeque::front
 *  Member 'front' index of the front from the end index of the deque array.
  * @var ArrayDeque::rear
 *  Member 'rear' index of the rear from the start index of the deque array.
 *  @var ArrayDeque::size
 *  Member 'size' holds the current size of the allocated deque array,ie the number of allocated items.
 *  @var ArrayDeque:: 'freeFn'
 *  Member 'freeFn' holds pointer to the function responsible for freeing the elements stored in the Deque.
 */
typedef struct ArrayDeque {
    void **memory;
    uint32_t front;
    uint32_t rear;
    uint32_t size;
    void (*freeFn)(void *);
} ArrayDeque;

ArrayDeque *ArrayDequeInitialize(uint32_t initialSize, void(*freeFn)(void *));

void ArrayDequeInsertFront(ArrayDeque *arrayDeque, void *key);

void ArrayDequeInsertRear(ArrayDeque *arrayDeque, void *key);

void ArrayDequeDeleteFrontWithFree(ArrayDeque *arrayDeque);

void ArrayDequeDeleteFrontWithoutFree(ArrayDeque *arrayDeque);

void ArrayDequeDeleteRearWithFree(ArrayDeque *arrayDeque);

void ArrayDequeDeleteRearWithoutFree(ArrayDeque *arrayDeque);

uint16_t ArrayDequeIsEmpty(ArrayDeque *arrayDeque);

void *ArrayDequeGetFront(ArrayDeque *arrayDeque);

void *ArrayDequeGetRear(ArrayDeque *arrayDeque);

void ArrayDequePrint(ArrayDeque *arrayDeque, void (*printFn)(void *));

uint32_t ArrayDequeLength(ArrayDeque *ad);

void **ArrayDequeToArray(ArrayDeque *ad);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_ARRAYDEQUE_H
