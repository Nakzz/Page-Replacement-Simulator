#include "simulator.h"

void secondPass(SpecNode *specification, process *processHead, char *traceFile)
{
    int numProcesses = getNumProcesses(processHead);
    Statistics *s = initStatistics(numProcesses);
    unsigned long size = 0;
    unsigned long maxSize = (specification->memSize) / (specification->pageSize);
    DiskQueue *queue = initDiskQueue();
    PageAlgoStruct *algoStruct = initPageAlgoStruct();

    long int currentByte = 0;
    const int BASE = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fPtr = fopen(traceFile, "r");
    if (!fPtr)
        errorReport("fopen() failed: ");

    process *toRun = findNextProcess(currentByte, processHead);

    while (toRun != NULL)
    {
        chunk *currentChunk = (chunk *)toRun->chunks->head->p;

        while (currentByte < currentChunk->end)
        {
            read = getline(&line, &len, fPtr);

            if (read == 1) // empty line
                continue;

            char s_pid[(int)ceil(log10(UCHAR_MAX)) + 1];
            char s_addr[(int)ceil(log10(UCHAR_MAX)) + 1];

            sscanf(line, "%s %s", s_pid, s_addr);

            unsigned long pid;
            unsigned long addr;

            pid = strtoul(s_pid, NULL, BASE);
            addr = strtoul(s_addr, NULL, BASE);

            if (pid != toRun->PID)
            {
                errorReport("currentByte < toRun->chunks->end did not work");
            }

            if (toRun->root == NULL)
            {
                diskPushToTail(queue, toRun, s->clockTick);
                toRun->currOffset = ftell(fPtr) - read;
                currentByte = currentChunk->end;
                currentChunk->reachedEnd = 0;
                if (queue->size == numProcesses)
                {
                    clock = queue->head->removeTime;
                }
            }
            else
            {
                treeNode *root = toRun->root;
                treeNode *present = findNode(addr, &root);

                if (!present)
                {
                    diskPushToTail(queue, toRun, clock);
                    toRun->currOffset = ftell(fPtr) - read;
                    currentByte = currentChunk->end;
                    currentChunk->reachedEnd = 0;
                    if (queue->size == numProcesses)
                    {
                        clock = queue->head->removeTime;
                    }
                }
                else
                {
                    pageReplacementAlgorithm(0, algoStruct, addr, toRun);
                    clock++;
                    //stats stuff
                    currentByte = ftell(fPtr);
                }
            }
        }
        if (currentChunk->reachedEnd)
        {
            listNode *toFree = popFromHead(toRun->chunks);
            free(toFree->p);
            free(toFree);
            listNode *chunkHead = toRun->chunks->head;
            if (chunkHead == NULL)
            {
                //free process somehow
            }
            else
            {
                chunk *tempChunk = (chunk *)chunkHead->p;
                toRun->currOffset = tempChunk->start;
            }
        }
        while (isTime(queue, clock))
        {
            process *toReadMissed = diskPopFromHead(queue);
            readMissed(fPtr, currentByte, toReadMissed->root, &clock, &size, algoStruct, &maxSize, queue, numProcesses);
        }
        toRun = findNextProcess(currentByte, processHead);
        currentByte = toRun->currOffset;
        // need to check for chunk head but actually set the ftell to offset instead, also if reachedEnd for chunk you need to pop it off the chunks, also check all blocked switch to that if possible
    }
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

void readMissed(FILE *fPtr, long int currPos, process *p, unsigned long int *clock, unsigned long *size, PageAlgoStruct *algoStruct, unsigned long *maxSize, DiskQueue *queue, int numProcesses)
{
    fseek(fPtr, p->currOffset, SEEK_SET);
    printf("setting file to byte: %lu\n", p->currOffset);

    listNode *currChunkList = p->chunks->head;
    chunk *currChunk = (chunk *)currChunkList->p;
    currChunk->reachedEnd = 1;
    int addedMem = 0;
    int first = 1;
    long int currentByte = p->currOffset;

    while (currentByte < currPos)
    {
        while (currentByte < currChunk->end)
        {
            size_t len = 0;
            char *line = NULL;
            int read;
            read = getline(&line, &len, fPtr);
            char s_pid[(int)ceil(log10(UCHAR_MAX)) + 1];
            char s_addr[(int)ceil(log10(UCHAR_MAX)) + 1];

            sscanf(line, "%s %s", s_pid, s_addr);

            unsigned long pid;
            unsigned long addr;

            pid = strtoul(s_pid, NULL, 10);
            addr = strtoul(s_addr, NULL, 10);
            if (pid != p->PID)
            {
                errorReport("something is wrong with the currOffset pointer as pid != p->PID");
            }

            if (p->root == NULL)
            {
                p->root = addNode(addr, &(p->root));
                *(clock)++;
                //stats stuff
                *(size)++;
                addedMem = 1;
                pageReplacementAlgorithm(0, algoStruct, addr, p);
                currentByte = ftell(fPtr);
            }
            else if (!addedMem)
            {
                if (*(size) == *(maxSize))
                {
                    process *procToRem = pageReplacementAlgorithm(1, algoStruct, addr, p);
                    treeNode *rootToRem = procToRem->root;
                    deleteNode(procToRem->memToRemove, &rootToRem);
                    procToRem->memToRemove = 0;
                    addNode(addr, &(p->root));
                }
                else
                {
                    addNode(addr, &(p->root));
                    *(size)++;
                    pageReplacementAlgorithm(0, algoStruct, addr, p);
                }
                *(clock)++;
                //stats stuff
                addedMem = 1;
                currentByte = ftell(fPtr);
            }
            else
            {
                treeNode *present = findNode(addr, &(p->root));

                if (!present)
                {
                    diskPushToTail(queue, p, clock);
                    p->currOffset = ftell(fPtr) - read;
                    currChunk->reachedEnd = 0;
                    currentByte = currPos;
                    if (queue->size == numProcesses)
                    {
                        *(clock) = queue->head->removeTime;
                    }
                }
                else
                {
                    pageReplacementAlgorithm(0, algoStruct, addr, p);
                    *(clock)++;
                    //stats stuff
                    currentByte = ftell(fPtr);
                }
            }
        }
        if (currChunk->reachedEnd)
        {
            listNode *toFree = popFromHead(p->chunks);
            free(toFree->p);
            free(toFree);
            currChunkList = p->chunks->head;

            if (currChunkList == NULL)
            {
                //free process somehow
                currentByte = currPos;
            }
            else
            {
                currChunk = (chunk *)currChunkList->p;
                currentByte = currChunk->start;
                p->currOffset = currentByte;
            }
        }
    }
}

process *findNextProcess(unsigned long endPos, process *head)
{
    process *current = head;
    while (current != NULL)
    {
        chunk *currentChunkHead = (chunk *)current->chunks->head->p;
        if (currentChunkHead->start == endPos)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}