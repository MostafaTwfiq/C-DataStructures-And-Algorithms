#ifndef C_DATASTRUCTURES_PAIR_H
#define C_DATASTRUCTURES_PAIR_H


#ifdef __cplusplus
extern "C" {
#endif

/** @struct Pair
*  @brief This structure implements a basic generic Pair.
*  @var Pair::fElem
*  Member 'fElem' is a pointer to the first element.
*  @var Pair::sElem
*  Member 'sElem' is a pointer to the second element.
*  @var Pair::fFreeFn
*  Member 'fFreeFn' is a pointer to the first free function, that will be called to free the first element.
*  @var Pair::sFreeFn
*  Member 'sFreeFn' is a pointer to the second free function, that will be called to free the second element.
*/

typedef struct Pair {

    void *fElem;
    void *sElem;

    void (*fFreeFn)(void *);

    void (*sFreeFn)(void *);

} Pair;


Pair *pairInitialization(void *fElem, void *sElem, void (*fFreeFn)(void *), void (*sFreeFn)(void *));

void *pairGetFElem(Pair *pair);

void *pairGetSElem(Pair *pair);

void pairSetFElem(Pair *pair, void *newElem);

void pairSetSElem(Pair *pair, void *newElem);

void *pairSetFElemWtoFr(Pair *pair, void *newElem);

void *pairSetSElemWtoFr(Pair *pair, void *newElem);

void pairSwapElements(Pair *pair);

void destroyPair(Pair *pair);

#ifdef __cplusplus
}
#endif

#endif //C_DATASTRUCTURES_PAIR_H
