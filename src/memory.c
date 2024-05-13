#include <stdlib.h>

#include "../header/memory.h"


// Initialize physical memory with MEM_SIZE free pages
void init(Memory* mem) {
    mem->freePages = NULL;
    Page* last = NULL;
    for (int i = 0; i < MEM_SIZE; ++i) {
        mem->memMap[i] = '.';
        Page* p = malloc(sizeof(Page));
        p->number = -1;
        p->assignTime = -1;
        p->lastUsed = -1;
        p->refCnt = 0;
        p->next = NULL;
        p->address = i;
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

// Assign page to process
void assignPages(Memory* mem, Proc* proc) {
    if (mem == NULL) {
        return;
    }
    if (mem->freePages == NULL) {
        return;
    }
    if (mem->numFreePages < MAX_NUM_PAGE) {
        return;
    }
    proc->inMem = mem->freePages;
    Page* temp = mem->freePages;
    Page* prev = NULL;
    for (int i = 0; i < MAX_NUM_PAGE; ++i) {
        mem->memMap[temp->address] = proc->name;
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    mem->freePages = temp;
    mem->numFreePages -= MAX_NUM_PAGE;
}

// Return assigned pages to memory after a process finishes
void returnPages(Memory* mem, Proc* proc) {
    // Clear out contents of pages
    Page* temp = proc->inMem;
    Page* prev = NULL;
    while (temp != NULL) {
        temp->number = -1;
        temp->assignTime = -1;
        temp->lastUsed = -1;
        temp->refCnt = 0;
        mem->memMap[temp->address] = '.';
        prev = temp;
        temp = temp->next;
    }
    // Pointer manipulations to finish the return
    prev->next = mem->freePages;
    mem->freePages = proc->inMem;
    proc->inMem = NULL;
    mem->numFreePages += MAX_NUM_PAGE;
}
