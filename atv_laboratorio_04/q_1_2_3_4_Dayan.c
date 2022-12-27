#include <stdio.h>
#include <stdlib.h>

struct Arv23
{
	int Info1, Info2, NInfos;
	struct Arv23 *esq, *cen, *dir;
};

struct Arv23 *criaNo(int valor, struct Arv23 *FEsq, struct Arv23 *FCen, struct Arv23 *FDir)
{
	struct Arv23 *No;

	No = (struct Arv23 *)malloc(sizeof(struct Arv23));

	(*No).Info1 = valor;
	(*No).Info2 = 0;
	(*No).NInfos = 1;
	(*No).esq = FEsq;
	(*No).cen = FCen;
	(*No).dir = FDir;

	return No;
}

int ehFolha(struct Arv23 *R)
{
	int folha = 0; // não é folha

	if (R->esq == NULL && R->cen == NULL && R->dir == NULL)
		folha = 1;

	return folha;
}

void adiciona(struct Arv23 **Raiz, int Valor, struct Arv23 *MaiorNo)
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

struct Arv23 *quebraNo(struct Arv23 **Raiz, int valor, int *sobe, struct Arv23 *MaiorNo)
{
	struct Arv23 *Novo;

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
	(*Raiz)->NInfos -= 1;
	(*Raiz)->dir = NULL;

	return (Novo);
}

struct Arv23 *insereArv23(struct Arv23 *Pai, struct Arv23 **Raiz, int valor, int *sobe)
{
	struct Arv23 *maiorNo;
	maiorNo = NULL;
	if (*Raiz == NULL)
		*Raiz = criaNo(valor, NULL, NULL, NULL);
	else
	{
		if (ehFolha(*Raiz) == 1)
		{
			if ((*Raiz)->NInfos == 1)
			{
				adiciona(Raiz, valor, maiorNo);
			}
			else // quando não tem espaço
			{
				struct Arv23 *novo;
				novo = quebraNo(Raiz, valor, sobe, maiorNo);
				if (Pai == NULL)
				{
					struct Arv23 *no;
					no = criaNo(*sobe, *Raiz, novo, NULL);
					*Raiz = no;
				}
				else
					maiorNo = novo;
			}
		}
		else
		{
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
					struct Arv23 *novo;
					novo = quebraNo(Raiz, *sobe, &sobe1, maiorNo);
					if (Pai == NULL)
					{
						struct Arv23 *no;
						no = criaNo(sobe1, *Raiz, novo, NULL);
						*Raiz = no;
						maiorNo = NULL;
					}
					else
						maiorNo = novo;
				}
			}
		}
	}

	return maiorNo;
}
// questao 1
void mostraEmOrdem(struct Arv23 *Raiz)
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
int buscaElemento(struct Arv23 *Raiz, int valor)
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
int nivelArv(struct Arv23 *Raiz)
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
void noInfo(struct Arv23 *Raiz, int *no, int *info)
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

int main()
{
	struct Arv23 *Raiz, *Pai, *Aux;
	int valor, sobe = 0, i;
	Raiz = NULL;
	Pai = NULL;

	/* Exemplo de inserção da letra c) da 1ª questao da atv de fixação 5
		onde há os desenhos para representar melhor essa inserção*/
	Aux = insereArv23(Pai, &Raiz, 100, &sobe);
	Aux = insereArv23(Pai, &Raiz, 500, &sobe);
	Aux = insereArv23(Pai, &Raiz, 200, &sobe);
	Aux = insereArv23(Pai, &Raiz, 300, &sobe);
	Aux = insereArv23(Pai, &Raiz, 600, &sobe);
	Aux = insereArv23(Pai, &Raiz, 450, &sobe);
	Aux = insereArv23(Pai, &Raiz, 700, &sobe);
	Aux = insereArv23(Pai, &Raiz, 50, &sobe);
	// Aux = insereArv23(Pai, &Raiz, 800, &sobe);

	// Questão 1.
	printf("\nEm Ordem: ");
	mostraEmOrdem(Raiz);

	// Questão 2.
	int num;
	printf("\nBuscar: ");
	scanf(" %d", &i);
	num = buscaElemento(Raiz, i);
	printf("Achou: %d\n", num);

	// Questao 3
	int nivel;
	nivel = nivelArv(Raiz);
	printf("\nNivel da Raiz: %d", nivel);

	// Questao 4
	int no = 0, info = 0;
	noInfo(Raiz, &no, &info);
	printf("\nNos Folhas: %d, Informacoes: %d", no, info);
	return 0;
}
