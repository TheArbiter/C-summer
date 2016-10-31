//HashTable.c
//This implementation uses chaining to handle collisions. Each address in 
//the hash table (array) contains a linked list.

#include "HashTableItem.h"
#include "HashTable.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct linkedListNode * hLink;

struct linkedListNode {
   Key key;
   Value value;
   hLink next;
};

struct hashTable {
   unsigned int size;   
   // array of linked lists. each 'bucket' contains a linked list of collisions
   hLink * buckets;
   // We are keeping track of the total number of collisions
   // that occur, so we can print out some statistics about our  
   //hashFunction 
   int numCollisions;
};

static int length(hLink head){
    int count = 0;
    hLink curr = NULL;
    
    for(curr = head; curr != NULL; curr = curr->next){
        count++;
    }
    
    return count;
}
//This function needs to be implemented for TASK3
static int longestChainSize(HashTable table){
    assert( table != NULL );
    int i,chainlength,longestSize = 0;
    
    for(i=0; i < table->size; i++){
        chainlength = length(table->buckets[i]);
        if(chainlength > longestSize){
            longestSize = chainlength;
        }
    }
    return longestSize;
}

HashTable createHashTable( unsigned int size ) {
    
   HashTable table = malloc(sizeof(struct hashTable));
   int i;
   assert( table != NULL );
  
   // set size and make buckets of valueNode pointers
   table->size = size;
   table->buckets = malloc( sizeof(hLink ) * size );
   assert( table->buckets != NULL );
  
   // set all buckets to empty
   for ( i = 0; i < size; i++ ) {
      table->buckets[i] = NULL;
   }
   table->numCollisions = 0;
   return table;
}


void addToHashTable( HashTable table, Key key, Value value ) {
   assert( table != NULL );
   
   // hash the key to find the right index
   unsigned int bucketIndex = hashFunction( key, table->size );
   assert( bucketIndex < table->size ); // must be an index that fits in the table
   
   // allocate new node
   hLink newNode = malloc( sizeof ( *newNode ) );
   assert( newNode != NULL );
  
   newNode->next = NULL;
   newNode->key = key;
   newNode->value = value;
   
   // find the last node in the linked list, inside this bucket
   hLink lastNode = table->buckets[bucketIndex];
   if( lastNode == NULL ) {
      // there is no node, so we make this the first
      
      table->buckets[bucketIndex] = newNode;
   } else {
      // already a node in this bucket, add to the end of the collision chain
      table->numCollisions++; 
      while(lastNode->next != NULL) {
         lastNode = lastNode->next;
      }
    
      // add the new node at the end of the chain
      lastNode->next = newNode;
   }
}

void updateHashTable( HashTable table, Key key, Value value) {
   assert( table != NULL );
  
   unsigned int bucketIndex = hashFunction( key, table->size );
   
   // iterate through collision list
   hLink node = table->buckets[bucketIndex];
   int found = FALSE;
   while( node != NULL && !found ) {
      // keep iterating until the end, or we've found a match
      
      if( compareKeys( key, node->key ) == 0) {
         // keys match, this is the value we want to update
         node->value = value;
         found = TRUE;
      } else {
         // no match, move to the next node
         node = node->next;
      }
      
   }
   
}

Value lookupInHashTable( HashTable table, Key key) {
   assert( table != NULL );
  
   unsigned int bucketIndex = hashFunction( key, table->size );
   
   Value retrievedValue = NULL;
   
   // iterate through collision list
   hLink node = table->buckets[bucketIndex];
   int found = FALSE;
   while( node != NULL && !found ) {
      if(  compareKeys( key, node->key ) == 0 ) {
         // keys match, this is the value we want to retrieve
         retrievedValue = node->value;
         found = TRUE;
      }else{
         node = node->next;
      }
   }
   
   // this function shouldn't be called if the value wasn't here
   assert( found );
   
   return retrievedValue;
}

Value removeFromHashTable( HashTable table, Key key ) {
   assert( table != NULL );

   unsigned int bucketIndex = hashFunction( key, table->size );

   hLink node = table->buckets[bucketIndex];
   hLink prevNode = NULL;
   
   Value removedValue = NULL;
   
   // iterate through collision list
   int found = FALSE;
   while( node != NULL && !found ) {
      
      if( compareKeys( key, node->key )  == 0) {
         // keys match
         
         if( prevNode == NULL ) {
            // this is the first node in the linked list
            // so we point the bucket to the next node as the first
            table->buckets[bucketIndex] = node->next;
         } else {
            // set the previous node to point to this node's next
            // skipping this node
            prevNode->next = node->next;
     
         }
         
         // save the value of the removed node
         removedValue = node->value;
         // free the node
         free( node );
         
         found = TRUE;
      } else {
         // no match, keep looking
         
         prevNode = node;
         node = node->next;
      }
   }
   
   // make sure it was found
   assert( found );
   
   return removedValue;
}


int isKeyInHashTable( HashTable table, Key key ) {
   assert( table != NULL );

   unsigned int bucketIndex = hashFunction( key, table->size );

   hLink node = table->buckets[bucketIndex];
  
   // iterate through collision list until found
   int found = FALSE;
   while( node != NULL && !found ) {
      if( compareKeys( key, node->key ) == 0) {
         // keys match
         found = TRUE;
      } else {
         // keep looking
         node = node->next;
      }
   }
  
   return found;
}

void destroyHashTable( HashTable table ) {
   int i;
   assert( table != NULL );
   
   hLink node;
   hLink nodeToFree;
  
   // free all the nodes in the table
   for ( i = 0; i < table->size; i++ ) {

     node = table->buckets[i];
    
     while ( node != NULL ) {
       nodeToFree = node;
       node = node->next;
       free( nodeToFree );
     }

   }
   
   free( table->buckets );
   free( table );
}

void showHashStats(HashTable table){
    printf("Size of hashtable %d\n",table->size);
    printf("Num Collisions %d\n",table->numCollisions);
    printf("Longest chain %d\n",longestChainSize(table));
}
