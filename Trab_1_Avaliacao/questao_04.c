#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct termos Termos;
typedef struct pags Pags;
typedef struct subtermos Subtermos;

struct termos
{
    int altura;
    char *termo;
    Pags *pag;
    Subtermos *sub;
    Termos *esq, *dir;
};

struct subtermos
{
    int altura;
    char subtermo[50];
    Pags *pag;
    Subtermos *esq, *dir;
};

struct pags
{
    int altura;
    int pag;
    Pags *esq, *dir;
};

// Inserir Termos;
int pegaAltura(Termos *raiz)
{
    int alt = 0;
    if (raiz != NULL)
    {
        int alt_esq = pegaAltura(raiz->esq);
        int alt_dir = pegaAltura(raiz->dir);
        if (alt_esq > alt_dir)
        {
            alt = alt_esq + 1;
        }
        else
        {
            alt = alt_dir + 1;
        }
    }
    return alt;
}
int atribuiAlturaTermo(Termos *esq, Termos *dir)
{
    int n = 0;
    if (esq != NULL && dir != NULL)
        n = esq->altura > dir->altura ? esq->altura : dir->altura;
    else
    {
        if (esq != NULL && dir == NULL)
            n = esq->altura;
        else if (esq == NULL && dir != NULL)
            n = dir->altura;
    }
    return n;
}
int alturaBal(Termos *tr)
{
    return tr == NULL ? -1 : tr->altura;
}
int fatorBal(Termos *tree)
{
    int bl;
    bl = tree != NULL ? abs(alturaPagBal(tree->esq) - alturaPagBal(tree->dir)) : 0;
    return bl;
}

int maior(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
void rotacaoEE(Termos **tree)
{
    if ((*tree)->esq != NULL)
    {
        Termos *aux = (*tree)->esq;
        (*tree)->esq = aux->dir;
        aux->dir = *tree;
        (*tree)->altura = maior(pegaAltura((*tree)->esq), pegaAltura((*tree)->dir)) + 1;
        aux->altura = maior(pegaAltura(aux->esq), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoDD(Termos **tree)
{
    if ((*tree)->dir != NULL)
    {
        Termos *aux = (*tree)->dir;
        (*tree)->dir = aux->esq;
        aux->esq = *tree;
        (*tree)->altura = maior(pegaAltura((*tree)->esq), pegaAltura((*tree)->dir)) + 1;
        aux->altura = maior(pegaAltura(aux->dir), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoED(Termos **tree)
{
    rotacaoDD(&(*tree)->esq);
    rotacaoEE(&(*tree));
}
void rotacaoDE(Termos **tree)
{
    rotacaoEE(&(*tree)->dir);
    rotacaoDD(&(*tree));
}

int insereTermos(Termos **tree, char *term)
{
    int inseriu = -1;
    if (*tree == NULL)
    {
        *tree = (Termos *)malloc(sizeof(Termos));
        (*tree)->termo = (char *)malloc(sizeof(char) * strlen(term));
        strcpy((*tree)->termo, term);
        (*tree)->altura = 0;
        (*tree)->sub = NULL;
        (*tree)->pag = NULL;
        (*tree)->esq = NULL;
        (*tree)->dir = NULL;
        inseriu = 1;
    }
    else
    {
        if (strcmp((*tree)->termo, term) == 1)
        {
            if ((inseriu = insereTermos(&(*tree)->esq, term) == 1))
            {
                if (fatorBal(*tree) >= 2)
                {
                    if (strcmp((*tree)->esq->termo, term) == 1)
                        rotacaoEE(&(*tree));
                    else
                        rotacaoED(&(*tree));
                }
            }
        }
        else
        {
            if (strcmp((*tree)->termo, term) == -1)
            {
                if ((inseriu = insereTermos(&(*tree)->dir, term)) == 1)
                {
                    if (fatorBal(*tree) >= 2)
                    {
                        if (strcmp((*tree)->dir->termo, term) == -1)
                            rotacaoDD(&(*tree));
                        else
                            rotacaoDE(&(*tree));
                    }
                }
            }
        }
        (*tree)->altura = pegaAltura((*tree));
    }
    return inseriu;
}

// Inserir pag;

int pegaAlturaPag(Pags *raiz)
{
    int alt = 0;
    if (raiz != NULL)
    {
        int alt_esq = pegaAlturaPag(raiz->esq);
        int alt_dir = pegaAlturaPag(raiz->dir);
        if (alt_esq > alt_dir)
            alt = alt_esq + 1;
        else
            alt = alt_dir + 1;
    }
    return alt;
}

int alturaPagBal(Pags *tr)
{
    return tr == NULL ? -1 : tr->altura;
}
int fatorPagBal(Pags *tree)
{
    int bl;
    bl = tree != NULL ? abs(alturaPagBal(tree->esq) - alturaPagBal(tree->dir)) : 0;
    return bl;
}

void rotacaoPagEE(Pags **tree)
{
    if ((*tree)->esq != NULL)
    {
        Pags *aux = (*tree)->esq;
        (*tree)->esq = aux->dir;
        aux->dir = *tree;
        (*tree)->altura = maior(pegaAlturaPag((*tree)->esq), pegaAlturaPag((*tree)->dir)) + 1;
        aux->altura = maior(pegaAlturaPag(aux->esq), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoPagDD(Pags **tree)
{
    if ((*tree)->dir != NULL)
    {
        Pags *aux = (*tree)->dir;
        (*tree)->dir = aux->esq;
        aux->esq = *tree;
        (*tree)->altura = maior(pegaAlturaPag((*tree)->esq), pegaAlturaPag((*tree)->dir)) + 1;
        aux->altura = maior(pegaAlturaPag(aux->dir), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoPagED(Pags **tree)
{
    rotacaoPagDD(&(*tree)->esq);
    rotacaoPagEE(&(*tree));
}
void rotacaoPagDE(Pags **tree)
{
    rotacaoPagEE(&(*tree)->dir);
    rotacaoPagDD(&(*tree));
}

int inserirPag(Pags **pags, int pag)
{
    int inseriu = -1;
    if ((*pags) == NULL)
    {
        (*pags) = (Pags *)malloc(sizeof(Pags));
        (*pags)->pag = pag;
        (*pags)->altura = 0;
        (*pags)->esq = NULL;
        (*pags)->dir = NULL;
        inseriu = 1;
    }
    else
    {
        if ((*pags)->pag > pag)
        {
            if ((inseriu = inserirPag(&(*pags)->esq, pag) == 1))
            {
                if (fatorPagBal(*pags) >= 2)
                {
                    if ((*pags)->esq->pag > pag)
                        rotacaoPagEE(&(*pags));
                    else
                        rotacaoPagED(&(*pags));
                }
            }
        }
        else
        {
            if ((*pags)->pag < pag)
            {
                if ((inseriu = inserirPag(&(*pags)->dir, pag) == 1))
                {
                    if (fatorPagBal(*pags) >= 2)
                    {
                        if ((*pags)->dir->pag < pag)
                            rotacaoPagDD(&(*pags));
                        else
                            rotacaoPagDE(&(*pags));
                    }
                }
            }
        }
        (*pags)->altura = pegaAlturaPag((*pags));
    }
    return inseriu;
}

int inserirPagInTermo(Termos **ter, char *termo, int pag)
{
    int inseriu = -1;
    if ((*ter) != NULL)
    {
        if (strcmp((*ter)->termo, termo) == 0)
            inseriu = inserirPag(&(*ter)->pag, pag);
        else if (strcmp((*ter)->termo, termo) == 1)
            inseriu = inserirPagInTermo(&(*ter)->esq, termo, pag);
        else if (strcmp((*ter)->termo, termo) == -1)
            inseriu = inserirPagInTermo(&(*ter)->dir, termo, pag);
    }
    return inseriu;
}

// Inserir subtermos
int pegaAlturaSub(Subtermos *raiz)
{
    int alt = 0;
    if (raiz != NULL)
    {
        int alt_esq = pegaAlturaSub(raiz->esq);
        int alt_dir = pegaAlturaSub(raiz->dir);
        if (alt_esq > alt_dir)
            alt = alt_esq + 1;
        else
            alt = alt_dir + 1;
    }
    return alt;
}

int alturaSubBal(Subtermos *tr)
{
    return tr == NULL ? -1 : tr->altura;
}
int fatorSubBal(Subtermos *tree)
{
    int bl;
    bl = tree != NULL ? abs(alturaSubBal(tree->esq) - alturaSubBal(tree->dir)) : 0;
    return bl;
}

void rotacaoSubEE(Subtermos **tree)
{
    if ((*tree)->esq != NULL)
    {
        Subtermos *aux = (*tree)->esq;
        (*tree)->esq = aux->dir;
        aux->dir = *tree;
        (*tree)->altura = maior(pegaAlturaSub((*tree)->esq), pegaAlturaSub((*tree)->dir)) + 1;
        aux->altura = maior(pegaAlturaSub(aux->esq), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoSubDD(Subtermos **tree)
{
    if ((*tree)->dir != NULL)
    {
        Subtermos *aux = (*tree)->dir;
        (*tree)->dir = aux->esq;
        aux->esq = *tree;
        (*tree)->altura = maior(pegaAlturaSub((*tree)->esq), pegaAlturaSub((*tree)->dir)) + 1;
        aux->altura = maior(pegaAlturaSub(aux->dir), (*tree)->altura) + 1;
        (*tree) = aux;
    }
}
void rotacaoSubED(Subtermos **tree)
{
    rotacaoSubDD(&(*tree)->esq);
    rotacaoSubEE(&(*tree));
}
void rotacaoSubDE(Subtermos **tree)
{
    rotacaoSubEE(&(*tree)->dir);
    rotacaoSubDD(&(*tree));
}
int inserirSub(Subtermos **subs, char *sub)
{
    int inseriu = -1;
    if ((*subs) == NULL)
    {
        (*subs) = (Subtermos *)calloc(1, sizeof(Subtermos));
        strcpy((*subs)->subtermo, sub);
        (*subs)->pag = NULL;
        (*subs)->esq = NULL;
        (*subs)->dir = NULL;
        inseriu = 1;
    }
    else
    {
        if (strcmp((*subs)->subtermo, sub) == 1)
        {
            if ((inseriu = inserirSub(&(*subs)->esq, sub) == 1))
            {
                if (fatorSubBal(*subs) >= 2)
                {
                    if (strcmp((*subs)->esq->subtermo, sub) == 1)
                        rotacaoSubEE(&(*subs));
                    else
                        rotacaoSubED(&(*subs));
                }
            }
        }
        else
        {
            if (strcmp((*subs)->subtermo, sub) == -1)
            {
                if ((inseriu = inserirSub(&(*subs)->dir, sub)) == 1)
                {
                    if (fatorSubBal(*subs) >= 2)
                    {
                        if (strcmp((*subs)->dir->subtermo, sub) == -1)
                            rotacaoSubDD(&(*subs));
                        else
                            rotacaoSubDE(&(*subs));
                    }
                }
            }
        }
        (*subs)->altura = pegaAlturaSub((*subs));
    }
    return inseriu;
}
int inserirSubTermoInTermo(Termos **ter, char *termo, char *sub)
{
    int inseriu = -1;
    if ((*ter) != NULL)
    {
        if (strcmp((*ter)->termo, termo) == 0)
            inseriu = inserirSub(&(*ter)->sub, sub);
        else if (strcmp((*ter)->termo, termo) == 1)
            inseriu = inserirSubTermoInTermo(&(*ter)->esq, termo, sub);
        else if (strcmp((*ter)->termo, termo) == -1)
            inseriu = inserirSubTermoInTermo(&(*ter)->dir, termo, sub);
    }
    return inseriu;
}
// Inserir paginas em subtermos.
void procuraSub(Subtermos **subs, char *sub, int pag)
{
    if ((*subs) != NULL)
    {
        if (strcmp((*subs)->subtermo, sub) == 0)
            inserirPag(&(*subs)->pag, pag);
        else if (strcmp((*subs)->subtermo, sub) == 1)
            procuraSub(&(*subs)->esq, sub, pag);
        else if (strcmp((*subs)->subtermo, sub) == -1)
            procuraSub(&(*subs)->dir, sub, pag);
    }
}
void inserirPagInSub(Termos **ter, char *termo, char *sub, int pag)
{
    if ((*ter) != NULL)
    {
        if (strcmp((*ter)->termo, termo) == 0)
        {
            procuraSub(&(*ter)->sub, sub, pag);
        }
        else if (strcmp((*ter)->termo, termo) == 1)
            inserirPagInSub(&(*ter)->esq, termo, sub, pag);
        else if (strcmp((*ter)->termo, termo) == -1)
            inserirPagInSub(&(*ter)->dir, termo, sub, pag);
    }
}
// Imprimir os termos, subtermos e paginas.
void mostrarPag(Pags *bt)
{
    if (bt != NULL)
    {
        printf("%d ", bt->pag);
        mostrarPag(bt->esq);
        mostrarPag(bt->dir);
    }
}
void mostrarSub(Subtermos *bt, int tab)
{
    if (bt != NULL)
    {
        mostrarSub(bt->esq, tab);
        int i;
        for (i = 0; i < tab; i++)
            printf("-");
        printf(" %s %c ", bt->subtermo, bt->pag == NULL ? ' ' : '-');
        printf("%s", bt->pag != NULL ? "pags: " : " ");
        mostrarPag(bt->pag);
        printf("\n");
        mostrarSub(bt->dir, tab);
    }
}
void mostrarTermo(Termos *bt)
{
    if (bt != NULL)
    {
        mostrarTermo(bt->esq);
        printf("%s %c ", bt->termo, bt->pag == NULL ? ' ' : '-');
        printf("%s", bt->pag != NULL ? "pags: " : " ");
        mostrarPag(bt->pag);
        printf("\n");
        mostrarSub(bt->sub, strlen(bt->termo));
        mostrarTermo(bt->dir);
    }
}

void main()
{
    Termos *term = NULL;
    clock_t tempo1, tempo2;
    double tf;

    tempo1 = clock();
    insereTermos(&term, "test3");
    insereTermos(&term, "test5");
    insereTermos(&term, "test2");
    insereTermos(&term, "test1");
    insereTermos(&term, "test6");
    insereTermos(&term, "test10");
    insereTermos(&term, "test20");
    insereTermos(&term, "test8");
    insereTermos(&term, "test50");

    inserirPagInTermo(&term, "test3", 4);
    inserirPagInTermo(&term, "test3", 1);
    inserirPagInTermo(&term, "test3", 10);
    inserirPagInTermo(&term, "test3", 2);

    inserirSubTermoInTermo(&term, "test3", "test345");
    inserirSubTermoInTermo(&term, "test3", "test3456");
    inserirSubTermoInTermo(&term, "test3", "test3457");
    inserirSubTermoInTermo(&term, "test3", "test3458");

    inserirSubTermoInTermo(&term, "test4", "test445");
    inserirSubTermoInTermo(&term, "test4", "test4456");
    inserirSubTermoInTermo(&term, "test4", "test4457");
    inserirSubTermoInTermo(&term, "test4", "test4458");

    inserirSubTermoInTermo(&term, "test5", "test545");
    inserirSubTermoInTermo(&term, "test5", "test5456");
    inserirSubTermoInTermo(&term, "test5", "test5457");
    inserirSubTermoInTermo(&term, "test5", "test5458");

    inserirSubTermoInTermo(&term, "test6", "test645");
    inserirSubTermoInTermo(&term, "test6", "test6456");
    inserirSubTermoInTermo(&term, "test6", "test6457");
    inserirSubTermoInTermo(&term, "test6", "test6458");

    inserirSubTermoInTermo(&term, "test1", "test145");
    inserirSubTermoInTermo(&term, "test1", "test1456");
    inserirSubTermoInTermo(&term, "test1", "test1457");
    inserirSubTermoInTermo(&term, "test1", "test1458");

    inserirSubTermoInTermo(&term, "test2", "test245");
    inserirSubTermoInTermo(&term, "test2", "test2456");
    inserirSubTermoInTermo(&term, "test2", "test2457");
    inserirSubTermoInTermo(&term, "test2", "test2458");

    inserirPagInSub(&term, "test3", "test345", 33);
    inserirPagInSub(&term, "test3", "test345", 48);
    inserirPagInSub(&term, "test3", "test345", 22);

    inserirPagInSub(&term, "test4", "test445", 75);
    inserirPagInSub(&term, "test4", "test445", 80);
    inserirPagInSub(&term, "test4", "test445", 76);

    inserirPagInSub(&term, "test5", "test545", 80);
    inserirPagInSub(&term, "test5", "test545", 90);
    inserirPagInSub(&term, "test5", "test545", 85);

    inserirPagInSub(&term, "test6", "test645", 40);
    inserirPagInSub(&term, "test6", "test645", 35);
    inserirPagInSub(&term, "test6", "test645", 46);

    inserirPagInSub(&term, "test1", "test145", 100);
    inserirPagInSub(&term, "test1", "test145", 106);
    inserirPagInSub(&term, "test1", "test145", 97);

    inserirPagInSub(&term, "test2", "test245", 133);
    inserirPagInSub(&term, "test2", "test245", 140);
    inserirPagInSub(&term, "test2", "test245", 122);
    tempo2 = clock();
    tf = (tempo2 - tempo1) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo de insercao: %lf\n", tf);

    tempo1 = clock();
    mostrarTermo(term);
    tempo2 = clock();
    tf = (tempo2 - tempo1) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo para Buscar e Mostrar todos os elementos: %lf\n", tf);

    free(term);
}