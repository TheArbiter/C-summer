/* 
  Graph.c
   
  
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

struct graphRep { 
  int V; 
  int E; 
  int **adj; //an array of adjacency matrix 
  char ** vLabels;
  char * types; 
}; 

static int GRAPHvalidEdge(Graph g, Edge e);
static int GRAPHvalidVertex(Graph g, Vertex v);

// Create an edge from v to w 
Edge mkEdge(Vertex v, Vertex w, int weight) { 
    assert(v >= 0 && w >= 0); 
    Edge e = {v,w,weight}; 
    return e; 
} 

//Initialise a new graph
Graph newGraph(int nV) { 
    //printf("number of nV is %d\n",nV);
    int i,j,v = 0; 
    // creating the graph
    Graph G;
    
    G = malloc(sizeof(struct graphRep));
    assert(G != NULL);
    
    G->V = nV; //set number of verticies 
    G->E = 0;  //set number of edges
    
    G->adj = malloc(nV * sizeof(int *));
    assert(G->adj != NULL);
    
    //making the adjacency matrix
    for (v = 0; v < nV; v++){
        G->adj[v] = malloc(nV * sizeof(int));
        assert(G->adj[v] != NULL);
        for(j = 0; j < nV; j++){
            G->adj[v][j] = 0;
        }
    }
    G->types = malloc(nV *sizeof(char *));
    assert(G->types != NULL);
    G->vLabels = malloc(nV * sizeof(char *));
    assert(G->vLabels != NULL);
    for(i = 0; i < G->V; i++){
        G->vLabels[i] = NULL;
    }
    
    return G;
}

static int GRAPHvalidEdge(Graph g, Edge e){
    assert(g != NULL);
    return (e.v >= 0 && e.v < g->V && 
            e.w >= 0 && e.w < g->V );
}

static int GRAPHvalidVertex(Graph g, Vertex v){
    assert(g != NULL);
    return (v >= 0 && v < g->V);
}
//Insert an edge into a graph
//the edge must not be inserted if
//     the vertices are not valid
//     it would create a self loop
//     there already exists an edge between the vertices
void insertE(Graph g, Edge e) { 
    
    if(GRAPHvalidEdge(g,e) && e.v != e.w){
        
        g->adj[e.v][e.w] = e.weight;
        g->adj[e.w][e.v] = e.weight; 
        g->E++;
    } else {
        printf("Edge not valid ignoring ");
        //GRAPHEdgePrint(e);
        printf("\n"); 
    }    //COMPLETE THIS
} 

//returns 1 if there is an edge from v to w
//returns 0 otherwise
int isAdjacent(Graph g, Vertex v, Vertex w){
    //COMPLETE THIS
    assert(g != NULL && GRAPHvalidVertex(g,v) && GRAPHvalidVertex(g,w));
    int adjacent = 0;
    
    if(g->adj[v][w] != 0){
        adjacent = 1;
    }
    
    return adjacent;
}

//returns the number of adjacent vertices
//and fills the adj array with the adjacent vertices
int adjacentVertices(Graph g, Vertex v, Vertex adj[]){
    //COMPLETE THIS 
    int counter, i = 0;
    for(i = 0,counter = 0; i < g->V; i++){
        if(g->adj[v][i] != 0){
            adj[counter] = i;
            counter++;
        }
    }
    return counter;
}

//returns the number of incident edges
//and fills the edges with incident edges
int incidentEdges(Graph g, Vertex v, Edge edges[]){
    //COMPLETE THIS
    int counter = 0;
    int i = 0;
    for(i = 0;i < g->V; i++){
        if(g->adj[v][i] > 0){
            edges[counter] = mkEdge(v,i,g->adj[v][i]);
            counter++;
        }
    }
    return counter;
}

char * getVertexLabel(Graph g, Vertex v){
    //COMPLETE THIS
    return g->vLabels[v];
}

void destroyGraph(Graph g){
    //COMPLETE THIS
   assert(g != NULL);
	int v = 0;
	for(v = 0; v < g->V;v++){
		free(g->adj[v]);
		free(g->vLabels[v]);		
	}
	free(g->adj);
	free(g->vLabels);
	free(g->types);		
	free(g);
}

//return the number of vertices in the graph
int numV(Graph g){
    //COMPLETE THIS
    return g->V;
}

//return the number of edges in the graph
int numE(Graph g){
    //COMPLETE THIS
    return g->E;
}

// returns the number of edges and fills the array of edges.
// nE is the max size of the es array
// The edges in the edges function should be in ascending order and not 
// contain duplicates. 
int edges(Edge es[], int nE, Graph g){
    //COMPLETE THIS
    assert(g != NULL && es != NULL && nE > 0);
    int i,j,n = 0;
    for(i = 0; i < g->V; i++){
        for(j = 0; j < g->V; j++){
            if(g->adj[i][j] != 0){
                assert(n < nE);
                es[n++] = mkEdge(i,j,g->adj[i][j]);
            }
        }
    }
    return n;
}

//Display the graph
void show(Graph g) { 
    assert(g != NULL); 
    printf("V=%d, E=%d\n", numV(g), numE(g)); 
    int i, j; 
    for (i = 0; i < numV(g); i++) { 
        int nshown = 0; 
        for (j = 0; j < numV(g); j++) { 
            if (isAdjacent(g,i,j)) {                
                printf("%d-%d : %d ",i,j,g->adj[i][j]); 
                nshown++; 
            } 
        } 
        if (nshown > 0){
            printf("\n"); 
        }
    } 
}

//my functions
void cityInfo(Graph g, Vertex v, char *cityName, char informant){
    if( v >= 0  && v < g->V){
        g->vLabels[v] = strdup(cityName);
        g->types[v] = informant;  
    }
    //printf("ho\n");
}

int informant(Graph g, Vertex v){
   int i = 0;
   
   if(g->types[v] == 'i'){
      i = 1;
   }
   
   return i;
}

int edgeWeight(Graph g, Vertex v, Vertex w){
    return g->adj[v][w];
}
