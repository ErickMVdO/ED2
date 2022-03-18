#include <stdio.h>
#include <stdlib.h>

typedef int Item;
#define key(A) (A)
#define less(A,B) (key(A)<key(B))
#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct comando{
    int cod;
    char com[16];
}comando;

int busca(comando *v, int num, int r){
    int e=-1, d;
    d=r;
    while(e<d-1){
        int m=(e+d)/2;
        if(v[m].cod<num) e=m;
        else d=m;
    }
    return d;
}

void insertionSort(comando *v, int l, int r){
    for(int i=r; i>l; i--){
        if(v[i-1].cod>v[i].cod){
            comando tmp = v[i-1];
            v[i-1] = v[i];
            v[i] = tmp;
        }
    }
    for(int i=l+2; i<=r; i++){
        int j=i; 
        comando aux=v[j];
        while(less(aux.cod, v[j-1].cod)){
            v[j]=v[j-1];
            j--;
        }
        v[j]=aux;
    }
}

int main(){

    int n, cod, posicao;

    scanf("%d", &n);
    comando *v = malloc(n*sizeof(comando));

    for(int i=0; i<n; i++){
        scanf("%d %s", &v[i].cod, v[i].com);
    }

    insertionSort(v, 0, n-1);

    while(scanf("%d", &cod)==1){
        posicao = busca(v, cod, n-1);
        if(v[posicao].cod==cod) printf("%s\n", v[posicao].com);
        else printf("undefined\n");
    }

    return 0;
}