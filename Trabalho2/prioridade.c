#include <stdio.h>
#include <stdlib.h>

typedef int Item;
#define key(A) (A)
#define less(A,B) (key(A)<key(B))
//#define exch(A,B) {Item t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

Item *data;

typedef struct casa{
    Item n;
    int posicao;
}casa;

typedef struct pq_ist{
    int N;
    casa *pq; //fila de prioridades
    casa *qp; //mantem a posição da heap para o elemento de índice K
}pq_ist;

void exch(pq_ist *PQ, casa i, casa j){
    casa t;
    t=PQ->qp[i.n]; PQ->qp[i.n]=PQ->qp[j.n]; PQ->qp[j.n]=t;
    PQ->pq[PQ->qp[i.n].n]=i; PQ->pq[PQ->qp[j.n].n]=j;
}

/*
* *v = fila de prioridades
* K = índice do vetor para fazer o ajuste
*/
void fixUp(pq_ist *PQ, int K){
    while(K>1 && less(PQ->pq[K/2].n, PQ->pq[K].n)){
        exch(PQ, PQ->pq[K], PQ->pq[K/2]);
        K=K/2;
    }
}

/*
* *v = fila de prioridades
* K = índice do vetor para fazer o ajuste
* N = tamanho da fila
*/
void fixDown(pq_ist *PQ, int K, int N){
    int j;
    while(2*K<=N){
        j=2*K;
        if(j<N && less(PQ->pq[j].n, PQ->pq[j+1].n)) j++;
        if(!less(PQ->pq[K].n, PQ->pq[j].n)) break;
        exch(PQ, PQ->pq[K], PQ->pq[j]);
        K=j;
    }
}

void PQinit(int max, pq_ist *PQ){
    PQ->N = 0;
    PQ->pq = malloc(sizeof(Item)*(max+1));
    PQ->qp = malloc(sizeof(Item)*(max+1));
}

int PQempty(pq_ist *PQ){
    return !PQ->N;
}

void PQinsert(pq_ist *PQ, casa K){
    printf("%d\n", K.n);
    PQ->qp[K.n].n = ++PQ->N;
    PQ->pq[PQ->N]=K;
    fixUp(PQ, PQ->N);
}

Item PQdelMax(pq_ist *PQ){
    exch(PQ, PQ->pq[1], PQ->pq[PQ->N]);
    fixDown(PQ, 1, --PQ->N);
    return PQ->pq[PQ->N+1].posicao;
}

/*void PQchange(pq_ist *PQ, int K){
    fixUp(PQ, PQ->qp[K]);
    fixDown(PQ, PQ->qp[K], PQ->N);
}*/

int main (){

    casa v[10] = {{10, 0}, {5, 1}, {20, 2}, {15, 3}, {12, 4}};
    int k;
    pq_ist *PQ = malloc(sizeof(pq_ist));
    PQinit(10, PQ);
    for(k=0;k<=4;k++) PQinsert(PQ, v[k]);
    printf("%d\n", PQdelMax(PQ));
    /*int aux = teste->N;
    printf("N:%d, pq:%d, qp:%d\n", teste->N+1, teste->pq[4], teste->qp[10]);*/
    //for(k=4;k>=0;k--) v[k]=PQdelMax(PQ);

    /*for(int i=0; i<5; i++) printf("%d ", v[i]);
    printf("\n");
    printf("%d\n", PQdelMax(PQ));*/

    return 0;
}