#ifndef C_DATASTRUCTURES_ERRORCODE_H
#define C_DATASTRUCTURES_ERRORCODE_H


typedef enum ERROR {

    ///The errors codes generated by summing the word characters ASCII and multiply every character in it's index + 1
    ///The first four numbers is the sum of the word "DATA_STRUCTURE",
    ///and the rest of the words is the sum of the error enum. ex: INVALID_ARG is 4987.

    FAILED_ALLOCATION             = -833811484,
    FAILED_REALLOCATION           = -833814245,
    FAILED_COPY                   = -83385167,
    INVALID_ARG                   = -83384987,
    NULL_POINTER                  = -83386157,
    OUT_OF_RANGE                  = -83385991,
    EMPTY_DATA_STRUCTURE          = -833816740
}ERROR;



#define         FAILED_ALLOCATION_MESSAGE           "The %s allocation in %s failed."
#define         FAILED_REALLOCATION_MESSAGE         "The %s reallocation in %s failed."
#define         FAILED_COPY_MESSAGE                 "Copying failed in %s."
#define         INVALID_ARG_MESSAGE                 "The passed arg %s in %s is invalid."
#define         NULL_POINTER_MESSAGE                "The %s pointer in %s is NULL."
#define         OUT_OF_RANGE_MESSAGE                "The passed index is out of the %s range."
#define         EMPTY_DATA_STRUCTURE_MESSAGE        "The passed %s pointer is empty."


#endif //C_DATASTRUCTURES_ERRORCODE_H
