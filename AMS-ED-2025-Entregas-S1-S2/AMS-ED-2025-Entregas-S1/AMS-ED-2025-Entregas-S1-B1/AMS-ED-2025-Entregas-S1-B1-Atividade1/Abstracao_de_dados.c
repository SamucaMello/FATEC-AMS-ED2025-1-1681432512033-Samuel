/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-1                                 */
/*             Objetivo: << Ponteiros >>                           		            */
/*                                                                                  */
/*                                  Autor: Samuel Mello de Campos e Silva           */
/*                                                                  Data:23/02/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>

void aplicarDesc(float* preco, float* prodDesc, float* precoTotal){
    
    if(*prodDesc < 0){
        *prodDesc = 0;
    }
    
    *precoTotal = *preco - ((*preco) * (*prodDesc)  / 100.0);
}

int main(){
    char 
        nomeProd[32];
    
    float 
        preco,
        prodDesc,
        precoTotal;
    
    float 
        *precoPtr      = &preco,
        *prodDescPtr   = &prodDesc,
        *precoTotalPtr = &precoTotal;
 
    
    printf("Coloque o nome do produto:\nNome: ");
    scanf("%s", nomeProd);
    
    printf("Coloque o preço do produto:\nR$:");
    scanf("%f", precoPtr);
    
    printf("Coloque o desconto do produto:\n");
    scanf("%f", prodDescPtr);
    
    aplicarDesc(precoPtr, prodDescPtr, precoTotalPtr);

    
    printf("\n\nResultado:\nNome do produto: %s\nPreço Inicial: %.2fR$\nDesconto: %.2f\nPreço total com desconto: %.2fR$\n",
        nomeProd, *precoPtr, *prodDescPtr, *precoTotalPtr
    );
   
    return 0;
}
