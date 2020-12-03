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
    s->processRunning = numProcesses;
    s->TMR = 0;
    s->TPI = 0;
    s->useableMem = 0;
}

/**
 * Returns the count of how many pages frames are occupied and average this over each clock tick that the simulator runs.
 **/
unsigned long getAMU(Statistics *s)
{
    unsigned long amu = s->useableMem / s->clockTick;
    return amu;
}

/**
 * Returns the count of average of the number of processes that are running (or runable). 
 * This value is averaged over each clock tick for which the simulator runs
 **/
unsigned long getARP(Statistics *s)
{
    unsigned long arp = s->processesRunning / s->clockTick;
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

/**
 * Increments total number of process running
 **/
void incProcessesRunning(Statistics *s, unsigned long runnableProcesses)
{
    s->processesRunning += runnableProcesses;
}

void incUsableMem(Statistics *s, unsigned long useableMem)
{
    s->useableMem += useableMem;
}

/**
 * Increments clock tick by 1ns
 **/
void incClock(Statistics *s, unsigned long runnableProcesses, unsigned long usableMem)
{
    s->clockTick = s->clockTick + 1;

    incProcessesRunning(runnableProcesses);
    incUsableMem(usableMem);
}

/**
 * Move clock tick given time
 **/
void moveClock(Statistics *s, unsigned long useableMem, unsigned long timeToMoveTo)
{
    long int difference = timeToMoveTo - s->clockTick;
    s->clockTick = timeToMoveTo;
    unsigned long memUsable = useableMem * difference;
    incUsableMem(memUsable);
}

void printStats(Statistics *s)
{
    unsigned long amu = getAMU(s);
    unsigned long aru = getARP(s);

    printf("Average Memory Utilization (AMU): %/ul\n", amu);
    printf("Average Runnable Processes (ARP): %/ul\n", arp);
    printf("Total Memory References (TMR): %ul\n", s->TMR);
    printf("Total Page Ins (TPI): %ul\n", s->TPI);
    printf("Running Time: %ul\n", s->clockTick);
}