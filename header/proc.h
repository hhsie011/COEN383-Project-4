#ifndef __PROC_H__
#define __PROC_H__

#include "page.h"

typedef struct Proc {
    char name;
    int size;
    int arrivalTime;
    int serviceTime;
    Page* inMem;    // keeps track of pages in memory
} Proc;

#endif
