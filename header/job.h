#ifndef __JOB_H__
#define __JOB_H__

#include "proc.h"

typedef struct Job {
    Proc* proc;
    struct Job* next;
} Job;

#endif