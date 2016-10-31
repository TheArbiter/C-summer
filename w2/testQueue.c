#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Item.h"
#include "Queue.h"

void queueWhiteBoxTests(void);
int main (int argc, char *argv[]){
    
    //Run black box tests
    printf("Black Box tests:\n");
    
    printf("Test 1: createQueue\n");
    Queue q = createQueue();
    assert(q != NULL);
    assert(queueSize(q) == 0);
    printf("Passed\n");

    printf("Test 2: add 10 items to the Queue\n");
    int i = 0;
    for(i = 0; i < 10; i++)
        putQueue(q,i);
    assert(queueSize(q) == 10);
    printf("Passed\n");

    printf("Test 3: Remove 2 items from the Queue\n");
    getQueue(q);
    getQueue(q);
    assert(queueSize(q) == 8);
    printf("Passed\n");
        
    /* 
    printf("Test 4: put more than the 10 items to the Queue\n");
    for(i = 0; i < 3; i++){
        putQueue(q,i);
        printf("item %d added\n",i);
    }     // check to see if it aborts
    printf("Passed\n");
    
    printf("Test 4: Remove more than the included items from the Queue\n");
    for(i = 0; i < 10; i++)
        getQueue(q); // check to see if it aborts
    printf("Passed\n");
    */
    
    printf("Test 4: destroyQueue\n");
    destroyQueue(q);
    printf("Passed\n");

   //Run white box tests
    queueWhiteBoxTests();

    return 0;
}       
