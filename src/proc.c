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
        // Check if current reference is page-<process size - 1>
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
// pointer to page - page is in memory
// NULL - page is not in memory
Page* isInMem(Proc* proc) {
    if (proc == NULL) {
        return NULL;
    }
    Page* temp = proc->inMem;
    while (temp != NULL) {
        if (temp->number == proc->pageRef) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
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
