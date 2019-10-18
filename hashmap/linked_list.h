#pragma once
#include "hashtypes.h"

typedef enum liststatus_e {
    LIST_OK,
    LIST_ERROR,
} liststatus_t;

struct listnode_s;

typedef struct listnode_s {
    struct listnode_s* p_next;
    hashelem_t elem;
} listnode_t;

typedef struct list_s {
    listnode_t* p_head;
    listnode_t* p_tail;
}list_t;

liststatus_t list_destroy(list_t* p_list);

liststatus_t list_append(list_t* p_list, hashelem_t elem);

liststatus_t list_insert(list_t* p_list, listnode_t* p_node, hashelem_t elem);

liststatus_t list_remove(list_t* p_list, listnode_t* p_node);             

listnode_t* list_search(const list_t* p_list, void* key, hash_comp comp);
    
    
            
