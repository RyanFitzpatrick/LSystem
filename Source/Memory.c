#include "Memory.h"
#include <stdlib.h>
#include <stdio.h>

static LS_Memory * memory = NULL;

static LS_Memory * BuildMemory();
static void MemoryFail();

void * LS_BuildResource(unsigned int size)
{
    static int index = 0;
    void * ptr;

    /* Return if there's no memory to allocate */
    if(size == 0)
        return NULL;

    /* Initialize the global free list if it is NULL */
    if(memory == NULL)
        memory = BuildMemory();

    /* Allocate heap memory for the pointer */
    ptr = malloc(size);

    /* If there was a problem, terminate and free all memory in the free list */
    if(ptr == NULL)
        MemoryFail();

    /* Assign the allocated pointer to the free list */
    memory->block[index++] = ptr;

    /* If the current free list block is full, create a new one and append it to the unrolled free list */
    if(index == LS_MEMSIZE)
    {
        memory = BuildMemory();
        index = 0;
    }

    /* After adding the pointer to the free list, return it to be used */
    return ptr;
}

void * LS_ResizePointer(void * ptr, unsigned int size)
{
    void * temp;

    /* Free the pointer if the new size is 0 */
    if(size == 0)
    {
        free(ptr);
        return NULL;
    }

    /* Reallocate the heap memory for the pointer */
    temp = realloc(ptr, size);
    
    /* If there was a problem, terminate and free all memory in the free list */
    if(temp == NULL)
    {
        free(ptr);
        MemoryFail();
    }

    /* Return the allocated pointer */
    return temp;
}

void LS_ReleaseMemory()
{
    LS_Memory * temp;
    int i;

    /* Free all the memory blocks in the unrolled free list */
    while(memory != NULL)
    {
        /* Free all the pointers in each block of the unrolled free list */
        for(i = 0; i < LS_MEMSIZE; ++i)
            free(memory->block[i]);

        temp = memory;
        memory = temp->next;
        free(temp);
    }
}

static LS_Memory * BuildMemory()
{
    LS_Memory * mem = malloc(sizeof(LS_Memory));
    int i;

    /* If a new block could not be allocated then terminate and free all memory in the free list */
    if(mem == NULL)
        MemoryFail();

    /* Initalize all pointers in the block to NULL */
    for(i = 0; i < LS_MEMSIZE; ++i)
        mem->block[i] = NULL;

    /* Append this new block to the global free list */
    mem->next = memory;

    return mem;
}

static void MemoryFail()
{
    /* Print an error, free all memory in the free list, and terminate if memory could not be allocated */
    fputs("Could not successfully allocate any more memory\n", stderr);
    LS_ReleaseMemory();
    exit(-1);
}
