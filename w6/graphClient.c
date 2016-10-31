#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GRAPH.h"
#include "time.h"

#define MAXV 5
#define MAXE 10

int randV(Graph g){
    return GRAPHnumV(g) *(rand()/(RAND_MAX + 1.0));
}

Graph randomGraph(int V, int E){
    Graph g = GRAPHinit(V);
    while(GRAPHnumE(g) < E){
        int v = randV(g);
        int w = randV(g);
        if(v != w){
            GRAPHinsertE(g,EDGE(v,w));
        }
    }
    return g;
}

Graph graphScan(){
    int v,w;
    int V;
    int count = 1;
    printf("Enter num vertices : ");
    scanf("%d",&V);
    printf("Enter pairs of vertices between 0 and %d\n",V-1);
    Graph g = GRAPHinit(V);
    while((scanf("%d %d",&v,&w) == 2) && count != V){
        GRAPHinsertE(g,EDGE(v,w));
        count++;
    }
    return g;
}

int main(int argc, char * argv[]){
    srand(time(NULL));
    Graph randG = randomGraph(MAXV,MAXE);
    printf("Here is my random graph\n");
    GRAPHshow(randG);
    
    Graph g1 = graphScan();
    printf("\nHere is my scanned graph\n");
    GRAPHshow(g1);
    GRAPHdestroy(randG);
    GRAPHdestroy(g1);
   
    Graph cop = GRAPHcopy(randG);
    GRAPHshow(cop);
    GRAPHdestroy(cop);
    GRAPHdestroy(randG);

    return 0;
}
