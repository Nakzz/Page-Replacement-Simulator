///////////////////////////////////////////////////////////////////////////////
//
// Title:		Page Replacement Simulator
// Filename:	main.c
//
// Course:		cs537, Fall 2020
// Authors:		Ajmain Naqib, Devanshu Mantri
// NetID:		naqib, dmantri
// CsLogin:		ajmain, devanshu
//
///////////////////////////////////////////////////////////////////////////////

#define _GNU_SOURCE
#include "trace_parser.h"
#include "argparser.h"

/**
 * Driver class for the program
 * */
int main(int argc, char **argv)
{

    // Your program will be structured as a continuous loop that reads trace records and advances the simulated time

    // long int clock =0; //holds the value of the current time. the clock tick will be 1 ns.
    // struct node **args = argParser(argc, argv); //TODO: throw error if proper flags aren't given

    SpecNode *args = argParser(argc, argv);

    process *head = generateProcessList(args->traceFile);

    // LinkedList *ll = initLinkedList();

    process *curr = head;
    while(curr){
        
        listNode *chunkNode = curr->chunks->head;

        while(chunkNode){
            
            chunk* tempChunk = (chunk*) chunkNode->p;

            printf("pid:%lu chunk:{%lu,%lu } ending in line: %d \n",curr->PID, tempChunk->start, tempChunk->end, tempChunk->lineNumber );

            chunkNode= chunkNode->next;
        }

            printf(" \n next pid \n\n" );

        curr= curr->next;
    }

    //TODO: clock++ if a process makes a memory reference and also while waiting for a disk I/O to complete

    // Flow of the program
    // Then go over design and datastructures
    // then other stuff
}