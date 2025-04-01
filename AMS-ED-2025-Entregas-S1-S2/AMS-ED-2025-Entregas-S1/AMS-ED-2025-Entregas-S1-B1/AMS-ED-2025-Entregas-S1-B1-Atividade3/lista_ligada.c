/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-3                                 */
/*             Objetivo: << Lista ligada para restaurante >>                        */
/*                                                                                  */
/*                                  Autor: Samuel Mello de Campos e Silva           */
/*                                                                  Data:25/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct modelo {
    int 
      idPedido,
      quant;
      
    char
      status[20],
      nomeCliente[32],
      descPrato[32];
      
    struct modelo* prox;
  } Pedido;

void adicionarPedido(Pedido** inicio, char nomeCliente[], char descPrato[], char status[],  int quant, int idPedido){
    Pedido* novoPedido = (Pedido*)malloc(sizeof(Pedido));
    
    
    if(novoPedido == NULL){
        printf("Algo deu errado na alocação de memória dinâmica");
       return;
    }
    
    strcpy(novoPedido->nomeCliente, nomeCliente);
    strcpy(novoPedido->descPrato, descPrato);
    strcpy(novoPedido->status, status);
    novoPedido->quant = quant;
    novoPedido->idPedido = idPedido;
    novoPedido->prox = *inicio;
    *inicio = novoPedido;
}

void mostrarInfoDoPedido(Pedido* temp){
    printf("Pedido (%d):\nQuantidade -> (%d)\nNome do cliente -> '%s'\nStatus -> (%s)\nDescrição do prato -> %s\n\n",
                temp->idPedido, temp->quant, temp->nomeCliente, temp->status, temp->descPrato
    );
}
void listarPedidos(Pedido** inicio){
    Pedido* temp = *inicio;
    
    if(temp == NULL){
        printf("Não há pedidos na lista.\n");
        return;
    }
    
    while(temp !=NULL){
        mostrarInfoDoPedido(temp);
        temp = temp->prox;
    }
}

void listarUmPedido(Pedido** inicio, int idPedido){
    Pedido *temp = *inicio;
    
    while(temp != NULL){
        if(temp->idPedido == idPedido) {
            mostrarInfoDoPedido(temp);
            return;
        }
        temp = temp->prox;
    }
    printf("Pedido com ID %d não encontrado.\n", idPedido);
}

void atualizarPedido(Pedido** inicio, int idPedido, char novoStatus[]){
    Pedido *temp = *inicio;
    
    while(temp!=NULL){
        if(temp->idPedido == idPedido){
            strcpy(temp->status, novoStatus);
            return;
        }
        temp = temp->prox;
    }
    printf("Pedido com ID %d não encontrado\n", idPedido);
};

void apagarPedido(Pedido** inicio, int idPedido){
    if(*inicio == NULL) return;
    
    Pedido
        *temp = *inicio,
        *anterior = NULL;
    
    if(temp->idPedido == idPedido){
        printf("Pedido %d apagado.\n", idPedido);
        free(temp);
        return;
    }
    
    while(temp!=NULL && temp->idPedido != idPedido){
        anterior = temp;
         temp = temp->prox;
    }
    if(temp == NULL){
        printf("Pedido com ID %d não encontrado.\n", idPedido);
        return;
    }
    printf("Pedido %d apagado.\n", idPedido);
    anterior->prox = temp->prox;
    free(temp);
}

void liberarLista(Pedido** inicio) {
    Pedido* temp;
    
    while (*inicio != NULL) {
        temp = *inicio;        
        *inicio = (*inicio)->prox;
        free(temp);            
    }
}

void finalizarPrograma(Pedido** inicio, Pedido** molde){
    
    printf("======/Listando pedidos/=====\n");
    listarPedidos(inicio);
    printf("=========/fim/======\n");
    
    printf("Liberando lista...\n");
    liberarLista(inicio);
    liberarLista(molde);
    printf("Encerrando programa...\n");
}

int main() {
    Pedido
        *inicio = NULL,
        *molde = (Pedido*) malloc(sizeof(Pedido));

    char 
        opc,
        continuarOpc;
        


    while (1) {
        printf("Selecione alguma opção:\n1 -> Adicionar um pedido\n2 -> Atualizar o status de um pedido\n3 -> Apagar um pedido\n4 -> Obter um pedido pelo id\n5 -> Listar todos os pedidos\n6 -> Finalizar programa\n\n");
        scanf(" %c", &opc); 
        
        
        
        switch (opc - '0') {
            
        case 1:
            printf("Coloque o nome Cliente: ");
            scanf(" %31[^\n]", molde->nomeCliente);
            printf("Coloque uma descrição breve do pedido: ");
            scanf(" %31[^\n]", molde->descPrato);

            printf("Coloque o status do pedido (pendente, em preparo, pronto, entregue): ");
            scanf(" %19[^\n]", molde->status);

            printf("Coloque o id do pedido: ");
            scanf("%d", & molde->idPedido);

            printf("Coloque a quantidade do pedido: ");
            scanf("%d", & molde->quant);

            adicionarPedido(&inicio, molde->nomeCliente, molde->descPrato, molde->status, molde->quant, molde->idPedido);
            break;

        case 2:
            printf("Coloque o id do pedido que será atualizado: ");
            scanf("%d", &molde->idPedido);
            printf("Coloque um novo status para esse pedido: ");
            scanf(" %19[^\n]", molde->status);
            atualizarPedido( & inicio, molde->idPedido, molde->status);
            break;

        case 3:
            printf("Coloque o id do pedido que será apagado: ");
            scanf("%d", &molde->idPedido);
            apagarPedido(&inicio, molde->idPedido);
            break;

        case 4:
            printf("Coloque o id do pedido: ");
            scanf("%d", &molde->idPedido);
            listarUmPedido( &inicio, molde->idPedido);
            break;
            
        case 5:
            listarPedidos(&inicio);
            break;

        case 6:
            finalizarPrograma(&inicio, &molde);
            return 0;
            break;

        default:
            printf("Escolha uma opção válida.\n");
            continue;
            break;
      }
      
      while (1) {
        printf("Deseja continuar? [s/n]\n");
        scanf(" %c", &continuarOpc);
        switch (tolower(continuarOpc)) {
        case 's':
            break;
        case 'n':
             finalizarPrograma(&inicio, &molde);    
            return 0;
            break;
        default:
            printf("Escolha entre 's' ou 'n'.\n");
            break;
        }
        if (continuarOpc == 'n' || continuarOpc == 's') {
            break;
        }
      }
}
    

  return 0;
}
