#include <stdio.h>
#include <stdlib.h>

typedef struct Node{ int data; struct Node *next; } Node;

Node* newNode(int x){ Node* n = malloc(sizeof(Node)); n->data=x; n->next=NULL; return n; }

void pushHead(Node **head, int x){
    Node *n = newNode(x); n->next = *head; *head = n;
}
void insertAfter(Node *prev, int x){
    if(!prev) return;
    Node *n = newNode(x); n->next = prev->next; prev->next = n;
}
void deleteValue(Node **head, int x){
    Node *temp = *head, *prev = NULL;
    while(temp && temp->data!=x){ prev=temp; temp=temp->next; }
    if(!temp) return;
    if(!prev) *head = temp->next; else prev->next = temp->next;
    free(temp);
}
Node* reverseList(Node *head){
    Node *prev=NULL, *curr=head, *next;
    while(curr){ next=curr->next; curr->next=prev; prev=curr; curr=next; }
    return prev;
}
Node* mergeSorted(Node *a, Node *b){
    if(!a) return b; if(!b) return a;
    Node *res=NULL;
    if(a->data <= b->data){ res=a; res->next = mergeSorted(a->next,b); }
    else { res=b; res->next = mergeSorted(a,b->next); }
    return res;
}
Node* getMiddle(Node *head){
    if(!head) return NULL;
    Node *slow=head, *fast=head;
    while(fast->next && fast->next->next){ slow=slow->next; fast=fast->next->next; }
    return slow;
}
Node* mergeSort(Node *head){
    if(!head || !head->next) return head;
    Node *mid = getMiddle(head);
    Node *r = mid->next; mid->next = NULL;
    return mergeSorted(mergeSort(head), mergeSort(r));
}
int detectLoop(Node *head){
    Node *slow=head, *fast=head;
    while(slow && fast && fast->next){
        slow=slow->next; fast=fast->next->next;
        if(slow==fast) return 1;
    }
    return 0;
}
int sumList(Node *head){
    int s=0; while(head){ s+=head->data; head=head->next; } return s;
}
void printOddEven(Node *head){
    printf("Odd: "); Node *t=head;
    while(t){ if(t->data%2) printf("%d ", t->data); t=t->next; }
    printf("\nEven: "); t=head;
    while(t){ if(!(t->data%2)) printf("%d ", t->data); t=t->next; }
    printf("\n");
}
void printList(Node *head){ while(head){ printf("%d->",head->data); head=head->next; } printf("NULL\n"); }

int main(){
    Node *a=NULL;
    pushHead(&a,5); pushHead(&a,3); pushHead(&a,8); pushHead(&a,1);
    printf("List: "); printList(a);
    a = mergeSort(a);
    printf("Sorted: "); printList(a);
    printf("Sum: %d\n", sumList(a));
    printOddEven(a);
    Node *mid = getMiddle(a);
    if(mid) printf("Middle: %d\n", mid->data);
    // create loop for test (comment out normally)
    // a->next->next->next = a->next;
    printf("Loop? %s\n", detectLoop(a) ? "Yes" : "No");
    a = reverseList(a);
    printf("Reversed: "); printList(a);
    return 0;
}
