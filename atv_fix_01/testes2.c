#include <stdio.h>
#include <string.h>
#include <math.h>
#define TAM 5

float misterio1(char b[TAM], float dec, int p, int i)
{
  if (p < strlen(b))
  {
    dec = misterio1(b, dec, p + 1, i - 1);
    if (b[p] == '1')
      dec = dec + pow(2, i);
  }
  return (dec);
}

int main()
{
  float dec = 0;
  int p = 0, i = 1;
  char b[TAM] = {'1', '0'};

  dec = misterio1(b, dec, p, i);
  printf("\nR = %.2f", dec);
  return (0);
}