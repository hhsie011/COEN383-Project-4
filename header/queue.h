#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "job.h"

typedef struct Queue {
    Job* head;
} Queue;

void addJob(Queue*, Job*);
void removeJob(Queue*, Job*);

#endif