#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "argparser.h"
#include "process.h"
#include "page_algorithm.h"
#include "diskqueue.h"
#include "statistics.h"
#include <string.h>

void secondPass(SpecNode *specification, process *processHead);

int getNumProcesses(process *head);

void readMissed(FILE *fPtr, unsigned long currPos, process *p, Statistics *s, PageAlgoStruct *algoStruct, unsigned long *maxSize, DiskQueue *queue, int *numProcesses, process **processHead);

process *findNextUnBlockedProcess(DiskQueue *q, process *head);

#endif