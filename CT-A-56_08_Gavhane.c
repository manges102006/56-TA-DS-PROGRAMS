#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void reverseStr(char *s){
    int i=0,j=strlen(s)-1;
    while(i<j){ char t=s[i]; s[i]=s[j]; s[j]=t; i++; j--; }
}
void swapParen(char *s){
    for(int i=0;i<strlen(s);i++){
        if(s[i]=='(') s[i]=')';
        else if(s[i]==')') s[i]='(';
    }
}
int prec(char c){
    if(c=='+'||c=='-') return 1;
    if(c=='*'||c=='/') return 2;
    if(c=='^') return 3;
    return -1;
}

char* infixToPostfix(const char *exp){
    int l=strlen(exp);
    char *stack = malloc(l);
    int top=-1; char *out = malloc(512); int k=0;
    for(int i=0;i<l;i++){
        char c=exp[i];
        if(isspace(c)) continue;
        if(isalnum(c)) out[k++]=c;
        else if(c=='(') stack[++top]=c;
        else if(c==')'){
            while(top!=-1 && stack[top]!='(') out[k++]=stack[top--];
            if(top!=-1) top--;
        } else {
            while(top!=-1 && ((prec(stack[top])>prec(c)) || (prec(stack[top])==prec(c) && c!='^')) && stack[top]!='(')
                out[k++]=stack[top--];
            stack[++top]=c;
        }
    }
    while(top!=-1) out[k++]=stack[top--];
    out[k]='\0';
    free(stack); return out;
}

void infixToPrefix(char *exp){
    reverseStr(exp); swapParen(exp);
    char *post = infixToPostfix(exp);
    reverseStr(post);
    printf("Prefix: %s\n", post);
    free(post);
}

int main(){
    char s[256];
    printf("Enter infix (single-letter operands): ");
    fgets(s,256,stdin); s[strcspn(s,"\n")]=0;
    infixToPrefix(s);
    return 0;
}
