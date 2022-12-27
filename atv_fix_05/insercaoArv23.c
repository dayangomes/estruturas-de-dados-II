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

void adiciona(struct Arv23 **Raiz, int Valor, struct Arv23 *MaiorNo){
	if (Valor > (*Raiz)->Info1)
	{
		(*Raiz)->Info2 = Valor;
		(*Raiz)->dir = MaiorNo;
	}
	else{
		(*Raiz)->Info2 = (*Raiz)->Info1;
		(*Raiz)->Info1 = Valor;
		(*Raiz)->dir = (*Raiz)->cen;
		(*Raiz)->cen = MaiorNo;
	}
	(*Raiz)->NInfos = 2;
}

struct Arv23 *quebraNo(struct Arv23 **Raiz, int valor, int *sobe, struct Arv23 *MaiorNo){
	struct Arv23 *Novo;

	if (valor < (*Raiz)->Info1){
		*sobe = (*Raiz)->Info1;
		Novo = criaNo((*Raiz)->Info2, (*Raiz)->cen, (*Raiz)->dir, NULL);
		(*Raiz)->Info1 = valor;
		(*Raiz)->cen = MaiorNo;
	}
	else if (valor < (*Raiz)->Info2){
		*sobe = valor;
		Novo = criaNo((*Raiz)->Info2, MaiorNo, (*Raiz)->dir, NULL);
	}
	else{
		*sobe = (*Raiz)->Info2;
		Novo = criaNo(valor, (*Raiz)->dir, MaiorNo, NULL);
	}
	(*Raiz)->Info2 = 0;
	(*Raiz)->NInfos = 1;
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
		else{ // quando não é folha
			if (valor < (*Raiz)->Info1)
				maiorNo = insereArv23(*Raiz, &((*Raiz)->esq), valor, sobe);
			else if ((*Raiz)->NInfos == 1 || (valor < (*Raiz)->Info2))
				maiorNo = insereArv23(*Raiz, &((*Raiz)->cen), valor, sobe);
			else
				maiorNo = insereArv23(*Raiz, &((*Raiz)->dir), valor, sobe);
				
			if (maiorNo != NULL){
				if ((*Raiz)->NInfos == 1){
					adiciona(Raiz, *sobe, maiorNo);
					maiorNo = NULL;
				}
				else{// quando não tem espaço
					int sobe1;
					struct Arv23 *novo;
					novo = quebraNo(Raiz, *sobe, &sobe1, maiorNo);
					if (Pai == NULL){
						struct Arv23 *no;
						no = criaNo(sobe1, *Raiz, novo, NULL);
						*Raiz = no;
						maiorNo = NULL;}
					else
						maiorNo = novo;
				}
			}
		}
	}
	return maiorNo;
}

int main()
{

	struct Arv23 *Raiz, *Pai;
	int valor, sobe = 0, i;

	Raiz = NULL;
	Pai = NULL;
	valor = 10;
	insereArv23(Pai, &Raiz, valor, &sobe);
	printf("Inseriu");
	// for (i = 0; i < 5; i++)
	// {
	// 	printf("Num %d: ", i + 1);
	// 	scanf("%d", &valor);
	// 	insereArv23(Pai, &Raiz, valor, &sobe);
	// }

	return 0;
}