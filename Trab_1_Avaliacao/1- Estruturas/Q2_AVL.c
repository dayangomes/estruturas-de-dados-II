#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 5000
#define repeat 30

typedef struct arv Arv;

struct arv
{
	int info;
	Arv *dir, *esq;
};

typedef struct
{
	int num;
	int cont;
} ContadorDiff;

Arv *criarArv()
{

	return NULL;
}

Arv *criarFolha(int valor)
{
	Arv *novoNo = (Arv *)malloc(sizeof(Arv));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->info = valor;
	return novoNo;
}

int maior(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void rotacaoRR(Arv **raiz)
{
	Arv *aux;
	aux = (*raiz)->dir;
	(*raiz)->dir = aux->esq;
	aux->esq = *raiz;
	*raiz = aux;
}

void rotacaoLL(Arv **raiz)
{
	Arv *aux;
	aux = (*raiz)->esq;
	(*raiz)->esq = aux->dir;
	aux->dir = *raiz;
	*raiz = aux;
}

void rotacaoLR(Arv **raiz)
{
	rotacaoRR(&((*raiz)->esq));
	rotacaoLL(raiz);
}

void rotacaoRL(Arv **raiz)
{
	rotacaoLL(&((*raiz)->dir));
	rotacaoRR(raiz);
}

int altNO(Arv *raiz)
{
	int n = 0;
	if (raiz == NULL)
		n = -1;
	else
		n = maior(altNO(raiz->esq), altNO(raiz->dir)) + 1;
	return n;
}

int inserirAVL(Arv **raiz, Arv *NO)
{
	int inseriu = 1;
	if (*raiz == NULL)
	{
		*raiz = NO;
	}
	else
	{
		if (NO->info < (*raiz)->info)
		{
			if (inserirAVL(&((*raiz)->esq), NO) == 1)
			{
				if (abs(altNO((*raiz)->esq) - altNO((*raiz)->dir)) == 2)
				{
					if (NO->info < ((*raiz)->esq)->info)
					{
						// printf("LL\n");
						rotacaoLL(raiz);
					}
					else
					{
						rotacaoLR(raiz);
						// printf("LR\n");
					}
				}
			}
		}
		else
		{
			if (NO->info > (*raiz)->info)
			{
				if (inserirAVL(&(*raiz)->dir, NO) == 1)
				{
					if (abs(altNO((*raiz)->esq) - altNO((*raiz)->dir)) == 2)
					{
						if (NO->info > ((*raiz)->dir)->info)
						{
							// printf("RR\n");
							rotacaoRR(raiz);
						}
						else
						{
							// printf("RL\n");
							rotacaoRL(raiz);
						}
					}
				}
			}
			else
				inseriu = 0;
		}
	}

	return inseriu;
}

void exibirAVL(Arv *raiz)
{
	if (raiz != NULL)
	{
		exibirAVL(raiz->esq);
		printf("%d %d\n", raiz->info, altNO(raiz));
		exibirAVL(raiz->dir);
	}
}

int buscarAVL(Arv *raiz, int Valor)
{
	int find = -1;

	if (raiz != NULL)
	{
		if (raiz->info == Valor)
			find = Valor;
		else if (raiz->info > Valor)
			find = buscarAVL(raiz->esq, Valor);
		else
			find = buscarAVL(raiz->dir, Valor);
	}
	return find;
}

int folha_MaiorP(Arv *raiz)
{
	int maxD = 0, maxE = 0, depth = -1;

	if (raiz != NULL)
	{
		maxE = folha_MaiorP(raiz->esq) + 1;
		maxD = folha_MaiorP(raiz->dir) + 1;

		if (maxD > maxE)
			depth = maxD;
		else
			depth = maxE;
	}
	return depth;
}

int folha_MenorP(Arv *raiz)
{
	int maxD = 0, maxE = 0, depth = -1;

	if (raiz != NULL)
	{
		maxE = folha_MaiorP(raiz->esq) + 1;
		maxD = folha_MaiorP(raiz->dir) + 1;

		if (maxD < maxE)
			depth = maxD;
		else
			depth = maxE;
	}
	return depth;
}

int *gerarNumRandom(int qtd)
{
	int *vetor = (int *)malloc(qtd * sizeof(int));
	for (int x = 0; x < qtd; x++)
		vetor[x] = rand() % tam;
	return vetor;
}

int main()
{

	ContadorDiff *Values = (ContadorDiff *)malloc(sizeof(ContadorDiff));
	int qtdDiff = 0;

	clock_t tempoBuscaI, tempoBuscaF;
	clock_t tempoInserirI, tempoInserirF;
	float tempoBuscaDecorrido, tempoInserirDecorrido;

	for (int i = 0; i < repeat; i++)
	{
		Arv *groot = criarArv();

		// Gerando numeros aleatorios
		int *numbers = gerarNumRandom(tam);

		// Contar tempo de inserção
		tempoInserirI = clock();
		// Inserindo numeros aleatorios na arvore
		Arv *folha = NULL;
		for (int x = 0; x < tam; x++)
		{
			folha = criarFolha(numbers[x]);
			inserirAVL(&groot, folha);
		}

		tempoInserirF = clock();

		tempoInserirDecorrido = ((tempoInserirF - tempoInserirI) * 1000) / CLOCKS_PER_SEC;
		printf("Tempo gasto INSERIR: %lf \n", tempoInserirDecorrido);

		int menorNivel = folha_MenorP(groot);
		int maiorNivel = folha_MaiorP(groot);

		// Mostrar nivel da folha de maior e menor profundidade

		printf("Menor Nivel: %d\n", menorNivel);
		printf("Maior Nivel: %d\n", maiorNivel);

		int diff = abs(maiorNivel - menorNivel);

		// Dicionario em Python
		int y = 0;
		for (; y < qtdDiff; y++)
			if (Values[y].num == diff)
				break;

		if (y == qtdDiff)
		{
			Values = (ContadorDiff *)realloc(Values, (qtdDiff + 1) * sizeof(ContadorDiff));
			Values[qtdDiff].num = diff;
			Values[qtdDiff].cont = 1;

			qtdDiff++;
		}
		else
		{
			Values[y].cont++;
		}

		// Contar tempo de BUSCA
		tempoBuscaI = clock();
		// for(int x = 0; x<tam; x++)
		int find = buscarAVL(groot, numbers[5]);

		tempoBuscaF = clock();
		tempoBuscaDecorrido = ((tempoBuscaF - tempoBuscaI) * 1000) / CLOCKS_PER_SEC;
		printf("Tempo gasto BUSCAR: %lf \n", tempoBuscaDecorrido);

		printf("-------------\n");
		free(groot);
	}

	printf("\n");
	for (int y = 0; y < qtdDiff; y++)
		printf("Numero Diff: %d | %d vez(es)\n", Values[y].num, Values[y].cont);

	return 0;
}
