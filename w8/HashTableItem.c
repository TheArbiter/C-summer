#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Item.h"
//This hashFunction is taken from program 14.2 from Sedgewick
unsigned int hashFunction( Key k, unsigned int tableSize ) {
        unsigned int hash = 0;
        int length = strlen( k );
        int i;
        int a = 31415;
        int b = 27183;
        for( i = 0; i < length; i++, a = a*b % (tableSize -1) ) {
            hash = (a*hash + k[i]) %tableSize;
        }
        hash = hash % tableSize;
        return hash;
}
