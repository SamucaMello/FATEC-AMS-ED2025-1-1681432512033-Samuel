/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-4                                 */
/*             Objetivo: << Calculadora RPN >>                                      */
/*                                                                                  */
/*                                  Autor: Samuel Mello de Campos e Silva           */
/*                                                                  Data:01/04/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_PILHA 32

typedef struct modeloPilha {
    char* pilha[MAX_PILHA];
    int top;
} Pilha;

Pilha* criarPilha() {
    Pilha* novaPilha = (Pilha*) malloc(sizeof(Pilha));
    if(novaPilha == NULL){
        printf("Não foi possível criar a pilha\n");
        return NULL;
    }
    novaPilha->top = -1;
    return novaPilha;
}

int pilha_cheia(Pilha* pilha) {
    return pilha->top == (MAX_PILHA - 1);
}

int pilha_vazia(Pilha* pilha) {
    return pilha->top == -1;
}

void push(Pilha* pilha, char* valor) {
    if(pilha_cheia(pilha)) {
        printf("A pilha está cheia\n");
        return;
    }
    pilha->top++;
    pilha->pilha[pilha->top] = strdup(valor);
}

char* pop(Pilha* pilha) {
    if(pilha_vazia(pilha)) {
        printf("A pilha está vazia\n");
        return NULL;
    }
    char* valor = pilha->pilha[pilha->top];
    pilha->top--;
    return valor;
}

char* top(Pilha* pilha) {
    if (pilha_vazia(pilha)) return NULL;
    return pilha->pilha[pilha->top];
}

void calcular(Pilha* pilha) {
    Pilha* pilhaAux = criarPilha();
    if (pilhaAux == NULL) return;

    for (int i = 0; i <= pilha->top; i++) {
        char* valor = pilha->pilha[i];

        if (strcmp(valor, "+") == 0 || strcmp(valor, "-") == 0 || 
            strcmp(valor, "*") == 0 || strcmp(valor, "/") == 0) {
            
            if (pilhaAux->top < 1) {
                printf("Erro: Expressão inválida\n");
                return;
            }

            double opc2 = atof(pop(pilhaAux)); 
            double opc1 = atof(pop(pilhaAux));
            double resultado = 0.0;

            switch(valor[0]){
                case '+': resultado = opc1 + opc2; break;
                case '-': resultado = opc1 - opc2; break;
                case '*': resultado = opc1 * opc2; break;
                case '/':
                    if(opc2 == 0){
                        printf("Erro: Divisão por 0\n");
                        return;
                    }
                    resultado = opc1 / opc2;
                    break;
            }
            
            char* resultadoStr = (char*)malloc(MAX_PILHA * sizeof(char));
            snprintf(resultadoStr, MAX_PILHA, "%f", resultado);
            push(pilhaAux, resultadoStr);
        } else {
            push(pilhaAux, valor);
        }
    }

    if (pilhaAux->top == 0) {
        printf("Resultado: %s\n", top(pilhaAux));
    } else {
        printf("Erro: Expressão mal formatada\n");
    }

    while (!pilha_vazia(pilhaAux)) {
        free(pop(pilhaAux));
    }
    free(pilhaAux);
}

int main() {
    Pilha* pilha = criarPilha();
    if (pilha == NULL) return 1;

    char conta[100];
    printf("Coloque a conta em RPN: ");
    
    fgets(conta, sizeof(conta), stdin);
    conta[strcspn(conta, "\n")] = 0;

    char* temp = strtok(conta, " ");
    
    while(temp != NULL){
        push(pilha, temp);
        temp = strtok(NULL, " ");
    }

    calcular(pilha);

    while (!pilha_vazia(pilha)) {
        free(pop(pilha));
    }
    free(pilha);
    
    return 0;
}
