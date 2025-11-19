#include <stdio.h>
#include <stdlib.h>

typedef struct Node{ int data; struct Node *prev,*next; } Node;

Node* newNode(int x){ Node* n = malloc(sizeof(Node)); n->data=x; n->prev=n->next=NULL; return n; }

void pushFront(Node **head, int x){
    Node *n = newNode(x);
    n->next = *head;
    if(*head) (*head)->prev = n;
    *head = n;
}
void insertAfter(Node *prev, int x){
    if(!prev) return;
    Node *n = newNode(x);
    n->next = prev->next;
    n->prev = prev;
    prev->next = n;
    if(n->next) n->next->prev = n;
}
void deleteNode(Node **head, Node *del){
    if(!*head || !del) return;
    if(*head == del) *head = del->next;
    if(del->next) del->next->prev = del->prev;
    if(del->prev) del->prev->next = del->next;
    free(del);
}
void reverseDLL(Node **head){
    Node *temp = NULL, *curr = *head;
    while(curr){
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }
    if(temp) *head = temp->prev;
}
void printForward(Node *head){
    while(head){ printf("%d->", head->data); head=head->next; } printf("NULL\n");
}

int main(){
    Node *head=NULL;
    pushFront(&head,10); pushFront(&head,20); pushFront(&head,30);
    printForward(head);
    insertAfter(head->next, 25);
    printForward(head);
    reverseDLL(&head);
    printForward(head);
    return 0;
}
