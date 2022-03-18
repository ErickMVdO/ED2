#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define hash(v,m) (v%m)

typedef struct linha{
    int n;
    char c;
}linha; 
linha NULLitem = {0,0};

#define key(x) (x.n)
#define less(a,b) (key(a)<key(b))
#define eq(a,b) ((a)==(b))
#define null(A) (key(ht[A])==key(NULLitem))
#define exch(A,B) {linha t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

static int n, m;
static linha *ht;

int separa(linha *V,int l,int r)
{
  linha c=V[r];
  int j=l;
  for(int k=l;k<r;k++)
    if(less(V[k],c))
    {
      exch(V[k],V[j]);
      j++;
    }
  exch(V[j],V[r]);
  return j;
}

void quicksort(linha *V,int l, int r)
{
  if (r<=l) return;

  cmpexch(V[(l+r)/2],V[r]);
  cmpexch(V[l],V[(l+r)/2]);
  cmpexch(V[r],V[(l+r)/2]);

  int j=separa(V,l,r);
  quicksort(V,l,j-1);
  quicksort(V,j+1,r);
}

void htinit(int max){
    int i;
    n = 0, m = 2*max;
    ht = malloc (sizeof(linha)*m);
    for(i=0; i<m; i++) ht[i]=NULLitem;
}

void expand();

void htinsert(linha item){
    int v = key(item);
    int i = hash(v,m);
    while(!null(i)) i=(i+1)%m;
    ht[i]=item;
    n++;
    if(n>=m/2) expand();
}

void expand(){
    int i;
    linha *t = ht;
    ht = malloc(sizeof(linha)*m*2);
    m*=2;
    for(i=0; i<m/2; i++){
        if(key(t[i])!=key(NULLitem)){
            htinsert(t[i]);
        }
    }
    free(t);
}

linha htsearch(int v){
    int i = hash(v,m);
    while(!null(i)){
        if(eq(v,key(ht[i])))
            return ht[i];
        else i = (i+1)%m;
    }
    return NULLitem;
}

int main(){

    char c;
    int i=0, tam=50, n;
    linha *l = malloc(tam*sizeof(linha));
    htinit(618033);

    while(scanf("%d %c", &n, &c)!=EOF){
      linha t = htsearch(n);
        if(t.n==0){
            t.n = n;
            t.c = c;
            htinsert(t);
            l[i].n=n;
            l[i].c=c;
            if(i==tam-1){
              l = realloc(l, 2*tam*sizeof(linha));
              tam*=2;
            }
            i++;
        }
    }

    quicksort(l, 0, i-1);

    for(int j=0; j<i; j++){
        printf("%c", l[j].c);
    }
    printf("\n");
    free(l);

    return 0;
}