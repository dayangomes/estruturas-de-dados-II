#include <stdio.h>
#include <stdlib.h>

typedef struct grafos Grafo;
struct grafos
{
    int ehPonderado;
    int *visitado;
    int nVertices;
    int **arestas;
    float **pesos;
    int *grau;
};

void unvisited(Grafo *gr)
{
    for (int i = 0; i < gr->nVertices; i++)
    {
        gr->visitado[i] = 0;
    }
}

Grafo *criaGrafo(int Vertices, int ehPonderado)
{
    Grafo *gr = (Grafo *)malloc(sizeof(Grafo));

    if (gr != NULL)
    {
        gr->nVertices = Vertices;
        gr->ehPonderado = (ehPonderado != 0) ? 1 : 0;
        gr->grau = (int *)calloc(Vertices, sizeof(int));
        gr->arestas = (int **)malloc(Vertices * sizeof(int *));
        for (int i = 0; i < Vertices; i++)
        {
            gr->arestas[i] = (int *)calloc(Vertices, sizeof(int));
        }
        gr->visitado = (int **)malloc(Vertices * sizeof(int *));
        for (int i = 0; i < Vertices; i++)
        {
            gr->visitado[i] = (int *)calloc(Vertices, sizeof(int));
        }
        if (gr->ehPonderado)
        {
            gr->pesos = (float **)malloc(Vertices * sizeof(float *));
            for (int i = 0; i < Vertices; i++)
            {
                gr->pesos[i] = (float *)calloc(Vertices, sizeof(float));
            }
        }
    }
    return gr;
}

void liberaGrafo(Grafo *gr)
{
    if (gr != NULL)
    {
        int i;
        for (int i = 0; i < gr->nVertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);
        if (gr->ehPonderado)
        {
            for (int i = 0; i < gr->nVertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }
        free(gr->grau);
        free(gr);
    }
}

int insereAresta(Grafo *gr, int origem, int destino, int digrafo, float peso)
{
    int criou = 0;
    if (gr != NULL)
    {
        if (origem >= 0 && origem < gr->nVertices)
        {
            if (destino >= 0 && destino < gr->nVertices)
            {
                gr->arestas[origem][destino] = 1;
                if (gr->ehPonderado)
                    gr->pesos[origem][destino] = peso;
                (gr->grau[origem])++;
                if (digrafo == 0)
                    insereAresta(gr, destino, origem, 1, peso);
                criou = 1;
            }
        }
    }
    return criou;
}

void buscaProfundidade(Grafo *gr, int ini, int cont)
{
    int i, j;
    gr->visitado[ini] = cont;
    for (i = 0; i < gr->nVertices; i++)
    {
        if (gr->arestas[ini][i] == 1 && !gr->visitado[i])
        {
            buscaProfundidade(gr, i, cont + 1);
        }
    }
}
void buscaProfundidade_Grafo(Grafo *gr, int ini)
{
    int i, cont = 1;
    unvisited(gr);
    buscaProfundidade(gr, ini, cont);

    for (i = 0; i < gr->nVertices; i++)
        printf("%d -> %d\n", i, gr->visitado[i]);
}

void buscaLargura_Grafo(Grafo *gr, int ini)
{
    int i, vert, NV, cont = 1;
    int *fila, IF = 0, FF = 0;
    unvisited(gr);

    NV = gr->nVertices;
    fila = (int *)malloc(NV * sizeof(int));
    FF++;
    fila[FF] = ini;
    gr->visitado[ini] = cont;
    while (IF != FF)
    {
        IF = (IF + 1) % NV;
        vert = fila[IF];
        cont++;
        for (i = 0; i < gr->nVertices; i++)
        {
            if (!gr->visitado[i] && gr->arestas[vert][i] == 1)
            {
                FF = (FF + 1) % NV;
                fila[FF] = i;
                gr->visitado[i] = cont;
            }
        }
    }
    free(fila);
    for (i = 0; i < gr->nVertices; i++)
        printf("%d -> %d\n", i, gr->visitado[i]);
}

void mostra(Grafo *gr)
{
    printf("   0 1 2 3 4\n____________\n");
    for (int i = 0; i < gr->nVertices; i++)
    {
        printf("%d| ", i);
        for (int j = 0; j < gr->nVertices; j++)
        {
            printf("%d ", gr->arestas[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int ehDigrafo = 1;
    Grafo *gr;
    gr = criaGrafo(5, 0);
    insereAresta(gr, 0, 1, ehDigrafo, 0);
    insereAresta(gr, 1, 3, ehDigrafo, 0);
    insereAresta(gr, 1, 2, ehDigrafo, 0);
    insereAresta(gr, 2, 4, ehDigrafo, 0);
    insereAresta(gr, 3, 0, ehDigrafo, 0);
    insereAresta(gr, 3, 4, ehDigrafo, 0);
    insereAresta(gr, 4, 1, ehDigrafo, 0);
    mostra(gr);
    printf("\n");
    // int vis1[5][5];
    buscaProfundidade_Grafo(gr, 0);
    printf("---------------\n");
    // int vis2[5];
    buscaLargura_Grafo(gr, 0);
    printf("final...\n");
    return 0;
}