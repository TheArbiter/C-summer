#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lists.h"


static link newNode(Item v)
{
	link n;
	
	n = (link) malloc(sizeof(node));
	assert(n != NULL);
	n->item = v;
	n->next = NULL;
	return n;
}

void printList (link list) {
  link curr = list;
  while (curr != NULL) {
    printf ("[%d]->", curr->item);
    curr = curr->next;
  }
  printf ("[X]\n");
}


int sumListItems (link ls) {
  
  //set count
  int count = 0;
  
  link curr = ls;
  while(curr !=NULL){
      count = count + curr->item;
      curr = curr->next;
  }
  return count;
}

void freeList(link list){
   
   link curr = list;
   link prev = NULL;
   while(curr !=NULL){
      prev = curr;
      curr = curr->next;
      free(prev);
   }

}

link fromTo (int start, int end) {
  if(start > end) {
      return NULL;
  } else {
      int i;
      link temp = NULL;
      link curr = NULL;
      link prev = NULL;
      
      for (i = start; i <= end; i++){
         curr = newNode(i);
         if(i == start){
            temp = curr;
            prev = temp;
         } else {
            prev->next = curr;
            prev = curr;
         }
      }
      return temp;
  }    
}

dlink newDnode (Item item) {
	dlink m = (dlink) malloc(sizeof(dnode));
	assert(m != NULL);
	m->item = item;
	m->next = NULL;
	m->prev = NULL;
	return m;
}

dlink doublify (link list) {
  dlink temp1 = NULL;
  dlink temp2 = NULL;
  dlink head = NULL;
  
  link curr;
  curr = list;
  
  while(curr != NULL){
      temp1 = newDnode(curr->item);
      temp1->prev = temp2;
      if(temp2 !=NULL){
         temp2->next = temp1;
      }
      temp2 = temp1;
      if(curr == list){ // this is the head
         head = temp1;
      }
      curr = curr->next;
  }
  
  return head;
}

void freeDList(dlink list){
   
	dlink curr, prev;
	curr = list;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}

}

void printDList (dlink list) {
  dlink curr = list;
  dlink temp = NULL;
  while (curr != NULL) {
    printf ("[%d]->", curr->item);
    temp = curr;
    curr = curr->next;
  }
  printf ("[X]\n");

  while(temp !=NULL){
    printf ("[%d]->", temp->item);
    temp = temp->prev;
  }
  printf("[L]\n");

}

