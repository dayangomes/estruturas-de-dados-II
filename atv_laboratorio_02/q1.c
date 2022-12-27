#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ArvBin ArvBin;
struct ArvBin
{
  int num;
  ArvBin *esq;
  ArvBin *dir;
};

ArvBin *inicializa(void);
ArvBin *insere(ArvBin *arv);
void insercao(ArvBin **arv, int num);
double multiplos(ArvBin *arv, double mult);
void exibirEmOrdem(ArvBin *arv);
int folhas(ArvBin *arv, int quant);
int pai(ArvBin *raiz, ArvBin *arv, int num);
int removeNum(ArvBin **arv, int num);
ArvBin *maiorDireita(ArvBin **no);

int main() // --> Dayan Ramos
{
  ArvBin *arvore;

  arvore = inicializa();
  insercao(&arvore, 50);
  insercao(&arvore, 100);
  insercao(&arvore, 40);
  insercao(&arvore, 20);
  insercao(&arvore, 45);
  insercao(&arvore, 30);
  insercao(&arvore, 120);
  insercao(&arvore, 60);

  printf("Numeros Inseridos: ");
  exibirEmOrdem(arvore);

  double mult = 1;
  mult = multiplos(arvore, mult);
  printf("\n\nProduto dos Multiplos de 5 maiores que 20: %.lf", mult);

  int quant = 0;
  quant = folhas(arvore, quant);
  printf("\nQuantidade de nos folhas: %d", quant);

  int num;
  num = pai(arvore, arvore, 30);
  printf("\nPai do numero dado: %d", num);

  int del;
  del = removeNum(&arvore, 66);
  printf("\nExclusao: %d", del);
}

ArvBin *inicializa(void)
{
  return NULL;
}
void insercao(ArvBin **arv, int numero)
{
  if (*arv == NULL)
  {
    *arv = (ArvBin *)malloc(sizeof(ArvBin));
    (*arv)->dir = NULL;
    (*arv)->esq = NULL;
    (*arv)->num = numero;
  }
  else if (numero < ((*arv)->num))
    insercao(&((*arv)->esq), numero);
  else
    insercao(&((*arv)->dir), numero);
}

double multiplos(ArvBin *arv, double mult)
{
  if (arv != NULL)
  {
    if (arv->num > 20 && arv->num % 5 == 0)
    {
      mult = mult * arv->num;
      mult = multiplos(arv->dir, mult);
      mult = multiplos(arv->esq, mult);
    }
    else
    {
      mult = multiplos(arv->dir, mult);
      mult = multiplos(arv->esq, mult);
    }
  }
  return mult;
}

void exibirEmOrdem(ArvBin *arv)
{
  if (arv != NULL)
  {
    exibirEmOrdem(arv->esq);
    printf("%d ", arv->num);
    exibirEmOrdem(arv->dir);
  }
}

int folhas(ArvBin *arv, int quant)
{
  if (arv != NULL)
  {
    if (arv->dir == NULL && arv->esq == NULL)
    {
      quant = quant + 1;
      quant = folhas(arv->dir, quant);
      quant = folhas(arv->esq, quant);
    }
    else
    {
      quant = folhas(arv->dir, quant);
      quant = folhas(arv->esq, quant);
    }
  }
  return quant;
}

int pai(ArvBin *raiz, ArvBin *arv, int num)
{
  int achou = -1;
  if (arv != NULL)
  {
    if (num < arv->num)
      achou = pai(raiz, arv->esq, num);
    else if (num > arv->num)
      achou = pai(raiz, arv->dir, num);

    if (achou == -2)
      achou = arv->num;
    else if (arv->num == num && arv->num != raiz->num) // se o numero existir e nao for o no raiz.
      achou = -2;
  }
  return achou;
}

int removeNum(ArvBin **arv, int num)
{
  int del = 0;
  if (*arv != NULL)
  {
    if (num < (*arv)->num)
      del = removeNum(&(*arv)->esq, num);
    else if (num > (*arv)->num)
      del = removeNum(&(*arv)->dir, num);
    else
    {
      if (((*arv)->esq == NULL) && ((*arv)->dir == NULL))
      {
        free(arv);
        *arv = NULL;
        del = 1;
      }
      else
      {
        ArvBin *Aux = *arv;
        if ((*arv)->esq == NULL) // quando tem um filho e é o da esquerda.
        {
          (*arv) = (*arv)->dir;
          Aux->dir = NULL;
          free(Aux);
          Aux = NULL;
          del = 1;
        }
        else if ((*arv)->dir == NULL) // quando tem um filho e é o da esquerda.
        {
          (*arv) = (*arv)->esq;
          Aux->esq = NULL;
          free(Aux);
          Aux = NULL;
          del = 1;
        }
        else // quando tem dois filhos.
        {
          Aux = maiorDireita(&(*arv)->esq);
          Aux->esq = (*arv)->esq;
          Aux->dir = (*arv)->dir;
          (*arv)->esq = (*arv)->dir = NULL;
          free((*arv));
          *arv = Aux;
          Aux = NULL;
          del = 1;
        }
      }
    }
  }
  return del;
}
ArvBin *maiorDireita(ArvBin **no)
{
  if ((*no)->dir != NULL)
    *no = maiorDireita(&(*no)->dir);
  else
  {
    ArvBin *aux = *no;
    if ((*no)->esq != NULL)
      *no = (*no)->esq;
    else
    {
      *no = NULL;
      return aux;
    }
  }
}
