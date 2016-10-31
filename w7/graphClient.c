// graphClient.c
// A graph client that reads in and creates a graph from a file
// This needs to be modified to complete lab07
// Written by: Angela Finlayson
// Date: 17/01/09

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Graph.h"
#include "time.h"

// This means that st is a global varaible 
// that was defined in a different file
extern int *st;
extern int cnt;

// THIS NEEDS TO BE COMPLETED FOR TASK 1
// Reads in data from the file with the given filename and creates a newGraph
// The file must be of the format
// numVertices
// v0 v1 v2 v3
// v1 v2 v4
Graph readGraph(char * filename) {
   FILE *fp;
   fp = fopen (filename, "r"); // open data file
   assert (fp != NULL);
  
   int city = 0;
   int dest = 0;
   char c = 0;
   // First line of file has the number of vertices
   int numV;
   Graph g;
   if(fscanf(fp, "%d", &numV) > 0){
      g = NULL;
   }
   g = newGraph(numV);   
   
   // scan through file and insert edges into graph
   int counter = 0;   
   while (counter < numV) {
     if(fscanf(fp, "%d", &city) > 0){
         counter++;
     }
     while (c != '\n') {
          if(fscanf (fp, "%d", &dest) > 0){
             insertE(g, mkEdge(city, dest));
             c = getc(fp);
          }   
     }
     c = 0;
   }   

   int v;
   char name[100];
   char capital[100];
   long population;  
     
   while(fscanf(fp, "%d %s %s %ld", &v, name, capital, &population) == 4) {
       //  TASK 1: ACTUALLY DO SOMETHING WITH THIS DATA!
       setData(g,v,name,capital,population);
   }
   fclose(fp);
   return g;
}

// IMPLEMENT THIS FOR TASK 3
Edge getNextFlight(Graph g, int *dfsOrdered, int *nDiffCountries, Vertex currCountry){
   int n = *nDiffCountries;
   Vertex end = dfsOrdered[n];
   
   if(isAdjacent(g,currCountry,end)){
      *nDiffCountries = *nDiffCountries + 1;
      st[end] = currCountry;
   } else {
      end = st[currCountry];
   }
   
   return mkEdge(currCountry,end);
}

void getFlights(Graph g, int * dfsOrdered){
    int nDiffCountries = 1; 
    int nFlights = 0;
    int currCountry = 0;
       
    while (nDiffCountries < numV(g)){
        Edge nextFlight = getNextFlight(g, dfsOrdered, &nDiffCountries, currCountry);  
        nFlights++;
        printf("Flight %d %s %s\n", nFlights, getVertexLabel(g,nextFlight.v), getVertexLabel(g,nextFlight.w));
	currCountry = nextFlight.w;
    }
    
}

int main(int argc, char * argv[]){
    if (argc < 2){ 
        printf("Incorrect usage: must enter filename\n");
        exit (1);
    }
    Graph g = readGraph(argv[1]);
    showGraph(g);
    printf("\n");

    // TASK 1
    printf("TASK 1\n");
    showGraphLabels(g);
    printf("\n");
    showData(g);
    printf("\n");
    
    // TASK 2
    printf("TASK 2\n");
    int *dfsOrdered = malloc(numV(g) * sizeof(Vertex));
    dfSearch2(g, dfsOrdered);
    int i;
    for(i=0;i< cnt;i++){
        Vertex v = dfsOrdered[i];
        showVertexData(g,v);
    }
    printf("\n");
    
    // TASK 3
    printf("TASK 3\n");
    printf("\nFlying all over the world\n");

    //Uncomment out this line when you get to task 3
    getFlights(g,dfsOrdered);
    
    free(dfsOrdered);    
    destroyGraph(g);    
    return 0;
}
