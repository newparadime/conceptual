#pragma once
#include <stdbool.h>
#include "linked_list.h"

typedef enum hashstatus_e {
    HASH_OK,
    HASH_ERROR,
    HASH_KEY_EXISTS
} hashstatus_t;

typedef struct hashtable_s {
    size_t key_size;
    size_t elem_size;
    size_t size;
    size_t num_buckets;
    hash_comp comp;
    list_t* table;
} hashtable_t;

hashtable_t hashtable_create(size_t key_size, size_t elem_size, hash_comp comp);

hashelem_t* hashtable_find(hashtable_t* p_hashtable, void* key);

hashstatus_t hashtable_emplace(hashtable_t* p_hashtable, hashelem_t elem);

hashstatus_t hashtable_remove(hashtable_t* p_hashtable, void* key);
