#include <stdio.h>
#include <stdlib.h>
#define N 100   
#define K 5    

int arr[N];
int top[K];
int next_idx[N];
int free_idx;

void initK(){
    int i;
    for(i=0;i<K;i++) top[i] = -1;
    for(i=0;i<N-1;i++) next_idx[i] = i+1;
    next_idx[N-1] = -1;
    free_idx = 0;
}
int isFull(){ return free_idx == -1; }
int isEmptyStack(int sn){ return top[sn] == -1; }

void pushK(int item, int sn){
    if(isFull()){ printf("Stack Overflow\n"); return; }
    int i = free_idx;
    free_idx = next_idx[i];
    arr[i] = item;
    next_idx[i] = top[sn];
    top[sn] = i;
}
int popK(int sn){
    if(isEmptyStack(sn)){ printf("Stack Underflow\n"); return -1; }
    int i = top[sn];
    top[sn] = next_idx[i];
    next_idx[i] = free_idx;
    free_idx = i;
    return arr[i];
}

int main(){
    initK();
    pushK(15, 2);
    pushK(45, 2);
    pushK(17, 1);
    pushK(49, 1);
    printf("Popped from stack 2: %d\n", popK(2));
    printf("Popped from stack 1: %d\n", popK(1));
    return 0;
}
