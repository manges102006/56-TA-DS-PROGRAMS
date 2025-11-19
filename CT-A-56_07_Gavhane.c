#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int prec(char c){
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    if(c=='^') return 3;
    return -1;
}

void infixToPostfix(char *exp){
    int l = strlen(exp);
    char *stack = malloc(l);
    int top = -1;
    char output[512]; int k=0;
    for(int i=0;i<l;i++){
        char c = exp[i];
        if(isspace(c)) continue;
        if(isalnum(c)) output[k++]=c;
        else if(c=='(') stack[++top]=c;
        else if(c==')'){
            while(top!=-1 && stack[top]!='(') output[k++]=stack[top--];
            if(top!=-1) top--;
        } else {
            while(top!=-1 && ((prec(stack[top])>prec(c)) || (prec(stack[top])==prec(c) && c!='^')) && stack[top]!='(')
                output[k++]=stack[top--];
            stack[++top]=c;
        }
    }
    while(top!=-1) output[k++]=stack[top--];
    output[k]='\0';
    printf("Postfix: %s\n", output);
    free(stack);
}

int main(){
    char exp[256];
    printf("Enter infix expression (single-letter operands): ");
    fgets(exp,256,stdin); exp[strcspn(exp,"\n")]=0;
    infixToPostfix(exp);
    return 0;
}
