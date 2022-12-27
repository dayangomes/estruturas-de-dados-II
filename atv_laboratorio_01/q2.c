#include <stdio.h>
#include <string.h>
#define TAML 3 // altera a quantidade de nomes a ser inserido.
#define TAMC 20

//============================================================================================//
void readNames(char names[][TAMC], int tam)
{
  int i;
  for (i = 0; i < tam; i++)
  {
    printf("Nome %d: ", i + 1);
    scanf(" %[^\n]s", names[i]);
  }
}
//============================================================================================//
// recebe a string de nomes, a 2 linha da matriz, o tamanho da primeira string, e a posição inicial da primeira string.
int smallerSize(char names[][TAMC], int line, int menor, int posMenor)
{
  if (line < TAML) // se a linha atual é menor que a quantidade de linhas que a matriz tem.
  {
    if (strlen(names[line]) < menor)
    {
      posMenor = line;
      menor = strlen(names[line]);
      posMenor = smallerSize(names, line + 1, menor, posMenor);
    }
    else
    {
      posMenor = smallerSize(names, line + 1, menor, posMenor);
    }
  }
  return (posMenor);
}

//============================================================================================//
int startConsonant(char c) // Verifica se a primeira letra da string nao é uma vogal.
{
  char vogais[] = {"AaEeIiOoUu"};
  int i, cons = 0;
  for (i = 0; i < strlen(vogais); i++)
  {
    if (c == vogais[i])
    {
      cons = 1;
    }
  } // caso nao for uma vogal ira ser uma consoante e retornar 0 para dizer que é consoante.
  return cons;
}
void quantConsonant(char names[][TAMC], int line, int *quant)
{
  if (line < TAML)
  {
    if (startConsonant(names[line][0]) == 0)
    {
      (*quant)++;
      quantConsonant(names, line + 1, quant);
    }
    else
      quantConsonant(names, line + 1, quant);
  }
}

//============================================================================================//
int startVowel(char c) // Verifica se a primeira letra da string nao é uma vogal Maiuscula.
{
  char vogais[] = {"AEIOU"};
  int i, cons = 0;
  for (i = 0; i < strlen(vogais); i++)
  { // caso for uma vogal maiuscula atribui 1 a cons e retorna depois.
    if (c == vogais[i])
    {
      cons = 1;
    }
  }
  return cons;
}
void smallerSixVow(char names[][TAMC], int six[TAML], int line, int *q)
{
  if (line < TAML)
  {
    if ((strlen(names[line]) < 7) && (startVowel(names[line][0]) == 1)) // se a string for menor/igual a 6 e se inicar com vogal maiscula.
    {
      six[*q] = line;
      (*q)++;
      smallerSixVow(names, six, line + 1, q);
    }
    else
      smallerSixVow(names, six, line + 1, q);
  }
}
//============================================================================================//

int main() // --> Dayan Ramos
{
  char names[TAML][TAMC];

  readNames(names, TAML);

  int pos = 0;
  pos = smallerSize(names, 1, strlen(names[0]), pos);
  printf("\n");
  printf("Menor String: %d - %s\n\n", pos + 1, names[pos]);

  int quant = 0;
  quantConsonant(names, 0, &quant);
  printf("%d strings iniciam com consoante.\n\n", quant);

  int six[TAML], q = 0, i;
  smallerSixVow(names, six, 0, &q);
  printf("Strings que atendem a letra (c): \n");
  for (i = 0; i < q; i++)
  {
    printf("%s\n", names[six[i]]);
  }
}