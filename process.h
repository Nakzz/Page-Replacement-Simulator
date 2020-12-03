
///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	process.h
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "pagetable.h"
#include "util.h"

typedef struct process
{
    unsigned long PID;
    unsigned long currOffset;
    unsigned long maxAddrOffset;
    unsigned long memToRemove; // set to zero after removing
    treeNode *root;            //NOTE: this is the root node that holds the pagetable data structure for this process
    struct process *next;
    struct LinkedList *chunks; // start: begining byte of line, end: just the pointer of end of the line, reachedEnd: if the end was really reached for this chunk or was it temporarily put on disk
} process;

typedef struct chunk
{
    unsigned long start;
    unsigned long end;
    unsigned long lineNumber;
    int reachedEnd;
} chunk;

process *getProcess(process *head, unsigned long pid);
process *initProcess(process *prev, unsigned long pid, unsigned long addr);
chunk *initChunk(int lineNumber, unsigned long addr);
void freeProcess(process *p);
void freeChunk(chunk *c);

#endif