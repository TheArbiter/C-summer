//A linked list implementation of a queue

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Item.h"
#include "Queue.h"

typedef struct queueNode * link;

struct queueNode { 
    Item item; 
    link next; 
};

struct queueImp { 
    link head; 
    link tail;
    int size; 
};

static link createNode(Item item){ 
    link n = malloc (sizeof(*n));
    assert(n != NULL);
    n->item = item; 
    n->next = NULL;     
    return n;                         
}

// Creates an empty Queue
Queue createQueue (void){ 
    Queue q = malloc (sizeof (*q));
    assert(q != NULL); 
    q->head = NULL; 
    q->tail = NULL;
    q->size = 0; 
    return q;
}

void destroyQueue(Queue queue){
    link curr;
    link next;
    assert(queue != NULL);
    curr = queue->head;
    while(curr!=NULL){
        next = curr->next;
        free(curr);
        curr = next;
    }
    free(queue);

}

int queueSize (Queue q){ 
    assert(q != NULL);
    return q->size; 
}


void putQueue (Queue q, Item item){ 
    assert(q != NULL);
    
    link n = createNode(item);
    if(q->head != NULL){
        n->next = q->head;
        q->head = n;
    } else {
       q->tail = n; 
    }
    q->head = n;
    q->size++;
}

Item getQueue (Queue q){ 
    assert(q != NULL);
    if(q->size > 0){
       Item item = q->head->item;
       link delNode = q->head;
       q->head = q->head->next;    
       free(delNode);
       q->size--;         
       return item;
     } else {
        fprintf(stderr,"queue underflow\n");
        abort();
     }    
}

void queueWhiteBoxTests(void){
    printf("White box tests\n");
         
    Queue queue = createQueue();
    assert(queue !=NULL);
    Item i;
    
    //put 5 items onto the queue
    for(i = 0;i < 5;i++){
        printf("pushing %d onto queue\n",i);
        putQueue(queue,i);
    }
    
    //check current queue size 
    printf("Queue size is %d\n",queue->size);
    assert(queue->size == 5);
    
    //get things out of the queue   
    for(i = 0; i < 5; i++){
        printf("getting %d from queue,queue size is %d\n",getQueue(queue),queue->size);           
    }
    
    //just to check if everything was popped off
    printf("Queue size %d\n",queue->size);
    assert(queue->size == 0);
    
    //put alot of items
    for(i = 0; i < 20; i++){
        printf("Putting %d onto queue, queue size is %d\n",i,queue->size);
        putQueue(queue,i);
    }
    assert(queue->size == 20);
    
    printf("going to get items until program aborts\n");
    //now pop until the program aborts
    for(i = 0; i < 21; i++){
        printf("getting %d from queue\n",getQueue(queue));   
    }   
    
}
