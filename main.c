#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CLIENTES 100
#define MAX_PRODUTOS 100
#define MAX_VENDAS 100
#define MAX_ITENS 10

typedef struct {
    int id;
    char nome[100];
    char cpf[20];
} Cliente;

typedef struct {
    int id;
    char nome[100];
    float preco;
    int estoque;
} Produto;

typedef struct {
    int id_produto;
    int quantidade;
    float valor_unitario;
} ItemVenda;

typedef struct {
    int id_venda;
    int id_cliente;
    char data[20];
    ItemVenda itens[MAX_ITENS];
    int total_itens;
    float total_nota;
} Venda;

Cliente clientes[MAX_CLIENTES];
Produto produtos[MAX_PRODUTOS];
Venda vendas[MAX_VENDAS];

int qtd_clientes = 0, qtd_produtos = 0, qtd_vendas = 0;

void cadastrar_cliente() {
    Cliente c;
    c.id = qtd_clientes + 1;
    printf("Nome: ");
    scanf("%s", c.nome);
    printf("CPF: ");
    scanf("%s", c.cpf);
    clientes[qtd_clientes++] = c;
    printf("Cliente cadastrado com sucesso!\n");
}

void listar_clientes() {
    for (int i = 0; i < qtd_clientes; i++) {
        printf("ID: %d | Nome: %s | CPF: %s\n", clientes[i].id, clientes[i].nome, clientes[i].cpf);
    }
}

void atualizar_cliente() {
    int id;
    printf("ID do cliente para atualizar: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].id == id) {
            printf("Novo nome: ");
            scanf("%s" , clientes[i].nome);
            printf("Novo CPF: ");
            scanf("%s", clientes[i].cpf);
            printf("Cliente atualizado!\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

void excluir_cliente() {
    int id;
    printf("ID do cliente para excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd_clientes; i++) {
        if (clientes[i].id == id) {
            clientes[i].id = 0;
            printf("Cliente excluido.\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

void cadastrar_produto() {
    Produto p;
    p.id = qtd_produtos + 1;
    printf("Nome: ");
    scanf("%s", p.nome);
    printf("Preco: ");
    scanf("%f", &p.preco);
    printf("Estoque: ");
    scanf("%d", &p.estoque);
    produtos[qtd_produtos++] = p;
    printf("Produto cadastrado com sucesso!\n");
}

void listar_produtos() {
    for (int i = 0; i < qtd_produtos; i++) {
        printf("ID: %d | Nome: %s | Preco: R$ %.2f | Estoque: %d\n",
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].estoque);
    }
}

void atualizar_produto() {
    int id;
    printf("ID do produto para atualizar: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].id == id) {
            printf("Novo nome: ");
            scanf("%s" , produtos[i].nome);
            printf("Novo preco: ");
            scanf("%f", &produtos[i].preco);
            printf("Novo estoque: ");
            scanf("%d", &produtos[i].estoque);
            printf("Produto atualizado!\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void excluir_produto() {
    int id;
    printf("ID do produto para excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd_produtos; i++) {
        if (produtos[i].id == id) {
            produtos[i].id = 0;
            printf("Produto excluido.\n");
            return;
        }
    }
    printf("Produto nao encontrado.\n");
}

void cadastrar_venda() {
    Venda v;
    v.id_venda = qtd_vendas + 1;
    printf("ID do cliente: ");
    scanf("%d", &v.id_cliente);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(v.data, sizeof(v.data), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    printf("Quantidade de itens: ");
    scanf("%d", &v.total_itens);
    v.total_nota = 0;

    for (int i = 0; i < v.total_itens; i++) {
        ItemVenda item;
        printf("ID do produto: ");
        scanf("%d", &item.id_produto);
        printf("Quantidade: ");
        scanf("%d", &item.quantidade);

        Produto *prod = &produtos[item.id_produto - 1];
        if (prod->estoque < item.quantidade) {
            printf("Estoque insuficiente!\n");
            return;
        }

        item.valor_unitario = prod->preco;
        prod->estoque -= item.quantidade;

        v.itens[i] = item;
        v.total_nota += item.quantidade * item.valor_unitario;
    }

    vendas[qtd_vendas++] = v;
    printf("Venda registrada com sucesso! Total: R$ %.2f\n", v.total_nota);
}

void listar_vendas() {
    for (int i = 0; i < qtd_vendas; i++) {
        Venda v = vendas[i];
        printf("Venda ID: %d | Cliente ID: %d | Data: %s\n", v.id_venda, v.id_cliente, v.data);
        for (int j = 0; j < v.total_itens; j++) {
            printf("  Produto ID: %d | Quantidade: %d | Valor unitario: R$ %.2f\n",
                   v.itens[j].id_produto, v.itens[j].quantidade, v.itens[j].valor_unitario);
        }
        printf("Total: R$ %.2f\n", v.total_nota);
    }
}

void excluir_venda() {
    int id;
    printf("ID da venda para excluir: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd_vendas; i++) {
        if (vendas[i].id_venda == id) {
            vendas[i].id_venda = 0;
            printf("Venda excluida.\n");
            return;
        }
    }
    printf("Venda nao encontrada.\n");
}

void atualizar_venda() {
    int id;
    printf("ID da venda para atualizar: ");
    scanf("%d", &id);
    for (int i = 0; i < qtd_vendas; i++) {
        if (vendas[i].id_venda == id) {
            Venda *v = &vendas[i];
            printf("Novo ID do cliente: ");
            scanf("%d", &v->id_cliente);

            printf("Nova quantidade de itens: ");
            scanf("%d", &v->total_itens);
            v->total_nota = 0;

            for (int j = 0; j < v->total_itens; j++) {
                ItemVenda item;
                printf("ID do produto: ");
                scanf("%d", &item.id_produto);
                printf("Quantidade: ");
                scanf("%d", &item.quantidade);

                Produto *prod = &produtos[item.id_produto - 1];
                if (prod->estoque < item.quantidade) {
                    printf("Estoque insuficiente!\n");
                    return;
                }

                item.valor_unitario = prod->preco;
                prod->estoque -= item.quantidade;

                v->itens[j] = item;
                v->total_nota += item.quantidade * item.valor_unitario;
            }

            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            snprintf(v->data, sizeof(v->data), "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

            printf("Venda atualizada com sucesso! Total: %.2f\n", v->total_nota);
            return;
        }
    }
    printf("Venda nao encontrada.\n");
}

int main() {
    int opcao;
    do {
        printf("\n1. Cadastrar Cliente\n2. Listar Clientes\n3. Atualizar Cliente\n4. Excluir Cliente\n");
        printf("5. Cadastrar Produto\n6. Listar Produtos\n7. Atualizar Produto\n8. Excluir Produto\n");
        printf("9. Cadastrar Venda\n10. Listar Vendas\n11. Excluir Venda\n12. Atualizar Venda\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: cadastrar_cliente(); break;
            case 2: listar_clientes(); break;
            case 3: atualizar_cliente(); break;
            case 4: excluir_cliente(); break;
            case 5: cadastrar_produto(); break;
            case 6: listar_produtos(); break;
            case 7: atualizar_produto(); break;
            case 8: excluir_produto(); break;
            case 9: cadastrar_venda(); break;
            case 10: listar_vendas(); break;
            case 11: excluir_venda(); break;
            case 12: atualizar_venda(); break;
        }
    } while (opcao != 0);
    return 0;
}
