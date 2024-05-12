#include <stdlib.h>

#include "../header/memory.h"


// Initialize physical memory with MEM_SIZE free pages
void init(Memory* mem) {
    mem->freePages = NULL;
    Page* last = NULL;
    for (int i = 0; i < MEM_SIZE; ++i) {
        Page* p = malloc(sizeof(Page));
        p->number = -1;
        p->lastUsed = -1;
        p->numRef = 0;
        p->next = NULL;
        if (mem->freePages == NULL) {
            mem->freePages = p;
            last = p;
            continue;
        }
        last->next = p;
        last = p;
    }
    mem->numFreePages = MEM_SIZE;
}
