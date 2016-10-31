CC = gcc
CFLAGS = -Wall -Werror -gdwarf-2

.PHONY:	clean clobber

all: bonus

%o:%c
	$(CC) $(CFLAGS) -c $<

assn2: main.o Graph.o Agent.o Queue.o Nodes.o
	$(CC) -o assn2 main.o Graph.o Agent.o Queue.o Nodes.o

clean:
	rm -f *.o core

clobber: clean
	rm -f assn2
	
bonus: main.o Graph.o Agent.o Queue.o Nodes.o
	$(CC) $(CFLAGS) -D BONUS -o assn2Bonus main.c Graph.c Agent.c Queue.c Nodes.c	
