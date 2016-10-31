
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "isMinHeapOrdered.h"
//To compile, run and test
//gcc -Wall -Werror -O -o testIsMinHeapOrdered testIsMinHeapOrdered.c isMinHeapOrdered.c
//./testIsMinHeapOrdered

//returns 1 if the tree-based heap is in min-heap order.
//You may assume an empty tree is in min-heap order and so 
//is a single node.
int isMinHeapOrdered(Link n){
    int pass = 1;
    
    if(n != NULL){
      if((n->left != NULL && n->item > n->left->item) || (n->right != NULL && n->item > n->right->item)){
         pass = 0;
      } else {
         pass = isMinHeapOrdered(n->left);
         if (pass != 0){
            pass = isMinHeapOrdered(n->right);
         }
      }  
    }
    return pass;
}


