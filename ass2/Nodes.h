#pragma once
#include "Graph.h"


typedef struct _node * Node;
Node makeNode(Vertex v, Node prev, int curStamina, int maxStamina,int depth, int nodeSum);
Vertex getVertex(Node node);
int getNeighbours(Graph g, Node node, Node * neighbours);
int getDepth(Node node);
int getStamina(Node node);
void freeNode(Node node);
int getSumVertices(Node node);
int reconstructPath(Node end, Vertex * array);
