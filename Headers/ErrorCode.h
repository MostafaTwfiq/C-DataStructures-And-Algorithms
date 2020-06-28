#ifndef C_DATASTRUCTURES_ERRORCODE_H
#define C_DATASTRUCTURES_ERRORCODE_H
typedef enum ERROR {
    FAILED_ALLOCATION     = -1,
    FAILED_REALLOCATION   = -2,
    FAILED_COPY           = -3,
    INVALID_ARG           = -4,
    NULL_POINTER          = -5,
    EMPTY_STACK           = -6
}ERROR;

#endif //C_DATASTRUCTURES_ERRORCODE_H
