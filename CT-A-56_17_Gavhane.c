#include <stdio.h>
#include <stdlib.h>

typedef struct AdjNode{ int v; struct AdjNode* next; } AdjNode;
typedef struct Graph{ int V; AdjNode **array; } Graph;

AdjNode* newAdjNode(int v){ AdjNode* n=malloc(sizeof(AdjNode)); n->v=v; n->next=NULL; return n; }
Graph* createGraph(int V){ Graph *g=malloc(sizeof(Graph)); g->V=V; g->array = malloc(V * sizeof(AdjNode*)); for(int i=0;i<V;i++) g->array[i]=NULL; return g;}
void addEdge(Graph *g,int src,int dest){
    AdjNode *n = newAdjNode(dest); n->next = g->array[src]; g->array[src]=n;
    // for undirected also add reverse
    //n = newAdjNode(src); n->next = g->array[dest]; g->array[dest]=n;
}

void bfs(Graph *g,int s){
    int *visited = calloc(g->V, sizeof(int));
    int *queue = malloc(g->V * sizeof(int)); int front=0,rear=0;
    visited[s]=1; queue[rear++]=s;
    while(front<rear){
        int u = queue[front++];
        printf("%d ", u);
        for(AdjNode *p=g->array[u]; p; p=p->next){
            if(!visited[p->v]){ visited[p->v]=1; queue[rear++]=p->v; }
        }
    }
    free(visited); free(queue);
}

void dfsUtil(Graph *g, int v, int *visited){
    visited[v]=1; printf("%d ", v);
    for(AdjNode *p=g->array[v]; p; p=p->next)
        if(!visited[p->v]) dfsUtil(g, p->v, visited);
}
void dfs(Graph *g, int s){
    int *visited = calloc(g->V, sizeof(int));
    dfsUtil(g, s, visited);
    free(visited);
}

int main(){
    int V=5; Graph *g = createGraph(V);
    addEdge(g,0,1); addEdge(g,0,4); addEdge(g,1,2); addEdge(g,1,3); addEdge(g,1,4); addEdge(g,2,3); addEdge(g,3,4);
    printf("BFS from 0: "); bfs(g,0); printf("\nDFS from 0: "); dfs(g,0); printf("\n");
    return 0;
}
