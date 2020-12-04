///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	lru.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "page_algorithm.h"

/**
 * Allocated memory for the Algorithm
 * 
 * */
PageAlgoStruct *initPageAlgoStruct()
{
    PageAlgoStruct *c = malloc(sizeof(PageAlgoStruct));
    if (c == NULL)
        errorReport("BAD MALLOC OR UNABLE TO MALLOC");
    c->datastructure = initLinkedList();
    return c;
}

/**
 * Page replacement algorithm 
 * 
 * */

process *pageReplacementAlgorithm(int evict, PageAlgoStruct *p, unsigned long memAddr, process *proc)
{
    //if evict is true, then tail gets kicked out, return this tail

    LinkedList *ll = p->datastructure;
    listNode *found = NULL;
    listNode *n = ll->head;

    //1: check if exists in Linked list

    while (n)
    {
        Page *page = n->p;

        if (page->memAddr == memAddr)
        {
            found = n;
            break;
        }

        n = n->next;
    }

    //1: if doesn't add to linked list
    if (found == NULL)
    {
        Page *page = initPage(memAddr, proc);
        listNode *n = initListNode(page);
        found = pushToHead(ll, n);
    }
    else
    {
        //1: if does, move to front
        Page *page = removeNode(ll, found);
         found = initListNode(page);

        pushToHead(ll, found);
    }

    if (evict)
    {
        found = popFromTail(ll);
    }

    Page *_p = (Page *)found->p;
    process *proc = (process *)_p->p;

    proc->memToRemove = _p->memAddr;
    freeListNode(found);
    free(_p);
    return proc;
}
