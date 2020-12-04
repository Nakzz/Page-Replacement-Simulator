
///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	linked_list.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "linked_list.h"

/**
 * Allocates memory for listnode
 * */
listNode *initListNode(void *p)
{
    listNode *n = malloc(sizeof(listNode));
    if (n == NULL)
        errorReport("BAD MALLOC OR UNABLE TO MALLOC");
    n->p = p;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

/**
 * Frees memory for listnode
 * */
void freeListNode(listNode *n)
{
    if (n)
        free(n);
}

/**
 * Allocates memory for linked list
 * */
void freeLinkedList(LinkedList *ll)
{
    if (ll)
        free(ll);
}

/**
 * Allocates memory for linkedlist
 * */
LinkedList *initLinkedList()
{
    LinkedList *ll = malloc(sizeof(LinkedList));
    if (ll == NULL)
        errorReport("BAD MALLOC OR UNABLE TO MALLOC");
    ll->size = 0;
    ll->head = NULL;
    ll->tail = NULL;

    return ll;
}

/**
 * Adds listnode to head of linkedlist
 * */
listNode *pushToHead(LinkedList *ll, listNode *n)
{ //FIFO, LRU !TESTED!

    if (ll->head == NULL)
    {
        ll->head = n; // set the only element as tail
        ll->size = ll->size + 1;
        ll->tail = n; // set the only element as tail
    }
    else
    {
        ll->head->prev = n; // add current heads prev
        n->next = ll->head; // add new heads next
        ll->head = n;       // set new head
        ll->size = ll->size + 1;
        // ll->tail->next = n;
    }

    return ll->head;
}

/**
 * Removes listnode from linkedlist tail
 * */
void *popFromTail(LinkedList *ll)
{ // FIFO LRU !TESTED!

    listNode *pop;

    if (ll->tail == NULL)
        pop = NULL;
    else
    {
        if (ll->head == ll->tail) // only node
        {
            pop = ll->head;
            ll->head = NULL;
            ll->tail = NULL;
            ll->size = ll->size - 1;
        }
        else
        {
            pop = ll->tail;
            ll->size = ll->size - 1;

            if (ll->size == 1)
                ll->tail = ll->head;
            else
                ll->tail = ll->tail->prev;
        }
    }

    void *p = pop->p;
    freeListNode(pop);
    return p;
}

/**
 * Removes listnode from linkedlist 
 * */
void *removeNode(LinkedList *ll, listNode *n)
{ //LRU !TESTED!

    if (ll->head != NULL)
    {
        listNode *curr = ll->head;

        while (curr != NULL)
        {

            if (curr == n)
                break;

            curr = curr->next;
        }

        if (curr == NULL) //if end of LL and still no match
            return NULL;

        if (curr == ll->head && curr == ll->tail)
        {                           // only elem
            return popFromTail(ll); //or popFromHead();
        }
        else if (curr == ll->head) //pop from head
        {
            return popFromHead(ll);
        }
        else if (curr == ll->tail) // pop from tail
        {
            return popFromTail(ll);
        }
        else
        { // base case
            curr->prev = curr->next;
            ll->size = ll->size - 1;
            return curr;
        }
    }

    return NULL;
}
/**
 * Removes listnode from linkedlist head
 * */
void *popFromHead(LinkedList *ll)
{ //REVIEW: DO test
    listNode *pop;

    if (ll->head == NULL)
        pop = NULL;
    else
    {
        if (ll->head == ll->tail)
        {
            pop = ll->head;
            ll->head = NULL;
            ll->tail = NULL;
            ll->size = ll->size - 1;
        }
        else
        {
            pop = ll->head;
            // ll->tail->next = ll->head->next;
            ll->head = ll->head->next;
            ll->size = ll->size - 1;
        }
    }

    void *p = pop->p;
    freeListNode(pop);
    return p;
}

/**
 * Adds listnode to tail of linkedlist
 * */
listNode *pushToTail(LinkedList *ll, listNode *n)
{

    if (ll->head == NULL)
    {
        ll->head = n; // set the only element as tail
        ll->size = ll->size + 1;

        ll->tail = n; // set the only element as tail
    }
    else
    {
        listNode *temp = ll->tail;
        ll->tail->next = n; // add to current tail
        // ll->head->prev = n;
        ll->tail = n;          // set new tail
        ll->tail->prev = temp; // set new tail
        // ll->tail->next = ll->head;       // set new tail

        ll->size = ll->size + 1;
    }

    return ll->tail;
}
