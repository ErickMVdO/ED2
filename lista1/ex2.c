#include <stdio.h>

typedef int Item;
#define key(A) (A)
#define less(A,B) (key(A)<key(B))
#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

void selectionSort(Item *v, int l, int r){
    if(l==r) return;
    for(int i=l+1; i<=r; i++){
    int menor = l;
        if(less(v[i], v[menor])){
            menor=i;
        }
        exch(v[l], v[menor]);
    }
    selectionSort(v, l+1, r);
}

int main(){

    Item v[1001];
    int i=0;

    while(scanf("%d", &v[i])==1){
        i++;
    }
    selectionSort(v, 0, i-1);

    for(int j=0; j<i; j++){
        if(j==0) printf("%d", v[j]);
        else printf(" %d", v[j]);
    }
    printf("\n");

    return 0;
}