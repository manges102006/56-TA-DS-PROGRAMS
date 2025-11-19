#include <stdio.h>
#include <stdlib.h>

typedef struct Node{ int data; struct Node *left,*right; } Node;
Node* newNode(int x){ Node* n=malloc(sizeof(Node)); n->data=x; n->left=n->right=NULL; return n; }
Node* insert(Node *root,int x){ if(!root) return newNode(x); if(x<root->data) root->left=insert(root->left,x); else root->right=insert(root->right,x); return root; }

void printRange(Node *root, int low, int high){
    if(!root) return;
    if(root->data > low) printRange(root->left, low, high);
    if(root->data >= low && root->data <= high) printf("%d ", root->data);
    if(root->data < high) printRange(root->right, low, high);
}

int main(){
    Node *root=NULL; int vals[]={20,8,4,12,10,14,22}; for(int i=0;i<7;i++) root=insert(root, vals[i]);
    int L=10, R=21;
    printf("Keys in [%d,%d]: ", L, R); printRange(root,L,R); printf("\n");
    return 0;
}
