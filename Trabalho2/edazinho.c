#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 9223372036854775808
#define MIN -9223372036854775808
#define hash(v,m) (v%m)
#define NULLlc 0

// sondagens = 1+(n*(n-1))/2
// dominacoes = n-1

typedef long int Item;

typedef struct casa{
    long int p;
    double lc;
    double l, c;
}casa;
casa NULLitem = {NULLlc,NULLlc,NULLlc};

#define keyL(A) (A)
#define lessL(A,B) (keyL(A)<keyL(B))
#define exchL(A,B) {casa t=A; A=B; B=t;}

#define key(x) (x.lc)
#define less(a,b) (key(a)<key(b))
#define eq(a,b) ((a)==(b))
#define nullPP(A) (key(pp[A])==key(NULLitem))
#define nullPI(A) (key(pi[A])==key(NULLitem))
#define nullIP(A) (key(ip[A])==key(NULLitem))
#define nullII(A) (key(ii[A])==key(NULLitem))
#define exch(A,B) {casa t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

typedef struct pq_st{
    int N;
    casa *pq;
}pq_st;

typedef struct fila {
  double *l, *c;
  long int N, p, u;
} fila;

static int n, m;
static casa *pp, *pi, *ip, *ii;
static int PP=0, PI=0, IP=0, II=0, isSondaveis=0;
static long int edazinhos=1, t=0;
double sondagens=0;

int desenfileira (fila *f, double *l, double *c){
    if(f->p==f->u) return 0;
    *l = f->l[f->p];
    *c = f->c[f->p];
    f->l[f->p] = NULLlc;
    f->c[f->p] = NULLlc;
    f->p = (f->p+1)%f->N;
    return 1;
}

int enfileira (fila *f, double l, double c){
    if(f!=NULL){
    if((f->p==0 && f->u == f->N-1) || f->u == f->p-1){
        f->l=realloc(f->l, 2*f->N*sizeof(double));
        f->c=realloc(f->c, 2*f->N*sizeof(double));
        if(f->p==0 && f->u == f->N-1){
            f->N*=2;
            if(f->l==NULL || f->c==NULL) return 0; 
        }
        else if(f->u<=(f->N - f->p)){
            int i;
            for(i=0; i<=f->u; i++){
                f->l[f->N+i]=f->l[i];
                f->c[f->N+i]=f->c[i];
            }
            f->u += f->N;
            f->N*=2;
            if(f->l==NULL || f->c==NULL) return 0;
        }
        else{
            int i = 2*f->N-1;
            for(int j = f->N-1; j>=f->u; j--){
                f->l[i]=f->l[j];
                f->c[i]=f->c[j];
                i--;
            }
            f->p += f->N;
            f->N*=2;
            if(f->l==NULL || f->c==NULL) return 0;
        }
    }
    f->l[f->u] = l;
    f->c[f->u] = c;
    f->u = (f->u+1)%f->N;
    return 1;
    }
    return 0;
}

int filaEmpty(fila *f){
    if(f->p==f->u) return 1;
    return 0;
}

void htinit(long int max){
    if(PP==1){
        int i;
        n = 0, m = 2*max;
        pp = malloc (sizeof(casa)*m);
        for(i=0; i<m; i++) pp[i]=NULLitem;
    }
    else if(PI==1){
        int i;
        n = 0, m = 2*max;
        pi = malloc (sizeof(casa)*m);
        for(i=0; i<m; i++) pi[i]=NULLitem;
    }
    else if(IP==1){
        int i;
        n = 0, m = 2*max;
        ip = malloc (sizeof(casa)*m);
        for(i=0; i<m; i++) ip[i]=NULLitem;
    }
    else{
        int i;
        n = 0, m = 2*max;
        ii = malloc (sizeof(casa)*m);
        for(i=0; i<m; i++) ii[i]=NULLitem;
    }
}

void expand();

void htinsert(casa item){
    if(PP==1){
        int v = key(item);
        int i = hash(v,m);
        while(!nullPP(i)) i=(i+1)%m;
        pp[i]=item;
        n++;
        if(n>=m/2) expand();
    }
    else if(PI==1){
        int v = key(item);
        int i = hash(v,m);
        while(!nullPI(i)) i=(i+1)%m;
        pi[i]=item;
        n++;
        if(n>=m/2) expand();
    }
    else if(IP==1){
        int v = key(item);
        int i = hash(v,m);
        while(!nullIP(i)) i=(i+1)%m;
        ip[i]=item;
        n++;
        if(n>=m/2) expand();
    }
    else{
        int v = key(item);
        int i = hash(v,m);
        while(!nullII(i)) i=(i+1)%m;
        ii[i]=item;
        n++;
        if(n>=m/2) expand();
    }
}

void expand(){
    if(PP==1){
        int i;
        casa *t = pp;
        pp = malloc(sizeof(casa)*m*2);
        m*=2;
        for(i=0; i<m/2; i++){
            if(key(t[i])!=key(NULLitem)){
                htinsert(t[i]);
            }
        }
        free(t);
    }
    else if(PI==1){
        int i;
        casa *t = pi;
        pi = malloc(sizeof(casa)*m*2);
        m*=2;
        for(i=0; i<m/2; i++){
            if(key(t[i])!=key(NULLitem)){
                htinsert(t[i]);
            }
        }
        free(t);
    }
    else if(IP==1){
        int i;
        casa *t = ip;
        ip = malloc(sizeof(casa)*m*2);
        m*=2;
        for(i=0; i<m/2; i++){
            if(key(t[i])!=key(NULLitem)){
                htinsert(t[i]);
            }
        }
        free(t);
    }
    else{
        int i;
        casa *t = ii;
        ii = malloc(sizeof(casa)*m*2);
        m*=2;
        for(i=0; i<m/2; i++){
            if(key(t[i])!=key(NULLitem)){
                htinsert(t[i]);
            }
        }
        free(t);
    }
}

casa htsearch(int v){
    if(PP==1){
        int i = hash(v,m);
        while(!nullPP(i)){
            if(eq(v,key(pp[i])))
                return pp[i];
            else i = (i+1)%m;
        }
        return NULLitem;
    }
    else if(PI==1){
        int i = hash(v,m);
        while(!nullPI(i)){
            if(eq(v,key(pi[i])))
                return pi[i];
            else i = (i+1)%m;
        }
        return NULLitem;
    }
    else if(IP==1){
        int i = hash(v,m);
        while(!nullIP(i)){
            if(eq(v,key(ip[i])))
                return ip[i];
            else i = (i+1)%m;
        }
        return NULLitem;
    }
    else{
        int i = hash(v,m);
        while(!nullII(i)){
            if(eq(v,key(ii[i])))
                return ii[i];
            else i = (i+1)%m;
        }
        return NULLitem;
    }
}

void fixUp(pq_st *PQ, int k)
{
  while(k>1 && lessL(PQ->pq[k/2].p,PQ->pq[k].p))
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
    if(j<N && lessL(PQ->pq[j].p,PQ->pq[j+1].p)) j++;
    if(!lessL(PQ->pq[k].p,PQ->pq[j].p)) break;
    exchL(PQ->pq[k],PQ->pq[j]);
    k=j;
  }
}

void PQinit( int max, pq_st *PQ)
{
  PQ->pq=malloc(sizeof(casa)*(max+1));
  PQ->N=0;
}

int PQempty(pq_st *PQ)
{
  return PQ->N==0;
}

void PQinsert(pq_st *PQ, casa v){
    if(sondagens>=t-1){
        if(v.p > PQ->pq[PQ->N].p){
            PQ->pq[PQ->N]=v;
            fixUp(PQ, PQ->N);
        }
    }
    else {
        PQ->pq[++PQ->N]=v;
        fixUp(PQ, PQ->N);
    }
}

casa PQdelMax(pq_st *PQ)
{
  exchL(PQ->pq[1],PQ->pq[PQ->N]);
  fixDown(PQ,1,PQ->N-1);
  return PQ->pq[PQ->N--];
}

double potencia(int a, int b){
    if (b == 0)
        return 1;
    else
        return a * potencia(a, b - 1);
}

double juntaNumeros(double l, double c){
  char n1[20], n2[20];
  sprintf(n1, "%.0lf", l);
  sprintf(n2, "%.0lf", c);
  int tam1=strlen(n1)-1;
  int tam2=strlen(n2)-1;
  if(n1[0]=='-'){
    memmove(&n1[0], &n1[0 + 1], strlen(n1) - 0);
    tam1--;
  } 
  if(n2[0]=='-'){
    memmove(&n2[0], &n2[0 + 1], strlen(n2) - 0);
    tam2--;
  } 
  while(tam1>3){
    memmove(&n1[0], &n1[0 + 1], strlen(n1) - 0);
    tam1--;
  }
  while(tam2>3){
    memmove(&n2[0], &n2[0 + 1], strlen(n2) - 0);
    tam2--;
  }
  if(n1[0]=='0' && n1[1]=='0' && n1[2]=='0' && n1[3]=='0')n1[0]='9';
  if(n2[0]=='0' && n2[1]=='0' && n2[2]=='0' && n2[3]=='0')n2[0]='9';
  if(tam1==0 && n1[0]=='0'){
      n1[0]='9';
      n1[1]='9';
      n1[2]='9';
      n1[3]='9';
      n1[4]='\0';
  }
  if(tam2==0 && n2[0]=='0'){
      n2[0]='9';
      n2[1]='9';
      n2[2]='9';
      n2[3]='9';
      n2[4]='\0';
  }
  return atof(strcat(n1, n2));
}

void setSinais(double l, double c){
    if(l>=0 && c>=0){
        PP=1;
        PI=0;
        IP=0;
        II=0;
    }
    else if(l>=0 && c<0){
        PP=0;
        PI=1;
        IP=0;
        II=0;
    }
    else if(l<0 && c>=0){
        PP=0;
        PI=0;
        IP=1;
        II=0;
    }
    else{
        PP=0;
        PI=0;
        IP=0;
        II=1;
    }
}

void addHash(double l, double c){
    setSinais(l, c);
    casa aux;
    double lc = juntaNumeros(l, c);
    aux.lc = lc;
    aux.l = l;
    aux.c = c;
    aux.p = 0;
    htinsert(aux);
}

void lerResposta(char *comando, long int qtd, pq_st *PQ){
    double l, c, p;
    for(int i=0; i<qtd; i++){
        scanf("%s ", comando);
        if(comando[0]=='s'){
            sondagens++;
            scanf("%lf %lf %lf", &l, &c, &p);
            casa nova;
            nova.l=l;
            nova.c=c;
            nova.p=p;
            nova.lc=NULLlc;
            PQinsert(PQ, nova);
            addHash(l, c);
        }
        else scanf("%lf", &p);
    }
}

void fimTurno(){
    printf("fimturno\n");
    fflush(stdout);
}

void sondar(double l, double c){
    printf("sondar %.0lf %.0lf\n", l, c);
}

void dominar(double l, double c){
    edazinhos++;
    printf("dominar %.0lf %.0lf\n", l, c);
}

void startGame(double l, double c, double p, long int t){

    char comando[10];

    sondar(l+1, c+1);
    addHash(l+1, c+1);
    fimTurno();

    scanf("%s %lf %lf %lf", comando, &l, &c, &p);
    dominar(l, c);
    sondar(l-2, c-2);
    addHash(l-2, c-2);
    fimTurno();

    scanf("%s ", comando);
    if(comando[0]=='s') scanf("%lf %lf %lf", &l, &c, &p);
    else scanf("%lf", &p);
    scanf("%s ", comando);
    if(comando[0]=='s') scanf("%lf %lf %lf", &l, &c, &p);
    else scanf("%lf", &p);
    dominar(l, c);
    sondar(l+3, c+3);
    addHash(l+3, c+3);
    sondar(l+3, c+2);
    addHash(l+3, c+2);
    fimTurno();
}

void initHash(long int maxSondagens){
    PP=1;
    htinit(maxSondagens);
    PP=0;
    PI=1;
    htinit(maxSondagens);
    PI=0;
    IP=1;
    htinit(maxSondagens);
    IP=0;
    II=1;
    htinit(maxSondagens);
    II=0;
}

void setSondaveis(fila *f, double l, double c){
    enfileira(f, l, c+1);
    enfileira(f, l-1, c+1);
    enfileira(f, l-1, c);
    enfileira(f, l, c-1);
    enfileira(f, l+1, c-1);
    enfileira(f, l-2, c);
    enfileira(f, l-2, c-1);
    enfileira(f, l-2, c-2);
    enfileira(f, l-1, c-2);
    enfileira(f, l, c-2);
    enfileira(f, l, c+2);
    addHash(l, c+1);
    addHash(l-1, c+1);
    addHash(l-1, c);
    addHash(l, c-1);
    addHash(l+1, c-1);
    addHash(l-2, c);
    addHash(l-2, c-1);
    addHash(l-2, c-2);
    addHash(l-1, c-2);
    addHash(l, c-2);
    addHash(l, c+2);
}

void setUltimasSondaveis(fila *f, double l, double c){
    double lc;
    setSinais(l, c+1);
    lc = juntaNumeros(l,c+1);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l, c+1);
        addHash(l, c+1);
    }
    setSinais(l+1, c+1);
    lc = juntaNumeros(l+1,c+1);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l+1, c+1);
        addHash(l+1, c+1);
    }
    setSinais(l+1, c);
    lc = juntaNumeros(l+1,c);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l+1, c);
        addHash(l+1, c);
    }
    setSinais(l+1, c-1);
    lc = juntaNumeros(l+1,c-1);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l+1, c-1);
        addHash(l+1, c-1);
    }
    setSinais(l, c-1);
    lc = juntaNumeros(l,c-1);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l, c-1);
        addHash(l, c-1);
    }
    setSinais(l-1, c-1);
    lc = juntaNumeros(l-1,c-1);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l-1, c-1);
        addHash(l-1, c-1);
    }
    setSinais(l-1, c);
    lc = juntaNumeros(l-1,c);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l-1, c);
        addHash(l-1, c);
    }
    setSinais(l-1, c+1);
    lc = juntaNumeros(l-1,c+1);
    if(htsearch(lc).lc==NULLlc){
        enfileira(f, l-1, c+1);
        addHash(l-1, c+1);
    }
}

void imprime(fila *f){
    for(int i=0; i<f->N; i++){
            printf("%.0lf %.0lf | ", f->l[i], f->c[i]);
        }
        printf("\n");
}

void putSondaveis(fila *para, fila *de){
    double l, c;
    while (desenfileira(de, &l, &c)==1){
        enfileira(para, l, c);
    }
}

fila *FilaInit(fila *f, long int tam){
    f = malloc(sizeof(fila));
    f->N = tam;
    f->p = 0;
    f->u = 0;
    f->l = malloc((f->N+1)*sizeof(double));
    f->c = malloc((f->N+1)*sizeof(double));
    return f;
}

int main(){

    double l, c, p, lc;
    char comando[10];
    casa aux;
    pq_st *proxDominacao = malloc(sizeof(pq_st));
    initHash(618033);
    
    scanf("%lf %lf %lf %ld", &l, &c, &p, &t);
    long int maxSondagens = 1+((t*(t-1))/2);
    PQinit(t, proxDominacao);
    fila *sondaveis = FilaInit(sondaveis, maxSondagens);
    setSondaveis(sondaveis, l, c);
    fila *ultimasSondaveis = FilaInit(ultimasSondaveis, 7);
    addHash(l, c);
    startGame(l, c, p, t);
    lerResposta(comando, 3, proxDominacao);
    aux = PQdelMax(proxDominacao);
    dominar(aux.l, aux.c);

    setUltimasSondaveis(ultimasSondaveis, aux.l, aux.c);

    /*imprime(sondaveis);
    imprime(ultimasSondaveis);
    putSondaveis(sondaveis, ultimasSondaveis);
    imprime(sondaveis);
    imprime(ultimasSondaveis);*/

    for(long int i=3; i<t-1; i++){
        long int k=0;
        for(k=0; k<i; k++){
            if(filaEmpty(sondaveis)==1) break;
            desenfileira(sondaveis, &l, &c);
            sondar(l, c);
        }
        fimTurno();
            /*printf("\n");
            imprime(sondaveis);
            printf("\n");
            imprime(ultimasSondaveis);
            printf("\n");*/
        lerResposta(comando, k+1, proxDominacao);
        aux = PQdelMax(proxDominacao);
        dominar(aux.l, aux.c);
        putSondaveis(sondaveis, ultimasSondaveis);
        setUltimasSondaveis(ultimasSondaveis, aux.l, aux.c);
    }
    fimTurno();
    lerResposta(comando, 1, proxDominacao);

    return 0;
}