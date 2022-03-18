#include <stdio.h>

typedef int Item;
#define key(A) (A)
#define less(A,B) (key(A)<key(B))
#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

void insertionSort(Item *v, int l, int r){
    for(int i=r; i>l; i--){
        cmpexch(v[i-1], v[i]);
    }
    for(int i=l+2; i<=r; i++){
        int j=i, aux=v[j];
        while(less(aux, v[j-1])){
            v[j]=v[j-1];
            j--;
        }
        v[j]=aux;
    }
}

int main(){

    Item v[50001];
    int i=0;

    while(scanf("%d", &v[i])==1){
        i++;
    }
    insertionSort(v, 0, i-1);

    for(int j=0; j<i; j++){
        if(j==0) printf("%d", v[j]);
        else printf(" %d", v[j]);
    }
    printf("\n");

    return 0;
}