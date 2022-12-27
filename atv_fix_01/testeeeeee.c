#include <stdio.h>
#include <string.h>
#define TAM 100

void calculaDiv(int num, int div[TAM], int i, int q)
{
  if (i <= num)
  {
    if ((num % i) == 0)
    {
      div[q] = i;
      q++;
      i++;
      calculaDiv(num, div, i, q);
    }
    else
    {
      i++;
      calculaDiv(num, div, i, q);
    }
  }
  printf("TAM: %d\n", strlen(div));
}

int main()
{
  int num = 20, div[TAM];
  int i = 1, q = 0, j;

  calculaDiv(num, div, i, q);

  printf("Divisores de %d: ", num);

  for (j = 0; j <= strlen(div); j++)
  {
    printf("%d ", div[j]);
  }
  return 0;
}
