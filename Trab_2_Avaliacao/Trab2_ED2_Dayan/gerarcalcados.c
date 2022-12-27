#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct list list;

struct list{
    char cod[7];
    char tipo[30];
    char marca[30];
    int tamanho;
    int quantidade;
    float preco;
    list *prox;
};

int verifica(list *lista, char *cod,char *marca,char *tipo, int tam){
    int repetido = 0;
    if(lista != NULL){
        if(strcmp(cod, lista->cod) == 0 ||(tam == lista->tamanho) && (strcmp(marca, lista->marca) == 0) && (strcmp(tipo, lista->tipo) == 0)){
            repetido = 1;
        }
        else
            // if(lista->prox != NULL)
            repetido = verifica(lista->prox, cod, marca, tipo, tam);
    }
    return repetido;
}

int insere(list *pai, list **lista, char *cod, char *tipo, char *marca, int tamanho, int quantidade, float preco){
    int inseriu = 0;
    if((*lista) == NULL){
        if(verifica(pai, cod,marca, tipo, tamanho) == 0){
            (*lista) = (list *) malloc(sizeof(list));
            strcpy((*lista)->cod, cod);
            strcpy((*lista)->tipo, tipo);
            strcpy((*lista)->marca, marca);
            (*lista)->tamanho = tamanho;
            (*lista)->quantidade = quantidade;
            (*lista)->preco = preco;
            (*lista)->prox = NULL;
            inseriu = 1;
        }
    }
    else
        inseriu = insere(pai,&(*lista)->prox, cod,tipo, marca, tamanho, quantidade,preco);
    return inseriu;
}


int main(){
    char *tipos[] = {"sapatenis", "social", "esporte", "bota", "rasteiro", "casual", "academia","aventura", "salto","sandalia","gladiadora","sapatilha", "chinelo"};
    char *marcas[] = {"nike", "adidas", "puma", "olympikus", "colcci", "fila", "oakley", "vans", "converse", "asics", "mizuno", "rebook", "allstar","havaianas", "rider","cartago"};
    char *nums[] = {'0', '1','2','3','4','5','6','7','8','9'};
    int *tamanhos = {33,34,35,36,37,38,39,40};
    list *lista = NULL;
    FILE *fp = fopen("calcados.txt","w");
    char codigo[7];
    char tipo[20];
    char marca[20];
    int quantidade;
    int tamanho;
    float preco;
    srand(time(NULL));
    for(int i = 0; i < 10; i ++){
        int j,k,l,m,n,o,p;
        for(j = 0; j < 6; j++){
            codigo[0] = nums[rand()%10];
            for(k = 0; k < 6; k ++){
                codigo[1] = nums[rand()%10];
                for(l = 0; l < 6; l ++){
                    codigo[2] = nums[rand()%10];
                    for(m = 0; m < 6; m ++){
                        codigo[3] = nums[rand()%10];
                        for(n = 0; n < 6; n ++){
                            codigo[4] = nums[rand()%10];
                            for(o = 0; o < 6; o ++){
                                codigo[5] = nums[rand()%10];
                            }
                            codigo[o] = '\0';
                            // printf("codigo: %s\n", codigo);
                            strcpy(tipo, tipos[rand()%13]);
                            strcpy(marca, marcas[rand()%16]);
                            quantidade = rand()%20+50;
                            tamanho = rand()%17+27;
                            preco = rand()%1000+100;
                            insere(lista, &lista, codigo, tipo, marca, tamanho, quantidade, preco);    
                        }
                    }
                }
            }
        }
    }

    for(list *p = lista; p != NULL; p = p->prox){
        fprintf(fp,"%s %s %s %d %d %.2f\n",p->cod,p->tipo,p->marca,p->tamanho,p->quantidade,p->preco);
    }

    close(fp);
    return 0;
}