#include "../Headers/SwapFunction.h"
#include <stdlib.h>
#include <string.h>


/** This function will take two pointers then it will swap between the two pointers.
 *
 * Note: the function will use memory copy to swap the items.
 *
 * @param first the first item pointer
 * @param second the second item pointer
 * @param elemSize the size of the items in bytes
 */

void swap(void *first, void *second, int elemSize) {

    void *temp = (void *) malloc(elemSize);
    memcpy(temp, first, elemSize);
    memcpy(first, second, elemSize);
    memcpy(second, temp, elemSize);

    free(temp);

}
