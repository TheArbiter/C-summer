//A complex Item with a key and a value
#include <string.h>

typedef char * Key;    //Can change key type
typedef char * Value; //Can change 

#define compareKeys(A,B) (strcmp((A), (B)))

unsigned int hashFunction( Key k, unsigned int tableSize ) ;
