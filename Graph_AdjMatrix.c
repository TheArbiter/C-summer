// An adjacency matrix implementation of a graph ADT. 
// This file needs to be modified for lab06

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

//The preorder array. Each index stores the order the vertex was visited.
int *pre = NULL; 
int cnt;
//The spanning tree array. Each index stores the predecessor vertex in the search
int *st = NULL; 

typedef struct graphRep GraphRep; 

//You will need to modify this for task 1 to store information
//about country/capital/population data.
struct graphRep { 
    int nV;       // #vertices 
    int nE;       // #edges 
    int **adj;  // matrix of 0 or 1
    char **countries; //array of countries
    char **capitals; //array of capitals
    long *population; //array of population
}; 

// local checking function 
static int validV(Graph g, Vertex v) { 
    return (v >= 0 && v < g->nV); 
} 

// Create an edge from v to w
// Does allow self loops
Edge mkEdge(Vertex v, Vertex w) { 
    assert(v >= 0 && w >= 0); 
    Edge e = {v,w}; 
    return e; 
} 

//Initialise a new graph
Graph newGraph(int nV) { 
    assert(nV >= 0); 
    int i, j; 
    Graph g = malloc(sizeof(GraphRep)); 
    assert(g != NULL); 
    g->adj = malloc(nV * sizeof(int *)); 
    assert(g->adj != NULL); 
    for (i = 0; i < nV; i++) { 
        g->adj[i] = malloc(nV * sizeof(int)); 
        assert(g->adj[i] != NULL); 
        for (j = 0; j < nV; j++) {
            g->adj[i][j] = 0; 
        } 
    } 
    g->nV = nV; 
    g->nE = 0; 
    
    g->countries = malloc(sizeof(char *) *nV);
    assert(g->countries != NULL);
    g->capitals = malloc(sizeof(char *) *nV);
    assert(g->capitals != NULL);
    g->population = malloc(sizeof(long) *nV);
    assert(g->population != NULL);
    
    return g; 
}

// returns true if there is an edge from v1 to v2
int isAdjacent(Graph g, Vertex v1, Vertex v2){
    assert(g != NULL);
    return(g->adj[v1][v2]);
}

//Insert an edge into a graph
void insertE(Graph g, Edge e) { 
    assert(g != NULL && validV(g,e.v) && validV(g,e.w)); 
    if (!g->adj[e.v][e.w]){ 
        g->adj[e.v][e.w] = 1; 
        g->adj[e.w][e.v] = 1; 
        g->nE++; 
    }
} 

// remove an edge from a graph
void removeE(Graph g, Edge e) { 
   assert(g != NULL && validV(g,e.v)&& validV(g,e.w)); 
   if (g->adj[e.v][e.w]){ 
       g->adj[e.v][e.w] = 0; 
       g->adj[e.w][e.v] = 0; 
       g->nE--; 
   }
} 

//Display the graph
void showGraph(Graph g) { 
    assert(g != NULL); 
    printf("V=%d, E=%d\n", g->nV, g->nE); 
    int i, j; 
    for (i = 0; i < g->nV; i++) { 
        int nshown = 0; 
        for (j = 0; j < g->nV; j++) { 
            if (g->adj[i][j] != 0) { 
                printf("%d-%d ",i,j); 
                nshown++; 
            } 
        } 
        if (nshown > 0) {
            printf("\n");
        } 
    } 
}

// get all the edges from the graph and put them in the array es
// return the number of edges
int edges(Edge es[], int nE, Graph g) { 
     assert(g != NULL && es != NULL && nE > 0); 
     int i, j, n = 0; 
     for (i = 0; i < g->nV; i++) { 
         for (j = i+1; j < g->nV; j++) { 
             if (g->adj[i][j] != 0) { 
                 assert(n < nE); 
                 es[n++] = mkEdge(i,j); 
             } 
         } 
     } 
     return n; 
} 

// returns the maximum number of vertices in the graph
int numV(Graph g){
    assert(g != NULL);
    return g->nV;
}

// Returns the number of edges in the graph
int numE(Graph g){
    assert(g != NULL);
    return g->nE;
}

//       Searching Functions

// Assume we start with cnt = 0 and pre[v] = -1 and
// st[v] = -1 for all v
// Assume we start with Edge(v,v) if v is our start
// vertex
void dfsR(Graph g, Edge e){
    int t, w = e.w;    
    pre[w] = cnt++; 
    st[w] = e.v;       
    for(t=0; t < g->nV; t++) {
        if(g->adj[w][t] != 0) {      // if t is adjacent
            if (pre[t] == -1){          // if t is not visited yet
                dfsR(g, mkEdge(w, t));
            }
        }  
    }
}

void dfSearch(Graph g){
    assert(g != NULL);
    int v=0; cnt = 0;
    pre = malloc(sizeof(int)*g->nV);
    st = malloc(sizeof(int)*g->nV);
    for(v=0;v<g->nV;v++) {
        pre[v] = -1;
        st[v] = -1;
    }  
    for(v=0;v < g->nV; v++){
        if(pre[v] == -1){
            dfsR(g,mkEdge(v,v));
        }
    }
}

void printPre(Graph g){
    int i=0;
    printf("Showing traversal order\n");
    for(i=0;i< g->nV;i++){
        printf("%d %d\n",i,pre[i]);
    }
}

void destroyGraph(Graph g){
    int i;
    assert(g != NULL);
    assert(g->adj != NULL);

    for (i = 0; i < g->nV; i++) {
        assert(g->adj[i] != NULL); 
        free(g->adj[i]);
    } 
    free(g->adj);
    if(pre != NULL){
        free(pre);
    }
    if(st != NULL){
        free(st);
    }
    
    for (i = 0; i < g->nV; i++) {
        assert(g->countries[i] != NULL); 
        free(g->countries[i]);
    } 
    free(g->countries);   
    
    for (i = 0; i < g->nV; i++) {
        assert(g->capitals[i] != NULL); 
        free(g->capitals[i]);
    }
     
    free(g->capitals);   
    free(g->population);   
    free(g);    
}

//IMPLEMENT THESE FUNCTIONS
void showGraphLabels(Graph g){
    assert(g != NULL); 
    printf("V=%d, E=%d\n", g->nV, g->nE); 
    int i, j; 
    for (i = 0; i < g->nV; i++) { 
        int nshown = 0; 
        for (j = 0; j < g->nV; j++) { 
            if (g->adj[i][j] != 0) { 
                printf("%s-%s ",g->countries[i],g->countries[j]); 
                nshown++; 
            } 
        } 
        if (nshown > 0) {
            printf("\n");
        } 
    } 
}

void showData(Graph g){
   int i = 0;
   for(i = 0; i < g->nV; i++){
        showVertexData(g,i);
   }
}

void showVertexData(Graph g,Vertex v){
    printf("%d: %s %s %ld\n",v,g->countries[v],g->capitals[v],g->population[v]);
}

void dfSearch2(Graph g, Vertex * dfsOrder){
   int v;
   
   Vertex *visited = malloc(sizeof(int) *g->nV);
   st = malloc(sizeof(int) *g->nV);
   
   for(v = 0; v < g->nV; v++){
      visited[v] = -1;
      st[v] = -1;
      dfsOrder[v] = -1;
   }
   
   for(v = 0; v < g->nV; v++){
      if(dfsOrder[v] == -1){
         dfsR2(g,mkEdge(v,v),dfsOrder);
      }
   }
   
   free(visited);
}

void dfsR2(Graph g, Edge e, Vertex * dfsOrder){
   int i;
   dfsOrder[cnt++] = e.w;
   Vertex *visited = malloc(sizeof(int) *g->nV);
   visited[e.w] = 1;
   st[e.w] = e.v;
   
   for(i = 0; i < g->nV; i++){
      if((g->adj[e.w][i] != 0) && (visited[i] == -1)){
         dfsR2(g,mkEdge(e.w,i),dfsOrder);
      }
   }
   free(visited);
}

char *getVertexLabel(Graph g, Vertex v){
    return g->countries[v];
}

void setData(Graph g, Vertex v, char *country, char *capital, long population){
    g->countries[v] = strdup(country);
    g->capitals[v] = strdup(capital);
    g->population[v] = population;
}
