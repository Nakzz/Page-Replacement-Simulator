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

// look at @820

typedef struct Statistics
{
    unsigned long clockTick;        // Number of clock ticks in nano seconds
    unsigned long processesRunning; // Number of processes running
    unsigned long useableMem;
    unsigned long TPI; // Number of Page Faults
    unsigned long TMR; // Number of Memory Reference
} Statistics;

Statistics *initStatistics(unsigned int numProcesses);
unsigned long getAMU(Statistics *s);
unsigned long getARP(Statistics *s);
unsigned long getTMR(Statistics *s);
unsigned long getTPI(Statistics *s);
void incTPI(Statistics *s);
void incTMR(Statistics *s);
void incProcessesRunning(Statistics *s, unsigned long runnableProcesses);
void incClock(Statistics *s, unsigned long runnableProcesses, unsigned long usableMem);

unsigned long getRunningTime(Statistics *s);