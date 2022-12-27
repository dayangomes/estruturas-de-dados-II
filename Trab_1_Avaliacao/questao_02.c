#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 5000

typedef struct avl Avl;

typedef struct diferencas
{
    int num;
    int quant;
} Diferencas;

struct avl
{
    int info;
    int altura;
    Avl *esq, *dir;
};
int pegaAltura(Avl *raiz)
{
    int alt = 0;
    if (raiz != NULL)
    {
        int alt_esq = pegaAltura(raiz->esq);
        int alt_dir = pegaAltura(raiz->dir);
        if (alt_esq > alt_dir)
            alt = alt_esq + 1;
        else
            alt = alt_dir + 1;
    }
    return alt;
}
int alturaBal(Avl *tr)
{
    return tr == NULL ? -1 : tr->altura;
}
int fatorBal(Avl *tree)
{
    int bl;
    bl = tree != NULL ? abs(alturaBal(tree->esq) - alturaBal(tree->dir)) : 0;
    return bl;
}
int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
void rotacaoEE(Avl **tree)
{
    if ((*tree)->esq != NULL)
    {
        Avl *aux = (*tree)->esq;
        (*tree)->esq = aux->dir;
        aux->dir = *tree;
        (*tree)->altura = maior(pegaAltura((*tree)->esq), pegaAltura((*tree)->dir)) + 1;
        aux->altura = maior(pegaAltura(aux->esq), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoDD(Avl **tree)
{
    if ((*tree)->dir != NULL)
    {
        Avl *aux = (*tree)->dir;
        (*tree)->dir = aux->esq;
        aux->esq = *tree;
        (*tree)->altura = maior(pegaAltura((*tree)->esq), pegaAltura((*tree)->dir)) + 1;
        aux->altura = maior(pegaAltura(aux->dir), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoED(Avl **tree)
{
    rotacaoDD(&(*tree)->esq);
    rotacaoEE(tree);
}
void rotacaoDE(Avl **tree)
{
    rotacaoEE(&(*tree)->dir);
    rotacaoDD(tree);
}
int insercao(Avl **tree, int valor)
{
    int inseriu = -1;
    if (*tree == NULL)
    {
        *tree = (Avl *)malloc(sizeof(Avl));
        (*tree)->info = valor;
        (*tree)->altura = 0;
        (*tree)->esq = NULL;
        (*tree)->dir = NULL;
        inseriu = 1;
    }
    else
    {
        if ((*tree)->info > valor)
        {
            if ((inseriu = insercao(&(*tree)->esq, valor) == 1))
            {
                if (fatorBal(*tree) >= 2)
                {
                    if ((*tree)->esq->info > valor)
                        rotacaoEE(&(*tree));
                    else
                        rotacaoED(&(*tree));
                }
            }
        }
        else
        {
            if ((*tree)->info < valor)
            {
                if ((inseriu = insercao(&(*tree)->dir, valor)) == 1)
                {
                    if (fatorBal(*tree) >= 2)
                    {
                        if ((*tree)->dir->info < valor)
                            rotacaoDD(&(*tree));
                        else
                            rotacaoDE(&(*tree));
                    }
                }
            }
        }
        (*tree)->altura = pegaAltura((*tree)) + 1;
    }
    return inseriu;
}
int ehfolha(Avl *tr)
{
    return (tr->esq == NULL && tr->dir == NULL);
}

int menorEsq(Avl *tr)
{
    int menor = -1;
    if (tr != NULL)
    {
        if (ehfolha(tr))
            menor = 0;
        if (tr->esq == NULL)
            menor = menorEsq(tr->dir);
        else if (tr->dir == NULL)
            menor = menorEsq(tr->esq);
        else
        {
            int esq = menorEsq(tr->esq);
            int dir = menorDir(tr->dir);
            menor = esq < dir ? esq : dir;
        }
    }
    return menor + 1;
}

int menorDir(Avl *tr)
{
    int menor = -1;
    if (tr != NULL)
    {
        if (ehfolha(tr))
            menor = 0;
        if (tr->esq == NULL)
            menor = menorDir(tr->dir);
        else if (tr->dir == NULL)
            menor = menorDir(tr->esq);
        else
        {
            int esq = menorEsq(tr->esq);
            int dir = menorDir(tr->dir);
            menor = esq < dir ? esq : dir;
        }
    }
    return menor + 1;
}
int folhaRaza(Avl *tr)
{
    int menor = -1;
    if (tr != NULL)
    {
        int esq, dir;
        if (tr->esq != NULL && tr->dir != NULL)
        {
            if (ehfolha(tr->esq) || ehfolha(tr->dir))
            {
                menor = 1;
            }
            else
            {
                esq = menorEsq(tr->esq);
                dir = menorDir(tr->dir);
                menor = esq < dir ? esq : dir;
            }
        }
        else
        {
            if (tr->esq == NULL)
                menor = menorDir(tr->dir);
            else if (tr->dir == NULL)
                menor = menorEsq(tr->esq);
        }
    }
    return menor;
}

int busca(Avl *tr, int valor)
{
    int achou = -1;
    if (tr != NULL)
    {
        if (tr->info == valor)
        {
            achou = 1;
        }
        else if (tr->info > valor)
            achou = busca(tr->esq, valor);
        else if (tr->info < valor)
            achou = busca(tr->dir, valor);
    }
    return achou;
}

void mostraArvore(Avl *a, int b)
{
    if (a == NULL)
    {
        imprimeNo(NULL, b);
        return;
    }
    mostraArvore(a->dir, b + 1);
    imprimeNo(a->info, b);
    mostraArvore(a->esq, b + 1);
}

// A função auxiliar imprimeNo imprime o caracter
// c precedido de 3b espaços e seguido de uma mudança
// de linha.
void imprimeNo(int c, int b)
{
    int i;
    for (i = 0; i < b; i++)
        printf("     ");
    if (c == NULL)
        printf("NULL\n");
    else
        printf("%d\n", c);
}

void main()
{
    clock_t tempo1, tempo2;
    Diferencas *dif = (Diferencas *)malloc(sizeof(Diferencas));
    int lenofdif = 0;
    double tf;
    int i;
    srand(time(NULL));
    for (i = 0; i < 30; i++)
    {
        Avl *tree = NULL;

        int j;
        // gerar numeros
        tempo1 = clock();
        for (j = 0; j < TAM / 2; j++)
            while (insercao(&tree, (rand() % TAM * 1000000)) == -1)
                ;
        for (j = 0; j < TAM / 2; j++)
            while (insercao(&tree, (rand() % 1000000)) == -1)
                ;
        tempo2 = clock();
        tf = (tempo2 - tempo1) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo de insercao: %lf\n", tf);

        // busca
        tempo1 = clock();
        printf("achou? %d\n", busca(tree, 1000));
        tempo2 = clock();
        tf = (tempo2 - tempo1) * 1000.0 / CLOCKS_PER_SEC;
        printf("Tempo de busca %lf\n", tf);

        // maior e menor profundidade
        printf("Maior profundidade: %d - Menor profundidade: %d\n", tree->altura, folhaRaza(tree));
        printf("------------------------------------------\n");
        // gravar as diferecas e suas repeticoes.
        for (j = 0; j < lenofdif; j++)
            if ((dif + j)->num == tree->altura - folhaRaza(tree))
                break;
        if (j == lenofdif)
        {
            dif = (Diferencas *)realloc(dif, (lenofdif + 1) * sizeof(Diferencas));
            (dif + lenofdif)->num = tree->altura - folhaRaza(tree);
            (dif + lenofdif)->quant = 1;
            lenofdif++;
        }
        else
            (dif + j)->quant++;

        free(tree);
    }
    for (i = 0; i < lenofdif; i++)
        printf("diferenca: %d, repeticoes: %d\n", (dif + i)->num, (dif + i)->quant);
}