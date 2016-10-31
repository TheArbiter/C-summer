CC = gcc
CFLAGS = -Wall -Werror -gdwarf-2

.PHONY:	clean clobber

all: graphClient

%o:%c
	$(CC) $(CFLAGS) -c $<

graphClient: graphClient.o Graph_AdjMatrix.o
	$(CC) -o graphClient graphClient.o Graph_AdjMatrix.o
clean:
	rm -f *.o core

clobber: clean
	rm -f graphClient
