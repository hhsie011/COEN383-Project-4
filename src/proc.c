#include <stdlib.h>

#include "../header/proc.h"

// Get next page reference using locality of reference
int getNextRef(int procSize, int currRef) {
    int randNum = rand() % 10;
    if (randNum < 7) {
        // Check if current reference is page-0
        if (!currRef) {
            return currRef + (rand() % 2);
        }
        // Check if current reference is page-<>
        if (currRef == procSize - 1) {
            return currRef - (rand() % 2); 
        }
        return currRef + ((rand() % 3) - 1);
    }
    // Randomly generate page number until it is at least 2 pages away from current page
    do {
        randNum = rand() % procSize;
    } while (abs(randNum - currRef) <= 1);
    return randNum;
}

// Find if page is in memory
// 1 - page is in memory
// 0 - page is not in memory
int isInMem(Proc* proc) {
    if (proc == NULL) {
        return 0;
    }
    Page* temp = proc->inMem;
    while (temp != NULL) {
        if (temp->number == proc->pageRef) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

// Get free page
// Returns pointer to page if there is a free page
// Returns NULL if there are no more free pages for processs
Page* getFreePage(Page* pg) {
    Page* temp = pg;
    while (temp != NULL) {
        if (temp->number == -1) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
