#ifndef C_DATASTRUCTURES_SET_H
#define C_DATASTRUCTURES_SET_H


#ifdef __cplusplus
extern "C" {
#endif

/** @struct Set
*  @brief This structure implements a basic generic Set.
*  @var Pair::vector
*  Member 'vector' is a pointer to the set vector (array).
*/

typedef struct Set {

    struct Vector *vector;

} Set;


Set *setInitialization(int initialLength, void (*freeFn)(void *), int (*cmp)(const void *, const void *));

void setAdd(Set *set, void *item);

void setAddAtIndex(Set *set, void *item, int index);

int setGetIndex(Set *set, void *item);

void *setGet(Set *set, int index);

int setContains(Set *set, void *item);

void setDelete(Set *set, int index);

void *setDeleteWtoFr(Set *set, int index);

int setGetLength(Set *set);

int setIsEmpty(Set *set);

void **setToArray(Set *set);

void clearSet(Set *set);

void destroySet(Set *set);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_SET_H
