// ADT Interface Functions:
typedef struct hashTable *HashTable;

HashTable createHashTable( unsigned int size );
        
void addToHashTable( HashTable table, Key key, Value value );
void updateHashTable( HashTable table, Key key, Value value );

Value lookupInHashTable( HashTable table, Key key );
Value removeFromHashTable( HashTable table, Key key );
int isKeyInHashTable( HashTable table, Key key );

void destroyHashTable( HashTable table );


void showHashStats(HashTable table);
