
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

/**
 * Returns process based on provided PID
 * */
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
/**
 * Allocates memory for chunk
 * */
chunk *initChunk(int lineNumber, unsigned long addr)
{
    chunk *c = malloc(sizeof(chunk));
    if (c == NULL)
        errorReport("BAD MALLOC OR UNABLE TO MALLOC");
    c->lineNumber = lineNumber;
    c->start = addr;
    c->reachedEnd = 1;
    return c;
}

/**
 * Allocates memory for listnode
 * */
void freeChunk(chunk *c)
{
    free(c);
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

/**
 * Frees memory allocated for the process
 * */
void freeProcess(process *p)
{
    //TODO: talk to D and figure out what to free
    //free treeNode root?

    // traverse thru chunks and freeChunk()
    //free chunkLinkedList

    free(p);

}
