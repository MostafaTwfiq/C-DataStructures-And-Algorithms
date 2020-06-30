#include "../Headers/LinekdListHashMap.h"




unsigned int hashCal(unsigned int address, unsigned int sizeOfKey, unsigned int length);


int compFun(const void *p1, const void *p2);





/** This function will take the length of the hash map, and the size of type as a parameters,
    then it will allocate a new linked list hash map in the memory,
    then the function will return the hash map address.
 * @param mapLength
 * @param sizeOfType
 * @return
 */

LinkedListHashMap *linkedListHashMapInitialization(int mapLength, int sizeOfType) {
    if (mapLength <= 0)
        return NULL;

    LinkedListHashMap *hashMap = (LinkedListHashMap *) malloc(sizeof(LinkedListHashMap));

    hashMap->length = mapLength;
    hashMap->arr = (DoublyLinkedList **) calloc(sizeof(DoublyLinkedList *), hashMap->length);
    hashMap->count = 0;
    hashMap->sizeOfType = sizeOfType;

    return hashMap;

}





/** This function will take the hash map address, the key address, the item address, and the size of the key as a parameters,
    then it will add the item and it's key in the hash map.
 * @param map
 * @param key
 * @param item
 * @param sizeOfKey
 */

void lLHashMapInsert(LinkedListHashMap *map, void *key, void *item, int sizeOfKey) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    } else if (key == NULL) {
        fprintf(stderr, "Illegal argument, the passed key is null.");
        exit(-3);
    }

    unsigned int index = hashCal((unsigned int) key, sizeOfKey, map->length);
    if (map->arr[index] == NULL)
        map->arr[index] = doublyLinkedListInitialization(sizeof(Entry));

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->value = item;
    entry->sizeOfKey = sizeOfKey;

    int entryIndex = doublyLinkedListGetIndex(map->arr[index], entry, compFun);
    if (entryIndex != -1)
        doublyLinkedListDeleteAtIndex(map->arr[index], entryIndex);

    doublyLinkedListAddLast(map->arr[index], entry);
    map->count++;

}





/** This function will take the hash map address, the key address, and the size of the key as a parameters,
    then it will return one (1) if the key is in the tree,
    other wise it will return zero (0).
 * @param map
 * @param key
 * @param sizeOfKey
 * @return
 */

int lLHashMapContains(LinkedListHashMap *map, void *key, int sizeOfKey) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    } else if (key == NULL) {
        fprintf(stderr, "Illegal argument, the passed key is null.");
        exit(-3);
    }

    unsigned int index = hashCal((unsigned int) key, sizeOfKey, map->length);
    if (map->arr[index] == NULL)
        return 0;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->sizeOfKey = sizeOfKey;

    int boolean = doublyLinkedListContains(map->arr[index], entry, compFun);
    free(entry);
    return boolean;

}






/** This function will take the hash map address, the key address, and the size if the key as a parameters,
    then it will return the item with the provided key,
    other wise if the function didn't find that key it will return NULL.
 * @param map
 * @param key
 * @param sizeOfKey
 * @return
 */

void *lLHashMapGet(LinkedListHashMap *map, void *key, int sizeOfKey) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    } else if (key == NULL) {
        fprintf(stderr, "Illegal argument, the passed key is null.");
        exit(-3);
    }

    unsigned int index = hashCal((unsigned int) key, sizeOfKey, map->length);
    if (map->arr[index] == NULL)
        return 0;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->sizeOfKey = sizeOfKey;

    int itemIndex = doublyLinkedListGetIndex(map->arr[index], entry, compFun);
    free(entry);
    if (itemIndex == -1)
        return NULL;

    void *item = ((Entry *) doublyLinkedListGet(map->arr[index], itemIndex))->value;
    return item;

}





/** This function will take the hash map address, the key address, and the size of the key as a parameters,
    then it will remove the item with the provided key from the hash map.
 * @param map
 * @param key
 * @param sizeOfKey
 */

void lLHashMapDelete(LinkedListHashMap *map, void *key, int sizeOfKey) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    } else if (key == NULL) {
        fprintf(stderr, "Illegal argument, the passed key is null.");
        exit(-3);
    }

    unsigned int index = hashCal((unsigned int) key, sizeOfKey, map->length);
    if (map->arr[index] == NULL)
        return;

    Entry *entry = (Entry *) malloc(sizeof(Entry));
    entry->key = key;
    entry->sizeOfKey = sizeOfKey;

    int itemIndex = doublyLinkedListGetIndex(map->arr[index], entry, compFun);
    free(entry);
    if (itemIndex == -1)
        return;

    doublyLinkedListDeleteAtIndex(map->arr[index], itemIndex);
    map->count--;

}





/** This function will take the hash map address as a parameter,
    then it will return a double void array that contains a copy of all the items in the hash map.
 * @param map
 * @return
 */

void **lLHashMapToArray(LinkedListHashMap *map) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    }

    void **arr = (void **) malloc(sizeof(void *) * map->count);
    int index = 0;

    for (int i = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            for (int j = 0; j < doublyLinkedListGetLength(map->arr[i]); j++) {
                Entry *entry = doublyLinkedListGet(map->arr[i], j);
                arr[index] = (void *) malloc(map->sizeOfType);
                memcpy(arr[index++], entry->value, map->sizeOfType);
            }

        }

    }

    return arr;

}





/** This function will take the hash map address as a parameter,
    then it will return an Entry double pointer array that contains all the entries in the hash map.
 * @param map
 * @return
 */

Entry **lLHashMapToEntryArray(LinkedListHashMap *map) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    }

    Entry **arr = (Entry **) malloc(sizeof(Entry *) * map->count);
    int index = 0;

    for (int i = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            for (int j = 0; j < doublyLinkedListGetLength(map->arr[i]); j++) {
                Entry *entry = doublyLinkedListGet(map->arr[i], j);
                arr[index] = (Entry *) malloc(sizeof(Entry));
                memcpy(arr[index++], entry, sizeof(Entry));
            }

        }

    }

    return arr;

}





/** This function will take the hash map address as a parameter,
    then it will return the number of the items in the hash map.
 * @param map
 * @return
 */

int lLHashMapGetLength(LinkedListHashMap *map) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    }

    return map->count;
}





/** This function will take the hash map address as a parameter,
    then it will return one (1) if the hash map is empty,
    other wise it will return zero (0).
 * @param map
 * @return
 */

int lLHashMapIsEmpty(LinkedListHashMap *map) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    }

    return map->count == 0;
}





/** This function will take the hash map address as a parameter,
    then it will clear and free all the hash map entries,
    without destroying the hash map it self.
 * @param map
 */

void clearLLHashMap(LinkedListHashMap *map) {
    if (map == NULL) {
        fprintf(stderr, "Illegal argument, the hash map is null.");
        exit(-3);
    }

    for (int i = 0; i < map->length; i++) {
        if (map->arr[i] != NULL) {
            destroyDoublyLinkedList(map->arr[i]);
            map->arr[i] = NULL;
        }

    }

}






/** This function will take the hash map address as a parameter,
    then it will destroy and free the hash map and all it's entries.
 * @param map
 */

void destroyLLHashMap(LinkedListHashMap *map) {
    clearLLHashMap(map);

    free(map->arr);
    free(map);
}





/** This function will take the address of the key, the size of the key, the length of the hash map array as a parameters,
    then it will return the hashed index.
 * Note: this function should only be called from the linked hash map functions.
 * @param address
 * @param sizeOfKey
 * @param length
 * @return
 */

unsigned int hashCal(unsigned int address, unsigned int sizeOfKey, unsigned int length) {
    unsigned int *key = (int *) calloc(sizeof(int), 1);
    memcpy(key, (void *) address, sizeOfKey > 4 ? 4 : sizeOfKey);
    unsigned int hash = (*key % length);
    free(key);
    return hash;
}






/** This function will take two entries pointers as it's parameters,
    then it will return zero (0) if the key of the two entries are the same.
 * Note: this function should only be called from the linked list hash map functions.
 * This function will be useful to pass it to the linked list functions to know if the linked list contains the key or not.
 * @param p1
 * @param p2
 * @return
 */

int compFun(const void *p1, const void *p2) {
    if (((Entry *) p1)->sizeOfKey != ((Entry *) p2)->sizeOfKey)
        return 1;

    else if (memcmp(((Entry *) p1)->key, ((Entry *) p2)->key, ((Entry *) p1)->sizeOfKey) == 0)
        return 0;

    return 1;

}