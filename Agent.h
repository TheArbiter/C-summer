//An ADT interface to represent an agent

//Constants to represent search strategies used by the agents

#define STATIONARY -1 //useful for debugging
#define RANDOM 0
#define C_L_VISITED 1 //Cheapest Least Visisted
#define DFS 2
#define Least_Turns 3

#define NOLOC -1
#define TRUE 1
#define FALSE 0

typedef struct agentRep * Agent;

//Initialise an agent
Agent initAgent(Vertex start, int maxCycles,int stamina, 
                              int strategy,Graph g, char * name, Vertex end);

//Calculate the next move
Edge getNextMove(Agent agent,Graph graph);
//Execute a given move
void makeNextMove(Agent agent,Edge move);


//Get information from the agent
Vertex getCurrentLocation(Agent agent);
Vertex getStartLocation(Agent agent);
Vertex getEndLocation(Agent agent);

char * getName(Agent agent);

void printAgent(Agent agent);

void destroyAgent(Agent agent);

void checkInformant (Agent agent,Graph graph, Vertex count);

// dfsOrder should contain each vertex as it is discovered in order
void dfSearch2(Graph g, Agent agent);
void dfsR2(Graph g, Edge e, Agent agent, Vertex *visited);

//least turns
void leastTurnsInformant(Agent agent, Agent thief, Graph graph);
void shortestPath(Graph g, Agent agent, Vertex EndLoc);
