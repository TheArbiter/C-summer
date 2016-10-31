#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Graph.h"
#include "Agent.h"

int main(int argc,char *argv[]){

    Graph g = newGraph(10);

    printf("Testing newGraph\n");
    assert(g != NULL);
    printf("Test passed!\n");   

    printf("Testing numV\n");
    assert(numV(g) == 10);  
    printf("Test passed!\n");

    printf("Testing mkEdge\n");
    Edge e = mkEdge(2,3,10);
    assert(e.v == 2);
    assert(e.w == 3);
    assert(e.weight == 10);
    printf("Test passed!\n");

    printf("Testing insertE\n");
    insertE(g,mkEdge(1,2,10));
    insertE(g,mkEdge(2,3,10));
    insertE(g,mkEdge(1,3,10));
    assert(numV(g) == 10);
    assert(numE(g) == 3);
    printf("Test passed!\n");

    printf("Testing isAdjacent\n");
    printf("Testing edges added\n");
    assert(isAdjacent(g,1,2) == 1);
    assert(isAdjacent(g,1,3) == 1);
    printf("Test passed!\n");


    printf("Testing graph symmetry\n");
    assert(isAdjacent(g,3,2) == 1);
    assert(isAdjacent(g,2,3) == 1);
    printf("Test passed!\n");


    printf("Testing for no edge\n");
    assert(isAdjacent(g,1,9) == 0);
    assert(isAdjacent(g,8,9) == 0);
    printf("Test passed!\n");

    printf("Testing adjacentVertices\n");
    Vertex adj[10];

    printf("Testing nomal.....\n");
    assert(adjacentVertices(g,1,adj) == 2);
    assert(adjacentVertices(g,3,adj) == 2);
    assert(adjacentVertices(g,2,adj) == 2);
    assert(adjacentVertices(g,7,adj) == 0);
    printf("Test passed!\n");
    
    printf("adding new edge...\n");
    insertE(g,mkEdge(4,1,15));
    assert(adjacentVertices(g,4,adj) == 1);
    assert(adj[0] == 1);
    printf("Test passed!\n");

    printf("Testing incidentEdges\n");
	Edge edgeArray[10];
    printf("testing normal......\n");
    assert(incidentEdges(g,1,edgeArray) == 3);
    printf("Test passed!\n");
    
    printf("testing with different edges......\n");
	assert(incidentEdges(g,2,edgeArray) == 2);
	assert(incidentEdges(g,3,edgeArray) == 2);
	assert(incidentEdges(g,4,edgeArray) == 1);
	assert(incidentEdges(g,9,edgeArray) == 0);	
    printf("Test passed!\n");
    
    printf("All Tests Passed!\n");
    destroyGraph(g);
    return 0;
}


