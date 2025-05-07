/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: AMS-ED-2025-Entregas-S1-B2-Atividade2   */
/*            Objetivo: << Algoritmo de ordenação Bubble Sort >>                    */
/*                                                                                  */
/*                                  Autor: Samuel Mello de Campos e Silva           */
/*                                                                  Data:07/05/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5

void inserir_numeros(int numArray[]){
    int numero;
    for(int i = 1; i < MAX+1; i++){
        printf("Adicione o %d° número: ", i);
        scanf(" %d", &numero);
        numArray[i-1] = numero;
    }
    printf("Números gravados com sucesso!\n");

}

void bubble_sort(int numArray[]){
        int tam = MAX - 1;
        for(int i = 0; i < tam; i++) {
            
            for(int j = 0; j < tam - i; j++){
                int atual = numArray[j];
                int prox = numArray[j + 1];
                
                if(prox < atual){
                    numArray[j + 1] = atual;
                    numArray[j] = prox;
                }
                
            }
        }
        printf("Números organizados!\n");
}

void imprimir_numeros(int numArray[]){
    printf("Seus números em ordem: ");
    for(int i = 0 ; i < MAX ; i++){
        printf("%d ", numArray[i]);
    }
}


void mostrar_menu() {
    printf("Selecione uma opção:\n");
    printf("1 - Organizar 5 números\n");
    printf("2 - Sair\n");
}

void iniciar_programa(){
   int numArray[MAX];
   int opcao;
   while(opcao != 2){
       mostrar_menu();
       scanf("%d", &opcao);
       
       switch(opcao){
           case 1:
                inserir_numeros(numArray);
                bubble_sort(numArray);
                imprimir_numeros(numArray);
                break;
            case 2:
                printf("Saindo...");
                break;
            
            default:
                printf("Opção inválida.\n");
                break;
       }
   }
    
}

int main() {
    iniciar_programa();
    return 0;
}