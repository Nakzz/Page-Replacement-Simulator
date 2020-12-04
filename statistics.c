///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	statistic.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "statistics.h"

/**
 * Initializes Statistics structure
 **/
Statistics *initStatistics(unsigned int numProcesses)
{
    Statistics *s = malloc(sizeof(Statistics));
    if (!s)
    {
        errorReport("COULD NOT MALLOC STATISTICS MODULE");
    }
    s->clockTick = 0;
    s->runnableProcesses = 0;
    s->processesRunning = numProcesses;
    s->TMR = 0;
    s->TPI = 0;
    s->useableMem = 0;
    return s;
}

/**
 * Returns the count of how many pages frames are occupied and average this over each clock tick that the simulator runs.
 **/
double getAMU(Statistics *s)
{
    double amu = s->useableMem / (double)s->clockTick;
    return amu;
}

/**
 * Returns the count of average of the number of processes that are running (or runable). 
 * This value is averaged over each clock tick for which the simulator runs
 **/
double getARP(Statistics *s)
{
    double arp = s->runnableProcesses / (double)s->clockTick;
    return arp;
}

/**
 * Returns total number of memory references in the trace file
 **/
unsigned long getTMR(Statistics *s)
{
    return s->TMR;
}

/**
 * Returns total number of page faults (resulting in disk transfers into memory).
 **/
unsigned long getTPI(Statistics *s)
{
    return s->TPI;
}

/**
 * Increments number of page faults (resulting in disk transfers into memory).
 **/
void incTPI(Statistics *s)
{
    s->TPI = s->TPI + 1;
}

/**
 * Increments total number of memory references in the trace file
 **/
void incTMR(Statistics *s)
{
    s->TMR = s->TMR + 1;
}

/**
 * Returns total number of clock ticks for the simulator run in nano seconds
 **/
unsigned long getRunningTime(Statistics *s)
{
    return s->clockTick;
}

unsigned long getSize(Statistics *s)
{
    return s->memBeingUsed;
}

void incProcessesRunning(Statistics *s)
{
    s->processesRunning++;
}

void decProcessesRunning(Statistics *s)
{
    s->processesRunning--;
}

/**
 * Increments total number of process running
 **/
void incRunnableProcesses(Statistics *s)
{
    s->runnableProcesses += s->processesRunning;
}

void incMemBeingUsed(Statistics *s)
{
    s->memBeingUsed++;
}

void incUsableMem(Statistics *s)
{
    s->useableMem += s->memBeingUsed;
}

void decUsableMem(Statistics *s){
    s->useableMem -= s->memBeingUsed;
}


/**
 * Increments clock tick by 1ns
 **/
void incClock(Statistics *s)
{
    s->clockTick = s->clockTick + 1;
    incRunnableProcesses(s);
    incUsableMem(s);
}

/**
 * Move clock tick given time
 **/
void moveClock(Statistics *s, unsigned long timeToMoveTo)
{
    long int difference = timeToMoveTo - s->clockTick;
    s->clockTick = timeToMoveTo;
    s->useableMem += (s->memBeingUsed * difference);
}

void printStats(Statistics *s)
{
    double amu = getAMU(s);
    double arp = getARP(s);

    printf("\n\n Average Memory Utilization (AMU): %f\n", amu);
    printf("Average Runnable Processes (ARP): %f\n", arp);
    printf("Total Memory References (TMR): %lu\n", s->TMR);
    printf("Total Page Ins (TPI): %lu\n", s->TPI);
    printf("Running Time: %lu\n", s->clockTick);
}