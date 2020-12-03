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

treeNode *addNode(unsigned long memAddr, void **root);

treeNode *findNode(unsigned long memAddr, const void **root);

void deleteNode(unsigned long memAddr, void **root);

#endif