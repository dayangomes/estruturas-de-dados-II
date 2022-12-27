#include <stdio.h>
#include <string.h>
#define TAM 6

void inter(int V1[TAM], int V2[TAM], int V3[TAM], int i, int j, int q1, int q2, int q3)
{
  if (i < q1 && j < q2)
  {
    if (V1[i] == V2[j])
    {
      V3[q3] = V2[j];
      inter(V1, V2, V3, i + 1, 0, q1, q2, q3 + 1);
    }
    else
    {
      if (j == q2 - 1)
        inter(V1, V2, V3, i + 1, 0, q1, q2, q3);
      else
        inter(V1, V2, V3, i, j + 1, q1, q2, q3);
    }
  }
}
int main()
{
  int V1[TAM] = {2, 3, 5, 6, 7}, V2[TAM] = {2, 4, 5, 7, 8};
  int V3[TAM], q1 = 5, q2 = 5, q3 = 0, i;

  inter(V1, V2, V3, 0, 0, q1, q2, q3);
  for (i = 0; i < 3; i++)
  {
    printf("R = %d%c ", V3[i], i == 2 ? '.' : ',');
    // printf(i < 1 ? "R = %d, " : "R = %d");
  }
  return (0);
}