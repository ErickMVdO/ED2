#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    unsigned long endereco;
    unsigned long ant;
    unsigned long prox;
} no;

typedef int Item;
#define key(A) (A)
#define less(A,B) (key(A)<key(B))
#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

void insertionSort(no *v, int l, int r){
    for(int i=r; i>l; i--){
        if(v[i-1].endereco>v[i].endereco){
            no tmp = v[i-1];
            v[i-1] = v[i];
            v[i] = tmp;
        }
    }
    for(int i=l+2; i<=r; i++){
        int j=i; 
        no aux=v[j];
        while(less(aux.endereco, v[j-1].endereco)){
            v[j]=v[j-1];
            j--;
        }
        v[j]=aux;
    }
}

int busca(no *v, unsigned long num, int r){
    int e=-1, d;
    d=r;
    while(e<d-1){
        int m=(e+d)/2;
        if(v[m].endereco<num) e=m;
        else d=m;
    }
    return d;
}

void imprimeResultado(no *v, no ptr1, no ptr2, int primeiro, int ultimo, int i){

    int index;

    printf("%lx %lx %lx\n", v[primeiro].endereco, v[primeiro].ant, v[primeiro].prox);
    index = busca(v, v[primeiro].prox, i-1);
    while(v[index].prox!=ptr1.endereco){
        printf("%lx %lx %lx\n", v[index].endereco, v[index].ant, v[index].prox);
        index = busca(v, v[index].prox, i-1);
    }

    v[index].prox = ptr2.prox;
    printf("%lx %lx %lx\n", v[index].endereco, v[index].ant, v[index].prox);
    index = busca(v, ptr2.prox, i-1);
    v[index].ant = ptr1.ant;

    while(v[index].endereco!=v[ultimo].endereco){
        printf("%lx %lx %lx\n", v[index].endereco, v[index].ant, v[index].prox);
        index = busca(v, v[index].prox, i-1);
    }
    printf("%lx %lx %lx\n", v[index].endereco, v[index].ant, v[index].prox);

}

void imprimeRemovidos(no *v, no ptr1, no ptr2, int i){

    int index;

    printf("\n");
    printf("%lx\n", ptr1.endereco);
    index = busca(v, ptr1.prox, i-1);
    while(v[index].endereco!=ptr2.endereco){
        printf("%lx\n", v[index].endereco);
        index = busca(v, v[index].prox, i-1);
    }
    printf("%lx\n", ptr2.endereco);

}

int main(){
 
    no v[250000];
    no ptr1, ptr2, cpm;
    int primeiro, ultimo;
    int i=0;

    while(scanf("%lx %lx %lx", &v[i].endereco, &v[i].ant, &v[i].prox)!=EOF){
        if(i==0) ptr1 = v[i];
        else if(i==1) ptr2 = v[i];
        i++;
    }

    insertionSort(v,0,i-1);

    cpm = ptr1;
    primeiro = busca(v, ptr1.ant, i-1);
    while(v[primeiro].endereco==cpm.ant){
        cpm = v[primeiro];
        primeiro = busca(v, cpm.ant, i-1);
    }

    cpm = ptr2;
    ultimo = busca(v, ptr2.prox, i-1);
    while(v[ultimo].endereco==cpm.prox){
        cpm = v[ultimo];
        ultimo = busca(v, cpm.prox, i-1);
    }
    ultimo--;

    imprimeResultado(v, ptr1, ptr2, primeiro, ultimo, i);

    imprimeRemovidos(v, ptr1, ptr2, i);

    /*printf("\n");
    for(int j=0; j<i-1; j++){
        printf("%lx %lx %lx\n", v[j].endereco, v[j].ant, v[j].prox);
    }*/

    return 0;
}

