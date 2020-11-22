CC = gcc
CFLAGS = -Wall -pedantic -ggdb -Wextra
OBJECTS = main.o list.o argparser.o util.o make_parser.o build_model.o build_graph.o executor.o

537make: $(OBJECTS)
	$(CC) $(CFLAGS) -o 537make ${OBJECTS}

main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

make_parser.o: make_parser.c make_parser.h 
	$(CC) $(CFLAGS) -c make_parser.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

argparser.o: argparser.c argparser.h
	$(CC) $(CFLAGS) -c argparser.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

executor.o: executor.c executor.h
	$(CC) $(CFLAGS) -c executor.c

build_model.o: build_model.c build_model.h
	$(CC) $(CFLAGS) -c build_model.c

build_graph.o: build_graph.c build_graph.c
	$(CC) $(CFLAGS) -c build_graph.c

clean:
	rm -f $(OBJECTS) 537make

test:
	# @printf "\n\n Test \n"
	# @./537make -f ./proj3_test/modification_check/makefile
	# @printf "\n\n Test Done"

	@printf "\n\n Test \n"
	@./537make -f /home/aj/classes/537/537make/proj3_test/simple_testcase/makefile
	@printf "\n\n Test Done"

	# @printf "\n\n Test \n"
	# @./537make -f /home/aj/classes/537/537make/proj3_test/null_character/makefile
	# @printf "\n\n Test Done"