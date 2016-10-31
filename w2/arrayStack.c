//An array based implementation of a stack

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "Item.h"
#include "Stack.h"
#include "assert.h"

#define DEFAULT_SIZE 10

struct stackImp{
    Item * items;
    int top;
    int maxSize;
};

//A stack is created with a default initial size of 10
Stack createStack (void){
    Stack s = malloc(sizeof(struct stackImp)); 
    assert(s != NULL);
    s->items = malloc(DEFAULT_SIZE * sizeof(Item));
    assert(s->items != NULL);
    s->top = 0; 
    s->maxSize = DEFAULT_SIZE;
    return s;
}

void destroyStack(Stack stack){
    assert(stack != NULL);
    free(stack->items);
    free(stack);
}

//You need to modify this
void push (Stack stack, Item item){ 
    assert(stack != NULL);
    
    // if array is full double array size
    if(stack->top == stack->maxSize){
      stack->items = realloc(stack->items,2*stack->maxSize*sizeof(Item));
      stack->maxSize = 2*stack->maxSize;
      assert(stack->items !=NULL); // check if realloc worked
    }    
    
    stack->items[stack->top] = item;
    stack->top++;  
}

//You need to modify this
Item pop (Stack stack){ 
    assert(stack != NULL);
    if(stack->top == 0){
        printf("Warning!! Stack Underflow\n");
        destroyStack(stack);
        abort();
    }
    if((stack->top < stack->maxSize/4) && (stack->maxSize > DEFAULT_SIZE)){
        stack->items = realloc(stack->items,(stack->maxSize/2)*sizeof(Item));
        stack->maxSize = stack->maxSize/2;
        assert(stack->items !=NULL); // check if realloc worked
    }
    stack->top--;
    return stack->items[stack->top];
}

int stackSize(Stack stack){
    assert(stack != NULL);
    return stack->top;
}

//You need to write these
void whiteBoxTests(void){
    printf("White box tests\n");
    
    Stack stack = createStack();
    Item i;
    
    //push items onto the stack
    for(i = 0;i < DEFAULT_SIZE;i++){
        printf("pushing %d onto stack\n",i);
        push(stack,i);
    }
    
    //check current stack size and max size
    printf("Stack size is %d\n",stackSize(stack));
    printf("Stack Max-Size is %d\n",stack->maxSize);
    assert(stack->top == 10);
    assert(stack->maxSize == 10);
    
    //push one more to double stack max size
    printf("pushing one more item\n");
    push(stack,i);
    
    //check stack max size and stack size
    printf("Stack size is %d\n",stackSize(stack));
    printf("Stack Max-Size is %d\n",stack->maxSize);
    assert(stack->top == 11);
    assert(stack->maxSize == 20);
    
    //pop things out of the stack   
    for(i = 0; i < DEFAULT_SIZE + 1; i++){
        printf("popping %d from stack\n",pop(stack));           
    }
    
    //just to check if everything was popped off
    printf("Stack top %d\n",stack->top);
    assert(stack->top == 0);
    
    // check if stack max size was halved but not bellow the DEFAULT_SIZE
    printf("Stack Max-Size is %d\n",stack->maxSize);
    assert(stack->maxSize == 10);
    
    //push alot of items
    for(i = 0; i < (DEFAULT_SIZE * 3) + 1; i++){
        printf("Pushing %d onto stack, stack max size is %d\n",i,stack->maxSize);
        push(stack,i);
    }
    assert(stack->top == 31);
    assert(stack->maxSize == 40);
 
    printf("going to pop until program aborts\n");
    //now pop until the program aborts
    for(i = 0; i <(DEFAULT_SIZE * 3) + 2; i++){
        printf("popping %d from stack\n",pop(stack));   
    }
}
