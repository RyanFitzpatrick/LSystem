#ifndef _LS_MEMORY_
#define _LS_MEMORY_

#define LS_MEMSIZE 1024

typedef struct LS_Memory
{
    void * block[LS_MEMSIZE];
    struct LS_Memory * next;
} LS_Memory;

void * LS_BuildResource(unsigned int);
void * LS_ResizePointer(void *, unsigned int);
void LS_ReleaseMemory();

#endif
