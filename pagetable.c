
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

int compare(const void *a, const void *b)
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

treeNode *findNode(unsigned long memAddr, void *const *root)
{
    treeNode toCompare;
    treeNode *toReturn;
    toCompare.addr = memAddr;

    void **present = tfind(&toCompare, root, compare);
    if (!present)
    {
        // printf("Key not Found: %lu\n", memAddr);
        toReturn = NULL;
    }
    else
    {
        toReturn = *(treeNode **)present;
    }
    return toReturn;
}

void addNode(unsigned long memAddr, void **root)
{
    treeNode *toCompare = initTreeNode(memAddr);

    void **present = tsearch(toCompare, root, compare);
    if (!present)
    {
        errorReport("Not enough memory for node to be added to tree");
    }
    else if (toCompare != *present)
    {
        // printf("Node already exsits in tree, with key: %lu\n", memAddr);
        free(toCompare);
        toCompare = NULL;
    }
    else
    {
        // printf("Added Node with Key: %lu\n", memAddr);
    }
}

void deleteNode(unsigned long memAddr, void **root)
{
    treeNode *toDelete = findNode(memAddr, root);
    if (toDelete != NULL)
    {
        tdelete(&toDelete, root, compare);
    }
    free(toDelete);
}

void freeNode(void *toFree)
{
    treeNode *toFreeNode = toFree;
    free(toFreeNode);
}