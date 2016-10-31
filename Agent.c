#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Agent.h"

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
static Edge DFSstrat(Graph g, Agent agent);
static Edge LeastTurns(Graph g, Agent agent);
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
    agent->leastTurns = malloc(sizeof(int) *2*numV(g));
    agent->oriStrategy = strategy;
    
    agent->visits[start]++;
    if(agent->strategy == DFS){
        dfSearch2(g,agent);
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
Edge getNextMove(Agent agent,Graph g){
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
        
        //if original strategy was DFS 
        if(agent->strategy == DFS){
            //fill the dfs search again
            dfSearch2(agent->map,agent);   
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
    checkInformant(agent,agent->map,FALSE);                              
    if(agent->name[0] == 'T'){
        printf(" %s ", getVertexLabel(agent->map,agent->endLocation));
        checkInformant(agent,agent->map,TRUE);
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
void dfSearch2(Graph g, Agent agent){
   int v;
   
   Vertex *visited = calloc(numV(g),sizeof(int) *numV(g));
   agent->dfsCount = 0;
   
   for(v = 0; v < numV(g); v++){
      visited[v] = -1;
      agent->st[v] = -1;
      agent->pre[v] = -1;
   }
   
   for(v = 0; v < numV(g); v++){
      if(agent->pre[v] == -1){
         dfsR2(g,mkEdge(agent->currentLocation,agent->currentLocation,0),agent,visited);
      }
   }
   agent->Goal = 1;
   
   free(visited);
}

void dfsR2(Graph g, Edge e, Agent agent, Vertex *visited){
   int i,w;
   agent->pre[agent->dfsCount++] = e.w;
   //Vertex *visited = malloc(sizeof(int) *g->V);
   visited[e.w] = 1;
   agent->st[e.w] = e.v;
   
   for(i = 0; i < numV(g); i++){
      w = edgeWeight(g,e.w,i);
      if((w != 0) && (visited[i] == -1)){
         dfsR2(g,mkEdge(e.w,i,w),agent,visited);
      }
   }
  // free(visited);
}

Edge DFSstrat(Graph g, Agent agent){
    int newGoal = agent->Goal;
    Vertex goal = agent->pre[newGoal];
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
    printf("got to implement\n");
}

Edge LeastTurns(Graph g, Agent agent){
    Vertex v = agent->leastTurns[agent->pathPos];
    agent->pathPos++;
    Vertex w = agent->leastTurns[agent->pathPos];
    
    return mkEdge(v,w,edgeWeight(g,v,w));
}

