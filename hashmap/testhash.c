#include <stdio.h>
#include <stdint.h>
#include "hashword.h"

int main(void)
{
    uint32_t test[4] = {1234,2345,3456,4567};
    
    uint32_t hash = hashword(test, 4);
    
    printf("test's hash=0x%08x\n", hash);
    
    return 0;
}
