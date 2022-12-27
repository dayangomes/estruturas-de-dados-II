#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no NO;

struct no{
    char status;
    int nInicio, nFinal;
    int endInicio, endFim;
    NO *esq, *dir;
};

NO* criarArv(){
	return NULL;
	//OK
}

NO* criarFolha(int *status, int nInicio, int nFinal,int endInicio, int endFim){
	NO* novoNo = (NO*) malloc(sizeof(NO));
	novoNo->esq = NULL;
	novoNo->dir = NULL;
	novoNo->nInicio = nInicio;
	novoNo->nFinal = nFinal;
	novoNo->endInicio = endInicio;
	novoNo->endFim = endFim;

	if( *status == 0)
		novoNo->status = 'L';
	else
		novoNo->status = 'O';
	*status = 1- (*status);
	return novoNo;
}

int maior(int a, int b){
	if(a>b)
		return a;
	return b;
}

int altNO(NO* raiz){
	int n = 0;
	if(raiz == NULL)
		n = -1;
	else
		n = maior(altNO(raiz->esq), altNO(raiz->dir))+1;
	return n;
}

void rotacaoRR(NO** raiz){
	NO *aux;
	aux = (*raiz)->dir;
	(*raiz)->dir = aux->esq;
	aux->esq = *raiz;
	*raiz = aux;
}

void inserirAVL(NO** raiz, NO* novo){
	if(*raiz==NULL){
		*raiz = novo;
	}else{
		if( (*raiz)->nFinal >= novo->endInicio){
			if(novo->endInicio > (*raiz)->endFim){
				inserirAVL(&(*raiz)->dir, novo);
				if( abs( altNO((*raiz)->esq)-altNO((*raiz)->dir)) == 2)
					rotacaoRR(raiz);
			}
		}
	}
}

void exibirAVL(NO* raiz){
	if( raiz != NULL){
		exibirAVL(raiz->esq);
		printf("(%c) |%d-%d| |%d-%d|\n",raiz->status, raiz->nInicio, raiz->nFinal, raiz->endInicio, raiz->endFim);
		exibirAVL(raiz->dir);
	}
}

int alocar(NO** raiz, NO** pai, int qtdBlocos, int *status){

	//Resul 1 para alocação concluida
	int resul = 0;

	if( *raiz != NULL){
		resul = alocar(&(*raiz)->esq,raiz, qtdBlocos, status);

		if(resul == 0){
			
			if((*raiz)->status == 'L'){
				int qtdLocal = (*raiz)->endFim - (*raiz)->endInicio +1;
				
				if( pai == NULL && (*raiz)->esq == NULL && (*raiz)->dir == NULL){		//apenas um nó
					
					if(qtdLocal == qtdBlocos){
						(*raiz)->status = 'O';
					}else{
						int newFim = (*raiz)->endFim - qtdBlocos;
						int auxFim = (*raiz)->endFim;
						(*raiz)->endFim = newFim;

						int newInicio = newFim+1;

						inserirAVL(raiz, criarFolha(status, (*raiz)->nInicio,(*raiz)->nFinal,newInicio,auxFim));

					}
					resul = 1;
				}else if((*raiz)->esq == NULL && (*raiz)->dir == NULL){
					if(qtdLocal == qtdBlocos){
						//Buscar os mais internos para unir;
						int newFim = (*pai)->endFim + qtdBlocos;
						(*pai)->endFim = newFim;
						free(*raiz);
						*raiz = NULL;
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						if((*pai)->esq == *raiz){
							int newFim = (*raiz)->endFim - qtdBlocos;
							int newInicio = (*pai)->endInicio - qtdBlocos;
							(*raiz)->endFim = newFim;
							(*pai)->endInicio = newInicio;
						}else{
							int newInicio = (*raiz)->endInicio + qtdBlocos;
							int newFim = (*pai)->endFim + qtdBlocos;
							(*raiz)->endInicio = newInicio;
							(*pai)->endFim = newFim;
						}
						resul = 1;
					}
				}else{
			
					//Buscando o mais a esquerda Ocupado.
					NO** paiMaisEsq = raiz;
					NO** maisEsq;
					if((*raiz)->dir == NULL){
						maisEsq = raiz;
					}else{
						maisEsq = &((*raiz)->dir);
					}
					while((*maisEsq)->esq != NULL){
						paiMaisEsq = maisEsq;
						maisEsq = &((*maisEsq)->esq) ;
					}
					if((*paiMaisEsq)->status == 'O'){
						maisEsq = paiMaisEsq;
					}
					//free(*paiMaisEsq);		

					if(qtdLocal == qtdBlocos){

						//Buscando o mais a direita Ocupado.
						NO** paiMaisDir = raiz;
						NO** maisDir;;
						if((*raiz)->esq == NULL ){
							maisDir = raiz;
						}else{
							maisDir = &((*raiz)->esq);	
						}
						while((*maisDir)->dir != NULL){
							paiMaisDir = maisDir;
							maisDir = &((*maisDir)->dir) ;
						}
						if((*paiMaisDir)->status == 'L'){
							maisDir = paiMaisDir;
						}
						//free(*paiMaisDir);
						
						
						//Buscar os mais internos para unir;
						int newInicio = (*maisDir)->endInicio;
						int newFim = (*maisEsq)->endFim;
						(*raiz)->endInicio = newInicio;
						(*raiz)->endFim = newFim;
						(*raiz)->status = 'O';

						if(paiMaisEsq == raiz){
							(*raiz)->dir = ((*maisEsq)->dir);
						}else{
							(*paiMaisEsq)->esq = ((*maisEsq)->dir);
						}

						if(paiMaisDir == raiz){
							(*raiz)->esq = ((*maisDir)->esq);
						}else {
							(*paiMaisDir)->dir = ((*maisDir)->esq);
						}
						
						//free(*maisDir);
						//free(*maisEsq);
						//*maisDir = NULL;
						//*maisEsq = NULL;	
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						int newFim = (*raiz)->endFim - qtdBlocos;
						int newInicio = (*maisEsq)->endInicio - qtdBlocos;
						(*raiz)->endFim = newFim;
						(*maisEsq)->endInicio = newInicio;
						resul = 1;
						
					}else{
						resul = alocar(&(*raiz)->dir,raiz, qtdBlocos, status);
					}	
				}
			}else{
				resul = alocar(&(*raiz)->dir,raiz, qtdBlocos, status);
			}
		}
	}
	return resul;
}

int liberar(NO** raiz, NO** pai, int qtdBlocos, int* status){

	//Resul 1 para alocação concluida
	int resul = 0;

	if( *raiz != NULL){
		resul = liberar(&(*raiz)->esq,raiz, qtdBlocos, status);
	
		if(resul == 0){
				
			if((*raiz)->status == 'O'){
				int qtdLocal = (*raiz)->endFim - (*raiz)->endInicio +1;
				
				if( pai == NULL && (*raiz)->esq == NULL && (*raiz)->dir == NULL){
					
					if(qtdLocal == qtdBlocos){
						(*raiz)->status = 'L';
					}else{
						int newFim = (*raiz)->endFim - qtdBlocos;
						int auxFim = (*raiz)->endFim;
						(*raiz)->endFim = newFim;

						int newInicio = newFim+1;

						inserirAVL(raiz, criarFolha(status, (*raiz)->nInicio,(*raiz)->nFinal,newInicio,auxFim));

					}
					resul = 1;
				}else if((*raiz)->dir == NULL){
					if(qtdLocal == qtdBlocos){
						//Buscar os mais internos para unir;
						int newFim = (*pai)->endFim + qtdBlocos;
						(*pai)->endFim = newFim;
						free(*raiz);
						*raiz = NULL;
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						if((*pai)->esq == *raiz){
							int newFim = (*raiz)->endFim - qtdBlocos;
							int newInicio = (*pai)->endInicio - qtdBlocos;
							(*raiz)->endFim = newFim;
							(*pai)->endInicio = newInicio;
						}else{
							int newInicio = (*raiz)->endInicio + qtdBlocos;
							int newFim = (*pai)->endFim + qtdBlocos;
							(*raiz)->endInicio = newInicio;
							(*pai)->endFim = newFim;
						}
						resul = 1;
					}
				}else{
			
					//Buscando o mais a esquerda Ocupado.
					NO** paiMaisEsq = raiz;
					NO** maisEsq;
					if((*raiz)->dir == NULL){
						maisEsq = raiz;
					}else{
						maisEsq = &((*raiz)->dir);
					}
					while((*maisEsq)->esq != NULL){
						paiMaisEsq = maisEsq;
						maisEsq = &((*maisEsq)->esq) ;
					}
					if((*paiMaisEsq)->status == 'L'){
						maisEsq = paiMaisEsq;
					}
					//free(*paiMaisEsq);		
					
					if(qtdLocal == qtdBlocos){

						//Buscando o mais a direita Ocupado.
						NO** paiMaisDir = raiz;
						NO** maisDir;
						if((*raiz)->esq == NULL ){
							maisDir = raiz;
						}else{
							maisDir = &((*raiz)->esq);	
						}


						while((*maisDir)->dir != NULL){
							paiMaisDir = maisDir;
							maisDir = &((*maisDir)->dir) ;
						}
						if((*paiMaisDir)->status == 'O'){
							maisDir = paiMaisDir;
						}
						

						int newInicio = (*maisDir)->endInicio;
						int newFim = (*maisEsq)->endFim;
						(*raiz)->endInicio = newInicio;
						(*raiz)->endFim = newFim;
						(*raiz)->status = 'L';
						
						printf("ERRO[%d][%d]\n",newInicio, newFim );

						if(paiMaisEsq == raiz){
							(*raiz)->dir = ((*maisEsq)->dir);
						}else{
							(*paiMaisEsq)->esq = ((*maisEsq)->dir);
						}

						if(paiMaisDir == raiz){
							(*raiz)->esq = ((*maisDir)->esq);
						}else {
							(*paiMaisDir)->dir = ((*maisDir)->esq);
						}

						
						//free(*maisDir);
						//free(*maisEsq);
						//*maisDir = NULL;
						//*maisEsq = NULL;	
						resul = 1;
					}else if(qtdLocal > qtdBlocos){
						int newFim = (*raiz)->endFim - qtdBlocos;
						int newInicio = (*maisEsq)->endInicio - qtdBlocos;
						(*raiz)->endFim = newFim;
						(*maisEsq)->endInicio = newInicio;
						resul = 1;
					
					}else{
						resul = liberar(&(*raiz)->dir,raiz, qtdBlocos, status);
					}	
				}
			}else{
				resul = liberar(&(*raiz)->dir,raiz, qtdBlocos, status);
			}
		}
	}
	return resul;
}

int buscarAVL_Alocar(NO* raiz, int Valor){
	int find = 0;

	if(raiz != NULL){
		find = buscarAVL_Alocar(raiz->esq, Valor);
		if((raiz)->status == 'L'){
			int qtdLocal = (raiz)->endFim - (raiz)->endInicio +1;
			if(Valor <= qtdLocal){
				find = 1;
			}
		}
		if(find==0){
			find = buscarAVL_Alocar(raiz->dir, Valor);
		}
	}
	return find;
}

int buscarAVL_Liberar(NO* raiz, int Valor){
	int find = 0;

	if(raiz != NULL){
		find = buscarAVL_Liberar(raiz->esq, Valor);
		if((raiz)->status == 'L'){
			int qtdLocal = (raiz)->endFim - (raiz)->endInicio +1;
			if(Valor <= qtdLocal){
				find = 1;
			}
		}
		if(find==0){
			find = buscarAVL_Liberar(raiz->dir, Valor);
		}
	}
	return find;
}

int main(){

	NO* groot = criarArv();
	int  status=0, op;	//1-Ocupado 0-Livre

	clock_t tempoBuscaI, tempoBuscaF;
	clock_t tempoAlterarI, tempoAlterarF;
	float tempoBuscaDecorrido, tempoAlterarDecorrido;

	while(1==1){
		printf("--------------------------------\n");
		printf("1 - Definir Arvore\n");
		printf("2 - Mostrar Arvore\n");
		printf("3 - Alocar\n");
		printf("4 - Liberar\n");
		printf("0 - SAIR\n");
		printf("---------------------------------\n");
		scanf("%d", &op);
		switch(op){
			case 1:

				free(groot);
				groot = NULL;

				printf("Insira o status do primeiro bloco 1-Ocupado 0-Livre\n");
				scanf("%d", &status);

				int Inicio, Fim;
				printf("Insira o endereço incial: ");
				scanf("%d", &Inicio);
				printf("Insira o endereço final: ");
				scanf("%d", &Fim);

				int auxInicio=0, auxFim=0, cont=0;

				while(auxFim < Fim){
					printf("Insira o endereço[%d] incial: ",cont);
					scanf("%d", &auxInicio);
					printf("Insira o endereço[%d] final: ", cont++);
					scanf("%d", &auxFim);
					inserirAVL(&groot, criarFolha(&status, Inicio,Fim,auxInicio,auxFim));
				}
				break;
			case 2:
				exibirAVL(groot);
				printf("------------\n");
				break;
			case 3:
				
				printf("Quantidade de blocos para Alocar: ");
				int auxalocar;
				scanf("%d", &auxalocar);


				tempoBuscaI = clock();
				int findAloc = buscarAVL_Alocar(groot, auxalocar);
				tempoBuscaF = clock();
				tempoBuscaDecorrido = ((tempoBuscaF- tempoBuscaI)*1000)/CLOCKS_PER_SEC;
				printf("Tempo gasto BUSCAR: %lf \n", tempoBuscaDecorrido);

				
				tempoAlterarI = clock();
				if( alocar(&groot,NULL, auxalocar, &status) == 0)
					printf("Espaço insuficiente [%d].\n", findAloc);
				else
					printf("Alocação bem sucedida [%d].\n", findAloc);
				
				tempoAlterarF = clock();
				tempoAlterarDecorrido = ((tempoAlterarF-tempoAlterarI)*1000)/CLOCKS_PER_SEC;
				printf("Tempo gasto ALTERAR: %lf \n", tempoBuscaDecorrido);

				break;
			case 4:

				printf("Quantidade de blocos para liberar: ");
				int auxliberar;
				scanf("%d", &auxliberar);

				tempoBuscaI = clock();
				
				int findLib = buscarAVL_Liberar(groot, auxliberar);

				tempoBuscaF = clock();
				tempoBuscaDecorrido = ((tempoBuscaF- tempoBuscaI)*1000)/CLOCKS_PER_SEC;
				printf("Tempo gasto BUSCAR: %lf \n", tempoBuscaDecorrido);
				

				tempoAlterarI = clock();
				if( liberar(&groot,NULL, auxliberar, &status) == 0)
					printf("Espaço insuficiente [%d].\n", findLib);
				else
					printf("Liberação bem sucedida [%d].\n", findLib);
				
				tempoAlterarF = clock();
				tempoAlterarDecorrido = ((tempoAlterarF-tempoAlterarI)*1000)/CLOCKS_PER_SEC;
				printf("Tempo gasto ALTERAR: %lf \n", tempoBuscaDecorrido);
				break;
			case 0:
				exit(0);
			default:
				break;
		}
	}
    return 0;
}