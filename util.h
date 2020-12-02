///////////////////////////////////////////////////////////////////////////////
//
// Title:		537make
// Filename:	util.h
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef UTIL_H
#define UTIL_H

void errorReport(char *err);
void errorReportDetail(char *errMsg, int lineNum, char *line);
int isAllDigit(char *s);
int isAllPositiveDigit(char *s);

#endif
