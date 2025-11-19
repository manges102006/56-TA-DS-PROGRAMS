#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdjNode{ int v; struct AdjNode *next; } AdjNode;
typedef struct Graph{ int V; AdjNode **adj; } Graph;

AdjNode* newAdj(int v){ AdjNode *n=malloc(sizeof(AdjNode)); n->v=v; n->next=NULL; return n; }
Graph* createGraph(int V){ Graph *g=malloc(sizeof(Graph)); g->V=V; g->adj=malloc(V*sizeof(AdjNode*)); for(int i=0;i<V;i++) g->adj[i]=NULL; return g; }
void addEdge(Graph* g,int u,int v){
    AdjNode *n=newAdj(v); n->next=g->adj[u]; g->adj[u]=n;
    n=newAdj(u); n->next=g->adj[v]; g->adj[v]=n;
}

void APUtil(Graph *g, int u, int visited[], int disc[], int low[], int parent[], int *ap, int *time){
    visited[u]=1; disc[u]=low[u]= ++(*time);
    int children = 0;
    for(AdjNode *p=g->adj[u]; p; p=p->next){
        int v = p->v;
        if(!visited[v]) {
            children++;
            parent[v]=u;
            APUtil(g,v,visited,disc,low,parent,ap,time);
            low[u] = (low[u] < low[v])? low[u]: low[v];
            if(parent[u]==-1 && children>1) ap[u]=1;
            if(parent[u]!=-1 && low[v]>=disc[u]) ap[u]=1;
        } else if(v != parent[u]){
            if(low[u] > disc[v]) low[u] = disc[v];
        }
    }
}

int isBiconnected(Graph *g){
    int V = g->V;
    int *visited = calloc(V, sizeof(int));
    int *disc = calloc(V, sizeof(int));
    int *low = calloc(V, sizeof(int));
    int *parent = malloc(V*sizeof(int));
    int *ap = calloc(V, sizeof(int));
    for(int i=0;i<V;i++) parent[i] = -1;
    int time = 0;
    // find first vertex with edges
    int start = 0;
    APUtil(g, start, visited, disc, low, parent, ap, &time);
    for(int i=0;i<V;i++) if(!visited[i]){ // not connected
        free(visited); free(disc); free(low); free(parent); free(ap);
        return 0;
    }
    for(int i=0;i<V;i++) if(ap[i]){ free(visited); free(disc); free(low); free(parent); free(ap); return 0; }
    free(visited); free(disc); free(low); free(parent); free(ap);
    return 1;
}

int main(){
    Graph *g = createGraph(5);
    addEdge(g,0,1); addEdge(g,1,2); addEdge(g,2,3); addEdge(g,3,0); addEdge(g,2,4);
    printf("Biconnected? %s\n", isBiconnected(g) ? "Yes" : "No");
    return 0;
}
