#include <stdio.h>
#include <stdlib.h>

typedef struct arv Arv;
struct arv
{
  int num, altura;
  Arv *esq, *dir;
};

Arv *criarArv() { return NULL; }
int inserir(Arv **raiz, int valor);
void rotacaoLL(Arv **raiz);
void rotacaoRR(Arv **raiz);
void rotacaoLR(Arv **raiz);
void rotacaoRL(Arv **raiz);
int maior(Arv *Alt1, Arv *Alt2);

void main()
{
  Arv *avl;
  avl = criarArv();
  inserir(&avl, 50);
}
int inserir(Arv **raiz, int valor)
{
  int inseriu = 0, res;
  if (*raiz == NULL)
  {
    Arv *novo;
    novo = (Arv *)malloc(sizeof(Arv));
    novo->dir = NULL;
    novo->esq = NULL;
    novo->num = valor;
    novo->altura = 0;
    inseriu = 1;
    *raiz = novo;
  }
  else if (valor < (*raiz)->num)
  {
  }

  return inseriu;
}

void rotacaoLL(Arv **raiz)
{
  Arv *aux;
  aux = (*raiz)->esq;
  (*raiz)->esq = aux->dir;
  aux->dir = *raiz;
  // maior retorna a maior altura dos filhos e soma mais um.
  (*raiz)->altura = maior(altura_No((*raiz)->esq), altura_No((*raiz)->dir)) + 1;
  aux->altura = maior(altura_No((*raiz)->esq), (*raiz)->altura) + 1;
  *raiz = aux;
}
void rotacaoRR(Arv **raiz)
{
  Arv *aux;
  aux = (*raiz)->dir;
  (*raiz)->dir = aux->esq;
  aux->esq = *raiz;
  // maior retorna a maior altura dos filhos e soma mais um.
  (*raiz)->altura = maior(altura_No((*raiz)->esq), altura_No((*raiz)->dir)) + 1;
  aux->altura = maior(altura_No((*raiz)->dir), (*raiz)->altura) + 1;
  *raiz = aux;
}
void rotacaoLR(Arv **raiz)
{
  rotacaoRR(&(*raiz)->esq);
  rotacaoLL(raiz);
}
void rotacaoRL(Arv **raiz)
{
  rotacaoLL(&(*raiz)->dir);
  rotacaoLL(raiz);
}

int maior(Arv *Alt1, Arv *Alt2)
{
}

void libera_NO(Arv *no)
{
  if (no == NULL)
    return;
  libera_NO(no->esq);
  libera_NO(no->dir);
  free(no);
  no = NULL;
}

void libera_ArvAVL(Arv *raiz)
{
  if (raiz == NULL)
    return;
  libera_NO(raiz); // libera cada n�
  free(raiz);      // libera a raiz
}