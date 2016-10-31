// words.c ... Build a tree of words from /usr/dict/words
// Written by John Shepherd, August 2008
// Modified by Angela Finlayson, January 2009

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "HashTableItem.h"
#include "HashTable.h"

#define WORD_FILE "/usr/share/dict/words"
#define MAX_WORD_SIZE 100 

void getAllWords(FILE *, HashTable h);

// Get words, store in hashTable, print hashtable stats
int main(int argc, char **argv){
    char *wordsFile; // name of file containing words
    FILE *wordf;     // file handle for file containing words
    HashTable hashTable; 
    int size = 100;

    // access the word file
    if (argc > 1){
	wordsFile = argv[1];
    }else{
	wordsFile = WORD_FILE;
    }
    if(argc > 2){
        size = atoi(argv[2]);
    }
    wordf = fopen(wordsFile,"r");
    if (wordf == NULL) {
        printf("Can't open %s\n",wordsFile);
        exit(1);
    }
    hashTable = createHashTable(size);
    printf("Reading words from %s\n",wordsFile);    
    // build tree containing all words
    getAllWords(wordf,hashTable);

    // print some properties
    showHashStats(hashTable);
    destroyHashTable(hashTable);
    return 0;
}

// Read all words from file into table 
void getAllWords(FILE *f, HashTable hashTable){
    char word[MAX_WORD_SIZE];

    while (fgets(word,MAX_WORD_SIZE,f) != NULL) {
        int n = strlen(word);
	word[n-1] = '\0'; // strip off \n
	// filter out empty words
	if (strcmp(word,"") != 0) {
       	    addToHashTable(hashTable,strdup(word),strdup(word));
        }
        
    }
}
