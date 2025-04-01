/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: << Utilização de array >>       		            */
/*                                                                                  */
/*                                  Autor: Samuel Mello de Campos e Silva           */
/*                                                                  Data:12/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define quantPE 4 
#define quantAC 5 
#define quantPP 10
#define quantEB 3
#define quantNomeCandi 32
#define maxCandi 50

typedef struct modeloCandidato {
    char 
	nome[quantNomeCandi];

    float 
        somaPE,
        somaAC,
        somaPP,
        somaEB,
    
        notaPE[quantPE],
        notaAC[quantAC],
        notaPP[quantPP],
        notaEB[quantEB],
        notaFinal;
} Candidato;

void somaNotasCentrais(float* notasArr, int tam, float* campo){
    float 
        maior = notasArr[0],
        menor = notasArr[0],
        soma = 0;
        
    
    for(int i = 0; i < tam; i++){
        if(notasArr[i] < menor){
            menor = notasArr[i];
        }
        if(notasArr[i] > maior){
            maior = notasArr[i];
        }
        soma += notasArr[i];
    }
    soma -= (maior + menor);
    
    *campo = soma;
}


void perguntarNota(char nomeProva[], float* notaArr, int quantProva, float * campo) {
  float tempNota;
  for (int i = 0; i < quantProva; i++) {
    printf("Digite a nota da prova %s (%d): ", nomeProva, i + 1);
    scanf("%f", & tempNota);
    if (tempNota < 0 || tempNota > 10) {
      printf("Nota inválida! A nota deve estar entre 0 e 10.\n");
      i--;
    } else {
      notaArr[i] = tempNota;
    }
  }

  somaNotasCentrais(notaArr, quantProva, campo);

}

void calcularNotaFinal(Candidato *c) {
    c->notaFinal = (c->somaPE * 0.3) + (c->somaAC * 0.1) + (c->somaPP * 0.4) + (c->somaEB * 0.2);
}

int compararNotaFinal(const void *a, const void *b) {
    Candidato 
	  *candidatoA = (Candidato *)a,
    	  *candidatoB = (Candidato *)b;

    float 
        NFcandiA = candidatoA->notaFinal,
        NFcandiB = candidatoB->notaFinal;
        
    if (NFcandiA > NFcandiB) {
        return -1;
    } else if (NFcandiA < NFcandiB) {
        return 1;
    } else {
        return 0;
    }
}


int main() {
    Candidato candidatos[maxCandi];
    int qtdCandidatos = 0;
   
    
    while (qtdCandidatos < maxCandi) {
        Candidato* c = &candidatos[qtdCandidatos];
        
        printf("Digite o nome do candidato: ");
        scanf("%s", c->nome);
	
        perguntarNota("PE", c->notaPE, quantPE, &c->somaPE);
        perguntarNota("AC", c->notaAC, quantAC, &c->somaAC);
        perguntarNota("PP", c->notaPP, quantPP, &c->somaPP); 
        perguntarNota("EB", c->notaEB, quantEB, &c->somaEB); 
        calcularNotaFinal(c);
        qtdCandidatos++;
        
	char opc = '\0';
	while (opc != 's' && opc != 'n'){
            printf("Deseja cadastrar outro candidato? [s/n]: ");
            scanf(" %c", &opc);
            opc = tolower(opc);  
            if (opc != 's' && opc != 'n') {
                printf("Opção inválida, escolha entre 's' ou 'n'.\n");
            }
        } 
        if(opc == 'n') break;
    }

    qsort(candidatos, qtdCandidatos, sizeof(Candidato), compararNotaFinal);

    int qtdExibir = 5;
    if(qtdCandidatos < qtdExibir){
        qtdExibir = qtdCandidatos;
    }
    
    printf("\nOs melhores %d candidatos:\n", qtdExibir);
    for (int i = 0; i < qtdExibir; i++) {
        printf("%d. '%s' - Nota Final: %.2f\n", i + 1, candidatos[i].nome, candidatos[i].notaFinal);
    }

    return 0;
}
