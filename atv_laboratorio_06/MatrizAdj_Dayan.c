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
  int *visitado;
};

Grafo *criaGrafo(int Vertices, int ehPonderado)
{
  Grafo *gr = (Grafo *)malloc(sizeof(Grafo));

  if (gr != NULL)
  {
  	int i;
    gr->nVertices = Vertices;
    gr->ehPonderado = (ehPonderado != 0) ? 1 : 0;
    gr->grau = (int *)calloc(Vertices, sizeof(int));
    gr->arestas = (int **)malloc(Vertices * sizeof(int *));
    for (i = 0; i < Vertices; i++)
    {
      gr->arestas[i] = (int *)calloc(Vertices, sizeof(int));
    }
    gr->visitado = (int **)malloc(Vertices * sizeof(int *));
    for (i = 0; i < Vertices; i++)
    {
      gr->visitado[i] = (int *)calloc(Vertices, sizeof(int));
    }
    if (gr->ehPonderado)
    {
      gr->pesos = (float **)malloc(Vertices * sizeof(float *));
      for (i = 0; i < Vertices; i++)
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

void mostraMatriz(Grafo *gr)
{
	int i, j;
  printf("\t   0 1 2 3 4");
  printf("\n\t------------\n");
  for (i = 0; i < gr->nVertices; i++)
  {
    printf("\t%d| ", i);
    for (j = 0; j < gr->nVertices; j++)
    {
      printf("%d ", gr->arestas[i][j]);
    }
    printf("\n");
  }
}

void naoVisitado(Grafo *gr)
{
	int i;
  for (i = 0; i < gr->nVertices; i++)
  {
    gr->visitado[i] = 0;
  }
}

void buscaEmLargura(Grafo *gr, int ini)
{
  int i, vert, NV, cont = 1;
  int *fila, IF = 0, FF = 0;
  naoVisitado(gr);

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

void buscaEmProfundidade(Grafo *gr, int ini)
{
  int i, cont = 1;
  naoVisitado(gr);
  buscaProfundidade(gr, ini, cont);

  for (i = 0; i < gr->nVertices; i++)
    printf("%d -> %d\n", i, gr->visitado[i]);
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

  printf("Matriz de Adjacencia:\n");
  mostraMatriz(gr);

  printf("\nBusca em Largura:\n");
  buscaEmLargura(gr, 0);
  printf("Busca em Profudidade:\n");
  buscaEmProfundidade(gr, 0);

  liberaGrafo(gr);

  return 0;
}
