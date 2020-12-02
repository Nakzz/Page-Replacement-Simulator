
///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	linked_list.h
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <string.h>
#include "process.h"

typedef struct listNode
{
    void *p;
    struct listNode *next;
    struct listNode *prev;
} listNode;

typedef struct LinkedList
{
    listNode *head;
    listNode *tail;
    int size;
} LinkedList;

LinkedList *initLinkedList();
void freeLinkedList(LinkedList *ll);
void freeListNode(listNode *n);
listNode *initListNode(void *p);
listNode *pushToHead(LinkedList *ll, listNode *n);
listNode *pushToTail(LinkedList *ll, listNode *n);
listNode *popFromTail(LinkedList *ll);
listNode *popFromHead(LinkedList *ll);

listNode *removeNode(LinkedList *ll, listNode *n);

#endif