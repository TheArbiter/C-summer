CC=gcc
CFLAGS=-Wall -Werror -O

all: words words2

words: words.o Tree.o
	$(CC) $(CFLAGS) -o words words.o Tree.o

words2: words2.o HashTable.o HashTableItem.o
	$(CC) $(CFLAGS) -o words2 words2.o HashTable.o HashTableItem.o


words.o: words.c Tree.h Item.h

tree.o: Tree.c Tree.h Item.h

words2.o: words2.c HashTable.h HashTableItem.h

HashTable.o: HashTable.c HashTable.h HashTableItem.h

HashTableItem.o: HashTableItem.c HashTableItem.h


clobber: clean
	rm -f words words2
clean:
	rm -f core *.o
