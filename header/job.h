#ifndef __JOB_H__
#define __JOB_H__

#include "proc.h"

typedef struct Job {
    Proc* proc;
    int runtime;    // in msec
    struct Job* next;
} Job;

#endif