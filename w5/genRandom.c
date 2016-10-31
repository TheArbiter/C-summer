#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char * argv[]){
     int size = 10;
     int i;
     srand(time(NULL));
     if(argc > 1){
       size = atoi(argv[1]);
     }
     
     printf("%d\n",size);
     for(i =0; i < size; i++){
       printf("%d\n",rand()); //0..RAND_MAX
     }
   
     return 0;
}
