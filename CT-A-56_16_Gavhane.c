#include <stdio.h>
#include <stdlib.h>

typedef struct Node{ int data; struct Node *left,*right; } Node;
Node* newNode(int x){ Node* n=malloc(sizeof(Node)); n->data=x; n->left=n->right=NULL; return n; }
Node* insert(Node *root,int x){ if(!root) return newNode(x); if(x<root->data) root->left=insert(root->left,x); else root->right=insert(root->right,x); return root; }

int findMin(Node *root){ while(root->left) root=root->left; return root->data; }
int findMax(Node *root){ while(root->right) root=root->right; return root->data; }

int main(){
    Node *root=NULL; int vals[]={50,30,20,40,70,60,80}; for(int i=0;i<7;i++) root=insert(root, vals[i]);
    printf("Min: %d\nMax: %d\n", findMin(root), findMax(root));
    return 0;
}
