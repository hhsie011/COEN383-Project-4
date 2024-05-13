#include <stdio.h>

#include "../header/output.h"

void printStart(Proc* proc, int timestamp, Memory* mem) {
    printf("Timestamp: %d, Process name: %c, Enter/exit: %s, Size: %d, Service duration: %d, Memory map: \"", 
        timestamp / SEC_TO_MSEC, proc->name, "Enter", proc->size, proc->serviceTime);
    for (int i = 0; i < MEM_SIZE; ++i) {
        printf("%c", mem->memMap[i]);
    }
    printf("\"\n");
}

void printCompletion(Proc* proc, int timestamp, Memory* mem) {
    printf("Timestamp: %d, Process name: %c, Enter/exit: %s, Size: %d, Service duration: %d, Memory map: \"", 
        timestamp / SEC_TO_MSEC, proc->name, "Exit", proc->size, proc->serviceTime);
    for (int i = 0; i < MEM_SIZE; ++i) {
        printf("%c", mem->memMap[i]);
    }
    printf("\"\n");
}

void printReference(Proc* proc, int timestamp, int pageInMem, int pgEvicted) {
    printf("Timestamp: %d, Process name: %c, Page referenced: %d, Page in memory (1=yes, 0=no): %d, Page evicted (-1=N/A): %d\n", 
        timestamp / SEC_TO_MSEC, proc->name, proc->pageRef, pageInMem, pgEvicted);
}