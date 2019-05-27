#ifdef __cplusplus
extern "C" {
#endif
typedef const char* cSprintf_t(const char*, ...);

typedef struct mblock_info_s
{
    bool free:1;
    bool corrupt:1;
    bool supervisor:1;
    bool contig:1;
} __attribute__((packed)) mblock_info_t;

typedef struct mblock_s mblock_t;
typedef struct mblock_s
{
    mblock_t* prev;
    size_t size;
    mblock_info_t info;
    char __attribute__((aligned(sizeof(void*)))) data[];
} mblock_t;

#ifdef __cplusplus
}
template<typename... Us>
cSprintf_t cSprintf;
#endif
