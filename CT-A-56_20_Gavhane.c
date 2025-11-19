#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode{ int v; struct AdjNode *next; } AdjNode;
typedef struct Graph{ int V; AdjNode **adj; } Graph;
AdjNode* newAdj(int v){ AdjNode* n=malloc(sizeof(AdjNode)); n->v=v; n->next=NULL; return n; }
Graph* createGraph(int V){ Graph *g=malloc(sizeof(Graph)); g->V=V; g->adj=malloc(V*sizeof(AdjNode*)); for(int i=0;i<V;i++) g->adj[i]=NULL; return g;}
void addEdge(Graph *g,int u,int v){ AdjNode *n=newAdj(v); n->next=g->adj[u]; g->adj[u]=n; }

void topoSort(Graph *g){
    int V = g->V; int *indeg = calloc(V,sizeof(int));
    for(int u=0;u<V;u++) for(AdjNode *p=g->adj[u]; p; p=p->next) indeg[p->v]++;
    int *queue = malloc(V*sizeof(int)); int front=0,rear=0;
    for(int i=0;i<V;i++) if(indeg[i]==0) queue[rear++]=i;
    int cnt=0;
    int *topo = malloc(V*sizeof(int));
    while(front<rear){
        int u = queue[front++];
        topo[cnt++]=u;
        for(AdjNode *p=g->adj[u]; p; p=p->next){
            indeg[p->v]--;
            if(indeg[p->v]==0) queue[rear++]=p->v;
        }
    }
    if(cnt != V) { printf("Graph has cycle, topo sort not possible\n"); }
    else { printf("Topo order: "); for(int i=0;i<V;i++) printf("%d ", topo[i]); printf("\n"); }
    free(indeg); free(queue); free(topo);
}

int main(){
    Graph *g = createGraph(6);
    addEdge(g,5,2); addEdge(g,5,0); addEdge(g,4,0); addEdge(g,4,1);
    addEdge(g,2,3); addEdge(g,3,1);
    topoSort(g);
    return 0;
}
