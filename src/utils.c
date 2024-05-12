#include <stdlib.h>

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
