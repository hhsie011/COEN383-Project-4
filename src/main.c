#include <stdlib.h>
#include <stdio.h>

#include "../header/proc.h"
#include "../header/queue.h"
#include "../header/memory.h"
#include "../header/algo.h"
#include "../header/stat.h"

const int NUM_SETS = 5;

int comparator(const void* p1, const void* p2) {
    Proc*  proc1 = (Proc*)p1;
    Proc* proc2 = (Proc*)p2;
    return (proc1->arrivalTime - proc2->arrivalTime);
}

int main() {
    // Initialize arrival queue
    Proc* arrivalQueue[NUM_SETS];

    // Generate 150 new random processes
    for (int i = 0; i < NUM_SETS; ++i) {
        arrivalQueue[i] = malloc(NUM_PROC * sizeof(Proc));
        char id = 'A';
        for (int j = 0; j < NUM_PROC; ++j) {
            // Assign process name
            arrivalQueue[i][j].name = id;
            // Update process name
            if (id == 'Z' || id == 'z') {
                id = (id == 'Z')? 'a' : 'A'; 
            }
            else {
                id++;
            }
            // Assign process size (# of pages)
            int rand1 = rand() % 4;
            if (!rand1) {
                arrivalQueue[i][j].size = 5;
            }
            else if (rand1 == 1) {
                arrivalQueue[i][j].size = 11;
            }
            else if (rand1 == 2) {
                arrivalQueue[i][j].size = 17;
            }
            else {
                arrivalQueue[i][j].size = 31;
            }
            // Assign arrival time (in seconds)
            arrivalQueue[i][j].arrivalTime = rand() % SIM_TIME_SEC;
            // Assign process service duration
            arrivalQueue[i][j].serviceTime = (rand() % 5) + 1;
            // Assign first page process references (page-0 by default)
            arrivalQueue[i][j].pageRef = 0;
            // Assign process pages in memory
            arrivalQueue[i][j].inMem = NULL;
        }

        // Sort queue based on process arrival time
        qsort(arrivalQueue[i], NUM_PROC, sizeof(Proc), comparator);

        // for (int j = 0; j < NUM_PROC; ++j) {
        //     printf("Process name: %c, Arrival time: %d\n", arrivalQueue[i][j].name, arrivalQueue[i][j].arrivalTime);
        // }
    }

    // Simulate for one minute per run
    printf("Part 1: Simulate for 1 Minute Per Run\n");

    // Prepare struct to record stats
    Stat aggregate;
    aggregate.hits = 0;
    aggregate.misses = 0;

    // Run FIFO
    printf("=============================================================================\n");
    printf("First In, First Out (FIFO)\n\n");
    for (int i = 0; i < NUM_SETS; ++i) {
        printf("Run #%d\n", i + 1);
        Stat singleRun;
        FirstInFirstOut(arrivalQueue[i], 0, &singleRun);
        aggregate.hits += singleRun.hits;
        aggregate.misses += singleRun.misses;
        printf("\nHit/miss ratio: %f\n\n\n", ((double) singleRun.hits) / singleRun.misses);
    }

    printf("Hit/miss ratio (Average over 5 runs): %f\n\n\n", ((double) aggregate.hits) / aggregate.misses);
    aggregate.hits = 0;
    aggregate.misses = 0;

    // Run LRU
    printf("=============================================================================\n");
    printf("Least Recently Used (LRU)\n\n");
    for (int i = 0; i < NUM_SETS; ++i) {
        printf("Run #%d\n", i + 1);
        Stat singleRun;
        LeastRecentlyUsed(arrivalQueue[i], 0, &singleRun);
        aggregate.hits += singleRun.hits;
        aggregate.misses += singleRun.misses;
        printf("\nHit/miss ratio: %f\n\n\n", ((double) singleRun.hits) / singleRun.misses);
    }

    printf("Hit/miss ratio (Average over 5 runs): %f\n\n\n", ((double) aggregate.hits) / aggregate.misses);
    aggregate.hits = 0;
    aggregate.misses = 0;

    // Run LFU
    printf("=============================================================================\n");
    printf("Least Frequently Used (LFU)\n\n");
    for (int i = 0; i < NUM_SETS; ++i) {
        printf("Run #%d\n", i + 1);
        Stat singleRun;
        LeastFrequentlyUsed(arrivalQueue[i], 0, &singleRun);
        aggregate.hits += singleRun.hits;
        aggregate.misses += singleRun.misses;
        printf("\nHit/miss ratio: %f\n\n\n", ((double) singleRun.hits) / singleRun.misses);
    }

    printf("Hit/miss ratio (Average over 5 runs): %f\n\n\n", ((double) aggregate.hits) / aggregate.misses);
    aggregate.hits = 0;
    aggregate.misses = 0;

    // Run MFU
    printf("=============================================================================\n");
    printf("Most Frequently Used (MFU)\n\n");
    for (int i = 0; i < NUM_SETS; ++i) {
        printf("Run #%d\n", i + 1);
        Stat singleRun;
        MostFrequentlyUsed(arrivalQueue[i], 0, &singleRun);
        aggregate.hits += singleRun.hits;
        aggregate.misses += singleRun.misses;
        printf("\nHit/miss ratio: %f\n\n\n", ((double) singleRun.hits) / singleRun.misses);
    }

    printf("Hit/miss ratio (Average over 5 runs): %f\n\n\n", ((double) aggregate.hits) / aggregate.misses);
    aggregate.hits = 0;
    aggregate.misses = 0;

    // Run Random Pick
    printf("=============================================================================\n");
    printf("Random Pick\n\n");
    for (int i = 0; i < NUM_SETS; ++i) {
        printf("Run #%d\n", i + 1);
        Stat singleRun;
        Random(arrivalQueue[i], 0, &singleRun);
        aggregate.hits += singleRun.hits;
        aggregate.misses += singleRun.misses;
        printf("\nHit/miss ratio: %f\n\n\n", ((double) singleRun.hits) / singleRun.misses);
    }

    printf("Hit/miss ratio (Average over 5 runs): %f\n\n\n", ((double) aggregate.hits) / aggregate.misses);
    aggregate.hits = 0;
    aggregate.misses = 0;

    // Free dynamic allocated memory
    for (int i = 0; i < NUM_SETS; ++i) {
        free(arrivalQueue[i]);
        arrivalQueue[i] = NULL;
    }

    return 0;
}