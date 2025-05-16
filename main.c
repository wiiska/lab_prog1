#include <stdio.h>

char clientes[10][50];
char produtos[10][50];
int total_clientes = 0;
int total_produtos = 0;

void insere_cliente() {
    if (total_clientes >= 10) {
        printf("Lista de clientes cheia!\n");
        return;
    }
    
    printf("Insira um cliente:\n");
    scanf("%s", clientes[total_clientes]);
    total_clientes++;  
}

void insere_produto() {
    if (total_produtos >= 10) {
        printf("Lista de produtos cheia!\n");
        return;
    }
    
    printf("Insira um produto:\n");
    scanf("%s", produtos[total_produtos]);
    total_produtos++; 
}

void lista_cliente() {
    printf("Funcao para listar os clientes\n");
    for(int i=0; i<total_clientes; i++){
        printf("Cliente %d: %s\n", i+1, clientes[i]);
    }
}

int main()
{
    int escolha;
    do{
    printf("Selecione uma opção: \n");
    printf("0 - Sair: \n");
    printf("1 - Inserir Cliente: \n");
    printf("2 - Inserir Produto: \n");
    printf("3 - Listar clientes: \n");
    scanf("%d", & escolha);
    
    if(escolha == 1){
        insere_cliente();
    }
    else if(escolha == 2){
        insere_produto();
    }
    else if(escolha == 3){
        lista_cliente();
    }
    }while(escolha != 0);
    
    return 0;
}
