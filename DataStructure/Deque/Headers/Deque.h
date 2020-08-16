#ifndef C_DATASTRUCTURES_DEQUE_H
#define C_DATASTRUCTURES_DEQUE_H


#ifdef __cplusplus
extern "C" {
#endif


/** @struct Deque
*  @brief This structure implements a basic generic Deque.
*  @var Deque::arr
*  Member 'arr' is a pointer to the the Deque's memory.
*  @var Deque::length
*  Member 'length' holds the current max allocated size for the Deque.
*  @var Deque::front
*  Member 'front' holds the index to the front of the Deque Element.
*  @var Deque::rear
*  Member 'rear' holds the index to the last Deque Element.
*  @var Deque:: 'freeFun'
*  Member 'freeFun' holds pointer to the function responsible for freeing the elements stored in the Deque.
*/

typedef struct Deque {

    void **arr;
    int length;
    int rear;
    int front;

    void (*freeFun)(void *);
} Deque;


Deque *dequeInitialization(void (*freeFun)(void *));

void dequeInsertFront(Deque *deque, void *item);

void dequeInsertRear(Deque *deque, void *item);

void *dequeGetFront(Deque *deque);

void *dequeGetRear(Deque *deque);

void *dequePeekFront(Deque *deque);

void *dequePeekRear(Deque *deque);

void **dequeToArray(Deque *deque);

int dequeGetLength(Deque *deque);

int dequeIsEmpty(Deque *deque);

void clearDeque(Deque *deque);

void destroyDeque(void *deque);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_DEQUE_H
