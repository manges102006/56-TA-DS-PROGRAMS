#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isMatching(char a, char b){
    return (a=='('&&b==')') || (a=='['&&b==']') || (a=='{'&&b=='}');
}

int isBalanced(const char *expr){
    int n = strlen(expr);
    char *stack = malloc(n);
    int top = -1;
    for(int i=0;i<n;i++){
        char ch = expr[i];
        if(ch=='('||ch=='['||ch=='{') stack[++top]=ch;
        else if(ch==')'||ch==']'||ch=='}'){
            if(top==-1 || !isMatching(stack[top--], ch)) { free(stack); return 0; }
        }
    }
    int res = (top==-1);
    free(stack); return res;
}

int main(){
    char s[256];
    printf("Enter expression: ");
    fgets(s,256,stdin);
    s[strcspn(s,"\n")] = 0;
    printf(isBalanced(s) ? "Balanced\n" : "Not Balanced\n");
    return 0;
}
