///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	page_algorithm.h
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////
#ifndef PAGEALGO_H
#define PAGEALGO_H

#include "linked_list.h"
#include "process.h"

typedef struct PageAlgoStruct
{
    LinkedList *datastructure;
    // void *ptr;
} PageAlgoStruct;

typedef struct Page
{
    unsigned long memAddr;
    process *p;
    int clock;
} Page;

PageAlgoStruct *initPageAlgoStruct();
Page *initPage(unsigned long memAddr, process *p);
process *pageReplacementAlgorithm(int evict, PageAlgoStruct *pas, unsigned long memAddr, process *p); //added evict bool so you know when to pop off a listnode and send it's void pointer to me
// also in this you will now hold mem refrences instead of pointers to treeNodes


#endif
