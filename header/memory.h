#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "page.h"
#include "proc.h"

#define MEM_SIZE 100

typedef struct Memory
{
    Page* freePages;
    int numFreePages;
    char memMap[MEM_SIZE];
} Memory;

void init(Memory*);
void assignPages(Memory*, Proc*);
void returnPages(Memory*, Proc*);

#endif