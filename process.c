
///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	process.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "process.h"

process *getProcess(process *head, unsigned long pid)
{
    if (head != NULL)
    {
        process *curr = head;
        while (curr != NULL)
        {

            if (curr->PID == pid)
                return curr;

            curr = curr->next;
        }
    }

    return NULL;
}
chunk *initChunk(int lineNumber, unsigned long addr)
{
    chunk *c = malloc(sizeof(chunk));
    c->lineNumber = lineNumber;
    c->start = addr;
    return c;
}

process *initProcess(process *prev, unsigned long pid, unsigned long addr)
{

    //check if propper digits

    process *p = malloc(sizeof(process));

    if (p == NULL)
    {
        errorReport("BAD MALLOC OR UNABLE TO MALLOC");
    }

    if (prev != NULL)
        prev->next = p;

    p->PID = pid;
    p->currOffset = addr;
    p->maxAddrOffset = addr;
    p->chunks = initLinkedList();
    //TODO: init listNode? D thinks i should init and free in the algo based on hit or miss.

    return p;
}

//TODO: create a free method for reccursively clean everyting?
