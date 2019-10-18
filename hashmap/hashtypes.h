#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct hashelem_s {
    void* key;
    void* data;
} hashelem_t;

typedef bool (*hash_comp)(void*,void*);
