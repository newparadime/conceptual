#ifndef __linked_list_h
#define __linked_list_h

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic error "-Wincompatible-pointer-types"
#endif
#define TYPE_COMP_ERROR(type1,type2) { type1 *__tmp; __tmp = (type2 *)NULL; }
#define CHECK_VAR_TYPE(var,type) { CHECK_VAR_TYPE(__typeof(var),type); }
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

#ifndef __LIST_DATA_TYPE
#error __LIST_DATA_TYPE not defined! \
       __LIST_DATA_TYPE should be defined in the file
       which includes this header, immediately before including it
#endif

typedef bool(*list_key_comp_t)(__LIST_KEY_TYPE a, __LIST_KEY_TYPE b);

#ifndef LIST_COMP_FUNC
#include <string.h>
#include <stdint.h>
//#include <stdio.h>

#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))

#define HASH(s)    ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))

#define XSTR(s) STR(s)
#define STR(s) #s

#define TYPE_COMP_COND(T1,T2) (HASH(XSTR(T1)) == HASH(XSTR(T2)))

//#if TYPE_COMP_COND(HASH(

#endif // LIST_COMP_FUNC




typedef enum liststatus_e {
    LIST_OK,
    LIST_ERROR,
} liststatus_t;

struct listnode_s;

typedef struct listnode_s {
    struct listnode_s* p_next;
    __LIST_DATA_TYPE data;
} listnode_t;

typedef struct list_s {
    listnode_t* p_head;
    listnode_t* p_tail;
}list_t;

liststatus_t list_destroy(list_t* p_list);

liststatus_t list_append(list_t* p_list, hashelem_t elem);

liststatus_t list_insert(list_t* p_list, listnode_t* p_node, hashelem_t elem);

liststatus_t list_remove(list_t* p_list, listnode_t* p_node);

listnode_t* list_search(const list_t* p_list, __LIST_KEY_TYPE key, list_key_comp_t comp);


#endif // __linked_list_h

#ifdef __linked_list_implementation
#undef __linked_list_implementation

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

listnode_t* list_search(const list_t* p_list, __LIST_KEY_TYPE key, list_key_comp_t comp)
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


#endif // __linked_list_implementation

