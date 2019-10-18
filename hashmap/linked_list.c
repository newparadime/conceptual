#include "linked_list.h"
#include <stdlib.h>

static void listnode_destroy(listnode_t* p_node)
{
    if(p_node)
    {
        listnode_destroy(p_node->p_next);
        free(p_node);
    }
}

liststatus_t list_destroy(list_t* p_list)
{
    if(p_list)
    {
        listnode_destroy(p_list->p_head);
        return LIST_OK;
    }
    return LIST_ERROR;
}

liststatus_t list_append(list_t* p_list, hashelem_t elem)
{
    if(!p_list->p_head)
    {
        p_list->p_head = (listnode_t*)malloc(sizeof(listnode_t));
        p_list->p_tail = p_list->p_head;
    }
    else
    {
        if(p_list->p_tail)
        {
            p_list->p_tail->p_next = (listnode_t*)malloc(sizeof(listnode_t));
            p_list->p_tail = p_list->p_tail->p_next;
        }
    }
    
    if(p_list->p_tail)
    {
        p_list->p_tail->elem = elem;
        return LIST_OK;
    }
    
    return LIST_ERROR;
}

liststatus_t list_insert(list_t* p_list, listnode_t* p_node, hashelem_t elem)
{
    if(!p_node)
    {
        return list_append(p_list, elem);
    }
    else
    {
        listnode_t* p_new_node = (listnode_t*)malloc(sizeof(listnode_t));
        if(p_new_node)
        {
            p_new_node->elem = elem;
            p_new_node->p_next = p_node->p_next;
            p_node->p_next = p_new_node;
            if(p_list->p_tail == p_node)
            {
                p_list->p_tail = p_new_node;
            }
            return LIST_OK;
        }
    }
    return LIST_ERROR;
}

liststatus_t list_remove(list_t* p_list, listnode_t* p_node)
{
    if(!p_node || !p_list || !p_list->p_head)
    {
        return LIST_ERROR;
    }
    
    
    if(p_node == p_list->p_head)
    {
        p_list->p_head = p_node->p_next;
        if(!p_list->p_head)
        {
            p_list->p_tail = NULL;
        }
        free(p_node);
    }
    else
    {
        listnode_t* p_prev = p_list->p_head;
        while(p_prev && p_prev->p_next != p_node)
        {
            p_prev = p_prev->p_next;
        }
        
        if(p_prev->p_next == p_node)
        {
            p_prev->p_next = p_node->p_next;
            free(p_node);
            if(p_list->p_tail == p_node)
            {
                p_list->p_tail = p_prev;
            }
        }
        else
        {
            return LIST_ERROR;
        }
    }
    return LIST_OK;
}                

listnode_t* list_search(const list_t* p_list, void* key, hash_comp comp)
{
    listnode_t* p_node = p_list->p_head;
    while(p_node)
    {
        if(!comp(key, p_node->elem.key) && !comp(p_node->elem.key, key))
        {
            break;
        }
        p_node = p_node->p_next;
    }
    return p_node;
}
