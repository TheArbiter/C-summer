#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "textbuffer.h"

#define TRUE 1
#define FALSE 0

typedef char *Line;
typedef struct _node *link;

typedef struct _node {
  Line line;
  link next;
  link prev;
} node;

struct textbuffer {
   int lineCount;
   int CharCount;
   link first;
   link last;
};

//my own functions
void freeNode(link Node);
void posCheck(TB tb, int pos1, int pos2);
void singlePosCheck(TB tb, int pos);
void rangeCheck(int from, int to);
Line repstr(Line str, Line orig, Line rep);

link newNode(char text[]) {
	
	link n = malloc(sizeof(node));
	assert(n != NULL);
	n->line = strdup(text);
	n->next = NULL;
   n->prev = NULL;
	return n;
}

TB createTB () {
   TB t = malloc(sizeof(struct textbuffer));
   assert(t != NULL);
   t->first = NULL;
   t->last = NULL;
   t->lineCount = 0;
   t->CharCount = 0;
   
   return t;
}

TB newTB (char text[]){
   int i = 0;
   int j = 0;
   
   int buffersize = strlen(text);
   link temp = NULL;
   link curr = NULL;
   
   // initialise TB
   TB newT = createTB();
   // allocate memory
   char* string = malloc(sizeof(char)*(buffersize+1));// +1 for the \0
   assert (string != NULL);
   
   for(i = 0; i < buffersize; i++){
      if(text[i] == '\n' || text[i] == '\0'){
         string[j] = '\0';
         temp = newNode(string);
         
         if(curr == NULL){
            // first line
            newT->first = temp;
         } else {
            curr->next = temp;
         }
         newT->last = temp;
         temp->prev = curr;
         newT->lineCount++;
         newT->CharCount++;
         curr = temp;
         j = 0;
      } else {
         string[j] = text[i];
         newT->CharCount++;
         j++;
      }
   }
   free(string);
   
   return newT;
}

void releaseTB (TB tb){
   if(tb != NULL){
      link curr = NULL;
      link temp = NULL;
      
      curr = tb->first;
      while(curr !=NULL){
         temp = curr->next;
         freeNode(curr);
         curr = temp;
      }
      tb->first = NULL;
      tb->last = NULL;
   }
   free(tb);
}

void freeNode (link Node){
   if(Node!=NULL){
      free(Node->line);
      free(Node);
   }
}


char *dumpTB (TB tb){
   link curr = NULL;
   Line text = NULL;
   int i = 0;
   int j = 0;
   
   if(tb !=NULL && tb->lineCount > 0){
      text = malloc(sizeof(char) * (tb->CharCount + 1));
      
      for(curr = tb->first; curr != NULL; curr = curr->next){
         for(j = 0; curr->line[j] != '\0';j++){
            text[i] = curr->line[j];
            i++;
         }
         text[i] = '\n'; //add new line
         i++; // now increment the index
      }
      text[i] = '\0'; // now add the null terminator to indicate end of line
   }
   return text;
}

int linesTB (TB tb){
   return tb->lineCount;
}

void swapTB (TB tb, int pos1, int pos2){
   link temp1 = NULL;
   link temp2 = NULL;
   link curr = NULL;
   int i = 0;
   Line middle;
   
   //check range
   posCheck(tb,pos1,pos2);

   //checks if both are not the same
   //if they are do nothing
   if(pos1 != pos2){
      for(i = 0,curr = tb->first; curr != NULL; curr = curr->next, i++){
            // for first swap
            if(i == pos1){
               temp1 = curr;
            }
            // for second swap
            if(i == pos2){
               temp2 = curr;
            }
      }
      
      //this is where the swap takes place
      middle = temp1->line;
      temp1->line = temp2->line;
      temp2->line = middle;
   
   }
   
}

void deleteTB (TB tb, int from, int to){
   
   //do the checks
   posCheck(tb,from,to);
   rangeCheck(from,to);
   
   link curr = NULL;
   link temp1 = NULL;
   link temp2 = NULL;
   link del = NULL;
   int i = 0;
   int f = FALSE;
   
   for(i = 0,curr = tb->first; (i<=to && i< tb->lineCount); curr = curr->next, i++){
      // for first delete
      if(i == from){
         temp1 = curr;
      }
      // for second delete
      if(i == to){
         temp2 = curr;
      }      
   }
   
   //The special set and where we do our delete
   if(from == 0 && (to == (tb->lineCount -1))){ 
      //delete everything
      tb->first = NULL;
      tb->last = NULL;
   } else if (from == 0 && (to < (tb->lineCount -1))){
      //delete from the start
      tb->first = temp2->next; //change of header
      temp2->next->prev = NULL; 
   } else if (from > 0 && (to == (tb->lineCount -1))){
      //delete until the end
      tb->last = temp1->prev; // change of tail
      temp1->prev->next = NULL;
   } else {
      //this is where the delete takes place if not in special case
      //changing the pointers
      temp1->prev->next = temp2->next;
      temp2->next->prev = temp1->prev;
   }
   
   // got to free memory
   curr = temp1;
   while(curr != NULL && f == FALSE){
      if(curr == temp2){
         f = TRUE; //exit case
      }
      del = curr->next;
      tb->lineCount--;
      tb->CharCount -= strlen(curr->line) - 1; 
      freeNode(curr);
      curr = del;
   }
}

void mergeTB (TB tb1, int pos, TB tb2){

   // check pos 
   singlePosCheck(tb1,pos); 
   
   int i = 0;
   link curr = NULL; //tb1
   
   // check if they arent the same
   if(tb1 != tb2){
      curr = tb1->first;
      while( i < pos && pos != tb1->lineCount ){
         i++;
         curr = curr->next;
      }      
      //now for all the scenarios
      //pos being 0 then tb2 will be put at the head
      if(pos == 0){
         curr->prev = tb2->last; //do the 
         tb2->last->next = curr; // pointer change
         tb1->first = tb2->first; //now update the head
      } else if (pos == tb1->lineCount){
         //pos being the last so tb2 will be put at the end of tb1
         tb1->last->next = tb2->first; //make tb1 last point to tb2 head
         tb2->first->prev = tb1->last; // make tb2 prev point to tb1 last
         tb1->last = tb2->last; // now update the tail
      } else {
         //in between case
         curr->prev->next = tb2->first; //make tb1 pos prev pointer point to tb2 head
         tb2->first->prev = curr->prev; //now make tb2 head point to tb1 pos prev
         tb2->last->next = curr; //make tb2 last now point to tb1 pos
         curr->prev = tb2->last; //make tb1 pos point to tb2 tail
      }
      //now to update the numbers
      tb1->lineCount += tb2->lineCount;
      tb1->CharCount += tb2->CharCount;
      
      //now to get rid of tb2
      tb2->first = NULL; // mmm looks like ive got to make the pointers
      tb2->last = NULL;  // of tb2 null before calling release even though
      releaseTB(tb2);   // its done in release
   }   
}

// this is basically a copy tb with the one less pos
// then just have to use merge
void pasteTB (TB tb1, int pos, TB tb2){
   
   //check pos
   singlePosCheck(tb1,pos);
   
   // create a copy of tb2
   TB new = copyTB(tb2,0,tb2->lineCount-1);
   //call merge to do the paste work
   mergeTB(tb1,pos,new);
}

TB cutTB (TB tb, int from, int to){
   
   //pos check 
   posCheck(tb,from,to);
   
   //create new tb2
   TB new = NULL;  
    
   if(to < from){
      return NULL;
   } else {
      new = copyTB(tb,from,to);
      //then delete the lines that were cut from tb1
      deleteTB(tb,from,to);
   }
   
   return new;
}

TB copyTB (TB tb, int from, int to){
   
   //pos check
   posCheck(tb,from,to);
   
   if(to < from){
      return NULL;
   } 
   
   link curr,temp = NULL;
   int i,bufferSize = 0;
   
   TB new = createTB();
   
   for(i = 0, curr = tb->first; i <= to ; curr = curr->next, i++){
      if(i >= from){
         temp = newNode(curr->line);
         bufferSize = (strlen(temp->line) + 1);
         // make head
         if(new->first == NULL){
            new->first = temp;
            new->last = temp;
         } else {
            new->last->next = temp;
            temp->prev = new->last;
            new->last = temp;
         }
         new->lineCount++;
         new->CharCount += bufferSize; 
  
      }      
   }
   return new;
}

void replaceText (TB tb, char* str1, char* str2){
   
   link curr = NULL;
   Line temp = NULL;
   int count,old = 0;
   
   for(curr = tb->first; curr != NULL; curr = curr->next){
      old = strlen(curr->line) + 1;
      temp = curr->line;
      curr->line = repstr(curr->line,str1,str2);
      free(temp);
      count = strlen(curr->line) + 1;
      tb->CharCount = ( tb->CharCount + count - old );
   }
}

Line repstr(Line str, Line orig, Line rep){
   static char buffer[4096];
   static char temp[4096];
   int i,o = 0;
   Line p;
    
   strcpy(buffer,str);
   
   while( (p = strstr(buffer + o,orig)) != NULL){
      i = p-buffer;
      o = i + strlen(rep);
      strcpy(temp,rep);
      strcat(temp,&buffer[i+strlen(orig)]);
      sprintf(&buffer[i],"%s",temp);    
   }
   return strdup(buffer);
}

// used for delete and swap
void posCheck(TB tb, int pos1, int pos2){
   if(pos1 < 0 || pos2 < 0 || pos1 > (tb->lineCount -1) || pos2 > (tb->lineCount -1)){
      fprintf(stderr,"Pos1 or Pos2 are out of range of the textbuffer\n");
      abort();
   }
}

// used for merge and paste
void singlePosCheck(TB tb, int pos){
   if(pos < 0 || pos > tb->lineCount){
      fprintf(stderr,"Pos out of range of the textbuffer\n");
      abort();
   }
}

void rangeCheck(int from, int to){
   if(from > to){
      fprintf(stderr,"from is greater than to\n");
      abort();
   }
}

void whiteBoxTests(void){

   printf("White Box Tests\n");   
   printf("Test newTB\n");
   TB whiteTest = newTB("Lets\ntry numbers\nalso\n21\nSHALL WE\n6\n");
   assert(whiteTest != NULL);
   
   printf("%s\n",dumpTB(whiteTest));
   assert(whiteTest->lineCount == 6);
   printf("line count: %d\n",whiteTest->lineCount);
   assert(whiteTest->first->line = "Lets");
   printf("first line: %s\n",whiteTest->first->line);
   assert(whiteTest->last->line = "6");
   printf("last line: %s\n",whiteTest->last->line);
   
   printf("Swap line 4 with 5...\n");   
   swapTB(whiteTest,4,5);
   printf("%s\n",dumpTB(whiteTest));
   printf("last line: %s\n",whiteTest->last->line);
   
   printf("Copy TB from line 1 to 4...\n");   
   TB copy = copyTB(whiteTest,1,4);
   printf("%s\n",dumpTB(copy));
   
   printf("Cut TB1 from line 2 to 3...\n");   
   TB cutnew = cutTB(copy,2,3);
   printf("%s\n",dumpTB(cutnew));
   printf("line count: %d\n",cutnew->lineCount);
   assert(cutnew->lineCount == 2);
   
   printf("Paste new Cut TB onto old TB into pos 1..\n");   
   pasteTB(whiteTest,1,cutnew);
   printf("%s\n",dumpTB(whiteTest));
 
   printf("Delete lines 2 to 4 in old TB..\n");   
   deleteTB(whiteTest,2,4);
   printf("%s\n",dumpTB(whiteTest));
 
   printf("Replace 21 with Twenty One..\n");   
   replaceText(whiteTest,"21","Twenty One");
   printf("%s\n",dumpTB(whiteTest));
   assert(whiteTest->first->line = "Lets");
   printf("first line: %s\n",whiteTest->first->line);
   assert(whiteTest->last->line = "SHALL WE");
   printf("last line: %s\n",whiteTest->last->line);
 
   printf("Merge old TB with TB1 in pos 0..\n");   
   mergeTB(copy,0,whiteTest);
   printf("%s\n",dumpTB(copy));
 
   releaseTB(copy);
   releaseTB(cutnew);
   printf("TB Released\n");
   printf("White box tests end\n");
   
}