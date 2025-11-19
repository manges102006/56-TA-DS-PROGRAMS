#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct {
    int *arr;
    int f1, r1, s1; 
    int f2, r2, s2;
    int half;
} TwoQueues;

void init2q(TwoQueues *q){
    q->arr = malloc(sizeof(int)*SIZE);
    q->half = SIZE/2;
    q->f1 = 0; q->r1 = -1; q->s1 = 0;
    q->f2 = q->half; q->r2 = q->half-1; q->s2 = 0;
}
int isFull1(TwoQueues *q){ return q->s1 == q->half; }
int isFull2(TwoQueues *q){ return q->s2 == q->half; }
void enqueue1(TwoQueues *q, int x){
    if(isFull1(q)){ printf("Q1 Full\n"); return; }
    q->r1 = (q->r1 + 1) % q->half;
    q->arr[q->r1] = x;
    q->s1++;
}
void enqueue2(TwoQueues *q, int x){
    if(isFull2(q)){ printf("Q2 Full\n"); return; }
    q->r2 = q->half + ((q->r2 + 1 - q->half) % q->half);
    q->arr[q->r2] = x;
    q->s2++;
}
int dequeue1(TwoQueues *q){
    if(q->s1==0){ printf("Q1 Empty\n"); return -1; }
    int val = q->arr[q->f1];
    q->f1 = (q->f1 + 1) % q->half;
    q->s1--;
    return val;
}
int dequeue2(TwoQueues *q){
    if(q->s2==0){ printf("Q2 Empty\n"); return -1; }
    int val = q->arr[q->f2];
    q->f2 = q->half + ((q->f2 + 1 - q->half) % q->half);
    q->s2--;
    return val;
}

int main(){
    TwoQueues q; init2q(&q);
    enqueue1(&q,1); enqueue1(&q,2);
    enqueue2(&q,10); enqueue2(&q,20);
    printf("%d %d\n", dequeue1(&q), dequeue2(&q));
    return 0;
}
