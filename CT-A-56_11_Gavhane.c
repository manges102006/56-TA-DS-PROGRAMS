#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

double evalPostfix(const char *exp){
    int n = strlen(exp); double stack[256]; int top=-1;
    for(int i=0;i<n;i++){
        if(isspace(exp[i])) continue;
        if(isdigit(exp[i])){
            double val = 0;
            while(i<n && isdigit(exp[i])) { val = val*10 + (exp[i]-'0'); i++; }
            if(i<n && exp[i]=='.'){
                i++; double frac=0, div=1;
                while(i<n && isdigit(exp[i])) { frac = frac*10 + (exp[i]-'0'); div*=10; i++; }
                val += frac/div;
            }
            stack[++top] = val; i--;
        } else {
            double b = stack[top--]; double a = stack[top--];
            switch(exp[i]){
                case '+': stack[++top]=a+b; break;
                case '-': stack[++top]=a-b; break;
                case '*': stack[++top]=a*b; break;
                case '/': stack[++top]=a/b; break;
                case '^': {
                    double res=1; for(int j=0;j<(int)b;j++) res*=a;
                    stack[++top]=res; break;
                }
            }
        }
    }
    return stack[top];
}

int main(){
    char exp[256];
    printf("Enter postfix expression (space separated tokens, e.g. \"3 4 + 2 *\"): ");
    fgets(exp,256,stdin); exp[strcspn(exp,"\n")]=0;
    printf("Result: %g\n", evalPostfix(exp));
    return 0;
}
