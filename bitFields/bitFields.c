#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define STRBOOL(flag) (flag?"true":"false")

typedef struct mblock_info_s
{
    bool free:1;
    bool corrupt:1;
    bool supervisor:1;
    bool contig:1;
} __attribute__((packed)) mblock_info_t;

int main(void)
{
    struct mblock_info_s info;
    uint8_t* bits = (uint8_t*)&info;
    info.free = true;
    info.corrupt = false;
    info.supervisor = false;
    info.contig = false;
    
    printf("free=%s, corrupt=%s, supervisor=%s, contig=%s\n",
           STRBOOL(info.free),
           STRBOOL(info.corrupt),
           STRBOOL(info.supervisor), 
           STRBOOL(info.contig));
           
    printf("sizeof(info)=%d(0x%08x)\n", sizeof(info), sizeof(info));
    printf("bits=0x%02x\n", (unsigned int)*bits);
//    printf("  sizeof(avail)     =%d(0x%08x)\n", sizeof(info.avail),sizeof(info.avail));
//    printf("  sizeof(supervisor)=%d(0x%08x)\n", sizeof(info.supervisor),sizeof(info.supervisor));
//    printf("  sizeof(contig)    =%d(0x%08x)\n", sizeof(info.contig),sizeof(info.contig));
    return 0;
}
