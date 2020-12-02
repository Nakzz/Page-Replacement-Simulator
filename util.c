///////////////////////////////////////////////////////////////////////////////
//
// Title:		537make
// Filename:	util.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#include "util.h"

/**
 * prints out message to with stderr
 * number and gives description
 * Used for malloc errors
 */
void errorReport(char *err)
{
    fprintf(stderr, "<ERROR MESSAGE>: %s\n", err);
    exit(1);
}

/**
 * Prints out errorts with specified line number and
 * the line at which the error occured
 */
void errorReportDetail(char *errMsg, int lineNum, char *line)
{
    fprintf(stderr, "%d: <%s>: %s\n", lineNum, errMsg, line);
    exit(1);
}

void remove_spaces(char *s)
{
    const char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while (*s++ = *d++);
}

int isAllDigit(char *s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
        return 0;
    char *p;

    strtod(s, &p);
    return *p == '\0';
}

int isAllPositiveDigit(char *s)
{
    if (s == NULL || *s == '\0' || isspace(*s) || s[0] == '-')
        return 0;
    char *p;

    strtod(s, &p);
    return *p == '\0';
}
