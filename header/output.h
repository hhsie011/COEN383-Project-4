#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include "proc.h"
#include "memory.h"

void printStart(Proc*, int, Memory*);
void printCompletion(Proc*, int, Memory*);
void printReference(Proc*, int, int, int);

#endif