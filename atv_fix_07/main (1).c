#include <stdio.h>
#include <stdlib.h>

enum cores
{
    RED = 1,
    BLACK = 0
};

typedef struct NO *ArvLLRB;
// typedef struct NO NO;

struct NO
{
    int info;
    int cores;
    struct NO *esq, *dir;
};

ArvLLRB *cria_ArvLLRB()
{
    ArvLLRB *raiz = (ArvLLRB *)malloc(sizeof(ArvLLRB));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }
    return raiz;
}
// =================================
// LIBERAR
// =================================
void libera_NO(struct NO *no)
{
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvLLRB(ArvLLRB *raiz)
{
    if (raiz == NULL)
        return;
    libera_NO(*raiz); // libera cada nó
    free(raiz);       // libera a raiz
}
enum cores cor(struct NO *H)
{
    return H != NULL ? H->cores : BLACK;
}
void trocaCor(struct NO *H)
{
    H->cores = !H->cores;
    if (H->esq != NULL)
        H->esq->cores = !H->esq->cores;
    if (H->dir != NULL)
        H->dir->cores = !H->dir->cores;
}
struct NO *rotacionaEsquerda(struct NO *A)
{
    struct NO *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cores = A->cores;
    A->cores = RED;
    return B;
}
// Rotação à direita
struct NO *rotacionaDireita(struct NO *A)
{
    struct NO *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cores = A->cores;
    A->cores = RED;
    return B;
}

// Inserindo um elemento na árvore rubro-negra
struct NO *insereNO(struct NO *H, int valor, int *resp)
{
    if (H == NULL)
    {
        struct NO *novo;
        novo = (struct NO *)malloc(sizeof(struct NO));
        if (novo == NULL)
        {
            *resp = 0;
            return NULL;
        }

        novo->info = valor;
        novo->cores = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if (valor == H->info)
        *resp = 0; // Valor duplicado
    else
    {
        if (valor < H->info)
            H->esq = insereNO(H->esq, valor, resp);
        else
            H->dir = insereNO(H->dir, valor, resp);
    }
    if (cor(H->dir) == RED && cor(H->esq) == BLACK)
        H = rotacionaEsquerda(H);
    if (cor(H->esq) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);
    if (cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);

    return H;
}
int insere_ArvLLRB(ArvLLRB *raiz, int valor)
{
    int resp;
    *raiz = insereNO(*raiz, valor, &resp);
    if ((*raiz) != NULL)
        (*raiz)->cores = BLACK;
    return resp;
}

// Movendo um nó vermelho para a esquerda
struct NO *move2EsqRED(struct NO *H)
{
    trocaCor(H);
    if (cor(H->dir->esq) == RED)
    {
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
}
struct NO *move2DirRED(struct NO *H)
{
    trocaCor(H);
    if (cor(H->esq->esq) == RED)
    {
        H->esq = rotacionaEsquerda(H->esq);
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
}

// Arrumando o balanceamento da rubro-negra
struct NO *balancear(struct NO *H)
{
    // Nó vermelho é sempre filho á esquerda
    if (cor(H->dir) == RED)
        H = rotacionaEsquerda(H);
    // Filho da direita e neto da esqureda são vermelhos
    if (H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED)
        H = rotacionaDireita(H);
    // 2 filhos vermelhos: troca cor!
    if (cor(H->esq) == RED && cor(H->dir) == RED)
        trocaCor(H);

    return H;
};

struct NO *removerMenor(struct NO *H)
{
    if (H->esq == NULL)
    {
        free(H);
        return NULL;
    }
    if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
        H = move2EsqRED(H);

    H->esq = removerMenor(H->esq);
    return balancear(H);
}

struct NO *procuraMenor(struct NO *atual)
{
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

struct NO *remove_NO(struct NO *H, int valor)
{
    if (valor < H->info)
    {
        if (cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK)
            H = move2EsqRED(H);
        H->esq = remove_NO(H->esq, valor);
    }
    else
    {
        if (cor(H->esq) == RED)
            H = rotacionaDireita(H);
        if (valor == H->info && (H->dir == NULL))
        {
            free(H);
            return NULL;
        }
        if (cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK)
            H = move2DirRED(H);
        if (valor < H->info)
        {
            struct NO *x = procuraMenor(H->dir);
            H->info = x->info;
            H->dir = removerMenor(H->dir);
        }
        else
            H->dir = remove_NO(H->dir, valor);
    }
    return balancear(H);
}

int consulta_ArvLLRB(struct NO *raiz, int valor)
{
    int resp = 0;
    if (valor == raiz->info)
        resp = 1;
    else
    {
        if (valor < raiz->info)
            resp = consulta_ArvLLRB(raiz->esq, valor);
        if (valor > raiz->info)
            resp = consulta_ArvLLRB(raiz->dir, valor);
    }
    return resp;
}
int remove_ArvLLRb(struct NO **raiz, int valor)
{
    if (consulta_ArvLLRB(*raiz, valor))
    {
        struct NO *h = *raiz;
        *raiz = remove_NO(h, valor);
        if (*raiz != NULL)
            (*raiz)->cores = BLACK;
        return 1;
    }
    else
        return 0;
}

void mostra(struct NO *tree)
{
    if (tree != NULL)
    {
        mostra(tree->esq);
        printf(" %d - ", tree->info);
        mostra(tree->dir);
    }
}

void mostraNO(int info, int cores, int b)
{
    for (int i = 0; i < b; i++)
        printf("            ");
    printf("___________\n");
    for (int i = 0; i < b; i++)
        printf("            ");
    printf("|%d- %s|\n", info, cores == RED ? "RED" : "BLACK");
    for (int i = 0; i < b; i++)
        printf("            ");
    printf("___________\n");
    printf("\n");
}
void mostraArv(struct NO *tree, int b)
{
    if (tree == NULL)
    {
        for (int i = 0; i < b + 1; i++)
            printf("            ");
        printf("NULL\n");
        return;
    }
    mostraArv(tree->dir, b + 1);
    mostraNO(tree->info, tree->cores, b);
    mostraArv(tree->esq, b + 1);
}

int main()
{
    ArvLLRB *tree = cria_ArvLLRB();
    int vet[6] = {200, 100, 300, 50, 150, 120};
    int vet1[7] = {500, 100, 200, 800, 300, 400, 350};
    int vet2[5] = {100, 200, 300, 150, 120};
    for (int i = 0; i < 7; i++)
        insere_ArvLLRB(tree, vet1[i]);
    // printf("%d\n", insere_ArvLLRB(&tree, 50));
    // printf("%d\n", insere_ArvLLRB(&tree, 80));
    // printf("%d\n", insere_ArvLLRB(&tree, 90));
    // printf("%d\n", insere_ArvLLRB(&tree, 40));
    // printf("%d\n", insere_ArvLLRB(&tree, 30));
    // printf("%d\n", insere_ArvLLRB(&tree, 20));
    // printf("%d\n", insere_ArvLLRB(&tree, 990));
    mostra(*tree);
    remove_ArvLLRb(&tree, 400);
    // mostra(tree);
    // printf("%d\n", remove_ArvLLRb(&tree, 90));
    mostra(*tree);
    printf("\n");
    mostraArv(*tree, 1);
    printf("\n");
    return 0;
}