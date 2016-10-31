#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"

int main (int argc, char *argv[]){
   printf("Testing BST\n");
   
   treelink t = NULL;
   treelink s = NULL;
      
   t = insertTreeNode(t,10);
   insertTreeNode(t,20);
   insertTreeNode(t,5);
   insertTreeNode(t,30);
   insertTreeNode(t,15);
   insertTreeNode(t,12);
   
   printf("Tree bellow\n");
   showTree(t);
   
   printf("number of leaves is %d\n",countLeaves(t));
   printf("Size of tree is %d\n",size(t));
   printf("Number of even : %d\n",countIf(t,isEven));
   printf("Number of odd : %d\n",countIf(t,isOdd));
   printf("Number of negative : %d\n",countIf(t,isNegative));
   

   s = insertTreeNode(s,15);
   insertTreeNode(s,-2);
   insertTreeNode(s,5);
   insertTreeNode(s,30);
   insertTreeNode(s,8);
   insertTreeNode(s,-7);
   insertTreeNode(s,-6);
   insertTreeNode(s,25);
   
   printf("Tree bellow\n");
   showTree(s);
   
   printf("number of leaves is %d\n",countLeaves(s));
   printf("Size of tree is %d\n",size(s));
   printf("Number of even : %d\n",countIf(s,isEven));
   printf("Number of odd : %d\n",countIf(s,isOdd));
   printf("Number of negative : %d\n",countIf(s,isNegative));


   return 0;
}
