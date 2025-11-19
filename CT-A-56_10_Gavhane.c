#include <stdio.h>
#include <stdlib.h>

typedef struct Node{ int data; struct Node* next; } Node;
Node *front=NULL, *rear=NULL;

void enqueue(int x){
    Node *n = malloc(sizeof(Node)); n->data=x; n->next=NULL;
    if(!rear) { front = rear = n; return; }
    rear->next = n; rear = n;
}
int dequeue(){
    if(!front){ printf("Empty\n"); return -1; }
    Node *t = front; int v = t->data; front = front->next;
    if(!front) rear = NULL; free(t); return v;
}

int main(){
    enqueue(1); enqueue(2); enqueue(3);
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    return 0;
}
