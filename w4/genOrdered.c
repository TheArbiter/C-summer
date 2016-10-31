#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STRINGSIZE 5

int main(int argc, char *argv[]) {
    int maxString = pow(26,STRINGSIZE);
    int i,j;
    int numElements;

    if(argc <= 1){
        fprintf(stderr, "Incorrect usage ./genOrdered n \n");
        return EXIT_FAILURE;
    } else {
        numElements = atoi(argv[1]);

        if (numElements > maxString) {
            fprintf(stderr,"N too large max is %d\n",maxString);
            return EXIT_FAILURE;
        }
        int d;
        
        // Generate strings
        for (i = 0; i < maxString && i < numElements; i++) {
            d = maxString/26;
            for(j = 0; j < STRINGSIZE; j++){ 
                int offset = (i/d)%26;
                //printf("offset %d\n",offset);
                printf("%c", 'a' + offset);
                d = d/26;
            }
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}

