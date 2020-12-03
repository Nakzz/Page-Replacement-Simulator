#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "argparser.h"
#include "process.h"
#include "page_algorithm.h"
#include "diskqueue.h"
#include "statistics.h"
#include <string.h>

void secondPass(SpecNode *specification, process *processHead, char *traceFile);

int getNumProcesses(process *head);

void readMissed(FILE *fPtr, long int currPos, process *p, unsigned long int *clock, unsigned long *size, PageAlgoStruct *algoStruct, unsigned long *maxSize, DiskQueue *queue, int numProcesses);

process *findNextProcess(unsigned long endPos, process *head);

#endif