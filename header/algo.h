#ifndef __ALGO_H__
#define __ALGO_H__

#include "proc.h"

#define SIM_TIME_SEC 60
#define SEC_TO_MSEC 1000
#define NUM_PROC 150
#define PERIOD_MSEC 100

void FirstInFirstOut(Proc*);
void LeastRecentlyUsed(Proc*);

#endif