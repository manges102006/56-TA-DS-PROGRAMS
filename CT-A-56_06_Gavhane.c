#include <stdio.h>

void decToBinary(unsigned int n){
    if(n==0){ printf("0\n"); return; }
    int bits[32], i=0;
    while(n>0){ bits[i++]=n%2; n/=2; }
    for(int j=i-1;j>=0;j--) printf("%d", bits[j]);
    printf("\n");
}

int main(){
    unsigned int x;
    printf("Enter decimal: ");
    if(scanf("%u",&x)!=1) return 0;
    decToBinary(x);
    return 0;
}
