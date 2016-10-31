// Implement the deleteLargest function below
//
// Compile and test the function using
// gcc -Wall -Werror -O -o deleteLargest deleteLargest.c deleteLargestTest.o
// ./deleteLargest


#include <stdio.h>
#include <stdlib.h>
#include "deleteLargest.h"

typedef struct _treeNode {
  Item item;
  treeLink left, right;
} treeNode;


//Delete the largest item in the tree and return the resulting tree
//You must free the memory of the node that is deleted
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
//You may assume there are no duplicates in the tree
treeLink deleteLargest (treeLink tree) {
      // CHANGE THE CODE HERE
   treeLink curr = tree;
  
   if (curr == NULL){
      return curr;
   } 
   
   //traverse the tree
   if(curr->right != NULL){
      curr->right = deleteLargest(curr->right);
 //     return tree; 
  
   // no right subtree which means you have hit the max
   } else {
      curr = tree->left;
      free(tree);
//      return curr;
   }
   return curr;
}

