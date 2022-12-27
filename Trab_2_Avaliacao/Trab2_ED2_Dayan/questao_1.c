#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Arv23 Arv23;

struct Arv23
{
    char cod[7];
    char tipo[30];
    char marca[30];
    int tamanho;
    int quantidade;
    float preco;
    int pos;

    char cod2[7];
    char tipo2[20];
    char marca2[20];
    int tamanho2;
    int quantidade2;
    float preco2;
    int pos2;

    int NInfos;
    Arv23 *esq, *cen, *dir;
};

int ehFolha(struct Arv23 *R)
{
    return (R->cen == NULL && R->esq == NULL && R->dir == NULL);
}

struct Arv23 *criaNo(char *cod, char *tipo, char *marca, int tamanho, int quantidade, float preco, int pos, struct Arv23 *FEsq, struct Arv23 *FCen, struct Arv23 *FDir)
{
    struct Arv23 *No;

    No = (struct Arv23 *)malloc(sizeof(struct Arv23));

    strcpy((*No).cod, cod);
    strcpy((*No).tipo, tipo);
    strcpy((*No).marca, marca);
    (*No).quantidade = quantidade;
    (*No).tamanho = tamanho;
    (*No).preco = preco;
    (*No).pos = pos;

    strcpy((*No).cod2, "000000");
    (*No).NInfos = 1;
    (*No).esq = FEsq;
    (*No).cen = FCen;
    (*No).dir = FDir;

    return No;
}
void adiciona(struct Arv23 **Raiz, char *cod, char *tipo, char *marca, int tamanho, int quantidade, float preco, int pos, struct Arv23 *MaiorNo)
{
    if (strcmp(cod, (*Raiz)->cod) > 0)
    {
        strcpy((*Raiz)->cod2, cod);
        strcpy((*Raiz)->tipo2, tipo);
        strcpy((*Raiz)->marca2, marca);
        (*Raiz)->tamanho2 = tamanho;
        (*Raiz)->quantidade2 = quantidade;
        (*Raiz)->preco2 = preco;
        (*Raiz)->pos2 = pos;
        (*Raiz)->dir = MaiorNo;
    }
    else
    {
        strcpy((*Raiz)->cod2, (*Raiz)->cod);
        strcpy((*Raiz)->tipo2, (*Raiz)->tipo);
        strcpy((*Raiz)->marca2, (*Raiz)->marca);
        (*Raiz)->tamanho2 = (*Raiz)->tamanho;
        (*Raiz)->quantidade2 = (*Raiz)->quantidade;
        (*Raiz)->preco2 = (*Raiz)->preco;
        (*Raiz)->pos2 = (*Raiz)->pos;

        strcpy((*Raiz)->cod, cod);
        strcpy((*Raiz)->tipo, tipo);
        strcpy((*Raiz)->marca, marca);
        (*Raiz)->tamanho = tamanho;
        (*Raiz)->quantidade = quantidade;
        (*Raiz)->preco = preco;
        (*Raiz)->pos = pos;

        (*Raiz)->dir = (*Raiz)->cen;
        (*Raiz)->cen = MaiorNo;
    }

    (*Raiz)->NInfos = 2;
}
struct Arv23 *quebraNo(struct Arv23 **Raiz, char cod[], char tipo[], char marca[], int tamanho, int quantidade, float preco, int pos, char *sobecod, char *sobetipo, char *sobemarca, int *sobetamanho, int *sobequantidade, float *sobepreco, int *sobepos, struct Arv23 *MaiorNo)
{
    struct Arv23 *Novo;
    if (strcmp(cod, (*Raiz)->cod) < 0)
    {
        // *sobe = (*Raiz)->Info1;
        strcpy(sobecod, (*Raiz)->cod);
        strcpy(sobetipo, (*Raiz)->tipo);
        strcpy(sobemarca, (*Raiz)->marca);
        *sobetamanho = (*Raiz)->tamanho;
        *sobequantidade = (*Raiz)->quantidade;
        *sobepreco = (*Raiz)->preco;
        *sobepos = (*Raiz)->pos;

        Novo = criaNo((*Raiz)->cod2, (*Raiz)->tipo2, (*Raiz)->marca2, (*Raiz)->tamanho2, (*Raiz)->quantidade2, (*Raiz)->preco, (*Raiz)->pos, (*Raiz)->cen, (*Raiz)->dir, NULL);
        // (*Raiz)->Info1 = valor;
        strcpy((*Raiz)->cod, cod);
        strcpy((*Raiz)->tipo, tipo);
        strcpy((*Raiz)->marca, marca);
        (*Raiz)->tamanho = tamanho;
        (*Raiz)->quantidade = quantidade;
        (*Raiz)->preco = preco;
        (*Raiz)->pos = pos;
        (*Raiz)->cen = MaiorNo;
    }
    else if (strcmp(cod, (*Raiz)->cod2) < 0)
    {
        strcpy(sobecod, cod);
        strcpy(sobetipo, tipo);
        strcpy(sobemarca, marca);
        *sobetamanho = tamanho;
        *sobequantidade = quantidade;
        *sobepreco = preco;
        *sobepos = pos;
        Novo = criaNo((*Raiz)->cod2, (*Raiz)->tipo2, (*Raiz)->marca2, (*Raiz)->tamanho2, (*Raiz)->quantidade2, (*Raiz)->preco2, (*Raiz)->pos2, MaiorNo, (*Raiz)->dir, NULL);
    }
    else
    {
        strcpy(sobecod, (*Raiz)->cod2);
        strcpy(sobetipo, (*Raiz)->tipo2);
        strcpy(sobemarca, (*Raiz)->marca2);
        *sobetamanho = (*Raiz)->tamanho2;
        *sobequantidade = (*Raiz)->quantidade2;
        *sobepreco = (*Raiz)->preco2;
        *sobepos = (*Raiz)->pos2;
        Novo = criaNo(cod, tipo, marca, tamanho, quantidade, preco, pos, (*Raiz)->dir, MaiorNo, NULL);
    }
    strcpy((*Raiz)->cod2, "000000");
    (*Raiz)->NInfos = 1;
    (*Raiz)->dir = NULL;

    return (Novo);
}
struct Arv23 *inserirArv23(struct Arv23 *Pai, struct Arv23 **Raiz, char *cod, char *tipo, char *marca, int tamanho, int quantidade, float preco, int pos, char *sobecod, char *sobetipo, char *sobemarca, int *sobetamanho, int *sobequantidade, float *sobepreco, int *sobepos)
{
    struct Arv23 *maiorNo;
    maiorNo = NULL;
    if (*Raiz == NULL)
        *Raiz = criaNo(cod, tipo, marca, tamanho, quantidade, preco, pos, NULL, NULL, NULL);
    else
    {
        if (ehFolha(*Raiz))
        {
            if ((*Raiz)->NInfos == 1)
                adiciona(Raiz, cod, tipo, marca, tamanho, quantidade, preco, pos, maiorNo);
            else // quando não tem espaço
            {
                struct Arv23 *novo;
                novo = quebraNo(Raiz, cod, tipo, marca, tamanho, quantidade, preco, pos, sobecod, sobetipo, sobemarca, sobetamanho, sobequantidade, sobepreco, sobepos, maiorNo);
                if (Pai == NULL)
                {
                    struct Arv23 *no;
                    no = criaNo(sobecod, sobetipo, sobemarca, *sobetamanho, *sobequantidade, *sobepreco, *sobepos, *Raiz, novo, NULL);
                    *Raiz = no;
                }
                else
                    maiorNo = novo;
            }
        }
        else
        { // quando não é folha
            if (strcmp(cod, (*Raiz)->cod) < 0)
                maiorNo = inserirArv23(*Raiz, &((*Raiz)->esq), cod, tipo, marca, tamanho, quantidade, preco, pos, sobecod, sobetipo, sobemarca, sobetamanho, sobequantidade, sobepreco, sobepos);
            else if ((*Raiz)->NInfos == 1 || strcmp(cod, (*Raiz)->cod2) < 0)
                maiorNo = inserirArv23(*Raiz, &((*Raiz)->cen), cod, tipo, marca, tamanho, quantidade, preco, pos, sobecod, sobetipo, sobemarca, sobetamanho, sobequantidade, sobepreco, sobepos);
            else
                maiorNo = inserirArv23(*Raiz, &((*Raiz)->dir), cod, tipo, marca, tamanho, quantidade, preco, pos, sobecod, sobetipo, sobemarca, sobetamanho, sobequantidade, sobepreco, sobepos);

            if (maiorNo != NULL)
            {
                if ((*Raiz)->NInfos == 1)
                {
                    adiciona(Raiz, sobecod, sobetipo, sobemarca, *sobetamanho, *sobequantidade, *sobepreco, *sobepos, maiorNo);
                    maiorNo = NULL;
                }
                else // quando não tem espaço
                {
                    char *sobecod1 = (char *)malloc(sizeof(char) * 6), sobetipo1[20], sobemarca1[20];
                    int sobequantidade1, sobetamanho1, sobepos1;
                    float sobepreco1;
                    struct Arv23 *novo;
                    novo = quebraNo(Raiz, sobecod, sobetipo, sobemarca, *sobetamanho, *sobequantidade, *sobepreco, *sobepos, sobecod1, sobetipo1, sobemarca1, &sobetamanho1, &sobequantidade1, &sobepreco1, &sobepos1, maiorNo);
                    if (Pai == NULL)
                    {
                        struct Arv23 *no;
                        no = criaNo(sobecod1, sobetipo1, sobemarca1, sobetamanho1, sobequantidade1, sobepreco1, sobepos1, *Raiz, novo, NULL);
                        *Raiz = no;
                        maiorNo = NULL;
                    }
                    else
                    {
                        maiorNo = novo;
                        strcpy(sobecod, sobecod1);
                        strcpy(sobetipo, sobetipo1);
                        strcpy(sobemarca, sobemarca1);
                        *sobetamanho = sobetamanho1;
                        *sobequantidade = sobequantidade1;
                        *sobepreco = sobepreco1;
                        *sobepos = sobepos1;
                    }
                }
            }
        }
    }
    return maiorNo;
}

Arv23 *criaArv23()
{
    FILE *arq = fopen("calcados.txt", "r");

    Arv23 *tree = NULL, *pai = NULL;
    if (arq == NULL)
        printf("nao abriu\n");
    int tamanho, quantidade;
    float preco;
    char cod[7], tipo[20], marca[20];

    int sobetamanho, sobequantidade;
    float sobepreco;
    char sobecod[7], sobetipo[20], sobemarca[20];

    int pos = 1, sobepos;
    while (fscanf(arq, " %s %s %s %d %d %f", cod, tipo, marca, &tamanho, &quantidade, &preco) != EOF)
    {
        inserirArv23(pai, &tree, cod, tipo, marca, tamanho, quantidade, preco, pos, sobecod, sobetipo, sobemarca, &sobetamanho, &sobequantidade, &sobepreco, &sobepos);
        pos++;
    }
    fclose(arq);
    return tree;
}

void grava(Arv23 *tree, FILE *arq)
{
    if (tree != NULL)
    {
        grava(tree->esq, arq);
        fprintf(arq, "%s %s %s %d %d %.2f\n", tree->cod, tree->tipo, tree->marca, tree->tamanho, tree->quantidade, tree->preco);
        grava(tree->cen, arq);
        if (tree->NInfos == 2)
        {
            fprintf(arq, "%s %s %s %d %d %.2f\n", tree->cod2, tree->tipo2, tree->marca2, tree->tamanho2, tree->quantidade2, tree->preco2);
        }
        grava(tree->dir, arq);
    }
}

void gravaArv23(Arv23 *tree)
{
    FILE *arq = fopen("calcados.txt", "w");
    fclose(arq);
    arq = fopen("calcados.txt", "a");
    grava(tree, arq);
    fclose(arq);
}

Arv23 **buscaCalcado(Arv23 **tree, char *codigo)
{
    Arv23 **NO;
    NO = NULL;
    if (*tree != NULL)
    {
        if (strcmp(codigo, (*tree)->cod) == 0 || strcmp(codigo, (*tree)->cod2) == 0)
        {
            NO = tree;
        }
        else
        {
            if (strcmp(codigo, (*tree)->cod) < 0)
            {
                NO = buscaCalcado(&(*tree)->esq, codigo);
            }
            else if (strcmp(codigo, (*tree)->cod2) < 0 || (*tree)->NInfos == 1)
            {
                NO = buscaCalcado(&(*tree)->cen, codigo);
            }
            else if ((*tree)->NInfos == 2 && strcmp((*tree)->cod2, codigo) < 0)
            {
                NO = buscaCalcado(&(*tree)->dir, codigo);
            }
        }
    }
    return NO;
}
Arv23 **buscaTestes(Arv23 **tree, char *codigo, int n)
{
    Arv23 **NO;
    NO = NULL;
    if (*tree != NULL)
    {
        if (strcmp(codigo, (*tree)->cod) == 0)
        {
            NO = tree;
        }
        else if (strcmp(codigo, (*tree)->cod2) == 0)
        {
            NO = tree;
        }
        else
        {
            if (strcmp(codigo, (*tree)->cod) < 0)
            {
                printf("%d-left ", n);
                NO = buscaTestes(&(*tree)->esq, codigo, ++n);
            }
            else if (strcmp(codigo, (*tree)->cod2) < 0 || (*tree)->NInfos == 1)
            {
                printf("%d-center ", n);
                NO = buscaTestes(&(*tree)->cen, codigo, ++n);
            }
            else
            {
                printf("%d-right ", n);
                NO = buscaTestes(&(*tree)->dir, codigo, ++n);
            }
        }
    }
    return NO;
}

void insereCalcado(Arv23 **tree, char *codigo, int quantidade)
{
    Arv23 **aux;
    aux = buscaCalcado(tree, codigo);
    if (aux != NULL)
    {
        if (strcmp((*aux)->cod, codigo) == 0)
        {
            (*aux)->quantidade += quantidade;
            printf("Nova quantidade: %d\n", (*aux)->quantidade);
        }
        else
        {
            (*aux)->quantidade2 += quantidade;
            printf("Nova quantidade: %d\n", (*aux)->quantidade2);
        }
    }
    else
        printf("Produto não registrado!\n");
}
void vendeCalcado(Arv23 **tree, char *codigo, int quantidade)
{
    Arv23 **aux;
    aux = buscaCalcado(tree, codigo);
    if (aux != NULL)
    {
        if (strcmp((*aux)->cod, codigo) == 0)
        {
            (*aux)->quantidade -= quantidade;
            if ((*aux)->quantidade < 0)
                (*aux)->quantidade = 0;
            printf("Nova quantidade: %d\n", (*aux)->quantidade);
        }
        else
        {
            (*aux)->quantidade2 -= quantidade;
            if ((*aux)->quantidade2 < 0)
                (*aux)->quantidade2 = 0;
            printf("Nova quantidade: %d\n", (*aux)->quantidade2);
        }
    }
    else
        printf("Produto não registrado!\n");
}

void mostra(Arv23 *tree)
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
        mostra(tree->cen);
        if (tree->NInfos == 2)
        {
            printf("%5d | %10s | %10s | %10s | %10d | %10d | R$%5.2f\n", tree->pos2,
                   tree->cod2,
                   tree->tipo2,
                   tree->marca2,
                   tree->tamanho2,
                   tree->quantidade2,
                   tree->preco2);
            printf("-----------------------------------------------------------------------------------\n");
        }
        mostra(tree->dir);
    }
}
void tabela(Arv23 *tree)
{
    if (tree != NULL)
    {
        printf("-----------------------------------------------------------------------------------\n");
        printf("%5s | %10s | %10s | %10s | %10s | %8s | %5s\n", "Linha",
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

int noFundo(Arv23 *tree)
{
    int maxD = 0, maxE = 0, maxC = 0, maior = -1;

    if (tree != NULL)
    {
        maxE = noFundo(tree->esq) + 1;
        maxC = noFundo(tree->cen) + 1;
        maxD = noFundo(tree->dir) + 1;

        if ((maxD > maxE) && (maxE > maxC))
            maior = maxD;
        else if ((maxE > maxD) && (maxD > maxC))
            maior = maxE;
        else
            maior = maxC;
    }
    return maior;
}

int noRazo(Arv23 *tree)
{
    int maxD = 0, maxE = 0, maxC = 0, menor = -1;

    if (tree != NULL)
    {
        maxE = noRazo(tree->esq) + 1;
        maxC = noRazo(tree->cen) + 1;
        maxD = noRazo(tree->dir) + 1;

        if ((maxD < maxE) && (maxE < maxC))
            menor = maxD;
        else if ((maxE < maxD) && (maxD < maxC))
            menor = maxE;
        else
            menor = maxC;
    }
    return menor;
}

int main()
{
    Arv23 *tree = criaArv23();
    int escolha = 1;

    //-----------------------------  EXPERIMENTO  ---------------------------------//
    clock_t tempoI, tempoF;
    double tf;
    char *nums[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    srand(time(NULL));
    tempoI = clock();

    printf("codigo: %s\n--> ", "984079");
    Arv23 **sn = buscaTestes(&tree, "984079", 0);
    printf("Encontrou: %s \n\n", sn == NULL ? "Nao" : "Sim");
    for (int i = 0; i < 29; i++)
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
        Arv23 **sn = buscaTestes(&tree, codigo, 0);
        printf("Encontrou: %s \n\n", sn == NULL ? "Nao" : "Sim");
    }
    tempoF = clock();
    tf = ((tempoF) - (tempoI)) * 1000 / CLOCKS_PER_SEC;
    printf("time: %.2lf ms\n", tf);

    // Naão é pedido isso, mas fiz a fim de de explicação para o relatório.
    int menorNivel = noRazo(tree);
    int maiorNivel = noFundo(tree);
    printf("Maior nivel: %d | Menor nivel: %d \n", maiorNivel, menorNivel);
    //-----------------------------------------------------------------------//

    //---------------------Menu com as opções sem ser as pedidas no experimento---------------------//
    do
    {
        printf("\nBEM-VINDO A SUA LOJA DE CALCADOS\n");
        printf("-->%3sInserir calcado[1]\n-->%3sVender calcado[2]\n-->%3sPesquisar Calcado[3]\n-->%3sCheca estoque[4]\n-->%3sSalva e Sair[5]\n-->%3sO que desja fazer: ", " ", " ", " ", " ", " ", " ");
        scanf("%d", &escolha);
        char codigo[7];
        int quantidade;

        switch (escolha)
        {
        case 1:
            printf("digite o codigo do produto: ");
            scanf("%s", codigo);
            printf("Quantidade: ");
            scanf("%d", &quantidade);
            insereCalcado(&tree, codigo, quantidade);
            break;
        case 2:
            printf("digite o codigo do produto: ");
            scanf("%s", codigo);
            printf("Quantidade: ");
            scanf("%d", &quantidade);
            vendeCalcado(&tree, codigo, quantidade);
            break;
        case 3:
            printf("digite o codigo do produto: ");
            scanf(" %s", codigo);
            Arv23 **NO = buscaCalcado(&tree, codigo);
            if (NO != NULL)
            {
                printf("%10s | %10s | %10s | %10s | %8s | %5s\n", "Codigo",
                       "Tipo",
                       "Marca",
                       "Tamanho",
                       "Quantidade",
                       "Preço");
                if (strcmp((*NO)->cod, codigo) == 0)
                {
                    printf("--------------------------------------------------------------------------\n");
                    printf("%10s | %10s | %10s | %10d | %10d | R$%5.2f\n", (*NO)->cod,
                           (*NO)->tipo,
                           (*NO)->marca,
                           (*NO)->tamanho,
                           (*NO)->quantidade,
                           (*NO)->preco);
                }
                else
                {
                    printf("--------------------------------------------------------------------------\n");
                    printf("%10s | %10s | %10s | %10d | %10d | R$%5.2f\n", (*NO)->cod2,
                           (*NO)->tipo2,
                           (*NO)->marca2,
                           (*NO)->tamanho2,
                           (*NO)->quantidade2,
                           (*NO)->preco2);
                }
                printf("--------------------------------------------------------------------------\n");
            }
            else
            {
                printf("--------------------------------------------------------------------------\n");
                printf("Calcado não registrado!\n");
                printf("--------------------------------------------------------------------------\n");
            }
            break;
        case 4:
            tabela(tree);
            break;
        default:
            gravaArv23(tree);
            break;
        }
    } while (escolha != 5);
    //--------------------------------------------------------------------------------------//

    return 0;
}
