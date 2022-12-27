#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

typedef struct termos Termos;
typedef struct pags Pags;
typedef struct subtermos Subtermos;

struct termos
{
    char *termo;
    Pags *pag;
    Subtermos *sub;
    Termos *esq, *dir;
};

struct subtermos
{
    char subtermo[50];
    Pags *pag;
    Subtermos *esq, *dir;
};

struct pags
{
    int pag;
    Pags *esq, *dir;
};

void inserirTermo(Termos **ter, char *termo)
{
    if ((*ter) == NULL)
    {
        (*ter) = (Termos *)malloc(sizeof(Termos));
        (*ter)->termo = (char *)malloc(sizeof(char) * strlen(termo));
        strcpy((*ter)->termo, termo);
        (*ter)->pag = NULL;
        (*ter)->sub = NULL;
        (*ter)->esq = NULL;
        (*ter)->dir = NULL;
    }
    else if (strcmp((*ter)->termo, termo) == 1)
        inserirTermo(&(*ter)->esq, termo);
    else if (strcmp((*ter)->termo, termo) == -1)
        inserirTermo(&(*ter)->dir, termo);
}

void inserirPag(Pags **pags, int pag)
{
    if ((*pags) == NULL)
    {
        (*pags) = (Pags *)malloc(sizeof(Pags));
        (*pags)->pag = pag;
        (*pags)->esq = NULL;
        (*pags)->dir = NULL;
    }
    else if ((*pags)->pag < pag)
    {
        inserirPag(&(*pags)->dir, pag);
    }
    else if ((*pags)->pag > pag)
    {
        inserirPag(&(*pags)->esq, pag);
    }
}
void inserirPagInTermo(Termos **ter, char *termo, int pag)
{
    if ((*ter) != NULL)
    {
        if (strcmp((*ter)->termo, termo) == 0)
            inserirPag(&(*ter)->pag, pag);
        else if (strcmp((*ter)->termo, termo) == 1)
            inserirPagInTermo(&(*ter)->esq, termo, pag);
        else if (strcmp((*ter)->termo, termo) == -1)
            inserirPagInTermo(&(*ter)->dir, termo, pag);
    }
}

void inserirSub(Subtermos **subs, char *sub)
{
    if ((*subs) == NULL)
    {
        (*subs) = (Subtermos *)calloc(1, sizeof(Subtermos));
        strcpy((*subs)->subtermo, sub);
        (*subs)->pag = NULL;
        (*subs)->esq = NULL;
        (*subs)->dir = NULL;
    }
    else if (strcmp((*subs)->subtermo, sub) == 1)
        inserirSub(&(*subs)->esq, sub);
    else if (strcmp((*subs)->subtermo, sub) == -1)
        inserirSub(&(*subs)->dir, sub);
    // else if ((*subs)->subtermo > sub)
    //     inserirSub(&(*subs)->esq, sub);
    // else if ((*subs)->subtermo < sub)
    //     inserirSub(&(*subs)->dir, sub);
}
void inserirSubTermoInTermo(Termos **ter, char *termo, char *sub)
{
    if ((*ter) != NULL)
    {
        if (strcmp((*ter)->termo, termo) == 0)
            inserirSub(&(*ter)->sub, sub);
        else if (strcmp((*ter)->termo, termo) == 1)
            inserirSubTermoInTermo(&(*ter)->esq, termo, sub);
        else if (strcmp((*ter)->termo, termo) == -1)
            inserirSubTermoInTermo(&(*ter)->dir, termo, sub);
    }
}
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

void mostrarPag(Pags *bt)
{
    if (bt != NULL)
    {
        mostrarPag(bt->esq);
        printf("%d ", bt->pag);
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
        printf("%s%c ", bt->termo, bt->pag == NULL ? ' ' : ',');
        printf("%s", bt->pag != NULL ? "pags: " : " ");
        mostrarPag(bt->pag);
        printf("\n");
        mostrarSub(bt->sub, strlen(bt->termo));
        mostrarTermo(bt->dir);
    }
}

void main()
{
    setlocale(LC_ALL, "Portuguese");
    clock_t tempo1, tempo2;
    double tf;

    Termos *termos = NULL;
    tempo1 = clock();
    inserirTermo(&termos, "test3");
    inserirTermo(&termos, "test5");
    inserirTermo(&termos, "test2");
    inserirTermo(&termos, "test1");
    inserirTermo(&termos, "test6");
    inserirTermo(&termos, "test4");
    inserirTermo(&termos, "test9");
    inserirTermo(&termos, "test8");
    inserirTermo(&termos, "test7");

    inserirPagInTermo(&termos, "test3", 4);
    inserirPagInTermo(&termos, "test3", 1);
    inserirPagInTermo(&termos, "test3", 10);
    inserirPagInTermo(&termos, "test3", 2);

    inserirSubTermoInTermo(&termos, "test3", "test3b");
    inserirSubTermoInTermo(&termos, "test3", "test3a");
    inserirSubTermoInTermo(&termos, "test3", "test3z");
    inserirSubTermoInTermo(&termos, "test3", "test3d");

    inserirSubTermoInTermo(&termos, "test4", "test445");
    inserirSubTermoInTermo(&termos, "test4", "test4456");
    inserirSubTermoInTermo(&termos, "test4", "test4457");
    inserirSubTermoInTermo(&termos, "test4", "test4458");

    inserirSubTermoInTermo(&termos, "test5", "test545");
    inserirSubTermoInTermo(&termos, "test5", "test5456");
    inserirSubTermoInTermo(&termos, "test5", "test5457");
    inserirSubTermoInTermo(&termos, "test5", "test5458");

    inserirSubTermoInTermo(&termos, "test6", "test645");
    inserirSubTermoInTermo(&termos, "test6", "test6456");
    inserirSubTermoInTermo(&termos, "test6", "test6457");
    inserirSubTermoInTermo(&termos, "test6", "test6458");

    inserirSubTermoInTermo(&termos, "test1", "test145");
    inserirSubTermoInTermo(&termos, "test1", "test1456");
    inserirSubTermoInTermo(&termos, "test1", "test1457");
    inserirSubTermoInTermo(&termos, "test1", "test1458");

    inserirSubTermoInTermo(&termos, "test2", "test245");
    inserirSubTermoInTermo(&termos, "test2", "test2456");
    inserirSubTermoInTermo(&termos, "test2", "test2457");
    inserirSubTermoInTermo(&termos, "test2", "test2458");

    inserirPagInSub(&termos, "test3", "test345", 33);
    inserirPagInSub(&termos, "test3", "test345", 48);
    inserirPagInSub(&termos, "test3", "test345", 22);

    inserirPagInSub(&termos, "test4", "test445", 75);
    inserirPagInSub(&termos, "test4", "test445", 80);
    inserirPagInSub(&termos, "test4", "test445", 76);

    inserirPagInSub(&termos, "test5", "test545", 80);
    inserirPagInSub(&termos, "test5", "test545", 90);
    inserirPagInSub(&termos, "test5", "test545", 85);

    inserirPagInSub(&termos, "test6", "test645", 40);
    inserirPagInSub(&termos, "test6", "test645", 35);
    inserirPagInSub(&termos, "test6", "test645", 46);

    inserirPagInSub(&termos, "test1", "test145", 100);
    inserirPagInSub(&termos, "test1", "test145", 106);
    inserirPagInSub(&termos, "test1", "test145", 97);

    inserirPagInSub(&termos, "test2", "test245", 133);
    inserirPagInSub(&termos, "test2", "test245", 140);
    inserirPagInSub(&termos, "test2", "test245", 122);
    tempo2 = clock();
    tf = (tempo2 - tempo1) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo de insercao: %lf\n", tf);

    tempo1 = clock();
    mostrarTermo(termos);
    tempo2 = clock();
    tf = (tempo2 - tempo1) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo para Buscar e Mostrar todos os elementos: %lf\n", tf);

    free(termos);
    system("PAUSE");
}
