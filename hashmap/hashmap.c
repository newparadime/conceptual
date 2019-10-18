#include "hashmap.h"
#include "hashword.h"
#include "linked_list.h"
#include <stdlib.h>

hashtable_t hashtable_create(size_t key_size, size_t elem_size, hash_comp comp)
{
    hashtable_t hashtable;
    hashtable.key_size = key_size;
    hashtable.elem_size = elem_size;
    hashtable.num_buckets = 1;
    hashtable.size = 0;
    hashtable.comp = comp;
    hashtable.table = (list_t*)malloc(hashtable.num_buckets * sizeof(list_t));
    if (!hashtable.table)
    {
        hashtable.size = 0;
    }
    return hashtable;
}

static hashstatus_t hashtable_expand(hashtable_t* p_hashtable)
{
    list_t* table = p_hashtable->table;
    p_hashtable->num_buckets *= 2;
    p_hashtable->table = (list_t*)malloc(p_hashtable->num_buckets * sizeof(list_t));
    if(!p_hashtable->table)
    {
        return HASH_ERROR;
    }
    
    for(int i = 0; i < p_hashtable->num_buckets/2; i++)
    {
        listnode_t* p_node = table[i].p_head;
        while(p_node)
        {
            if(hashtable_emplace(p_hashtable, p_node->elem) != HASH_OK)
            {
                return HASH_ERROR;
            }
            p_node = p_node->p_next;
        }
    }
    return HASH_OK;
}

static list_t* hashtable_find_list(hashtable_t* p_hashtable, void* key)
{
    const uint32_t hash = hashword(key, p_hashtable->key_size);
    
    return &p_hashtable->table[hash%p_hashtable->num_buckets];
}
    
    

static listnode_t* hashtable_find_listnode(hashtable_t* p_hashtable, void* key)
{
    const list_t* p_list = hashtable_find_list(p_hashtable, key);
    
    return list_search(p_list, key, p_hashtable->comp);
}

hashelem_t* hashtable_find(hashtable_t* p_hashtable, void* key)
{
    listnode_t* p_node = hashtable_find_listnode(p_hashtable, key);
    if(p_node)
    {
        return &p_node->elem;
    }
    return NULL;
}
    

hashstatus_t hashtable_emplace(hashtable_t* p_hashtable, hashelem_t elem)
{
    if(p_hashtable->size == p_hashtable->num_buckets)
    {
        if(hashtable_expand(p_hashtable) != HASH_OK)
        {
            return HASH_ERROR;
        }
    }
    
    if(hashtable_find(p_hashtable, elem.key))
    {
        return HASH_KEY_EXISTS;
    }
    else
    {
        const uint32_t hash = hashword(elem.key, p_hashtable->key_size);
        list_t* p_list = &p_hashtable->table[hash%p_hashtable->num_buckets];
        if(list_append(p_list, elem) != LIST_OK)
        {
            return HASH_ERROR;
        }
    }
    
    p_hashtable->size += 1;
    
    return HASH_OK;
}

hashstatus_t hashtable_remove(hashtable_t* p_hashtable, void* key)
{
    list_t* p_list = hashtable_find_list(p_hashtable, key);
    
    listnode_t* p_node = hashtable_find_listnode(p_hashtable, key);
    
    if(list_remove(p_list, p_node) != LIST_OK)
    {
        return HASH_ERROR;
    }
    
    p_hashtable->size -= 1;
    
    return HASH_OK;
}
