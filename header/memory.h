#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "page.h"

#define MEM_SIZE 100

typedef struct Memory
{
    Page* freePages;
    int numFreePages;
} Memory;

void init(Memory*);

#endif