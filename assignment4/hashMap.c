/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: 
 * Date: 
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
    link = NULL;
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);

    HashLink* itr;
    HashLink* holder;
    int i = 0;

    // using while instead of for so that it stops when size = 0 even if capacity of array wasn't reached
    while (map->size > 0) {
        // set itr to array index and delete links while itr doesn't equal null
        itr = map->table[i];
        while (itr != NULL) {
            holder = itr->next;
            hashLinkDelete(itr);
            itr = holder;
            map->size--;    // decrement size for every deletion
        }
        i++;    // increment to next index
    }

    free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != NULL);

    HashLink* itr = map->table[HASH_FUNCTION(key) % map->capacity];
    while (itr != NULL) {
        if (itr->key == key) {
            return &itr->value;
        }
    }

    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given 
 * capacity (double of the old capacity). After allocating the new table, 
 * all of the links need to rehashed into it because the capacity has changed.
 * 
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 * 
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    assert(map != NULL);
    HashMap* newMap = hashMapNew(capacity);
    assert(newMap != NULL);

    int index = 0;
    HashLink* itr;
    HashLink* holder;
    while (index < map->capacity) {
        itr = map->table[index];
        while (itr != NULL) {
            holder = itr->next;
            hashMapPut(newMap, itr->key, itr->value);
            hashLinkDelete(itr);
            map->size--;
            itr = holder;
        }
        index++;
    }
    hashMapDelete(map);
    map = newMap;
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 * 
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    assert(map != NULL);
    HashLink* itr = map->table[HASH_FUNCTION(key) % map->capacity];
    int* valSearch = hashMapGet(map, key);

    if (valSearch == NULL) {
        if (hashMapTableLoad(map) >= 0.75) {
            resizeTable(map, map->capacity * 2);
            itr = map->table[HASH_FUNCTION(key) % map->capacity];
        }
        itr = hashLinkNew(key, value, itr);
        map->size++;
    } else {
        *valSearch = value;
    }
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != NULL);

    if (hashMapContainsKey(map, key)) {
        HashLink* itr = map->table[HASH_FUNCTION(key) % map->capacity];
        HashLink* holder;

        if (itr->key == key) {
            holder = itr->next;
            hashLinkDelete(itr);
            itr = holder;
        } else {
            while (itr->next->key != key) {
                itr = itr->next;
            }
            holder = itr->next->next;
            hashLinkDelete(itr->next);
            itr->next = holder;
        }
        map->size--;
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 * 
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 * 
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    // FIXME: implement
    assert(map != NULL);

    HashLink* itr = map->table[HASH_FUNCTION(key) % map->capacity];
    while (itr != NULL) {
        if (itr->key == key) {
            return 1;
        }
    }

    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);
    int empty = 0;

    for (int i =0; i < map->capacity; i++) {
        if (map->table[0] == NULL) {
            empty++;
        }
    }
    return empty;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);

    return (map->size / 1.0f) / map->capacity;
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    // FIXME: implement
    assert(map != NULL);

    HashLink* itr;
    int i = 0;

    while (i < map->capacity) {
        itr = map->table[i];
        while(itr != NULL) {
            printf("Key: %s     Value: %d\n", itr->key, itr->value);
            itr = itr->next;
        }
        i++;
    }
}
