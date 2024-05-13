#include <stdlib.h>
#include <stdio.h>

#include "../header/memory.h"
#include "../header/algo.h"
#include "../header/queue.h"
#include "../header/output.h"

void LeastFrequentlyUsed(Proc* arrivalQueue, int shortSim, Stat* stat) {
    // Initialize virutal memory
    Memory* mem = malloc(sizeof(Memory));
    init(mem);

    // Initialize important variables
    int timeMsec = 0;
    int index = 0;
    int hits = 0;
    int misses = 0;
    int swaps = 0;
    int references = 0;

    // Initialize ready queue
    Queue* readyQueue = malloc(sizeof(Queue));
    readyQueue->head = NULL;

    // Initialize running queue
    Queue* runningQueue = malloc(sizeof(Queue));
    runningQueue->head = NULL;

    // Initialize finish queue
    Queue* finishQueue = malloc(sizeof(Queue));
    finishQueue->head = NULL;

    while (timeMsec <= SIM_TIME_SEC * SEC_TO_MSEC && (!shortSim || references < SHORT_SIM)) {
        // Processes only arrive at the start of a second
        if (timeMsec % SEC_TO_MSEC == 0) {
            // Check if any processes arrive at this second
            while (index < NUM_PROC && arrivalQueue[index].arrivalTime == timeMsec / SEC_TO_MSEC) {
                // Initilize a new job for the newly arrived process
                Job* newJob = malloc(sizeof(Job));
                newJob->proc = &arrivalQueue[index];
                newJob->next = NULL;
                // Insert new job into the ready queue
                addJob(readyQueue, newJob);
                index++;
            }
        }

        // Swap-in and run ready processes if there are enough available pages
        while (mem->numFreePages >= MAX_NUM_PAGE && readyQueue != NULL && readyQueue->head != NULL) {
            Job* newJob = readyQueue->head;
            removeJob(readyQueue, readyQueue->head);
            assignPages(mem, newJob->proc);
            addJob(runningQueue, newJob);
            if (!shortSim) {
                printStart(newJob->proc, timeMsec);
            }
            swaps++;
        }
        
        // Iterate through the queue of running processes
        if (runningQueue != NULL && runningQueue->head != NULL) {
            Job* temp = runningQueue->head;
            while (temp != NULL) {
                // Find if new page referenced is in memory
                Page* refPg;
                if ((refPg = isInMem(temp->proc))) {
                    hits++;
                    refPg->refCnt++;
                    if (shortSim) {
                        printReference(temp->proc, timeMsec, 1, -1);
                    }
                }
                else {
                    misses++;
                    // Try to get a free page
                    Page* freePg = getFreePage(temp->proc->inMem);
                    // If there is no more free page, evict the least recently used page
                    if (freePg == NULL) {
                        // Find the least frequently used page in memory
                        int leastRef = __INT_MAX__;
                        Page* pgEvict = NULL;
                        Page* pg = temp->proc->inMem;
                        while (pg != NULL) {
                            if (pg->refCnt < leastRef) {
                                leastRef = pg->refCnt;
                                pgEvict = pg;
                            }
                            pg = pg->next;
                        }
                        if (pgEvict != NULL) {
                            if (shortSim) {
                                printReference(temp->proc, timeMsec, 0, pgEvict->number);
                            }
                            pgEvict->number = temp->proc->pageRef;
                            pgEvict->refCnt = 1;
                        }
                    }
                    // If there is a free page, no need to evict
                    else {
                        freePg->number = temp->proc->pageRef;
                        freePg->refCnt++;
                    }
                }
                temp->runtime += PERIOD_MSEC;
                // Swap-out if process has finished
                if (temp->runtime >= temp->proc->serviceTime * SEC_TO_MSEC) {
                    // Return assigned pages to memory
                    returnPages(mem, temp->proc);
                    // Move process from runningQueue to finishQueue
                    Job* nextJob = temp->next;
                    addJob(finishQueue, temp);
                    removeJob(runningQueue, temp);
                    if (!shortSim) {
                        printCompletion(temp->proc, timeMsec);
                    }
                    temp = nextJob;
                    continue;
                }
                if (++references >= SHORT_SIM && shortSim) {
                    break;
                }
                // Get new page reference
                temp->proc->pageRef = getNextRef(temp->proc->size, temp->proc->pageRef);
                temp = temp->next;
            }
        }
        
        timeMsec += PERIOD_MSEC;
    }
    // printf("Hits: %d\n", hits);
    // printf("Misses: %d\n", misses);
    // printf("Swaps: %d\n\n", swaps);
    if (stat) {
        stat->hits = hits;
        stat->misses = misses;
        stat->swaps = swaps;
    }

    // Free dynamic memory
    free(mem);
    mem = NULL;
    free(readyQueue);
    readyQueue = NULL;
    free(runningQueue);
    runningQueue = NULL;
    free(finishQueue);
    finishQueue = NULL;
}