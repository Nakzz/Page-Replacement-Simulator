# Page-Replacement-Simulator

three executables - 537pfsim-fifo - 537pfsim-lru - 537pfsim-clock

Run using: pfsim-lru -p 8192 -m 2 tracefile1

## The Trace Files

The trace files contain a sequence of records that report on memory references made by the running process (and not the operating system) Each record is a line in the file that describes one memory reference. The record has two decimal numbers, the process ID (PID) and virtual page number (not the full address, but just the VPN). Each number in the trace file is a long integer ("unsigned long"). For example, a line in the trace file might be:
1234 10000
which indicates that process 1234 referenced page 10000.

# TODO

[] MAKEFILE
[] build rules for - 537pfsim-fifo - 537pfsim-lru - 537pfsim-clock
[] arg_parser
[] -p
[] -m
[] <tracefile>
[] trace_parser: DO NOT READ ALL TRACES IN ONE TIME
[] pass 1: find all PID, first mem ref and last mem ref
[] pass 2:
[] disk_queue for disk I/O
[] page_algorithm
[] FIFO
[] LRU
[] CLOCK
[] process
[] page_tables
[] page_frame_table
[] Build test suite
[] bad trace file
[] null char
[] improper format
[] white space
[] read largest long unsigned(64 bit=> 18,446,744,073,709,551,615 , 32 bit=> 4,294,967,295) +1  
 [] can be buffer overflow? if so, throw error
[] run each trace_files with 6 times - page sizes of 512 and 4096 bytes - physical memory sizes of 1 MB, 4MB, and 32 MB.
[] Grade Check
[] valgrind: memory leaks
[] Headers
[] gcc warning
[] Use global constants instead of macro
[] malloc return values

## Meeting Logs

- 11/22:
  [] Software Design and Architecture
  [] Schedule Meeting with TA for review
  [] Argue points for prog 3 - Does not print parsing erros correctly - incorrect .h dependencies (eg arg parsing) - program chaes (many commands test case)

gcc argparser.c argparser.h util.c util.h -o argparser
