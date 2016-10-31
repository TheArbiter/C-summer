#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define STRINGLENGTH 5

int main(int argc, char *argv[]) {
    int i, j, numElements;

    if(argc <= 1){
        fprintf(stderr, "Incorrect usage ./genRandom n \n");
        return EXIT_FAILURE;
    } else {
        numElements = atoi(argv[1]);


        // Generate random data
        srand(time(NULL)); // Seed random number generator
        for (i = 0; i < numElements; i++) { // Randomly generate data
            for (j = 0; j < STRINGLENGTH; j++) { // Randomly STRINGLENGTH chars
                // Generate a random number between 0 and 25 and add to 'a'
                printf("%c", 'a' + (int) rand()%26);
            }
            printf("\n");
        }
    }
    
    return EXIT_SUCCESS;
}
