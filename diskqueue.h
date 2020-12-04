#ifndef DISKQUEUE_H
#define DISKQUEUE_H

#include "process.h"
#include "util.h"

typedef struct diskNode
{
    unsigned long removeTime;
    process *proc;
    struct diskNode *next;
} diskNode;

typedef struct DiskQueue
{
    diskNode *head;
    diskNode *tail;
    long size;
} DiskQueue;

DiskQueue *initDiskQueue();

diskNode *initDiskNode(process *proc);

void diskPushToTail(DiskQueue *q, process *proc, unsigned long int clock);

process *diskPopFromHead(DiskQueue *q);

int isTime(DiskQueue *q, unsigned long int clock);

int inDiskQueue(DiskQueue *q, unsigned long pid);

#endif