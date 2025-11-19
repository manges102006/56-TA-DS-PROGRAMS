#include <stdio.h>
#include <stdlib.h>
#include <queue.h> // Not standard; will implement simple queue below

typedef struct Node{ int data; struct Node *left,*right,*parent; } Node;

Node* newNode(int x, Node *p){ Node* n = malloc(sizeof(Node)); n->data=x; n->left=n->right=NULL; n->parent = p; return n; }

Node* insert(Node *root, int x, Node *parent){
    if(!root) return newNode(x, parent);
    if(x < root->data) root->left = insert(root->left,x,root);
    else root->right = insert(root->right,x,root);
    return root;
}
void inorder(Node *r){ if(!r) return; inorder(r->left); printf("%d ", r->data); inorder(r->right); }
void preorder(Node *r){ if(!r) return; printf("%d ", r->data); preorder(r->left); preorder(r->right); }
void postorder(Node *r){ if(!r) return; postorder(r->left); postorder(r->right); printf("%d ", r->data); }

// simple queue for BFS
typedef struct QNode{ Node *data; struct QNode *next; } QNode;
typedef struct { QNode *front,*rear; } Queue;
void qinit(Queue *q){ q->front=q->rear=NULL; }
int qempty(Queue *q){ return q->front==NULL; }
void qpush(Queue *q, Node *n){ QNode *t = malloc(sizeof(QNode)); t->data=n; t->next=NULL; if(q->rear) q->rear->next=t; q->rear=t; if(!q->front) q->front=t;}
Node* qpop(Queue *q){ if(qempty(q)) return NULL; QNode *t=q->front; Node *d=t->data; q->front=q->front->next; if(!q->front) q->rear=NULL; free(t); return d; }

void bfs(Node *root){
    Queue q; qinit(&q);
    if(!root) return;
    qpush(&q, root);
    while(!qempty(&q)){
        Node *n = qpop(&q);
        printf("%d ", n->data);
        if(n->left) qpush(&q, n->left);
        if(n->right) qpush(&q, n->right);
    }
}

void mirror(Node *root){
    if(!root) return;
    Node *t = root->left; root->left = root->right; root->right = t;
    mirror(root->left); mirror(root->right);
}
Node* findNode(Node *root, int key){
    if(!root) return NULL;
    if(root->data==key) return root;
    if(key < root->data) return findNode(root->left,key);
    return findNode(root->right,key);
}
Node* getParent(Node *node){ return node ? node->parent : NULL; }
Node* getSibling(Node *node){
    if(!node || !node->parent) return NULL;
    if(node->parent->left==node) return node->parent->right;
    return node->parent->left;
}
Node* getGrandParent(Node *node){ if(!node) return NULL; return getParent(getParent(node)); }
Node* getUncle(Node *node){ Node *gp = getGrandParent(node); if(!gp) return NULL; Node *p = getParent(node); if(gp->left == p) return gp->right; return gp->left; }

int main(){
    Node *root = NULL;
    int vals[] = {50,30,20,40,70,60,80}; int n=7;
    for(int i=0;i<n;i++) root = insert(root, vals[i], NULL);
    // reattach parents properly (simple way: rebuild parent pointers)
    // For correctness in this small demo, we re-insert with parent using helper:
    // (We used parent while inserting above; for safety this works.)
    printf("Inorder: "); inorder(root); printf("\nPreorder: "); preorder(root); printf("\nPostorder: "); postorder(root); printf("\nBFS: "); bfs(root); printf("\n");
    Node *node = findNode(root, 60);
    if(node){
        printf("Parent of 60: %d\n", getParent(node)->data);
        Node *sib = getSibling(node); if(sib) printf("Sibling: %d\n", sib->data);
        Node *gp = getGrandParent(node); if(gp) printf("Grandparent: %d\n", gp->data);
        Node *unc = getUncle(node); if(unc) printf("Uncle: %d\n", unc->data);
    }
    mirror(root);
    printf("Inorder after mirror: "); inorder(root); printf("\n");
    return 0;
}
