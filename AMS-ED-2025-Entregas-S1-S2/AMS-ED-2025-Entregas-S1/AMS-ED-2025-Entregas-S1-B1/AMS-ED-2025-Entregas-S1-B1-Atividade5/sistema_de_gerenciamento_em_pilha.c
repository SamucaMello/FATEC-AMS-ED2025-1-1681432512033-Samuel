/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-5                                 */
/*          Objetivo: << Sistema de Gerenciamento de Pedidos usando pilha >>        */
/*                                                                                  */
/*                                  Autor: Samuel Mello de Campos e Silva           */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 32

typedef struct modelo {
    int idPedido;
    int quant;
    char status[20];
    char nomeCliente[32];
    char descPrato[32];
} Pedido;

typedef struct pilha {
    Pedido itens[MAX];
    int topo;
} Pilha;

Pilha* criarPilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha.\n");
        exit(1);
    }
    p->topo = -1;
    return p;
}

int pilha_vazia(Pilha* p) {
    return p->topo == -1;
}

int pilha_cheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void push(Pilha* p, Pedido pedido) {
    if (pilha_cheia(p)) {
        printf("Pilha cheia. Não é possível adicionar mais pedidos.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = pedido;
}

Pedido top(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("Pilha vazia.\n");
        exit(1);
    }
    return p->itens[p->topo];
}

void pop(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("Pilha vazia. Não há pedidos para remover.\n");
        return;
    }
    p->topo--;
}

void inserirPedido(Pilha* p) {
    if (pilha_cheia(p)) {
        printf("A pilha está cheia. Não é possível adicionar mais pedidos.\n");
        return;
    }

    Pedido novoPedido;
    
    printf("Digite o ID do Pedido: ");
    scanf("%d", &novoPedido.idPedido);

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novoPedido.nomeCliente);

    printf("Digite a descrição do prato: ");
    scanf(" %[^\n]", novoPedido.descPrato);

    printf("Digite a quantidade: ");
    scanf("%d", &novoPedido.quant);

    printf("Digite o status (pendente, em preparo, pronto, entregue): ");
    scanf(" %[^\n]", novoPedido.status);

    push(p, novoPedido);
}

void apagarPedido(Pilha* p, int idPedido) {
    if (pilha_vazia(p)) {
        printf("Não há pedidos na pilha para apagar.\n");
        return;
    }

    Pilha temp;
    temp.topo = -1;
    
    int encontrado = 0;

    while (!pilha_vazia(p)) {
        Pedido pedidoAtual = top(p);
        pop(p);

        if (pedidoAtual.idPedido == idPedido) {
            printf("Pedido ID %d removido.\n", pedidoAtual.idPedido);
            encontrado = 1;
            break;
        }

        push(&temp, pedidoAtual);
    }

    if (!encontrado) {
        printf("Pedido com ID %d não encontrado.\n", idPedido);
    }

    while (!pilha_vazia(&temp)) {
        push(p, top(&temp));
        pop(&temp);
    }
}

void atualizarPedido(Pilha* p, int idPedido) {
    Pilha temp;
    temp.topo = -1;
    
    int encontrado = 0;
    while (!pilha_vazia(p)) {
        Pedido pedidoAtual = top(p);
        pop(p);

        if (pedidoAtual.idPedido == idPedido) {
            printf("Digite o novo status para o pedido ID %d: ", idPedido);
            scanf(" %[^\n]", pedidoAtual.status);
            encontrado = 1;
        }

        push(&temp, pedidoAtual);
    }

    while (!pilha_vazia(&temp)) {
        push(p, top(&temp));
        pop(&temp);
    }

    if (!encontrado) {
        printf("Pedido com ID %d não encontrado.\n", idPedido);
    }
}

void obterPedido(Pilha* p, int idPedido) {
    Pilha temp;
    temp.topo = -1;

    int encontrado = 0;
    while (!pilha_vazia(p)) {
        Pedido pedidoAtual = top(p);
        pop(p);

        if (pedidoAtual.idPedido == idPedido) {
            printf("Pedido ID %d encontrado:\n", idPedido);
            printf("Nome do cliente: %s\n", pedidoAtual.nomeCliente);
            printf("Descrição do prato: %s\n", pedidoAtual.descPrato);
            printf("Quantidade: %d\n", pedidoAtual.quant);
            printf("Status: %s\n\n", pedidoAtual.status);
            encontrado = 1;
        }

        push(&temp, pedidoAtual);
    }

    while (!pilha_vazia(&temp)) {
        push(p, top(&temp));
        pop(&temp);
    }

    if (!encontrado) {
        printf("Pedido com ID %d não encontrado.\n", idPedido);
    }
}

void listarPedidos(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("Não há pedidos na pilha.\n");
        return;
    }

    Pilha temp;
    temp.topo = -1;

    while (!pilha_vazia(p)) {
        Pedido pedidoAtual = top(p);
        pop(p);

        printf("Pedido ID %d:\n", pedidoAtual.idPedido);
        printf("Nome do cliente: %s\n", pedidoAtual.nomeCliente);
        printf("Descrição do prato: %s\n", pedidoAtual.descPrato);
        printf("Quantidade: %d\n", pedidoAtual.quant);
        printf("Status: %s\n\n", pedidoAtual.status);

        push(&temp, pedidoAtual);
    }

    while (!pilha_vazia(&temp)) {
        push(p, top(&temp));
        pop(&temp);
    }
}

void liberarPilha(Pilha* p) {
    free(p);
}

int main() {
    Pilha* p = criarPilha();
    
    int opcao, idPedido;

    while (1) {
        printf("Escolha uma opção:\n");
        printf("1. Inserir Pedido\n");
        printf("2. Apagar Pedido\n");
        printf("3. Atualizar Status\n");
        printf("4. Obter Pedido\n");
        printf("5. Listar Pedidos\n");
        printf("6. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirPedido(p);
                break;
            case 2:
                printf("Digite o ID do pedido para apagar: ");
                scanf("%d", &idPedido);
                apagarPedido(p, idPedido);
                break;
            case 3:
                printf("Digite o ID do pedido para atualizar o status: ");
                scanf("%d", &idPedido);
                atualizarPedido(p, idPedido);
                break;
            case 4:
                printf("Digite o ID do pedido para obter: ");
                scanf("%d", &idPedido);
                obterPedido(p, idPedido);
                break;
            case 5:
                listarPedidos(p);
                break;
            case 6:
                liberarPilha(p);
                printf("Sistema encerrado.\n");
                return 0;
            default:
                printf("Opção inválida.\n");
        }
    }

    return 0;
}
