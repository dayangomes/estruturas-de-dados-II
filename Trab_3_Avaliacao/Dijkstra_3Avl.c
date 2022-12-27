#include <stdio.h>
#include <stdlib.h>

struct grafo{
    int ponderado;
    int nVertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
};
typedef struct grafo Grafo;
Grafo* criaGrafo(int nVertices, int grau_max, int ponderado){
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL){
        int i;
        gr->nVertices = nVertices;
        gr->grau_max = grau_max;
        gr->ponderado = (ponderado != 0)?1:0;
        gr->grau = (int*) calloc(nVertices,sizeof(int));

        gr->arestas = (int**) malloc(nVertices * sizeof(int*));
        for(i=0; i<nVertices; i++)
            gr->arestas[i] = (int*) malloc(grau_max * sizeof(int));

        if(gr->ponderado){
            gr->pesos = (float**) malloc(nVertices * sizeof(float*));
            for(i=0; i<nVertices; i++)
                gr->pesos[i] = (float*) malloc(grau_max * sizeof(float));
        }

    }
    return gr;
}

void liberaGrafo(Grafo* gr){
    if(gr != NULL){
        int i;
        for(i=0; i<gr->nVertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->ponderado){
            for(i=0; i<gr->nVertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(orig < 0 || orig >= gr->nVertices)
        return 0;
    if(dest < 0 || dest >= gr->nVertices)
        return 0;

    gr->arestas[orig][gr->grau[orig]] = dest;
    if(gr->ponderado)
        gr->pesos[orig][gr->grau[orig]] = peso;
    gr->grau[orig]++;

    if(eh_digrafo == 0)
        insereAresta(gr,dest,orig,1,peso);
    return 1;
}


int procuraMenorDistancia(float *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for(i=0; i < NV; i++){
        if(dist[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    return menor;
}

void menorCaminho(Grafo *gr, int ini, int *ant, float *dist){
    int i, cont, NV, ind, *visitado, vert;
    cont = NV = gr->nVertices;
    visitado = (int*) malloc(NV * sizeof(int));
    for(i=0; i < NV; i++){
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }
    dist[ini] = 0;
    while(cont > 0){
        vert = procuraMenorDistancia(dist, visitado, NV);
        if(vert == -1)
            break;

        visitado[vert] = 1;
        cont--;
        for(i=0; i<gr->grau[vert]; i++){
            ind = gr->arestas[vert][i];
            if(dist[ind] < 0){
               dist[ind] = dist[vert] + gr->pesos[vert][i];
               ant[ind] = vert;
            }else{
                if(dist[ind] > dist[vert] + gr->pesos[vert][i]){
                    dist[ind] = dist[vert] +gr->pesos[vert][i];
                    ant[ind] = vert;
                }
            }
        }
    }
    free(visitado);
}

void mostra(Grafo *gr){
    if(gr != NULL){
        int i, j;
        for(i=0; i < gr->nVertices; i++){
            printf("%d: ", i);
            for(j=0; j < gr->grau[i]; j++){
                if(gr->ponderado)
                    printf("%d(%.2f), ", gr->arestas[i][j], gr->pesos[i][j]);
                else
                    printf("%d, ", gr->arestas[i][j]);
            }
            printf("\n");
        }
    }
    else return NULL;
}

int main(){
    int ehDigrafo = 0;
    Grafo* gr = criaGrafo(10, 10, 1);
    insereAresta(gr,0,1,ehDigrafo,60);
    insereAresta(gr,0,2,ehDigrafo,54);
    insereAresta(gr,0,3,ehDigrafo,42);
    insereAresta(gr,1,4,ehDigrafo,29);
    insereAresta(gr,1,3,ehDigrafo,71);
    insereAresta(gr,2,3,ehDigrafo,56);
    insereAresta(gr,2,5,ehDigrafo,67);
    insereAresta(gr,3,4,ehDigrafo,52);
    insereAresta(gr,3,6,ehDigrafo,87);
    insereAresta(gr,3,5,ehDigrafo,26);
    insereAresta(gr,4,7,ehDigrafo,25);
    insereAresta(gr,4,6,ehDigrafo,20);
    insereAresta(gr,5,6,ehDigrafo,70);
    insereAresta(gr,5,8,ehDigrafo,73);
    insereAresta(gr,6,7,ehDigrafo,36);
    insereAresta(gr,6,8,ehDigrafo,59);
    insereAresta(gr,6,9,ehDigrafo,32);
    insereAresta(gr,7,9,ehDigrafo,25);
    insereAresta(gr,8,9,ehDigrafo,26);
    
	mostra(gr);
	printf("\n");
    int i,ant[10];
    float dist[10];
    menorCaminho(gr, 0, ant, dist);
    for(i=0; i<10; i++)
        printf("%d: %d -> %f\n",i,ant[i],dist[i]);
    liberaGrafo(gr);

    system("pause");
    return 0;
}
