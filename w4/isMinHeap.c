#include "isMinHeap.h"
//To compile, run and test
//gcc -Wall -Werror -O -o testIsMinHeap testIsMinHeap.c isMinHeap.c


//return 1 if the array heap with a sepcified number of items is in heap order 
//You must assume that the heap items are in indexes 1..heapSize and that index 0 
//is empty and not used to store items.
int isMinHeap(int heap[], int heapSize){
    //COMPLETE FOR TASK 3
    int pass = 1;
    int i = 0;
    
    if(heapSize > 1){
       for( i = heapSize; i >1 && pass == 1; i--){
         if(heap[i] < heap[i/2]){
            pass = 0;
         }
       }
    }
    return pass;
}
