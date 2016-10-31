#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void quickSort (int items[],int l, int r);
void quickSortMT (int a[], int l, int r);
void quickSortRand (int a[], int l, int r);
void swap (int index1, int index2, int items[]);

int main (int argc,char *argv[]) {
    int size;
    int i;

    srand(time(NULL)); //creates a 
	//char command = argv[1];
    printf("Enter data size:");
    scanf("%d",&size);
	//scanf("%s",&command);
    int * a = malloc(size * sizeof(int));   
    printf("Enter data:\n"); 
    for(i=0;i<size;i++){
	    scanf("%d",&a[i]);
    }

    if (argc > 1){	
		if(strcmp(argv[1],"-pn") == 0){
		 	quickSort(a,0,size-1);
			printf("Sorted with naive pivot:\n");    
		} else if (strcmp(argv[1],"-pm") == 0){
			quickSortMT(a,0,size-1);
			printf("Sorted with median of three pivot:\n");
		} else if (strcmp(argv[1],"-pr") == 0){
			quickSortRand(a,0,size-1);
			printf("Sorted with randomised pivot:\n");
		}

		if(! (argc == 3 && strcmp(argv[2],"-q") == 0)){    
			for(i=0;i<size;i++){
				printf("%d ",a[i]);
			}
			printf("\n");
		}
    }
    free(a);
    return 0;
}

int partition(int a[], int l, int r);
int partitionRand(int a[], int l, int r);

void quickSort (int a[], int l, int r){         	
   int i;  
   if  (r <= l) {
       return;
   } 
   i = partition (a, l, r);  
   quickSort (a, l, i-1);  
   quickSort (a, i+1, r);
}

void quickSortMT(int a[], int l, int r){         	
   int i;  
   if  (r <= l) {
       return;
   } 
   if(r-l > 1){
       int mid = (r+l)/2;

       swap(r-1,mid,a);
       if(a[r-1] < a[l]){
           swap(r-1,l,a);
       }
       if(a[r] < a[l]){
           swap(r,l,a);
       }
       if(a[r] < a[r-1]){
           swap(r,r-1,a);
       }
     
       i = partition(a,l+1,r-1);
   } else {
       i = partition(a,l,r);  
   }  
 
   quickSortMT (a, l, i-1);  
   quickSortMT (a, i+1, r);
}

void quickSortRand(int a[], int l, int r){
   int i;  
   if  (r <= l) {
       return;
   } 
   
   i = partitionRand (a, l, r);  
   quickSortRand (a, l, i-1);  
   quickSortRand (a, i+1, r);
}

int partition (int a[], int l, int r) {   
   	int i = l-1;
   	int j = r;   
   	int pivot = a[r]; //rightmost is pivot  	
	for(;;) {   
		while ( a[++i] < pivot) ;    
		while ( pivot <  a[--j] && j != l);
		if (i >= j) { 
      		break;
    	}    
		swap(i,j,a);  
   	}
    //put pivot into place  
    swap(i,r,a);  
    return i; //Index of the pivot
}

int partitionRand(int a[], int l, int r){
   int i = l-1;
   int j = r;
   int pivotRand = ((rand() % (r-l)) + l + 1);
   int pivot = a[pivotRand]; //random pivot
   swap(pivotRand,r,a); // swapping random pivot to the end

   for(;;){
      while( a[++i] < pivot);
      while( pivot < a[--j] && j != l);
      if(i >= j){
         break;
      }
      swap(i,j,a);
   }
   //put pivot into place
   swap(i,r,a);
   return i;
}
void swap(int index1, int index2, int items[]){
    int tmp;
    tmp = items[index1];
    items[index1] = items[index2];
    items[index2] = tmp;
}

