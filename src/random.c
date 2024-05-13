#include <stdlib.h>
#include <stdio.h>

#include "../header/memory.h"
#include "../header/algo.h"
#include "../header/queue.h"
#include "../header/output.h"

void Random(Proc* arrivalQueue, int shortSim, Stat* stat) {
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
                // printf("Name: %c\n", temp->proc->name);
                // Find if new page referenced is in memory
                if (isInMem(temp->proc)) {
                    hits++;
                }
                else {
                    misses++;
                    // Try to get a free page
                    Page* freePg = getFreePage(temp->proc->inMem);
                    // If there is no more free page, evict a randomly chosen page
                    if (freePg == NULL) {
                        // Pick a random page in memory
                        int random = rand() % MAX_NUM_PAGE;
                        Page* pgEvict = temp->proc->inMem;
                        for (int i = 0; i < random; ++i) {
                            pgEvict = pgEvict->next;
                        }
                        if (pgEvict != NULL) {
                            pgEvict->number = temp->proc->pageRef;
                        }
                    }
                    // If there is a free page, no need to evict
                    else {
                        freePg->number = temp->proc->pageRef;
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
    stat->hits = hits;
    stat->misses = misses;
    
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