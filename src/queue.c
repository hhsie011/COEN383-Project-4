#include <stdlib.h>

#include "../header/queue.h"


// Add job to back of the queue
void addJob(Queue* q, Job* j) {
    Job* temp = q->head;
    Job* prev = NULL;
    while (temp != NULL) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL) {
        q->head = j;
        return;
    }
    prev->next = j;
}

// Remove the specified job from the queue
void popJob(Queue* q, Job* j) {
    Job* temp = q->head;
    Job* prev = NULL;
    while (temp != NULL && temp != j) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    if (prev == NULL) {
        q->head = temp->next;
        return;
    }
    prev->next = temp->next;
}
