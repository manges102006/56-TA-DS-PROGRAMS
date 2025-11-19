#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data; struct Node *next;
} Node;

Node* top = NULL;

void push(int x){
    Node *n = malloc(sizeof(Node));
    n->data = x; n->next = top; top = n;
}
int pop(){
    if(!top){ printf("Underflow\n"); return -1; }
    int v = top->data; Node *t = top; top = top->next; free(t); return v;
}
int peekLL(){ return top ? top->data : -1; }

int main(){
    push(5); push(10); push(20);
    printf("Peek: %d\n", peekLL());
    printf("Pop: %d\n", pop());
    printf("Pop: %d\n", pop());
    return 0;
}
