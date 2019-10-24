#include <stdio.h>
#include <stdint.h>
#include "hashword.h"
#include "hashmap.h"

#include <stdbool.h>

bool comp(void* a, void* b)
{
    char* A = (char*)a;
    char* B = (char*)b;
    while(*A && *B && *A == *B)
    {
        A++;
        B++;
    }
    
    return *A < *B;
}

int main(void)
{
    uint32_t test[4] = {1234,2345,3456,4567};
    
    uint32_t hash = hashword((char*)test, 4);
    
    printf("test's hash=0x%08x\n", hash);
    
    char keys[5][5] = { "abcd", "bcde", "cdef", "defg", "efgh" };
    int data[5] = { 1, 2, 3, 4, 5 };
    
    hashtable_t hashtable = hashtable_create(5, 4, comp);
    
    for(int i = 0; i < 5; i++)
    {
        hashelem_t elem = {(void*)keys[i], (void*)&data[i] };
        if(hashtable_emplace(&hashtable, elem) != HASH_OK)
        {
            printf("HASH_ERROR for %s(%d)\n", keys[i], data[i]);
            return -1;
        }

    }
    int d = 6;
    hashelem_t elem = {(void*)"abcd", (void*)&d };
    if(hashtable_emplace(&hashtable, elem) == HASH_OK)
    {
        printf("emplace should've failed!\n");
    }
    else
    {
        printf("emplace failed as expected!\n");
    }
    
    hashelem_t* p_elem = hashtable_find(&hashtable, (void*)"abcd");
    p_elem->data = &d;
    
    for(int i = 0; i < 5; i++)
    {
        hashelem_t* p_elem = hashtable_find(&hashtable, (void*)keys[i]);
        if(!p_elem)
        {
            printf("match for key=%s not found!\n", keys[i]);
        }
        else
        {
            printf("match for key=%s found! %s(%d)\n", keys[i], (char*)p_elem->key, *(int*)p_elem->data);
        }
    }
    
    return 0;
}
