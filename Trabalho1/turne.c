#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula {
   char str[27];
   struct celula *prox;
} celula;

int desenfileira (celula *f, char *y){
    celula *lixo = f->prox;
    if(lixo!=NULL){
        f->prox = lixo->prox;
        strcpy(y,lixo->str);
        lixo=NULL;
        free(lixo);
        return 1;
    }
    return 0;
}

celula *enfileira (celula *f, char *x){
    if(f!=NULL){
      celula *novo = malloc(sizeof(celula));
      novo->prox = f->prox;
      f->prox=novo;
      strcpy(f->str,x);
      return novo;
    }
    return NULL;
}

void imprime(celula *le){
    for(celula *elem = le->prox; elem!=le; elem=elem->prox){
        printf("%s -> ", elem->str);
    }
    printf("NULL\n");
}


int main(){

    char cidade[27], y[27];
    celula *p = malloc(sizeof(celula));
    p->prox=p;
    int i=0;

    while(scanf("%s", cidade)!=EOF){
        p = enfileira(p, cidade);
    }

    for(celula *elem = p; elem->prox!=elem; ){
        desenfileira(elem,y);
        printf("%s\n", y);
        int tam = strlen(y);
        if(y[tam-1]==elem->prox->str[0]+32){
            desenfileira(elem,y);
            elem = enfileira(elem,y);
        }
    }

    return 0;
}