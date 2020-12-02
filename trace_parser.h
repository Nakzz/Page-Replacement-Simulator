
///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	trace_parser.h
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#ifndef TRACEPARSER_H
#define TRACEPARSER_H

#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "process.h"
#include "util.h"

process *generateProcessList(char *traceFile);

#endif