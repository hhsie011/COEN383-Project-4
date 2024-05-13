#include <stdio.h>

#include "../header/output.h"

void printStart(Proc* proc, int timestamp) {
    printf("Timestamp: %d, Process name: %c, Enter/exit: %s, Size: %d, Service duration: %d\n", 
        timestamp / SEC_TO_MSEC, proc->name, "Enter", proc->size, proc->serviceTime);
}

void printCompletion(Proc* proc, int timestamp) {
    printf("Timestamp: %d, Process name: %c, Enter/exit: %s, Size: %d, Service duration: %d\n", 
        timestamp / SEC_TO_MSEC, proc->name, "Exit", proc->size, proc->serviceTime);
}

void printReference(Proc* proc, int timestamp, int pageInMem, int pgEvicted) {
    printf("Timestamp: %d, Process name: %c, Page referenced: %c, Page in memory (1=yes, 0=no): %d, Page evicted (-1=N/A): %d\n", 
        timestamp / SEC_TO_MSEC, proc->name, proc->pageRef, pageInMem, pgEvicted);
}