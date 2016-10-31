// Implement the deleteLargest function below
//
// Compile and test the function using
// gcc -Wall -Werror -o deleteLargest deleteLargest.c deleteLargestTest.o
// ./deleteLargest


#include <stdio.h>
#include <stdlib.h>
#include "deleteLargest.h"

typedef struct _treeNode {
  Item item;
  treeLink left, right;
} treeNode;


//Delete the largest item in the tree and return the resulting tree
//If the tree is empty simply return the empty tree
//For example
/*
//       5                 5
/      / \               /  \
//     2   7        ---> 2   7
//        / \                /
//       6   8              6
//
*/

treeLink deleteLargest (treeLink tree) {
      // CHANGE THE CODE HERE
     if(tree == NULL){
         return NULL;
     }
     treeLink prev = NULL;
     treeLink curr = tree;

     while(curr->right != NULL){
         prev = curr;
         curr = curr->right;
     }
     printf("Del %d\n",curr->item);
     if(prev == NULL){
         tree = curr->left;
         free(curr);
         return tree;\
     }
     prev->right = curr->left;
     free(curr);
     return tree;
}

