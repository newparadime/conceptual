#include "hashmap.h"
#include "hashword.h"

typedef bool (hash_comp*)(void*,void*);

typedef struct hashelem_s {
    void* key;
    void* data;
} hashelem_t;

typedef struct hashtable_s {
    size_t key_size;
    size_t elem_size;
    size_t size;
    size_t capacity;
    hash_comp comp;
    hashelem_t* table;
} hashtable_t;

typedef enum hashstatus_e {
    HASH_OK,
    HASH_ERROR,
} hashstatus_t;
    
hashtable_t hashtable_create(size_t key_size, size_t elem_size, hash_comp comp)
{
    hashtable_t hashtable;
    hashtable.key_size = key_size;
    hashtable.elem_size = elem_size;
    hashtable.capacity = 1;
    hashtable.size = 0;
    hashtable.comp = comp;
    hashtable.table = (hashelem_t*)malloc(hashtable.capacity * sizeof(hashelem_t));
    if (!hashtable.table)
    {
        hashtable.table_size = 0;
    }
    return hashtable;
}

static hashstatus_t hashtable_expand(hashtable_t hashtable)
{
    hashelem_t* table = (hashelem_t*)malloc(hashtable.capacity * 2 * sizeof(hashelem_t));
        
}

hashstatus_t hashtable_emplace(hashtable_t hashtable, hashelem_t elem)
{
    if(size == capacity)
    {
        
}

    
