#include <stdio.h>

void altera1(int **p, int *a)
{ 
  **p = *a; // x recebe o valor de y
  *a = *a +50; // y recebe seu valor mais 50.
}
// R = No segundo printf o valor de x recebe o valor de y  e o valor
// de y é somado mais 50  pela função que o antecede, chamada “altera1”, 
// na qual o difere do primeiro printf.
void altera2(int **p, int *b)
{ 
  *p = b; //  p recebe o endereço de memoria de x.
  *b = *b +30; //  acrescenta mais 30 a x.
}
// R  = No quarto printf o ponteiro não guarda mais o endereço 
// de memória de y, e sim de x, e o valor da variável 
int main(){
  int x,y, *px, *py;

  x = 10;
  y = x + 20;

  px = &x; py = &y;


  printf("x = %d, End. x = %p, px = %p, y = %d \n",x,&x, px,y); 
  altera1(&px, &y);
  printf("x = %d, End. x = %p, px = %p, y = %d \n",x,&x, px,y); 
  getchar();

  printf("y = %d, End. y = %p, py = %p, x = %d \n",y,&y, py,x); 
  altera2(&py, &x);
  printf("y = %d, End. y = %p, py = %p, x = %d \n",y,&y, py,x); 
  
  getchar();

  return(0);
}
