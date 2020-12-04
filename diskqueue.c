#include "diskqueue.h"

DiskQueue *initDiskQueue()
{
    DiskQueue *init = malloc(sizeof(DiskQueue));
    if (init == NULL)
    {
        errorReport("CANNOT MALLOC DISKQUEUE");
    }
    init->head = NULL;
    init->tail = NULL;
    init->size = 0;
    return init;
}

diskNode *initDiskNode(process *proc)
{
    diskNode *init = malloc(sizeof(diskNode));
    if (init == NULL)
    {
        errorReport("CANNOT MALLOC DISKNODE");
    }
    init->proc = proc;
    init->next = NULL;
    return init;
}

void diskPushToTail(DiskQueue *q, process *proc, unsigned long int clock)
{
    diskNode *toAdd = initDiskNode(proc);
    if (q->tail == NULL)
    {
        toAdd->removeTime = clock + 2000000;
        q->tail = toAdd;
        q->head = toAdd;
    }
    else
    {
        toAdd->removeTime = q->tail->removeTime + 2000000;
        q->tail->next = toAdd;
        q->tail = toAdd;
    }
    q->size++;
}

process *diskPopFromHead(DiskQueue *q)
{
    diskNode *toFree = NULL;
    process *toReturn = NULL;
    if (q->head != NULL)
    {
        toFree = q->head;
        toReturn = q->head->proc;
        if (q->head == q->tail)
        {
            q->tail = NULL;
            q->head = NULL;
        }
        else
        {
            q->head = q->head->next;
        }
        q->size--;
        free(toFree);
    }
    return toReturn;
}

int inDiskQueue(DiskQueue *q, unsigned long pid)
{
    diskNode *current = q->head;
    while (current != NULL)
    {
        if (current->proc->PID == pid)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int isTime(DiskQueue *q, unsigned long int clock)
{
    if (!q->head)
    {
        return 0;
    }
    if (q->head->removeTime == clock)
    {
        return 1;
    }
    return 0;
}
