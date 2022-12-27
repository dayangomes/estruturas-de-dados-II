#include <stdio.h>
#include <string.h>
#define TAM 100

void calculaDiv(int num, int div[TAM], int i, int *q)
{
  if (i <= num)
  {
    if ((num % i) == 0)
    {
      div[*q] = i;
      (*q)++;
      calculaDiv(num, div, i + 1, q);
    }
    else
    {
      calculaDiv(num, div, i + 1, q);
    }
  }
}

int main() // --> Dayan Ramos
{
  int num = 17, div[TAM];
  int i = 1, q = 0;

  calculaDiv(num, div, i, &q);

  printf("Divisores de %d: ", num);

  for (i = 0; i < q; i++)
  {
    printf("%d ", div[i]);
  }
  return 0;
}