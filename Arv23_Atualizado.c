#include <stdio.h>
#include <stdlib.h>

typedef struct Arv23 Arv23;
struct Arv23
{
	int Info1, Info2, NInfos;
	struct Arv23 *esq, *cen, *dir;
};

Arv23 *criaNo(int valor, Arv23 *FEsq, Arv23 *FCen, Arv23 *FDir)
{
	Arv23 *No;

	No = (Arv23 *)malloc(sizeof(Arv23));

	(*No).Info1 = valor;
	(*No).Info2 = 0;
	(*No).NInfos = 1;
	(*No).esq = FEsq;
	(*No).cen = FCen;
	(*No).dir = FDir;

	return No;
}

int ehFolha(Arv23 *R)
{
	int folha = 0; // não é folha

	if (R->esq == NULL && R->cen == NULL && R->dir == NULL)
		folha = 1;

	return folha;
}

void adiciona(Arv23 **Raiz, int Valor, Arv23 *MaiorNo)
{
	if (Valor > (*Raiz)->Info1)
	{
		(*Raiz)->Info2 = Valor;
		(*Raiz)->dir = MaiorNo;
	}
	else
	{
		(*Raiz)->Info2 = (*Raiz)->Info1;
		(*Raiz)->Info1 = Valor;
		(*Raiz)->dir = (*Raiz)->cen;
		(*Raiz)->cen = MaiorNo;
	}

	(*Raiz)->NInfos = 2;
}

Arv23 *quebraNo(Arv23 **Raiz, int valor, int *sobe, Arv23 *MaiorNo)
{
	Arv23 *Novo;

	if (valor < (*Raiz)->Info1)
	{
		*sobe = (*Raiz)->Info1;
		Novo = criaNo((*Raiz)->Info2, (*Raiz)->cen, (*Raiz)->dir, NULL);
		(*Raiz)->Info1 = valor;
		(*Raiz)->cen = MaiorNo;
	}
	else if (valor < (*Raiz)->Info2)
	{
		*sobe = valor;
		Novo = criaNo((*Raiz)->Info2, MaiorNo, (*Raiz)->dir, NULL);
	}
	else
	{
		*sobe = (*Raiz)->Info2;
		Novo = criaNo(valor, (*Raiz)->dir, MaiorNo, NULL);
	}
	(*Raiz)->Info2 = 0;
	(*Raiz)->NInfos = 1;
	(*Raiz)->dir = NULL;

	return (Novo);
}

Arv23 *insereArv23(Arv23 *Pai, Arv23 **Raiz, int valor, int *sobe)
{
	Arv23 *maiorNo;
	maiorNo = NULL;
	if (*Raiz == NULL)
		*Raiz = criaNo(valor, NULL, NULL, NULL);
	else
	{
		if (ehFolha(*Raiz))
		{
			if ((*Raiz)->NInfos == 1)
			{
				adiciona(Raiz, valor, maiorNo);
			}
			else // quando não tem espaço
			{
				Arv23 *novo;
				novo = quebraNo(Raiz, valor, sobe, maiorNo);
				if (Pai == NULL)
				{
					Arv23 *no;
					no = criaNo(*sobe, *Raiz, novo, NULL);
					*Raiz = no;
				}
				else
					maiorNo = novo;
			}
		}
		else
		{ // quando não é folha
			if (valor < (*Raiz)->Info1)
				maiorNo = insereArv23(*Raiz, &((*Raiz)->esq), valor, sobe);
			else if ((*Raiz)->NInfos == 1 || (valor < (*Raiz)->Info2))
				maiorNo = insereArv23(*Raiz, &((*Raiz)->cen), valor, sobe);
			else
				maiorNo = insereArv23(*Raiz, &((*Raiz)->dir), valor, sobe);

			if (maiorNo != NULL)
			{
				if ((*Raiz)->NInfos == 1)
				{
					adiciona(Raiz, *sobe, maiorNo);
					maiorNo = NULL;
				}
				else // quando não tem espaço
				{
					int sobe1;
					Arv23 *novo;
					novo = quebraNo(Raiz, *sobe, &sobe1, maiorNo);
					if (Pai == NULL)
					{
						Arv23 *no;
						no = criaNo(sobe1, *Raiz, novo, NULL);
						*Raiz = no;
						maiorNo = NULL;
					}
					else
					{
						maiorNo = novo;
						*sobe = sobe1; // Ela botou isso que nao tinha
					}
				}
			}
		}
	}
	return maiorNo;
}

// questao 1
void mostraEmOrdem(Arv23 *Raiz)
{
	if (Raiz != NULL)
	{
		mostraEmOrdem(Raiz->esq);
		printf("%d ", Raiz->Info1);
		mostraEmOrdem(Raiz->cen);
		if (Raiz->Info2 != 0)
			printf("%d ", Raiz->Info2);
		mostraEmOrdem(Raiz->dir);
	}
}
// questao 2
int buscaElemento(Arv23 *Raiz, int valor)
{
	int achou = 0;
	if (Raiz != NULL)
	{
		if ((valor == Raiz->Info1))
			achou = 1;
		else if ((Raiz->NInfos == 2) && (Raiz->Info2 == valor))
			achou = 1;
		else if (valor < Raiz->Info1)
			achou = buscaElemento(Raiz->esq, valor);
		else if ((Raiz->NInfos == 1) || (valor < Raiz->Info2))
			achou = buscaElemento(Raiz->cen, valor);
		else if ((Raiz->NInfos == 2) && (valor > Raiz->Info2))
			achou = buscaElemento(Raiz->dir, valor);
	}
	return achou;
}
// Questao 3
int nivelArv(Arv23 *Raiz)
{
	int nv = -1;
	if (Raiz != NULL)
	{
		if (Raiz->esq != NULL)
			nv = nivelArv(Raiz->esq);
	}
	return nv + 1;
}

// Questao 4
void noInfo(Arv23 *Raiz, int *no, int *info)
{
	if (Raiz != NULL)
	{
		// int aux;
		if (ehFolha(Raiz) == 1)
		{
			*no += 1;
			*info = *info + Raiz->NInfos;
		}
		noInfo(Raiz->esq, no, info);
		noInfo(Raiz->cen, no, info);
		noInfo(Raiz->dir, no, info);
	}
}

void menorInfoDir(Arv23 *Raiz, Arv23 **no, Arv23 **paiNo)
{
	if (Raiz->esq != NULL)
	{
		*paiNo = Raiz;
		menorInfoDir(Raiz->esq, no, paiNo);
	}
	else
		*no = Raiz;
}

void maiorInfoEsq(Arv23 *Raiz, Arv23 **no, Arv23 **paiNo)
{
	if (Raiz->dir != NULL)
	{
		*paiNo = Raiz;
		maiorInfoEsq(Raiz->dir, no, paiNo);
	}
	else
		*no = Raiz;
}

int remover23(Arv23 **Pai, Arv23 **Raiz, int valor)
{
	int removeu = 0;
	Arv23 *no = NULL, *no1, *paiNo = NULL, *paiNo1 = NULL, **aux;
	aux = (Arv23 **)malloc(sizeof(Arv23 *));
	no1 = (Arv23 *)malloc(sizeof(Arv23));

	if (*Raiz != NULL)
	{
		if (ehFolha(*Raiz) == 1)
		{
			if ((*Raiz)->NInfos == 2)
			{
				if (valor == (*Raiz)->Info2)
				{ // quando é folha, tem duas informações e o numero ta na segunda posição
					(*Raiz)->Info2 = 0;
					(*Raiz)->NInfos = 1;
					removeu = 1;
				}
				else if (valor == (*Raiz)->Info1)
				{ // quando é folha, tem duas informações e o numero ta na primeira posição do nó
					(*Raiz)->Info1 = (*Raiz)->Info2;
					(*Raiz)->Info2 = 0;
					(*Raiz)->NInfos = 1;
					removeu = 1;
				}
			}
			else if (valor == (*Raiz)->Info1)
			{
				if (*Pai == NULL)
				{
					free(*Raiz);
					*Raiz = NULL;
					removeu = 1;
				}
				else if (*Raiz == (*Pai)->esq)
				{
					(*Raiz)->Info1 = (*Pai)->Info1;
					paiNo = *Pai;
					menorInfoDir((*Pai)->cen, &no, &paiNo);
					(*Pai)->Info1 = no->Info1;
					removeu = 1;

					if (no->NInfos == 2)
					{
						no->Info1 = no->Info2;
						no->Info2 = 0;
						no->NInfos = 1;
					}
					else
					{
						if (paiNo->NInfos == 1)
						{
							(*Raiz)->Info2 = no->Info1;
							(*Raiz)->NInfos = 2;
							free(no);
							*Pai = *Raiz;
						}
						else
						{
							no->Info1 = paiNo->Info2;
							paiNo1 = paiNo;
							menorInfoDir(paiNo->dir, &no1, &paiNo1);
							paiNo->Info2 = no1->Info1;

							if (no1->NInfos == 2)
							{
								no1->Info1 = no1->Info2;
								no1->Info2 = 0;
								no1->NInfos = 1;
							}
							else
							{
								no->Info2 = paiNo->Info2;
								no->NInfos = 2;
								paiNo->Info2 = 0;
								paiNo->NInfos = 1;
								free(no1);
								paiNo1->dir = NULL;
							}
						}
					}
				}
				else if (*Raiz == (*Pai)->cen)
				{
					removeu = 1;
					if ((*Pai)->NInfos == 1)
					{
						if (((*Pai)->esq)->NInfos == 2)
						{
							(*Raiz)->Info1 = (*Pai)->Info1;
							(*Pai)->Info1 = ((*Pai)->esq)->Info2;
							((*Pai)->esq)->Info2 = 0;
							((*Pai)->esq)->NInfos = 1;
						}
						else
						{
							((*Pai)->esq)->Info2 = (*Pai)->Info1;
							free(*Raiz);
							((*Pai)->esq)->NInfos = 2;
							*aux = (*Pai)->esq;
							free(*Pai);
							*Pai = *aux;
						}
					}
					else
					{
						(*Raiz)->Info1 = (*Pai)->Info2;
						paiNo = *Pai;
						menorInfoDir((*Pai)->dir, &no, &paiNo);
						(*Pai)->Info2 = no->Info1;

						if (no->NInfos == 2)
						{
							no->Info1 = no->Info2;
							no->Info2 = 0;
							no->NInfos = 1;
						}
						else
						{
							(*Raiz)->NInfos = 2;
							(*Raiz)->Info2 = (*Pai)->Info2;
							(*Pai)->Info2 = 0;
							(*Pai)->NInfos = 1;
							free(no);
							(*Pai)->dir = NULL;
						}
					}
				}
				else
				{
					removeu = 1;
					paiNo = *Pai;
					maiorInfoEsq((*Pai)->cen, &no, &paiNo);

					if (no->NInfos == 1)
					{
						no->Info2 = (*Pai)->Info2;
						(*Pai)->Info2 = 0;
						(*Pai)->NInfos = 1;
						no->NInfos = 2;
						free(*Raiz);
						*Raiz = NULL;
					}
					else
					{
						(*Raiz)->Info1 = (*Pai)->Info2;
						(*Pai)->Info2 = no->Info2;
						no->Info2 = 0;
						no->NInfos = 1;
					}
				}
			}
		}
		else
		{ // se nao é folha
			if (valor < (*Raiz)->Info1)
				removeu = remover23(Raiz, &(*Raiz)->esq, valor);
			else if (valor == (*Raiz)->Info1)
			{
				paiNo = *Raiz;
				menorInfoDir((*Raiz)->cen, &no, &paiNo);
				(*Raiz)->Info1 = no->Info1;
				remover23(Raiz, &(*Raiz)->cen, (*Raiz)->Info1);
				removeu = 1;
			}
			else if (((*Raiz)->NInfos == 1) || (valor < (*Raiz)->Info2))
			{
				removeu = remover23(Raiz, &(*Raiz)->cen, valor);
			}
			else if (valor == (*Raiz)->Info2)
			{
				paiNo = *Pai;
				menorInfoDir((*Pai)->dir, &no, &paiNo);
				(*Raiz)->Info2 = no->Info1;
				remover23(Raiz, &(*Raiz)->dir, (*Raiz)->Info2);
				removeu = 1;
			}
			else
			{
				removeu = remover23(Raiz, &(*Raiz)->dir, valor);
			}
		}
	}
	return removeu;
}

int main() // --> Dayan Gomes
{
	Arv23 *Raiz, *Pai;
	int valor, sobe = 0, i;
	Raiz = NULL;
	Pai = NULL;

	// for(i = 20; i > 0; i--){ // Teste para ver se ta repetindo.
	// 	insereArv23(Pai, &Raiz, i, &sobe);
	// }

	// Exemplo de inserção da 1ª questao da atv de fixação 06
	insereArv23(Pai, &Raiz, 1000, &sobe);
	insereArv23(Pai, &Raiz, 500, &sobe);
	insereArv23(Pai, &Raiz, 600, &sobe);
	insereArv23(Pai, &Raiz, 2000, &sobe);
	insereArv23(Pai, &Raiz, 1500, &sobe);
	insereArv23(Pai, &Raiz, 200, &sobe);
	insereArv23(Pai, &Raiz, 1300, &sobe);
	insereArv23(Pai, &Raiz, 900, &sobe);
	insereArv23(Pai, &Raiz, 4000, &sobe);

	printf("\nEm Ordem: ");
	mostraEmOrdem(Raiz);

	// REMOVENDO OS MESMOS NUMEROS DO EXEMPLO DA ATIVIDADE DE FIXAÇÃO 06
	int rem;
	rem = remover23(&Pai, &Raiz, 1500);
	printf("\nRemoveu: %d", rem);
	rem = remover23(&Pai, &Raiz, 1300);
	printf("\nRemoveu: %d", rem);
	rem = remover23(&Pai, &Raiz, 900);
	printf("\nRemoveu: %d", rem);
	rem = remover23(&Pai, &Raiz, 1000);
	printf("\nRemoveu: %d", rem);

	// EXIBE NOVAMENTE APÓS AS REMOÇÕES
	printf("\nEm Ordem: ");
	mostraEmOrdem(Raiz);

	// Busca um número.
	// int num;
	// printf("\nBuscar: ");
	// scanf(" %d", &i);
	// num = buscaElemento(Raiz, i);
	// printf("Achou: %d\n", num);

	// // Mostra o nivel da árvore.
	// int nivel;
	// nivel = nivelArv(Raiz);
	// printf("\nNivel da Raiz: %d", nivel);

	// // Quantidade de nós folhas e informações neles.
	// int no = 0, info = 0;
	// noInfo(Raiz, &no, &info);
	// printf("\nNos Folhas: %d, Informacoes: %d", no, info);
	return 0;
}