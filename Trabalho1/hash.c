#include <stdio.h>
#include <stdlib.h>

#define hash(v,m) (v%m)
#define hashtwo(v,m) (v%97)

typedef struct Item{
    int n;
    char c;
}Item; 
Item NULLitem = {0,0};

#define key(x) (x.n)
#define less(a,b) (key(a)<key(b))
#define eq(a,b) ((a)==(b))
#define null(A) (key(ht[A])==key(NULLitem))

static int n, m;
static Item *ht;

void htinit(int max){
    int i;
    n = 0, m = 2*max;
    ht = malloc (sizeof(Item)*m);
    for(i=0; i<m; i++) ht[i]=NULLitem;
}

int htcount() {return n;}

void expand();

void htinsert(Item item){
    int v = key(item);
    int i = hash(v,m);
    int k = hashtwo(v,m);
    while(!null(i)) i=(i+k)%m;
    ht[i]=item;
    n++;
    if(n>=m/2) expand();
}

void expand(){
    int i;
    Item *t = ht;
    ht = malloc(sizeof(Item)*m*2);
    m*=2;
    for(i=0; i<m/2; i++){
        if(key(t[i])!=key(NULLitem)){
            htinsert(t[i]);
        }
    }
    free(t);
}

Item htsearch(int v){
    int i = hash(v,m);
    int k = hashtwo(v,m);
    while(!null(i)){
        if(eq(v,key(ht[i])))
            return ht[i];
        else i = (i+k)%m;
    }
    return NULLitem;
}

int main(){

    Item v;
    int n;

    htinit(10);
    
    v.n = 1;
    v.c = 'a';
    htinsert(v);
    v.n = 2;
    htinsert(v);
    v.n = 3;
    htinsert(v);
    v.n = 4;
    htinsert(v);
    v.n = 5;
    htinsert(v);
    v.n = 6;
    htinsert(v);
    v.n = 7;
    htinsert(v);
    v.n = 8;
    htinsert(v);
    v.n = 9;
    htinsert(v);
    v.n = 10;
    htinsert(v);

    scanf("%d", &n);
    while (n!=0){
        Item t = htsearch(n);
        printf("%d\n", t.n);
        scanf("%d", &n);
    }
    

    return 0;
}
