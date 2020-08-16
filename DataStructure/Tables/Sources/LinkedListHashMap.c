#include "../Headers/LinkedListHashMap.h"
#include "../../LinkedLists/Headers/DoublyLinkedList.h"
#include "../../../System/Utils.h"
#include "../../../Unit Test/CuTest/CuTest.h"

unsigned int LLHashMapFHashCal(int (*hashFun)(const void *), void *key, unsigned int length);


/** This function will take two entries pointers as it's parameters,
 * then it will return zero (0) if the key of the two entries are the same.
 *
 * Note: this function should only be called from the linked list hash map functions.
 *
 * This function will be useful to pass it to the linked list functions to know if the linked list contains the key or not.
 *
 * @param p1 the first entry address
 * @param p2 the second entry address
 * @return it will return zero if the two entries has the same key value, other wise it will return one
 */

int entriesCompFun(const void *p1, const void *p2) {
    Entry *entry1 = (Entry *) p1;
    Entry *entry2 = (Entry *) p2;

    return entry1->keyCompFun(entry1->key, entry2->key);

}


/** The freeing entry function.
 *
 * @param entry the entry address.
 */

void freeEntryFun(void *entry) {
    Entry *entryToFree = (Entry *) entry;
    entryToFree->freeItemFun(entryToFree->item);
    entryToFree->freeKeyFun(entryToFree->key);
    free(entryToFree);

}


/** This function will take the length of the hash map, the free function address, and the key comparator function as a parameters,
 * then it will allocate a new linked list hash map in the memory,
 * then the function will return the hash map address.
 *
 * @param mapLength the hash map length
 * @param freeFun the free function address, that will be called to free the hash map items
 * @param keyComp the key comparator function address, that will be called to compare two keys
 * @param hashFun the hashing function that will return a unique integer representing the hash map key
 * @return it will return the new hash map address
 */

LinkedListHashMap *linkedListHashMapInitialization(
        int mapLength,
        void (*freeKey)(void *),
        void (*freeItem)(void *),
        int (*keyComp)(const void *, const void *),
        int (*hashFun)(const void *)
) {

    if (mapLength <= 0) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash map initial length", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    } else if (freeKey == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free key function pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    } else if (freeItem == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "free item function pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    } else if (keyComp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key comparator function pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    } else if (keyComp == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "hash function pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif
    }

    LinkedListHashMap *hashMap = (LinkedListHashMap *) malloc(sizeof(LinkedListHashMap));
    if (hashMap == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "hash map", "linked list hash map data structure");
        exit(FAILED_ALLOCATION);
#endif

    }


    hashMap->length = mapLength;
    hashMap->arr = (DoublyLinkedList **) calloc(sizeof(DoublyLinkedList *), hashMap->length);
    if (hashMap->arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "hash map linked lists array",
                "linked list hash map data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    hashMap->count = 0;
    hashMap->freeKeyFun = freeKey;
    hashMap->freeItemFun = freeItem;
    hashMap->keyCompFun = keyComp;
    hashMap->hashFun = hashFun;

    return hashMap;

}


/** This function will take the hash map address, the key address, and the item address as a parameters,
 * then it will add the item and it's key in the hash map.
 *
 * @param map the hash map address
 * @param key the key address
 * @param item the new item address
 */

void lLHashMapInsert(LinkedListHashMap *map, void *key, void *item) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    } else if (key == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    } else if (item == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "item pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int index = LLHashMapFHashCal(map->hashFun, key, map->length);
    if (map->arr[index] == NULL)
        map->arr[index] = doublyLinkedListInitialization(freeEntryFun, entriesCompFun);

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    if (entry == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "new entry", "linked list hash map data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    entry->key = key;
    entry->item = item;
    entry->freeItemFun = map->freeItemFun;
    entry->freeKeyFun = map->freeKeyFun;
    entry->keyCompFun = map->keyCompFun;

    int entryIndex = doublyLinkedListGetIndex(map->arr[index], entry);
    if (entryIndex != -1)
        doublyLinkedListDeleteAtIndex(map->arr[index], entryIndex);

    doublyLinkedListAddLast(map->arr[index], entry);
    map->count++;

}


/** This function will take the hash map address, and the key address as a parameters,
 * then it will return one (1) if the key is in the tree,
 * other wise it will return zero (0).
 *
 * Note: this function will not free the key after it's done.
 *
 * @param map the hash map address
 * @param key the key address
 * @return it will return one if the key is in the hash map, other wise it will return zero
 */

int lLHashMapContains(LinkedListHashMap *map, void *key) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    } else if (key == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return -1;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int index = LLHashMapFHashCal(map->hashFun, key, map->length);
    if (map->arr[index] == NULL)
        return 0;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->keyCompFun = map->keyCompFun;

    int boolean = doublyLinkedListContains(map->arr[index], entry);
    free(entry);
    return boolean;

}


/** This function will take the hash map address, and the key address as a parameters,
 * then it will return the item with the provided key,
 * other wise if the function didn't find that key it will return NULL.
 *
 * Note: this function will not free the key after it's done.
 *
 * @param map the hash map address
 * @param key the key address
 * @return it will return the item with the provided key if found, other wise it will return NULL
 */

void *lLHashMapGet(LinkedListHashMap *map, void *key) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    } else if (key == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int index = LLHashMapFHashCal(map->hashFun, key, map->length);
    if (map->arr[index] == NULL)
        return 0;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->keyCompFun = map->keyCompFun;

    int itemIndex = doublyLinkedListGetIndex(map->arr[index], entry);
    free(entry);
    if (itemIndex == -1)
        return NULL;

    void *item = ((Entry *) doublyLinkedListGet(map->arr[index], itemIndex))->item;

    return item;

}


/** This function will take the hash map address, and the key address as a parameters,
 * then it will return the key pointer that equals to the provided key,
 * other wise if the function didn't find that key it will return NULL.
 *
 * Note: this function will not free the passed key after it's done.
 *
 * @param map the hash map address
 * @param key the key address
 * @return it will return the key that equals to the provided key if found, other wise it will return NULL
 */

void *lLHashMapGetKey(LinkedListHashMap *map, void *key) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    } else if (key == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int index = LLHashMapFHashCal(map->hashFun, key, map->length);
    if (map->arr[index] == NULL)
        return 0;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->keyCompFun = map->keyCompFun;

    int itemIndex = doublyLinkedListGetIndex(map->arr[index], entry);
    free(entry);
    if (itemIndex == -1)
        return NULL;

    void *returnKey = ((Entry *) doublyLinkedListGet(map->arr[index], itemIndex))->key;

    return returnKey;

}


/** This function will take the hash map address, and the key address as a parameters,
 * then it will remove the item with the provided key from the hash map.
 *
 * Note: this function will not free the key after it's done.
 *
 * @param map the hash map address
 * @param key the key address
 */

void lLHashMapDelete(LinkedListHashMap *map, void *key) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    } else if (key == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int index = LLHashMapFHashCal(map->hashFun, key, map->length);
    if (map->arr[index] == NULL)
        return;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->keyCompFun = map->keyCompFun;

    int itemIndex = doublyLinkedListGetIndex(map->arr[index], entry);
    free(entry);
    if (itemIndex == -1)
        return;

    doublyLinkedListDeleteAtIndex(map->arr[index], itemIndex);
    map->count--;

}


/** This function will take the hash map address, and the key address as a parameters,
 * then it will remove the item with the provided key from the hash map without freeing it.
 *
 * Note: the function will free the key without the item.
 *
 * Note: this function will not free the passed key after it's done.
 *
 * @param map the hash map address
 * @param key the key address
 * @return it will return the deleted item pointer if found, other wise it will return NULL
 */

void *lLHashMapDeleteWtoFr(LinkedListHashMap *map, void *key) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    } else if (key == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int index = LLHashMapFHashCal(map->hashFun, key, map->length);
    if (map->arr[index] == NULL)
        return NULL;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->keyCompFun = map->keyCompFun;

    int itemIndex = doublyLinkedListGetIndex(map->arr[index], entry);
    free(entry);
    if (itemIndex == -1)
        return NULL;

    Entry *deletedEntry = doublyLinkedListDeleteAtIndexWtoFr(map->arr[index], itemIndex);
    map->freeKeyFun(deletedEntry->key);
    void *returnItem = deletedEntry->item;
    free(deletedEntry);

    map->count--;

    return returnItem;
}


/** This function will take the hash map address, and the key address as a parameters,
 * then it will remove the item with the provided key from the hash map without freeing it.
 *
 * Note: the function will not free the key and the item.
 *
 * Note: this function will not free the passed key after it's done.
 *
 * @param map the hash map address
 * @param key the key address
 * @return it will return the deleted entry pointer if found, other wise it will return NULL
 */

Entry *lLHashMapDeleteWtoFrAll(LinkedListHashMap *map, void *key) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    } else if (key == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = INVALID_ARG;
        return NULL;
#else
        fprintf(stderr, INVALID_ARG_MESSAGE, "key pointer", "linked list hash map data structure");
        exit(INVALID_ARG);
#endif

    }

    unsigned int index = LLHashMapFHashCal(map->hashFun, key, map->length);
    if (map->arr[index] == NULL)
        return NULL;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->keyCompFun = map->keyCompFun;

    int itemIndex = doublyLinkedListGetIndex(map->arr[index], entry);
    free(entry);
    if (itemIndex == -1)
        return NULL;

    Entry *deletedEntry = doublyLinkedListDeleteAtIndexWtoFr(map->arr[index], itemIndex);

    map->count--;

    return deletedEntry;

}


/** This function will take the hash map address as a parameter,
 * then it will return a double void array that contains all the items in the hash map.
 *
 * @param map the hash map address
 * @return it will return a double void array that has a copy from the hash map items
 */

void **lLHashMapToArray(LinkedListHashMap *map) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    }

    void **arr = (void **) malloc(sizeof(void *) * map->count);
    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to array", "linked list hash map data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    int index = 0;

    for (int i = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            for (int j = 0; j < doublyLinkedListGetLength(map->arr[i]); j++) {
                Entry *entry = (Entry *) doublyLinkedListGet(map->arr[i], j);
                arr[index++] = entry->item;
            }

        }

    }

    return arr;

}


/** This function will take the hash map address as a parameter,
 * then it will return an Entry double pointer array that contains all the entries in the hash map.
 *
 * Note: the returned Entries will not be a really copy of the keys and items, it will reference to the same addresses.
 *
 * @param map the hash map address
 * @return it will return a double Entry pointer array that contains a copy of all the entries in the hash map
 */

Entry **lLHashMapToEntryArray(LinkedListHashMap *map) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return NULL;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    }

    Entry **arr = (Entry **) malloc(sizeof(Entry *) * map->count);
    if (arr == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = FAILED_ALLOCATION;
        return NULL;
#else
        fprintf(stderr, FAILED_ALLOCATION_MESSAGE, "to entries array", "linked list hash map data structure");
        exit(FAILED_ALLOCATION);
#endif

    }

    int index = 0;

    for (int i = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            for (int j = 0; j < doublyLinkedListGetLength(map->arr[i]); j++)
                arr[index++] = doublyLinkedListGet(map->arr[i], j);

        }

    }

    return arr;

}


/** This function will take the hash map address as a parameter,
 * then it will return the number of the items in the hash map.
 *
 * @param map the hash map address
 * @return it will return the number of items in the hash map
 */

int lLHashMapGetLength(LinkedListHashMap *map) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    }

    return map->count;
}


/** This function will take the hash map address as a parameter,
 * then it will return one (1) if the hash map is empty,
 * other wise it will return zero (0).
 *
 * @param map the hash map address
 * @return it will return one if the hash map is empty, other wise it will return zero
 */

int lLHashMapIsEmpty(LinkedListHashMap *map) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return -1;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    }

    return map->count == 0;

}


/** This function will take the hash map address as a parameter,
 * then it will clear and free all the hash map entries,
 * without destroying the hash map it self.
 *
 * @param map the hash map address
 */

void clearLLHashMap(LinkedListHashMap *map) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    }

    for (int i = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            destroyDoublyLinkedList(map->arr[i]);
            map->arr[i] = NULL;
        }

    }

    map->count = 0;

}


/** This function will take the hash map address as a parameter,
 * then it will destroy and free the hash map and all it's entries.
 *
 * @param map the hash map address
 */

void destroyLLHashMap(void *map) {
    if (map == NULL) {
#ifdef C_DATASTRUCTURES_ERRORSTESTSTRUCT_H
        ERROR_TEST->errorCode = NULL_POINTER;
        return;
#else
        fprintf(stderr, NULL_POINTER_MESSAGE, "hash map pointer", "linked list hash map data structure");
        exit(NULL_POINTER);
#endif

    }

    clearLLHashMap(map);

    free(((LinkedListHashMap *) map)->arr);
    free(map);

}


/** This function will take the hash function pointer, the key pointer, and the hash map array length as a parameters,
 * then it will return the first hash of this key.
 *
 * Note: this function should only be called from the hash map functions.
 * 
 * @param hashFun the hash function pointer
 * @param key the key pointer
 * @param length the length of the hash map array
 * @return it will return the first hashed key
 */

unsigned int LLHashMapFHashCal(int (*hashFun)(const void *), void *key, unsigned int length) {
    return (hashFun(key) % length);
}