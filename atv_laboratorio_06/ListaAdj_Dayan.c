#include <stdio.h>
#include <stdlib.h>

typedef struct grafos Grafo;
struct grafos
{
  int ehPonderado;
  int nVertices;
  int **arestas;
  float **pesos;
  int *grau;
};

Grafo *criaGrafo(int Vertices, int ehPonderado)
{
  Grafo *gr;
  gr = (Grafo *)malloc(sizeof(struct grafos));
  if (gr != NULL)
  {
  	int i;
    gr->nVertices = Vertices;
    gr->ehPonderado = (ehPonderado != 0) ? 1 : 0;
    gr->grau = (int *)calloc(Vertices, sizeof(int));
    gr->arestas = (int **)malloc(Vertices * sizeof(int *));
    for (i = 0; i < Vertices; i++)
    {
      gr->arestas[i] = (int *)malloc(Vertices * sizeof(int));
    }
    if (gr->ehPonderado)
    {
      gr->pesos = (float **)malloc(Vertices * sizeof(float *));
      for (i = 0; i < Vertices; i++)
      {
        gr->pesos[i] = (float *)malloc(Vertices * sizeof(float));
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
    for (i = 0; i < gr->nVertices; i++)
      free(gr->arestas[i]);
    free(gr->arestas);
    if (gr->ehPonderado)
    {
      for (i = 0; i < gr->nVertices; i++)
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
        gr->arestas[origem][gr->grau[origem]] = destino;
        if (gr->ehPonderado)
          gr->pesos[origem][gr->grau[origem]] = peso;
        (gr->grau[origem])++;
        if (digrafo == 0)
          insereAresta(gr, destino, origem, 1, peso);
        criou = 1;
      }
    }
  }
  return criou;
}
void mostraGrafo(Grafo *gr)
{
	int i, d;
  printf("origem \t\t destino \n");
  for (i = 0; i < gr->nVertices; i++)
    for (d = 0; d < gr->grau[i]; d++)
      if (gr->arestas[i][d] != 0)
        printf("%d \t\t %d \n", i, gr->arestas[i][d]);
}

void buscaEmLargura(Grafo *gr, int ini, int *visitado)
{
  int i, vert, NV, cont = 1;
  int *fila, IF = 0, FF = 0;
  for (i = 0; i < gr->nVertices; i++)
    visitado[i] = 0;

  NV = gr->nVertices;
  fila = (int *)malloc(NV * sizeof(int));
  FF++;
  fila[FF] = ini;
  visitado[ini] = cont;
  while (IF != FF)
  {
    IF = (IF + 1) % NV;
    vert = fila[IF];
    cont++;
    for (i = 0; i < gr->grau[vert]; i++)
    {
      if (!visitado[gr->arestas[vert][i]])
      {
        FF = (FF + 1) % NV;
        fila[FF] = gr->arestas[vert][i];
        visitado[gr->arestas[vert][i]] = cont;
      }
    }
  }
  free(fila);
  for (i = 0; i < gr->nVertices; i++)
    printf("%d -> %d\n", i, visitado[i]);
}

void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont)
{
  int i;
  visitado[ini] = cont;
  for (i = 0; i < gr->grau[ini]; i++)
  {
    if (!visitado[gr->arestas[ini][i]])
      buscaProfundidade(gr, gr->arestas[ini][i], visitado, cont + 1);
  }
}
void buscaEmProfundidade(Grafo *gr, int ini, int *visitado)
{
  int i, cont = 1;
  for (i = 0; i < gr->nVertices; i++)
    visitado[i] = 0;
  buscaProfundidade(gr, ini, visitado, cont);

  for (i = 0; i < gr->nVertices; i++)
    printf("%d -> %d\n", i, visitado[i]);
}

int main() // --> Dayan Ramos Gomes
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
  // Lista de Adjacencia
  mostraGrafo(gr);

  int visitado[5];
  printf("Busca em Largura:\n");
  buscaEmLargura(gr, 0, visitado);
  printf("Busca em Profudidade:\n");
  buscaEmProfundidade(gr, 0, visitado);

  liberaGrafo(gr);

  return 0;
}
