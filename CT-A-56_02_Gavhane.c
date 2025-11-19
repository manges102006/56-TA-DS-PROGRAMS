#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int arr[MAX];
    int front, rear, size;
} Queue;

void init(Queue *q){ q->front = 0; q->rear = -1; q->size = 0; }
int isEmptyQ(Queue *q){ return q->size == 0; }
int isFullQ(Queue *q){ return q->size == MAX; }
void enqueue(Queue *q, int x){
    if(isFullQ(q)){ printf("Queue Full\n"); return; }
    q->rear = (q->rear + 1) % MAX;
    q->arr[q->rear] = x;
    q->size++;
}
int dequeue(Queue *q){
    if(isEmptyQ(q)){ printf("Queue Empty\n"); return -1; }
    int val = q->arr[q->front];
    q->front = (q->front + 1) % MAX;
    q->size--;
    return val;
}

int main(){
    Queue q; init(&q);
    enqueue(&q,1); enqueue(&q,2); enqueue(&q,3);
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    return 0;
}
