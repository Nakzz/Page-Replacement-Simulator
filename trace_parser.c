
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

/**
 * Return Process node which points to other Processes
 * */
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

        char s_pid[1024]="";
        char s_addr[1024]="";
        char extra_read[1024]="";

        errno = 0; /* reset errno to 0 before call */
        unsigned long pid;
        unsigned long addr;
        const int BASE = 0;
        unsigned long offset = 0;
        offset = ftell(fPtr) - read;

        sscanf(line, "%s %s %s", s_pid, s_addr, extra_read);

        // printf("%d \n \n", strlen(extra_read));
        if(strlen(extra_read) >0)
            errorReportDetail("tracefile format contains error", lineNumber, line);

        if (isAllPositiveDigit(s_pid) && isAllPositiveDigit(s_addr))
        // if (isAllDigit(s_pid) && isAllDigit(s_addr))

        {
            char *stopPID, *stopAddr;

            pid = strtoul(s_pid, &stopPID, BASE);
            addr = strtoul(s_addr, &stopAddr, BASE);

            checkStrtoulError(s_pid, stopPID, pid);
            checkStrtoulError(s_addr, stopAddr, addr);

            printf(" string: %s %s      long: %ld %ld BASE:(%d) \n", s_pid, s_addr, pid, addr, BASE);

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
                    pushToTail(temp->chunks, initListNode(c)); //REVIEW: SHOULD BE PUSH TO TAIL?
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

/* test return to number and errno values */
void checkStrtoulError(char *start, char *end, unsigned long val)
{

    if (start == end)
        // printf (" number : %ld  invalid  (no digits found, 0 returned)\n", val);
        errorReport("Error parsing tracefile: invalid (no digits found, 0 returned)");
    else if (errno == ERANGE && val == ULONG_MAX)
        // printf (" number : %ld  invalid  (underflow occurred)\n", val);
        errorReport("Error parsing tracefile: invalid (underflow occurred)");

    else if (errno == ERANGE && val == ULONG_MAX)
        // printf (" number : %ld  invalid  (overflow occurred)\n", val);
        errorReport("Error parsing tracefile: invalid (overflow occurred)");

    else if (errno == EINVAL) /* not in all c99 implementations - gcc OK */
        // printf (" number : %ld  invalid  (base contains unsupported value)\n", val);
        errorReport("Error parsing tracefile: invalid (base contains unsupported value)");

    else if (errno != 0 && val == 0)
        // printf (" number : %ld  invalid  (unspecified error occurred)\n", val);
        errorReport("Error parsing tracefile: invalid (unspecified error occurred)");
}
