typedef int Item;

typedef struct node * link;
struct node{
    Item item;
    link next;
};

void printList(link list);
link newList();
link newNode(Item item);
link insertEnd(link list, link n);
link insertFront(link list, link n);
void freeList(link list);

//Functions
link insertionSort(link list);
