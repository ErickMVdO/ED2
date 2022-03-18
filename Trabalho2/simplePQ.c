#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct casa{
    Item n;
    int posicao;
}casa;

#define keyL(A) (A)
#define lessL(A,B) (keyL(A)<keyL(B))
#define exchL(A,B) {casa t=A; A=B; B=t;}


typedef struct pq_st{
    int N;
    casa *pq; //mantem a posição da heap para o elemento de índice K
}pq_st;

void fixUp(pq_st *PQ, int k)
{
  while(k>1 && lessL(PQ->pq[k/2].n,PQ->pq[k].n))
  {
    exchL(PQ->pq[k],PQ->pq[k/2]);
    k=k/2;
  }
}

void fixDown(pq_st *PQ, int k, int N)
{
  int j;
  while(2*k <= N)
  {
    j=2*k;
    if(j<N && lessL(PQ->pq[j].n,PQ->pq[j+1].n)) j++;
    if(!lessL(PQ->pq[k].n,PQ->pq[j].n)) break;
    exchL(PQ->pq[k],PQ->pq[j]);
    k=j;
  }
}

void PQinit(pq_st *PQ, int maxN)
{
  PQ->pq=malloc(sizeof(casa)*(maxN+1));
  PQ->N=0;
}

int PQempty(pq_st *PQ)
{
  return PQ->N==0;
}

void PQinsert(pq_st *PQ, casa v)
{
  PQ->pq[++PQ->N]=v;
  fixUp(PQ, PQ->N);
}

Item PQdelMax(pq_st *PQ)
{
  exchL(PQ->pq[1],PQ->pq[PQ->N]);
  fixDown(PQ,1,PQ->N-1);
  return PQ->pq[PQ->N--].n;
}

int main (){

    casa v[10] = {{10, 0}, {5, 1}, {20, 2}, {2, 3}, {17, 4}};
    casa n[2] = {{1, 0}};
    int k;
    pq_st *PQ = malloc(sizeof(pq_st));
    PQinit(PQ, 10);
    for(k=0;k<=4;k++) PQinsert(PQ, v[k]);
    printf("%d\n", PQdelMax(PQ));
    PQinsert(PQ, n[0]);
    printf("%d\n", PQ->pq[PQ->N].n);
    /*int aux = teste->N;
    printf("N:%d, pq:%d, qp:%d\n", teste->N+1, teste->pq[4], teste->qp[10]);*/
    //for(k=4;k>=0;k--) v[k]=PQdelMax(PQ);

    /*for(int i=0; i<5; i++) printf("%d ", v[i]);
    printf("\n");
    printf("%d\n", PQdelMax(PQ));*/

    return 0;
}