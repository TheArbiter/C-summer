#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "textbuffer.h"

void compareText(char* textDumped, char* textInsert);
void printTB(TB tb);
void whiteBoxTests(void);

int main (int argc, char* argv[]){

   whiteBoxTests();
   
   /**LEVEL 1 TEST**/
   //test newTB
   printf("Test 1: Test newTB\n");
   TB tb1 = newTB("one\ntwo\nanother\n");
   assert(tb1 != NULL);
   printf("Test 1 passed!\n");
   //printf("print TB\n");
   //printTB(tb1);
   
   //test dumpTB
   printf("Test 2: DumpTB\n");
   compareText(dumpTB(tb1),"one\ntwo\nanother\n");
   printf("Test 2 passed!\n");
   
   //test lines
   printf("Test 3: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb1));     
   assert(linesTB(tb1) == 3);
   printf("Test 3 passed!\n");
   
   //test swap
   printf("Test 4: swapTB\n");
   swapTB(tb1,0,2);
   compareText(dumpTB(tb1), "another\ntwo\none\n");
   printf("Test 4 passed!\n");
   
   //test delete
   printf("Test 5: deleteTB\n");
   deleteTB(tb1,0,1);
   compareText(dumpTB(tb1), "one\n");
   printf("Test 5 passed!\n");
   
   releaseTB(tb1);
   
   /**LEVEL 2 TEST**/
   //test newTB
   printf("Test 6: Test newTB\n");
   TB tb2 = newTB("One\nTwo\nAnother\nPost\n");
   assert(tb2 != NULL);
   printf("Test 6 passed!\n");
   
   //test dumpTB
   printf("Test 7: DumpTB\n");
   compareText(dumpTB(tb2),"One\nTwo\nAnother\nPost\n");
   printf("Test 7 passed!\n");
   
   //test lines
   printf("Test 8: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb2));     
   assert(linesTB(tb2) == 4);
   printf("Test 8 passed!\n");
   
   //test swap
   printf("Test 9: swapTB\n");
   swapTB(tb2,1,2);
   compareText(dumpTB(tb2), "One\nAnother\nTwo\nPost\n");
   printf("Test 9 passed!\n");
   
   //test delete
   printf("Test 10: deleteTB\n");
   deleteTB(tb2,1,2);
   compareText(dumpTB(tb2), "One\nPost\n");
   printf("Test 10 passed!\n");
   
   releaseTB(tb2);

   /**LEVEL 3 TEST**/
   //test newTB
   printf("Test 11: Test newTB\n");
   TB tb3 = newTB("Five\ntwo\nanother\nYoYo\nSIX\n");
   assert(tb3 != NULL);
   printf("Test 11 passed!\n");
   
   //test dumpTB
   printf("Test 12: DumpTB\n");
   compareText(dumpTB(tb3),"Five\ntwo\nanother\nYoYo\nSIX\n");
   printf("Test 12 passed!\n");
   
   //test lines
   printf("Test 13: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb3));     
   assert(linesTB(tb3) == 5);
   printf("Test 13 passed!\n");
   
   //test swap
   printf("Test 14: swapTB\n");
   swapTB(tb3,1,1);
   compareText(dumpTB(tb3), "Five\ntwo\nanother\nYoYo\nSIX\n");
   printf("Test 14 passed!\n");
   
   //test delete
   printf("Test 15: deleteTB\n");
   deleteTB(tb3,2,2);
   compareText(dumpTB(tb3), "Five\ntwo\nYoYo\nSIX\n");
   printf("Test 15 passed!\n");
   
   releaseTB(tb3);

   /**LEVEL 4 TEST**/
   //test newTB
   printf("Test 16: Test newTB\n");
   TB tb4 = newTB("Last\ntest\nWith\nONe\nwoRd\nLinEs\n");
   assert(tb4 != NULL);
   printf("Test 16 passed!\n");
   
   //test dumpTB
   printf("Test 17: DumpTB\n");
   compareText(dumpTB(tb4),"Last\ntest\nWith\nONe\nwoRd\nLinEs\n");
   printf("Test 17 passed!\n");
   
   //test lines
   printf("Test 18: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb4));     
   assert(linesTB(tb4) == 6);
   printf("Test 18 passed!\n");
   
   
   //abort test comment out for now
/*   //test swap
   printf("Test 19: swapTB\n");
   swapTB(tb4,0,6); //should abort
   compareText(dumpTB(tb4), "Last\ntest\nWith\nONe\nwoRd\nLinEs\n");
   printf("Test 19 passed!\n");
   
   //test delete
   printf("Test 20: deleteTB\n");
   deleteTB(tb4,3,1); //should abort
   compareText(dumpTB(tb4), "Last\ntest\nWith\nONe\nwoRd\nLinEs\n");
   printf("Test 20 passed!\n");
  */ 
   releaseTB(tb4);

   /**LEVEL 5 TEST**/
   //test newTB
   printf("Test 21: Test newTB\n");
   TB tb5 = newTB("one two\nthree four\nanother one\n");
   assert(tb5 != NULL);
   printf("Test 21 passed!\n");
   
   //test dumpTB
   printf("Test 22: DumpTB\n");
   compareText(dumpTB(tb5),"one two\nthree four\nanother one\n");
   printf("Test 22 passed!\n");
   
   //test lines
   printf("Test 23: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb5));     
   assert(linesTB(tb5) == 3);
   printf("Test 23 passed!\n");
   
   //test swap
   printf("Test 24: swapTB\n");
   swapTB(tb5,0,2);
   compareText(dumpTB(tb5), "another one\nthree four\none two\n");
   printf("Test 24 passed!\n");
   
   //test delete
   printf("Test 25: deleteTB\n");
   deleteTB(tb5,0,1);
   compareText(dumpTB(tb5), "one two\n");
   printf("Test 25 passed!\n");
   
   releaseTB(tb5);

   /**LEVEL 6 TEST**/
   //test newTB
   printf("Test 26: Test newTB\n");
   TB tb6 = newTB("Lets\ntry numbers\nalso\n21\nSHALL WE\n6\n");
   assert(tb6 != NULL);
   printf("Test 26 passed!\n");
   
   //test dumpTB
   printf("Test 27: DumpTB\n");
   compareText(dumpTB(tb6),"Lets\ntry numbers\nalso\n21\nSHALL WE\n6\n");
   printf("Test 27 passed!\n");
   
   //test lines
   printf("Test 28: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb6));     
   assert(linesTB(tb6) == 6);
   printf("Test 28 passed!\n");
   
   //test swap
   printf("Test 29: swapTB\n");
   swapTB(tb6,1,3);
   compareText(dumpTB(tb6), "Lets\n21\nalso\ntry numbers\nSHALL WE\n6\n");
   printf("Test 29 passed!\n");
   
   //test delete
   printf("Test 30: deleteTB\n");
   deleteTB(tb6,4,5);
   compareText(dumpTB(tb6), "Lets\n21\nalso\ntry numbers\n");
   printf("Test 30 passed!\n");
   
   releaseTB(tb6);

   /**LEVEL 7 TEST**/
   //test newTB
   printf("Test 31: Test newTB\n");
   TB tb7 = newTB("9\n21\n007\n21 17\n");
   assert(tb7 != NULL);
   printf("Test 31 passed!\n");
   
   //test dumpTB
   printf("Test 32: DumpTB\n");
   compareText(dumpTB(tb7),"9\n21\n007\n21 17\n");
   printf("Test 32 passed!\n");
   
   //test lines
   printf("Test 33: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb7));     
   assert(linesTB(tb7) == 4);
   printf("Test 33 passed!\n");
   
   //test swap
   printf("Test 34: swapTB\n");
   swapTB(tb7,0,2);
   compareText(dumpTB(tb7), "007\n21\n9\n21 17\n");
   printf("Test 34 passed!\n");
   
   //test delete
   printf("Test 35: deleteTB\n");
   deleteTB(tb7,1,3);
   compareText(dumpTB(tb7), "007\n");
   printf("Test 35 passed!\n");
   
   //test lines
   printf("Test 36: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb7));     
   assert(linesTB(tb7) == 1);
   printf("Test 36 passed!\n");
   
   
   releaseTB(tb7);

   /**LEVEL 8 TEST**/
   //test newTB
   printf("Test 37: Test newTB\n");
   TB tb8 = newTB("Lucky number 7\n21\nAgent 007\n21 and over\n");
   assert(tb8 != NULL);
   printf("Test 37 passed!\n");
   
   //test dumpTB
   printf("Test 38: DumpTB\n");
   compareText(dumpTB(tb8),"Lucky number 7\n21\nAgent 007\n21 and over\n");
   printf("Test 38 passed!\n");
   
   //test lines
   printf("Test 39: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb8));     
   assert(linesTB(tb8) == 4);
   printf("Test 39 passed!\n");
   
   //test swap
   printf("Test 40: swapTB\n");
   swapTB(tb8,1,3);
   compareText(dumpTB(tb8), "Lucky number 7\n21 and over\nAgent 007\n21\n");
   printf("Test 40 passed!\n");
   
   // abort test comment out for now
   /*//test delete
   printf("Test 41: deleteTB\n");
   deleteTB(tb8,1,5); //should abort because out of range
   compareText(dumpTB(tb8), "Lucky number 7\n21 and over\nAgent 007\n21\n");
   printf("Test 41 passed!\n");
   */
   releaseTB(tb8);

   //* copying all the previous test text above to test for merge, copy and paste *//
 
   /**LEVEL 9 TEST**/
   //test newTB
   printf("Test 42: Test newTB1\n");
   TB tb9 = newTB("one\ntwo\nanother\n");
   assert(tb9 != NULL);
   printf("Test 42 passed!\n");
   //printf("print TB\n");
   //printTB(tb9);
   
   printf("Test 43: Test newTB2\n");
   TB tb10 = newTB("One\nTwo\nAnother\nPost\n");
   assert(tb10 != NULL);
   printf("Test 43 passed!\n");
   //printTB(tb10);
   
   //test paste
   printf("Test 44: pasteTB\n");
   pasteTB(tb9,0,tb10);
   compareText(dumpTB(tb9), "One\nTwo\nAnother\nPost\none\ntwo\nanother\n");
   printf("Test 44 passed!\n");
     
   //test copy
   printf("Test 46: Test copyTB\n");
   TB tb11 = copyTB(tb10,1,2);
   assert(tb11 != NULL);
   printf("Test 46 passed!\n"); 
   
   //test lines
   printf("Test 45: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb9));
   //printf("Tb lines = %d \n",linesTB(tb10));
   //printf("Tb lines = %d \n",linesTB(tb11));     
   assert(linesTB(tb9) == 7);
   assert(linesTB(tb10) == 4);
   assert(linesTB(tb11) == 2);
   printf("Test 45 passed!\n");
   
   //test merge
   printf("Test 47: mergeTB\n");
   mergeTB(tb10,0,tb11);
   compareText(dumpTB(tb10), "Two\nAnother\nOne\nTwo\nAnother\nPost\n");
   printf("Test 47 passed!\n");
   
   //test lines
   printf("Test 48: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb10));
   assert(linesTB(tb10) == 6);
   printf("Test 48 passed!\n");

   releaseTB(tb9);
   releaseTB(tb10);
   /* Notes to remember 
      cant use compareText on second tb after merge there will be error in 
      valgrind even though it will work normally without it
      Also since the second tb will be released in the merge function we dont
      release it here valgrind will give errors invalid free
   */
   
   /**LEVEL 10 TEST**/
   //test newTB
    
   printf("Test 49: Test newTB1\n");
   TB tb12 = newTB("Five\ntwo\nanother\nYoYo\nSIX\n");
   assert(tb12 != NULL);
   printf("Test 49 passed!\n");
   
   printf("Test 50: Test newTB2\n");
   TB tb13 = newTB("Last\ntest\nWith\nONe\nwoRd\nLinEs\n");
   assert(tb13 != NULL);
   printf("Test 50 passed!\n");
   
   //test paste
   printf("Test 51: pasteTB\n");
   pasteTB(tb12,2,tb13);
   compareText(dumpTB(tb12), "Five\ntwo\nLast\ntest\nWith\nONe\nwoRd\nLinEs\nanother\nYoYo\nSIX\n");
   printf("Test 51 passed!\n");
     
   //test copy
   printf("Test 52: Test copyTB\n");
   TB tb14 = copyTB(tb13,1,4);
   assert(tb11 != NULL);
   printf("Test 52 passed!\n"); 
   
   //test lines
   printf("Test 53: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb13));     
   assert(linesTB(tb12) == 11);
   assert(linesTB(tb14) == 4);
   printf("Test 53 passed!\n");
   
   //test cut
   printf("Test 54: cutTB\n");
   TB tb15 = cutTB(tb12,2,6);
   compareText(dumpTB(tb15), "Last\ntest\nWith\nONe\nwoRd\n");
   printf("Test 54 passed!\n");
   
   //test lines
   printf("Test 55: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb13));     
   assert(linesTB(tb12) == 6);
   assert(linesTB(tb15) == 5);
   printf("Test 55 passed!\n");
   
   //test merge
   printf("Test 56: mergeTB\n");
   mergeTB(tb14,2,tb15);
   compareText(dumpTB(tb14), "test\nWith\nLast\ntest\nWith\nONe\nwoRd\nONe\nwoRd\n");
   printf("Test 56 passed!\n");
   
   //test replace text
   printf("Test 57: replace text\n");
   replaceText(tb14,"st","ST's");
   compareText(dumpTB(tb14), "teST's\nWith\nLaST's\nteST's\nWith\nONe\nwoRd\nONe\nwoRd\n");
   printf("Test 57 passed!\n");
   
   //test lines
   printf("Test 58: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb13));     
   assert(linesTB(tb14) == 9);
   printf("Test 58 passed!\n");
   
   releaseTB(tb12);
   releaseTB(tb13);
   releaseTB(tb14);
   
   /**LEVEL 11 TEST**/
   //test newTB    
   printf("Test 59: Test newTB1\n");
   TB tb16 = newTB("one two\nthree four\nanother one\n");
   assert(tb16 != NULL);
   printf("Test 59 passed!\n");
   
   printf("Test 60: Test newTB2\n");
   TB tb17 = newTB("Lets\ntry numbers\nalso\n21\nSHALL WE\n6\n");
   assert(tb17 != NULL);
   printf("Test 60 passed!\n");
   
   //test paste
   printf("Test 61: pasteTB\n");
   pasteTB(tb16,2,tb17);
   compareText(dumpTB(tb16), "one two\nthree four\nLets\ntry numbers\nalso\n21\nSHALL WE\n6\nanother one\n");
   printf("Test 61 passed!\n");
     
   //test copy
   printf("Test 62: Test copyTB\n");
   TB tb18 = copyTB(tb17,1,5);
   assert(tb18 != NULL);
   printf("Test 62 passed!\n"); 
   
   //test lines
   printf("Test 63: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb13));     
   assert(linesTB(tb16) == 9);
   assert(linesTB(tb18) == 5);
   printf("Test 63 passed!\n");
   
   //test cut
   printf("Test 64: cutTB\n");
   TB tb19 = cutTB(tb18,0,1);
   compareText(dumpTB(tb19), "try numbers\nalso\n");
   printf("Test 64 passed!\n");
   
   //test lines
   printf("Test 65: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb13));     
   assert(linesTB(tb18) == 3);
   assert(linesTB(tb19) == 2);
   printf("Test 65 passed!\n");

   //test merge
   printf("Test 66: mergeTB\n");
   mergeTB(tb19,2,tb16);
   compareText(dumpTB(tb19), "try numbers\nalso\none two\nthree four\nLets\ntry numbers\nalso\n21\nSHALL WE\n6\nanother one\n");
   printf("Test 66 passed!\n");
   
   //test replace text
   printf("Test 67: replace text\n");
   replaceText(tb19,"e","3");
   compareText(dumpTB(tb19), "try numb3rs\nalso\non3 two\nthr33 four\nL3ts\ntry numb3rs\nalso\n21\nSHALL WE\n6\nanoth3r on3\n");
   printf("Test 67 passed!\n");
   
   //test lines
   printf("Test 68: linesTB\n");
   //printf("Tb lines = %d \n",linesTB(tb13));     
   assert(linesTB(tb19) == 11);
   printf("Test 68 passed!\n");
   
   releaseTB(tb17);
   releaseTB(tb18);
   releaseTB(tb19);
   
   return 0;
}

void compareText(char* textDumped, char* textInsert){
   if(strcmp(textDumped,textInsert) == 0){
      printf("Test Passed, You are Awesome!\n");
   } else {
      printf("Test Failed :( \n");
   }
   
   free(textDumped);
}

void printTB(TB tb){
   char* text;
   text = dumpTB(tb);
   printf("%s\n",text);
   free(text);
}
