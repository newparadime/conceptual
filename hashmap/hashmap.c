#include <stdbool.h>

typedef bool (hash_comp*)(void*,void*);

typedef struct hashtable_s {
    size_t elem_size;
    size_t table_size;
    hash_comp comp;
    char* table;
} hashtable_t;



hashtable_t hashtable_create(size_t elem_size, hash_comp comp)
{
    hashtable_t hashtable;
    hashtable.elem_size = elem_size;
    hashtable.table_size = 1;
    hashtable.comp = comp;
    hashtable.table = malloc(hashtable.table_size * hashtable.elem_size);
    if (!hashtable.table)
    {
        hashtable.table_size = 0;
    }
    return hashtable;
}


    
