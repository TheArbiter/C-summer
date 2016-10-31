#include <stdlib.h>
#include <assert.h>
#include "Nodes.h"
#include "Graph.h"
struct _node {
	Vertex v;
	Node prev;
	int curStamina;
	int maxStamina;
	int depth;
	int vertexSum;
};


Node makeNode(Vertex v, Node prev, int curStamina, int maxStamina,int depth, int vertexSum){
	//just a struct
	Node ret = malloc(sizeof(struct _node));
	assert(ret!=NULL);
	ret->v = v;
	ret->prev = prev;
	ret->curStamina = curStamina;
	ret->maxStamina = maxStamina;
	ret->depth = depth;
	ret->vertexSum = vertexSum;
	return ret;
}

Vertex getVertex(Node node){
	return node->v;
}

int getDepth(Node node){
	return node->depth;
}

int getStamina(Node node){
	return node->curStamina;
}

int getSumVertices(Node node){
	return node->vertexSum;
}


void freeNode(Node node){
	free(node);
}

int getNeighbours(Graph g, Node node, Node * neighbours){
	//neighbours is size g->nV + 1
	int i;
	Edge * adjacent = malloc(sizeof(Edge) * numV(g));
	assert(adjacent != NULL);
	int numAdjacent = incidentEdges(g,node->v,adjacent);
	Edge e;
	Vertex newV;

	int numNeighbours = 0;

	for (i=0; i<numAdjacent; i++){
		e = adjacent[i];
		if (e.v == node->v){
			newV = e.w;
		} else {
			newV = e.v;
		}
		//if this is a valid neighbour
		if (node->curStamina - e.weight >= 0){
			neighbours[numNeighbours] = makeNode(newV, node, node->curStamina - e.weight,
												node->maxStamina, node->depth + 1, node->vertexSum + newV);
			numNeighbours++;
		}//else have to wait
	}

	//add waiting node
	neighbours[numNeighbours] = makeNode(node->v,node, node->maxStamina, node->maxStamina,
										node->depth + 1, node->vertexSum + node->v);
	numNeighbours++;
	free(adjacent);

	return numNeighbours;

}

int reconstructPath(Node end, Vertex * array){

	Node cur;
	int numV,i;

	for (cur = end, numV=0; cur != NULL; cur=cur->prev, numV++);

	for (cur = end, i=numV-1; i >=0;cur=cur->prev, i--) {
		array[i] = cur->v;
	}

	return numV;

}