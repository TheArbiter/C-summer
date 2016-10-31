#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Item.h"
#include "Stack.h"

//This function should contain
//tests that have access to the internal structure 
//of the stack. It should be implemented in arrayStack.c
void whiteBoxTests(void);


int main (int argc, char *argv[]){
    Stack s;
    
    //Run black box tests
    //Black box tests should test the ADT through the interface only
    printf("Black Box tests:\n");
    printf("This is just a small example for you to get started\n");

    printf("Test 1: createStack\n");
    s = createStack();
    assert(s != NULL);
    assert(stackSize(s) == 0);
    printf("Passed\n");

    int i = 0;
    printf("Test 2: Push item to stack\n");
    i = 1;
    push(s,i);
    assert(stackSize(s) == 1);      
    printf("Passed\n");

    printf("Test 3: Pop item from stack\n");
    pop(s);
    assert(stackSize(s) == 0);      
    printf("Passed\n");
    //etc
    
    printf("Test 4: Push 11 items to stack\n");
    for(i=0; i<11; i++)
      push(s,i);
    assert(stackSize(s) == 11);      
    printf("Passed\n");
    
    //Run white box tests
    whiteBoxTests();
    
    return 0;
}       
