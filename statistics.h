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

#ifndef STAT_H
#define STAT_H

#include <stdlib.h>
#include "util.h"
#include <stdio.h>

typedef struct Statistics
{
    unsigned long clockTick;         // Number of clock ticks in nano seconds
    double runnableProcesses;        // holds count for runnable processes per clock tick
    double  useableMem;              // holds count for usableMem
    unsigned long processesRunning;  // num processes running atm
    unsigned long memBeingUsed;      //num mem being used atm
    unsigned long TPI;               // Number of Page Faults
    unsigned long TMR;               // Number of Memory Reference
} Statistics;

Statistics *initStatistics(unsigned int numProcesses);
double getAMU(Statistics *s);
double getARP(Statistics *s);
unsigned long getTMR(Statistics *s);
unsigned long getTPI(Statistics *s);

void incTPI(Statistics *s);
void incTMR(Statistics *s);

void incProcessesRunning(Statistics *s);
void decProcessesRunning(Statistics *s);
void incRunnableProcesses(Statistics *s);
void incMemBeingUsed(Statistics *s);
void decUsableMem(Statistics *s);
void incUsableMem(Statistics *s);
void freeProcessUsableMem(Statistics *s, unsigned long processMem);
void incClock(Statistics *s);
void moveClock(Statistics *s, unsigned long timeToMoveTo);
unsigned long getRunningTime(Statistics *s);
unsigned long getSize(Statistics *s);
void printStats(Statistics *s);

#endif