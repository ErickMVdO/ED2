#include <stdio.h>
#include <stdlib.h>

static int cnt, pre[5001], maior=1, maiorCidade, tam, cid=0;

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

int GRAPHInsertE(Graph G, Edge e){
    int v = e.v; int w=e.w;
    if(G->adj[v][w] == 0) G->E++;
    G->adj[v][w]=1;
    G->adj[w][v]=1; // Nao dirigido

    return 1;
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
}

int GRAPHSearch(Graph G) {
	int conexos = 0;
	for (int i = 0; i < G->V; i++) {
		if (pre[i] == -1) {
            cnt=0;
            cid++;
			dfsR(G, EDGE(i, i));
            if(cnt>maior){
                maior=cnt;
			    conexos=i;
            }
		}
	}
	return conexos;
}

int GRAPHReach(Graph G, int s, int t) {

	return G->tc[s][t];
}

void GRAPHFtc(Graph G) {
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


int GRAPHConte(Graph G, int joao) {
    int maior=0, contador=0, cidade, maiorJoao;

	for (int i = 0; i < G->V; i++) {
		for (int j = 0; j < G->V; j++){
			if (GRAPHReach(G, i, j)){
                contador++;
                if(contador>maior){
                    maior = contador;
                    cidade = i;
                }
			}
			if(i==joao) maiorJoao = contador;
        }
        contador = 0;
	}

	if(maiorJoao == maior) return joao;
	else return cidade;
}



int main (void) {
	int qtd, v1, v2, cidadeJoao, cidadeLocalizada, confirma;

	scanf("%d %d", &qtd, &cidadeJoao);
	Graph G = GRAPHinit(qtd);

	while(scanf("%d %d", &v1, &v2) != EOF){
        confirma = GRAPHInsertE(G, EDGE(v1,v2));
	}

	cnt = 0;
	for (int i = 0; i < G->V; i++) pre[i] = -1;
    dfsR(G, EDGE(cidadeJoao, cidadeJoao));
    tam=cnt;

    cidadeLocalizada = GRAPHSearch(G);

    if(maior==1 && tam==1) printf("Fique em casa\n");
    else if(tam >= maior || pre[maiorCidade] == pre[cidadeJoao]) printf("Bora para estrada\n");
	else printf("Vamos para %d\n", cidadeLocalizada);
	return 0;
}