#ifndef ARGPARSER_H
#define ARGPARSER_H
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "util.h"

typedef struct SpecNode
{
    unsigned long pageSize;
    unsigned long memSize;
    char *traceFile;
} SpecNode;

SpecNode *argParser(int argc, char **argv);
bool isPowerOfTwo(unsigned long n);
#endif