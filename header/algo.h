#ifndef __ALGO_H__
#define __ALGO_H__

#include "proc.h"
#include "stat.h"

#define SIM_TIME_SEC 60
#define PERIOD_MSEC 100
#define SHORT_SIM 100

void FirstInFirstOut(Proc*, int, Stat*);
void LeastRecentlyUsed(Proc*, int, Stat*);
void LeastFrequentlyUsed(Proc*, int, Stat*);
void MostFrequentlyUsed(Proc*, int, Stat*);
void Random(Proc*, int, Stat*);

#endif