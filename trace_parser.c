
///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	trace_parser.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "trace_parser.h"

process *generateProcessList(char *traceFile)
{

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    process *head = NULL;
    process *prev = NULL;
    int lineNumber = 0;

    FILE *fPtr = fopen(traceFile, "r");
    if (!fPtr)
        errorReport("fopen() failed: ");

    while ((read = getline(&line, &len, fPtr)) != -1) //use sentinel value to signal EOF
    {
        lineNumber++;
        if (read == 1) // empty line
            continue;

        //REVIEW: check for buffer overflow and underflow using debugger and long unsigned input+1
        // See if it resets every iterations or needs to be manually cleared after every iteration
        char s_pid[(int)ceil(log10(UCHAR_MAX)) + 1];
        char s_addr[(int)ceil(log10(UCHAR_MAX)) + 1];

        unsigned long pid;
        unsigned long addr;
        const int BASE = 0;
        unsigned long offset = 0;
        offset = ftell(fPtr) - read;

        sscanf(line, "%s %s", s_pid, s_addr);

        if (isAllPositiveDigit(s_pid) && isAllPositiveDigit(s_addr))
        // if (isAllDigit(s_pid) && isAllDigit(s_addr))

        {
            char *stopPID, *stopAddr;

            pid = strtoul(s_pid, &stopPID, BASE);
            addr = strtoul(s_addr, &stopAddr, BASE);

            // printf(" string: %s %s      long: %ld %ld BASE:(%d) ", s_pid, s_addr, pid, addr, BASE);
            // printf("   strtoul = %ld (base %d)\n", pid, BASE);
            // printf("   strtoul = %ld (base %d)\n", addr, BASE);
        }
        else
        {
            if (!isAllDigit(s_pid) || !isAllDigit(s_addr))
                errorReportDetail("Error encountered parsing Tracefile: Must be numbers only", lineNumber, line);

            if (!isAllPositiveDigit(s_pid) || !isAllPositiveDigit(s_addr))
                errorReportDetail("Error encountered parsing Tracefile: Numbers can't be negative", lineNumber, line);
        }

        //first node
        if (head == NULL)
        {
            head = initProcess(NULL, pid, offset);
            prev = head;
            chunk *c = initChunk(lineNumber, offset);
                c->end = offset + read;

                pushToHead(prev->chunks, initListNode(c));
        }
        else
        {
            // 1: see if process exist
            process *temp = getProcess(head, pid);

            if (temp == NULL)
            {
                // 1: if doesn't exist, create new and set min and max
                prev = initProcess(prev, pid, offset);
                //create chunk header

                chunk *c = initChunk(lineNumber, offset);
                c->end = offset + read;

                pushToHead(prev->chunks, initListNode(c));
            }
            else
            {
                //2: start chunking
                listNode *currChunk = temp->chunks->head;
                chunk *found = NULL;

                for (int i = 0; i < temp->chunks->size; i++)
                {
                    //2: check if chunks head's lineNumber is current LineNumber-1
                    chunk *temp = (chunk *)currChunk->p;

                    if (temp->lineNumber == lineNumber - 1)
                    {
                        //2: if so, update end and lineNumber
                        temp->end = offset + read;
                        temp->lineNumber = lineNumber;

                        found = temp;
                        break;
                    }

                    //2: if not,  check next

                    currChunk = currChunk->next;
                }

                //2: if none found, then create new and add to tail
                if (found == NULL)
                {
                    chunk *c = initChunk(lineNumber, offset);
                    c->end = offset + read;
                    pushToTail(temp->chunks, initListNode(c));  //REVIEW: SHOULD BE PUSH TO TAIL?
                }

                //1: if it does, then update maxAddr
                prev = temp;
                prev->maxAddrOffset = offset;
            }
        }
    }

    fclose(fPtr);
    return head;
}
