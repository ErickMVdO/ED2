#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cnt, pre[5001], aux=0, maior=0;

typedef struct Animal{
    char nome[31];
    int n;
} Animal;

typedef struct{
    int v;
    int w;
} Edge;

Edge EDGE(int v, int w){
    Edge EDGE;
    EDGE.v = v;
    EDGE.w = w;
    return EDGE;
};

typedef struct graph *Graph;

struct graph {
    int V;
    int E;
    int **adj;
    int **tc;
};


int **MATRIXInit(int w, int h, int value) {
	int **arr = malloc(sizeof(*arr) * w);
	for (int i = 0; i < w; i++)
		arr[i] = malloc(sizeof(int) * h);
	return arr;
}

Graph GRAPHinit(int v){
    Graph G = malloc(sizeof(*G));
    G->V = v; G->E= 0;
    G->adj=MATRIXInit(v,v,0);
    return G;
}

void GRAPHInsertE(Graph G, Edge e){
    int v = e.v; int w=e.w;
    if(G->adj[v][w] == 0) G->E++;
    G->adj[v][w]=1;
    G->adj[w][v]=1; // Nao dirigido
}


int GRAPHEdges(Edge a[], Graph G){
    int v,w,E=0;
    for(v=0; v<G->V;v++){
        for(w=v+1; w<G->V;w++){
            if (G->adj[v][w] == 1)
            a[E++]=EDGE(v,w);
        }
    }
    return E;
}


void GRAPHFt(Graph G) {
	int s, i, t;
	G->tc = MATRIXInit(G->V, G->V, 0);
	for (s = 0; s < G->V; s++){
		for (t = 0; t < G->V; t++){
			G->tc[s][t] = G->adj[s][t];
		}
	}
	for (s = 0; s < G->V; s++) {
		G->tc[s][s] = 1;
	}
	for (i = 0; i < G->V; i++){
		for (s = 0; s < G->V; s++){
			if (G->tc[s][i] == 1){
				for (t = 0; t < G->V; t++){
					if (G->tc[i][t] == 1)
						G->tc[s][t] = 1;
				}
			}
		}
	}
}


void GRAPHshow( Graph G) {
   for (int v = 0; v < G->V; ++v) {
      printf( "%2d:", v);
      for (int w = 0; w < G->V; ++w)
         if (G->adj[v][w] == 1)
            printf( " %2d", w);
      printf( "\n");
   }
}

void dfsR(Graph G, Edge e) {
	int w = e.w;
	pre[w] = cnt++;
	for(int i = 0; i < G->V; i++) {
		if (G->adj[w][i] != 0){
            if (pre[i] == -1) dfsR(G, EDGE(w, i));
        }
	}
    aux++;
}

int GRAPHSearch(Graph G) {
	int conexos = 0;
	cnt = 0;
	for (int i = 0; i < G->V; i++) pre[i] = -1;
	for (int i = 0; i < G->V; i++) {
		if (pre[i] == -1) {
            aux=0;
			dfsR(G, EDGE(i, i));
            if(aux>maior) maior=aux;
			conexos++;
		}
	}
	return conexos;
}

int find(Animal *a, char *animal, int tam){
    for(int i=0; i<tam; i++){
        if(strcmp(a[i].nome, animal)==0){
            return a[i].n;
        }
    }
    return -1;
}

int main(){

    int c, r;
    char animal[31], predador[31];

    scanf("%d %d", &c, &r);
    while (c!=0 || r!=0){
       Graph G = GRAPHinit(c);
        Animal *a = malloc(c*sizeof(Animal));
        for(int i=0; i<c; i++){
            scanf(" %[^\n]", a[i].nome);
            a[i].n=i;
        }

        for(int i=0; i<r; i++){
            scanf("%s %s", animal, predador);
            int v1 = find(a, animal, c);
            int v2 = find(a, predador, c);
            GRAPHInsertE(G, EDGE(v1,v2));
        }
        GRAPHSearch(G);
        printf("%d\n", maior); 
        maior=0;
        scanf("%d %d", &c, &r);
    }

    return 0;
}