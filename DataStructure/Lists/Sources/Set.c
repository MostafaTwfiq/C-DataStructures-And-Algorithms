#include "../Headers/Set.h"
#include "../Headers/Vector.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"





/** This function will allocate a new set then it will return its pointer.
 *
 * @param initialLength the initial length of the set
 * @param freeFn the free function pointer, that will be called to free the set items
 * @param cmp the comparison function pointer, that will be called to compare the set items
 * @return it will return the new allocated set pointer
 */

Set *setInitialization(int initialLength, void (*freeFn)(void *), int (*cmp)(const void *, const void *)) {

    Set *set = (Set *) malloc(sizeof(Set));
    if (set == NULL) {

    }

    set->vector = vectorInitialization(initialLength, freeFn, cmp);

    return set;

}




/** This function will add the passed item in the end of the set,
 * if the item doesn't exist in the set, other wise the function will free the passed item.
 *
 * @param set the set pointer
 * @param item the new item pointer
 */

void setAdd(Set *set, void *item) {

    int itemIndex = vectorGetIndex(set->vector, item);

    if (itemIndex == -1) {
        set->vector->freeItem(item);
        return;
    }

    vectorAdd(set->vector, item);


}





/** This function will add the passed item in the passed index,
 * if the item doesn't exist in the set, other wise the function will free the passed item,
 *
 * @param set the set pointer
 * @param item the new item pointer
 * @param index the index that the new item will be inserted in
 */

void setAddAtIndex(Set *set, void *item, int index) {

    int itemIndex = vectorGetIndex(set->vector, item);

    if (itemIndex == -1) {
        set->vector->freeItem(item);
        return;
    }

    vectorAddAtIndex(set->vector, item, index);

}





/** This function will return the index of the passed item if found,
 * other wise the function will return minus one (-1).
 *
 * @param set the set pointer
 * @param item the item pointer
 * @return it will return the item index if found, other wise it will return -1
 */

int setGetIndex(Set *set, void *item) {

    return vectorGetIndex(set->vector, item);

}




/** This function will return the item pointer in the passed index.
 *
 * @param set the set pointer
 * @param index the index of the item
 * @return it will return the item in the passed index
 */

void *setGet(Set *set, int index) {

    return vectorGet(set, index);

}




/** This function will check if the passed item exist in the set or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param set the set pointer
 * @param item the item pointer
 * @return it will return 1 if the item exist in the set, other wise it will return 0
 */

int setContains(Set *set, void *item) {

    return vectorContains(set->vector, item);

}




/** This function will delete and free the item in the passed index.
 *
 * @param set the set pointer
 * @param index the index of the item
 */

void setDelete(Set *set, int index) {

    vectorRemoveAtIndex(set->vector, index);

}




/** This function will delete the item in the passed index from the set without freeing it,
 * then the function will return the deleted item pointer.
 *
 * @param set the set pointer
 * @param index the item index
 * @return it will return the deleted item pointer
 */

void *setDeleteWtoFr(Set *set, int index) {

    return vectorRemoveAtIndexWtFr(set->vector, index);

}




/** This function will return the number of items in the set.
 *
 * @param set the set pointer
 * @return it will return the number of items in the set
 */

int setGetLength(Set *set) {
    return vectorGetLength(set->vector);
}




/** This function will check if the set is empty or not,
 * and if it was the function will return one (1),
 * other wise it will return zero (0).
 *
 * @param set the set pointer
 * @return it will return 1 if the set was empty, other wise it will return 0
 */

int setIsEmpty(Set *set) {
    return vectorIsEmpty(set->vector);
}




/** This function will return a double void pointer,
 * that contains the set items.
 *
 * @param set the set pointer
 * @return it will return a double void pointer, that contains the set items
 */

void **setToArray(Set *set) {


    return vectorToArray(set->vector);

}




/** This function will clear and free the set items,
 * without freeing the set itself.
 *
 * @param set the set pointer
 */

void clearSet(Set *set) {

    clearVector(set->vector);

}




/** This function will destroy and free the set with all it's items.
 *
 * @param set the set pointer
 */

void destroySet(Set *set) {

    destroyVector(set->vector);

    free(set);

}
