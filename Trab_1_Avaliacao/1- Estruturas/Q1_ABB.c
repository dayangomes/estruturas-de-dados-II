#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tam 10000
#define repeat 30

typedef struct arv Arv;

struct arv{
	int info, altura;
	Arv *dir ,*esq;
};

typedef struct{
	int num;
	int cont;
}ContadorDiff;

Arv* criarArv(){
	
	return NULL;
}

Arv* criarFolha(int valor){
	Arv* novoNo = (Arv*) malloc(sizeof(Arv));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->altura = 0;
	novoNo->info = valor;
	return novoNo;
}

int RamoMaior(Arv* esq, Arv* dir){
	int n = 0;
	if(esq == NULL)
		n = dir->altura;
	else if(dir == NULL)
		n = esq->altura;
	else if(dir->altura > esq->altura)
		n = dir->altura;
	else
		n = esq->altura;
	return n;
}

void inserirABB(Arv** raiz, Arv* NO){	
	if(*raiz==NULL){
		*raiz = NO;
	}else{
		if((*raiz)->info > NO->info)
			inserirABB( &((*raiz)->esq), NO);
		else
			//Numeros iguais iram para a direita
			inserirABB( &((*raiz)->dir), NO);
		(*raiz)->altura = RamoMaior((*raiz)->esq, (*raiz)->dir)+1;
	}
}

void exibirABB(Arv* raiz){
	if( raiz != NULL){
		exibirABB(raiz->esq);
		printf("%d %d\n",raiz->info, raiz->altura);
		exibirABB(raiz->dir);
	}
}

int buscarABB(Arv* raiz, int Valor){
	int find = -1;

	if(raiz != NULL){
		if(raiz->info == Valor)
			find = Valor;
		else if(raiz->info > Valor)
			find = buscarABB(raiz->esq, Valor);
		else
			find = buscarABB(raiz->dir, Valor);
	}
	return find;
}

int folha_MaiorP(Arv* raiz){
	int maxD = 0, maxE = 0,depth = -1;

	if(raiz != NULL){
		maxE = folha_MaiorP(raiz->esq)+1;
		maxD = folha_MaiorP(raiz->dir)+1;

		if(maxD > maxE)	
			depth = maxD;
		else
			depth = maxE;
	}
	return depth;
}

int folha_MenorP(Arv* raiz){
	int maxD = 0, maxE = 0,depth = -1;

	if(raiz != NULL){
		maxE = folha_MaiorP(raiz->esq)+1;
		maxD = folha_MaiorP(raiz->dir)+1;

		if(maxD < maxE)	
			depth = maxD;
		else
			depth = maxE;
	}
	return depth;
}

int* gerarNumRandom(int qtd){
	int* vetor = (int*) malloc(qtd*sizeof(int));
	for(int x = 0; x<qtd; x++)
		vetor[x] = rand()%tam;
	return vetor;
}

int main(){
	ContadorDiff* Values = (ContadorDiff*) malloc(sizeof(ContadorDiff));
	int qtdDiff = 0;
	clock_t tempoBuscaI, tempoBuscaF;
	clock_t tempoInserirI, tempoInserirF;
	float tempoBuscaDecorrido, tempoInserirDecorrido;
	srand(time(NULL));
	
	for(int i = 0; i<repeat; i++){
		printf("-- repetição: %d --\n", i+1);
		Arv* groot = criarArv();

		//Gerando numeros aleatorios
		int *numbers = gerarNumRandom(tam);


		//Contar tempo de inserção
		tempoInserirI = clock();
		//Inserindo numeros aleatorios na arvore
		for(int x = 0; x<tam; x++){
			inserirABB(&groot, criarFolha(numbers[x]));
		}
		tempoInserirF = clock();

		tempoInserirDecorrido = ((tempoInserirF- tempoInserirI)*1000)/CLOCKS_PER_SEC;
		printf("Tempo gasto INSERIR: %lf \n", tempoInserirDecorrido);

		int menorNivel = folha_MenorP(groot);
		int maiorNivel = folha_MaiorP(groot);
		printf("Maior nível: %d | Menor nível: %d \n",maiorNivel,menorNivel);

	
		int diff = abs( maiorNivel - menorNivel);
		
		//Dicionario em Python
		int y = 0;
		for( ; y<qtdDiff; y++)	
			if(Values[y].num == diff) break;

		if(y == qtdDiff){
			Values = (ContadorDiff*) realloc(Values, (qtdDiff+1)*sizeof(ContadorDiff));
			Values[qtdDiff].num = diff;
			Values[qtdDiff].cont = 1;

			qtdDiff++;
		}else{
			Values[y].cont++;
		}

		//Contar tempo de BUSCA
		tempoBuscaI = clock();
		//for(int x = 0; x<tam; x++)
		int find = buscarABB(groot,numbers[6]);		//buscar o décimo elemento gerado aleatóriamente
		
		tempoBuscaF = clock();
		tempoBuscaDecorrido = ((tempoBuscaF - tempoBuscaI)*1000)/CLOCKS_PER_SEC;
		printf("Tempo gasto BUSCAR: %lf \n", tempoBuscaDecorrido);

		printf("-------------\n");
		free(groot);
	}
	
	printf("\n");
	for(int y = 0 ; y<qtdDiff; y++){
		printf("Numero Diff: %d | %d vez(es)\n", Values[y].num, Values[y].cont);
	}
	return 0;
}
