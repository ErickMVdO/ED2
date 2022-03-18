#include <stdio.h>

typedef int Item;
#define key(A) (A)
#define less(A,B) (key(A)<key(B))
#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

void bubbleSort(Item *v, int l, int r){
    if(l==r) return;
    for(int i=l; i<r; i++){
        cmpexch(v[i], v[i+1]);
    }
    bubbleSort(v, l, r-1);
}

int main(){

    Item v[1001];
    int i=0;

    while(scanf("%d", &v[i])==1){
        i++;
    }

    bubbleSort(v, 0, i-1);

    for(int j=0; j<i; j++){
        if(j==0) printf("%d", v[j]);
        else printf(" %d", v[j]);
    }
    printf("\n");

    return 0;
}