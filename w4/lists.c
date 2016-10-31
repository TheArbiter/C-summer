#include <stdlib.h>
#include <stdio.h>
#include "lists.h"


void printList(link list){
    link curr;
    for(curr = list; curr != NULL; curr= curr->next){
        printf("%d ",curr->item);
    }
    printf("\n");
}

link newList(){
    return NULL;
}

link newNode(Item item){
    link n = (link) malloc(sizeof(*n));
    n->item = item;
    n->next = NULL;
    return n;
}

//O(n)
link insertEnd(link list, link n){
    link curr;
    if(list == NULL){
        list = n;
    } else {
        for(curr = list; curr->next != NULL; curr = curr->next){
    
        }
        curr->next = n;
    }
    return list;
}

//O(1)
link insertFront(link list, link n){
   n->next = list;
   return n;
}

void freeList(link list){
  link curr = list;
  link next;   
  while(curr!= NULL){
        next = curr->next;
        free(curr);
        curr = next;
  }

}

link insertionSort(link list){
   link curr,temp,temp2,prev,head = NULL;
   int pass = 0;

   if(list != NULL){
      for(curr = list; curr != NULL;){
         temp = curr->next;
         if(curr == list){
	 //this is the head
			head = curr;
			head->next = NULL;
	 } else {
	    pass = 0;
	    for(prev = NULL,temp2 = head; temp2 != NULL && pass == 0; prev = temp2, temp2 = temp2->next){
	       if(curr->item <= temp2->item){
		  if(prev != NULL){
		     prev->next = curr;
		     curr->next = temp2;
		     pass = 1;
		  } else {
		     head = insertFront(head,curr);
		     pass = 1;
		  }
	       }
	    }
	    if(pass == 0){
	    //tail
	       prev->next = curr;
	       curr->next = NULL;
	    }
	 }
	 curr = temp;
      }
   }
   return head;
}
