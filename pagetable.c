
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

treeNode *findNode(unsigned long memAddr, const void **root)
{
    treeNode toCompare;
    toCompare.addr = memAddr;
    treeNode *toReturn;
    void *present = tfind(&toCompare, root, compare);
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

treeNode *addNode(unsigned long memAddr, void **root)
{
    treeNode *toCompare = initTreeNode(memAddr);
    void *present = tsearch(toCompare, root, compare);
    if (!present)
    {
        errorReport("Not enough memory for node to be added to tree");
    }
    toCompare = *(treeNode **)present; //possible mem leak if toCompare and what is returned by tsearch if not found is not the same mem addr/ pointer
    return toCompare;
}

void deleteNode(unsigned long memAddr, void **root)
{
    treeNode toCompare;
    toCompare.addr = memAddr;
    void *present = tdelete(&toCompare, root, compare);
    if (!present)
    {
        errorReport("Node to delete was not in tree");
    }
    free(present);
}