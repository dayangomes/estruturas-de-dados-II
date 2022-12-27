#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// #define TAM 100

struct pessoa
{
  int id;
  char nome[20];
  int anoNascimento;
  int altura;
};
typedef struct lista Lista;
struct lista
{
  struct pessoa Info;
  struct lista *prox;
};

Lista *inicializa(void);
Lista *insere(Lista *l);
int tamLista(Lista *l);
int pessoaMaisBaixa(Lista *l, char **nomes, int menor, int *q);
void menorMaior(Lista *l, int *maior);
void quantPesMed(Lista *l, int media, int *quant);
void quantAcima(Lista *l, int media, int *quant);

int main() // --> Dayan Ramos
{
  Lista *lista;
  int i;

  lista = inicializa();
  for (i = 0; i < 4; i++)
  {
    lista = insere(lista);
  }

  char **baixa;
  baixa = (char **)malloc(sizeof(char *) * tamLista(lista));
  int menor, q = 0;
  menor = pessoaMaisBaixa(lista, baixa, lista->Info.altura, &q);
  printf("Letra a: \n");
  for (i = 0; i < q; i++)
    printf("%s\n", baixa[i]);
  // printf("\nMenor: %d", menor);

  int maior = lista->Info.altura;
  menorMaior(lista, &maior);
  printf("\nMaior: %d, Menor: %d", maior, menor);

  int med = (maior + menor) / 2;
  int pessoasMed = 0;
  printf("\nAltura Media: %d", med);
  quantPesMed(lista, med, &pessoasMed);
  printf("\n%d pessoas estao na altura media.", pessoasMed);

  int quant = 0;
  quantAcima(lista, med, &quant);
  printf("\n%d pessoas atendem a letra (d).", quant);
}

//============================================================================================//
Lista *inicializa(void)
{
  return NULL;
}
//============================================================================================//
Lista *insere(Lista *l)
{
  Lista *novo = (Lista *)malloc(sizeof(Lista));
  novo->prox = l;

  printf("Id: ");
  scanf("%d", &novo->Info.id);
  printf("Nome: ");
  scanf(" %[^\n]s", novo->Info.nome);
  printf("Ano Nascimento: ");
  scanf("%d", &novo->Info.anoNascimento);
  printf("Altura: ");
  scanf("%d", &novo->Info.altura);
  printf("\n");

  return novo;
}
//============================================================================================//

int tamLista(Lista *l)
{
  int t = 0;
  if (l != NULL)
  {
    t = t + tamLista(l->prox);
    t++;
  }
  return t;
}
//============================================================================================//
int pessoaMaisBaixa(Lista *l, char **nomes, int menorAlt, int *q)
{
  if (l != NULL)
  {
    if (l->Info.altura <= menorAlt)
      menorAlt = pessoaMaisBaixa(l->prox, nomes, l->Info.altura, q);
    else
      menorAlt = pessoaMaisBaixa(l->prox, nomes, menorAlt, q);

    if (l->Info.altura == menorAlt)
    {
      *(nomes + *q) = (char *)malloc(sizeof(char) * strlen(l->Info.nome));
      strcpy(*(nomes + *q), l->Info.nome);
      (*q)++;
    }
  }
  return menorAlt;
}
//============================================================================================//
void menorMaior(Lista *l, int *maior)
{
  if (l != NULL)
  {
    if (l->Info.altura > *maior)
    {
      *maior = l->Info.altura;
    }
    menorMaior(l->prox, maior);
  }
}
void quantPesMed(Lista *l, int media, int *quant)
{
  if (l != NULL)
  {
    if (l->Info.altura == media)
      (*quant)++;
    quantPesMed(l->prox, media, quant);
  }
}
void quantAcima(Lista *l, int media, int *quant)
{
  if (l != NULL)
  {
    if ((2022 - l->Info.anoNascimento) > 50 && l->Info.altura > media)
      (*quant)++;
    quantAcima(l->prox, media, quant);
  }
}