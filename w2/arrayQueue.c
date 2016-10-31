#include <stdlib.h>
#include <stdio.h>
#include "Item.h"
#include "Queue.h"
#include <assert.h>

#define DEFAULT_SIZE 10

struct queueImp{
    Item *items;
    int size;
    int maxSize;
    int first;
    int last;
};

//O(1)
Queue createQueue(){
    Queue q = malloc(sizeof(struct queueImp));
    q->items = malloc(DEFAULT_SIZE * sizeof(Item));
    q->size =0;
    q->first = 0;
    q->last = 0;
    q->maxSize = DEFAULT_SIZE;
    return q;
}

void destroyQueue(Queue q){
    assert(q != NULL);
    free(q->items);
    free(q);
}

//O(1)
int queueSize(Queue q){
    assert(q != NULL);
    return (q->size);
}

//O(1);
void putQueue(Queue q, Item i){
    assert(q != NULL);
    assert(q->size < q->maxSize);
    q->items[q->last]  = i;
    q->last = (q->last +1) % q->maxSize;
    q->size++;
}

//O(n)
Item getQueue(Queue q){
    //int i;
    assert(q != NULL);
    if(q->size > 0){
        Item item = q->items[q->first];
        q->first = (q->first + 1) % q->maxSize;
        q->size--;
        /*//shift the elements across
        for(i=0;i<q->size;i++){
            q->items[i] = q->items[i+1];
        }*/
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
        printf("putting %d onto queue, size: %d, first: %d, last: %d \n",i,queue->size,queue->first,queue->last);
        putQueue(queue,i);
    }
    
    //check current queue size 
    printf("Queue size is %d\n",queue->size);
    assert(queue->size == 5);
    
    //get things out of the queue   
    for(i = 0; i < 5; i++){
        printf("getting %d from queue,queue size is %d, first: %d, last: %d \n",getQueue(queue),queue->size,queue->first,queue->last);           
    }
    
    //just to check if everything was popped off
    printf("Queue size %d\n",queue->size);
    assert(queue->size == 0);
/*    
    //put alot of items
    for(i = 0; i < 20; i++){
        printf("putting %d onto queue, size: %d, first: %d, last: %d \n",i,queue->size,queue->first,queue->last);
        putQueue(queue,i);
    }
    assert(queue->size == 20);
  */  
    printf("going to get items until program aborts\n");
    //now pop until the program aborts
    for(i = 0; i < 21; i++){
        printf("getting %d from queue,queue size is %d, first: %d, last: %d \n",getQueue(queue),queue->size,queue->first,queue->last);   
    }  
 
}
