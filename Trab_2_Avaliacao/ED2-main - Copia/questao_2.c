#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

enum cores
{
    RED = 1,
    BLACK = 0
};

typedef struct ArvLLBB ArvLLRB;

struct ArvLLBB
{
    char cod[7];
    char tipo[30];
    char marca[30];
    int tamanho;
    int quantidade;
    float preco;
    int pos;
    int cores;
    ArvLLRB *esq, *dir;
};

enum cores cor(ArvLLRB *H)
{
    return H != NULL ? H->cores : BLACK;
}
void trocaCor(ArvLLRB **H)
{
    (*H)->cores = !(*H)->cores;
    if ((*H)->esq != NULL)
        (*H)->esq->cores = !(*H)->esq->cores;
    if ((*H)->dir != NULL)
        (*H)->dir->cores = !(*H)->dir->cores;
}
ArvLLRB *rotacionaEsquerda(ArvLLRB **A)
{
    ArvLLRB *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    B->cores = (*A)->cores;
    (*A)->cores = RED;
    return B;
}
// Rotação à direita
ArvLLRB *rotacionaDireita(ArvLLRB **A)
{
    ArvLLRB *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    B->cores = (*A)->cores;
    (*A)->cores = RED;
    return B;
}

// Inserindo um elemento na árvore rubro-negra
ArvLLRB *insereNO(ArvLLRB **H, char *cod, char *tipo, char *marca, int tamanho, int quantidade, float preco, int pos, int *resp)
{
    if (*H == NULL)
    {
        ArvLLRB *novo;
        novo = (ArvLLRB *)malloc(sizeof(ArvLLRB));
        if (novo == NULL)
        {
            *resp = 0;
            return NULL;
        }
        strcpy(novo->cod, cod);
        strcpy(novo->tipo, tipo);
        strcpy(novo->marca, marca);
        novo->tamanho = tamanho;
        novo->quantidade = quantidade;
        novo->preco = preco;
        novo->pos = pos;
        novo->cores = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if (strcmp(cod, (*H)->cod) == 0)
        *resp = 0; // Valor duplicado
    else
    {
        if (strcmp(cod, (*H)->cod) < 0)
            (*H)->esq = insereNO(&(*H)->esq, cod, tipo, marca, tamanho, quantidade, preco, pos, resp);
        else
            (*H)->dir = insereNO(&(*H)->dir, cod, tipo, marca, tamanho, quantidade, preco, pos, resp);
    }
    if (cor((*H)->dir) == RED && cor((*H)->esq) == BLACK)
        *H = rotacionaEsquerda(H);
    if (cor((*H)->esq) == RED && cor((*H)->esq->esq) == RED)
        *H = rotacionaDireita(H);
    if (cor((*H)->esq) == RED && cor((*H)->dir) == RED)
        trocaCor(&(*H));

    return *H;
}
int insere_ArvLLRB(ArvLLRB **raiz, char *cod, char *tipo, char *marca, int tamanho, int quantidade, float preco, int pos)
{
    int resp;
    (*raiz) = insereNO(&(*raiz), cod, tipo, marca, tamanho, quantidade, preco, pos, &resp);
    if ((*raiz) != NULL)
        (*raiz)->cores = BLACK;
    return resp;
}

ArvLLRB *criaArvLLRB()
{
    FILE *arq = fopen("calcados.txt", "r");

    ArvLLRB *tree = NULL;
    if (arq == NULL)
        printf("nao abriu\n");
    int tamanho, quantidade;
    float preco;
    char cod[7], tipo[20], marca[20];

    int pos = 1;
    while (fscanf(arq, "%s %s %s %d %d %f", cod, tipo, marca, &tamanho, &quantidade, &preco) != EOF)
    {
        insere_ArvLLRB(&tree, cod, tipo, marca, tamanho, quantidade, preco, pos);
        pos++;
    }
    fclose(arq);
    return tree;
}
ArvLLRB **buscaCalcado(ArvLLRB **tree, char *codigo)
{
    ArvLLRB **NO;
    NO = NULL;
    if (*tree != NULL)
    {
        if (strcmp(codigo, (*tree)->cod) == 0)
        {
            NO = tree;
        }
        if (strcmp(codigo, (*tree)->cod) < 0)
            NO = buscaCalcado(&(*tree)->esq, codigo);
        else if (strcmp(codigo, (*tree)->cod) > 0)
            NO = buscaCalcado(&(*tree)->dir, codigo);
    }
    return NO;
}
ArvLLRB **buscaTestes(ArvLLRB **tree, char *codigo, int n)
{
    ArvLLRB **NO;
    NO = NULL;
    if (*tree != NULL)
    {
        if (strcmp(codigo, (*tree)->cod) == 0)
        {
            NO = tree;
        }
        if (strcmp(codigo, (*tree)->cod) < 0)
        {
            printf("%d-left ", n);
            NO = buscaTestes(&(*tree)->esq, codigo, ++n);
        }
        else if (strcmp(codigo, (*tree)->cod) > 0)
        {
            printf("%d-right ", n);
            NO = buscaTestes(&(*tree)->dir, codigo, ++n);
        }
    }
    return NO;
}

void grava(ArvLLRB *tree, FILE *arq)
{
    if (tree != NULL)
    {
        grava(tree->esq, arq);
        fprintf(arq, "%s %s %s %d %d %.2f\n", tree->cod, tree->tipo, tree->marca, tree->tamanho, tree->quantidade, tree->preco);
        grava(tree->dir, arq);
    }
}
void gravaArvLLRB(ArvLLRB *tree)
{
    FILE *arq = fopen("calcados.txt", "w");
    fclose(arq);
    arq = fopen("calcados.txt", "a");
    grava(tree, arq);
    fclose(arq);
}

void insereCalcado(ArvLLRB **tree, char *codigo, int quantidade)
{
    ArvLLRB **aux = buscaCalcado(tree, codigo);

    if (aux != NULL)
    {
        (*aux)->quantidade += quantidade;
        printf("--> Nova quantidade: %d\n", (*aux)->quantidade);
        gravaArvLLRB(*tree);
    }
    else
        printf("Produto não registrado!\n");
}

void vendeCalcado(ArvLLRB **tree, char *codigo, int quantidade)
{
    ArvLLRB **aux = buscaCalcado(tree, codigo);
    if (aux != NULL)
    {
        if (strcmp((*aux)->cod, codigo) == 0)
        {
            (*aux)->quantidade -= quantidade;
            if ((*aux)->quantidade < 0)
                (*aux)->quantidade = 0;
            printf("Nova quantidade: %d\n", (*aux)->quantidade);
        }
        gravaArvLLRB(*tree);
    }
    else
        printf("Produto não registrado!\n");
}

void mostra(ArvLLRB *tree)
{
    if (tree != NULL)
    {
        mostra(tree->esq);
        printf("%5d | %10s | %10s | %10s | %10d | %10d | R$%5.2f\n", tree->pos,
               tree->cod,
               tree->tipo,
               tree->marca,
               tree->tamanho,
               tree->quantidade,
               tree->preco);
        printf("-----------------------------------------------------------------------------------\n");
        mostra(tree->dir);
    }
}
void tabela(ArvLLRB *tree)
{
    if (tree != NULL)
    {
        printf("-----------------------------------------------------------------------------------\n");
        printf("%4s | %10s | %10s | %10s | %10s | %8s | %5s\n", "Linha",
               "Codigo",
               "Tipo",
               "Marca",
               "Tamanho",
               "Quantidade",
               "Preço");
        printf("-----------------------------------------------------------------------------------\n");
        mostra(tree);
        printf("\n");
    }
}

int noFundo(ArvLLRB *raiz)
{
    int maxD = 0, maxE = 0, maior = -1;

    if (raiz != NULL)
    {
        maxE = noFundo(raiz->esq) + 1;
        maxD = noFundo(raiz->dir) + 1;

        if (maxD > maxE)
            maior = maxD;
        else
            maior = maxE;
    }
    return maior;
}

int noRazo(ArvLLRB *raiz)
{
    int maxD = 0, maxE = 0, menor = -1;

    if (raiz != NULL)
    {
        maxE = noRazo(raiz->esq) + 1;
        maxD = noRazo(raiz->dir) + 1;

        if (maxD < maxE)
            menor = maxD;
        else
            menor = maxE;
    }
    return menor;
}

int main()
{
    ArvLLRB *tree = criaArvLLRB();

    //-----------------------------  TESTES  ---------------------------------//
    clock_t tempoI, tempoF;
    double tf;
    char *nums[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    // printf("%s\n", tree->cod);
    tempoI = clock();
    srand(time(NULL));

    printf("codigo: %s\n--> ", "984079");
    ArvLLRB **sn = buscaTestes(&tree, "984079", 0);
    printf("Encontrou: %s \n\n", sn == NULL ? "Nao" : "Sim");
    for (int i = 0; i < 20; i++)
    {
        char codigo[7];
        codigo[0] = nums[rand() % 10];
        codigo[1] = nums[rand() % 10];
        codigo[2] = nums[rand() % 10];
        codigo[3] = nums[rand() % 10];
        codigo[4] = nums[rand() % 10];
        codigo[5] = nums[rand() % 10];
        codigo[6] = '\0';
        printf("codigo: %s\n--> ", codigo);
        ArvLLRB **sn = buscaTestes(&tree, codigo, 0);
        printf("Encontrou: %s \n\n", sn == NULL ? "Nao" : "Sim");
    }
    tempoF = clock();
    tf = ((tempoF) - (tempoI)) * 1000 / CLOCKS_PER_SEC;
    printf("time: %.2lf ms\n", tf);

    int menorNivel = noRazo(tree);
    int maiorNivel = noFundo(tree);
    printf("Maior nivel: %d | Menor nivel: %d \n", maiorNivel, menorNivel);
    //-----------------------------------------------------------------------//

    //-------------------------------------------  Usuario -------------------------------------------//
    // int escolha = 1;
    // do{
    //     printf("BEM-VINDO A SUA LOJA DE CALCADOS\n");
    //     printf("-->%3sInserir calcado[1]\n-->%3sVender calcado[2]\n-->%3sPesquisar Calcado[3]\n-->%3sCheca estoque[4]\n-->%3sSair[5]\n-->%3sO que desja fazer: ", " "," "," "," "," ", " ");
    //     scanf("%d", &escolha);
    //     char codigo[7];
    //     int quantidade;
    //     switch (escolha)
    //     {
    //         case 1:
    //             printf("digite o codigo do produto: ");
    //             scanf(" %s", codigo);
    //             printf("Quantidade: ");
    //             scanf("%d", &quantidade);
    //             insereCalcado(&tree, codigo, quantidade);
    //             break;
    //         case 2:
    //             printf("digite o codigo do produto: ");
    //             scanf(" %s", codigo);
    //             printf("Quantidade: ");
    //             scanf("%d", &quantidade);
    //             vendeCalcado(&tree, codigo, quantidade);
    //             break;
    //         case 3:
    //             printf("digite o codigo do produto: ");
    //             scanf(" %s", codigo);
    //             ArvLLRB **NO = buscaCalcado(&tree, codigo);
    //             if(NO != NULL){
    //                 printf("%10s | %10s | %10s | %10s | %8s | %5s\n", "Codigo",
    //                                                                   "Tipo",
    //                                                                   "Marca",
    //                                                                   "Tamanho",
    //                                                                   "Quantidade",
    //                                                                   "Preço");
    //                 printf("--------------------------------------------------------------------------\n");
    //                 printf("%10s | %10s | %10s | %10d | %10d | R$%5.2f\n",(*NO)->cod,
    //                                                                       (*NO)->tipo,
    //                                                                       (*NO)->marca,
    //                                                                       (*NO)->tamanho,
    //                                                                       (*NO)->quantidade,
    //                                                                       (*NO)->preco);
    //                 printf("--------------------------------------------------------------------------\n");
    //             }
    //             else{
    //                 printf("--------------------------------------------------------------------------\n");
    //                 printf("Calcado não registrado!\n");
    //                 printf("--------------------------------------------------------------------------\n");
    //             }
    //             break;
    //         case 4:
    //             tabela(tree);
    //             break;
    //         default:
    //             break;
    //     }
    // }while(escolha != 5);
    //--------------------------------------------------------------------------------------//
    return 0;
}
