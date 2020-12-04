#ifndef PAGETABLE_H
#define PAGETABLE_H

#include <search.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

typedef struct treeNode
{
    long int addr;
} treeNode;

treeNode *initTreeNode(unsigned long addr);

int compare(const void *a, const void *b);

void addNode(unsigned long memAddr, void **root);

treeNode *findNode(unsigned long memAddr, void *const *root);

void deleteNode(unsigned long memAddr, void **root);

void freeNode(void *toFree);

#endif