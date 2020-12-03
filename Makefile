CC = gcc 
CFLAGS = -Wall -pedantic -ggdb -Wextra
OBJECTS = main.o util.o trace_parser.o process.o argparser.o linked_list.o

temp_build: $(OBJECTS)
	$(CC) $(CFLAGS) -o temp_build ${OBJECTS} -lm

argparser.o: argparser.c argparser.h 
	$(CC) $(CFLAGS) -c argparser.c 

main.o: main.c
	$(CC) $(CFLAGS) -c main.c 

trace_parser.o: trace_parser.c trace_parser.h 
	$(CC) $(CFLAGS) -c trace_parser.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

process.o: process.c process.h
	$(CC) $(CFLAGS) -c process.c

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

# executor.o: executor.c executor.h
# 	$(CC) $(CFLAGS) -c executor.c

# build_model.o: build_model.c build_model.h
# 	$(CC) $(CFLAGS) -c build_model.c

# build_graph.o: build_graph.c build_graph.c
# 	$(CC) $(CFLAGS) -c build_graph.c

clean:
	rm -f $(OBJECTS) temp_build

new: clean
	$(MAKE)

537pfsim-fifo: $(OBJECTS) fifo.o
	$(CC) $(CFLAGS) -o temp_build ${OBJECTS} fifo.o -lm
537pfsim-lru: $(OBJECTS) lru.o
	$(CC) $(CFLAGS) -o temp_build ${OBJECTS} lru.o -lm
537pfsim-clock: $(OBJECTS) clock.o
	$(CC) $(CFLAGS) -o temp_build ${OBJECTS} clock.o -lm

test:
	@printf "\n\n Test \n"
	@./537pfsim-fifo ./trace_files/12million.addrtrace  
	@printf "\n\n Test Done"

	@printf "\n\n Test \n"
	@./537make -f /home/aj/classes/537/537make/proj3_test/simple_testcase/makefile
	@printf "\n\n Test Done"

	@printf "\n\n Test \n"
	@./537make -f /home/aj/classes/537/537make/proj3_test/null_character/makefile
	@printf "\n\n Test Done"