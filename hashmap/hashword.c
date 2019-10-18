#include <stddef.h>
#include "hashword.h"

#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))

#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c,4);  \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}

#define mix(a,b,c) \
{ \
  a -= c;  a ^= rot(c, 4);  c += b; \
  b -= a;  b ^= rot(a, 6);  a += c; \
  c -= b;  c ^= rot(b, 8);  b += a; \
  a -= c;  a ^= rot(c,16);  c += b; \
  b -= a;  b ^= rot(a,19);  a += c; \
  c -= b;  c ^= rot(b, 4);  b += a; \
}

uint32_t hashword(
const char *bytes,                   /* the key, an array of uint32_t values */
size_t        numBytes)               /* the length of the key, in uint32_ts */
{
    uint32_t a,b,c;
    static uint32_t initval = 0x0;
    size_t length = numBytes / sizeof(uint32_t);
    uint32_t* k = (uint32_t*)bytes;
    uint32_t last;
    /* Set up the internal state */
    a = b = c = 0xdeadbeef + (((uint32_t)length)<<2) + initval;
    
    if(numBytes % sizeof(uint32_t) == 0)
    {
        last = k[length-1];
        length -= 1;
    }
    else
    {
        last = 0x0;
        while(numBytes % sizeof(uint32_t))
        {
            last |= bytes[numBytes-1] << (((numBytes % sizeof(uint32_t))-1) * sizeof(char));
            numBytes -= 1;
        }
    }
    
    /*------------------------------------------------- handle most of the key */
    while (length > 2)
    {
        a += k[0];
        b += k[1];
        c += k[2];
        mix(a,b,c);
        length -= 3;
        k += 3;
    }

    /*------------------------------------------- handle the last 3 uint32_t's */
    switch(length)                     /* all the case statements fall through */
    { 
    case 2 : c+=k[1];
    case 1 : b+=k[0];
    case 0 : a+=last;
        final(a,b,c);
    }
    /*------------------------------------------------------ report the result */
    //initval = c;
    return c;
}
