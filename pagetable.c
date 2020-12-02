
#include "pagetable.h"

treeNode *initTreeNode(unsigned long addr)
{
    treeNode *newNode = malloc(sizeof(treeNode));
    if (!newNode)
    {
        errorReport("CANNOT MALLOC TREENODE");
    }
    newNode->addr = addr;
    return newNode;
}

int compare(void *a, void *b)
{
    treeNode *x = (treeNode *)a;
    treeNode *y = (treeNode *)b;

    if (x->addr - y->addr < 0)
    {
        return -1;
    }
    else if (x->addr - y->addr > 0)
    {
        return 1;
    }
    return 0;
}

treeNode *findNode(unsigned long memAddr, treeNode **root)
{
    treeNode toCompare;
    toCompare.addr = memAddr;
    treeNode *toReturn;
    void *present = tfind(&toCompare, (const void *)root, compare);
    if (!present)
    {
        toReturn = NULL;
    }
    else
    {
        toReturn = *(treeNode **)present;
    }
    return toReturn;
}

void addNode(unsigned long memAddr, treeNode **root)
{
    treeNode toCompare;
    toCompare.addr = memAddr;
    void *present = tsearch(&toCompare, (const void *)root, compare);
    if (!present)
    {
        errorReport("Not enough memory for node to be added to tree");
    }
}

void deleteNode(unsigned long memAddr, treeNode **root)
{
    treeNode toCompare;
    toCompare.addr = memAddr;
    void *present = tdelete(&toCompare, (const void *)root, compare);
    if (!present)
    {
        errorReport("Node to delete was not in tree");
    }
    free(present);
}