#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int top;
} Stack;

void init(Stack *s){ s->top = -1; }
int isEmpty(Stack *s){ return s->top == -1; }
int isFull(Stack *s){ return s->top == MAX-1; }
void push(Stack *s, int x){
    if(isFull(s)){ printf("Overflow\n"); return; }
    s->arr[++s->top] = x;
}
int pop(Stack *s){
    if(isEmpty(s)){ printf("Underflow\n"); return -1; }
    return s->arr[s->top--];
}
int peek(Stack *s){
    if(isEmpty(s)){ printf("Empty\n"); return -1; }
    return s->arr[s->top];
}

int main(){
    Stack s; init(&s);
    push(&s,10); push(&s,20); push(&s,30);
    printf("Top: %d\n", peek(&s));
    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));
    printf("Popped: %d\n", pop(&s));
    return 0;
}
