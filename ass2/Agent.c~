#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Graph.h"
#include "Agent.h"
#include <limits.h>
#include "Item.h"
#include "Queue.h"


//This struct stores information about an individual agent(detective or thief)
//You might want to add to this struct to store more information
struct agentRep{
    Vertex startLocation;
    Vertex currentLocation;
    int currentCycle;
    int maxCycles;
    int initialStamina; //max stamina
    int stamina;  //current stamina
    int strategy;
    Graph map;
    char *name;
    //stuff I added
    Vertex endLocation;
    int *visits; // array of visits
    //dfs 
    int dfsCount;
    int Goal;
    Vertex *st;
    Vertex *pre;
    //least turns
    Vertex *leastTurns;
    Vertex *ThiefLoc; //thief's location from informant
    int nVPath; //number of vertices
    int oriStrategy; //if needed to return to original strategy
    int pathPos;    
};

//static Edge clVisited(Agent agent, Graph g, Edge *move, int numMoves);
static Edge CLFilterEdges(Agent agent, Graph g, Edge *filteredMoves, int numFilteredEdges);
static Edge DFSstrat(Graph g,Agent agent);
static Edge LeastTurns(Graph g, Agent agent);
static Edge thiefMove(Graph g,Agent agent,Agent * agents);


//This creates one individual thief or detective
//You may need to add more to this
Agent initAgent(Vertex start, int maxCycles,int stamina, 
                              int strategy, Graph g, char * name, Vertex end){
    if(start >= numV(g)){
        printf("Error starting vertex %d not valid\n",start);
        abort();
    }
    Agent agent = malloc(sizeof(struct agentRep));

    agent->startLocation = start;
    agent->currentLocation = start;
    agent->currentCycle = 0;
    agent->maxCycles = maxCycles;
    agent->initialStamina = stamina;
    agent->stamina = stamina;
    agent->strategy = strategy;
    agent->map = g;
    agent->name = strdup(name);
    agent->endLocation = end;
    agent->visits = calloc(numV(g),sizeof(int) *numV(g));
    agent->st = calloc(numV(g),sizeof(int) *numV(g));
    agent->pre = calloc(numV(g),sizeof(int) *numV(g));
    agent->leastTurns = malloc(sizeof(Vertex) *2*numV(g));
    agent->oriStrategy = strategy;

    agent->visits[start]++;

    if(agent->strategy == DFS){
        dfsSearch(g,agent);
    }
    return agent;
}


// Takes an array with all the possible edges and puts the ones the agent
// has enough stamina for into the filteredMoves array
// returns the number of filteredMoves
int filterEdges(Agent a,int numEdges,Edge *possibleMoves,Edge * filteredMoves){
    int numFiltered = 0;
    int i;
    for(i=0;i<numEdges;i++){
        if(possibleMoves[i].weight <= a->stamina){
            filteredMoves[numFiltered++] = possibleMoves[i];     
        }
    }
    return numFiltered;
}

// Get a legal move. This should be a move that the agent has enough 
// stamina to make and is a valid edge from the graph. 
// You need to implement all other strategies.
Edge getNextMove(Agent agent,Graph g, Agent thief, Agent * agents){
    Edge nextMove;          
    //Stationary strategy useful for debugging
    if(agent->strategy == STATIONARY){
        nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);  
    }else if(agent->strategy == RANDOM || agent->strategy == C_L_VISITED){      
         Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
         Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

         //Get all edges to adjacent vertices
         int numEdges = incidentEdges(g,agent->currentLocation,possibleMoves);
         
         //Filter out edges that the agent does not have enough stamina for
         int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);
         if(numFilteredEdges!= 0){
             //nextMove is randomly chosen from the filteredEdges
             if(agent->strategy == RANDOM){
                nextMove = filteredMoves[rand()%numFilteredEdges];
             } else if (agent->strategy == C_L_VISITED){
                //have to implement cheapest least visited strat
                //nextMove = clVisited(agent,g,filteredMoves,numFilteredEdges);
                nextMove = CLFilterEdges(agent,g,filteredMoves,numFilteredEdges);
             }   
	     } else {
             //the agent must stay in the same location
             nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
         }
         free(filteredMoves);
         free(possibleMoves);
    }else if(agent->strategy == DFS){      
         nextMove = DFSstrat(g,agent);
    }else if(agent->strategy == Least_Turns){
         nextMove = LeastTurns(g,agent);     
    } else if (agent->strategy == THIEF_STRAT) {
         nextMove = thiefMove(g,agent,agents);
    }else {
         printf("Agent strategy not implemented yet\n");
         abort();
    }
    agent->visits[nextMove.w]++;
    return nextMove;
}

//Actually perform the move, by changing the agent's state
//This function needs to be updated to adjust the agent's stamina
void makeNextMove(Agent agent,Edge move){
    agent->currentCycle++;
    
    //deduct stamina for every move
    if(agent->currentLocation != move.w){
        agent->currentLocation = move.w; 
        agent->stamina = agent->stamina - move.weight;
    } else {
        //stamina reloads because agent hasnt moved
        agent->stamina = agent->initialStamina;
    }

    //used Least turns strat and came to the location mentioned in informant
    if(agent->strategy == Least_Turns && agent->currentLocation == agent->endLocation){
        //but no thief so switch back to original strategy
        agent->strategy = agent->oriStrategy;
        if (agent->oriStrategy != THIEF_STRAT){
            //if not the thief
            agent->endLocation = NOLOC;
        }
        
        //if original strategy was DFS 
        if(agent->strategy == DFS){
            //fill the dfs search again
            dfsSearch(agent->map,agent);    
        }
    }
}

Vertex getCurrentLocation(Agent agent){
    return agent->currentLocation;
}

Vertex getEndLocation(Agent agent){
    return agent->endLocation;
}

char * getName(Agent agent){
    return agent->name;
}

//Needs to be updated to print out vertex name information
//and * for cities with informants
void printAgent(Agent agent){    
    //MODIFY THIS
    printf("%s %d %s ",agent->name,agent->stamina,
                         getVertexLabel(agent->map,agent->currentLocation));
    /*checkInformant(agent,agent->map,FALSE);                              
    if(agent->name[0] == 'T'){
        printf(" %s ", getVertexLabel(agent->map,agent->endLocation));
        checkInformant(agent,agent->map,TRUE);
    } */
    if (informant(agent->map,agent->currentLocation) == TRUE){
        printf("(%d*)",agent->currentLocation);
    } else {
        printf("(%d)",agent->currentLocation);
    }

    if (agent->endLocation != NOLOC){
        printf(" %s ",getVertexLabel(agent->map,agent->endLocation));
        if (informant(agent->map,agent->endLocation)){
            printf("(%d*)",agent->endLocation);
        } else {
            printf("(%d)",agent->endLocation);
        }
    }
    
    printf("\n");
}

void checkInformant (Agent agent, Graph graph, Vertex count){
    Vertex loc = 0;
    if((agent->name[0]  == 'T') && count == TRUE){
        loc = agent->endLocation;
    } else {
        loc = agent->currentLocation;
    }
    if(informant(agent->map,loc) == TRUE) {
	    printf("(%d*)",loc);
	} else {
	    printf("(%d)",loc);
	} 
}

void leastTurnsInformant(Agent agent, Agent thief, Graph graph){
    if(informant(graph,agent->currentLocation) == TRUE){
        agent->strategy = Least_Turns;
        agent->pathPos = 0;
        agent->endLocation = thief->currentLocation;
        shortestPath(graph, agent, thief->currentLocation);
    }
}

//You may need to update this to free any extra memory you use
void destroyAgent(Agent agent){
    //YOU MAY NEED TO MODIFY THIS
    free(agent->name);
    free(agent->visits);
    free(agent->pre);
    free(agent->st);
    free(agent->leastTurns);
    free(agent);
} 

static Edge CLFilterEdges(Agent agent, Graph g, Edge *filteredMoves, int numFilteredEdges){
  
  int i , minIndex = 0;

  for(i = 0; i < numFilteredEdges; i++){
    if(agent->visits[filteredMoves[minIndex].w] > agent->visits[filteredMoves[i].w]){
      minIndex = i;    
    } else if(agent->visits[filteredMoves[minIndex].w] == agent->visits[filteredMoves[i].w]){                
        if(filteredMoves[minIndex].weight > filteredMoves[i].weight){
          minIndex = i;       
        } else if(filteredMoves[minIndex].weight == filteredMoves[i].weight){            
            if(filteredMoves[minIndex].w > filteredMoves[i].w){
              minIndex = i;            
            }
        }
    }
  }
  return filteredMoves[minIndex]; 
}

//DFS
void dfsR(Graph g, Edge e, Agent agent, Vertex * visited){
    int i;
    int w = e.w;
    //find the right spot to put the visited node
    agent->pre[agent->dfsCount++] = w;
    visited[w] = 1;
    agent->st[w] = e.v;
    int weight;
    for (i=0;i<numV(g);i++){
        weight = edgeWeight(g,w,i);

        if (weight > 0 && visited[i] == -1){
            dfsR(g,mkEdge(w,i,weight),agent,visited);
        }
    }
}

void dfsSearch(Graph g, Agent agent){
    int i;
    Vertex * visited = malloc(sizeof(int) * numV(g));
    assert(visited != NULL);
    agent->dfsCount =0;
    //clean up array
    for (i=0; i< numV(g); i++){
        agent->pre[i] = -1;
        visited[i] = -1;
        agent->st[i] = -1;
    }

    //assume graph is connected
    dfsR(g,mkEdge(agent->currentLocation,agent->currentLocation,0),
         agent, visited);
    agent->Goal = 1;

    free(visited);
}
Edge DFSstrat(Graph g, Agent agent){
    
    int newGoal = agent->Goal;
    Vertex goal = agent->pre[agent->Goal];
    Edge pass;
    
    Vertex curr = agent->currentLocation;
    int w = edgeWeight(g,curr,goal);
    if(w > 0){
        newGoal = (agent->Goal + 1) % numV(g);
        pass = mkEdge(curr, goal, w);
    } else {
        w = edgeWeight(g, curr, agent->st[curr]);
        pass = mkEdge(curr, agent->st[curr], w);
    }
    
    if(agent->stamina < w){
        pass = mkEdge(curr,curr,0);
    } else {
        agent->Goal = newGoal;
    }
    
    return pass;
}
//least turns

void shortestPath(Graph g, Agent agent, Vertex EndLoc){
    
    Queue queue = createQueue();
    Queue set = createQueue();
    Node init = makeNode(agent->currentLocation, NULL,
                      agent->stamina,agent->initialStamina,
                      0, agent->currentLocation);
    putQueue(set, init);

    int i;
    Node * neighbours = malloc(sizeof(Node) * (numV(g) + 1));
    assert(neighbours != NULL);

    int numNeighbours;

    putQueue(queue, init);
    Node t;
    int done = 0;
    Node * goalNodes = malloc(sizeof(Node) * numV(g));
    assert(goalNodes != NULL);
    int numShortestPath = 0;
    int maxDepth = INT_MAX;
    Node best;
    //BFS

    while (queueSize(queue) > 0){
        t = getQueue(queue);

        if (getVertex(t) == EndLoc && getDepth(t) <= maxDepth){
            goalNodes[numShortestPath] = t;
            numShortestPath++;
            maxDepth = getDepth(t);
            done = 1;
        }

        if (!done){
            numNeighbours = getNeighbours(g,t,neighbours);
            for (i=0;i<numNeighbours;i++){
                putQueue(queue,neighbours[i]);
                putQueue(set,neighbours[i]);
            }
        }
    }
    
    // check that we have a short path

    assert(numShortestPath != 0);
    //get shortest of the paths
    best = goalNodes[0];
    for(i=1;i<numShortestPath;i++){
        assert(getDepth(best) == getDepth(goalNodes[i]));
        if (getStamina(goalNodes[i]) > getStamina(best)){
            best = goalNodes[i];
        } else if (getStamina(goalNodes[i]) == getStamina(best)){
            if (getSumVertices(goalNodes[i]) < getSumVertices(best)) {
                best = goalNodes[i];
            }
        }
    }

    for(i = 0; i < 2*numV(g); i++){
        agent->leastTurns[i] = -1;
    }

    agent->nVPath = reconstructPath(best, agent->leastTurns);
    
    free(goalNodes);
    free(neighbours);
    destroyQueue(queue);
    destroyQueue(set);
}

Edge LeastTurns(Graph g, Agent agent){
    Vertex v = agent->leastTurns[agent->pathPos];
    agent->pathPos++;
    Vertex w = agent->leastTurns[agent->pathPos];
    
    return mkEdge(v,w,edgeWeight(g,v,w));
}

void bonusStrategy(Agent thief, Graph g){

    thief->strategy = THIEF_STRAT;
    thief->oriStrategy = THIEF_STRAT;
    thief->pathPos = 0;
    shortestPath(g,thief,thief->endLocation);

}

Vertex compareVertices(Graph g, Agent *agents, Vertex v, Vertex w){
    int i;
    int * dummy = malloc(sizeof(Vertex) * numV(g));
    assert(dummy != NULL);
    //not actual probabilities
    double probV = 0.0;
    double probW = 0.0;
    Vertex ret= v;
    for(i=1; i<=NUM_DETECTIVES; i++){
            if (isAdjacent(g,agents[i]->currentLocation,v)){
                probV += 1.0 / (double)(adjacentVertices(g,v,dummy) + 1);
            } else if (isAdjacent(g,agents[i]->currentLocation,w)){
                probW += 1.0 / (double)(adjacentVertices(g,w,dummy) + 1);
            }
    }

    if (probV >= probW){
        ret = w;
    }
    free(dummy);
    return ret;
}


Edge thiefMove(Graph g,Agent agent,Agent * agents){

    Vertex v = agent->leastTurns[agent->pathPos];
    Vertex w = agent->leastTurns[agent->pathPos + 1];
    Vertex y = agent->leastTurns[agent->pathPos + 2];
    //decide whether to wait or to move on
    
    if (v!=w){
        if (edgeWeight(g,v,w) < agent->stamina && compareVertices(g,agents,v,w) == w ){
            //go on
            agent->pathPos++;
        } else {
            w=v;
        }
    } else {
        if (y != -1 && edgeWeight(g,v,w) < agent->stamina){
            //decide whether to move to y instead
            if (compareVertices(g,agents,v,y) == y){
                //move to w
                w = y;
               agent->pathPos += 2;
            }
        }
    }

    return mkEdge(v,w,edgeWeight(g,v,w));
}

