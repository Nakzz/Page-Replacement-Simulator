CC = gcc 
CFLAGS = -Wall -pedantic -ggdb -Wextra 
OBJECTS = check_linked_list.o ../util.o ../process.o ../linked_list.o


check: $(OBJECTS)
	$(CC) $(CFLAGS) -o check ${OBJECTS} `pkg-config --cflags --libs check`


check_linked_list.o: check_linked_list.c
	$(CC) $(CFLAGS) -c check_linked_list.c 