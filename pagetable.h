#ifndef PAGETABLE_H
#define PAGETABLE_H

#include "util.h"
#include <search.h>
#include <stdlib.h>

typedef struct treeNode
{
    unsigned long addr;
} treeNode;

treeNode *initTreeNode(unsigned long addr);

int compare(void *a, void *b);

void addNode(unsigned long memAddr, treeNode **root);

treeNode *findNode(unsigned long memAddr, treeNode **root);

void deleteNode(unsigned long memAddr, treeNode **root);

#endif