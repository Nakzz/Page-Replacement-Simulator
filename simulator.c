#include "simulator.h"

void secondPass(SpecNode *specification, process *processHead)
{
    int numProcesses = getNumProcesses(processHead);
    Statistics *s = initStatistics(numProcesses);
    unsigned long maxSize = (specification->memSize) / (specification->pageSize);
    DiskQueue *queue = initDiskQueue();
    PageAlgoStruct *algoStruct = initPageAlgoStruct();

    unsigned long currentByte = 0;
    const int BASE = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fPtr = fopen(specification->traceFile, "r");
    if (!fPtr)
        errorReport("fopen() failed: ");

    process *toRun = processHead;

    while (toRun != NULL)
    {
        chunk *currentChunk = (chunk *)toRun->chunks->head->p;
        // printf(" \n processing chunk %lu %lu for pid %lu\n", currentChunk->start, currentChunk->end, toRun->PID);
        while (currentByte < currentChunk->end)
        {

            read = getline(&line, &len, fPtr);

            if (read == 1) // empty line
                continue;

            char s_pid[1024] = "";
            char s_addr[1024] = "";

            sscanf(line, "%s %s", s_pid, s_addr);

            unsigned long pid;
            unsigned long addr;

            pid = strtoul(s_pid, NULL, BASE);
            addr = strtoul(s_addr, NULL, BASE);

            if (pid != toRun->PID)
            {
                printf("pid: %li\n", pid);
                errorReport("   currentByte < toRun->chunks->end did not work");
            }

            if (toRun->root == NULL)
            {
                decProcessesRunning(s);
                incTPI(s);
                diskPushToTail(queue, toRun, getRunningTime(s));
                toRun->currOffset = ftell(fPtr) - read;
                // printf("    toRun-> PID{%lu}  toRun->currOffset:{%lu}\n", toRun->PID, toRun->currOffset);
                currentByte = currentChunk->end;
                currentChunk->reachedEnd = 0;
                if (queue->size == numProcesses)
                {
                    moveClock(s, queue->head->removeTime);
                }
            }
            else
            {
                void *root = toRun->root;
                treeNode *present = findNode(addr, &root);

                if (!present)
                {
                    decProcessesRunning(s);
                    incTPI(s);
                    diskPushToTail(queue, toRun, getRunningTime(s));
                    toRun->currOffset = ftell(fPtr) - read;
                    // printf("    toRun-> PID then toRun->currOffset: %lu %lu\n", toRun->PID, toRun->currOffset);
                    currentByte = currentChunk->end;
                    currentChunk->reachedEnd = 0;
                    if (queue->size == numProcesses)
                    {
                        moveClock(s, queue->head->removeTime);
                    }
                }
                else
                {
                    pageReplacementAlgorithm(0, algoStruct, addr, toRun);
                    incClock(s);
                    incTMR(s);
                    currentByte = ftell(fPtr);
                }
            }
        }
        int processHeadNULL = 0;
        if (currentChunk->reachedEnd)
        {
            chunk *toFree = popFromHead(toRun->chunks);
            freeChunk(toFree);
            listNode *chunkHead = toRun->chunks->head;
            if (chunkHead == NULL)
            {
                processHead = freeProcess(processHead, toRun);
                if (processHead == NULL)
                {
                    processHeadNULL = 1;
                }
                numProcesses--;
                if (queue->size == numProcesses)
                {
                    moveClock(s, queue->head->removeTime);
                }
            }
            else
            {
                chunk *tempChunk = (chunk *)chunkHead->p;
                toRun->currOffset = tempChunk->start;
            }
        }

        while (isTime(queue, getRunningTime(s)))
        {
            process *toReadMissed = diskPopFromHead(queue);
            incProcessesRunning(s);
            readMissed(fPtr, currentByte, toReadMissed, s, algoStruct, &maxSize, queue, &numProcesses, &processHead);
            if (processHead == NULL)
            {
                processHeadNULL = 1;
                break;
            }
        }

        if (processHeadNULL)
        {
            break;
        }
        // printf("currentByte: %lu\n", currentByte);
        toRun = findNextUnBlockedProcess(queue, processHead);
        if (!toRun)
        {
            break;
        }
        currentByte = toRun->currOffset;
        // printf("currentByte aftr set: %lu\n", currentByte);
        fseek(fPtr, currentByte, SEEK_SET);
    }
    printStats(s);
}

int getNumProcesses(process *head)
{
    process *current = head;
    int size = 0;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    return size;
}

void readMissed(FILE *fPtr, unsigned long currPos, process *p, Statistics *s, PageAlgoStruct *algoStruct, unsigned long *maxSize, DiskQueue *queue, int *numProcesses, process **processHead)
{
    // printf("setting file to byte: %lu\n", p->currOffset);
    fseek(fPtr, p->currOffset, SEEK_SET);

    listNode *currChunkList = p->chunks->head;
    chunk *currChunk = (chunk *)currChunkList->p;
    currChunk->reachedEnd = 1;
    int addedMem = 0;
    unsigned long currentByte = p->currOffset;

    while (currentByte < currPos)
    {
        while (currentByte < currChunk->end)
        {
            size_t len = 0;
            char *line = NULL;
            int read;
            read = getline(&line, &len, fPtr);
            char s_pid[1024] = "";
            char s_addr[1024] = "";

            sscanf(line, "%s %s", s_pid, s_addr);

            unsigned long pid;
            unsigned long addr;

            pid = strtoul(s_pid, NULL, 10);
            addr = strtoul(s_addr, NULL, 10);
            if (pid != p->PID)
            {
                printf("ftell() of readline beginning %li\n", (ftell(fPtr) - read));
                errorReport("something is wrong with the currOffset pointer as pid != p->PID");
            }

            if (p->root == NULL)
            {
                addNode(addr, &(p->root));
                p->treeSize++;
                incClock(s);
                incMemBeingUsed(s);
                incTMR(s);
                addedMem = 1;
                pageReplacementAlgorithm(0, algoStruct, addr, p);
                currentByte = ftell(fPtr);
            }
            else if (!addedMem)
            {
                if (getSize(s) == *(maxSize))
                {
                    process *procToRem = pageReplacementAlgorithm(1, algoStruct, addr, p);
                    void *rootToRem = procToRem->root;
                    deleteNode(procToRem->memToRemove, &rootToRem);
                    procToRem->treeSize--;
                    procToRem->memToRemove = 0;
                    addNode(addr, &(p->root));
                    p->treeSize++;
                }
                else
                {
                    addNode(addr, &(p->root));
                    p->treeSize++;
                    incMemBeingUsed(s);
                    pageReplacementAlgorithm(0, algoStruct, addr, p);
                }
                incClock(s);
                incTMR(s);
                addedMem = 1;
                currentByte = ftell(fPtr);
            }
            else
            {
                void *root = p->root;
                treeNode *present = findNode(addr, &root);

                if (!present)
                {
                    decProcessesRunning(s);
                    incTPI(s);
                    diskPushToTail(queue, p, getRunningTime(s));
                    p->currOffset = ftell(fPtr) - read;
                    // printf("p-> PID then p->currOffset: %lu %lu\n", p->PID, p->currOffset);
                    currChunk->reachedEnd = 0;
                    currentByte = currPos;
                    if (queue->size == *(numProcesses))
                    {
                        moveClock(s, queue->head->removeTime);
                    }
                }
                else
                {
                    pageReplacementAlgorithm(0, algoStruct, addr, p);
                    incClock(s);
                    incTMR(s);
                    currentByte = ftell(fPtr);
                }
            }
        }

        if (currChunk->reachedEnd)
        {
            void *toFree = popFromHead(p->chunks);
            free(toFree);
            currChunkList = p->chunks->head;

            if (currChunkList == NULL)
            {
                *(processHead) = freeProcess(*(processHead), p);
                currentByte = currPos;
            }
            else
            {
                currChunk = (chunk *)currChunkList->p;
                p->currOffset = currChunk->start;
                currentByte = currPos;
            }
        }
    }
}

process *findNextUnBlockedProcess(DiskQueue *q, process *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    process *nextProcess = NULL;
    chunk *nextByteChunk = NULL;
    process *current = head;
    while (current != NULL)
    {
        chunk *currentChunk = (chunk *)current->chunks->head->p;
        if (!(inDiskQueue(q, current->PID)))
        {
            if (nextProcess == NULL)
            {
                nextProcess = current;
                nextByteChunk = currentChunk;
            }
            else if (currentChunk->start < nextByteChunk->start)
            {
                nextProcess = current;
                nextByteChunk = currentChunk;
            }
        }
        current = current->next;
    }
    return nextProcess;
}