#include <stdlib.h>

#include "../header/queue.h"

// Add job to end of the queue
void addJob(Queue* queue, Job* job) {
    Job* temp = queue->head;
    Job* prev = NULL;
    while (temp != NULL) {
        prev = temp;
        temp = temp->next;
    }
    if (prev == NULL) {
        queue->head = job;
        return;
    }
    prev->next = job;
    
}

// Remove specified job from the queue
void removeJob(Queue* queue, Job* job) {
    if (queue == NULL) {
        return;
    }
    Job* temp = queue->head;
    Job* prev = NULL;
    while (temp != NULL && temp != job) {
        prev = temp;
        temp = temp->next;
    }
    Job* successor = temp->next;
    temp->next = NULL;
    if (prev == NULL) {
        queue->head = successor;
        return;
    }
    prev->next = successor;
}
