#include <stdio.h>
#include <stdlib.h>

typedef struct linha{
    int n;
    char c;
}linha; 

#define key(x) (x.n)
#define less(a,b) (key(a)<key(b))
#define eq(a,b) ((a)==(b))
#define exch(A,B) {linha t=A; A=B; B=t;}
#define cmpexch(A,B) {if(less(B,A)) exch(A,B);}

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

int main(){

    char c;
    int i=0, tam=50, n;
    linha *l = malloc(tam*sizeof(linha));

    while(scanf("%d %c", &n, &c)!=EOF){
            l[i].n = n;
            l[i].c = c;
            if(i==tam-1){
              l = realloc(l, 2*tam*sizeof(linha));
              tam*=2;
            }
            i++;
    }

    quicksort(l, 0, i-1);

    for(int j=0; j<i; j++){
      if(l[j].n!=l[j+1].n)
        printf("%c", l[j].c);
    }
    printf("\n");
    free(l);

    return 0;
}