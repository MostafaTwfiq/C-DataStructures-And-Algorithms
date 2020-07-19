#ifndef C_DATASTRUCTURES_DEQUE_H
#define C_DATASTRUCTURES_DEQUE_H


#ifdef __cplusplus
extern "C" {
#endif


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

int dequeGetLength(Deque  *deque);

int dequeIsEmpty(Deque *deque);

void clearDeque(Deque *deque);

void destroyDeque(Deque *deque);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_DEQUE_H
