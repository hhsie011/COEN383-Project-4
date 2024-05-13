#ifndef __PROC_H__
#define __PROC_H__

#include "page.h"

#define MAX_NUM_PAGE 4

typedef struct Proc {
    char name;
    int size;
    int arrivalTime;
    int serviceTime;
    int pageRef;
    Page* inMem;    // keeps track of pages in memory
} Proc;

int getNextRef(int, int);
int isInMem(Proc*);
Page* getFreePage(Page*);

#endif
