
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
// #include "main.c"
/**
 * Returns process based on provided PID
 * */

// static int processNum = 0;  //TODO: remove

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
    {
        while (prev->next)
        { //Find the last process

            prev = prev->next;
        }

        prev->next = p;
    }

    p->PID = pid;
    p->currOffset = addr;
    p->maxAddrOffset = addr;
    p->chunks = initLinkedList();
    // p->prev = prev;
    // prev->next =p;
    p->root = NULL;
    // p->next = NULL;
    return p;
}

/**
 * Frees memory allocated for the process
 * */
process *freeProcess(process *head, process *p)
{

    // printf("        Freeing Process num: %d \n", processNum++);

    if (!p)
        return NULL;
    process *toRemove;

    if (head == p)
    {
        toRemove = p;
        head = p->next;
    }
    else
    {
        process *curr;
        while (curr)
        {
            if (curr == p)
            {

                toRemove = p;
                break;
            }
            curr = curr->next;
        }
    }

    if (toRemove)
    {
        // traverse thru chunks and freeChunk()
        //free chunkLinkedList

        // freeLinkedList(p->chunks);
        // if (toRemove->prev != NULL)
        //     toRemove->prev = toRemove->next;
        // else
        // {
        //     toRemove->prev == NULL;
        // }

        // else
        //     toRemove->next

        tdestroy(toRemove->root, freeNode);

        free(toRemove);
    }

    if (head == NULL)
        return NULL;
    return head;
}
