#include <stdlib.h>
#include <stdio.h>

#include "../header/proc.h"
#include "../header/queue.h"
#include "../header/memory.h"

const int NUM_SETS = 5;
const int NUM_PROC = 150;
const int SIM_TIME_SEC = 60;
const int SEC_TO_MSEC = 1000;

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
        }

        // Sort queue based on process arrival time
        qsort(arrivalQueue[i], NUM_PROC, sizeof(Proc), comparator);

        // for (int j = 0; j < NUM_PROC; ++j) {
        //     printf("Process name: %c, Arrival time: %d\n", arrivalQueue[i][j].name, arrivalQueue[i][j].arrivalTime);
        // }
    }
    
    // Run the algorithms

    // Free dynamic allocated memory
    for (int i = 0; i < NUM_SETS; ++i) {
        free(arrivalQueue[i]);
        arrivalQueue[i] = NULL;
    }

    return 0;
}