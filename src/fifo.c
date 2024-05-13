#include <stdlib.h>
#include <stdio.h>

#include "../header/memory.h"
#include "../header/algo.h"
#include "../header/queue.h"

void FirstInFirstOut(Proc* arrivalQueue) {
    // Initialize virutal memory
    Memory* mem = malloc(sizeof(Memory));
    init(mem);

    // Initialize important variables
    int timeMsec = 0;
    int index = 0;
    int hits = 0;
    int misses = 0;
    int swaps = 0;

    // Initialize ready queue
    Queue* readyQueue = malloc(sizeof(Queue));
    readyQueue->head = NULL;

    // Initialize running queue
    Queue* runningQueue = malloc(sizeof(Queue));
    runningQueue->head = NULL;

    // Initialize finish queue
    Queue* finishQueue = malloc(sizeof(Queue));
    finishQueue->head = NULL;

    while (timeMsec <= SIM_TIME_SEC * SEC_TO_MSEC) {
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
            swaps++;
        }
        
        // Iterate through the queue of running processes
        if (runningQueue != NULL && runningQueue->head != NULL) {
            Job* temp = runningQueue->head;
            while (temp != NULL) {
                // printf("Name: %c\n", temp->proc->name);
                // Get new page reference
                temp->proc->pageRef = getNextRef(temp->proc->size, temp->proc->pageRef);
                // Find if new page referenced is in memory
                if (isInMem(temp->proc)) {
                    hits++;
                }
                else {
                    misses++;
                    // Try to get a free page
                    Page* freePg = getFreePage(temp->proc->inMem);
                    // If there is no more free page, evict the oldest page
                    if (freePg == NULL) {
                        // Find the oldest page in memory
                        int timeInMem = __INT_MAX__;
                        Page* pgEvict = NULL;
                        Page* pg = temp->proc->inMem;
                        while (pg != NULL) {
                            if (pg->assignTime < timeInMem) {
                                timeInMem = pg->assignTime;
                                pgEvict = pg;
                            }
                            pg = pg->next;
                        }
                        if (pgEvict != NULL) {
                            pgEvict->number = temp->proc->pageRef;
                            pgEvict->assignTime = timeMsec;
                        }
                    }
                    // If there is a free page, no need to evict
                    else {
                        freePg->number = temp->proc->pageRef;
                        freePg->assignTime = timeMsec;
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
                    temp = nextJob;
                    continue;
                }
                temp = temp->next;
            }
        }
        
        timeMsec += PERIOD_MSEC;
    }
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Swaps: %d\n\n", swaps);

    // Free dynamic memory
    free(mem);
    free(readyQueue);
    free(runningQueue);
    free(finishQueue);
}
